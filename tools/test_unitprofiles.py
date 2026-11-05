"""One translation unit, one profile: the units table, its resolution and the foreign-profile category.

The table and override tests need no compiler. The category tests compile the 16-byte
`igObjectSystem_FindMetaByNameDefault` (0x2fe460, the body tools/test_oracle_holes.py uses)
under a fixture units table and skip without the private compiler and retail image.
"""
import hashlib
import os
import shutil
import tempfile
import unittest
from pathlib import Path

import gen_unit_profiles as gen
import unitcompilers
import unitflags
import unitprofiles
import verify

ROOT = Path(unitprofiles.ROOT)
VA, NAME = 0x2fe460, "igObjectSystem_FindMetaByNameDefault"
SOURCE = ("extern int igObjectSystem_FindMetaByName(void *objectSystem, const char *name);\n"
          "extern void *g_objectSystem_00586dc8[4];\n"
          "int igObjectSystem_FindMetaByNameDefault(const char *name)"
          "{return igObjectSystem_FindMetaByName(g_objectSystem_00586dc8[0],name);}\n")


def retail_available():
    return (all(Path(p).exists() for p in (verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, verify.ELF_DEFAULT))
            and shutil.which("mipsel-linux-gnu-readelf"))


class Fixture(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.compiler = self.root / "mwcc.exe"
        self.compiler.write_bytes(b"compiler fixture")
        self.digest = hashlib.sha256(self.compiler.read_bytes()).hexdigest()
        self.units = self.root / "units.tsv"
        self.flags = self.root / "unit-flags.tsv"
        self.compilers = self.root / "unit-compilers.tsv"
        self.flags.write_text("")
        self.compilers.write_text("")
        self.addCleanup(self.clear)

    def clear(self):
        unitprofiles.load.cache_clear()
        unitcompilers.load_rows.cache_clear()
        unitflags._CACHE.clear()

    def write_units(self, rows, compilers=None):
        head = "".join("@compiler\t%s\t%s\t%s\n" % c for c in (compilers or [("default", "mwcc.exe", self.digest)]))
        self.units.write_text(head + "".join(rows))
        self.clear()

    def resolve(self, va, default_flags="-O3 -Iinclude"):
        return unitprofiles.resolve(va, default_flags, "global.exe", units=str(self.units),
                                    unit_flags=str(self.flags), unit_compilers=str(self.compilers), root=self.root)


class TableTests(Fixture):
    def test_rows_resolve_by_address_with_an_exclusive_end(self):
        self.write_units(["0x00100000\t0x00100100\tfirst\tdefault\t-O3 -Iinclude\toff\t-\tevidence\n",
                          "0x00100100\t0x00100200\tsecond\tdefault\t-O3,p -Iinclude\ton\tprovisional\t\n"])
        table = unitprofiles.load(str(self.units))
        self.assertEqual([u.name for u in table.units], ["first", "second"])
        self.assertEqual(unitprofiles.unit_for(0x1000f0, table).name, "first")
        self.assertEqual(unitprofiles.unit_for(0x100100, table).name, "second")
        self.assertIsNone(unitprofiles.unit_for(0x100200, table))
        self.assertIsNone(unitprofiles.unit_for(0xfffff, table))
        res = self.resolve(0x100010)
        self.assertEqual(res.profile, unitprofiles.Profile(str(self.compiler), "-O3 -Iinclude", "off"))
        self.assertEqual(unitprofiles.command_flags(res.profile), "-O3 -Iinclude -Cpp_exceptions off")
        on = self.resolve(0x100180).profile
        self.assertEqual(unitprofiles.command_flags(on), "-O3,p -Iinclude")

    def test_malformed_tables_are_rejected(self):
        bad = [
            ("0x00100000\t0x00100100\tu\tnope\t-O3\toff\t-\t\n", "unknown compiler id"),
            ("0x00100000\t0x00100100\tu\tdefault\t-O3\tmaybe\t-\t\n", "exceptions must be"),
            ("0x00100000\t0x00100100\tu\tdefault\t-O3\toff\tguess\t\n", "status must be"),
            ("0x00100100\t0x00100000\tu\tdefault\t-O3\toff\t-\t\n", "inverted"),
            ("0x00100000\t0x00100100\ta\tdefault\t-O3\toff\t-\t\n0x000000f0\t0x00100010\tb\tdefault\t-O3\toff\t-\t\n", "overlap"),
        ]
        for row, message in bad:
            with self.subTest(row=row):
                with self.assertRaisesRegex(ValueError, message):
                    unitprofiles.parse("@compiler\tdefault\tmwcc.exe\t%s\n%s" % (self.digest, row))
        with self.assertRaisesRegex(ValueError, "SHA-256"):
            unitprofiles.parse("@compiler\tdefault\tmwcc.exe\tnot-a-digest\n")
        with self.assertRaisesRegex(ValueError, "repository-relative"):
            unitprofiles.parse("@compiler\tdefault\t/abs/mwcc.exe\t%s\n" % self.digest)

    def test_missing_or_changed_compiler_never_falls_back(self):
        self.write_units(["0x00100000\t0x00100100\tu\tdefault\t-O3 -Iinclude\toff\t-\t\n"])
        self.resolve(0x100010)
        self.compiler.write_bytes(b"another build")
        with self.assertRaisesRegex(ValueError, "SHA-256 mismatch"):
            self.resolve(0x100010)
        self.compiler.unlink()
        with self.assertRaisesRegex(ValueError, "required compiler missing"):
            self.resolve(0x100010)

    def test_units_path_follows_the_symbol_map(self):
        self.assertEqual(unitprofiles.units_path(None), str(ROOT / "config" / "SLUS-20836" / "units.tsv"))
        self.assertEqual(unitprofiles.units_path(str(ROOT / "config" / "SLUS-20836" / "symbols.txt")),
                         str(ROOT / "config" / "SLUS-20836" / "units.tsv"))
        symbols = self.root / "symbols.txt"
        symbols.write_text("")
        self.assertIsNone(unitprofiles.units_path(str(symbols)))
        self.units.write_text("")
        self.assertEqual(unitprofiles.units_path(str(symbols)), str(self.units))
        self.assertEqual(unitprofiles.units_path(str(symbols), explicit="x/units.tsv"), str(ROOT / "x" / "units.tsv"))


class OverrideTests(Fixture):
    def test_outside_every_unit_rows_are_the_whole_profile(self):
        self.write_units([])
        res = self.resolve(0x100010, "-O3 -Cpp_exceptions off -Iinclude")
        self.assertIsNone(res.unit)
        self.assertEqual(res.profile, unitprofiles.Profile(str(self.root / "global.exe"), "-O3 -Iinclude", "off"))
        self.flags.write_text("0x100010\t-O3,p -Iinclude\n")
        self.compilers.write_text("0x100010\tmwcc.exe\t%s\n" % self.digest)
        self.clear()
        res = self.resolve(0x100010)
        self.assertEqual(res.profile, unitprofiles.Profile(str(self.compiler), "-O3,p -Iinclude", "on"))
        self.assertIsNone(res.override)

    def test_inside_a_unit_rows_must_be_provisional_and_become_overrides(self):
        self.write_units(["0x00100000\t0x00100100\tu\tdefault\t-O3 -Iinclude\toff\t-\t\n"])
        self.flags.write_text("0x100010\t-O3,p -Iinclude\n")
        self.clear()
        with self.assertRaisesRegex(ValueError, "not marked provisional"):
            self.resolve(0x100010)
        self.flags.write_text("0x100010\t-O3,p -Iinclude\tprovisional\tfinding #646\n")
        self.clear()
        res = self.resolve(0x100010)
        self.assertEqual(res.unit.name, "u")
        self.assertEqual(res.profile.flags, "-O3 -Iinclude")
        self.assertEqual(res.override, unitprofiles.Profile(str(self.compiler), "-O3,p -Iinclude", "off"))
        self.assertFalse(res.redundant)
        # a `-Cpp_exceptions on` token in the row overrides the unit's exception mode
        self.flags.write_text("0x100010\t-O3 -Cpp_exceptions on -Iinclude\tprovisional\t\n")
        self.clear()
        self.assertEqual(self.resolve(0x100010).override.exceptions, "on")
        # rows that repeat the unit profile are redundant, not an override
        self.flags.write_text("0x100010\t-O3 -Cpp_exceptions off -Iinclude\tprovisional\t\n")
        self.clear()
        res = self.resolve(0x100010)
        self.assertIsNone(res.override)
        self.assertTrue(res.redundant)
        # the compiler table has the same rule
        self.flags.write_text("")
        self.compilers.write_text("0x100010\tmwcc.exe\t%s\n" % self.digest)
        self.clear()
        with self.assertRaisesRegex(ValueError, "not marked provisional"):
            self.resolve(0x100010)

    def test_profile_key_changes_with_the_rows_and_the_unit(self):
        self.write_units(["0x00100000\t0x00100100\tu\tdefault\t-O3 -Iinclude\toff\t-\t\n"])
        args = dict(units=str(self.units), unit_flags=str(self.flags), unit_compilers=str(self.compilers), root=self.root)
        before = unitprofiles.profile_key(0x100010, "-O3 -Iinclude", "global.exe", **args)
        self.assertEqual(before, unitprofiles.profile_key(0x100010, "-O3 -Iinclude", "global.exe", **args))
        self.write_units(["0x00100000\t0x00100100\tu\tdefault\t-O3,p -Iinclude\toff\t-\t\n"])
        self.assertNotEqual(before, unitprofiles.profile_key(0x100010, "-O3 -Iinclude", "global.exe", **args))
        self.flags.write_text("0x100010\t-O4 -Iinclude\tprovisional\t\n")
        self.clear()
        with_row = unitprofiles.profile_key(0x100010, "-O3 -Iinclude", "global.exe", **args)
        self.assertNotEqual(before, with_row)
        self.assertNotEqual(with_row, unitprofiles.profile_key(0x100020, "-O3 -Iinclude", "global.exe", **args))


class GeneratorConsistency(unittest.TestCase):
    """The generator names every unit whose members have no common profile and marks it provisional."""

    def function(self, va, name, pin, category="match", ext=".c"):
        f = gen.Function(va, 0x40, name)
        f.path = "src/x/%s%s" % (name, ext)
        f.pin = pin
        f.category = category
        return f

    def test_empty_intersection_is_provisional_and_a_common_profile_wins(self):
        gen.GROUP_OWNERS.clear()
        contested = gen.Unit("igContested", [
            self.function(0x200000, "igContested_A", ("default", "-O3 -Iinclude", None)),
            self.function(0x200040, "igContested_B", ("default", "-O3 -Iinclude", None)),
            self.function(0x200080, "igContested_C", ("combat", "-O3,p -Iinclude", None))], "class", "test")
        agreed = gen.Unit("beAgreed", [
            self.function(0x300000, "beAgreed_A", ("default", "-O3 -Iinclude", None)),
            self.function(0x300040, "beAgreed_B", ("default", "-O3 -Iinclude", None)),
            self.function(0x300080, "beAgreed_C", ("combat", "-O3,p -Iinclude", None))], "class", "test")
        evidence = gen.Evidence()
        combat = gen.COMPILERS["combat"]
        default = gen.COMPILERS["default"]
        results = [
            # contested: nobody reproduces the other side (3.0.3 fails everywhere too)
            (0x200080, default, "-O3 -Iinclude", False), (0x200000, combat, "-O3,p -Iinclude", False),
            (0x200040, combat, "-O3,p -Iinclude", False),
            # agreed: the default members also reproduce under combat -O3,p
            (0x300000, combat, "-O3,p -Iinclude", True), (0x300040, combat, "-O3,p -Iinclude", True),
            (0x300080, default, "-O3 -Iinclude", False),
        ]
        for va, compiler, flags, ok in results:
            for mode in ("on", "off"):
                evidence.results[(va, gen.compiler_id(compiler), flags, mode)] = gen.YES if ok else gen.NO
        for va, flags in ((0x200000, "-O3 -Iinclude"), (0x200040, "-O3 -Iinclude"), (0x200080, "-O3,p -Iinclude"),
                          (0x200000, "-O3,p -Iinclude"), (0x200040, "-O3,p -Iinclude"), (0x200080, "-O3 -Iinclude"),
                          (0x300000, "-O3 -Iinclude"), (0x300040, "-O3 -Iinclude"), (0x300080, "-O3,p -Iinclude"),
                          (0x300000, "-O3,p -Iinclude"), (0x300040, "-O3,p -Iinclude"), (0x300080, "-O3 -Iinclude")):
            for mode in ("on", "off"):
                evidence.results[(va, "3.0.3", flags, mode)] = gen.NO
        units = [contested, agreed]
        for u in units:
            u.exceptions = "on"       # the pins carry no -Cpp_exceptions token: exceptions on
        undecided = gen.evaluate(units, evidence)
        self.assertEqual(undecided, [])
        gen.choose(units)
        self.assertEqual(contested.status, "provisional")
        self.assertEqual(contested.profile, ("default", "-O3 -Iinclude"))
        self.assertEqual([f.name for f, _ in contested.overrides], ["igContested_C"])
        self.assertEqual(agreed.status, "-")
        self.assertEqual(agreed.profile, ("combat", "-O3,p -Iinclude"))
        self.assertEqual(agreed.overrides, [])
        import contextlib
        import io
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            gen.report(units, [f for u in units for f in u.functions], {0x200080: None, 0x300080: None}, {})
        text = out.getvalue()
        self.assertIn("igContested", text)
        self.assertIn("override 0x200080 igContested_C", text)
        self.assertNotIn("override 0x300080", text)
        self.assertIn("1 provisional", text)

    def test_untested_members_stay_undecided_until_swept(self):
        gen.GROUP_OWNERS.clear()
        unit = gen.Unit("igPending", [
            self.function(0x400000, "igPending_A", ("default", "-O3 -Iinclude", None)),
            self.function(0x400040, "igPending_B", ("combat", "-O3 -Iinclude", None), ext=".cpp")], "class", "test")
        unit.exceptions = "on"
        undecided = gen.evaluate([unit], gen.Evidence())
        pairs = {(f.name, cand) for f, cand, _mode in undecided}
        self.assertIn(("igPending_B", ("default", "-O3 -Iinclude")), pairs)
        self.assertIn(("igPending_A", ("combat", "-O3 -Iinclude")), pairs)
        self.assertIn(("igPending_A", ("3.0.3", "-O3 -Iinclude")), pairs)


@unittest.skipUnless(retail_available(), "needs the private compiler and retail image")
class ForeignProfileCategory(Fixture):
    """A function that matches only under its provisional override is debt, never a match."""

    def setUp(self):
        super().setUp()
        self.mwcc = Path(verify.MWCC_DEFAULT)
        self.digest = hashlib.sha256(self.mwcc.read_bytes()).hexdigest()
        self.source = self.root / "cand.c"
        self.source.write_text(SOURCE)
        self.repo_compiler = [("default", os.path.relpath(self.mwcc, ROOT), self.digest)]

    def check(self):
        return verify.verify_one(VA, str(self.source), symbols=str(ROOT / "config" / "SLUS-20836" / "symbols.txt"),
                                 units=str(self.units), unit_flags=str(self.flags),
                                 unit_compilers=str(self.compilers))

    def test_override_only_match_is_foreign_profile(self):
        self.write_units(["0x002fe460\t0x002fe470\tfixture\tdefault\t-O0 -Iinclude\toff\t-\t\n"], self.repo_compiler)
        self.flags.write_text("0x2fe460\t-O3 -Iinclude\tprovisional\tmatches at -O3 only\n")
        self.clear()
        ok, report = self.check()
        self.assertFalse(ok, report)
        head = report.partition("\n")[0]
        self.assertIn("cat=foreign-profile", head)
        self.assertIn("override=foreign", head)
        self.assertIn("foreign-profile: the code bytes are reproduced only under the provisional override", report)
        self.assertIn("unit profile of fixture", report)

    def test_unit_profile_match_reports_a_stale_override(self):
        self.write_units(["0x002fe460\t0x002fe470\tfixture\tdefault\t-O3 -Iinclude\toff\t-\t\n"], self.repo_compiler)
        self.flags.write_text("0x2fe460\t-O0 -Iinclude\tprovisional\tstale\n")
        self.clear()
        ok, report = self.check()
        self.assertTrue(ok, report)
        self.assertIn("cat=match", report.partition("\n")[0])
        self.assertIn("override=unused", report.partition("\n")[0])
        self.flags.write_text("0x2fe460\t-O3 -Iinclude -Cpp_exceptions off\tprovisional\tredundant\n")
        self.clear()
        ok, report = self.check()
        self.assertTrue(ok, report)
        self.assertIn("override=redundant", report.partition("\n")[0])

    def test_unmarked_row_inside_a_unit_fails_before_compiling(self):
        self.write_units(["0x002fe460\t0x002fe470\tfixture\tdefault\t-O3 -Iinclude\toff\t-\t\n"], self.repo_compiler)
        self.flags.write_text("0x2fe460\t-O3,p -Iinclude\n")
        self.clear()
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("compile failed: per-function row", report)
        self.assertIn("not marked provisional", report)

    def test_neither_profile_is_a_mismatch_naming_both(self):
        self.write_units(["0x002fe460\t0x002fe470\tfixture\tdefault\t-O0 -Iinclude\toff\t-\t\n"], self.repo_compiler)
        self.flags.write_text("0x2fe460\t-O0,p -Iinclude\tprovisional\t\n")
        self.clear()
        ok, report = self.check()
        self.assertFalse(ok)
        self.assertIn("cat=mismatch", report.partition("\n")[0])
        self.assertIn("does not reproduce the code bytes either", report)


if __name__ == "__main__":
    unittest.main()
