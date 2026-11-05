"""Explicit paths must not inherit the source, profile and span defaults."""
import contextlib
import hashlib
import io
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import check
import buildcache
import layout
import linkcheck
import linkgen
import unitcompilers
import unitflags
import verify


class SectionOptions(unittest.TestCase):
    def test_layout_default_and_selected_bounds(self):
        default = layout.build([])
        self.assertEqual(default[0][:3], (layout.SECTION_LO,
                         layout.SECTION_HI - layout.SECTION_LO, "data"))
        units = layout.build([(0x100018, 8, "leaf")], section_lo=0x100010,
                             section_hi=0x100028)
        self.assertEqual([(u[0], u[1]) for u in units],
                         [(0x100010, 8), (0x100018, 8), (0x100020, 8)])
        with self.assertRaisesRegex(ValueError, "outside selected"):
            layout.build([(0x100008, 8, "wrong")], section_lo=0x100010,
                         section_hi=0x100028)

    def test_linkcheck_selected_span_and_vma(self):
        with tempfile.TemporaryDirectory() as tmp:
            retail = Path(tmp) / "retail.elf"
            retail.write_bytes(bytes(0x90) + b"fixtures")
            linked = Path(tmp) / "linked.elf"
            linked.touch()
            args = [str(linked), "--retail", str(retail), "--section-start",
                    "0x100010", "--section-size", "8"]
            with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
                with patch.object(linkcheck, "section_bytes", return_value=(0x100010, b"fixtures")):
                    self.assertEqual(linkcheck.main(args), 0)
                with patch.object(linkcheck, "section_bytes", return_value=(0x100000, b"fixtures")):
                    self.assertEqual(linkcheck.main(args), 1)

    def test_verify_cli_forwards_both_profile_paths(self):
        with patch.object(verify, "verify_one", return_value=(True, "MATCH")) as call, \
             contextlib.redirect_stdout(io.StringIO()):
            result = verify.main(["0x100010", "absent-source.c", "--unit-flags", "flags.tsv",
                                  "--unit-compilers", "compilers.tsv"])
        self.assertEqual(result, 0)
        self.assertEqual(call.call_args.kwargs["unit_flags"], "flags.tsv")
        self.assertEqual(call.call_args.kwargs["unit_compilers"], "compilers.tsv")


@unittest.skipUnless(Path(verify.WIBO_DEFAULT).is_file() and Path(verify.MWCC_DEFAULT).is_file()
                     and all(shutil.which("mipsel-linux-gnu-" + t)
                             for t in ("as", "ld", "objcopy", "readelf", "objdump")),
                     "requires the matching compiler and MIPS binutils")
class BuildFixture(unittest.TestCase):
    """A small independent target with a required compiler flag and private source inventory."""
    START = 0x100000
    VA = 0x100010

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="dw4-build-options-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.src = self.root / "fixture-src"
        self.src.mkdir()
        self.source = self.src / "fixture_leaf.c"
        self.source.write_text("#ifndef FIXTURE_VALUE\n#error target profile missing\n#endif\n"
                               "int fixture_leaf(void) { return FIXTURE_VALUE; }\n")
        self.flags = self.root / "unit-flags.tsv"
        self.flags.write_text(f"0x{self.VA:x}\t-O3 -DFIXTURE_VALUE=23 -Iinclude\n")
        self.compilers = self.root / "unit-compilers.tsv"
        compiler = Path(verify.MWCC_DEFAULT)
        relative = compiler.absolute().relative_to(Path(verify.ROOT).absolute())
        digest = hashlib.sha256(compiler.read_bytes()).hexdigest()
        self.compilers.write_text(f"0x{self.VA:x}\t{relative.as_posix()}\t{digest}\n")
        self.registry = self.root / "unit-objects.json"
        self.registry.write_text("{}\n")
        self.jumps = self.root / "jumptables.txt"
        self.jumps.write_text("")
        self.obj = self.root / "independent.o"
        subprocess.run([verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, "-c", "-O3",
                        "-DFIXTURE_VALUE=23", str(self.source), "-o", str(self.obj)],
                       capture_output=True, check=True)
        offset, self.size, index = verify.object_sym(str(self.obj), "fixture_leaf")
        body = verify.object_section(str(self.obj), ".text", index)[offset:offset+self.size]
        self.expected = bytes(range(16)) + body + bytes(range(8))
        self.span = len(self.expected)
        image = bytearray(0x80) + self.expected
        # A .reginfo table makes the fixture independent of any USA GP fallback.
        reginfo = len(image)
        image.extend(struct.pack("<6I", 0, 0, 0, 0, 0, 0x210000))
        names = b"\0.shstrtab\0.reginfo\0"
        names_at = len(image)
        image.extend(names)
        image.extend(bytes(-len(image) % 4))
        sections = len(image)
        image.extend(bytes(40))
        image.extend(struct.pack("<10I", 1, 3, 0, 0, names_at, len(names), 0, 0, 1, 0))
        image.extend(struct.pack("<10I", 11, 0x70000006, 0, 0, reginfo, 24, 0, 0, 4, 0))
        ident = b"\x7fELF\x01\x01\x01" + bytes(9)
        struct.pack_into("<16sHHIIIIIHHHHHH", image, 0, ident, 2, 8, 1,
                         self.VA, 52, sections, 0, 52, 32, 1, 40, 3, 1)
        struct.pack_into("<8I", image, 52, 1, 0x80, self.START, self.START,
                         self.span, self.span + 16, 7, 128)
        self.retail = self.root / "fixture.elf"
        self.retail.write_bytes(image)
        self.symbols = self.root / "symbols.txt"
        self.symbols.write_text(f"{self.VA:08x} {self.size:06x} fixture_leaf\n")
        self.layout = self.root / "layout.txt"
        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(layout.main(["--symbols", str(self.symbols), "--jumptables",
                str(self.jumps), "--out", str(self.layout), "--section-size", hex(self.span)]), 0)
        self.asm = self.root / "asm"
        self.asm.mkdir()
        words = struct.unpack("<" + "I" * (len(body) // 4), body)
        (self.asm / "fixture_leaf.s").write_text(".text\n" +
            "\n".join(f".word 0x{word:08x}" for word in words) + "\n")

    def profile_args(self):
        return ["--elf", str(self.retail), "--symbols", str(self.symbols),
                "--unit-objects", str(self.registry), "--unit-flags", str(self.flags),
                "--unit-compilers", str(self.compilers)]

    def test_custom_profile_check_and_selected_source_relink(self):
        output = io.StringIO()
        with contextlib.redirect_stdout(output), contextlib.redirect_stderr(output):
            # The invalid global compiler proves the explicit pinned table wins.
            self.assertEqual(verify.main([hex(self.VA), str(self.source), *self.profile_args(),
                                         "--mwcc", "missing-global-compiler"]), 0, output.getvalue())
            self.assertEqual(check.main([*self.profile_args(), "--asm", str(self.asm), "--src",
                str(self.src), "--mwcc", "missing-global-compiler", "--no-cache", "--jobs", "1"]), 0,
                output.getvalue())
            script = self.root / "link.ld"
            with patch.dict(os.environ, {"DW4_MWCC": "missing-global-compiler"}):
                self.assertEqual(linkgen.main([*self.profile_args(), "--layout", str(self.layout),
                    "--src", str(self.src), "--out", str(self.root / "objects"), "--ld", str(script),
                    "--section-start", hex(self.START), "--section-size", hex(self.span),
                    "--all", "--no-cache", "--jobs", "1"]), 0, output.getvalue())
            linked = self.root / "linked.elf"
            subprocess.run(["mipsel-linux-gnu-ld", "--no-warn-mismatch", "-G0", "-T", str(script),
                            "-o", str(linked)], capture_output=True, check=True)
            self.assertEqual(linkcheck.main([str(linked), "--retail", str(self.retail),
                "--section-start", hex(self.START), "--section-size", hex(self.span)]), 0,
                output.getvalue())
        self.assertIn("linked from C", output.getvalue())
        self.assertEqual(verify.object_section(str(linked), ".text"), self.expected)

    def test_profile_mismatch_fails_and_cache_inputs_cover_pinned_compiler(self):
        files = verify.profile_input_files(str(self.flags), str(self.compilers))
        self.assertIn(str(self.flags), files)
        self.assertIn(str(Path(verify.MWCC_DEFAULT).absolute()), files)
        wrong = self.root / "wrong-flags.tsv"
        wrong.write_text(f"0x{self.VA:x}\t-O3 -DFIXTURE_VALUE=24 -Iinclude\n")
        ok, report = verify.verify_one(self.VA, str(self.source), elf=str(self.retail),
            symbols=str(self.symbols), unit_flags=str(wrong), unit_compilers=str(self.compilers),
            unit_objects=str(self.registry))
        self.assertFalse(ok, report)

    def test_check_cache_does_not_reuse_another_profile(self):
        cache = self.root / "cache"
        cache.mkdir()
        wrong = self.root / "other-target-flags.tsv"
        wrong.write_text(f"0x{self.VA:x}\t-O3 -DFIXTURE_VALUE=24 -Iinclude\n")
        args = [*self.profile_args(), "--asm", str(self.asm), "--src", str(self.src),
                "--mwcc", "missing-global-compiler", "--jobs", "1"]
        changed = list(args)
        changed[changed.index("--unit-flags") + 1] = str(wrong)
        output = io.StringIO()
        with patch.object(buildcache, "CACHE_DIR", str(cache)), \
             contextlib.redirect_stdout(output), contextlib.redirect_stderr(output):
            self.assertEqual(check.main(args), 0, output.getvalue())
            self.assertNotEqual(check.main(changed), 0, output.getvalue())

    def test_linkgen_explicit_global_compiler_and_flags(self):
        flags = self.root / "empty-flags.tsv"
        compilers = self.root / "empty-compilers.tsv"
        flags.write_text("")
        compilers.write_text("")
        args = self.profile_args()
        args[args.index("--unit-flags") + 1] = str(flags)
        args[args.index("--unit-compilers") + 1] = str(compilers)
        output = self.root / "global-profile-objects"
        with patch.dict(os.environ, {"DW4_MWCC": "missing-environment-compiler"}), \
             contextlib.redirect_stdout(io.StringIO()):
            result = linkgen.main([*args, "--layout", str(self.layout), "--src", str(self.src),
                "--out", str(output), "--ld", str(self.root / "global.ld"),
                "--mwcc", verify.MWCC_DEFAULT, "--flags=-O3 -DFIXTURE_VALUE=23 -Iinclude",
                "--section-size", hex(self.span), "--all", "--no-cache", "--jobs", "1"])
        self.assertEqual(result, 0)
        self.assertEqual(verify.object_section(str(output / f"u_{self.VA:08x}.o"), ".text"),
                         self.expected[16:16+self.size])


if __name__ == "__main__":
    unittest.main()
