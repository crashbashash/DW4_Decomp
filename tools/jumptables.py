#!/usr/bin/env python3
"""
jumptables.py — find the switches' jump tables and record them in a config file.

Ghidra stops a `switch` at the indirect `jr $vN`, so a dispatcher's case bodies
were attributed to nobody until `tools/split.py` grew those symbols.
The *table* is not in the function at all: MWCC puts it in `.rodata`, and the
dispatcher reaches it through a `lui`/`addiu` pair, so from the source alone there
is no way to know it exists. This tool recovers it from the retail image.

Detection works backwards from the indirect jump:

    lui   $v1, 0x4f          ; %hi of the table
    ...
    addiu $v1, $v1, -24064   ; %lo of the table  (negative lo is common)
    sll   $v0, $v0, 2        ; index * 4
    addu  $v0, $v0, $v1      ; table base (a two-register chain in either order)
    lw    $v0, 0($v0)
    jr    $v0

  * the load that defines the jump register gives the pointer register;
  * following that register's definitions back through the `addu` chain finds the
    unique `lui`/`addiu` pair, i.e. the table's address;
  * the entry count comes from the `sltiu $at, <index>, N` bound guard, whose
    register must be the one the `sll` scales;
  * every entry must land inside the function, which is what rejects the
    look-alike idiom (a `lui`/`addiu`ed *data* table that is loaded, not jumped
    through) and any mis-detected base.

The result is `config/SLUS-20836/jumptables.txt`, `fn_va jtbl_va count` in hex, one line per
table. `tools/verify.py` uses it to compare the compiler's `.rodata` against the
retail table bytes, `tools/layout.py` to make the table its own layout unit and
`tools/linkgen.py` to place the compiled table at the retail address. Without that
plumbing a switch function could "verify" while its table was never looked at, and
the relink would orphan the table (see docs/engine/m2c-bulk.md).

Usage:
  jumptables.py --write                 # regenerate config/SLUS-20836/jumptables.txt
  jumptables.py --report                # census, write nothing
  jumptables.py --show 0x204840         # one function's tables
"""
import argparse
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import automatch as am  # noqa: E402

VADDR_BASE, FILE_BASE = 0x100000, 0x80
ROOT = os.path.dirname(HERE)
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
SYMBOLS_DEFAULT = os.path.join(os.path.dirname(HERE), "config", "SLUS-20836", "symbols.txt")
CONFIG_DEFAULT = os.path.join(os.path.dirname(HERE), "config", "SLUS-20836", "jumptables.txt")
POOLS_DEFAULT = os.path.join(os.path.dirname(HERE), "config", "SLUS-20836", "rodata-pools.tsv")

LOADS = ("lw", "lhu", "lbu", "lh", "lb")
MEMOP = re.compile(r"^(-?\w+)\((\w+)\)$")


def va_bytes(img, va, n):
    o = va - VADDR_BASE + FILE_BASE
    return img[o:o + n]


def splits(ops):
    return [x.strip() for x in ops.split(",")] if ops else []


def eff_addr(hi, off, is_addiu):
    """Effective address of a `lui`/`addiu`-or-`ori` pair (see automatch.eff_addr).

    Kept as a one-line wrapper so the sign convention lives in exactly one place:
    objdump prints an `addiu` immediate already sign-extended and an `ori` immediate
    raw, and getting that wrong shifts half the globals by 0x10000.
    """
    return am.eff_addr(hi, off, is_addiu)


def _def_before(ins, idx, reg):
    """Index of the instruction that last wrote `reg` before ins[idx], or None."""
    for j in range(idx - 1, max(-1, idx - 20), -1):
        mn, p = ins[j][1], splits(ins[j][2])
        if not p or p[0] != reg:
            continue
        if mn in ("sw", "sb", "sh", "sd", "sq", "swc1", "sdc1", "jr", "jalr",
                  "b", "beqz", "bnez", "beq", "bne", "beql", "bnel", "blez",
                  "bgtz", "bltz", "bgez", "beqzl", "bnezl", "branch_likely"):
            continue
        return j
    return None


def table_base(ins, jl, rb):
    """Table address feeding the pointer register `rb`. -> [addr] (0 or 1 hit)."""
    stack, himap = [(rb, jl)], {}
    for _ in range(12):
        if not stack:
            break
        r, at = stack.pop(0)
        j = _def_before(ins, at, r)
        if j is None:
            continue
        mn, p = ins[j][1], splits(ins[j][2])
        if mn == "lui" and len(p) == 2 and p[0] == r:
            hi = am.imm(p[1])
            if hi is not None:
                himap.setdefault(r, (hi, j))
        elif mn in ("addu", "or", "move", "daddu", "add", "addi") and len(p) >= 3:
            stack += [(p[1], j), (p[2], j)]
        elif mn == "sll" and len(p) == 3:
            stack.append((p[1], j))
        elif mn in ("addiu", "ori") and len(p) == 3 and p[0] == r and p[1] == r:
            stack.append((r, j))
    out = []
    for r, (hi, j) in himap.items():  # hi is the raw 16-bit half
        done = False
        for k in range(j + 1, min(j + 10, len(ins))):
            mn, p = ins[k][1], splits(ins[k][2])
            if mn in ("addiu", "ori") and len(p) == 3 and p[0] == r and p[1] == r:
                off = am.imm(p[2])
                if off is not None:
                    out.append(eff_addr(hi, off, mn == "addiu"))
                    done = True
                break
        if done:
            continue
        # The other half can also sit in the *load's displacement*:
        #   lui v1,0x4d ; ... ; lw v1,0x41d0(v1)   -> the table is at 0x4d41d0
        # (vfiprintf, 89 cases).
        for k in range(j + 1, jl + 1):
            mn, p = ins[k][1], splits(ins[k][2])
            if mn not in ("lw", "lhu", "lbu", "lh", "lb", "sw", "sb", "sh"):
                continue
            if len(p) < 2:
                continue
            m = MEMOP.match(p[1].replace(" ", ""))
            if m and m.group(2) == r:
                off = am.imm(m.group(1))
                if off is not None:
                    out.append(eff_addr(hi, off, True))
                break
    return out


def find_tables(va, size, table, img):
    """Jump tables of the function at `va`. -> [{va, count, entries}]."""
    ins = [(va + 4 * i,) + table[va + 4 * i] for i in range(size // 4)
           if va + 4 * i in table]
    res = []
    for idx, (a, mn, ops, w) in enumerate(ins):
        if mn != "jr":
            continue
        rs = ops.strip()
        if rs == "ra":
            continue
        jl, rb = None, None
        for j in range(idx - 1, max(-1, idx - 10), -1):
            p = splits(ins[j][2])
            if ins[j][1] in LOADS and p and p[0] == rs:
                m = MEMOP.match(p[1].replace(" ", ""))
                if m:
                    jl, rb = j, m.group(2)
                break
        if jl is None:
            continue
        bases = table_base(ins, jl, rb)
        if len(bases) != 1:
            continue
        tbl = bases[0]
        idxreg = None
        for j in range(jl - 1, max(-1, jl - 8), -1):
            p = splits(ins[j][2])
            if ins[j][1] == "sll" and len(p) == 3:
                idxreg = p[1]
                break
        cnt = None
        # The bound guard is `sltiu Rd, <index>, N` — usually `$at`, but MWCC
        # puts it in any free register when the value is reused (FUN_00109410 uses
        # `sltiu $v0,$s2,5`), so the destination cannot be pinned. Prefer the guard
        # whose source is the register the `sll` scales; fall back to the nearest
        # immediate bound above the jump.
        fallback = None
        for j in range(idx - 1, max(-1, idx - 60), -1):
            p = splits(ins[j][2])
            if ins[j][1] == "sltiu" and len(p) == 3 and am.imm(p[2]):
                if idxreg is not None and p[1] == idxreg:
                    cnt = am.imm(p[2])
                    break
                if fallback is None:
                    fallback = am.imm(p[2])
        if cnt is None:
            cnt = fallback
        if not cnt or cnt <= 0 or cnt > 0x4000:
            continue
        raw = va_bytes(img, tbl, 4 * cnt)
        if len(raw) != 4 * cnt:
            continue
        entries = [struct.unpack_from("<I", raw, 4 * i)[0] for i in range(cnt)]
        if not all(va <= e < va + size for e in entries):
            continue
        res.append(dict(va=tbl, count=cnt, entries=entries))
    return res


def scan(elf=ELF_DEFAULT, symbols=SYMBOLS_DEFAULT, table=None):
    """Every (function, jump table) pair in the image. -> [(va, size, name, tables)]."""
    img = open(elf, "rb").read()
    syms = am.load_symbols(symbols)
    if table is None:
        lo = min(v for v, s, n in syms)
        hi = max(v + s for v, s, n in syms)
        table = am.disassemble(img, lo, hi)
    out = []
    for va, size, name in syms:
        ts = find_tables(va, size, table, img)
        if ts:
            out.append((va, size, name, ts))
    return out


def entries(img, jtbl_va, count):
    """The `count` entry words at `jtbl_va`, read from the retail image."""
    raw = va_bytes(img, jtbl_va, 4 * count)
    return [struct.unpack_from("<I", raw, 4 * i)[0] for i in range(count)]


def load(path=CONFIG_DEFAULT):
    """config/SLUS-20836/jumptables.txt -> {fn_va: [(jtbl_va, count)]}."""
    out = {}
    if not os.path.exists(path):
        return out
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.setdefault(int(p[0], 16), []).append((int(p[1], 16), int(p[2], 16)))
    return out


def write(path=CONFIG_DEFAULT, elf=ELF_DEFAULT, symbols=SYMBOLS_DEFAULT):
    found = scan(elf, symbols)
    pools = load(POOLS_DEFAULT) if os.path.exists(POOLS_DEFAULT) else {}

    def pooled(va, t):
        # a reviewed pool that spans a scanned table replaces it
        lo, hi = t["va"], t["va"] + 4 * t["count"]
        return any(p <= lo and hi <= p + 4 * n for p, n in pools.get(va, ()))

    with open(path, "w") as fh:
        fh.write("# fn_va jtbl_va count — GENERATED by tools/jumptables.py; do not edit.\n"
                 "# The switch dispatchers' jump tables, recovered from the retail image:\n"
                 "# MWCC puts a table in .rodata and reaches it with a lui/addiu pair, so it\n"
                 "# is invisible to the source. tools/verify.py compares the compiled table\n"
                 "# against these retail bytes and tools/{layout,linkgen}.py place it there.\n")
        for va, size, name, ts in found:
            for t in ts:
                if not pooled(va, t):
                    fh.write("%08x %08x %04x\n" % (va, t["va"], t["count"]))
        # reviewed .rodata pools of Sony-built functions (not visible to the scan)
        if os.path.exists(POOLS_DEFAULT):
            for ln in open(POOLS_DEFAULT):
                if ln.strip() and not ln.startswith("#"):
                    fh.write(ln.strip() + "\n")
    return found


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--symbols", default=SYMBOLS_DEFAULT)
    ap.add_argument("--out", default=CONFIG_DEFAULT)
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--show", default=None, help="print one function's tables")
    a = ap.parse_args(argv)
    if a.show:
        va = int(a.show, 0)
        img = open(a.elf, "rb").read()
        syms = am.load_symbols(a.symbols)
        size, name = next((s, n) for v, s, n in syms if v == va)
        lo = min(v for v, s, n in syms)
        hi = max(v + s for v, s, n in syms)
        table = am.disassemble(img, lo, hi)
        for t in find_tables(va, size, table, img):
            print("0x%08x %s tbl 0x%08x count %d" % (va, name, t["va"], t["count"]))
            print("   " + " ".join("0x%08x" % e for e in t["entries"]))
        return 0
    found = scan(a.elf, a.symbols)
    ntab = sum(len(t) for _, _, _, t in found)
    nent = sum(t["count"] for _, _, _, ts in found for t in ts)
    print("jumptables: %d functions, %d tables, %d entries" % (len(found), ntab, nent))
    if a.report:
        for va, size, name, ts in found[:20]:
            print("  0x%08x %-28s %s" % (va, name,
                  " ".join("0x%x(%d)" % (t["va"], t["count"]) for t in ts)))
        return 0
    if a.write:
        write(a.out, a.elf, a.symbols)
        print("wrote %s" % a.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
