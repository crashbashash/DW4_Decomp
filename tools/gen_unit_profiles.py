#!/usr/bin/env python3
"""gen_unit_profiles.py — derive config/SLUS-20836/units.tsv (one build profile per translation unit)
from the per-function pins, the build-settings sweeps and the retail exception evidence.

The model (docs/engine/build-profiles.md, tools/unitprofiles.py): a compiler, a flag set
and an exception mode belong to a translation unit. This tool draws the unit boundaries
the evidence supports, chooses one profile per unit, prints every unit whose members
cannot share a profile, and rewrites the per-function tables so that only the dissenting
members keep a row, marked `provisional`.

Unit boundaries, in priority order (a unit never crosses a function):

  1. the Sony EE GCC blocks and stock libraries of config/SLUS-20836/regions.tsv, cut at
     docs/engine/module-map.md's address-contiguous runs (a run of
     functions separated from the next by data is the closest proxy for the library's
     object files);
  2. an address-contiguous **class run**: consecutive functions carrying the same class
     label (`<Class>_<Method>`, `Gap__<Lib>__<Class>__vfunc_N`), unlabeled functions
     between two members included — MWCC emits a unit's functions in source order and
     the linker places whole objects, so a run is a lower bound on one unit;
  3. everything else: consecutive unlabeled functions. No boundary evidence exists
     there, so such a run is cut where the retail exception evidence changes (a function
     with an index record beside a non-leaf function without one) and where the current
     pins change; it never claims a conflict it cannot see.

Exception mode: `on` when any function of the unit has a retail exception index record
(config/SLUS-20836/exceptions.txt); MWCC emits a record for every function with a stack frame or a
call when exceptions are on, so a run of record-less leaves beside recorded functions is
still one unit with exceptions on. `off` otherwise (no non-leaf member has a record, or
the unit holds nothing but frameless leaves, which decide nothing).

Profile: for each unit the candidates are the members' current pins plus, for a unit
whose pins disagree, the 3.0.3 build (the audit found it reproduces the engine's
"default-only" members where the 2003 betas do not). A candidate is scored by the
members it reproduces; the evidence is the result files (`--results`, JSON lines with
va, compiler, flags, ok and, when present, cat) and the pins themselves. A pair the
evidence does not decide is written to `--sweep-tasks` and, with `--sweep`, verified
here (tools/verify.py with the tables disabled, so compiler and flags are exactly the
candidate's). The best candidate wins; ties go to the pin most members already carry,
then to the Makefile default. Members the winning profile does not reproduce keep an
override row, and the unit is marked `provisional`.

Usage:
  gen_unit_profiles.py --results sweep.jsonl ... [--sweep-tasks tasks.jsonl]
  gen_unit_profiles.py --results ... --sweep more.jsonl --jobs 8    # verify undecided pairs
  gen_unit_profiles.py --results ... --write                        # rewrite the three tables

Without --write nothing under config/ changes; the consistency report is always printed.
"""
import argparse
import collections
import hashlib
import json
import os
import re
import struct
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import exceptions as exception_records  # noqa: E402
import regions  # noqa: E402
import unitcompilers  # noqa: E402
import unitflags  # noqa: E402
import unitobjects  # noqa: E402
import unitprofiles  # noqa: E402
import units as unitfiles  # noqa: E402

VADDR_BASE, FILE_BASE = 0x100000, 0x80
DEFAULT_FLAGS = "-O3 -Iinclude"
# compiler id -> repository-relative executable. The id is what units.tsv rows name; the
# table in the file header carries the path and the content digest.
COMPILERS = collections.OrderedDict([
    ("default", "local/mwcps2/3.0-011126/mwccps2.exe"),
    ("combat", "local/mwcps2/combat/mwccps2.exe"),
    ("3.0.3", "local/mwcps2/3.0.3-020716/mwccps2.exe"),
    ("b50", "local/mwcps2/3.0b50-030527/mwccps2.exe"),
    ("b52", "local/mwcps2/3.0b52-030722/mwccps2.exe"),
    ("2.4", "local/mwcps2/2.4/mwccps2.exe"),
    ("ee-gcc", "local/ee-gcc2.96/bin/ee-gcc"),
])
COMPILER_ID = {v: k for k, v in COMPILERS.items()}
# The Sony EE GCC blocks and the stock libraries whose object files are unlabeled.
SONY_BLOCKS = [(r.lo, r.hi, r.id) for r in regions.load() if r.build == "gcc"]
LIBRARY_REGIONS = [(r.lo, r.hi, r.id) for r in regions.load() if r.id in ("libpng", "zlib", "lua")]
MODULE_MAP = os.path.join(ROOT, "docs", "engine", "module-map.md")
CATEGORIES = os.path.join(ROOT, "data", "check-categories.tsv")
CODE_OK = {"match", "code-only", "name-defect", "inventory-gap"}


def compiler_id(path):
    """`local/mwcps2/combat/mwccps2.exe` -> `combat` (an absolute path is made relative first)."""
    if path is None:
        return "default"
    rel = os.path.relpath(path, ROOT) if os.path.isabs(path) else path
    if rel in COMPILER_ID:
        return COMPILER_ID[rel]
    raise ValueError(f"compiler not in the id table: {rel}")


def split_exceptions(flags):
    tokens = flags.split()
    mode = None
    while "-Cpp_exceptions" in tokens:
        i = tokens.index("-Cpp_exceptions")
        if i + 1 < len(tokens) and tokens[i + 1] in ("on", "off"):
            mode = tokens[i + 1]
            del tokens[i:i + 2]
        else:
            del tokens[i]
    return " ".join(tokens), mode


def load_symbols(path):
    out = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2]))
    out.sort()
    return out


def label(name):
    m = re.match(r"^(Gap__\w+?__(\w+?))__vfunc_\d+$", name)
    if m:
        return m.group(2)
    m = re.match(r"^((?:be|ig|lib)[A-Za-z0-9]+)_[A-Z]\w*$", name)
    if m:
        return m.group(1)
    return None


def module_map_runs(path=MODULE_MAP):
    """[(start, end, region)] from the module map's "Runs" table."""
    runs = []
    if not os.path.exists(path):
        return runs
    for ln in open(path):
        m = re.match(r"^\| `0x([0-9a-f]+)` \| `0x([0-9a-f]+)` \| \d+ \| \d+ \| \d+ \| ([^|]*)\|", ln)
        if m:
            runs.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3).strip()))
    return runs


def prologue_kind(img, va, size):
    """"gcc" when the body saves registers with `sd` to the stack (the Sony EE GCC prologue of
    docs/engine/sd-prologue.md), "mwcc" when it saves with `sq`, None when it saves nothing."""
    off = va - VADDR_BASE + FILE_BASE
    kind = None
    for i in range(0, size - size % 4, 4):
        w = struct.unpack_from("<I", img, off + i)[0]
        if (w >> 26) == 0x3f and (w >> 21) & 0x1f == 29:      # sd rt, off(sp)
            return "gcc"
        if (w >> 26) == 0x1f and (w >> 21) & 0x1f == 29:      # sq rt, off(sp)
            kind = "mwcc"
    return kind


def frameless_leaf(img, va, size):
    """True when the body has no call and no stack adjustment (MWCC emits no exception record for it)."""
    off = va - VADDR_BASE + FILE_BASE
    for i in range(0, size - size % 4, 4):
        w = struct.unpack_from("<I", img, off + i)[0]
        if w >> 26 == 3:                              # jal
            return False
        if w & 0xfc00003f == 0x09:                    # jalr
            return False
        if w & 0xffff0000 in (0x27bd0000, 0x67bd0000):  # addiu/daddiu sp
            return False
    return True


def slug(text):
    return re.sub(r"[^A-Za-z0-9]+", "-", text).strip("-").lower()


class Function:
    __slots__ = ("va", "size", "name", "path", "label", "record", "leaf", "pin", "category", "group_owner",
                 "prologue", "asm_body")

    def __init__(self, va, size, name):
        self.va, self.size, self.name = va, size, name
        self.path = None
        self.label = label(name)
        self.record = False
        self.leaf = False
        self.pin = None           # (compiler id, base flags, exception mode or None)
        self.category = None
        self.group_owner = None   # owner address when this body is emitted by another unit
        self.prologue = None      # "gcc" / "mwcc" / None (see prologue_kind)
        self.asm_body = False     # retail bytes in an MWCC `asm` function: no profile shapes them

    @property
    def member(self):
        """A function whose own source is compiled (not an emitted body of another owner)."""
        return self.path is not None and self.group_owner is None

    @property
    def scored(self):
        """A member whose bytes a profile can reproduce or not: an asm body says nothing."""
        return self.member and not self.asm_body

    @property
    def ext(self):
        return os.path.splitext(self.path)[1] if self.path else None


class Unit:
    def __init__(self, name, functions, kind, evidence, prologue=None):
        self.name, self.functions, self.kind, self.evidence = name, functions, kind, evidence
        self.prologue = prologue  # "gcc"/"mwcc" for a Sony-block piece whose bodies say which compiler
        self.exceptions = "off"
        self.exception_source = ""
        self.profile = None       # (compiler id, flags)
        self.status = "-"
        self.overrides = []       # [(Function, reason)]
        self.candidates = {}
        self.source = ""

    @property
    def lo(self):
        return self.functions[0].va

    @property
    def hi(self):
        return self.functions[-1].va + self.functions[-1].size

    @property
    def members(self):
        return [f for f in self.functions if f.member]

    @property
    def scored(self):
        return [f for f in self.functions if f.scored]


def build_functions(a, img):
    syms = load_symbols(a.symbols)
    functions = [Function(va, sz, nm) for va, sz, nm in syms]
    by_va = {f.va: f for f in functions}
    src_index = unitfiles.scan(a.src, symbols=a.symbols, unit_objects=a.unit_objects)
    for f in functions:
        if f.name in src_index:
            f.path = src_index[f.name]
    registry = unitobjects.load(a.unit_objects) if a.unit_objects else unitobjects.load()
    for group in registry.values() if isinstance(registry, dict) else registry:
        for _name, address in group.emitted:
            if address in by_va and address != group.owner:
                by_va[address].group_owner = group.owner
    records = exception_records.load(exception_records.config_path(a.symbols))
    categories = {}
    if os.path.exists(a.categories):
        for ln in open(a.categories, errors="replace"):
            if ln.startswith("#") or not ln.strip():
                continue
            p = ln.rstrip("\n").split("\t")
            if len(p) >= 3:
                categories[int(p[0], 16)] = p[2]
    for f in functions:
        f.record = f.va in records
        f.leaf = frameless_leaf(img, f.va, f.size)
        f.prologue = prologue_kind(img, f.va, f.size)
        f.category = categories.get(f.va)
        if f.path is not None:
            f.asm_body = unitprofiles.asm_body_source(f.path)
            # the pin is what the tree compiles the function with today: before this table existed
            # the per-function rows, afterwards its unit profile or its provisional override
            # (tools/unitprofiles.resolve), so a regeneration starts from the current state
            res = unitprofiles.resolve(f.va, DEFAULT_FLAGS, COMPILERS["default"], units=a.units,
                                       unit_flags=a.unit_flags, unit_compilers=a.unit_compilers, symbols=a.symbols)
            pinned = res.override or res.profile
            # a legacy row without a -Cpp_exceptions token pinned no mode (None): the compiler default
            mode = pinned.exceptions if (res.unit is not None or pinned.exceptions == "off") else None
            f.pin = (compiler_id(pinned.compiler), pinned.flags, mode)
    return functions


def build_units(functions):
    """Carve the function list into units (see the module docstring)."""
    assigned = {}
    units = []
    runs = module_map_runs()

    position = {f.va: i for i, f in enumerate(functions)}

    def take(name, funcs, kind, evidence, prologue=None):
        """Make a unit of `funcs` (those not yet assigned); a run that another unit already
        cut in two (a Sony block inside a library region) becomes one unit per contiguous stretch."""
        funcs = [f for f in funcs if f.va not in assigned]
        stretch = []
        for f in funcs + [None]:
            if stretch and (f is None or position[f.va] != position[stretch[-1].va] + 1):
                label_ = name if stretch[0] is funcs[0] else "%s_%06x" % (name.rsplit("_", 1)[0], stretch[0].va)
                u = Unit(label_, list(stretch), kind, evidence, prologue)
                for g in stretch:
                    assigned[g.va] = u
                units.append(u)
                stretch = []
            if f is not None:
                stretch.append(f)

    # 1. library and Sony blocks, cut at the module map's runs: consecutive functions of the
    #    block that the map lists in the same run (or in none) form one unit. The Sony blocks
    #    also hold Metrowerks runtime objects (the `sq` prologue beside Sony's `sd`), so a run
    #    there is cut again where the prologue kind changes; a body that saves nothing follows
    #    its predecessor.
    for lo, hi, tag in SONY_BLOCKS + LIBRARY_REGIONS:
        piece, piece_run, piece_kind = [], None, None
        for f in [f for f in functions if lo <= f.va < hi]:
            run = next(((s, e) for s, e, _r in runs if s <= f.va <= e), None)
            kind = f.prologue if (lo, hi, tag) in SONY_BLOCKS else None
            if piece and (run != piece_run or (kind and piece_kind and kind != piece_kind)):
                take_piece(take, tag, lo, hi, piece, piece_run, piece_kind)
                piece, piece_kind = [], None
            piece.append(f)
            piece_run = run
            piece_kind = piece_kind or kind
        if piece:
            take_piece(take, tag, lo, hi, piece, piece_run, piece_kind)
    # 2. class runs
    index = {f.va: i for i, f in enumerate(functions)}
    cur = None
    class_runs = []
    for f in functions:
        if f.va in assigned:
            cur = None
            continue
        if f.label is None:
            continue
        if cur and cur[0] == f.label:
            cur[1].append(f)
        else:
            cur = (f.label, [f])
            class_runs.append(cur)
    names = collections.Counter()
    for lab, members in class_runs:
        span = functions[index[members[0].va]:index[members[-1].va] + 1]
        if any(f.va in assigned for f in span):
            span = [f for f in span if f.va not in assigned]
        names[lab] += 1
        name = lab if names[lab] == 1 else "%s_%06x" % (lab, span[0].va)
        take(name, span, "class", "class run of %d labeled members%s" % (
            len(members), ", %d unlabeled functions inside" % (len(span) - len(members)) if len(span) > len(members) else ""))
    # 3. unlabeled remainder: contiguous, cut at exception-evidence and pin changes
    chunk = []

    def flush():
        if chunk:
            take("unlabeled_%06x" % chunk[0].va, list(chunk), "unlabeled",
                 "unlabeled run, no boundary evidence: cut where the retail exception evidence or the pins change")
        chunk.clear()

    def state(f):
        if f.record:
            return "R"
        return None if f.leaf else "N"

    for i, f in enumerate(functions):
        if f.va in assigned:
            flush()
            continue
        if chunk:
            prev = chunk[-1]
            known_prev = next((state(g) for g in reversed(chunk) if state(g)), None)
            if (state(f) and known_prev and state(f) != known_prev) \
                    or (f.pin and prev_pin(chunk) and f.pin[:2] != prev_pin(chunk)):
                flush()
        chunk.append(f)
    flush()
    units.sort(key=lambda u: u.lo)
    for u in units:
        decide_exceptions(u)
    return units


def take_piece(take, tag, lo, hi, piece, run, kind=None):
    where = ("outside any mapped run" if run is None
             else "cut at module-map run %#x-%#x" % (run[0], run[1]))
    prologue = {"gcc": "; `sd` prologues (Sony EE GCC)", "mwcc": "; `sq` prologues (Metrowerks)"}.get(kind, "")
    take("%s_%06x" % (tag, piece[0].va), piece, "library",
         "%s block %#x-%#x (docs/engine/sd-prologue.md, module-map.md) %s%s" % (tag, lo, hi, where, prologue), kind)


def prev_pin(chunk):
    for g in reversed(chunk):
        if g.pin:
            return g.pin[:2]
    return None


def decide_exceptions(u):
    recorded = [f for f in u.functions if f.record]
    telling = [f for f in u.functions if not f.leaf]
    if recorded:
        u.exceptions = "on"
        odd = [f for f in telling if not f.record]
        u.exception_source = "exceptions on: %d/%d functions have retail index records" % (len(recorded), len(u.functions))
        if odd:
            u.exception_source += "; %d non-leaf function(s) without one (%s)" % (
                len(odd), ", ".join("%#x" % f.va for f in odd[:3]))
    elif telling:
        u.exceptions = "off"
        u.exception_source = "exceptions off: none of %d non-leaf functions has a retail index record" % len(telling)
    else:
        u.exceptions = "off"
        u.exception_source = "exceptions undetermined (every function is a frameless leaf, which carries no record either way): off"


# ---- evidence -------------------------------------------------------------------------

YES, NO, FAILED = "yes", "no", "failed"


class Evidence:
    """(va, compiler id, base flags, exception mode) -> YES (code reproduced), NO (the code bytes or the
    compile failed: definite) or FAILED (verify said no without saying why: the metadata may be what failed)."""

    def __init__(self):
        self.results = {}

    def add_file(self, path):
        n = 0
        for ln in open(path):
            if not ln.strip():
                continue
            r = json.loads(ln)
            try:
                cid = compiler_id(r["compiler"])
            except ValueError:
                continue
            base, mode = split_exceptions(r["flags"])
            cat = r.get("cat")
            if cat is None:
                m = re.search(r"\bcat=([\w-]+)", r.get("first", "") or "")
                cat = m.group(1) if m else None
            if r.get("ok") or (cat in CODE_OK):
                verdict = YES
            elif cat in ("mismatch", "compile"):
                verdict = NO
            else:
                verdict = FAILED
            key = (r["va"], cid, base, "on" if cid == "ee-gcc" else (mode or "on"))   # GCC has no mode
            # a positive answer is never overwritten; a definite no outranks an unexplained failure
            rank = {YES: 2, NO: 1, FAILED: 0}
            if rank[verdict] > rank.get(self.results.get(key), -1):
                self.results[key] = verdict
            n += 1
        return n

    def add_check(self, categories, functions, a):
        """Evidence from data/check-categories.tsv: every row was verified under the resolution of the
        current tables, so a code-reproducing category is a YES for the unit profile (or for the
        override, when the row is foreign-profile: then the unit profile is a NO)."""
        n = 0
        by_va = {f.va: f for f in functions}
        for ln in open(categories, errors="replace"):
            if ln.startswith("#") or not ln.strip():
                continue
            p = ln.rstrip("\n").split("\t")
            va, cat = int(p[0], 16), p[2]
            f = by_va.get(va)
            if f is None or f.path is None:
                continue
            res = unitprofiles.resolve(f.va, DEFAULT_FLAGS, COMPILERS["default"], units=a.units,
                                       unit_flags=a.unit_flags, unit_compilers=a.unit_compilers, symbols=a.symbols)
            unit_key = (va, compiler_id(res.profile.compiler), res.profile.flags,
                        "on" if compiler_id(res.profile.compiler) == "ee-gcc" else res.profile.exceptions)
            if cat == "foreign-profile" and res.override is not None:
                self.results[unit_key] = NO
                over = res.override
                self.results[(va, compiler_id(over.compiler), over.flags,
                              "on" if compiler_id(over.compiler) == "ee-gcc" else over.exceptions)] = YES
            elif cat in CODE_OK:
                self.results[unit_key] = YES
            elif cat in ("mismatch", "compile"):
                self.results[unit_key] = NO
            n += 1
        return n

    def lookup(self, f, cid, flags, mode):
        """True/False when the evidence decides whether `f` reproduces under the candidate, else None."""
        if cid == "ee-gcc":
            mode = "on"          # the Sony compiler has no exception switch; one key per candidate
        if f.pin and f.pin[:2] == (cid, flags) and (f.pin[2] or "on") == mode:
            return True          # the pin itself: the tree verifies it today
        got = self.results.get((f.va, cid, flags, mode))
        if got == YES:
            return True
        if got == NO:
            return False
        if got == FAILED:
            # an unexplained failure is informative only when the metadata could have passed: the
            # function is fully verified under its pin (so no retail record is unproduced) and, for
            # C++, the exception mode agrees (C emits no metadata whatever the mode)
            if f.category == "match" and f.pin and (f.ext == ".c" or (f.pin[2] or "on") == mode):
                return False
        if f.ext == ".c":
            # C emits no exception metadata: a full match under the other mode reproduces the code
            other = self.results.get((f.va, cid, flags, "off" if mode == "on" else "on"))
            if other == YES and (f.pin or (None,))[0] != "ee-gcc" and cid != "ee-gcc":
                return None      # the code is likely the same, but the mode is untested: sweep it
        return None


EEGCC_FLAGS = "-O2 -G0 -Iinclude"


def candidates_for(u):
    """([(compiler id, flags)], Counter of the scored members' pins) for a unit.

    A Sony-block piece whose bodies carry the `sd` prologue is Sony EE GCC output and admits
    only ee-gcc candidates (an MWCC match of a leaf inside it is a coincidence of bytes, and is
    reported as foreign-profile); a piece with `sq` prologues admits only MWCC builds."""
    pins = collections.Counter(f.pin[:2] for f in u.scored if f.pin)
    cands = list(pins)
    if len(pins) > 1 and not any(c == "ee-gcc" for c, _ in pins):
        for _c, flags in list(pins):
            if ("3.0.3", flags) not in cands:
                cands.append(("3.0.3", flags))
    if (any(c == "ee-gcc" for c, _ in pins) or u.prologue == "gcc") and ("ee-gcc", EEGCC_FLAGS) not in cands:
        cands.append(("ee-gcc", EEGCC_FLAGS))
    if u.prologue == "gcc":
        cands = [c for c in cands if c[0] == "ee-gcc"]
    elif u.prologue == "mwcc":
        cands = [c for c in cands if c[0] != "ee-gcc"] or cands
    return cands, pins


def evaluate(units, evidence):
    """Score every candidate of every unit; return the undecided (function, candidate) pairs."""
    undecided = []
    for u in units:
        cands, pins = candidates_for(u)
        u.candidates = {}
        for cand in cands:
            yes, no, unknown = [], [], []
            for f in u.scored:
                got = evidence.lookup(f, cand[0], cand[1], u.exceptions)
                if got is None and f.group_owner is None and f.va in GROUP_OWNERS:
                    # a compiler-unit owner is verified with its emitted bodies and twins; the sweep
                    # cannot test it without the tables, so beyond `make check`'s own results
                    # (--from-check) its pin (compiler, flags and exception mode) is the only evidence
                    got = f.pin[:2] == cand and (f.pin[2] or "on") == u.exceptions
                (yes if got is True else no if got is False else unknown).append(f)
            u.candidates[cand] = (yes, no, unknown)
            for f in unknown:
                undecided.append((f, cand, u.exceptions))
    return undecided


GROUP_OWNERS = set()


def choose(units):
    for u in units:
        cands, pins = candidates_for(u)
        if not u.scored or not u.candidates:
            if u.prologue == "gcc":
                u.profile = ("ee-gcc", EEGCC_FLAGS)
                u.source = "no compiled C member yet; `sd` prologues: Sony EE GCC"
            else:
                u.profile = pins.most_common(1)[0][0] if pins else ("default", DEFAULT_FLAGS)
                u.source = ("no compiled member yet; default profile" if not u.members
                            else "only asm bodies compiled so far (no profile shapes them); %s" % (
                                "majority pin" if pins else "default profile"))
            u.overrides = []
            continue
        order = sorted(u.candidates, key=lambda c: (-len(u.candidates[c][0]), -pins.get(c, 0),
                                                    0 if c[0] == "default" else 1, len(c[1]), c))
        best = order[0]
        yes, no, unknown = u.candidates[best]
        u.profile = best
        u.overrides = [(f, "unit %s profile %s %s exceptions %s does not reproduce it%s" % (
            u.name, best[0], best[1], u.exceptions,
            "" if f in no else " (untested)")) for f in no + unknown]
        # a pinned body that is not compiled on its own (an emitted member or duplicate of a
        # compiler unit) keeps its row when the pin differs: the twin compile depends on it and
        # nothing here can test it
        for f in u.functions:
            if f.pin and not f.member and (f.pin[:2] != best or (f.pin[2] or "on") != u.exceptions):
                u.overrides.append((f, "emitted body of compiler unit %#x: pin kept, untested under unit %s" % (
                    f.group_owner or 0, u.name)))
        total = len(u.scored)
        bits = []
        if len(u.members) > total:
            bits.append("%d asm bod%s not scored" % (len(u.members) - total, "y" if len(u.members) - total == 1 else "ies"))
        if len(pins) > 1:
            bits.append("pins %s" % ", ".join("%d×%s %s" % (n, c, fl) for (c, fl), n in pins.most_common()))
        bits.append("%s reproduces %d/%d members" % ("%s %s" % best, len(yes), total))
        losers = [c for c in order[1:] if u.candidates[c][0]]
        if losers:
            bits.append("; ".join("%s %s %d/%d" % (c[0], c[1], len(u.candidates[c][0]), total) for c in losers[:3]))
        if u.overrides:
            u.status = "provisional"
            bits.append("%d member(s) keep a provisional override" % len(u.overrides))
        u.source = "; ".join(bits)


# ---- the sweep -------------------------------------------------------------------------

def run_sweep(undecided, out, jobs):
    """Verify every undecided pair with tools/verify.py, tables disabled; append JSON lines to `out`."""
    from multiprocessing import Pool
    tasks = []
    seen = set()
    for f, (cid, flags), mode in undecided:
        key = (f.va, cid, flags, mode)
        if key in seen:
            continue
        seen.add(key)
        full = flags + (" -Cpp_exceptions off" if mode == "off" and cid != "ee-gcc" else "")
        tasks.append(dict(va=f.va, name=f.name, path=f.path, compiler=COMPILERS[cid], flags=full))
    done = set()
    if os.path.exists(out):
        for ln in open(out):
            if ln.strip():
                r = json.loads(ln)
                done.add((r["va"], r["compiler"], r["flags"]))
    todo = [t for t in tasks if (t["va"], t["compiler"], t["flags"]) not in done]
    print("sweep: %d pairs, %d to verify -> %s" % (len(tasks), len(todo), out), flush=True)
    with Pool(jobs) as pool, open(out, "a") as fh:
        for i, r in enumerate(pool.imap_unordered(_verify_task, todo, chunksize=4)):
            fh.write(json.dumps(r) + "\n")
            fh.flush()
            if (i + 1) % 500 == 0:
                print("  %d/%d" % (i + 1, len(todo)), flush=True)
    print("sweep: done", flush=True)


def _verify_task(task):
    import verify as vfy
    t0 = time.time()
    try:
        src, tmp = unitfiles.standalone(task["path"], task["name"], symbols="config/SLUS-20836/symbols.txt",
                                        unit_objects=None)
        try:
            ok, rep = vfy.verify_one(task["va"], src, flags=task["flags"], mwcc=task["compiler"],
                                     unit_flags="/dev/null", unit_compilers="/dev/null",
                                     units="/dev/null", unit_objects=None)
        finally:
            if tmp:
                os.remove(tmp)
    except Exception as e:       # noqa: BLE001 — one bad candidate must not abort the sweep
        ok, rep = False, "exception: %r" % e
    head = rep.strip().splitlines()[0] if rep else ""
    m = re.search(r"\bcat=([\w-]+)", head)
    return dict(task, ok=ok, cat=m.group(1) if m else ("compile" if "compile failed" in head else None),
                first=head[:200], secs=round(time.time() - t0, 2))


# ---- output -----------------------------------------------------------------------------

def sha256(path):
    with open(path, "rb") as fh:
        return hashlib.sha256(fh.read()).hexdigest()


def write_tables(units, a):
    used = sorted({u.profile[0] for u in units} | {f.pin[0] for u in units for f, _ in u.overrides},
                  key=list(COMPILERS).index)
    lines = [
        "# config/SLUS-20836/units.tsv — one build profile per translation unit (docs/engine/build-profiles.md).",
        "# GENERATED by tools/gen_unit_profiles.py from the per-function pins, the build-settings sweeps and",
        "# config/SLUS-20836/exceptions.txt; reviewed and committed. Regenerate rather than hand-edit a row; to add or",
        "# change a unit by hand follow docs/engine/build-profiles.md and keep the columns below.",
        "#",
        "# @compiler\tid\trepository-relative executable\tSHA-256",
        "# lo\thi\tname\tcompiler\tflags\texceptions\tstatus\tsource",
        "#   lo <= function start < hi; flags is the complete flag string except the exception mode;",
        "#   exceptions on|off (off adds -Cpp_exceptions off to an MWCC compile); status - or provisional",
        "#   (the members' evidence has no common profile: the majority profile is recorded and the",
        "#   dissenting members keep a provisional row in unit-flags.tsv / unit-compilers.tsv).",
    ]
    for cid in used:
        lines.append("@compiler\t%s\t%s\t%s" % (cid, COMPILERS[cid], sha256(os.path.join(ROOT, COMPILERS[cid]))))
    for u in units:
        lines.append("0x%08x\t0x%08x\t%s\t%s\t%s\t%s\t%s\t%s" % (
            u.lo, u.hi, u.name, u.profile[0], u.profile[1], u.exceptions, u.status,
            ("%s; %s; %s" % (u.evidence, u.exception_source, u.source)).replace("\t", " ")))
    with open(os.path.join(ROOT, a.units_out), "w") as fh:
        fh.write("\n".join(lines) + "\n")
    # per-function overrides: flags where flags or exception mode differ, compiler where it differs
    flag_lines = [
        "# Per-function flag overrides — tools/unitflags.py; the unit profile is config/SLUS-20836/units.tsv.",
        "# Every row is provisional: the function has not been reproduced under its unit's profile and",
        "# `make check` reports it as foreign-profile debt until it is (docs/engine/build-profiles.md).",
        "# GENERATED by tools/gen_unit_profiles.py; a hand-added row keeps the same four columns.",
        "# va\tflags\tstatus\treason",
    ]
    comp_lines = [
        "# Per-function compiler overrides — tools/unitcompilers.py; the unit profile is config/SLUS-20836/units.tsv.",
        "# Every row is provisional: the function has not been reproduced under its unit's compiler and",
        "# `make check` reports it as foreign-profile debt until it is (docs/engine/build-profiles.md).",
        "# GENERATED by tools/gen_unit_profiles.py; a hand-added row keeps the same five columns.",
        "# va\trepository-relative executable\tSHA-256\tstatus\treason",
    ]
    nflags = ncomp = 0
    for u in units:
        for f, reason in sorted(u.overrides, key=lambda fr: fr[0].va):
            cid, flags, mode = f.pin
            mode = mode or "on"
            if cid != u.profile[0]:
                comp_lines.append("0x%08x\t%s\t%s\tprovisional\t%s" % (
                    f.va, COMPILERS[cid], sha256(os.path.join(ROOT, COMPILERS[cid])), reason))
                ncomp += 1
            # the mode is part of the row even for a C file: C emits no metadata, but the code of a
            # C unit can still depend on it (luaK_testgo's interprocedural register allocation)
            mode_matters = mode != u.exceptions and cid != "ee-gcc"
            if flags != u.profile[1] or mode_matters:
                full = flags + (" -Cpp_exceptions " + mode if mode_matters else "")
                flag_lines.append("0x%08x\t%s\tprovisional\t%s" % (f.va, full, reason))
                nflags += 1
    with open(os.path.join(ROOT, a.flags_out), "w") as fh:
        fh.write("\n".join(flag_lines) + "\n")
    with open(os.path.join(ROOT, a.compilers_out), "w") as fh:
        fh.write("\n".join(comp_lines) + "\n")
    return nflags, ncomp


def report(units, functions, old_flag_rows, old_comp_rows):
    provisional = [u for u in units if u.status == "provisional"]
    print("units: %d (%d library, %d class, %d unlabeled); %d provisional" % (
        len(units), sum(u.kind == "library" for u in units), sum(u.kind == "class" for u in units),
        sum(u.kind == "unlabeled" for u in units), len(provisional)))
    print("exceptions: %d units on, %d off (%d undetermined)" % (
        sum(u.exceptions == "on" for u in units), sum(u.exceptions == "off" for u in units),
        sum("undetermined" in u.exception_source for u in units)))
    profiles = collections.Counter(u.profile for u in units)
    print("profiles: " + ", ".join("%d×%s %s" % (n, c, f) for (c, f), n in profiles.most_common()))
    print()
    print("units whose members have no common profile (provisional; majority profile recorded):")
    for u in provisional:
        print("  %-44s %#08x-%#08x %s %s exc=%s" % (u.name[:44], u.lo, u.hi, u.profile[0], u.profile[1], u.exceptions))
        print("      %s" % u.source)
        for f, reason in u.overrides:
            print("      override %#x %-40s pin %s %s %s%s" % (
                f.va, f.name[:40], f.pin[0], f.pin[1], f.pin[2] or "on", "" if "untested" not in reason else " (untested)"))
    n_over = sum(len(u.overrides) for u in units)
    members = {f.va for u in units for f in u.members}
    kept_f = {f.va for u in units for f, _ in u.overrides
              if f.pin[1] != u.profile[1] or ((f.pin[2] or "on") != u.exceptions and f.pin[0] != "ee-gcc")}
    kept_c = {f.va for u in units for f, _ in u.overrides if f.pin[0] != u.profile[0]}
    print()
    print("per-function rows: unit-flags.tsv %d -> %d (%d deleted as covered by the unit profile), "
          "unit-compilers.tsv %d -> %d (%d deleted); %d functions keep an override" % (
              len(old_flag_rows), len(kept_f), len(set(old_flag_rows) - kept_f),
              len(old_comp_rows), len(kept_c), len(set(old_comp_rows) - kept_c), n_over))
    stale = [va for va in list(old_flag_rows) + list(old_comp_rows) if va not in members]
    if stale:
        print("rows for bodies not compiled on their own (emitted members of a compiler unit): %s — kept as untested "
              "overrides where the pin differs from the unit profile, else dropped"
              % ", ".join("%#x" % v for v in sorted(set(stale))[:10]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--src", default="src")
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")))
    ap.add_argument("--unit-objects", default=None)
    ap.add_argument("--unit-flags", default=None, help="the per-function flag table to migrate (default config/SLUS-20836/unit-flags.tsv)")
    ap.add_argument("--unit-compilers", default=None, help="the per-function compiler table to migrate")
    ap.add_argument("--units", default=None,
                    help="the units table whose profiles are the current pins (default config/SLUS-20836/units.tsv when it exists; "
                         "absent on the first generation, when the per-function rows alone are the pins)")
    ap.add_argument("--categories", default=CATEGORIES, help="data/check-categories.tsv of the current tree")
    ap.add_argument("--results", action="append", default=[], help="JSON-lines verify results (repeatable)")
    ap.add_argument("--from-check", action="store_true",
                    help="read data/check-categories.tsv (the last `make check`) as evidence: a row verified under the "
                         "current resolution says whether the unit profile (or, for foreign-profile, only the override) "
                         "reproduces the function")
    ap.add_argument("--sweep-tasks", help="write the undecided (function, candidate) pairs here as JSON lines")
    ap.add_argument("--sweep", metavar="RESULTS", help="verify the undecided pairs now and append the results to this file")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--write", action="store_true", help="rewrite config/SLUS-20836/units.tsv, unit-flags.tsv and unit-compilers.tsv")
    ap.add_argument("--units-out", default="config/SLUS-20836/units.tsv")
    ap.add_argument("--flags-out", default="config/SLUS-20836/unit-flags.tsv")
    ap.add_argument("--compilers-out", default="config/SLUS-20836/unit-compilers.tsv")
    a = ap.parse_args(argv)
    os.chdir(ROOT)
    img = open(a.elf, "rb").read()
    functions = build_functions(a, img)
    registry = unitobjects.load(a.unit_objects) if a.unit_objects else unitobjects.load()
    GROUP_OWNERS.update(g.owner for g in (registry.values() if isinstance(registry, dict) else registry))
    units = build_units(functions)
    evidence = Evidence()
    for path in a.results:
        print("evidence: %d results from %s" % (evidence.add_file(path), path))
    if a.from_check:
        print("evidence: %d results from %s under the current resolution" % (
            evidence.add_check(a.categories, functions, a), a.categories))
    if a.sweep:
        a.results.append(a.sweep)
        if os.path.exists(a.sweep):
            evidence.add_file(a.sweep)
    undecided = evaluate(units, evidence)
    print("undecided (function, candidate) pairs: %d" % len(undecided))
    if a.sweep_tasks:
        with open(a.sweep_tasks, "w") as fh:
            for f, (cid, flags), mode in undecided:
                fh.write(json.dumps(dict(va=f.va, name=f.name, path=f.path, compiler=COMPILERS[cid],
                                         flags=flags + (" -Cpp_exceptions off" if mode == "off" and cid != "ee-gcc" else ""))) + "\n")
    if a.sweep and undecided:
        run_sweep(undecided, a.sweep, a.jobs)
        evidence.add_file(a.sweep)
        undecided = evaluate(units, evidence)
        print("undecided after the sweep: %d" % len(undecided))
    choose(units)
    old_flags = unitflags.load_rows(a.unit_flags or unitflags.DEFAULT_PATH)
    old_comps = unitcompilers.load_rows(a.unit_compilers or unitcompilers.DEFAULT_PATH)
    report(units, functions, old_flags, old_comps)
    if a.write:
        nflags, ncomp = write_tables(units, a)
        print("written: %s (%d units), %s (%d rows), %s (%d rows)" % (
            a.units_out, len(units), a.flags_out, nflags, a.compilers_out, ncomp))
    return 0


if __name__ == "__main__":
    sys.exit(main())
