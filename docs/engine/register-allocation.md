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

## Small functions: tool and lessons

`python3 tools/dispatcher/regalloc.py FUNCTION_OR_VA CANDIDATE.c[pp]` ([usage and limits](../../tools/dispatcher/README.md)) runs the
tracer on any single function with the compiler and flags the build uses for it (the 3.0 default compiler and the combat build
both have patch profiles), ties the differing registers of the emitted code to graph nodes, replays simplify/select, and
searches the id permutations that give retail's colours.  What the first sweep of near-miss functions showed (all verified byte
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
