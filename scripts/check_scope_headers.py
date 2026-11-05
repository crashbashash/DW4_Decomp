#!/usr/bin/env python3
"""Every class named in config/typed-scope.tsv has its authoritative struct in include/dw4/reflected.h.

The scope list names a class per function; `FUN` (unnamed helpers) and `bePlayer` (the helper `bePlayer_GetStruct`, no reflected
class) are not classes and are excluded, as docs/engine/typed-game-layer.md records. Exits 1 and lists the classes that lack a struct.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NOT_CLASSES = {"FUN", "bePlayer"}


def main():
    scope = set()
    with open(os.path.join(ROOT, "config", "typed-scope.tsv")) as f:
        for line in f:
            if line.strip() and not line.startswith("#"):
                c = line.rstrip("\n").split("\t")[1]
                if c not in NOT_CLASSES and not c.startswith("FUN_"):
                    scope.add(c)
    header = open(os.path.join(ROOT, "include", "dw4", "reflected.h")).read()
    have = set(re.findall(r"^\} (\w+);", header, re.M))
    missing = sorted(scope - have)
    print("scope headers: %d in-scope classes, %d with an authoritative struct" % (len(scope), len(scope) - len(missing)))
    if missing:
        print("missing: " + ", ".join(missing))
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
