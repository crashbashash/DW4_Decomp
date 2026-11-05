"""Real C++ emitted members: independent linking, ownership and corruptions."""
import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import linkgen
import m2c_loop
import unitflags
import unitobjects
import units
import verify


class EmittedObjects(unittest.TestCase):
    OWNER, MEMBER = 0x180000, 0x180100
    EXTERNALS = {"Drop": 0x180300, "Tick": 0x180310, "fixture_delete": 0x180320}
    SOURCE = '''
extern "C" void Drop(int *);
extern "C" void Tick();
class Result {
public:
    int *value;
    Result(int *p):value(p) {}
    Result(const Result &other):value(other.value) { if(value) ++*value; }
    ~Result() { if(value) Drop(value); }
};
extern "C" Result fixture_owner(int *p) { Result result(p); Tick(); return result; }
'''

    def setUp(self):
        if not all(Path(p).exists() for p in (verify.WIBO_DEFAULT, verify.MWCC_DEFAULT)):
            self.skipTest("private compiler unavailable")
        if not shutil.which("mipsel-linux-gnu-ld"):
            self.skipTest("GNU MIPS tools unavailable")
        self.temp = tempfile.TemporaryDirectory(prefix="dw4-emitted-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.source = self.root / "fixture.cpp"
        self.source.write_text(self.SOURCE)
        self.obj = self.root / "fixture.o"
        self.flags = "-O3,p -Cpp_exceptions off -I" + str(Path(verify.ROOT) / "include")
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", *self.flags.split(),
                        str(self.source), "-o", str(self.obj)], check=True, capture_output=True,
                       env=dict(os.environ, MWCIncludes=str(self.root)))
        syms, _ = verify.object_syms(str(self.obj))
        self.member_name = next(name for name in syms if name.startswith("__dt__"))
        self.bodies = {"fixture_owner": (self.OWNER, syms["fixture_owner"]),
                       self.member_name: (self.MEMBER, syms[self.member_name])}
        self.symbols = self.root / "symbols.txt"
        rows = [(address, size, "fixture_owner" if address == self.OWNER else "fixture_member")
                for address, (_, _, size) in self.bodies.values()]
        rows += [(address, 8, name) for name, address in self.EXTERNALS.items()]
        self.symbols.write_text("".join(f"{va:08x} {size:06x} {name}\n"
                                         for va, size, name in sorted(rows)))
        self.registry = self.root / "objects.json"
        self.good_registry = {hex(self.OWNER): {
            "emitted": {self.member_name: hex(self.MEMBER)},
            "externals": {"__dl__FPv": hex(self.EXTERNALS["fixture_delete"])}}}
        self.write_registry(self.good_registry)
        self.flag_file = self.root / "flags.tsv"
        self.flag_file.write_text(f"{hex(self.OWNER)}\t{self.flags}\n")

        # Relocate the complete original compiler object with GNU ld, without
        # using the emitted-object verifier or extraction code as the oracle.
        names = {section: f".body{section}" for _, (section, _, _) in self.bodies.values()}
        verify.rename_object_sections(str(self.obj), names)
        script = self.root / "independent.ld"
        definitions = dict(self.EXTERNALS, __dl__FPv=self.EXTERNALS["fixture_delete"])
        statements = [f"{name} = 0x{address:x};" for name, address in definitions.items()]
        statements += ["SECTIONS {"]
        for _, (address, (section, _, _)) in self.bodies.items():
            statements.append(f".out{section} 0x{address:x} : {{ *({names[section]}) }}")
        statements.append("/DISCARD/ : { *(.mwcats) *(.comment) *(.reginfo) } }")
        script.write_text("\n".join(statements))
        independent = self.root / "independent.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-T", str(script),
                        str(self.obj), "-o", str(independent)], check=True, capture_output=True)
        image = bytearray([0xa5]) * (0x180330 - verify.VADDR_BASE + verify.FILE_BASE)
        for _, (address, (section, _, size)) in self.bodies.items():
            code = verify.object_section(str(independent), f".out{section}")
            self.assertEqual(len(code), size)
            start = address - verify.VADDR_BASE + verify.FILE_BASE
            image[start:start + size] = code
        for address in self.EXTERNALS.values():
            start = address - verify.VADDR_BASE + verify.FILE_BASE
            image[start:start + 8] = struct.pack("<2I", 0x03e00008, 0)
        self.expected = bytes(image[verify.FILE_BASE:])
        image[:6] = b"\x7fELF\x01\x01"
        reginfo = len(image)
        image.extend(struct.pack("<6I", 0, 0, 0, 0, 0, 0x210000))
        strings = b"\0.shstrtab\0.reginfo\0"
        strings_at = len(image)
        image.extend(strings)
        image.extend(b"\0" * (-len(image) % 4))
        shoff = len(image)
        image.extend(bytes(40))
        image.extend(struct.pack("<10I", 1, 3, 0, 0, strings_at, len(strings), 0, 0, 1, 0))
        image.extend(struct.pack("<10I", 11, 0x70000006, 0, 0, reginfo, 24, 0, 0, 4, 0))
        struct.pack_into("<I", image, 0x20, shoff)
        struct.pack_into("<HHH", image, 0x2e, 40, 3, 1)
        self.image = self.root / "fixture.elf"
        self.image.write_bytes(image)

    def write_registry(self, value):
        self.registry.write_text(json.dumps(value))
        unitobjects.load.cache_clear()

    def check(self, address=None, image=None, source=None):
        return verify.verify_one(address or self.OWNER, str(source or self.source),
            elf=str(image or self.image), symbols=str(self.symbols),
            unit_flags=str(self.flag_file), unit_objects=str(self.registry), jumptables={})

    def test_every_body_matches_independent_linker_and_source_ownership(self):
        for address in (self.OWNER, self.MEMBER):
            ok, report = self.check(address)
            self.assertTrue(ok, report)
            self.assertIn("2 complete bodies", report)
        index = units.scan(str(self.root), symbols=str(self.symbols), unit_objects=str(self.registry))
        self.assertEqual(index["fixture_owner"], index["fixture_member"])
        path, temporary = units.standalone(str(self.source), "fixture_member",
            symbols=str(self.symbols), unit_objects=str(self.registry))
        self.assertEqual(path, str(self.source))
        self.assertIsNone(temporary)
        for address, (_, _, size) in self.bodies.values():
            ok, report = verify.verify_one(address, str(self.source), elf=str(self.image),
                symbols=str(self.symbols), unit_flags=str(self.flag_file),
                unit_objects=str(self.registry), jumptables={}, verbose=True)
            self.assertTrue(ok, report)
            actual, retail = m2c_loop.parse_verbose(report)
            self.assertEqual(len(actual), size // 4)
            self.assertEqual(actual, retail)

    def test_corrupt_member_rejects_owner_too(self):
        image = bytearray(self.image.read_bytes())
        image[self.MEMBER - verify.VADDR_BASE + verify.FILE_BASE] ^= 1
        corrupted = self.root / "corrupt.elf"
        corrupted.write_bytes(image)
        for address in (self.OWNER, self.MEMBER):
            ok, report = self.check(address, image=corrupted)
            self.assertFalse(ok, report)
            self.assertIn("DIFFER emitted 0x180100", report)

    def test_missing_unknown_and_unowned_bodies_are_rejected(self):
        self.write_registry({})
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("per-function linking requires an isolated body", report)
        wrong = {hex(self.OWNER): {"emitted": {"MissingMember": hex(self.MEMBER)}}}
        self.write_registry(wrong)
        self.assertFalse(self.check()[0])
        self.write_registry(self.good_registry)
        extra = self.root / "extra.cpp"
        extra.write_text(self.SOURCE + '\nextern "C" int unowned(){return 7;}\n')
        ok, report = self.check(source=extra)
        self.assertFalse(ok)
        self.assertIn("unowned code or runtime data", report)

    def test_conflicting_ownership_and_external_alias_are_rejected(self):
        self.write_registry({hex(self.OWNER): {"emitted": {self.member_name: hex(self.OWNER)}}})
        with self.assertRaisesRegex(ValueError, "multiple compiler bodies"):
            unitobjects.load(str(self.registry))
        self.write_registry({hex(self.OWNER): {"emitted": {self.member_name: hex(self.MEMBER)},
            "externals": {"Drop": hex(self.EXTERNALS["Tick"])}}})
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("conflicts with the symbol map", report)

    def stripped_registry(self):
        return {hex(self.OWNER): {"stripped": [self.member_name],
                                  "externals": {"__dl__FPv": hex(self.EXTERNALS["fixture_delete"])}}}

    def without_retail_member(self):
        image = bytearray(self.image.read_bytes())
        start = self.MEMBER - verify.VADDR_BASE + verify.FILE_BASE
        image[start:start + 0x100] = bytes([0xa5]) * 0x100
        stripped = self.root / "stripped.elf"
        stripped.write_bytes(image)
        return stripped

    def test_stripped_destructor_is_accepted_only_when_retail_has_no_copy(self):
        self.write_registry(self.stripped_registry())
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("has a retail copy at 0x180100; name it as a duplicate", report)
        ok, report = self.check(image=self.without_retail_member())
        self.assertTrue(ok, report)
        self.assertIn("1 complete bodies", report)

    def test_stripped_body_must_be_an_unreferenced_destructor(self):
        self.write_registry({hex(self.OWNER): {"stripped": ["fixture_owner"]}})
        with self.assertRaisesRegex(ValueError, "compiler destructor name"):
            unitobjects.load(str(self.registry))
        self.write_registry(self.stripped_registry())
        caller = self.root / "caller.cpp"
        caller.write_text(self.SOURCE.replace(
            'extern "C" Result fixture_owner(int *p) { Result result(p); Tick(); return result; }',
            '#pragma dont_inline on\nextern "C" void fixture_owner(int *p) { Result result(p); Tick(); }'))
        obj = self.root / "caller.o"
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", *self.flags.split(),
                        str(caller), "-o", str(obj)], check=True, capture_output=True,
                       env=dict(os.environ, MWCIncludes=str(self.root)))
        size = verify.object_syms(str(obj))[0]["fixture_owner"][2]
        self.symbols.write_text(self.symbols.read_text().replace(
            f"{self.OWNER:08x} {self.bodies['fixture_owner'][1][2]:06x}", f"{self.OWNER:08x} {size:06x}"))
        ok, report = self.check(source=caller, image=self.without_retail_member())
        self.assertFalse(ok)
        self.assertIn("a referenced body cannot have been dead-stripped", report)

    def test_unknown_auxiliary_relocation_and_exception_data_are_rejected(self):
        self.write_registry({hex(self.OWNER): {"emitted": {self.member_name: hex(self.MEMBER)}}})
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("__dl__FPv", report)
        self.write_registry(self.good_registry)
        self.flag_file.write_text(f"{hex(self.OWNER)}\t-O3,p -Iinclude\n")
        unitflags._CACHE.clear()
        ok, report = self.check()
        self.assertFalse(ok)
        # exceptions on: the object's records are compared with retail (none here), not a rejection
        self.assertIn("exc=extra cat=code-only", report)
        self.assertIn("MATCH emitted 0x180000 fixture_owner", report)
        self.assertNotIn("rejected", report)

    def test_linkgen_places_both_and_preserves_all_gap_bytes(self):
        entries = [(address, size, "code", "fixture_owner" if address == self.OWNER
                    else "fixture_member") for address, (_, _, size) in self.bodies.values()]
        entries += [(address, 8, "code", name) for name, address in self.EXTERNALS.items()]
        rows, cursor = [], verify.VADDR_BASE
        for va, size, kind, name in sorted(entries):
            if cursor < va:
                rows.append(f"{cursor:08x} {va-cursor:06x} data gap_{cursor:08x}\n")
            rows.append(f"{va:08x} {size:06x} {kind} {name}\n")
            cursor = va + size
        if cursor < 0x180330:
            rows.append(f"{cursor:08x} {0x180330-cursor:06x} data tail\n")
        layout = self.root / "layout.txt"
        layout.write_text("".join(rows))
        script, linked = self.root / "generated.ld", self.root / "generated.elf"
        real_scan = units.scan
        index = real_scan(str(self.root), symbols=str(self.symbols), unit_objects=str(self.registry))
        with patch.object(linkgen.unitfiles, "scan", return_value=index), \
             patch.object(unitflags, "flags_for", return_value=self.flags), \
             contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(linkgen.main(["--all", "--layout", str(layout),
                "--elf", str(self.image), "--symbols", str(self.symbols),
                "--unit-objects", str(self.registry), "--unit-flags", str(self.flag_file),
                "--out", str(self.root / "objects"), "--ld", str(script), "--jobs", "2"]), 0)
        subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-G0", "-T", str(script),
                        "-o", str(linked)], check=True, capture_output=True)
        self.assertEqual(verify.object_section(str(linked), ".text"), self.expected)
        corrupted = self.root / "bad-link.elf"
        image = bytearray(self.image.read_bytes())
        image[self.MEMBER - verify.VADDR_BASE + verify.FILE_BASE] ^= 1
        corrupted.write_bytes(image)
        rejected = self.root / "rejected.ld"
        with patch.object(linkgen.unitfiles, "scan", return_value=index), \
             patch.object(unitflags, "flags_for", return_value=self.flags), \
             contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            self.assertEqual(linkgen.main(["--all", "--layout", str(layout),
                "--elf", str(corrupted), "--symbols", str(self.symbols),
                "--unit-objects", str(self.registry), "--unit-flags", str(self.flag_file),
                "--out", str(self.root / "bad-objects"), "--ld", str(rejected), "--jobs", "2"]), 2)
        self.assertFalse(rejected.exists())


if __name__ == "__main__":
    unittest.main()
