"""asmsources.py — the owner-approved hand-written assembly sources under `src/`.

Some retail routines were written in assembly, not compiled: their source is a `.S` file, and no C
reproduces them. Such a file may sit in `src/` only once the project owner has reviewed the evidence
that the routine is hand-written and added its row to config/assembly-sources.tsv. Every other `.S`
file in `src/` is refused, so an agent cannot turn an unmatched function into assembly on its own
(CLAUDE.md, docs/engine/assembly-sources.md).

A row is `symbol <TAB> path <TAB> evidence`: the function, the repository-relative `.S` file that
defines it, and the anchor of its evidence in docs/engine/assembly-sources.md. A `.S` file's
definitions are its `.globl` symbols that it also labels.
"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TABLE = os.path.join(ROOT, "config", "assembly-sources.tsv")
EXT = ".S"

_GLOBL_RE = re.compile(r"^\s*\.globl\s+([A-Za-z_.$][\w.$]*)", re.M)
_LABEL_RE = re.compile(r"^([A-Za-z_.$][\w.$]*):", re.M)
_COMMENT_RE = re.compile(r"/\*.*?\*/", re.S)


def load(path=TABLE):
    """{symbol: (path, evidence)} from the approval table."""
    rows = {}
    if not os.path.exists(path):
        return rows
    for n, line in enumerate(open(path), 1):
        if not line.strip() or line.startswith("#"):
            continue
        cols = line.rstrip("\n").split("\t")
        if len(cols) != 3 or not all(c.strip() for c in cols):
            raise ValueError("%s:%d: expected `symbol<TAB>path<TAB>evidence`" % (path, n))
        symbol, source, evidence = (c.strip() for c in cols)
        if symbol in rows:
            raise ValueError("%s:%d: %s is listed twice" % (path, n, symbol))
        rows[symbol] = (source, evidence)
    return rows


def definitions(text):
    """The symbols an assembly file defines: `.globl` names it also labels, in file order."""
    text = _COMMENT_RE.sub(" ", text)
    labels = set(_LABEL_RE.findall(text))
    return [name for name in _GLOBL_RE.findall(text) if name in labels]


def extract(text, name):
    """`text` with every function except `name` blanked: a function runs from its `.globl` line to
    the next function's `.globl` line, and what precedes the first one (`.set` modes, includes) is
    kept for all. Line breaks survive, so the assembler's line numbers still point into the file."""
    names = definitions(text)
    if name not in names:
        raise KeyError("%s is not defined here" % name)
    starts = []
    for found in _GLOBL_RE.finditer(text):
        if found.group(1) in names and _COMMENT_RE.sub(" ", text[:found.start()]).count("/*") == 0:
            starts.append((found.start(), found.group(1)))
    out = list(text)
    for k, (start, symbol) in enumerate(starts):
        end = starts[k + 1][0] if k + 1 < len(starts) else len(text)
        if symbol != name:
            for i in range(start, end):
                if out[i] != "\n":
                    out[i] = " "
    return "".join(out)


def is_assembly(path):
    return str(path).endswith(EXT)


def approved_definitions(path, root=ROOT, table=None):
    """The symbols `path` defines, after checking every one of them is approved for that file.

    Raises ValueError naming the first symbol without a row, or with a row for another file."""
    rows = load() if table is None else table
    rel = os.path.relpath(os.path.abspath(path), root)
    names = definitions(open(path).read())
    if not names:
        raise ValueError("%s defines no `.globl` function" % rel)
    for name in names:
        row = rows.get(name)
        if row is None:
            raise ValueError("%s defines %s, which config/assembly-sources.tsv does not approve as "
                             "hand-written assembly (only the project owner approves a row)" % (rel, name))
        if os.path.normpath(row[0]) != os.path.normpath(rel):
            raise ValueError("%s defines %s, approved in config/assembly-sources.tsv for %s"
                             % (rel, name, row[0]))
    return names


def approved_names(src_index):
    """The symbols of a `units.scan` index whose source is an assembly file."""
    return {name for name, path in src_index.items() if is_assembly(path)}
