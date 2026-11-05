#!/usr/bin/env python3
"""getvtable_stack_gen.py [--out DIR] NAME... — emit the stack-object `*_GetVTable` accessors as C.

Retail shape: `igObject_InitHeader(&obj)` (or a class-specific init), the vtable pointer stored into the
stack object, the vtable method slot read as `*(int *)((char *)&obj + DAT_00586dc8[0][229])`, the vtable
pointer stored again, then (depending on the class) one of

  plain    nothing else                                   (60 bytes, frame 32/64)
  straight embedded members zeroed, member destructors called with `(&obj.wN, -1)` and the object's own
           destructor with `(&obj, 0)`                    (100..136 bytes)
  member   an embedded smart-pointer member released inline: refcount decrement and `igObject_Destroy`, or the
           string-chunk header release (`StringChunk_ReleaseHeader`)   (132..148 bytes)

The generator reads the retail words from asm/NAME.s and writes DIR/NAME.c (default src/unmatched), then
hands the file to tools/initfields_gen.py, which turns it into the translation unit the function's unit
profile needs (phase 3b, docs/engine/build-profiles.md): a `.cpp` with typed `extern "C"` prototypes where
the unit compiled with exceptions on (retail keeps the exception index record only the C++ front end
emits), the local declarations in the unit compiler's saved-register order.  `--retarget FILE...` runs
that step alone on existing files and verifies them (`--no-retarget` keeps the raw C draft).  It does not
claim a match: verify with `python3 tools/verify.py 0x<va> <file>`, which applies the unit profile.
Rows it cannot model print `skip` and the reason.  See archived near-miss note wave4s8 and
docs/engine/getvtable-fold.md (phase 3b section).
"""
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SP = 29


def sx(v):
    return v - 0x10000 if v >= 0x8000 else v


def load_syms():
    syms = {}
    for line in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        p = line.split()
        if len(p) >= 3 and not line.startswith("#"):
            try:
                syms[int(p[0], 16)] = p[2]
            except ValueError:
                pass
    return syms


def words(name):
    txt = open(os.path.join(ROOT, "asm", name + ".s")).read()
    return [int(x, 16) for x in re.findall(r"\.word (0x[0-9a-f]+)", txt)]


def trace(w, syms):
    """Symbolic walk of a straight-line body.  Returns (frame, obj_base, statements, calls)."""
    frame = -sx(w[0] & 0xFFFF)
    reg = {}
    stmts = []
    state = {"base": None}

    def exe(x):
        op = x >> 26
        rs = (x >> 21) & 31
        rt = (x >> 16) & 31
        imm = sx(x & 0xFFFF)
        if op in (0x1F, 0x3F, 0x37, 0x1E):          # sq sd ld lq
            return
        if op == 9 and rs == SP:
            reg[rt] = ("addr", imm)
        elif op == 9 and rs == 0:
            reg[rt] = ("c", imm)
        elif op == 0xF:
            reg[rt] = ("hi", (x & 0xFFFF) << 16)
        elif op == 9 and rs == rt and reg.get(rt, ("",))[0] == "hi":
            reg[rt] = ("c", reg[rt][1] + imm)
        elif op == 0 and (x & 0x3F) == 0x2D and rt == 0:       # move rd,rs
            reg[(x >> 11) & 31] = reg.get(rs, ("c", 0)) if rs else ("c", 0)
        elif op == 0x2B:                                        # sw
            if rs == SP:
                if rt == 0:
                    stmts.append(("zero", imm))
                elif reg.get(rt, ("",))[0] == "c" and reg[rt][1] > 0x100000:
                    stmts.append(("vt", imm, reg[rt][1]))
                else:
                    raise ValueError("sw")
            elif rs in reg and reg[rs][0] == "addr" and rt == 0:
                stmts.append(("zero", reg[rs][1] + imm))
            else:
                raise ValueError("sw base")
        elif op == 0x23:                                        # lw
            if imm in (28104, 916):
                pass
            elif rs == 2 and 16 <= rt <= 23:
                stmts.append(("t", imm))
            else:
                raise ValueError("lw")
        elif op == 0 and (x & 0x3F) == 0x21:                    # addu
            pass
        elif x == 0:
            pass
        else:
            raise ValueError("op %08x" % x)

    calls = []
    skip = set()
    i = 0
    while i < len(w):
        x = w[i]
        if i in skip:
            i += 1
            continue
        op = x >> 26
        if op in (4, 5, 1, 6, 7):
            raise ValueError("branch")
        if op == 3:
            exe(w[i + 1])
            skip.add(i + 1)
            tgt = syms.get((x & 0x3FFFFFF) << 2)
            a0, a1 = reg.get(4), reg.get(5)
            if state["base"] is None:
                state["base"] = a0[1]
                calls.append(tgt)
            else:
                stmts.append(("call", tgt, a0[1] if a0 and a0[0] == "addr" else None, a1[1] if a1 else 0))
            i += 1
            continue
        if op == 0 and (x & 0x3F) == 8:
            break
        if i < 6 and op in (0x2F, 0x3F, 0x1F) and ((x >> 21) & 31) == SP:
            i += 1
            continue
        exe(x)
        i += 1
    return frame, state["base"], stmts, calls


def gen_straight(name, w, syms):
    frame, base, stmts, calls = trace(w, syms)
    init = calls[0]
    nw = (frame - base) // 4
    vts = [s[2] for s in stmts if s[0] == "vt"]
    if len(vts) != 2:
        raise ValueError("vt count")
    decls = "".join("extern int DAT_%08x[4];\n" % v for v in sorted(set(vts)))
    cdecl = "".join("int %s();\n" % c for c in sorted({s[1] for s in stmts if s[0] == "call"}))
    lines = []
    for s in stmts:
        if s[0] == "zero":
            lines.append("    obj.w%d = 0;" % ((s[1] - base) // 4))
        elif s[0] == "vt":
            lines.append("    obj.vt = &DAT_%08x[0];" % s[2])
        elif s[0] == "t":
            lines.append("    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));")
        elif s[0] == "call":
            k = (s[2] - base) // 4
            lines.append("    %s(%s, %d);" % (s[1], "&obj" if k == 0 else "&obj.w%d" % k, s[3]))
    fields = "".join("int w%d; " % i for i in range(1, nw))
    return ("struct Obj { int *vt; %s};\nint %s(struct Obj *);\n%s%sextern void * DAT_00586dc8[4];\n"
            "int %s(void) {\n    struct Obj obj;\n    int t;\n    %s(&obj);\n%s\n    return t;\n}\n"
            % (fields, init, cdecl, decls, name, init, "\n".join(lines)))


def gen_plain(name, w, syms):
    if len(w) != 15:
        raise ValueError("not 15 words")
    frame = -sx(w[0] & 0xFFFF)
    base = [x & 0xFFFF for x in w if x >> 16 == 0x27A4][0]
    hi = lo = None
    for x in w:
        if x >> 16 == 0x3C03:
            hi = x & 0xFFFF
        if x >> 16 == 0x2463:
            lo = x & 0xFFFF
    vt = (hi << 16) + sx(lo)
    pad = frame - base - 4
    return ("struct Obj { int *vt; char pad[%d]; };\nint igObject_InitHeader(struct Obj *);\n"
            "extern int DAT_%08x[4];\nextern void * DAT_00586dc8[4];\nint %s(void) {\n    struct Obj obj;\n"
            "    igObject_InitHeader(&obj);\n    obj.vt = &DAT_%08x[0];\n"
            "    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));\n}\n"
            % (pad, vt, name, vt))


def gen_member(name, w, syms):
    frame = -sx(w[0] & 0xFFFF)
    jals = [syms.get((x & 0x3FFFFFF) << 2) for x in w if x >> 26 == 3]
    if len(jals) != 2:
        raise ValueError("jal count")
    init, rel = jals
    if rel not in ("igObject_Destroy", "StringChunk_ReleaseHeader"):
        raise ValueError("release " + str(rel))
    m = [x & 0xFFFF for x in w if x >> 16 == 0x27A4 and (x & 0xFFFF) != 32][0]
    loads, vts = {}, []
    for x in w:
        op, rs, rt = x >> 26, (x >> 21) & 31, (x >> 16) & 31
        if op == 0xF and rt in (2, 3):
            loads[rt] = (x & 0xFFFF) << 16
        if op == 9 and rs == rt and rt in loads and len(vts) < 2 and loads[rt] >= 0x100000:
            loads[rt] += sx(x & 0xFFFF)
        if x >> 16 in (0xAFA2, 0xAFA3) and (x & 0xFFFF) == 32:
            vts.append(loads[rt])
    if len(vts) not in (1, 2):
        raise ValueError("vt count")
    vt1, vt2 = (None, vts[0]) if len(vts) == 1 else vts
    zl = [i for i, x in enumerate(w) if x == 0xAC800000]
    spos = [i for i, x in enumerate(w) if x >> 16 in (0xAFA2, 0xAFA3) and (x & 0xFFFF) == 32][0]
    mfirst = bool(zl) and zl[0] < spos
    size, mo = frame - 32, m - 32
    pre, post = mo - 4, size - mo - 4
    if rel == "igObject_Destroy":
        decl, loc = "int igObject_Destroy();\n", "    char *o;\n"
        body = ("            *(int *)(o + 4) = *(int *)(o + 4) - 1;\n"
                "            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {\n                igObject_Destroy(o);\n            }")
    else:
        decl, loc = "int StringChunk_ReleaseHeader();\n", "    char *o;\n    int *a1;\n    int v0;\n"
        body = ("            a1 = (int *)(o - 8);\n            v0 = *(int *)(o - 4) - 1;\n"
                "            *(int *)(o - 4) = v0;\n            if (v0 == 0) {\n"
                "                StringChunk_ReleaseHeader(*a1, a1);\n            }")
    first = ""
    if vt1 is not None and zl:
        first = ("    obj.m = 0;\n    obj.vt = &DAT_%08x[0];\n" if mfirst else "    obj.vt = &DAT_%08x[0];\n    obj.m = 0;\n") % vt1
    elif vt1 is not None:
        first = "    obj.vt = &DAT_%08x[0];\n" % vt1
    elif zl:
        first = "    obj.m = 0;\n"
    ext = ("extern int DAT_%08x[4];\n" % vt1 if vt1 else "") + ("extern int DAT_%08x[4];\n" % vt2 if vt2 != vt1 else "")
    return ("struct Obj { int *vt; %s char *m; %s};\nint %s(struct Obj *);\n%s%sextern void * DAT_00586dc8[4];\n"
            "int %s(void) {\n    struct Obj obj;\n%s    int t;\n    %s(&obj);\n%s"
            "    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));\n"
            "    obj.vt = &DAT_%08x[0];\n    if (&obj.m != 0) {\n        o = obj.m;\n        if (o != 0) {\n%s\n"
            "        }\n    }\n    return t;\n}\n"
            % ("char pad[%d];" % pre if pre else "", "char pad2[%d]; " % post if post else "", init, decl,
               ext, name, loc, init, first, vt2, body))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(ROOT, "src", "unmatched"))
    ap.add_argument("--retarget", action="store_true",
                    help="NAMES are existing source files: retarget them to their unit profile and verify")
    ap.add_argument("--no-retarget", action="store_true", help="keep the raw C draft")
    ap.add_argument("names", nargs="+")
    a = ap.parse_args()
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import initfields_gen
    if a.retarget:
        for f in a.names:
            status, info = initfields_gen.retarget(f, None, "auto", True)
            print("%s\t%s\t%s" % (status, os.path.relpath(f, ROOT), info))
        return
    syms = load_syms()
    for n in a.names:
        w = words(n)
        src = None
        for fn in (gen_plain, gen_straight, gen_member):
            try:
                src = fn(n, w, syms)
                break
            except (ValueError, IndexError, KeyError, TypeError):
                continue
        if src is None:
            print("skip", n)
            continue
        path = os.path.join(a.out, n + ".c")
        open(path, "w").write(src)
        if not a.no_retarget:
            status, info = initfields_gen.retarget(path, None, "auto", False)
            print("wrote", n, status, info)
        else:
            print("wrote", n)


if __name__ == "__main__":
    main()
