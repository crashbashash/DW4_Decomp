#!/usr/bin/env python3
"""Every sound name the original game scripts PLAY must exist in a sound pack's catalogue.

Reads the decompiled Lua (`lua/`, `... "PLAY", "NAME"` and `"PLAYatPAUSE"` requests) and the cue names of every
igb file that carries a sound pack (`build/survey_stagesound <roms> --names`), and requires that no requested name is missing
from every pack. This is a coverage check of the catalogue against the scripts that use it; it does not say which stage a
script runs in, or that the cue plays correctly.

    python3 tools/verify_stagesound_lua.py [--roms DIR] [--lua DIR]
"""
import argparse
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REQUEST = re.compile(r'"(?:PLAY|PLAYatPAUSE)"\s*,\s*"([A-Za-z_0-9]+)"')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--roms", default=os.path.join(ROOT, "..", "..", "local", "extracted"))
    ap.add_argument("--lua", default=os.path.join(ROOT, "..", "lua"))
    args = ap.parse_args()
    tool = os.path.join(ROOT, "build", "survey_stagesound")
    out = subprocess.run([tool, args.roms, "--names"], check=True, capture_output=True, text=True).stdout
    catalogue = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 3:
            catalogue.setdefault(parts[1], parts[0])
    requested = set()
    for dirpath, _, files in os.walk(args.lua):
        for name in files:
            if name.endswith(".lua"):
                with open(os.path.join(dirpath, name), errors="replace") as f:
                    requested.update(REQUEST.findall(f.read()))
    missing = sorted(requested - set(catalogue))
    print(f"stagesound/lua: {len(requested)} distinct PLAY names, {len(catalogue)} distinct cue names in "
          f"the sound packs, {len(missing)} missing")
    if missing:
        print("missing:", ", ".join(missing))
        return 1
    if len(requested) < 60:
        print("stagesound/lua: too few script requests were found; is the Lua tree present?")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
