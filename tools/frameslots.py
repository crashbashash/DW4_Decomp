#!/usr/bin/env python3
"""frameslots.py — compare a candidate's stack frame with retail's, slot by slot.

A frame that differs (a slot 16 bytes higher, one local too many, two spills exchanged) says which
locals the source declares, in what order, and which of them live in memory; the instruction diff
shows the same thing only as scattered offsets (the idea is Persona 4 Decompilation's frame-slot
comparison; this is our own code). For one function this prints:

  * the frame size of each side (`addiu sp,sp,-N`);
  * the saved registers and their slots, compared by register;
  * every other slot (locals, spills, address-taken objects and outgoing arguments alike): its
    offset, the widest access, whether its address is taken (`addiu rX,sp,N`), and the index of the
    instruction that first touches it. Retail and candidate slots are paired by the aligned
    instructions that use them (a masked instruction alignment, tools/listing.py `token`), and what
    is left over by order of first use;
  * for the candidate, the source local behind each slot (`name+4` inside one), from the debug
    records b52 writes under `-g` (tools/listing.py `debug_records`; the `-g` body is checked to be
    the same code first; MWCC units only), and with `--registers` the register of every parameter
    and local in declaration order. Retail has no records, so a retail slot is named through its
    pair.

Lines marked `!!` differ: a slot at another offset (measured from the frame top when the frame
sizes differ, so one extra slot does not mark every other one), another width, address taken on one
side only, a slot without a pair, a first use away from where retail's aligns (`early`/`late`: the
candidate initialises or spills the slot at another point), or a saved register missing on one side.
The exit status is 1 when anything differs.

The candidate is compiled the way tools/check.py builds it (tools/project.py `compile_unit`: the
function's definition from the file under its translation unit's profile), so `--cand` takes a
whole-file unit or a one-function draft alike. Without `--cand`, the function's definition in
`src/` is used.

Usage:
  frameslots.py 0x2d9740 --cand build/drafts/SetSubPropertyValue.cpp
  frameslots.py igDriverDatabase_GetSubPropertyValue          # its definition in src/
"""
import argparse
import difflib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import listing  # noqa: E402

CALLEE_SAVED = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "fp", "ra"} | {
    "$f%d" % n for n in range(20, 32)} | {"f%d" % n for n in range(20, 32)}


class Slot:
    def __init__(self, offset):
        self.offset, self.first, self.width = offset, None, 0
        self.loads = self.stores = 0
        self.address_taken = False
        self.saved = None          # the callee-saved register this slot preserves

    def touch(self, index, width=0, store=None):
        self.first = index if self.first is None else min(self.first, index)
        self.width = max(self.width, width)
        if store is True:
            self.stores += 1
        elif store is False:
            self.loads += 1

    def kind(self):
        return "addr" if self.address_taken else "slot"


def frame(insns):
    """(frame size or None, {offset: Slot}) of one listing."""
    size = None
    if insns and insns[0].mnemonic in ("addiu", "daddiu"):
        parts = insns[0].operands.split(",")
        if parts[:2] == ["sp", "sp"] and parts[2].lstrip("-").isdigit() and int(parts[2]) < 0:
            size = -int(parts[2])
    first_branch = next((i for i, insn in enumerate(insns)
                         if insn.target is not None or insn.mnemonic in ("jal", "jalr", "jr")), len(insns))
    written = set()          # registers written so far, for "still holds the caller's value"
    slots = {}
    for i, insn in enumerate(insns):
        regs = listing.registers(insn)
        mem = listing.memory_operand(insn)
        if mem and mem[1] == "sp":
            slot = slots.setdefault(mem[0], Slot(mem[0]))
            store = insn.mnemonic in listing.STORES
            slot.touch(i, listing.WIDTHS[insn.mnemonic], store)
            reg = regs[0] if regs else None
            if store and reg in CALLEE_SAVED and reg not in written and i <= first_branch + 1 \
                    and slot.saved is None and slot.stores == 1 and not slot.loads:
                slot.saved = reg
            elif slot.saved and (reg != slot.saved or store):
                slot.saved = None       # touched by anything but its restore
        elif insn.mnemonic in ("addiu", "daddiu", "addu", "daddu") and len(regs) >= 2 and regs[1] == "sp" \
                and regs[0] != "sp":
            imm = insn.operands.rsplit(",", 1)[-1]
            offset = int(imm) if imm.lstrip("-").isdigit() else 0
            slot = slots.setdefault(offset, Slot(offset))
            slot.touch(i)
            slot.address_taken = True
            slot.saved = None
        if regs and insn.mnemonic not in listing.STORES and insn.target is None:
            written.add(regs[0])
    return size, slots


def alignment(retail, cand):
    """{retail index: candidate index} for the instructions the masked alignment calls equal."""
    r_tok, c_tok = [listing.token(x) for x in retail], [listing.token(x) for x in cand]
    out = {}
    for tag, i1, i2, j1, _j2 in difflib.SequenceMatcher(None, r_tok, c_tok, autojunk=False).get_opcodes():
        if tag == "equal":
            out.update((i1 + k, j1 + k) for k in range(i2 - i1))
    return out


def pair_slots(retail, cand, r_slots, c_slots, aligned):
    """{retail offset: candidate offset} for the non-save slots."""
    votes = {}
    for i, j in aligned.items():
        r, c = _slot_at(retail[i], r_slots), _slot_at(cand[j], c_slots)
        if r is not None and c is not None:
            votes[(r, c)] = votes.get((r, c), 0) + 1
    pairs, used = {}, set()
    for (r, c), _n in sorted(votes.items(), key=lambda kv: -kv[1]):
        if r not in pairs and c not in used:
            pairs[r] = c
            used.add(c)
    rest_r = sorted((s for s in r_slots.values() if not s.saved and s.offset not in pairs), key=lambda s: s.first)
    rest_c = sorted((s for s in c_slots.values() if not s.saved and s.offset not in used), key=lambda s: s.first)
    for r, c in zip(rest_r, rest_c):
        pairs[r.offset] = c.offset
    return pairs


def moved_first_use(r, c, aligned, slack=2):
    """'early'/'late' when the candidate first touches its slot away from where retail's first touch
    aligns (the nearest aligned instruction at or before it), else ''."""
    before = [i for i in aligned if i <= r.first]
    if not before:
        return ""
    i = max(before)
    expected = aligned[i] + (r.first - i)
    if c.first < expected - slack:
        return "early"
    if c.first > expected + slack:
        return "late"
    return ""


def _slot_at(insn, slots):
    mem = listing.memory_operand(insn)
    if mem and mem[1] == "sp" and mem[0] in slots and not slots[mem[0]].saved:
        return mem[0]
    regs = listing.registers(insn)
    if insn.mnemonic in ("addiu", "daddiu") and len(regs) >= 2 and regs[1] == "sp" and regs[0] != "sp":
        imm = insn.operands.rsplit(",", 1)[-1]
        return int(imm) if imm.lstrip("-").isdigit() else None
    return None


def slot_name(offset, records):
    """The candidate local stored at `offset` (`name+4` inside one), from the -g records."""
    if records is None:
        return ""
    best = None
    for var in records.variables:
        if var.location and var.location[0] == "sp" and var.location[1] <= offset:
            if best is None or var.location[1] > best.location[1]:
                best = var
    if best is None:
        return ""
    delta = offset - best.location[1]
    return best.name + ("+%d" % delta if delta else "")


def _cell(slot):
    return "%4d %s w%s" % (slot.offset, slot.kind(), slot.width or "-") if slot else "-"


def report(name, va, retail, cand, records, note, show_registers=False):
    r_size, r_slots = frame(retail)
    c_size, c_slots = frame(cand)
    from_top = r_size is not None and c_size is not None and r_size != c_size
    out = ["%s (0x%x): frame retail %s, candidate %s%s" % (
        name, va, r_size or "none", c_size or "none",
        "  !! %+d bytes; offsets compared from the frame top" % (c_size - r_size) if from_top else "")]
    bad = int(r_size != c_size)
    r_saved = {s.saved: s.offset for s in r_slots.values() if s.saved}
    c_saved = {s.saved: s.offset for s in c_slots.values() if s.saved}
    regs = sorted(set(r_saved) | set(c_saved), key=lambda r: -max(r_saved.get(r, -1), c_saved.get(r, -1)))
    cells = []
    for reg in regs:
        r, c = r_saved.get(reg), c_saved.get(reg)
        differs = r is None or c is None or (r_size - r if from_top else r) != (c_size - c if from_top else c)
        bad += differs
        cells.append("%s%s@%s/%s" % ("!!" if differs else "", reg, "-" if r is None else r, "-" if c is None else c))
    out.append("saved (retail/candidate): " + (" ".join(cells) if cells else "none"))
    aligned = alignment(retail, cand)
    pairs = pair_slots(retail, cand, r_slots, c_slots, aligned)
    rows = []
    for off, slot in r_slots.items():
        if slot.saved:
            continue
        c = c_slots.get(pairs[off]) if off in pairs else None
        rows.append((slot, c))
    paired = set(pairs.values())
    rows += [(None, s) for s in c_slots.values() if not s.saved and s.offset not in paired]
    rows.sort(key=lambda rc: (rc[0].first if rc[0] else 10 ** 6, rc[1].first if rc[1] else 10 ** 6))
    out.append("slots in retail order of first use (#n = instruction index):")
    out.append("     retail            candidate         first use         source (candidate -g)")
    for r, c in rows:
        moved = moved_first_use(r, c, aligned) if r and c else ""
        differs = r is None or c is None or r.width != c.width or r.address_taken != c.address_taken or (
            (r_size - r.offset if from_top else r.offset) != (c_size - c.offset if from_top else c.offset)) \
            or bool(moved)
        bad += differs
        out.append("  %s %-17s %-17s %-17s %s" % (
            "!!" if differs else "  ",
            _cell(r),
            _cell(c),
            "%s/%s%s" % ("#%d" % r.first if r else "-", "#%d" % c.first if c else "-",
                         " " + moved if moved else ""),
            slot_name(c.offset, records) if c else ""))
    if records is not None:
        in_frame = ["%s@%d" % (v.name, v.location[1]) for v in records.variables
                    if v.location and v.location[0] == "sp"]
        out.append("candidate locals in the frame, declaration order: %s" % (" ".join(in_frame) or "none"))
        if show_registers:
            out.append("candidate locals in registers, declaration order: %s" % " ".join(
                "%s=%s" % (v.name, v.location[1]) for v in records.variables
                if v.location and v.location[0] == "reg"))
    if note:
        out.append(note)
    out.append("%d mismatched slot%s" % (bad, "" if bad == 1 else "s"))
    return "\n".join(out), bad


def resolve_function(spec, symbols_path=listing.SYMBOLS):
    by_name, by_va = listing.symbols(symbols_path)
    if spec in by_name:
        return spec, by_name[spec][0]
    va = int(spec, 16)
    if va not in by_va:
        raise SystemExit("%s is not in %s" % (spec, symbols_path))
    return by_va[va][0], va


def source_of(name, cand):
    if cand:
        return cand
    import units
    path = units.scan(os.path.join(listing.ROOT, "src"), listing.SYMBOLS).get(name)
    if path is None:
        raise SystemExit("%s has no definition in src/; give --cand" % name)
    return path


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("function", help="retail VA (hex) or symbol")
    ap.add_argument("--cand", help="source holding the candidate definition (default: its file in src/)")
    ap.add_argument("--registers", action="store_true",
                    help="also list the candidate's register locals (from -g), declaration order")
    a = ap.parse_args(argv)
    name, va = resolve_function(a.function)
    try:
        cand, records, note = listing.compile_pair(name, source_of(name, a.cand))
    except ValueError as error:
        print("frameslots: %s" % error, file=sys.stderr)
        return 2
    text, bad = report(name, va, listing.retail_listing(va), cand, records, note, a.registers)
    print(text)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
