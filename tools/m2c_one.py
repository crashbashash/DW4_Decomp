#!/usr/bin/env python3
"""m2c_one.py — feed one retail function through m2c (mipsee-mwcc-c).

m2c (github.com/matt-kempster/m2c, vendored under `local/m2c/` in this tree) wants the
spimdisasm assembly format:

    glabel NAME
    /* <off> <vaddr> <word> */  addiu $sp, $sp, -16

`config/SLUS-20836/symbols.txt` gives the function's VA and size, so the input can be
generated straight from the retail bytes. Two things have to be fixed up or m2c
refuses the file / guesses wrong:

  * **registers need `$`** — objdump prints `lui at,0x0`, m2c expects `$at`;
  * **branch/jump targets must be labels** — objdump prints `beqz v0,0x13008c`,
    which m2c cannot parse. Targets are recomputed from the encoded offset and
    rewritten to `.L<addr>` local labels (inserted in the listing) or, for `jal`/
    `j` outside the function, to a symbol name.

This is the *first* half of the pipeline. m2c's output references globals as
literal casts (`*(int *)0x55EBC0`), which MWCC compiles to a scratch register +
`ori` instead of retail's symbol-relative `lui`/`addiu` (finding #307), so a
post-pass (see `tools/m2c_batch.py`) is what turns it into a verifiable candidate.

Usage:
  m2c_one.py 0x130060                 # print the C m2c infers
  m2c_one.py 0x130060 --keep-asm      # also print the generated assembly
  m2c_one.py 0x130060 --asm-out a.s   # write the assembly somewhere
"""
import argparse
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import automatch as am  # noqa: E402

REGS = ("zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3",
        "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9", "k0", "k1", "gp", "sp", "fp", "s8", "ra")
REG_RE = re.compile(r"\b(" + "|".join(REGS) + r")\b")
BRANCH = re.compile(r"^(b|bal|beq|bne|blez|bgtz|bltz|bgez|bltzal|bgezal)")
# instructions whose last operand is a memory reference, i.e. the ones a `lui`/`%hi`
# pair (or a `gp` displacement) can complete.
LOADS = ("lw", "lb", "lbu", "lh", "lhu", "sw", "sb", "sh", "lwc1",
         "swc1", "ld", "sd", "lq", "sq", "lwl", "lwr", "swl", "swr")

# opcodes that do not write a GPR (stores, branches/jumps, hi/lo and cop moves).
# Everything else writes its first operand, which is what invalidates a tracked
# `lui` high half. `move` is `addu rd,rs,zero` and is caught as an ordinary write.
_NO_DST = re.compile(
    r"^(s[bwdhql]|sq|sw[lr]|s[dw]c[01]|b|j|jr|jalr|mult|multu|div|divu|nop|syscall|"
    r"break|sync|cache|pref|eret|tlb|mtc|ctc|mthi|mtlo|lwc[23]|swc[23]|gt|ge|lt|le|eq)\b")


def _written_reg(mn, ops):
    """The GPR an instruction writes (its first operand), or None."""
    if _NO_DST.match(mn) or not ops:
        return None
    first = ops.split(",", 1)[0].strip()
    return first if first.startswith("$") else None


def _reg_use_offset(mn, ops, reg):
    """The numeric displacement/addend for `reg`, or (None, None).

    Returns `(off, "base")` for a load/store `off($reg)` and `(off, "addiu")` for a
    `$reg,$reg,off` address completion. A *symbolic* displacement (`%lo(...)`,
    `%gp_rel(...)`) already carries its address, so it is reported as `(None, form)`
    only when it does not name `reg` at all.
    """
    if mn in LOADS and ops.endswith("(%s)" % reg):
        disp = ops.rsplit(",", 1)[-1][:-len("(%s)" % reg)].strip()
        try:
            return int(disp, 0), "base"
        except ValueError:
            return None, None
    if mn in ("addiu", "ori") and "," in ops:
        p = [x.strip() for x in ops.split(",")]
        if len(p) == 3 and p[0] == reg and p[1] == reg:
            try:
                return int(p[2], 0), "addiu"
            except ValueError:
                return None, None
    return None, None

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
M2C_DEFAULT = os.environ.get("DW4_M2C", os.path.join(ROOT, "local", "m2c", "m2c.py"))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
SYMBOLS_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")


def load_gp(elf):
    """gp from the ELF's `.reginfo` — the symbolizer needs it to name `off(gp)`.

    Single source of truth: `verify.reginfo_gp` owns the parse (and the sanity check
    `gp - 32112 == 0x00554b00`), so importing it lazily keeps one implementation.
    verify.py does not import this module, so there is no cycle.
    """
    import verify as vfy
    return vfy.reginfo_gp(elf)


def load_bounds(elf):
    """(lo, hi) of the loadable image, from the ELF program headers.

    The relinked section is only 0x100000..0x554b00, but the globals the C
    references run to the first PT_LOAD's memsz (0x58d280): `.sbss` starts at
    0x554b00. Hard-coding the *section* end leaves every global above it as an
    anonymous literal, which is what defeated the first m2c pass.
    """
    import struct
    img = open(elf, "rb").read()
    phoff, = struct.unpack_from("<I", img, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", img, 0x2A)
    lo, hi = None, 0
    for i in range(phnum):
        o = phoff + i * phentsize
        if struct.unpack_from("<I", img, o)[0] != 1:          # PT_LOAD
            continue
        vaddr, = struct.unpack_from("<I", img, o + 8)
        memsz, = struct.unpack_from("<I", img, o + 20)
        lo = vaddr if lo is None else min(lo, vaddr)
        hi = max(hi, vaddr + memsz)
    return lo, hi


def asm_for(va, name, size, table, names_by_va, bounds=None, symbolize_data=True,
            jtables=None, gp=None, ee_abi=True):
    """spimdisasm-style assembly text for one function.

    `symbolize_data` rewrites a `lui`/`lw` (or `lui`/`addiu`) address pair into
    `%hi(SYM)` / `%lo(SYM)`, which is how m2c is meant to be fed. Without it m2c
    sees only a computed number, so it invents an anonymous literal global
    (`*(void **)0x55EBC0`) — and then a `--context` declaration can never match it,
    which is why the recovered class types had no effect until this was added.

    `jtables` is `{table_va: [case_va, ...]}` for this function (from
    `tools/jumptables.py`). m2c refuses a `switch` whose table it cannot see:

        There must be a read of a variable before the instruction which has a name
        starting with "jtbl"/"jpt_"/"lbl_"/"jumptable_".

    so the base pair is named `jtbl_<addr>`, a `.L<case>` label is inserted at every
    entry target, and the entries themselves are appended as a `.section .rodata`
    block — the contract m2c's own `tests/end_to_end/got/manual.s` demonstrates.

    `gp` (the value from the ELF's `.reginfo`) turns a `disp($gp)` load/store into
    `%gp_rel(SYM)($gp)`, and an `addiu $r,$gp,disp` address computation into
    `%gp_rel(SYM)`, so a small-data access names its object instead of an
    offset off a saved-gp register. Without it m2c cannot compile those functions.

    `ee_abi` renames the hardware `t0-t3` argument registers to m2c's `a4-a7` so its
    EE arch can model arguments 5..8 (see the `ee_abi` block below).
    """
    lo_bound, hi_bound = bounds or (0x100000, 0x58D280)
    jtables = jtables or {}
    jtbl_names = {a: "jtbl_%08x" % a for a in jtables}
    labels = {}
    if jtables:
        for ents in jtables.values():
            for e in ents:
                if va <= e < va + size:
                    labels.setdefault(e, ".L%08X" % (e & 0xFFFFFF))
    ins = []
    for i in range(size // 4):
        a = va + 4 * i
        mn, ops, word = table[a]
        op = word >> 26
        if op in (2, 3):                                    # j / jal
            tgt = ((word & 0x3FFFFFF) << 2) | (a & 0xF0000000)
            ops = names_by_va.get(tgt) or ("func_%08X" % tgt)
        elif BRANCH.match(mn):                              # pc-relative branch
            off = word & 0xFFFF
            if off & 0x8000:
                off -= 0x10000
            tgt = a + 4 + 4 * off
            labels.setdefault(tgt, ".L%08X" % (tgt & 0xFFFFFF))
            ops = (ops.rsplit(",", 1)[0] + "," if "," in ops else "") + labels[tgt]
        ops = REG_RE.sub(r"$\1", ops)
        ins.append([a, mn, ops, word])

    def sym_for(addr):
        return (jtbl_names.get(addr) or names_by_va.get(addr)
                or ("DAT_%08x" % addr))

    if symbolize_data:
        # A register loaded by `lui $r,HIGH` keeps that high half until it is written
        # again, and **every** load/store that uses it adds the `%lo` of the object
        # being addressed. The original pass paired a `lui` with only the first use in
        # a 4-instruction window and stopped, so a second use after a branch kept its
        # bare numeric displacement: FUN_00270db0's `sw $a0,-28036($v0)` at 0x270dcc
        # (the same DAT_004a927c, reached across the `bnez`) stayed numeric, and m2c
        # then added that displacement **on top of** the named `%hi` symbol, emitting
        # `DAT_004a927c.unk-6D84` — an address 0x6D84 too low, which no C could match.
        # 130 of the 10,740 unmatched functions (1.2 %) had at least one such use.
        hi_by_reg = {}
        for i, (a, mn, ops, word) in enumerate(ins):
            if mn == "lui" and "," in ops:
                dst, imm = [x.strip() for x in ops.split(",", 1)]
                try:
                    hi = int(imm, 0)
                except ValueError:
                    hi = None
                if hi is not None:
                    # name the object from the first use while the register is intact.
                    # The `addiu $dst,$dst,lo` completion **writes** dst, so the
                    # "register was reassigned" check has to come *after* recognising
                    # it — testing the write first breaks on the very `%lo` it should
                    # name (that is how a jump-table base was left numeric and m2c
                    # then refused the `jr` with "unable to determine jump table").
                    sym, use, form = None, None, None
                    for j in range(i + 1, len(ins)):
                        mn2, ops2 = ins[j][1], ins[j][2]
                        addr = None
                        if mn2 in LOADS and ops2.endswith("(%s)" % dst):
                            base_off = ops2.rsplit(",", 1)[-1][:-len("(%s)" % dst)]
                            try:
                                off = int(base_off, 0)
                            except ValueError:
                                break
                            # a load displacement is already sign-extended by objdump
                            addr, form = (hi << 16) + off, "base"
                        elif mn2 in ("addiu", "ori") and "," in ops2:
                            p = [x.strip() for x in ops2.split(",")]
                            if len(p) == 3 and p[0] == dst and p[1] == dst:
                                try:
                                    off = int(p[2], 0)
                                except ValueError:
                                    break
                                addr = am.eff_addr(hi, off, mn2 == "addiu")
                                form = "addiu"
                            elif _written_reg(mn2, ops2) == dst:
                                break
                        elif _written_reg(mn2, ops2) == dst:
                            # `addu $dst,$dst,$idx` keeps the high half — the classic
                            # `lui; addu; lw %lo($dst)` jump-table base — so keep looking.
                            p = [x.strip() for x in ops2.split(",")]
                            if mn2 in ("add", "addu", "daddu") and len(p) == 3 \
                                    and p[0] == dst and p[1] == dst:
                                continue
                            break
                        if addr is None:
                            continue
                        if lo_bound <= addr < hi_bound:
                            sym, use = sym_for(addr), j
                        break
                    if sym is not None:
                        ins[i][2] = "%s, %%hi(%s)" % (dst, sym)
                        mn2, ops2 = ins[use][1], ins[use][2]
                        if form == "base":
                            ins[use][2] = (ops2.rsplit(",", 1)[0]
                                           + ",%%lo(%s)(%s)" % (sym, dst))
                        else:
                            p = [x.strip() for x in ops2.split(",")]
                            ins[use][2] = "%s, %s, %%lo(%s)" % (p[0], p[1], sym)
                        hi_by_reg[dst] = hi
                    continue
            # any later use of a still-live `lui` register completes a `%lo`
            for reg, hi in hi_by_reg.items():
                off, form = _reg_use_offset(mn, ops, reg)
                if off is None:
                    continue
                addr = (hi << 16) + off if form == "base" else am.eff_addr(hi, off, mn == "addiu")
                if not (lo_bound <= addr < hi_bound):
                    continue
                sym = sym_for(addr)
                if form == "base":
                    ins[i][2] = ops.rsplit(",", 1)[0] + ",%%lo(%s)(%s)" % (sym, reg)
                else:
                    p = [x.strip() for x in ops.split(",")]
                    ins[i][2] = "%s, %s, %%lo(%s)" % (p[0], p[1], sym)
            d = _written_reg(mn, ops)
            if d is not None:
                hi_by_reg.pop(d, None)

    if gp:
        # `lbu $v1,-32476($gp)` is a *small-data* access: the displacement is
        # `symbol - gp`, and the original compiler chose gp-relative because the object
        # is a byte/float/double small enough for .sdata. Left numeric, m2c models the
        # whole thing as pointer arithmetic on the saved-gp register and emits
        # `saved_reg_gp->unk-7EDC`, which does not compile. Naming the target address
        # (`%gp_rel(...)($gp)`) makes m2c emit the global instead, and MWCC emits the
        # same gp-relative access back; verify.py already resolves R_MIPS_GPREL16 with
        # gp from `.reginfo`.
        #
        # The name is `GPR_<addr>`, not `DAT_<addr>`, because it has to carry the
        # *addressing mode*: `m2c_batch.arrayize_globals` forces a `DAT_` global out of
        # small data (so it gets absolute `lui`/`addiu`, finding #311), which is exactly
        # wrong for an object retail reaches through gp. Keeping the two namespaces
        # apart lets the cleaner leave a `GPR_` object the size m2c inferred, so `lbu`
        # stays `lbu` and `lwc1`/`ld` stay gp-relative too.
        for i, (a, mn, ops, word) in enumerate(ins):
            if mn not in LOADS or not ops.endswith("($gp)"):
                continue
            head, _, disp = ops[:-len("($gp)")].rpartition(",")
            try:
                addr = gp + int(disp.strip(), 0)
            except ValueError:
                continue
            if not (lo_bound <= addr < hi_bound):
                continue
            ins[i][2] = "%s,%%gp_rel(GPR_%08x)($gp)" % (head, addr)

        # `addiu $a3,$gp,-31940` computes the **address** of a small-data object and
        # passes/stores it, rather than dereferencing it. The displacement is the same
        # `symbol - gp`, but here the operand is a bare `$gp` register (not a `disp($gp)`
        # address mode), so the load/store pass above does not reach it and m2c models
        # the saved-gp register directly, emitting `saved_reg_gp - 0x7CC4`. Naming the
        # target the same way the other gp operands are named makes m2c emit `&GPR_x`.
        for i, (a, mn, ops, word) in enumerate(ins):
            if mn not in ("addiu", "addi", "daddiu", "daddi"):
                continue
            parts = [x.strip() for x in ops.split(",")]
            if len(parts) != 3 or parts[1] != "$gp":
                continue
            try:
                addr = gp + int(parts[2], 0)
            except ValueError:
                continue
            if not (lo_bound <= addr < hi_bound):
                continue
            ins[i][2] = "%s,$gp,%%gp_rel(GPR_%08x)" % (parts[0], addr)

    if ee_abi:
        # The R5900 has no `a4-a7`: integer arguments 5..8 arrive in the hardware
        # registers `t0-t3`. m2c's EE arch (`MipseeArch`) names those argument slots
        # `a4-a7` instead, so feeding it the hardware names leaves the `t0-t3` setup
        # unmodelled as a *temporary* and the arguments are dropped from the call
        # (finding #332 measured the convention; this is the bridge to m2c).
        for row in ins:
            row[2] = re.sub(r"\$t([0-3])\b",
                            lambda m: "$a%d" % (4 + int(m.group(1))), row[2])

    out = [".set noat", ".set noreorder", "", "glabel %s" % name]
    for a, mn, ops, word in ins:
        if a in labels:
            out.append("%s:" % labels[a])
        out.append("/* %06X %08X %08X */  %-8s %s" % (a - 0x100000, a, word, mn, ops))
    out.append("endlabel %s" % name)
    if jtables:
        # The compiler-generated jump table, as m2c's parser wants it: a `.rodata`
        # section whose words name the case labels it just read in the text.
        out.append("")
        out.append(".section .rodata")
        for tv in sorted(jtables):
            out.append("%s:" % jtbl_names[tv])
            for e in jtables[tv]:
                out.append(".word .L%08X" % (e & 0xFFFFFF))
    return "\n".join(out) + "\n"


def decompile(va, elf=ELF_DEFAULT, symbols=SYMBOLS_DEFAULT, m2c=M2C_DEFAULT,
              target="mipsee-mwcc-c", context=None, extra=(), asm_out=None,
              indices=None, jtables=None):
    """-> (c_source, asm_text, info). `indices` restricts work to cached symbols.

    `jtables` is the function's `{table_va: [case_va, ...]}` (default: looked up in
    `config/SLUS-20836/jumptables.txt`); without it a `switch` cannot get past m2c's jump-table
    check.
    """
    img = open(elf, "rb").read()
    syms = indices if indices is not None else am.load_symbols(symbols)
    bysym = {v: (s, n) for v, s, n in syms}
    names_by_va = {v: n for v, s, n in syms}
    size, name = bysym[va]
    if jtables is None:
        jtables = load_jtables(elf, symbols).get(va, {})
    lo = min(v for v, _, _ in syms)
    hi = max(v + s for v, s, _ in syms)
    table = indices["__table__"] if isinstance(indices, dict) and "__table__" in indices \
        else am.disassemble(img, lo, hi)
    text = asm_for(va, name, size, table, names_by_va, bounds=load_bounds(elf),
                   jtables=jtables, gp=load_gp(elf))
    sp = asm_out or "/tmp/m2c_one_%d.s" % os.getpid()
    os.makedirs(os.path.dirname(sp) or ".", exist_ok=True)
    open(sp, "w").write(text)
    # Run m2c through the guard wrapper, not `m2c.py` directly: the vendored m2c crashes
    # on `fold_shift_bgez` (see tools/m2c_compat.py), and a subprocess cannot inherit the
    # in-process patch that `m2c_batch.run_m2c` applies. `DW4_M2C_DIR` tells the wrapper
    # which checkout to use, so an explicit `--m2c` is still honoured.
    m2c_run = os.path.join(os.path.dirname(os.path.abspath(__file__)), "m2c_run.py")
    cmd = [sys.executable, m2c_run, "--no-cache", "-t", target, "-f", name,
           "--comment-style", "none"] + list(extra)
    if context:
        cmd += ["--context", context]
    cmd.append(sp)
    r = subprocess.run(cmd, capture_output=True, text=True,
                       env=dict(os.environ, DW4_M2C_DIR=os.path.dirname(os.path.abspath(m2c))))
    return r.stdout, text, {"rc": r.returncode, "stderr": r.stderr, "name": name,
                            "size": size}


def load_jtables(elf=ELF_DEFAULT, symbols=SYMBOLS_DEFAULT, path=None):
    """config/SLUS-20836/jumptables.txt -> {fn_va: {table_va: [case_va, ...]}} (reads the image)."""
    import jumptables as jt
    cfg = jt.load(path) if path else jt.load()
    img = open(elf, "rb").read()
    out = {}
    for fn, tabs in cfg.items():
        out[fn] = {tv: list(jt.entries(img, tv, n)) for tv, n in tabs}
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("address")
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--symbols", default=SYMBOLS_DEFAULT)
    ap.add_argument("--m2c", default=M2C_DEFAULT)
    ap.add_argument("--target", default="mipsee-mwcc-c")
    ap.add_argument("--context", default=None)
    projection = ap.add_mutually_exclusive_group()
    projection.add_argument("--materialize-calls", action="store_true",
                    help="keep nonvoid call results in explicit temporaries (diagnostic)")
    projection.add_argument("--materialize-boundaries", action="store_true",
                            help="keep named call results and consumed MIPS remainders explicit")
    ap.add_argument("--extra", action="append", default=[])
    ap.add_argument("--keep-asm", action="store_true")
    ap.add_argument("--asm-out", default=None)
    a = ap.parse_args(argv)
    va = int(a.address, 0)
    extra = list(a.extra)
    if a.materialize_calls:
        extra.append("--materialize-calls")
    if a.materialize_boundaries:
        extra.append("--materialize-boundaries")
    c, text, info = decompile(va, elf=a.elf, symbols=a.symbols, m2c=a.m2c,
                              target=a.target, context=a.context,
                              extra=extra,
                              asm_out=a.asm_out)
    if a.keep_asm:
        print("=== asm ===\n" + text)
    print("=== m2c (rc=%d) ===" % info["rc"])
    print(c)
    if info["rc"]:
        print("STDERR:", info["stderr"][:1500])
    return 0 if info["rc"] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
