"""tools/buildlock.py: a sweep takes the build lock shared one unit at a time and lets a waiting heavy run in."""
import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import signal
import struct
import subprocess
import sys
import tempfile
import time
import unittest
from unittest import mock

import buildlock
import check
import unitobjects
import verify
from test_data_only_units import COMPILER, FLAGS, image_with

# a heavy run: blocks for the lock exclusively (or polls for it, as the agent shell's builtin `flock` does), says
# when it holds it, holds it a moment and says when it is done
HEAVY = r"""
import fcntl, os, sys, time
path, ready, log, poll = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4] == "poll"
fd = os.open(path, os.O_RDONLY | os.O_CREAT)
open(ready, "w").close()
while True:
    try:
        fcntl.flock(fd, fcntl.LOCK_EX | (fcntl.LOCK_NB if poll else 0))
        break
    except BlockingIOError:
        time.sleep(0.02)
with open(log, "a") as fh:
    fh.write("got ")
time.sleep(0.3)
with open(log, "a") as fh:
    fh.write("done")
os.close(fd)
"""

# a light run: holds the lock shared for a second
LIGHT = r"""
import fcntl, os, sys, time
fd = os.open(sys.argv[1], os.O_RDONLY | os.O_CREAT)
fcntl.flock(fd, fcntl.LOCK_SH)
open(sys.argv[2], "w").close()
time.sleep(1)
"""

# a process with the lock file open that never locks it
IDLE = r"""
import os, sys, time
fd = os.open(sys.argv[1], os.O_RDONLY | os.O_CREAT)
open(sys.argv[2], "w").close()
time.sleep(10)
"""

PROBE = r"""
import fcntl, os, sys
fd = os.open(sys.argv[1], os.O_RDONLY | os.O_CREAT)
try:
    fcntl.flock(fd, (fcntl.LOCK_SH if sys.argv[2] == "shared" else fcntl.LOCK_EX) | fcntl.LOCK_NB)
except BlockingIOError:
    sys.exit(1)
"""


def can_take(path, mode):
    """Whether another process could take the lock file `mode` ("shared" or "exclusive") now."""
    return subprocess.run([sys.executable, "-c", PROBE, path, mode]).returncode == 0


class Other:
    """A script run as another agent's process: started through a shell, so that it is no child of this
    process (whose children are the sweep's own workers, never waiters). `ready` is the file it writes once it
    has the lock file open (or holds it)."""

    def __init__(self, case, code, path, *args):
        self.ready = os.path.join(case.folder, "ready%d" % time.monotonic_ns())
        self.log = self.ready + ".log"
        self.process = subprocess.Popen(["sh", "-c", '"$@" & wait', "sh", sys.executable, "-c", code, path,
                                         *(arg.format(log=self.log, ready=self.ready) for arg in args)],
                                        start_new_session=True)
        case.addCleanup(self.stop)
        deadline = time.monotonic() + 10
        while not os.path.exists(self.ready):
            if time.monotonic() > deadline:
                raise AssertionError("the other process never started")
            time.sleep(0.01)

    def state(self):
        return open(self.log).read() if os.path.exists(self.log) else ""

    def wait(self):
        self.process.wait(timeout=30)

    def stop(self):
        with contextlib.suppress(ProcessLookupError):
            os.killpg(self.process.pid, signal.SIGKILL)
        self.process.wait()


def heavy(case, path, poll=False):
    return Other(case, HEAVY, path, "{ready}", "{log}", "poll" if poll else "block")


class Options(unittest.TestCase):
    def test_the_lock_file(self):
        with mock.patch.dict(os.environ, {"DW4_BUILD_LOCK": "/tmp/env.lock"}, clear=False):
            os.environ.pop("MAKELEVEL", None)
            self.assertEqual(buildlock.path(), "/tmp/env.lock")
            self.assertEqual(buildlock.path("/tmp/arg.lock"), "/tmp/arg.lock")
            self.assertIsNone(buildlock.path(""))
            # a make target is a heavy run: its caller holds the file exclusively, and a shared take would deadlock
            os.environ["MAKELEVEL"] = "1"
            self.assertIsNone(buildlock.path())
            self.assertEqual(buildlock.path("/tmp/arg.lock"), "/tmp/arg.lock")

    def test_a_sweep_under_the_lock_runs_few_workers(self):
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("DW4_JOBS", None)
            self.assertEqual(buildlock.sweep_jobs("/tmp/x.lock", 16), buildlock.SWEEP_JOBS)
            self.assertEqual(buildlock.sweep_jobs("/tmp/x.lock", 2), 2)
            self.assertEqual(buildlock.sweep_jobs(None, 16), 16)
            os.environ["DW4_JOBS"] = "12"
            self.assertEqual(buildlock.sweep_jobs("/tmp/x.lock", 12), 12)


class Lock(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="dw4-buildlock-")
        self.addCleanup(temp.cleanup)
        self.folder = temp.name
        self.path = os.path.join(self.folder, "build.lock")
        self.lock = buildlock.Lock(self.path)

    def test_a_unit_holds_it_shared_and_lets_it_go(self):
        with self.lock.shared():
            self.assertTrue(can_take(self.path, "shared"))
            self.assertFalse(can_take(self.path, "exclusive"))
        self.assertTrue(can_take(self.path, "exclusive"))

    def check_heavy_run_comes_between_units(self, poll):
        with self.lock.shared():
            other = heavy(self, self.path, poll)
            time.sleep(0.3)
            self.assertEqual(other.state(), "", "the heavy run must wait for the unit in flight")
            self.assertEqual(len(self.lock.waiters()), 1)
        with contextlib.redirect_stderr(io.StringIO()), self.lock.shared():
            # the next unit waited for the heavy run to take the lock, and the lock for it to finish
            self.assertEqual(other.state(), "got done")
        other.wait()

    def test_a_blocked_heavy_run_comes_between_units(self):
        self.check_heavy_run_comes_between_units(poll=False)

    def test_a_polling_heavy_run_comes_between_units(self):
        self.check_heavy_run_comes_between_units(poll=True)

    def test_a_first_unit_does_not_wait_for_writers(self):
        # one-unit runs (and each worker's first unit) take the lock as `flock -s` would: a light run holds it,
        # a heavy run waits, and the unit gets in beside the light run
        Other(self, LIGHT, self.path, "{ready}")
        other = heavy(self, self.path, poll=True)
        started = time.monotonic()
        with self.lock.shared():
            self.assertLess(time.monotonic() - started, 0.5)
            self.assertEqual(other.state(), "")

    def test_a_waiter_that_never_takes_it_is_waited_for_once(self):
        # a process that has the file open and never locks it (or that waits for this run's own caller)
        idle = Other(self, IDLE, self.path, "{ready}")
        self.assertEqual(len(self.lock.waiters()), 1)
        with self.lock.shared():
            pass
        with mock.patch.object(buildlock, "PREFER_SECONDS", 0.5), contextlib.redirect_stderr(io.StringIO()) as err:
            started = time.monotonic()
            with self.lock.shared():
                pass
            self.assertGreaterEqual(time.monotonic() - started, 0.5)
            self.assertIn("still waits for %s" % self.path, err.getvalue())
            self.lock.clear_until = 0.0
            started = time.monotonic()
            with self.lock.shared():
                pass
            self.assertLess(time.monotonic() - started, 0.5)
        idle.stop()


class Sweep(unittest.TestCase):
    """tools/check.py over three data-only units under --lock: each unit's compile and compare holds the lock
    shared, a heavy run arriving during the first unit comes in before the second, and the report is the one an
    unlocked run prints."""
    DATA = (0x190000, 0x190100, 0x190200)

    def setUp(self):
        if not Path(COMPILER).exists():
            self.skipTest("private compiler unavailable")
        if not shutil.which("mipsel-linux-gnu-objcopy"):
            self.skipTest("GNU MIPS tools unavailable")
        temp = tempfile.TemporaryDirectory(prefix="dw4-buildlock-sweep-")
        self.addCleanup(temp.cleanup)
        self.folder = temp.name
        self.root = Path(temp.name)
        (self.root / "src" / "lib").mkdir(parents=True)
        (self.root / "asm").mkdir()
        self.lock = str(self.root / "build.lock")
        symbols = self.root / "symbols.txt"
        symbols.write_text("00180000 000040 fixture_code\n")
        image = self.root / "fixture.elf"
        image.write_bytes(image_with({0x180000: bytes(64), **{va: struct.pack("<4i", 1, 2, 3, -1) for va in self.DATA}},
                                     self.DATA[-1] + 0x100))
        registry, rows = self.root / "objects.json", {}
        compilers = [line for line in Path(verify.ROOT, "config", "SLUS-20836", "units.tsv").read_text().splitlines(True)
                     if line.startswith("@compiler\tee-gcc-2.9\t")]
        lines = [compilers[0]]
        for n, va in enumerate(self.DATA):
            (self.root / "src" / "lib" / f"part{n}.c").write_text(
                f"int part{n}_table[3] = {{1, 2, 3}};\nstatic int part{n}_state = -1;\n")
            rows[hex(va)] = {"whole_file": True, "data": {"@data": hex(va)}, "stripped": [f"part{n}_dropped"],
                             "source": f"lib/part{n}.c"}
            lines.append("0x%08x\t0x%08x\tlib_part%d\tee-gcc-2.9\t%s\toff\t-\twhole file\n"
                         % (va, va + 16, n, " ".join(FLAGS)))
        registry.write_text(json.dumps(rows))
        units = self.root / "units.tsv"
        units.write_text("".join(lines))
        unitobjects.load.cache_clear()
        self.common = ["--elf", str(image), "--symbols", str(symbols), "--unit-objects", str(registry),
                       "--units", str(units), "--no-cache", "--src", str(self.root / "src"),
                       "--asm", str(self.root / "asm")]

    def run_check(self, *argv):
        out = io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()), \
                mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("DW4_BUILD_LOCK", None)
            rc = check.main([*argv, *self.common])
        return rc, out.getvalue()

    def test_each_unit_holds_the_lock_shared_and_a_heavy_run_comes_between(self):
        rc, unlocked = self.run_check("--jobs", "1")
        self.assertEqual(rc, 0, unlocked)
        self.assertIn("data-only: 3 units the retail linker kept the data of and no function, 3 match", unlocked)

        real, seen, others = verify.verify_one, [], []

        def unit(va, *args, **kwargs):
            # inside the unit: the lock is held shared (a light run gets in, a heavy one does not)
            seen.append((va, can_take(self.lock, "shared"), can_take(self.lock, "exclusive"),
                         others[0].state() if others else None))
            if not others:
                # polling, as the agent shell's `flock` does: only the sweep's writer preference lets it in
                others.append(heavy(self, self.lock, poll=True))
                time.sleep(0.3)
            return real(va, *args, **kwargs)

        with mock.patch.object(verify, "verify_one", unit):
            rc, locked = self.run_check("--jobs", "1", "--lock", self.lock)
        others[0].wait()
        self.assertEqual(rc, 0, locked)
        self.assertEqual(locked, unlocked)
        # the heavy run waited for the first unit only, and ran to its end before the second
        self.assertEqual(seen, [(self.DATA[0], True, False, None), (self.DATA[1], True, False, "got done"),
                                (self.DATA[2], True, False, "got done")])
        self.assertTrue(can_take(self.lock, "exclusive"))

    def test_forked_workers_give_the_same_report(self):
        rc, unlocked = self.run_check("--jobs", "1")
        rc2, locked = self.run_check("--jobs", "2", "--lock", self.lock)
        self.assertEqual((rc, rc2), (0, 0), locked)
        self.assertEqual(locked, unlocked)

    def test_one_unit_by_its_key_holds_the_lock(self):
        real, seen = verify.verify_one, []

        def unit(va, *args, **kwargs):
            seen.append(can_take(self.lock, "exclusive"))
            return real(va, *args, **kwargs)

        with mock.patch.object(verify, "verify_one", unit):
            rc, out = self.run_check("--function", hex(self.DATA[0]), "--lock", self.lock,
                                     "--cand", str(self.root / "src" / "lib" / "part0.c"))
        self.assertEqual(rc, 0, out)
        self.assertEqual(seen, [False])


if __name__ == "__main__":
    unittest.main()
