#!/usr/bin/env python3
"""
asm_body_gen.py — emit a function as an MWCC `asm` body from the retail bytes.

Decision (see docs/engine/asm-body-matches.md): a function that cannot be written as C/C++ under
any recorded compiler/flag/shape (vendor SDK code built by another compiler, hand-written MMI/VU0)
counts as matched once an `asm` body assembled by the pinned compiler is byte-identical to retail
under tools/verify.py. The body uses canonical (no-alias) mnemonics, labels for branch targets
inside the function and symbols for `jal`/`j` targets.

Usage:
  asm_body_gen.py NAME [-o FILE]       # print or write the asm-body source for one function
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import verify

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
VADDR_BASE, FILE_BASE = 0x100000, 0x80

BRANCH = re.compile(r"^(b|beq|bne|beql|bnel|blez|bgtz|bltz|bgez|blezl|bgtzl|bltzl|bgezl|"
                    r"bltzal|bgezal|bltzall|bgezall|bc0f|bc0t|bc0fl|bc0tl|bc1f|bc1t|bc1fl|bc1tl|"
                    r"bc2f|bc2t|bc2fl|bc2tl)$")
JUMP = re.compile(r"^(j|jal)$")
# Mnemonics the pinned assembler rejects; kept as raw words with the instruction in a comment.
RAW = {"dli", "dla", "div", "divu", "div1", "divu1", "madd", "maddu", "madd1", "maddu1", "msub", "msubu", "c1", "cvt.w.s",
       "break", "teq", "tne", "tge", "tgeu", "tlt", "tltu", "teqi", "tnei", "tgei", "tgeiu", "tlti", "tltiu"}


def load_symbols():
    by_va = {}
    for line in open(SYMBOLS):
        f = line.split()
        if len(f) >= 3 and not line.startswith("#"):
            by_va[int(f[0], 16)] = f[2]
    return by_va


def func_range(name):
    for line in open(SYMBOLS):
        f = line.split()
        if len(f) >= 3 and not line.startswith("#") and f[2] == name:
            return int(f[0], 16), int(f[1], 16)
    raise SystemExit("unknown function %s" % name)


def disassemble(va, size):
    with open(ELF, "rb") as fh:
        fh.seek(va - VADDR_BASE + FILE_BASE)
        data = fh.read(size)
    with tempfile.NamedTemporaryFile(suffix=".bin") as tmp:
        tmp.write(data)
        tmp.flush()
        out = subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-b", "binary", "-m", "mips:5900", "-EL",
                              "-z", "-M", "no-aliases", "--adjust-vma=0x%x" % va, tmp.name],
                             capture_output=True).stdout.decode()
    ins = []
    for line in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$", line)
        if m:
            ins.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3).strip()))
    return data, ins


def generate(name):
    va, size = func_range(name)
    by_va = load_symbols()
    data, ins = disassemble(va, size)
    if len(ins) * 4 != size:
        raise SystemExit("%s: disassembled %d words for %d bytes" % (name, len(ins), size))
    labels = {}
    externs = []
    body = []
    prev_raw_jump = False
    for addr, word, text in ins:
        parts = text.split(None, 1)
        mn = parts[0]
        ops = parts[1] if len(parts) > 1 else ""
        if mn == "(bad)" or text.startswith(".word") or text.startswith("0x"):
            raise SystemExit("%s: undecodable word 0x%08x at 0x%x" % (name, word, addr))
        if BRANCH.match(mn):
            tgt = int(ops.split(",")[-1].strip(), 16)
            if va <= tgt < va + size:
                labels.setdefault(tgt, "L_%06x" % tgt)
                ops = ",".join(ops.split(",")[:-1] + [labels[tgt]])
            else:
                mn, ops = ".word", "0x%08x /* %s */" % (word, text)
        elif JUMP.match(mn):
            tgt = int(ops.strip(), 16)
            if va <= tgt < va + size:
                # a section-relative relocation would resolve to the function start; keep the literal
                labels.setdefault(tgt, "L_%06x" % tgt)
                mn, ops = ".word", "0x%08x /* %s */" % (word, text)
            elif tgt in by_va:
                ops = by_va[tgt]
                if ops not in externs:
                    externs.append(ops)
            else:
                mn, ops = ".word", "0x%08x /* %s */" % (word, text)
        if mn == "jalr" and "," not in ops:
            ops = "ra," + ops
        elif mn == "syscall" and not ops:
            ops = "0"
        if prev_raw_jump:
            mn, ops = ".word", "0x%08x /* %s */" % (word, text)
        prev_raw_jump = False
        if mn in RAW or mn.startswith(("cvt.", "trunc.", "round.", "floor.", "ceil.")) or "c0_" in ops:
            mn, ops = ".word", "0x%08x /* %s */" % (word, text)
        if mn == ".word" and (BRANCH.match(text.split()[0]) or JUMP.match(text.split()[0])):
            prev_raw_jump = True
        body.append((addr, mn, ops))
    lines = ["#pragma optimization_level 0"]
    lines += ["extern void %s(void);" % e for e in externs]
    lines += ["/* 0x%08x - %s (%d bytes): retained as an asm body, see docs/engine/asm-body-matches.md */" % (va, name, size),
             "asm void %s(void) {" % name]
    for addr, mn, ops in body:
        if addr in labels:
            lines.append("%s:" % labels[addr])
        lines.append("    %s%s" % (mn, " " + ops if ops else ""))
    lines.append("}")
    lines += jump_tables(name, va, size)
    return "\n".join(lines) + "\n"


def jump_tables(name, va, size):
    """One `const` pointer array per recorded jump table of the function (config/SLUS-20836/jumptables.txt).

    The pinned compiler emits a `.rodata` section for it whose entries are relocations against the function symbol, which is
    exactly the shape of a `switch` table, so `tools/verify.py` and `tools/linkgen.py` treat it as the compiler-generated table.
    A pointer sum is the only constant expression it accepts (`(unsigned)fn + k` is not).
    """
    image = verify.read_elf(ELF)
    out = []
    for n, (tva, count) in enumerate(sorted(verify.load_jumptables(verify.jumptables_path(SYMBOLS)).get(va, []))):
        words = struct.unpack("<%dI" % count, verify.va_bytes(image, tva, 4 * count))
        for w in words:
            if not va <= w < va + size:
                raise SystemExit("%s: jump table 0x%x entry 0x%x leaves the function" % (name, tva, w))
        out.append("/* jump table 0x%08x: %d entries (config/SLUS-20836/jumptables.txt) */" % (tva, count))
        out.append("const char *const %s_jtbl%d[] = {%s};" % (
            name, n, ", ".join("(const char *)%s + 0x%x" % (name, w - va) for w in words)))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("-o", "--out")
    a = ap.parse_args()
    text = generate(a.name)
    if a.out:
        open(a.out, "w").write(text)
    else:
        sys.stdout.write(text)


if __name__ == "__main__":
    main()
