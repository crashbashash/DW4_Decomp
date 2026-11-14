#!/usr/bin/env python3
"""residual_census.py — find matched functions whose retail code has the shape a candidate misses.

Before a residual is called a floor, look for the same shape in code that already matches: if a
matched function's retail instructions contain the window a candidate gets wrong, that function's C
is a spelling that produces it under some profile, and often under this one. The search runs on
masked shapes (tools/listing.py `token`: the mnemonic, `.sp`/`.gp` on a load or store through the
frame or small-data base, `<`/`>` on a branch backwards or forwards, a constant shift's amount;
registers and other immediates dropped), so it finds the construct, not the function. The ideas are
Persona 4 Decompilation's signature census and dotr-decomp's call-similarity donor search; this is
our own code.

Steps, for one function:

  1. The residual. The candidate is compiled as tools/check.py builds it (tools/project.py
     `compile_unit`), and its masked listing is aligned with retail's (difflib, no junk heuristic).
     Every region the alignment does not call equal is a hunk; so is a run of aligned instructions
     whose registers differ (`reg` hunks, listed by offset and censused only with `--registers`).
     Hunks two or fewer instructions apart are merged (`mixed` when the kinds differ). Without
     `--cand`, `--at OFF[:N]` names a retail window instead (hex bytes from the function start, N
     instructions, default 8), for a function with no draft.
  2. The signature: the masked retail tokens of the hunk with `--context` instructions either side
     (default 3). `--registers` adds each instruction's registers renamed by first appearance in the
     window, which is what a `reg` hunk needs.
  3. The census: every function `data/check-categories.tsv` files as `match` and `src/` defines is
     read from the split's `asm/` and searched for the signature. When the full window has no hit,
     the context is narrowed one instruction at a time and the width that first hits is reported;
     a hunk longer than `--width` (default 6) with no hit even bare is censused again in pieces of
     that width. Zero hits for a short window sends the work back to control flow and the call ABI.
  4. The hits, ranked: same source file, then same compiler and flags (config/SLUS-20836/units.tsv),
     then the rest, each with the definition's `file:line` and the window's offset. `--lines`
     compiles the shown hits with `-g` and prints the source lines behind the window
     (tools/listing.py `debug_records`); a line outside the definition came from an inline.

`--calls` is the call-sequence census instead: the functions whose sequence of callees is most like
the target's retail one (difflib ratio over callee names; `jalr` counts as `*`), for a function with
no draft at all.

Usage:
  residual_census.py 0x32f7f0 --cand build/drafts/ThreadEntry.cpp
  residual_census.py 0x2d9740 --cand build/drafts/SetSubPropertyValue.cpp --registers --lines
  residual_census.py 0x2d7280 --at 0x380:10
  residual_census.py 0x2d7280 --calls
"""
import argparse
import difflib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import listing  # noqa: E402

CATEGORIES = os.path.join(listing.ROOT, "data", "check-categories.tsv")
UNITS = os.path.join(listing.ROOT, "config", "SLUS-20836", "units.tsv")


# ---- the residual ------------------------------------------------------------------------------
def hunks(retail, cand):
    """[(kind, retail i1, i2, candidate j1, j2)]: the regions the masked alignment does not call equal,
    and the runs of aligned instructions whose registers differ (kind `reg`)."""
    r_tok, c_tok = listing.shape(retail), listing.shape(cand)
    out = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, r_tok, c_tok, autojunk=False).get_opcodes():
        if tag != "equal":
            out.append((tag, i1, i2, j1, j2))
            continue
        run = None
        for k in range(i2 - i1):
            same = listing.registers(retail[i1 + k]) == listing.registers(cand[j1 + k])
            if not same and run is None:
                run = k
            if run is not None and (same or k == i2 - i1 - 1):
                end = k if same else k + 1
                out.append(("reg", i1 + run, i1 + end, j1 + run, j1 + end))
                run = None
    return merge(sorted(out, key=lambda h: h[1]))


def merge(found, gap=2):
    """Hunks no more than `gap` instructions apart on both sides become one (kind `mixed` when the
    kinds differ), so one source difference is censused once."""
    out = []
    for h in found:
        if out and h[1] - out[-1][2] <= gap and h[3] - out[-1][4] <= gap:
            prev = out[-1]
            out[-1] = (prev[0] if prev[0] == h[0] else "mixed", prev[1], max(prev[2], h[2]), prev[3],
                       max(prev[4], h[4]))
        else:
            out.append(h)
    return out


def window(retail, i1, i2, context):
    lo = max(0, i1 - context)
    hi = min(len(retail), max(i2, i1 + 1) + context)
    return lo, hi


# ---- the corpus --------------------------------------------------------------------------------
class Corpus:
    """The retail listings of the matched functions that have source, keyed by name."""

    def __init__(self, exclude=()):
        import units
        by_name, by_va = listing.symbols()
        sources = units.scan(os.path.join(listing.ROOT, "src"), listing.SYMBOLS)
        matched = set()
        with open(CATEGORIES) as fh:
            for line in fh:
                cols = line.rstrip("\n").split("\t")
                if len(cols) >= 3 and cols[2] == "match":
                    matched.add(cols[1])
        self.by_name, self.sources, self.functions = by_name, sources, {}
        for name in sorted(matched & set(sources) - set(exclude), key=lambda n: by_name.get(n, (0,))[0]):
            path = os.path.join(listing.ROOT, "asm", name + ".s")
            if name in by_name and os.path.exists(path):
                self.functions[name] = listing.asm_listing(path, by_va)
        self._shapes = {}
        self.profiles = _unit_profiles()

    def shapes(self, with_registers):
        """{name: the function's tokens, one per line, with a leading newline} (searched as text)."""
        if with_registers not in self._shapes:
            self._shapes[with_registers] = {n: "\n" + "\n".join(listing.shape(f, with_registers)) + "\n"
                                            for n, f in self.functions.items()}
        return self._shapes[with_registers]

    def search(self, signature, with_registers):
        """[(name, instruction index)] of every occurrence of `signature`."""
        needle, hits = "\n" + "\n".join(signature) + "\n", []
        for name, text in self.shapes(with_registers).items():
            at = text.find(needle)
            while at >= 0:
                hits.append((name, text.count("\n", 0, at)))
                at = text.find(needle, at + 1)
        return hits

    def profile(self, name):
        va = self.by_name[name][0]
        return next((p for lo, hi, p in self.profiles if lo <= va < hi), None)


def _unit_profiles():
    """[(lo, hi, (compiler id, flags, exceptions))] from units.tsv."""
    out = []
    with open(UNITS) as fh:
        for line in fh:
            cols = line.rstrip("\n").split("\t")
            if len(cols) >= 6 and cols[0].startswith("0x"):
                out.append((int(cols[0], 16), int(cols[1], 16), (cols[3], cols[4], cols[5])))
    return out


def rank(corpus, hits, target):
    """Hits ordered: same source file, same profile, then the rest (address order within each)."""
    path, profile = corpus.sources.get(target), corpus.profile(target) if target in corpus.by_name else None

    def key(hit):
        name = hit[0]
        return (corpus.sources.get(name) != path if path else True, corpus.profile(name) != profile,
                corpus.by_name[name][0])
    return sorted(hits, key=key)


# ---- hit lines ---------------------------------------------------------------------------------
_DEBUG_CACHE = {}


def hit_lines(corpus, name, lo, hi):
    """'file:first-last' lines of instructions lo..hi of a matched function, from its -g build."""
    path = corpus.sources[name]
    key = (path, name)
    if key not in _DEBUG_CACHE:
        import cc
        out = os.path.join(cc.scratch_dir(), "census_%d.o" % len(_DEBUG_CACHE))
        try:
            listing.compile_function(name, path, out, "-g")
            same = listing.shape(listing.object_listing(out, name)) == listing.shape(corpus.functions[name])
            _DEBUG_CACHE[key] = listing.debug_records(out, name) if same else None
        except ValueError:
            _DEBUG_CACHE[key] = None
    records = _DEBUG_CACHE[key]
    if records is None or not records.lines:
        return None
    lines = sorted({listing.line_at(records, 4 * i) for i in range(lo, hi)} - {None})
    if not lines:
        return None
    return records.file, lines


def source_text(path, lines):
    try:
        with open(os.path.join(listing.ROOT, path), errors="replace") as fh:
            text = fh.read().split("\n")
    except OSError:
        return []
    return ["        %5d  %s" % (n, text[n - 1].rstrip()) for n in lines if 0 < n <= len(text)]


# ---- reports -----------------------------------------------------------------------------------
def describe(insns, lo, hi, mark=()):
    return ["      %s%04x  %-8s %s" % ("> " if i in mark else "  ", insns[i].offset, insns[i].mnemonic,
                                       insns[i].operands) for i in range(lo, hi)]


def census_window(corpus, target, retail, i1, i2, args, indent="    "):
    """Lines reporting the census of retail[i1:i2] widened by the context. A hunk longer than
    `--width` without a hit even bare is censused again in pieces of that width."""
    out = []
    for context in range(args.context, -1, -1):
        lo, hi = window(retail, i1, i2, context)
        signature = listing.shape(retail[lo:hi], args.registers)
        hits = corpus.search(signature, args.registers)
        if hits or context == 0:
            break
    out.append("%ssignature (%d instructions, context %d): %s" % (indent, hi - lo, context, " ".join(signature)))
    if not hits:
        split = i2 - i1 > args.width and indent == "    "
        advice = ("; in pieces of %d:" % args.width if split
                  else "" if args.registers else "; check control flow and the call ABI")
        out.append("%s0 hits: no matched function has this %s%s" % (
            indent, "register pattern" if args.registers else "shape", advice))
        if split:
            piece = argparse.Namespace(**dict(vars(args), context=0, hits=min(args.hits, 2)))
            for start in [s for s in range(i1, i2, args.width) if min(i2, s + args.width) - s >= 3]:
                out.append("      piece +0x%x:" % (4 * start))
                out += census_window(corpus, target, retail, start, min(i2, start + args.width), piece, "        ")
        return out
    ranked = rank(corpus, hits, target)
    out.append("%s%d hit%s in %d function%s%s" % (
        indent, len(hits), "" if len(hits) == 1 else "s", len({h[0] for h in hits}),
        "" if len({h[0] for h in hits}) == 1 else "s",
        "" if context == args.context else " (only with context %d)" % context))
    for name, i in ranked[:args.hits]:
        path, line = listing.definition_site(corpus.sources[name], name)
        out.append("%s  %s  +0x%x  %s:%s" % (indent, name, 4 * i, path, line or "?"))
        if args.lines:
            found = hit_lines(corpus, name, i, i + (hi - lo))
            if found:
                out += source_text(found[0], found[1])
            else:
                out.append("%s    (no -g lines)" % indent)
    return out


def calls_report(corpus, target, retail, top):
    want = [x.callee or ("*" if x.mnemonic == "jalr" else "?") for x in retail if x.mnemonic in ("jal", "jalr")]
    out = ["call sequence of %s (%d calls): %s" % (target, len(want), " ".join(want))]
    if len(want) < 2:
        return out + ["  fewer than two calls: nothing to compare"]
    scores = []
    for name, insns in corpus.functions.items():
        got = [x.callee or ("*" if x.mnemonic == "jalr" else "?") for x in insns if x.mnemonic in ("jal", "jalr")]
        if len(got) < 2:
            continue
        sm = difflib.SequenceMatcher(None, want, got, autojunk=False)
        if sm.real_quick_ratio() < 0.3 or sm.quick_ratio() < 0.3:
            continue
        scores.append((sm.ratio(), name, len(got)))
    for ratio, name, n in sorted(scores, reverse=True)[:top]:
        path, line = listing.definition_site(corpus.sources[name], name)
        out.append("  %.2f  %-48s %3d calls  %s:%s" % (ratio, name, n, path, line or "?"))
    return out


def main(argv=None):
    import frameslots
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("function", help="retail VA (hex) or symbol")
    ap.add_argument("--cand", help="source holding the candidate definition (default: its file in src/)")
    ap.add_argument("--at", help="census a retail window instead of a residual: OFFSET[:N] (hex bytes, N insns)")
    ap.add_argument("--calls", action="store_true", help="rank matched functions by call-sequence similarity")
    ap.add_argument("--context", type=int, default=3, help="instructions either side of a hunk (default 3)")
    ap.add_argument("--width", type=int, default=6,
                    help="a hunk longer than this with no hit is censused in pieces this long (default 6)")
    ap.add_argument("--registers", action="store_true", help="signatures keep the register pattern")
    ap.add_argument("--hits", type=int, default=5, help="hits shown per hunk (default 5)")
    ap.add_argument("--lines", action="store_true", help="compile shown hits with -g and print their lines")
    a = ap.parse_args(argv)
    name, va = frameslots.resolve_function(a.function)
    retail = listing.retail_listing(va)
    corpus = Corpus(exclude=[name])
    print("corpus: %d matched functions with source" % len(corpus.functions))
    if a.calls:
        print("\n".join(calls_report(corpus, name, retail, a.hits)))
        return 0
    if a.at:
        off, _, count = a.at.partition(":")
        i1 = int(off, 16) // 4
        i2 = min(len(retail), i1 + (int(count) if count else 8))
        print("%s +0x%x, %d instructions:" % (name, 4 * i1, i2 - i1))
        print("\n".join(describe(retail, i1, i2)))
        exact = argparse.Namespace(**dict(vars(a), context=0))     # the window as named, no widening
        print("\n".join(census_window(corpus, name, retail, i1, i2, exact)))
        return 0
    try:
        cand, _records, _note = listing.compile_pair(name, frameslots.source_of(name, a.cand))
    except ValueError as error:
        print("residual_census: %s" % error, file=sys.stderr)
        return 2
    found = hunks(retail, cand)
    shown = [h for h in found if h[0] != "reg" or a.registers]
    print("%s: retail %d instructions, candidate %d; %d hunk%s" % (
        name, len(retail), len(cand), len(found), "" if len(found) == 1 else "s"))
    if len(shown) < len(found):
        print("register-only hunks (retail offsets; --registers censuses them): " + " ".join(
            "+0x%x..+0x%x" % (4 * h[1], 4 * h[2]) for h in found if h[0] == "reg"))
    for kind, i1, i2, j1, j2 in shown:
        print("\n  %s retail +0x%x..+0x%x (%d) / candidate +0x%x..+0x%x (%d)" % (
            kind, 4 * i1, 4 * i2, i2 - i1, 4 * j1, 4 * j2, j2 - j1))
        lo, hi = window(retail, i1, i2, a.context)
        print("    retail:")
        print("\n".join(describe(retail, lo, hi, range(i1, i2))))
        clo, chi = window(cand, j1, j2, a.context)
        print("    candidate:")
        print("\n".join(describe(cand, clo, chi, range(j1, j2))))
        print("\n".join(census_window(corpus, name, retail, i1, i2, a)))
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main())
