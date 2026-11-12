"""buildcache.py — a content-addressed result cache for tools/check.py and tools/linkgen.py.

`make check` and `make link` recompute everything every run (about 47 and 70 minutes), yet each answer is a pure function of what
it was computed from: the function's source text, the headers it includes, the flags, the compiler, the retail bytes and the
tool logic that interprets them. This module hashes exactly that and remembers the answer, so a rerun only redoes what changed.

Safety rules (a cache that can hide a regression is worse than none):

  * the key covers EVERY input listed above; anything not provably irrelevant is included, and a change to any of it changes every
    key (a coarse miss, never a stale hit): the whole include/ tree and every non-C file under src/, the compiler tree and the
    wibo binary, the retail ELF, the config tables, and the source of every tool module the cache's user imports;
  * only definite answers are stored (a compile failure is never cached), and a stored hit is re-validated by its user where it
    can be (linkgen checks the object file's own digest);
  * `--no-cache` and `DW4_NOCACHE=1` bypass it entirely, and nothing is written in that mode. Run one uncached pass before
    publishing a milestone: tools/check.py --no-cache.

The store is a JSON file under build/cache/ (untracked). A run rewrites it with only the entries that run used, so it cannot grow
without bound.
"""
import hashlib
import json
import os
import re
import tempfile
import threading

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CACHE_DIR = os.path.join(ROOT, "build", "cache")
TOOLS = os.path.dirname(os.path.abspath(__file__))
VERSION = 1

_memo = {}
_memo_lock = threading.Lock()


def enabled(no_cache_flag=False):
    """False when the caller passed --no-cache or DW4_NOCACHE is set to 1/true/yes."""
    if no_cache_flag:
        return False
    return os.environ.get("DW4_NOCACHE", "").lower() not in ("1", "true", "yes")


def sha(*parts):
    """Hex digest over parts (str is UTF-8 encoded; each part is length-prefixed so boundaries cannot be forged)."""
    h = hashlib.sha256()
    for p in parts:
        b = p if isinstance(p, bytes) else str(p).encode("utf-8")
        h.update(len(b).to_bytes(8, "little"))
        h.update(b)
    return h.hexdigest()


def file_sha(path):
    """Digest of one file's bytes ('missing' for an absent file), memoised per process."""
    with _memo_lock:
        hit = _memo.get(("f", path))
    if hit is not None:
        return hit
    try:
        with open(path, "rb") as fh:
            digest = hashlib.sha256(fh.read()).hexdigest()
    except OSError:
        digest = "missing"
    with _memo_lock:
        _memo[("f", path)] = digest
    return digest


def fresh_sha(path):
    """Digest of one file's bytes, never memoised (used to validate an artifact that may have changed on disk)."""
    try:
        with open(path, "rb") as fh:
            return hashlib.sha256(fh.read()).hexdigest()
    except OSError:
        return "missing"


# What a digest of src/ leaves out when it stands for "the headers every compile can read": the
# translation units themselves (each is keyed by its own text) and documentation (a README or a
# licence file is no compiler input, so editing one must not invalidate every compiled result).
# Everything else under src/ is treated as a header.
NOT_HEADERS = (".c", ".cpp", ".s", ".md", "LICENSE", "COPYRIGHT", "README")


def tree_sha(root, skip_ext=()):
    """Digest of every file under `root` (relative path + bytes), skipping names that end in one of skip_ext."""
    key = ("t", root, tuple(skip_ext))
    with _memo_lock:
        hit = _memo.get(key)
    if hit is not None:
        return hit
    h = hashlib.sha256()
    for dirpath, dirs, files in os.walk(root):
        dirs.sort()
        for f in sorted(files):
            if f.endswith(tuple(skip_ext)):
                continue
            p = os.path.join(dirpath, f)
            h.update(os.path.relpath(p, root).encode())
            h.update(file_sha(p).encode())
    digest = h.hexdigest()
    with _memo_lock:
        _memo[key] = digest
    return digest


def module_closure(entry):
    """tools/ modules `entry` imports, transitively (by `import x` / `from x import`), including itself, as a sorted list of paths."""
    seen, todo = set(), [os.path.splitext(os.path.basename(entry))[0]]
    while todo:
        name = todo.pop()
        path = os.path.join(TOOLS, name + ".py")
        if name in seen or not os.path.exists(path):
            continue
        seen.add(name)
        for m in re.finditer(r"^\s*(?:import|from)\s+([A-Za-z_]\w*)", open(path).read(), re.M):
            todo.append(m.group(1))
    return sorted(os.path.join(TOOLS, n + ".py") for n in seen)


def tools_sha(entry):
    """Digest of the source of `entry` and everything in tools/ it imports."""
    return sha(*[os.path.basename(p) + file_sha(p) for p in module_closure(entry)])


def unit_profile_sha(va, flags_default, mwcc_default, unit_objects=None, units=None, unit_flags=None,
                     unit_compilers=None, symbols=None):
    """Digest of the build profile that applies to the function at `va`: the unit-objects group it belongs to (owner, emitted
    bodies, externals, duplicates, exception tables) and, for the owner and every member and duplicate of that group, the
    unit profile row of config/SLUS-20836/units.tsv (compiler path and content digest, flags, exception mode, status), the per-function
    override rows and what they resolve to. Mirrors what tools/verify.py and tools/linkgen.py look up by address
    (tools/unitprofiles.resolve); a resolution error is part of the digest too.

    The digest depends on the group, not on which member asks, so it is computed once per group and set of loaded
    tables: a library-sized group has thousands of members, and resolving every member for each of them is quadratic."""
    import unitobjects
    import unitprofiles
    group = unitobjects.group_for(va, unit_objects)
    if group is None:
        return _profile_sha(None, va, flags_default, mwcc_default, units, unit_flags, unit_compilers, symbols)
    # the tables resolve() reads; a reloaded table (the tests clear the caches) is a new object, so a new key
    tables = (unitprofiles.load(units) if units is not None
              else unitprofiles.load(unitprofiles.units_path(symbols) or "/nonexistent/units.tsv"),
              unitprofiles.unitflags.load_rows(unit_flags or unitprofiles.unitflags.DEFAULT_PATH),
              unitprofiles.unitcompilers.load_rows(unit_compilers or unitprofiles.unitcompilers.DEFAULT_PATH))
    key = ("g", id(group), tuple(map(id, tables)), flags_default, mwcc_default, units, unit_flags, unit_compilers, symbols)
    with _memo_lock:
        hit = _memo.get(key)
    # the held objects keep their ids from being reused while the entry lives
    if hit is not None and hit[0] is group and all(a is b for a, b in zip(hit[1], tables)):
        return hit[2]
    digest = _profile_sha(group, group.owner, flags_default, mwcc_default, units, unit_flags, unit_compilers, symbols)
    with _memo_lock:
        _memo[key] = (group, tables, digest)
    return digest


def _profile_sha(group, owner, flags_default, mwcc_default, units, unit_flags, unit_compilers, symbols):
    import unitprofiles
    members = set(group.members) | {address for _name, address in group.duplicates} if group else {owner}
    parts = [repr(group)]
    for m in sorted(members | {owner}):
        parts.append("%x %s" % (m, unitprofiles.profile_key(m, flags_default, mwcc_default, units=units,
                                                           unit_flags=unit_flags, unit_compilers=unit_compilers,
                                                           symbols=symbols)))
        try:
            res = unitprofiles.resolve(m, flags_default, mwcc_default, units=units, unit_flags=unit_flags,
                                       unit_compilers=unit_compilers, symbols=symbols)
        except ValueError:
            continue
        for profile in (res.profile, res.override):
            if profile is not None:
                parts.append("compiler-bytes %s %s" % (profile.compiler, file_sha(profile.compiler)))
    return sha(*parts)


def build_inputs_sha(elf, symbols, unit_objects=None, extra_files=()):
    """Digest of what every compile/verify result depends on besides the function's own text."""
    cfg = os.path.join(ROOT, "config")
    parts = [
        "elf", file_sha(elf),
        "symbols", file_sha(symbols),
        "include", tree_sha(os.path.join(ROOT, "include")),
        "src-headers", tree_sha(os.path.join(ROOT, "src"), skip_ext=NOT_HEADERS),
        "compilers", tree_sha(os.path.join(ROOT, "local", "mwcps2")),
        # the Sony EE GCCs the pinned library units compile with (tools/eegcc_compile.py), each with its own
        # assembler: the whole trees, like mwcps2
        "ee-gcc", tree_sha(os.path.join(ROOT, "local", "ee-gcc2.96")),
        "ee-gcc-2.9", tree_sha(os.path.join(ROOT, "local", "ee-gcc2.9-991111-01")),
        "ee-gcc-2.9-as210", tree_sha(os.path.join(ROOT, "local", "ee-gcc2.9-991111-01-as210")),
        "wibo", file_sha(os.path.join(ROOT, "local", "wibo")),
    ]
    # the profile tables (units.tsv, the per-function compiler and flag overrides, unit-objects) are NOT hashed whole: adding a
    # row for one unit must not invalidate the others, so each result's key carries its own unit's rows instead
    # (unit_profile_sha). The tables every unit's resolution reads are hashed whole: the switch tables, the layout, the retail
    # exception records and the compiler runtime addresses.
    for name in ("jumptables.txt", "layout.txt", "exceptions.txt", "compiler-runtime-symbols.tsv", "data-names.tsv"):
        parts += [name, file_sha(os.path.join(cfg, name))]
    for p in extra_files:
        parts += [os.path.basename(p), file_sha(p)]
    return sha(*parts)


class Store:
    """key -> JSON value, loaded once, written once. Thread-safe. A disabled store never reads or writes."""

    def __init__(self, name, active=True):
        self.path = os.path.join(CACHE_DIR, name + ".json")
        self.active = active
        self.entries = {}
        self.used = {}
        self.hits = self.misses = 0
        self._lock = threading.Lock()
        if active:
            try:
                with open(self.path) as fh:
                    blob = json.load(fh)
                if blob.get("version") == VERSION:
                    self.entries = blob.get("entries", {})
            except (OSError, ValueError):
                self.entries = {}

    def get(self, key):
        if not self.active:
            return None
        with self._lock:
            value = self.entries.get(key)
            if value is None:
                self.misses += 1
                return None
            self.hits += 1
            self.used[key] = value
            return value

    def put(self, key, value):
        if not self.active:
            return
        with self._lock:
            self.used[key] = value

    def save(self, prune=False):
        """Write the store back. By default the entries this run used are merged over what was
        loaded, so a partial run (a `--unit-range`, a `--cover-limit`, the build-option tests driving the
        tools on a synthetic tree) never discards the whole-tree answers; a complete whole-tree run
        passes `prune=True` to drop entries nothing used any more."""
        if not self.active:
            return
        os.makedirs(CACHE_DIR, exist_ok=True)
        entries = self.used if prune else {**self.entries, **self.used}
        fd, tmp = tempfile.mkstemp(dir=CACHE_DIR, suffix=".tmp")
        with os.fdopen(fd, "w") as fh:
            json.dump({"version": VERSION, "entries": entries}, fh, separators=(",", ":"))
        os.replace(tmp, self.path)

    def summary(self, what):
        if not self.active:
            return "cache : off (%s recomputed)" % what
        return "cache : %d hits, %d recomputed (%s)" % (self.hits, self.misses, what)
