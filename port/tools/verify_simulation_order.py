#!/usr/bin/env python3
"""Check DM/Action2 serial-manager order against a private retail savestate."""
import argparse
from pathlib import Path
import sys
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from system_clock_probe import _extract, SYS_CLOCK
p = argparse.ArgumentParser(description=__doc__)
p.add_argument('state', type=Path)
a = p.parse_args()
ram = _extract(a.state)
def read(addr):
    assert 0x100000 <= addr <= len(ram)-4
    return int.from_bytes(ram[addr:addr+4], 'little')
scheduler = read(SYS_CLOCK+12)
assert read(read(scheduler)+0x5c) == 0x237ec0
lst = read(read(scheduler+8)+8)
count, capacity, data = read(lst+8), read(lst+12), read(lst+16)
assert count <= capacity <= 100000
slots = []
for i in range(count):
    manager = read(data+4*i)
    vtable = read(manager)
    slots.append((read(vtable+0x74), read(vtable+0x84)))
dm = [i for i, pair in enumerate(slots) if pair[0] == 0x37ed70]
action = [i for i, pair in enumerate(slots) if pair == (0x378bc0, 0x3778d0)]
assert dm == [8] and action == [17], (dm, action)
assert dm[0] < action[0]
print(f'Retail serial scheduler: {count} managers; DM slot 8 precedes Action2 slot 17')
