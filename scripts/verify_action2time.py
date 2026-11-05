#!/usr/bin/env python3
"""Retail-instruction differential for the beAction2 timing/completion slice.

Executes the ORIGINAL retail instructions of

    0x00230110 float->int64          0x00398e80 node clock
    0x003a7a20/d00/d80/e90/fd0 timer group
    0x00376340/0x003764c0 WAITCHECK Update/Start
    0x00376de0/0x00376f40 JOINTSET Update/Start
    0x00377700 StartComponents       0x003778d0 per-frame driver
    0x00377990 vfunc_33, message case ISCOMEND only

on an R5900 interpreter (scripts/ee_core.py: exact 64-bit integers; EE
single-precision arithmetic on bit patterns, never host floats), and runs the
recovered C (recovered/frontend/action2time.c, eefloat.c) in the same world.
Everything the module calls that is NOT in this list -- property-list lookup,
allocation, string interning, the FADESET/MOTIONSET/FLASHSET handlers, the
0x1dd4b0/0x1af510 motion helpers, the messenger -- is a leaf: both sides see
the same stub, and the comparison covers

  * the ordered leaf calls with their meaningful arguments (32/64-bit exact),
  * the ordered non-stack stores (8-byte stores as low,high words),
  * the final memory image, and the returned value where defined,
  * instruction coverage: every statically reachable address of every body.

Threshold, ordering and multi-tick expectations are ALSO asserted against
independent Python integer arithmetic, so the comparison cannot pass by both
sides sharing a misreading.

Not established: the source and cadence of the system clock (sys+0x50), the
EE FPU rounding model on hardware, the leaves' own behaviour, rendering.
"""
import argparse
import ctypes as C
import hashlib
from pathlib import Path
import random
import struct
import subprocess
import tempfile
from ee_core import EE, MASK, M32, sx, f_mul, f_div, f_add, f_from_i32, f_trunc_w, f_cmp, f_parts
from verify_loadintf2 import PEEK, POKE, CALL

ROOT = Path(__file__).resolve().parents[1]
CALL64 = C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_int32, C.POINTER(C.c_int64))
STACK_LO, STACK_HI = 0x01f00000, 0x02000000
TMP_LO, TMP_HI = 0x01060000, 0x01070000          # A2_SCRATCH
GPFLAG = 0x554c14
G_RHYTHM, G_TYPE, G_POOLROOT = 0x58a348, 0x585be0, 0x587110
G_CLS = {'MOTION': 0x589fe8, 'JOINT': 0x589fc8, 'FADE': 0x589fb0, 'WAIT': 0x589fa0, 'FLASH': 0x589f98}
CLS_ID = {'MOTION': 0x7001, 'JOINT': 0x7002, 'FADE': 0x7003, 'WAIT': 0x7004, 'FLASH': 0x7005}
TIMER_NAME, FADE_NAME, EMPTY = 0x50dfd8, 0x50dfe0, 0x4e0858

(MGR, SYS, MSGR, MGR2, ROBJ, RVT, RFN) = range(0x1400000, 0x1400700, 0x100)
ACT, NODE, WORK, DATA, CLIST, CARR, MOBJ = range(0x1410000, 0x1410700, 0x100)
X20, MLST, MARR, MELEM, MW2, MPP, MM, MQ = range(0x1411000, 0x1411800, 0x100)
CVT, GETMETA = 0x1412000, 0x1412100
COMP0 = 0x1413000                                  # + 0x100 per component
STR0 = 0x1415000                                   # component strings
POOLTOK, POOLTOK2 = 0x1450000, 0x1450100
LIST0, TIMER0 = 0x1460000, 0x1470000               # allocator arenas

ELF_SHA1 = 'ffad4dab663cb290190bdfa34a8016d616a1652a'


class Range:
    def __init__(self, lo, hi):
        self.lo, self.hi = lo, hi

    def __contains__(self, a):
        return self.lo <= a < self.hi


class Union:
    def __init__(self, *parts):
        self.parts = parts

    def __contains__(self, a):
        return any(a in p for p in self.parts)


def symbol_sizes():
    sizes = {}
    for line in (ROOT / 'config/SLUS-20836/symbols.txt').read_text().splitlines():
        parts = line.split()
        if len(parts) >= 3:
            try:
                sizes[int(parts[0], 16)] = int(parts[1], 16)
            except ValueError:
                pass
    return sizes


# Every retail body the C implements (sizes come from config/SLUS-20836/symbols.txt).
ENTRIES = (0x230110, 0x398e80, 0x3a7a20, 0x3a7d00, 0x3a7d80, 0x3a7e90, 0x3a7fd0, 0x376340, 0x3764c0,
           0x376de0, 0x376f40, 0x377700, 0x3778d0)
_SIZES = symbol_sizes()
BODIES = {a: _SIZES[a] for a in ENTRIES}
MODULE = frozenset(BODIES) | {0x377990}
SOFTFLOAT = Range(0x22e000, 0x231000)
# Statically reachable but dynamically unreachable retail instructions.
#   0x376540..48: WAITCHECK_Start 'R' path substitutes the empty string for a null
#                 type name, but a null name never reaches the 'R' test (EMPTY[0] is 0).
#   0x376e70/74:  JOINTSET_Update's in-loop "neither state" exit; the state was
#                 already checked to be 1 or 2 and nothing changes it mid-loop.
DEAD = {0x3764c0: {0x376540, 0x376544, 0x376548}, 0x376de0: {0x376e70, 0x376e74}}
# Leaf argument specs: i=int32 q=int64 p=pointer (stack/scratch normalised) -=unobserved.
LEAF = {
    0x301000: 'p', 0x2f88e0: 'i', 0x36ae80: 'i', 0x2ff820: 'p', 0x36a510: 'i', 0x2fecb0: 'pi',
    0x301e30: 'pp', 0x3022c0: 'pii', 0x100610: 'p', 0x1dd4b0: 'qqp', 0x1af510: 'pq',
    0x377340: 'ppp', 0x376930: 'ppp', 0x375ff0: 'ppp', 0x377090: 'pp', 0x376680: 'pp',
    0x375e70: 'pp', 0x36dcd0: 'p', 0x38d4a0: 'pii', 0x38f150: 'pi', 0x377700: 'pp',
    GETMETA: 'p', RFN: 'p',
}


def i32(v):
    return sx(v & M32, 32)


class World:
    """Memory plus the leaf stubs.  One instance per side; `options` fully
    determines behaviour, so both sides see identical leaves."""

    def __init__(self, image, **options):
        self.image = image
        self.mem = {}
        self.trace = []
        self.options = dict(options)
        self.timers = {}
        self.names = {}
        self.next_list, self.next_timer = LIST0, TIMER0
        self.list_calls = 0
        self.sizes = {}
        self.setup()

    # -- memory ----------------------------------------------------------
    def read(self, a, n):
        a &= M32
        if 0x100000 <= a and a + n <= 0x554b00:
            o = a - 0x100000 + 0x80
            return int.from_bytes(self.image[o:o + n], 'little')
        return sum(self.mem.get(a + i, 0) << (8 * i) for i in range(n))

    def hidden(self, a):
        return STACK_LO <= a < STACK_HI or TMP_LO <= a < TMP_HI

    def write(self, a, n, v):
        a &= M32
        v &= (1 << (8 * n)) - 1
        for i in range(n):
            self.mem[a + i] = (v >> (8 * i)) & 255
        if not self.hidden(a):
            if n == 8:
                self.trace.append(('write', a, 4, v & M32))
                self.trace.append(('write', a + 4, 4, v >> 32))
            else:
                self.trace.append(('write', a, n, v))

    def w32(self, a, v):
        self.write(a, 4, v)

    def w64(self, a, v):
        self.write(a, 8, v)

    def snapshot(self):
        return {a: v for a, v in self.mem.items() if not self.hidden(a)}

    # -- world construction ---------------------------------------------
    def setup(self):
        o, w32 = self.options, self.w32
        w32(MGR + 0xc, SYS); w32(MGR + 0x10, MGR2); w32(MGR + 0x14, MSGR)
        w32(MGR2 + 0x30, ROBJ); w32(ROBJ, RVT); w32(RVT + 0x60, RFN)
        self.w64(SYS + 0x50, o.get('clock', 0))
        w32(ACT + 8, o.get('idx', 0)); w32(ACT + 0xc, DATA); w32(ACT + 0x10, MGR)
        self.write(ACT + 0x14, 1, o.get('active', 1)); w32(ACT + 0x2c, NODE); w32(ACT + 0x38, WORK)
        w32(ACT + 0x28, o.get('list', 0))
        w32(NODE + 0x78, o.get('scale', 0x3f800000)); self.w64(NODE + 0x80, o.get('bias', 0))
        self.write(GPFLAG, 1, o.get('gpflag', 0))
        w32(G_POOLROOT, POOLTOK2); w32(G_TYPE, 0x5a5a)
        w32(G_RHYTHM, o.get('global', 0x42f00000))
        for k, g in G_CLS.items():
            w32(g, CLS_ID[k])
        w32(WORK + 0x44, o.get('wait', 0)); w32(WORK + 0x1c, o.get('joint', 0))
        w32(WORK + 0x14, o.get('motion', 0)); w32(WORK + 0x34, o.get('fade', 0))
        w32(WORK + 0x48, o.get('flash', 0)); self.write(WORK + 0x4c, 1, o.get('freeze', 0))
        self.write(WORK + 0x30, 1, o.get('jisend', 0))
        self.w64(WORK + 0x20, o.get('jstart', 0)); self.w64(WORK + 0x28, o.get('jend', 0))
        w32(WORK + 4, o.get('work_refs', 1))
        w32(WORK + 8, DATA); w32(WORK + 0xc, o.get('comindex', 0))
        w32(DATA + 0xc, CLIST); w32(CLIST + 0x10, CARR)
        w32(CVT + 0x58, GETMETA)
        if o.get('timer') is not None:           # (duration, base, scale, refs)
            d, b, s, refs = o['timer']
            self.add_timer(TIMER_NAME, d, b, s, refs)
        if 'chain' in o:
            self.motion_chain(**o['chain'])
        self.trace = []

    def add_timer(self, name, duration, base, scale, refs=1):
        t = self.next_timer
        self.next_timer += 0x100
        self.w32(t + 4, refs); self.w32(t + 0x10, scale)
        self.w64(t + 0x18, base); self.w64(t + 0x20, duration)
        self.timers[name] = t
        if not self.read(ACT + 0x28, 4):
            lst = self.next_list
            self.next_list += 0x100
            self.w32(lst + 4, 1); self.w32(ACT + 0x28, lst)
        return t

    def set_components(self, comps):
        """comps: list of (class, type string, f1, f2, loop string)."""
        self.w32(CLIST + 8, len(comps))
        for i, (cls, text, f1, f2, loop) in enumerate(comps):
            c = COMP0 + 0x100 * i
            s = STR0 + 0x40 * i
            self.w32(CARR + 4 * i, c)
            self.w32(c, CVT); self.w32(c + 0x20, CLS_ID[cls])
            data = text.encode() + b'\0' + loop.encode() + b'\0'
            for k, b in enumerate(data):
                self.write(s + k, 1, b)
            self.w32(c + 8, s if text is not None else 0)
            self.w32(c + 0xc, f1); self.w32(c + 0x10, f2)
            self.w32(c + 0x14, s + len(text) + 1)
        self.trace = []

    def motion_chain(self, flag=1, cur=0, q20=0, q28=0, q30=0, m28=0):
        self.w32(DATA + 0x20, X20); self.w32(X20 + 0x24, MLST); self.w32(MLST + 0x10, MARR)
        self.w32(MARR + 4 * self.options.get('idx', 0), MELEM)
        self.w32(MELEM + 0x38, MW2); self.w32(MW2 + 8, flag)
        self.w32(MW2 + 0x10, MPP); self.w32(MPP, MM); self.w32(MM + 8, MQ)
        self.w64(MM + 0x28, cur); self.w64(MQ + 0x20, q20); self.w64(MQ + 0x28, q28)
        self.w64(MQ + 0x30, q30)

    # -- leaves ------------------------------------------------------------
    def call(self, addr, a):
        assert addr in LEAF, hex(addr)
        spec = LEAF[addr]
        ev = []
        for k, ch in enumerate(spec):
            v = a[k]
            if ch == 'q':
                ev.append(sx(v, 64))
            else:
                u = v & M32
                ev.append(0 if (ch == 'p' and (self.hidden(u))) else sx(u, 32))
        self.trace.append(('call', addr, *ev))
        o = self.options
        if addr == 0x301000:
            return POOLTOK
        if addr == 0x2f88e0:
            return POOLTOK2
        if addr == 0x36ae80:
            self.list_calls += 1
            if o.get('null_list_calls', 0) >= self.list_calls:
                return 0
            if o.get('list_side') is not None:        # the leaf itself installs a list
                self.w32(LIST0 + 0x8004, o['list_side'])
                self.w32(ACT + 0x28, LIST0 + 0x8000)
            p = self.next_list
            self.next_list += 0x100
            self.w32(p + 4, o.get('list_refs', 1))
            return p
        if addr == 0x36a510:
            p = self.next_timer
            self.next_timer += 0x100
            self.w32(p + 4, o.get('timer_refs', 1)); self.w32(p + 0x10, o.get('tscale', 0x3f800000))
            return p
        if addr == 0x2fecb0:
            self.names[i32(a[0])] = i32(a[1])
            return 0
        if addr == 0x301e30:
            t = i32(a[1])
            self.w32(t + 4, self.read(t + 4, 4) + 1)
            self.timers[self.names[t]] = t
            return 0
        if addr == 0x3022c0:
            return self.timers.get(i32(a[2]), 0)
        if addr == 0x1dd4b0:
            self.write(i32(a[2]), 8, (a[0] ^ a[1]) & MASK)
            return 0
        if addr == 0x1af510:
            self.w64(i32(a[0]) + 0x28, (a[1] + o.get('m_off', 0)) & MASK)
            return 0
        if addr in (0x377340, 0x376930, 0x375ff0):
            return o.get('ret', {}).get(addr, 1)
        if addr == 0x36dcd0:
            return 0x77
        if addr == 0x38d4a0:
            return o.get('msgcase', 0)
        if addr == GETMETA:
            return self.read(i32(a[0]) + 0x20, 4)
        if addr == RFN:
            return o.get('rhythm', 0)
        return 0


class Retail(World, EE):
    def __init__(self, image, **options):
        self.ee_reset()
        self.descend = Union(SOFTFLOAT, _Entries(MODULE))
        World.__init__(self, image, **options)
        self.real = set()

    def call_hook(self, addr):
        a = [v for v in self.r[4:12]]
        self.r[2] = self.call(addr, a) & MASK

    def invoke(self, addr, args, farg=None):
        cov = self.covered
        self.ee_reset()
        self.covered = cov
        self.r[4:4 + len(args)] = [v & MASK for v in args]
        if farg is not None:
            self.f[12] = farg
        self.r[28], self.r[29], self.r[31] = 0x55c870, 0x1fff000, 0xfffffff0
        self.run_until(addr, 0xfffffff0)
        return self.r[2]


class _Entries:
    def __init__(self, s):
        self.s = s

    def __contains__(self, a):
        return a in self.s


class Native:
    def __init__(self, lib, world):
        self.world, self.errors, self.lib = world, [], lib

        def safe(fn, default=0):
            def wrapped(*args):
                try:
                    return fn(*args)
                except Exception as e:       # surfaced after the call
                    self.errors.append(e)
                    return default
            return wrapped
        self.peek = PEEK(safe(lambda u, a, n: sx(world.read(a, n), n * 8)))
        self.poke = POKE(safe(lambda u, a, n, v: world.write(a, n, v)))
        self.call = CALL(safe(lambda u, a, v: sx(world.call(a, [sx(x, 32) & MASK for x in v[:8]]), 32)))
        self.call64 = CALL64(safe(lambda u, a, v: sx(world.call(a, [x & MASK for x in v[:8]]), 32)))

        class Api(C.Structure):
            _fields_ = [('user', C.c_void_p), ('peek', C.c_void_p), ('poke', C.c_void_p),
                        ('call', C.c_void_p), ('call64', C.c_void_p)]
        self.api = Api(None, *[C.cast(f, C.c_void_p) for f in (self.peek, self.poke, self.call, self.call64)])
        self.Api = Api
        S = {
            0x398e80: ('a2_node_time', [C.c_int32, C.c_int64], C.c_int64),
            0x3a7a20: ('a2_timer_start', [C.c_int32, C.c_int32, C.c_int64], None),
            0x3a7d00: ('a2_ref_release', [C.c_int32, C.c_int32], C.c_int32),
            0x3a7d80: ('a2_timer_exists', [C.c_int32, C.c_int32], C.c_int32),
            0x3a7e90: ('a2_timer_complete', [C.c_int32, C.c_int32], C.c_int32),
            0x3a7fd0: ('a2_timer_elapsed', [C.c_int32, C.c_int32], C.c_int64),
            0x376340: ('a2_waitcheck_update', [C.c_int32, C.c_int32], None),
            0x3764c0: ('a2_waitcheck_start', [C.c_int32] * 3, C.c_int32),
            0x376de0: ('a2_jointset_update', [C.c_int32, C.c_int32], None),
            0x376f40: ('a2_jointset_start', [C.c_int32] * 3, C.c_int32),
            0x377700: ('a2_start_components', [C.c_int32, C.c_int32], None),
            0x3778d0: ('a2_update', [C.c_int32, C.c_int32], None),
            0x377990: ('a2_msg_iscomend', [C.c_int32] * 3, C.c_int32),
        }
        self.S = S

    def invoke(self, addr, args):
        if addr == 0x230110:
            fn = self.lib.a2_f32_to_s64
            fn.argtypes, fn.restype = [C.c_uint32], C.c_int64
            return fn(args[0] & M32)
        name, at, rt = self.S[addr]
        fn = getattr(self.lib, name)
        fn.argtypes, fn.restype = [C.POINTER(self.Api)] + at, rt
        r = fn(C.byref(self.api), *[sx(a, 64) if t == C.c_int64 else sx(a, 32) for a, t in zip(args, at)])
        assert not self.errors, self.errors
        return r


# what each entry returns, if anything: 'i' 32-bit, 'q' 64-bit
RETURNS = {0x230110: 'q', 0x398e80: 'q', 0x3a7d00: 'i', 0x3a7d80: 'i', 0x3a7e90: 'i',
           0x3a7fd0: 'q', 0x3764c0: 'i', 0x376f40: 'i', 0x377990: 'i'}


# ------------------------------------------------------------ static coverage
def reachable(image, start, size):
    def word(a):
        o = a - 0x100000 + 0x80
        return int.from_bytes(image[o:o + 4], 'little')
    end = start + size
    seen, todo = set(), [start]
    while todo:
        pc = todo.pop()
        if pc in seen or not start <= pc < end:
            continue
        seen.add(pc)
        w = word(pc)
        op, rs, rt, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 63
        imm = sx(w, 16)
        tgt = pc + 4 + (imm << 2)
        if op == 2:
            seen.add(pc + 4)
            todo.append(((pc + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2))
        elif op == 3 or (op == 0 and fn == 9):
            seen.add(pc + 4)
            todo.append(pc + 8)
        elif op == 0 and fn == 8:
            seen.add(pc + 4)
        elif op == 4 and rs == rt:                       # unconditional `b`
            seen.add(pc + 4)
            todo.append(tgt)
        elif op in (1, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 0x11 and rs == 8):
            seen.add(pc + 4)
            todo += [tgt, pc + 8]
        else:
            todo.append(pc + 4)
    return seen


def code_extent(image, start, size):
    """Drop trailing alignment padding after the final `jr ra` + delay slot."""
    return reachable(image, start, size)


# ----------------------------------------------------------------- self-test
def interpreter_selftest():
    """Hand-assembled programs pinning the semantics the verifier relies on."""
    class T(EE):
        def __init__(s, words):
            s.words = dict(enumerate(words))
            s.ee_reset()
            s.mem = {}
        def read(s, a, n):
            if a < 0x1000:
                return s.words.get(a // 4, 0)
            return sum(s.mem.get(a + i, 0) << (8 * i) for i in range(n))
        def write(s, a, n, v):
            for i in range(n):
                s.mem[a + i] = (v >> (8 * i)) & 255
        def call_hook(s, a):
            raise AssertionError('call')
    def enc_i(op, rs, rt, imm):
        return op << 26 | rs << 21 | rt << 16 | imm & 0xffff
    def enc_r(rs, rt, rd, sh, fn):
        return rs << 21 | rt << 16 | rd << 11 | sh << 6 | fn
    def run(words, setup=None):
        t = T(words + [enc_r(31, 0, 0, 0, 8), 0])
        if setup:
            setup(t)
        t.r[31] = 0x800
        pc = 0
        for _ in range(1000):
            if pc == 0x800:
                break
            pc = t.step(pc)
        return t
    # dsrlv / dsllv / dsrav on 64-bit values
    t = run([enc_r(5, 4, 2, 0, 0x16), enc_r(5, 4, 3, 0, 0x14), enc_r(5, 4, 6, 0, 0x17)],
            lambda t: (t.r.__setitem__(4, 0x8000000000000000), t.r.__setitem__(5, 63)))
    assert t.r[2] == 1 and t.r[3] == 0 and t.r[6] == MASK
    # divu by zero: lo=-1, hi=dividend; normal divu; mult1/mflo1
    t = run([enc_r(4, 5, 0, 0, 0x1b), enc_r(0, 0, 2, 0, 0x10), enc_r(0, 0, 3, 0, 0x12)],
            lambda t: (t.r.__setitem__(4, 123), t.r.__setitem__(5, 0)))
    assert t.r[2] == 123 and t.r[3] == MASK
    t = run([enc_r(4, 5, 0, 0, 0x1b), enc_r(0, 0, 2, 0, 0x10), enc_r(0, 0, 3, 0, 0x12)],
            lambda t: (t.r.__setitem__(4, 0xfffffff0), t.r.__setitem__(5, 7)))
    assert t.r[3] == (0xfffffff0 // 7) and t.r[2] == 0xfffffff0 % 7
    # lbu is zero-extended, lb sign-extended, lw sign-extended
    t = run([enc_i(0x24, 4, 2, 0), enc_i(0x20, 4, 3, 0), enc_i(0x23, 4, 6, 4)],
            lambda t: (t.write(0x2000, 4, 0x000000f0), t.write(0x2004, 4, 0x80000000), t.r.__setitem__(4, 0x2000)))
    assert t.r[2] == 0xf0 and t.r[3] == MASK - 15 and t.r[6] == (MASK ^ 0x7fffffff)
    # branch-likely: not taken nullifies the delay slot, taken executes it
    t = run([enc_i(0x16, 0, 0, 2), enc_i(9, 0, 2, 5), enc_i(9, 0, 3, 7)])   # blezl zero: taken
    assert t.r[2] == 5
    t = run([enc_i(0x17, 0, 0, 2), enc_i(9, 0, 2, 5), enc_i(9, 0, 3, 7)])   # bgtzl zero: not taken
    assert t.r[2] == 0 and t.r[3] == 7
    # FPU: mula.s/msub.s, c.lt.s + bc1t/bc1f, mtc1/cvt.s.w, cvt.w.s, mfc1
    def fpu(rs, ft, fs, fd, fn):
        return 0x11 << 26 | rs << 21 | ft << 16 | fs << 11 | fd << 6 | fn
    two, three, five = 0x40000000, 0x40400000, 0x40a00000
    t = run([fpu(0x10, 2, 1, 0, 0x1a), fpu(0x10, 3, 1, 4, 0x1d)],
            lambda t: (t.f.__setitem__(1, five), t.f.__setitem__(2, three), t.f.__setitem__(3, two)))
    assert t.acc == f_mul(five, three) and t.f[4] == f_add(f_mul(five, three), f_mul(five, two), True)
    # c.lt.s f1,f2 (2<3 true): bc1t taken executes the delay slot, skips the next li
    prog = [fpu(0x10, 2, 1, 0, 0x34), 0x45010002, enc_i(9, 0, 2, 5), enc_i(9, 0, 3, 7), enc_i(9, 0, 6, 9)]
    t = run(prog, lambda t: (t.f.__setitem__(1, two), t.f.__setitem__(2, three)))
    assert t.r[2] == 5 and t.r[3] == 0 and t.r[6] == 9
    t = run(prog, lambda t: (t.f.__setitem__(1, three), t.f.__setitem__(2, two)))      # false: falls through
    assert t.r[2] == 5 and t.r[3] == 7 and t.r[6] == 9
    prog = [fpu(0x10, 2, 1, 0, 0x34), 0x45000002, enc_i(9, 0, 2, 5), enc_i(9, 0, 3, 7), enc_i(9, 0, 6, 9)]   # bc1f
    t = run(prog, lambda t: (t.f.__setitem__(1, three), t.f.__setitem__(2, two)))
    assert t.r[2] == 5 and t.r[3] == 0 and t.r[6] == 9
    # mtc1 + cvt.s.w + cvt.w.s + mfc1 round trip, with truncation toward zero
    t = run([0x44842000, fpu(0x14, 0, 4, 6, 0x20), fpu(0x10, 0, 6, 8, 0x24)],
            lambda t: t.r.__setitem__(4, 100))
    assert t.f[6] == f_from_i32(100) and t.f[8] == 100
    assert f_trunc_w(0xc0600000) == (-3) & M32            # -3.5 truncates toward zero


# ------------------------------------------------------------ FPU model checks
def fpu_checks(rng, lib, tmp):
    """The integer FPU model against (a) the C eefloat and (b) the host FPU
    forced to round toward zero (an independent oracle for rounding)."""
    src = Path(tmp) / 'rz.c'
    src.write_text(r'''
#include <fenv.h>
#include <stdint.h>
#include <string.h>
static float f(uint32_t b){float x;memcpy(&x,&b,4);return x;}
static uint32_t u(float x){uint32_t b;memcpy(&b,&x,4);return b;}
#pragma STDC FENV_ACCESS ON
uint32_t rz(int op,uint32_t a,uint32_t b){
    volatile float x=f(a),y=f(b),r;
    fesetround(FE_TOWARDZERO);
    switch(op){case 0:r=x+y;break;case 1:r=x-y;break;case 2:r=x*y;break;case 3:r=x/y;break;
               default:r=(float)(int32_t)a;}
    fesetround(FE_TONEAREST);
    return u(r);
}''')
    so = Path(tmp) / 'rz.so'
    subprocess.run(['cc', '-O0', '-frounding-math', '-shared', '-fPIC', str(src), '-o', str(so)], check=True)
    rz = C.CDLL(str(so)).rz
    rz.argtypes, rz.restype = [C.c_int, C.c_uint32, C.c_uint32], C.c_uint32
    ops = [('add', lambda a, b: f_add(a, b), lib.ee_f32_add), ('sub', lambda a, b: f_add(a, b, True), lib.ee_f32_sub),
           ('mul', f_mul, lib.ee_f32_mul), ('div', f_div, lib.ee_f32_div)]
    for _, _, fn in ops:
        fn.argtypes, fn.restype = [C.c_uint32, C.c_uint32], C.c_uint32
    lib.ee_f32_from_s32.argtypes, lib.ee_f32_from_s32.restype = [C.c_int32], C.c_uint32
    lib.ee_f32_trunc_s32.argtypes, lib.ee_f32_trunc_s32.restype = [C.c_uint32], C.c_int32
    lib.ee_f32_cmp.argtypes, lib.ee_f32_cmp.restype = [C.c_uint32, C.c_uint32], C.c_int
    lib.ee_f32_to_s64.argtypes, lib.ee_f32_to_s64.restype = [C.c_uint32], C.c_int64
    lib.ee_f32_from_clock_ticks.argtypes, lib.ee_f32_from_clock_ticks.restype = [C.c_int64], C.c_uint32
    interesting = [0, 0x80000000, 0x3f800000, 0xbf800000, 0x40000000, 0x42700000, 0x4e6e6b28, 0x42c80000,
                   0x00800000, 0x7f7fffff, 0x7f800000, 0xff7fffff, 0x3f7fffff, 0x00000001, 0x007fffff,
                   0x4b000000, 0x4b800000, 0x4effffff, 0x4f000000, 0x5f800000]
    n = 0

    def rnd():
        r = rng.random()
        if r < 0.25:
            return rng.choice(interesting)
        if r < 0.5:     # same neighbourhood: stresses cancellation/alignment
            return (rng.getrandbits(1) << 31) | ((100 + rng.randrange(60)) << 23) | rng.getrandbits(23)
        return rng.getrandbits(32)
    for _ in range(40000):
        a, b = rnd(), rnd()
        for k, (name, py, c) in enumerate(ops):
            m, cc = py(a, b), c(a, b)
            assert m == cc, (name, hex(a), hex(b), hex(m), hex(cc))
            n += 1
            ea, eb = (a >> 23) & 255, (b >> 23) & 255
            # host FPU oracle: only where no operand/result is denormal/overflow/inf/nan
            if 20 < ea < 230 and 20 < eb < 230 and (k != 3 or eb):
                host = rz(k, a, b)
                if 0 < ((host >> 23) & 255) < 254:
                    assert host == m or (host & 0x7fffffff) == 0 and (m & 0x7fffffff) == 0, (name, hex(a), hex(b), hex(host), hex(m))
                    n += 1
    for _ in range(20000):
        v = rng.choice((rng.getrandbits(32), rng.getrandbits(24), rng.getrandbits(10), 0x7fffffff, 0x80000000, 0xffffffff))
        v = sx(v, 32)
        assert f_from_i32(v) == lib.ee_f32_from_s32(v) == rz(4, v & M32, 0), hex(v)
        a = rnd()
        assert f_trunc_w(a) == lib.ee_f32_trunc_s32(a) & M32, hex(a)
        b = rnd()
        assert f_cmp(a, b) == lib.ee_f32_cmp(a, b), (hex(a), hex(b))
        n += 4
    return n


# ----------------------------------------------------------------- the harness
class Case:
    def __init__(self, image, lib):
        self.image, self.lib = image, lib
        self.total = 0
        self.covered = set()
        self.touched = set()

    def pair(self, **kw):
        r, w = Retail(self.image, **kw), World(self.image, **kw)
        r.covered = self.covered
        return r, w, Native(self.lib, w)

    def both(self, p, fn):
        fn(p[0]); fn(p[1])
        p[0].trace, p[1].trace = [], []

    def step(self, p, addr, *args, farg=None):
        r, w, c = p
        r.trace, w.trace = [], []
        x = r.invoke(addr, args, farg)
        y = c.invoke(addr, args if farg is None else (farg,))
        assert r.trace == w.trace, (hex(addr), r.options, '\nretail', r.trace, '\nnative', w.trace)
        assert r.snapshot() == w.snapshot(), (hex(addr), 'memory', r.options)
        kind = RETURNS.get(addr)
        if kind == 'q':
            assert sx(x, 64) == y, (hex(addr), hex(sx(x, 64)), hex(y), r.options)
        elif kind == 'i':
            assert i32(x) == i32(y), (hex(addr), i32(x), i32(y), r.options)
        self.total += 1
        self.touched.add(addr)
        return sx(x, 64) if kind == 'q' else (i32(x) if kind == 'i' else None)


def f32(x):
    return struct.unpack('<I', struct.pack('<f', x))[0]


def S64(v):
    return sx(v, 64)


def py_ticks_f32(clock):
    """Independent Python spelling of (float)(unsigned)(clock>>18) in the EE model."""
    u = (clock & MASK) >> 18 & M32
    if u >> 31 == 0:
        return f_from_i32(u)
    h = f_from_i32((u >> 1) | (u & 1))
    return f_add(h, h)


def py_ftoll(bits):
    neg = f_cmp(bits, 0) < 0
    if neg:
        bits ^= 0x80000000
    _, m, e = f_parts(bits)
    mag = 0 if m == 0 else (m << e if e >= 0 else m >> -e)
    mag = min(mag, (1 << 64) - 1)
    return S64((-mag if neg else mag) & MASK)


def py_node_time(clock, scale, bias):
    return S64(((py_ftoll(f_mul(py_ticks_f32(clock), scale)) << 18) + bias) & MASK)


def sysclock(w):
    return S64(w.read(SYS + 0x50, 8))


def node_bias(w):
    return S64(w.read(NODE + 0x80, 8))


def verify(image, lib, tmp, quick=False):
    rng = random.Random(0xa2)
    cs = Case(image, lib)
    stats = {}
    S = cs.step
    q = 0.25 if quick else 1.0

    def clk(p, v):
        cs.both(p, lambda w: w.w64(SYS + 0x50, v))

    # ---- FPU model ---------------------------------------------------------
    stats['fpu'] = fpu_checks(rng, lib, tmp)

    # ---- 0x230110: float -> int64 -----------------------------------------
    p = cs.pair()
    vectors = []
    for e in range(256):
        for sign in (0, 1):
            for m in (0, 1, 0x7fffff, 0x400000, 0x2aaaaa, rng.getrandbits(23)):
                vectors.append(sign << 31 | e << 23 | m)
    vectors += [f32(x) for x in (0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 1.5, -1.5, 29999999.0, 1e9, 5e8, 3e10,
                                 4294967296.0, 9.223372e18, 1.8446744e19)]
    vectors += [rng.getrandbits(32) for _ in range(int(1500 * q))]
    for b in vectors:
        got = S(p, 0x230110, 0, farg=b)
        assert got == py_ftoll(b), (hex(b), hex(got), hex(py_ftoll(b)))
    stats['ftoll'] = len(vectors)

    # ---- 0x398e80: node time -------------------------------------------------
    scales = [0x3f800000, 0x3f000000, 0x40000000, 0, 0x80000000, 0xbf800000, 0x00400000, 0x7f7fffff,
              0x3f7fffff, 0x3f800001, 0x41200000, f32(0.3)]
    clocks = [0, 1, (1 << 18) - 1, 1 << 18, (1 << 18) + 1, 16666667, 16666666 * 30, 500000010, (1 << 49) - 1,
              1 << 49, (1 << 49) + (1 << 18), 1 << 50, (1 << 50) - 1, 0x7fffffffffffffff, -1, -(1 << 18),
              -(1 << 18) - 1, S64(0x8000000000000000), 1 << 49, (1 << 49) - 1, (1 << 50) - 1, 1 << 50]
    clocks += [rng.getrandbits(64) - (1 << 63) for _ in range(int(30 * q))]
    clocks += [(rng.getrandbits(34) << 18) | rng.getrandbits(18) for _ in range(int(30 * q))]
    biases = [0, 1, -1, 1 << 40, -(1 << 40), S64(0x8000000000000000), 0x7fffffffffffffff]
    count = 0
    for sc in scales:
        for ck in clocks:
            p = cs.pair(scale=sc, bias=rng.choice(biases))
            got = S(p, 0x398e80, NODE, ck)
            assert got == py_node_time(ck, sc, node_bias(p[0])), (hex(sc), ck)
            count += 1
    stats['node_time'] = count

    # ---- timer group ---------------------------------------------------------
    cases = 0
    sides = (None, 1, 2, 0x800001, 0x800000)

    def ens_kw():
        return dict(gpflag=rng.choice((0, 1)), null_list_calls=rng.choice((0, 0, 1, 2)),
                    list_refs=rng.choice((0, 1, 2, 0x800001)), list_side=rng.choice(sides))
    for gp in (0, 1):
        for null_calls in (0, 1, 2, 9):
            for list_refs in (0, 1, 0x800001):
                for side in sides:
                    for existing in (None, (123, 5, 0x3f800000, 1), (2, -7, 0x40000000, 0x800001)):
                        kw = dict(gpflag=gp, null_list_calls=null_calls, list_refs=list_refs, list_side=side,
                                  clock=rng.choice((0, 262143, 262144, 123456789, 5 << 18, 1 << 49, (1 << 49) + 77777777)),
                                  timer_refs=rng.choice((1, 0, 0x7fffff + 1)),
                                  tscale=rng.choice((0x3f800000, 0x40000000, 0)), timer=existing)
                        p = cs.pair(**kw)
                        for dur in (0, 1, 499999968, -5, 1 << 62):
                            S(p, 0x3a7a20, ACT, TIMER_NAME, dur)
                            cases += 1
                        if existing is None:
                            S(p, 0x3a7a20, ACT, FADE_NAME, 7)
    for ck in (1 << 49, (1 << 49) + 262144 * 5, (3 << 48) + 1):
        for timer_refs in (1, 0):
            p = cs.pair(clock=ck, timer_refs=timer_refs, timer=None)
            S(p, 0x3a7a20, ACT, TIMER_NAME, 100)
            clk(p, ck + (7 << 18))
            S(p, 0x3a7e90, ACT, TIMER_NAME)
            cases += 2
    # a pre-existing property list, with and without the timer
    for refs in (1, 2, 0x800001):
        for has in (False, True):
            p = cs.pair(timer=(1, 2, 0x3f800000, 1) if has else None, clock=99 << 18)
            cs.both(p, lambda w: w.w32(w.read(ACT + 0x28, 4) + 4, refs) if has else (w.w32(LIST0 + 0x9004, refs), w.w32(ACT + 0x28, LIST0 + 0x9000)))
            S(p, 0x3a7a20, ACT, TIMER_NAME, 5)
            cases += 1
    for gp in (0, 1):
      for list_refs in (0, 1):
        p = cs.pair(gpflag=gp, list_refs=list_refs)
        S(p, 0x3a7d80, ACT, TIMER_NAME)
        cases += 1
    for null_calls in (0, 1, 2):
        for has in (False, True):
            for side in sides:
                kw = dict(null_list_calls=null_calls, list_side=side, timer=(1, 2, 0x3f800000, 1) if has else None,
                          gpflag=rng.choice((0, 1)), list_refs=rng.choice((0, 1, 0x800001)))
                p = cs.pair(**kw)
                if has and null_calls == 0:
                    cs.both(p, lambda w: w.w32(ACT + 0x28, 0))
                S(p, 0x3a7d80, ACT, TIMER_NAME)
                S(p, 0x3a7d80, ACT, FADE_NAME)
                cases += 2
    for refs in (0, 1, 2, 0x800001, 0x800000):
        for flags in (0, 1, -1, 0x10001, 0x8000, 0xffff, 0x7fff, 0x18000, -32768):
            for ref in (0, ACT + 0x500):
                p = cs.pair()
                cs.both(p, lambda w: (w.w32(ACT + 0x500, ACT + 0x600), w.w32(ACT + 0x604, refs)))
                S(p, 0x3a7d00, ref, flags)
                cases += 1
    # elapsed/complete: the strict threshold, across scales and clock alignment
    for sc in (0x3f800000, 0x3f000000, 0x40000000, f32(1.7), 0):
        for ck_start in (0, 12345678, (1 << 18) - 1):
            for ck_now in (0, 1, (1 << 18) - 1, 1 << 18, 5 << 18, 500000010 + ck_start, (1 << 32) << 18,
                           ((1 << 32) << 18) + 12345, 1 << 49):
                p = cs.pair(clock=ck_start, scale=0, tscale=sc, timer=None)
                S(p, 0x3a7a20, ACT, TIMER_NAME, 499999968)
                clk(p, ck_now)
                E = S(p, 0x3a7fd0, ACT, TIMER_NAME)
                base = S64(p[0].read(p[0].timers[TIMER_NAME] + 0x18, 8))
                assert E == S64(((py_ftoll(f_mul(py_ticks_f32(ck_now), sc)) << 18) + base) & MASK)
                for d in (E - 1, E, E + 1, E - (1 << 18), E + (1 << 18), 0, -1, 1 << 62, -(1 << 62),
                          0x7fffffffffffffff, S64(0x8000000000000000)):
                    d = S64(d & MASK)
                    cs.both(p, lambda w: w.w64(w.timers[TIMER_NAME] + 0x20, d))
                    done = S(p, 0x3a7e90, ACT, TIMER_NAME)
                    assert done == int(d < E), (d, E)          # strict: duration < elapsed
                    cases += 1
    # the ensure-list variants of elapsed/complete (timer preloaded, list absent from the act)
    for gp in (0, 1):
        for null_calls in (0, 1):
            for side in sides:
                for refs in (0, 1, 0x800001):
                    p = cs.pair(gpflag=gp, null_list_calls=null_calls, list_side=side, list_refs=refs,
                                timer=(10, 0, 0x3f800000, 1), clock=9 << 18)
                    cs.both(p, lambda w: w.w32(ACT + 0x28, 0))
                    S(p, 0x3a7e90, ACT, TIMER_NAME)
                    cs.both(p, lambda w: w.w32(ACT + 0x28, 0))
                    S(p, 0x3a7fd0, ACT, TIMER_NAME)
                    cases += 2
    # missing timer reads complete
    for null_calls in (0, 1, 9):
        p = cs.pair(null_list_calls=null_calls)
        assert S(p, 0x3a7e90, ACT, TIMER_NAME) == 1
        cases += 1
    stats['timer'] = cases

    # ---- WAITCHECK Start --------------------------------------------------------
    cases = 0
    fl = [0, 0x80000000, f32(30.0), f32(10.0), f32(0.5), f32(60.0), f32(-3.0), f32(1e30), 0x7f7fffff, 0x7fffffff,
          0x00400000, f32(0.016666668)] + [rng.getrandbits(32) for _ in range(6)]
    for text in ('Joint', 'Motion', 'Frame', 'Rhythm', 'RxxS', 'RxxX', 'R', 'F', 'J', 'M', 'Zebra', '', 'Rate'):
        for secs in fl:
            for glob in (0x42f00000, 0, f32(2.0), f32(0.25)):
                for rhythm in (0, 7, 100, -1, 12345):
                    if text[:1] != 'R' and (glob != 0x42f00000 or rhythm):
                        continue
                    kw = dict(clock=rng.choice((0, 99999999)), rhythm=rhythm, tscale=rng.choice((0x3f800000, 0x40000000)))
                    kw['global'] = glob
                    p = cs.pair(**kw)
                    cs.both(p, lambda w: w.set_components([('WAIT', text, secs, 0, '')]))
                    S(p, 0x3764c0, MGR, ACT, COMP0)
                    cases += 1
    p = cs.pair()
    cs.both(p, lambda w: (w.set_components([('WAIT', 'x', f32(30.0), 0, '')]), w.w32(COMP0 + 8, 0)))
    S(p, 0x3764c0, MGR, ACT, COMP0)
    # frame wait: the armed duration equals ftoll(1e9f * f / 60) in the EE model
    for secs, expect in ((30.0, 499999968),):
        p = cs.pair()
        cs.both(p, lambda w: w.set_components([('WAIT', 'Frame', f32(secs), 0, '')]))
        S(p, 0x3764c0, MGR, ACT, COMP0)
        t = p[0].timers[TIMER_NAME]
        assert S64(p[0].read(t + 0x20, 8)) == expect == py_ftoll(f_div(f_mul(0x4e6e6b28, f32(secs)), 0x42700000))
    stats['wait_start'] = cases + 2

    # ---- WAITCHECK Update ---------------------------------------------------------
    cases = 0
    for state in (0, 1, 2, 3, 4, -1, 0x100, 5):
        for jis in (0, 1, 2, 255):
            for jis_hi in (0, 1):
                for timer in (None, (499999968, 0, 0x3f800000, 1)):
                    p = cs.pair(wait=state, comindex=0, timer=timer, clock=500000010)
                    cs.both(p, lambda w: w.w32(WORK + 0x30, jis | jis_hi << 8))
                    S(p, 0x376340, MGR, ACT)
                    cases += 1
    for flag in (0, 1, 2):
        for q30 in (0, 1000, 1 << 40, -1):
            for cur_off in (-1, 0, 1):
                for q20, q28 in ((0, 0), (500, 7), (-3, 1 << 33)):
                    for m_off in (0, 5):
                        p = cs.pair(wait=2, idx=rng.choice((0, 2)), chain=dict(flag=flag, cur=0, q20=q20, q28=q28, q30=q30),
                                    clock=rng.choice((0, 5 << 18, 1 << 40)), m_off=m_off, bias=rng.choice((0, 77)))
                        node_t = py_node_time(sysclock(p[0]), 0x3f800000, node_bias(p[0]))
                        end = S64((node_t + m_off + cur_off) & MASK) if q30 else 0
                        cs.both(p, lambda w: w.w64(MQ + 0x30, end))
                        S(p, 0x376340, MGR, ACT)
                        cases += 1
    stats['wait_update'] = cases

    # ---- JOINTSET Start -----------------------------------------------------------
    cases = 0
    for loop in ('L', 'LP', 'OS', 'O', '', 'x', 'l'):
        for a, b in ((0, 30), (30, 0), (240, 360), (0, 209), (0.0, 0.5), (1e9, 3.0), (-5, 5), (0.016666668, 1e-30)):
            for sc in (0x3f800000, 0x40000000, 0, 0x3f000000):
                for ck in (0, 12345678901, (1 << 50) + 12345, (1 << 49) + 999):
                    p = cs.pair(scale=sc, bias=rng.choice((0, -123)), clock=ck)
                    cs.both(p, lambda w: w.set_components([('JOINT', 'x', f32(float(a)), f32(float(b)), loop)]))
                    S(p, 0x376f40, MGR, ACT, COMP0)
                    cases += 1
    p = cs.pair()
    cs.both(p, lambda w: (w.set_components([('JOINT', 'x', f32(0.0), f32(30.0), 'OS')]), w.w32(COMP0 + 0x14, 0)))
    S(p, 0x376f40, MGR, ACT, COMP0)
    stats['joint_start'] = cases + 1

    # ---- JOINTSET Update: exact threshold, clamp, loop wrap ---------------------------
    cases = 0
    for state in (0, 1, 2, 3, -1):
        for sc in (0x3f800000, 0x40000000, 0x3f000000, f32(1.25)):
            for ck in (0, 7 << 18, 123456789, (3 << 32) << 18, 1 << 49, (1 << 49) + 123456789):
                for bias in (0, -1000, 1 << 33):
                    T = py_node_time(ck, sc, bias)
                    for end_off in (-(1 << 20), -1, 0, 1, 1 << 20):
                        start = rng.choice((0, -5, 100)) if state == 1 else rng.choice((0, 5))
                        end = S64((T + end_off) & MASK)
                        if state == 1 and not start < end:
                            start = S64((end - 1000) & MASK)
                        p = cs.pair(joint=state, scale=sc, bias=bias, clock=ck, jisend=0, jstart=start, jend=end)
                        S(p, 0x376de0, MGR, ACT)
                        w = p[0]
                        changed = state in (1, 2) and end < T
                        assert w.read(WORK + 0x30, 1) == int(changed), (state, end_off)
                        if changed and state == 2:                       # clamped to end exactly
                            assert py_node_time(ck, sc, node_bias(w)) == end
                        if changed and state == 1:                       # wrapped one span at a time
                            span, expect = end - start, T
                            while end < expect:
                                expect -= span
                            assert py_node_time(ck, sc, node_bias(w)) == expect <= end
                        before = w.snapshot()
                        S(p, 0x376de0, MGR, ACT)                          # repeated tick: no further change
                        if changed:
                            assert p[0].snapshot() == before
                        cases += 1
    stats['joint_update'] = cases

    # ---- components / driver / ISCOMEND ---------------------------------------------
    cases = 0
    OPEN = [('FADE', 'IN', f32(10.0), 0, ''), ('JOINT', 'x', f32(0.0), f32(30.0), 'OS'), ('WAIT', 'Joint', 0, 0, '')]
    CLOSE = [('FADE', 'OUT', f32(30.0), 0, ''), ('WAIT', 'Frame', f32(30.0), 0, '')]
    seqs = [OPEN, CLOSE,
            [('MOTION', 'm', 0, 0, ''), ('FLASH', 'f', 0, 0, ''), ('WAIT', 'Motion', 0, 0, '')],
            [('JOINT', 'x', f32(0.0), f32(5.0), 'LP'), ('WAIT', 'Joint', 0, 0, ''), ('FADE', 'IN', f32(1.0), 0, '')],
            [('WAIT', 'RxxS', f32(60.0), 0, ''), ('WAIT', 'Rhythm', f32(30.0), 0, ''), ('MOTION', 'm', 0, 0, '')],
            []]
    for comps in seqs:
        for start_idx in range(0, len(comps) + 1):
            for ret in (1, 0):
                p = cs.pair(comindex=start_idx, ret={0x377340: ret, 0x376930: ret, 0x375ff0: ret}, rhythm=5)
                cs.both(p, lambda w: w.set_components(comps))
                S(p, 0x377700, MGR, ACT)
                cases += 1
    for active in (0, 1):
        for freeze in (0, 1, 7):
            for mo, jo, fa, wa, fl_ in ((0, 0, 0, 0, 0), (1, 1, 1, 1, 1), (0, 1, 0, 1, 0), (3, 0, 5, 0, 2), (0, 2, 0, 3, 0)):
                p = cs.pair(active=active, freeze=freeze, motion=mo, joint=jo, fade=fa, wait=wa, flash=fl_,
                            clock=5 << 18, jend=1 << 40, jstart=0, timer=(0, 0, 0x3f800000, 1))
                S(p, 0x3778d0, MGR, ACT)
                cases += 1
    for comp_idx in (0, 1, 2, 3):
        for wait in (0, 1, -1):
            p = cs.pair(comindex=comp_idx, wait=wait)
            cs.both(p, lambda w: w.set_components(OPEN))
            got = S(p, 0x377990, MGR, ACT, 0x50f150)
            assert got == 1
            flag = [e for e in p[0].trace if e[:2] == ('call', 0x38f150)][0][3]
            assert flag == int(wait == 0 and comp_idx == 3)           # ISCOMEND = no wait && all started
            cases += 1
    for refs in (0, 1, 0x800000, 0x7fffff):
        p = cs.pair(work_refs=refs, comindex=3)
        cs.both(p, lambda w: w.set_components(OPEN))
        S(p, 0x377990, MGR, ACT, 0x50f150)
        cases += 1
    # a message that is not ISCOMEND is outside the recovered case: -1, refcount restored
    p = cs.pair(msgcase=3)
    before = p[1].read(WORK + 4, 4)
    assert p[2].invoke(0x377990, (MGR, ACT, 0)) == -1 and p[1].read(WORK + 4, 4) == before
    stats['components'] = cases

    # ---- end-to-end action lifecycles: logo OPEN / CLOSE and random interleavings --------
    cases = 0
    frames = {'OPEN': [], 'CLOSE': []}
    DUR = 499999968

    def comend(p):
        e = [e for e in p[0].trace if e[:2] == ('call', 0x38f150)]
        return e[-1][3]

    def run_logo(name, comps, steps, c0, scale=0x3f800000):
        nonlocal cases
        p = cs.pair(clock=c0, comindex=0, scale=scale, tscale=scale, bias=0)
        cs.both(p, lambda w: w.set_components(comps))
        S(p, 0x377700, MGR, ACT)
        # drive the per-frame driver; ISCOMEND is queried like the host would
        done = None
        ck = c0
        for n, dt in enumerate(steps, 1):
            ck += dt
            clk(p, ck)
            S(p, 0x3778d0, MGR, ACT)
            S(p, 0x377990, MGR, ACT, 0x50f150)
            complete = comend(p)
            # independent expectation: both the JOINTSET and the WAIT timer complete once
            # the 2^18-ns tick difference, scaled, exceeds 499,999,968 ns (strictly)
            # Round each absolute clock separately, exactly where retail does.
            # Rounding their difference is wrong once either tick count loses precision.
            elapsed = S64(py_node_time(ck, scale, 0) - py_node_time(c0, scale, 0))
            assert complete == int(DUR < elapsed), (name, n, c0, ck, elapsed)
            assert complete in (0, 1)
            if done is None and complete:
                done = n
            if done is not None:
                assert complete == 1                                      # stays complete
            cases += 3
        return done
    base_steps = lambda dt, n: [dt] * n
    for c0 in [0, 1, (1 << 18) - 1, 123456789, 262144 * 1000 + 131072,
               ((1 << 24) - 1000) << 18, ((1 << 25) + 1) << 18,
               (1 << 31) << 18, ((1 << 31) + 255) << 18] + [rng.getrandbits(40) for _ in range(int(8 * q))]:
        for dt in (16666667, 16666666, 16666700, 16000000, 17000000):
            for name, comps in (('OPEN', OPEN), ('CLOSE', CLOSE)):
                n = run_logo(name, comps, base_steps(dt, 45), c0)
                assert n is not None
                frames[name].append((dt, n))
    # jittered clock steps, and a half-speed scale
    for _ in range(int(20 * q)):
        steps = [rng.choice((16666667, 16666666, 33333333, 1, 262144, 262143, 0)) for _ in range(120)]
        for name, comps in (('OPEN', OPEN), ('CLOSE', CLOSE)):
            run_logo(name, comps, steps, rng.getrandbits(40))
    for name, comps in (('OPEN', OPEN), ('CLOSE', CLOSE)):
        run_logo(name, comps, base_steps(16666667, 100), 0, scale=0x3f000000)
    # interruption / re-entry: restart the component walk, freeze, deactivate, re-arm mid-wait
    for trial in range(int(60 * q)):
        comps = rng.choice([OPEN, CLOSE, OPEN + CLOSE, CLOSE + OPEN])
        c0 = rng.getrandbits(40)
        p = cs.pair(clock=c0, comindex=0, rhythm=3)
        cs.both(p, lambda w: w.set_components(comps))
        S(p, 0x377700, MGR, ACT)
        ck = c0
        for _ in range(80):
            op = rng.random()
            if op < 0.55:
                ck += rng.choice((16666667, 16666666, 5000000, 262144, 1))
                clk(p, ck)
                S(p, 0x3778d0, MGR, ACT)
            elif op < 0.65:
                cs.both(p, lambda w: w.w32(WORK + 0xc, 0))           # rewind the walk
                S(p, 0x377700, MGR, ACT)
            elif op < 0.72:
                S(p, 0x377700, MGR, ACT)                              # re-entry at the saved index
            elif op < 0.80:
                v = rng.choice((0, 1))
                cs.both(p, lambda w: w.write(WORK + 0x4c, 1, v))
            elif op < 0.86:
                v = rng.choice((0, 1))
                cs.both(p, lambda w: w.write(ACT + 0x14, 1, v))
            elif op < 0.92:
                S(p, 0x377990, MGR, ACT, 0x50f150)
            else:
                cs.both(p, lambda w: w.w32(WORK + 0x44, rng.choice((0, 1, 3))) if False else None)
                S(p, 0x376340, MGR, ACT)
            cases += 1
    stats['lifecycle'] = cases
    stats['open_frames'] = '%d..%d' % (min(n for _, n in frames['OPEN']), max(n for _, n in frames['OPEN']))
    stats['close_frames'] = '%d..%d' % (min(n for _, n in frames['CLOSE']), max(n for _, n in frames['CLOSE']))

    # ---- coverage -------------------------------------------------------------------
    missing = {}
    for entry, size in BODIES.items():
        miss = reachable(image, entry, size) - cs.covered
        if miss:
            missing[hex(entry)] = sorted(hex(a) for a in miss)
    for entry, dead in DEAD.items():
        if hex(entry) in missing:
            missing[hex(entry)] = [a for a in missing[hex(entry)] if int(a, 16) not in dead]
            if not missing[hex(entry)]:
                del missing[hex(entry)]
    assert not missing, missing
    iscomend_path = set(range(0x377990, 0x377a28, 4)) | set(range(0x377a40, 0x377a78, 4)) | {0x377a80, 0x377a84, 0x377a88, 0x377a8c} \
        | set(range(0x378370, 0x3783a8, 4)) | {0x3783a8, 0x3783b0}
    assert iscomend_path <= cs.covered, sorted(hex(a) for a in iscomend_path - cs.covered)
    required = {a for e, size in BODIES.items() for a in reachable(image, e, size)}
    exempt = set().union(*DEAD.values()) & required
    stats['instruction_exemptions'] = len(exempt)
    n_addr = len(required & cs.covered)
    return cs, stats, n_addr


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf', type=Path, default=ROOT / 'orig/SLUS-20836/SLUS_208.36')
    ap.add_argument('--quick', action='store_true')
    ap.add_argument('--cflags', default='', help='extra C flags, e.g. -fsanitize=undefined')
    ap.add_argument('--src', type=Path, default=ROOT / 'recovered/frontend', help='directory holding action2time.c, eefloat.c (mutation testing)')
    args = ap.parse_args()
    image = args.elf.read_bytes()
    assert hashlib.sha1(image[0x80:0x454b80]).hexdigest() == ELF_SHA1
    interpreter_selftest()
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / 'a2.so'
        subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', '-O2', *args.cflags.split(),
                        str(args.src / 'action2time.c'), str(args.src / 'eefloat.c'), '-I', str(ROOT / 'recovered/frontend'), '-o', str(out)], check=True)
        cs, stats, n_addr = verify(image, C.CDLL(str(out)), tmp, args.quick)
    print('action2time: %d retail/C calls (entries %s); %d covered body instruction addresses; '
          'ordered leaf calls, ordered stores, final memory agree; %s'
          % (cs.total, ','.join(hex(a) for a in sorted(cs.touched)), n_addr,
             ' '.join(f'{k}={v}' for k, v in stats.items())))


if __name__ == '__main__':
    main()
