#!/usr/bin/env python3
"""The debt ratchet tracks readability without refusing a byte-matching change."""
import contextlib
import io
import os
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import progress  # noqa: E402


def state(**rises):
    counters = {k: 10 for k, _ in progress.DEBT_COUNTERS}
    counters.update(rises)
    return {"debt": {"counters": counters,
                     "baseline": {k: {"value": 10, "reason": None} for k, _ in progress.DEBT_COUNTERS}}}


def quiet(fn, *args):
    with contextlib.redirect_stdout(io.StringIO()):
        return fn(*args)


class Ratchet(unittest.TestCase):
    def setUp(self):
        folder = tempfile.TemporaryDirectory()
        self.addCleanup(folder.cleanup)
        patch = mock.patch.object(progress, "DEBT_BASELINE", os.path.join(folder.name, "baseline.json"))
        patch.start()
        self.addCleanup(patch.stop)

    def test_readability_counters_may_rise(self):
        d = state(**{k: 99 for k in progress.READABILITY_COUNTERS})
        self.assertEqual(quiet(progress.debt_check, d), 0)

    def test_a_correctness_counter_still_refuses(self):
        d = state(**{"mismatch.functions": 11})
        self.assertEqual(quiet(progress.debt_check, d), 1)

    def test_recording_a_readability_rise_needs_no_reason(self):
        d = state(**{k: 99 for k in progress.READABILITY_COUNTERS})
        self.assertNotEqual(quiet(progress.debt_record, d, None), 1)

    def test_recording_a_correctness_rise_needs_a_reason(self):
        d = state(**{"mismatch.functions": 11})
        self.assertEqual(quiet(progress.debt_record, d, None), 1)

    def test_a_new_reason_keeps_the_earlier_one_and_skips_readability(self):
        import json
        d = state(**{"mismatch.functions": 11, "fun_dat_refs": 12})
        d["debt"]["baseline"]["mismatch.functions"]["reason"] = "first"
        quiet(progress.debt_record, d, "second")
        saved = json.load(open(progress.DEBT_BASELINE))["counters"]
        self.assertEqual(saved["mismatch.functions"], {"value": 11, "reason": "first second"})
        self.assertEqual(saved["fun_dat_refs"], 12)


if __name__ == "__main__":
    unittest.main()
