#!/usr/bin/env python3
"""regalloc_sim.py ADJ.json CTX.json : replay the pinned compiler's simplify/select passes on a graph dumped by
`regalloc_trace.py SOURCE --adj DIR --ctx FILE` (use the adjN.json of the last big pass, normally adj1.json).

The replay reproduces the compiler's push order and colours exactly for the dumped graph, in about 15 ms, so what-if questions can
be answered without recompiling: relabel node ids (the id order is the scan order), change costs, add or remove edges, delete nodes.
Rules (Coloring.c in the pinned mwccps2.exe, see ALLOCATION.md):
  * simplify scans the virtual nodes in ascending id and pushes every node whose degree is below K = 25 (decrementing its
    neighbours as it goes); it rescans from the lowest id while anything was pushed;
  * when a scan pushes nothing it picks the stuck node with the smallest cost / degree (ties: highest id), pushes it and rescans;
  * select pops in reverse push order and gives each node the lowest free register of v0 v1 a0-a3 t0-t7 s0-s7 t8 t9 s8.
As a module: load(adj, ctx) -> (adj, cost, ctx); simplify(adj, cost) -> [(id, kind, degree)]; select(adj, stack) -> {id: colour}.
"""
import json, sys

K = 25
ORDER = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 30]


def load(adjf, ctxf):
    g = json.load(open(adjf))
    g = g["adj"] if "adj" in g and "blocks" in g else g          # adjN.json also carries the class and the IR
    adj = {int(k): v for k, v in g.items()}
    ctx = json.load(open(ctxf))
    cost = {n["id"]: n["cost"] for n in ctx["snap"]}
    return adj, cost, ctx


def _drain(adj, deg, virt, done, stack, kind):
    """Scan until nothing is pushed; return the nodes that were stuck in the last scan."""
    while True:
        pushed, stuck = False, []
        for i in virt:
            if i in done:
                continue
            if deg[i] >= K:
                stuck.append(i)
                continue
            done.add(i)
            stack.append((i, kind, deg[i]))
            for o in adj[i]:
                deg[o] -= 1
            pushed = True
        if not pushed:
            return stuck


def simplify(adj, cost):
    deg = {i: len(adj[i]) for i in adj}
    virt = sorted(i for i in adj if i >= 32)
    done, stack = set(), []
    stuck = _drain(adj, deg, virt, done, stack, "scan")
    while stuck:
        best = None
        for i in reversed(stuck):                       # list order: highest id first, strict < keeps the first minimum
            r = cost[i] / deg[i] if deg[i] else float("inf")
            if best is None or r < best[0]:
                best = (r, i)
        i = best[1]
        done.add(i)
        stack.append((i, "PICK", deg[i]))
        for o in adj[i]:
            deg[o] -= 1
        stuck = _drain(adj, deg, virt, done, stack, "rescan")
    return stack


def select(adj, stack):
    col = {i: i for i in adj if i < 32}
    for i, _, _ in reversed(stack):
        used = {col[o] for o in adj[i] if o in col}
        col[i] = next((r for r in ORDER if r not in used), -1)
    return col


def reg(c):
    return "s%d" % (c - 16) if 16 <= c < 24 else "s8" if c == 30 else "t%d" % (c - 8) if 8 <= c < 16 else str(c)


if __name__ == "__main__":
    adj, cost, ctx = load(sys.argv[1], sys.argv[2])
    stack = simplify(adj, cost)
    real = [p["id"] for p in ctx["push"]]
    print("pushes: compiler %d, replay %d, same order: %s" % (len(real), len(stack), real == [i for i, _, _ in stack]))
    col = select(adj, stack)
    fin = {n["id"]: n["color"] for n in ctx["final"]}
    print("colour mismatches:", sum(1 for i in col if i >= 32 and col[i] != fin[i]))
    print("receiver:", reg(col[32]))
    print("last pushes:", [i for i, _, _ in stack[-8:]])
