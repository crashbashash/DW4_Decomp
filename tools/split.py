#!/usr/bin/env python3
"""
split.py — lay out the retail code and emit one assembly unit per function.

Two jobs, both driven by the Ghidra function dump:

  1. `--symbols`  write `config/SLUS-20836/symbols.txt`, the canonical layout of the binary:
                  one `<va> <size> <name>` line per function, sorted by address.
                  This is the file that says what code exists and where.
  2. (default)    emit `asm/<name>.s` for every symbol — the retail instruction
                  words, byte-exact, so the not-yet-decompiled remainder can be
                  linked into a "Ship of Theseus" build (C where we have it,
                  original bytes everywhere else).

The generated assembly is `.word` per instruction with the disassembly in a
comment: it reassembles byte-for-byte with `mipsel-linux-gnu-as`, and reads as
the original code for review. `asm/` is GENERATED and not committed (it is the retail
code as text): never hand-edit it; re-run this. `make` calls
`split.py --ensure`, which writes the tree when it is missing or stale.

Usage:
  split.py --symbols                       # (re)write config/SLUS-20836/symbols.txt
  split.py                                 # emit asm/ for every symbol
  split.py --ensure                        # emit asm/ only when it is missing or stale
  split.py --limit 200                     # first 200 symbols (smoke test)
  split.py --symbols --limit 0             # symbols only
  split.py --region 0x100000,0x110000      # only this VA range

Notes / limits:
  * Function boundaries start from Ghidra and are repaired here: the reviewed rows of
    config/SLUS-20836/extent-overrides.tsv (growth, shrink, `cut`, `merge`) and the promotion rules
    that give the code Ghidra never made a function a symbol of its own. The rules, their
    evidence and the inventory they produce: docs/engine/function-inventory.md. The run
    prints every rule with its count; a replay reproduces config/SLUS-20836/symbols.txt bit for bit.
    `tools/check.py` catches a bad split, because it compares the assembled bytes against
    the retail image; `scripts/inventory_scan.py` reports the code still outside the map.
  * Jump tables and other data that live *inside* a function's address range
    disassemble as instructions; check.py treats them as opaque words, so they
    still round-trip byte-exactly.
"""
import argparse
import bisect
import json
import os
import re
import struct
import sys
import subprocess
import sys
import tempfile

VADDR_BASE, FILE_BASE = 0x100000, 0x80
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
LABELS_DEFAULT = os.path.join(ROOT, "data", "symbols.json")
SDK_STARTS_DEFAULT = "data/sdk-bindings.json"
NAMES_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "names")
FUNCS_DEFAULT = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                             "..", "data", "functions.json")
EXTENTS_DEFAULT = os.path.join(ROOT, "data", "function-extents.json")
OVERRIDES_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "extent-overrides.tsv")


def apply_function_extents(fns, path):
    """Use reviewed address spans where the dump counted a disjoint body.

    Evidence comes from dump_function_extents.py, never an edited symbol table.
    Reject shrinking, misalignment, missing entries, duplicates, and overlap.
    """
    if not os.path.exists(path):
        return fns
    with open(path) as fh:
        rows = json.load(fh)
    spans = {}
    for row in rows:
        va, end = int(row["address"], 0), int(row["end_exclusive"], 0)
        if va in spans or va % 4 or end % 4 or end <= va:
            raise ValueError("invalid/duplicate function span at %#x" % va)
        spans[va] = end
    out = []
    for i, (va, size, name, original) in enumerate(fns):
        end = spans.pop(va, None)
        if end is not None:
            if end < va + size or (i + 1 < len(fns) and end > fns[i + 1][0]):
                raise ValueError("function span shrinks or overlaps at %#x" % va)
            size = end - va
        out.append((va, size, name, original))
    if spans:
        raise ValueError("function span has no function: %s" % sorted(spans))
    return out


def load_extent_overrides(path):
    """config/SLUS-20836/extent-overrides.tsv -> {va: (size, name, kind)}; kind is "", "cut" or "merge"."""
    rows = {}
    if not path or not os.path.exists(path):
        return rows
    with open(path) as fh:
        for ln in fh:
            if not ln.strip() or ln.startswith("#"):
                continue
            p = ln.split()
            va, size = int(p[0], 0), int(p[1])
            name = p[2] if len(p) > 2 else None
            kind = p[3] if len(p) > 3 else ""
            if va in rows or size <= 0 or size % 4 or kind not in ("", "cut", "merge"):
                raise ValueError("invalid/duplicate extent override at %#x" % va)
            rows[va] = (size, name, kind)
    return rows


def apply_extent_overrides(fns, img, path):
    """Set the size of the functions named in config/SLUS-20836/extent-overrides.tsv.

    A row is a reviewed correction of the dump (see the file header). It may shrink a function
    whose recorded extent ran past its own return, or grow one that stops short of it, but never cuts
    into a neighbour: a growth stops at the next function, and a plain shrink may leave only zero
    words before the next function. Two reviewed keywords in the fourth column go further:

    * ``cut``   — the shrink leaves *code* behind: the dump had glued a second function onto this
                  one. The remainder is not a function yet; a promotion rule must claim it, and
                  `check_cuts` fails the run if none does, so a cut can never orphan code silently.
    * ``merge`` — the function at `va` absorbs every dump function that starts inside its new
                  extent and takes the row's name: Ghidra had split one body into a `thunk_` and a
                  fragment (`FUN_002fe2ac`), and only one symbol may own those bytes.

    Returns (functions, cuts) — `cuts` is `[(va, new_end)]` for `check_cuts`.
    """
    rows = load_extent_overrides(path)
    if not rows:
        return fns, []
    # merges first: they delete dump entries, so sizes and neighbours are settled before the cuts
    merged = set()
    for va, (size, name, kind) in rows.items():
        if kind != "merge":
            continue
        head = next((f for f in fns if f[0] == va), None)
        if head is None:
            raise ValueError("merge row at %#x names no function" % va)
        inside = [f for f in fns if va < f[0] < va + size]
        merged.update(f[0] for f in inside)
    fns = [f for f in fns if f[0] not in merged]
    out, cuts = [], []
    for i, (va, size, name, original) in enumerate(fns):
        row = rows.pop(va, None)
        if row is not None:
            new, rname, kind = row
            nxt = fns[i + 1][0] if i + 1 < len(fns) else None
            end = va + new
            if nxt is not None and end > nxt:
                raise ValueError("extent override at %#x runs into the next function" % va)
            if kind == "merge":
                name, original = rname, None
            elif end < va + size:
                tail = va_bytes(img, end, min(va + size, nxt if nxt is not None else va + size) - end)
                if any(tail):
                    if kind != "cut":
                        raise ValueError("extent override at %#x would cut non-padding bytes" % va)
                    cuts.append((va, end))
            size = new
        out.append((va, size, name, original))
    if rows:
        raise ValueError("extent override has no function: %s" % sorted(hex(v) for v in rows))
    return out, cuts


def check_cuts(fns, img, cuts):
    """Every `cut` row's remainder must have become a function: the first non-zero word at or
    after the cut must be a function start. Raises otherwise — a cut that no rule claims would
    turn reviewed code into an unsymbolised gap, which is the defect this file exists to remove."""
    starts = {f[0] for f in fns}
    for va, end in cuts:
        o = end
        while struct.unpack_from("<I", img, o - VADDR_BASE + FILE_BASE)[0] == 0:
            o += 4
        if o not in starts:
            raise ValueError("cut at %#x leaves unclaimed code at %#x: no promotion rule took it"
                             % (va, o))


def read_elf(path):
    with open(path, "rb") as fh:
        return fh.read()


def va_bytes(img, va, n):
    off = va - VADDR_BASE + FILE_BASE
    return img[off:off + n]


def sanitize(name):
    """Make a symbol usable as a filename, an assembler label and a C identifier.

    The Ghidra dump contains C++-style names (`Gap::Bec::ParticleArray::vfunc_35`,
    1,289 of them from the vtable pass). `::` is fine in Ghidra and illegal in both
    GNU as labels and C identifiers, so it has to be mapped before anything can be
    written out or decompiled. Every other non-identifier character goes too, and
    the original is preserved in config/SLUS-20836/symbols.txt's fourth column and in the asm
    header comment.
    """
    return re.sub(r"[^A-Za-z0-9_]", "_", name)


def is_terminator(word):
    """True if `word` is a branch/jump that MIPS requires a delay slot after."""
    op = word >> 26
    if op in (1, 2, 3, 4, 5, 6, 7):          # regimm / j / jal / beq..bgtz
        return True
    return op == 0 and (word & 0x3F) in (8, 9)   # jr / jalr


def extend_delay_slots(fns, img):
    """Give back the delay slot of functions Ghidra cut short.

    728 functions (4.6%) end on a branch/jump with no delay slot inside their
    symbol — e.g. `FUN_00100240` ends at `jr $ra` and the `addiu sp,sp,16` that
    must follow it lives in the *next* layout unit. The build still links
    byte-identically (those bytes are emitted as data), but the function is not a
    function: no C can match it, and m2c refuses the listing outright
    ("Last instruction is missing a delay slot").

    Grow those sizes by the one word the hardware requires, unless it would run
    into the next symbol (2 cases, where Ghidra's boundaries genuinely overlap and
    tools/layout.py already resolves the tiling).
    """
    out, grown = [], 0
    for i, (va, sz, nm, orig) in enumerate(fns):
        nxt = fns[i + 1][0] if i + 1 < len(fns) else None
        off = va - VADDR_BASE + FILE_BASE
        if sz >= 4 and sz % 4 == 0 and off + sz <= len(img) \
                and (nxt is None or nxt >= va + sz + 4):
            word, = struct.unpack_from("<I", img, off + sz - 4)
            if is_terminator(word):
                sz += 4
                grown += 1
        out.append((va, sz, nm, orig))
    return out, grown


def extend_jump_table_bodies(fns, img):
    """Give switch dispatchers their case bodies back.

    Ghidra stops a `switch` at the indirect `jr v0` and never follows the jump
    table, so the case bodies (and the shared epilogue they branch to) end up in the
    *unclaimed* gap before the next symbol. `FUN_00204840` is 52 bytes — just
    `sltiu at,a0,14 ; ... ; lw v0,0(v0) ; jr v0` — and its 14 case bodies plus the
    `jr ra` epilogue sit at 0x204874..0x204910, attributed to nobody. m2c rejects
    such a function outright (`Cannot find branch target .L00204904`), and no C can
    match a fragment.

    151 functions (400 KB, 13% of the code) are in this state, and none of the
    4,413 already matched ones branches outside its own range. The fix is to grow
    the symbol to the next one when every out-of-range branch lands in the
    unclaimed gap (i.e. none lands inside another function), capped so a stray
    branch cannot swallow a huge data region.
    """
    MAX_GROW = 8192
    out, grown, added = [], 0, 0
    for i, (va, sz, nm, orig) in enumerate(fns):
        nxt = fns[i + 1][0] if i + 1 < len(fns) else None
        off = va - VADDR_BASE + FILE_BASE
        if nxt is not None and nxt > va + sz and (nxt - va - sz) <= MAX_GROW \
                and off + sz + 4 <= len(img):
            targets = []
            for j in range(sz // 4):
                word, = struct.unpack_from("<I", img, off + 4 * j)
                if (word >> 26) in (1, 4, 5, 6, 7):        # pc-relative branches only
                    rel = word & 0xFFFF
                    if rel & 0x8000:
                        rel -= 0x10000
                    t = va + 4 * j + 4 + 4 * rel
                    if not (va <= t < va + sz):
                        targets.append(t)
            if targets and all(va + sz <= t < nxt for t in targets):
                added += nxt - (va + sz)
                sz = nxt - va
                grown += 1
        out.append((va, sz, nm, orig))
    return out, grown, added


def _is_prologue(word):
    """`addiu sp,sp,-N`, N != 0 — the frame a non-leaf function opens with."""
    return 0x27BD8000 <= word <= 0x27BDFFFF


# ---- instruction shape -------------------------------------------------------------------
# The promotion rules below decide extents from the retail words alone (no Ghidra, no objdump),
# so a replay of `--symbols` is a pure function of the image and the committed inputs. These
# helpers are the whole instruction knowledge they need: the fields of a MIPS word, the EE's
# opcode inventory, and the branch forms that end a body. docs/engine/function-inventory.md
# states the rules in prose.

SECTION_HI = 0x554B00          # end of the loadable section (tools/layout.py SECTION_HI)

# SPECIAL function codes the EE core has (R5900 lacks dmult/dmultu/ddiv/ddivu and movci)
_SPECIAL_OK = frozenset([0x00, 0x02, 0x03, 0x04, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
                         0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,
                         0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
                         0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x36, 0x38, 0x3A,
                         0x3B, 0x3C, 0x3E, 0x3F])
# ...of which these write `rd`: a compiler never targets $zero with them (the zero word is `nop`)
_SPECIAL_RD = frozenset([0x00, 0x02, 0x03, 0x04, 0x06, 0x07, 0x0A, 0x0B, 0x10, 0x12, 0x14, 0x16,
                         0x17, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2A, 0x2B,
                         0x2C, 0x2D, 0x2E, 0x2F, 0x38, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F])
_REGIMM_OK = frozenset([0, 1, 2, 3, 8, 9, 0xA, 0xB, 0xC, 0xE, 0x10, 0x11, 0x12, 0x13, 0x18, 0x19])
_MMI_OK = frozenset([0x00, 0x01, 0x04, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x18, 0x19, 0x1A, 0x1B,
                     0x20, 0x21, 0x28, 0x29, 0x30, 0x31, 0x34, 0x36, 0x37, 0x3C, 0x3E, 0x3F])
_IMM_OK = frozenset([0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x18, 0x19])   # addi..lui, daddi/daddiu
_MEM_OK = frozenset([0x1A, 0x1B, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
                     0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x31, 0x33, 0x36, 0x37, 0x39, 0x3E,
                     0x3F])                 # ldl..sq, lb..lwu, sb..swr, cache, lwc1, pref, lqc2, ld, swc1, sqc2, sd
_BRANCH_OK = frozenset([0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17])


def _op(w):
    return w >> 26


def _rs(w):
    return (w >> 21) & 0x1F


def _rt(w):
    return (w >> 16) & 0x1F


def _rd(w):
    return (w >> 11) & 0x1F


def _code_shaped(w):
    """True if `w` is an instruction the EE has and a compiler could emit.

    Opcode and function-code inventory of the R5900, plus one semantic rule: nothing but the
    zero word (`nop`) writes $zero. Data that happens to decode (floats, string bytes, table
    entries) almost never survives a whole body of this test, and that is what keeps the
    structural rules out of the rodata regions."""
    if w == 0:
        return True
    op = _op(w)
    if op == 0:
        f = w & 0x3F
        if f not in _SPECIAL_OK:
            return False
        return not (f in _SPECIAL_RD and _rd(w) == 0)
    if op == 1:
        return _rt(w) in _REGIMM_OK
    if op in (2, 3):
        # a `j`/`jal` must land in the section: a tab or newline byte in a string table also
        # decodes as `j`, to an address no code has
        return VADDR_BASE <= (w & 0x3FFFFFF) << 2 < SECTION_HI
    if op in _BRANCH_OK or op in _MEM_OK:
        return True
    if op in _IMM_OK:
        return _rt(w) != 0
    if op == 0x10:                                   # COP0: mfc0/mtc0/bc0/C0 (tlb*, eret, ei, di)
        return _rs(w) in (0, 4, 8, 0x10)
    if op == 0x11:                                   # COP1: mfc1/cfc1/mtc1/ctc1/bc1/S/W formats
        return _rs(w) in (0, 2, 4, 6, 8, 0x10, 0x14)
    if op == 0x12:                                   # COP2: qmfc2/cfc2/qmtc2/ctc2/bc2/VU macro
        return _rs(w) in (1, 2, 5, 6, 8) or _rs(w) >= 0x10
    if op == 0x1C:
        return (w & 0x3F) in _MMI_OK
    return False


def _is_jr(w):
    return _op(w) == 0 and (w & 0x3F) == 8


def _is_j(w):
    return _op(w) == 2


def _is_jal(w):
    return _op(w) == 3


def _is_pc_branch(w):
    """A PC-relative branch, conditional or not: regimm, beq..bgtz, their likely forms, bc0/1/2."""
    op = _op(w)
    if op in _BRANCH_OK:
        return True
    if op == 1:
        return _rt(w) in (0, 1, 2, 3, 0x10, 0x11, 0x12, 0x13)
    return op in (0x10, 0x11, 0x12) and _rs(w) == 8


def _branch_target(va, w):
    rel = w & 0xFFFF
    if rel & 0x8000:
        rel -= 0x10000
    return va + 4 + 4 * rel


def _j_target(va, w):
    return ((va + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)


def _is_b(w):
    """An unconditional `b`: `beq zero,zero` or `bgez zero`. The likely forms are left out: no
    compiler spells `b` as `beql zero,zero`, and that word (`0x5000xxxx`) is what a NUL byte
    followed by `P` looks like in a string table."""
    if _op(w) == 4 and _rs(w) == 0 and _rt(w) == 0:
        return True
    return _op(w) == 1 and _rs(w) == 0 and _rt(w) == 1


def _is_unconditional_end(w):
    """A word after whose delay slot control never falls through: `jr X`, `j X`, `b X`."""
    return _is_jr(w) or _is_j(w) or _is_b(w)


def _word(img, va):
    return struct.unpack_from("<I", img, va - VADDR_BASE + FILE_BASE)[0]


def _fresh_start(img, va):
    """True if nothing falls into `va`: the word before it is padding (a zero that is not some
    branch's or call's delay slot) or the delay slot of an unconditional transfer. A function
    can begin here; a block of the preceding function cannot, except as a branch target —
    and that case the sweep in `_sweep_extent` rules out by refusing a body whose bytes a
    branch from the candidate jumps past."""
    if va % 4 or va - 8 < VADDR_BASE:
        return False
    p1, p2 = _word(img, va - 4), _word(img, va - 8)
    if _is_jr(p2) and _rs(p2) not in (31, 25):
        return False          # `jr v0; nop` is a switch dispatch: what follows is its first case body
    if _is_unconditional_end(p2):
        return True
    return p1 == 0 and not is_terminator(p2)


def _in_sorted(lst, x):
    k = bisect.bisect_left(lst, x)
    return k < len(lst) and lst[k] == x


def _sweep_extent(img, va, bound, strong=()):
    """Size of the self-contained body that starts at `va`, or None.

    Walk forward from `va`. The body ends after the delay slot of the first transfer that is
    unconditional *and* not jumped over by an earlier branch of the body: `jr ra`, `jr t9`, or a
    `j` that leaves [va, bound), goes backwards or lands on a frame prologue (a tail call).
    Internal `j`s (EE GCC spells long forward jumps that way) and every PC-relative branch —
    `b` included — extend the body to their target; a body that ends in a backward `b` (an
    idle loop) is not recognised, because a `b` is also what string bytes most easily decode
    to, and a return or jump never is. None when a word is not code-shaped, a branch leaves
    [va, bound), a second frame opens (the walk ran into the next function), or no end comes
    before `bound`. `strong` is the sorted list of externally referenced starts: a `j` to one
    of them is a tail call, not an internal jump."""
    o, max_tgt = va, va
    while o + 8 <= bound:
        w = _word(img, o)
        if not _code_shaped(w):
            return None
        if o > va and _is_prologue(w) and _fresh_start(img, o):
            return None                               # the next function's frame: the walk missed an end

        end = False
        if _is_jr(w):
            end = _rs(w) in (31, 25)                 # jr ra / jr t9; `jr v0` is a switch dispatch
        elif _is_j(w):
            t = _j_target(o, w)
            if va <= t < bound and t > o and not _is_prologue(_word(img, t)) \
                    and not _in_sorted(strong, t):
                max_tgt = max(max_tgt, t)
            else:
                end = True
        elif _is_pc_branch(w):
            t = _branch_target(o, w)
            if not (va <= t < bound):
                return None
            max_tgt = max(max_tgt, t)
        if end and max_tgt < o + 8:
            d = _word(img, o + 4)
            if not _code_shaped(d) or _is_prologue(d):
                return None
            return o + 8 - va
        o += 4
    return None


def _has_switch_dispatch(img, va, size):
    """True if the body jumps through a register other than ra/t9 (`jr v0`: a jump table)."""
    return any(_is_jr(_word(img, va + 4 * k)) and _rs(_word(img, va + 4 * k)) not in (31, 25)
               for k in range(size // 4))


def _claim(img, va, gap_hi, strong, strong_data):
    """The extent a new function at `va` may take inside its gap, or None.

    The sweep gives the body; a *referenced* start inside it (`strong`, sorted) means either the
    body really ends before that start — then the sweep bounded there must still end cleanly,
    and the function is cut to it — or this is not one function, and nothing is promoted. A body
    with a switch dispatch owns the data words that point into it (its jump table), so those do
    not count against it; jump-table entries are the one data reference that lands mid-body."""
    size = _sweep_extent(img, va, gap_hi, strong)
    if size is None:
        return None
    k = bisect.bisect_right(strong, va)
    inner = [s for s in strong[k:bisect.bisect_left(strong, va + size)]]
    if inner and _has_switch_dispatch(img, va, size):
        inner = [s for s in inner if s not in strong_data]
    if inner:
        if not _fresh_start(img, inner[0]):
            return None
        size = _sweep_extent(img, va, inner[0], strong)
        if size is None or any(_word(img, a) for a in range(va + size, inner[0], 4)):
            return None
    return size


def _thunk_target(img, va, size, by_va):
    """The function an 8-byte `j <function>; nop` body jumps to, else None."""
    if size != 8:
        return None
    w, d = _word(img, va), _word(img, va + 4)
    if _is_j(w) and d == 0 and _j_target(va, w) in by_va:
        return _j_target(va, w)
    return None


def _promote_in_gaps(fns, img, candidates, strong, strong_data, accept, min_size=8, overlay=None):
    """Promote the sorted `candidates` that start a self-contained body in an unclaimed gap.

    Shared by every structural rule: a candidate is taken when it lies outside every function,
    nothing falls into it, `_claim` finds its extent, `accept(va, size)` agrees on the
    shape, and the body does not reach the next candidate (the earlier one is kept; the later
    one is then inside a function and skipped). Nothing moves: every byte stays where it was.
    An 8-byte `j <function>; nop` body is named after its target like `promote_j_thunks`
    does (`thunk_<target>`), so the rule that finds a stub does not decide its name.
    """
    starts = [f[0] for f in fns]
    ends = [f[0] + f[1] for f in fns]
    by_va = {f[0]: f[2] for f in fns}
    overlay = overlay or {}
    out, added = list(fns), []
    taken_end = 0
    for va in candidates:
        if va % 4 or va < VADDR_BASE or va >= SECTION_HI or va < taken_end:
            continue
        i = bisect.bisect_right(starts, va) - 1
        if i >= 0 and va < ends[i]:
            continue                                  # inside a function
        gap_hi = starts[i + 1] if i + 1 < len(starts) else SECTION_HI
        if not _fresh_start(img, va):
            continue
        size = _claim(img, va, gap_hi, strong, strong_data)
        if size is None or size < min_size or not accept(va, size):
            continue
        target = _thunk_target(img, va, size, by_va)
        if target is not None:
            nm = sanitize("thunk_" + overlay.get(target, (by_va[target],))[0])
            out.append((va, size, nm, nm))
        else:
            out.append((va, size, "FUN_%08x" % va, None))
        added.append((va, size))
        taken_end = va + size
    out.sort(key=lambda f: f[0])
    return out, added


def non_entry_tables(exceptions_path, jumptables_path):
    """Address ranges whose code pointers are not function entries: `[(lo, hi)]`.

    Two kinds of retail table hold code addresses that point *into* bodies and must not
    bound or seed a structural rule: the C++ exception index and tables (call-site and
    range addresses; tools/exceptions.py, config/SLUS-20836/exceptions.txt) and the switch jump tables
    of known functions (case bodies; config/SLUS-20836/jumptables.txt). Both files are committed and
    generated, so the replay stays reproducible; a missing file excludes nothing.
    """
    out = []
    if exceptions_path and os.path.exists(exceptions_path):
        idx, tabs = [], []
        for ln in open(exceptions_path):
            if ln.startswith("#") or not ln.strip():
                continue
            _fn, at, table, size = ln.split()
            idx.append(int(at, 16))
            if table != "-":
                tabs.append((int(table, 16), int(size, 16)))
        if idx:
            out.append((min(idx), max(idx) + 12))
        if tabs:
            out.append((min(t for t, _ in tabs), max(t + s for t, s in tabs)))
    if jumptables_path and os.path.exists(jumptables_path):
        for ln in open(jumptables_path):
            if ln.startswith("#") or not ln.strip():
                continue
            _fn, table, count = ln.split()[:3]
            out.append((int(table, 16), int(table, 16) + 4 * int(count, 16)))
    return out


def strong_reference_starts(img, fns, lit=frozenset(), exclude=()):
    """(sorted starts, data-word subset): the addresses some *external* reference names as code.

    Three evidence classes, each one a reader can check in the image: a `jal`/`j` from inside a
    known function (a `j` only when it leaves that function), a code address in a table of code
    addresses *outside every function* (a vtable or function-pointer table: the word next to it
    is a code address too — a lone coincidence in rodata is not a table, and an instruction
    word that happens to equal an address is not a reference at all), and a literal the code
    forms (`lui`/`addiu`, `literal_code_addresses`). These bound the structural rules and seed
    the referenced-start rule; Ghidra's `LAB_` labels are not references and do not belong
    here. `exclude` lists the table ranges whose pointers are not entries (`non_entry_tables`).
    """
    calls = set()
    for va, sz, *_ in fns:
        for k in range(sz // 4):
            w = _word(img, va + 4 * k)
            if _is_jal(w):
                calls.add(_j_target(va + 4 * k, w))
            elif _is_j(w):
                t = _j_target(va + 4 * k, w)
                if not (va <= t < va + sz):
                    calls.add(t)
    body = img[:len(img) - len(img) % 4]
    words = [w for (w,) in struct.iter_unpack("<I", body)]
    is_code = [VADDR_BASE <= w < SECTION_HI and w % 4 == 0 for w in words]
    skip = bytearray(len(words))
    for lo, hi in list(exclude) + [(va, va + sz) for va, sz, *_ in fns]:
        for k in range(max(0, (lo - VADDR_BASE + FILE_BASE) // 4),
                       min(len(words), (hi - VADDR_BASE + FILE_BASE + 3) // 4)):
            skip[k] = 1
    data = set()
    for k, w in enumerate(words):
        if is_code[k] and not skip[k] and ((k > 0 and is_code[k - 1])
                                           or (k + 1 < len(words) and is_code[k + 1])):
            data.add(w)
    strong = sorted((calls | data | set(lit)) - {0})
    return strong, data


def load_gap_labels(path):
    """VAs of Ghidra's `LAB_*` labels — addresses it discovered but did not turn
    into function objects (see `promote_gap_labels`)."""
    syms = json.load(open(path)).get("symbols", [])
    out = set()
    for it in syms:
        a, n = it.get("address"), it.get("name", "")
        if a and n.startswith("LAB_"):
            try:
                out.add(int(a, 16))
            except ValueError:
                pass
    return sorted(out)


def promote_gap_labels(fns, img, labels, strong, strong_data):
    """Rule 1 — turn frame-opening `LAB_` labels in unclaimed gaps into functions.

    `data/functions.json` is Ghidra's *function* list, but Ghidra also records
    addresses it only knows as labels ("`LAB_x`") — branch targets and referenced
    stubs it never promoted to function objects. When nothing branches into one and
    nothing takes its address as code, it stays a label and lands in the unclaimed
    gap between two functions, so it is absent from `config/SLUS-20836/symbols.txt` and can
    never be decompiled. The 592 class-registrar trampolines were exactly this
: each alone in its own 116-404-byte gap with a `LAB_<addr>` at
    its `addiu sp,sp,-N`, e.g. `LAB_001301d0`.

    A gap label is promoted when it opens a frame (`addiu sp,sp,-N`), nothing falls
    into it (`_fresh_start`), and `_sweep_extent` finds the body: it ends at the
    first `jr ra`/`jr t9`/tail-call `j`/backward `b` that no branch of the body jumps
    over. The earlier form bounded a candidate at the next label *of any kind* and
    only accepted `jr ra`, so a function with an internal branch-target label, or
    one ending in a tail call, was dropped (106 + 76 cases in the inventory audit);
    the bound is now the next *referenced* start (`strong`), exactly as the leaf rule
    has always done. The gap after the last function is scanned like every other.
    Nothing is invented: every byte stays where it was, so the relink is unaffected.
    """
    cands = [L for L in labels if VADDR_BASE + 8 <= L < SECTION_HI and _is_prologue(_word(img, L))]
    return _promote_in_gaps(fns, img, cands, strong, strong_data, lambda va, size: True, min_size=16)


def promote_call_targets(fns, img, strong, strong_data, overlay=None):
    """Rule 3 — a `jal`/`j` target with no symbol is a function.

    A call from known code is the strongest evidence of a function start there is, and
    the one no label-driven pass could use: Ghidra's dump stopped at its own function
    objects, so a callee it never made one of (the inventory audit found 11 `jal` and 47
    tail-call targets) was linked as raw data and its callers' units went to
    `inventory-gap`. The candidates are the `strong` starts that come from calls; the
    body is whatever `_sweep_extent` finds, leaf or framed.
    """
    calls = set()
    for va, sz, *_ in fns:
        for k in range(sz // 4):
            w = _word(img, va + 4 * k)
            if _is_jal(w) or (_is_j(w) and not (va <= _j_target(va + 4 * k, w) < va + sz)):
                calls.add(_j_target(va + 4 * k, w))
    return _promote_in_gaps(fns, img, sorted(calls), strong, strong_data, lambda va, size: True,
                            overlay=overlay)


def promote_referenced_starts(fns, img, strong, strong_data, overlay=None):
    """Rule 4 — code a vtable, a function-pointer table or a literal points at.

    Same evidence the leaf rule (`promote_data_labels`) uses, without its two limits: the
    address need not carry a `LAB_` label, and the body may open a frame. A 3.6 KB
    vtable method with a 272-byte `sq` frame and 34 calls (0x3236a0) sat in a gap for
    want of this rule. The candidates are the table-context data words and the literals
    in `strong`; the body comes from `_sweep_extent`.
    """
    return _promote_in_gaps(fns, img, strong, strong, strong_data, lambda va, size: True,
                            overlay=overlay)


def _framed(img, va, size):
    """The body opens a frame of N and closes exactly that frame at its end: `addiu
    sp,sp,-N` first, `addiu sp,sp,N` in the delay slot of the final transfer or just
    before it. The symmetric frame is what makes an *unreferenced* body a function."""
    w = _word(img, va)
    if not _is_prologue(w):
        return False
    restore = 0x27BD0000 | ((-w) & 0xFFFF)
    return _word(img, va + size - 4) == restore or _word(img, va + size - 8) == restore


def promote_framed_bodies(fns, img, strong, strong_data):
    """Rule 5 — an unreferenced body that opens and closes its own frame.

    Static functions the linker kept although nothing calls them (EE GCC emits every
    function of a unit) have no label, no caller and no table entry, so no evidence-driven
    rule reaches them; four of the five tail-call wrappers the `cut` rows split off leave
    such a body behind. The shape is the evidence here, and it is strict: nothing falls
    into the start, the first word is `addiu sp,sp,-N`, every word is code-shaped, the
    sweep ends cleanly, and the final transfer restores exactly N. Candidates are every
    gap word that opens a frame.
    """
    cands = []
    prev_end = VADDR_BASE
    for va, sz, *_ in fns + [(SECTION_HI, 0)]:
        o = max(prev_end, VADDR_BASE + 8)
        while o + 8 <= va:
            if _is_prologue(_word(img, o)):
                cands.append(o)
            o += 4
        prev_end = max(prev_end, va + sz)
    return _promote_in_gaps(fns, img, cands, strong, strong_data,
                            lambda va, size: _framed(img, va, size), min_size=16)


def _is_end_word(word):
    """A branch that ends a function body: an unconditional `j` (a tail call) or a
    `jr` of any register — `jr ra` for a return, `jr t9`/`jr v0` for a tail call.

    `promote_gap_labels` only accepts `jr ra`, which is right for its non-leaf
    shapes but misses the leaf stub that tail-calls instead of returning; the two
    live in the same vtables (e.g. `igMetaField`'s `+0xd4` body 0x2fd1e0)."""
    if (word >> 26) == 2:                       # j
        return True
    return (word >> 26) == 0 and (word & 0x3F) == 8   # jr


def referenced_code_addresses(img, fns):
    """VAs in the code range that some 4-byte little-endian word in `img` equals.

    A code address held in a vtable or a function-pointer table is a *data*
    reference, and Ghidra follows branch and `jal` targets but not those, so a stub
    reached only from a vtable is never promoted to a function object. The word that points at it is the evidence that it is code; this is the
    set `promote_data_labels` uses in place of the frame prologue it cannot expect
    from a leaf.
    """
    body = img[:len(img) - len(img) % 4]
    return {w for (w,) in struct.iter_unpack("<I", body)
            if VADDR_BASE <= w < SECTION_HI}


def promote_data_labels(fns, img, labels):
    """Promote *leaf* `LAB_` gap labels — the ones a vtable points at.

    `promote_gap_labels` recognises a function by its frame (`addiu sp,sp,-N`), which
    every non-leaf function has and no leaf one does. That leaves a whole class
    behind: the hundreds of leaf stubs the class vtables are full of — the 8-byte
    `jr ra; li v0,N` getters, the 8-byte `jr ra; nop` default methods, the `lui at,hi;
    jr ra; lw v0,lo(at)` MetaObject accessors, the 12-byte bodies that tail-call a
    shared implementation with `j`. Ghidra knows each as a `LAB_` label but never
    made it a function, because nothing *branches* into it — only a vtable holds its
    address, and Ghidra does not follow that kind of reference.

    The evidence is the same in every case: the label sits in an unclaimed gap, its
    address appears as a word in the image (a code pointer), and the bytes from it
    form a leaf body — exactly one terminating `j`/`jr`, never a prologue, and not
    reachable by fallthrough (the preceding word is padding, or a `jr ra`/its delay
    slot). Its size runs to that terminator's delay slot; a sibling start bounds it.
    Nothing is invented and no existing symbol changes size, so the relink is
    unaffected — the bytes it claims were already linked as raw data (
    precedent).
    """
    refs = referenced_code_addresses(img, fns)
    out, added = [], 0
    for i, f in enumerate(fns):
        va, sz = f[0], f[1]
        out.append(f)
        gap_lo = va + sz
        gap_hi = fns[i + 1][0] if i + 1 < len(fns) else SECTION_HI
        if gap_hi <= gap_lo:
            continue
        inside = []
        j = bisect.bisect_left(labels, gap_lo)
        while j < len(labels) and labels[j] < gap_hi:
            inside.append(labels[j])
            j += 1
        # The plausible starts: referenced as code, leaf-shaped, and not a
        # fallthrough of whatever precedes them.
        starts = []
        for L in inside:
            off = L - VADDR_BASE + FILE_BASE
            if off < 12 or off + 4 > len(img) or L not in refs or L >= SECTION_HI:
                continue
            w, = struct.unpack_from("<I", img, off)
            if _is_prologue(w):
                continue                      # the other rule's shape
            p1, = struct.unpack_from("<I", img, off - 4)
            p2, = struct.unpack_from("<I", img, off - 8)
            if p1 == 0:
                # Padding — unless the zero is a branch's delay slot, which makes
                # the label a branch target inside another body, or a switch
                # dispatch's (`jr v1; nop`), which makes it the first case body.
                if is_terminator(p2) and (p2 >> 26) != 0:
                    continue
                if _is_jr(p2) and _rs(p2) not in (31, 25):
                    continue
            elif not (p1 == 0x03E00008 or p2 == 0x03E00008):
                continue
            starts.append(L)
        for k, L in enumerate(starts):
            # Bound by the next plausible start, not by the next label of any kind:
            # a function with an internal loop carries branch-target labels of its
            # own, and those must not cut its body short. Sibling stubs are
            # referenced like the first, so they do bound it.
            bound = starts[k + 1] if k + 1 < len(starts) else gap_hi
            off = L - VADDR_BASE + FILE_BASE
            ends = []
            o = off
            while o < off + (bound - L):
                w, = struct.unpack_from("<I", img, o)
                if _is_end_word(w):
                    ends.append(o)
                o += 4
            if len(ends) != 1:
                continue          # a merge of two stubs, or none at all: leave it
            size = (ends[0] + 8) - off
            if size < 8 or size > bound - L:
                continue
            if any(_is_prologue(struct.unpack_from("<I", img, off + 4 * m)[0])
                   for m in range(1, size // 4)):
                continue          # a nested non-leaf function: not a leaf body
            if not all(_code_shaped(struct.unpack_from("<I", img, off + 4 * m)[0])
                       for m in range(size // 4)):
                continue          # a referenced word in rodata, not a stub
            out.append((L, size, "FUN_%08x" % L, None))
            added += 1
    out.sort(key=lambda f: f[0])
    return out, added


def load_sdk_starts(path):
    """Function starts an SDK library descriptor declares (data/sdk-bindings.json).

    Eight descriptors sit in the image's rodata and one of them,
    `libdma`'s, carries a real function table. Those addresses are entry points by
    construction, which makes the table a **split oracle**: three of them are
    boundaries the tiling does not have, because Ghidra treats an unconditional
    tail-call `j` as fallthrough, so one function object swallowed the bodies after
    it.
    """
    if not path or not os.path.exists(path):
        return []
    data = json.load(open(path))
    out = set()
    for rec in data.get("descriptors", []):
        for e in rec.get("code_entries") or []:
            out.add(e["value"])
    return sorted(out)


def _clean_start(img, va):
    """True if nothing falls into `va` -- the only place this pass will cut.

    Two shapes count, both observed at the boundaries it splits: padding (a zero
    word that is nobody's delay slot), or a word following a completed return or an
    unconditional `j`. A `jal` immediately before does *not* count: its code
    resumes right here when it returns.
    """
    off = va - VADDR_BASE + FILE_BASE
    if off < 12 or va % 4:
        return False
    p1, = struct.unpack_from("<I", img, off - 4)
    p2, = struct.unpack_from("<I", img, off - 8)
    if p1 == 0:
        # a zero is padding only if it is not some branch's delay slot
        return not (is_terminator(p2) and (p2 >> 26) not in (0,))
    if p2 == 0x03E00008 and p1 not in (0,):        # jr ra; <delay slot>
        return True
    return (p2 >> 26) == 2                          # j <target>; <delay slot>


def _jr_ra_extent(img, va, stop):
    """Size of the body at `va` up to and including the first `jr ra`'s delay slot.

    `None` when there is no such return before `stop` or the body would run past it.
    """
    off = va - VADDR_BASE + FILE_BASE
    stop_off = stop - VADDR_BASE + FILE_BASE
    o = off
    while o + 8 <= stop_off:
        w, = struct.unpack_from("<I", img, o)
        if w == 0x03E00008:
            return (o + 8) - off
        o += 4
    return None


def promote_sdk_starts(fns, img, starts, refs):
    """Promote (and, where needed, split for) the starts a descriptor declares.

    This is the first pass that *shrinks* a symbol, so it moves carefully: it only
    cuts where `_clean_start` says the bytes ended a body just before, it only
    takes an unclaimed address whose value some 4-byte word in the image holds (the
    descriptor's own table), and it asserts that every byte the old symbol had is
    still in exactly one piece. `make check` is the backstop: it round-trips every
    byte of the image, so a cut in the middle of an instruction cannot survive.
    """
    starts = [s for s in starts if s in refs]
    out, added, splits = [], 0, 0
    for f in fns:
        va, sz = f[0], f[1]
        inside = [s for s in starts if va < s < va + sz]
        if not inside:
            out.append(f)
            continue
        good = [s for s in inside if _clean_start(img, s)]
        if not good:
            out.append(f)
            continue
        bounds = good + [va + sz]
        pieces = [(good[k], bounds[k + 1] - good[k]) for k in range(len(good))]
        remainder = (va, good[0] - va)
        assert remainder[1] + sum(s for _, s in pieces) == sz
        out.append(remainder + (f[2], f[3]))
        # The last piece inherits the swallowing symbol's end, and that end was Ghidra's guess for
        # a different function: `FUN_001044f0`'s loop and return lie 84 bytes past it. The body
        # walk gives the piece its own extent, growing only into the unclaimed gap that follows.
        nxt = next((g[0] for g in fns if g[0] > va), SECTION_HI)
        s, size = pieces[-1]
        walked = _sweep_extent(img, s, nxt)
        if walked is not None and walked > size:
            pieces[-1] = (s, walked)
        for s, size in pieces:
            out.append((s, size, "FUN_%08x" % s, None))
            added += 1
        splits += len(pieces)
    out.sort(key=lambda f: f[0])
    have = {f[0] for f in out}
    for s in starts:
        if s in have:
            continue
        j = bisect.bisect_right([f[0] for f in out], s) - 1
        if j >= 0 and out[j][0] + out[j][1] > s:
            continue                            # covered: the split above handled it
        stop = out[j + 1][0] if j + 1 < len(out) else s + 0x400
        if not _clean_start(img, s):
            continue
        size = _jr_ra_extent(img, s, stop)
        if not size or s + size > stop:
            continue
        out.append((s, size, "FUN_%08x" % s, None))
        added += 1
    out.sort(key=lambda f: f[0])
    return out, added, splits


def literal_code_addresses(img, fns):
    """VAs the *code* forms as an immediate (`lui` plus a completing low half).

    The second evidence class for a code pointer besides a data word. The class
    registrars pass their per-class accessor stub as the 9th argument, materialised
    with `lui t0,hi; addiu t0,t0,lo`, so the stub's own address is never a data word
    and `referenced_code_addresses` cannot see it. The
    resolution rules -- the low half usually lands in a call's delay slot, and a page
    is not an address -- live in tools/mips_literals.py, shared with the
    platform-boundary map. The search window has to be wider than the default:
    a registrar builds all nine arguments at once, so `lui t0,hi` and its completing
    `addiu t0,t0,lo` sit up to eleven instructions apart, past `scan_from_lui`'s
    default of eight. Nothing writes `rt` in between, which is
    what keeps the wider window honest -- raising it 9 -> 16 finds all 572 registrar
    thunks and saturates there.
    """
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import mips_literals as ml

    word = ml.make_word(img)
    out = set()
    for va, sz, *_ in fns:
        off = va - VADDR_BASE + FILE_BASE
        if off < 0 or off + sz > len(img):
            continue
        for k in range(sz // 4):
            ins, = struct.unpack_from("<I", img, off + 4 * k)
            if (ins >> 26) != 0x0F:
                continue
            rt = (ins >> 16) & 0x1F
            if rt == 0:
                continue
            for kind, addr in ml.scan_from_lui(word, va + 4 * k, ins & 0xFFFF, rt,
                                              window=16):
                if kind == "exact":
                    out.add(addr)
                break
    return out


def promote_j_thunks(fns, img, refs, names=None):
    """Promote `j <target>; nop` stubs in unclaimed gaps, and name them.

    The class registrars pass a function pointer per class, and for 572 classes
    that pointer is a two-instruction stub whose body jumps to the class's accessor
    (`j <accessor>; nop`). Ghidra never disassembled them and never made them
    functions, so no label-driven pass can see them; the call
    is indirect, so no `jal` reaches them either.

    Evidence is shape *and* reference: the stub's address is formed as a code literal
    (or held in a data word), the bytes there are exactly `j X; nop` with X an
    existing function, and the address is not inside any function. The name follows
    from the target, which is what the stub means. It sits in the middle of a data
    region rather than in an eight-byte gap between two functions, so a gap-skewed
    rule sees nothing -- the reference is what identifies it.
    """
    by_va = {f[0]: f[2] for f in fns}
    names = names or {}
    starts = [f[0] for f in fns]
    ends = [f[0] + f[1] for f in fns]
    out, added = [], 0
    for va in sorted(refs):
        if va % 4:
            continue
        i = bisect.bisect_right(starts, va) - 1
        if i >= 0 and va < ends[i]:
            continue                            # inside a function: not a stub
        off = va - VADDR_BASE + FILE_BASE
        if off < 0 or off + 8 > len(img):
            continue
        w, d = struct.unpack_from("<II", img, off)
        if (w >> 26) != 2 or d != 0:            # `j <target>` followed by a nop
            continue
        target = ((va + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
        if target not in by_va:
            continue
        nm = sanitize("thunk_" + names.get(target, (by_va[target],))[0])
        out.append((va, 8, nm, nm))
        added += 1
    out.extend(fns)
    out.sort(key=lambda f: f[0])
    return out, added


def load_names(path):
    """The curated name overlay -> {va: (name, module)}.

    Names live in the Ghidra project and reach the build as `data/functions.json`,
    which makes a naming change a Ghidra round-trip plus a regenerated dump — not a
    diff anyone can review.  The overlay is the same information as a committed
    file: an address given here replaces the dump's `FUN_<addr>`, so a name can be
    added and reviewed like any other source change.  It is merged over the dump,
    never instead of it: the dump still supplies every function the overlay does
    not name.

    `path` is a directory of `<Module>.tsv` files (one per module, the unit the
    work proceeds in) or a single file.  Columns are `<va>\t<name> [\t<module>]`;
    `#` comments and blank lines are skipped.  `name` may contain `::` (sanitised
    by the caller); `module` is the `src/` folder the unit belongs in
    (tools/apply_names.py moves it there).  An address may be named only once, so
    two modules disagreeing is an error rather than a silent last-wins.
    """
    if not path or not os.path.exists(path):
        return {}
    if os.path.isdir(path):
        files = [os.path.join(path, f) for f in sorted(os.listdir(path))
                 if f.endswith(".tsv")]
    else:
        files = [path]
    out, where = {}, {}
    for f in files:
        for ln in open(f):
            ln = ln.strip()
            if not ln or ln.startswith("#"):
                continue
            p = ln.split("\t") if "\t" in ln else ln.split()
            va = int(p[0], 0)
            name = p[1].strip()
            mod = p[2].strip() if len(p) > 2 else "unmatched"
            if va in out and out[va][0] != name:
                raise ValueError("%s names 0x%08x %s, %s names it %s"
                                 % (where[va], va, out[va][0], f, name))
            out[va] = (name, mod)
            where[va] = f
    return out


def dedupe(fixed):
    """(va, size, sanitised, original) -> names unique by appending `__<va>`."""
    counts = {}
    for _, _, nm, _o in fixed:
        counts[nm] = counts.get(nm, 0) + 1
    seen, result = {}, []
    for va, sz, nm, orig in fixed:
        if counts[nm] > 1:
            seen[nm] = seen.get(nm, 0) + 1
            if seen[nm] > 1:
                nm = "%s__%08x" % (nm, va)
        result.append((va, sz, nm, orig))
    names = [n for _, _, n, _ in result]
    assert len(names) == len(set(names)), "disambiguation failed"
    return result


def apply_overlay(fns, names):
    """Override each function's name from the overlay, then re-sanitise and dedupe.

    This runs **after** the gap-label promotion, not inside the dump loader: 592 of
    the registrars are not in `data/functions.json` at all (Ghidra never promoted
    them), so an overlay applied while loading the dump would silently skip exactly
    the functions it was written for.
    """
    if not names:
        return fns
    out = []
    for va, sz, nm, orig in fns:
        if va in names:
            orig = names[va][0]
            nm = sanitize(orig)
        out.append((va, sz, nm, orig))
    return dedupe(out)


def load_functions(path):
    """-> [(va, size, name, original)] sorted by va, names unique and C-safe.

    Two normalisations the dump needs before it can be built against:

    * **Sanitised names** — `::` and friends become `_` (see `sanitize`).
    * **Unique names** — the dump has repeated names at *distinct* addresses
      (SDK-style stubs such as `AddDmacHandler`, `RFU116_SetSyscall`). Left alone
      they would collide: one `asm/<name>.s` would overwrite another (losing code)
      and the assembler would see duplicate global labels. Repeats after
      sanitising get a `__<va>` suffix.
    """
    fns = json.load(open(path))["functions"]
    out = []
    for f in fns:
        try:
            va = int(f["address"], 0)
            sz = int(f.get("size") or 0)
        except (TypeError, ValueError):
            continue
        if sz > 0:
            out.append((va, sz, f["name"]))
    out.sort()
    return dedupe([(va, sz, sanitize(nm), nm) for va, sz, nm in out])


def disassemble_range(img, lo, hi):
    """Disassemble [lo, hi) in ONE objdump pass -> {va: (word, text)}.

    MIPS instructions are all 4 bytes, so a single linear pass from a 4-aligned
    start decodes every aligned address in the range: no drift, and no need for
    one subprocess per function (which is what makes 15k functions tractable).
    """
    import re
    with tempfile.NamedTemporaryFile(prefix="split_raw_", suffix=".bin") as raw:
        raw.write(va_bytes(img, lo, hi - lo))
        raw.flush()
        out = subprocess.run(
            ["mipsel-linux-gnu-objdump", "-D", "-b", "binary",
             "-m", "mips:5900", "-EL", "--adjust-vma", hex(lo), raw.name],
            capture_output=True, text=True).stdout
    table = {}
    for ln in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$", ln)
        if m:
            table[int(m.group(1), 16)] = (int(m.group(2), 16), m.group(3).strip())
    return table


def emit_asm(table, img, va, size, name, outdir, mnemonic_comments=True, original=None):
    path = os.path.join(outdir, name + ".s")
    title = "/* %s — 0x%08x, %d bytes. GENERATED by tools/split.py; do not edit." % (name, va, size)
    lines = [title]
    if original and original != name:
        lines.append(" * Ghidra name: %s" % original)
    lines.append(" * Retail bytes, reassembled verbatim so the undecompiled remainder links. */")
    lines += [
        "\t.section .text",
        "\t.globl %s" % name,
        "\t.align 2",   # 4-byte: 9 functions are 4- but not 8-byte aligned, so .align 3 would insert padding
        "%s:" % name,
    ]
    done = 0
    for off in range(0, size - size % 4, 4):
        addr = va + off
        word, text = table.get(addr, (struct.unpack_from("<I", va_bytes(img, addr, 4))[0],
                                     "(undecoded)"))
        cmt = ("  /* %08x: %s */" % (addr, text)) if mnemonic_comments else ""
        lines.append("\t.word 0x%08x%s" % (word, cmt))
        done = off + 4
    # a size that is not a multiple of 4 (rare) keeps its tail as raw words
    while done < size:
        w = struct.unpack_from("<I", va_bytes(img, va + done, 4))[0]
        lines.append("\t.word 0x%08x  /* %08x: (partial) */" % (w, va + done))
        done += 4
    lines.append("")
    with open(path, "w") as fh:
        fh.write("\n".join(lines))
    return path


STAMP = ".stamp"


def asm_key(elf, symbols, comments=True):
    """The identity of a generated asm/ tree: the retail image, the symbol map it lays out,
    this tool and the comment mode."""
    import hashlib
    key = hashlib.sha256(b"comments" if comments else b"no-comments")
    for path in (elf, symbols, os.path.abspath(__file__)):
        with open(path, "rb") as fh:
            key.update(hashlib.sha256(fh.read()).digest())
    return key.hexdigest()


def asm_current(out, elf, symbols, comments=True):
    """True when `out` holds exactly the tree this image, symbol map and tool generate: the
    stamp a full run leaves carries the key and the unit count."""
    try:
        with open(os.path.join(out, STAMP)) as fh:
            key, count = fh.read().split()
        units = sum(1 for name in os.listdir(out) if name.endswith(".s"))
        return key == asm_key(elf, symbols, comments) and units == int(count)
    except (OSError, ValueError):
        return False


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--functions", default=FUNCS_DEFAULT)
    ap.add_argument("--function-extents", default=EXTENTS_DEFAULT,
                    help="reviewed contiguous Ghidra spans, generated by dump_function_extents.py")
    ap.add_argument("--names", default=NAMES_DEFAULT,
                    help="curated name overlay (config/SLUS-20836/names/, one .tsv per module)")
    ap.add_argument("--gap-labels", default=LABELS_DEFAULT,
                    help="promote code-shaped LAB_ labels in gaps (data/symbols.json)")
    ap.add_argument("--no-gap-labels", dest="gap_labels", action="store_const", const=None,
                    help="skip the gap-label promotion")
    ap.add_argument("--sdk-starts", default=SDK_STARTS_DEFAULT,
                    help="function starts from the SDK descriptors (data/sdk-bindings.json);"
                         " the only input that can split an existing symbol")
    ap.add_argument("--no-sdk-starts", dest="sdk_starts", action="store_const", const=None,
                    help="skip the SDK-descriptor promotion")
    ap.add_argument("--symbols", action="store_true", help="(re)write config/SLUS-20836/symbols.txt")
    ap.add_argument("--symbols-only", action="store_true", help="stop after the symbols file")
    ap.add_argument("--extent-overrides", default=OVERRIDES_DEFAULT,
                    help="reviewed extent corrections of the dump (config/SLUS-20836/extent-overrides.tsv)")
    ap.add_argument("--symbols-out", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--out", default="asm")
    ap.add_argument("--limit", type=int, default=0, help="0 = all")
    ap.add_argument("--region", help="VA_LO,VA_HI")
    ap.add_argument("--no-comments", action="store_true")
    ap.add_argument("--ensure", action="store_true",
                    help="emit asm/ only when it is missing or stale (the image, the symbol map "
                         "or this tool changed since the last full run)")
    a = ap.parse_args(argv)

    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    os.chdir(root)

    if a.ensure and asm_current(a.out, a.elf, a.symbols_out, not a.no_comments):
        print("%s/: up to date" % a.out)
        return 0

    fns = load_functions(a.functions)
    fns = apply_function_extents(fns, a.function_extents)
    img = read_elf(a.elf)
    fns, grown = extend_delay_slots(fns, img)
    if grown:
        print("extended %d functions by one delay slot (Ghidra cut them short)" % grown)
    fns, jgrown, jadded = extend_jump_table_bodies(fns, img)
    if jgrown:
        print("extended %d switch dispatchers over their jump-table bodies (+%d bytes)"
              % (jgrown, jadded))
    # the default table describes the PS2 USA image only; other targets pass their own extents
    cuts = []
    if a.extent_overrides != OVERRIDES_DEFAULT or a.function_extents == EXTENTS_DEFAULT:
        fns, cuts = apply_extent_overrides(fns, img, a.extent_overrides)
        if cuts:
            print("cut %d functions the dump had glued to a neighbour (config/SLUS-20836/extent-overrides.tsv)"
                  % len(cuts))

    def summary(rule, added):
        if added:
            print("rule %s: promoted %d functions (%d bytes)" % (rule, len(added), sum(s for _, s in added)))

    # The structural rules bound every candidate at the next externally referenced start.
    # The label rules see the calls and tables of the Ghidra functions (plus the reviewed
    # extents); the later rules see those of the promoted functions too, and the literals
    # they form. Each set is a pure function of the image and the inputs before it, so a
    # replay reproduces the symbol table exactly.
    cfg = os.path.dirname(os.path.abspath(a.symbols_out))
    exclude = non_entry_tables(os.path.join(cfg, "exceptions.txt"),
                               os.path.join(cfg, "jumptables.txt"))
    overlay = load_names(a.names)
    strong, strong_data = strong_reference_starts(img, fns, exclude=exclude)
    if a.gap_labels is not None:
        labels = load_gap_labels(a.gap_labels)
        fns, dadded = promote_data_labels(fns, img, labels)
        if dadded:
            print("rule 2 referenced leaf LAB_ label in a gap: promoted %d functions" % dadded)
        fns, gadded = promote_gap_labels(fns, img, labels, strong, strong_data)
        summary("1 framed LAB_ label in a gap", gadded)
    refs = referenced_code_addresses(img, fns)
    if a.sdk_starts:
        starts = load_sdk_starts(a.sdk_starts)
        fns, sadded, ssplit = promote_sdk_starts(fns, img, starts, refs)
        if sadded:
            print("promoted %d SDK-descriptor starts (%d of them by splitting a function "
                  "Ghidra's tail-call fallthrough had swallowed)" % (sadded, ssplit))
    # A registrar's accessor stub is reached by `lui`/`addiu`, not by a data word, so
    # the literal form has to join the reference set for the stubs to be visible.
    lit = literal_code_addresses(img, fns)
    if lit:
        print("resolved %d code addresses formed as literals" % len(lit))
    fns, tadded = promote_j_thunks(fns, img, refs | lit, overlay)
    if tadded:
        print("promoted %d `j <target>; nop` stubs in unclaimed gaps" % tadded)
    # Rules 3-5 feed each other: a function rule 5 finds calls a stub only rule 3 can see, and a
    # body rule 3 adds forms literals that rule 4 needs. They run to a fixpoint, each round
    # recomputing the reference set from every function known so far; the rounds are a pure
    # function of the inputs, so the replay is unchanged by the iteration.
    cadded, radded, fadded = [], [], []
    while True:
        before = len(fns)
        strong, strong_data = strong_reference_starts(img, fns, lit, exclude)
        fns, c = promote_call_targets(fns, img, strong, strong_data, overlay)
        fns, r = promote_referenced_starts(fns, img, strong, strong_data, overlay)
        fns, f = promote_framed_bodies(fns, img, strong, strong_data)
        cadded, radded, fadded = cadded + c, radded + r, fadded + f
        if len(fns) == before:
            break
        lit = lit | literal_code_addresses(img, fns)
    summary("3 jal/j target without a symbol", cadded)
    summary("4 table/literal-referenced start", radded)
    summary("5 unreferenced framed body", fadded)
    check_cuts(fns, img, cuts)
    if a.region:
        lo, hi = (int(x, 0) for x in a.region.split(","))
        fns = [f for f in fns if lo <= f[0] < hi]
    # The overlay is merged last, over the fully assembled list, so it names the
    # gap-promoted functions too (592 of the class registrars are only ever born
    # in promote_gap_labels).
    fns = apply_overlay(fns, overlay)
    if a.symbols:
        os.makedirs(os.path.dirname(a.symbols_out) or ".", exist_ok=True)
        with open(a.symbols_out, "w") as fh:
            fh.write("# va size name — GENERATED by tools/split.py; do not edit.\n")
            fh.write("# %d functions, %d bytes of code\n"
                     % (len(fns), sum(f[1] for f in fns)))
            fh.write("# va size name [ghidra-name]  — name is sanitised for C/as; the\n"
                     "# 4th column is the original when it differs (e.g. Foo::vfunc_01 ->\n"
                     "# Foo__vfunc_01).\n")
            for va, sz, nm, orig in fns:
                extra = (" %s" % orig) if orig and orig != nm else ""
                fh.write("%08x %06x %s%s\n" % (va, sz, nm, extra))
        print("wrote %s: %d functions, %d bytes" % (a.symbols_out, len(fns),
                                                    sum(f[1] for f in fns)))
    if a.symbols_only:
        return 0

    os.makedirs(a.out, exist_ok=True)
    todo = fns[:a.limit] if a.limit else fns
    if not todo:
        return 0
    table = disassemble_range(img, todo[0][0], max(v + s for v, s, *_ in todo))
    n = 0
    for va, sz, nm, orig in todo:
        emit_asm(table, img, va, sz, nm, a.out, not a.no_comments, orig)
        n += 1
    print("wrote %d asm units to %s/" % (n, a.out))
    if not a.limit and not a.region:
        # A full run owns the folder: units of symbols that no longer exist go, and the stamp
        # records what the tree was generated from (`--ensure` compares it).
        current = {nm + ".s" for _va, _sz, nm, _orig in todo}
        stale = [name for name in os.listdir(a.out) if name.endswith(".s") and name not in current]
        for name in stale:
            os.remove(os.path.join(a.out, name))
        if stale:
            print("removed %d stale asm units" % len(stale))
        with open(os.path.join(a.out, STAMP), "w") as fh:
            fh.write("%s %d\n" % (asm_key(a.elf, a.symbols_out, not a.no_comments), len(current)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
