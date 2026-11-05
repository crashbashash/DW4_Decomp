"""Verify and link duplicate-named MWCC table sections against GNU ld."""
from contextlib import contextmanager, redirect_stdout
import io
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import linkgen
import verify


@contextmanager
def directory(path):
    previous = Path.cwd()
    os.chdir(path)
    try:
        yield
    finally:
        os.chdir(previous)


@unittest.skipUnless(Path(verify.MWCC_DEFAULT).exists() and shutil.which("mipsel-linux-gnu-ld"),
                     "locally supplied MWCC and MIPS binutils required")
class MultipleTables(unittest.TestCase):
    VA = 0x180000
    TABLES = [(0x190010, 12), (0x190080, 12)]

    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix="dw4-two-tables-")
        cls.root = Path(cls.temporary.name)
        (cls.root / "src").mkdir()
        cls.source = cls.root / "src/fixture.c"
        targets = [f"target_{0x1a0000 + i * 16:08x}" for i in range(23)]
        lines = [f"int {target}(void);" for target in targets]
        lines += ["int fixture_dispatch(unsigned int outer, unsigned int inner) {",
                  "switch (outer) { case 0: switch (inner) {"]
        lines += [f"case {i}: return {targets[i]}();" for i in range(12)]
        lines += ["default: return -1; }"]
        lines += [f"case {i}: return {targets[11+i]}();" for i in range(1, 12)]
        lines += ["default: return -2; }}"]
        cls.source.write_text("\n".join(lines) + "\n")
        cls.object = cls.root / "fixture.o"
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", "-O3",
                        str(cls.source), "-o", str(cls.object)], check=True, capture_output=True,
                       env=dict(os.environ, MWCIncludes=str(cls.root / "src")))
        headers = verify.elf_section_headers(str(cls.object))
        cls.rodata = [(i, h) for i, (name, h) in enumerate(headers) if name == ".rodata" and h[5]]
        if len(cls.rodata) != 2 or [h[5] for _, h in cls.rodata] != [48, 48]:
            raise AssertionError("fixture must exercise two duplicate-named table sections")
        _, cls.size, cls.text_index = verify.object_sym(str(cls.object), "fixture_dispatch")
        cls.symbols = cls.root / "symbols.txt"
        cls.symbols.write_text(f"{cls.VA:08x} {cls.size:06x} fixture_dispatch\n")
        cls.flags = cls.root / "unit-flags.tsv"
        cls.flags.write_text("")

        # Independently link the real compiler object. Table section names are
        # changed by index; assertions below prove no payload/index ownership moves.
        renamed = cls.root / "renamed.o"
        shutil.copyfile(cls.object, renamed)
        verify.rename_object_sections(str(renamed),
                                      {index: f".fixture{i}" for i, (index, _) in enumerate(cls.rodata)})
        script = cls.root / "independent.ld"
        script.write_text("\n".join(
            [f"{target} = 0x{0x1a0000 + i*16:x};" for i, target in enumerate(targets)]
            + ["SECTIONS {", f".text 0x{cls.VA:x} : SUBALIGN(1) {{ *(.text) }}"]
            + [f".fixture{i} 0x{address:x} : SUBALIGN(1) {{ *(.fixture{i}) }}"
               for i, (address, _) in enumerate(cls.TABLES)]
            + ["/DISCARD/ : { *(.reginfo) *(.mwcats) *(.comment) } }"]) + "\n")
        linked = cls.root / "independent.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-T", str(script),
                        str(renamed), "-o", str(linked)], check=True, capture_output=True)
        cls.end = cls.TABLES[-1][0] + 48 + 16
        cls.expected = bytearray(b"\xa5" * (cls.end - verify.VADDR_BASE))
        body = verify.object_section(str(linked), ".text")
        cls.expected[cls.VA - verify.VADDR_BASE:cls.VA - verify.VADDR_BASE + cls.size] = body
        for i, (address, _) in enumerate(cls.TABLES):
            table = verify.object_section(str(linked), f".fixture{i}")
            cls.expected[address - verify.VADDR_BASE:address - verify.VADDR_BASE + 48] = table
        # The verifier's flat retail reader uses +0x80, whereas the independent
        # GNU ELF has its own section offsets. Add controlled reginfo metadata
        # beyond the flat region; linkgen requires it even without GP accesses.
        image = bytearray(0x80) + cls.expected
        image[:6] = b"\x7fELF\x01\x01"
        reginfo_offset = len(image)
        image.extend(struct.pack("<6I", 0, 0, 0, 0, 0, 0x210000))
        strings = b"\0.shstrtab\0.reginfo\0"
        strings_offset = len(image)
        image.extend(strings)
        image.extend(b"\0" * (-len(image) % 4))
        shoff = len(image)
        image.extend(bytes(40))
        image.extend(struct.pack("<10I", 1, 3, 0, 0, strings_offset, len(strings), 0, 0, 1, 0))
        image.extend(struct.pack("<10I", 11, 0x70000006, 0, 0, reginfo_offset, 24, 0, 0, 4, 0))
        struct.pack_into("<I", image, 0x20, shoff)
        struct.pack_into("<HHH", image, 0x2e, 40, 3, 1)
        cls.image = cls.root / "fixture.elf"
        cls.image.write_bytes(image)

    @classmethod
    def tearDownClass(cls):
        cls.temporary.cleanup()

    def verify(self, *, image=None, tables=None):
        return verify.verify_one(self.VA, str(self.source), elf=str(image or self.image),
                                 symbols=str(self.symbols), unit_flags=str(self.flags),
                                 jumptables={self.VA: self.TABLES if tables is None else tables})

    def test_both_tables_and_text_match_independent_linker(self):
        ok, report = self.verify()
        self.assertTrue(ok, report)
        for address, _ in self.TABLES:
            self.assertIn(f"jump table 0x{address:06x}", report)
        self.assertEqual(report.count("matches retail"), 2)

    def test_corrupt_second_table_is_rejected(self):
        image = bytearray(self.image.read_bytes())
        image[self.TABLES[1][0] - verify.VADDR_BASE + verify.FILE_BASE] ^= 1
        corrupted = self.root / "corrupted.elf"
        corrupted.write_bytes(image)
        ok, report = self.verify(image=corrupted)
        self.assertFalse(ok)
        self.assertIn("jump table 0x190080 differs", report)
        self.assertIn("jump table 0x190010: 12 entries, 48 bytes, matches retail", report)

    def test_missing_or_wrong_sized_table_is_rejected(self):
        for tables in (self.TABLES[:1], [self.TABLES[0], (self.TABLES[1][0], 13)], []):
            ok, report = self.verify(tables=tables)
            self.assertFalse(ok, report)

    def test_unresolved_relocation_belongs_to_only_its_table(self):
        original = verify.object_relocs
        bad_index = self.rodata[1][0]

        def relocs(obj, target_section=None):
            rows = original(obj, target_section)
            if target_section == bad_index:
                rows.append((".rodata", 0, verify.R_32, "MissingTableTarget", 0))
            return rows

        with patch.object(verify, "object_relocs", side_effect=relocs):
            ok, report = self.verify()
        self.assertFalse(ok)
        self.assertIn("MissingTableTarget", report)
        self.assertIn("jump table 0x190010: 12 entries, 48 bytes, matches retail", report)

    def test_renaming_preserves_payloads_symbols_and_relocation_owners(self):
        renamed = self.root / "metadata-check.o"
        shutil.copyfile(self.object, renamed)
        before = verify.elf_section_headers(str(renamed))
        symbols, _ = verify.object_syms(str(renamed))
        payloads = {i: verify.object_section(str(renamed), name, i)
                    for i, (name, h) in enumerate(before) if h[1] != 8 and h[5] and name != ".shstrtab"}
        verify.rename_object_sections(str(renamed),
                                      {index: f".table{i}" for i, (index, _) in enumerate(self.rodata)})
        after = verify.elf_section_headers(str(renamed))
        self.assertEqual(symbols, verify.object_syms(str(renamed))[0])
        for index, payload in payloads.items():
            self.assertEqual(payload, verify.object_section(str(renamed), after[index][0], index))
            self.assertEqual(before[index][1][1:], after[index][1][1:])
        for index, (name, header) in enumerate(before):
            if header[1] in (4, 9):
                self.assertEqual(header[7], after[index][1][7])  # sh_info target section

    def test_linkgen_preserves_table_gap_and_entire_layout(self):
        layout, cursor = [], verify.VADDR_BASE
        bodies = [(self.VA, self.size, "code", "fixture_dispatch", "")]
        bodies += [(address, count * 4, "jtbl", f"table_{i}", "fixture_dispatch")
                   for i, (address, count) in enumerate(self.TABLES)]
        for address, size, kind, name, owner in bodies:
            if address > cursor:
                layout.append(f"{cursor:08x} {address-cursor:06x} data gap_{cursor:08x}")
            layout.append(f"{address:08x} {size:06x} {kind} {name} {owner}".rstrip())
            cursor = address + size
        layout.append(f"{cursor:08x} {self.end-cursor:06x} data tail")
        path = self.root / "layout.txt"
        path.write_text("\n".join(layout) + "\n")
        script = self.root / "generated.ld"
        with directory(self.root), redirect_stdout(io.StringIO()):
            result = linkgen.main(["--layout", str(path), "--elf", str(self.image),
                                   "--out", str(self.root / "objects"), "--ld", str(script), "--jobs", "2"])
        self.assertEqual(result, 0)
        linked = self.root / "generated.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-G0", "-T", str(script),
                        "-o", str(linked)], check=True, capture_output=True)
        self.assertEqual(verify.object_section(str(linked), ".text"), self.expected)
        for address, _ in self.TABLES:
            self.assertIn(f".rodata.dw4_{address:08x}", script.read_text())


if __name__ == "__main__":
    unittest.main()
