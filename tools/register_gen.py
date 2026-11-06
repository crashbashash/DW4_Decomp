#!/usr/bin/env python3
"""register_gen.py [--out DIR] [--dry-run] NAME... — emit the `<Class>_Register` registrars from asm/NAME.s.

Every `<Class>_Register` is the same body (docs/engine/reflection-metadata.md section 1): a
`<Library>Library_MarkRegistered` call, then `igMetaObject_RegisterClass` with eight register arguments (a0..t3) and three
stack arguments (sp+0, sp+8, sp+16).  The generator reads the retail words, resolves every address through
config/SLUS-20836/symbols.txt (functions) or the naming convention of the existing files (`g_<Class>_metaObject_<addr>`,
`<Class>_className`, `g_<Class>_callbackList_<addr>`), and keeps any identifier the existing
translation unit already uses for the same address, so hand-recovered names survive a regeneration.

Build profile (phase 3b, docs/engine/build-profiles.md): the unit profile of the function decides the
language.  A unit compiled with exceptions on keeps a 12-byte exception index record for this body in retail,
which only the C++ front end emits, so the file is written as `.cpp` (`extern "C"` linkage); a unit with
exceptions off (or outside every unit) is written as `.c`.  The stale twin (`.c` when `.cpp` is written and
vice versa) is removed so one translation unit owns the function.  The generator does not claim a match:
verify with `python3 tools/verify.py 0x<va> <file>`.
"""
import argparse
import glob
import os
import re
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import verify  # noqa: E402
import unitprofiles  # noqa: E402

SP = 29
REGNAME = {4: "a0", 5: "a1", 6: "a2", 7: "a3", 8: "t0", 9: "t1", 10: "t2", 11: "t3"}
# Named arguments say what they are; a bare number needs its role beside it.
ROLES = {0: "abstract", 6: "instance size", 9: "extra callback item", 10: "callback list"}
# C++ parameter list of igMetaObject_RegisterClass, one entry per argument, in call order.
PARAMS = [
    ("int", "abstractState"),
    ("igMetaObject **", "slot"),
    ("void *(*)(void)", "baseRegister"),
    ("igMetaObject *(*)(void)", "baseMetaObject"),
    ("igMetaObject *(*)(void)", "getMetaObject"),
    ("const char *", "className"),
    ("int", "instanceSize"),
    ("int (*)(void)", "getVTable"),
    ("void (*)(void)", "initFields"),
    ("void (*)(void)", "callbackItem"),
    ("void *", "callbackList"),
]
# Declaration of a function-typed argument, by argument index.
FN_DECL = {2: "void *%s(void);", 3: "igMetaObject *%s(void);", 4: "igMetaObject *%s(void);",
           7: "int %s(void);", 8: "void %s(void);", 9: "void %s(void);"}


def sx(v):
    return v - 0x10000 if v >= 0x8000 else v


def load_syms():
    syms, addr_of = {}, {}
    for line in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        p = line.split()
        if len(p) >= 3 and not line.startswith("#"):
            try:
                syms[int(p[0], 16)] = p[2]
                addr_of[p[2]] = int(p[0], 16)
            except ValueError:
                pass
    return syms, addr_of


def words(name):
    txt = open(os.path.join(ROOT, "asm", name + ".s")).read()
    return [int(x, 16) for x in re.findall(r"\.word (0x[0-9a-f]+)", txt)]


def trace(w, syms):
    """Return (setonce, registrar, args) with args[i] = ('c', value) | ('a', address) for the 11 arguments."""
    if w[0] != 0x27BDFFD0:
        raise ValueError("not the 48-byte-frame registrar body")
    reg = {}
    stack = {}
    calls = []
    def exe(x):
        op, rs, rt, imm = x >> 26, (x >> 21) & 31, (x >> 16) & 31, sx(x & 0xFFFF)
        if op == 9 and rs == SP and rt == SP:               # the frame itself
            pass
        elif op == 0xF:                                     # lui
            reg[rt] = ("hi", (x & 0xFFFF) << 16)
        elif op == 9 and rs == rt and reg.get(rt, ("",))[0] == "hi":   # addiu rt,rt,lo
            reg[rt] = ("a", reg[rt][1] + imm)
        elif op == 9 and rs == 0:                           # li
            reg[rt] = ("c", imm)
        elif op == 0 and (x & 0x3F) == 0x2D and rt == 0:    # move rd,rs
            reg[(x >> 11) & 31] = reg.get(rs, ("c", 0)) if rs else ("c", 0)
        elif op == 0x3F and rs == SP:                       # sd rt,N(sp)  (ra's own save excluded)
            if rt != 31:
                stack[imm] = reg.get(rt, ("c", 0))
        elif op == 0x37 or (op == 0 and (x & 0x3F) == 8) or x == 0:  # ld ra / jr / nop
            pass
        else:
            raise ValueError("unexpected word %08x" % x)

    i = 0
    while i < len(w):
        x = w[i]
        if x >> 26 == 3:                                    # jal: the delay slot runs first
            exe(w[i + 1])
            calls.append((x & 0x3FFFFFF) << 2)
            i += 2
            continue
        exe(x)
        i += 1
    if len(calls) != 2:
        raise ValueError("expected two calls, found %d" % len(calls))
    setonce, registrar = calls
    if syms.get(registrar) != "igMetaObject_RegisterClass":
        raise ValueError("second call is %s, not igMetaObject_RegisterClass" % syms.get(registrar))
    args = [reg.get(r, ("c", 0)) for r in (4, 5, 6, 7, 8, 9, 10, 11)]
    args += [stack.get(0, ("c", 0)), stack.get(8, ("c", 0)), stack.get(16, ("c", 0))]
    return syms[setonce], args


def existing_names(cls):
    """{address: identifier} for every address-bearing identifier the current translation unit uses."""
    names, table = {}, verify.data_symbols()
    for path in glob.glob(os.path.join(ROOT, "src", "*", cls + "_Register.c*")):
        text = open(path).read()
        for m in re.finditer(r"\b([A-Za-z_]\w*?_([0-9a-f]{8}))\b", text):
            names.setdefault(int(m.group(2), 16), m.group(1))
        for m in re.finditer(r"\b[A-Za-z_]\w*\b", text):
            if m.group(0) in table:
                names.setdefault(table[m.group(0)], m.group(0))
    return names


def spell(cls, idx, arg, syms, old):
    """The identifier (or constant) spelling argument `idx`, plus its declaration line or None."""
    kind, value = arg
    if kind == "c":
        return (hex(value) if value > 9 else str(value)), None
    if idx in FN_DECL:
        name = pick_name(syms.get(value), old.get(value))
        if name is None:
            raise ValueError("no symbol for function argument %d at 0x%08x" % (idx, value))
        return name, FN_DECL[idx] % name
    if idx == 1:
        # an array of unknown bound: a scalar would be placed in the gp-relative small data
        # section and addressed with one `addiu a1,gp,...` where retail has lui/addiu
        name = old.get(value) or "g_%s_metaObject_%08x" % (cls, value)
        return name, "extern igMetaObject *%s[];" % name
    if idx == 5:
        name = old.get(value) or "%s_className" % cls
        return name, "extern const char %s[];" % name
    if idx == 10:
        name = pick_name(syms.get(value), old.get(value)) or "g_%s_callbackList_%08x" % (cls, value)
        return name, "extern char %s[];" % name
    raise ValueError("argument %d is an address" % idx)


def placeholder(name):
    return name is None or re.match(r"^(thunk_)?(FUN|DAT|LAB)_[0-9a-f]{8}$", name) is not None


def pick_name(symbol, old):
    """config/SLUS-20836/symbols.txt wins unless it only has a placeholder and the translation unit has a real name."""
    if placeholder(symbol) and old and not placeholder(old):
        return old
    return symbol or old


def base_class(registrar):
    m = re.match(r"^(\w+)_Register$", registrar)
    return m.group(1) if m else None


def emit(name, va, syms, cxx):
    cls = name[: -len("_Register")]
    w = words(name)
    setonce, args = trace(w, syms)
    old = existing_names(cls)
    spelled, decls = [], []
    for i, a in enumerate(args):
        s, d = spell(cls, i, a, syms, old)
        spelled.append(s)
        if d:
            decls.append(d)
    base = base_class(spelled[2])
    derived = (", derived from %s" % base) if base else ""
    params = ",\n        ".join(t.replace("(*)", "(*%s)" % n) if "(*)" in t else ("%s%s" % (t, n) if t.endswith("*") else "%s %s" % (t, n))
                             for t, n in PARAMS)
    seen = set()
    decls = [d for d in decls if not (d in seen or seen.add(d))]
    body = ""
    for i, s in enumerate(spelled):
        role = " /* %s */" % ROLES[i] if i in ROLES and s[0].isdigit() else ""
        body += "        %s%s%s\n" % (s, "," if i < 10 else "", role)
    out = ""
    out += "struct igMetaObject;\n"
    if cxx:
        out += 'extern "C" {\n'
    out += "void %s(void);\n" % setonce
    out += "void *igMetaObject_RegisterClass(\n        %s);\n" % params
    out += "".join(d + "\n" for d in decls)
    out += "void *%s(void);\n" % name
    if cxx:
        out += "}\n"
    out += "\nvoid *%s(void) {\n    %s();\n    return igMetaObject_RegisterClass(\n%s    );\n}\n" % (name, setonce, body)
    if not cxx:
        out = out.replace("struct igMetaObject;\n", "typedef struct igMetaObject igMetaObject;\n")
    return out


def target_path(name, out_dir, cxx):
    """Keep the function in the folder that owns it today; default src/unmatched."""
    hits = glob.glob(os.path.join(ROOT, "src", "*", name + ".c*"))
    folder = os.path.dirname(hits[0]) if hits and out_dir is None else (out_dir or os.path.join(ROOT, "src", "unmatched"))
    return os.path.join(folder, name + (".cpp" if cxx else ".c")), hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=None, help="output folder (default: the folder that holds the function today)")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("names", nargs="+")
    a = ap.parse_args()
    syms, addr_of = load_syms()
    for n in a.names:
        va = addr_of.get(n)
        if va is None:
            print("skip", n, "not in config/SLUS-20836/symbols.txt")
            continue
        res = unitprofiles.resolve(va, "-O3 -Iinclude", "local/mwcps2/3.0-011126/mwccps2.exe")
        cxx = res.profile.exceptions == "on"
        try:
            src = emit(n, va, syms, cxx)
        except (ValueError, KeyError, IndexError) as e:
            print("skip", n, e)
            continue
        path, hits = target_path(n, a.out, cxx)
        if a.dry_run:
            print("would write", os.path.relpath(path, ROOT))
            continue
        for h in hits:
            if a.out is None and os.path.abspath(h) != os.path.abspath(path):
                rename_tracked(h, path)      # in-place regeneration: the twin becomes the new file
        open(path, "w").write(src)
        print("wrote", os.path.relpath(path, ROOT), "cpp" if cxx else "c")


def rename_tracked(old, new):
    """`git mv` when the old file is tracked (keeps the rename in history), plain rename otherwise.
    Concurrent generators contend for the index lock, so a failed `git mv` is retried briefly."""
    if subprocess.run(["git", "-C", ROOT, "ls-files", "--error-unmatch", old], capture_output=True).returncode != 0:
        os.replace(old, new)
        return
    for attempt in range(100):
        r = subprocess.run(["git", "-C", ROOT, "mv", "-f", old, new], capture_output=True, text=True)
        if r.returncode == 0:
            return
        if "index.lock" not in r.stderr:
            raise RuntimeError("git mv %s -> %s failed: %s" % (old, new, r.stderr.strip()))
        time.sleep(0.2)
    raise RuntimeError("git mv %s -> %s: index lock held for too long" % (old, new))


if __name__ == "__main__":
    main()
