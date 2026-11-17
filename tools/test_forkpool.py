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


if __name__ == "__main__":
    unittest.main()
