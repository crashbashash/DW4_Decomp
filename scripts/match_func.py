#!/usr/bin/env python3
"""
match_func.py — matching-decompilation harness for Digimon World 4 (SLUS-20836).

Compiles a candidate C function with the *original* compiler (Metrowerks
CodeWarrior for PS2, version 3.0 build 011126) and diffs the emitted instruction
words against the bytes at the target address in the retail ELF.

The compiler is a 32-bit Windows PE binary and is NOT redistributable, so it is
kept outside this repo (gitignored) and supplied by the user:

    local/mwcps2/3.0-011126/mwccps2.exe  (gitignored; see README §Prerequisites)

Transport is **wibo** (the N64/PS2 decomp community's Win32 loader), not Wine:
under Wine this compiler aborts with `License check failed` (FLEXlm), under wibo it
compiles. Get wibo from https://github.com/decompals/wibo/releases.

Toolchain identity (verified by CRC32 against the published inventory):
    mwccps2.exe (3.0, 011126)  CRC32 C82F0A93   <- the compiler that built the game
    mwccps2.exe (2.4, 001213)  CRC32 D37D90D4   <- near miss: same .comment, wrong
                                                   register-move idiom, see docs
    mwldps2.exe (2.4, 001213)  CRC32 6F8C5863
    asm_r5900_elf.exe          CRC32 2B1C459C

The `.comment` string is useless for identification: "MW MIPS C Compiler
(2.4.1.01)" is emitted by 2.4 *and* 3.0 releases alike.

Usage:
  match_func.py 0x151090 cand.c f1 [--flags "-O4,p"] [--size N] [--show]

  --flags   compiler flags (default "-O4,p")
  --size    target byte count; default from ../data/functions.json
  --show    print both disassemblies even on a match

Exit status: 0 match, 1 mismatch, 2 error.
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
MWCC_DEFAULT = os.path.join(ROOT, "local", "mwcps2", "3.0-011126", "mwccps2.exe")
WIBO_DEFAULT = os.environ.get("DW4_WIBO", os.path.join(ROOT, "local", "wibo"))
# The ELF loads at 0x100000 from file offset 0x80.
VADDR_BASE, FILE_BASE = 0x100000, 0x80


def elf_bytes(path, va, n):
    with open(path, "rb") as fh:
        fh.seek(va - VADDR_BASE + FILE_BASE)
        return fh.read(n)


def func_size(addr, functions_json):
    """Look the target up in the Ghidra dump; returns size or None."""
    try:
        fns = json.load(open(functions_json))["functions"]
    except Exception:
        return None
    want = int(addr, 0)
    for f in fns:
        try:
            if int(f["address"], 0) == want:
                return f.get("size")
        except (TypeError, ValueError):
            continue
    return None


def disasm_words(obj, func_name=None):
    """Instruction words of the object, optionally only function `func_name`.

    Read from the symbol table plus raw .text bytes, NOT from `objdump -d`:
    objdump elides runs of 0x00000000 as `...`, which silently drops `nop`s and
    makes a correct match look like a mismatch.
    """
    binpath = "/tmp/match_func_text.bin"
    if os.path.exists(binpath):
        os.remove(binpath)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-j", ".text", "-O", "binary",
                    obj, binpath], capture_output=True)
    if not os.path.exists(binpath):
        return []
    text = open(binpath, "rb").read()
    if func_name is None:
        return [struct.unpack_from("<I", text, 4 * i)[0] for i in range(len(text) // 4)]
    syms = subprocess.run(["mipsel-linux-gnu-readelf", "-sW", obj],
                          capture_output=True, text=True).stdout
    for ln in syms.splitlines():
        f = ln.split()
        if len(f) >= 8 and f[7] == func_name and f[3] in ("FUNC", "OBJECT", "NOTYPE"):
            off, size = int(f[1], 16), int(f[2], 16)
            if size:
                chunk = text[off:off + size]
                return [struct.unpack_from("<I", chunk, 4 * i)[0]
                        for i in range(len(chunk) // 4)]
    return []


def words_to_bytes(words):
    return b"".join(struct.pack("<I", w) for w in words)


def diff_report(theirs, mine):
    """Both are lists of 32-bit words."""
    n = max(len(theirs), len(mine))
    lines = []
    for i in range(n):
        t = theirs[i] if i < len(theirs) else None
        m = mine[i] if i < len(mine) else None
        flag = "  " if t == m else "!!"
        f = lambda v: "--------" if v is None else f"{v:08x}"
        lines.append(f"  {flag} [{i:3}] game {f(t)}  ours {f(m)}")
    return lines


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("address", help="target virtual address, e.g. 0x151090")
    ap.add_argument("source", help="candidate .c file")
    ap.add_argument("function", nargs="?",
                    help="function name to compare (default: whole object)")
    ap.add_argument("--flags", default="-O4,p")
    ap.add_argument("--size", type=lambda s: int(s, 0))
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--mwcc", default=os.environ.get("DW4_MWCC", MWCC_DEFAULT))
    ap.add_argument("--wibo", default=os.environ.get("DW4_WIBO", WIBO_DEFAULT))
    ap.add_argument("--show", action="store_true")
    a = ap.parse_args(argv)

    va = int(a.address, 0)
    for p, what in ((a.elf, "retail ELF"), (a.mwcc, "compiler"), (a.wibo, "wibo")):
        if not os.path.exists(p):
            print(f"match_func: {what} not found: {p}", file=sys.stderr)
            return 2

    size = a.size
    if size is None:
        size = func_size(a.address, os.path.join(os.path.dirname(__file__),
                                                "..", "data", "functions.json"))
        if not size:
            print("match_func: unknown target size; pass --size", file=sys.stderr)
            return 2

    obj = "/tmp/match_func.o"
    env = dict(os.environ, MWCIncludes=os.path.dirname(os.path.abspath(a.source)))
    r = subprocess.run([a.wibo, a.mwcc, "-c", *a.flags.split(), a.source, "-o", obj],
                       capture_output=True, text=True, env=env)
    if not os.path.exists(obj):
        print("match_func: compile failed\n" + (r.stdout + r.stderr)[:2000], file=sys.stderr)
        return 2

    theirs = [struct.unpack_from("<I", elf_bytes(a.elf, va, size), 4 * i)[0]
              for i in range(size // 4)]
    mine = disasm_words(obj, a.function)[:size // 4]

    ok = mine == theirs
    print(f"{'MATCH ' if ok else 'DIFFER'} 0x{va:06x}  {size:4} bytes  "
          f"flags={a.flags!r}  func={a.function or '<object>'}")
    if not ok or a.show:
        print("\n".join(diff_report(theirs, mine)))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
