"""Tests for tools/forkpool.py: ordered results from forked workers, and the state they send back."""
import os
import pickle
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import buildcache  # noqa: E402
import cc  # noqa: E402
import forkpool  # noqa: E402
import verify  # noqa: E402


class Imap(unittest.TestCase):
    def test_results_keep_the_order_of_the_items_and_come_from_other_processes(self):
        offset = 7      # a closure: only indices and results cross to the workers

        def work(n):
            return n + offset, os.getpid()

        got = list(forkpool.imap(work, range(40), 4))
        self.assertEqual([value for value, _pid in got], [n + 7 for n in range(40)])
        self.assertNotIn(os.getpid(), {pid for _value, pid in got})

    def test_one_job_runs_in_this_process(self):
        got = list(forkpool.imap(lambda n: (n, os.getpid()), range(5), 1))
        self.assertEqual(got, [(n, os.getpid()) for n in range(5)])

    def test_a_worker_exception_reaches_the_caller(self):
        def work(n):
            if n == 3:
                raise ValueError("unit 3")
            return n

        with self.assertRaisesRegex(ValueError, "unit 3"):
            list(forkpool.imap(work, range(6), 3))

    def test_workers_share_the_callers_scratch_folder(self):
        def where(_n):
            return cc.scratch_dir()

        self.assertEqual(set(forkpool.imap(where, range(6), 3)), {cc.scratch_dir()})


class Shared(unittest.TestCase):
    def test_tally_and_memo_writes_come_back_once(self):
        tally = forkpool.Tally(seen=0, odd=0)
        memo = forkpool.Memo(before=-1)        # the caller's own entries are not sent back

        def work(n):
            tally["seen"] += 1
            if n % 2:
                tally["odd"] += 1
            memo[n] = n * n
            return n

        self.assertEqual(list(forkpool.imap(work, range(30), 4, (tally, memo))), list(range(30)))
        self.assertEqual(dict(tally), {"seen": 30, "odd": 15})
        self.assertEqual(memo, dict({n: n * n for n in range(30)}, before=-1))

    def test_a_later_sweep_sees_what_an_earlier_one_sent_back(self):
        memo = forkpool.Memo()
        list(forkpool.imap(lambda n: memo.__setitem__(n, "built %d" % n), range(8), 4, (memo,)))
        self.assertEqual(list(forkpool.imap(lambda n: memo.get(n), range(8), 4, (memo,))),
                         ["built %d" % n for n in range(8)])

    def test_store_take_and_merge(self):
        with tempfile.TemporaryDirectory() as tmp, mock.patch.object(buildcache, "CACHE_DIR", tmp):
            store = buildcache.Store("forkpool-test")
            store.entries = {"hit": {"v": 1}}

            def work(n):
                if store.get("hit" if n == 0 else "miss%d" % n) is None:
                    store.put("k%d" % n, {"v": n})
                return n

            list(forkpool.imap(work, range(6), 3, (store,)))
            self.assertEqual((store.hits, store.misses), (1, 5))
            self.assertEqual(store.used, dict({"hit": {"v": 1}}, **{"k%d" % n: {"v": n} for n in range(1, 6)}))

    def test_the_unit_result_marker_unpickles_as_itself(self):
        self.assertIs(pickle.loads(pickle.dumps(verify._NOT_SHARED)), verify._NOT_SHARED)


class DefaultJobs(unittest.TestCase):
    def jobs(self, available_mb, cores=16, **env):
        with mock.patch.dict(os.environ, {k: v for k, v in env.items()}, clear=False), \
                mock.patch.object(forkpool, "_available_mb", return_value=available_mb), \
                mock.patch.object(forkpool.os, "cpu_count", return_value=cores):
            for name in ("DW4_JOBS", "DW4_JOB_MB", "DW4_RESERVE_MB"):
                if name not in env:
                    os.environ.pop(name, None)
            return forkpool.default_jobs()

    def test_memory_not_cores_bounds_the_workers(self):
        # 6 GB free: (6000 - 3000) // 500 = 6, not 16
        self.assertEqual(self.jobs(6000, DW4_RESERVE_MB="3000"), 6)

    def test_a_32gb_host_runs_every_core(self):
        # 26 GB free: (26000 - 8000) // 500 = 36, so the 16 cores bound it
        self.assertEqual(self.jobs(26000), 16)

    def test_low_memory_still_runs_one_worker(self):
        self.assertEqual(self.jobs(5000), 1)

    def test_cores_bound_a_large_host(self):
        self.assertEqual(self.jobs(512000, cores=8), 8)

    def test_dw4_jobs_overrides(self):
        self.assertEqual(self.jobs(26000, DW4_JOBS="5"), 5)


if __name__ == "__main__":
    unittest.main()
