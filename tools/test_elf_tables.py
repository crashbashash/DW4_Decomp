"""verify.py reads an object's symbols and relocations in Python, and gives exactly what its readelf parse gave.

The objects here are built byte by byte, so each case holds one quirk of readelf's printed form. Where
binutils is installed, every answer is also compared with the readelf parse it replaces.
"""
import os
import shutil
import struct
import sys
import tempfile
import threading
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import verify  # noqa: E402

READELF = shutil.which("mipsel-linux-gnu-readelf")


def build_object(sections, symbols, relocations, rela=False):
    """An ELF32 little-endian relocatable object.

    `sections`: [(name, type, flags, bytes)] after the null header; `symbols`: [(name, value, size, info,
    other, shndx)] with name "" for st_name 0; `relocations`: {target index: [(offset, type, symbol,
    addend)]}, one REL (or RELA) section each, in that order.
    """
    rows = [("", 0, 0, b"", 0, 0, 0, 0)]
    rows += [(name, kind, flags, data, 0, 0, 4, 0) for name, kind, flags, data in sections]
    symtab = len(rows) + len(relocations)
    for target, entries in sorted(relocations.items()):
        body = b"".join(struct.pack("<IIi", at, symbol << 8 | kind, addend) if rela
                        else struct.pack("<II", at, symbol << 8 | kind)
                        for at, kind, symbol, addend in entries)
        rows.append(((".rela" if rela else ".rel") + rows[target][0], 4 if rela else 9, 0, body,
                     symtab, target, 4, 12 if rela else 8))
    strings, offsets = b"\0", []
    for name, *_ in symbols:
        offsets.append(len(strings) if name else 0)
        strings += name.encode() + b"\0" if name else b""
    table = b"".join(struct.pack("<IIIBBH", at, value, size, info, other, shndx)
                     for at, (_name, value, size, info, other, shndx) in zip(offsets, symbols))
    rows.append((".symtab", 2, 0, table, symtab + 1, sum(1 for s in symbols if not s[3] >> 4), 4, 16))
    rows.append((".strtab", 3, 0, strings, 0, 0, 1, 0))
    rows.append((".shstrtab", 3, 0, b"", 0, 0, 1, 0))
    names, name_at = b"\0", []
    for row in rows:
        name_at.append(len(names) if row[0] else 0)
        names += row[0].encode() + b"\0" if row[0] else b""
    rows[-1] = rows[-1][:3] + (names,) + rows[-1][4:]
    out, placed = bytearray(52), []
    for row in rows:
        out += b"\0" * (-len(out) % 4)
        placed.append(len(out))
        out += row[3]
    out += b"\0" * (-len(out) % 4)
    shoff = len(out)
    for i, (_name, kind, flags, data, link, info, align, entsize) in enumerate(rows):
        out += struct.pack("<10I", name_at[i], kind, flags, 0, placed[i] if i else 0, len(data), link, info,
                           align, entsize)
    struct.pack_into("<16sHHIIIIIHHHHHH", out, 0, b"\x7fELF\x01\x01\x01" + b"\0" * 9, 1, 8, 1, 0, 0, shoff,
                     0, 52, 0, 0, 40, len(rows), len(rows) - 1)
    return bytes(out)


TEXT = (".text", 1, 6, b"\0" * 64)
RODATA = (".rodata", 1, 2, b"\0" * 16)
NULL_SYMBOL = ("", 0, 0, 0, 0, 0)


class Tables(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.count = 0

    def tearDown(self):
        self.tmp.cleanup()

    def write(self, data):
        self.count += 1
        path = os.path.join(self.tmp.name, "o%d.o" % self.count)
        with open(path, "wb") as fh:
            fh.write(data)
        return path

    def same_as_readelf(self, path):
        """The Python answers equal the readelf parse's, refusals included."""
        if not READELF:
            return

        def outcome(call):
            try:
                return "ok", call()
            except ValueError as error:
                return "raise", str(error)
        self.assertEqual(outcome(lambda: verify.object_syms(path)),
                         outcome(lambda: verify._object_syms_readelf(path)))
        headers = verify.elf_section_headers(path)
        for target in [None] + list(range(len(headers))):
            targets = ({h[4]: h[7] for _, h in headers if h[1] in (4, 9)} if target is not None else None)
            self.assertEqual(outcome(lambda: verify.object_relocs(path, target)),
                             outcome(lambda: verify._object_relocs_readelf(path, target, targets)), target)

    def readelf_never_runs(self):
        return mock.patch.object(verify.subprocess, "run", side_effect=AssertionError("readelf ran"))

    def test_symbols_keep_the_text_parse(self):
        path = self.write(build_object([TEXT, RODATA], [
            NULL_SYMBOL,
            ("", 0, 0, 3, 0, 1),                    # a section symbol prints its section's name
            ("f", 0x10, 40, 0x12, 0, 1),
            ("g", 0, 8, 0xd2, 0, 1),                # MWCC's processor-specific binding: three tokens
            ("", 0, 4, 0xd2, 0, 2),                 # ... and without a name the index is read as the name
            ("ext", 0, 0, 0x10, 0, 0),
            ("abs", 5, 0, 0x10, 0, 0xfff1),
            ("dup", 4, 0, 0x10, 0, 1),
            ("dup", 8, 0, 0x10, 0, 2),              # a repeated name keeps the last entry
            ("hidden", 0, 0, 0x10, 2, 1),
        ], {}))
        with self.readelf_never_runs():
            syms, secs = verify.object_syms(path)
        self.assertEqual(secs[0], "NULL")
        self.assertEqual(secs[1], ".text")
        self.assertEqual(syms[".text"], (1, 0, 0))
        self.assertEqual(syms["f"], (1, 0x10, 40))
        self.assertEqual(syms["g"], (1, 0, 8))
        self.assertEqual(syms["2"], ("DEFAULT", 0, 4))
        self.assertEqual(syms["ext"], ("UND", 0, 0))
        self.assertEqual(syms["abs"], ("ABS", 5, 0))
        self.assertEqual(syms["dup"], (2, 8, 0))
        self.assertNotIn("", syms)
        self.same_as_readelf(path)

    def test_a_size_readelf_prints_in_hex_is_refused(self):
        path = self.write(build_object([TEXT], [NULL_SYMBOL, ("big", 0, 100000, 0x12, 0, 1)], {}))
        with self.readelf_never_runs(), self.assertRaises(ValueError):
            verify.object_syms(path)
        self.same_as_readelf(path)

    def test_relocations_in_table_order_by_owner(self):
        path = self.write(build_object([TEXT, TEXT, RODATA], [
            NULL_SYMBOL, ("", 0, 0, 3, 0, 1), ("f", 0, 64, 0x12, 0, 1), ("ext", 0, 0, 0x10, 0, 0),
            ("", 0, 0, 1, 0, 1),
        ], {1: [(8, verify.R_HI16, 3, 0), (4, verify.R_LO16, 3, 0), (12, verify.R_26, 2, 0),
                (16, 0, 0, 0)],                      # a folded literal: cleared to R_MIPS_NONE, no symbol
            2: [(0, verify.R_LITERAL, 3, 0), (4, verify.R_GPREL16, 4, 0)],
            3: [(0, verify.R_32, 1, 0)]}))
        with self.readelf_never_runs():
            rows = verify.object_relocs(path)
            second = verify.object_relocs(path, target_section=2)
            table = verify.object_relocs(path, target_section=3)
        self.assertEqual(rows[:3], [(".text", 8, verify.R_HI16, "ext", 0), (".text", 4, verify.R_LO16, "ext", 0),
                                    (".text", 12, verify.R_26, "f", 0)])
        self.assertEqual(second, [(".text", 0, verify.R_GPREL16, "ext", 0), (".text", 4, verify.R_GPREL16, "<null>", 0)])
        self.assertEqual(table, [(".rodata", 0, verify.R_32, ".text", 0)])
        self.assertEqual(len(rows), 6)
        self.same_as_readelf(path)

    def test_rela_addends_are_signed_hex(self):
        addends = [0x10, -8, 0x1c, 0, -0x80000000, 0x7fffffff]
        path = self.write(build_object([TEXT], [NULL_SYMBOL, ("x", 0, 0, 0x10, 0, 0)], {1: [
            (4 * i, kind, 1, addend) for i, (kind, addend) in enumerate(zip(
                [verify.R_HI16, verify.R_LO16, verify.R_26, verify.R_32, verify.R_32, verify.R_32], addends))]},
            rela=True))
        with self.readelf_never_runs():
            rows = verify.object_relocs(path)
        self.assertEqual([r[4] for r in rows], addends)
        self.assertEqual({r[0] for r in rows}, {".text"})
        if READELF:
            self.assertEqual([r[4] for r in verify._object_relocs_readelf(path, None, None)], addends)
        self.same_as_readelf(path)

    def test_an_unknown_type_is_refused_in_readelfs_words(self):
        path = self.write(build_object([TEXT], [NULL_SYMBOL, ("x", 0, 0, 0x10, 0, 0)],
                                       {1: [(0, verify.R_26, 1, 0), (4, 9, 1, 0)]}))
        text = ("Relocation section '.rel.text' at offset 0x%x contains 2 entries:\n"
                "00000004  00000109 R_MIPS_GOT16            00000000   x\n"
                % verify.elf_section_headers(path)[2][1][4])
        with mock.patch.object(verify.subprocess, "run") as run:
            run.return_value.stdout = text
            with self.assertRaisesRegex(ValueError, "unsupported relocation type R_MIPS_GOT16 against 'x'"):
                verify.object_relocs(path)
        self.same_as_readelf(path)

    def test_what_readelf_would_escape_or_split_is_left_to_readelf(self):
        path = self.write(build_object([TEXT], [NULL_SYMBOL, ("two words", 0, 0, 0x10, 0, 1),
                                                ("other", 0, 0, 0x10, 0x10, 1)], {}))
        self.assertIsNone(verify._from_tables(path, lambda t: t.object_syms()))
        with mock.patch.object(verify.subprocess, "run") as run:
            run.return_value.stdout = ""
            self.assertEqual(verify.object_syms(path), ({}, {}))
        self.assertEqual(run.call_count, 2)
        self.same_as_readelf(path)

    def test_an_object_rewritten_in_place_is_read_again(self):
        path = self.write(build_object([TEXT], [NULL_SYMBOL, ("x", 0, 0, 0x10, 0, 0)],
                                       {1: [(0, verify.R_LITERAL, 1, 0)]}))
        self.assertEqual(len(verify.object_relocs(path)), 1)
        with open(path, "r+b") as fh:
            data = bytearray(fh.read())
            at = verify.elf_section_headers(path)[2][1][4]
            struct.pack_into("<I", data, at + 4, 0)
            fh.seek(0)
            fh.write(data)
        stat = os.stat(path)
        os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
        verify._forget(path)
        self.assertEqual(verify.object_relocs(path), [])


class UnitResults(unittest.TestCase):
    def setUp(self):
        verify._UNIT_RESULTS.clear()

    def test_a_shared_report_is_computed_once(self):
        calls = []

        def compute():
            calls.append(1)
            return True, "MATCH emitted object", True
        self.assertEqual(verify._unit_result(("k",), compute), (True, "MATCH emitted object"))
        self.assertEqual(verify._unit_result(("k",), compute), (True, "MATCH emitted object"))
        self.assertEqual(len(calls), 1)

    def test_a_report_naming_the_member_is_computed_for_each(self):
        calls = []

        def compute():
            calls.append(1)
            return False, "DIFFER %d" % len(calls), False
        self.assertEqual(verify._unit_result(("k",), compute)[1], "DIFFER 1")
        self.assertEqual(verify._unit_result(("k",), compute)[1], "DIFFER 2")
        self.assertEqual(verify._unit_result(None, compute)[1], "DIFFER 3")

    def test_members_taken_up_together_wait_for_the_first(self):
        calls, gate = [], threading.Event()

        def compute():
            calls.append(1)
            gate.wait(5)
            return True, "MATCH", True
        results = []
        threads = [threading.Thread(target=lambda: results.append(verify._unit_result(("k",), compute)))
                   for _ in range(4)]
        for thread in threads:
            thread.start()
        gate.set()
        for thread in threads:
            thread.join()
        self.assertEqual(results, [(True, "MATCH")] * 4)
        self.assertEqual(len(calls), 1)


class SharedRenameTargets(unittest.TestCase):
    """objcopy cannot redefine two symbols to one name: aliases of one address keep their own."""

    def test_aliases_of_one_address_keep_their_names(self):
        renames = {"X0_0014d010": "DAT_0014d010", "X1_0014d010": "DAT_0014d010",
                   "@12=DAT": "DAT_004df070", "FUN_0015f430__FPviii": "FUN_0015f430", "same": "same"}
        self.assertEqual(verify.unshared_renames(renames),
                         {"@12=DAT": "DAT_004df070", "FUN_0015f430__FPviii": "FUN_0015f430", "same": "same"})

    def test_single_rename_is_kept(self):
        self.assertEqual(verify.unshared_renames({"a": "b"}), {"a": "b"})


if __name__ == "__main__":
    unittest.main()

