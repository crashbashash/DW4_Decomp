#!/usr/bin/env python3
"""getvtable_ptr_gen.py [--out DIR] [--search] NAME... - stack-object `*_GetVTable` accessors with pointer locals.

Complements getvtable_stack_gen.py for the frames that keep saved-register pointers into the stack object
(`addiu s0,sp,96` ...) and for the bodies with two inlined smart-pointer releases:

  ptr      straight line: zero stores through saved-register pointers and member destructor calls
           (`sw zero,0(s1)`, `move a0,s1; li a1,-1`); one `int *pN = &o.f[k]` local per saved register.
  release  two inlined releases (`igObject_Destroy` ref release and/or `StringChunk_ReleaseHeader`
           string release) of members at fixed offsets; union U template.

--search tries the declaration orders of the locals (and the late/early placement of the pointer
initialisers for `ptr`) with tools/verify.py at the alternate compiler -O3 and -O3,p (and the default
compiler for `release`) and keeps the first MATCH in DIR/NAME.c, printing the flags it needs.
Without --search only the first candidate is written.  Rows it cannot model print `skip`.
"""
import argparse
import itertools
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ALT = "local/mwcps2/combat/mwccps2.exe"
SP = 29
def sx(v): return v - 0x10000 if v >= 0x8000 else v
def load_syms():
    syms = {}
    for line in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        p = line.split()
        if len(p) >= 3 and not line.startswith("#"):
            try: syms[int(p[0], 16)] = p[2]
            except ValueError: pass
    return syms
def words(name):
    txt = open(os.path.join(ROOT, "asm", name + ".s")).read()
    return [int(x, 16) for x in re.findall(r"\.word (0x[0-9a-f]+)", txt)]

def trace(w, syms):
    frame = -sx(w[0] & 0xFFFF)
    reg = {}
    st = {"base": None}
    stmts = []
    calls = []
    sregs = {}   # reg -> addr off
    res = {"r": None}
    def exe(x):
        op = x >> 26; rs = (x >> 21) & 31; rt = (x >> 16) & 31; imm = sx(x & 0xFFFF)
        if op in (0x1F, 0x3F, 0x37, 0x1E): return
        if op == 9 and rs == SP:
            reg[rt] = ("addr", imm, None)
            if 16 <= rt <= 23: sregs[rt] = imm
        elif op == 9 and rs == 0: reg[rt] = ("c", imm)
        elif op == 0xF: reg[rt] = ("hi", (x & 0xFFFF) << 16)
        elif op == 9 and rs == rt and reg.get(rt, ("",))[0] == "hi": reg[rt] = ("c", reg[rt][1] + imm)
        elif op == 0 and (x & 0x3F) == 0x2D and rt == 0:
            rd = (x >> 11) & 31
            if rs == 0: reg[rd] = ("c", 0)
            else:
                v = reg.get(rs)
                if v and v[0] == "addr" and rs in sregs: v = ("addr", v[1], rs)
                reg[rd] = v
        elif op == 0x2B:
            if rs == SP:
                if rt == 0: stmts.append(("zero", imm, None))
                elif reg.get(rt, ("",))[0] == "c" and reg[rt][1] > 0x100000: stmts.append(("vt", imm, reg[rt][1]))
                else: raise ValueError("sw")
            elif rs in reg and reg[rs][0] == "addr" and rt == 0:
                stmts.append(("zero", reg[rs][1] + imm, rs if rs in sregs else None, imm))
            else: raise ValueError("sw base")
        elif op == 0x23:
            if imm in (28104, 916): pass
            elif rs == 2 and 16 <= rt <= 23:
                stmts.append(("t", imm)); res["r"] = rt
            else: raise ValueError("lw")
        elif op == 0 and (x & 0x3F) == 0x21: pass
        elif x == 0: pass
        else: raise ValueError("op %08x" % x)
    i = 0; skip = set()
    while i < len(w):
        x = w[i]
        if i in skip: i += 1; continue
        op = x >> 26
        if op in (4, 5, 1, 6, 7): raise ValueError("branch")
        if op == 3:
            exe(w[i + 1]); skip.add(i + 1)
            tgt = syms.get((x & 0x3FFFFFF) << 2)
            a0, a1 = reg.get(4), reg.get(5)
            if st["base"] is None:
                st["base"] = a0[1]; st["init"] = tgt
            else:
                stmts.append(("call", tgt, a0[1] if a0 and a0[0] == "addr" else None,
                              a0[2] if a0 and a0[0] == "addr" else None, a1[1] if a1 else None))
            reg.pop(4, None); reg.pop(5, None)
            i += 1; continue
        if op == 0 and (x & 0x3F) == 8: break
        if i < 8 and op in (0x2F, 0x3F, 0x1F) and ((x >> 21) & 31) == SP: i += 1; continue
        exe(x); i += 1
    return frame, st["base"], st["init"], stmts, sregs, res["r"]

def gen(name, w, syms, order=None, decl_order=None, late=False):
    frame, base, init, stmts, sregs, rres = trace(w, syms)
    size = frame - base
    nf = size // 4 - 1
    # pointer vars: s-regs used in stmts (zero via, call via)
    used = []
    for s in stmts:
        v = s[2] if s[0] == "zero" else (s[3] if s[0] == "call" else None)
        if v is not None and v not in used: used.append(v)
    vts = sorted({s[2] for s in stmts if s[0] == "vt"})
    def elem(a):
        k = (a - base) // 4
        return "&o" if k == 0 else "&o.f[%d]" % (k - 1)
    def ptrinit(r):
        a = sregs[r]
        d = (a - base) // 4
        return "(int *)&o" if d == 0 else "&o.f[%d]" % (d - 1)
    lines = []
    seen = set()
    seq = stmts if order is None else [stmts[i] for i in order]
    for s in seq:
        if late:
            v = s[2] if s[0] == "zero" else (s[3] if s[0] == "call" else None)
            if v is not None and v not in seen:
                seen.add(v); lines.append("    p%d = %s;" % (v, ptrinit(v)))
        if s[0] == "zero":
            if s[2] is not None:
                p = "p%d" % s[2]
                lines.append("    %s[%d] = 0;" % (p, s[3] // 4) if s[3] else "    *%s = 0;" % p)
            else:
                k = (s[1] - base) // 4
                lines.append("    o.f[%d] = 0;" % (k - 1))
        elif s[0] == "vt": lines.append("    o.vt = &DAT_%08x[0];" % s[2])
        elif s[0] == "t": lines.append("    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));")
        elif s[0] == "call":
            arg = ("p%d" % s[3]) if s[3] is not None else (elem(s[2]) if s[2] is not None else "0")
            if s[2] is not None and s[2] == base and s[3] is None: arg = "&o"
            lines.append("    %s(%s%s);" % (s[1], arg, "" if s[4] is None else ", %d" % s[4]))
    decls = []
    for r in used: decls.append("    int *p%d;" % r)
    decls.append("    int r;")
    if decl_order: decls = [decls[i] for i in decl_order]
    inits = "" if late else "".join("    p%d = %s;\n" % (r, ptrinit(r)) for r in used)
    cdecl = "".join("int %s();\n" % c for c in sorted({s[1] for s in stmts if s[0] == "call"}))
    ext = "".join("extern int DAT_%08x[4];\n" % v for v in vts)
    return ("struct W { int *vt; int f[%d]; };\n%sint %s(struct W *);\n%sextern void * DAT_00586dc8[4];\n"
            "int %s(void) {\n    struct W o;\n%s\n%s    %s(&o);\n%s\n    return r;\n}\n"
            % (nf, "", init, cdecl + ext, name, "\n".join(decls), inits, init, "\n".join(lines)))

def trace3(w, syms):
    frame = -sx(w[0] & 0xFFFF)
    reg = {}; st = {"base": None}; stmts = []; sregs = {}
    def exe(x):
        op = x >> 26; rs = (x >> 21) & 31; rt = (x >> 16) & 31; imm = sx(x & 0xFFFF)
        if op in (0x1F, 0x3F, 0x37, 0x1E): return
        if op == 9 and rs == SP:
            reg[rt] = ("addr", imm)
            if 16 <= rt <= 23: sregs[rt] = imm
        elif op == 9 and rs == 0: reg[rt] = ("c", imm)
        elif op == 0xF: reg[rt] = ("hi", (x & 0xFFFF) << 16)
        elif op == 9 and rs == rt and reg.get(rt, ("",))[0] == "hi": reg[rt] = ("c", reg[rt][1] + imm)
        elif op == 0 and (x & 0x3F) == 0x2D and rt == 0:
            rd = (x >> 11) & 31
            reg[rd] = ("c", 0) if rs == 0 else reg.get(rs)
        elif op == 0x2B:
            if rs == SP:
                if rt == 0: stmts.append(("zero", imm))
                elif reg.get(rt, ("",))[0] == "c" and reg[rt][1] > 0x100000: stmts.append(("vt", imm, reg[rt][1]))
                else: raise ValueError("sw")
            elif rs in reg and reg[rs][0] == "addr" and rt == 0 and imm == 0:
                stmts.append(("zero", reg[rs][1]))
            else: raise ValueError("sw base")
        elif op == 0x23:
            if imm in (28104, 916): pass
            elif rs == 2 and 16 <= rt <= 23: stmts.append(("t", imm))
            else: raise ValueError("lw")
        elif op == 0 and (x & 0x3F) == 0x21: pass
        elif x == 0: pass
        else: raise ValueError("op %08x" % x)
    i = 0
    n = len(w)
    while i < n:
        x = w[i]; op = x >> 26
        if op in (4, 5):
            rs = (x >> 21) & 31
            if op != 4 or rs == 0 or (x>>16)&31 != 0: raise ValueError("branch kind")
            tgt = i + 1 + sx(x & 0xFFFF)
            exe(w[i + 1])
            kinds = [syms.get((y & 0x3FFFFFF) << 2) for y in w[i + 2:tgt] if y >> 26 == 3]
            if len(kinds) != 1 or kinds[0] not in ("igObject_Destroy", "StringChunk_ReleaseHeader"): raise ValueError("block")
            a = reg.get(rs)
            if not a or a[0] != "addr": raise ValueError("member reg")
            stmts.append(("rel", a[1], kinds[0]))
            i = tgt; continue
        if op == 3:
            exe(w[i + 1])
            t = syms.get((x & 0x3FFFFFF) << 2)
            if st["base"] is None:
                st["base"] = reg[4][1]; st["init"] = t
            else: raise ValueError("extra call")
            reg.pop(4, None); reg.pop(5, None)
            i += 2; continue
        if op == 0 and (x & 0x3F) == 8: break
        if i < 8 and op in (0x2F, 0x3F, 0x1F) and ((x >> 21) & 31) == SP: i += 1; continue
        exe(x); i += 1
    return frame, st["base"], st["init"], stmts

def gen3(name, w, syms, decl_order=None, vt_perm=None):
    frame, base, init, stmts = trace3(w, syms)
    size = frame - base
    mem = {}
    for s in stmts:
        if s[0] == "rel": mem[s[1]] = s[2]
    offs = list(mem)
    vname = {o: "q%d" % k for k, o in enumerate(offs)}
    vts = sorted({s[2] for s in stmts if s[0] == "vt"})
    lines = []
    for s in stmts:
        if s[0] == "zero":
            o = s[1] - base
            if s[1] in mem:
                v = vname[s[1]]
                lines.append("    %s = &u.b[%d];" % (v, o) if mem[s[1]] == "StringChunk_ReleaseHeader" else "    %s = (S_ref *)&u.b[%d];" % (v, o))
                lines.append("    *(int *)%s = 0;" % v)
            else:
                lines.append("    *(int *)&u.b[%d] = 0;" % o)
        elif s[0] == "vt": lines.append("    u.vt = (int)&DAT_%08x[0];" % s[2])
        elif s[0] == "t": lines.append("    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];")
        elif s[0] == "rel":
            v = vname[s[1]]
            if s[2] == "igObject_Destroy":
                lines += ["    if (%s != 0) {" % v, "        %s = *(S_ref **)%s;" % (v, v), "        if (%s != 0) {" % v,
                  "            %s->f4 = (int)((int) (%s->f4 - 1));" % (v, v),
                  "            if (((unsigned long long) ((long long) %s->f4 << 0x29) >> 0x29) == 0) {" % v,
                  "                igObject_Destroy(%s);" % v, "            }", "        }", "    }"]
            else:
                lines += ["    if (%s != 0) {" % v, "        temp_v1 = *(int **)%s;" % v, "        if (temp_v1 != 0) {",
                  "            temp_a1 = temp_v1 - 2;", "            temp_v0 = temp_v1[-1] - 1;", "            temp_v1[-1] = temp_v0;",
                  "            if (temp_v0 == 0) {", "                StringChunk_ReleaseHeader(*temp_a1, temp_a1);", "            }", "        }", "    }"]
    decls = ["    int temp_s0;"]
    for o in offs: decls.append("    %s *%s;" % ("char" if mem[o] == "StringChunk_ReleaseHeader" else "S_ref", vname[o]))
    if any(mem[o] == "StringChunk_ReleaseHeader" for o in offs):
        decls += ["    int *temp_v1;", "    int *temp_a1;", "    int temp_v0;"]
    if decl_order: decls = [decls[i] for i in decl_order]
    ext = "".join("extern int DAT_%08x[4];\n" % v for v in vts)
    return ("typedef struct S_ref { char pad4[4]; int f4; } S_ref;\nint igObject_Destroy();\nint StringChunk_ReleaseHeader();\nint %s();\n%s"
            "extern void * DAT_00586dc8[4];\nunion U { int vt; char b[%d]; };\nint %s(void) {\n    union U u;\n%s\n\n    %s(u.b);\n%s\n    return temp_s0;\n}\n"
            % (init, ext, size, name, "\n".join(decls), init, "\n".join(lines))), len(decls)

def verify(va, path, flags):
    env=dict(os.environ); env['DW4_MWCC']=ALT
    r=subprocess.run(['python3','tools/verify.py',va,path,'--flags',flags],cwd=ROOT,env=env,capture_output=True,text=True)
    for l in r.stdout.splitlines():
        if l.startswith(('MATCH','DIFFER')): return l.split()[0]
    return 'ERR'


def addr_of(name, syms_path=None):
    for line in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        p = line.split()
        if len(p) >= 3 and p[2] == name:
            return "0x" + p[0]
    raise KeyError(name)


def search(name, out):
    syms = load_syms()
    w = words(name)
    va = addr_of(name)
    cands = []
    try:
        frame, base, init, stmts, sregs, rres = trace(w, syms)
        used = []
        for s in stmts:
            v = s[2] if s[0] == "zero" else (s[3] if s[0] == "call" else None)
            if v is not None and v not in used:
                used.append(v)
        for late in (True, False):
            for perm in itertools.permutations(range(len(used) + 1)):
                cands.append(("ptr", lambda p=perm, l=late: gen(name, w, syms, decl_order=list(p), late=l)))
    except Exception:
        pass
    try:
        src, nd = gen3(name, w, syms)
        for perm in itertools.islice(itertools.permutations(range(nd)), 0, 24):
            cands.append(("release", lambda p=perm: gen3(name, w, syms, decl_order=list(p))[0]))
    except Exception:
        pass
    tmp = os.path.join(out, name + ".c")
    for kind, mk in cands[:120]:
        open(tmp, "w").write(mk())
        for alt, fl in ((1, "-O3 -Iinclude"), (1, "-O3,p -Iinclude"), (0, "-O3 -Iinclude")):
            env = dict(os.environ)
            if alt:
                env["DW4_MWCC"] = ALT
            else:
                env.pop("DW4_MWCC", None)
            r = subprocess.run([sys.executable, "tools/verify.py", va, tmp, "--flags", fl],
                               cwd=ROOT, env=env, capture_output=True, text=True).stdout
            if r.startswith("MATCH"):
                print("MATCH", name, kind, "alternate" if alt else "default", fl)
                return True
    print("nomatch", name)
    return False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(ROOT, "src", "unmatched"))
    ap.add_argument("--search", action="store_true")
    ap.add_argument("names", nargs="+")
    a = ap.parse_args()
    syms = load_syms()
    for n in a.names:
        if a.search:
            search(n, a.out)
            continue
        w = words(n)
        for fn in (lambda: gen(n, w, syms, late=True), lambda: gen3(n, w, syms)[0]):
            try:
                open(os.path.join(a.out, n + ".c"), "w").write(fn())
                print("wrote", n)
                break
            except (ValueError, IndexError, KeyError, TypeError):
                continue
        else:
            print("skip", n)


if __name__ == "__main__":
    main()
