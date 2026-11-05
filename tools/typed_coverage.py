#!/usr/bin/env python3
"""Measure typed coverage: how much of the decompiled C speaks in structs.

Byte-matching is the repo's outward oracle; this is the inward one. m2c's C reproduces
retail instruction-for-instruction while spelling every field as
`*(int *)((char *)p + 12)`, which satisfies the matching build and is useless to another
compiler on another machine -- the port's prerequisite. Two numbers come
out of here:

  * **typed** -- field accesses written as a member of a *recovered* class (one that
    `data/reflection.json`, `config/SLUS-20836/authoritative-fields.tsv` or the class hierarchy names)
    rather than an offset cast, a member of automatch's synthetic `struct G`, or a member of
    a type the metadata does not know. This is the progress bar and the gated count.
  * **typeable** -- of the offset casts that remain, the ones on the function's own receiver
    (`arg0`/`this`) at an offset where the receiver class -- taken from the function's
    `<Class>_<Method>` name -- has a reflected field. It is a *mechanically convertible
    subset* of the raw casts, not a ceiling: casts on other variables, on receivers the name
    does not reveal, or at unreflected offsets are convertible by hand and are not counted.

Comments and string literals are blanked before counting, so `p->field` in a prose
comment or a format string is not an access. The per-folder table shows where the raw
casts remain (`src/engine`, `src/game`, `src/unmatched`, ...).

The types used for a field are not invented: where the matched C already accesses a
(class, offset) with a particular cast, that cast *is* the type (it is byte-exact by
construction), and the reflection metadata supplies the field's name. So a conversion
cannot change codegen unless the type was chosen wrongly, which is what `make check`
catches.

Usage:
    typed_coverage.py                       # the numbers, and the per-folder table
    typed_coverage.py --by-class            # where the recovered and convertible accesses are
    typed_coverage.py --json out.json       # machine-readable detail
    typed_coverage.py --untyped src/x.c     # every untyped access in one file
"""

import argparse
import collections
import glob
import json
import os
import re
import sys

# Reflection's field types are MetaField *classes*; this is the C type they denote. The
# size is what matters for codegen; where the matched code disagrees, the code wins (see
# the module docstring) and the disagreement is reported.
META_TO_C = {
    "igIntMetaField": "int",
    "igEnumMetaField": "int",
    "igUnsignedIntMetaField": "unsigned int",
    "igBoolMetaField": "int",
    "igShortMetaField": "short",
    "igUnsignedShortMetaField": "unsigned short",
    "igLongMetaField": "long long",
    "igUnsignedLongMetaField": "unsigned long long",
    "igCharMetaField": "char",
    "igUnsignedCharMetaField": "unsigned char",
    "igFloatMetaField": "float",
    "igDoubleMetaField": "double",
    "igStringMetaField": "int",          # a handle/pointer, 4 bytes
    "igObjectRefMetaField": "int",       # ditto: a reference, not inline data
    "igRawRefMetaField": "int",
    "igMemoryRefMetaField": "int",
    "igStructMetaField": "int",
    "igVec2fMetaField": "int",           # 8 bytes inline, accessed as words
    "igVec3fMetaField": "int",
    "igVec4fMetaField": "int",
    "igMatrix44fMetaField": "int",
    "igIntArrayMetaField": "int",
    "igFloatArrayMetaField": "int",
    "igCharArrayMetaField": "int",
    "igUnsignedCharArrayMetaField": "int",
    "igEnumArrayMetaField": "int",
    "igShortArrayMetaField": "int",
    "igBoolArrayMetaField": "int",
    "igUnsignedIntArrayMetaField": "int",
    "igUnsignedShortArrayMetaField": "int",
    "igVec4fArrayMetaField": "int",
    "igObjectRefArrayMetaField": "int",
}

FUNC_RE = re.compile(
    r"^(?P<ret>[A-Za-z_][\w \t\*]*?[\s\*])(?P<name>\w+)\s*\((?P<args>[^;{)]*)\)\s*\{",
    re.M)
CAST_RE = re.compile(r"\*\(\s*([A-Za-z_][\w \t\*]*?)\s*\*\s*\)\s*\(")
MEMBER_RE = re.compile(r"\b(\w+)\s*->\s*(\w+)")
# `((T *)base)->field` -- an explicit cast around a temporary, which the passes in
# `scripts/` emit when the object's class comes from reflection rather than the
# variable's declaration (`(void *)(igMetaObject_GetFieldAt(...))` has no declared type).
CAST_OPEN_RE = re.compile(r"\(\s*\(\s*([A-Za-z_]\w*)\s*\*\s*\)")
ARROW_RE = re.compile(r"\s*->\s*(\w+)")
CAST_MEMBER_RE = re.compile(r"\(\s*\(\s*([A-Za-z_]\w*)\s*\*\s*\)\s*(\w+)\s*\)\s*->\s*(\w+)")
# `igMetaObject *g = ...` / `struct G *g = ...` -- the declared type of a pointer is the
# strongest evidence for what a member access on it means, and it is what catches the
# conversion of automatch's synthetic layout into a recovered class.
DECL_RE = re.compile(r"\b(?:struct\s+)?([A-Za-z_]\w*)\s*\*+\s*(\w+)\s*(?:=|;|,|\))")
OFFSET_RE = re.compile(r"[+\-]\s*(\d+)\s*$")


def load_classes(path):
    """{class name: {"fields": [(offset, name, ctype)], "handle": str}}."""
    data = json.load(open(path))
    out = {}
    for handle, o in data["classes"].items():
        fields = []
        for f in o.get("fields") or []:
            fields.append((f["offset"], f["name"],
                           META_TO_C.get(f["type"], "int"), f["type"]))
        fields.sort()
        out[o["class"]] = {"handle": handle, "fields": fields,
                           "by_offset": {off: (nm, ct) for off, nm, ct, _ in fields}}
    # Authoritative fields reflection does not list (config/SLUS-20836/authoritative-fields.tsv).
    overlay = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(path))), "config",
                           "SLUS-20836",
                           "authoritative-fields.tsv")
    if os.path.exists(overlay):
        for line in open(overlay):
            if line.strip() and not line.startswith("#"):
                cls, off, mtype, fname = line.rstrip("\n").split("\t")[:4]
                c = out.setdefault(cls, {"handle": "", "fields": [], "by_offset": {}})
                c["fields"].append((int(off), fname, META_TO_C.get(mtype, "int"), mtype))
                c["fields"].sort()
    # Reflection lists only a class's own fields; the generated include/dw4/reflected.h merges the
    # ancestors' (data/class-hierarchy.tsv), so a member inherited from a base class is typed too.
    base = {}
    hier = os.path.join(os.path.dirname(os.path.abspath(path)), "class-hierarchy.tsv")
    if os.path.exists(hier):
        for line in open(hier):
            if line.strip() and not line.startswith("#"):
                f = line.rstrip("\n").split("\t")
                if len(f) >= 2:
                    base[f[0]] = f[1]
    own = {name: list(c["fields"]) for name, c in out.items()}
    for name, c in out.items():
        seen, cur, merged = {name}, base.get(name), list(own[name])
        while cur and cur not in seen:
            seen.add(cur)
            merged.extend(own.get(cur, []))
            cur = base.get(cur)
        merged.sort()
        c["fields"] = merged
        c["by_offset"] = {off: (nm, ct) for off, nm, ct, _ in merged}
    return out


def class_of(name):
    """The class a function name implies for its first argument, or None.

    The repo's naming is `<Class>_<Method>` (`igMetaEnum_GetNameCount`), so the receiver
    type is recoverable from the name alone. Names with no underscore (`sceMtapPortOpen`)
    imply nothing and are left untyped.
    """
    if name.startswith("Gap__"):
        # `Gap__Bec__<Class>__vfunc_N`: the class is the segment before `__vfunc_`
        parts = name.split("__")
        if len(parts) >= 3 and parts[-1].startswith("vfunc_"):
            return parts[-2]
    if "_" not in name:
        return None
    return name.rsplit("_", 1)[0]


_COMMENT_OR_STRING_RE = re.compile(
    r"/\*.*?\*/"                      # block comment
    r"|//[^\n]*"                      # line comment
    r"|\"(?:\\.|[^\"\\\n])*\""        # string literal
    r"|'(?:\\.|[^'\\\n])*'",          # character literal
    re.S)


def strip_comments_and_strings(text):
    """`text` with every comment and string/character literal blanked to spaces.

    Length and newlines are preserved, so spans and line numbers computed on the result
    index the original file. Blanking rather than deleting is what keeps `--untyped`'s
    excerpts correct.
    """
    def blank(m):
        s = m.group(0)
        return "".join("\n" if ch == "\n" else " " for ch in s)
    return _COMMENT_OR_STRING_RE.sub(blank, text)


def split_functions(text):
    """[(name, args, body_start, body_end)] for top-level definitions in `text`."""
    out = []
    starts = [(m, m.start()) for m in FUNC_RE.finditer(text)]
    for i, (m, pos) in enumerate(starts):
        end = starts[i + 1][1] if i + 1 < len(starts) else len(text)
        out.append((m.group("name"), m.group("args"), pos, end))
    return out


def matching_paren(text, open_idx):
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
    return -1


SYNTH_RE = re.compile(r"struct\s+(\w+)\s*\{([^}]*)\}\s*;")


def synthetic_structs(text):
    """{struct name: [(offset, field)]} for the local `struct G` idiom automatch emits.

    `struct G { char pad[36]; int f; };` -- a layout with no meaning, but an *access
    shape* that already compiles on another machine, which is why it is measured
    separately from a recovered class.
    """
    out = {}
    for m in SYNTH_RE.finditer(text):
        fields, off = [], 0
        for decl in m.group(2).split(";"):
            decl = decl.strip()
            pm = re.match(r"char\s+pad\s*\[\s*(\d+)\s*\]", decl)
            if pm:
                off += int(pm.group(1))
                continue
            fm = re.match(r"([A-Za-z_][\w ]*?)\s*\*?\s*(\w+)$", decl)
            if fm:
                fields.append((off, fm.group(2)))
                off += 4
        out[m.group(1)] = fields
    return out


def accesses(text):
    """Every field access in `text`: (kind, type, offset, base, span).

    kind is "cast" for `*(T *)(base + N)` and "member" for `x->field`.  `base` is the
    expression the offset is applied to, normalised to its innermost identifier when it is
    a plain deref chain, so `*(int *)((char *)(arg0) + 12)` yields base "arg0".
    """
    out = []
    pos = 0
    while True:
        m = CAST_RE.search(text, pos)
        if not m:
            break
        open_idx = m.end() - 1
        close = matching_paren(text, open_idx)
        if close < 0:
            pos = m.end()
            continue
        expr = text[open_idx + 1:close].strip()
        pos = close
        # the offset is the trailing `+ N`; everything before it is the base
        base = expr
        offset = None
        om = OFFSET_RE.search(expr)
        if om:
            offset = int(om.group(1))
            if expr[om.start()] == "-":
                offset = -offset
            base = expr[:om.start()].strip()
        # The root is the innermost identifier the expression is built from.  m2c nests
        # these (`*(int *)((char *)(arg0) + 52)`), and taking the *first* word instead
        # picks up a cast type ("int"), which silently classified nothing.
        root = re.sub(r"\(\s*[A-Za-z_][\w \t\*]*\s*\*\s*\)", "", expr).strip()
        while root.startswith("(") and matching_paren(root, 0) == len(root) - 1:
            root = root[1:-1].strip()
        root = re.sub(r"\(\s*[A-Za-z_][\w \t\*]*\s*\*\s*\)", "", root).strip()
        ident = re.search(r"\b([A-Za-z_]\w*)\b", root)
        out.append(("cast", m.group(1).strip(), offset,
                    ident.group(1) if ident else None, (m.start(), close + 1)))
    # `((T *)expr)->field`: the cast wraps any expression, including a nested reference access
    # (`((beMessenger *)p->_messenger)->_intList`), which is how an arena handle is followed.
    for m in CAST_OPEN_RE.finditer(text):
        close = matching_paren(text, m.start())
        if close < 0:
            continue
        fm = ARROW_RE.match(text, close + 1)
        if fm:
            out.append(("castmember", fm.group(1), None, m.group(1), (m.start(), fm.end())))
    for m in MEMBER_RE.finditer(text):
        # the member *name* goes in the type slot; a member access has no offset cast
        out.append(("member", m.group(2), None, m.group(1), (m.start(), m.end())))
    out.sort(key=lambda a: a[4][0])
    return out


def measure(reflection="data/reflection.json", src="src"):
    """The two numbers, plus what could be converted and where.

    Called by tools/progress.py as well as by the CLI, so the published figure and the
    one this tool prints can never disagree.
    """
    classes = load_classes(reflection)
    # `dw4u_*` are the transient one-function splits tools/units.py writes while a check
    # runs; they duplicate a unit's function and may vanish mid-walk, so they are not units.
    files = sorted(p for p in glob.glob(os.path.join(src, "**", "*.c"), recursive=True) +
                   glob.glob(os.path.join(src, "**", "*.cpp"), recursive=True)
                   if not os.path.basename(p).startswith("dw4u_"))
    observed = collections.defaultdict(collections.Counter)
    stats = dict(total=0, offset_casts=0, recovered=0, synthetic=0, other_members=0,
                 typeable=0, by_class={}, typeable_by_class={}, accesses=[],
                 files=len(files), parsed=0,
                 pairs=0, conflicting_pairs=0, per_function={}, by_folder={})
    for path in files:
        # Comments and literals are blanked first: a `p->field` in prose, or in a format
        # string, is not an access.
        try:
            text = strip_comments_and_strings(open(path, errors="replace").read())
        except FileNotFoundError:        # removed between the walk and the read
            continue
        folder = os.path.relpath(path, src).split(os.sep)[0]
        if folder.endswith((".c", ".cpp")):
            folder = "."                      # a file at the root of src/
        ff = stats["by_folder"].setdefault(
            folder, dict(total=0, offset_casts=0, recovered=0, synthetic=0,
                         other_members=0, files=0))
        ff["files"] += 1
        synth_structs = synthetic_structs(text)
        fns = split_functions(text)
        if fns:
            stats["parsed"] += 1
        for name, _signature, start, end in fns:
            body = text[start:end]
            cls = class_of(name)
            rec = classes.get(cls) if cls else None
            decls = {var: t for t, var in DECL_RE.findall(body)}
            fc = collections.Counter()
            stats["per_function"][(path, name)] = fc
            for kind, ctype, offset, base, span in accesses(body):
                ff["total"] += 1
                if kind == "member":
                    member, decl_class = ctype, decls.get(base)
                    if decl_class is None and base in ("arg0", "this"):
                        decl_class = cls
                    if decl_class and decl_class in synth_structs and \
                            any(f[1] == member for f in synth_structs[decl_class]):
                        stats["synthetic"] += 1
                        ff["synthetic"] += 1
                        fc["synthetic"] += 1
                    elif decl_class in classes and \
                            any(f[1] == member for f in classes[decl_class]["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][decl_class] = stats["by_class"].get(decl_class, 0) + 1
                    elif rec and any(f[1] == member for f in rec["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][cls] = stats["by_class"].get(cls, 0) + 1
                    else:
                        stats["other_members"] += 1
                        ff["other_members"] += 1
                        fc["other"] += 1
                    continue
                if kind == "castmember":
                    member, decl_class = ctype, base
                    if decl_class in classes and \
                            any(f[1] == member for f in classes[decl_class]["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][decl_class] = \
                            stats["by_class"].get(decl_class, 0) + 1
                    else:
                        stats["other_members"] += 1
                        ff["other_members"] += 1
                        fc["other"] += 1
                    continue
                stats["offset_casts"] += 1
                ff["offset_casts"] += 1
                fc["raw"] += 1
                if rec is None or offset is None or base not in ("arg0", "this"):
                    continue
                field = rec["by_offset"].get(offset)
                if not field:
                    continue
                observed[(cls, offset)][ctype] += 1
                stats["typeable"] += 1
                stats["typeable_by_class"][cls] = stats["typeable_by_class"].get(cls, 0) + 1
                stats["accesses"].append({"file": path, "function": name, "class": cls,
                                          "offset": offset, "field": field[0],
                                          "cast_type": ctype})
    stats["total"] = (stats["offset_casts"] + stats["recovered"] + stats["synthetic"] +
                      stats["other_members"])
    for ff in stats["by_folder"].values():
        ff["recovered_pct"] = round(100.0 * ff["recovered"] / max(1, ff["total"]), 2)
    stats["pairs"] = len(observed)
    stats["conflicting_pairs"] = sum(1 for v in observed.values() if len(v) > 1)
    stats["recovered_pct"] = round(100.0 * stats["recovered"] / max(1, stats["total"]), 2)
    stats["typeable_pct"] = round(100.0 * stats["typeable"] / max(1, stats["total"]), 2)
    return stats


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--reflection", default="data/reflection.json")
    ap.add_argument("--src", default="src")
    ap.add_argument("--json")
    ap.add_argument("--by-class", action="store_true")
    ap.add_argument("--untyped", metavar="FILE", help="list the untyped accesses in one file")
    ap.add_argument("--baseline", default="config/typed-coverage.json",
                    help="recorded coverage this run is compared against")
    ap.add_argument("--check", action="store_true",
                    help="fail unless this run matches the baseline (what CI runs)")
    ap.add_argument("--update-baseline", action="store_true",
                    help="record this run as the baseline (commit the result)")
    args = ap.parse_args()

    if args.untyped:
        raw = open(args.untyped).read()
        for kind, ctype, offset, base, span in accesses(strip_comments_and_strings(raw)):
            if kind == "cast":
                print("  %-16s +%-6s base=%-12s %s"
                      % (ctype, offset, base, raw[span[0]:span[1]][:60]))
        return

    # One analysis, used by the report, the baseline gate and tools/progress.py, so the
    # published figure and the checked one can never disagree.
    t = measure(args.reflection, args.src)
    total, recovered = t["total"], t["recovered"]
    by_class = collections.Counter(t["by_class"])

    print("typed coverage")
    print("  field accesses in matched C: %d" % total)
    print("    offset casts (untyped):        %5d (%.1f%%)" % (t["offset_casts"], 100.0 * t["offset_casts"] / max(1, total)))
    print("    members on a *recovered* class:%5d (%.1f%%)   <- the port's number" % (recovered, t["recovered_pct"]))
    print("    members on a synthetic layout:%5d (%.1f%%)   (automatch's `struct G`)" % (t["synthetic"], 100.0 * t["synthetic"] / max(1, total)))
    print("    other member accesses:        %5d (%.1f%%)" % (t["other_members"], 100.0 * t["other_members"] / max(1, total)))
    print("  raw casts on the named receiver at a reflected offset (mechanically convertible): %d (%.1f%% of accesses)"
          % (t["typeable"], t["typeable_pct"]))
    print("  files parsed: %d of %d" % (t["parsed"], t["files"]))
    print("  distinct (class, offset) pairs with both evidence sources: %d" % t["pairs"])
    print("  pairs where the matched C uses more than one cast type: %d "
          "(a conversion has to pick one, or leave them raw)" % t["conflicting_pairs"])
    print("\n  by top-level src folder (comments and string literals excluded):")
    print("    %-12s %6s %9s %9s %9s %9s %7s" % ("folder", "files", "accesses", "recovered",
                                                "raw", "synthetic", "typed%"))
    for folder, ff in sorted(t["by_folder"].items(), key=lambda kv: -kv[1]["total"]):
        print("    %-12s %6d %9d %9d %9d %9d %6.1f%%"
              % (folder, ff["files"], ff["total"], ff["recovered"], ff["offset_casts"],
                 ff["synthetic"], ff["recovered_pct"]))
    if args.by_class:
        print("\n  recovered accesses by class (what the baseline tracks):")
        for cls, n in by_class.most_common(25):
            print("    %-42s %4d" % (cls, n))
        print("\n  raw casts on the named receiver at a reflected offset, by class (convertible now):")
        for cls, n in collections.Counter(t["typeable_by_class"]).most_common(10):
            print("    %-42s %4d" % (cls, n))

    measured = {"recovered": recovered, "total": total,
                "offset_casts": t["offset_casts"], "synthetic": t["synthetic"],
                "by_class": dict(by_class), "typeable": t["typeable"],
                "by_folder": {k: {kk: vv for kk, vv in v.items()}
                              for k, v in sorted(t["by_folder"].items())}}

    if args.update_baseline:
        json.dump({"note": "Baseline for tools/typed_coverage.py --check. The gate is on the "
                           "*count* of recovered accesses, never on the percentage: the m2c loop "
                           "keeps adding matched (and so untyped) C, so the ratio can fall while "
                           "the count only grows. Update it deliberately with --update-baseline "
                           "and commit, so every change in coverage is a reviewed diff.",
                   **measured}, open(args.baseline, "w"), indent=1, sort_keys=True)
        print("\nrecorded baseline: %s (%d recovered of %d accesses)" % (args.baseline, recovered, total))
        return

    if args.check:
        try:
            base = json.load(open(args.baseline))
        except FileNotFoundError:
            print("typed coverage: no baseline at %s — run --update-baseline" % args.baseline)
            raise SystemExit(1)
        was = base.get("recovered", 0)
        base_class = base.get("by_class", {})
        moved = {k for k in set(base_class) | set(by_class)
                 if base_class.get(k, 0) != by_class.get(k, 0)}
        if recovered == was and not moved:
            print("typed coverage: %d recovered accesses, baseline matches" % recovered)
            return
        if recovered == was:
            # the count held but the accesses changed owner -- still a change worth reviewing,
            # otherwise a class could lose its typing invisibly
            print("typed coverage: MOVED — %d recovered accesses unchanged, but %d class(es) differ"
                  % (recovered, len(moved)))
            for cls in sorted(moved):
                print("    %-42s %+d" % (cls, by_class.get(cls, 0) - base_class.get(cls, 0)))
            print("    run --update-baseline and commit %s to record it" % args.baseline)
            raise SystemExit(1)
        print("typed coverage: %s — %d recovered accesses, baseline %d (%+d)"
              % ("REGRESSION" if recovered < was else "GAIN", recovered, was, recovered - was))
        for cls in sorted(set(base.get("by_class", {})) | set(by_class)):
            delta = by_class.get(cls, 0) - base.get("by_class", {}).get(cls, 0)
            if delta:
                print("    %-42s %+d" % (cls, delta))
        print("    %d of %d accesses are still raw casts" % (t["offset_casts"], total))
        if recovered < was:
            print("    a drop means typing was removed, or moved to another class: restore it, "
                  "or update the baseline deliberately if the move was intended")
        else:
            print("    run --update-baseline and commit %s, so the gain is recorded"
                  % args.baseline)
        raise SystemExit(1)

    if args.json:
        json.dump(measured, open(args.json, "w"), indent=1, sort_keys=True)
        print("\nwrote %s" % args.json)


if __name__ == "__main__":
    main()
