"""Session preludes: a unit compiled after another file in the same MWCC process (tools/cc.py).

The table, command-line and cache-key tests need no compiler beyond the b52 executable's presence for the
cache key; the compile tests run b52 under wibo and skip without them.
"""
import hashlib
import os
import re
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

import buildcache
import cc
import unitcompilers
import unitflags
import unitobjects
import unitprofiles

ROOT = Path(unitprofiles.ROOT)
B52_RELATIVE = "local/mwcps2/3.0b52-030722/mwccps2.exe"
B52 = ROOT / B52_RELATIVE
WIBO = Path(os.environ.get("DW4_WIBO", ROOT / "local" / "wibo"))
PRELUDE = "config/SLUS-20836/session-preludes/runtime_call_a0.cpp"
FLAGS = "-O4,p -sdatathreshold 2 -inline level=8,bottomup"


def clear_tables():
    unitprofiles.load.cache_clear()
    unitcompilers.load_rows.cache_clear()
    unitflags._CACHE.clear()
    unitobjects.load.cache_clear()
    buildcache._memo.clear()


class Setting(unittest.TestCase):
    """The setting in config/SLUS-20836/units.tsv: `-session-prelude <file>` in a unit's flags."""

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "mwcc.exe").write_bytes(b"compiler fixture")
        (self.root / "preludes").mkdir()
        (self.root / "preludes" / "lead.cpp").write_text("extern \"C\" float L(long long x) { return (float)x; }\n")
        digest = hashlib.sha256(b"compiler fixture").hexdigest()
        self.head = ("@compiler\tmw\tmwcc.exe\t%s\n@compiler\tgcc\tbin/ee-gcc\t%s\n" % (digest, digest))
        self.units = self.root / "units.tsv"
        self.empty = self.root / "empty.tsv"
        self.empty.write_text("")
        self.addCleanup(clear_tables)

    def write(self, *rows):
        self.units.write_text(self.head + "".join(rows))
        clear_tables()

    def resolve(self, va):
        return unitprofiles.resolve(va, "-O3", "global.exe", units=str(self.units), unit_flags=str(self.empty),
                                    unit_compilers=str(self.empty), root=self.root)

    def test_split_takes_every_pair_and_keeps_the_rest_in_order(self):
        self.assertEqual(cc.split_session_preludes("-O4,p -Iinclude"), ("-O4,p -Iinclude", []))
        self.assertEqual(cc.split_session_preludes("-O4,p -session-prelude a.cpp -Iinclude -session-prelude b.cpp"),
                         ("-O4,p -Iinclude", ["a.cpp", "b.cpp"]))
        with self.assertRaisesRegex(ValueError, "needs a file"):
            cc.split_session_preludes("-O4,p -session-prelude")

    def test_a_unit_row_carries_the_prelude_in_its_flags(self):
        self.write("0x00100000\t0x00100100\tlead\tmw\t-O4,p -session-prelude preludes/lead.cpp\ton\t-\t\n",
                   "0x00100100\t0x00100200\tplain\tmw\t-O4,p\ton\t-\t\n")
        lead, plain = self.resolve(0x100010).profile, self.resolve(0x100110).profile
        self.assertEqual(cc.split_session_preludes(unitprofiles.command_flags(lead)), ("-O4,p", ["preludes/lead.cpp"]))
        self.assertEqual(unitprofiles.command_flags(plain), "-O4,p")
        self.assertFalse(unitprofiles.same_profile(lead, plain))

    def test_malformed_settings_are_rejected(self):
        for flags, message in (("-O4,p -session-prelude", "needs a file"),
                               ("-O4,p -session-prelude /abs/lead.cpp", "repository-relative"),
                               ("-O4,p -session-prelude ../lead.cpp", "repository-relative")):
            with self.subTest(flags=flags):
                with self.assertRaisesRegex(ValueError, message):
                    unitprofiles.parse(self.head + "0x00100000\t0x00100100\tu\tmw\t%s\ton\t-\t\n" % flags)
        with self.assertRaisesRegex(ValueError, "needs an MWCC compiler"):
            unitprofiles.parse(self.head + "0x00100000\t0x00100100\tu\tgcc\t-O2 -session-prelude p.c\toff\t-\t\n")

    def test_a_missing_prelude_is_a_resolution_error(self):
        self.write("0x00100000\t0x00100100\tlead\tmw\t-O4,p -session-prelude preludes/gone.cpp\ton\t-\t\n")
        with self.assertRaisesRegex(ValueError, "session prelude preludes/gone.cpp is missing"):
            self.resolve(0x100010)


class CommandLine(unittest.TestCase):
    def test_a_unit_without_the_setting_keeps_its_command_line(self):
        self.assertEqual(cc.compile_argv("wibo", "mwcc.exe", "-O4,p -Iinclude -Cpp_exceptions off", "src/a.cpp", "a.o"),
                         ["wibo", "mwcc.exe", "-c", "-O4,p", "-Iinclude", "-Cpp_exceptions", "off", "src/a.cpp",
                          "-o", "a.o"])

    def test_a_prelude_compiles_first_in_the_same_process(self):
        argv = cc.compile_argv("wibo", "mwcc.exe", "-O4,p -session-prelude %s -Iinclude" % PRELUDE, "src/a.cpp", "a.o")
        self.assertEqual(argv[1:4], [os.path.abspath(cc.__file__), "--session", "a.o"])
        self.assertEqual(argv[4:], ["wibo", "mwcc.exe", "-c", "-O4,p", "-Iinclude", str(ROOT / PRELUDE), "src/a.cpp"])

    def test_refusals(self):
        with self.assertRaisesRegex(ValueError, "Sony EE GCC"):
            cc.compile_argv(None, "bin/ee-gcc", "-O2 -session-prelude %s" % PRELUDE, "a.c", "a.o")
        with self.assertRaisesRegex(ValueError, "same object name"):
            cc.compile_argv("wibo", "mwcc.exe", "-O4,p -session-prelude %s" % PRELUDE, "src/RUNTIME_CALL_A0.cpp", "a.o")


@unittest.skipUnless(B52.exists(), "b52 compiler unavailable")
class CacheKey(unittest.TestCase):
    """tools/buildcache.unit_profile_sha keys a unit on its prelude's bytes and nothing else on them."""

    def setUp(self):
        os.makedirs(ROOT / "build", exist_ok=True)
        folder = Path(tempfile.mkdtemp(prefix="test-session-prelude-", dir=ROOT / "build"))
        self.addCleanup(shutil.rmtree, folder, ignore_errors=True)
        self.prelude = folder / "lead.cpp"
        self.prelude.write_text("extern \"C\" float L(long long x) { return (float)x; }\n")
        relative = self.prelude.relative_to(ROOT).as_posix()
        self.units = folder / "units.tsv"
        self.units.write_text(
            "@compiler\tb52\t%s\t%s\n" % (B52_RELATIVE, buildcache.file_sha(str(B52)))
            + "0x00100000\t0x00100100\tlead\tb52\t-O4,p -session-prelude %s\ton\t-\t\n" % relative
            + "0x00100100\t0x00100200\tplain\tb52\t-O4,p\ton\t-\t\n")
        self.empty = folder / "empty.tsv"
        self.empty.write_text("")
        self.objects = folder / "unit-objects.json"
        self.objects.write_text("{}")
        self.addCleanup(clear_tables)

    def key(self, va):
        clear_tables()
        return buildcache.unit_profile_sha(va, "-O3", B52_RELATIVE, unit_objects=str(self.objects),
                                           units=str(self.units), unit_flags=str(self.empty),
                                           unit_compilers=str(self.empty))

    def test_the_key_follows_the_prelude_content(self):
        lead, plain = self.key(0x100010), self.key(0x100110)
        self.assertEqual(lead, self.key(0x100010))
        self.prelude.write_text("extern \"C\" double L(int x) { return x; }\n")
        self.assertNotEqual(lead, self.key(0x100010))
        self.assertEqual(plain, self.key(0x100110))


@unittest.skipUnless(B52.exists() and WIBO.exists() and shutil.which("mipsel-linux-gnu-objdump"),
                     "b52 compiler unavailable")
class Compile(unittest.TestCase):
    """The repository's prelude puts a0 in b52's runtime-call mask: a later `__fixsfdi` keeps a0 live from entry."""

    SOURCE = ("extern long long g_time;\n"
              "void probe(int unused, int *p, float shown) {\n"
              "    int x = p[0], y = p[1], z = p[2], w = p[3];\n"
              "    p[4] = x + y; p[5] = z + w; p[6] = x - w; p[7] = y - z;\n"
              "    g_time = (long long)shown;\n"
              "}\n")

    def compile(self, folder, flags, name):
        source = os.path.join(folder, "probe.cpp")
        with open(source, "w") as fh:
            fh.write(self.SOURCE)
        out = os.path.join(folder, name)
        argv = cc.compile_argv(str(WIBO), str(B52), flags, source, out)
        subprocess.run(argv, check=True, capture_output=True, cwd=ROOT, env=dict(os.environ, MWCIncludes=folder))
        dump = subprocess.run(["mipsel-linux-gnu-objdump", "-dr", out], check=True, capture_output=True, text=True)
        return argv, dump.stdout

    def test_only_the_unit_object_is_kept_and_it_carries_the_session_state(self):
        with tempfile.TemporaryDirectory(prefix="dw4-session-") as folder:
            argv, plain = self.compile(folder, FLAGS, "plain.o")
            self.assertEqual(argv[:3], [str(WIBO), str(B52), "-c"])
            _argv, session = self.compile(folder, FLAGS + " -session-prelude " + PRELUDE, "session.o")
            self.assertEqual(sorted(os.listdir(folder)), ["plain.o", "probe.cpp", "session.o"])
        self.assertNotIn("LeakA0", session)
        self.assertIn("__fixsfdi", session)
        self.assertIsNotNone(re.search(r"\blw\s+a0,", plain))
        self.assertIsNone(re.search(r"\ba0\b", session.split("<probe__FiPif>:")[1]))


if __name__ == "__main__":
    unittest.main()
