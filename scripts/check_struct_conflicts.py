#!/usr/bin/env python3
"""Report the local struct/class views of src/ that disagree with each other or with reflected.h.

Matched units declare *local views* of the objects they touch: `struct Pool { int vt; unsigned rc;
int count; ... }` names only the offsets one function uses.  That is fine for one unit, but the
same view name is reused across units with different members, and a view of a reflected class can
drift from the recovered layout.  This script parses every struct/class/union body in
src/**/*.c, src/**/*.cpp and include/dw4/ (reflected.h excluded, it is the reference), computes
each member's offset and size, and reports:

  (a) the same non-generic name defined in several units with members that clash at the same
      offset (different size, or one straddling another) or with different total sizes;
  (b) the receiver view of a unit named for a reflected class (`<Class>_<Method>`, `Gap__*__<Class>__vfunc_N`)
      whose member at an offset disagrees in size with the reflected field there, or lies beyond
      the registered instance size. The receiver is the view named for the class or taken as a function's
      first parameter, or any view of a `_GetVTable` or `_Construct` unit; other local views describe
      other objects;
  (c) an offset-named member (`fNN`, `wNN`, `pNN`, `_NN`, ...) whose NN is not the member's
      decimal offset (hex spellings `f0x1c` / `f_1c` are accepted when they match).

The output is grouped by struct name with file:line pairs.  It is a report, not a gate
(`make struct-report`): the lead schedules the fixes.  The parser is approximate (no
preprocessor); unknown member types are sized 0 and the view is marked `~` in the report.

Usage: scripts/check_struct_conflicts.py [--src src] [--include include/dw4]
                                         [--reflected include/dw4/reflected.h] [--only a,b,c]
"""
import argparse
import collections
import glob
import os
import re
import sys

BASIC = {
    "char": 1, "signed char": 1, "unsigned char": 1, "bool": 1, "u8": 1, "s8": 1, "png_byte": 1, "Bytef": 1,
    "Byte": 1, "uch": 1, "uchar": 1,
    "short": 2, "unsigned short": 2, "signed short": 2, "u16": 2, "s16": 2, "png_uint_16": 2, "ush": 2,
    "ushort": 2, "uShort": 2,
    "int": 4, "unsigned": 4, "unsigned int": 4, "signed int": 4, "signed": 4, "float": 4, "long": 4,
    "unsigned long": 4, "u32": 4, "s32": 4, "png_uint_32": 4, "uInt": 4, "uLong": 4, "uLongf": 4, "size_t": 4,
    "ulg": 4, "png_size_t": 4, "int32": 4, "uint32": 4, "ptrdiff_t": 4, "void": 0,
    "long long": 8, "unsigned long long": 8, "signed long long": 8, "double": 8, "u64": 8, "s64": 8,
    "long double": 8, "u128": 16, "u_long128": 16, "uint128": 16,
}
PAD_RE = re.compile(r"^(_?pad|_?p\d|pad\d|_?unk|gap|skip|filler|dummy|reserved|_reserved|_?unused|_gap|_skip|_reflected)", re.I)
# names that mean nothing outside the one unit (a conflict between two `struct S` is no finding)
GENERIC_RE = re.compile(r"^(?:[A-Z][a-z]?\d?|S\d+|Obj|Ref|Self|View|Arg\d?|Tmp)$")
OFFSET_NAME_RE = re.compile(r"^(?:[fwpvbd]|_|f_|w_|p_)(0x[0-9a-fA-F]+|\d+|[0-9a-fA-F]*\d[0-9a-fA-F]*)$")
BODY_RE = re.compile(r"(?:^|[;{}\n])\s*(typedef\s+)?(struct|class|union)\s+([A-Za-z_]\w*)\s*"
                     r"(?::\s*((?:public|private|protected)?\s*[A-Za-z_][\w:]*(?:\s*,\s*(?:public|private|protected)?\s*"
                     r"[A-Za-z_][\w:]*)*)\s*)?\{")
REFLECTED_STRUCT_RE = re.compile(r"/\* handle 0x[0-9a-f]+, \d+ field\(s\), sizeof (\d+) [^*]*\*/\n"
                                 r"typedef struct (\w+) \{(.*?)\n\} \2;", re.S)
REFLECTED_FIELD_RE = re.compile(r"^\s*([A-Za-z_][\w ]*?)\s*(\w+)((?:\[\d+\])*);\s*(?:/\*[^*]*\*/\s*)?/\*\s*\+(\d+)\s+(\w+)",
                                re.M)

Member = collections.namedtuple("Member", "name type size offset count")
View = collections.namedtuple("View", "kind name base members size file line nvirtual unknown")


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    # drop preprocessor lines: a `#define` body is not a member
    return re.sub(r"^\s*#[^\n]*(?:\\\n[^\n]*)*", "", text, flags=re.M)


def bodies(text):
    """Yield (kind, name, base, body, line) for every struct/class/union body in `text`."""
    for m in BODY_RE.finditer(text):
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += (text[i] == "{") - (text[i] == "}")
            i += 1
        yield m.group(2), m.group(3), (m.group(4) or "").strip(), text[m.end():i - 1], text[:m.start()].count("\n") + 1


def statements(body):
    """Top-level `;`-separated statements of a body, with nested braces kept whole."""
    out, cur, depth = [], "", 0
    for c in body:
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0 and cur.strip():
                out.append(cur.strip() + "}")
                cur = ""
                continue
        if depth == 0 and c == ";":
            out.append(cur.strip())
            cur = ""
            continue
        cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


def type_size(tname, local, reflected):
    """(element size, alignment) of a C type name, or (None, 4) when unknown."""
    tname = re.sub(r"\b(const|volatile|struct|class|union|enum|extern \"C\")\b", "", tname)
    tname = re.sub(r"\s+", " ", tname).strip()
    if "*" in tname or tname.startswith("enum"):
        return 4, 4
    if tname in BASIC:
        s = BASIC[tname]
        return s, (min(s, 8) if s else 1)
    if tname in local:
        return local[tname]
    if tname in reflected:
        return reflected[tname]["size"], 4
    return None, 4


def parse_view(kind, name, base, body, local, reflected, path, line):
    members, offset, maxalign, nvirtual, unknown = [], 0, 1, 0, False
    base_names = [b.strip().split()[-1] for b in base.split(",")] if base else []
    for b in base_names:
        if b in local:
            offset = max(offset, local[b][0] or 0)
        elif b in reflected:
            offset = max(offset, reflected[b]["size"])
        else:
            unknown = True
    has_vptr = False
    bits_used, bf_off, bf_size = 0, None, 0   # the open bit-field storage unit, if any
    for s in statements(body):
        s = re.sub(r"^(public|private|protected)\s*:\s*", "", s.strip())
        if not s:
            continue
        if s.startswith("virtual"):
            nvirtual += 1
            if not has_vptr and not base_names:
                has_vptr = True
                members.append(Member("<vptr>", "void *", 4, 0, 1))
                offset, maxalign = max(offset, 4), max(maxalign, 4)
            continue
        if re.match(r"^(static|typedef|friend|using|enum)\b", s):
            continue
        if re.match(r"^(struct|union|class)\s+\w*\s*\{", s):
            # a nested aggregate: size it recursively when it declares a member
            inner = re.match(r"^(struct|union|class)\s+(\w*)\s*\{(.*)\}\s*(\w*)\s*((?:\[[^\]]*\])*)$", s, re.S)
            if not inner:
                unknown = True
                continue
            v = parse_view(inner.group(1), inner.group(2) or "<anon>", "", inner.group(3), local, reflected, path, line)
            if inner.group(4):
                al = 4
                off = (offset + al - 1) // al * al
                members.append(Member(inner.group(4), inner.group(1), v.size, off, 1))
                offset = off + v.size
                maxalign = max(maxalign, al)
            unknown = unknown or v.unknown
            continue
        if "(" in s and not re.search(r"\(\s*\*\s*[A-Za-z_]", s):
            continue  # a method declaration or definition
        fp = re.match(r"^(.+?)\(\s*\*\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*\)\s*\(.*\)$", s, re.S)
        if fp:
            count = 1
            if fp.group(3):
                try:
                    count = int(eval(fp.group(3)[1:-1], {}, {}))
                except Exception:
                    unknown = True
            off = (offset + 3) // 4 * 4
            members.append(Member(fp.group(2), "void (*)()", 4 * count, off, count))
            offset, maxalign = off + 4 * count, max(maxalign, 4)
            continue
        bf = re.match(r"^(.+?)\s*:\s*(\d+)$", s)
        if bf:
            s = bf.group(1)
        parts = [x.strip() for x in s.split(",")]
        dm = re.match(r"^(.+?)\s*(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(?:=.*)?$", parts[0], re.S)
        if not dm:
            unknown = True
            continue
        tname = dm.group(1).strip()
        decls = [(dm.group(2), dm.group(3), dm.group(4))]
        for d in parts[1:]:
            dm2 = re.match(r"^(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(?:=.*)?$", d, re.S)
            if dm2:
                decls.append((dm2.group(1), dm2.group(2), dm2.group(3)))
            else:
                unknown = True
        for ptr, mname, arrtxt in decls:
            count = 1
            for a in re.findall(r"\[([^\]]*)\]", arrtxt):
                try:
                    count *= int(eval(a, {}, {}))
                except Exception:
                    unknown = True
            t = tname + ("*" if ptr else "")
            esize, al = type_size(t, local, reflected)
            if esize is None:
                unknown = True
                esize = 0
            if bf:
                width = int(bf.group(2))
                if bf_off is not None and bf_size == esize and bits_used + width <= 8 * esize:
                    off = bf_off                      # packs into the open storage unit
                else:
                    off = (offset + al - 1) // al * al if al else offset
                    bf_off, bf_size, bits_used = off, esize, 0
                    offset = off + esize
                bits_used += width
                members.append(Member(mname, t + ":" + bf.group(2), esize, off, count))
                continue
            bf_off = None
            off = (offset + al - 1) // al * al if al else offset
            members.append(Member(mname, t, esize * count, off, count))
            offset = off + esize * count
            maxalign = max(maxalign, al)
    if kind == "union":
        size = max([m.offset + m.size for m in members] or [0])
        members = [m._replace(offset=0) for m in members]
        unknown = True
    else:
        size = (offset + maxalign - 1) // maxalign * maxalign if maxalign else offset
    return View(kind, name, base_names, members, size, path, line, nvirtual, unknown)


def parse_reflected(path):
    out = {}
    text = open(path, errors="replace").read()
    for m in REFLECTED_STRUCT_RE.finditer(text):
        fields = {}
        for fm in REFLECTED_FIELD_RE.finditer(m.group(3)):
            t, name, arr, off, kind = fm.groups()
            count = 1
            for a in re.findall(r"\[(\d+)\]", arr):
                count *= int(a)
            es = BASIC.get(re.sub(r"\s+", " ", t.strip()), 4)
            fields[int(off)] = (name, t.strip(), es * count)
        out[m.group(2)] = {"size": int(m.group(1)), "fields": fields}
    return out


def class_of_unit(path):
    """The reflected class a unit's file name implies, or None."""
    base = os.path.splitext(os.path.basename(path))[0]
    if base.startswith("Gap__"):
        parts = base.split("__")
        if len(parts) >= 3 and parts[-1].startswith("vfunc_"):
            return parts[-2]
    if "__" in base:
        return base.split("__", 1)[0]
    if "_" in base:
        return base.rsplit("_", 1)[0]
    return None


def collect(files, reflected):
    views = []
    for path in files:
        text = strip_comments(open(path, errors="replace").read())
        local = {}
        for kind, name, base, body, line in bodies(text):
            v = parse_view(kind, name, base, body, local, reflected, path, line)
            local[name] = (v.size, 4)
            views.append(v)
    return views


def report_a(views, out):
    """Same non-generic name across units with clashing members or sizes."""
    by_name = collections.defaultdict(list)
    for v in views:
        if v.members and not GENERIC_RE.match(v.name) and v.kind != "union":
            by_name[v.name].append(v)
    groups = 0
    for name in sorted(by_name):
        vs = by_name[name]
        if len({v.file for v in vs}) < 2:
            continue
        lines = []
        for i, x in enumerate(vs):
            for y in vs[i + 1:]:
                if x.file == y.file:
                    continue
                xm = {m.offset: m for m in x.members if not PAD_RE.match(m.name)}
                for m in y.members:
                    if PAD_RE.match(m.name):
                        continue
                    o = xm.get(m.offset)
                    if o and o.size != m.size and o.size and m.size:
                        lines.append("  +%d: %s %s[%d] (%s:%d) vs %s %s[%d] (%s:%d)"
                                     % (m.offset, o.type, o.name, o.size, x.file, x.line, m.type, m.name, m.size, y.file, y.line))
                    for o2 in xm.values():
                        if o2.offset < m.offset < o2.offset + o2.size and o2.size and m.size:
                            lines.append("  %s@%d[%d] (%s:%d) straddles %s@%d (%s:%d)"
                                         % (o2.name, o2.offset, o2.size, x.file, x.line, m.name, m.offset, y.file, y.line))
                if x.size != y.size and not x.unknown and not y.unknown:
                    lines.append("  size %d (%s:%d) vs %d (%s:%d)" % (x.size, x.file, x.line, y.size, y.file, y.line))
        if lines:
            groups += 1
            out.append("%s: %d definitions in %d files" % (name, len(vs), len({v.file for v in vs})))
            out.extend(sorted(set(lines))[:12])
    return groups


# The first parameter of a function definition, when it is a pointer or reference to a named type: the
# receiver of a unit named `<Class>_<Method>` or `Gap__*__<Class>__vfunc_N`.
RECEIVER_RE = re.compile(r"\b\w+\s*\(\s*(?:const\s+)?(?:struct\s+|class\s+)?(\w+)\s*(?:const\s*)?[*&]"
                         r"[^;{}()]*(?:\([^;{}()]*\)[^;{}()]*)*\)\s*(?:const\s*)?\{")
_receivers = {}


def receivers(path):
    """The type names a file's function definitions take as their first, receiving parameter."""
    if path not in _receivers:
        text = strip_comments(open(path, errors="replace").read())
        _receivers[path] = set(RECEIVER_RE.findall(text))
    return _receivers[path]


def _builds_instance(path):
    return os.path.splitext(os.path.basename(path))[0].endswith(("_GetVTable", "_Construct"))


def report_b(views, reflected, out):
    """A receiver view in a unit named for a reflected class vs the recovered layout. A view counts
    as the receiver when it is named for the class or a function of the unit takes it as its first
    parameter; another local struct of the file describes some other object. A `<Class>_GetVTable` or
    `<Class>_Construct` unit builds an instance of the class itself, so every view there counts."""
    groups = 0
    by_class = collections.defaultdict(list)
    for v in views:
        cls = class_of_unit(v.file)
        if cls in reflected and v.members and v.kind != "union" and "reflected.h" not in v.file \
                and (v.name == cls or v.name in receivers(v.file) or _builds_instance(v.file)):
            by_class[cls].append(v)
    for cls in sorted(by_class):
        ref = reflected[cls]
        lines = []
        for v in by_class[cls]:
            if v.nvirtual:
                continue  # a dummy-vtable view carries no layout
            # a view that embeds the reflected struct, or whose first member is of a reflected type, is a wrapper
            if any(m.type in reflected for m in v.members):
                continue
            for m in v.members:
                if PAD_RE.match(m.name) or not m.size or m.name == "<vptr>":
                    continue
                if m.offset >= ref["size"]:
                    lines.append("  %s:%d (%s %s): %s %s@%d is beyond the registered size %d"
                                 % (v.file, v.line, v.kind, v.name, m.type, m.name, m.offset, ref["size"]))
                    continue
                f = ref["fields"].get(m.offset)
                if f is None:
                    inside = [(o, g) for o, g in ref["fields"].items() if o < m.offset < o + g[2]]
                    if inside:
                        o, g = inside[0]
                        lines.append("  %s:%d (%s %s): %s %s@%d sits inside reflected %s %s@%d"
                                     % (v.file, v.line, v.kind, v.name, m.type, m.name, m.offset, g[1], g[0], o))
                    continue
                if f[2] != m.size and m.count == 1:
                    lines.append("  %s:%d (%s %s): %s %s@%d is %d bytes, reflected %s %s is %d"
                                 % (v.file, v.line, v.kind, v.name, m.type, m.name, m.offset, m.size, f[1], f[0], f[2]))
        if lines:
            groups += 1
            out.append("%s (reflected, %d bytes): %d view(s) disagree" % (cls, ref["size"], len(lines)))
            out.extend(sorted(set(lines))[:12])
    return groups


def report_c(views, out):
    """Offset-named members whose number is not the member's offset."""
    groups = 0
    for v in views:
        if v.kind == "union":
            continue
        lines = []
        for m in v.members:
            om = OFFSET_NAME_RE.match(m.name)
            if not om or PAD_RE.match(m.name):
                continue
            digits = om.group(1)
            if digits.startswith("0x") or re.search(r"[a-fA-F]", digits):
                claimed = int(digits, 16)   # an explicit or unmistakable hex spelling
            else:
                claimed = int(digits, 10)   # the project convention: decimal offsets
            if m.offset != claimed and not v.unknown:
                lines.append("  %s:%d (%s %s): %s %s is at +%d" % (v.file, v.line, v.kind, v.name, m.type, m.name, m.offset))
        if lines:
            groups += 1
            out.append("%s %s (%s:%d): %d offset-named member(s) off" % (v.kind, v.name, v.file, v.line, len(lines)))
            out.extend(lines[:8])
    return groups


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default="src")
    ap.add_argument("--include", default="include/dw4")
    ap.add_argument("--reflected", default="include/dw4/reflected.h")
    ap.add_argument("--only", default="a,b,c", help="which reports to print (default all)")
    a = ap.parse_args(argv)
    reflected = parse_reflected(a.reflected)
    files = sorted(glob.glob(os.path.join(a.src, "**", "*.c"), recursive=True)
                   + glob.glob(os.path.join(a.src, "**", "*.cpp"), recursive=True)
                   + [f for f in glob.glob(os.path.join(a.include, "**", "*"), recursive=True) if os.path.isfile(f)])
    files = [f for f in files if "/asmbody/" not in f and os.path.abspath(f) != os.path.abspath(a.reflected)]
    views = collect(files, reflected)
    out = []
    counts = {}
    if "a" in a.only:
        out.append("==== (a) same struct name, clashing layouts across units ====")
        counts["a"] = report_a(views, out)
        out.append("")
    if "b" in a.only:
        out.append("==== (b) receiver views vs the reflected class the unit is named for ====")
        counts["b"] = report_b(views, reflected, out)
        out.append("")
    if "c" in a.only:
        out.append("==== (c) offset-named members (fNN) whose NN is not the member's offset ====")
        counts["c"] = report_c(views, out)
        out.append("")
    print("\n".join(out))
    print("struct report: %d views in %d files; %s" % (
        len(views), len(files), ", ".join("(%s) %d group(s)" % (k, v) for k, v in sorted(counts.items()))))
    return 0


if __name__ == "__main__":
    sys.exit(main())
