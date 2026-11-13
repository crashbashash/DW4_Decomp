#!/usr/bin/env python3
"""
inventory_scan.py — find code the symbol map does not own, and keep it from growing.

The relink proves every byte of the section, but it proves bytes, not the inventory: a
function that no symbol names links as a `data` unit of config/SLUS-20836/layout.txt and is counted
by nobody. This scan walks every `data` unit for instruction-shaped bodies and attributes
each one to the reason it has no symbol (docs/engine/function-inventory.md):

  A  continuation   the preceding symbol falls through or branches into it: that symbol's
                    extent is short (config/SLUS-20836/extent-overrides.tsv is the fix)
  B  jal-called     a `jal` from a known function lands here: a function nothing promoted
  C  data-referenced a data word outside every function holds its address (a vtable or table)
  D  j-reached      a `j` from a known function lands here: a tail-called function
  E  branch-target  a PC-relative branch from a non-adjacent symbol or from unsymbolised code
  G  unreferenced   nothing points at it: dead code, a literal the scan cannot form, or data
                    that happens to decode
  H  stub           an unreferenced 8-byte `jr ra; <delay>` body (the weakest evidence)

A body is *code* when every non-zero word decodes as an EE instruction a compiler could
emit (tools/split.py `_code_shaped`), it ends in an unconditional transfer plus delay
slot, and it carries one hard sign: a frame prologue, a `jal`/`j` to a symbol, or a
`jr ra` return with at least one more word. Segments one unit's branches connect are
merged into one candidate. The `data` rows of config/SLUS-20836/extent-overrides.tsv are
reviewed data, not code: the scan skips their bytes and does not count their words as
references. Everything is read from committed files and the retail image — no Ghidra,
no objdump — so a replay reproduces the table exactly.

Usage:
  inventory_scan.py --write     # regenerate data/inventory-scan.tsv and print the summary
  inventory_scan.py --check     # fail if the committed table is stale, or if the unsymbolised
                                # bytes exceed `inventory.unsymbolised_bytes` in config/debt-baseline.json
  inventory_scan.py             # summary only
"""
import argparse
import bisect
import collections
import json
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import split as S                                   # noqa: E402  the instruction model lives there

ELF_DEFAULT = os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36"))
LAYOUT_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "layout.txt")
SYMBOLS_DEFAULT = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
LABELS_DEFAULT = os.path.join(ROOT, "data", "symbols.json")
OUT_DEFAULT = os.path.join(ROOT, "data", "inventory-scan.tsv")
BASELINE_DEFAULT = os.path.join(ROOT, "config", "debt-baseline.json")
COUNTER = "inventory.unsymbolised_bytes"
CLASSES = collections.OrderedDict([
    ("A", "continuation of the preceding symbol (its extent is short)"),
    ("B", "jal target of a known function"),
    ("C", "address held in a data word outside every function"),
    ("D", "j target of a known function (tail call)"),
    ("E", "branch target of a non-adjacent symbol or of unsymbolised code"),
    ("G", "no incoming reference"),
    ("H", "unreferenced 8-byte `jr ra` stub"),
])


def load_symbols(path):
    out = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2]))
    out.sort()
    return out


def load_layout(path):
    out = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2], p[3]))
    return out


def load_labels(path):
    out = {}
    if not path or not os.path.exists(path):
        return out
    for it in json.load(open(path)).get("symbols", []):
        try:
            out.setdefault(int(it["address"], 16), []).append(it.get("name", ""))
        except (KeyError, ValueError, TypeError):
            pass
    return out


def _outside(lo, hi, rows):
    """[lo, hi) less the sorted `rows` [(va, end)], as [(lo, hi)] pieces."""
    out = []
    for a, b in rows:
        if b <= lo or a >= hi:
            continue
        if a > lo:
            out.append((lo, a))
        lo = max(lo, b)
    if lo < hi:
        out.append((lo, hi))
    return out


class Scan:
    """One scan over an image: `rows` is the list of candidate functions with their class.
    `data_rows` are the reviewed data spans [(va, end)] the scan leaves alone."""

    def __init__(self, img, syms, units, labels=None, exclude=(), section_hi=S.SECTION_HI,
                 data_rows=()):
        self.img, self.syms, self.labels = img, syms, labels or {}
        self.starts = [s[0] for s in syms]
        self.by_va = {s[0]: s for s in syms}
        self.section_hi = section_hi
        self.data_units = [u for u in units if u[2] == "data"]
        self.incoming = self._incoming(list(exclude) + list(data_rows))
        segs = []
        for va, sz, _k, _n in self.data_units:
            for lo, hi in _outside(va, va + sz, data_rows):
                segs.extend(self._segments(lo, hi - lo))
        self.rows = self._classify(self._merge(segs))

    # ---- helpers ------------------------------------------------------------------
    def word(self, va):
        return S._word(self.img, va)

    def sym_of(self, va):
        i = bisect.bisect_right(self.starts, va) - 1
        if i >= 0 and self.starts[i] <= va < self.starts[i] + self.syms[i][1]:
            return self.syms[i]
        return None

    def _incoming(self, exclude):
        """target -> [(source, kind)] over the whole section: branches, j and jal from inside
        symbols; data words outside every symbol and outside the excluded tables."""
        inc = collections.defaultdict(list)
        lo = S.VADDR_BASE
        in_sym = bytearray((self.section_hi - lo) // 4)
        for va, sz, _n in self.syms:
            for k in range((va - lo) // 4, min(len(in_sym), (va + sz - lo) // 4)):
                in_sym[k] = 1
        skip = bytearray(len(in_sym))
        for a, b in exclude:
            for k in range(max(0, (a - lo) // 4), min(len(skip), (b - lo + 3) // 4)):
                skip[k] = 1
        for k in range(len(in_sym)):
            a = lo + 4 * k
            w = self.word(a)
            if in_sym[k]:
                if S._is_pc_branch(w):
                    inc[S._branch_target(a, w)].append((a, "branch"))
                elif S._is_j(w):
                    inc[S._j_target(a, w)].append((a, "j"))
                elif S._is_jal(w):
                    inc[S._j_target(a, w)].append((a, "jal"))
            elif not skip[k] and lo <= w < self.section_hi and w % 4 == 0:
                inc[w].append((a, "dataword"))
        return inc

    def _segments(self, va, sz):
        """Code-shaped segments of one data unit: (va, size, prologue, calls, ret)."""
        end, a, out = va + sz, va, []
        while a < end:
            if self.word(a) == 0:
                a += 4
                continue
            b, ended = a, False
            while b + 4 <= end:
                w = self.word(b)
                if S._is_unconditional_end(w):
                    b, ended = b + 8, True
                    break
                b += 4
            b = min(b, end)
            words = [self.word(k) for k in range(a, b, 4)]
            shaped = all(S._code_shaped(w) for w in words)
            pro = S._is_prologue(words[0])
            calls = sum(1 for k in range(a, b, 4)
                        if (S._is_jal(self.word(k)) or S._is_j(self.word(k)))
                        and S._j_target(k, self.word(k)) in self.by_va)
            ret = any(w == 0x03E00008 for w in words)
            if shaped and ended and (pro or calls or (ret and len(words) >= 2)):
                out.append((a, b - a, pro, calls, ret))
            a = b
        return out

    def _merge(self, segs):
        """Segments of one unit that branch into each other are one function."""
        by_unit = collections.defaultdict(list)
        unit_starts = [u[0] for u in self.data_units]
        for s in segs:
            i = bisect.bisect_right(unit_starts, s[0]) - 1
            by_unit[unit_starts[i]].append(s)
        funcs = []
        for u, ss in sorted(by_unit.items()):
            ss.sort()
            bounds = [(s[0], s[0] + s[1]) for s in ss]
            parent = list(range(len(ss)))

            def find(x):
                while parent[x] != x:
                    parent[x] = parent[parent[x]]
                    x = parent[x]
                return x

            def seg_at(t):
                i = bisect.bisect_right([b[0] for b in bounds], t) - 1
                return i if i >= 0 and bounds[i][0] <= t < bounds[i][1] else None

            for i, s in enumerate(ss):
                for k in range(s[0], s[0] + s[1], 4):
                    w = self.word(k)
                    t = S._branch_target(k, w) if S._is_pc_branch(w) else \
                        S._j_target(k, w) if S._is_j(w) else None
                    if t is None:
                        continue
                    j = seg_at(t)
                    if j is not None and j != i:
                        parent[find(i)] = find(j)
            groups = collections.defaultdict(list)
            for i in range(len(ss)):
                groups[find(i)].append(i)
            spans = []
            for members in groups.values():
                members.sort()
                spans.append([ss[members[0]][0], ss[members[-1]][0] + ss[members[-1]][1], members])
            # a group that spans another one's segments owns them too: the body between a
            # forward branch and its target is one function whatever reaches the middle
            spans.sort()
            merged = []
            for lo, hi, members in spans:
                if merged and lo < merged[-1][1]:
                    merged[-1][1] = max(merged[-1][1], hi)
                    merged[-1][2] += members
                else:
                    merged.append([lo, hi, list(members)])
            for lo, hi, members in merged:
                first = min(members)
                funcs.append(dict(va=lo, size=hi - lo, unit=u, pro=ss[first][2],
                                  calls=sum(ss[m][3] for m in members)))
        funcs.sort(key=lambda f: f["va"])
        return funcs

    def _classify(self, funcs):
        rows = []
        for f in funcs:
            va, size = f["va"], f["size"]
            inc = collections.Counter()
            srcs = collections.defaultdict(list)
            prev = self.sym_of(va - 4)
            for k in range(va, va + size, 4):
                for src, kind in self.incoming.get(k, []):
                    if kind == "dataword":
                        key = "dataword"
                    else:
                        so = self.sym_of(src)
                        if so is None:
                            key = kind + ":unsymbolised"
                        elif prev is not None and so[0] == prev[0]:
                            key = kind + ":prev"
                        else:
                            key = kind + ":other"
                    inc[key] += 1
                    if len(srcs[key]) < 3:
                        srcs[key].append("%s@%x" % (kind, src))
            p2, p1 = self.word(va - 8), self.word(va - 4)
            falls = prev is not None and prev[0] + prev[1] == va \
                and not S._is_unconditional_end(p2) and p1 != 0
            if falls or inc["branch:prev"]:
                cls = "A"
            elif inc["jal:other"] or inc["jal:prev"] or inc["jal:unsymbolised"]:
                cls = "B"
            elif inc["dataword"]:
                cls = "C"
            elif inc["j:other"] or inc["j:prev"] or inc["j:unsymbolised"]:
                cls = "D"
            elif inc["branch:other"] or inc["branch:unsymbolised"]:
                cls = "E"
            elif size == 8 and self.word(va) == 0x03E00008:
                cls = "H"
            else:
                cls = "G"
            ev = []
            if falls:
                ev.append("falls-through-from:%s" % prev[2])
            for key in sorted(srcs):
                ev.append(key + "(" + ",".join(srcs[key]) + ")")
            if f["pro"]:
                ev.append("prologue")
            if f["calls"]:
                ev.append("calls:%d" % f["calls"])
            lab = [n for n in self.labels.get(va, []) if n.startswith(("LAB_", "DAT_", "FUN_"))]
            if lab:
                ev.append("label:" + lab[0])
            rows.append((va, size, cls, " ".join(ev) or "-"))
        return rows


def summary(rows):
    by = collections.OrderedDict((c, [0, 0]) for c in CLASSES)
    for _va, size, cls, _ev in rows:
        by[cls][0] += 1
        by[cls][1] += size
    return by


def format_summary(rows):
    by = summary(rows)
    lines = ["inventory: %d unsymbolised code bodies, %d bytes" % (len(rows), sum(r[1] for r in rows))]
    for c, (n, b) in by.items():
        lines.append("  %s %-70s %5d bodies %7d bytes" % (c, CLASSES[c], n, b))
    return "\n".join(lines)


def render(rows):
    out = ["# va\tbytes\tclass\tevidence — GENERATED by scripts/inventory_scan.py; do not edit.",
           "# Instruction-shaped bodies that no symbol of config/SLUS-20836/symbols.txt owns, one per line, with the",
           "# class of evidence (docs/engine/function-inventory.md) and the references that reach them.",
           "# The byte total is the debt counter `%s` (tools/progress.py)." % COUNTER]
    out += ["# " + ln for ln in format_summary(rows).splitlines()]
    for va, size, cls, ev in rows:
        out.append("%08x\t%d\t%s\t%s" % (va, size, cls, ev))
    return "\n".join(out) + "\n"


def load_table(path):
    rows = []
    if not os.path.exists(path):
        return None
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        va, size, cls, ev = ln.rstrip("\n").split("\t", 3)
        rows.append((int(va, 16), int(size), cls, ev))
    return rows


def unsymbolised_bytes(path=OUT_DEFAULT):
    """The debt counter: the byte total of the committed table, or None when it is missing."""
    rows = load_table(path)
    return None if rows is None else sum(r[1] for r in rows)


def run(elf, layout, symbols, labels):
    img = S.read_elf(elf)
    syms = load_symbols(symbols)
    units = load_layout(layout)
    cfg = os.path.dirname(os.path.abspath(symbols))
    exclude = S.non_entry_tables(os.path.join(cfg, "exceptions.txt"), os.path.join(cfg, "jumptables.txt"))
    data = S.data_rows(S.load_extent_overrides(os.path.join(cfg, "extent-overrides.tsv")))
    return Scan(img, syms, units, load_labels(labels), exclude, data_rows=data).rows


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--layout", default=LAYOUT_DEFAULT)
    ap.add_argument("--symbols", default=SYMBOLS_DEFAULT)
    ap.add_argument("--labels", default=LABELS_DEFAULT)
    ap.add_argument("--out", default=OUT_DEFAULT)
    ap.add_argument("--baseline", default=BASELINE_DEFAULT)
    ap.add_argument("--write", action="store_true", help="regenerate the table")
    ap.add_argument("--check", action="store_true",
                    help="fail if the table is stale or the byte total exceeds the recorded debt")
    a = ap.parse_args(argv)
    rows = run(a.elf, a.layout, a.symbols, a.labels)
    print(format_summary(rows))
    if a.write:
        with open(a.out, "w") as fh:
            fh.write(render(rows))
        print("wrote %s" % os.path.relpath(a.out, ROOT))
    if a.check:
        committed = load_table(a.out)
        if committed is None:
            print("inventory-check: %s is missing — run scripts/inventory_scan.py --write" % os.path.relpath(a.out, ROOT))
            return 1
        if committed != rows:
            print("inventory-check: %s is stale (%d rows committed, %d scanned) — run scripts/inventory_scan.py --write"
                  % (os.path.relpath(a.out, ROOT), len(committed), len(rows)))
            return 1
        total = sum(r[1] for r in rows)
        base = None
        if os.path.exists(a.baseline):
            v = json.load(open(a.baseline)).get("counters", {}).get(COUNTER)
            base = v.get("value") if isinstance(v, dict) else v
        if base is None:
            print("inventory-check: no `%s` in %s — record it with tools/progress.py --debt-baseline"
                  % (COUNTER, os.path.relpath(a.baseline, ROOT)))
            return 1
        if total > base:
            print("inventory-check: %d unsymbolised code bytes exceed the recorded debt %d" % (total, base))
            return 1
        print("inventory-check: %d unsymbolised code bytes <= recorded debt %d  OK" % (total, base))
    return 0


if __name__ == "__main__":
    sys.exit(main())
