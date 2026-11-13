"""scripts/inventory_scan.py on a synthetic image: segmentation, merging, classes and the check."""
import os
import struct
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "scripts"))
sys.path.insert(0, os.path.join(HERE, "..", "tools"))
import inventory_scan as inv          # noqa: E402
import split as S                     # noqa: E402

JR_RA, NOP = 0x03E00008, 0
ADDIU_SP_M16, ADDIU_SP_P16 = 0x27BDFFF0, 0x27BD0010
SD_RA, LD_RA = 0xFFBF0000, 0xDFBF0000
LI_V0_1 = 0x24020001
LW_V0_A0 = 0x8C820010


def jal(src, target):
    return 0x0C000000 | ((target >> 2) & 0x3FFFFFF)


def j(src, target):
    return 0x08000000 | ((target >> 2) & 0x3FFFFFF)


def beq_zero(src, target):
    rel = (target - (src + 4)) // 4
    return 0x10000000 | (rel & 0xFFFF)


class Image:
    """A tiny section at VADDR_BASE whose words the test lays out by address."""

    def __init__(self, n_words):
        self.words = [0] * n_words

    def put(self, va, *words):
        k = (va - S.VADDR_BASE) // 4
        self.words[k:k + len(words)] = words

    def bytes(self):
        return b"\0" * S.FILE_BASE + b"".join(struct.pack("<I", w) for w in self.words)


def scan(img, syms, hi, data_rows=()):
    units, cur = [], S.VADDR_BASE
    for va, sz, nm in syms:
        if va > cur:
            units.append((cur, va - cur, "data", "data_%08x" % cur))
        units.append((va, sz, "code", nm))
        cur = va + sz
    if cur < hi:
        units.append((cur, hi - cur, "data", "data_%08x" % cur))
    return inv.Scan(img.bytes(), syms, units, {}, (), section_hi=hi, data_rows=data_rows)


class Classes(unittest.TestCase):
    def setUp(self):
        self.img = Image(128)
        B = S.VADDR_BASE
        # a known function at +0x00: calls +0x40, tail-calls +0x60, returns
        self.img.put(B + 0x00, ADDIU_SP_M16, SD_RA, jal(B + 0x08, B + 0x40), NOP, LD_RA, j(B + 0x14, B + 0x60), ADDIU_SP_P16, NOP)
        # +0x40: a jal target, leaf                       -> B
        self.img.put(B + 0x40, LW_V0_A0, JR_RA, NOP)
        # +0x60: a j target, leaf                         -> D
        self.img.put(B + 0x60, JR_RA, LI_V0_1)
        # +0x80: a framed body nothing references         -> G
        self.img.put(B + 0x80, ADDIU_SP_M16, SD_RA, LD_RA, JR_RA, ADDIU_SP_P16)
        # +0xa0: an 8-byte `jr ra` stub nothing references -> H
        self.img.put(B + 0xa0, JR_RA, NOP)
        # +0xc0: a body whose address a data word at +0xf0 holds -> C
        self.img.put(B + 0xc0, LW_V0_A0, LI_V0_1, JR_RA, NOP)
        self.img.put(B + 0xf0, B + 0xc0, 0)
        # +0x100: a second known function; +0x120 its fallen-through tail -> A
        self.img.put(B + 0x100, ADDIU_SP_M16, SD_RA, LD_RA, LI_V0_1, LW_V0_A0, LI_V0_1, LI_V0_1, LI_V0_1)
        self.img.put(B + 0x120, JR_RA, ADDIU_SP_P16)
        self.syms = [(B + 0x00, 0x20, "caller"), (B + 0x100, 0x20, "short")]
        self.rows = scan(self.img, self.syms, B + 0x200).rows

    def by_class(self):
        return {cls: (va, size) for va, size, cls, _ev in self.rows}

    def test_every_class_is_recognised(self):
        B = S.VADDR_BASE
        got = self.by_class()
        self.assertEqual(got["B"], (B + 0x40, 12))
        self.assertEqual(got["D"], (B + 0x60, 8))
        self.assertEqual(got["G"], (B + 0x80, 20))
        self.assertEqual(got["H"], (B + 0xa0, 8))
        self.assertEqual(got["C"], (B + 0xc0, 16))
        self.assertEqual(got["A"], (B + 0x120, 8))
        self.assertEqual(len(self.rows), 6)

    def test_evidence_names_the_reference(self):
        ev = {cls: e for _va, _size, cls, e in self.rows}
        self.assertIn("jal:other(jal@100008)", ev["B"])
        self.assertIn("dataword(dataword@1000f0)", ev["C"])
        self.assertIn("falls-through-from:short", ev["A"])
        self.assertIn("prologue", ev["G"])

    def test_data_rows_are_neither_code_nor_references(self):
        B = S.VADDR_BASE
        rows = scan(self.img, self.syms, B + 0x200, [(B + 0x80, B + 0x98), (B + 0xf0, B + 0xf8)]).rows
        got = {va: cls for va, _size, cls, _ev in rows}
        self.assertNotIn(B + 0x80, got)              # the framed body inside the first row
        self.assertEqual(got[B + 0xc0], "G")         # its only reference lies in the second row

    def test_data_words_and_table_text_are_not_code(self):
        # a string and a float table decode to nothing the scan accepts
        img = Image(64)
        B = S.VADDR_BASE
        img.put(B + 0x20, 0x6c6c6548, 0x6f77206f, 0x00646c72, 0x3f800000, 0x40000000)
        rows = scan(img, [(B, 8, "f")], B + 0x100).rows
        self.assertEqual(rows, [])

    def test_summary_and_render_round_trip(self):
        text = inv.render(self.rows)
        self.assertTrue(text.startswith("# va\tbytes\tclass\tevidence — GENERATED"))
        path = os.path.join(HERE, "..", "build", "test-inventory-scan.tsv")
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w") as fh:
            fh.write(text)
        try:
            self.assertEqual(inv.load_table(path), self.rows)
            self.assertEqual(inv.unsymbolised_bytes(path), sum(r[1] for r in self.rows))
        finally:
            os.remove(path)

    def test_branch_connected_segments_merge(self):
        # a body with an early return: `beq zero,zero,+0x14; nop; jr ra; nop; <target> jr ra; nop`
        img = Image(32)
        B = S.VADDR_BASE
        img.put(B + 0x10, ADDIU_SP_M16, beq_zero(B + 0x14, B + 0x24), NOP, JR_RA, NOP, JR_RA, ADDIU_SP_P16)
        rows = scan(img, [(B, 8, "f")], B + 0x80).rows
        self.assertEqual([(r[0], r[1]) for r in rows], [(B + 0x10, 28)])


if __name__ == "__main__":
    unittest.main()
