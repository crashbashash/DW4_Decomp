"""asmsources.py — the owner-approved hand-written assembly sources under `src/`.

Some retail routines were written in assembly, not compiled: their source is a `.S` file, and no C
reproduces them. Such a file may sit in `src/` only once the project owner has reviewed the evidence
that the routine is hand-written and added its row to config/assembly-sources.tsv. Every other `.S`
file in `src/` is refused, so an agent cannot turn an unmatched function into assembly on its own
(CLAUDE.md, docs/engine/assembly-sources.md).

A row is `symbol <TAB> path <TAB> evidence`: the function, the repository-relative `.S` file that
defines it, and the anchor of its evidence in docs/engine/assembly-sources.md. A `.S` file's
definitions are its `.globl` symbols that it also labels.

An EE GCC whole-file C unit keeps an assembly function in its own file instead, as a file-scope
`__asm__("...");` block starting a line, in address order among the C (`gcc_functions`). The block
defines exactly one function, the `.globl` name its text also labels; any other count stops every
tool that reads `src/`. Such a function is approved by an `asm-function` row in
config/source-approvals.tsv, as an MWCC `asm` function is (tools/sourceapprovals.py), and without
the row it is `unapproved`.
"""
import functools
import os
import re

import srctext

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


# a file-scope GCC `asm` block: `__asm__(` at the start of a line (a statement inside a function is indented)
_GCC_BLOCK_RE = re.compile(r"^__asm__\s*\(", re.M)
_C_COMMENT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
_ESCAPES = {"n": "\n", "t": "\t", '"': '"', "\\": "\\", "'": "'"}


def _blank_comments(text):
    """`text` with C comments spaced out (newlines kept), so offsets still index it."""
    return _C_COMMENT_RE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def _gcc_block(text, at):
    """(end, assembler text) of the `__asm__(` block whose `(` is at `at`: the block runs to its closing
    parenthesis and `;`, and its text is its string literals joined and unescaped."""
    depth, i, parts = 0, at, []
    while i < len(text):
        c = text[i]
        if c == '"':
            j, part = i + 1, []
            while text[j] != '"':
                if text[j] == "\\":
                    j += 1
                    part.append(_ESCAPES.get(text[j], "\\" + text[j]))
                else:
                    part.append(text[j])
                j += 1
            parts.append("".join(part))
            i = j
        elif c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                end = i + 1
                while end < len(text) and text[end] in " \t":
                    end += 1
                return (end + 1 if text[end:end + 1] == ";" else end), "".join(parts)
        i += 1
    raise ValueError("an `__asm__(` block at offset %d is not closed" % at)


@functools.lru_cache(maxsize=256)
def gcc_functions(text):
    """[(name, start, end)] of the assembly functions a C source defines in file-scope `__asm__("...");`
    blocks, in file order. Raises ValueError for a block that defines no function or several."""
    clean = _blank_comments(text)
    out = []
    for found in _GCC_BLOCK_RE.finditer(clean):
        end, asm = _gcc_block(clean, found.end() - 1)
        names = definitions(asm)
        if len(names) != 1:
            line = clean.count("\n", 0, found.start()) + 1
            raise ValueError("the file-scope `__asm__` block at line %d defines %s: such a block defines exactly "
                             "one function (tools/asmsources.py)"
                             % (line, "no `.globl` function" if not names else "%d (%s)" % (len(names), ", ".join(names))))
        out.append((names[0], found.start(), end))
    return tuple(out)


def gcc_function_names(path):
    """The assembly functions C source `path` defines in file-scope `__asm__` blocks (`gcc_functions`)."""
    if is_assembly(path):
        return frozenset()
    try:
        stamp = os.stat(path).st_mtime_ns
    except OSError:
        return frozenset()
    hit = _GCC_NAMES.get(path)
    if hit is None or hit[0] != stamp:
        text = srctext.read(path, errors="replace")
        names = frozenset(name for name, _s, _e in gcc_functions(text)) if "__asm__" in text else frozenset()
        hit = _GCC_NAMES[path] = (stamp, names)
    return hit[1]


_GCC_NAMES = {}
