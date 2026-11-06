#!/usr/bin/env python3
"""verify_skin.py — diff the port's C skinning path against `scripts/live_skin.py`.

The engine's skinning data is runtime-only, so both the C path
(`dw4asset skin`, `src/skin.c`) and the Python extractor (`scripts/live_skin.py`) read it
from the same paused EE RAM dump.  This runs both over every 24-matrix palette in the pool
and requires the **OBJ bytes** to be identical, for the bind pose and the posed mesh — a
wrong field offset, bone map, matrix convention or triangle rule shows up as different text.

  tools/verify_skin.py [--tool build/dw4asset] [--ram <dump>] [--script <live_skin.py>]

Skipped (exit 0) when no dump is present, so `make check` runs on a machine without one.
Point `DW4_LIVEDUMP` (or `--ram`) at the dump to enable it.
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_RAM = os.environ.get("DW4_LIVEDUMP", "")
DEFAULT_SCRIPT = os.path.join(PORT, "..", "scripts", "live_skin.py")

PAL_RE = re.compile(r"palette\[(\d+)\]\s+([0-9a-f]+)\s+(\d+) matrices")


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True)


def check_one(tool, ram, script, bad):
    if not os.path.exists(ram):
        print("  skin: no RAM dump (%s), skipped" % ram)
        return bad
    if not os.path.exists(script):
        print("  skin: %s missing, skipped" % script)
        return bad

    listing = run([tool, "skin", ram, "--list"])
    if listing.returncode != 0:
        print("  skin: the C reader failed:\n%s%s" % (listing.stdout, listing.stderr))
        return bad + 1
    palettes = [(int(m.group(1)), int(m.group(3)))
                for m in PAL_RE.finditer(listing.stdout)]
    # the shipped mesh's bone map covers ~24 slots; the 40-matrix palettes are another skeleton
    todo = [k for k, n in palettes if 18 <= n <= 27][:3]
    if not todo:
        print("  skin: no character-sized palette in the pool")
        return bad + 1

    with tempfile.TemporaryDirectory() as tmp:
        for k in todo:
            cbind = os.path.join(tmp, "c%d_bind.obj" % k)
            couter = os.path.join(tmp, "c%d.obj" % k)
            pbind = os.path.join(tmp, "p%d_bind.obj" % k)
            pouter = os.path.join(tmp, "p%d.obj" % k)
            for cmd in ([tool, "skin", ram, "--palette", str(k),
                         "--bind", cbind, "--out", couter],
                        [sys.executable, script, "--from", ram, "--palette", str(k),
                         "--bind", pbind, "--out", pouter]):
                r = run(cmd)
                if r.returncode != 0:
                    print("  skin palette %d: extractor failed: %s" % (k, r.stderr))
                    bad += 1
            if bad:
                continue
            ok = True
            for a, b in ((cbind, pbind), (couter, pouter)):
                if open(a, "rb").read() != open(b, "rb").read():
                    print("  skin palette %d: %s differs from the Python OBJ"
                          % (k, os.path.basename(a)))
                    ok = False
            if ok:
                print("  skin palette %-2d  bind + posed OBJ bytes identical  ok" % k)
            else:
                bad += 1
    return bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4asset"))
    ap.add_argument("--ram", action="append", default=None,
                    help="a paused EE RAM dump (repeatable; default: DW4_LIVEDUMP)")
    ap.add_argument("--script", default=DEFAULT_SCRIPT)
    args = ap.parse_args()

    rams = args.ram or ([DEFAULT_RAM] if os.path.exists(DEFAULT_RAM) else [])
    if not rams:
        print("  skin: no RAM dump (set DW4_LIVEDUMP), skipped")
        return 0
    bad = 0
    for ram in rams:
        print("  %s" % os.path.basename(ram))
        bad = check_one(args.tool, ram, args.script, bad)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
