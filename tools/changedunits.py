"""changedunits.py — the translation units a change since a git revision reaches, for `check.py --changed-since`.

A change to one header invalidates every cached check result (each key carries a digest of all of `src/`'s
and `include/`'s headers, tools/buildcache.py), so after a declaration move a plain `make check` recompiles
everything. `check.py --changed-since REV` checks only the units the change can reach instead: `changed_files`
lists the files that differ from REV in the working tree (committed since, staged or not, and new files git
does not ignore), and `affected` keeps the sources among them or whose `#include`s reach one of them,
transitively. Resolution over-approximates the compiler's: a quoted or angled name is tried against the
includer's folder, the repository root, `include/` and `src/` (the folders the unit profiles pass with `-I`),
and every candidate that exists is followed, so a unit is never left out because an include resolved
elsewhere; a deleted header still reaches the units that name it.

Only sources and headers are followed. The tables in config/ and the tool modules check.py runs (its imports and
the EE GCC driver's, as tools/buildcache.py digests them) reach every unit, and a kernel patch's source
(tools/kpatch.py) reaches its owner through a built `.inc`; a change to one of these is reported by
`not_followed` and needs the full `make check`.
"""
import os
import re
import subprocess

import buildcache
import kpatch

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*[<"]([^>"\n]+)[>"]', re.M)
# where a change reaches compiled results the include graph cannot place
UNFOLLOWED = ("config/", os.path.relpath(kpatch.PATCH_DIR, ROOT) + "/")


def checking_tools():
    """{repository-relative path} of the tool modules whose source is part of every check result."""
    return {os.path.relpath(path, ROOT) for entry in ("check.py", "eegcc_compile.py")
            for path in buildcache.module_closure(entry)}


def git(root, *args):
    r = subprocess.run(("git",) + args, cwd=root, capture_output=True, text=True)
    if r.returncode:
        raise ValueError("git %s: %s" % (" ".join(args), (r.stderr or r.stdout).strip()))
    return r.stdout


def changed_files(ref, root=ROOT):
    """{repository-relative path} of the files that differ between `ref` and the working tree: changed or
    deleted since (committed, staged or not; a rename as both its paths) and untracked files git does not ignore."""
    out = git(root, "diff", "--name-only", "--no-renames", "-z", ref, "--")
    out += git(root, "ls-files", "--others", "--exclude-standard", "-z")
    return {os.path.normpath(p) for p in out.split("\0") if p}


def not_followed(changed):
    """The changed files whose effect on the results the include graph cannot place, sorted."""
    tools = checking_tools()
    return sorted(p for p in changed if p.startswith(UNFOLLOWED) or p in tools)


def _includes(path, root):
    """[repository-relative candidate path] of each name `path`'s `#include` lines spell."""
    try:
        with open(os.path.join(root, path), errors="replace") as fh:
            text = fh.read()
    except OSError:
        return []
    bases = (os.path.dirname(path), "", "include", "src")
    return [os.path.normpath(os.path.join(base, name)) for name in _INCLUDE.findall(text) for base in bases]


def affected(sources, changed, root=ROOT):
    """The `sources` (repository-relative) that are in `changed` or include one of its files, directly or
    through other files."""
    graph, todo = {}, list(sources)
    while todo:
        path = todo.pop()
        if path in graph:
            continue
        graph[path] = _includes(path, root)
        todo += [inc for inc in graph[path] if inc not in graph and os.path.isfile(os.path.join(root, inc))]
    included_by = {}
    for path, incs in graph.items():
        for inc in incs:
            included_by.setdefault(inc, set()).add(path)
    reached, todo = set(), [p for p in changed if p in graph or p in included_by]
    while todo:
        path = todo.pop()
        if path in reached:
            continue
        reached.add(path)
        todo += included_by.get(path, ())
    return {path for path in sources if path in reached}
