#!/usr/bin/env python3
"""Layer-switch dispatch and first-accepting-manager contracts from retail MIPS.

Receiver selection, enum/string parsing and mask mutation are controlled leaves.
The actual dispatcher chooses targets and operations; the native fixture uses
original prepared title assets. This does not establish scene/draw equivalence.
"""
import argparse
from pathlib import Path
import subprocess
from verify_scriptownership_retail import World, BASE, SELF, INFO, MSG

LAYERS = ('BG01 BG02 GM01 GM02 EM01 NP01 PC01 EF01 EF02 EF03 BG03 GM03 '
          'WN00 WN01 WN02 WN03 WN04 FONT LOADING NONE').split()
SWITCH, CONTEXT, ARG = BASE+0x3000, BASE+0x4000, BASE+0x5000

class LayerWorld(World):
    def __init__(self, image):
        super().__init__(image)
        self.bits = [0]*20
        self.bits[18] = 1  # file-list phase 6 LOADING/SET
        rows = []
        for name in LAYERS:
            p = self.obj()
            self.w(p+8, 4, self.token(name))
            rows.append(p)
        self.w(SWITCH+0x1c, 4, self.lst(rows))
        self.w(SWITCH+0x20, 4, self.lst([1<<18]))
        self.w(SELF+0x24, 4, SWITCH)
        self.w(CONTEXT+12, 4, INFO)
        self.w(ARG+20, 4, self.token('SWITCH'))
        self.params = []

    def call(self, e, a):
        if e in (0x35ca40, 0x35c9e0):
            return e
        if e == 0x38d4a0:
            if a[1] == 0x35ca40:
                return 1  # SWITCH
            return {'CLR':0, 'DISPOFF':0, 'SET':1, 'DISPON':1, 'FLIP':2}.get(self.string(a[2]), -1)
        if e == 0x38f820:
            return len(self.params)
        if e == 0x38f8f0:
            return self.token(self.params[a[1]])
        if e in (0x1dc820, 0x1dc880, 0x1dc870, 0x1dc8d0):
            value = int(e in (0x1dc820, 0x1dc870))
            if e in (0x1dc870, 0x1dc8d0):
                self.bits = [value]*len(self.bits)
            else:
                self.bits[a[1]] = value
            block = self.read(SWITCH+0x20, 4)
            self.w(self.read(block+16, 4), 4, sum(b<<i for i,b in enumerate(self.bits)))
            return 0
        return super().call(e, a)

    def command(self, text):
        self.params = text.split('/')
        return self.invoke(0x389170, SELF, CONTEXT, ARG)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf', default='../../local/extracted/SLUS_208.36')
    ap.add_argument('--roms', default='../../local/extracted')
    ap.add_argument('--tool', default='build/test_stageobjects')
    args = ap.parse_args()
    image = Path(args.elf).read_bytes()
    assert image[:4] == b'\x7fELF'
    scenarios = [(f'{name}/{action}',) for name in ('BG01','WN01','LOADING','NONE','missing','ALL')
                 for action in ('SET','CLR','DISPON','DISPOFF','FLIP')]
    scenarios += [('ALL/SET','BG02/CLR','BG02/FLIP'), ('ALL/SET','ALL/FLIP'),
                  ('ALL/CLR','LOADING/FLIP'), ('WN01/SET','WN01/SET','WN01/CLR')]
    for commands in scenarios:
        w = LayerWorld(image)
        for command in commands:
            assert w.command(command) == 1
        result = subprocess.run([str(Path(args.tool).resolve()), args.roms, *commands],
                                check=True, text=True, capture_output=True)
        got = dict(line.split(':') for line in result.stdout.splitlines())
        assert got == dict(zip(LAYERS, map(str,w.bits))), (commands, got, w.bits)
    # Retail central collector probes ordered manager acceptors, stops on the
    # first nonzero result, and retains the object even if no manager accepts.
    for acceptance in ([], [0], [1], [0,1,1], [0,0,0], [0,0,7]):
        w = World(image)
        managers = [w.obj() for _ in acceptance]
        for i, p in enumerate(managers):
            vt = w.alloc();w.w(p,4,vt);w.w(vt+0x6c,4,BASE+0x6000+i*16)
        holder=w.obj();w.w(holder+8,4,w.lst(managers));w.w(SELF+8,4,holder)
        retained=w.lst([]);w.w(SELF+16,4,retained)
        called=[];published=[];old=w.call
        def leaf(e,a):
            if BASE+0x6000 <= e < BASE+0x6100:
                i=(e-(BASE+0x6000))//16;called.append(i)
                assert a[:2] == [managers[i],INFO]
                return acceptance[i]
            if e == 0x301e30:
                assert a[:2] == [retained,INFO];published.append(INFO);return 0
            return old(e,a)
        w.call=leaf;w.invoke(0x237030,SELF,INFO)
        end=next((i+1 for i,v in enumerate(acceptance) if v),len(acceptance))
        assert called == list(range(end)) and published == [INFO]
    print(f'native objects retail: {len(scenarios)} layer-mask scenarios and 6 ordered-manager dispatch contracts passed (controlled leaves)')

if __name__ == '__main__':
    main()
