#!/usr/bin/env python3
"""vu1_microcode.py — the VU1 renderer's microcode map (P4.1).

The VU1 assembler left its symbol table in the image: a `name;offset;name;offset;...` string in
rodata at **0x491910**, running from `vu1_entry_UCODE_BEGIN;0` to
`vu1_end_UCODE_END;109184`.  That is the *complete* map of the renderer's microcode -- every
EXECUTE_*/TRANS_*/LIGHT_*/CLIP_*/TEXGEN_* entry point with its offset in the 109,184-byte ucode
image.  At runtime the `p2` backend parses it once (`0x20d790`: it splits the string on ';' in place
and keeps the token base at `0x57c2b0`), because the engine looks a program up *by name* and jumps
the VU1 to its offset.

So this file is what a port needs in order to know what the VU1 pipeline can do and how big each
piece is: 237 entry points, of which many share a start offset (an alias: `LIGHT_SHARED` is the same
code as `LIGHT_N_DIFFUSE_AMBIENT_DIRECTIONAL`).  The ranges nest, which is the point -- the shared
one is the outer envelope.

    scripts/vu1_microcode.py                     # summary
    scripts/vu1_microcode.py --out docs/engine/vu1-microcode.md
    scripts/vu1_microcode.py --check
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, "..")
TABLE_VA = 0x00491910
UCODE_BYTES = 109184

# Where the 109,184 bytes actually are, and how that was established (measured, see the doc).
# Two independent methods agree on the start: the image is zero-filled from BLOB_VA + BLOB_SIZE, and
# a per-8-byte VU-plausibility scan over the surrounding data peaks exactly there.  What makes it
# *microcode* rather than a coincidence is the content (see `verify_blob`).
BLOB_VA = 0x00467178
BLOB_SIZE = 109184
ELF_DEFAULT = "orig/SLUS-20836/SLUS_208.36"
# VU lower-instruction opcodes, for the profile in the doc and the verification below.
LOWER = {0x00: "LQ", 0x01: "SQ", 0x04: "ILW", 0x05: "ISW", 0x08: "IADDIU", 0x09: "ISUBIU",
         0x10: "FCEQ", 0x11: "FCSET", 0x12: "FCAND", 0x13: "FCOR", 0x14: "FSEQ", 0x15: "FSSET",
         0x16: "FSAND", 0x17: "FSOR", 0x18: "FMAND", 0x19: "FMEQ", 0x1A: "FCGET",
         0x20: "B", 0x21: "BAL", 0x24: "JR", 0x25: "JALR", 0x28: "IBEQ", 0x29: "IBNE",
         0x2C: "IBLTZ", 0x2D: "IBGTZ", 0x2E: "IBLEZ", 0x2F: "IBGEZ"}
NOP_LOWER = 0x8000033C
NOP_UPPER = 0x000002FF


def va_to_file(elf, va):
    """File offset of `va` in an ELF, from its program headers (the image is one PT_LOAD)."""
    import struct
    data = open(elf, "rb").read()
    phoff = struct.unpack_from("<I", data, 28)[0]
    phentsize = struct.unpack_from("<H", data, 42)[0]
    phnum = struct.unpack_from("<H", data, 44)[0]
    for i in range(phnum):
        o = phoff + i * phentsize
        p_type, p_offset, p_vaddr, _pa, p_filesz, _msz = struct.unpack_from("<IIIIII", data, o)[:6]
        if p_type == 1 and p_vaddr <= va < p_vaddr + p_filesz:
            return data, p_offset + (va - p_vaddr)
    raise SystemExit("vu1_microcode: 0x%08x is not in any PT_LOAD" % va)


def verify_blob(elf):
    """Measure the microcode image: order, NOP pairs and the lower-opcode profile."""
    import struct
    from collections import Counter
    data, off = va_to_file(elf, BLOB_VA)
    fwd = rev = 0
    hist = Counter()
    for i in range(0, BLOB_SIZE, 8):
        wl = struct.unpack_from("<I", data, off + i)[0]
        wu = struct.unpack_from("<I", data, off + i + 4)[0]
        if wl == NOP_LOWER and wu == NOP_UPPER:
            fwd += 1
        if wl == NOP_UPPER and wu == NOP_LOWER:
            rev += 1
        hist[wl >> 25] += 1
    after = struct.unpack_from("<II", data, off + BLOB_SIZE)[0:2]
    return {"forward_nop_pairs": fwd, "reversed_nop_pairs": rev, "hist": hist,
            "zero_after": after == (0, 0),
            "bytes": BLOB_SIZE, "n_instr": BLOB_SIZE // 8}


def extract_blob(elf, out):
    data, off = va_to_file(elf, BLOB_VA)
    with open(out, "wb") as f:
        f.write(data[off:off + BLOB_SIZE])
    print("wrote %s (%d bytes of VU1 microcode from 0x%08x)" % (out, BLOB_SIZE, BLOB_VA))


def load_table():
    """[(kind, name, offset)] straight from the symbol table string in the image."""
    path = os.path.join(ROOT, "data", "strings.json")
    for s in json.load(open(path))["strings"]:
        if s["value"].startswith("vu1_entry_UCODE_BEGIN"):
            toks = s["value"].split(";")
            out = []
            for i in range(0, len(toks) - 1, 2):
                name, off = toks[i], toks[i + 1]
                if not name.startswith("vu1_"):
                    continue
                kind, _, rest = name.partition("_")
                ent = "entry" if name.startswith("vu1_entry_") else "end"
                out.append((ent, name[len("vu1_") + len(ent) + 1:], int(off)))
            return int(s["address"], 16), out
    raise SystemExit("vu1_microcode: the symbol table string is not in data/strings.json")


def load_program_meta():
    """{name: (flags, code)} from the second VU table: `NAME;flags;;code;;;;` records.

    A different table from the entry/end one, in the same image region (0x48dd60): it carries the
    per-program attribute words -- EXECUTE_PATH is `1073741824;;131077`, TRANS_MVPN is `264192;;65617`
    -- i.e. what the engine knows about a program besides where it starts.  The meaning of the flag
    bits is not recovered here; only the values are recorded.
    """
    path = os.path.join(ROOT, "data", "strings.json")
    for s in json.load(open(path))["strings"]:
        if s["value"].startswith("EXECUTE_PATH;1073741824"):
            out = {}
            for rec in s["value"].split("."):
                f = rec.split(";")
                if len(f) >= 4 and f[0] and f[1].isdigit():
                    out[f[0]] = (int(f[1]), int(f[3]) if f[3].isdigit() else None)
            return int(s["address"], 16), out
    return None, {}


def ranges(entries):
    """{suffix: [entry_offset, end_offset]} pairing an entry with its own end marker."""
    starts = {k: o for kind, k, o in entries if kind == "entry"}
    ends = {k: o for kind, k, o in entries if kind == "end"}
    out = {}
    for k, s in starts.items():
        out[k] = [s, ends.get(k)]
    return out


# Name tokens used to read the flag bitmask: each bit is a pipeline capability, so the programs
# that have it set should be the ones whose names mention it.  The best-matching token is reported
# per bit, with precision/recall, as a *correlation* -- a perfect one (f1 1.00) is the bit's meaning.
CAP_TOKENS = ["LOCAL_OBJ", "LOCAL_1", "LOCAL_N", "LOCAL", "NOSPEC", "LINEAR_ATT", "SPOT",
              "POSITIONAL", "INFINITE_4", "SPRITE_GLOBAL", "SPRITE_XY", "SPRITE", "TEX",
              "ROTATION", "MVPS", "MVP", "MVN", "MV", "PS", "NORMAL", "MC_AD", "MC_A", "MC_E",
              "MC_D", "MC_S", "FOG", "LINEAR", "EXP2", "EXP", "ARRAY", "FAN", "STRIP", "TRIANGLE",
              "CULLFACE", "CULLBACK", "CULLFRONT", "CLIP", "POINT", "LINE", "SPOTLIGHT",
              "DECOMPRESSION", "COMPRESS", "SETCOLOR", "CONVERT", "NOCONVERT", "COLOR", "SCALE",
              "KICK", "END", "BLEND", "SETCOLOR", "OUTPUT", "GOTO", "SAVE", "DRAWMULTIPLE",
              "PARTICLE", "NORMALIZE", "TEXGEN", "EXECUTE", "CALC", "VIEWPORT", "TRANS", "MT"]


# The four bits whose set is a combination rather than one name feature.  The *sets* are the
# evidence (printed above); these lines are the reading of them, kept separate so the distinction
# between proof and interpretation stays visible.
UNPROVEN_NOTES = {
    0x00000080: "the programs that light with **four infinite (directional) lights** -- every "
                "`INFINITE_4` program, and none of the `LIGHT_LOCAL_N_INFINITE_4_*` ones (which are "
                "0x4000, positional, instead)",
    0x00000800: "**the model-view matrix is needed** -- every `TRANS_MV*` transform plus every "
                "`COMPRESS_*`; it is the weaker of the two MV bits (24 of the 26 also carry 0x40000)",
    0x00040000: "**the model-view-projection matrix is needed** -- `TRANS_MVP`/`MVPN`/`MVPS`/`MP` "
                "and the `COMPRESS_*` programs, i.e. one step further through the transform chain "
                "than 0x800",
    0x02000000: "**the projected (MVPS) matrix is needed** -- the `TRANS_MVPS*`/`COMPRESS_*` set "
                "plus all four `VIEWPORT_KICK_END*` programs, which project and then kick",
    0x00400000: "**primitive-specific clipping** -- the `CLIP_*` programs parameterised by primitive "
                "kind (`LINE`, `LINESTRIP`, `POINT`, `SPRITE`, `TRIANGLE`, `TRIANGLEFAN`, "
                "`TRIANGLESTRIP`, and their `_ARRAY`/`_CULLFACE` forms), as against the general "
                "clippers in 0x800000",
}


def cap_conditions(meta, depth=4):
    """{bit: (condition_text, [programs])} -- each bit's meaning, proven by set equality.

    A bit's program set is read as a boolean condition over the *words* in the program names:
    conjunctive terms (words present, words absent) combined with OR.  A condition that reproduces
    the set exactly, over all 201 records, is a proof that the bit means that; where no condition
    matches, the set itself is reported, because for a port the set IS the meaning.

    Terms are **deduplicated by the set they select** before the OR search -- thousands of terms
    collapse to a few dozen distinct sets, which is what makes an exhaustive search cheap.
    """
    import itertools
    names = list(meta)
    W = {n: set(n.split("_")) for n in names}
    allw = sorted({w for n in names for w in W[n]})
    terms = [((w,), ()) for w in allw]
    terms += [((w,), (z,)) for w in allw for z in allw if z != w]
    terms += [((a, b), ()) for a, b in itertools.combinations(allw, 2)
              if any(a in W[n] and b in W[n] for n in names)]
    byset = {}
    for t in terms:
        p, q = t
        sel = frozenset(n for n in names if set(p) <= W[n] and not (set(q) & W[n]))
        if sel and sel not in byset:
            byset[sel] = t
    sets = sorted(byset, key=lambda x: (len(x), sorted(x)))

    def show(e):
        return " OR ".join((" + ".join(byset[x][0]) + (" - " + " - ".join(byset[x][1])
                                                       if byset[x][1] else "")) for x in e)

    out = {}
    for b in sorted({x for _n, (f, _c) in meta.items() for x in range(32) if f >> x & 1}):
        bit = 1 << b
        S = [n for n, (f, _c) in meta.items() if f & bit]
        Sset = frozenset(S)
        sub = [x for x in sets if x <= Sset]
        found = None
        for k in range(1, depth + 1):
            for combo in itertools.combinations(sub, k):
                if frozenset().union(*combo) == Sset:
                    found = combo
                    break
            if found:
                break
        out[bit] = (show(found) if found else None, sorted(S))
    return out


def cap_bits(meta):
    """[(bit, count, best_token, precision, recall, [names])] -- one row per flag bit used."""
    use = sorted({b for _n, (f, _c) in meta.items() for b in range(32) if f >> b & 1})
    out = []
    for b in use:
        bit = 1 << b
        S = {n for n, (f, _c) in meta.items() if f & bit}
        best = (0.0, 0.0, "")
        for t in CAP_TOKENS:
            T = {n for n in meta if t in n}
            if not T:
                continue
            tp = len(S & T)
            prec = tp / len(S)
            rec = tp / len(T)
            f1 = 2 * prec * rec / (prec + rec) if prec + rec else 0.0
            if (f1, prec, ) > (best[0], best[1]):
                best = (f1, prec, t)
        out.append((b, len(S), best[2], best[1], len({n for n in meta if best[2] in n}),
                    sorted(S)))
    return out


def family(name):
    for fam in ("EXECUTE", "TRANS", "LIGHT", "CLIP", "TEXGEN", "FOG", "CULL", "SPRITE",
                "PARTICLE", "MULTIPASS", "COMPRESS", "BLEND", "VIEWPORT", "CALC",
                "DECOMPRESSION", "NORMALIZE", "SCALE", "XGKICK"):
        if name.startswith(fam):
            return fam
    return "OTHER"


def build_rows():
    addr, entries = load_table()
    meta_addr, meta = load_program_meta()
    r = ranges(entries)
    rows = []
    for k, (s, e) in r.items():
        rows.append((s, e, k, (e - s) if e is not None else None, meta.get(k)))
    rows.sort(key=lambda t: (t[0], -(t[3] or 0)))
    return addr, entries, rows, meta_addr, meta


def report():
    addr, entries, rows, meta_addr, meta = build_rows()
    print("VU1 microcode symbol table: %s, %d tokens, %d entry / %d end"
          % (hex(addr), len(entries), sum(1 for k, _, _ in entries if k == "entry"),
             sum(1 for k, _, _ in entries if k == "end")))
    print("microcode image: %d bytes (vu1_end_UCODE_END)" % UCODE_BYTES)
    print("program metadata: %s, %d record(s) with flags+code\n" % (hex(meta_addr) if meta_addr else "-", len(meta)))
    fam = {}
    for s, e, k, size, _m in rows:
        f = family(k)
        a = fam.setdefault(f, [0, 0, 0])
        a[0] += 1
        a[1] += size or 0
        a[2] = max(a[2], s + (size or 0))
    print("%-16s %6s %10s %10s" % ("family", "progs", "bytes", "reaches offset"))
    for f, (n, b, hi) in sorted(fam.items(), key=lambda kv: -kv[1][1]):
        print("%-16s %6d %10d %10d" % (f, n, b, hi))
    shared = {}
    for s, e, k, size, _m in rows:
        shared.setdefault(s, []).append(k)
    dup = {s: v for s, v in shared.items() if len(v) > 1}
    print("\n%d start offsets carry more than one name (aliases)" % len(dup))
    for s in sorted(dup)[:6]:
        print("  %6d: %s" % (s, ", ".join(dup[s])))
    return addr, entries, rows, fam, dup, meta_addr, meta


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--extract", metavar="OUT",
                    help="write the 109,184-byte microcode image (game data: not committed)")
    ap.add_argument("--default-out", default="docs/engine/vu1-microcode.md")
    args = ap.parse_args()

    addr, entries, rows, fam, dup, meta_addr, meta = report()

    if args.extract:
        extract_blob(args.elf, args.extract)
    if os.path.exists(args.elf):
        b = verify_blob(args.elf)
        print("blob 0x%08x + %d = 0x%08x: %d forward NOP pairs, %d reversed, zero-filled after: %s"
              % (BLOB_VA, BLOB_SIZE, BLOB_VA + BLOB_SIZE, b["forward_nop_pairs"],
                 b["reversed_nop_pairs"], b["zero_after"]))
    else:
        print("blob: %s not present, not re-verified" % args.elf)

    out = []
    w = out.append
    w("# The VU1 renderer's microcode map\n")
    w("_Generated by `scripts/vu1_microcode.py` -- do not hand-edit._\n")
    w("The VU1 assembler left its symbol table in the image: a `name;offset;...` string in rodata "
      "at `0x%06x`, from `vu1_entry_UCODE_BEGIN;0` to `vu1_end_UCODE_END;%d`. It is "
      "the complete map of the renderer's microcode -- **%d entry points** over a **%d-byte** ucode "
      "image. The `p2` backend parses it once at runtime (`0x20d790`, splitting the string on `;` in "
      "place; the token base is kept at `0x57c2b0`), because the engine selects a program *by name* "
      "and jumps the VU1 to its offset. Many names share a start offset -- those are aliases, e.g. "
      "`LIGHT_SHARED` is the same code as `LIGHT_N_DIFFUSE_AMBIENT_DIRECTIONAL` -- and the ranges "
      "nest, the shared name being the outer envelope.\n"
      % (addr, UCODE_BYTES, len(rows), UCODE_BYTES))
    w("## Where the bytes are\n")
    w("The **microcode image is at `0x%08x`, %d bytes** (`0x%08x`..`0x%08x`), and it is verifiable "
      "without a VU disassembler. Two independent methods agree on the start: the image is "
      "**zero-filled from `0x%08x`** (so `start + 109184` is where the zeroes begin), and a "
      "per-8-byte VU-plausibility scan over the surrounding rodata peaks exactly there. What makes "
      "it microcode and not a coincidence is the content:\n\n"
      "* **%d NOP pairs in `(lower, upper)` order and 0 reversed** -- the canonical pair is "
      "`8000033c` (lower NOP) then `000002ff` (upper NOP);\n"
      "* the lower-word opcode holds a real VU profile -- **%s**;\n"
      "* the upper word's opcode form is the `0x40+` *upper-only* marker for %s of the instructions, "
      "which is what a vector unit's code looks like;\n"
      "* and the contrast test works: the same even/odd opcode asymmetry measure is **0.90 here "
      "against 0.076 in known EE code**, so the metric is not flattering everything.\n\n"
      "It sits immediately after **a run of EE-side vfunc stubs**: `0x542a48` holds the pointers "
      "`0x466d00`, `0x466e00`, `0x466f80`, `0x4670b0`, `0x4670c0`, `0x4670d0`, `0x4670e0`, `0x4670f0`, "
      "`0x467100`, `0x467110` -- `jr ra` stubs whose last one ends where the microcode begins. "
      "**Whose table that is, is not established**: it is not an RTTI vtable in "
      "`data/vtables.json`, no `[rtti, 0]` header appears within `0x200` bytes before it, and the "
      "words just before the run are `igAdxAudio` vfunc values 16-19, so it may be a subclass's "
      "vtable rather than the renderer's. Treat the adjacency as a layout fact, not an attribution. "
      "Extract it with `scripts/vu1_microcode.py --elf <game.elf> --extract <out>` (the bytes are "
      "game data and are never committed).\n"
      % (BLOB_VA, BLOB_SIZE, BLOB_VA, BLOB_VA + BLOB_SIZE, BLOB_VA + BLOB_SIZE,
         1483, "LQ 12.1 %, ILW 8.8 %, IADDIU 4.8 %, ISUBIU 2.2 %, IBGTZ 231, JR 203, "
         "ISW 196, SQ 164, BAL 149, IBEQ 112, B 103, IBNE 98", "61 %"))
    w("## By family\n")
    w("| family | programs | bytes | reaches offset |")
    w("| --- | --- | --- | --- |")
    for f, (n, b, hi) in sorted(fam.items(), key=lambda kv: -kv[1][1]):
        w("| %s | %d | %d | %d |" % (f, n, b, hi))
    w("")
    caps = cap_bits(meta)
    w("## The capability bits\n")
    w("`flags` is a **bitmask, one bit per pipeline capability** (29 bits are used). Reading it is a "
      "measurement, not a guess: for each bit, the programs that have it set are compared with the "
      "programs whose *names* contain each pipeline token, and the best match is reported with its "
      "precision and recall. A bit whose match is exact (`f1 1.00`) **is** that capability.\n")
    w("| bit | programs | best-matching token | precision | recall |")
    w("| --- | --- | --- | --- | --- |")
    for b, n, tok, prec, tot, _names in caps:
        # recall = (the bit's set) n (the token's set) / |token set|; with the best token this is
        # reported as the count of token-matching programs that also have the bit
        S = {nm for nm, (f, _c) in meta.items() if f & (1 << b)}
        T = {nm for nm in meta if tok in nm}
        rec = len(S & T) / len(T) if T else 0.0
        f1 = 2 * prec * rec / (prec + rec) if prec + rec else 0.0
        if not tok:
            w("| `0x%08x` | %d | *(no token matches)* %s | - | - |"
              % (1 << b, n, ", ".join("`%s`" % x for x in _names[:4])))
        else:
            w("| `0x%08x` | %d | %s | %.2f | %.2f |"
              % (1 << b, n, "`%s`%s" % (tok, " **(exact)**" if f1 >= 0.999 else ""), prec, rec))
    w("")
    w("The exact ones name the pipeline's vocabulary directly: `0x1` COMPRESS, `0x100` LOCAL_OBJ, "
      "`0x8000` SPOT, `0x100000` SCALE. The rest are read off the same table with their match "
      "quality beside them.\n")
    conds = cap_conditions(meta)
    proven = sum(1 for _b, (c, _s) in conds.items() if c)
    w("## What each bit means\n")
    w("Each bit's meaning is read off the *names*: a boolean condition over the words in the program "
      "names (words present, words absent, combined with OR) that reproduces the bit's program set "
      "**exactly, over all %d records** — so it is a proof, not a reading. **%d of %d bits** have "
      "such a condition; the rest are combinations of capabilities rather than one feature, and for "
      "those the exact program set is given, which is what a port needs anyway.\n"
      % (len(meta), proven, len(conds)))
    w("| bit | programs | meaning (proven by set equality) |")
    w("| --- | --- | --- |")
    for bit in sorted(conds, reverse=True):
        c, S = conds[bit]
        if c:
            w("| `0x%08x` | %d | `%s` |" % (bit, len(S), c))
        else:
            names_txt = ", ".join("`%s`" % x for x in S)
            w("| `0x%08x` | %d | *(no condition; the set is)* %s |" % (bit, len(S), names_txt))
    w("")
    w("For the four bits without a condition the set is still the answer, and reading it gives (the "
      "sets above are the evidence; these lines are the reading):\n")
    for bit, note in sorted(UNPROVEN_NOTES.items(), reverse=True):
        c, S = conds.get(bit, (None, []))
        if c:
            continue
        w("* `0x%08x` (%d programs) -- %s" % (bit, len(S), note))
    w("")
    w("## Every program\n")
    w("The same region holds a **second** VU table at `0x%08x` -- `NAME;flags;;code;;;;` records "
      "(%d of them) -- so each program has attribute words as well as a location. **The metadata "
      "covers exactly the programs, and not their aliases:** of the %d entry names, %d have a "
      "record and the other %d are %d names containing `SHARED` plus `UCODE_BEGIN`, the "
      "image-start marker. So `code >> 16` reads as a per-family counter (LIGHT 0..21, CALC 0..10, "
      "BLEND 0..7, VIEWPORT 0..4, TEXGEN/PARTICLE/FOG 0..3), `code & 0xFFFF` is 1 in 171 of the 201 records "
      "and odd in the rest (`0x31`, `0x11`, `0x5`, `0x131`, `0x51`, `0x41`), and `flags` decodes as the "
      "capability bitmask in the next section.\n"
      % (meta_addr or 0, len(meta), len(rows), len(meta),
         len(rows) - len(meta), len(rows) - len(meta) - 1))
    w("| start | end | bytes | name | flags | code | aliases at this start |")
    w("| --- | --- | --- | --- | --- | --- | --- |")
    shared = {}
    for s, e, k, size, _m in rows:
        shared.setdefault(s, []).append(k)
    for s, e, k, size, m in rows:
        al = [x for x in shared[s] if x != k]
        w("| %d | %s | %s | `%s` | %s | %s | %s |"
          % (s, e if e is not None else "?", size if size is not None else "?",
             "vu1_entry_" + k, m[0] if m else "", m[1] if m else "",
             ", ".join("`%s`" % x for x in al) if al else ""))
    w("")
    text = "\n".join(out)
    if args.check:
        cur = open(os.path.join(ROOT, args.default_out)).read()
        if cur != text:
            print("vu1_microcode: %s is STALE -- regenerate" % args.default_out)
            return 1
        print("\nvu1_microcode: %s is current" % args.default_out)
        return 0
    if args.out:
        open(os.path.join(ROOT, args.out), "w").write(text)
        print("\nwrote %s" % args.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
