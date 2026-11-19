#!/usr/bin/env python3
"""notes_for.py — print everything the repository already says about one function or datum.

Run it before attacking a function: an earlier agent may have found its lever, refuted a spelling or
left it open with a reason. Given a symbol or a retail address it prints, from committed files only:

  * the symbol: address and size (config/SLUS-20836/symbols.txt), the name overlays
    (config/SLUS-20836/names/*.tsv) and data-names.tsv rows that name it;
  * its state: the data/check-categories.tsv row of the last `make check`, the units.tsv profile row
    covering it, its unit-objects.json row (and its role there) and every other config table row
    that names it;
  * its source: the defining file, the comment in front of the definition and every comment inside
    it (`matching construct` notes included), and any other source line quoting its address;
  * what the documents say: every docs/ line naming the symbol or its address, under the heading it
    sits in, with the data/levers.jsonl entry a line of understanding-shapes.md belongs to.

It answers a query; it keeps no list. The idea is dc3-decomp's `find_refutations.py` ("ship the
query, not the answer", https://github.com/freeqaz/dc3-decomp); the code is this project's own.

  python3 tools/notes_for.py igMetaObject_GetFieldAt
  python3 tools/notes_for.py 0x2fe9c0
  python3 tools/notes_for.py 002fe9c0 --max 10      # at most 10 lines per document section
"""
import argparse
import glob
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import levers  # noqa: E402
import unitprofiles  # noqa: E402
import unitobjects  # noqa: E402
import units  # noqa: E402

CONFIG = "config/SLUS-20836"
SYMBOLS = CONFIG + "/symbols.txt"
_HEX = re.compile(r"^(?:0x)?([0-9a-fA-F]{1,8})$")
_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
# config tables the sections above already read, or that are generated wholesale from the image
_SKIP_CONFIG = {"symbols.txt", "layout.txt", "units.tsv", "unit-objects.json", "data-names.tsv"}


def address_pattern(va):
    """A retail address as the repository writes it: `0x2fe9c0`, `0x002fe9c0` or the bare 8-digit form."""
    digits = "%x" % va
    return re.compile(r"(?<![0-9A-Za-z_])(?:0x0*%s|%08x)(?![0-9A-Za-z_])" % (digits, va), re.I)


def name_pattern(names):
    names = sorted({n for n in names if n}, key=len, reverse=True)
    if not names:
        return None
    return re.compile(r"(?<![A-Za-z0-9_])(?:%s)(?![A-Za-z0-9_])" % "|".join(map(re.escape, names)))


def rel(path):
    return os.path.relpath(path, ROOT)


def tsv_rows(path):
    with open(path, encoding="utf-8") as fh:
        for number, line in enumerate(fh, 1):
            if line.strip() and not line.startswith("#"):
                yield number, line.rstrip("\n")


def member_names(query, symbols=SYMBOLS):
    """{compiler name: retail address} of the functions and data a C++ name means: a compiler name itself
    (`setVisualContext__10igRendererFP15igVisualContext`) or a member (`igRenderer::setVisualContext`,
    `Gap::Gui::igRenderer::setVisualContext`; overloads give several). Read from the compiler-name map
    (config/SLUS-20836/compiler-names.tsv) and the whole-file rows that bind compiler names."""
    from demangle import demangle
    import compiler_names
    bound = {name: va for name, (va, _retail) in compiler_names.load(os.path.join(ROOT, symbols)).items()}
    for group in unitobjects.load():
        for pairs in (group.emitted, group.duplicates, group.externals, group.data):
            for name, va in pairs:
                bound.setdefault(name, va)
        if group.symbol:
            bound.setdefault(group.symbol, group.owner)
    if query in bound:
        return {query: bound[query]}
    if "::" not in query:
        return {}
    out = {}
    for name, va in bound.items():
        member = demangle(name) if "__" in name else None
        if member is not None and member.class_name and (
                member.qualified == query or member.qualified.endswith("::" + query)):
            out[name] = va
    return out


def resolve(query):
    """-> (va or None, size or None, symbol or None) for a symbol, a data name, a compiler or member name or an
    address."""
    by_name, by_va = unitobjects.names(SYMBOLS)
    if query in by_name:
        return by_name[query][0], by_name[query][1], query
    m = _HEX.match(query)
    if m and (query.lower().startswith("0x") or (len(m.group(1)) >= 6 and any(c.isdigit() for c in query))):
        va = int(m.group(1), 16)
        if va in by_va:
            return va, by_va[va][1], by_va[va][0]
        for _, line in tsv_rows(os.path.join(ROOT, CONFIG, "data-names.tsv")):
            fields = line.split("\t")
            if int(fields[0], 16) == va:
                return va, None, fields[1]
        return va, None, None
    for path in [os.path.join(ROOT, CONFIG, "data-names.tsv")] + sorted(glob.glob(os.path.join(ROOT, CONFIG, "names", "*.tsv"))):
        for _, line in tsv_rows(path):
            fields = line.split("\t")
            if len(fields) > 1 and fields[1] == query:
                va = int(fields[0], 16)
                entry = by_va.get(va)
                return va, entry[1] if entry else None, query
    vas = set(member_names(query).values())
    if len(vas) == 1:
        va = vas.pop()
        if va in by_va:
            return va, by_va[va][1], by_va[va][0]
        for _, line in tsv_rows(os.path.join(ROOT, CONFIG, "data-names.tsv")):
            fields = line.split("\t")
            if int(fields[0], 16) == va:
                return va, None, fields[1]
        return va, None, None
    return None, None, query


def section(title, lines):
    print("== " + title)
    for line in lines or ["(none)"]:
        print("  " + line)
    print()


def identity(va, size, symbol, match_addr, match_name):
    out = []
    if va is not None:
        out.append("address 0x%08x%s" % (va, ", function of 0x%x bytes" % size if size else ", not a function"))
    if symbol:
        out.append("symbol  " + symbol)
    if va is None:
        out.append("not a retail symbol, data name or name overlay row: the text is searched as a name")
    paths = [os.path.join(ROOT, CONFIG, "data-names.tsv")] + sorted(glob.glob(os.path.join(ROOT, CONFIG, "names", "*.tsv")))
    for path in paths:
        for number, line in tsv_rows(path):
            fields = line.split("\t")
            if (va is not None and match_addr.search(fields[0])) or (len(fields) > 1 and match_name and match_name.fullmatch(fields[1])):
                out.append("%s:%d  %s" % (rel(path), number, line))
    return out


def state(va, function, match_addr, match_name):
    out = []
    if function:
        for number, line in tsv_rows(os.path.join(ROOT, "data", "check-categories.tsv")):
            if int(line.split("\t", 1)[0], 16) == va:
                out.append("data/check-categories.tsv:%d  %s" % (number, line))
                break
        else:
            out.append("data/check-categories.tsv: no row (no source in src/ at the last make check)")
        table = unitprofiles.load()
        unit = unitprofiles.unit_for(va, table)
        if unit:
            compiler = table.compilers.get(unit.compiler, ("?",))[0]
            out.append("units.tsv  %s 0x%08x-0x%08x %s (%s) %s exceptions=%s status=%s  %s"
                       % (unit.name, unit.lo, unit.hi, unit.compiler, compiler, unit.flags, unit.exceptions,
                          unit.status, unit.source))
        else:
            out.append("units.tsv: no unit covers it (default profile)")
    if va is not None:
        roles = []
        for group in unitobjects.load():
            for role, pairs in (("owner", [(None, group.owner)]), ("emitted", group.emitted),
                                ("duplicate", group.duplicates), ("external", group.externals),
                                ("data", group.data)):
                if any(address == va for _, address in pairs):
                    roles.append("%s of the row 0x%08x%s" % (role, group.owner, " (whole_file)" if group.whole_file else ""))
            if va in group.anon:
                roles.append("anon datum of the row 0x%08x" % group.owner)
        out.extend("unit-objects.json  " + r for r in roles)
    for path in sorted(glob.glob(os.path.join(ROOT, "config", "**", "*"), recursive=True)):
        if not os.path.isfile(path) or os.path.basename(path) in _SKIP_CONFIG or "/names/" in path:
            continue
        try:
            rows = list(tsv_rows(path))
        except UnicodeDecodeError:
            continue
        for number, line in rows:
            if (va is not None and match_addr.search(line)) or (match_name and match_name.search(line)):
                out.append("%s:%d  %s" % (rel(path), number, line[:200]))
    return out


def leading_block(lines, index):
    """The comment and `#pragma` lines directly above `lines[index]` (no blank line between), as
    (first line index, text), or None."""
    first, inside = index, False
    while first > 0:
        line = lines[first - 1].strip()
        if inside:
            inside = "/*" not in line
        elif line.endswith("*/"):
            inside = "/*" not in line
        elif not (line.startswith("//") or line.startswith("#pragma")):
            break
        first -= 1
    return (first, " ".join(lines[first:index])) if first < index else None


_MEMBER_HEAD = re.compile(r"((?:[A-Za-z_]\w*\s*::\s*)+)(~?\s*[A-Za-z_]\w*)\s*\(")


def member_of_head(head):
    """`Class::name` of a member definition head (`T Gap::Gui::igRenderer::setVisualContext(...)`: the class is
    its innermost scope), or None for a free function."""
    m = _MEMBER_HEAD.search(head)
    if not m:
        return None
    return "%s::%s" % (re.sub(r"\s+", "", m.group(1))[:-2].rsplit("::", 1)[-1], m.group(2).replace(" ", ""))


def defined_member(text, start):
    """`Class::name` of the out-of-class member definition starting at `start`, or None."""
    return member_of_head(text[start:text.find("{", start)])


def source(names, datum, match_addr, match_name, limit):
    """A function's definition with its comments, a datum's source lines (at most `limit`), and every
    source line quoting the address. Files are read raw, so line numbers are the file's own (a unity
    unit's fragment is reported as the fragment)."""
    out, defined, uses = [], False, 0
    for p in sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.*"), recursive=True)):
        if not p.endswith((".c", ".cpp", ".h", ".inc", ".S")):
            continue
        with open(p, encoding="utf-8", errors="replace") as fh:
            text = fh.read()
        if datum and match_name and match_name.search(text):
            for number, line in enumerate(text.split("\n"), 1):
                if match_name.search(line):
                    uses += 1
                    if not limit or uses <= limit:
                        out.append("%s:%d  %s" % (rel(p), number, line.strip()[:200]))
            continue
        if not datum and not defined and match_name and not p.endswith(".h") and match_name.search(text):
            found = next(((s, e) for n, s, e in units.definitions(text)
                          if n in names or defined_member(text, s) in names), None)
            if found:
                defined = True
                start, end = found
                lines = text.split("\n")
                first = text.count("\n", 0, text.rfind("\n", 0, start) + 1)
                out.append("defined in %s:%d-%d" % (rel(p), first + 1, text.count("\n", 0, end) + 1))
                lead = leading_block(lines, first)
                if lead:
                    out.append("%d: %s" % (lead[0] + 1, " ".join(lead[1].split())))
                for c in _COMMENT.finditer(text, start, end):
                    out.append("%d: %s" % (text.count("\n", 0, c.start()) + 1, " ".join(c.group(0).split())))
        if match_addr and match_addr.search(text):
            for number, line in enumerate(text.split("\n"), 1):
                if match_addr.search(line):
                    out.append("%s:%d  %s" % (rel(p), number, line.strip()[:200]))
    if limit and uses > limit:
        out.append("… %d more source lines name it" % (uses - limit))
    if not datum and not defined and match_name:
        # a whole-file member defined under another name: tools/units.py resolves it through its row
        index = units.scan(os.path.join(ROOT, "src"), SYMBOLS)
        path = next((index[n] for n in names if n in index), None)
        out.insert(0, "defined in %s (through its unit-objects row)" % rel(path) if path
                   else "no definition in src/")
    return out


def documents(match_addr, match_name, limit):
    """docs/ lines naming the function, grouped by file and heading."""
    entries = levers.load(ROOT)
    out = []
    for path in sorted(glob.glob(os.path.join(ROOT, "docs", "**", "*.md"), recursive=True)):
        heading, shown = "", {}
        with open(path, encoding="utf-8") as fh:
            for number, line in enumerate(fh, 1):
                if line.startswith("#"):
                    heading = line.strip("# \n")
                    continue
                if not ((match_addr and match_addr.search(line)) or (match_name and match_name.search(line))):
                    continue
                where = heading
                if rel(path) == levers.DOC:
                    lever = next((e for e in entries if e["lines"][0] <= number <= e["lines"][1]), None)
                    if lever:
                        where = "lever %s (%s)" % (lever["id"], lever["confidence"])
                shown[where] = shown.get(where, 0) + 1
                if limit and shown[where] > limit:
                    if shown[where] == limit + 1:
                        out.append("%s [%s] … more lines under this heading" % (rel(path), where))
                    continue
                out.append("%s:%d [%s] %s" % (rel(path), number, where, line.strip()[:240]))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("query", help="a symbol, a data name, a compiler or member name (`igRenderer::setVisualContext`) "
                                  "or a retail address (0x2fe9c0, 002fe9c0)")
    ap.add_argument("--max", type=int, default=20, help="document lines shown per heading (0: all)")
    args = ap.parse_args(argv)

    from demangle import demangle
    va, size, symbol = resolve(args.query)
    names = {args.query, symbol} - {None}
    if va is not None:
        names.update(name for name, at in member_names(args.query).items() if at == va)
    for n in list(names):
        # the symbol map writes `Class::method` as `Class__method`, and a whole-file member may be
        # defined under its unit-objects name: its compiler name, and the member that name spells
        if "__" in n.strip("_") and "::" not in n:
            names.add(n.replace("__", "::", 1))
        for compiled in {n, unitobjects.source_name(n, SYMBOLS)}:
            names.add(compiled)
            member = demangle(compiled) if "__" in compiled else None
            if member is not None and member.class_name:
                names.update({member.qualified, "%s::%s" % (member.class_base, member.name)})
    address_query = va is not None and symbol != args.query and _HEX.match(args.query) is not None
    match_addr = address_pattern(va) if va is not None else None
    match_name = name_pattern(names - {args.query} if address_query else names)
    datum = va is not None and size is None
    section("symbol", identity(va, size, symbol, match_addr, match_name))
    section("state", state(va, size is not None, match_addr, match_name))
    section("source", source(names, datum, match_addr, match_name, args.max))
    section("documents", documents(match_addr, match_name, args.max))
    return 0


if __name__ == "__main__":
    sys.exit(main())
