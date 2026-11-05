#!/usr/bin/env python3
"""Replace file-private two-word refcount shim structs with the authoritative `igObject`.

Matched C spells the header of every engine object, a vtable word at +0 and a reference-count word at
+4, as a private struct per file (`struct T { int word0; int references; }`, `struct Rc { int vt;
unsigned rc; }`, ... 548 definitions in src/). `config/SLUS-20836/authoritative-fields.tsv` records that layout
for `igObject` (evidence: the release idiom `--o->refs; if ((refs & 0x7fffff) == 0) igObject_Destroy(o)`
at hundreds of matched sites, the matched `igObject_Destroy` it calls and `igObject_InitHeader`), and
`scripts/gen_type_headers.py` emits it into include/dw4/reflected.h. This script then deletes the
shim definition in a file, retypes its users to `igObject` and renames the count member to `_refCount`.

Every changed file is re-verified function by function with tools/verify.py; a file that does not
match byte for byte is restored. Only functions in config/typed-scope.tsv are touched.

Usage:
  scripts/retype_igobject_shims.py              # dry run: what would change
  scripts/retype_igobject_shims.py --apply      # rewrite, verify, restore the files that fail
"""
import argparse
import collections
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "tools"))
import units  # noqa: E402

FIRST = {"word0", "w0", "vt", "vtable", "p0", "pad0", "f0", "vptr", "word_0"}
SECOND = {"refs", "references", "rc", "f4", "refcount", "refCount", "references_"}
SHIM = re.compile(r"(?:typedef\s+)?struct\s+(\w+)\s*\{\s*(?:int|unsigned(?:\s+int)?)\s+(\w+)\s*;"
                  r"\s*(int|unsigned(?:\s+int)?)\s+(\w+)\s*;\s*\}\s*(\w*)\s*;")
INCLUDE = '#include "dw4/reflected.h"\n'


def scope_files(scope_tsv, symbols="config/SLUS-20836/symbols.txt"):
    names = {l.split("\t")[0] for l in open(scope_tsv) if l.strip() and not l.startswith("#")}
    paths = units.scan("src")
    return sorted({paths[n] for n in names if n in paths and "/asmbody/" not in paths[n]})


def rewrite(text):
    """(new text, shim names replaced) or (None, [])."""
    shims = {}
    for m in SHIM.finditer(text):
        name, a, ctype, b, alias = m.groups()
        if a in FIRST and b in SECOND:
            shims[name] = (b, ctype)
    if not shims:
        return None, []
    new = text
    for name, (member, ctype) in shims.items():
        # drop the definition (struct or typedef struct)
        new = re.sub(r"(?:typedef\s+)?struct\s+%s\s*\{[^{}]*\}\s*\w*\s*;[ \t]*\n?" % re.escape(name), "", new)
        # every declared variable/field/parameter of the shim type, then its type name
        vars_ = set(re.findall(r"\b(?:struct\s+)?%s\s*\*+\s*(?:volatile\s+)?(\w+)" % re.escape(name), new))
        new = re.sub(r"\bstruct\s+%s\b" % re.escape(name), "igObject", new)
        new = re.sub(r"\b%s\b" % re.escape(name), "igObject", new)
        for v in vars_:
            new = re.sub(r"\b%s\s*->\s*%s\b" % (re.escape(v), re.escape(member)), "%s->_refCount" % v, new)
        new = re.sub(r"\(\s*\(\s*igObject\s*\*\s*\)\s*([^()]*?)\s*\)\s*->\s*%s\b" % re.escape(member),
                     lambda m: "((igObject *)%s)->_refCount" % m.group(1), new)
        if ctype == "int":
            # igObject._refCount is unsigned (lwu where the code reads it as 64-bit); a site the retail
            # code spells as a signed int reads it through an (int) cast, which keeps the plain lw
            new = re.sub(r"(?<![\w.>])(?<!\(int\))(\w+(?:->\w+)*)->_refCount\b(?!\s*=[^=])",
                         lambda m: "(int)%s->_refCount" % m.group(1), new)
            new = re.sub(r"(?<!\(int\))(\(\(igObject \*\)[^()]*\))->_refCount\b(?!\s*=[^=])",
                         lambda m: "(int)%s->_refCount" % m.group(1), new)
    if "dw4/reflected.h" not in new:
        new = INCLUDE + new
    return new, sorted(shims)


def verify_file(path, sym, env):
    text = open(path, errors="replace").read()
    bad = []
    for name, _s, _e in units.definitions(text):
        if name not in sym:
            continue
        if "beNDMWGameRam__vfunc_34" in path:
            e2 = dict(env, DW4_MWCC="local/mwcps2/combat/mwccps2.exe")
            r = subprocess.run([sys.executable, "tools/dispatcher/full_verify.py", path],
                               capture_output=True, text=True, env=e2)
            if "VERDICT: MATCH" not in r.stdout:
                bad.append(name)
            continue
        r = subprocess.run([sys.executable, "tools/verify.py", "0x%x" % sym[name], path],
                           capture_output=True, text=True, env=env)
        out = (r.stdout + r.stderr).splitlines()
        if not (r.returncode == 0 and any(l.startswith("MATCH") for l in out)
                and not any(l.startswith("DIFFER") for l in out)):
            bad.append(name)
    return bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--scope", default="config/typed-scope.tsv")
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--jobs", type=int, default=8)
    a = ap.parse_args()
    sym = {}
    for l in open("config/SLUS-20836/symbols.txt"):
        f = l.split()
        if len(f) >= 3 and not l.startswith("#"):
            sym[f[2]] = int(f[0], 16)
    env = dict(os.environ, DW4_ELF=os.environ.get("DW4_ELF", "orig/SLUS-20836/SLUS_208.36"))
    changes = {}
    for path in scope_files(a.scope):
        text = open(path, errors="replace").read()
        new, shims = rewrite(text)
        if new is not None and new != text:
            changes[path] = (text, new, shims)
    print("files with an igObject shim: %d" % len(changes))
    if not a.apply:
        for p, (_, _, s) in sorted(changes.items())[:20]:
            print("  %-70s %s" % (p, ",".join(s)))
        return 0
    for p, (_, new, _) in changes.items():
        open(p, "w").write(new)

    def check(p):
        return p, verify_file(p, sym, env)

    kept = restored = 0
    with ThreadPoolExecutor(a.jobs) as ex:
        for p, bad in ex.map(check, list(changes)):
            if bad:
                open(p, "w").write(changes[p][0])
                restored += 1
                print("restored %s (%s)" % (p, ",".join(bad[:3])))
            else:
                kept += 1
    print("igObject shims replaced in %d files, %d restored" % (kept, restored))
    return 0


if __name__ == "__main__":
    sys.exit(main())
