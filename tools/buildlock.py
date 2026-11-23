"""buildlock.py — the machine's build lock, taken shared one unit at a time by a sweep.

The build lock (AGENTS.md "Build lock") is one file with two tiers. A heavy run (`make check`, `make link`, the
`-fresh` variants) holds it exclusively for its whole run: `flock <file> make check`. A light run (one unit) holds
it shared: `flock -s <file> <cmd>`. A sweep over many units (`tools/check.py --changed-since`, tools/whole_file_rows.py
over several files, `tools/memberize.py --rekey`) is a light run per unit: given the file (`--lock FILE`, by default
`$DW4_BUILD_LOCK`), it takes the file shared around each unit's compile and compare and releases it between units,
so a heavy run waits only for the units in flight and light runs interleave with the sweep. A sweep under a lock
also defaults to at most SWEEP_JOBS workers, so that sharing the machine does not exhaust its memory.

Writer preference. flock(2) grants a shared lock while another shared lock is held, whatever waits for the
exclusive one, so the overlapping units of a sweep's workers would keep a heavy run out until the sweep ends.
Before each unit after its first, a process of the sweep therefore waits while another process has the file open
without holding a lock on it: a heavy run blocked in flock(2), or one polling with LOCK_NB (the agent shell's
builtin `flock` polls). Those are found from /proc/<pid>/fd and the `lock:` lines of /proc/<pid>/fdinfo/<fd>. A
waiter still there after PREFER_SECONDS (one that waits for this run's own caller, say) is not waited for again.

Under make (MAKELEVEL set) `$DW4_BUILD_LOCK` is not read: a make target is a heavy run whose caller holds the file
exclusively (`flock <file> make check`, `tools/apply_names.py --check`), and a shared take would wait for it forever.
For the same reason a sweep is run with the variable and no outer `flock`: under an outer exclusive `flock` its
first unit waits forever (it says so on stderr), and under an outer shared one a heavy run waits for the whole sweep.
"""
import contextlib
import fcntl
import os
import sys
import time

SWEEP_JOBS = 4          # the default worker count of a sweep under the lock (DW4_JOBS or --jobs overrides it)
PREFER_SECONDS = 120    # the longest a unit waits for one process waiting to take the lock
POLL_SECONDS = 0.2      # how often a waiting unit looks again
CLEAR_SECONDS = 0.5     # how long a look that found no waiter stands, for a sweep of many short units


def path(arg=None):
    """The lock file a run takes: `arg` (`--lock`; '' for none), else `$DW4_BUILD_LOCK` outside make, else None."""
    if arg is not None:
        return arg or None
    if os.environ.get("MAKELEVEL"):
        return None
    return os.environ.get("DW4_BUILD_LOCK") or None


def sweep_jobs(lock_path, jobs):
    """The worker count of a sweep: `jobs` (the tool's default), at most SWEEP_JOBS under a lock unless DW4_JOBS
    names the count."""
    if lock_path and not os.environ.get("DW4_JOBS"):
        return min(jobs, SWEEP_JOBS)
    return jobs


def holder(lock_path):
    """A callable giving the context to hold around one unit's compile and compare: the lock file taken shared,
    or nothing when there is no lock."""
    return Lock(lock_path).shared if lock_path else contextlib.nullcontext


def _parent(pid):
    try:
        with open("/proc/%d/stat" % pid) as fh:
            return int(fh.read().rpartition(")")[2].split()[1])
    except (OSError, ValueError, IndexError):
        return None


class Lock:
    """The lock file, taken shared by `shared()`. Made before a sweep forks its workers: each process opens the
    file for itself (a descriptor shared across a fork would share its lock), and the sweep's own processes (this
    one and its children) are no waiters to each other."""

    def __init__(self, lock_path):
        self.path = os.path.abspath(lock_path)
        self.real = os.path.realpath(lock_path)
        self.sweep = os.getpid()
        self.used = None        # the pid that last took the lock: its next unit is not its first
        self.ignored = set()    # (pid, fd) of waiters that outlasted PREFER_SECONDS
        self.clear_until = 0.0  # a look before this found no waiter
        self.noted = None       # the pid that said it waits for the lock

    @contextlib.contextmanager
    def shared(self):
        pid = os.getpid()
        if self.used == pid:
            self.let_writers_in()
        self.used = pid
        fd = os.open(self.path, os.O_RDONLY | os.O_CREAT | os.O_CLOEXEC, 0o666)
        try:
            try:
                fcntl.flock(fd, fcntl.LOCK_SH | fcntl.LOCK_NB)
            except BlockingIOError:
                if self.noted != pid:
                    self.noted = pid
                    print("buildlock: waiting for %s, held exclusively (a heavy run; if this run is itself under "
                          "`flock %s`, that flock is what it waits for: drop it)" % (self.path, self.path),
                          file=sys.stderr, flush=True)
                fcntl.flock(fd, fcntl.LOCK_SH)
            yield
        finally:
            os.close(fd)        # closing the only descriptor of the open file releases its lock

    def let_writers_in(self):
        """Wait while another process waits to take the lock (up to PREFER_SECONDS for each)."""
        start = time.monotonic()
        if start < self.clear_until:
            return
        while True:
            waiting = self.waiters() - self.ignored
            now = time.monotonic()
            if not waiting:
                self.clear_until = now + CLEAR_SECONDS
                return
            if now - start >= PREFER_SECONDS:
                self.ignored |= waiting
                print("buildlock: %s still waits for %s after %d s; not waiting for it again"
                      % (", ".join("pid %d" % waiter for waiter, _fd in sorted(waiting)), self.path, PREFER_SECONDS),
                      file=sys.stderr, flush=True)
                return
            time.sleep(POLL_SECONDS)

    def waiters(self):
        """{(pid, fd)} of the descriptors outside this sweep open on the lock file and holding no lock on it."""
        out = set()
        for name in os.listdir("/proc"):
            if not name.isdigit():
                continue
            pid = int(name)
            try:
                fds = os.listdir("/proc/%d/fd" % pid)
            except OSError:
                continue
            for fd in fds:
                try:
                    if os.readlink("/proc/%d/fd/%s" % (pid, fd)) != self.real:
                        continue
                    with open("/proc/%d/fdinfo/%s" % (pid, fd)) as fh:
                        held = "\nlock:" in fh.read()
                except OSError:
                    continue
                if not held and pid != self.sweep and _parent(pid) != self.sweep:
                    out.add((pid, int(fd)))
        return out
