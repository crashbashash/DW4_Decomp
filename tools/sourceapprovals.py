#!/usr/bin/env python3
"""sourceapprovals.py — owner approval of inline `asm` and `volatile` in C and C++ sources.

An `asm` statement or a `volatile` passes the byte check whether or not plain C could have produced
the same bytes, so either can force a match the original source did not have. A function using one
counts as matched only once the project owner has reviewed the evidence and added a row to
config/source-approvals.tsv. Until then `make check` files it as `unapproved`: its source stays and
links byte-identically, but it counts in no matched figure (docs/engine/source-approvals.md).

A row is `kind <TAB> symbol <TAB> count <TAB> evidence`: `asm` or `volatile`, the function, how many
uses reach it, and the anchor of the evidence in docs/engine/source-approvals.md. The count voids the
approval when another use appears. `sync` and `ei` need no row, since C cannot spell them, and stock
source under src/third_party/ is out of scope, as it is for tools/inline_asm.py.

  python3 tools/sourceapprovals.py --list     # the unapproved queue, for the owner to review
  python3 tools/sourceapprovals.py --stale    # rows whose function no longer uses what they approve
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
import asmsources  # noqa: E402
import inline_asm  # noqa: E402
import units  # noqa: E402

TABLE = os.path.join(ROOT, "config", "source-approvals.tsv")
INCLUDE = os.path.join(ROOT, "include")
KINDS = ("asm", "volatile")
_STRING = re.compile(r'"(?:\\.|[^"\\\n])*"')
_VOLATILE = re.compile(r"\b(?:__volatile__|volatile)\b")
_INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)
_WORD = re.compile(r"[A-Za-z_]\w*")
_USE_WORD = re.compile(r"asm|volatile")
_header_cache = {}


def load(path=TABLE):
    """{(kind, symbol): (count, evidence)} from the approval table."""
    rows = {}
    if not os.path.exists(path):
        return rows
    for n, line in enumerate(open(path), 1):
        if not line.strip() or line.startswith("#"):
            continue
        cols = [c.strip() for c in line.rstrip("\n").split("\t")]
        if len(cols) != 4 or not all(cols) or cols[0] not in KINDS or not cols[2].isdigit() or int(cols[2]) < 1:
            raise ValueError("%s:%d: expected `asm|volatile<TAB>symbol<TAB>count<TAB>evidence`" % (path, n))
        key = (cols[0], cols[1])
        if key in rows:
            raise ValueError("%s:%d: %s %s is listed twice" % (path, n, cols[0], cols[1]))
        rows[key] = (int(cols[2]), cols[3])
    return rows


def in_scope(path):
    rel = os.path.relpath(os.path.abspath(path), ROOT)
    return not asmsources.is_assembly(path) and "third_party" not in rel.split(os.sep)


def _blank(text):
    """The text with comments and string contents gone, so only code is counted. `asm("nop")` keeps
    its parentheses, and what its string held decides whether it is hardware, so the strings of asm
    statements are read before this."""
    return _STRING.sub('""', inline_asm.blank_comments(text))


def _count(text):
    """(asm statements C could spell, volatile keywords) in a source text."""
    asm = sum(1 for _s, _e, body in inline_asm.statements(text) if not inline_asm.is_hardware(body))
    return asm, len(_VOLATILE.findall(_blank(text)))


def _reachable_text(text, name):
    """The text of function `name` with every other top-level definition blanked, except the inline
    helpers it reaches by name: those are compiled into it."""
    defs = units.definitions(text)
    if len(defs) <= 1:
        return text
    bodies = {nm: (s, e) for nm, s, e in defs}
    if name not in bodies:
        raise KeyError("%s is not defined here" % name)
    keep, pending = {name}, [name]
    while pending:
        s, e = bodies[pending.pop()]
        for word in set(_WORD.findall(_blank(text[s:e]))):
            if word in bodies and word not in keep:
                s2, _e2 = bodies[word]
                if re.search(r"\binline\b", text[s2:text.index("{", s2)]):
                    keep.add(word)
                    pending.append(word)
    out = list(text)
    for nm, s, e in defs:
        if nm not in keep:
            for k in range(s, e):
                if out[k] != "\n":
                    out[k] = " "
    return "".join(out)


def _read(path):
    with open(path, errors="surrogateescape") as fh:
        return fh.read()


def _header(path):
    """(asm, volatile, the headers it includes) of one project header, read once per run."""
    if path not in _header_cache:
        text = _read(path)
        a, v = _count(text)
        _header_cache[path] = (a, v, _includes(text, os.path.dirname(path)))
    return _header_cache[path]


def _includes(text, directory):
    found = []
    for name in _INCLUDE.findall(inline_asm.blank_comments(text)):
        for base in (directory, INCLUDE):
            path = os.path.normpath(os.path.join(base, name))
            if os.path.isfile(path):
                found.append(path)
                break
    return found


def _header_counts(includes, seen):
    """(asm, volatile) over project headers and what they include, each counted once."""
    asm = vol = 0
    for path in includes:
        if path in seen:
            continue
        seen.add(path)
        a, v, nested = _header(path)
        a2, v2 = _header_counts(nested, seen)
        asm, vol = asm + a + a2, vol + v + v2
    return asm, vol


def uses(path, name):
    """{"asm": n, "volatile": n} reaching function `name` as defined in `path`."""
    if not in_scope(path):
        return {"asm": 0, "volatile": 0}
    text = _read(path)
    a, v = _count(_reachable_text(text, name)) if _USE_WORD.search(text) else (0, 0)
    a2, v2 = _header_counts(_includes(text, os.path.dirname(os.path.abspath(path))), set())
    return {"asm": a + a2, "volatile": v + v2}


def problem(path, name, rows=None):
    """Why function `name` is not approved, or None. `name` is the definition in the source: an
    emitted member's owner."""
    rows = load() if rows is None else rows
    found = uses(path, name)
    missing = []
    for kind in KINDS:
        count = found[kind]
        if not count:
            continue
        row = rows.get((kind, name))
        if row is None:
            missing.append("%d %s without an approval row" % (count, kind))
        elif row[0] != count:
            missing.append("%d %s, but its approval row covers %d" % (count, kind, row[0]))
    return "; ".join(missing) or None


def _covered(path, name, rows):
    """Whether an `asm` row names function `name` and still counts what reaches it."""
    row = rows.get(("asm", name))
    return row is not None and row[0] == uses(path, name)["asm"]


def _callers(text):
    """The definitions in a source that a row can name: an inline helper is compiled into its callers."""
    return [name for name, start, _end in units.definitions(text)
            if not re.search(r"\binline\b", text[start:text.index("{", start)])]


def _includes_header(includes, header, seen):
    for path in includes:
        if path == header:
            return True
        if path not in seen:
            seen.add(path)
            if _includes_header(_header(path)[2], header, seen):
                return True
    return False


def approved_statements(paths, rows=None):
    """{(path, offset)} of the `asm` statements C could spell whose every function has a current row.
    A statement that reaches no function, or one function without a row, stays out."""
    rows = load() if rows is None else rows
    sources = [(path, _read(path)) for path in paths]
    approved = set()
    for path, text in sources:
        found = [start for start, _end, body in inline_asm.statements(text) if not inline_asm.is_hardware(body)]
        if not found:
            continue
        if path.endswith((".h", ".hpp")):
            header = os.path.normpath(path)
            reach = []
            for source, source_text in sources:
                if not source.endswith((".h", ".hpp")) and _INCLUDE.search(source_text) and _includes_header(
                        _includes(source_text, os.path.dirname(os.path.abspath(source))), header, set()):
                    reach += [(source, name) for name in _callers(source_text)]
            if reach and all(_covered(source, name, rows) for source, name in reach):
                approved.update((path, start) for start in found)
            continue
        callers = _callers(text)
        for start in found:
            reach = [name for name in callers if _reachable_text(text, name)[start:start + 3] == text[start:start + 3]]
            if reach and all(_covered(path, name, rows) for name in reach):
                approved.add((path, start))
    return approved


def _index():
    return units.scan(os.path.relpath(os.path.join(ROOT, "src"), os.getcwd()))


def stale(rows=None, index=None):
    """["kind symbol: reason"] for rows that no longer describe their function."""
    rows = load() if rows is None else rows
    index = _index() if index is None else index
    out = []
    for (kind, symbol), (count, _evidence) in sorted(rows.items()):
        path = index.get(symbol)
        if path is None:
            out.append("%s %s: no definition in src/" % (kind, symbol))
            continue
        found = uses(path, symbol)[kind]
        if found != count:
            out.append("%s %s: the row covers %d, the source has %d" % (kind, symbol, count, found))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list", action="store_true", help="print the functions awaiting approval")
    ap.add_argument("--stale", action="store_true", help="print rows that no longer match their function")
    a = ap.parse_args(argv)
    os.chdir(ROOT)
    index = units.scan("src")
    if a.stale:
        lines = stale(index=index)
        print("\n".join(lines) if lines else "source approvals: no stale rows")
        return 1 if lines else 0
    if a.list:
        rows = load()
        waiting = [(name, path, problem(path, name, rows)) for name, path in sorted(index.items())]
        waiting = [w for w in waiting if w[2]]
        for name, path, why in waiting:
            print("%s\t%s\t%s" % (name, path, why))
        print("%d functions await approval" % len(waiting))
        return 0
    ap.print_help()
    return 2


if __name__ == "__main__":
    sys.exit(main())
