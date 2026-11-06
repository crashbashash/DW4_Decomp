#!/usr/bin/env python3
"""apply_data_names.py — apply `config/SLUS-20836/data-names.tsv` to the matched C sources.

The data counterpart of `apply_names.py`.  A data symbol has no layout entry or
`asm/` unit, so a rename only touches the C that mentions it: every `DAT_<addr>`
in the chosen modules becomes the overlay name (word-boundary match, so
`DAT_0013b120` never matches inside a longer name).  The build still finds the
symbol's address because a recovered name has a row in that table or is a function
symbol (`tools/verify.py:sym_address`, `tools/linkgen.py`).

A `function-symbol` row names a callback passed by address.  Its old declaration
was `extern <type> DAT_<addr>[...];`; once the name is a function, that line
becomes a function declaration (`int name();`) unless the unit already declares
or defines the function, in which case the line is dropped.  A symbol the unit
indexes (`DAT_x[2]`) keeps its data declaration, and `&DAT_x[0]` becomes plain `name`.  C++ units keep the
data declaration: a function declared there would be name-mangled and could not be
passed as a `char *`.

  apply_data_names.py --module engine           # dry run for one src/ folder
  apply_data_names.py --module engine --apply   # rewrite it
  apply_data_names.py --all --apply --check     # every module, then make check/link

`--literals` also names the class-handle slots that the source reads by absolute
address (`*(int *)0x0058a0e0` becomes `g_ParticleInfo_metaObject_0058a0e0[0]`, with
an `extern int ...[4];` declaration — the array form keeps the load absolute rather
than gp-relative, as for every other extern here).

Run `make check` and `make link` afterwards: only a clean check makes the batch
safe to commit.
"""
import argparse
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SCOPE = ("engine", "game", "lua", "audio", "menu", "movie")
DAT = re.compile(r"\bDAT_([0-9a-f]{8})\b")


def load(path):
    rows = {}
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        va, name, rule = ln.rstrip("\n").split("\t")
        rows[int(va, 16)] = (name, rule)
    return rows


def declaration(addr):
    """Regex for the unit's `extern ... DAT_<addr>...;` line, newline included."""
    return re.compile(r"^extern [^;\n]*\bDAT_%08x\b[^;\n]*;[ \t]*\n" % addr, re.M)


def rewrite(text, rows, cpp=False):
    """-> (new_text, number_of_symbols_renamed)."""
    used = {int(m.group(1), 16) for m in DAT.finditer(text)} & rows.keys()
    for addr in sorted(used):
        name, rule = rows[addr]
        if rule == "function-symbol" and not cpp:
            text = re.sub(r"&DAT_%08x\[0\]" % addr, "DAT_%08x" % addr, text)
            if not re.search(r"\bDAT_%08x\s*\[" % addr, text):   # never indexed: a plain callback
                already = re.search(r"\b%s\s*\(" % re.escape(name), text)
                text = declaration(addr).sub("" if already else "int %s();\n" % name, text, count=1)
        text = re.sub(r"\bDAT_%08x\b" % addr, name, text)
    return text, len(used)


LITERAL = re.compile(r"\*\s*\(\s*int\s*\*\s*\)\s*0x0*([0-9a-fA-F]{6})\b")
INCLUDE_END = re.compile(r"\A(?:/\*.*?\*/\s*)?(?:#include[^\n]*\n)*", re.S)


def name_literals(text, handles):
    """Replace `*(int *)0x<handle slot>` with the named handle global; -> (text, count)."""
    wanted = {}
    def sub(m):
        va = int(m.group(1), 16)
        if va not in handles:
            return m.group(0)
        wanted[va] = handles[va]
        return "%s[0]" % handles[va]
    text = LITERAL.sub(sub, text)
    if wanted:
        decls = "".join("extern int %s[4];\n" % n for _, n in sorted(wanted.items()))
        head = INCLUDE_END.match(text).end()
        text = text[:head] + decls + text[head:]
    return text, len(wanted)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--module", action="append", choices=SCOPE, help="src/ folder to rewrite")
    ap.add_argument("--all", action="store_true", help="every module in scope")
    ap.add_argument("--literals", action="store_true", help="also name class-handle slots read by absolute address")
    ap.add_argument("--apply", action="store_true", help="write the files (default: dry run)")
    ap.add_argument("--check", action="store_true", help="run make check and make link afterwards")
    ap.add_argument("--table", default=os.path.join(ROOT, "config/SLUS-20836/data-names.tsv"))
    a = ap.parse_args()
    mods = SCOPE if a.all else (a.module or [])
    if not mods:
        ap.error("choose --module or --all")
    rows = load(a.table)
    handles = {va: name for va, (name, rule) in rows.items() if rule == "class-handle"}
    files = renamed = 0
    for mod in mods:
        d = os.path.join(ROOT, "src", mod)
        for f in sorted(os.listdir(d)):
            path = os.path.join(d, f)
            old = open(path).read()
            new, n = rewrite(old, rows, f.endswith(".cpp"))
            if a.literals and not f.endswith(".cpp"):
                new, extra = name_literals(new, handles)
                n += extra
            if new != old:
                files += 1
                renamed += n
                if a.apply:
                    open(path, "w").write(new)
    print("%s %d symbol uses in %d files (%s)" %
          ("renamed" if a.apply else "would rename", renamed, files, ", ".join(mods)))
    if a.apply and a.check:
        for target in ("check", "link"):
            if subprocess.call(["make", target], cwd=ROOT) != 0:
                print("make %s failed: revert with git checkout -- src/" % target)
                return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
