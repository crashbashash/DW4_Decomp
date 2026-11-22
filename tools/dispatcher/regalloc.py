#!/usr/bin/env python3
"""regalloc.py FUNCTION_OR_VA CANDIDATE.c[pp] [--as MEMBER] [--flags "..."] [--compiler EXE] [--max-pool N] [--show-all]
             [--no-edits] [--edit-pool N] [--edit-show N] [--edit-depth 1|2]

Register-colouring diagnosis for ANY single function (the general entry point of the tools in this folder).

What it does, in order:
  1. resolves the function (a symbol name from config/SLUS-20836/symbols.txt, a VA such as 0x1c5870, or a member the
     compiler-name map binds: its compiler name or `Class::method`) and picks the compiler and flags the build uses for it (its
     config/SLUS-20836/units.tsv profile or a provisional per-function row; --flags/--compiler override), then runs
     tools/verify.py on the candidate and prints its instruction diff, aligned so that one extra or missing instruction does
     not shift every later pair. The function is compared on its own, outside its unit row, so the candidate may be the whole
     file (the colouring pass that fits the function is used) or a test file with just the function; it is looked up under
     the name the build binds, or under --as MEMBER (a compiler name, or `Class::method` read from the compiled candidate)
     when the candidate defines it as a member the build does not bind yet;
  2. compiles the candidate once more under a debugger that instruments the compiler's graph colouring (regalloc_trace.py; no
     file of the compiler is modified) and takes, for the last general-register colouring pass that belongs to the emitted code,
     the interference graph, the push order and the IR;
  3. aligns the IR with the emitted instructions, so every register in the emitted code is tied to its virtual-register node, and
     tells which of those nodes would have to get which register to reproduce retail (for each differing register pair: the node
     id, what it is, cost, degree, the neighbours that decided it, and the push order around it);
  4. replays simplify/select on the graph (regalloc_sim.py rules; the replay is checked against the compiler's own result) and
     SUGGESTS: it searches permutations of the node ids of the nodes involved and of their most related neighbours, up to
     --max-pool nodes (the id order is the scan order of simplify, the only thing a declaration change moves: a neighbour
     whose id comes below an involved node's is pushed before that node is scanned and lowers its degree) for an order whose
     replay gives retail's colours, the ones that leave the parameters' ids in place first, and prints the order together
     with what each node is, so that the declarations can be arranged accordingly;
  5. searches single graph edits (doldecomp/sms AGENT_MATCHING_TIPS, "Replay the allocator when only registers differ"): renumber
     a node below/above another (an involved node or one of its neighbours, and the same neighbour move made at once for each
     of a set of involved nodes that must change alike: the repeated code of one construct), merge two nodes (lower id kept,
     as b52's coalescer does), delete a node, add an interference, add k neighbours, split a coalesced node off its survivor;
     pairs of edits when no single one is enough. Each edit that gives retail's colours is printed with the nodes' guessed
     source names (declaration order) and the nodes coalesced into them.

How the ids come about (use it to turn a suggested order into a source change; see docs/engine/register-allocation.md):
  * function-level variables and parameters take ids from their position in the declaration block (parameters first);
  * block-local variables from the place they are declared; a second web of one variable (a reassignment that does not join the
    first) is a new, later id; two assignments that join into one web share one id;
  * int copies of call results take theirs from the call order, pointer-typed copies from their declaration position.
  After a change, run the tool again: the "ids now" column shows where the nodes landed.

Exit status: 0 when the candidate already matches, 1 otherwise, 2 on a tool error.

What it cannot do: it needs a traceable compiler build, assumes the two functions have the same instruction sequence, explains
register choice only, and stops at graph terms: an edit says which node needs another id or web, not the spelling that gives it.
"""
import argparse, difflib, itertools, os, random, re, struct, subprocess, sys, tempfile

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
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")


def member_names(spec, names):
    """The compiler names among `names` that `spec` denotes: the name itself, or a member function spelled
    `[Scope::]Class::method` (any trailing part of its qualified name) or `...::method(params)` (its signature)."""
    from demangle import demangle
    if spec in names:
        return [spec]
    want = spec.replace(" ", "")
    out = []
    for n in names:
        d = demangle(n)
        if d is None or d.data:
            continue
        full = (d.signature if "(" in want else d.qualified).replace(" ", "")
        if full == want or full.endswith("::" + want):
            out.append(n)
    return sorted(out)


def resolve(spec):
    """-> (va, name, size, compiler name or None): `spec` is a symbols.txt name, a VA, or a member the compiler-name map
    binds (its compiler name, or `Class::method` matched through tools/demangle.py)."""
    import verify, compiler_names
    by_name, by_va = verify.load_symbols(SYMBOLS)
    if spec in by_name:
        return by_name[spec][0], spec, by_name[spec][1], None
    try:
        va = int(spec, 16)
    except ValueError:
        va = None
    if va in by_va:
        return va, by_va[va][0], by_va[va][1], None
    bound = compiler_names.load(SYMBOLS)
    hits = member_names(spec, bound)
    if len(hits) > 1:
        raise SystemExit("%r names %d members: %s" % (spec, len(hits), ", ".join(hits)))
    if not hits:
        raise SystemExit("unknown function %r: not in config/SLUS-20836/symbols.txt nor in the compiler-name map; a member "
                         "the build does not bind yet is given as its retail function with --as %s" % (spec, spec))
    va = bound[hits[0]][0]
    return va, by_va[va][0], by_va[va][1], hits[0]


def binding(va, name):
    """The name the build compiles the function at `va` under: its unit row's key (the owner's `symbol`, or the emitted
    member's compiler name), else its symbols.txt name."""
    import unitobjects
    group = unitobjects.group_for(va, None)
    if group is None:
        return name
    if va == group.owner:
        return group.symbol or name
    return next(n for n, address in group.emitted if address == va)


def defined_as(spec, cand, exe, flags):
    """The compiler name the candidate defines `spec` (a compiler name, or `Class::method` read from the compiled
    candidate's functions) under."""
    import cc, verify
    from demangle import demangle
    if demangle(spec) is not None:
        return spec
    obj = os.path.join(cc.scratch_dir(), "regalloc-candidate.o")
    r = subprocess.run(cc.compile_argv(verify.WIBO_DEFAULT, exe, flags, cand, obj), cwd=ROOT, capture_output=True,
                       text=True, env=dict(os.environ, MWCIncludes=os.path.dirname(cand)))
    if not os.path.exists(obj):
        raise SystemExit("the candidate does not compile:\n" + (r.stdout + r.stderr)[-1500:])
    syms, sections = verify.object_syms(obj)
    hits = member_names(spec, [n for n, (ndx, _value, size) in syms.items() if sections.get(ndx) == ".text" and size])
    if len(hits) != 1:
        raise SystemExit("the candidate defines %s for %r" % (", ".join(hits) if hits else "no function", spec))
    return hits[0]


def standalone_inputs(va, name, defined):
    """verify.verify_one's `unit_objects` and `symbols` that compare the function at `va` on its own, as the candidate
    `defined` it: the unit-objects table without the function's unit row (a whole-file candidate's other functions are
    then notes, a one-function candidate is not its whole unit), and, when the candidate's name is not symbols.txt's,
    a copy of config/SLUS-20836 (links) whose symbols.txt gives the function that name."""
    import json, cc, unitobjects
    tmp = os.path.join(cc.scratch_dir(), "regalloc-config")
    os.makedirs(tmp, exist_ok=True)
    group = unitobjects.group_for(va, None)
    rows = json.loads(unitobjects.resolve_path(unitobjects.DEFAULT_PATH).read_text())
    table = os.path.join(tmp, "unit-objects.json")
    with open(table, "w") as fh:
        json.dump({k: v for k, v in rows.items() if not group or int(k, 0) != group.owner}, fh)
    symbols = SYMBOLS
    if defined != name:
        config = os.path.dirname(SYMBOLS)
        for entry in os.listdir(config):
            if entry != "symbols.txt" and not os.path.lexists(os.path.join(tmp, entry)):
                os.symlink(os.path.join(config, entry), os.path.join(tmp, entry))
        symbols = os.path.join(tmp, "symbols.txt")
        with open(SYMBOLS) as src, open(symbols, "w") as out:
            for line in src:
                f = line.split()
                if len(f) >= 3 and not line.startswith("#") and int(f[0], 16) == va:
                    line = " ".join([f[0], f[1], defined] + f[3:]) + "\n"
                out.write(line)
    return table, symbols


def build_profile(va):
    """-> (compiler path, flags) the build would use for the function at `va` (its units.tsv profile, or the provisional
    per-function override when one exists, as tools/verify.py compiles it)."""
    import verify, unitobjects, unitprofiles
    group = unitobjects.group_for(va, None)
    owner = group.owner if group else va
    res = unitprofiles.resolve(owner, verify.FLAGS_DEFAULT, verify.MWCC_DEFAULT, symbols=SYMBOLS)
    profile = res.override or res.profile
    return profile.compiler, unitprofiles.command_flags(profile)


def disassemble(words):
    """list of 32-bit words -> list of (mnemonic, operand text)"""
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


BRANCH = re.compile(r"(j|jal|b|bal|beq|bne|beql|bnel|[bB]\w*z\w*|bc[01][tf]l?)$")


def shape(mn, ops, keep_regs=False):
    """An instruction with its jump target (unrelocated or shifted: no information) and, unless keep_regs, its registers
    replaced by placeholders."""
    if BRANCH.match(mn):
        ops = re.sub(r"(^|,)(0x)?[0-9a-f]+$", r"\1T", ops)
    if not keep_regs:
        ops = re.sub(r"\b(%s)\b" % "|".join(sorted(REGNUM, key=len, reverse=True)), "R", ops)
    return mn, ops


def match_instructions(asm_o, asm_r):
    """-> {ours index: retail index}: a difflib alignment of the two instruction shapes, so one extra or missing instruction
    (a delay-slot nop) does not turn every later pair into a difference; equal-length replaced runs are paired in order."""
    sm = difflib.SequenceMatcher(None, [shape(*x) for x in asm_o], [shape(*x) for x in asm_r], autojunk=False)
    out = {}
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal" or (tag == "replace" and i2 - i1 == j2 - j1):
            out.update({i1 + k: j1 + k for k in range(i2 - i1)})
    return out


def parse_words(report):
    ours, retail = [], []
    for m in re.finditer(r"\[\s*(\d+)\] retail ([0-9a-f]{8})\s+ours ([0-9a-f]{8})", report):
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


def tie(nodes, ro, rr, pr, fin):
    """The virtual nodes of one aligned IR instruction (`nodes`, in IR operand order) that must take another register, with the
    register: by position when the nodes' colours (`fin`) read as ours's registers `ro` in order, else (the IR lists the
    operands in another order) through the colour ours used for each differing pair of `pr`. -> [(node, retail register)]"""
    if [REGNAME.get(fin.get(nd) if nd >= 32 else nd) for nd in nodes] == ro:
        return [(nodes[j], rr[j]) for j in range(len(ro)) if ro[j] != rr[j] and nodes[j] >= 32]
    return [(nd, y) for x, y in pr for nd in nodes if nd >= 32 and REGNAME.get(fin.get(nd)) == x]


# ------------------------------------------------------------------------------------------------------------- replay
def relabel(adj, perm):
    """perm: {old id: new id} for a subset of nodes (a permutation of their ids)"""
    f = lambda i: perm.get(i, i)
    return {f(i): [f(o) for o in n] for i, n in adj.items()}


def replay(adj, cost, K=None):
    stack = sim.simplify(adj, cost)
    return stack, sim.select(adj, stack)


def calibrate(p, adj, cost):
    """Find the simplify limit that reproduces the compiler's push order and colours on this very graph (`adj`: the pass's graph
    without the nodes simplify skips)."""
    real = [x["id"] for x in p["push"]]
    fin = {n["id"]: n["color"] for n in p["final"]}
    best = None
    for K in (25, 24, 26, 23, 27, 22, 28):
        sim.K = K
        stack, col = replay(adj, cost)
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


def neighbours(adj, cost, involved):
    """The virtual neighbours of the `involved` nodes, most relevant first: next to more involved nodes, then those simplify
    can push in its first scan (degree below K: pushed before an involved node is scanned, one lowers that node's degree), then
    by cost and by degree."""
    near = {}
    for m in involved:
        for o in adj[m]:
            if o >= 32 and o not in involved:
                near[o] = near.get(o, 0) + 1
    return sorted(near, key=lambda o: (-near[o], len(adj[o]) >= sim.K, -cost.get(o, 0), -len(adj[o]), o))


def rank_orders(sols, pool, fixed):
    """The solutions of `search` over `pool`, the realisable ones first: the ones that keep every `fixed` node (a parameter:
    parameters take the first ids, in declaration order) in its slot, then the nearest to the current order."""
    slots = sorted(pool)
    return sorted(sols, key=lambda o: (any(n in fixed and n != s for s, n in zip(slots, o)), kendall(o, slots)))


def search(adj, cost, want, pool, limit=40000, seed=1):
    """Permute the ids of `pool` (a list of nodes, in current id order) among their own id slots. -> list of (orders) solving want."""
    slots = sorted(pool)
    cons = {n: c for n, c in want.items()}

    def check(order):                       # order[k] = node that takes slots[k]
        perm = {n: slots[k] for k, n in enumerate(order)}
        a = relabel(adj, perm)
        _s, col = replay(a, {perm.get(i, i): c for i, c in cost.items()})
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


# ---------------------------------------------------------------------------------------------------------- single edits
# The sms project's tip "replay the allocator when only registers differ" (doldecomp/sms, docs/AGENT_MATCHING_TIPS.md): from the
# replayed graph, try one edit at a time and keep the ones whose replay gives retail's colours; each edit names a source change.
# On b52 the coalescer runs before colouring, keeps the lower id of a merged pair and leaves the merged node without edges
# (docs/engine/register-allocation.md, "Coalescing"), which is what merge/split model here.
PHANTOMS = (1, 26, 27)      # at, k0, k1: never allocatable, so as extra neighbours they add degree and block no colour


def candidate_edits(adj, cost, rel, want, alias, pre_adj, nmove=12, step=0.5):
    """Yield (kind, args, graph, costs, idmap) for every single edit on the nodes `rel` (renumbering only the first `nmove`);
    idmap renames nodes of the old graph."""
    adjs = {i: set(v) for i, v in adj.items()}
    for n in rel:                                                       # delete
        yield "delete", (n,), {i: [o for o in v if o != n] for i, v in adj.items() if i != n}, cost, None
    for x, y in itertools.combinations(sorted(rel), 2):                 # merge (x < y: y joins x, as the coalescer does)
        if y in adjs[x] or (x in want and y in want and want[x] != want[y]):
            continue
        a2 = {i: [x if o == y else o for o in v if not (o == y and x in adjs[i])] for i, v in adj.items() if i != y}
        a2[x] = sorted((adjs[x] | adjs[y]) - {x, y})
        c2 = dict(cost)
        c2[x] = cost.get(x, 0) + cost.get(y, 0)
        yield "merge", (x, y), a2, c2, {y: x}
    for x, y in itertools.combinations(sorted(rel), 2):                 # edge
        if y not in adjs[x]:
            a2 = dict(adj)
            a2[x], a2[y] = list(adj[x]) + [y], list(adj[y]) + [x]
            yield "edge", (x, y), a2, cost, None
    for n in rel:                                                       # degree
        free = [ph for ph in PHANTOMS if ph not in adjs[n]]
        for k in range(1, len(free) + 1):
            a2 = dict(adj)
            a2[n] = list(adj[n]) + free[:k]
            for ph in free[:k]:
                a2[ph] = list(adj.get(ph, [])) + [n]
            yield "degree", (n, k), a2, cost, None
    for n in rel[:nmove]:                                               # renumber
        for m in rel:
            for side in (-1, 1) if m != n else ():
                new = m + step * side
                yield ("renumber", (n, m, side), relabel(adj, {n: new}), {(new if i == n else i): c for i, c in cost.items()},
                       {n: new})
    for m, r in (alias or {}).items() if pre_adj else ():               # split (un-coalesce)
        if m < 32 or r < 32 or m not in pre_adj or r not in rel:
            continue
        nb = {o for o in ({alias.get(o, o) for o in pre_adj[m]} - {m, r}) if o in adj}
        a2 = dict(adj)
        a2[m] = sorted(nb)
        for o in nb:
            a2[o] = list(a2[o]) + [m]
        c2 = dict(cost)
        c2[m] = cost.get(r, 0)
        yield "split", (m, r), a2, c2, None


def neighbour_edits(adj, cost, involved, col, want, step=0.5):
    """Yield, as candidate_edits does, the renumber edits that move a neighbour of an involved node just below or above it, for
    every virtual neighbour of every involved node (simplify scans in id order, so a neighbour pushed before an involved node is
    scanned lowers that node's degree); and the same move made at once for each of a set of siblings, involved nodes that must
    change from one colour (`col`) to one other (`want`), each with exactly one neighbour of a given cost and degree (one
    source construct repeated, such as the count of each of three list appends): kind "renumber each", args
    (((n, m), ...), side)."""
    for m in involved:
        for n in sorted(o for o in adj[m] if o >= 32 and o not in involved):
            for side in (-1, 1):
                new = m + step * side
                yield ("renumber", (n, m, side), relabel(adj, {n: new}), {(new if i == n else i): c for i, c in cost.items()},
                       {n: new})
    siblings = {}
    for m in involved:
        siblings.setdefault((col.get(m), want.get(m)), []).append(m)
    for ms in siblings.values():
        alike = {}
        for m in ms:
            for n in adj[m]:
                if n >= 32 and n not in involved:
                    alike.setdefault((cost.get(n, 0), len(adj[n])), {}).setdefault(m, []).append(n)
        for _sig, per in sorted(alike.items(), key=lambda e: (-e[0][0], -e[0][1])):
            pairs = tuple((per[m][0], m) for m in ms if len(per.get(m, ())) == 1)
            if len(ms) < 2 or len(pairs) < len(ms) or len({n for n, _m in pairs}) < len(pairs):
                continue
            for side in (-1, 1):
                perm = {n: m + step * side for n, m in pairs}
                yield ("renumber each", (pairs, side), relabel(adj, perm), {perm.get(i, i): c for i, c in cost.items()},
                       perm)


def edit_search(adj, cost, want, involved, alias=None, pre_adj=None, pool=40, depth=1, fixed=()):
    """Graph edits around the `involved` nodes. -> (base score, total, [(score, [(kind, args), ...])]) where score counts the
    constrained nodes of `want` ({node: colour}) that get their colour, best first, and among equals the edits that renumber
    none of the `fixed` nodes (parameters: their ids come from their position) first. Kinds: delete (n), merge (a, b: one
    web, id min(a, b)), split (m, r: undo the coalescing of m into r; args gain whether both then get one colour), degree
    (n, k phantom neighbours), edge (a, b: make them interfere), renumber (n, m, -1/+1: n's id just below/above m's; n is an
    involved node or one of the edit pool, or a neighbour of m), renumber each (((n, m), ...), -1/+1: each n's id just
    below/above its m's at once; see neighbour_edits). depth=2 also applies each of the best 12 single edits and searches
    one more edit on the result when no single edit is a full solution (only full solutions are kept)."""
    total = len(want)

    def score(a2, c2, w, idmap=None):
        _s, col = replay(a2, c2)
        f = (idmap or {}).get
        return sum(1 for nd, c in w.items() if col.get(f(nd, nd) if idmap else nd) == c), col

    def related(a, c, inv):
        return list(inv) + neighbours(a, c, inv)[:max(0, pool - len(inv))]

    base, col0 = score(adj, cost, want)
    out, firsts, seen = [], [], set()
    for kind, args, a2, c2, idmap in itertools.chain(
            candidate_edits(adj, cost, related(adj, cost, involved), want, alias, pre_adj, max(12, len(involved))),
            neighbour_edits(adj, cost, involved, col0, want)):
        if (kind, args) in seen:
            continue
        seen.add((kind, args))
        sc, col = score(a2, c2, want, idmap)
        if kind == "split":
            args = args + (col.get(args[0]) == col.get(args[1]),)
        out.append((sc, [(kind, args)]))
        firsts.append((sc, kind, args, a2, c2, idmap, col))
    order = ["renumber", "renumber each", "merge", "delete", "edge", "degree", "split"]
    if depth > 1 and not any(sc == total for sc, _ in out):
        firsts.sort(key=lambda e: (-e[0], order.index(e[1])))
        for sc, kind, args, a2, c2, idmap, col in [e for e in firsts if base < e[0] < total][:12]:
            f = (idmap or {}).get
            w2 = {(f(n, n) if idmap else n): c for n, c in want.items()}
            inv2 = [n for n, c in w2.items() if n in a2 and col.get(n) != c]
            for kind2, args2, a3, c3, idmap2 in candidate_edits(a2, c2, related(a2, c2, inv2), w2, None, None,
                                                                       max(12, len(inv2)), 0.25):
                if score(a3, c3, w2, idmap2)[0] == total:
                    out.append((total, [(kind, args), (kind2, args2)]))

    def moves_fixed(steps):
        return any(n in fixed for kind, args in steps if kind in ("renumber", "renumber each")
                   for n in ([args[0]] if kind == "renumber" else [n for n, _m in args[0]]))
    out.sort(key=lambda e: (-e[0], len(e[1]), moves_fixed(e[1]), [order.index(k) for k, _ in e[1]]))
    return base, total, out


def explain_edit(kind, args, who):
    """One edit in source terms; who(node) describes a node."""
    if kind == "delete":
        return "delete node %s %s: the value is not a web of its own (compute it straight into the variable that uses it, or let " \
               "its uses read the source)" % (args[0], who(args[0]))
    if kind == "merge":
        return "merge %s and %s into one web (id %s): one variable for both values, or a copy between them that coalesces\n" \
               "         %s: %s\n         %s: %s" % (args[0], args[1], args[0], args[0], who(args[0]), args[1], who(args[1]))
    if kind == "split":
        return "split %s off %s (undo the coalescing): %s keeps its own register, so its copy must survive (b52 coalesces every copy " \
               "whose two sides do not overlap)%s\n         %s: %s\n         %s: %s" % (
                   args[0], args[1], args[0], "; both get the same colour, so no move is emitted" if args[2] else "; this adds a move",
                   args[0], who(args[0]), args[1], who(args[1]))
    if kind == "degree":
        return "give %s %d more neighbour(s) (one more value live across its whole range per neighbour): %s" % (args[0], args[1], who(args[0]))
    if kind == "edge":
        return "make %s and %s interfere (keep one live across the other's definition)\n         %s: %s\n         %s: %s" % (
            args[0], args[1], args[0], who(args[0]), args[1], who(args[1]))
    if kind == "renumber":
        return "renumber %s just %s %s (declare or create it %s that value):\n         %s: %s\n         %s: %s" % (
            args[0], "below" if args[2] < 0 else "above", args[1], "before" if args[2] < 0 else "after",
            args[0], who(args[0]), args[1], who(args[1]))
    if kind == "renumber each":
        pairs, side = args
        return "renumber each of %s just %s %s (declare or create each %s that value):%s" % (
            ", ".join(str(n) for n, _m in pairs), "below" if side < 0 else "above", ", ".join(str(m) for _n, m in pairs),
            "before" if side < 0 else "after", "".join("\n         %s: %s\n         %s: %s" % (n, who(n), m, who(m))
                                                       for n, m in pairs))
    return "%s %s" % (kind, args)


SCALAR = {"int", "char", "short", "long", "float", "double", "bool", "unsigned", "signed", "u8", "u16", "u32", "s8", "s16", "s32"}


def source_names(path, func, member=False):
    """Guess {node id: name} from the declarations of `func` in `path` (or a file it includes with quotes): parameters take ids
    from 32 in order (`this` first for a member function: `member`, or a definition spelled `Class::func`), then every scalar or
    pointer local in textual order. A local of class type takes no id. This is the declaration-order rule of
    docs/engine/register-allocation.md, so it is a guess: inline functions' locals and compiler temporaries come after, and a
    local the optimizer removes still holds its id."""
    seen, todo, text = set(), [path], None
    while todo and text is None:
        f = todo.pop(0)
        if f in seen or not os.path.exists(f):
            continue
        seen.add(f)
        src = open(f, errors="replace").read()
        m = re.search(r"(?:^|\n)[^\n;{}]*?\b((?:\w+::)?%s)\s*\(([^)]*)\)\s*\{" % re.escape(func), src)
        if m:
            text = (m, src)
            break
        for inc in re.findall(r'^\s*#\s*include\s+"([^"]+)"', src, re.M):
            todo += [os.path.join(ROOT, inc), os.path.join(os.path.dirname(f), inc)]
    if text is None:
        return {}
    m, src = text
    params = ["this"] if member or "::" in m.group(1) else []
    for p in m.group(2).split(","):
        w = re.findall(r"[A-Za-z_]\w*", p)
        if w and w != ["void"]:
            params.append(w[-1])
    depth, i = 1, m.end()
    while i < len(src) and depth:
        depth += {"{": 1, "}": -1}.get(src[i], 0)
        i += 1
    body = re.sub(r"//[^\n]*|/\*.*?\*/", " ", src[m.end():i - 1], flags=re.S)
    locs = []
    for st in re.split(r"[;{}]", body):
        st = re.sub(r"^\s*for\s*\(", "", st).strip()
        d = re.match(r"(?:(?:const|volatile|register|static)\s+)*([A-Za-z_][\w:]*(?:<[^;]*?>)?(?:\s+(?:int|char|short|long))*)(\s*\*+\s*|\s+)([A-Za-z_]\w*)\s*(?:=|\[|$|,)", st)
        if not d or d.group(1) in ("return", "goto", "case", "delete", "else", "do") or "(" in st.split("=")[0]:
            continue
        scalar = "*" in d.group(2) or d.group(1).split()[0] in SCALAR
        rest = st[d.end(3):]
        while re.search(r"\([^()]*\)", rest):                          # drop initialisers' argument lists
            rest = re.sub(r"\([^()]*\)", "", rest)
        decls = [d.group(2).strip() + d.group(3)] + re.findall(r",\s*(\**\s*[A-Za-z_]\w*)\s*(?==|,|$|\[)", rest)
        for name in decls:
            if scalar or name.lstrip().startswith("*"):
                locs.append(name.strip(" *"))
    return {32 + k: n for k, n in enumerate(params + locs)}


# --------------------------------------------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("function", help="symbol name, VA (0x...), or a member the compiler-name map binds (compiler name or Class::method)")
    ap.add_argument("candidate")
    ap.add_argument("--as", dest="defined", metavar="MEMBER",
                    help="the candidate defines the function as this member (compiler name or Class::method), not under the name the build binds")
    ap.add_argument("--flags", help="compiler flags (default: the build's flags for this unit)")
    ap.add_argument("--compiler", help="compiler executable (default: the build's compiler for this unit)")
    ap.add_argument("--max-pool", type=int, default=8, help="nodes whose ids are permuted: the involved ones, then their most related "
                    "neighbours up to this many (default 8; up to 8 exhaustively, more at random)")
    ap.add_argument("--pass", dest="passno", type=int, help="use this colouring pass (default: the one that best fits the emitted code)")
    ap.add_argument("--show-all", action="store_true", help="list every node, not only the ones involved")
    ap.add_argument("--no-suggest", action="store_true", help="stop after the node report (no id permutations, no graph edits)")
    ap.add_argument("--no-edits", action="store_true", help="skip the single graph edit search")
    ap.add_argument("--edit-pool", type=int, default=40, help="nodes the edit search works on: the involved ones and their most connected neighbours (default 40)")
    ap.add_argument("--edit-show", type=int, default=12, help="full solutions printed (default 12)")
    ap.add_argument("--edit-depth", type=int, default=2, choices=(1, 2), help="2 (default): when no single edit is a full solution, also try pairs")
    a = ap.parse_args()

    import verify
    va, name, size, member = resolve(a.function)
    cand = os.path.abspath(a.candidate)
    exe, flags = build_profile(va)
    if a.compiler:
        exe = os.path.abspath(a.compiler)
    if a.flags:
        flags = a.flags
    os.chdir(ROOT)
    defined = defined_as(a.defined, cand, exe, flags) if a.defined else member or binding(va, name)
    print("function %s 0x%06x (%d bytes)%s\ncompiler %s\nflags    %s" % (
        name, va, size, "" if defined == name else ", defined as %s" % defined, os.path.relpath(exe, ROOT), flags))
    table, symbols = standalone_inputs(va, name, defined)
    ok, report = verify.verify_one(va, cand, flags=flags, mwcc=exe, verbose=True, symbols=symbols, unit_objects=table)
    ours_w, _ = parse_words(report)
    retail_w = list(struct.unpack("<%dI" % (size // 4), verify.va_bytes(verify.read_elf(verify.ELF_DEFAULT), va, size)))
    print("\n== verify.py ==")
    # a whole-file candidate defines every other function of its unit too: those notes (their symbols, relocations and
    # literals) say nothing about this one
    noise = ("[", "!!", "object defines ", "unresolved relocation", "unowned allocated", "object has ", "literal reference at ",
             ".lit")
    lines = report.splitlines()
    print("\n".join(l for l in lines if not l.lstrip().startswith(noise)))
    skipped = sum(1 for l in lines[1:] if l.lstrip().startswith(noise[2:]))
    if skipped:
        print("   (%d notes about other symbols of the object omitted)" % skipped)
    if ok or ours_w == retail_w:          # a whole-file candidate's other functions make the standalone verdict DIFFER
        print("\nMATCH: nothing to diagnose")
        sys.exit(0)
    if not ours_w:
        print("\nthe candidate does not produce a comparable body; nothing to trace")
        sys.exit(2)

    asm_o, asm_r = disassemble(ours_w), disassemble(retail_w)
    rmap = match_instructions(asm_o, asm_r)       # ours index -> retail index (an extra or missing instruction shifts no pair)
    n = len(asm_o)
    diffs = [i for i in range(n) if i not in rmap or (ours_w[i] != retail_w[rmap[i]] and shape(*asm_o[i], True) != shape(*asm_r[rmap[i]], True))]
    unpaired_r = sorted(set(range(len(asm_r))) - set(rmap.values()))
    regdiff, other, swapped = [], [], []
    for i in diffs:
        if i not in rmap:
            other.append(i)
            continue
        (mo, to), (mr, tr) = asm_o[i], asm_r[rmap[i]]
        ro, rr = regs_of(to), regs_of(tr)
        if mo == mr and len(ro) == len(rr) and shape(mo, to) == shape(mr, tr):
            if mo in COMMUTATIVE and ro[:1] == rr[:1] and sorted(ro) == sorted(rr):
                swapped.append(i)           # same registers, source operands exchanged: expression operand order, not colouring
            else:
                regdiff.append((i, [(x, y) for x, y in zip(ro, rr) if x != y]))
        else:
            other.append(i)
    print("\n== instruction diff: %d words differ; %d register-only, %d operand-order swaps, %d other, %d retail-only; ours %d words, retail %d =="
          % (len(diffs), len(regdiff), len(swapped), len(other), len(unpaired_r), len(asm_o), len(asm_r)))
    for i in diffs:
        mo, to = asm_o[i]
        mr, tr = asm_r[rmap[i]] if i in rmap else ("-", "(no retail counterpart)")
        print("  [%3d] ours %-8s %-26s retail %-8s %s%s" % (i, mo, to, mr, tr, "" if any(i == r[0] for r in regdiff) else
              "   <-- same registers, operands swapped (expression operand order, not colouring)" if i in swapped else "   <-- not a register difference"))
    for j in unpaired_r:
        print("  [r%3d] retail only: %-8s %s   <-- not a register difference" % ((j,) + tuple(asm_r[j])))
    if len(asm_o) != len(asm_r) or other or unpaired_r:
        print("\nNOTE: the difference is not register-only; fix the instruction sequence first (the colouring below is only a hint).")

    if not regdiff:
        print("\nno register-colouring difference to explain (see the notes above); skipping the trace")
        sys.exit(1)
    print("\n== tracing the compiler's colouring ==")
    try:
        passes, _obj = rt.trace(cand, flags, exe, min_nodes=1, coalesce=True)
    except SystemExit as e:
        print(str(e))
        sys.exit(2)
    gprs = [(k, p) for k, p in enumerate(passes) if p["cls"] == GPR and "adj" in p and p["final"]]
    if not gprs:
        print("no general-register colouring pass recorded")
        sys.exit(2)
    # a whole-file unit colours thousands of functions: align only passes of about the function's size, and prefer the pass whose
    # IR is covered best (aligned instructions minus half the IR instructions left over)
    real_ir = lambda p: sum(1 for _w, ins in p["blocks"] for op, _o in ins if op != 0x100)
    if a.passno is not None:
        cands = [(k, p) for k, p in gprs if k == a.passno]
    else:
        cands = [(k, p) for k, p in gprs if 0.5 * len(asm_o) <= real_ir(p) <= 1.6 * len(asm_o)] or gprs
    best = None
    for k, p in cands:
        fin = {nd["id"]: nd["color"] for nd in p["final"]}
        colour = lambda i, fin=fin: fin.get(i) if i >= 32 else i
        ir = ir_instrs(p["blocks"], colour)
        pairs, score = align(ir, asm_o)
        fit = score - 0.5 * (real_ir(p) - score)
        if best is None or fit >= best[0]:
            best = (fit, k, p, ir, pairs, score)
    _fit, k, p, ir, pairs, score = best
    print("%d colouring pass(es), %d general-register; using pass %d (%d nodes, %d IR instructions, %d/%d aligned with the emitted code)"
          % (len(passes), len(gprs), k, len(p["init"]), len(ir), score, len(asm_o)))
    fin = {nd["id"]: nd["color"] for nd in p["final"]}
    init = {nd["id"]: nd for nd in p["init"]}
    snap = {nd["id"]: nd for nd in (p["snap"] or [])}
    # nodes flagged 4 have no edges and simplify never pushes them; the replay leaves them out
    adj = {i: v for i, v in p["adj"].items() if i < 32 or not init[i]["flags"] & 4}
    cost = {i: snap[i]["cost"] for i in snap}
    est = {}
    for w, ins in p["blocks"]:
        for op, ops in ins:
            for (k, _c, f, nd) in ops:
                if k == 0 and (f & (USE | DEF)) and nd >= 32:
                    est[nd] = est.get(nd, 0) + w
    for i in adj:
        cost.setdefault(i, est.get(i, 0))
    K, same, bad = calibrate(p, adj, cost)
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

    def copy_kind(nd):
        """"param copy aN" / "call result copy vN" for a node first defined as a copy of that register, else ""."""
        idx = first_def.get(nd)
        src = [x for f, x in ir[idx]["ops"] if (f & USE)] if idx is not None else []
        if not src or ir[idx]["op"] != 0x4010 or not all(s < 32 for s in src):
            return ""
        return {4: "param copy a0", 5: "param copy a1", 6: "param copy a2", 7: "param copy a3", 2: "call result copy v0",
                3: "call result copy v1"}.get(src[0], "")

    def describe(nd):
        idx = first_def.get(nd)
        if idx is None:
            return "param/entry value"
        ai = inv.get(idx)
        txt = "%s %s" % asm_o[ai] if ai is not None else "(IR op 0x%x, registers %s)" % (ir[idx]["op"], ",".join(sorted(ir[idx]["regs"])))
        kind = copy_kind(nd)
        return (("[%s] " % kind) if kind else "") + (txt + ("  @%d" % ai if ai is not None else ""))

    from demangle import demangle
    method = demangle(defined)
    names = source_names(cand, method.name, method.class_name is not None) if method else source_names(cand, defined)
    alias = p.get("alias") or {}

    def label(nd):
        """`name` (a declaration-order guess) and the nodes the coalescer merged into nd, for the source terms of a report."""
        joined = sorted(m for m, r in alias.items() if r == nd and m >= 32)
        out = "`%s` " % names[nd] if nd in names else ""
        if joined:
            out += "(joins %s) " % ", ".join("%d%s" % (m, " `%s`" % names[m] if m in names else "") for m in joined)
        return out

    # constraints from the aligned register differences ---------------------------------------------------------------------
    want, conflict = {}, set()
    for i, pr in regdiff:
        irx = pairs.get(i)
        if irx is None:
            continue
        nodes = [nd for f, nd in ir[irx]["ops"]]
        ro, rr = regs_of(asm_o[i][1]), regs_of(asm_r[rmap[i]][1])
        if asm_o[i][0] in COMMUTATIVE and len(rr) == 3:      # retail may have exchanged the two source operands as well
            alt = [rr[0], rr[2], rr[1]]
            if sum(x != y for x, y in zip(ro, alt)) < sum(x != y for x, y in zip(ro, rr)):
                rr = alt
        tied = tie(nodes, ro, rr, pr, fin)
        for nd, y in tied:
            if nd in want and want[nd] != REGNUM[y]:
                conflict.add(nd)
            want[nd] = REGNUM[y]
    # nodes the retail code leaves alone keep their colour
    ok_asm = set(rmap) - set(diffs)
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
              REGNAME.get(fin[nd], fin[nd]), REGNAME.get(want[nd], want[nd]), "  (conflicting evidence)" if nd in conflict else "", label(nd) + describe(nd)))
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
        ro, rr = regs_of(asm_o[i][1]), regs_of(asm_r[rmap[i]][1])
        if len(rr) >= 2 and rr[0] in rr[1:] and ro[0] not in ro[1:] and asm_o[i][0] not in ("sw", "sb", "sh", "sd", "sq"):
            print("\n   HINT [%d]: retail writes %s over one of its own sources (%s); ours does not. That is usually one web: the result is the" % (i, rr[0], asm_r[rmap[i]][1]))
            print("   same variable as the source (`x = x * 4;` / `x += y;` instead of a fresh temporary), or the source is a parameter that is reused.")
    params = {"a0", "a1", "a2", "a3"}
    for i, pr in regdiff:
        if asm_o[i][0] in ("lw", "lh", "lhu", "lb", "lbu", "sw", "sh", "sb", "lwc1", "swc1") and all(x in params and y in params for x, y in pr):
            print("\n   HINT [%d]: retail uses another parameter as the base here (%s vs %s): the same accesses in a different source order" % (i, asm_o[i][1], asm_r[rmap[i]][1]))
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
    print("\n== suggest: permuting the ids of the involved nodes and their neighbours ==")
    wantc = {nd: c for nd, c in want.items() if nd not in conflict}
    # the involved nodes and their most related neighbours: a neighbour's id below an involved node's can change when that
    # node is pushed, which is what decides its colour
    near = neighbours(adj, cost, involved)[:max(0, a.max_pool - len(involved))]
    pool = sorted(involved + near)
    sols, total = search(adj, cost, wantc, pool, limit=30000)
    fixed = {nd for nd in adj if nd >= 32 and (nd not in first_def or copy_kind(nd).startswith("param"))}
    if not sols:
        print("no permutation of the ids of %s makes the replay reproduce retail's colours for the %d constrained nodes."
              % (pool, len(wantc)))
        print("The difference is not an id order of these nodes: see the single graph edits below.")
    else:
        slots = pool
        sols = rank_orders(sols, pool, fixed)
        print("search over %d nodes (%d involved, neighbours %s): %d solution(s); the ones that leave the parameters' ids in "
              "place first (parameters take the first ids), then the nearest to the current order.\n"
              % (len(pool), len(involved), " ".join(map(str, near)) or "none", len(sols)))
        for s_i, order in enumerate(sols[:3]):
            print("solution %d (%d swaps away from the current relative order):" % (s_i + 1, kendall(order, slots)))
            print("   id slot   node   now  what")
            for slot, nd in zip(slots, order):
                print("   %7d  %5d %5s  %s%s" % (slot, nd, "same" if nd == slot else "moves", label(nd), describe(nd)))
            print("   -> the nodes must appear in this id order (lowest first): %s" % " < ".join(str(nd) for nd in order))
            perm = {nd: slots[k2] for k2, nd in enumerate(order)}
            _s, col = replay(relabel(adj, perm), {perm.get(i, i): c for i, c in cost.items()})
            print("   replay: " + ", ".join("%d %s->%s" % (nd, REGNAME.get(fin[nd]), REGNAME.get(col[perm.get(nd, nd)])) for nd in involved))
        print("""
How to move an id (see the docstring): declare the variable earlier/later among the function's locals, move a block-local to
another block or to function level, join two assignments into one variable (or split them), or reorder the calls whose results
are copied. Re-run this tool after each change; the node ids are stable only below the first changed declaration.""")
    if a.no_edits:
        sys.exit(1)

    # single graph edits ------------------------------------------------------------------------------------------------------
    print("\n== single graph edits (replayed; the ones that give retail's colours name a source change) ==")
    base, total, edits = edit_search(adj, cost, wantc, involved, alias, p.get("pre_adj"), pool=a.edit_pool, depth=a.edit_depth,
                                     fixed=fixed)
    full = [e for e in edits if e[0] == total]
    print("%d single edits tried around %d involved nodes; the current graph satisfies %d of %d constrained nodes; %d full solution(s)."
          % (sum(1 for e in edits if len(e[1]) == 1), len(involved), base, total, len(full)))
    who = lambda nd: (label(nd) + describe(nd)) if nd in init else "(renumbered %s)" % nd
    if full:
        groups = {}                                     # first edit -> the second edits that complete it ([] for a single edit)
        for sc, steps in full:
            groups.setdefault(steps[0], []).extend(steps[1:])
        for first, seconds in list(groups.items())[:a.edit_show]:
            print("  %s %s" % ("one edit:" if not seconds else "this edit", explain_edit(first[0], first[1], who)))
            if seconds:
                print("    together with any one of (%d):" % len(seconds))
                for kind, args in seconds[:6]:
                    print("      - " + explain_edit(kind, args, who).replace("\n", "\n        "))
    else:
        better = [e for e in edits if e[0] > base]
        print("No edit reaches retail's colours (pairs of edits included)." if a.edit_depth > 1 else "No single edit reaches retail's colours.")
        if better:
            print("The best partial edits of each kind (more constrained nodes right than now):")
            for kind in ("renumber", "renumber each", "merge", "delete", "edge", "degree", "split"):
                for sc, steps in [e for e in better if e[1][0][0] == kind][:2]:
                    print("  [%d/%d] %s" % (sc, total, explain_edit(kind, steps[0][1], who)))
    sys.exit(1)


if __name__ == "__main__":
    main()
