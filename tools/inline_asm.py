#!/usr/bin/env python3
"""inline_asm.py — count the `asm` statements in src/, and test whether each one is needed.

A statement passes the byte check whether or not C could have produced the same bytes, so
tools/progress.py ratchets these counts and tools/verify.py cannot tell them apart. `sync` and
`ei` have no C spelling; every other statement has to show the function fails without it.

  python3 tools/inline_asm.py                          # the counts, by what each statement holds
  python3 tools/inline_asm.py --test src/game/x.cpp    # which statements can go; exit 1 if any can
"""
import argparse
import collections
import os
import re
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

_START = re.compile(r"(?:__asm__|__asm|\basm)\s*(?:volatile|__volatile__)?\s*([{(])")
_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
_HARDWARE = re.compile(r"^(sync|ei)$")


def blank_comments(text):
    """The text with comments spaced out, so offsets still index the original."""
    return _COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def _close(text, i):
    opening = text[i]
    closing = "}" if opening == "{" else ")"
    depth = 0
    while i < len(text):
        if text[i] == opening:
            depth += 1
        elif text[i] == closing:
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return -1


def statements(text):
    """[(start, end, body)] for each `asm` statement in a source text."""
    blank = blank_comments(text)
    found = []
    for m in _START.finditer(blank):
        end = _close(blank, m.end() - 1)
        if end < 0:
            continue
        body = " ".join(blank[m.end():end - 1].replace('"', " ").split())
        found.append((m.start(), end + 1 if blank[end:end + 1] == ";" else end, body))
    return found


def is_hardware(body):
    return bool(_HARDWARE.match(body))


def sources():
    for base in ("src", os.path.join("include", "dw4")):
        for dirpath, dirs, files in os.walk(os.path.join(ROOT, base)):
            dirs[:] = [d for d in dirs if d != "third_party"]
            for name in files:
                # `dw4u_*` are tools/units.py's one-function splits, copies of a unit's own code
                if name.endswith((".c", ".cpp", ".h", ".hpp")) and not name.startswith("dw4u_"):
                    yield os.path.join(dirpath, name)


def counts():
    """{"hardware": n, "other": n}: the statements in the tree, by whether C could spell them."""
    found = collections.Counter({"hardware": 0, "other": 0})
    for path in sources():
        with open(path, errors="surrogateescape") as fh:
            for _start, _end, body in statements(fh.read()):
                found["hardware" if is_hardware(body) else "other"] += 1
    return found


def _functions(path):
    import units
    table = units.scan("src")
    rel = os.path.relpath(path, ROOT)
    out = []
    with open(os.path.join(ROOT, "data", "check-categories.tsv")) as fh:
        for line in fh:
            if line[0] != "#":
                row = line.rstrip("\n").split("\t")
                if table.get(row[1]) == rel:
                    out.append((int(row[0], 16), row[1], row[2]))
    return out


def _keeps_its_category(path, text, functions):
    import units
    import verify
    fd, tmp = tempfile.mkstemp(suffix=os.path.splitext(path)[1], prefix="inline_asm")
    os.write(fd, text.encode("utf8", "surrogateescape"))
    os.close(fd)
    try:
        for va, name, category in functions:
            source, extra = units.standalone(tmp, name, symbols="config/SLUS-20836/symbols.txt")
            try:
                _ok, report = verify.verify_one(va, source)
            finally:
                if extra:
                    os.remove(extra)
            found = re.search(r"\bcat=([\w-]+)", (report or "").split("\n")[0])
            if not found or found.group(1) not in (category, "match"):
                return False
        return True
    finally:
        os.remove(tmp)


def removable(path):
    """The statements a file's functions still verify without, tried one at a time."""
    with open(path, errors="surrogateescape") as fh:
        text = fh.read()
    functions = _functions(path)
    return [body for start, end, body in statements(text) if not is_hardware(body)
            and _keeps_its_category(path, text[:start] + ";" + text[end:], functions)]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--test", nargs="+", metavar="SOURCE", help="try removing each statement")
    a = ap.parse_args(argv)
    if not a.test:
        for kind, n in sorted(counts().items()):
            print("%-9s %d" % (kind, n))
        return 0
    os.chdir(ROOT)
    spare = 0
    for path in a.test:
        for body in removable(os.path.abspath(path)):
            print("%s: not needed: %s" % (path, body))
            spare += 1
    return 1 if spare else 0


if __name__ == "__main__":
    sys.exit(main())
