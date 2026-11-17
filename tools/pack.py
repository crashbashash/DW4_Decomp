#!/usr/bin/env python3
"""pack.py — a compact reading view of one function's translation unit.

    pack.py --function <name|0xVA> [--repo <worktree>] [--keep N] [--out DIR] [--decl-depth D]
            [--notes-dir DIR] [--near-misses TSV] [--ref-dir DIR]...

Writes DIR/pack.md and DIR/pack.c|.cpp (default DIR: build/packs/<function>/):

  pack.c|.cpp  the unit as the compiler sees it. The unity file's own text (preamble, globals) is kept;
               the fragment(s) holding the target and its N nearest neighbours on each side (file order)
               are inlined and marked, with every other function body there replaced by
               `{ /* body elided: N B, STATUS */ }`; every other fragment becomes one
               `// [fragment <path>: N functions (M matched), K globals/tables elided]` line. The unplaced
               `inline`/`static` helpers the kept functions call stay whole when in a kept region.
  pack.md      the header block (unit row, profile, compiler, VA/size, the note file --notes-dir holds for the function,
               its row in the --near-misses table),
               the headers the unit includes (transitively) and the declarations the kept functions
               use, from those headers and from the elided fragments (globals, tables, types, unplaced
               helpers), plus, to --decl-depth, the declarations those mention; then
               `## Retail assembly`: the function's lines from the generated asm/<name>.s (a note instead when
               asm/ is absent); `## Callees without a prototype`: the symbols the function calls (retail `jal`
               and tail-call `j` targets, and calls in its C body) that no declaration visible to the unit
               names, whose implicit `int` return silently changes code; `## Reference sources`: with
               --ref-dir (repeatable), the files under those directories that mention the function's name or an
               alias, as path and line numbers (no content).

N B is the retail size from symbols.txt; STATUS is the data/check-categories.tsv category
(MATCH, UNAPPROVED, ...), `unchecked` for a placed function without a row, `unplaced` for a
definition with no retail address. A target with no definition in source gets a marker at its
address-order position, with neighbours chosen around it.

Read-only: it reads the checkout (--repo defaults to the one this script lives in) and writes only
under --out. --notes-dir is searched for <name>.md; --near-misses is a tab-separated table with a header
row (columns 1 and 2 hold a function name, column 3 an address); both are optional.
"""
import argparse
import bisect
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAME = "SLUS-20836"
KEYWORDS = set("""auto break case char const continue default do double else enum extern float for goto if
inline int long register restrict return short signed sizeof static struct switch typedef union unsigned
void volatile while class public private protected virtual template typename this new delete operator
namespace using friend bool true false asm explicit mutable const_cast static_cast dynamic_cast
reinterpret_cast throw try catch NULL define include ifdef ifndef endif pragma undef elif defined""".split())
SRC_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"(src/[^"]+)"[^\n]*$', re.M)
ANY_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+(["<])([^">]+)[">]', re.M)
IDENT = re.compile(r"[A-Za-z_]\w*")
HEADER_EXT = (".h", ".hpp")
DIRECTIVE = re.compile(r"#[ \t]*(\w*)")
DEFINE = re.compile(r"#[ \t]*define[ \t]+([A-Za-z_]\w*)")


def load_tools(repo):
    sys.path.insert(0, os.path.join(repo, "tools"))
    os.chdir(repo)          # the repository tools resolve config/ and src/ relative to the root
    global units, unitprofiles, unitobjects, srctext
    import units, unitprofiles, unitobjects, srctext  # noqa: E401


# ---------------------------------------------------------------- symbols and status

def load_symbols(repo):
    rows = []
    with open(os.path.join(repo, "config", GAME, "symbols.txt")) as fh:
        for line in fh:
            if line.startswith("#") or not line.strip():
                continue
            f = line.split()
            rows.append((int(f[0], 16), int(f[1], 16), f[2], f[3] if len(f) > 3 else ""))
    return rows


def load_categories(repo):
    out = {}
    path = os.path.join(repo, "data", "check-categories.tsv")
    if os.path.exists(path):
        with open(path) as fh:
            for line in fh:
                if line.startswith("#"):
                    continue
                f = line.rstrip("\n").split("\t")
                if len(f) >= 3:
                    out[int(f[0], 16)] = (f[2], f[3] if len(f) > 3 else "-")
    return out


def status_of(va, cats):
    if va is None:
        return "unplaced"
    cat = cats.get(va)
    if cat is None:
        return "unchecked"
    return cat[0].upper() if cat[0] != "match" else "MATCH"


# ---------------------------------------------------------------- the expanded unit

def expand(path, repo, stack=()):
    """(text, [(fragment, start, end)]) of `path` with every non-header `#include "src/..."` inlined and
    marked; the spans are the top-level fragments' marked regions in the text.

    Headers under src/ (`.h`) stay includes: they are listed and mined in pack.md instead."""
    with open(path) as fh:
        text = fh.read()
    real = os.path.realpath(path)
    if real in stack:
        raise ValueError("%s includes itself" % path)
    out, frags, pos, size = [], [], 0, 0
    for m in SRC_INCLUDE.finditer(text):
        inc = os.path.join(repo, m.group(1))
        if m.group(1).endswith(HEADER_EXT) or not os.path.isfile(inc):
            continue
        out.append(text[pos:m.start()])
        size += m.start() - pos
        body, _inner = expand(inc, repo, stack + (real,))
        piece = "// >>> %s\n%s%s// <<< %s" % (m.group(1), body, "" if body.endswith("\n") else "\n", m.group(1))
        out.append(piece)
        frags.append((m.group(1), size, size + len(piece)))
        size += len(piece)
        pos = m.end()
    out.append(text[pos:])
    return "".join(out), frags


def qualified(sig):
    m = re.search(r"([A-Za-z_]\w*)\s*::\s*(~?\s*[A-Za-z_]\w*)\s*\(", sig)
    return "%s::%s" % (m.group(1), m.group(2).replace(" ", "")) if m else None


def map_definitions(text, clean, defs, symbols, unit, group):
    """[(name, start, end, va|None)] for the top-level definitions of `text`."""
    by_name = {}
    for va, size, name, ghidra in symbols:
        by_name.setdefault(name, va)
        if ghidra:
            by_name.setdefault(ghidra, va)
    emitted = {}
    if group:
        emitted = dict(group.emitted)
        owner_name = next((n for va, s, n, g in symbols if va == group.owner), None)
        emitted[group.symbol or owner_name] = group.owner
        if owner_name:
            emitted.setdefault(owner_name, group.owner)
    used, out = set(), []
    for name, s, e in defs:
        va = emitted.get(name, by_name.get(name))
        if va is None:
            sig = clean[s:body_open(clean, s)]
            q = qualified(sig)
            if q and q in by_name:
                va = by_name[q]
            else:
                # a C++ member under its mangled compiler symbol: the first unused emitted name for it
                for sym, addr in sorted(emitted.items(), key=lambda kv: kv[1]):
                    if addr in used:
                        continue
                    special = unitobjects.special_member(sym)
                    if (special and special == name) or sym.startswith(name + "__"):
                        va = addr
                        break
        if va is not None and va in used:
            va = None
        if va is not None:
            used.add(va)
        out.append((name, s, e, va))
    return out


def body_open(clean, s):
    """Index of the `{` that opens the body of the definition starting at `s` in comment-blanked text.

    The declarator may carry a member-initialiser list in parentheses; the body's `{` is the first
    one outside parentheses."""
    depth, i, n = 0, s, len(clean)
    while i < n:
        c = clean[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        elif c == "{" and depth == 0:
            return i
        i += 1
    return n


# ---------------------------------------------------------------- declarations of headers

def chunks(text):
    """[(start, end, kind, names)] top-level declarations of a header (or unit) text."""
    clean = units._clean(text)
    defs = units.definitions(text)
    def_at = {s: (n, e) for n, s, e in defs}
    dlines = _directive_lines(clean)
    out, i, n, depth, stmt = [], 0, len(clean), 0, 0
    transparent = 0
    conditionals = []
    while i < n:
        c = clean[i]
        if depth == 0 and i in def_at:
            name, e = def_at[i]
            out.append((i, e, "func", {name}))
            i = stmt = e
            continue
        line_start = c == "#" and not clean[clean.rfind("\n", 0, i) + 1:i].strip()
        if line_start:
            word = DIRECTIVE.match(clean, i).group(1)
            if word.startswith("if"):
                conditionals.append(depth)
            elif word in ("else", "elif") and conditionals:
                depth = conditionals[-1]
            elif word == "endif" and conditionals:
                conditionals.pop()
            end = i
            while True:
                end = clean.find("\n", end)
                if end < 0:
                    end = n
                    break
                if clean[end - 1] != "\\":
                    break
                end += 1
            if depth == 0:
                m = DEFINE.match(clean, i, end)
                if m:
                    out.append((i, end, "macro", {m.group(1)}))
                if not clean[stmt:i].strip():
                    stmt = end + 1
            i = end + 1
            continue
        if c == "{":
            head = clean[stmt:i].strip()
            if depth == 0 and (head == "extern" or re.fullmatch(r"namespace(\s+\w+)?", head)):
                transparent += 1
                stmt = i + 1
            else:
                depth += 1
        elif c == "}":
            if depth == 0:
                if transparent:
                    transparent -= 1
                stmt = i + 1
            else:
                depth -= 1
        elif c == ";" and depth == 0:
            seg = clean[stmt:i + 1]
            lead = len(seg) - len(seg.lstrip())
            kind, names = statement_names(seg.strip())
            if names:
                out.append(balance_conditionals(clean, dlines, stmt + lead, i + 1) + (kind, names))
            stmt = i + 1
        i += 1
    out.sort()
    return out

def _directive_lines(clean):
    """[(line start, word)] for the preprocessor lines of `clean`."""
    return [(m.start(), m.group(1)) for m in re.finditer(r"^[ \t]*#[ \t]*(\w+)", clean, re.M)]


def balance_conditionals(clean, dlines, start, end):
    """(start, end) widened to the `#if` an inner `#else`/`#endif` belongs to, and to the `#endif` of an
    `#if` the span opens, so a declaration written once per language comes out whole."""
    first, last = bisect.bisect_left(dlines, (start,)), bisect.bisect_left(dlines, (end,))
    depth, low = 0, 0
    for _pos, word in dlines[first:last]:
        if word.startswith("if"):
            depth += 1
        elif word == "endif":
            depth -= 1
        elif word in ("else", "elif") and depth == 0:
            low = min(low, -1)
        low = min(low, depth)
    need = -low
    if need:
        lines = dlines[:first]
        for pos, word in reversed(lines):
            if word == "endif":
                need += 1
            elif word.startswith("if"):
                need -= 1
                if need == 0:
                    start = pos
                    break
    depth -= low   # conditionals still open at the end, counting the ones the start now includes
    if depth > 0:
        lines_after = dlines[last:]
        for pos, word in lines_after:
            if word.startswith("if"):
                depth += 1
            elif word == "endif":
                depth -= 1
                if depth == 0:
                    nl = clean.find("\n", pos)
                    end = len(clean) if nl < 0 else nl
                    break
    return start, end



def _depth0(s, opens="({[<", closes=")}]>"):
    """`s` with every bracketed part blanked (the brackets kept)."""
    out, depth = [], 0
    for ch in s:
        if ch in closes and depth:
            depth -= 1
            out.append(ch if depth == 0 else " ")
        elif ch in opens:
            out.append(ch if depth == 0 else " ")
            depth += 1
        else:
            out.append(ch if depth == 0 else " ")
    return "".join(out)


def statement_names(s):
    """(kind, names declared) for one `;`-terminated top-level statement (comments/strings blanked)."""
    names = set()
    tag = re.match(r"(?:template\s*<[^{;]*>\s*)?(?:typedef\s+)?(struct|class|union|enum)\s+([A-Za-z_]\w*)?[^{;]*\{", s)
    if tag:
        if tag.group(2):
            names.add(tag.group(2))
        body_start = s.index("{")
        flat = _depth0(s[body_start:], "{", "}")
        if tag.group(1) == "enum":
            inner = s[body_start + 1:s.rfind("}")]
            for part in _depth0(inner, "({[", ")}]").split(","):
                m = IDENT.match(part.strip())
                if m:
                    names.add(m.group(0))
        trail = flat[flat.rfind("}") + 1:].rstrip(";")
        names.update(w for w in IDENT.findall(re.sub(r"\[[^\]]*\]", "", trail)) if w not in KEYWORDS)
        return "type", names
    if re.match(r"(struct|class|union|enum)\s+[A-Za-z_]\w*\s*;\Z", s):
        return "forward", set()
    flat = _depth0(s[:-1])
    if s.startswith("typedef"):
        m = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", s)
        if m:
            return "type", {m.group(1)}
        idents = [w for w in IDENT.findall(re.sub(r"\[[^\]]*\]", "", flat)) if w not in KEYWORDS]
        return "type", {idents[-1]} if idents else set()
    for part in flat.split(","):
        part = part.split("=")[0]
        paren = part.find("(")
        if paren >= 0:
            m = re.search(r"([A-Za-z_]\w*)\s*$", part[:paren])
            if m and m.group(1) not in KEYWORDS:
                names.add(m.group(1))
                continue
            m = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)", s)
            if m:
                names.add(m.group(1))
            continue
        idents = [w for w in IDENT.findall(re.sub(r"\[[^\]]*\]", "", part)) if w not in KEYWORDS]
        if idents:
            names.add(idents[-1])
    return "decl", names


def identifiers(text):
    return {w for w in IDENT.findall(units._clean(text)) if w not in KEYWORDS}


def resolve_include(name, includer_dir, include_dirs):
    for d in [includer_dir] + include_dirs:
        p = os.path.normpath(os.path.join(d, name))
        if os.path.isfile(p):
            return p
    return None


def header_tree(text, includer_dir, include_dirs, repo, seen, depth=0):
    """[(depth, written, path|None)] for the includes of `text`, recursively, each header once."""
    out = []
    for m in ANY_INCLUDE.finditer(text):
        written = m.group(2)
        if m.group(1) == '"' and written.startswith("src/") and not written.endswith(HEADER_EXT):
            continue   # an inlined fragment
        path = resolve_include(written, includer_dir if m.group(1) == '"' else None, include_dirs) \
            if m.group(1) == '"' else resolve_include(written, include_dirs[0], include_dirs)
        if path is None:
            out.append((depth, written, None))
            continue
        if path in seen:
            continue
        seen.add(path)
        out.append((depth, written, path))
        with open(path, errors="replace") as fh:
            sub = fh.read()
        out.extend(header_tree(sub, os.path.dirname(path), include_dirs, repo, seen, depth + 1))
    return out


# ---------------------------------------------------------------- retail assembly, callees, references

ASM_INSN = re.compile(r"/\* ([0-9a-f]{8}): (\w[\w.]*)\s*([^*]*?)\s*\*/")
ASM_HEADER = re.compile(r"^/\* \S+ \u2014 0x([0-9a-f]+), ")
REF_MAX_LINES = 20
REF_MAX_BYTES = 4 << 20


def find_asm(repo, name, va):
    """Path of the generated asm file holding the function at `va`: asm/<name>.s, else the file under asm/
    whose header comment gives that address; None when asm/ is absent or has no such file."""
    adir = os.path.join(repo, "asm")
    if not os.path.isdir(adir):
        return None
    path = os.path.join(adir, name + ".s")
    if os.path.isfile(path):
        return path
    for fn in sorted(os.listdir(adir)):
        if not fn.endswith(".s"):
            continue
        with open(os.path.join(adir, fn), errors="replace") as fh:
            m = ASM_HEADER.match(fh.readline())
        if m and int(m.group(1), 16) == va:
            return os.path.join(adir, fn)
    return None


def asm_body(path):
    """[(va, mnemonic, operands)] of the instruction comments of a generated asm file."""
    out = []
    with open(path, errors="replace") as fh:
        for line in fh:
            m = ASM_INSN.search(line)
            if m:
                out.append((int(m.group(1), 16), m.group(2), m.group(3).strip()))
    return out


def asm_callees(insns, va, size):
    """Sorted target addresses of the `jal`s, and of the `j`s that leave [va, va+size) (tail calls)."""
    out = set()
    for _at, mn, ops in insns:
        m = re.fullmatch(r"0x([0-9a-f]+)", ops)
        if m and mn in ("jal", "j"):
            tgt = int(m.group(1), 16)
            if mn == "jal" or not va <= tgt < va + size:
                out.add(tgt)
    return sorted(out)


def called_names(body):
    """Identifiers followed by `(` in a function's C text, in first-use order."""
    seen = {}
    for m in re.finditer(r"([A-Za-z_]\w*)\s*\(", units._clean(body)):
        if m.group(1) not in KEYWORDS:
            seen.setdefault(m.group(1), None)
    return list(seen)


def unprototyped(callees, declared, self_va):
    """[(va, name, alias, why)] of `callees` ({va: (name, alias, why)}) with no name in `declared`."""
    return [(va, n, g, why) for va, (n, g, why) in sorted(callees.items())
            if va != self_va and n not in declared and (not g or g not in declared)]


def reference_hits(ref_dirs, names):
    """[(path, [line numbers])] for the files under `ref_dirs` (each as written) that mention any of
    `names` as a whole word; sorted by path, unreadable and binary files skipped."""
    pat = re.compile(r"(?<![A-Za-z0-9_])(?:%s)(?![A-Za-z0-9_])" % "|".join(re.escape(n) for n in sorted(names)))
    hits = []
    for d in ref_dirs:
        for root, dirs, files in os.walk(d):
            dirs[:] = sorted(x for x in dirs if x != ".git")
            for fn in sorted(files):
                path = os.path.join(root, fn)
                try:
                    if os.path.getsize(path) > REF_MAX_BYTES:
                        continue
                    with open(path, "rb") as fh:
                        raw = fh.read()
                except OSError:
                    continue
                if b"\0" in raw:
                    continue
                lines = [i for i, l in enumerate(raw.decode("utf-8", "replace").splitlines(), 1) if pat.search(l)]
                if lines:
                    hits.append((path, lines))
    return sorted(hits)


def tail_sections(md, repo, tname, tghidra, tva, tsize, by_va, symbols, declared, body, ref_dirs):
    """Append `## Retail assembly`, `## Callees without a prototype` and `## Reference sources` to `md`.

    `declared` is the set of names a declaration visible to the unit gives, None when there is no unit;
    `body` the target's C text or None."""
    md("")
    md("## Retail assembly")
    md("")
    apath = find_asm(repo, tname, tva)
    insns = asm_body(apath) if apath else []
    if apath:
        md("From `%s`." % os.path.relpath(apath, repo))
        md("")
        md("```")
        with open(apath, errors="replace") as fh:
            md("".join(l for l in fh if ASM_INSN.search(l) or re.match(r"\S+:\s*$", l)).rstrip("\n"))
        md("```")
    elif not os.path.isdir(os.path.join(repo, "asm")):
        md("none: `asm/` is absent (generate it with `tools/split.py`)")
    else:
        md("none: no file under `asm/` holds 0x%08x" % tva)
    md("")
    md("## Callees without a prototype")
    md("")
    if declared is None:
        md("not checked: no source unit for this function")
    else:
        by_name = {}
        for va, _s, n, g in symbols:
            by_name.setdefault(n, va)
            if g:
                by_name.setdefault(g, va)
        callees = {}
        for va in asm_callees(insns, tva, tsize):
            row = by_va.get(va)
            callees[va] = (row[2], row[3], "retail jal/j") if row else ("0x%08x" % va, "", "retail jal/j, no symbol")
        for n in called_names(body or ""):
            va = by_name.get(n)
            if va is not None and va not in callees:
                callees[va] = (by_va[va][2], by_va[va][3], "C body")
        miss = unprototyped(callees, declared, tva)
        if not apath and not body:
            md("not checked: neither asm nor a C body to read the calls from")
        elif miss:
            for va, n, g, why in miss:
                md("- `%s`%s at 0x%08x (%s)" % (n, " (`%s`)" % g if g else "", va, why))
        else:
            md("none%s" % ("" if apath else " (retail asm absent: C body calls only)"))
    if ref_dirs:
        md("")
        md("## Reference sources")
        md("")
        names = {n for n in (tname, tghidra, "FUN_%08x" % tva) if n}
        hits = reference_hits(ref_dirs, names)
        md("Files mentioning %s (no content copied):" % ", ".join("`%s`" % n for n in sorted(names)))
        md("")
        for path, lines in hits:
            more = len(lines) - REF_MAX_LINES
            md("- `%s`: line%s %s%s" % (path, "" if len(lines) == 1 else "s",
                                       ", ".join(map(str, lines[:REF_MAX_LINES])),
                                       " (+%d more)" % more if more > 0 else ""))
        if not hits:
            md("- none")


# ---------------------------------------------------------------- main

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--repo", help="checkout to read (default: the one this script lives in)")
    ap.add_argument("--function", required=True, help="symbol, Ghidra name or 0xVA")
    ap.add_argument("--keep", type=int, default=2, help="neighbours kept on each side (default 2)")
    ap.add_argument("--out", help="output directory (default build/packs/<function> under the checkout)")
    ap.add_argument("--notes-dir", help="directory of per-function note files <name>.md to point at")
    ap.add_argument("--near-misses", help="near-miss table (TSV with a header row) to quote the function's row from")
    ap.add_argument("--ref-dir", action="append", default=[], metavar="DIR",
                    help="directory to search for files mentioning the function (repeatable); listed as path and "
                         "line numbers under 'Reference sources'")
    ap.add_argument("--decl-depth", type=int, default=1,
                    help="rounds of following the names a picked header declaration mentions (default 1)")
    a = ap.parse_args(argv)
    repo = os.path.abspath(a.repo or ROOT)
    out_dir = os.path.abspath(a.out) if a.out else None
    load_tools(repo)

    symbols = load_symbols(repo)
    cats = load_categories(repo)
    by_va = {r[0]: r for r in symbols}
    q = a.function
    if re.fullmatch(r"0x[0-9a-fA-F]+", q):
        target = by_va.get(int(q, 16))
    else:
        target = next((r for r in symbols if r[2] == q), None) or next((r for r in symbols if r[3] == q), None)
    if target is None:
        sys.exit("pack: no symbol %s in config/%s/symbols.txt" % (q, GAME))
    tva, tsize, tname, tghidra = target
    out_dir = out_dir or os.path.join(repo, "build", "packs", tname)

    table = unitprofiles.load()
    unit = unitprofiles.unit_for(tva, table)
    group = unitobjects.group_for(tva)
    index = units.scan("src", symbols="config/%s/symbols.txt" % GAME)

    # the unit's source: the target's own, else the file defining the nearest placed symbol of its unit
    path = index.get(tname)
    if path is None:
        lo, hi = (unit.lo, unit.hi) if unit else (tva, tva + 1)
        nearby = sorted((abs(va - tva), index[n]) for va, _s, n, _g in symbols
                        if lo <= va < hi and n in index)
        path = nearby[0][1] if nearby else None
    lines_md = []
    md = lines_md.append

    md("# pack: %s" % tname)
    md("")
    md("- function: `%s`%s at 0x%08x, %d B (0x%x), status %s"
       % (tname, " (`%s`)" % tghidra if tghidra else "", tva, tsize, tsize, status_of(tva, cats)))
    if unit:
        exe = table.compilers.get(unit.compiler, ("?",))[0]
        md("- unit row: `%s` 0x%08x-0x%08x, compiler `%s` (`%s`), exceptions %s, status %s"
           % (unit.name, unit.lo, unit.hi, unit.compiler, exe, unit.exceptions, unit.status))
        md("- profile flags: `%s`" % unit.flags)
        if unit.source and unit.source != "whole file":
            md("- unit note: %s" % unit.source)
    else:
        md("- unit row: none (default profile)")
    if group:
        md("- unit-objects row: owner 0x%08x%s, %d emitted" % (group.owner, " whole_file" if group.whole_file else "",
                                                                len(group.emitted)))
    md("- source: `%s`" % (os.path.relpath(path, repo) if path else "none: no function of this unit is in src/"))
    if a.notes_dir:
        notes = [os.path.join(os.path.abspath(a.notes_dir), n + ".md") for n in dict.fromkeys(
            [tname, tghidra, "FUN_%08x" % tva]) if n]
        found = [p for p in notes if os.path.exists(p)]
        md("- note file: %s" % (", ".join("`%s`" % p for p in found) if found else "none (`%s`)" % notes[0]))
    nm_path = os.path.abspath(a.near_misses) if a.near_misses else None
    if nm_path and os.path.exists(nm_path):
        with open(nm_path) as fh:
            rows = [l.rstrip("\n").split("\t") for l in fh if l.strip()]
        head, rows = rows[0], rows[1:]
        hits = [r for r in rows if len(r) > 2 and (r[1] in (tname, tghidra) or
                                                     (re.fullmatch(r"0x[0-9a-fA-F]+", r[2]) and int(r[2], 16) == tva))]
        if hits:
            for r in hits:
                md("- near-miss row:")
                for k, v in zip(head, r):
                    if v:
                        md("  - %s: %s" % (k, v))
        else:
            md("- near-miss row: none")

    if path is None:
        tail_sections(md, repo, tname, tghidra, tva, tsize, by_va, symbols, None, None, a.ref_dir)
        os.makedirs(out_dir, exist_ok=True)
        with open(os.path.join(out_dir, "pack.md"), "w") as fh:
            fh.write("\n".join(lines_md) + "\n")
        print("pack: %s has no source unit; wrote %s" % (tname, os.path.join(out_dir, "pack.md")))
        return 0

    text, frags = expand(path, repo)
    full_bytes = len(srctext.read(path, root=repo).encode())
    clean = units._clean(text)
    defs = map_definitions(text, clean, units.definitions(text), symbols, unit, group)

    # target and neighbours, in file order
    ti = next((k for k, d in enumerate(defs) if d[3] == tva), None)
    missing_at = None
    if ti is None:
        before = [k for k, d in enumerate(defs) if d[3] is not None and d[3] < tva]
        missing_at = (before[-1] + 1) if before else 0
        lo_k, hi_k = max(0, missing_at - a.keep), min(len(defs), missing_at + a.keep)
        keep = set(range(lo_k, hi_k))
        # the marker goes right after the definition before it
        marker_pos = defs[missing_at - 1][2] if missing_at > 0 else (defs[0][1] if defs else len(text))
    else:
        keep = set(range(max(0, ti - a.keep), min(len(defs), ti + a.keep + 1)))
        marker_pos = None
    neighbours = sorted(keep)

    def frag_of(pos):
        return next((f for f in frags if f[1] <= pos < f[2]), None)

    kept_frags = {frag_of(defs[k][1]) for k in neighbours}
    if marker_pos is not None:
        kept_frags.add(frag_of(marker_pos - 1 if missing_at else marker_pos))
    kept_frags.discard(None)
    elided_frags = [f for f in frags if f not in kept_frags]

    def elided(pos):
        f = frag_of(pos)
        return f is not None and f not in kept_frags

    # unplaced inline/static helpers the kept functions use, followed transitively
    by_def_name = {}
    for k, d in enumerate(defs):
        by_def_name.setdefault(d[0], []).append(k)
    used = set()
    for k in neighbours:
        used |= identifiers(text[defs[k][1]:defs[k][2]])
    frontier = set(used)
    helpers = set()
    while frontier:
        nxt = set()
        for w in frontier:
            for k in by_def_name.get(w, []):
                if k in keep or k in helpers or defs[k][3] is not None:
                    continue
                helpers.add(k)
                ids = identifiers(text[defs[k][1]:defs[k][2]])
                nxt |= ids - used
                used |= ids
        frontier = nxt
    # a helper in a kept region stays in the pack; one in an elided fragment goes to pack.md
    keep |= {k for k in helpers if not elided(defs[k][1])}

    unit_chunks = chunks(text)

    def frag_marker(f):
        _p, s, e = f
        inside = [d for d in defs if s <= d[1] < e]
        matched = sum(1 for d in inside if status_of(d[3], cats) == "MATCH")
        data = sum(1 for cs, _ce, kind, _n in unit_chunks if s <= cs < e and kind in ("decl", "type"))
        return ("// [fragment %s: %d functions (%d matched), %d globals/tables elided]"
                % (f[0], len(inside), matched, data))

    # the stripped unit: events in text order
    events = [(f[1], 0, f) for f in elided_frags]
    events += [(d[1], 1, k) for k, d in enumerate(defs) if not elided(d[1])]
    if marker_pos is not None:
        events.append((marker_pos, 2, None))
    events.sort(key=lambda ev: (ev[0], ev[1]))
    pieces, pos, target_line = [], 0, None
    for at, kind, item in events:
        if kind == 0:
            pieces.append(text[pos:at])
            pieces.append(frag_marker(item))
            pos = item[2]
        elif kind == 2:
            pieces.append(text[pos:at])
            pos = at
            target_line = "".join(pieces).count("\n") + 2
            pieces.append("\n/* >>> %s (0x%08x, %d B) belongs here: no definition in source; see pack.md */\n"
                          % (tname, tva, tsize))
        else:
            name, s, e, va = defs[item]
            if item in keep:
                if item == ti:
                    pieces.append(text[pos:s])
                    target_line = "".join(pieces).count("\n") + 1
                    pieces.append(text[s:e])
                    pos = e
                continue
            b = body_open(clean, s)
            size = by_va[va][1] if va is not None else None
            desc = ("%d B, %s" % (size, status_of(va, cats))) if size is not None else \
                ("%d B source, %s" % (e - b, status_of(None, cats)))
            pieces.append(text[pos:b])
            pieces.append("{ /* body elided: %s */ }" % desc)
            pos = e
    pieces.append(text[pos:])
    packed = "".join(pieces)
    if elided_frags:
        packed = ("// pack: each `// [fragment ...]` line stands for an elided fragment; the declarations the kept "
                  "code uses from them are in pack.md\n" + packed)
        if target_line:
            target_line += 1
    ext = os.path.splitext(path)[1]
    if ext not in (".c", ".cpp"):
        ext = ".c"

    # headers and the declarations the kept functions use
    include_dirs = []
    for tok in (unit.flags.split() if unit else []):
        if tok.startswith("-I") and tok != "-I-":
            include_dirs.append(os.path.join(repo, tok[2:]))
    if not include_dirs:
        include_dirs = [os.path.join(repo, "include")]
    seen = set()
    tree = header_tree(text, os.path.dirname(path), include_dirs, repo, seen)
    # names the kept code mentions, plus those of the pack's own declarations of them
    for s, e, kind, names in unit_chunks:
        if kind != "func" and names & used and not elided(s):
            used |= identifiers(text[s:e])
    # sources of declarations: each header, and each elided fragment (its declarations and the
    # unplaced helpers it defines; never a placed function's body)
    helper_starts = {defs[k][1] for k in helpers}
    sources = {}
    for f in elided_frags:
        sources[f[0]] = (text, [c for c in unit_chunks if f[1] <= c[0] < f[2]
                                and (c[2] != "func" or c[0] in helper_starts)])
    for _d, _w, p in tree:
        if p:
            with open(p, errors="replace") as fh:
                htext = fh.read()
            sources[p] = (htext, chunks(htext))
    picked = {}
    want = set(used)
    for _round in range(a.decl_depth + 1):
        new = set()
        for p, (stext, cs) in sources.items():
            for s, e, kind, names in cs:
                if (p, s) in picked or not (names & want):
                    continue
                picked[(p, s)] = e
                new |= identifiers(stext[s:e])
        want = new - want - used
        used |= new
        if not want:
            break

    md("- pack: `%s` (target at line %s); kept %s; %d of %d fragments kept"
       % ("pack" + ext, target_line,
          ", ".join("`%s`%s" % (defs[k][0], " (helper)" if k in helpers else "") for k in sorted(keep)),
          len(kept_frags), len(frags)))
    md("- sizes: expanded unit %d B (srctext.read, headers under src/ included), fragments-only %d B, "
       "pack%s %d B" % (full_bytes, len(text.encode()), ext, len(packed.encode())))
    md("")
    md("## Headers")
    md("")
    for d, w, p in tree:
        md("%s- `%s`%s" % ("  " * d, os.path.relpath(p, repo) if p else w, "" if p else " (unresolved)"))
    md("")
    md("## Declarations used by the kept functions")
    md("")
    order = [(f[0], "fragment " + f[0]) for f in elided_frags]
    order += [(p, os.path.relpath(p, repo)) for _d, _w, p in tree if p]
    for p, title in order:
        stext, _cs = sources[p]
        merged = []
        for s, e in sorted((s, e) for (pp, s), e in picked.items() if pp == p):
            if merged and s < merged[-1][1]:
                merged[-1][1] = max(merged[-1][1], e)
            else:
                merged.append([s, e])
        if not merged:
            continue
        md("### %s (%d)" % (title, len(merged)))
        md("")
        md("```c")
        for s, e in merged:
            md(stext[s:e].rstrip())
        md("```")
        md("")

    declared = set()
    for s, _e, kind, names in unit_chunks:
        if kind == "func" and s >= (defs[ti][1] if ti is not None else marker_pos):
            continue    # a definition after the target is not yet visible to it
        declared |= names
    for _d, _w, p in tree:
        if p:
            for _s, _e, _kind, names in sources[p][1]:
                declared |= names
    tail_sections(md, repo, tname, tghidra, tva, tsize, by_va, symbols, declared,
                  text[defs[ti][1]:defs[ti][2]] if ti is not None else None, a.ref_dir)

    os.makedirs(out_dir, exist_ok=True)
    md_text = "\n".join(lines_md) + "\n"
    with open(os.path.join(out_dir, "pack.md"), "w") as fh:
        fh.write(md_text)
    with open(os.path.join(out_dir, "pack" + ext), "w") as fh:
        fh.write(packed)
    print("pack: %s  expanded %d B  pack.md %d B  pack%s %d B  -> %s"
          % (tname, full_bytes, len(md_text), ext, len(packed), out_dir))
    return 0


if __name__ == "__main__":
    sys.exit(main())
