#!/usr/bin/env python3
"""webgraph.py (retail | OBJECT.o) [--dump out.json] : rebuild the callee-saved interference graph from machine code.

Why: the pinned compiler's colouring (see ALLOCATION.md) is decided by the interference graph and the use counts of the
virtual registers that live across calls.  For OUR object that graph is observable (regalloc_trace2.py / regalloc_graph.py),
but for the RETAIL function only its machine code exists.  This script rebuilds the graph from machine code alone, with the
same procedure for retail and for a compiled draft, so the two can be compared node by node and the simulator
(simulate() below, validated against the compiler) can be run on retail.

Model (checked against the compiler's own graph for the draft):
  * a node is a web of one callee-saved register (s0-s7, s8) - the def/use chains linked by reaching definitions;
  * two webs interfere when one is defined while the other is live;
  * a web that is live across a call has the 19 caller-saved physical neighbours; a web live where gp is live (gp is read
    by the global byte loads, so it is live from the entry to the last reachable read) has one more;  K = 25;
  * cost = 2 per use + 1 per definition, times 8 per loop level (the compiler's block weights are 1, 8, 64);
    on non-loop code 361 of the 372 across-call nodes of the draft match a web exactly in (register, cost);
    loop code differs in the weights of some blocks and the compiler's variables merge webs (11 nodes of the draft
    absorb 42 webs), so a rebuilt graph is a model of the web-level structure, not of the compiler's exact nodes;
  * simplify pushes nodes of degree < 25 in ascending order, otherwise picks the smallest cost/degree (ties: highest id).
Only webs that end up in callee-saved registers matter for the end game (all other webs are pushed in the first scans).

What it is good for: comparing a draft with retail web by web (webdiff.py).  Two builds with the same machine code up to
register names give the same webs, so any difference is a real difference in generated code (a value that crosses a call
in one and not in the other, an extra interference, a use count).  What it cannot see: how retail's source grouped webs into
variables (see webdiff.py for what remains after the visible differences are fixed).

Usage as a module: build(source) -> Graph; Graph.simulate(); see main() for the printed report.
"""
import re, sys, os, subprocess, collections, json, struct

BASE = 0x3fca10
SREGS = {'s0': 16, 's1': 17, 's2': 18, 's3': 19, 's4': 20, 's5': 21, 's6': 22, 's7': 23, 's8': 30}
NAMES = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
         's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra']
RN = {n: i for i, n in enumerate(NAMES)}
CALLER_SAVED = {RN[n] for n in ['v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7', 't8', 't9', 'at']}
HOT = sorted(SREGS.values())

ALU3 = {'addu', 'subu', 'add', 'sub', 'and', 'or', 'xor', 'nor', 'slt', 'sltu', 'daddu', 'dsubu', 'sllv', 'srlv', 'srav',
        'dsllv', 'dsrlv', 'dsrav', 'movn', 'movz'}
ALUI = {'addiu', 'daddiu', 'addi', 'slti', 'sltiu', 'andi', 'ori', 'xori'}
SHIFT = {'sll', 'srl', 'sra', 'dsll', 'dsrl', 'dsra', 'dsll32', 'dsrl32', 'dsra32'}
LOADS = {'lw', 'lh', 'lhu', 'lb', 'lbu', 'ld', 'lq', 'lwu', 'lwc1', 'ldc1', 'lwl', 'lwr'}
STORES = {'sw', 'sh', 'sb', 'sd', 'sq', 'swc1', 'sdc1', 'swl', 'swr'}
COND2 = {'beq', 'bne', 'beql', 'bnel'}
COND1 = {'beqz', 'bnez', 'bgez', 'bltz', 'blez', 'bgtz', 'beqzl', 'bnezl', 'bgezl', 'bltzl'}


def reg(s):
    return RN[s]


def parse_text(lines, rebase=0):
    """lines: (addr, 'mn\tops') -> list of (addr, mn, [ops])."""
    out = []
    for addr, txt in lines:
        txt = re.sub(r'<[^>]*>', '', txt).strip()
        if '\t' in txt:
            mn, ops = txt.split('\t', 1)
        else:
            mn, ops = txt, ''
        ops = [o.strip() for o in ops.split(',')] if ops.strip() else []
        if mn in COND2 | COND1 | {'b', 'j', 'jal'} and ops:
            t = ops[-1]
            t = int(t, 16)
            ops[-1] = t + rebase if rebase else t
        out.append((addr + rebase if rebase else addr, mn, ops))
    return out


def read_retail():
    lines = []
    for l in open(os.path.join(os.path.dirname(__file__), '..', '..', 'asm', 'Gap__Bec__beNDMWGameRam__vfunc_34.s')):
        m = re.search(r'/\* ([0-9a-f]{8}): (.*) \*/', l)
        if m:
            t = m.group(2)
            if t.startswith('(undecoded)'):
                t = 'nop'
            lines.append((int(m.group(1), 16), t))
    ins = parse_text(lines)
    root = os.path.join(os.path.dirname(__file__), '..', '..')
    sys.path.insert(0, os.path.join(root, 'tools'))
    import verify
    img = verify.read_elf(os.path.join(root, 'orig', 'SLUS-20836', 'SLUS_208.36'))
    tabs = []
    for l in open(os.path.join(root, 'config', 'SLUS-20836', 'jumptables.txt')):
        p = l.split()
        if len(p) == 3 and p[0] == '003fca10':
            va, n = int(p[1], 16), int(p[2], 16)
            raw = verify.va_bytes(img, va, 4 * n)
            tabs.append([struct.unpack_from('<I', raw, 4 * i)[0] for i in range(n)])
    tabs.sort(key=lambda t: min(t))
    return ins, tabs


def read_object(path):
    out = subprocess.run(['mipsel-linux-gnu-objdump', '-d', '-j', '.text', '--no-show-raw-insn', path], capture_output=True, text=True).stdout
    lines = []
    seen = 0
    for l in out.split('\n'):
        if re.match(r'^[0-9a-f]+ <', l):
            seen += 1
            continue
        if seen != 1:
            continue
        m = re.match(r'^\s*([0-9a-f]+):\t(.*)$', l)
        if m:
            lines.append((int(m.group(1), 16), m.group(2)))
    ins = parse_text(lines, rebase=BASE)
    sec = subprocess.run(['mipsel-linux-gnu-objdump', '-s', '-j', '.rodata', path], capture_output=True, text=True).stdout
    tabs = []
    cur = None
    for l in sec.split('\n'):
        if l.startswith('Contents of section'):
            cur = []
            tabs.append(cur)
            continue
        m = re.match(r'^ ([0-9a-f]{4}) ((?:[0-9a-f]{8} ?){1,4})', l)
        if m and cur is not None:
            for w in m.group(2).split():
                cur.append(struct.unpack('<I', bytes.fromhex(w))[0] + BASE)
    tabs = [t[:22] for t in tabs if t]
    tabs.sort(key=lambda t: min(t))
    return ins, tabs


class Graph:
    pass


def effects(mn, ops):
    """-> (defs, uses, kind) over register numbers; kind in plain/branch/call/jump/ret."""
    d, u = [], []
    kind = 'plain'
    R = lambda s: reg(s)
    mem = lambda s: re.match(r'^(-?\d+)\((\w+)\)$', s)
    if mn in ALU3:
        d, u = [R(ops[0])], [R(ops[1]), R(ops[2])]
        if mn == 'move':
            pass
    elif mn == 'move':
        d, u = [R(ops[0])], [R(ops[1])]
    elif mn in ALUI:
        d, u = [R(ops[0])], [R(ops[1])]
    elif mn in SHIFT:
        d, u = [R(ops[0])], [R(ops[1])]
    elif mn in ('lui', 'li'):
        d = [R(ops[0])]
    elif mn == 'negu' or mn == 'neg' or mn == 'not':
        d, u = [R(ops[0])], [R(ops[1])]
    elif mn in LOADS:
        m = mem(ops[1])
        if mn in ('lwc1', 'ldc1'):
            u = [R(m.group(2))]
        else:
            d, u = [R(ops[0])], [R(m.group(2))]
    elif mn in STORES:
        m = mem(ops[1])
        u = [R(m.group(2))] + ([] if mn in ('swc1', 'sdc1') else [R(ops[0])])
    elif mn in ('mult', 'mult1', 'multu', 'multu1', 'div', 'divu', 'div1', 'divu1', 'madd', 'madd1'):
        if len(ops) == 3:
            d = [R(ops[0])] if ops[0] != 'zero' else []
            u = [R(ops[1]), R(ops[2])]
        else:
            u = [R(ops[0]), R(ops[1])]
    elif mn in ('mfhi', 'mflo', 'mfhi1', 'mflo1'):
        d = [R(ops[0])]
    elif mn in ('mthi', 'mtlo'):
        u = [R(ops[0])]
    elif mn == 'mtc1':
        u = [R(ops[0])]
    elif mn == 'mfc1':
        d = [R(ops[0])]
    elif mn in COND2:
        u = [R(ops[0]), R(ops[1])]
        kind = 'branch'
    elif mn in COND1:
        u = [R(ops[0])]
        kind = 'branch'
    elif mn == 'b':
        kind = 'jump'
    elif mn == 'j':
        kind = 'jump'
    elif mn == 'jal':
        d = [31]
        kind = 'call'
    elif mn == 'jalr':
        u = [R(ops[-1])]
        d = [31]
        kind = 'call'
    elif mn == 'jr':
        u = [R(ops[0])]
        kind = 'ret' if ops[0] == 'ra' else 'tjump'
    elif mn == 'nop':
        pass
    else:
        raise SystemExit('unhandled mnemonic %s %s' % (mn, ops))
    d = [x for x in d if x != 0]
    return d, u, kind


def build(source):
    ins, tabs = read_retail() if source == 'retail' else read_object(source)
    n = len(ins)
    addr2i = {a: i for i, (a, _, _) in enumerate(ins)}
    eff = [effects(mn, ops) for _, mn, ops in ins]
    succ = [[] for _ in range(n)]
    callslot = set()
    jrn = 0
    for i, (a, mn, ops) in enumerate(ins):
        kind = eff[i][2]
        if kind in ('branch', 'jump', 'tjump', 'ret', 'call'):
            succ[i] = [i + 1]       # the delay slot
            slot = i + 1
            if kind == 'call':
                callslot.add(slot)
                succ[slot] = [i + 2]
            elif kind == 'branch':
                succ[slot] = [addr2i[ops[-1]], i + 2]
            elif kind == 'jump':
                succ[slot] = [addr2i[ops[-1]]]
            elif kind == 'ret':
                succ[slot] = []
            else:
                tb = tabs[jrn]
                jrn += 1
                succ[slot] = sorted({addr2i[t] for t in tb})
        elif not succ[i]:
            succ[i] = [i + 1] if i + 1 < n else []
    # slots were assigned above only when their predecessor is a branch; plain instructions default to fallthrough
    for i in range(n):
        if i not in callslot and not succ[i] and eff[i][2] == 'plain' and i + 1 < n:
            succ[i] = [i + 1]
    pred = [[] for _ in range(n)]
    for i in range(n):
        for s in succ[i]:
            pred[s].append(i)
    hotset = set(HOT)
    defs = [[r for r in eff[i][0] if r in hotset] for i in range(n)]
    uses = [[r for r in eff[i][1] if r in hotset] for i in range(n)]
    # slots of branches already hold their own effects (they are ordinary instructions); gp readers
    gpuse = [28 in eff[i][1] for i in range(n)]
    # liveness (per hot register bit)
    bit = {r: 1 << k for k, r in enumerate(HOT)}
    use_m = [sum(bit[r] for r in uses[i]) for i in range(n)]
    def_m = [sum(bit[r] for r in defs[i]) for i in range(n)]
    live_in = [0] * n
    live_out = [0] * n
    changed = True
    order = list(range(n - 1, -1, -1))
    while changed:
        changed = False
        for i in order:
            lo = 0
            for s in succ[i]:
                lo |= live_in[s]
            li = use_m[i] | (lo & ~def_m[i])
            if lo != live_out[i] or li != live_in[i]:
                live_out[i], live_in[i] = lo, li
                changed = True
    # gp liveness: gp (never redefined) is live from the entry to every instruction from which a gp read is reachable
    gplive_in = [False] * n
    gplive_out = [False] * n
    changed = True
    while changed:
        changed = False
        for i in order:
            lo = any(gplive_in[s] for s in succ[i])
            li = gpuse[i] or lo
            if lo != gplive_out[i] or li != gplive_in[i]:
                gplive_out[i], gplive_in[i] = lo, li
                changed = True
    # reaching definitions: def sites are (i, reg); forward dataflow with dict reg -> frozenset(sites) merged as sets
    rd_in = [None] * n
    rd_in[0] = {r: frozenset() for r in HOT}
    work = collections.deque([0])
    inq = [False] * n
    inq[0] = True
    while work:
        i = work.popleft()
        inq[i] = False
        cur = rd_in[i]
        out = dict(cur)
        for r in defs[i]:
            out[r] = frozenset([i])
        for s in succ[i]:
            if rd_in[s] is None:
                rd_in[s] = dict(out)
                ch = True
            else:
                ch = False
                new = rd_in[s]
                for r in HOT:
                    u2 = new[r] | out[r]
                    if u2 != new[r]:
                        new[r] = u2
                        ch = True
            if ch and not inq[s]:
                inq[s] = True
                work.append(s)
    # webs
    parent = {}

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a, b = find(a), find(b)
        if a != b:
            parent[b] = a
    for i in range(n):
        for r in defs[i]:
            parent[(i, r)] = (i, r)
    for i in range(n):
        if rd_in[i] is None:
            continue
        for r in uses[i]:
            sites = [(d, r) for d in rd_in[i][r]]
            for s in sites[1:]:
                union(sites[0], s)
    webs = {}
    wid = {}
    for k in sorted(parent, key=lambda x: x[0]):
        root = find(k)
        if root not in wid:
            wid[root] = len(wid)
        webs[k] = wid[root]
    nw = len(wid)
    G = Graph()
    G.n, G.nw, G.ins, G.eff, G.succ, G.webs = n, nw, ins, eff, succ, webs
    G.reg = {}
    G.first = {}
    for (i, r), w in webs.items():
        G.reg[w] = r
        G.first[w] = min(G.first.get(w, 1 << 30), i)
    # loop weights: instructions inside backward-jump spans (cheap approximation of natural loops)
    depth = [0] * n
    for i in range(n):
        for s in succ[i]:
            if s <= i:
                for k in range(s, i + 1):
                    depth[k] += 1
    G.depth = depth
    cost = collections.Counter()
    crosscall = set()
    crossgp = set()
    adj = collections.defaultdict(set)

    def webat(rdset, r):
        for d in rdset[r]:
            return webs[(d, r)]
        return None
    G.sites = collections.defaultdict(list)
    for i in range(n):
        W = 8 ** min(depth[i], 3)
        mn = ins[i][1]
        for r in uses[i]:
            w = webat(rd_in[i], r) if rd_in[i] else None
            if w is not None:
                cost[w] += 2 * W
                G.sites[w].append((ins[i][0], 'use'))
        for r in defs[i]:
            w = webs[(i, r)]
            cost[w] += W
            G.sites[w].append((ins[i][0], 'def'))
    for i in range(n):
        if rd_in[i] is None:
            continue
        out_rd = dict(rd_in[i])
        for r in defs[i]:
            out_rd[r] = frozenset([i])
        lo = live_out[i]
        li = live_in[i]
        liveout_webs = {}
        for r in HOT:
            if lo & bit[r]:
                w = webat(out_rd, r)
                if w is not None:
                    liveout_webs[r] = w
        for r in defs[i]:
            wd = webs[(i, r)]
            for r2, w2 in liveout_webs.items():
                if r2 != r and w2 != wd:
                    adj[wd].add(w2)
                    adj[w2].add(wd)
        # two webs live-out together also interfere (covers webs defined earlier and never redefined here)
        ws = sorted(set(liveout_webs.values()))
        for a in range(len(ws)):
            for b in range(a + 1, len(ws)):
                adj[ws[a]].add(ws[b])
                adj[ws[b]].add(ws[a])
        if i in callslot:
            for w in set(liveout_webs.values()):
                crosscall.add(w)
        if gplive_out[i]:
            for w in set(liveout_webs.values()):
                crossgp.add(w)
    G.cost, G.cross, G.crossgp, G.adj = cost, crosscall, crossgp, adj
    return G


def simulate(G, K=25, costover=None):
    alive = [w for w in range(G.nw) if w not in getattr(G, 'dead', ())]
    floor = {w: (19 if w in G.cross else 0) + (1 if w in G.crossgp else 0) for w in alive}
    deg = {w: floor[w] + len(G.adj[w]) for w in alive}
    cost = {w: max(G.cost[w], 0) for w in alive}
    if costover:
        cost.update(costover)
    ids = sorted(alive, key=lambda w: G.first[w])
    done = set()
    pushed = []

    def push(w, kind):
        done.add(w)
        pushed.append((w, kind, deg[w]))
        for m in G.adj[w]:
            if m not in done:
                deg[m] -= 1
    while len(done) < len(alive):
        moved = False
        stuck = []
        for w in ids:
            if w in done:
                continue
            if deg[w] < K:
                push(w, 'scan')
                moved = True
            else:
                stuck.append(w)
        if moved:
            continue
        best = None
        bv = None
        for w in reversed(stuck):
            v = cost[w] / deg[w] if deg[w] else 0.0
            if best is None or v < bv:
                best, bv = w, v
        push(best, 'PICK')
    # select: lowest free register in the compiler's order among s-regs only (other colours are never free for these webs)
    order = [16, 17, 18, 19, 20, 21, 22, 23, 30]
    col = {}
    for w, _, _ in reversed(pushed):
        used = {col[m] for m in G.adj[w] if m in col}
        col[w] = next((r for r in order if r not in used), None)
    return pushed, col


def describe(G, w):
    a = G.ins[G.first[w]][0]
    return 'w%d(%s@%x c%d)' % (w, NAMES[G.reg[w]], a, G.cost[w])


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument('source')
    ap.add_argument('--tail', type=int, default=30)
    a = ap.parse_args()
    G = build(a.source)
    print('instructions %d, webs %d, across-call webs %d, gp webs %d' % (G.n, G.nw, len(G.cross), len(G.crossgp)))
    pushed, col = simulate(G)
    recv = [w for w in range(G.nw) if len(G.adj[w]) == max(len(G.adj[x]) for x in range(G.nw))][0]
    print('receiver web', describe(G, recv), 'colour', NAMES[col[recv]] if col.get(recv) else None, 'degree', len(G.adj[recv]))
    first = next((i for i, p in enumerate(pushed) if p[1] == 'PICK'), len(pushed))
    print('first pick at %d of %d' % (first, len(pushed)))
    for w, k, d in pushed[-a.tail:]:
        print('%-5s deg %2d  %-28s -> %s' % (k, d, describe(G, w), NAMES[col[w]] if col.get(w) else 'spill'))


if __name__ == '__main__':
    main()
