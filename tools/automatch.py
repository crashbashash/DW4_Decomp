#!/usr/bin/env python3
"""
automatch.py — bulk-decompile the idiomatic shapes, and let verification decide.

Hand-writing 3,000 functions is not the way; the same instruction shapes recur, so
generate candidate C from a template and make `verify.py` prove it. Nothing is
written to `src/` unless the compiled bytes are identical to retail, so the
auto-generated files are as trustworthy as hand-written ones — the tool only saves
the typing.

Templates (`--only NAME` to run one):

  empty        jr ra; nop                              -> void f(void) { }
  guard        the flag-guard family (72 B, 18 insns)    -> needs C++ (writes .cpp)
  wcall        addiu sp,-16 ; sd ra ; jal X ; nop ;\
               ld ra ; jr ra ; addiu sp,sp,16 (28 B)      -> void f(void) { X(); }   (.cpp)
  wload        the same, with one constant-address argument
               loaded into aX before the jal (32 B)       -> void f(void) { X(DAT); } (.cpp)
  wargs        any other frame-keeping single-call wrapper; the argument
               setup is decoded (constant, pass-through, field load,
               global address, address of a parameter)    -> void f(void) { X(...); } (.cpp)
  gget         lui at,HI; jr ra; lw v0,OFF(at)         -> int f(void) { return *(int*)ADDR; }

`guard`, `wcall`, `wload` and `wargs` write a `.cpp`, and both reasons are codegen,
not taste — MWCC picks the language from the file extension:

* `guard` needs a *named* C++ `bool`; only C++ has the type (finding #312).
* `wcall`/`wload`/`wargs` are the frame-keeping single-call wrappers, and **MWCC
  keeps the frame in C++ mode but turns the same source into a `j` tail call in C
  mode** (finding #314). The 1,085 wrappers only reproduce as C++. `wargs`
  generalises the argument setup; its decode relies on the R5900 convention of
  passing the first EIGHT integer arguments in a0-a3 then t0-t3 (finding #332).

`Makefile`, `tools/check.py` and `tools/linkgen.py` all treat `src/<name>.cpp` as a
source unit.
  fget         jr ra; lw/lb/lh/lwc1/ld v0,OFF(a0)      -> int f(int *p) { return *(int*)((char*)p+OFF); }
  setter       jr ra; sb/sh/sw/sd aX,OFF(aY)           -> void f(aY, aX) { *(...*)((char*)aY+OFF)=aX; }; width from the mnemonic
  fset         jr ra; swc1 $f12,OFF(a0)                -> void f(int *p, float a1) { *(float*)((char*)p+OFF)=a1; }
  rbase        jr ra; addiu v0,aN,IMM                  -> int f(int aN) { return aN + IMM; }
  fzero        sw zero,OFF(a0); jr ra; move v0,a0      -> int *f(int *p) { *(int*)((char*)p+OFF)=0; return p; }
  thunk        j TARGET   (no prologue)                -> int f(a...) { return TARGET(a...); } tried at arity 1..4
  tsetup       j TARGET; <delay-slot setup>            -> void f(...) { [store;] TARGET(...); }, setup decoded from the delay slot
               (move/li/lw/addiu/addu into an argument, or a store before the jump; findings #391)

Caveat worth stating loudly: **matching proves the code, not the types.** A 4-byte
return load is byte-identical whether the source said int, unsigned, float or a
pointer, and a one-argument identity is identical for any pointer type. Generated
files therefore get a header saying the shape matched and the C types are a guess.

Usage:
  automatch.py --dry-run                 # generate + verify, write nothing
  automatch.py                           # write verified matches to src/
  automatch.py --only gget --limit 50
  automatch.py --report                  # yield per template only
"""
import argparse
import collections
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cc
import verify as vfy  # noqa: E402

VADDR_BASE, FILE_BASE = 0x100000, 0x80
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")


def load_symbols(path):
    out = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2]))
    return out


def disassemble(img, lo, hi):
    """{va: (mnemonic, operands, word)} over the whole code range in one pass.

    `-z` (--disassemble-zeroes) is required: without it objdump elides every run of
    four or more zero words as `...`, those addresses never reach the table, and any
    function containing a nop block looks truncated (it is skipped as "missing").
    """
    binpath = os.path.join(cc.scratch_dir(), "automatch.bin")
    open(binpath, "wb").write(img[lo - VADDR_BASE + FILE_BASE:hi - VADDR_BASE + FILE_BASE])
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-z", "-b", "binary",
                          "-m", "mips:5900", "-EL", "--adjust-vma", hex(lo),
                          binpath], capture_output=True, text=True).stdout
    table = {}
    for ln in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$", ln)
        if m:
            table[int(m.group(1), 16)] = (m.group(3), m.group(4).strip(),
                                          int(m.group(2), 16))
    return table


def imm(tok):
    """Parse an immediate operand ('0x57', '-8392', '8936')."""
    tok = tok.strip().rstrip(",")
    try:
        return int(tok, 0)
    except ValueError:
        return None


# Operands arrive with the destination register attached: "v0,-29112(at)",
# "zero,0(a0)". The first regex version omitted that prefix and silently matched
# nothing, so every non-trivial template yielded zero candidates.
MEM = re.compile(r"^(?:\w+\s*,\s*)?(-?\w+)\((\w+)\)$")
BR = re.compile(r"^(?:0x)?([0-9a-f]+)")


def mem(operand):
    m = MEM.match(operand.strip().replace(" ", ""))
    if not m:
        return None, None
    return imm(m.group(1)), m.group(2)


def reg_imm(operand):
    """Parse `dst,src,IMM` (addiu/ori/...). Returns (dst, src, imm) or (None,)*3."""
    parts = [x.strip() for x in operand.split(",")]
    if len(parts) != 3:
        return None, None, None
    v = imm(parts[2])
    if v is None:
        return None, None, None
    return parts[0], parts[1], v


def hi_lo_addr(hi_op, lo_op):
    """Absolute address from a `lui at,HI` + `lw v0,OFF(at)` pair."""
    h = imm(hi_op.split(",")[-1]) if hi_op else None
    off, reg = mem(lo_op)
    if h is None or off is None:
        return None
    if off >= 0x8000:
        off -= 0x10000
    return (h << 16) + off


def eff_addr(hi, off, is_addiu):
    """Effective address of a `lui`/`addiu`-or-`ori` pair.

    objdump prints an `addiu` immediate already sign-extended (`-24064`) but an
    `ori` immediate as the raw 16-bit value (`0x52b0`, and 0xa200 for what is really
    -24064). Applying the sign correction to both — as this pipeline did until
    finding #323 — shifts every address whose `%lo` half has bit 15 set down by
    0x10000, silently misnaming half the globals.
    """
    if is_addiu:
        return (hi << 16) + off
    return (hi << 16) + (off & 0xFFFF)


ARGS = ["a0", "a1", "a2", "a3"]


def params(n):
    """C parameter list for the first n integer arguments."""
    return ", ".join("int a%d" % i for i in range(n))


def call_args(n):
    return ", ".join("a%d" % i for i in range(n))


# Parameters 5-8 live in the hardware t0-t3 (finding #332), which C spells a4-a7.
# `call_args`/`params` only reach a3, so the tail-call setup needs the full eight.
REG8 = ["a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"]
HWREG = {"a0": "a0", "a1": "a1", "a2": "a2", "a3": "a3",
         "t0": "a4", "t1": "a5", "t2": "a6", "t3": "a7"}


def ridx(r):
    """Argument index of a register, or None (t0-t3 map to a4-a7)."""
    return REG8.index(HWREG[r]) if r in HWREG else None


def tsetup_source(name, callee, last):
    """C for a tail call whose delay slot sets up an argument: `j T ; <setup>`.

    m2c drops this delay-slot instruction from the candidate, so the call loses the
    argument the target is actually given (the 8-byte near-misses of finding #391).
    The setup is a single instruction -- a register move, a constant, a field load,
    an address add, or a store that runs just before the call.  Registers the setup
    does not touch are passed through unchanged, so they are still forwarded.
    """
    op = last[0]
    ops = last[1]
    parts = [p.strip() for p in ops.split(",")]
    off, base = mem(ops)
    args, n, lines = None, 1, []
    if op in ("sb", "sh", "sw", "sd") and off is not None and base in HWREG \
            and len(parts) == 2:
        w = {"sb": "char", "sh": "short", "sw": "int", "sd": "long long"}[op]
        src, dst = parts[0], parts[1]
        if src == "zero":
            lines.append("*(%s *)((char *)%s + %d) = 0;" % (w, base, off))
            n = ridx(base) + 1
        elif ridx(src) is not None:
            lines.append("*(%s *)((char *)%s + %d) = %s;" % (w, base, off, src))
            n = max(ridx(base), ridx(src)) + 1
        else:
            return None
        args = [REG8[i] for i in range(n)]
    elif op in ("lw", "lb", "lbu", "lh", "lhu", "ld") and off is not None \
            and base in HWREG and len(parts) == 2 and ridx(parts[0]) is not None:
        w = {"lw": "int", "lb": "char", "lbu": "unsigned char",
             "lh": "short", "lhu": "unsigned short", "ld": "long long"}[op]
        dst = parts[0]
        n = max(ridx(base), ridx(dst)) + 1
        args = [REG8[i] for i in range(n)]
        args[ridx(dst)] = "*(%s *)((char *)%s + %d)" % (w, base, off)
    elif op == "move" and len(parts) == 2 and ridx(parts[0]) is not None:
        dst, src = parts
        n = max(ridx(dst), ridx(src) if ridx(src) is not None else 0) + 1
        args = [REG8[i] for i in range(n)]
        args[ridx(dst)] = "0" if src == "zero" else REG8[ridx(src)]
    elif op == "li" and len(parts) == 2 and ridx(parts[0]) is not None:
        k = imm(parts[1])
        if k is None:
            return None
        n = ridx(parts[0]) + 1
        args = [REG8[i] for i in range(n)]
        args[ridx(parts[0])] = str(k)
    elif op == "addiu" and len(parts) == 3:
        d, s, k = parts[0], parts[1], imm(parts[2])
        if ridx(d) is None or ridx(s) is None or k is None:
            return None
        n = max(ridx(d), ridx(s)) + 1
        args = [REG8[i] for i in range(n)]
        args[ridx(d)] = "(char *)%s %s %d" % (REG8[ridx(s)], "+" if k >= 0 else "-", abs(k))
    elif op == "addu" and len(parts) == 3 and all(ridx(p) is not None for p in parts):
        d, x, y = parts
        n = max(ridx(d), ridx(x), ridx(y)) + 1
        args = [REG8[i] for i in range(n)]
        args[ridx(d)] = "(char *)%s + %s" % (REG8[ridx(x)], REG8[ridx(y)])
    if args is None:
        return None
    body = "".join("    %s\n" % l for l in lines)
    return ("int %s();\n\nvoid %s(%s)\n{\n%s    %s(%s);\n}\n"
            % (callee, name, params(n), body, callee, ", ".join(args)))


NEXT_SYM = {}

# Templates whose output must be compiled as C++ (MWCC decides by extension).
CPP_TEMPLATES = {"guard", "wcall", "wload", "wargs"}

# ---- the generalised frame-keeping wrapper (finding #332) ------------------
# The R5900 C calling convention passes the first EIGHT integer arguments in
# a0-a3 followed by t0-t3, not the O32 four, so a wrapper that forwards more than
# four arguments sets t-registers (measured: MWCC emits `li t0,4` for the fifth
# argument of `X(a, b, 2, 3, 4)`). `wcall`/`wload` cover only the two exact shapes
# with no argument or one constant address; `wargs` decodes the setup — a
# constant, a pass-through of the enclosing parameter, a field load, a global
# address or the address of a parameter — and lets verification decide.
WARGS = ARGS + ["t0", "t1", "t2", "t3"]

# Instructions that write their first operand. Stores are excluded: `sw a0,0(sp)`
# mentions a0 but does not define it.
WARGS_WRITES = frozenset(["li", "lui", "addiu", "addi", "daddiu", "ori", "lw", "lbu",
                          "lhu", "lb", "lh", "lwc1", "swc1", "move", "addu", "daddu",
                          "or", "andi", "and", "sll", "srl", "sra", "xor", "nor",
                          "dsll32", "dsra32", "mfhi", "mflo"])
WARGS_BRANCH = frozenset(["beq", "bne", "beqz", "bnez", "bltz", "bgez", "bgtz", "blez",
                          "b", "j", "jr", "jal", "jalr", "bltzal", "bgezal", "bc1f",
                          "bc1t"])


def wrapper_shape(ins):
    """`(frame_size, jal_index)` for a frame-keeping single-call wrapper, else None.

    The body is a prologue (`addiu sp,sp,-N`, register saves), argument setup, one
    `jal`, its delay slot, and the mirror-image epilogue — nothing else, and no
    branch outside the call and the closing `jr ra`. A function with a second call
    or a loop is a real function, not a wrapper, and is left to m2c.
    """
    if len(ins) < 6:
        return None
    m = re.match(r"^sp,sp,(-?\d+)$", ins[0][1].replace(" ", ""))
    if ins[0][0] != "addiu" or not m or int(m.group(1)) >= 0:
        return None
    n = -int(m.group(1))
    if ins[-1][0] != "addiu" or ins[-1][1].replace(" ", "") != "sp,sp,%d" % n:
        return None
    if ins[-2][0] != "jr":
        return None
    jals = [i for i, (mn, _, _) in enumerate(ins) if mn == "jal"]
    if len(jals) != 1:
        return None
    jal = jals[0]
    # The epilogue starts right after the delay slot: scan the trailing restores.
    end = len(ins) - 2
    while end - 1 > jal and ins[end - 1][0] in ("ld", "lw", "lq") and "sp)" in ins[end - 1][1]:
        end -= 1
    if end != jal + 2:
        return None
    for i, (mn, _, _) in enumerate(ins):
        if mn in WARGS_BRANCH and i != jal and i != len(ins) - 2:
            return None
    return n, jal


def wrapper_args(ins, jal):
    """Decode the argument registers set before the call (and in its delay slot).

    `-> (defs, stores)` where `defs[r]` is one of
    `('const', k)`, `('pass', src)`, `('load', mn, off, base)`, `('addr', a)`,
    `('gl', mn, off, a)`, `('sp', off)` or `None` (undecodable), and `stores` maps a
    stack offset to the register stored there (the address-of-parameter idiom).
    """
    defs, stores = {}, []
    for i in range(jal + 2):
        mn, ops, _ = ins[i]
        parts = [x.strip() for x in ops.split(",")]
        if not parts:
            continue
        if mn in ("sw", "sd") and len(parts) == 2:
            off, base = mem(ops)
            if base == "sp":
                stores.append((parts[0], off))
            continue
        if parts[0] not in WARGS or mn not in WARGS_WRITES:
            continue
        d = parts[0]
        v = None
        if mn == "li" and len(parts) == 2:
            v = ("const", imm(parts[1]))
        elif mn in ("addiu", "ori", "daddiu", "addi") and len(parts) == 3:
            src, off = parts[1], imm(parts[2])
            if src == d and defs.get(d) and defs[d][0] == "hi":
                continue        # the low half of a `lui d,HI` pair: folded below, not an argument-plus-offset
            if src == "zero":
                v = ("const", off)
            elif off == 0 and src in WARGS:
                v = ("pass", src)
            elif src in WARGS:
                v = ("argexpr", src, off)
            elif src == "sp":
                v = ("sp", off)
        elif mn == "move" and len(parts) == 2:
            v = ("const", 0) if parts[1] == "zero" else (
                ("pass", parts[1]) if parts[1] in WARGS else
                (("sp", 0) if parts[1] == "sp" else None))
        elif mn in ("addu", "or", "daddu") and len(parts) == 3:
            if parts[1] == "zero":
                v = ("const", 0)
            elif parts[1] in WARGS and imm(parts[2]) == 0:
                v = ("pass", parts[1])
            elif parts[1] == "sp" and imm(parts[2]) == 0:
                v = ("sp", 0)
        elif mn == "lui" and len(parts) == 2:
            hi = imm(parts[1])
            v = ("hi", hi, i) if hi is not None else None
        elif mn in ("lw", "lbu", "lhu", "lb", "lh") and len(parts) == 2:
            off, base = mem(ops)
            if base in WARGS:
                v = ("load", mn, off, base)
            elif base == "at":
                # `lui at,HI` is a scratch pair: the nearest earlier `lui at` owns it.
                hi = None
                for k in range(i - 1, -1, -1):
                    p2 = [x.strip() for x in ins[k][1].split(",")]
                    if p2 and p2[0] == "at":
                        if ins[k][0] == "lui":
                            hi = imm(p2[1])
                        break
                if hi is not None:
                    # the offset is already sign-extended (see the `addiu` note above)
                    a = (hi << 16) + ((((off or 0) + 0x8000) & 0xffff) - 0x8000)
                    v = ("gl", mn, off, a)
        defs[d] = v
    # `lui r,HI` is only half an address: fold in the `addiu`/`ori r,r,LO` that
    # follows. A `lui` with no such follow-up is not decodable.
    for r, v in list(defs.items()):
        if v and v[0] == "hi":
            hi, start = v[1], v[2]
            fold = None
            for k in range(start + 1, jal + 2):
                mn, ops, _ = ins[k]
                parts = [x.strip() for x in ops.split(",")]
                if parts and parts[0] == r and mn in ("addiu", "ori") and len(parts) == 3 \
                        and parts[1] == r:
                    lo = imm(parts[2])
                    # objdump prints the addiu immediate already sign-extended: normalise, never subtract 0x10000 twice
                    a = (hi << 16) + (((lo + 0x8000) & 0xffff) - 0x8000) \
                        if mn == "addiu" else (hi << 16) + (lo & 0xffff)
                    fold = ("addr", a)
                    break
            defs[r] = fold
    return defs, stores


def wrapper_source(name, va, ins, buf=256):
    """C++ source for a generalised frame-keeping wrapper, or None.

    The enclosing function's own parameters are named `p0..` in argument-register
    order (a0-a3, t0-t3); a register the setup does not touch is passed through, a
    register set from a constant is passed as a literal, and the remaining kinds
    are decoded as a field load, a global address, a global load or the address of a
    parameter. Types are a guess (verified identical bytes only prove the shape).
    """
    shape = wrapper_shape(ins)
    if shape is None:
        return None
    _n, jal = shape
    defs, stores = wrapper_args(ins, jal)
    hi = -1
    for i, r in enumerate(WARGS):
        if defs.get(r) is not None:
            hi = i
    for r, v in defs.items():
        if v and v[0] in ("pass", "argexpr"):
            hi = max(hi, WARGS.index(v[1]))
        if v and v[0] == "load":
            hi = max(hi, WARGS.index(v[3]))
    if hi < 0:
        return None

    def isptr(v):
        return v is not None and v[0] in ("load", "addr", "gl", "sp")

    ptype = {}
    for i in range(hi + 1):
        r = WARGS[i]
        v = defs.get(r)
        ptype[r] = "char *" if (isptr(v) or (v and v[0] == "argexpr" and isptr(defs.get(v[1])))) else "int"

    smap = {off: val for val, off in stores}
    exprs = []
    for i in range(hi + 1):
        r = WARGS[i]
        v = defs.get(r)
        if v is None:
            exprs.append(("p%d" % i, "int"))
        elif v[0] == "const":
            exprs.append((str(v[1]), "int"))
        elif v[0] == "pass":
            exprs.append(("p%d" % WARGS.index(v[1]), ptype[v[1]]))
        elif v[0] == "argexpr":
            exprs.append(("*(int *)((char *)p%d + %d)" % (WARGS.index(v[1]), v[2]), "int"))
        elif v[0] == "load":
            exprs.append(("*(int *)((char *)p%d + %d)" % (WARGS.index(v[3]), v[2]), "int"))
        elif v[0] == "addr":
            exprs.append(("%s" % (NEXT_SYM.get(v[1]) or "DAT_%08x" % v[1]), "char *"))
        elif v[0] == "gl":
            exprs.append(("*(int *)0x%08x" % v[3], "int"))
        elif v[0] == "sp":
            src = smap.get(v[1])
            if src in WARGS and WARGS.index(src) <= hi:
                exprs.append(("&p%d" % WARGS.index(src), "void *"))
            else:
                exprs.append(("buf + %d" % v[1], "char *"))
        else:
            return None

    callee_va = ((ins[jal][2] & 0x3ffffff) << 2) | ((va + 4 * jal + 4) & 0xf0000000)
    callee = NEXT_SYM.get(callee_va, "FUN_%08x" % callee_va)
    decls = "".join("extern char DAT_%08x[];\n" % v[1] for v in defs.values()
                    if v and v[0] == "addr")
    local = ""
    if any(v and v[0] == "sp" and not (smap.get(v[1]) in WARGS) for v in defs.values()):
        local = "    char buf[%d];\n" % buf
    # The data declarations belong inside the extern "C" block: outside it MWCC gives them C++ linkage and the
    # relocation no longer names the retail symbol.
    return ('extern "C" {\n%svoid %s(%s);\nvoid %s(%s);\n}\n'
            'void %s(%s)\n{\n%s    %s(%s);\n}\n'
            % (decls, callee, ", ".join(t for _, t in exprs), name,
               ", ".join(ptype[WARGS[i]] for i in range(hi + 1)), name,
               ", ".join("%s p%d" % (ptype[WARGS[i]], i) for i in range(hi + 1)),
               local, callee, ", ".join(e for e, _ in exprs)))


def gen(name, cand, va=None):
    """-> [(template_name, c_source)] for one function's instructions."""
    ins = cand
    mn = [m for m, _, _ in ins]
    out = []

    # ---- the flag-guard family (finding #312) -----------------------------
    # 18 instructions, 72 bytes:
    #   addiu sp,-16 ; lui at,HI ; sd ra ; lw v0,OFF(at) ; beqz v0,CALL ; nop
    #   lw v0,36(v0) ; andi v0,v0,4 ; sltu v0,zero,v0 ; bnez v0,END ; nop
    #   CALL: jal X ; nop ; END: lui at,HI ; ld ra ; lw v0,OFF(at) ; jr ra ; addiu sp,sp,16
    # Semantics `if (!g || !(g->f36 & 4)) X(); return g;`. The `sltu` only appears
    # when the flag is a MATERIALISED bool, and the source that does it without
    # materialising the pointer test too is an assignment to a NAMED bool inside
    # the short-circuit condition. That needs C++, hence the .cpp extension.
    if va is not None and len(ins) == 18:
        w = [x[2] for x in ins]
        if (w[0] == 0x27bdfff0 and w[2] == 0xffbf0000 and w[4] == 0x10400006
                and w[5] == 0 and (w[6] & 0xffff0000) == 0x8c420000
                and (w[7] & 0xffff0000) == 0x30420000 and w[8] == 0x0002102b
                and w[9] == 0x14400003 and w[10] == 0
                and (w[11] >> 26) == 0x03 and w[12] == 0
                and (w[13] & 0xffff0000) == 0x3c010000 and w[14] == 0xdfbf0000
                and (w[15] & 0xffff0000) == 0x8c220000 and w[16] == 0x03e00008
                and w[17] == 0x27bd0010 and w[13] == w[1]
                and (w[15] & 0xffff) == (w[3] & 0xffff)):
            lo = w[15] & 0xffff
            glob = ((w[1] & 0xffff) << 16) + (lo - 0x10000 if lo & 0x8000 else lo)
            field, mask = w[6] & 0xffff, w[7] & 0xffff
            callee_va = ((w[11] & 0x3ffffff) << 2) | ((va + 44) & 0xf0000000)
            callee = NEXT_SYM.get(callee_va, "FUN_%08x" % callee_va)
            gname = "DAT_%08x" % glob
            # The global is declared as a 16-byte ARRAY so MWCC addresses it
            # absolutely (`lui at` + `lw`) like retail; as a plain pointer it is
            # small data and goes gp-relative. See finding #311.
            out.append(("guard",
                        "struct G { char pad[%d]; int f; };\n"
                        "extern struct G *%s[4];\n"
                        "extern \"C\" {\n"
                        "void %s(void);\n"
                        "struct G *%s(void);\n"
                        "}\n"
                        "struct G *%s(void)\n"
                        "{\n"
                        "    struct G *g = %s[0];\n"
                        "    bool t;\n"
                        "    if (!g || !(t = g->f & %d))\n"
                        "        %s();\n"
                        "    return %s[0];\n"
                        "}\n"
                        % (field, gname, callee, name, name, gname, mask, callee,
                           gname)))

    # ---- no relocation involved -------------------------------------------
    # empty: jr ra ; nop
    if len(ins) == 2 and mn[0] == "jr" and mn[1] == "nop":
        out.append(("empty", "void %s(void)\n{\n}\n" % name))

    # return a constant in the delay slot: jr ra ; li v0,K
    if len(ins) == 2 and mn[0] == "jr" and mn[1] == "li":
        dst, _, val = ins[1][1].partition(",")
        k = imm(val)
        if dst.strip() == "v0" and k is not None:
            out.append(("rconst", "int %s(void)\n{\n    return %d;\n}\n" % (name, k)))

    # identity / argument pass-through: jr ra ; move v0,aN
    if len(ins) == 2 and mn[0] == "jr" and mn[1] == "move":
        dst, _, src = ins[1][1].partition(",")
        if dst.strip() == "v0" and src.strip() in ARGS:
            n = ARGS.index(src.strip()) + 1
            out.append(("ident", "int %s(%s)\n{\n    return a%d;\n}\n"
                        % (name, params(n), n - 1)))

    # return a parameter plus a constant: jr ra ; addiu v0,aN,IMM
    if len(ins) == 2 and mn[0] == "jr" and mn[1] == "addiu":
        d, s, k = reg_imm(ins[1][1])
        if d == "v0" and ridx(s) is not None and k is not None:
            n = ridx(s) + 1
            out.append(("rbase", "int %s(%s)\n{\n    return a%d %s %d;\n}\n"
                        % (name, params(n), ridx(s), "+" if k >= 0 else "-", abs(k))))

    # field getters: jr ra ; <load> v0,OFF(a0)
    if len(ins) == 2 and mn[0] == "jr":
        off, reg = mem(ins[1][1])
        if off is not None and reg == "a0":
            ct = {"lw": "int", "lbu": "unsigned char", "lhu": "unsigned short",
                  "lh": "short", "lb": "char", "lwc1": "float",
                  "ld": "long long"}.get(mn[1])
            if ct:
                out.append(("fget", "%s %s(int *p)\n{\n    return *(%s *)((char *)p + %d);\n}\n"
                            % (ct, name, ct, off)))

    # store zero and return the pointer: sw zero,OFF(a0) ; jr ra ; move v0,a0
    if (len(ins) == 3 and mn[0] == "sw" and mn[1] == "jr" and mn[2] == "move"
            and ins[2][1].replace(" ", "") == "v0,a0"):
        off, reg = mem(ins[0][1])
        if off is not None and reg == "a0":
            out.append(("fzero", "int *%s(int *p)\n{\n    *(int *)((char *)p + %d) = 0;\n    return p;\n}\n"
                        % (name, off)))

    # plain setter: jr ra ; sw/sb/sh/sd aX,OFF(aY), or a zero store.  The width
    # comes from the mnemonic -- m2c widens a byte store to a word and emits
    # dsll32/dsra32/sw, which is the near-miss class of finding #391.
    if len(ins) == 2 and mn[0] == "jr" and mn[1] in ("sw", "sb", "sh", "sd"):
        off, base = mem(ins[1][1])
        val, _, _ = ins[1][1].partition(",")
        val = val.strip()
        w = {"sw": "int", "sb": "char", "sh": "short", "sd": "long long"}[mn[1]]
        if off is not None and ridx(base) is not None:
            if val == "zero":
                n = ridx(base) + 1
                body = "*(%s *)((char *)a%d + %d) = 0;" % (w, ridx(base), off)
                out.append(("setter", "void %s(%s)\n{\n    %s\n}\n" % (name, params(n), body)))
            elif ridx(val) is not None:
                n = max(ridx(base), ridx(val)) + 1
                body = "*(%s *)((char *)a%d + %d) = a%d;" % (w, ridx(base), off, ridx(val))
                out.append(("setter", "void %s(%s)\n{\n    %s\n}\n" % (name, params(n), body)))

    # float store: jr ra ; swc1 $f12,OFF(a0)  (the first float argument is f12).
    # `mem` cannot parse a `$f` register prefix, so the offset is read from the
    # memory operand alone.
    if len(ins) == 2 and mn[0] == "jr" and mn[1] == "swc1":
        parts = [p.strip() for p in ins[1][1].split(",")]
        if len(parts) == 2 and parts[0] == "$f12":
            off, base = mem(parts[1])
            if off is not None and base == "a0":
                out.append(("fset", "void %s(int *p, float a1)\n{\n    *(float *)((char *)p + %d) = a1;\n}\n"
                            % (name, off)))

    # ---- frame-keeping one-call wrappers (finding #314) -------------------
    # MWCC's C front end turns `void f(void){ X(); }` into a 2-instruction tail
    # call; its C++ front end keeps the frame. These two shapes are the retail
    # wrappers, so they must be compiled as C++ (.cpp).
    #  wcall: addiu sp,-16 ; sd ra,0(sp) ; jal X ; nop ; ld ra ; jr ra ; addiu sp,sp,16
    if (va is not None and len(ins) == 7 and (
            ins[0][2] == 0x27bdfff0 and ins[1][2] == 0xffbf0000
            and (ins[2][2] >> 26) == 0x03 and ins[3][2] == 0
            and ins[4][2] == 0xdfbf0000 and ins[5][2] == 0x03e00008
            and ins[6][2] == 0x27bd0010)):
        callee_va = ((ins[2][2] & 0x3ffffff) << 2) | ((va + 8) & 0xf0000000)
        callee = NEXT_SYM.get(callee_va, "FUN_%08x" % callee_va)
        out.append(("wcall",
                    "extern \"C\" {\n"
                    "void %s(void);\n"
                    "void %s(void);\n"
                    "}\n"
                    "void %s(void)\n"
                    "{\n"
                    "    %s();\n"
                    "}\n" % (callee, name, name, callee)))

    #  wload: addiu sp,-16 ; lui aX,HI ; sd ra ; jal X ; addiu aX,aX,LO ; ld ra ; jr ra ; addiu sp,sp,16
    if va is not None and len(ins) == 8:
        w = [x[2] for x in ins]
        if (w[0] == 0x27bdfff0 and (w[1] >> 26) == 0x0f and w[2] == 0xffbf0000
                and (w[3] >> 26) == 0x03 and (w[4] >> 26) == 0x09
                and w[5] == 0xdfbf0000 and w[6] == 0x03e00008 and w[7] == 0x27bd0010):
            r_lui, r_add = (w[1] >> 16) & 0x1f, (w[4] >> 16) & 0x1f
            if r_lui == r_add and ((w[4] >> 21) & 0x1f) == r_lui:
                lo = w[4] & 0xffff
                arg = ((w[1] & 0xffff) << 16) + (lo - 0x10000 if lo & 0x8000 else lo)
                callee_va = ((w[3] & 0x3ffffff) << 2) | ((va + 12) & 0xf0000000)
                callee = NEXT_SYM.get(callee_va, "FUN_%08x" % callee_va)
                out.append(("wload",
                            "extern char DAT_%08x[];\n"
                            "extern \"C\" {\n"
                            "void %s(char *);\n"
                            "void %s(void);\n"
                            "}\n"
                            "void %s(void)\n"
                            "{\n"
                            "    %s(DAT_%08x);\n"
                            "}\n" % (arg, callee, name, name, callee, arg)))

    #  wargs: every other argument setup, decoded from the retail shape (finding #332)
    if va is not None and wrapper_shape(ins) is not None:
        wsrc = wrapper_source(name, va, ins)
        if wsrc:
            if "char buf[256];" in wsrc:
                # the stack buffer's size is not recorded in the code: the frame size is, so try the plausible sizes
                for size in (16, 8, 4, 12, 24, 32, 48, 64, 128):
                    out.append(("wargs", wrapper_source(name, va, ins, size)))
            else:
                out.append(("wargs", wsrc))

    # ---- relocations: globals, calls --------------------------------------
    # global getter: lui at,HI ; jr ra ; <load> v0,OFF(at)
    if len(ins) == 3 and mn[0] == "lui" and mn[1] == "jr":
        addr = hi_lo_addr(ins[0][1], ins[2][1])
        ct = {"lw": "int", "lbu": "unsigned char", "lhu": "unsigned short",
              "lh": "short", "lb": "char", "lwc1": "float"}.get(mn[2])
        if addr is not None and ct:
            out.append(("gget", "%s %s(void)\n{\n    return *(%s *)0x%08x;\n}\n"
                        % (ct, name, ct, addr)))
            # The same read through a named symbol: MWCC keeps the base in the destination-side scratch (`lui v1`) instead
            # of `$at`, which is how the literal and symbol spellings differ (finding #307).
            out.append(("gget", "extern %s DAT_%08x;\n%s %s(void)\n{\n    return DAT_%08x;\n}\n"
                        % (ct, addr, ct, name, addr)))

    # tail call with a constant pointer argument:
    #   lui a0,HI ; j TARGET ; addiu a0,a0,OFF
    # lui a0,HI ; j TARGET ; addiu a0,a0,OFF      (or the same with ori)
    if len(ins) == 3 and mn[0] == "lui" and mn[1] == "j" and mn[2] in ("addiu", "ori"):
        t = BR.match(ins[1][1])
        dst, _, rest = ins[0][1].partition(",")
        h = imm(rest)
        d2, src2, off = reg_imm(ins[2][1])
        if (t and h is not None and off is not None
                and d2 == dst.strip() and src2 == dst.strip()):
            a = (h << 16) + (off - 0x10000 if (mn[2] == "addiu" and off >= 0x8000) else off)
            target = int(t.group(1), 16)
            tn = NEXT_SYM.get(target, "FUN_%08x" % target)
            # The pointer must be a SYMBOL reference, not a literal cast. MWCC
            # materialises a literal into a scratch register (`lui v0` + `ori a0,v0`)
            # but a symbol address straight into the destination (`lui a0` +
            # `addiu a0,a0`), which is what retail has. So name the object at that
            # address: its own function name when one is known, else DAT_<addr>.
            argname = NEXT_SYM.get(a) or ("DAT_%08x" % a)
            decl = ("extern char %s[];\n" % argname) if argname.startswith("DAT_") else ""
            out.append(("ccall", "%svoid %s(void)\n{\n    %s(%s);\n}\n"
                        % (decl, name, tn, argname)))

    # tail call with a loaded argument: j TARGET ; lw a0,OFF(a0)
    if len(ins) == 2 and mn[0] == "j":
        t = BR.match(ins[0][1])      # the target is the j's operand, not the delay slot's
        off, reg = mem(ins[1][1])
        if t and off is not None and reg == "a0":
            target = int(t.group(1), 16)
            tn = NEXT_SYM.get(target, "FUN_%08x" % target)
            out.append(("jload", "int %s(int *p)\n{\n    return %s(*(int *)((char *)p + %d));\n}\n"
                        % (name, tn, off)))

    # tail call with a delay-slot argument setup: j TARGET ; <setup>  (finding #391).
    # m2c drops this setup, so the candidate loses the argument the target is given.
    if len(ins) == 2 and mn[0] == "j":
        t = BR.match(ins[0][1])
        if t:
            target = int(t.group(1), 16)
            tn = NEXT_SYM.get(target, "FUN_%08x" % target)
            src = tsetup_source(name, tn, ins[1])
            if src:
                out.append(("tsetup", src))

    # bare thunk: j TARGET (optionally with a nop)
    if (len(ins) == 1 and mn[0] == "j") or (len(ins) == 2 and mn[0] == "j" and mn[1] == "nop"):
        t = BR.match(ins[0][1])
        if t:
            target = int(t.group(1), 16)
            tn = NEXT_SYM.get(target, "FUN_%08x" % target)
            for n in range(0, 5):
                out.append(("jthunk", "int %s(%s)\n{\n    return %s(%s);\n}\n"
                            % (name, params(n), tn, call_args(n))))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--out", default="src/unmatched")
    ap.add_argument("--only", action="append", default=[])
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--report", action="store_true", help="counts only, no writes")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--force", action="store_true",
                    help="overwrite src/ files that already exist (default: keep them)")
    a = ap.parse_args(argv)

    img = open(a.elf, "rb").read()
    syms = load_symbols(a.symbols)
    byname = {n: (va, sz) for va, sz, n in syms}
    lo = min(va for va, _, _ in syms)
    hi = max(va + sz for va, sz, _ in syms)
    ins = disassemble(img, lo, hi)

    NEXT_SYM.update({v: n for v, _, n in syms})
    want = set(a.only)
    stats = collections.Counter()
    written = 0
    tried = 0
    # A function already defined anywhere in src/ (one-function units, folded translation units, hand-written files) is
    # not a candidate: units.scan is the same definition `make check` uses. Checking only the output directory
    # re-banked ~2,300 functions that were already matched elsewhere and broke the build with duplicate definitions.
    import units
    defined = set(units.scan(os.path.dirname(a.out.rstrip("/")) or "src"))
    for va, sz, name in syms:
        if a.limit and tried >= a.limit:
            break
        if name in defined:
            continue
        cand = [ins.get(va + 4 * i) for i in range(sz // 4)]
        if any(c is None for c in cand):
            continue
        for tmpl, src in gen(name, cand, va):
            if want and tmpl not in want:
                continue
            tried += 1
            stats[tmpl + ":tried"] += 1
            # MWCC picks the language from the file extension: `guard` needs C++.
            ext = ".cpp" if tmpl in CPP_TEMPLATES else ".c"
            tmp = os.path.join(cc.scratch_dir(), "automatch_cand" + ext)
            with open(tmp, "w") as fh:
                fh.write(src)
            ok, _report = vfy.verify_one(va, tmp, elf=a.elf, symbols=a.symbols)
            if ok:
                stats[tmpl + ":match"] += 1
                dest = os.path.join(a.out, name + ext)
                if (os.path.exists(os.path.join(a.out, name + ".c"))
                        or os.path.exists(os.path.join(a.out, name + ".cpp"))) and not a.force:
                    # A function never has both a .c and a .cpp: a unit already in
                    # the other language mode is kept, not shadowed by this one.
                    stats[tmpl + ":kept"] += 1
                    break
                if not a.report and not a.dry_run:
                    os.makedirs(os.path.dirname(dest) or ".", exist_ok=True)
                    with open(dest, "w") as fh:
                        fh.write(src)
                    written += 1
                elif a.verbose:
                    print("  match %-7s 0x%06x %s" % (tmpl, va, name))
                break
            else:
                stats[tmpl + ":fail"] += 1
    print("automatch: %d candidate compiles" % tried)
    for tmpl in sorted({k.split(":")[0] for k in stats}):
        t, m = stats[tmpl + ":tried"], stats[tmpl + ":match"]
        print("   %-7s %4d tried, %4d match  (%.0f%%)"
              % (tmpl, t, m, 100.0 * m / t if t else 0))
    print("automatch: %d written to %s/" % (written, a.out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
