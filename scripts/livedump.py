#!/usr/bin/env python3
"""livedump.py — an EE RAM image the offline tools can address, from a PCSX2 savestate.

The tools that read a live capture (`capture_scene.py`, `camera_match.py`, `texture_map.py`,
`extract_live_models.py`, and the port's `--livedump`) all assume the dump
**starts at EE 0x00100000** (the kernel owns the low megabyte).  `scripts/p2s_ram.py` writes the
whole 32 MB `eeMemory.bin` starting at 0, so feeding it straight to a tool shifts every address by
0x100000 — an object resolves at 0x001…… where the tool looks at 0x000……, and the graph comes back
empty rather than wrong-looking.  This wrapper does the trim, so the dump is addressed the way the
tools expect:

    python3 scripts/livedump.py <savestate>.p2s out.bin

    # then, no emulator needed:
    python3 scripts/capture_scene.py --from out.bin --pack ../local/extracted/NDMW.AFS:614 --tsv s.tsv
    python3 scripts/camera_match.py --from out.bin --pack ../local/extracted/NDMW.AFS:614 \\
        --target 421.83 72 -110.07 --character auto --tsv cam.tsv --textures
    port/build/dw4asset livetex out.bin --list

The port's `livetex.c` accepts both sizes (it auto-detects the base), so only the Python tools need
the trim.
"""
import argparse
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
P2S_RAM = os.path.join(HERE, "..", "scripts", "p2s_ram.py")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("state", help="a PCSX2 .p2s savestate")
    ap.add_argument("out", help="output RAM image (EE 0x00100000 .. 0x02000000)")
    ap.add_argument("--p2s-ram", default=P2S_RAM, help="scripts/p2s_ram.py path")
    args = ap.parse_args()

    tmp = args.out + ".32m"
    r = subprocess.run([sys.executable, args.p2s_ram, args.state,
                        "--extract", "eeMemory.bin", "--out", tmp])
    if r.returncode != 0 or not os.path.exists(tmp):
        sys.exit("livedump: p2s_ram.py did not write %s" % tmp)
    data = open(tmp, "rb").read()
    if len(data) == 0x2000000:
        # the whole 32 MB from 0: drop the kernel's low megabyte
        open(args.out, "wb").write(data[0x100000:])
        print("livedump: %s -> %s (%d bytes, base 0x00100000)" % (args.state, args.out,
                                                                  len(data) - 0x100000))
    elif len(data) == 0x1f00000:
        os.replace(tmp, args.out)
        print("livedump: %s -> %s (already based at 0x00100000)" % (args.state, args.out))
    else:
        sys.exit("livedump: eeMemory.bin is %d bytes, expected 31 or 32 MB" % len(data))
    try:
        os.remove(tmp)
    except OSError:
        pass
    return 0


if __name__ == "__main__":
    sys.exit(main())
