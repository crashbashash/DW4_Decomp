#!/usr/bin/env python3
"""verify_platform.py -- the port's copy of the platform seam still matches the recovered one.

`include/dw4/platform.h` carries the `igPsx2*` -> generic-interface inventory (porting P2.1), copied
from the decompilation repo's `docs/engine/platform-seam.md`.  The numbers are pinned here, so if the
recovered seam changes -- a class appears, a base moves, a field count differs -- this check fails
instead of the port quietly believing a stale seam.

    tools/verify_platform.py            # in `make check`
"""
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, "..")

# pinned from docs/engine/platform-seam.md; regenerate that doc and update these
# three numbers together, never one alone
EXPECT_CLASSES = 31          # igPsx2* classes under a generic interface (igPsx2IopRpcConnection is
                             # not: it derives from igObject and is deleted on a port)
EXPECT_IFACES = 30           # distinct generic interfaces among them
EXPECT_FIELDS = 153          # serialised fields across those interfaces


def main():
    text = open(os.path.join(ROOT, "src", "host.c")).read()
    body = text[text.index("dw4_ifaces[] = {"):]
    rows = re.findall(r'\{\s*"([^"]+)",\s*"([^"]+)",\s*(\d+),\s*(DW4_IF_\w+)\s*\}', body)
    if len(rows) != EXPECT_CLASSES:
        print("verify_platform: %d rows, expected %d" % (len(rows), EXPECT_CLASSES))
        return 1
    ifaces = sorted({r[1] for r in rows})
    if len(ifaces) != EXPECT_IFACES:
        print("verify_platform: %d distinct interfaces, expected %d" % (len(ifaces), EXPECT_IFACES))
        return 1
    fields = sum(int(r[2]) for r in rows)
    if fields != EXPECT_FIELDS:
        print("verify_platform: %d fields, expected %d" % (fields, EXPECT_FIELDS))
        return 1
    host = [r for r in rows if r[3] == "DW4_IF_HOST"]
    if len(host) != 1 or host[0][0] != "igPsx2File":
        print("verify_platform: expected exactly igPsx2File implemented, got %s"
              % [r[0] for r in host])
        return 1
    inp = [r for r in rows if r[3] == "DW4_IF_INPUT"]
    if sorted(r[0] for r in inp) != ["igPsx2Controller", "igPsx2ControllerManager"]:
        print("verify_platform: expected the two controller interfaces implemented as input, got %s"
              % [r[0] for r in inp])
        return 1
    if not all(r[3] in ("DW4_IF_STUB", "DW4_IF_HOST", "DW4_IF_INPUT") for r in rows):
        print("verify_platform: unknown status in the table")
        return 1
    print("verify_platform: %d class(es) -> %d interface(s), %d field(s); "
          "%d implemented (%s), %d input (%s), %d stub"
          % (len(rows), len(ifaces), fields, len(host), host[0][1],
             len(inp), "igPsx2Controller", len(rows) - len(host) - len(inp)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
