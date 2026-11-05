#!/usr/bin/env python3
"""Check retail RAM slot assignment, Work record default and object health.

Manager/class acceptance, list insertion and instance initialization are leaves.
Health initialization executes 396d74..98; record metadata executes 3510e4..104.
Direct-sequence health preservation is a native regression guard. This does not
establish full model dispatch, gameplay records or rendering.
"""
import argparse
from pathlib import Path
import subprocess
from verify_scriptservices_retail import World, BASE, ROOT

MANAGER = BASE + 0x80000
INFO = MANAGER + 0x1000
RAMLIST = INFO + 0x100
ARRAY = RAMLIST + 0x100
RAM = MANAGER + 0x10000
VT = MANAGER + 0x20000
GETCLASS, INFOCLASS, INITINFO, INITRAM = range(VT + 0x1000, VT + 0x1400, 0x100)

class Slots(World):
    def __init__(self, image, count, accepted):
        super().__init__(image)
        self.accepted = accepted
        self.slots = []
        self.calls = []
        self.w(MANAGER, 4, VT)
        self.w(MANAGER + 0x18, 4, RAMLIST + 0x300)
        self.w(VT + 0x80, 4, GETCLASS)
        self.w(VT + 0x78, 4, INITINFO)
        self.w(VT + 0x7c, 4, INITRAM)
        self.w(INFO, 4, VT + 0x200)
        self.w(VT + 0x200 + 0x58, 4, INFOCLASS)
        self.w(INFO + 0x18, 4, RAMLIST)
        self.w(RAMLIST + 8, 4, count)
        self.w(RAMLIST + 0x10, 4, ARRAY)
        for i in range(count):
            row = RAM + i * 0x40
            self.w(ARRAY + 4*i, 4, row)
            for off in (8, 12, 16, 24, 28, 32, 36):
                self.w(row + off, 4, 0xdeadbeef)
    def call(self, entry, a):
        if entry == GETCLASS:
            return 123
        if entry == INFOCLASS:
            return 123 if self.accepted else 456
        if entry == INITRAM:
            assert a[0] == MANAGER
            row = a[1]
            self.slots.append(self.read(row + 8, 4))
            assert self.read(row + 12, 4) == INFO
            assert self.read(row + 16, 4) == MANAGER
            assert all(self.read(row + off, 4) == 0 for off in (24, 28, 32, 36))
            return 0
        if entry in (INITINFO, 0x301e30, 0x236be0):
            self.calls.append(entry)
            return 0
        raise AssertionError(hex(entry))

class Health(World):
    def generate(self, hp, max_hp):
        work=BASE+0x90000;ramdata=work+0x100;maximum=work+0x200;current=work+0x300
        self.ee_reset();self.r[17]=ramdata
        self.w(ramdata+20,4,work);self.w(work+8,4,maximum);self.w(work+12,4,current)
        self.w(maximum+12,4,max_hp);self.w(current+12,4,hp)
        self.run_until(0x396d74,0x396d98)
        return tuple(int.from_bytes(self.read(p+12,4).to_bytes(4,'little'),'little',signed=True) for p in (current,maximum))
    def record_default(self):
        self.ee_reset();self.r[16]=INFO;self.r[17]=0
        self.default=None;self.run_until(0x3510e4,0x351104)
        return self.default
    def call(self,entry,a):
        if entry==0x2fdf00:
            assert a[0]==INFO and a[1]==2 # Work._recNo descriptor
            return INFO+0x100
        if entry==0x2ea4b0:
            assert a[0]==INFO+0x100
            self.default=a[1]&0xffffffff;return 0
        return super().call(entry,a)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf', type=Path, default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    parser.add_argument('--roms',type=Path,default=ROOT.parent.parent / 'local/extracted')
    parser.add_argument('--tool',type=Path,default=ROOT/'build/test_controllers')
    args=parser.parse_args();image = args.elf.read_bytes()
    for accepted in (False, True):
        for count in (0, 1, 2, 12, 64):
            world = Slots(image, count, accepted)
            result = world.invoke(0x3787a0, MANAGER, INFO)
            assert world.slots == (list(range(count)) if accepted else [])
            assert bool(result) == accepted
            assert world.calls == ([0x301e30, INITINFO, 0x236be0] if accepted else [])
    print('Controller slots retail: 10 acceptance/row-order cases passed; instance initializer is a controlled leaf')
    health=Health(image);assert health.record_default()==0xffffffff
    output=subprocess.check_output([str(args.tool),str(args.roms),'--health'],text=True)
    samples=0;generated=0
    for line in output.splitlines():
        if not line.startswith('HEALTH '):continue
        active,generate,hp,maximum,got_hp,got_max=map(int,line.split()[1:])
        expected=health.generate(hp,maximum) if generate else (hp,maximum)
        assert (got_hp,got_max)==expected,(line,expected)
        samples+=1
        generated+=generate
    assert samples==64 and generated==32
    print('Controller state retail: Work record default -1, 32 GENERATE health comparisons and 32 native sequence-preservation guards passed; allocation/other creation services excluded')

if __name__ == '__main__':
    main()
