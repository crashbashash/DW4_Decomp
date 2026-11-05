#!/usr/bin/env python3
"""Offline self-test for name_live_models.py's pointer walk (no emulator needed).

Builds a synthetic EE RAM image and checks the corrected ownership rule:

  * a shape's geometry attr is the entry in the **one** igAttrList at its +0x20;
  * the object 0x18 bytes on from that list (the next list in the packed arena) is
    another shape's list and must NOT be claimed;
  * non-geometry entries in the list are skipped;
  * the +0x1c wrapper attr is used only when the +0x20 list yields nothing.

Run:  python3 testing/test_name_live_models.py
"""
import importlib.util
import os
import struct
import sys

HERE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "scripts")
sys.path.insert(0, HERE)


def load():
    spec = importlib.util.spec_from_file_location(
        "name_live_models", os.path.join(HERE, "name_live_models.py"))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


def main():
    nl = load()
    LO, SIZE = 0x100000, 0x100000
    blob = bytearray(SIZE)

    def w32(a, v):
        struct.pack_into("<I", blob, a - LO, v)

    def wstr(a, s):
        blob[a - LO:a - LO + len(s) + 1] = s + b"\x00"

    # Shape 1: has its own list (list1) holding ATTR_A; also a wrapper attr that must be ignored.
    S1, NAME1, WRAP1 = 0x110000, 0x111000, 0x112000
    ATTR_W1 = WRAP1 + 0x18
    ATTR_A = 0x113000
    LIST1, ARR1 = 0x114000, 0x115000
    # Shape 2's list is physically the next object after list1 -- the old stride walk stole it.
    LIST2, ARR2, ATTR_B = LIST1 + 0x18, 0x115100, 0x113100
    S2, NAME2 = 0x116000, 0x117000
    # Shape 3: empty list -> the wrapper attr is the fallback.
    S3, NAME3, WRAP3 = 0x118000, 0x119000, 0x11A000
    ATTR_W3 = WRAP3 + 0x18
    EMPTY = 0x11B000

    wstr(NAME1, b"M_BK17v1_barrelmShape")
    wstr(NAME2, b"pCubeShape5")
    wstr(NAME3, b"barrelbody")

    w32(S1, nl.VT_SHAPE); w32(S1 + 0x08, NAME1)
    w32(S1 + 0x1C, WRAP1); w32(S1 + 0x20, LIST1)
    w32(WRAP1, nl.VT_WRAPPER); w32(ATTR_W1, nl.VT_GEOM)

    w32(S2, nl.VT_SHAPE); w32(S2 + 0x08, NAME2); w32(S2 + 0x20, LIST2)

    w32(S3, nl.VT_SHAPE); w32(S3 + 0x08, NAME3)
    w32(S3 + 0x1C, WRAP3); w32(S3 + 0x20, EMPTY)
    w32(WRAP3, nl.VT_WRAPPER); w32(ATTR_W3, nl.VT_GEOM)

    # list1: one geometry attr + one non-attr; list2: another shape's geometry attr.
    w32(LIST1, nl.VT_ATTRLIST); w32(LIST1 + 0x08, 2); w32(LIST1 + 0x10, ARR1)
    w32(ARR1, ATTR_A); w32(ARR1 + 4, 0x22222222)
    w32(ATTR_A, nl.VT_GEOM)
    w32(LIST2, nl.VT_ATTRLIST); w32(LIST2 + 0x08, 1); w32(LIST2 + 0x10, ARR2)
    w32(ARR2, ATTR_B); w32(ATTR_B, nl.VT_GEOM)
    w32(EMPTY, nl.VT_ATTRLIST); w32(EMPTY + 0x08, 0); w32(EMPTY + 0x10, 0)

    ram = nl.EeRam(bytes(blob), LO)
    assert nl.find_all(ram, nl.VT_SHAPE) == [S1, S2, S3], "find_all"

    a1, n1 = nl.attrs_of_shape(ram, S1)
    assert n1 == "M_BK17v1_barrelmShape", n1
    assert a1 == [ATTR_A], [hex(a) for a in a1]      # wrapper attr ignored, list2's attr not stolen
    a2, n2 = nl.attrs_of_shape(ram, S2)
    assert n2 == "pCubeShape5" and a2 == [ATTR_B], (n2, [hex(a) for a in a2])
    a3, n3 = nl.attrs_of_shape(ram, S3)
    assert n3 == "barrelbody" and a3 == [ATTR_W3], (n3, [hex(a) for a in a3])

    print("PASS: one-list ownership, no stride over-claim, wrapper fallback")
    return 0


if __name__ == "__main__":
    sys.exit(main())
