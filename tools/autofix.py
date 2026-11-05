#!/usr/bin/env python3
"""autofix.py — iteratively repair m2c drafts MWCC rejects, using the compiler's
own diagnostics, then verify each repaired draft.

m2c types recovered address temporaries `void *`, then uses them in integer
arithmetic (illegal type) or dereferences an `int` (pointer/array required); it
also references stack slots (`sp4C`) it forgot to declare. The compiler points a
caret at the offending token, so this driver reads (line, column, message),
flips the declaration of the identifier under the caret, and recompiles until the
unit is accepted or the repair budget is spent.
"""
import json, os, re, subprocess, sys
from multiprocessing import Pool

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT + "/tools")
import verify as vfy  # noqa: E402

WIBO = ROOT + "/local/wibo"
MWCC = ROOT + "/local/mwcps2/3.0-011126/mwccps2.exe"
SYMBOLS = ROOT + "/config/symbols.txt"
ELF = ROOT + "/orig/SLUS-20836/SLUS_208.36"
SRC = ROOT + "/build/m2c"
OUT = ROOT + "/build/m2c_autofix"

PREAMBLE = ["#define unaligned", "#define M2C_ERROR(x) 0",
            "typedef long long s128;", "typedef unsigned long long u128;"]
PTR_TYPES = ["void *", "int *", "char *", "unsigned int *"]
INT_TYPES = ["int", "unsigned int"]

ERR_RE = re.compile(r"^#\s+(\d+):\s?(.*)$")


def strip_header(t):
    return "".join(l for l in t.splitlines(keepends=True)
                   if not l.startswith("/*") and not l.startswith(" * ")).lstrip("\n")


def demote_ptrs(body):
    return re.sub(r"\bvoid (\*(?:var|temp|unk|sp)_?[A-Za-z0-9_]*)", r"int \1", body)


def compile_raw(text, name, tag):
    p = os.path.join(OUT, "%s_%s.c" % (name, tag))
    open(p, "w").write(text)
    r = subprocess.run([WIBO, MWCC, "-c", "-O3", "-Iinclude", p, "-o", os.path.join(OUT, "t.o")],
                       capture_output=True, text=True,
                       env=dict(os.environ, MWCIncludes=OUT))
    return (r.stdout + r.stderr).replace("\r", "")


def first_error(out):
    lines = out.splitlines()
    for i, l in enumerate(lines):
        m = ERR_RE.match(l)
        if m and i + 1 < len(lines) and lines[i + 1].strip().startswith("#   Error:"):
            caret = lines[i + 1]
            col = caret.index("^") - len("#   Error:")
            msg = lines[i + 2].strip().lstrip("#").strip() if i + 2 < len(lines) else ""
            return int(m.group(1)), m.group(2), col, msg
    return None


def ident_at(line, col):
    best = None
    for m in re.finditer(r"[A-Za-z_]\w*", line):
        if m.start() <= col < m.end():
            return m.group(0)
        if m.start() <= col:
            best = m.group(0)
    return best


def set_decl_type(text, name, newtype):
    pat = re.compile(r"\b(?:void \*|int \*|char \*|unsigned int \*|int|unsigned int|"
                     r"long long|unsigned long long|short|unsigned short|char|"
                     r"unsigned char)\s*(\*?)%s\b" % re.escape(name))
    m = pat.search(text)
    if not m:
        # a later declarator in a multi-declaration line: `void *a, *b;`
        m2 = re.search(r"(?:,\s*)(\*?)%s\b" % re.escape(name), text)
        if m2:
            star = m2.group(1)
            t = newtype if star else newtype.replace(" *", "")
            return text[:m2.start()] + ", " + t + " " + star + name + text[m2.end():]
        return None
    star = m.group(1)
    t = newtype if (star and newtype.endswith("*")) else (newtype.replace(" *", "") if not star else newtype)
    return text[:m.start()] + t + " " + star + name + text[m.end():]


def add_decl(text, name):
    if re.search(r"\b%s\b\s*[;=,)]" % re.escape(name), text):
        pass
    # declare at file scope, right after the preamble/typedefs
    return "#define unaligned\n" if False else text


def repair(name, draft):
    body = demote_ptrs(strip_header(open(draft).read()))
    extra = []
    flip = {}
    for attempt in range(24):
        text = "\n".join(PREAMBLE + extra) + "\n" + body
        out = compile_raw(text, name, "a%d" % attempt)
        if "Error" not in out and "error" not in out:
            return text, "ok"
        fe = first_error(out)
        if not fe:
            return None, "unparsed"
        lineno, srcline, col, msg = fe
        if msg.startswith("undefined identifier"):
            ident = msg.split("'")[1] if "'" in msg else None
            if not ident or not re.fullmatch(r"[A-Za-z_]\w*", ident):
                return None, "noident"
            extra.append("int %s;" % ident)
            continue
        ident = ident_at(srcline, col)
        if not ident:
            return None, "noid"
        if msg.startswith("pointer/array required"):
            newt = "int *"
        elif msg.startswith("illegal type") or msg.startswith("illegal operand") or \
                msg.startswith("illegal implicit conversion"):
            # toggle int <-> pointer: m2c's recovered temporaries are word-sized,
            # and the right declaration depends on how the value is used.
            newt = "int" if flip.get(ident, 0) % 2 == 0 else "int *"
            flip[ident] = flip.get(ident, 0) + 1
        else:
            return None, msg[:40]
        nt = set_decl_type(text, ident, newt)
        handled_extra = False
        if nt is None:
            for i, d in enumerate(extra):
                if d.split()[-1].rstrip(";") == ident:
                    extra[i] = "%s %s;" % (newt, ident)
                    nt = text
                    handled_extra = True
                    break
        if nt is None:
            return None, "nodcl:" + ident
        if not handled_extra:
            newbody = set_decl_type(body, ident, newt)
            if newbody is None or newbody == body:
                return None, "nodcl:" + ident
            body = newbody
        text = nt
    return None, "budget"


def do_one(row):
    name = row["name"]
    draft = None
    for e in (".c", ".cpp"):
        p = os.path.join(SRC, name + e)
        if os.path.exists(p):
            draft = p
            break
    if not draft:
        return {"name": name, "status": "nodraft"}
    os.makedirs(OUT, exist_ok=True)
    text, why = repair(name, draft)
    if not text:
        return {"name": name, "status": "nofix", "why": why}
    dest = os.path.join(OUT, name + ".c")
    open(dest, "w").write(text)
    va = row.get("va")
    if not va:
        return {"name": name, "status": "fixed_nova"}
    ok, rep = vfy.verify_one(va, dest, symbols=SYMBOLS, elf=ELF)
    if ok:
        bank = os.path.join(ROOT, "src", "unmatched", name + ".c")
        if not os.path.exists(bank):
            open(bank, "w").write(
                "/* 0x%08x — %s. m2c draft auto-repaired to compile; verified\n"
                " * byte-identical by tools/verify.py (tools/autofix.py). */\n" % (va, name) + text)
        return {"name": name, "status": "BANKED"}
    return {"name": name, "status": "fixed", "va": va}


if __name__ == "__main__":
    rows = [json.loads(l) for l in open(ROOT + "/build/near_scan.jsonl")]
    todo = [r for r in rows if r["status"] == "compile"]
    print("auto-repairing %d compile failures" % len(todo), flush=True)
    res = []
    with Pool(int(os.environ.get("SWEEP_WORKERS", "16"))) as pool:
        for i, r in enumerate(pool.imap_unordered(do_one, todo, chunksize=4)):
            res.append(r)
            if r["status"] == "BANKED":
                print("  BANKED %s" % r["name"], flush=True)
            if (i + 1) % 100 == 0:
                print("  %d/%d" % (i + 1, len(todo)), flush=True)
    with open(ROOT + "/build/autofix.jsonl", "w") as fh:
        for r in res:
            fh.write(json.dumps(r) + "\n")
    import collections
    print(collections.Counter(r["status"] for r in res))
