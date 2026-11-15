#!/usr/bin/env python3
"""gate_stamp.py — remember which source trees passed the four gates, for the pre-push hook.

A task is complete when `make check`, `make link`, `make typed-check` and `make hygiene` pass on the final
tree (CLAUDE.md, "Completion and regression"). Each of those targets runs `start GATE` first and `pass GATE`
last, so a gate that fails never reaches `pass`. `pass` stamps the tree when the tree did not change during
the run, apart from the files the gates themselves regenerate (`data/check-categories.tsv`,
`data/check-data.tsv`, `config/SLUS-20836/layout.txt`, and the progress pages `make check` writes), and, for
`check`, when the match count is at least
`functions.fully_verified` in HEAD's `docs/progress.json`. It never changes the target's exit code: a run
that cannot be stamped says why on one `gate-stamp:` line. .githooks/pre-push refuses a pushed commit whose
tree is not stamped by all four (docs/engine/oracle-runner.md, "The local stamp").

The tree is `git write-tree` of the working tree as `git add -A` would stage it: every file that is not
ignored, with its content on disk, built in a temporary index (the real index is not touched). So the
commit has to hold exactly what the gates saw: a new source file is committed with the change, and a stray
untracked file is removed or ignored before the gates run. Stamps are appended to `dw4-gate-stamps` in the
git common directory (shared by every worktree of a clone, never committed); DW4_GATE_STAMPS names another
file.

  python3 tools/gate_stamp.py tree               # the working tree's id
  python3 tools/gate_stamp.py status [REV]       # the gates stamped for REV's tree (default: the working tree)
  python3 tools/gate_stamp.py missing REV        # the gates REV's tree lacks, one per line; exit 1 if any
  python3 tools/gate_stamp.py start|pass GATE    # what the Makefile runs around a gate
"""
# The idea (a gate run recorded against the exact tree id, checked before the commit leaves) is from
# dq8-decomp's .claude/hooks/gate-guard.py (CC0, https://github.com/Yakuru-43/dq8-decomp).
import json
import os
import shutil
import subprocess
import sys
import tempfile
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GATES = ("check", "link", "typed-check", "hygiene")
# tracked files the gates write; a run that only rewrote these verified the tree it leaves behind
OUTPUTS = {"data/check-categories.tsv", "data/check-data.tsv", "config/SLUS-20836/layout.txt",
           "PROGRESS.md", "docs/progress.json", "README.md"}
CATEGORIES = os.path.join(ROOT, "build", "check-categories.tsv")


def git(*args, env=None):
    r = subprocess.run(("git",) + args, cwd=ROOT, env=env, capture_output=True, text=True)
    if r.returncode:
        raise RuntimeError("git %s: %s" % (args[0], (r.stderr or r.stdout).strip()))
    return r.stdout.strip()


def stamps_path():
    return os.environ.get("DW4_GATE_STAMPS") or os.path.join(
        os.path.abspath(os.path.join(ROOT, git("rev-parse", "--git-common-dir"))), "dw4-gate-stamps")


def work_tree():
    """The tree id of the working tree: every file that is not ignored, as it is on disk."""
    index = os.path.join(ROOT, git("rev-parse", "--git-path", "index"))
    with tempfile.TemporaryDirectory() as tmp:
        env = dict(os.environ, GIT_INDEX_FILE=os.path.join(tmp, "index"))
        if os.path.exists(index):
            shutil.copyfile(index, env["GIT_INDEX_FILE"])   # keeps the stat cache: only edits are rehashed
        else:
            git("read-tree", "HEAD", env=env)
        git("add", "-A", "--", ":/", env=env)
        return git("write-tree", env=env)


def stamped(tree):
    try:
        with open(stamps_path()) as fh:
            return {f[1] for f in (line.split() for line in fh) if len(f) >= 2 and f[0] == tree}
    except FileNotFoundError:
        return set()


def start_file(gate):
    return os.path.join(ROOT, "build", "gate-stamp", gate + ".start")


def start(gate):
    os.makedirs(os.path.dirname(start_file(gate)), exist_ok=True)
    with open(start_file(gate), "w") as fh:
        fh.write("%s %f\n" % (work_tree(), time.time()))


def check_matches(began):
    """None when `make check`'s match count holds against HEAD, else the reason it does not."""
    if not os.path.exists(CATEGORIES) or os.path.getmtime(CATEGORIES) < began:
        return "build/check-categories.tsv was not written by this run"
    with open(CATEGORIES) as fh:
        matched = sum(1 for line in fh if line.split("\t")[2:3] == ["match"])
    try:
        baseline = json.loads(git("show", "HEAD:docs/progress.json"))["functions"]["fully_verified"]
    except (RuntimeError, KeyError, ValueError) as exc:
        return "no functions.fully_verified in HEAD's docs/progress.json (%s)" % exc
    if matched < baseline:
        return "%d match, below functions.fully_verified %d in HEAD's docs/progress.json" % (matched, baseline)
    return None


def record(gate):
    """Stamp the tree `gate` just passed on; returns the line to print."""
    try:
        with open(start_file(gate)) as fh:
            began_tree, began = fh.read().split()
        os.remove(start_file(gate))
    except (FileNotFoundError, ValueError):
        return "gate-stamp: %s: no start record (build/gate-stamp/%s.start); not stamped" % (gate, gate)
    tree = work_tree()
    if tree != began_tree:
        changed = set(git("diff-tree", "-r", "--name-only", began_tree, tree).splitlines())
        if changed - OUTPUTS:
            some = sorted(changed - OUTPUTS)
            return "gate-stamp: %s: the tree changed during the run (%s%s); not stamped" % (
                gate, ", ".join(some[:3]), ", ..." if len(some) > 3 else "")
    if gate == "check":
        why = check_matches(float(began))
        if why:
            return "gate-stamp: check: %s; not stamped" % why
    with open(stamps_path(), "a") as fh:
        fh.write("%s %s %s\n" % (tree, gate, time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())))
    return "gate-stamp: %s passed on tree %s" % (gate, tree[:12])


def tree_of(rev):
    return work_tree() if rev is None else git("rev-parse", "--verify", rev + "^{tree}")


def main(argv):
    cmd, arg = (argv + [None, None])[:2]
    try:
        if cmd in ("start", "pass") and arg in GATES:
            if cmd == "start":
                start(arg)
            else:
                print(record(arg))
            return 0
        if cmd == "tree" and arg is None:
            print(work_tree())
            return 0
        if cmd == "status":
            tree = tree_of(arg)
            have = stamped(tree)
            print("tree %s: %s" % (tree, "  ".join("%s %s" % (g, "yes" if g in have else "no") for g in GATES)))
            return 0
        if cmd == "missing" and arg:
            lack = [g for g in GATES if g not in stamped(tree_of(arg))]
            if lack:
                print("\n".join(lack))
            return 1 if lack else 0
    except (RuntimeError, OSError) as exc:
        if cmd in ("start", "pass"):        # never fail a gate's target over its stamp
            print("gate-stamp: %s: %s; not stamped" % (arg, exc))
            return 0
        print("gate-stamp: %s" % exc, file=sys.stderr)
        return 2
    print(__doc__.strip().split("\n\n")[-1], file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
