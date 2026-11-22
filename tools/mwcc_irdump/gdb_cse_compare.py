"""gdb_cse_compare.py: how IRO_CommonSubs grouped one function's expressions, which pairs it compared and why a compared
pair differed, which candidates never met, and which members of a group share one value (gdb script).

Common-subexpression elimination first sorts the expressions into groups: in flow order, each expression is compared
with the LATEST member of every existing group, in the order the groups were opened; the first group that compares
equal takes it, and when none does it opens a new group. The node comparison needs equal node kinds, equal
`nodeflags` (bit 0x200 ignored) and equal types, then recurses into the operands. Then, flow node by flow node, an
occurrence reuses the value of an earlier member only where the group is available: computed earlier in the same flow
node and not killed since, or available on entry (computed on every path into the flow node). Every other
occurrence computes the value again, and the computations a reuse can take its value from share one temporary; an
occurrence that a later one reuses computes into a temporary of its own even when an earlier value reaches it.
So two alike expressions stay apart because they were compared and differ, because they never met in the grouping
(one joined a group whose latest member by then was another, or an earlier group took it first), or because the
second does not take the first one's value. This stops in one call of IRO_CommonSubs and writes to IRDUMP_OUT, per
group (here four `index << 2` shifts of one function):

    group 6 (kind 3, nodetype 17): 93 183 229 389
      93: compared with (group:latest) 0:11 1:19 2:450 3:456 4:455 5:45: differ; opens group 6
           node 93 vs 455 (nodetype 17): rtype 5601a8 vs 6d23ce78 [type kind 1 vs 11, size 4 vs 4] -> TYPES NOT EQUAL
      183: compared with (group:latest) 0:11 1:19 2:450 3:456 4:455 5:45: differ; joins group 6 (latest 93)
      ...
      shares one value: 93 389 | 183 229
      183 (flow node 12) does not reuse 93: the value of 93 reaches it, but it computes into a temporary of its own,
      which 229 reuses
      killed at: 54 (flow node 2), 74 (flow node 5)
    group 26 (kind 3, nodetype 17): 296 318
      ...
      never compared with a member: 93 (group 6), 183 (group 6), 389 (group 6)

the members and, for each, the groups it was compared with (with that group's latest member then) before it joined or
opened its own, with the flags or type that made a compared pair differ; the candidates of the same node kind and node
type that never met a member in the grouping; the members that share one value (one temporary); for the first member
of each set after the first, why it does not reuse the value computed before it; and the IR nodes that kill the group.

    IRDUMP_OUT=/tmp/irdump/cse.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_cse_compare.py \
        --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,p -sdatathreshold 2 \
        -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o

IRDUMP_CALL picks the call (default 0, the first: IRO_CommonSubs runs on each optimised function, once per round of
the optimizer's pass loop, in the order the dump log lists them). Node numbers are the dump log's. Run from the
repository root.
"""
import os
import sys

try:
    import gdb
except ImportError:         # imported outside gdb for `report` (tools/test_cse_compare.py)
    gdb = None

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import b52  # noqa: E402


def never_met(group, joins, shapes, compares):
    """The candidates of the same node kind and node type as `group`'s first member, in other groups, that the grouping
    never compared with any member of `group` (the comparison takes each group's latest member only)."""
    members = [node for node, g2 in joins if g2 == group]
    group_of = dict(joins)
    met = {frozenset((node, latest)) for node, _g2, latest in compares}
    return [n for n in sorted(shapes) if shapes[n] == shapes[members[0]] and group_of.get(n) != group
            and not any(frozenset((n, m)) in met for m in members)]


def value_sets(occs):
    """The members of one group (its occurrences, in flow order) that share one value, as lists in flow order.

    The replacement phase (0x532850) looks at the temporary first: an occurrence with one computes into it, even when
    a computation reaches it (its sources); one without a temporary and with sources reads the sources' temporary
    (0x532770 gave all of them one)."""
    parent = {o["node"]: o["node"] for o in occs}

    def find(n):
        while parent[n] != n:
            n = parent[n]
        return n

    by_temp = {}
    for o in occs:
        if o["temp"]:
            by_temp.setdefault(o["temp"], []).append(o["node"])
        else:
            for s in o["sources"]:
                parent[find(o["node"])] = find(s)
    for same in by_temp.values():
        for n in same[1:]:
            parent[find(n)] = find(same[0])
    sets = {}
    for o in occs:
        sets.setdefault(find(o["node"]), []).append(o["node"])
    return list(sets.values())


def apart(o, occs, kills, group):
    """Why the occurrence `o` of `group` computes the value although an earlier member does: ("own temporary",
    [sources], [readers]) when a computation reaches it but it has reusers of its own, so it computes into its own
    temporary; ("killed", earlier member, [killing nodes]) when the value was computed earlier in its flow node and
    killed since; ("not on entry", flow node) when the group is not available on entry to its flow node (not computed
    on every path into it, or killed on one); ("unreached", flow node) otherwise."""
    order = [x["node"] for x in occs]
    if o["temp"] and o["sources"]:
        return ("own temporary", sorted(set(o["sources"]), key=order.index),
                [x["node"] for x in occs if o["node"] in x["sources"]])
    if o["role"] == 1:
        at = {n: k for k, (n, _flow, _groups) in enumerate(kills)}
        before = [x["node"] for x in occs[:order.index(o["node"])] if x["flow"] == o["flow"]][-1]
        return ("killed", before, [n for n, _flow, groups in kills if group in groups
                                   and at[before] < at[n] < at[o["node"]]])
    return ("not on entry" if not o["entry"] else "unreached", o["flow"])


def report(shapes, compares, joins, rejects, occurrences, kills, other=()):
    """The text of the log.

    shapes: {node: (kind, nodetype)} of every candidate; compares: [(candidate, group, latest member)] in the order
    the grouping made them; joins: [(candidate, group)] in order (the first join of a group opens it); rejects:
    {(candidate, group): [why lines]}; occurrences: [{node, flow, group, role, entry, sources, temp}] in flow order
    (role and entry as the expression record holds them, sources the nodes a reuse takes its value from, temp the
    temporary's address or 0); kills: [(node, flow, [groups it kills])] for every IR node in flow order; other: why
    lines of comparisons made outside the grouping."""
    members = {}
    for node, group in joins:
        members.setdefault(group, []).append(node)
    tried = {}
    for node, group, latest in compares:
        tried.setdefault(node, []).append((group, latest))
    lines = []
    for group in sorted(members):
        nodes = members[group]
        lines.append("group %d (kind %d, nodetype %d): %s" % ((group,) + shapes[nodes[0]] + (" ".join(map(str, nodes)),)))
        for k, node in enumerate(nodes):
            before = [(g2, latest) for g2, latest in tried.get(node, []) if g2 != group]
            text = "  %d: " % node
            if before:
                text += "compared with (group:latest) %s: differ; " % " ".join("%d:%d" % x for x in before)
            if k:
                text += "joins group %d (latest %d)" % (group, next(latest for g2, latest in tried[node] if g2 == group))
            else:
                text += "opens group %d" % group
            lines.append(text)
            for g2, _latest in before:
                lines.extend("       " + why for why in rejects.get((node, g2), []))
        never = never_met(group, joins, shapes, compares)
        if never:
            lines.append("  never compared with a member: %s" % ", ".join(
                "%d (group %s)" % (n, dict(joins).get(n, "-")) for n in never))
        occs = [o for o in occurrences if o["group"] == group]
        sets = value_sets(occs)
        if len(occs) > 1:
            lines.append("  shares one value: %s" % " | ".join(" ".join(map(str, s)) for s in sets))
        for s in sets[1:]:
            o = next(x for x in occs if x["node"] == s[0])
            why = apart(o, occs, kills, group)
            if why[0] == "own temporary":
                text = "the value of %s reaches it, but it computes into a temporary of its own, which %s reuses" % (
                    " ".join(map(str, why[1])), " ".join(map(str, why[2])))
            elif why[0] == "killed":
                text = "computed at %d in its flow node and killed since at %s" % (why[1], " ".join(map(str, why[2])))
            elif why[0] == "not on entry":
                text = "not available on entry to its flow node"
            else:
                text = "available on entry to its flow node, but no computation reaches it"
            earlier = [x["node"] for x in occs[:occs.index(o)]]
            lines.append("  %d (flow node %d) does not reuse %s: %s" % (o["node"], o["flow"], " ".join(map(str, earlier)),
                                                                        text))
        killed = ["%d (flow node %d)" % (n, flow) for n, flow, groups in kills if group in groups]
        if killed:
            lines.append("  killed at: %s" % ", ".join(killed))
    if other:
        lines.append("comparisons outside the grouping:")
        lines.extend("  " + why for why in other)
    return "\n".join(lines) + "\n"


def main():
    import gdb_common as g
    inferior = g.start(b52.COMMON_SUBS)
    rd = g.reader(inferior)
    out = open(os.environ["IRDUMP_OUT"], "w")
    gdb.execute("break *%#x" % b52.COMMON_SUBS)
    for _ in range(int(os.environ.get("IRDUMP_CALL", "0")) + 1):
        gdb.execute("continue")
    gdb.execute("delete")
    ret = rd(g.esp(), 4)
    for address in (b52.GROUP_MATCH, b52.GROUP_ADD, b52.NODE_EQUAL_FLAGS, b52.NODE_EQUAL_TYPES, b52.SHARE_KILLS,
                    b52.SHARE_DONE, ret):
        gdb.execute("break *%#x" % address)
    shapes, compares, joins, rejects, occurrences, kills, other = {}, [], [], {}, [], [], []
    current = None                                     # (candidate, group) of the comparison under way

    def index(node):
        return rd(node + b52.NODE_INDEX, 4)

    def node_of(expr):
        node = rd(expr + b52.EXPR_NODE, 4)
        shapes[index(node)] = (rd(node + b52.NODE_KIND, 1), rd(node + b52.NODE_TYPE, 1))
        return index(node)

    def bits(vector):
        words = [rd(vector + 4 + 4 * w, 4) for w in range(rd(vector, 4))]
        return [32 * w + b for w, word in enumerate(words) for b in range(32) if word >> b & 1]

    def walk():
        flow = rd(b52.FLOW_HEAD, 4)
        while flow:
            node, last = rd(flow + b52.FLOW_FIRST, 4), rd(flow + b52.FLOW_LAST, 4)
            while node:
                expr = rd(node + b52.NODE_EXPR, 4)
                if expr:
                    sources, cell = [], rd(expr + b52.EXPR_SOURCES, 4)
                    while cell:
                        sources.append(node_of(rd(cell, 4)))
                        cell = rd(cell + 4, 4)
                    occurrences.append(dict(node=index(node), flow=rd(flow + b52.FLOW_INDEX, 2),
                                            group=rd(expr + b52.EXPR_GROUP, 4), role=rd(node + b52.NODE_ROLE, 1),
                                            entry=rd(expr + b52.EXPR_ENTRY, 1), sources=sources,
                                            temp=rd(expr + b52.EXPR_TEMP, 4)))
                if node == last:
                    break
                node = rd(node + b52.NODE_NEXT, 4)
            flow = rd(flow + b52.FLOW_NEXT, 4)

    seen = set()
    while True:
        gdb.execute("continue", to_string=True)
        pc = g.register("pc")
        if pc == ret:
            break
        if pc == b52.GROUP_MATCH:
            latest = rd(rd(g.esp() + 8, 4), 4)
            current = (node_of(rd(g.esp() + 4, 4)), rd(latest + b52.EXPR_GROUP, 4))
            compares.append(current + (node_of(latest),))
            continue
        if pc == b52.GROUP_ADD:
            joins.append((node_of(rd(g.esp() + 4, 4)), rd(g.esp() + 8, 4)))
            current = None
            continue
        if pc == b52.SHARE_KILLS:
            kills.append((index(g.register("ebp")), rd(rd(g.esp() + 0x10, 4) + b52.FLOW_INDEX, 2),
                          bits(rd(b52.KILLED, 4))))
            continue
        if pc == b52.SHARE_DONE:
            walk()
            continue
        a, b = g.register("edi"), g.register("esi")
        ia, ib = rd(a + b52.NODE_INDEX, 4), rd(b + b52.NODE_INDEX, 4)
        ntype = rd(a + b52.NODE_TYPE, 1)
        why = None
        if pc == b52.NODE_EQUAL_FLAGS:
            fa, fb = rd(a + b52.NODE_FLAGS, 2), rd(b + b52.NODE_FLAGS, 2)
            if (fa ^ fb) & ~b52.FLAG_IGNORED:
                why = "node %d vs %d (nodetype %d): nodeflags %04x vs %04x -> NOT EQUAL" % (ia, ib, ntype, fa, fb)
        elif g.register("eax") & 0xFF == 0:
            ta, tb = rd(a + b52.NODE_RTYPE, 4), rd(b + b52.NODE_RTYPE, 4)
            why = ("node %d vs %d (nodetype %d): rtype %x vs %x [type kind %d vs %d, size %d vs %d] -> TYPES NOT EQUAL"
                   % (ia, ib, ntype, ta, tb, rd(ta, 1), rd(tb, 1), rd(ta + 2, 4), rd(tb + 2, 4)))
        if why is None:
            continue
        if current is not None:
            rejects.setdefault(current, []).append(why)
        elif why not in seen:
            seen.add(why)
            other.append(why)
    out.write(report(shapes, compares, joins, rejects, occurrences, kills, other))
    g.finish(out)


if gdb is not None:
    main()
