#!/usr/bin/env python3
"""sourceapprovals.py — owner approval of inline `asm` and `volatile` in C and C++ sources.

An `asm` statement or a `volatile` passes the byte check whether or not plain C could have produced
the same bytes, so either can force a match the original source did not have. A function using one
counts as matched only once the project owner has reviewed the evidence and added a row to
config/source-approvals.tsv. Until then `make check` files it as `unapproved`: its source stays and
links byte-identically, but it counts in no matched figure (docs/engine/source-approvals.md).

A row is `kind <TAB> symbol <TAB> count <TAB> evidence`: `asm`, `volatile` or `asm-function`, the function,
how many uses reach it, and the anchor of the evidence in docs/engine/source-approvals.md. `asm-function`
approves a whole MWCC `asm` function, written in assembly in the original source (its count is 1); without
the row such a function is an asm body, which counts in no matched figure. The count voids the
approval when another use appears. A call of an MWCC `__I_<mnemonic>` instruction builtin emits the
instruction it names, so it counts as an `asm` use. `sync` and `ei` need no row, since C cannot spell
them, and stock source under src/third_party/ is out of scope, as it is for tools/inline_asm.py.

  python3 tools/sourceapprovals.py --list     # the unapproved queue, for the owner to review
  python3 tools/sourceapprovals.py --stale    # rows whose function no longer uses what they approve
"""
import argparse
import functools
import srctext
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
import asmsources  # noqa: E402
import inline_asm  # noqa: E402
import units  # noqa: E402
import unitprofiles  # noqa: E402
import unitobjects  # noqa: E402

TABLE = os.path.join(ROOT, "config", "source-approvals.tsv")
INCLUDE = os.path.join(ROOT, "include")
KINDS = ("asm", "volatile", "asm-function")
_STRING = re.compile(r'"(?:\\.|[^"\\\n])*"')
_VOLATILE = re.compile(r"\b(?:__volatile__|volatile)\b")
_INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)
_WORD = re.compile(r"[A-Za-z_]\w*")
_USE_WORD = re.compile(r"asm|volatile|__I_")
# an MWCC instruction builtin (`__I_mfc0(3, 12)`, `__I_nop()`): inline assembly by another name
_BUILTIN = re.compile(r"(?<!\w)__I_\w+\s*\(")
# `inline`, or GCC's `__inline` and `__inline__`, which Sony's headers spell
_INLINE = re.compile(r"\b(?:__)?inline(?:__)?\b")
_header_cache = {}
_defined_cache = {}
_source_cache = {}


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
    """(asm statements and instruction builtin calls C could spell, volatile keywords) in a source text."""
    asm = sum(1 for _s, _e, body in inline_asm.statements(text) if not inline_asm.is_hardware(body))
    blank = _blank(text)
    return asm + len(_BUILTIN.findall(blank)), len(_VOLATILE.findall(blank))


@functools.lru_cache(maxsize=64)
def _text_count(text):
    """`_count` of a whole source text, kept per text."""
    return _count(text)


def _reachable_text(text, name):
    """The text of function `name` with every other top-level definition blanked, except the inline
    helpers it reaches by name: those are compiled into it. A file-scope declaration or macro
    stays only when the function or a kept helper names something it declares, directly or through
    a type definition or macro it reaches (C keywords aside, so a shared type name keeps it): a `volatile`
    global reaches the functions that use it, and a `volatile` member the functions that reach its type."""
    defs = units.definitions(text)
    if not defs:
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
                if _INLINE.search(text[s2:text.index("{", s2)]):
                    keep.add(word)
                    pending.append(word)
    out = list(text)
    for nm, s, e in defs:
        if nm not in keep:
            for k in range(s, e):
                if out[k] != "\n":
                    out[k] = " "
    kept = [bodies[nm] for nm in keep]
    used = set()
    for s, e in kept:
        used.update(_NAME.findall(_blank(text[s:e])))
    statements = []
    for s, e in _file_scope_statements(text, [(s, e) for _nm, s, e in defs]):
        body = _blank(text[s:e])
        words = set(_NAME.findall(body)) - _C_KEYWORDS
        # a type definition is reached by its tag or typedef name, not by a member's name
        if _TYPE_DEF.match(body):
            keys, passes = set(_NAME.findall(_unnest(body, "{}"))) - _C_KEYWORDS, words
        elif _PROPAGATES.match(body):
            # a macro is reached by its name, and passes on the names it uses, its parameters aside
            macro = _MACRO.match(body)
            keys = {macro.group(1)}
            passes = words - keys - set(_NAME.findall(macro.group(2) or ""))
        else:
            # a variable or function declaration passes on its type names, not its parameter names
            keys, passes = words, set(_NAME.findall(_unnest(body, "()"))) - _C_KEYWORDS
        statements.append((s, e, keys, passes))
    reached, grew = set(), True
    while grew:
        grew = False
        for k, (_s, _e, keys, passes) in enumerate(statements):
            if k not in reached and keys & used:
                reached.add(k)
                used |= passes
                grew = True
    for k, (s, e, _keys, _passes) in enumerate(statements):
        if k not in reached:
            for j in range(s, e):
                if out[j] != "\n":
                    out[j] = " "
    return "".join(out)


_C_KEYWORDS = frozenset(
    "auto break case char const continue default do double else enum extern float for goto if inline int long "
    "register restrict return short signed sizeof static struct switch typedef union unsigned void volatile while "
    "__volatile__ __inline__ __inline __attribute__ __restrict__ __extension__ bool class asm __asm__ __asm "
    "define undef include ifdef ifndef elif endif pragma defined".split())
_NAME = re.compile(r"(?<![\w])[A-Za-z_]\w*")
# A type definition is reached by its tag or typedef name and passes on every name it uses (a member's
# type); a macro is reached by its name and passes on the names it uses, its parameters aside; a variable or function declaration is reached
# by its names and passes on only those outside parentheses, so a parameter's name links nothing.
_TYPE_DEF = re.compile(r"\s*(?:typedef\b|struct\b|union\b|enum\b)")
_PROPAGATES = re.compile(r"\s*#\s*define\b")
_MACRO = re.compile(r"\s*#\s*define\s+(\w+)(\([^)]*\))?")


def _unnest(text, pair):
    """The text with every bracketed span of `pair`, and what it holds, spaced out."""
    opening, closing = pair
    out, depth = [], 0
    for c in text:
        if c == opening:
            depth += 1
        out.append(" " if depth else c)
        if c == closing and depth:
            depth -= 1
    return "".join(out)


def _spaced(text):
    """The text with comments and string contents spaced out, so offsets still index the original."""
    return _STRING.sub(lambda m: '"' + " " * (len(m.group(0)) - 2) + '"', inline_asm.blank_comments(text))


def _file_scope_statements(text, kept):
    """[(start, end)] of the declarations a file makes outside its definitions (`kept`): each runs to its
    `;` at brace and parenthesis depth 0, and a preprocessor line, continuations included, is one statement.
    A file-scope `volatile` reaches a function only through a name the function uses, so the text of the
    other statements is what `_reachable_text` may blank."""
    clean = _spaced(text)
    inside = sorted(kept)
    out, i, n, start, depth = [], 0, len(clean), None, 0
    at = 0   # the definitions are sorted and disjoint, and `i` only grows: the first one not yet behind it
    while i < n:
        while at < len(inside) and inside[at][1] <= i:
            at += 1
        hit = inside[at] if at < len(inside) and inside[at][0] <= i else None
        if hit:
            if start is not None and depth == 0:
                out.append((start, i))
            start = None
            i = hit[1]
            continue
        c = clean[i]
        if start is None and c == "#" and not clean[clean.rfind("\n", 0, i) + 1:i].strip():
            end = i
            while True:
                end = clean.find("\n", end)
                if end < 0:
                    end = n
                    break
                if clean[end - 1] != "\\":
                    break
                end += 1
            out.append((i, end))
            i = end
            continue
        if start is None and not c.isspace():
            start = i
        if c in "{(":
            depth += 1
        elif c in "})":
            depth -= 1
        elif c == ";" and depth == 0 and start is not None:
            out.append((start, i + 1))
            start = None
        i += 1
    if start is not None:
        out.append((start, n))
    return out


def _read(path):
    return srctext.read(path, errors="surrogateescape")


def _header(path):
    """(text, the headers it includes) of one project header, read once per run."""
    if path not in _header_cache:
        text = _read(path)
        _header_cache[path] = (text, _includes(text, os.path.dirname(path)))
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


def _header_texts(includes, seen):
    """[(path, text)] of the project headers a source includes and what they include, each once, a
    header's own includes ahead of it as the preprocessor reads them."""
    out = []
    for path in includes:
        if path in seen:
            continue
        seen.add(path)
        text, nested = _header(path)
        out += _header_texts(nested, seen)
        out.append((path, text))
    return out


def defines(path, name):
    """Whether `path` holds a top-level definition of `name`: a whole-file member does, while a
    function the compiler emits from another definition (an out-of-line copy) does not."""
    if path not in _defined_cache:
        _defined_cache[path] = {nm for nm, _s, _e in units.definitions(_read(path))}
    return name in _defined_cache[path]


def uses(path, name):
    """{"asm": n, "volatile": n} reaching function `name` as defined in `path`."""
    if not in_scope(path):
        return {"asm": 0, "volatile": 0, "asm-function": 0}
    text, counted, _offsets = _source(path)
    # blanking only removes text, so a source with nothing to count has nothing to count for any of its
    # functions; a whole library unit holds thousands, and its reachable text is costly to build
    a, v = _count(_reachable_text(text, name)) if counted else (0, 0)
    return {"asm": a, "volatile": v, "asm-function": int(name in unitprofiles.asm_body_names(path))}


def _source(path):
    """(text, whether it has anything to count, {header: offset}) of one source, read once per version of
    the file: its project headers come first, as the preprocessor reads them, so a header's helpers,
    macros and declarations reach a function the same way the file's own do, and the offsets place each
    header in the text. A library unit's thousands of members would each expand and scan it again."""
    st = os.stat(path)
    stamp = (st.st_mtime_ns, st.st_size)
    hit = _source_cache.get(path)
    if hit is None or hit[0] != stamp:
        own = _read(path)
        parts, offsets, at = [], {}, 0
        for header, header_text in _header_texts(_includes(own, os.path.dirname(os.path.abspath(path))), set()):
            offsets[header] = at
            parts.append(header_text + "\n")
            at += len(header_text) + 1
        text = "".join(parts) + own
        counted = bool(_USE_WORD.search(text)) and _text_count(text) != (0, 0)
        hit = _source_cache[path] = (stamp, (text, counted, offsets))
    return hit[1]


def approved_asm_function(path, name, rows=None):
    """Whether `name` is an MWCC `asm` function in `path` with a current `asm-function` row."""
    rows = load() if rows is None else rows
    row = rows.get(("asm-function", name))
    return row is not None and row[0] == 1 and name in unitprofiles.asm_body_names(path)


def problem(path, name, rows=None, row=None):
    """Why function `name` is not approved, or None. `name` is the definition in the source: an
    emitted member's owner. `row` is the symbol its approval row names when that differs (a static
    the symbol map names apart)."""
    rows = load() if rows is None else rows
    found = uses(path, name)
    missing = []
    for kind in KINDS:
        count = found[kind]
        if not count:
            continue
        row_found = rows.get((kind, row or name))
        if row_found is None:
            missing.append("%d %s without an approval row" % (count, kind))
        elif row_found[0] != count:
            missing.append("%d %s, but its approval row covers %d" % (count, kind, row_found[0]))
    return "; ".join(missing) or None


def _covered(path, name, rows, aliases=None):
    """Whether an `asm` row names function `name` (or the symbol `aliases` gives the static it is in `path`)
    and still counts what reaches it."""
    row = rows.get(("asm", (aliases or {}).get((os.path.abspath(path), name), name)))
    return row is not None and row[0] == uses(path, name)["asm"]


def _aliases(rows):
    """{(path, definition): symbol} for rows naming a static by the symbol the symbol map gives it
    (`Copy_tlbfunc` for `tlbfunc.c`'s `Copy`)."""
    index, out = None, {}
    for _kind, symbol in rows:
        name = unitobjects.source_name(symbol)
        if name == symbol:
            continue
        index = _index() if index is None else index
        path = index.get(symbol)
        if path is not None:
            out[(os.path.abspath(path), name)] = symbol
    return out


def _callers(text):
    """The definitions in a source that a row can name: an inline helper is compiled into its callers."""
    return [name for name, start, _end in units.definitions(text)
            if not _INLINE.search(text[start:text.index("{", start)])]


def approved_statements(paths, rows=None):
    """{(path, offset)} of the `asm` statements C could spell whose every function has a current row.
    A statement that reaches no function, or one function without a row, stays out."""
    rows = load() if rows is None else rows
    aliases = _aliases(rows)
    sources = [(path, _read(path)) for path in paths]
    approved = set()
    for path, text in sources:
        found = [start for start, _end, body in inline_asm.statements(text) if not inline_asm.is_hardware(body)]
        if not found:
            continue
        if path.endswith((".h", ".hpp")):
            header = os.path.normpath(os.path.abspath(path))
            for start in found:
                reach = []
                for source, source_text in sources:
                    if source.endswith((".h", ".hpp")) or not in_scope(source):
                        continue
                    combined, _counted, offsets = _source(source)
                    at = offsets.get(header)
                    if at is None:
                        continue
                    reach += [(source, name) for name in _callers(source_text)
                              if _reachable_text(combined, name)[at + start:at + start + 3] == text[start:start + 3]]
                if reach and all(_covered(source, name, rows, aliases) for source, name in reach):
                    approved.add((path, start))
            continue
        callers = _callers(text)
        for start in found:
            reach = [name for name in callers if _reachable_text(text, name)[start:start + 3] == text[start:start + 3]]
            if reach and all(_covered(path, name, rows, aliases) for name in reach):
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
        path = index.get(symbol) or index.get(unitobjects.source_owner(symbol))
        if path is None:
            out.append("%s %s: no definition in src/" % (kind, symbol))
            continue
        name = symbol if defines(path, symbol) else unitobjects.source_name(symbol)
        if not defines(path, name):
            out.append("%s %s: no definition in %s" % (kind, symbol, path))
            continue
        found = uses(path, name)[kind]
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
        waiting = []
        for name, path in sorted(index.items()):
            if defines(path, name):
                waiting.append((name, path, problem(path, name, rows)))
                continue
            # a static the symbol map names apart is counted under its source name; an emitted copy
            # answers through its owner, which the index lists itself
            member = unitobjects.source_name(name)
            if member != name and defines(path, member):
                waiting.append((name, path, problem(path, member, rows, row=name)))
        waiting = [w for w in waiting if w[2]]
        for name, path, why in waiting:
            print("%s\t%s\t%s" % (name, path, why))
        print("%d functions await approval" % len(waiting))
        return 0
    ap.print_help()
    return 2


if __name__ == "__main__":
    sys.exit(main())
