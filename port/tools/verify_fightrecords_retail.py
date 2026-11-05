#!/usr/bin/env python3
"""Compare retargeted WAZALIST lookup with retail 3fc6f0 instructions.

The property lookup is a controlled leaf; list iteration, first-match selection,
base/row projections and unchanged output on a miss execute from the private ELF.
"""
import argparse
from pathlib import Path
import subprocess
from verify_scriptservices_retail import World, ROOT, BASE

FOLDER, RECORD, LIST, OUTPUT = [BASE + 0x600000 + i * 0x100 for i in range(4)]


class Retail(World):
    def call(self, entry, args):
        if entry == 0x3a9340:
            assert args[0] == FOLDER and args[1] == 0x518928
            return RECORD
        return super().call(entry, args)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf', type=Path, required=True)
    args = parser.parse_args()
    if not args.elf.exists():
        print('fight records retail: private ELF unavailable, skipped')
        return
    world = Retail(args.elf.read_bytes())
    world.descend = {0x3fc6f0}
    world.w(RECORD + 12, 4, LIST)
    total = 0
    for line in subprocess.check_output([str(ROOT / 'build/test_fightrecords'), '--dump'], text=True).splitlines():
        tag, *values = line.split()
        values = list(map(int, values))
        if tag == 'L':
            n, *pairs = values
            assert len(pairs) == n * 2
            items = []
            for i in range(n):
                item = BASE + 0x610000 + i * 0x40
                world.w(item + 12, 4, pairs[i * 2])
                world.w(item + 20, 4, pairs[i * 2 + 1])
                items.append(item)
            world.list(LIST, items)
        elif tag == 'Q':
            base, rc, actual = values
            world.w(OUTPUT, 4, 123456)
            world.invoke(0x3fc6f0, 0, FOLDER, base, OUTPUT)
            expected = world.read(OUTPUT, 4)
            assert actual & 0xffffffff == expected, (base, rc, actual, expected)
            assert rc == (0 if any(pairs[i * 2 + 1] == base for i in range(n)) else -1)
            total += 1
        else:
            raise AssertionError(line)
    assert total == 384, ('incomplete native fixture', total)
    print(f'fight records retail: {total} empty/duplicate/signed/hit/miss lookups match; property lookup controlled')


if __name__ == '__main__':
    main()
