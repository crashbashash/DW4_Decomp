# Register allocation of the pinned MWCC: node ordering, receiver colour, and the tools

Notes from matching the GAMERAM dispatcher ([result](../systems/combat-dispatcher.md)): how the allocator orders and colours its nodes, what decides the receiver's register, and the source forms that move a node. Tools: `tools/dispatcher/regalloc_trace.py`, `regalloc_sim.py`, `localize_slots.py`.

## The allocator (read from the pinned compiler, checked against the draft)

`Coloring.c` in the pinned combat `mwccps2.exe` (simplify at 0x4c3f30, select at 0x4c42a0), GPR class:

* A node is a virtual register (ids from 32; ids 0..31 are the physical registers).  Its degree counts every neighbour,
  virtual or physical.  K = 25 allocatable registers.
* A virtual register that lives across a call has the physical neighbours `zero, v0, v1, a0-a3, t0-t9, sp, ra` = 19
  (the "floor"); the receiver additionally has `gp` (it is live across the two `lbu ...,(gp)` guard-byte reads at
  0x3fdc38/0x3fdcb8) = 20.  Most other long-lived nodes have the floor of 19.
* **Simplify** scans the nodes in ascending id and pushes every node whose degree is < 25 (decrementing its neighbours as it
  goes); it repeats the scan while anything was pushed.  When a scan pushes nothing it **picks** the remaining node with the
  smallest `cost / degree` (cost = reference count, x8 per loop level, computed lazily at the first pick; ties go to the highest
  id), pushes it, and rescans.
* **Select** pops in reverse push order and gives each node the lowest free register number
  (`v0 < v1 < a0.. < t0.. < s0..s7 < t8 t9 < s8`).  The last node pushed is coloured first and gets `s0`.

The complete push order of the 153 nodes that survive the first scans in the draft is reproduced (153/153) with exactly these
rules, so the model is reliable for the part of the process that decides the receiver.

**Read the right colouring pass.**  The compiler colours the function twice (the first pass spills 14 values, spill code is
inserted, the second pass produces the emitted registers).  `regalloc_trace.py` follows every pass and reports the last big
one; the colours at the end of the first pass are not the emitted ones (read there, the receiver showed `s3` while the object
had `s0`).  `--adj DIR` also dumps the interference graph, and `regalloc_sim.py` replays simplify/select on such a dump exactly
(7,405 of 7,405 pushes and every colour), so what-if changes cost milliseconds.

## What decides the receiver

The receiver's colour is not a prologue or alias problem and no change there moves it.  It is the outcome of how the compiler's
graph colouring resolves the hot regions of the function, and four FIGHTCALC regions (sub-commands 13, 6, 3 and 20) each, on
their own, force it to `s0`.  `regalloc_trace.py` measures it in about a second.

The receiver is node 32 (the parameter vreg, cost 4181).  It **is not adjacent to every node** (degree 1,769 of 7,437) but it is
stuck until at most four of its neighbours are unpushed (it is pushed when its degree drops below 25), and the colour it gets is
decided only by those last survivors (they are coloured first: `s0..s3`).

* Retail: the receiver is `s4`, so exactly four mutually adjacent nodes outlive the receiver (they are the `s0..s3` nodes
  next to it at the function start).
* A six-wide hot clique gives `s0`.  When the survivors of the last pick are the receiver and six hot-loop nodes of FIGHTCALC
  command 6 (costs 49 168 200 320 344 425), the six have the floor of 19, so after the last pick they have degree 24 and are
  pushed in one scan; the receiver has 20 + 5 = 25, was already passed by that scan, and is pushed last, alone.  Colour `s0`,
  with the six at `s1..s6`.

Isolating one sub-command at a time (`--only-case N`; everything else emptied) in a draft whose receiver is `s0` gives:

| kept | receiver colour | last survivors (cost) |
| --- | --- | --- |
| none of the 22 (parent switch only) | **s4**, pushed 4th from last | - |
| 1, 2, 5, 21, 14-19, 0, 4, 7-12 | s4 | - |
| 13 (P2ESKILLUP) | s0 | 14 27 27 33 17 357 |
| 6 (P2EEXPUP) | s0 | 49 168 320 425 200 344 4181 (the loop of 4 iterations) |
| 3 (E2PDAMAGE) | s0 | 19 15 95 19 31 451 |
| 20 (P2PKOUKAMAGIC) | s0 | 40 85 56 55 41 41 56 2069 |

So the receiver is `s4` in every case where the region leaves no six-wide hot clique, and `s0` as soon as any one of 13/6/3/20
does.  Retail is `s4` with all four present, hence in retail each of those four regions resolves with fewer / differently
shaped surviving hot nodes than such a draft's.  This is the property to chase region by region.

**How four survivors arise.**  Each rescan starts at the lowest id, which is the receiver.  In the last group (the hot
FIGHTCALC 6 loop: index, player record, level, the exp chain, plus total/class/two GetInt values) the receiver is stuck
(20 + 5 neighbours).  Nodes of the group are only stuck at their visit if they are visited **before** the first pushable node
of the scan; the pushable ones (total, leveled flag) get pushed, and the next scan pushes the receiver while the visited-first
nodes are still there.  So survivors = group members whose **ids are lower than the lowest-id pushable member**.  With the
player record (id 1415) and the exp chain (ids 1428/1497) above `total` (id 732) they are pushed with it, so only two
survivors are left (receiver `s2`); with both below `total` four survive and the receiver is `s4`.

**Ids follow declaration order.**  A function-level local gets its vreg id from its position in the declaration block
(block-local declarations and later webs get larger ids); two assignments of the *same* variable that join into one web share
one id.  Hence the two source forms that colour the receiver `s4` (exact-diff 2,717 -> 1,146, shape 71 -> 67): the old-exp /
new-total chain of case 6 is one variable `temp_s0_9` (retail keeps both in `s0`; this also avoids a separate web), and
`temp_v0_68` is declared right after it.

Pointer-typed copies of call results take their id from their declaration position; integer copies take it from call order.

## Moving a node to another register

Because every region's colouring is the reverse push order of its own group, **the same lever fixes register
permutations in any region**: a clique is drained by picks (smallest cost/degree) and ascending-id scans, and the colours it receives are the
reverse of that order.  To make a node take a higher/lower register, change its relative id (declaration position,
block-local vs top-level, joining webs into one variable) or its cost.  Use `regalloc_trace.py --adj/--ctx` then
`regalloc_sim.py`, and identify a node by adding a dummy use (`beMessenger_AppendInt(arg0->_messenger, var);`) and seeing which
cost changes by 8.  Node ids that are stable across such edits are the low ones (below about 900).

Things that were measured and did **not** help: relabelling the ids of the hot loop nodes in every order (all `s0`), scaling
their costs, adding edges between the pair webs, extra physical neighbours.  Raising the cost of the case-17 parent values by
x10 also gives `s4` in the replay but corresponds to nothing in retail (those values are cold).

Node names found in the FIGHTCALC 6 loop (ids of the draft before the two declaration forms above): index `var_s3_3` 723, record `temp_v0_68` 1416,
level `var_s1_2` 701, class `temp_s6` 634, `temp_ret_360`/`361` 283/284, base `var_s0_12` 289, total `var_s5_5` 733, old exp
`exp_before` 1428, new total `temp_s0_9` 593; the parent switch case 17 values (`temp_v0_17..23`) are 808, 810, 811, 103, 108,
112, 116.

## Things that were tried and cannot work

* Aliasing the receiver after the first call, through an inline accessor, a one-member holder, a member function with
  `#define arg0 this`, reassigning the parameter: the copy is coalesced and the surviving node is still id 32.
  Adding 3000 reads of the receiver, or a hot loop full of them, changes its cost only; it stays last.
* Initialising any one of the 133 `var_*` locals at function entry: the receiver stays `s0` in all of them.

## Measured improvements in other regions' lines

1. **Parent switch, list search loops (retail 0x3fd7d0, 0x3fd870, 0x3fd920).**  The draft hoists two interior addresses
   (`addiu s3,s1,8` and `addiu s2,s1,16`, ours 0xdc8) into saved registers; retail reloads `8(s3)`/`16(s3)`.  The cause is
   untyped `*(int *)((char *)p + 8)` arithmetic on a `void *`: with a typed list pointer
   (`struct DW4ListRec { char pad[8]; int count; int cap; void **data; };`, `temp_v0_24` declared `DW4ListRec *`,
   `->count` / `->data[i]`) the two `addiu` disappear (shape 303 -> 301, body 41840 -> 41832 bytes; the loop then uses the same registers as retail apart from the v1/a2 swap).
2. **FIGHTCALC 13, level table loop (retail 0x3ff488).**  Retail's `slt at,v0,s7 / bnez at` needs the test written
   `var_s7_2 <= *var_v1_5` (level <= table[i]); the draft's `*p >= level` makes a virtual register of the compare (`slt v0,v0,s7`),
   which also changes the loop-register choice (v1/a2 swap).
3. **FIGHTCALC 7 (retail ~0x403110):** the draft hoists `addiu s3,s1,40` (an interior member address, ours 0x66fc) and keeps
   it in a saved register; retail recomputes the address at each use.

A caution for anyone using register-liveness on the asm: a MIPS branch delay slot executes on the taken path too.  A liveness
pass that treats the slot as a plain fall-through instruction reports phantom uninitialised "live-in" variables (retail
showed six; with the slot modelled correctly there are two, the cmd-5 value and the cmd-13 value, in both retail and the draft).

## Using the tracer

    python3 tools/dispatcher/regalloc_trace.py tools/dispatcher/draft.cpp              # whole function
    python3 tools/dispatcher/regalloc_trace.py tools/dispatcher/draft.cpp --only-case 13 --tail 9

It prints the receiver's colour and the last pushes (colouring order is the reverse).  A change to a region is an improvement
towards retail when `--only-case <that region>` turns the receiver from `s0` to `s4` (a necessary, not a sufficient, condition:
retail's single-region behaviour is not observable, only the whole function's).
Requirements: gdb, 32-bit capable `as`/`ld`, the wibo loader; the script patches the compiler's memory image in the debugged
process only and refuses to run if the bytes at its patch sites differ from the pinned build.

Without the tracer, `python3 tools/frameslots.py 0xVA --cand <file> --registers` names the variable behind each of the
candidate's registers from the debug records b52 writes under `-g`, which leaves the code unchanged (one location per
variable; [frame slots against retail](understanding-shapes.md#frame-slots-against-retail)). It works under b52, which has no
tracer profile.

## Small functions: tool and lessons

`python3 tools/dispatcher/regalloc.py FUNCTION_OR_VA CANDIDATE.c[pp]` ([usage and limits](../../tools/dispatcher/README.md)) runs the
tracer on any single function with the compiler and flags the build uses for it (its `units.tsv` profile; b52, the 3.0
default compiler and the combat build have patch profiles), ties the differing registers of the emitted code to graph nodes,
replays simplify/select, searches the id permutations that give retail's colours, and then searches single graph edits
([below](#b52-coalescing-and-the-graph-edit-search)).  What the first sweep of near-miss functions showed (all verified byte
for byte):

* Ids follow the order the IR builder creates values, and that order is **not** the order of the source text for a commutative
  expression: `a + b * 4` and `b * 4 + a` produce the same IR.  Splitting the expression into statements with separate locals
  (`idx = f(x) * 4; p = (int *)(idx + (int)p);`) fixes the creation order and, through the operand order of the final add, the
  `addu rd,rs,rt` operand order as well.
* Reassigning one local (`p = base; p = p + idx;`, `arg1 *= 4; arg1 += arg0;`) joins the values into one web, which is how retail gets
  `sll a1,a1,2 / addu a1,a1,a0`; a fresh temporary per step cannot produce it.
* A constant stored early gets a high id when it is created early: moving the `flag = 1;` store behind the first data store gave the
  first loaded value the lower id retail needs.
* Two loads in the other order (`lw v1,0(a0); lw v0,0(a1)` against ours) are an evaluation-order difference, fixed by swapping the
  operands of the comparison, not by anything in the allocator.
* `lw t9,N(..); jalr t9` is the form of a C++ virtual call; no id order produces `t9` for an ordinary call.
* `lui rA / addiu rB,rA,lo` with a scratch `rA` is an address materialised as a literal or through a different expression, not a
  colouring difference.
* Alternate compiler at `-O3,p`: a volatile struct member (or `*(volatile T *)&x->f`) forces its load at the statement position
  and cannot be forward-substituted, so the loaded value becomes a named virtual register with a low id. This reorders integer
  and float colouring and fixes swapped f-registers and operand order that no ordinary spelling changes. A function using it stays
  `unapproved` until the owner approves that use ([source approvals](source-approvals.md)). Float colouring is the tracer's class-1 pass.
* Alternate compiler at `-O3,p`: accumulating a sum in place on the call-result web (`r = call << 18; r += prop->field; b = r;`)
  instead of `b = field + (call << 18)` keeps the first sum out of the saved register holding `b` across the second call, producing
  retail's `move s1,v0` in the `jal` delay slot and the trailing `nop`.

## b52: coalescing and the graph-edit search

The tracer has a b52 profile (`local/mwcps2/3.0b52-030722`, the compiler of the core and most engine units): every patch site
is the combat site + 0x550 with the same bytes. A whole `CoreLibrary.cpp` traces in about a minute (3,260 colouring passes);
`regalloc.py` keeps the pass whose IR fits the requested function, so a whole-file candidate works. A test file that holds
`#include "src/engine/core/CoreLibrary.h"`, the inline helpers and the one function gave the same instructions as the whole
file for 0x2d9740 and traces in under a second.

**Coalescing (b52, verified).** The coalescer is its own pass (0x4bc7e0, phase name "After coalesceregisters"), run twice
before colouring. Read from the code and checked on every general-register pass of `CoreLibrary.cpp`:

* it merges the two nodes of every copy that do not interfere, with no degree test; the only vetoes are `zero` and nodes
  marked by its graph builder (0x4bbe50). The surviving node is always the **lower id** (alias array at `[0x58acd0]`;
  35,255 merged nodes in 3,251 passes, none into a higher id);
* the colouring graph is built afterwards from the rewritten code, so a merged node has no edges and degree 0 and appears in
  no neighbour list (0 exceptions in the same passes). A coalesced node therefore adds **no** degree to its neighbours; the
  sms rule "a coalesced node adds +1 to every neighbour" (GC/1.2.5) does not hold on b52;
* a copy between two declared locals coalesces like any other copy: in
  `int x = 0, y, i; for (...) x += p[i]; y = x; while (y > 100) y -= g(y); return y;` the copy `y = x` reaches the allocator
  and `y` (id 35) is merged into `x` (34). The sms rule "a move between two named locals never coalesces" does not hold
  either;
* so a local copy of a parameter (`int i = index;`, a one-member struct holding it, a copy inside one branch) keeps the
  parameter's id when the two do not overlap: it cannot move the parameter's colour. On 0x2d9740 these spellings gave the same
  graph as the draft. Simplify also skips nodes flagged 4 (degree 0, no edges); the replay leaves them out. With that the
  replay gives the compiler's push order and colours in 3,246 of the 3,251 passes; the other 5 are not explained.

**Graph edits** (the sms tip "replay the allocator when only registers differ"). After the id permutations, `regalloc.py`
tries one edit at a time on the involved nodes and their most connected neighbours, replays each, and prints the ones that
give retail's colours, with the `name` of each node guessed from the declaration order and the nodes the coalescer merged into
it. The edits: renumber a node just below/above another (a declaration or creation-order change; the moved node is an involved
node, one of the edit pool, or any neighbour of an involved node, and for a set of involved nodes that must change from one
colour to the same other one, each with exactly one neighbour of one cost and degree, those neighbours are moved at once),
merge two non-adjacent nodes (one variable; the merged web keeps the lower id, as the coalescer does), delete a node, add an
interference, add one more value live beside a node (a degree edit, below), raise or lower a node's cost by one reference
outside or inside a loop (±1, ±8: the cost is the reference count, x8 per loop level), and split a coalesced node off its
survivor (the copy then has to survive: on b52 only when the two overlap). Edits that renumber a parameter, or put a new
value's id among the parameters', come after the others of the same score: a parameter's id comes from its position. When
no single edit is a full solution it tries pairs (`--edit-depth 1` turns that off); when no pair is either, it prints the
best partial edits of each kind, the kind of the best one first. About 1,000 replays take a second for a 290-node graph
(0x20bb20, below: some 10,000 single edits in 9 seconds).

**Degree edits.** A node's colour can depend on how many neighbours it still has when simplify scans it, and a phantom
neighbour (one that is never pushed) does not model a real value: a real one is pushed too, takes a register and blocks it
for its neighbours. So the degree edit adds a new virtual node, a value kept live across the chosen node's range and its
calls: it interferes with the node and with every neighbour of it (the physical ones included), or with all but one
involved node (a value that starts after that node's last use or ends before it is set). Its cost is the chosen node's
(at least 2: one definition, one use), and it is tried at each id just below and above the nodes of the edit pool (where
it is declared or created). The report gives the colour the replay gives it, and says so when that is also the colour of
the involved node it leaves out (then the new value uses no register that node does not use already).

What it found:

* 0x2d9740 (`igDriverDatabase_SetSubPropertyValue`, MatchY's draft rebased): no single edit, but every two-edit solution
  starts with the same one: `index` (node 33) needs an id between node 71 (the `names` smart pointer's scalarised member) and
  node 74 (`index * 4`, a CSE temporary); then the list loaded for the second store (node 42) and `values`' member (72) must
  swap order. Retail's `index` is therefore a value the optimizer creates after class members are scalarised, not the
  parameter's own web, which the local-copy spellings above cannot produce. Not matched.
* 0x2d7280 (`igDependencyOrderedList_TopologicalSort`, MatchC's draft): 22 nodes over the whole function and 4 non-register
  differences; no single edit or pair reaches retail (best: 70 of 87 constrained nodes), so the remaining difference is in the code, not the colouring. Not matched.
* 0x1dc610 (`igSorter::endCompoundRenderPackage`, each package-list append through a helper taking the list): the sorter
  (a parameter) colours s2 and the three lists s1, retail the reverse. Each list has degree K at the first scan and is pushed
  after the sorter; each append's count (degree 24) is pushed in that scan, but after the list's id. Both searches give
  "each count's id below its list's" first (the count then drops its list to 24 before simplify reaches it, and the sorter
  is coloured before the lists); the other full edits move the parameter. Matched by writing each append out with the
  count declared ahead of the list.
* 0x20bb20 (binds a texture chain to a program in `src/engine/p2texture.c`, NmGfxTex's best draft): `textures` (node 32,
  a parameter) colours s4 and `program` (33) s3, retail the reverse. The last group of the pass is eleven values live
  across the calls at its end; after the picks (34 49 35 70 48 66) every one of 32, 33, 36 (`uploadCount`), 37 (`count`)
  and 39 (`bound`) has degree 24 and the rescan pushes them in id order, so 33 is coloured before 32. No id order of the
  locals and no cost change of 32 or 33 flips them (only renumbering the parameter does). The best edit (144 of 146
  constrained nodes; no edit fixes the other two, 44 and 174) is one more value live beside `program` and the rest of the
  group but not `textures`, numbered between
  `stage` (35) and `uploadCount` (36): it is pushed right after 33, takes s3, and 33 then gets s4 and 32 s3. The same value
  beside 36, 37 or 39 works as well. Its s3 is the register `textures` gets too, which retail uses for nothing else, so
  in retail it would add no register; which source value it is has not been found. Not matched.

