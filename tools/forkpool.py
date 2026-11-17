"""forkpool.py — run a sweep of tools/check.py or tools/linkgen.py on every core.

Most of an uncached `make check` or `make link` is Python (reading objects, applying relocations,
comparing), not the compiler, so a thread pool keeps about one core busy whatever its size: the threads
take turns on the interpreter. `imap(fn, items, jobs)` runs `fn` in `jobs` worker processes forked from
the caller instead, and yields the results in the order of `items`, as `ThreadPoolExecutor.map` does, so
a report built from them is unchanged.

`fn` may be a closure: the workers are forked once it and `items` exist, so only an item's index goes to
a worker and only the result comes back (results must pickle). A worker's writes to the caller's state
are its own, so the state the caller reads afterwards is named in `shared`: each object there has
`take()`, which returns what this process added since the last call and forgets it, and `merge(taken)`,
which adds that to the caller's copy. A worker takes its state after every item and the caller merges it
before it yields the item's result. `Tally` (counters) and `Memo` (a dict whose new entries travel back)
cover the plain cases; `buildcache.Store` implements the same pair.

The caller must hold no lock and run no other thread when it calls `imap` (a forked child would inherit
the lock held). One job, or one item, runs in the calling process with no fork. The workers use the
caller's scratch folder (tools/cc.py), which is created first, so a temporary file named in a result
outlives the worker.

Each worker grows towards the caller's size as it touches the caller's objects (CPython's reference counts
copy every page it reads), so the worker count is bounded by memory as well as cores: `default_jobs()`
takes the smaller of the core count and what the free memory holds at `DW4_JOB_MB` per worker (500 MB),
after keeping `DW4_RESERVE_MB` (8000 MB) for the rest of the machine. `DW4_JOBS` overrides both. A link
worker measured about 300 MB of its own memory (PSS); unbounded, every core at once once came to about
60 GB, when each result still carried its whole unit's undefined symbols (tools/linkgen.py).
"""
import multiprocessing
import os

import cc

_TASK = None


def _available_mb():
    try:
        with open("/proc/meminfo") as fh:
            for line in fh:
                if line.startswith("MemAvailable:"):
                    return int(line.split()[1]) // 1024
    except OSError:
        pass
    return None


def default_jobs():
    """Worker processes for a sweep: DW4_JOBS if set, else the cores the free memory can hold."""
    if os.environ.get("DW4_JOBS"):
        return max(1, int(os.environ["DW4_JOBS"]))
    cores = os.cpu_count() or 1
    available = _available_mb()
    if available is None:
        return cores
    per_job = int(os.environ.get("DW4_JOB_MB", "500"))
    reserve = int(os.environ.get("DW4_RESERVE_MB", "8000"))
    return max(1, min(cores, (available - reserve) // per_job))


def _start():
    for state in _TASK[2]:
        state.take()        # what the caller already held is the caller's, not this worker's


def _run(index):
    fn, items, shared = _TASK
    result = fn(items[index])
    return result, [state.take() for state in shared]


def imap(fn, items, jobs, shared=()):
    """Yield fn(item) for every item, in order, computed in up to `jobs` forked processes."""
    global _TASK
    items = list(items)
    if jobs <= 1 or len(items) <= 1:
        yield from map(fn, items)
        return
    if _TASK is not None:
        raise RuntimeError("forkpool.imap is not reentrant")
    cc.scratch_dir()
    _TASK = (fn, items, tuple(shared))
    try:
        with multiprocessing.get_context("fork").Pool(min(jobs, len(items)), initializer=_start) as pool:
            for result, taken in pool.imap(_run, range(len(items))):
                for state, part in zip(shared, taken):
                    state.merge(part)
                yield result
    finally:
        _TASK = None


class Tally(dict):
    """Counters: `take()` returns them and resets them to zero; `merge` adds."""

    def take(self):
        taken = dict(self)
        for key in self:
            self[key] = 0
        return taken

    def merge(self, taken):
        for key, value in taken.items():
            self[key] = self.get(key, 0) + value


class Memo(dict):
    """A dict whose entries set by item assignment since the last `take()` travel back to the caller."""

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._new = []

    def __setitem__(self, key, value):
        super().__setitem__(key, value)
        self._new.append(key)

    def take(self):
        taken = [(key, self[key]) for key in dict.fromkeys(self._new) if key in self]
        self._new = []
        return taken

    def merge(self, taken):
        self.update(taken)
