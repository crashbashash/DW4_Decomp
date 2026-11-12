# GAMERAM draft: reviewed ABI and memory repairs

The full `beNDMWGameRam::vfunc_34` callback (41,864 code bytes, including the nested
36,000-byte FIGHTCALC region) is described in
[the dispatcher page](combat-dispatcher.md). This page describes the reviewed repairs
applied to its m2c draft. The repairs make a provisional draft more faithful; they do not
by themselves establish complete equivalence, and the draft variants measured below are
diagnostics, not the dispatcher's source.

## Call interfaces and type propagation

The [flat context](../../scripts/gen_combat_context.py) supplies reviewed
interfaces for the scalar result-count getters, allocator lookup, cached enum
builders, string-pool accessor and generic list/data accessors. These describe
meaningful machine inputs and result words, not claimed original C++ declarations.

`igObject_GetAllocator` consumes one generic object. Without that prototype,
m2c retains stale extra arguments and propagates the callback receiver's
`beNDMWGameRam *` type to another object returned by the messenger. The resulting
draft mislabels its +40 member as `_dBWeapon` and performs `object + 0x28`
as struct-pointer arithmetic. The generic interface keeps that object's type
opaque and the offset in bytes.

The integer-buffer getter at `0x3e9090` returns a guest address word in the
analysis context. A late inferred `int *` return leaves already-scaled
`index * 4` expressions inside C pointer addition, producing a second scaling:
a local compiled-instruction scan finds 19 indexed uses shifting by four bits.
With the address-word return the projection shifts by two, as required for four-byte entries.
This local scan is evidence for address units, not full control-flow equivalence.
The byte-buffer getter at `0x406f00` instead has an explicit byte-pointer result.
Byte-property records have a reviewed one-byte value at +12. Their named value
member preserves its width. The byte-pointer return alone is insufficient:
`m2c_batch.clean` defaults bare pointer-expression dereferences to `int`.
Five explicit source repairs restore three buffer loads and two stores to bytes.
A whole-callback compile comparison isolates four changed instruction words:
`lw` to `lbu` at `0x3fdbf4`/`0x3fdc74`, and `sw` to `sb` at
`0x3fdc48`/`0x3fdcc8`. The fifth load compiles to `lbu` without the repair because the
fixed byte argument to `AppendBool` narrows it. Its source width is repaired as well
so correctness does not depend on that consumer. Sizes and frame are unchanged by the repairs.

The [list accessor](../../src/engine/ObjectList_GetAt_003e9260.c)
takes an `igDataList` receiver. Its complete five-instruction body reads
the buffer at +16 and an indexed word. GAMERAM supplies object lists and lists
of lists, whose hierarchy reaches the declaring base `igDataList`. The source
uses `igDataList::_data`, preserving all 20 bytes and the unchecked index.
A LoadIntf2 `_system` association for that receiver is refuted.

## Guarded diagnostic source repairs

`scripts/repair_combat_draft.py` applies 17 source changes to a cleaned
GAMERAM draft:

- Three object-reference cursors advance one four-byte element, rather than four
  elements. Original steps are at `0x3fd844`, `0x3fd8ac` and `0x3fd95c`.
- The skill-band cursor advances one signed short, matching the two-byte step
  at `0x3ff4ac`.
- Two item `_isEquip` predicates read a byte at +16, matching the two original
  `lbu` instructions and the reflected `beNDMWItemBase` field.
- The rank override's returned entry has a byte at +8. Its preceding list count
  also sits at +8 but remains a word; offset equality is insufficient evidence
  for access width.
- Three byte-buffer reads and two writes remain byte accesses after cleanup.
- The first integer-buffer element store receives an explicit word-pointer cast
  after its getter is modeled as an address word.

Before writing output, the transform checks 36 original words: the 23 original
access/stride guards and 13 words proving both technique table address calculations. It also requires
one complete callback definition, exact cursor types and unique source preimages.
Already partially repaired or changed source fails for review. Regression
tests cover the edits, every counterfactual original-word mutation, changed
pointer types, duplicate preimages, partial repair and a different function.

The optional `--hit-switch` projection also checks six original control words.
Retail branches to the magic-hit block and otherwise branches past it to the
regular calculation. A one-case sparse switch reproduces that arrangement;
an if/else draft puts the magic arm at the end. The transform evaluates
the same pure category division once and keeps each arm's statements. Arms
with unreviewed break/continue/label transfers fail for review. This is a
compatible source rendering, not a claim of original syntax.

In a diagnostic with indexed CTRLITEM loops and reviewed scalar call interfaces,
that projection aligns the hit, critical and damage entry addresses. The
1,056-byte critical region has 264 aligned instruction shapes after normalizing
general registers, stack slots and branch targets. Separately checking its
branches confirms all 25 internal destinations agree; its external exit is
relocated. Register assignments and stack layout differ in that diagnostic, so this regional
result is not a byte match.

For a diagnostic intermediate, from the repository root:

```sh
python3 scripts/gen_combat_context.py
python3 tools/m2c_one.py 0x3fca10 --context build/combat-context.c > build/combat-raw.c
python3 scripts/repair_combat_draft.py build/combat-raw.c --raw --out build/combat-repaired.c
python3 testing/test_combat_draft_repairs.py
```

Add `--hit-switch` when inspecting that reviewed control-flow projection.
Sixteen repair/control tests cover the modes, original-word mutations and
missing or changed buffer/table preimages.

The output is an intermediate, not a standalone verified translation unit. The
context definitions, initialization proofs, signed high-product operations and
CTRLITEM acknowledgment need their separate reviewed treatment. Nothing
is copied automatically into `src/`. The complete instruction and both switch
table comparisons remain mandatory.

## Complete quotients across branch merges

The damage spread selects factors 950, 975, 1000 and 1025, then divides the
signed word result by 1000. The raw draft merges partial high products and
their sign corrections. Lowering those partials through a generic 64-bit
multiplication macro causes long constant shift/add sequences where retail
uses a word multiply-high. A private branch-local quotient reconstruction
removes those sequences. The analogous EXP branches need complete `/3` and
`/5` operations, not a truncating quotient plus another sign correction.

The unshifted `/3` reciprocal is protected in
[`m2c_compat.py`](../../tools/m2c_compat.py). It uses `0x55555556`, followed by
the logical sign bit. For example, prematurely replacing its partial with
truncating `-3 / 3`, then adding one, gives zero instead of minus one.
The full signed-word proof treats positive and negative domains separately:
positive product residuals must be strictly below the scale; negative residuals
may equal it at `INT_MIN`. All eleven reviewed reciprocal patterns have these
feasible quotient/remainder bounds, AST checks and synthetic instruction tests.
Unsigned/wide/mismatched corrections remain outside the rule.

Without the growth-label and scalar-lifetime projections below, the reviewed private
variant is 41,768 bytes versus retail's 41,864, with a 1,216-byte frame
versus 1,200. It fails complete
instruction and table comparison. Smaller code size, normalized shapes and
correct arithmetic identities do not establish a matching callback.

## Skill-growth label indexing and scalar lifetime

The growth-label table at `0x4cf5c0` has six pointers, naming BLUNT_GROW,
SLASH_GROW, STAB_GROW, BASH_GROW, SHOT_GROW and CRUSH_GROW. Retail computes
`table + index * 4` (`sll a2,s5,2` at `0x3ff574`) and loads the label pointer.
With no table type, the draft's cleaner retains an explicit `index * 4`
inside addition to an `int *`, resulting in a sixteen-byte stride. The context
declares the six string pointers, and both raw and cleaned output retain
`DAT_004cf5c0[var_s5_3]`. This fixes address units without adding an index guard;
retail's unchecked index remains unchecked.

[`test_combat_context.py`](../../testing/test_combat_context.py) checks all six
retail strings and the original shift/address/load instructions. A synthetic
instruction pipeline using the generated context verifies that cleanup retains
the element index and string-pointer result. The full callback regenerated
with this context passes the thirteen memory repairs plus hit projection.

Two further private source projections improve the arithmetic shape. Retail
negates the technique's `HP` column immediately at `0x3fe8d4`, tests that word,
and multiplies it by 20 later. Moving the draft's delayed negation back to its
producer gives the same modular word operation; the diagnostic uses unsigned
negation before conversion to an integer word, preserving `INT_MIN`. Separately,
keeping the signed-short chance-table result in an `int` removes four redundant
sign-extension instructions while preserving its promoted value.

The combined diagnostic is 41,752 bytes with a 1,216-byte frame, versus retail's
41,864 and 1,200. It does not match. A generic inline clamp
changes some joins but does not resolve the differences. Pointer-return,
explicit index-sequencing and additional unused formal-argument projections do
not restore the retail frame.

## Technique-action branch order

The final FIGHTCALC case tests the pairs 40/45, 55/60 and 50/-50, then
65, 80 and 75. These comparisons are interleaved with their action bodies.
The draft's sparse switch instead emits the tests together in reverse order.
An equivalent private `if` ladder restores the retail ordering. The context
regression test also checks the eighteen original comparison/branch words;
this establishes the control sequence, not original C++ syntax.

Six nearby-list loops can also be rendered as indexed `for` loops instead of
separate element and byte-cursor induction variables. Each preserves the cached
count, skipped nonpositive counts and body calls. Combined with the ladder,
the final action region's normalized instruction edits fall from 240 to 172.
This comparison abstracts general registers, stack slots and branch targets;
it is a discovery aid, not a byte or control-flow equivalence oracle. The
combined callback is 41,792 bytes / frame 1,216 and fails full verification.

## Materialized reference temporaries

Retail stores five reference temporaries at stack offsets `0x4ac..0x49c` and
reloads them for ownership and item operations. A diagnostic compiler debug
inspection instead assigns their scalar-pointer draft equivalents to registers.
A plain one-word record is still promoted. Explicit owning C++ objects restore
stack homes but change the frame and emit additional destructor code.

A nested inline-release projection emits a 128-byte destructor and a 68-byte
release body at inline level 1, while a destructor that calls an external release
emits 88 bytes. These are private source-model hypotheses: sizes do not
prove helper identity or original inline settings. The oracle rejects the
unowned emitted code.

A case-local scope experiment must exclude the parent command case.
With that switch boundary, case-local declarations are permitted, but they do
not by themselves reproduce retail. Individually restoring the known call interfaces produces
identical code for 37 compiling prototypes; ten other restorations require
additional type recovery.

## Bounded RNG sampling before ratio math

At getter sites `0x403b68`, `0x4043c0` and `0x404bd8`, retail calls the RNG's
vtable slot +96 and computes its unsigned remainder modulo 10000 before the
reusable ratio division. The draft lifts that ratio into a statement before
an embedded virtual call in the following condition. Restoring an explicit
bounded-roll temporary reproduces the original sampling point.

The optional `--rng-samples` mode in
[`repair_combat_draft.py`](../../scripts/repair_combat_draft.py) operates on the
cleaned C before its separate C++ virtual-call projection. It checks 33 original
words covering getter/call, modulus/remainder and ratio-division operations.
Each receiver must have its reviewed declaration, assignment and single call.
Only the exact reviewed ratio assignment may intervene. The transform keeps
one draw and the same arithmetic, adding an unsigned roll local before the
ratio statement. The repair tests cover instruction/source drift, extra
uses or intervening effects, preserved draws and repeat rejection.

For this source projection:

```sh
python3 scripts/repair_combat_draft.py build/combat-raw.c --raw --hit-switch --rng-samples --out build/combat-repaired.c
```

With this projection the complete diagnostic's cases 9/11/12 have 7/17/16 normalized
instruction edits instead of 40/55/54. The normalization abstracts general registers,
stack memory and branch destinations; the full byte/table oracle fails.
The resulting callback is 41,760 bytes with a 1,216-byte frame versus retail's
41,864 bytes and 1,200.

Natural skill/level-up loops and equivalent nonvirtual messenger member calls
do not close the match either. Scoped const initialization and
inline field accessors alter allocation or scheduling but do not restore the
retail frame. Available compiler alternatives likewise do not match this
candidate. These negative probes are diagnostic evidence, not reasons to
weaken the oracle or assume an original source/compiler identity.

## Attack effect lookup order

The `KOUKA` field at `0x5191f0` supplies the effect strings compared with
`sleep`, `ashidome`, `freeze` and `powerdown` in cases 9–12. At query sites
`0x403a4c`, `0x403d64`, `0x4042a4` and `0x404abc`, retail obtains the string
before initializing the result in the `strcmp` call's delay slot. The nested
draft expression instead leaves zero initialization ahead of the lookup.

The optional `--attack-effects` projection materializes the string first. It
checks twenty original query/argument/comparison/initialization words and four
exact source preimages. Each result must be a plain local `int` without an
address escape. One shared string-pointer temporary suffices because the
paths do not overlap. The lookup, comparison and body calls are preserved;
changed sources, intervening effects and repeat application fail for review.
The draft-repair tests cover this and the other transformations.

The full-draft CLI with `--raw --hit-switch --rng-samples --attack-effects`
applies twenty-one reviewed changes. The compiled diagnostic differs
from retail at 41,760 bytes / frame 1,216. Cases 9–12 have 2/4/12/11 normalized
instruction edits; case 9's seven internal relative branch destinations also
agree independently. General registers, stack slots and external destinations
differ. This does not establish a matching region or callback.

## Explicit call-result materialization

The call-order investigations have a reproducible opt-in mode:

```sh
python3 tools/m2c_one.py 0x3fca10 --context build/combat-context.c --materialize-calls > build/combat-materialized.c
```

Every nonvoid call result becomes a temporary at its translation site. Void
calls retain their ordinary rendering. The mode is scoped to one serial
invocation and restores the translator after exceptions. Four integration
and scope tests cover it. The complete callback's ordinary output is unchanged
by the option.

The option's output compiles with the retail 1,200-byte frame, but is 42,360 bytes
long and lacks the reviewed memory/arithmetic repairs. Matching frame size is not
proof.

The materialized draft passes the access-width,
cursor and word-store instruction guards. Completing both damage-spread
quotients and EXP `/3`/`/5`, preserving signed-short table promotion and early
HP negation, and restoring the indexed item loops/scalar interfaces retains the
retail 1,200-byte frame. Adding the reflected work-object view and first hit
branch projection yields 41,896 bytes versus retail's 41,864. Compiler debug
locations put the level cap in `s8`, also as retail does. The receiver and many
other instructions/table targets differ, so this is not a match.

The complete diagnostic has the same static direct-call target histogram as
retail: 1,681 `jal` instructions with no per-target count differences. Static
counts do not prove pathwise ordering or behavior.

## Direct-call boundaries and RNG expressions

`--materialize-boundaries` preserves named call-result
lifetimes and consumed remainders while leaving indirect RNG calls nested with
their bounds. It reproduces the independently reviewed full-draft input. The
ordinary mode and the all-call mode are unaffected by it. See the
[m2c projection contract](../engine/m2c-bulk.md#named-calls-and-consumed-remainders).

With the width, quotient, promotion, HP, item-loop, scalar ABI and
work-object repairs, the first hit projection produces 41,848 bytes with the
retail 1,200-byte frame. The full code and both switch tables differ from retail.
FIGHT case 9 is 792 bytes in both, with 198 aligned instruction forms. A private
lockstep expression audit also checks all seven internal branch destinations,
the external cleanup destination, and 35 static calls over 50 branch paths.
It compares call targets/arguments, load addresses and branch predicates,
including delay slots and the commuted multiplication operands.

That audit assumes the same incoming receiver (`s4` in retail, `s0` in the
candidate), the same initial memory and opaque calls with the reviewed argument
counts and callee-saved-register convention. It enumerates both outcomes without
path-feasibility pruning. Five negative controls alter a target, a branch, an
argument, a delay-slot argument or multiplication input; all are rejected.
These are conditional local dataflow observations, not whole-function semantic
verification or recovered bytes. The audit does not address register allocation
or ownership lifetimes.

Applying the six indexed-list loops to this draft raises its frame to
1,216 bytes and yields 41,896 bytes. The technique ladder alone retains the
1,200-byte frame at 41,840 bytes, but fails full comparison. Code size is not
the acceptance criterion.
A five-reference class projection whose destructor calls the recovered release
helper also leaves the receiver in `s0`, raises the frame to 1,216 bytes, and
emits 88 unowned destructor bytes. The strict verifier rejects that object;
adding an alias for diagnostic inspection does not establish ownership or a match.

## Predicate and expression review

Four clamps in the boundary draft use `value > 80`
rather than `value >= 81`. Constant list indices 0, 1, 4 and 5 use the ordinary
`count && index >= 0 && index < count` shape; an inlined setter, an explicit
local index and equivalent strict constant comparisons reproduce the same code.
For case 10, a plain byte truth test and placing the threshold on the left of
`threshold <= sample` reproduce the original comparison form. Nesting the
string-pool getter inside the intern call preserves its call order and removes
extra padding in cases 11 and 12. These are verified source projections, not
assertions about original syntax.

The resulting complete candidate is 41,840 bytes with the original 1,200-byte
frame. Cases 9–12 have 1,550 aligned instruction pairs / 6,200 bytes. A private
paired def/use audit checks non-register encoding bits, operation inputs,
call targets and argument registers, load/store addresses and values, branch
destinations and delay slots. It covers 1,200 branch paths, using memoized
register correspondences at joins; seven corrupted controls are rejected.

This audit is conditional on corresponding initial receiver/memory, opaque
callee contracts, and explicit frame-slot correspondence: retail `+0x110`
maps to candidate `+0x120`, `+0x440` to `+0x454`, and `+0x43c` to `+0x450`.
It is a local correspondence diagnostic, not a replacement for byte identity
or a whole-function semantic proof. The candidate's full code, allocation and switch tables
fail verification. A broader pure-comparison projection fixes a few more
comparison forms but does not close the match; named and temporary six-reference
class projections enlarge the frame and emit unowned destructor/EH data.

## Retail unwind data

The retail flat image retains GAMERAM's unwind
index at `0x553b80`, pointing to table `0x544fd4` for `0x3fca10..0x406d98`.
The cleanup records identify the five missing reference homes and five physical
destructor targets, plus the copied argument at `+0x408` and nearby-list cleanup.
The [reference-helper inventory](combat-reference-helpers.md#retail-unwind-identities)
records their exact sites and associations.

The single-wrapper C++ probes are hypotheses. Their private
symbol aliases do not establish original cleanup identities. Retail's table
provides those identities directly. Candidate
exception data requires explicit verified ownership before it can be linked;
unowned sections are strictly rejected.

## Complete scopes and allocation differences

All 36 protected ranges and 34 cleanup actions are decoded; the
[format and generated inventory](../engine/exception-unwind.md) give the precise
return-PC and lifetime rules. A private C++ model reproduces the ordered pattern of 1,681 direct-call targets and 29
indirect-call sites, plus all 36 protected call spans and cleanup chains,
under an explicit semantic mapping for its diagnostic destructor classes.
This does not prove call arguments or dynamic indirect-call targets. In that model the
emitted bodies and metadata are unowned and do not pass verification.

Three redundant `GetInt` result aliases (`temp_ret_246`, `temp_ret_328`,
`temp_ret_794`) copy immediately into `sp12C`, `sp128`, `sp120`. Folding each
result into its actual scalar local removes the extra 16-byte frame allocation.
Independent compiler debug locations then put all 15 vector locals, seven matrix
locals, byte `sp110` and scalar homes `sp120/124/128/12c` at retail offsets.
The complete main body of this candidate is 41,840 bytes versus retail 41,864, receiver `s0`
versus retail `s4`, with incorrect reference-home placement and switch targets.
The call/scope audit does not substitute for the complete byte oracle.
Further copy-fold controls show why broad cleanup is unsafe for matching:
merging `temp_ret_340` into its alternate-branch destination spills the level cap
from `s8` and enlarges the frame by 16. Folding 56 adjacent same-type copies
reaches the retail code size but retains the wrong frame and mismatched bytes.
The three-alias candidate is the stronger baseline. A separate finite
case-14 instruction audit matches 25,000 input/callee-contract seeds and rejects
two deliberate arithmetic corruptions; this does not establish all-input or
whole-function equivalence. The unusual case-5 `%1000` is present in retail.

## Technique parameter table address units

The draft has an actual source defect at `0x405a04..0x405a34`.
The row helper writes `sp428`; retail shifts that row left by two once, adds the
result to both `0x4cf538` and `0x4cf558`, and loads signed words. The draft instead
adds the already scaled offset to `int *` bases, making the compiled stride 16.
The repair makes both loads add through `char *` before the word dereference. Placeholder
`extern int [4]` extents become unspecified; four entries are not established.
There is no added row bound or lookup-miss fallback.

The minimal reviewed full-body correction changes exactly one compiled word:
`sll a0,a0,4` becomes retail's `sll a0,a0,2`; all other compiled code and tables
stay unchanged. The guarded ordinary-output repair requires the exact row-scale
preimage, both declarations and both reads. An independent audit of the other
11 global arrays / 12 value uses finds no additional scaling, width or cursor
defect.

## Parent command enum

[`GameRamMessage_GetMetaEnum`](../../src/game/ndmw/beNDMWGameRam.inc)
is **84 matched code bytes**, including all 13 relocations.
Its metadata label is `Message`; the 22 names at `0x4cc410` include GETCOMMON,
GETPLAYER, CTRLITEM, FIGHTCALC and CTRLPLAYER. Values at `0x4cc470` are 0–21,
and the lazy cache is at `0x58c098`. The semantic function name identifies this
GAMERAM command table without asserting original method spelling.
