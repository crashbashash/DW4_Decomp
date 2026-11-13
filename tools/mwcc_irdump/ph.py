#!/usr/bin/env python3
"""ph.py LOG [PHASE] [--function NAME] [--nth N] [--fold] [--changes] [--list]: read an IR dump log.

LOG is the `<source>.log` the dump copy writes (dump.py). PHASE is text of a phase name, as in "IRO_CommonSubs"
or "after IRO_RotateLoop"; --list prints the phase headers instead. Some phases run more than once (the propagation
group, "Creating PreHeader"); --nth picks the N-th match, counting from 0, and --all every match. --function keeps
one function of a log that holds several (the dump writes MWCC's short name for it).

The listing: each flow-graph node gives its successors, predecessors and linear IR, one numbered IR node per line,
`72: EADD 73 75 <ind> <subs>` adding nodes 73 and 75. Dominator, loop-depth and must-reach lines are left out.
--fold folds the linear IR back into statements, one per line (`*(i) = 0`, `IfNot ((0 < ...)) goto @43`), with the
loop depth of each flow-graph node; `(cast)` is a conversion node, `@N` a compiler temporary in creation order.
--changes prints, of the phases selected, only those whose IR differs from the phase before (index numbers
ignored), which is the quickest way to see which phase made a change. In the IRO_CommonSubs phase, "Replacing common
sub at N" lines name the IR nodes common-subexpression elimination replaced with a shared value; comparing their count
between two spellings says how many loads one of them keeps separate.

`#pragma opt_dumptypes on` at the top of the compiled file adds types to the listing.

    python3 tools/mwcc_irdump/ph.py /tmp/irdump/out/t.log "after IRO_CommonSubs"
    python3 tools/mwcc_irdump/ph.py /tmp/irdump/out/t.log --fold --changes --all ""
"""
import argparse
import re
import sys

SKIP = ("---", "MustReach", "LoopDepth", "Dom:", "*****", "Dumps for pass")
HEADER = re.compile(r"^Dumping function (\S+) (after|before) (.*?)\s*$")
BIN = {"EADD": "+", "ESUB": "-", "ESHL": "<<", "ESHR": ">>", "EMUL": "*", "EDIV": "/", "ELESS": "<", "EGREATER": ">",
       "EEQU": "==", "ENOTEQU": "!=", "ELESSEQU": "<=", "EGREATEREQU": ">=", "EAND": "&", "EOR": "|", "EXOR": "^",
       "EADDASS": "+=", "ESUBASS": "-="}


def phases(text):
    """[(function, 'after'/'before', phase name, body text)] in log order. A phase prints its own messages
    ("Replacing common sub at N") before its header; they are moved into the phase that printed them."""
    out, current, pending = [], None, []
    for line in text.split("\n"):
        m = HEADER.match(line)
        if m:
            current = [m.group(1), m.group(2), m.group(3), pending]
            pending = []
            out.append(current)
        elif line.startswith("Replacing common sub"):
            pending.append(line)
        elif current is not None:
            current[3].append(line)
    return [(f, w, n, "\n".join(body)) for f, w, n, body in out]


def raw(body):
    return "\n".join(line for line in body.split("\n") if line.strip() and not line.startswith(SKIP))


def fold(body):
    """The linear IR of one phase folded into statements."""
    out, expr = [line for line in body.split("\n") if line.startswith("Replacing common sub")], {}
    for blk in re.split(r"\n(?=Flowgraph node)", body):
        m = re.match(r"Flowgraph node (\d+).*?\nSucc = (.*?)\nPred = (.*?)\n.*?LoopDepth = (\d+)", blk, re.S)
        if not m:
            continue
        out.append("--- node %s succ[%s] pred[%s] depth %s" % (m.group(1), m.group(2).strip(), m.group(3).strip(), m.group(4)))
        used, stmts = set(), []

        def e(k):
            used.add(int(k))
            return expr.get(int(k), "#" + k)
        for line in blk.splitlines():
            mm = re.match(r"\s*(\d+): (\S+)\s*(.*)$", line)
            if not mm:
                continue
            n, op = int(mm.group(1)), mm.group(2)
            rest = re.sub(r"<[\w ]+>", "", mm.group(3)).strip()
            a = rest.split()
            stmt = None
            if op == "Operand":
                expr[n] = rest
            elif op == "EINDIRECT":
                expr[n] = "*(%s)" % e(a[0])
            elif op in BIN:
                expr[n] = "(%s %s %s)" % (e(a[0]), BIN[op], e(a[1]))
                stmt = expr[n] if op.endswith("ASS") else None
            elif op == "EASS":
                expr[n] = stmt = "%s = %s" % (e(a[0]), e(a[1]))
            elif op == "ETYPCON":
                expr[n] = "(cast)%s" % e(a[0])
            elif op in ("EPOSTINC", "EPREINC", "EPOSTDEC", "EPREDEC"):
                expr[n] = stmt = e(a[0]) + ("++" if "INC" in op else "--")
            elif op == "Funccall":
                f = re.match(r"(\d+)\((.*?)\)", rest)
                expr[n] = stmt = "%s(%s)" % (e(f.group(1)), ", ".join(e(x) for x in f.group(2).split(",") if x.strip()))
            elif op in ("If", "IfNot"):
                stmt = "%s (%s) goto %s" % (op, e(a[0]), a[1])
            elif op == "Return":
                stmt = "return %s" % (e(a[0]) if a else "")
            elif op in ("Goto", "Label"):
                stmt = "%s %s" % (op, rest)
            elif op not in ("Nop", "End"):
                expr[n] = "%s[%s]" % (op, rest)
            if stmt is not None:
                stmts.append((n, stmt))
        for n, s in stmts:
            if n not in used or s.split()[0] in ("If", "IfNot", "return", "Goto", "Label"):
                out.append("   %d: %s" % (n, s))
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("log")
    ap.add_argument("phase", nargs="?")
    ap.add_argument("--function")
    ap.add_argument("--nth", type=int, default=0)
    ap.add_argument("--all", action="store_true", help="every matching phase, not only the N-th")
    ap.add_argument("--fold", action="store_true")
    ap.add_argument("--changes", action="store_true")
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args()
    found = [p for p in phases(open(a.log, errors="replace").read().replace("\r", ""))
             if a.function is None or p[0] == a.function]
    if a.list or a.phase is None:
        for fn, when, name, _ in found:
            print("%s: %s %s" % (fn, when, name))
        return 0
    shown, previous, hits = [], {}, 0
    for fn, when, name, body in found:
        text = fold(body) if a.fold else raw(body)
        key = re.sub(r"^\s*\d+: ", "", text, flags=re.M)
        changed = previous.get(fn) != key
        previous[fn] = key
        if a.phase not in "%s %s" % (when, name):
            continue
        if a.changes and not changed:
            continue
        if a.all or hits == a.nth:
            shown.append("===== %s: %s %s\n%s" % (fn, when, name, text))
        hits += 1
    if not shown:
        print("no phase matching %r" % a.phase, file=sys.stderr)
        return 1
    print("\n".join(shown))
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except BrokenPipeError:
        sys.exit(0)
