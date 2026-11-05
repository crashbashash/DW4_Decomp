#!/usr/bin/env python3
"""perm_refine.py — get more out of a decomp-permuter search on one function than a single long run gives.

`tools/permuter_one.py` builds a project (`base.c`, `target.o`, `compile.sh`) and runs the permuter
on it once. The permuter keeps restarting from the same `base.c`, so its improvements do not add
up, and a lower score is sometimes bought by losing code (a call hoisted behind an early return, a
store folded away). This tool works on the same project folder and adds three things:

  merge   The outputs that tie or nearly tie the best one usually differ from `base.c` in different
          places. Every small change any of them makes is tried on its own on top of `base.c`; the
          ones that lower the score are then stacked, re-scoring after each.
  rounds  Search in short rounds; the best acceptable output of a round becomes the next round's
          `base.c`, with a merge every few rounds.
  guard   A candidate is acceptable only if it does not lose code the retail function has: compared
          with the current `base.c` it may not be missing more of the target's calls, have fewer
          of its stores to memory, or shrink below a share of its instruction count.

    perm_refine.py merge  DIR [--within 0.02] [--max-lines 12] [--apply]
    perm_refine.py rounds DIR [--rounds 20] [--budget 60] [--jobs 4] [--stall 4] [--merge-every 4]
    perm_refine.py facts  DIR [FILE.c]        # what the guard sees for base.c (or FILE.c) and the target

DIR is the project folder; its name is the function's symbol (`--function NAME` otherwise). The
score used here is the number of instruction-level differences from `target.o`; like the
permuter's own, it is a search measure and not proof. Nothing is written to `src/`: a result that
reaches 0 still has to pass `tools/verify.py`, and its source carries the usual
`/* matching construct: permuter — … */` note where a shape came from the search.
"""
import argparse
import collections
import difflib
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
OBJDUMP = os.environ.get("DW4_OBJDUMP", "mipsel-linux-gnu-objdump")
STORE = re.compile(r"^(?:sb|sh|sw|sd|sq|swl|swr|sdl|sdr|swc1|sdc1|sqc2)$")
STACK_BASE = re.compile(r"\((?:sp|s8|fp)\)\s*$")
LABEL = re.compile(r"^[0-9a-f]+ <([^>]+)>:\s*$")
INSN = re.compile(r"^\s*([0-9a-f]+):\s+[0-9a-f]{8}\s+(\S+)\s*(.*)$")
RELOC = re.compile(r"^\s*([0-9a-f]+):\s+(R_MIPS_\w+)\s+(\S+)")
Facts = collections.namedtuple("Facts", "tokens calls stores")


# ---- what a compiled function contains -------------------------------------------------------

def parse_listing(listing, function):
    """Facts for `function` from `objdump -d -r` text: its instructions as comparable tokens, the
    symbols it calls (a multiset) and how many of its instructions store to memory off the stack."""
    tokens, calls, stores = [], collections.Counter(), 0
    inside = False
    for line in listing.splitlines():
        label = LABEL.match(line)
        if label:
            inside = label.group(1) == function
            continue
        if not inside:
            continue
        reloc = RELOC.match(line)
        if reloc:
            kind, symbol = reloc.group(2), reloc.group(3)
            if kind == "R_MIPS_26":
                calls[symbol] += 1
            if tokens:                      # the address field of a relocated instruction is the symbol
                tokens[-1] = "%s %s:%s" % (tokens[-1].split(" ", 1)[0], kind, symbol)
            continue
        insn = INSN.match(line)
        if not insn:
            continue
        mnemonic, operands = insn.group(2), insn.group(3).split("<", 1)[0].strip()
        if mnemonic[0] in "bj" and mnemonic not in ("break",):
            operands = re.sub(r"(?:0x)?[0-9a-f]+$", "@", operands)      # a branch target moves with the code
        tokens.append(("%s %s" % (mnemonic, operands)).strip())
        if STORE.match(mnemonic) and not STACK_BASE.search(operands):
            stores += 1
    return Facts(tokens, calls, stores)


def object_facts(path, function):
    """Facts for `function` in the object `path`, or None when it is not there."""
    listing = subprocess.run([OBJDUMP, "-d", "-r", "-z", path], capture_output=True, text=True).stdout
    facts = parse_listing(listing, function)
    return facts if facts.tokens else None


def difference(candidate, target):
    """How many instruction-level edits separate two functions (0 means the same sequence)."""
    edits = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, candidate.tokens, target.tokens, autojunk=False).get_opcodes():
        if tag != "equal":
            edits += max(i2 - i1, j2 - j1)
    return edits


def loses_code(candidate, base, target, min_share=0.9):
    """Why `candidate` is unacceptable next to `base`, or "" when it keeps what the target has.

    Each test is relative to the current base, so a draft that already lacks something is not held
    to a standard it never met; it only may not get worse."""
    def missing_calls(facts):
        return sum((target.calls - facts.calls).values())

    def missing_stores(facts):
        return max(0, target.stores - facts.stores)

    if missing_calls(candidate) > missing_calls(base):
        lost = target.calls - candidate.calls - (target.calls - base.calls)
        return "drops a call the target makes (%s)" % ", ".join(sorted(lost)) if lost else "drops a call the target makes"
    if missing_stores(candidate) > missing_stores(base):
        return "has %d stores to memory, the target has %d" % (candidate.stores, target.stores)
    floor = min(len(base.tokens), int(len(target.tokens) * min_share))
    if len(candidate.tokens) < floor:
        return "shrinks to %d instructions, the target has %d" % (len(candidate.tokens), len(target.tokens))
    return ""


# ---- a project folder ------------------------------------------------------------------------

class Project:
    def __init__(self, folder, function=None, min_share=0.9):
        self.folder = os.path.abspath(folder)
        self.function = function or os.path.basename(self.folder.rstrip(os.sep))
        self.min_share = min_share
        self.target = object_facts(os.path.join(self.folder, "target.o"), self.function)
        if self.target is None:
            raise SystemExit("%s: target.o does not define %s (pass --function)" % (folder, self.function))

    @property
    def base_path(self):
        return os.path.join(self.folder, "base.c")

    def compile(self, text):
        """Facts of the function compiled from `text`, or None when it does not compile."""
        with tempfile.TemporaryDirectory(dir=self.folder) as scratch:
            source, obj = os.path.join(scratch, "candidate.c"), os.path.join(scratch, "candidate.o")
            with open(source, "w") as handle:
                handle.write(text)
            done = subprocess.run(["bash", os.path.join(self.folder, "compile.sh"), source, "-o", obj],
                                  capture_output=True, text=True)
            if done.returncode or not os.path.exists(obj):
                return None
            return object_facts(obj, self.function)

    def score(self, facts):
        return difference(facts, self.target)

    def outputs(self, earlier_rounds=True):
        """[(permuter score, source path)] for the outputs the permuter has written here, lowest
        score first; `earlier_rounds=False` leaves out the ones filed under rounds/."""
        found = []
        for root in [self.folder] + (sorted(self._round_dirs()) if earlier_rounds else []):
            for name in os.listdir(root):
                matched = re.match(r"output-(\d+)-\d+$", name)
                source = os.path.join(root, name, "source.c")
                if matched and os.path.exists(source):
                    found.append((int(matched.group(1)), source))
        return sorted(found)

    def _round_dirs(self):
        rounds = os.path.join(self.folder, "rounds")
        if not os.path.isdir(rounds):
            return []
        return [path for path in (os.path.join(rounds, name) for name in os.listdir(rounds)) if os.path.isdir(path)]


# ---- merge -----------------------------------------------------------------------------------

Change = collections.namedtuple("Change", "start end lines")      # base lines [start, end) -> lines


def changes_between(base_lines, other_lines, max_lines):
    """The edits that turn base into other, each no longer than `max_lines` on either side."""
    out = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, base_lines, other_lines, autojunk=False).get_opcodes():
        if tag != "equal" and i2 - i1 <= max_lines and j2 - j1 <= max_lines:
            out.append(Change(i1, i2, tuple(other_lines[j1:j2])))
    return out


def overlaps(change, chosen):
    for other in chosen:
        if change.start < other.end and other.start < change.end:
            return True
        if change.start == change.end == other.start or other.start == other.end == change.start:
            return True                     # two insertions at one point: order would be a guess
    return False


def apply_changes(base_lines, chosen):
    lines = list(base_lines)
    for change in sorted(chosen, key=lambda c: (c.start, c.end), reverse=True):
        lines[change.start:change.end] = change.lines
    return lines


def merge(project, within=0.02, max_lines=12, jobs=4, log=print):
    """-> (text, score, base score). The best stack of small changes taken from the near-best outputs."""
    base_text = open(project.base_path).read()
    base_lines = base_text.split("\n")
    base = project.compile(base_text)
    if base is None:
        raise SystemExit("base.c does not compile")
    base_score = project.score(base)
    outputs = project.outputs()
    if not outputs:
        log("merge: the permuter has written no outputs here yet")
        return base_text, base_score, base_score
    best = outputs[0][0]
    near = [path for score, path in outputs if score <= best * (1 + within)]
    seen, candidates = set(), []
    for path in near:
        for change in changes_between(base_lines, open(path).read().split("\n"), max_lines):
            if change not in seen:
                seen.add(change)
                candidates.append(change)
    log("merge: %d outputs within %.0f %% of the best, %d distinct small changes" % (len(near), within * 100, len(candidates)))

    def trial(chosen):
        facts = project.compile("\n".join(apply_changes(base_lines, chosen)))
        if facts is None or loses_code(facts, base, project.target, project.min_share):
            return None
        return project.score(facts)

    with ThreadPoolExecutor(max_workers=max(1, jobs)) as pool:
        alone = list(pool.map(lambda change: trial([change]), candidates))
    helpful = sorted(((score, index) for index, score in enumerate(alone) if score is not None and score < base_score))
    log("merge: %d changes lower the score on their own (base %d)" % (len(helpful), base_score))
    chosen, score = [], base_score
    for _alone, index in helpful:
        change = candidates[index]
        if overlaps(change, chosen):
            continue
        stacked = trial(chosen + [change])
        if stacked is not None and stacked < score:
            chosen, score = chosen + [change], stacked
    log("merge: stacked %d changes, score %d -> %d" % (len(chosen), base_score, score))
    return "\n".join(apply_changes(base_lines, chosen)), score, base_score


def replace_base(project, text, note):
    stamp = time.strftime("%H%M%S")
    shutil.copyfile(project.base_path, os.path.join(project.folder, "base.before-%s-%s.c" % (note, stamp)))
    with open(project.base_path, "w") as handle:
        handle.write(text)


# ---- rounds ----------------------------------------------------------------------------------

def best_acceptable(project, base, base_score, log):
    """The lowest-scoring new output that keeps the target's code: (score, text) or None."""
    for _permuter_score, path in project.outputs(earlier_rounds=False)[:8]:
        text = open(path).read()
        facts = project.compile(text)
        if facts is None:
            continue
        why = loses_code(facts, base, project.target, project.min_share)
        if why:
            log("   rejected %s: %s" % (os.path.relpath(path, project.folder), why))
            continue
        score = project.score(facts)
        if score < base_score:
            return score, text
    return None


def rounds(project, count, budget, jobs, stall, merge_every, within, max_lines, log=print):
    import permuter_one
    keep = os.path.join(project.folder, "rounds")
    os.makedirs(keep, exist_ok=True)
    if not os.path.exists(os.path.join(keep, "base.start.c")):
        shutil.copyfile(project.base_path, os.path.join(keep, "base.start.c"))
    idle = 0
    for number in range(1, count + 1):
        base_text = open(project.base_path).read()
        base = project.compile(base_text)
        if base is None:
            raise SystemExit("base.c does not compile")
        base_score = project.score(base)
        if base_score == 0:
            break
        permuter_one.run(project.folder, budget, jobs=jobs)
        found = best_acceptable(project, base, base_score, log)
        round_dir = os.path.join(keep, "r%03d" % number)
        os.makedirs(round_dir, exist_ok=True)
        for name in os.listdir(project.folder):          # each round keeps its own outputs
            if re.match(r"output-\d+-\d+$", name):
                shutil.move(os.path.join(project.folder, name), os.path.join(round_dir, name))
        if found:
            score, text = found
            replace_base(project, text, "r%03d" % number)
            log("round %d: %d -> %d" % (number, base_score, score))
            idle = 0
        else:
            idle += 1
            log("round %d: no acceptable improvement (%d in a row)" % (number, idle))
        if merge_every and (number % merge_every == 0 or idle >= stall):
            text, score, before = merge(project, within, max_lines, jobs, log)
            if score < before:
                replace_base(project, text, "merge")
                idle = 0
        if idle >= stall:
            log("stopping: %d rounds without an acceptable improvement" % idle)
            break
    final = project.compile(open(project.base_path).read())
    return project.score(final) if final else None


# ---- command line ----------------------------------------------------------------------------

def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("command", choices=["merge", "rounds", "facts"])
    parser.add_argument("folder")
    parser.add_argument("source", nargs="?", help="facts: a C file to compile instead of base.c")
    parser.add_argument("--function", help="the function's symbol (default: the folder's name)")
    parser.add_argument("--within", type=float, default=0.02, help="merge: outputs this close to the best score take part")
    parser.add_argument("--max-lines", type=int, default=12, help="merge: skip changes longer than this")
    parser.add_argument("--apply", action="store_true", help="merge: replace base.c when the merge scores lower")
    parser.add_argument("--rounds", type=int, default=20)
    parser.add_argument("--budget", type=int, default=60, help="rounds: seconds of search per round")
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--stall", type=int, default=4, help="rounds: stop after this many rounds without improvement")
    parser.add_argument("--merge-every", type=int, default=4, help="rounds: merge after every N rounds (0: never)")
    parser.add_argument("--min-share", type=float, default=0.9,
                        help="guard: a candidate may not shrink below this share of the target's instruction count")
    args = parser.parse_args(argv)
    project = Project(args.folder, args.function, args.min_share)

    if args.command == "facts":
        path = args.source or project.base_path
        facts = project.compile(open(path).read())
        target = project.target
        print("target : %d instructions, %d stores off the stack, calls %s"
              % (len(target.tokens), target.stores, dict(target.calls) or "none"))
        if facts is None:
            print("%s does not compile" % os.path.basename(path))
            return 1
        print("%-7s: %d instructions, %d stores off the stack, calls %s; %d differences from the target"
              % (os.path.basename(path), len(facts.tokens), facts.stores, dict(facts.calls) or "none", project.score(facts)))
        return 0
    if args.command == "merge":
        text, score, before = merge(project, args.within, args.max_lines, args.jobs)
        with open(os.path.join(project.folder, "merged.c"), "w") as handle:
            handle.write(text)
        if args.apply and score < before:
            replace_base(project, text, "merge")
            print("base.c replaced (the previous one is kept beside it)")
        return 0
    score = rounds(project, args.rounds, args.budget, args.jobs, args.stall, args.merge_every, args.within, args.max_lines)
    print("final score: %s%s" % (score, "  (run tools/verify.py on base.c before believing it)" if score == 0 else ""))
    return 0


if __name__ == "__main__":
    sys.path.insert(0, HERE)
    sys.exit(main())
