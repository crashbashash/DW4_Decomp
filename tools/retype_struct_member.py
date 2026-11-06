#!/usr/bin/env python3
"""retype_struct_member.py — bank the near-miss tier's mechanical source shapes.

The m2c bulk pass is exhausted: a full re-sweep of every unmatched function banks 0.
What is left in the low-diff tier is a handful of *source spellings* the m2c cleaner
does not emit, each measurable from the retail instruction words.  This tool prepares a
candidate exactly as `m2c_batch.py` does, applies one or more of those spellings, and
banks only when `tools/verify.py` proves the compiled bytes identical to retail.

Shapes (`--shape`, repeatable / comma-separated):

  * ``struct`` — a struct member keeps the base pointer.  m2c CSEs ``argN + K`` into a
    scratch register (``addiu sX,aN,K; sb 0(sX)``) where retail keeps the base
    (``move sX,aN; sb K(sX)``).  Giving the parameter a struct type and reading
    ``argN->fK`` reproduces retail (the shape; 13
    of these by hand).
  * ``width`` — a defaulted ``int`` member access whose retail instruction is narrower
    (``sb``/``sh``/``lb``/``lbu``/``lh``/``lhu``/``sd``/``ld``).  m2c only carries the
    access width when it had a cast to put on the value, so a zero store and a narrowed
    load default to ``sw``/``lw``.  The retail instruction is the authority.
  * ``leadfn`` — a dropped leading parameter.  m2c declares fewer parameters than the body
    uses, so its ``arg0`` is retail's ``a1``/``a2``.  Prepending 1-3 dummy parameters to
    the definition shifts the body's ``argN`` names into the right registers.
  * ``leadcall`` — a call drops its leading argument.  Retail loads an argument register
    before the ``jal`` where m2c emits a shorter argument list; prepending the enclosing
    function's own parameters restores it.

Every mutation is *fail-closed*: a candidate is written to ``src/`` only after
``verify.py`` agrees, in the same way `m2c_batch.py` banks.  ``make check`` must be green
and ``make link`` byte-identical after a batch.

Usage:
  retype_struct_member.py --worklist build/m2c_worklist.tsv --shape struct,width,leadfn \
      --max-diffs 8 --jobs 8 --report            # measure a tier, write nothing
  retype_struct_member.py --max-diffs 8 --jobs 8 --write   # bank the matches
  retype_struct_member.py --only FUN_00154b40 --show
"""
import argparse
import collections
import os
import re
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, os.environ.get("DW4_M2C_DIR", os.path.join(ROOT, "local", "m2c")))

import automatch as am          # noqa: E402
import m2c_compat               # noqa: E402,F401  (guards a vendored-m2c crash)
import m2c_one                  # noqa: E402
import m2c_batch as mb          # noqa: E402
import syscalls                 # noqa: E402
import units                    # noqa: E402
import verify as vfy            # noqa: E402

ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
SYMBOLS_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
WORKLIST_DEFAULT = os.path.join(ROOT, "build", "m2c_worklist.tsv")
CAND_DIR = os.path.join(ROOT, "build", "m2c")

# ---------------------------------------------------------------------------
# The scalar widths a member access can have, and the retail mnemonics that fix it.
WIDTH_TYPE = {"char": "char", "signed char": "char", "unsigned char": "unsigned char",
              "short": "short", "unsigned short": "unsigned short", "int": "int",
              "unsigned int": "unsigned int", "long long": "long long",
              "unsigned long long": "unsigned long long", "float": "float",
              "double": "double"}
WIDTH_BY_MN = {"sb": "char", "sh": "short", "sw": "int", "sd": "long long",
               "lb": "char", "lbu": "unsigned char", "lh": "short",
               "lhu": "unsigned short", "lw": "int", "ld": "long long",
               "lwc1": "float", "swc1": "float"}
SCALAR = set(WIDTH_TYPE) | {"void *", "char *", "int *", "unsigned char *",
                            "short *", "unsigned *", "void **"}

# ---------------------------------------------------------------------------
# A tiny expression scanner. `*(CAST)(EXPR)` is easy to mis-parse with a regex (the
# base can be a deref-cast of its own), so walk the balanced parentheses.


def _match_paren(s, i):
    """Index just past the `)` matching the `(` at `s[i]`, or -1."""
    depth = 0
    while i < len(s):
        if s[i] == "(":
            depth += 1
        elif s[i] == ")":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return -1


def iter_deref_casts(src):
    """[(start, end, ctype, expr_text)] for every `*(CTYPE)(EXPR)` in `src`."""
    i, n = 0, len(src)
    while True:
        j = src.find("*(", i)
        if j < 0:
            return
        k = src.find(")", j + 2)
        if k < 0:
            return
        ctype = src[j + 2:k].strip()
        p = k + 1
        if p < n and src[p] == "(":
            close = _match_paren(src, p)
            if close < 0:
                return
            yield (j, close, ctype, src[p + 1:close - 1])
            i = close
        else:
            i = k + 1


CHAR_BASE_RE = re.compile(r"^\s*\(\s*char\s*\*\s*\)\s*")
OFF_RE = re.compile(r"^(.*?)\s*([+-])\s*(0x[0-9A-Fa-f]+|\d+)\s*$")


def parse_char_access(expr):
    """(base_text, offset) for a `(char *)(BASE) + K` expression, else None.

    `BASE` may itself be an expression (`*(int *)((char *)(arg0) + 28)`), so the
    offset is the *last* top-level `+`/`-`, found by the anchored non-greedy match.
    """
    m = CHAR_BASE_RE.match(expr)
    if not m:
        return None
    rest = expr[m.end():]
    mo = OFF_RE.match(rest)
    if mo:
        base, sign, off = mo.group(1).strip(), mo.group(2), int(mo.group(3), 0)
        if base.startswith("(") and base.endswith(")"):
            base = base[1:-1].strip()
        return base, (off if sign == "+" else -off)
    base = rest.strip()
    if base.startswith("(") and base.endswith(")"):
        base = base[1:-1].strip()
    return base, 0


def _base_reg(base):
    """m2c's name for a held value -> its register, or None (see m2c_batch._base_reg)."""
    if base.startswith("arg") and base[3:].isdigit():
        return "a" + base[3:]
    m = re.match(r"temp_([a-z]+\d*)(?:_\d+)?$", base)
    return m.group(1) if m else None


# ---------------------------------------------------------------------------
# Shape 1: member width.

def _retail_widths(table, va, size):
    """{(base_reg, off): type} and {off: type-or-None} from retail memory ops.

    The offset-only map ignores the frame registers (`sp`, `ra`, `gp`, `at`): a member
    access through a saved copy of a parameter reads `sN` where the source says `argN`,
    and the stack's own slots at the same offset would otherwise make the width
    ambiguous (`FUN_00141650`'s `lh a1,16(s0)` vs the frame's `ld ra,16(sp)`).
    """
    by_base, by_off = {}, {}
    frame = {"sp", "ra", "gp", "at", "zero", "fp"}
    for i in range(max(size, 0) // 4):
        e = table.get(va + 4 * i)
        if not e:
            continue
        mn, ops = e[0], e[1]
        if mn not in WIDTH_BY_MN:
            continue
        m = re.search(r"(-?[0-9A-Fa-fx]+)\((\w+)\)\s*$", ops)
        if not m:
            continue
        off = am.imm(m.group(1))
        if off is None:
            continue
        t = WIDTH_BY_MN[mn]
        by_base[(m.group(2), off)] = t
        if m.group(2) in frame:
            continue
        by_off[off] = t if by_off.get(off, t) == t else None
    return by_base, by_off


LOAD_MN = {"lb": ("char", 1), "lbu": ("unsigned char", 1),
           "lh": ("short", 2), "lhu": ("unsigned short", 2),
           "lw": ("int", 4), "ld": ("long long", 8), "lwc1": ("float", 4)}
STORE_MN = {"sb": ("char", 1), "sh": ("short", 2), "sw": ("int", 4),
            "sd": ("long long", 8), "swc1": ("float", 4)}


def _retail_field_types(table, va, size):
    """{offset: C type} for a member implied by retail, loads preferred to stores.

    `sb` + `lbu` on one member is not a conflict: the *store* of an `unsigned char`
    is still `sb`, so the load's signedness is the right field type.  Only two
    different *sizes* at one offset are ambiguous, and those map to `None`.
    """
    frame = {"sp", "ra", "gp", "at", "zero", "fp"}
    sizes = collections.defaultdict(set)
    load_t, store_t = {}, {}
    for i in range(max(size, 0) // 4):
        e = table.get(va + 4 * i)
        if not e:
            continue
        mn, ops = e[0], e[1]
        if mn in LOAD_MN:
            t, w = LOAD_MN[mn]
        elif mn in STORE_MN:
            t, w = STORE_MN[mn]
        else:
            continue
        m = re.search(r"(-?[0-9A-Fa-fx]+)\((\w+)\)\s*$", ops)
        if not m or m.group(2) in frame:
            continue
        off = am.imm(m.group(1))
        if off is None:
            continue
        sizes[off].add(w)
        (load_t if mn in LOAD_MN else store_t)[off] = t
    return {off: (load_t.get(off) or store_t.get(off)) if len(w) == 1 else None
            for off, w in sizes.items()}


def mut_width(src, va, size, table):
    """Rewrite a defaulted `int` member access to the width retail uses."""
    by_base, by_off = _retail_widths(table, va, size)
    if not by_base and not by_off:
        return None
    field = _retail_field_types(table, va, size)
    edits = []
    for (start, end, ctype, expr) in iter_deref_casts(src):
        if ctype != "int *":
            continue
        pa = parse_char_access(expr)
        if pa is None:
            continue
        base, off = pa
        t = by_base.get((_base_reg(base), off)) if _base_reg(base) else None
        if t is None:
            t = field.get(off) or by_off.get(off)
        if t and t != "int":
            edits.append((start, end, "*(%s *)(%s)" % (t, expr)))
    if not edits:
        return None
    out, last = [], 0
    for s, e, rep in edits:
        out.append(src[last:s])
        out.append(rep)
        last = e
    out.append(src[last:])
    return "".join(out)


# ---------------------------------------------------------------------------
# Shape 2: struct member keeps the base pointer.

WIDTH_SZ = {"char": 1, "signed char": 1, "unsigned char": 1, "short": 2,
            "unsigned short": 2, "int": 4, "unsigned int": 4, "float": 4,
            "long long": 8, "unsigned long long": 8, "double": 8,
            "void *": 4, "char *": 4, "int *": 4, "unsigned char *": 4}


def _func_signature(src):
    """(signature_match, [(ptype_text, name)]) for the first definition, or (None, [])."""
    m = re.search(r"^([A-Za-z_][\w \t\*]*?)\s+(\w+)\s*\(([^)]*)\)\s*\{", src, re.M)
    if not m:
        return None, []
    ps = []
    for p in m.group(3).split(","):
        p = p.strip()
        if not p or p == "void":
            continue
        nm = re.search(r"(\w+)\s*$", p)
        if nm:
            ps.append((p, nm.group(1)))
    return m, ps


def _struct_for(offsets_and_types):
    """A `typedef struct { ... }` body for increasing, non-overlapping offsets, or None."""
    keys = sorted(offsets_and_types)
    fields, prev, ok = [], 0, True
    for k in keys:
        t = offsets_and_types[k]
        w = WIDTH_SZ[t]
        if k < prev or k + w > 0x10000:
            ok = False
            break
        if k > prev:
            fields.append("char pad%d[%d];" % (k, k - prev))
        fields.append("%s f%X;" % (t, k))
        prev = k + w
    if not ok:
        return None
    return " ".join(fields) if fields else "char pad;"


LOCAL_DECL_RE = re.compile(
    r"^(\s*)((?:void|char|int|short|long long|unsigned char|unsigned short"
    r"|unsigned int|unsigned long long|float|double)\s*\*?)\s*(\w+)\s*;\s*$", re.M)


def _member_map(src, bases, width_map=None):
    """{base: {offset: value type}} over `bases`, skipping conflicting widths.

    With `width_map` (retail's per-offset field types) a defaulted `int` field whose
    retail access is narrower/wider takes the retail width, so the struct variant also
    carries the width fix.
    """
    per = collections.defaultdict(dict)
    for (start, end, ctype, expr) in iter_deref_casts(src):
        if ctype not in SCALAR:
            continue
        # `*(T *)` is a deref of a pointer-to-T, so the *member* type is T: drop the
        # last `*` (`int *` -> `int`, `void **` -> `void *`).
        ftype = ctype.rsplit("*", 1)[0].strip()
        if ftype not in WIDTH_SZ:
            continue
        pa = parse_char_access(expr)
        if pa is None:
            continue
        base, off = pa
        if base not in bases:
            continue
        if width_map:
            rt = width_map.get(off)
            if rt and rt in WIDTH_SZ and WIDTH_SZ.get(rt) != WIDTH_SZ.get(ftype):
                ftype = rt
        prev = per[base].get(off)
        if prev is not None and prev != ftype:
            per[base][off] = None              # conflicting widths at one offset
        else:
            per[base][off] = ftype
    clean = {}
    for base, om in per.items():
        good = {k: t for k, t in om.items() if t is not None and t in WIDTH_SZ}
        if good:
            clean[base] = good
    return clean


def _build_struct_variant(src, ps, selected, locals_map):
    """`src` with each base in `selected` retyped to a struct of its member offsets."""
    typedefs, newsrc = [], src
    # parameter replacements, right to left so the spans stay valid
    for i in range(len(ps) - 1, -1, -1):
        ptype, pname = ps[i]
        if pname not in selected:
            continue
        body = _struct_for(selected[pname])
        if body is None:
            return None
        sname = "S%d" % i
        typedefs.append("typedef struct %s { %s } %s;" % (sname, body, sname))
        pat = re.compile(r"(?<![\w\*])\b[A-Za-z_][\w \t]*?\*?\s*\b%s\b(?=\s*[,)])"
                         % re.escape(pname))
        newsrc = pat.sub("%s *%s" % (sname, pname), newsrc, count=1)
    # local declarations
    def decl_repl(m):
        indent, _decl, name = m.group(1), m.group(2), m.group(3)
        if name not in selected:
            return m.group(0)
        body = _struct_for(selected[name])
        if body is None:
            return m.group(0)
        sname = "S_%s" % name
        typedefs.append("typedef struct %s { %s } %s;" % (sname, body, sname))
        return "%s%s *%s;" % (indent, sname, name)
    # the typedefs have to be known before the accesses are rewritten, but the
    # declaration pass has to run before the access pass so the spans do not shift
    tmp = LOCAL_DECL_RE.sub(decl_repl, newsrc)
    newsrc = tmp
    # access replacements on the final text
    edits = []
    for (start, end, ctype, expr) in iter_deref_casts(newsrc):
        pa = parse_char_access(expr)
        if pa is None:
            continue
        base, off = pa
        if base in selected and off in selected[base]:
            edits.append((start, end, "%s->f%X" % (base, off)))
    if not edits:
        return None
    out, last = [], 0
    for s, e, rep in edits:
        out.append(newsrc[last:s])
        out.append(rep)
        last = e
    out.append(newsrc[last:])
    return "\n".join(typedefs) + "\n" + "".join(out)


def struct_variants(src, width_map=None):
    """Sources with parameters and/or pointer locals retyped to member structs."""
    sig, ps = _func_signature(src)
    if not sig:
        return []
    params = {n for _, n in ps}
    locals_map = {m.group(3) for m in LOCAL_DECL_RE.finditer(src)}
    bases = params | locals_map
    clean = _member_map(src, bases, width_map)
    if not clean:
        return []
    param_clean = {b: v for b, v in clean.items() if b in params}
    local_clean = {b: v for b, v in clean.items() if b in locals_map}
    variants = []
    for base in sorted(clean):                      # one base at a time
        v = _build_struct_variant(src, ps, {base: clean[base]}, locals_map)
        if v:
            variants.append(v)
    if len(param_clean) > 1:
        v = _build_struct_variant(src, ps, param_clean, locals_map)
        if v:
            variants.append(v)
    if local_clean:
        v = _build_struct_variant(src, ps, local_clean, locals_map)
        if v:
            variants.append(v)
    if param_clean and local_clean:
        v = _build_struct_variant(src, ps, dict(param_clean, **local_clean), locals_map)
        if v:
            variants.append(v)
    return variants


# ---------------------------------------------------------------------------
# Shape 3: leading parameters.

def leadfn_variants(src):
    """Sources with 1-3 dummy leading parameters (m2c's argN shift right)."""
    m, ps = _func_signature(src)
    if not m:
        return []
    open_paren = src.rfind("(", 0, m.end())
    close_paren = src.find(")", open_paren)         # the parameter list has no nesting
    if open_paren < 0 or close_paren < 0:
        return []
    old = src[open_paren + 1:close_paren]
    out = []
    for k in range(1, 4):
        dummies = ", ".join("int dummy%d" % t for t in range(k))
        new = dummies + (", " + old if old.strip() else "")
        out.append(src[:open_paren + 1] + new + src[close_paren:])
    return out


CALL_RE = re.compile(r"(?<![\w.])(FUN_[0-9a-f]{8})\s*\(")


def _find_calls(src):
    """Calls in the function *body* (a `typedef struct { ... }` can hold the first `{`)."""
    sig, _ = _func_signature(src)
    if not sig:
        return []
    brace = src.find("{", sig.end())
    if brace < 0:
        return []
    res = []
    for m in CALL_RE.finditer(src, brace):
        i = m.end()
        depth, j = 1, i
        while j < len(src) and depth:
            if src[j] == "(":
                depth += 1
            elif src[j] == ")":
                depth -= 1
            j += 1
        if depth:
            continue
        res.append((m.end(), j - 1, m.group(1), src[i:j - 1]))
    return res


def _split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def leadcall_variants(src, max_calls=3, max_k=3):
    """Sources with a call's argument list corrected.

    The measured families: prepend a prefix of the enclosing parameters (a dropped
    leading pass-through argument) and prepend/append a small constant (a dropped
    leading or trailing immediate argument).
    """
    _, ps = _func_signature(src)
    params = [n for _, n in ps]
    out = []
    for (ins, close, cname, args) in _find_calls(src)[:max_calls]:
        cur = _split_args(args)
        cands = []
        for k in range(1, min(max_k, len(params)) + 1):
            cands.append(params[:k] + cur)
        for c in ("0", "1"):
            cands.append([c] + cur)
            cands.append(cur + [c])
        for cand in cands:
            out.append(src[:ins] + ", ".join(cand) + src[close:])
    return out


# ---------------------------------------------------------------------------
# Driver.

def prepare_src(ctx, cand):
    """The cleaned best-mode source for one candidate (same variant loop as m2c_batch)."""
    va, sz, name = cand
    asm = m2c_one.asm_for(va, name, sz, ctx["table"], ctx["names"],
                          bounds=ctx["bounds"], jtables=ctx["jtabs"].get(va, {}),
                          gp=ctx["gp"])
    with mb._M2C_LOCK:
        draft = mb.run_m2c(asm, name, "/tmp/shape_%s.s" % mb._tag(),
                           context=ctx["context"])
    if not draft.strip() or "Decompilation failure" in draft or "Decompilation error" in draft:
        return None, "", "m2cfail"
    best = None
    for mode in ("hybrid", "symbol", "literal"):
        src = mb.clean(draft, addr_mode=mode, bounds=ctx["bounds"])
        fit = mb.fit_widths(src, va, sz, ctx["table"])
        variants = [(src, mode)] + ([(fit, mode + "+w")] if fit != src else [])
        for base, tag in list(variants):
            ptr = mb.retype_global_loads(base)
            if ptr != base:
                variants.append((ptr, tag + "+p"))
                od = mb.order_pointer_decls(ptr)
                if od != ptr:
                    variants.append((od, tag + "+po"))
            od = mb.order_pointer_decls(base)
            if od != base and all(od != v for v, _ in variants):
                variants.append((od, tag + "+o"))
        for base, tag in list(variants):
            vc = mb.virtualize_calls(base, name)
            if vc and all(vc != v for v, _ in variants):
                variants.append((vc, tag + "+vcpp"))
            sret = mb.virtualize_calls(base, name, sret=True)
            if sret and all(sret != v for v, _ in variants):
                variants.append((sret, tag + "+sretvcpp"))
        for vsrc, vmode in variants:
            tmp = "/tmp/shape_%s%s" % (mb._tag(),
                                       ".cpp" if vmode.endswith("vcpp") else ".c")
            open(tmp, "w").write("/* %s */\n" % name + vsrc)
            ok, rep = vfy.verify_one(va, tmp, symbols=ctx["symbols"], elf=ctx["elf"])
            first = rep.splitlines()[0]
            nb = (10 ** 9 if "compile failed" in first
                  else mb._diffcount(rep) + (1 if "size:" in rep else 0))
            if best is None or nb < best[0]:
                best = (nb, vmode, vsrc, ok, rep)
            if ok:
                break
        if best is not None and best[3]:
            break
    nb, mode, src, ok, rep = best
    return (src, mode, ok, rep, nb), None, "ok"


def candidate_variants(src, shapes, va, size, table):
    """Ordered (tag, source) spellings to try, base first."""
    seen = collections.OrderedDict()

    def add(tag, s):
        if s and s not in seen:
            seen[s] = tag

    add("base", src)
    wmap = _retail_field_types(table, va, size)
    structs = []
    if "struct" in shapes:
        structs = struct_variants(src, wmap)
        for i, v in enumerate(structs):
            add("struct%d" % i, v)
    widths = []
    if "width" in shapes:
        w = mut_width(src, va, size, table)
        if w:
            add("width", w)
            widths.append(w)
            for i, v in enumerate(structs):
                w2 = mut_width(v, va, size, table)
                if w2:
                    add("struct%d+width" % i, w2)
                    widths.append(w2)
    if "leadfn" in shapes:
        seed = [src] + structs + widths
        for s in seed:
            for k, v in enumerate(leadfn_variants(s), 1):
                add("leadfn%d" % k, v)
    if "leadcall" in shapes:
        seed = [src] + structs[:1] + widths[:1]
        for s in seed:
            for i, v in enumerate(leadcall_variants(s)):
                add("leadcall%d" % i, v)
    return [(tag, s) for s, tag in seen.items()]


def work(ctx, cand, shapes, args):
    va, sz, name = cand
    res, err, kind = prepare_src(ctx, cand)
    # prepare_src returns (None, "", "m2cfail") when m2c refuses the function, so a
    # bare `if err` misses it and the unpack below hits None (the m2c-failure path was
    # never exercised before this sweep).
    if err or res is None:
        return {"name": name, "va": va, "size": sz, "status": kind, "tag": "",
                "src": None, "base": None}
    src, mode, ok, rep, nb = res
    # A base match means the pipeline itself (m2c + cleaner + the vcpp/sret transforms)
    # now reproduces the unit, with no shape respelling needed. The oracle is still
    # verify.py, so bank it like a shape match rather than dropping it — the base was
    # assumed pre-banked when this tool was written, which is no longer true once the
    # transforms improve.
    if ok:
        return {"name": name, "va": va, "size": sz, "mode": mode, "base_diffs": nb,
                "base_ok": True, "status": "MATCH", "tag": "base", "src": src,
                "ext": ".cpp" if "vcpp" in (mode or "") else ".c"}
    base = {"name": name, "va": va, "size": sz, "mode": mode, "base_diffs": nb,
            "base_ok": False, "status": "mismatch", "tag": "", "src": None}
    if nb > args.max_diffs:
        return base
    best = None
    cpp = "vcpp" in (mode or "")
    for tag, vsrc in candidate_variants(src, shapes, va, sz, ctx["table"])[1:]:
        ext = ".cpp" if cpp else ".c"
        tmp = "/tmp/shape_%s%s" % (mb._tag(), ext)
        open(tmp, "w").write("/* %s */\n" % name + vsrc)
        good, rep2 = vfy.verify_one(va, tmp, symbols=ctx["symbols"], elf=ctx["elf"])
        if good:
            best = (tag, vsrc, ".cpp" if ext == ".cpp" else ".c", True)
            break
    if best:
        return {"name": name, "va": va, "size": sz, "mode": mode, "base_diffs": nb,
                "base_ok": False, "status": "MATCH", "tag": best[0], "src": best[1],
                "ext": best[2]}
    return base


def write_unit(path, name, va, tag, src, ext):
    dest = os.path.join(path, name + ext)
    os.makedirs(os.path.dirname(dest) or ".", exist_ok=True)
    header = ("/* 0x%08x — %s. Banked by tools/retype_struct_member.py (shape: %s):\n"
              " * the m2c draft plus a mechanical source respelling, verified\n"
              " * byte-identical to retail by tools/verify.py. */\n"
              % (va, name, tag))
    open(dest, "w").write(header + src)
    return dest


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--symbols", default=SYMBOLS_DEFAULT)
    ap.add_argument("--worklist", default=WORKLIST_DEFAULT)
    ap.add_argument("--src-root", default=os.path.join(ROOT, "src"))
    ap.add_argument("--out", default=os.path.join(ROOT, "src", "unmatched"),
                    help="where a match is banked")
    ap.add_argument("--shape", default="struct,width,leadfn",
                    help="comma-separated: struct,width,leadfn,leadcall,all")
    ap.add_argument("--max-diffs", type=int, default=8)
    ap.add_argument("--max-size", type=int, default=0)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--only", action="append", default=[])
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--show", action="store_true")
    args = ap.parse_args(argv)

    shapes = args.shape.split(",")
    if "all" in shapes:
        shapes = ["struct", "width", "leadfn", "leadcall"]

    img = open(args.elf, "rb").read()
    syms = am.load_symbols(args.symbols)
    have = set(units.scan(args.src_root))
    lo = min(v for v, _, _ in syms)
    hi = max(v + s for v, s, _ in syms)
    table = am.disassemble(img, lo, hi)
    ctx = dict(table=table, names={v: n for v, s, n in syms},
               bounds=m2c_one.load_bounds(args.elf), gp=m2c_one.load_gp(args.elf),
               jtabs=m2c_one.load_jtables(args.elf, args.symbols),
               sdk=syscalls.load(), symbols=args.symbols, elf=args.elf,
               context=None)
    mb._CTX.update(ctx)

    rows = []
    if args.only:
        want = set(args.only)
        rows = [{"name": n, "va": v, "size": s, "status": "mismatch", "diffs": 0}
                for v, s, n in syms if n in want]
    else:
        with open(args.worklist) as fh:
            fh.readline()
            for ln in fh:
                p = ln.rstrip("\n").split("\t")
                if len(p) < 6:
                    continue
                rows.append({"name": p[0], "va": int(p[1], 0), "size": int(p[2]),
                             "status": p[3], "diffs": int(p[4])})
    cands = [(r["va"], r["size"], r["name"]) for r in rows
             if r["name"] not in have and r["status"] in ("mismatch", "compile")
             and (r["diffs"] < 0 or r["diffs"] <= args.max_diffs)
             and (not args.max_size or r["size"] <= args.max_size)]
    if args.limit:
        cands = cands[:args.limit]
    print("shapes=%s  %d candidates (diffs<=%d, %d..%s bytes), jobs=%d"
          % (",".join(shapes), len(cands), args.max_diffs, 0,
             args.max_size or "inf", args.jobs), flush=True)

    t0 = time.time()
    done = matched = 0
    banked = collections.Counter()
    with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
        for out in pool.map(lambda c: work(ctx, c, shapes, args), cands):
            done += 1
            if out["status"] == "MATCH":
                matched += 1
                banked[out["tag"].split("+")[0].rstrip("0123456789")] += 1
                print("  MATCH %-32s 0x%08x %5dB  base=%d  shape=%s"
                      % (out["name"], out["va"], out["size"], out["base_diffs"],
                         out["tag"]), flush=True)
                if args.show:
                    print(out["src"])
                if args.write:
                    write_unit(args.out, out["name"], out["va"], out["tag"],
                               out["src"], out.get("ext", ".c"))
            elif args.show and done <= 40:
                print("  .     %-32s 0x%08x %5dB  base=%d"
                      % (out["name"], out["va"], out["size"], out["base_diffs"]))
            if done % 200 == 0:
                print("  %d/%d  matched=%d  (%.1f f/s, %.0fs)"
                      % (done, len(cands), matched, done / (time.time() - t0),
                         time.time() - t0), flush=True)
    print("retype_struct_member: %d/%d matched in %.0fs  %s"
          % (matched, len(cands), time.time() - t0, dict(banked)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
