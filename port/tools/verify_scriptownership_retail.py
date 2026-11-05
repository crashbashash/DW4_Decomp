#!/usr/bin/env python3
"""Recover Lua lookup, scene startup and coordinated cleanup from retail MIPS.

Runs original instructions from a private ELF. Lua execution, allocation,
archive IO, interning and receiver methods are controlled leaves. This is a
contract probe, not a full-game or host-runtime equivalence claim.
"""
import argparse
from pathlib import Path
import sys
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from ee_core import EE, MASK, sx

BASE = 0x1900000
SELF, SYS, INFO, STATE, VM, MSG, FRAME = range(BASE, BASE + 0x700, 0x100)
BUFFER, FILES = BASE + 0x900, BASE + 0xa00
RUNBUFFER, RUNFILE = BASE + 0x1000, BASE + 0x1010

class World(EE):
    def __init__(self, image):
        self.image = image
        self.mem = {}
        self.trace = []
        self.tokens = {}
        self.next = BASE + 0x10000
        self.results = {}
        self.ee_reset()
        self.descend = set()
        self.w(0x586f20, 4, BASE + 0xb00)  # existing string interner
        self.w(SELF + 16, 4, SYS)
        self.w(SELF + 24, 4, STATE)
        self.w(SELF + 12, 4, FRAME)
        self.w(SELF + 20, 4, MSG)
        self.w(STATE, 4, VM)
        self.w(VM + 100, 4, RUNBUFFER)
        self.w(VM + 96, 4, RUNFILE)
        self.w(SYS + 56, 4, self.token('stagML11'))
        for off in (0x14, 0x24, 0x28, 0x2c, 0x30, 0x34):
            if off != 0x14:
                self.w(SELF + off, 4, self.lst([]))
        self.w(SYS + 0x34, 4, self.lst([]))

    def alloc(self):
        p = self.next
        self.next += 0x400
        return p

    def read(self, a, n):
        a &= 0xffffffff
        if 0x100000 <= a and a + n <= 0x554b00:
            p = a - 0x100000 + 0x80
            return int.from_bytes(self.image[p:p+n], 'little')
        return sum(self.mem.get(a+i, 0) << (8*i) for i in range(n))

    def write(self, a, n, v):
        a &= 0xffffffff
        for i in range(n):
            self.mem[a+i] = (v >> (8*i)) & 255
    w = write

    def string(self, p):
        if not p:
            return None
        data = bytearray()
        for i in range(1024):
            b = self.read(p+i, 1)
            if not b:
                return data.decode()
            data.append(b)
        raise AssertionError('unterminated string')

    def token(self, s):
        if s is None:
            return 0
        if s not in self.tokens:
            p = self.alloc()
            self.tokens[s] = p
            for i, b in enumerate(s.encode() + b'\0'):
                self.w(p+i, 1, b)
            self.w(p-4, 4, 1000)
        return self.tokens[s]

    def lst(self, rows):
        p = self.alloc()
        self.w(p+8, 4, len(rows))
        self.w(p+12, 4, max(64, len(rows)))
        self.w(p+16, 4, p+64)
        for i, v in enumerate(rows):
            self.w(p+64+i*4, 4, v)
        return p

    def obj(self):
        p = self.alloc()
        self.w(p+4, 4, 1)
        return p

    def invoke(self, entry, *args):
        covered = self.covered
        self.ee_reset()
        self.covered = covered
        self.r[4:4+len(args)] = [v & MASK for v in args]
        self.r[28], self.r[29], self.r[31] = 0x55c870, 0x1fff000, 0xfffffff0
        self.run_until(entry, 0xfffffff0)
        return sx(self.r[2], 32)

    def call_hook(self, entry):
        self.r[2] = self.call(entry, [x & 0xffffffff for x in self.r[4:12]]) & MASK

    def call(self, e, a):
        if e == 0x12a4a4:
            return int(self.string(a[0]) != self.string(a[1]))
        if e == 0x129e60:
            fmt = self.string(a[1])
            text = fmt % tuple(self.string(x) for x in a[2:2+fmt.count('%s')])
            for i, b in enumerate(text.encode()+b'\0'):
                self.w(a[0]+i, 1, b)
            return len(text)
        if e == 0x2eaf60:
            return self.token(self.string(a[1]))
        if e == 0x30c940:
            raise AssertionError('unexpected string destruction')
        if e == RUNBUFFER:
            self.trace.append(('buffer', a[1], a[2], self.string(a[3])))
            return self.results.get(a[1], 0)
        if e == RUNFILE:
            self.trace.append(('file', self.string(a[1])))
            return self.file_result
        if e == 0x301000:
            return 0
        if e == 0x2f88e0:
            return BASE + 0x2000
        if e == 0x35aa20:
            self.trace.append(('create-state',))
            return STATE
        if e in (0x2ed4c0, 0x2465f0, 0x253170, 0x246230):
            self.trace.append(('close-step', e, a[0]))
            return 0
        if e == 0x236f80:
            return SELF  # controlled registered Lua manager
        if e == 0x38a2d0:
            self.trace.append(('fresh-state',))
            return 0
        if e == 0x389ff0:
            self.trace.append(('script', self.string(a[1]), self.string(a[2])))
            return 0
        if e == 0x38e670:
            self.trace.append(('sd', self.string(a[1]), self.string(a[2])))
            return 0
        if e == 0x2ff820:
            self.trace.append(('destroy', a[0]))
            return 0
        if e == 0x2d6680:
            self.trace.append(('capacity', a[0], a[1]))
            return 0
        if e in (0x3817d0, 0x3810c0):
            self.trace.append(('load-step', e))
            return 1
        if e == 0x38f220:
            return 0
        raise AssertionError(f'unknown leaf {e:#x}')

    def infos(self, groups):
        infos = []
        for group in groups:
            rows = []
            for name, payload, result in group:
                row = self.obj()
                data = self.obj()
                self.w(data+8, 4, 32)
                self.w(data+12, 4, payload)
                self.w(row+8, 4, self.token(name))
                self.w(row+12, 4, data)
                rows.append(row)
                self.results[payload] = result
            info = self.obj()
            self.w(info+28, 4, self.lst(rows))
            infos.append(info)
        self.w(SELF+20, 4, self.lst(infos))


def lookup_checks(image):
    # First match per info, all infos in forward order; last status gates fallback.
    cases = [
        ([], [], -1),
        ([[('x.lua', 11, 0), ('x.lua', 12, 0)]], [11], 0),
        ([[('x.lua', 11, 0)], [('x.lua', 21, 0)]], [11, 21], 0),
        ([[('other.lua', 11, 0)], [('x.lua', 21, 0)]], [21], 0),
        ([[('x.lua', 11, -1)], [('x.lua', 21, 0)]], [11, 21], 0),
        ([[('x.lua', 11, 0)], [('x.lua', 21, -1)]], [11, 21], -1),
        ([[('x.lua', 11, 2)]], [11], 2),
        ([[('x.lua', 11, 1)]], [11], 1),
    ]
    n = 0
    for groups, payloads, status in cases:
        for explicit in (False, True):
            for file_result in (0, 2, -1):
                w = World(image)
                w.infos(groups)
                w.file_result = file_result
                result = w.invoke(0x389ff0, SELF, w.token('x.lua'),
                                  w.token('custom/lua') if explicit else 0)
                expected = [('buffer', p, 32, 'x.lua') for p in payloads]
                if status == -1:
                    expected.append(('file', ('custom/lua' if explicit else 'stagML11/lua')+'/x.lua'))
                assert w.trace == expected, (w.trace, expected)
                assert result == (file_result if status == -1 else status)
                n += 1
    return n


def startup_checks(image):
    w = World(image)
    expected = {
        3: ([('fresh-state',), ('script', 'func.lua', 'stagML11/lua'),
              ('script', 'boot.lua', 'stagML11/lua')], 4),
        7: ([('sd', 'TEXTCTL', 'INITIALIZE'), ('script', 'start.lua', 'stagML11/lua')], 8),
        8: ([], 9),
        9: ([('script', 'first.lua', 'stagML11/lua')], -1),
    }
    for state, (trace, next_state) in expected.items():
        w.trace.clear()
        w.w(SELF+0x3c, 4, state)
        w.invoke(0x37fa30, SELF)
        assert w.trace == trace, (state, w.trace)
        assert sx(w.read(SELF+0x3c, 4), 32) == next_state
    # Frame suspension gates every state; 8 enables system before first.lua.
    assert w.read(SYS+0x2c, 1) == 1
    for state in expected:
        w.trace.clear()
        w.w(SYS+0x58, 4, 1)
        w.w(SELF+0x3c, 4, state)
        w.invoke(0x37fa30, SELF)
        assert not w.trace and w.read(SELF+0x3c, 4) == state
    return 8


def cleanup_checks(image):
    n = 0
    for count in (0, 1, 8, 9, 17):
        w = World(image)
        infos = [w.obj() for _ in range(count)]
        state = w.obj()
        lst = w.lst(infos)
        w.w(SELF+20, 4, lst)
        w.w(SELF+24, 4, state)
        w.invoke(0x38a490, SELF)
        assert w.trace == [('destroy', p) for p in infos + [state]]
        assert w.read(lst+8, 4) == 0 and w.read(SELF+24, 4) == 0
        assert all(w.read(lst+64+i*4, 4) == 0 for i in range(count))
        # DM RemoveAll deferral preserves both active and unfinished groups.
        for deferred in (False, True):
            w = World(image)
            groups = [w.obj() for _ in range(count)]
            building = w.obj()
            lst = w.lst(groups)
            w.w(SELF+28, 4, lst)
            w.w(SELF+24, 4, building)
            w.w(SELF+0x20, 1, 1)
            w.w(SELF+0x21, 1, deferred)
            w.invoke(0x37eb80, SELF)
            if deferred:
                assert not w.trace and w.read(SELF+0x22, 1) == 1
                assert w.read(lst+8, 4) == count and w.read(SELF+24, 4) == building
            else:
                assert w.trace == [('destroy', p) for p in groups] + [('capacity', lst, 0), ('destroy', building)]
                assert w.read(lst+8, 4) == 0 and w.read(SELF+24, 4) == 0
                assert w.read(SELF+0x20, 1) == w.read(SELF+0x22, 1) == 0
            n += 1
        w = World(image)
        context = w.obj()
        lists = [w.lst([w.obj() for _ in range(count)]) for _ in range(4)]
        owned = [[w.read(p+64+i*4, 4) for i in range(count)] for p in lists]
        w.w(SELF+16, 4, context)
        for off, p in zip((20, 24, 28, 32), lists):
            w.w(SELF+off, 4, p)
        w.w(SELF+0x24, 4, 7)
        w.w(SELF+0x28, 8, 123)
        w.w(SELF+0x30, 1, 1)
        w.invoke(0x38c490, SELF)
        trace = [('destroy', context)]
        for p, rows in zip(lists, owned):
            trace += [('destroy', v) for v in rows] + [('capacity', p, 4)]
            assert w.read(p+8, 4) == 0
        assert w.trace == trace
        assert all(w.read(SELF+off, size) == 0 for off, size in ((16,4),(0x24,4),(0x28,8),(0x30,1)))
        n += 2
    # The tick epilogue clears the disable byte before consuming the deferred
    # RemoveAll latch. Even an empty pass must release unfinished build data.
    for requested in (False, True):
        w = World(image)
        building, vt = w.obj(), w.alloc()
        lst = w.lst([])
        w.w(SELF, 4, vt)
        w.w(vt+0x70, 4, 0x37eb80)
        w.w(SELF+28, 4, lst)
        w.w(SELF+24, 4, building)
        w.w(SELF+0x20, 1, 1)
        w.w(SELF+0x22, 1, requested)
        w.descend.add(0x37eb80)
        w.invoke(0x37ed70, SELF)
        assert w.read(SELF+0x21, 1) == 0
        if requested:
            assert w.trace == [('capacity', lst, 0), ('destroy', building)]
            assert w.read(SELF+24, 4) == w.read(SELF+0x20, 1) == w.read(SELF+0x22, 1) == 0
        else:
            assert not w.trace and w.read(SELF+24, 4) == building
        n += 1
    return n


def coordinator_checks(image):
    # The real coordinator invokes every manager's RemoveAll in forward order,
    # before releasing its collected objects. Methods here are opaque leaves.
    n = 0
    for count in (0, 1, 8, 35):
        w = World(image)
        rows = [w.obj() for _ in range(count)]
        methods = {}
        for i, row in enumerate(rows):
            vt = w.alloc()
            entry = BASE + 0x3000 + i*4
            w.w(row, 4, vt)
            w.w(vt+0x70, 4, entry)
            methods[entry] = i
        registry = w.obj()
        w.w(registry+8, 4, w.lst(rows))
        w.w(SELF+8, 4, registry)
        pending = [w.obj() for _ in range(3)]
        collected = w.lst(pending)
        w.w(SELF+16, 4, collected)
        call = w.call
        def leaf(e, a):
            if e in methods:
                w.trace.append(('remove-all', methods[e], a[0]))
                # Objects are still owned when manager cleanup executes.
                assert w.read(collected+8, 4) == 3
                return 0
            return call(e, a)
        w.call = leaf
        w.invoke(0x2370c0, SELF)
        assert w.trace == ([('remove-all', i, row) for i, row in enumerate(rows)] +
                           [('destroy', p) for p in pending] + [('capacity', collected, 0)])
        assert w.read(collected+8, 4) == 0
        n += 1
    w = World(image)
    old = w.obj()
    w.w(SELF+24, 4, old)
    w.invoke(0x38a2d0, SELF)
    assert w.trace == [('destroy', old), ('create-state',)]
    assert w.read(SELF+24, 4) == STATE
    # State shutdown frees the RunFile scratch buffer, then closes the base VM.
    w = World(image)
    w.w(STATE+20, 4, BUFFER)
    w.invoke(0x38a660, STATE)
    assert w.trace == [('close-step', 0x2ed4c0, BUFFER), ('close-step', 0x2465f0, STATE)]
    w = World(image)
    w.w(STATE+12, 4, VM)
    w.w(0x56df48, 4, BASE+0x5000)
    w.invoke(0x2465f0, STATE)
    assert w.trace == [('close-step', 0x253170, VM), ('close-step', 0x246230, BASE+0x5000)]
    return n + 3


def snapshot_checks(path):
    from system_clock_probe import _extract, SYS_CLOCK
    ram = _extract(path)
    def read(a):
        assert 0 <= a <= len(ram)-4
        return int.from_bytes(ram[a:a+4], 'little')
    def string(a):
        assert 0 < a < len(ram)
        end = ram.find(b'\0', a, a+512)
        assert end >= a
        return ram[a:end].decode()
    scheduler = read(SYS_CLOCK+12)
    lst = read(read(scheduler+8)+8)
    count, data = read(lst+8), read(lst+16)
    assert count <= read(lst+12) <= 100000
    methods = []
    lua = None
    for i in range(count):
        manager = read(data+i*4)
        method = read(read(manager)+0x70)
        methods.append(method)
        if method == 0x38a490:
            lua = manager
    assert [methods.index(e) for e in (0x38d080, 0x38a490, 0x37eb80)] == [3, 7, 8]
    assert lua is not None
    stage = string(read(read(lua+16)+56))
    infos = read(lua+20)
    rows = []
    assert read(infos+8) <= read(infos+12) <= 100000
    for i in range(read(infos+8)):
        info = read(read(infos+16)+i*4)
        data = read(info+28)
        assert read(data+8) <= read(data+12) <= 100000
        names = [string(read(read(read(data+16)+j*4)+8)) for j in range(read(data+8))]
        assert all(name in names for name in ('func.lua', 'boot.lua', 'start.lua', 'first.lua'))
        rows.append(len(names))
    print(f'{path.name}: {stage}, {count} managers, SD/Lua/DM cleanup slots 3/7/8, '
          f'Lua-info chunk counts {rows}, state {read(lua+24):#x}')


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf', type=Path, default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    p.add_argument('--state', type=Path, action='append', default=[],
                   help='Optional offline retail savestate roster/loaded-info check')
    a = p.parse_args()
    image = a.elf.read_bytes()
    assert image[:4] == b'\x7fELF'
    n = lookup_checks(image) + startup_checks(image) + cleanup_checks(image) + coordinator_checks(image)
    for state in a.state:
        snapshot_checks(state)
    print(f'Retail Lua ownership: {n} lookup/startup/cleanup contract samples passed (controlled leaves)')

if __name__ == '__main__':
    main()
