#!/usr/bin/env python3
"""CFL queue and USA query contracts against actual retail instructions.

Interner, list indexing/appending and capacity allocation are controlled leaves.
No scene/gameplay service behavior is established by this comparison.
"""
import argparse
from pathlib import Path
import random
import subprocess
from verify_scriptownership_retail import World, SYS


class QueueWorld(World):
    def __init__(self, image):
        super().__init__(image)
        self.w(0x58a1b8, 4, SYS)
        self.queue = self.lst([])
        self.w(SYS + 0x34, 4, self.queue)
        self.w(SYS + 0x38, 4, self.token('stagIS10'))

    def call(self, entry, args):
        if entry == 0x1c64e0:  # igStringList element copy
            self.w(args[0], 4, self.read(self.read(args[1] + 16, 4) + 4*args[2], 4))
            return 0
        if entry == 0x1ca620:  # append the supplied interned string reference
            n = self.read(args[0] + 8, 4)
            self.w(self.read(args[0] + 16, 4) + 4*n, 4, self.read(args[1], 4))
            self.w(args[0] + 8, 4, n + 1)
            return 0
        return super().call(entry, args)

    def paths(self):
        n = self.read(self.queue + 8, 4)
        p = self.read(self.queue + 16, 4)
        return [self.string(self.read(p + 4*i, 4)) for i in range(n)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf', type=Path, default=Path('../../local/extracted/SLUS_208.36'))
    parser.add_argument('--roms', default='../../local/extracted')
    parser.add_argument('--tool', default='build/test_filelist')
    args = parser.parse_args()
    image = args.elf.read_bytes()
    rng = random.Random(5150)
    cases = [[], ['a'], ['a', 'a'], ['a', 'A', 'a'], ['a', '<clear>', 'b'],
             ['<clear>', '<clear>'], ['a', 'b', '<clear>', 'a', 'a'],
             [f'asset{i}.igb' for i in range(70)]]
    cases += [[rng.choice(['a', 'A', '_common/m_dorumon.igb', 'stage/USA_pack.igb', '<clear>'])
               for _ in range(n)] for n in range(1, 25)]
    for commands in cases:
        world = QueueWorld(image)
        for path in commands:
            if path == '<clear>':
                world.invoke(0x372a30)
            else:
                world.invoke(0x372b50, world.token(path))
        expected = ['folder:' + world.string(world.invoke(0x372ce0))]
        for method, address in [('SYSgetArea', 0x371ed0), ('SYSgetCountry', 0x371ee0),
                                ('SYSgetIsPackOnly', 0x371f00)]:
            expected.append(f'{method}:{world.invoke(address)}')
        expected += ['queue:' + path for path in world.paths()]
        native = subprocess.run([args.tool, args.roms, '--queue', *commands],
                                check=True, text=True, capture_output=True)
        assert native.stdout.splitlines() == expected, (commands, native.stdout, expected)
    print(f'file-list retail: {len(cases)} native/retail queue, folder and USA constant comparisons passed')


if __name__ == '__main__':
    main()
