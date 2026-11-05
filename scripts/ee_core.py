#!/usr/bin/env python3
"""R5900 integer/FPU interpreter for the retail-instruction differential verifiers.

Scope: the instructions needed by the Action2 timing group
(`verify_action2time.py`).  Integer arithmetic is exact 64-bit modular
arithmetic; single-precision arithmetic is implemented on IEEE bit patterns with
integer arithmetic only -- never Python `float` -- using the documented
Emotion Engine FPU model:

  * rounding is toward zero for add/sub/mul/div/cvt.s.w/mula/msub;
  * exponent 0 is zero (denormals flush, sign kept), exponent 255 is an
    ordinary number (no Inf/NaN); overflow saturates to sign|0x7fffffff;
  * division by zero saturates to sign|0x7fffffff;
  * trunc.w.s truncates toward zero and saturates to 0x7fffffff/0x80000000.

That model is *assumed*, not measured on hardware; see
docs/engine/action2-timing.md ("Unverified").  Both the interpreter and the C
reference (recovered/frontend/eefloat.c) implement it independently.

Memory is supplied by the host class (`read(addr,size)`, `write(addr,size,v)`).
Calls (`jal`/`jalr`) go to `call_hook(addr)` unless the target is in
`self.descend`, in which case the callee's original instructions execute.
"""
MASK = (1 << 64) - 1
M32 = 0xffffffff
MAXF = 0x7fffffff


def sx(n, bits):
    n &= (1 << bits) - 1
    return n - (1 << bits) if n >> (bits - 1) else n


# ---------------------------------------------------------------- float model
def f_parts(b):
    """(sign, mantissa24, exp2) with value = (-1)^sign * mantissa24 * 2^exp2."""
    b &= M32
    e = (b >> 23) & 255
    if e == 0:
        return b >> 31, 0, 0
    return b >> 31, 0x800000 | (b & 0x7fffff), e - 127 - 23


def f_pack(sign, mant, e2):
    """Truncate |sign*mant*2^e2| to 24 bits; saturate/flush like the EE."""
    if mant == 0:
        return sign << 31
    n = mant.bit_length()
    if n > 24:
        mant >>= n - 24
        e2 += n - 24
    else:
        mant <<= 24 - n
        e2 -= 24 - n
    biased = e2 + 23 + 127
    if biased >= 256:
        return (sign << 31) | MAXF
    if biased <= 0:
        return sign << 31
    return (sign << 31) | (biased << 23) | (mant & 0x7fffff)


def f_mul(a, b):
    sa, ma, ea = f_parts(a)
    sb, mb, eb = f_parts(b)
    if ma == 0 or mb == 0:
        return (sa ^ sb) << 31
    return f_pack(sa ^ sb, ma * mb, ea + eb)


def f_div(a, b):
    sa, ma, ea = f_parts(a)
    sb, mb, eb = f_parts(b)
    if mb == 0:
        return ((sa ^ sb) << 31) | MAXF
    if ma == 0:
        return (sa ^ sb) << 31
    return f_pack(sa ^ sb, (ma << 64) // mb, ea - eb - 64)


def f_add(a, b, sub=False):
    sa, ma, ea = f_parts(a)
    sb, mb, eb = f_parts(b)
    if sub:
        sb ^= 1
    if ma == 0 and mb == 0:
        return (sa & sb) << 31
    if ma == 0:
        return f_pack(sb, mb, eb)
    if mb == 0:
        return f_pack(sa, ma, ea)
    e = min(ea, eb)
    va = (-ma if sa else ma) << (ea - e)
    vb = (-mb if sb else mb) << (eb - e)
    v = va + vb
    if v == 0:
        return 0
    return f_pack(int(v < 0), abs(v), e)


def f_sqrt(a):
    """Positive square root, truncated independently using integer isqrt.

    Negative operands use their magnitude, as the EE does; exception flags
    are outside this interpreter's model.
    """
    from math import isqrt
    _, m, e = f_parts(a)
    if not m:
        return a & 0x80000000
    if e & 1:
        m <<= 1
        e -= 1
    return f_pack(0, isqrt(m << 80), e // 2 - 40)


def f_from_i32(v):
    v = sx(v, 32)
    return f_pack(int(v < 0), abs(v), 0)


def f_trunc_w(a):
    s, m, e = f_parts(a)
    if m == 0:
        return 0
    mag = m << e if e >= 0 else m >> -e
    if s:
        return 0x80000000 if mag >= 1 << 31 else (-mag) & M32
    return MAXF if mag >= 1 << 31 else mag


def f_cmp(a, b):
    """-1/0/1 comparing values; both zeros compare equal."""
    sa, ma, ea = f_parts(a)
    sb, mb, eb = f_parts(b)
    if ma == 0 or mb == 0:
        va = 0 if ma == 0 else (-1 if sa else 1)
        vb = 0 if mb == 0 else (-1 if sb else 1)
    else:
        e = min(ea, eb)
        va = (-ma if sa else ma) << (ea - e)
        vb = (-mb if sb else mb) << (eb - e)
    return (va > vb) - (va < vb)


# ------------------------------------------------------------------ the core
class EE:
    """Mixin: requires self.read / self.write / self.call_hook / self.descend."""

    descend = frozenset()

    def ee_reset(self):
        self.r = [0] * 32
        self.f = [0] * 32
        self.acc = 0
        self.hi = self.lo = self.hi1 = self.lo1 = 0
        self.fcond = 0
        self.covered = set()

    def step(self, pc, delay=False):
        """Execute one instruction (and its delay slot); return the next pc."""
        w = self.read(pc, 4)
        self.covered.add(pc)
        op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        sh, fn = (w >> 6) & 31, w & 63
        imm = sx(w, 16)
        r = self.r
        dest = None
        call = False
        likely_skip = False

        def rw32(v):
            return sx(v, 32) & MASK

        def branch(take, likely=False):
            nonlocal dest, likely_skip
            if take:
                dest = (pc + 4 + (imm << 2)) & M32
            elif likely:
                likely_skip = True
                dest = (pc + 8) & M32
            else:
                dest = (pc + 8) & M32

        if op == 0:
            if fn == 0:
                r[rd] = rw32(r[rt] << sh)
            elif fn == 2:
                r[rd] = rw32((r[rt] & M32) >> sh)
            elif fn == 3:
                r[rd] = (sx(r[rt], 32) >> sh) & MASK
            elif fn == 4:
                r[rd] = rw32(r[rt] << (r[rs] & 31))
            elif fn == 6:
                r[rd] = rw32((r[rt] & M32) >> (r[rs] & 31))
            elif fn == 7:
                r[rd] = (sx(r[rt], 32) >> (r[rs] & 31)) & MASK
            elif fn in (8, 9):
                dest = r[rs] & M32
                if fn == 9:
                    r[rd] = (pc + 8) & MASK
                    call = dest not in self.descend
            elif fn == 0x14:
                r[rd] = (r[rt] << (r[rs] & 63)) & MASK
            elif fn == 0x16:
                r[rd] = r[rt] >> (r[rs] & 63)
            elif fn == 0x17:
                r[rd] = (sx(r[rt], 64) >> (r[rs] & 63)) & MASK
            elif fn == 0x0a:
                if r[rt] == 0:
                    r[rd] = r[rs]
            elif fn == 0x0b:
                if r[rt] != 0:
                    r[rd] = r[rs]
            elif fn == 0x10:
                r[rd] = self.hi
            elif fn == 0x12:
                r[rd] = self.lo
            elif fn == 0x18:                       # mult
                p = sx(r[rs], 32) * sx(r[rt], 32)
                self.lo, self.hi = rw32(p), rw32(p >> 32)
                if rd:
                    r[rd] = self.lo
            elif fn == 0x19:                       # multu
                p = (r[rs] & M32) * (r[rt] & M32)
                self.lo, self.hi = rw32(p), rw32(p >> 32)
                if rd:
                    r[rd] = self.lo
            elif fn == 0x1a:                       # div (signed 32)
                a, b = sx(r[rs], 32), sx(r[rt], 32)
                if b == 0:
                    self.lo, self.hi = (MASK if a >= 0 else 1), rw32(a)
                else:
                    q = abs(a) // abs(b) * (1 if (a < 0) == (b < 0) else -1)
                    self.lo, self.hi = rw32(q), rw32(a - q * b)
            elif fn == 0x1b:                       # divu
                a, b = r[rs] & M32, r[rt] & M32
                if b == 0:
                    self.lo, self.hi = MASK, rw32(a)
                else:
                    self.lo, self.hi = rw32(a // b), rw32(a % b)
            elif fn == 0x21:
                r[rd] = rw32(r[rs] + r[rt])
            elif fn == 0x23:
                r[rd] = rw32(r[rs] - r[rt])
            elif fn == 0x24:
                r[rd] = r[rs] & r[rt]
            elif fn == 0x25:
                r[rd] = r[rs] | r[rt]
            elif fn == 0x26:
                r[rd] = r[rs] ^ r[rt]
            elif fn == 0x27:
                r[rd] = ~(r[rs] | r[rt]) & MASK
            elif fn == 0x2a:
                r[rd] = int(sx(r[rs], 64) < sx(r[rt], 64))
            elif fn == 0x2b:
                r[rd] = int(r[rs] < r[rt])
            elif fn == 0x2d:
                r[rd] = (r[rs] + r[rt]) & MASK
            elif fn == 0x2f:
                r[rd] = (r[rs] - r[rt]) & MASK
            elif fn == 0x38:
                r[rd] = (r[rt] << sh) & MASK
            elif fn == 0x3a:
                r[rd] = r[rt] >> sh
            elif fn == 0x3b:
                r[rd] = (sx(r[rt], 64) >> sh) & MASK
            elif fn == 0x3c:
                r[rd] = (r[rt] << (sh + 32)) & MASK
            elif fn == 0x3e:
                r[rd] = r[rt] >> (sh + 32)
            elif fn == 0x3f:
                r[rd] = (sx(r[rt], 64) >> (sh + 32)) & MASK
            else:
                raise AssertionError(f'SPECIAL {w:#010x} at {pc:#x}')
        elif op == 1:
            v = sx(r[rs], 64)
            if rt in (0, 2):
                branch(v < 0, rt == 2)
            elif rt in (1, 3):
                branch(v >= 0, rt == 3)
            else:
                raise AssertionError(f'REGIMM {w:#010x} at {pc:#x}')
        elif op in (2, 3):
            dest = ((pc + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2)
            if op == 3:
                r[31] = (pc + 8) & MASK
                call = dest not in self.descend
        elif op in (4, 5, 0x14, 0x15):
            branch((r[rs] == r[rt]) == (op in (4, 0x14)), op >= 0x14)
        elif op in (6, 7, 0x16, 0x17):
            v = sx(r[rs], 64)
            branch(v <= 0 if op in (6, 0x16) else v > 0, op >= 0x14)
        elif op == 8:
            r[rt] = rw32(r[rs] + imm)
        elif op == 9:
            r[rt] = rw32(r[rs] + imm)
        elif op == 0x19:
            r[rt] = (r[rs] + imm) & MASK
        elif op == 0xa:
            r[rt] = int(sx(r[rs], 64) < imm)
        elif op == 0xb:
            r[rt] = int(r[rs] < (imm & MASK))
        elif op == 0xc:
            r[rt] = r[rs] & (w & 0xffff)
        elif op == 0xd:
            r[rt] = r[rs] | (w & 0xffff)
        elif op == 0xe:
            r[rt] = r[rs] ^ (w & 0xffff)
        elif op == 0xf:
            r[rt] = rw32((w & 0xffff) << 16)
        elif op in (0x20, 0x21, 0x23, 0x24, 0x25, 0x27, 0x37, 0x1e):
            size = {0x20: 1, 0x21: 2, 0x23: 4, 0x24: 1, 0x25: 2, 0x27: 4, 0x37: 8, 0x1e: 16}[op]
            v = self.read((r[rs] + imm) & M32, size)
            if op in (0x20, 0x21, 0x23):
                v = sx(v, size * 8) & MASK
            # LQ loads the complete 128-bit GPR. SQ below must retain its upper
            # lane as well; masking here silently zeroed half each matrix row.
            r[rt] = v if op == 0x1e else v & MASK
        elif op in (0x28, 0x29, 0x2b, 0x3f, 0x1f):
            size = {0x28: 1, 0x29: 2, 0x2b: 4, 0x3f: 8, 0x1f: 16}[op]
            self.write((r[rs] + imm) & M32, size, r[rt] & ((1 << (8 * size)) - 1))
        elif op == 0x1c:                            # MMI subset: pipeline-1 multiply/divide
            if fn == 0x18:                          # mult1
                p = sx(r[rs], 32) * sx(r[rt], 32)
                self.lo1, self.hi1 = rw32(p), rw32(p >> 32)
                if rd:
                    r[rd] = self.lo1
            elif fn == 0x19:                        # multu1
                p = (r[rs] & M32) * (r[rt] & M32)
                self.lo1, self.hi1 = rw32(p), rw32(p >> 32)
                if rd:
                    r[rd] = self.lo1
            elif fn == 0x10 and sh == 0:            # mfhi1 uses fn 0x10
                r[rd] = self.hi1
            elif fn == 0x12 and sh == 0:            # mflo1
                r[rd] = self.lo1
            else:
                raise AssertionError(f'MMI {w:#010x} at {pc:#x}')
        elif op == 0x31:
            self.f[rt] = self.read((r[rs] + imm) & M32, 4)
        elif op == 0x39:
            self.write((r[rs] + imm) & M32, 4, self.f[rt])
        elif op == 0x11:
            self._cop1(w, rs, rt, rd, sh, fn, branch)
        else:
            raise AssertionError(f'opcode {w:#010x} at {pc:#x}')
        r[0] = 0
        if dest is not None:
            assert not delay, f'branch in delay slot at {pc:#x}'
            if not likely_skip:
                self.step((pc + 4) & M32, True)
            r[0] = 0
            if call:
                self.call_hook(dest)
                return (pc + 8) & M32
            return dest
        return (pc + 4) & M32

    def _cop1(self, w, rs, rt, rd, sh, fn, branch):
        r, f = self.r, self.f
        if rs == 0:
            r[rt] = sx(f[rd], 32) & MASK
        elif rs == 2:
            r[rt] = 0
        elif rs == 4:
            f[rd] = r[rt] & M32
        elif rs == 6:
            pass
        elif rs == 8:                               # bc1f/bc1t/bc1fl/bc1tl
            branch(bool(self.fcond) == bool(rt & 1), bool(rt & 2))
        elif rs == 0x10:                            # single
            fs, ft, fd = rd, rt, sh
            if fn == 0:
                f[fd] = f_add(f[fs], f[ft])
            elif fn == 1:
                f[fd] = f_add(f[fs], f[ft], True)
            elif fn == 2:
                f[fd] = f_mul(f[fs], f[ft])
            elif fn == 3:
                f[fd] = f_div(f[fs], f[ft])
            elif fn == 4:                         # sqrt.s
                f[fd] = f_sqrt(f[ft])              # R5900 source is ft
            elif fn == 6:
                f[fd] = f[fs]
            elif fn == 7:
                f[fd] = f[fs] ^ 0x80000000
            elif fn == 5:
                f[fd] = f[fs] & 0x7fffffff
            elif fn == 0x18:                        # adda.s
                self.acc = f_add(f[fs], f[ft])
            elif fn == 0x1a:                        # mula.s
                self.acc = f_mul(f[fs], f[ft])
            elif fn == 0x1c:                        # madd.s
                f[fd] = f_add(self.acc, f_mul(f[fs], f[ft]))
            elif fn == 0x1d:                        # msub.s
                f[fd] = f_add(self.acc, f_mul(f[fs], f[ft]), True)
            elif fn == 0x24:                        # cvt.w.s (retail disassembles trunc.w.s; the EE truncates)
                f[fd] = f_trunc_w(f[fs])
            elif fn == 0x34:                        # c.lt.s
                self.fcond = int(f_cmp(f[fs], f[ft]) < 0)
            elif fn == 0x32:                        # c.eq.s
                self.fcond = int(f_cmp(f[fs], f[ft]) == 0)
            elif fn == 0x36:                        # c.le.s
                self.fcond = int(f_cmp(f[fs], f[ft]) <= 0)
            else:
                raise AssertionError(f'COP1.S {w:#010x}')
        elif rs == 0x14:                            # word source
            if fn == 0x20:                          # cvt.s.w
                f[sh] = f_from_i32(f[rd])
            else:
                raise AssertionError(f'COP1.W {w:#010x}')
        else:
            raise AssertionError(f'COP1 {w:#010x}')

    def run_until(self, pc, stop, limit=2_000_000):
        for _ in range(limit):
            if pc == stop:
                return
            pc = self.step(pc)
        raise AssertionError('instruction budget exhausted')
