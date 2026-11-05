#!/usr/bin/env python3
"""Diff DW4 save story-state (BASE_FLAG / BASE_FLAGFOLDER / BASE_COUNTER).

Usage: diff_story.py <save_a> <save_b>
Inputs are extracted 81920-byte saves or PS2 memory-card images (optional ps2mc).
Prints byte diffs in the story regions between two saves.
"""
import argparse
from save_probe import read_save_payload

REGIONS = {
    'flags':   (0x320, 1024),      # BASE_FLAG (1024 x u8, ids 0..936)
    'folder':  (0x720, 12),        # BASE_FLAGFOLDER (12 x u8)
    'counter': (0x72c, 0x50),      # BASE_COUNTER + gap
}


def story_state(path):
    raw = read_save_payload(path)
    return {region: raw[off:off + size] for region, (off, size) in REGIONS.items()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("save_a")
    parser.add_argument("save_b")
    parser.add_argument("--full", action="store_true", help=argparse.SUPPRESS)
    args = parser.parse_args()
    a_path, b_path = args.save_a, args.save_b
    try:
        a, b = story_state(a_path), story_state(b_path)
    except (OSError, ValueError) as exc:
        parser.error(str(exc))
    print(f"# {a_path}  ->  {b_path}")
    for region in ('flags', 'folder', 'counter'):
        ba, bb = a[region], b[region]
        base = REGIONS[region][0]
        for i, (x, y) in enumerate(zip(ba, bb)):
            if x != y:
                off = base + i
                print(f"{region} +{i:03x} (off 0x{off:04x}): 0x{x:02x} -> 0x{y:02x}")


if __name__ == '__main__':
    main()
