#!/usr/bin/env python3
"""Self-test for the parsing half of .githooks/pre-push: saved `make check` / `make link` output in, verdict out.

The hook's gate is evaluated with DW4_PREPUSH_GATE_ONLY=1 on sample logs, so no build runs here.
"""
import os, subprocess, sys, tempfile, unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HOOK = os.path.join(ROOT, ".githooks", "pre-push")

CHECK_CLEAN = """\
cache : 20 hits, 3 recomputed (split units)
split : 19293/19293 units round-trip byte-exactly
cache : 19290 hits, 3 recomputed (functions compiled and compared)
code  : 19293 functions, 3377884 bytes laid out in config/SLUS-20836/symbols.txt
cover : 18407/19293 decompiled in src/ (95.4%), 18407 match byte-for-byte
"""
CHECK_MISMATCH = CHECK_CLEAN.replace("18407 match", "18405 match") + """\
   !! FUN_00123456: mismatch
   !! FUN_00123460: mismatch
   !! FUN_00123470: code-only (exc=missing)
   (3 not matched: 2 mismatch, 1 debt)
"""
CHECK_DEBT_ONLY = CHECK_CLEAN.replace("18407 match", "14047 match") + """\
   match           14047  code bytes, exception metadata and symbol rules all pass
!! debt: code-only        4323  code bytes identical, exception metadata unproven (exc=missing/extra/differ)
!! debt: name-defect         4  code bytes identical, a symbol name is wrong for its address
   !! FUN_00100240: code-only (exc=extra)
   !! FUN_00100390: code-only (exc=missing)
   (4360 not matched: 0 mismatch, 4360 debt)
"""
CHECK_FAILED = CHECK_CLEAN + "   !! FUN_00123456: compile failed: error: undefined identifier\n"
LINK_OK = """\
linked .text: vma=0x100000 size=4541184   retail: 4541184
linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly
linkcheck: orphans: 22697 bytes linked outside .text (.exceptix 21108, .exception 1589) <= recorded debt 22712 bytes (1759 exc=extra/differ units in data/check-categories.tsv)  OK
"""
LINK_ORPHANS_EXCEED = LINK_OK.replace("<= recorded debt 22712 bytes", "> recorded debt 0 bytes").replace("  OK\n", "  REFUSED\n")
LINK_NO_ORPHAN_LINE = LINK_OK.splitlines(keepends=True)[0] + LINK_OK.splitlines(keepends=True)[1]
UNIT_OK = "...........\n----------------------------------------------------------------------\nRan 90 tests in 30.0s\n\nOK\n"
UNIT_FAILED = UNIT_OK.replace("\nOK\n", "\nFAILED (failures=1)\n")
COUNTEREXAMPLES = ["test_smuggled_data_fails_naming_every_section",
                   "test_defining_the_referenced_datum_fails",
                   "test_function_name_pointing_inside_a_body_fails",
                   "test_data_name_pointing_into_code_fails"]
ORACLE_OK = "".join("%s (test_oracle_holes.Counterexamples.%s) ... ok\n" % (t, t) for t in COUNTEREXAMPLES) + UNIT_OK
ORACLE_SKIPPED = ORACLE_OK.replace("test_data_name_pointing_into_code_fails) ... ok",
                                   "test_data_name_pointing_into_code_fails) ... skipped 'private retail compiler unavailable'")
LINK_BAD = """\
linked .text: vma=0x100000 size=4541184   retail: 4541184
linkcheck: 12 differing bytes (0.00%)
"""


def gate(check, link, baseline):
    with tempfile.TemporaryDirectory() as d:
        c, l = os.path.join(d, "check.log"), os.path.join(d, "link.log")
        open(c, "w").write(check)
        open(l, "w").write(link)
        env = dict(os.environ, DW4_PREPUSH_GATE_ONLY="1")
        r = subprocess.run(["sh", HOOK, c, l, str(baseline)], capture_output=True, text=True, env=env, cwd=ROOT)
        return r.returncode, r.stdout


def oracle_rule(repo, range_, unit_log, oracle_log):
    with tempfile.TemporaryDirectory() as d:
        u, o = os.path.join(d, "unit.log"), os.path.join(d, "oracle.log")
        open(u, "w").write(unit_log)
        open(o, "w").write(oracle_log)
        env = dict(os.environ, DW4_PREPUSH_ORACLE_ONLY="1")
        r = subprocess.run(["sh", HOOK, range_, u, o], capture_output=True, text=True, env=env, cwd=repo)
        return r.returncode, r.stdout + r.stderr


class Gate(unittest.TestCase):
    def test_pass(self):
        rc, out = gate(CHECK_CLEAN, LINK_OK, 18407)
        self.assertEqual(rc, 0, out)
        self.assertIn("mismatches: 0", out)
        self.assertIn("matched: 18407", out)
        self.assertIn("BYTE-IDENTICAL", out)
        self.assertIn("orphans <= recorded debt", out)
        self.assertIn("debt-check: tools/progress.py has no --debt-check; skipped", out)
        self.assertIn("pre-push: PASS", out)
        self.assertEqual(sum(1 for ln in out.splitlines() if ln.startswith(("gate ", "pre-push:"))), 6)

    def test_cover_line_with_asm_bodies(self):
        check = CHECK_CLEAN.replace("18407 match byte-for-byte", "18407 match byte-for-byte, 1209 asm bodies not counted")
        rc, out = gate(check, LINK_OK, 18407)
        self.assertEqual(rc, 0, out)
        self.assertIn("matched: 18407", out)

    def test_orphans_exceeding_debt_refused(self):
        rc, out = gate(CHECK_CLEAN, LINK_ORPHANS_EXCEED, 18407)
        self.assertEqual(rc, 1)
        self.assertIn("gate 4/5  orphans <= recorded debt: 22697 bytes", out)
        self.assertIn("REFUSED", out)

    def test_missing_orphan_line_refused(self):
        rc, out = gate(CHECK_CLEAN, LINK_NO_ORPHAN_LINE, 18407)
        self.assertEqual(rc, 1)
        self.assertIn("no 'linkcheck: orphans:' line", out)

    def test_debt_check_verdict(self):
        with tempfile.TemporaryDirectory() as d:
            c, l = os.path.join(d, "check.log"), os.path.join(d, "link.log")
            open(c, "w").write(CHECK_CLEAN)
            open(l, "w").write(LINK_OK)
            for verdict, rc_want in (("0", 0), ("1", 1)):
                env = dict(os.environ, DW4_PREPUSH_GATE_ONLY="1", DEBT_RC=verdict)
                r = subprocess.run(["sh", HOOK, c, l, "18407"], capture_output=True, text=True, env=env, cwd=ROOT)
                self.assertEqual(r.returncode, rc_want, r.stdout)
                self.assertIn("gate 5/5  debt-check", r.stdout)


class OracleChangeRule(unittest.TestCase):
    """(a)-(c) on a throwaway repository with the real protected-file list."""

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="dw4-oracle-rule-")
        self.addCleanup(self.temp.cleanup)
        self.repo = self.temp.name
        self.git("init", "-q", "-b", "main")
        self.git("config", "user.email", "test@example.invalid")
        self.git("config", "user.name", "test")
        os.makedirs(os.path.join(self.repo, ".githooks"))
        os.makedirs(os.path.join(self.repo, "tools"))
        os.makedirs(os.path.join(self.repo, "docs"))
        with open(os.path.join(ROOT, ".githooks", "oracle-files.txt")) as src, \
                open(os.path.join(self.repo, ".githooks", "oracle-files.txt"), "w") as dst:
            dst.write(src.read())
        self.commit("docs/a.md", "base", "base commit")
        self.base = self.git("rev-parse", "HEAD").strip()

    def git(self, *args):
        return subprocess.run(["git", *args], cwd=self.repo, check=True, capture_output=True, text=True).stdout

    def commit(self, path, text, message):
        full = os.path.join(self.repo, path)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        open(full, "w").write(text)
        self.git("add", path)
        self.git("commit", "-q", "-m", message)
        return self.git("rev-parse", "HEAD").strip()

    def test_untouched_oracle_passes_through(self):
        head = self.commit("docs/b.md", "doc", "docs only")
        rc, out = oracle_rule(self.repo, f"{self.base}..{head}", UNIT_FAILED, "")
        self.assertEqual(rc, 0, out)
        self.assertIn("no protected oracle file changes", out)

    def test_documented_change_with_passing_suites(self):
        head = self.commit("tools/verify.py", "# v2", "tighten the resolver\n\noracle-change: data names may not point into code\n")
        rc, out = oracle_rule(self.repo, f"{self.base}..{head}", UNIT_OK, ORACLE_OK)
        self.assertEqual(rc, 0, out)
        for line in ("oracle a/c", "oracle b/c", "oracle c/c"):
            self.assertIn(line, out)
        self.assertNotIn("REFUSED", out)

    def test_missing_oracle_change_line_refused(self):
        head = self.commit("tools/check.py", "# v2", "tweak check\n")
        rc, out = oracle_rule(self.repo, f"{self.base}..{head}", UNIT_OK, ORACLE_OK)
        self.assertEqual(rc, 1)
        self.assertIn("commits without an 'oracle-change:' line: " + head[:7], out)

    def test_failing_unit_tests_refused(self):
        head = self.commit("config/SLUS-20836/exceptions.txt", "# v2", "regenerate\n\noracle-change: refreshed records\n")
        rc, out = oracle_rule(self.repo, f"{self.base}..{head}", UNIT_FAILED, ORACLE_OK)
        self.assertEqual(rc, 1)
        self.assertIn("unit tests: not OK", out)

    def test_skipped_counterexample_refused(self):
        head = self.commit(".githooks/pre-push", "#!/bin/sh\n", "hook\n\noracle-change: new gate\n")
        rc, out = oracle_rule(self.repo, f"{self.base}..{head}", UNIT_OK, ORACLE_SKIPPED)
        self.assertEqual(rc, 1)
        self.assertIn("not shown failing (skipped/failed/absent): test_data_name_pointing_into_code_fails", out)

    def test_only_the_oracle_commit_needs_the_line(self):
        self.commit("docs/c.md", "doc", "docs commit without the line")
        head = self.commit("tools/linkgen.py", "# v2", "place metadata\n\noracle-change: carve data units\n")
        rc, out = oracle_rule(self.repo, f"{self.base}..{head}", UNIT_OK, ORACLE_OK)
        self.assertEqual(rc, 0, out)

    def test_more_matches_than_baseline_pass(self):
        rc, _ = gate(CHECK_CLEAN, LINK_OK, 18000)
        self.assertEqual(rc, 0)

    def test_debt_only_passes(self):
        rc, out = gate(CHECK_DEBT_ONLY, LINK_OK, 14047)
        self.assertEqual(rc, 0, out)
        self.assertIn("mismatches: 0", out)

    def test_mismatch_refused(self):
        rc, out = gate(CHECK_MISMATCH, LINK_OK, 18405)
        self.assertEqual(rc, 1)
        self.assertIn("mismatches: 2", out)
        self.assertIn("pre-push: REFUSED", out)

    def test_compile_failure_refused(self):
        rc, out = gate(CHECK_FAILED, LINK_OK, 18407)
        self.assertEqual(rc, 1)
        self.assertIn("mismatches: 1", out)

    def test_lost_match_refused(self):
        rc, out = gate(CHECK_CLEAN, LINK_OK, 18408)
        self.assertEqual(rc, 1)
        self.assertIn("required >= 18408", out)

    def test_link_not_identical_refused(self):
        rc, out = gate(CHECK_CLEAN, LINK_BAD, 18407)
        self.assertEqual(rc, 1)
        self.assertIn("not byte-identical", out)

    def test_missing_cover_line_refused(self):
        rc, out = gate("nothing useful\n", LINK_OK, 0)
        self.assertEqual(rc, 1)
        self.assertIn("no cover line", out)


if __name__ == "__main__":
    unittest.main()
