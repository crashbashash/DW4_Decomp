#!/usr/bin/env python3
"""regalloc.py FUNCTION_OR_VA CANDIDATE.c[pp] [--flags "..."] [--compiler EXE] [--max-pool N] [--show-all]

Register-colouring diagnosis for ANY single function (the general entry point of the tools in this folder).

What it does, in order:
  1. resolves the function (a symbol name from config/SLUS-20836/symbols.txt, or a VA such as 0x1c5870) and picks the compiler and flags the
     build uses for it (config/SLUS-20836/unit-compilers.tsv, config/SLUS-20836/unit-flags.tsv, else tools/verify.py's defaults; --flags/--compiler
     override), then runs tools/verify.py on the candidate and prints its instruction diff;
  2. compiles the candidate once more under a debugger that instruments the compiler's graph colouring (regalloc_trace.py; no
     file of the compiler is modified) and takes, for the last general-register colouring pass that belongs to the emitted code,
     the interference graph, the push order and the IR;
  3. aligns the IR with the emitted instructions, so every register in the emitted code is tied to its virtual-register node, and
     tells which of those nodes would have to get which register to reproduce retail (for each differing register pair: the node
     id, what it is, cost, degree, the neighbours that decided it, and the push order around it);
  4. replays simplify/select on the graph (regalloc_sim.py rules; the replay is checked against the compiler's own result) and
     SUGGESTS: it searches permutations of the node ids of the nodes involved (the id order is the scan order of simplify, the only
     thing a declaration change moves) for an order whose replay gives retail's colours, and prints the order together with what
     each node is, so that the declarations can be arranged accordingly.

How the ids come about (use it to turn a suggested order into a source change; see docs/engine/register-allocation.md):
  * function-level variables and parameters take ids from their position in the declaration block (parameters first);
  * block-local variables from the place they are declared; a second web of one variable (a reassignment that does not join the
    first) is a new, later id; two assignments that join into one web share one id;
  * int copies of call results take theirs from the call order, pointer-typed copies from their declaration position.
  After a change, run the tool again: the "ids now" column shows where the nodes landed.

Exit status: 0 when the candidate already matches, 1 otherwise, 2 on a tool error.

What it cannot do: see the "Small functions" section of the archived note `README.md` (it needs a traceable compiler build, assumes the
two functions have the same instruction sequence, explains register choice only, and treats an id order as the only lever).
"""
import argparse, difflib, itertools, os, random, re, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regalloc_trace as rt   # noqa: E402
import regalloc_sim as sim    # noqa: E402

GPR = 0                     # class number of the general registers in the compiler's tables
REGNAME = dict(rt.REGS)
REGNAME.update({1: "at", 26: "k0", 27: "k1"})
REGNUM = {v: k for k, v in REGNAME.items()}
COMMUTATIVE = {"addu", "add", "and", "or", "xor", "nor", "mult", "mul", "multu", "daddu", "dadd", "movz", "movn"}
USE, DEF = 1, 2             # IR operand flag bits


# ----------------------------------------------------------------------------------------------------------- verify + asm
def resolve(spec):
    """-> (va, name, size)"""
    import verify
    by_name, by_va = verify.load_symbols(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt"))
    if spec in by_name:
        return by_name[spec][0], spec, by_name[spec][1]
    try:
        va = int(spec, 16)
    except ValueError:
        va = None
    if va in by_va:
        return va, by_va[va][0], by_va[va][1]
    raise SystemExit("unknown function %r (not in config/SLUS-20836/symbols.txt)" % spec)


def build_profile(va):
    """-> (compiler path, flags) the build would use for the function at `va`."""
    import verify, unitobjects, unitflags, unitcompilers
    group = unitobjects.group_for(va, None)
    owner = group.owner if group else va
    flags = unitflags.load(unitflags.DEFAULT_PATH).get(owner, verify.FLAGS_DEFAULT)
    exe = unitcompilers.compiler_for(owner, verify.MWCC_DEFAULT, unitcompilers.DEFAULT_PATH)
    return exe, flags


def disassemble(words):
    """list of 32-bit words -> list of (mnemonic, operand text)"""
    import struct
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as f:
        f.write(b"".join(struct.pack("<I", w) for w in words))
        name = f.name
    try:
        out = subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-b", "binary", "-m", "mips:5900", "-EL", name],
                             capture_output=True, text=True, check=True).stdout
    finally:
        os.unlink(name)
    res = []
    for line in out.splitlines():
        m = re.match(r"\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s*(.*)$", line)
        if m:
            res.append((m.group(1), m.group(2).split("#")[0].strip()))
    return res


def regs_of(text):
    return [t for t in re.split(r"[,() \t]+", text) if t in REGNUM]


def parse_words(report):
    ours, retail = [], []
    for m in re.finditer(r"\[\s*(\d+)\] retail ([0-9a-f]{8})  ours ([0-9a-f]{8})", report):
        retail.append(int(m.group(2), 16))
        ours.append(int(m.group(3), 16))
    return ours, retail


# --------------------------------------------------------------------------------------------------------- IR <-> asm
def ir_instrs(blocks, colour):
    """flatten the IR; -> list of dicts {ops: [(flags, node)], regs: frozenset(names), weight}"""
    out = []
    for w, ins in blocks:
        for op, ops in ins:
            rops = [(f, nd) for (k, _c, f, nd) in ops if k == 0 and (f & (USE | DEF)) and 0 <= nd < 4096]
            names = []
            for f, nd in rops:
                c = colour(nd)
                if c is not None:
                    names.append(REGNAME.get(c, "r%d" % c))
            out.append(dict(op=op, ops=rops, regs=frozenset(names), weight=w))
    return out


def align(ir, asm):
    """Monotone alignment of IR instructions with emitted ones (longest common subsequence). Two instructions correspond when
    their register sets agree, or when the IR instruction's registers are all used by the emitted one (the emitted code adds
    `at`/`zero` and address-materialising operands the IR does not show). -> ({asm index: ir index}, score)"""
    A = [i["regs"] if i["op"] != 0x100 else None for i in ir]        # 0x100: block label / return pseudo-op
    # the instruction in a branch delay slot executes before the branch, which is where the IR puts it
    order, k = list(range(len(asm))), 0
    while k < len(asm) - 1:
        if re.match(r"(j|jr|jal|jalr|b\w*)$", asm[k][0]) and k + 1 < len(asm):
            order[k], order[k + 1] = order[k + 1], order[k]
            k += 1
        k += 1
    B = [frozenset(regs_of(asm[o][1])) for o in order]

    def eq(x, y):
        if x is None:
            return 0
        if x == y:
            return 2
        if x and x <= (y | {"zero", "at"}) and len(y - x) <= 1:
            return 1
        return 0
    n, m = len(A), len(B)
    best = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):
            w = eq(A[i], B[j])
            best[i][j] = max(best[i + 1][j], best[i][j + 1], best[i + 1][j + 1] + (w + 1 if w else 0))
    pairs, i, j, score = {}, 0, 0, 0
    while i < n and j < m:
        w = eq(A[i], B[j])
        if w and best[i][j] == best[i + 1][j + 1] + w + 1:
            pairs[order[j]] = i
            score += 1
            i += 1
            j += 1
        elif best[i][j] == best[i + 1][j]:
            i += 1
        else:
            j += 1
    return pairs, score


# ------------------------------------------------------------------------------------------------------------- replay
def relabel(adj, perm):
    """perm: {old id: new id} for a subset of nodes (a permutation of their ids)"""
    f = lambda i: perm.get(i, i)
    return {f(i): [f(o) for o in n] for i, n in adj.items()}


def replay(adj, cost, K=None):
    stack = sim.simplify(adj, cost)
    return stack, sim.select(adj, stack)


def calibrate(p, cost):
    """Find the simplify limit that reproduces the compiler's push order and colours on this very graph."""
    real = [x["id"] for x in p["push"]]
    fin = {n["id"]: n["color"] for n in p["final"]}
    best = None
    for K in (25, 24, 26, 23, 27, 22, 28):
        sim.K = K
        stack, col = replay(p["adj"], cost)
        bad = sum(1 for i in col if i >= 32 and col[i] != fin[i])
        same = real == [i for i, _, _ in stack]
        if best is None or (not same, bad) < (not best[1], best[2]):
            best = (K, same, bad)
        if same and bad == 0:
            break
    sim.K = best[0]
    return best


# --------------------------------------------------------------------------------------------------------------- suggest
def kendall(a, b):
    pos = {n: i for i, n in enumerate(b)}
    seq = [pos[n] for n in a]
    return sum(1 for i in range(len(seq)) for j in range(i + 1, len(seq)) if seq[i] > seq[j])


def search(adj, cost, want, pool, limit=40000, seed=1):
    """Permute the ids of `pool` (a list of nodes, in current id order) among their own id slots. -> list of (orders) solving want."""
    slots = sorted(pool)
    cons = {n: c for n, c in want.items()}

    def check(order):                       # order[k] = node that takes slots[k]
        perm = {n: slots[k] for k, n in enumerate(order)}
        a = relabel(adj, perm)
        _s, col = replay(a, cost)
        return sum(1 for n, c in cons.items() if col.get(perm.get(n, n)) == c), col

    total = len(cons)
    sols = []
    if len(pool) <= 8:
        for order in itertools.permutations(pool):
            sc, _ = check(order)
            if sc == total:
                sols.append(order)
        return sols, total
    rnd = random.Random(seed)
    best = list(pool)
    bsc, _ = check(best)
    for _ in range(limit):
        o = list(best)
        i, j = rnd.sample(range(len(o)), 2)
        o[i], o[j] = o[j], o[i]
        sc, _ = check(o)
        if sc >= bsc:
            best, bsc = o, sc
            if sc == total:
                sols.append(tuple(o))
                if len(sols) >= 3:
                    break
    return sols, total


# --------------------------------------------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("function", help="symbol name or VA (0x...)")
    ap.add_argument("candidate")
    ap.add_argument("--flags", help="compiler flags (default: the build's flags for this unit)")
    ap.add_argument("--compiler", help="compiler executable (default: the build's compiler for this unit)")
    ap.add_argument("--max-pool", type=int, default=8, help="largest set of node ids permuted exhaustively (default 8)")
    ap.add_argument("--pass", dest="passno", type=int, help="use this colouring pass (default: the one that best fits the emitted code)")
    ap.add_argument("--show-all", action="store_true", help="list every node, not only the ones involved")
    ap.add_argument("--no-suggest", action="store_true")
    a = ap.parse_args()

    import verify
    va, name, size = resolve(a.function)
    cand = os.path.abspath(a.candidate)
    exe, flags = build_profile(va)
    if a.compiler:
        exe = os.path.abspath(a.compiler)
    if a.flags:
        flags = a.flags
    os.chdir(ROOT)
    print("function %s 0x%06x (%d bytes)\ncompiler %s\nflags    %s" % (name, va, size, os.path.relpath(exe, ROOT), flags))
    ok, report = verify.verify_one(va, cand, flags=flags, mwcc=exe, verbose=True)
    ours_w, retail_w = parse_words(report)
    head = report.splitlines()[0] if report else ""
    print("\n== verify.py ==")
    print("\n".join(l for l in report.splitlines() if not l.lstrip().startswith(("[", "!!")) or "!!" in l))
    if ok:
        print("\nMATCH: nothing to diagnose")
        sys.exit(0)
    if not ours_w:
        print("\nthe candidate does not produce a comparable body; nothing to trace")
        sys.exit(2)

    asm_o, asm_r = disassemble(ours_w), disassemble(retail_w)
    n = min(len(asm_o), len(asm_r))
    diffs = [i for i in range(n) if ours_w[i] != retail_w[i]]
    regdiff, other, swapped = [], [], []
    for i in diffs:
        (mo, to), (mr, tr) = asm_o[i], asm_r[i]
        ro, rr = regs_of(to), regs_of(tr)
        strip = lambda t: re.sub(r"\b(%s)\b" % "|".join(REGNUM), "R", t)
        if mo == mr and len(ro) == len(rr) and strip(to) == strip(tr):
            if mo in COMMUTATIVE and ro[:1] == rr[:1] and sorted(ro) == sorted(rr):
                swapped.append(i)           # same registers, source operands exchanged: expression operand order, not colouring
            else:
                regdiff.append((i, [(x, y) for x, y in zip(ro, rr) if x != y]))
        else:
            other.append(i)
    print("\n== instruction diff: %d words differ; %d register-only, %d operand-order swaps, %d other; ours %d words, retail %d ==" %
          (len(diffs), len(regdiff), len(swapped), len(other), len(asm_o), len(asm_r)))
    for i in diffs:
        (mo, to), (mr, tr) = asm_o[i], asm_r[i]
        print("  [%3d] ours %-8s %-26s retail %-8s %s%s" % (i, mo, to, mr, tr, "" if any(i == r[0] for r in regdiff) else
              "   <-- same registers, operands swapped (expression operand order, not colouring)" if i in swapped else "   <-- not a register difference"))
    if len(asm_o) != len(asm_r) or other:
        print("\nNOTE: the difference is not register-only; fix the instruction sequence first (the colouring below is only a hint).")

    if not regdiff:
        print("\nno register-colouring difference to explain (see the notes above); skipping the trace")
        sys.exit(1)
    print("\n== tracing the compiler's colouring ==")
    try:
        passes, _obj = rt.trace(cand, flags, exe, min_nodes=1)
    except SystemExit as e:
        print(str(e))
        sys.exit(2)
    gprs = [(k, p) for k, p in enumerate(passes) if p["cls"] == GPR and "adj" in p and p["final"]]
    if not gprs:
        print("no general-register colouring pass recorded")
        sys.exit(2)
    best = None
    for k, p in gprs:
        fin = {nd["id"]: nd["color"] for nd in p["final"]}
        colour = lambda i, fin=fin: fin.get(i) if i >= 32 else i
        ir = ir_instrs(p["blocks"], colour)
        pairs, score = align(ir, asm_o)
        if a.passno is not None and k == a.passno:
            best = (score, k, p, ir, pairs)
        if a.passno is None and (best is None or score >= best[0]):
            best = (score, k, p, ir, pairs)
    score, k, p, ir, pairs = best
    print("%d colouring pass(es), %d general-register; using pass %d (%d nodes, %d IR instructions, %d/%d aligned with the emitted code)"
          % (len(passes), len(gprs), k, len(p["init"]), len(ir), score, len(asm_o)))
    fin = {nd["id"]: nd["color"] for nd in p["final"]}
    init = {nd["id"]: nd for nd in p["init"]}
    snap = {nd["id"]: nd for nd in (p["snap"] or [])}
    adj = p["adj"]
    cost = {i: snap[i]["cost"] for i in snap}
    est = {}
    for w, ins in p["blocks"]:
        for op, ops in ins:
            for (k, _c, f, nd) in ops:
                if k == 0 and (f & (USE | DEF)) and nd >= 32:
                    est[nd] = est.get(nd, 0) + w
    for i in adj:
        cost.setdefault(i, est.get(i, 0))
    K, same, bad = calibrate(p, cost)
    print("replay of simplify/select with K=%d: push order %s, %d colour mismatches%s" %
          (K, "identical" if same else "DIFFERENT", bad, "" if same and not bad else "   (the suggestions below are unreliable)"))
    stack, col0 = replay(adj, cost)
    pushpos = {i: (k2, kind) for k2, (i, kind, _d) in enumerate(stack)}

    # node descriptions -------------------------------------------------------------------------------------------------------
    first_def, nuses = {}, {}
    for idx, ins in enumerate(ir):
        for f, nd in ins["ops"]:
            if nd >= 32:
                if (f & DEF) and nd not in first_def:
                    first_def[nd] = idx
                nuses[nd] = nuses.get(nd, 0) + 1
    inv = {v: k2 for k2, v in pairs.items()}      # ir index -> asm index

    def describe(nd):
        idx = first_def.get(nd)
        if idx is None:
            return "param/entry value"
        ai = inv.get(idx)
        txt = "%s %s" % asm_o[ai] if ai is not None else "(IR op 0x%x, registers %s)" % (ir[idx]["op"], ",".join(sorted(ir[idx]["regs"])))
        src = [x for f, x in ir[idx]["ops"] if (f & USE)]
        kind = ""
        if ir[idx]["op"] == 0x4010 and src and all(s < 32 for s in src):
            kind = {4: "param copy a0", 5: "param copy a1", 6: "param copy a2", 7: "param copy a3", 2: "call result copy v0",
                    3: "call result copy v1"}.get(src[0], "")
        return (("[%s] " % kind) if kind else "") + (txt + ("  @%d" % ai if ai is not None else ""))

    # constraints from the aligned register differences ---------------------------------------------------------------------
    want, conflict = {}, set()
    for i, pr in regdiff:
        irx = pairs.get(i)
        if irx is None:
            continue
        nodes = [nd for f, nd in ir[irx]["ops"]]
        ro, rr = regs_of(asm_o[i][1]), regs_of(asm_r[i][1])
        if asm_o[i][0] in COMMUTATIVE and len(rr) == 3:      # retail may have exchanged the two source operands as well
            alt = [rr[0], rr[2], rr[1]]
            if sum(x != y for x, y in zip(ro, alt)) < sum(x != y for x, y in zip(ro, rr)):
                rr = alt
        if len(nodes) == len(ro):                       # operand order agrees: map by position
            tied = [(nodes[j], rr[j]) for j in range(len(ro)) if ro[j] != rr[j] and nodes[j] >= 32]
        else:                                           # otherwise by the colour ours used
            tied = [(nd, y) for x, y in pr for nd in nodes if nd >= 32 and REGNAME.get(fin.get(nd)) == x]
        for nd, y in tied:
            if nd in want and want[nd] != REGNUM[y]:
                conflict.add(nd)
            want[nd] = REGNUM[y]
    # nodes the retail code leaves alone keep their colour
    ok_asm = set(range(n)) - set(diffs)
    for asm_i in ok_asm:
        irx = pairs.get(asm_i)
        if irx is None:
            continue
        for f, nd in ir[irx]["ops"]:
            if nd >= 32 and nd not in want:
                want[nd] = fin.get(nd)
            elif nd >= 32 and want[nd] != fin.get(nd):
                conflict.add(nd)
    involved = sorted(nd for nd in want if want[nd] != fin.get(nd))
    if not involved:
        print("\nno register-coloured node could be tied to a differing instruction (nothing to search)")
        sys.exit(1)

    print("\n== nodes involved in the register differences (%d) ==" % len(involved))
    print("   id  cost  deg  push#/kind      ours -> retail   what")
    for nd in involved:
        pp = pushpos[nd]
        print("%5d %5d %4d  %5d %-7s  %5s -> %-5s%s  %s" % (nd, cost.get(nd, 0), init[nd]["deg"], pp[0] + 1, pp[1],
              REGNAME.get(fin[nd], fin[nd]), REGNAME.get(want[nd], want[nd]), "  (conflicting evidence)" if nd in conflict else "", describe(nd)))
    print("\n   neighbours and push order around the involved nodes (colouring runs in reverse push order; the last pushed gets the")
    print("   lowest free register of v0 v1 a0-a3 t0-t7 s0-s7 t8 t9 s8 not used by an already coloured neighbour):")
    for nd in involved:
        nb = sorted(o for o in adj[nd])
        virt = [o for o in nb if o >= 32]
        phys = [REGNAME.get(o, o) for o in nb if o < 32]
        pp = pushpos[nd][0]
        around = [(stack[j][0], stack[j][1]) for j in range(max(0, pp - 2), min(len(stack), pp + 3))]
        print("   node %d: virtual neighbours %s, %d physical (%s)" % (nd, virt, len(phys), "across a call" if "a0" in phys and "t0" in phys else "no call"))
        print("      pushed after %s, before %s" % (stack[pp - 1][0] if pp else "-", stack[pp + 1][0] if pp + 1 < len(stack) else "-"))
        print("      push window: %s" % " ".join("%d%s" % (x, "*" if x == nd else "") for x, _ in around))
    for i, pr in regdiff:
        ro, rr = regs_of(asm_o[i][1]), regs_of(asm_r[i][1])
        if len(rr) >= 2 and rr[0] in rr[1:] and ro[0] not in ro[1:] and asm_o[i][0] not in ("sw", "sb", "sh", "sd", "sq"):
            print("\n   HINT [%d]: retail writes %s over one of its own sources (%s); ours does not. That is usually one web: the result is the" % (i, rr[0], asm_r[i][1]))
            print("   same variable as the source (`x = x * 4;` / `x += y;` instead of a fresh temporary), or the source is a parameter that is reused.")
    params = {"a0", "a1", "a2", "a3"}
    for i, pr in regdiff:
        if asm_o[i][0] in ("lw", "lh", "lhu", "lb", "lbu", "sw", "sh", "sb", "lwc1", "swc1") and all(x in params and y in params for x, y in pr):
            print("\n   HINT [%d]: retail uses another parameter as the base here (%s vs %s): the same accesses in a different source order" % (i, asm_o[i][1], asm_r[i][1]))
            print("   (swap the operands of the comparison/arithmetic, or the order of two statements) rather than a colouring change.")
            break
    if any(REGNAME.get(want[nd]) == "t9" for nd in involved):
        print("\n   HINT: retail uses t9 for a call target (lw t9,N(..); jalr t9). The compiler fixes t9 for C++ virtual calls (and some")
        print("   indirect calls); register choice cannot produce it. Write the call as a virtual member call, or check the callee's form.")
    if a.show_all:
        print("\n   all virtual nodes:")
        for nd in sorted(i for i in adj if i >= 32 and (est.get(i) or init[i]["deg"] or i in involved)):
            print("   %5d cost %-5d deg %-3d colour %-4s %s" % (nd, cost.get(nd, 0), init[nd]["deg"], REGNAME.get(fin[nd], fin[nd]), describe(nd)))

    if a.no_suggest:
        sys.exit(1)

    # suggest -----------------------------------------------------------------------------------------------------------------
    print("\n== suggest: permuting the ids of the involved nodes ==")
    wantc = {nd: c for nd, c in want.items() if nd not in conflict}
    pool = list(involved)
    tried = []
    sols = []
    # grow the pool by the most related neighbours until a solution appears (or the limit is reached)
    related = []
    for nd in involved:
        for o in adj[nd]:
            if o >= 32 and o not in pool and o not in related:
                related.append(o)
    related.sort(key=lambda o: -len(set(adj[o]) & set(adj[involved[0]])))
    while True:
        pool_sorted = sorted(pool)
        sols, total = search(adj, cost, wantc, pool_sorted, limit=30000)
        tried.append(len(pool_sorted))
        if sols or len(pool_sorted) >= a.max_pool or not related:
            break
        pool.append(related.pop(0))
    if not sols:
        print("no permutation of the ids of %s makes the replay reproduce retail's colours for the %d constrained nodes."
              % (sorted(pool), len(wantc)))
        print("The difference is structural (different webs, edges or costs), not an id order: look at what the nodes are above.")
        sys.exit(1)
    slots = sorted(pool)
    cur = sorted(pool)
    sols = sorted(sols, key=lambda o: kendall(o, cur))
    print("search over %s nodes: %d solution(s); nearest to the current order first.\n" %
          ("/".join(str(t) for t in tried), len(sols)))
    for s_i, order in enumerate(sols[:3]):
        print("solution %d (%d swaps away from the current relative order):" % (s_i + 1, kendall(order, cur)))
        print("   id slot   node   now  what")
        for slot, nd in zip(slots, order):
            print("   %7d  %5d %5s  %s" % (slot, nd, "same" if nd == slot else "moves", describe(nd)))
        print("   -> the nodes must appear in this id order (lowest first): %s" % " < ".join(str(nd) for nd in order))
        perm = {nd: slots[k2] for k2, nd in enumerate(order)}
        _s, col = replay(relabel(adj, perm), cost)
        print("   replay: " + ", ".join("%d %s->%s" % (nd, REGNAME.get(fin[nd]), REGNAME.get(col[perm.get(nd, nd)])) for nd in involved))
    print("""
How to move an id (see the docstring): declare the variable earlier/later among the function's locals, move a block-local to
another block or to function level, join two assignments into one variable (or split them), or reorder the calls whose results
are copied. Re-run this tool after each change; the node ids are stable only below the first changed declaration.""")
    sys.exit(1)


if __name__ == "__main__":
    main()
