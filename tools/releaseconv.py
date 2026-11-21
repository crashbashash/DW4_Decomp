#!/usr/bin/env python3
"""releaseconv.py — write the open reference-count idioms as the kit's igObject::ref()/release().

Retail open-codes Alchemy's inline release at every site, and the decompiled source spells it the same way:

    if (obj != 0) {
        obj->_refCount = obj->_refCount - 1;
        if ((obj->_refCount & 0x7FFFFF) == 0) igObject_Destroy(obj);
    }

The kit (alchemy-kit_202309 igCore/igObject.h) writes that as `igObject::release(obj)`, and as `obj->release()`
where the object is known not to be null; the increment `obj->_refCount = obj->_refCount + 1` is `ref()`. The
generated igObject's reference word is the kit's union, whose `release()` compiles to the decrement, the reload
and the `dsll32 9`/`dsrl32 9` test every site has (docs/engine/member-conversion.md); the flat struct's C++
view forwards to it. This tool rewrites the spellings it recognises:

- the decrement (`p->_refCount = p->_refCount - 1;`, with `(int)` casts or the extra parentheses of a
  decompiled body, `--p->_refCount;`, `p->_refCount--;`, `p->_refCount -= 1;`), then the 23-bit test (the
  `& 0x7fffff` mask, its 64-bit form, or the `<< 0x29 >> 0x29` shift pair) calling `igObject_Destroy` on the
  same object, becomes `p->release();`; inside an `if (p != 0) { ... }` that holds nothing else, the whole
  `if` becomes `igObject::release(p);`;
- the increment (`p->_refCount = p->_refCount + 1;`, `++p->_refCount;`, `p->_refCount++;`,
  `p->_refCount += 1;`) becomes `p->ref();`, and under an `if (p != 0)` holding nothing else
  `igObject::ref(p);`;
- a call of DW4's release helper `igRelease(p)` (include/dw4/core/igSmartPointer.h, which holds the guarded
  release) becomes the kit's static `igObject::release(p)`; `--view FILE:LINE=CLASS` writes it as
  `CLASS::release(p)` for a pointer typed as a view that carries the kit statics (`igVirtualObject`,
  `igObjectDispatchView`).

Only the `_refCount` word is read: local views spelling it `f4` or `refs`, or reading `+4` through casts, stay
open until their type is written. Whether a site's pointer has the members (a converted class, or a flat struct
deriving from the flat igObject) is the compiler's call: `--member FILE:LINE` keeps a site's `if` and writes
only the call inside it (code in `Gap` holding a flat pointer, where `igObject` is the Gap class), and `--keep
FILE:LINE` leaves a site as it is (its pointer is a view, or the rewritten unit no longer matches). LINE is the
first line of the site in the file as it was (`--sites` lists them, with each site's lines after the rewrite).

usage: releaseconv.py FILE... [--member FILE:LINE]... [--keep FILE:LINE]... [--view FILE:LINE=CLASS]...
                      [--sites] [--dry-run]
Tests: tools/test_releaseconv.py.
"""
import argparse
import re
import sys

_CAST = re.compile(r"\(\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?"
                   r"(?:int|long\s+long|long|short|char|(?:::)?(?:Gap\s*::\s*Core\s*::\s*)?igObject\s*\*)\s*\)")
_EXPR = r"[^;{}=\n]+?"
_DEC = re.compile(r"(?:--\s*(?P<d1>%s)\s*->\s*_refCount\s*;"
                  r"|(?P<d2>%s)\s*->\s*_refCount\s*(?:--|-=\s*1)\s*;"
                  r"|(?P<d3>%s)\s*->\s*_refCount\s*=\s*(?P<rhs>[^;{}]+);)" % (_EXPR, _EXPR, _EXPR))
_TEST = re.compile(r"\s*if\s*\((?P<cond>[^;{}]*?)\)\s*(?P<open>\{\s*)?"
                   r"(?:igObject_Destroy\s*\((?P<arg>[^;{}]*?)\)|(?P<self>[^;{}]*?)\s*->\s*internalRelease\s*\(\s*\))\s*;"
                   r"(?(open)\s*\})")
_INC = re.compile(r"(?:\+\+\s*(?P<i1>%s)\s*->\s*_refCount\s*;"
                  r"|(?P<i2>%s)\s*->\s*_refCount\s*(?:\+\+|\+=\s*1)\s*;"
                  r"|(?P<i3>%s)\s*->\s*_refCount\s*=\s*(?P<rhs>[^;{}]+);)" % (_EXPR, _EXPR, _EXPR))
_LEAD = re.compile(r"(?:^|(?<=[;{}]))[ \t]*", re.M)
_GUARD = re.compile(r"if\s*\(\s*(?P<w>[^;{}]+?)\s*(?:!=\s*(?:0|NULL)\s*)?\)\s*(?P<open>\{)?\s*$")
_HELPER = re.compile(r"(?<![\w:.>])igRelease\s*\(")


def bare(expr):
    """`expr` with the casts the decompiled spellings add, whitespace and parentheses removed: two spellings
    of one object compare equal."""
    return re.sub(r"[\s()]", "", _CAST.sub("", expr))


def _tests_zero(cond, obj):
    word = bare(obj) + "->_refCount"
    return bare(cond).lower() in {(word + tail).lower() for tail in
                                  ("&0x7fffff==0", "&0x7fffffull==0", "<<0x29>>0x29==0", "<<41>>41==0")}


def _postfix(expr):
    """Whether `expr` is a postfix expression (`p`, `(*pp)`, `self->_list[i]`, `((igNode *)p)`), the receiver
    `->` binds to; `*pp` or `(igNode *)p` before `->_refCount` reads the word of something else."""
    i, n = 0, len(expr)
    m = re.match(r"\w+", expr)
    if m:
        i = m.end()
    elif expr.startswith("("):
        i = _close(expr, 0)
        if i is None:
            return False
    else:
        return False
    while i < n:
        m = re.match(r"\s*(?:->|\.)\s*\w+", expr[i:])
        if m:
            i += m.end()
        elif expr.startswith("[", i):
            depth = 0
            for j in range(i, n):
                depth += {"[": 1, "]": -1}.get(expr[j], 0)
                if depth == 0:
                    break
            else:
                return False
            i = j + 1
        else:
            return False
    return True


def _close(expr, i):
    """The index after the parenthesis closing the one at `expr[i]`, or None."""
    depth = 0
    for j in range(i, len(expr)):
        depth += {"(": 1, ")": -1}.get(expr[j], 0)
        if depth == 0:
            return j + 1
    return None


def _target(m, names):
    for name in names:
        if m.group(name) is not None:
            obj = m.group(name).strip()
            return obj if _postfix(obj) else None
    return None


def _step_ok(m, obj, sign):
    rhs = m.group("rhs")
    word = bare(obj) + "->_refCount"
    return rhs is None or bare(rhs) in (word + sign + "1", "1+" + word if sign == "+" else None)


class Site:
    def __init__(self, kind, start, end, obj, guard, indent, line):
        self.kind = kind              # "release" or "ref"
        self.start, self.end = start, end
        self.obj = obj
        self.guard = guard            # (start, end) of the enclosing `if (obj != 0) { ... }`, or None
        self.indent = indent
        self.line = line              # first line of the site in the original text (1-based)
        self.form = None              # "static", "member" or "keep"
        self.new_lines = None         # (first, last) line in the rewritten text


def _guard(text, start, end, obj):
    """The span of an `if (obj != 0) { ... }` holding only text[start:end], or None."""
    head = _GUARD.search(text, max(0, start - 400), start)
    if not head or bare(head.group("w")) != bare(obj):
        return None
    if head.group("open"):
        tail = re.match(r"\s*\}", text[end:])
        if not tail:
            return None
        return head.start(), end + tail.end()
    return None


def _in_directive(text, pos):
    """Whether `pos` lies in a preprocessor line (a macro body, with its continuation lines)."""
    start = text.rfind("\n", 0, pos) + 1
    while start > 0 and text[:start - 1].endswith("\\"):
        start = text.rfind("\n", 0, start - 1) + 1
    return text[start:pos].lstrip().startswith("#")


def find_sites(text):
    """[Site] of the open releases and increments in `text`, in text order; a macro's body is left (its users'
    types differ)."""
    sites, taken = [], []
    for lead in _LEAD.finditer(text):
        pos = lead.end()
        if any(a <= pos < b for a, b in taken) or _in_directive(text, pos):
            continue
        dec = _DEC.match(text, pos)
        if dec:
            obj = _target(dec, ("d1", "d2", "d3"))
            test = _TEST.match(text, dec.end())
            if obj and test and _step_ok(dec, obj, "-") and _tests_zero(test.group("cond"), obj) \
                    and bare(test.group("arg") if test.group("arg") is not None else test.group("self")) == bare(obj):
                site = Site("release", pos, test.end(), obj, None, lead.group(0).strip("\n"),
                            text.count("\n", 0, pos) + 1)
                sites.append(site)
                taken.append((pos, test.end()))
                continue
        inc = _INC.match(text, pos)
        if inc:
            obj = _target(inc, ("i1", "i2", "i3"))
            if obj and _step_ok(inc, obj, "+"):
                site = Site("ref", pos, inc.end(), obj, None, lead.group(0).strip("\n"),
                            text.count("\n", 0, pos) + 1)
                sites.append(site)
                taken.append((pos, inc.end()))
    for site in sites:
        site.guard = _guard(text, site.start, site.end, site.obj)
        if site.guard is None and site.kind == "ref":
            # `if (p != 0) p->_refCount = p->_refCount + 1;`: an unbraced guard
            head = _GUARD.search(text, max(0, site.start - 400), site.start)
            if head and not head.group("open") and bare(head.group("w")) == bare(site.obj):
                site.guard = (head.start(), site.end)
    sites.extend(helper_sites(text))
    sites.sort(key=lambda s: s.start)
    return sites


def helper_sites(text):
    """[Site] of the calls `igRelease(p)` in `text` (kind "helper", obj p, span the call without its `;`); the
    helper's own definitions and macro bodies are left."""
    sites = []
    for m in _HELPER.finditer(text):
        line_start = text.rfind("\n", 0, m.start()) + 1
        if _in_directive(text, m.start()) or re.search(r"\bvoid\s*$", text[line_start:m.start()]):
            continue
        end = _close(text, m.end() - 1)
        if end is None or not re.match(r"\s*;", text[end:]):
            continue
        sites.append(Site("helper", m.start(), end, text[m.end():end - 1].strip(), None, "",
                          text.count("\n", 0, m.start()) + 1))
    return sites


def convert(text, member=(), keep=(), view=None):
    """-> (rewritten text, [Site]); `member`/`keep` are the original first lines of sites to write in the member
    form inside their `if` and to leave open, `view` {line: class} the helper calls whose pointer is that view."""
    view = view or {}
    sites = find_sites(text)
    out, cursor = [], 0
    for site in sites:
        if site.line in keep:
            site.form = "keep"
            continue
        call = "%s->%s();" % (site.obj, site.kind)
        if site.kind == "helper":
            start, end = site.start, site.end
            replacement = "%s::release(%s)" % (view.get(site.line, "igObject"), site.obj)
            site.form = "view" if site.line in view else "static"
        elif site.guard and site.line not in member:
            start, end = site.guard
            line_start = text.rfind("\n", 0, start) + 1
            if text[line_start:start].strip() == "":
                start = line_start
                prefix = text[line_start:site.guard[0]]
            else:
                prefix = ""
            replacement = "%sigObject::%s(%s);" % (prefix, site.kind, site.obj)
            site.form = "static"
        else:
            start, end = site.start, site.end
            replacement = call
            site.form = "member"
        out.append(text[cursor:start])
        out.append(replacement)
        cursor = end
        site.span = (start, end, replacement)
    out.append(text[cursor:])
    new = "".join(out)
    # each site's lines in the rewritten text
    shift = 0
    for site in sites:
        if site.form == "keep":
            continue
        start, end, replacement = site.span
        first = text.count("\n", 0, start) + 1 + shift
        site.new_lines = (first, first + replacement.count("\n"))
        shift += replacement.count("\n") - text.count("\n", start, end)
    return new, sites


def _locations(values):
    found = {}
    for value in values or ():
        path, _, line = value.rpartition(":")
        found.setdefault(path, set()).add(int(line))
    return found


def _views(values):
    found = {}
    for value in values or ():
        where, _, cls = value.partition("=")
        path, _, line = where.rpartition(":")
        found.setdefault(path, {})[int(line)] = cls
    return found


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("files", nargs="+")
    ap.add_argument("--member", action="append", help="FILE:LINE of a site written as p->ref()/release() in its if")
    ap.add_argument("--keep", action="append", help="FILE:LINE of a site left open")
    ap.add_argument("--view", action="append", help="FILE:LINE=CLASS of an igRelease call written CLASS::release(p)")
    ap.add_argument("--sites", action="store_true", help="list each site: file, line, form, rewritten lines")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args(argv)
    member, keep, view = _locations(args.member), _locations(args.keep), _views(args.view)
    total = {}
    for path in args.files:
        text = open(path).read()
        new, sites = convert(text, member.get(path, ()), keep.get(path, ()), view.get(path))
        for site in sites:
            total[site.form] = total.get(site.form, 0) + 1
            if args.sites:
                print("%s:%d\t%s %s\t%s" % (path, site.line, site.kind, site.form,
                                            "%d-%d" % site.new_lines if site.new_lines else "-"))
        if new != text and not args.dry_run:
            open(path, "w").write(new)
    print("%d sites: %s" % (sum(total.values()), ", ".join("%d %s" % (n, f) for f, n in sorted(total.items()))),
          file=sys.stderr)


if __name__ == "__main__":
    main()
