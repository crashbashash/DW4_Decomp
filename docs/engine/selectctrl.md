# SELECTCTRL manager and pad input

This page covers the concrete `beSelectCtrl` receiver used by the
[shop selectors](shop-selectors.md). Two entry bodies match exactly:
`beSelectCtrl_EnsurePadManager` at `0x0039cb70` (64 bytes) and
`beSelectCtrl_RegisterReceiver` at `0x0039cbc0` (36 bytes).
The metadata getter at `0x0039cbb0` (12 bytes) and inherited dispatch check at
`0x00378410` (8 bytes) are matched as well.
The complete update (2,864 bytes) and general handler (1,960 bytes)
have [readable behavioral source](../../recovered/engine/selectctrl.c), checked
against the original instructions. These two bodies match in
[Gap__Bec__beSelectCtrl__vfunc_31.cpp](../../src/unmatched/Gap__Bec__beSelectCtrl__vfunc_31.cpp) and
[Gap__Bec__beSelectCtrl__vfunc_33.cpp](../../src/unmatched/Gap__Bec__beSelectCtrl__vfunc_33.cpp).

## Entry methods and ownership

The RTTI-headed table at `0x0053b290` stores the receiver initializer at raw byte
124, info-class getter at128, update at132, pad-manager acquisition at136,
general handler at140 and inherited check at144. These are raw offsets from
the table header, not an index into a headerless function list.

The method at raw136 is **not cleanup**. It tests the reflected `_padManager`
word32 and, only when absent, calls `0x00236f80` with `_insight` word12 and the
published metadata at `0x00588518`. It stores the returned pointer directly.
This body has no retain/release traffic; a failed lookup leaves zero for another
attempt.

The initializer calls `beMessenger_RegisterReceiverFromInfo` (`0x0038d820`)
with `_messenger` word20, the supplied info record and literal `SELECTCTRL`
(`0x0050f7f0`). The C++ compilation matches its36-byte frame/call/return;
C mode instead emits a16-byte tail call. The pad-manager method uses the
existing explicit retail NOP convention after pointer publication.
These matching sources preserve observed machine behavior; their original
source spelling is unknown.

Sources: [manager methods](../../src/game/beSelectCtrl.cpp) and
[receiver registration](../../src/game/beSelectCtrl_RegisterReceiver.cpp).
Reflection supplies the field names and offsets; there is no synthetic receiver
layout.

## Distinct state objects

The original-instruction oracle verifies these distinct records. Their offsets
must not be merged into a single state layout: all three have meaningful words
24 and 28.

| Record | Relevant fields |
| --- | --- |
| Manager's per-info context, the second argument | player8, info12, active byte20, primary state24, substate28, counters32/36, named work registry40 |
| `beSelectCtrlInfoRamData`, found via the named registry | orientation byte16, maximum20, selected result24, work reference28 |
| `beSelectCtrlInfoWork`, held by that data record | offset vector8/12/16, maximum20, cancellation byte24, retained sequence string28, decision-byte list32 |

The manager lazily allocates its registry if context40 is absent, then uses
`0x003022c0` and literal `ONE` (`0x0050f800`) to find its data. Update obtains pad state
through `0x0039b810(manager->_padManager, context.player)` and reads words36,
68 and72. Recovered shop-owner selection state is a separate record again.

## Original command contract

The enum getter at `0x003459a0` uses name/value tables `0x004c3b40/0x004c3b60`.
The handler's jump table is `0x0050f8e0`.

| Value | Command | Observed effect |
| --- | --- | --- |
| 0 | GENERATE | Activate/reset the context and replace its work. Read optional count/start/vector/NOCANCEL and matching-count decision flags. |
| 1 | ISEND | Append true when the context active byte is zero. |
| 2 | GETSELECT | Append data.selected result, including the -1 cancellation result. |
| 3 | ISSELECTNOW | Append true when active and primary state is neither2 nor3. |
| 4 | FO2TOP | Only state1/substate0 accepts: reset selected result0, optionally replace count/decision flags, enter state10 and append true. Otherwise append false. |
| 5 | ISFO2TOP | Append false for that same state1/substate0 eligibility condition, true otherwise. |
| 6 | REMOVE | Set result-1, enter state2 and reset counters; return0 despite performing the mutation. |

Other commands return0. The inherited raw144 check returns0, so messenger dispatch
uses the raw140 general handler. This differs from SUBWND's shortcut receiver
path. Existing dependency tests prove the table, enum, registration and FO2TOP
eligibility prefix directly from retail words.

## Original input/update contract

Primary state0 generates the model at its saved offset, starts the opening
sequence, then waits before entering state1. The opening result specifically
compares its **low byte against1**; later sequence waits compare the full return
against zero. State1/substate0 handles directional movement and choice actions.
Orientation selects which pair of direction masks is used. Movement stops at
both ends rather than wrapping, and the negative direction has precedence when
both direction conditions hold. The selected result is published before the
movement sequence is sent.

The pad word72's `0x2000` branch precedes `0x4000`. The first requests
cancellation: a nonzero cancellation byte publishes -1 and enters state2; zero
runs the rejection path. The second accepts the current choice only if no
decision list exists or its indexed byte is nonzero. A rejected action runs a
message sequence and substate2's16-count wait. Accepted selection uses its saved
sequence and enters state2 after that sequence completes. State2 starts a
close/cancel sequence and waits, then enters state3. The default primary-state
path, including3, clears active and releases/clears the data's work reference.
State10 runs the FO2TOP sequence and returns to state1.

The update's complete span is2,864 bytes (`0x0039cbf0..0x0039d720`), including
48 bytes of padding omitted from Ghidra's occupied-byte count. The general
handler is **1,960 bytes** (`0x0039d720..0x0039dec8`), not its1,932 occupied-byte
count. The other **28 bytes** are five saved-register restores,
`jr ra` and its delay slot, as covered by the extent regression. The contiguous span includes those seven
words. Generated extents retain every occupied range.

## Behavioral verification and matching residue

Run from the repository root:

```sh
python3 testing/test_selectctrl_retail.py
make check
make link
make typed-check
```

The oracle runs **4,089 manager cases**, comparing every non-stack RAM byte and ordered
engine-call arguments/state snapshots. It executes all **1,187 non-padding
instruction addresses** in the two bodies' 1,206-word spans; the 19 omitted
words are independently checked as zero padding. No original output is copied
into the recovered expectation. Input state and private temporary storage are
mapped before the two implementations execute independently.

Cases cover all commands, invalid full-width command values, inactive contexts,
both registry allocators, live integer counts/start-point handling, vector bit
patterns (including signed zero and NaN payloads), cancellation defaults, typed
bool-list creation/growth, signed size/capacity extremes, old and temporary
reference deletion, string replacement, pool creation/failure and callback
mutation. The decision loop reloads its temporary list pointer after each bool
getter and its backing data after resize. Cancellation writes zero only for an
exact NOCANCEL string; otherwise the new work's supplied cancellation byte is
preserved. The FO2TOP eligibility test does not additionally require active=1.
Work-owned animation waits reload their saved sequence **after** selecting the
model receiver. A deliberate callback replacement in the regression checks it:
the source uses the later string, and a capture taken before the selection is stale.

Persistent sequences run GENERATE/open, directional selection, confirmation,
close and final work release. Separate sequences cover cancellation (including
simultaneous `0x2000|0x4000` precedence), REMOVE, FO2TOP and rejected-choice
recovery through the 16-count wait. The named model sequences are
`SQ_OPEN`, `SQ_LINESL%02d`, `SQ_LINEUP%02d`, `SQ_LINEDW%02d`,
`SQ_LINEON%02d`, `SQ_CLOSE`, `SQ_CANCEL` and `SQ_FO2TOP`. Rejection sends
`SOUND CURSOR_NG PLAY`. Model/animation execution itself remains controlled.

Factories/allocators, registry lookup, pad-state acquisition, messenger services,
formatting, interning and destruction are bounded leaves. This proves the two
manager bodies at those boundaries. It does not establish real pad sampling,
rendering, physical animation timing or the original
scripts' complete outcomes. The 576-case shop-selector oracle
controls its SELECTCTRL receiver responses. The separate
[joint common-owner oracle](selector-manager-composition.md) executes the
actual handler/update/pad lookup beneath the owner, with immediate SD delivery
and empty close queues. Shop-specific initialization and XDATA transactions
are not part of that call tree.

The update (2,864 bytes) and the general handler (1,960 bytes) match.

Open: extending the joint common-owner
oracle to actual ShopSelect initialization and XDATA transactions, and closing the
pad/model service dependencies. The broader chip/list/recalculation, other services,
saving and hub script closure belong to the full lobby goal, which is unfinished.

## Original pad-record selection

The SELECTCTRL update's lookup at `0x0039b810` is named
`bePadManager_GetPadForPlayer` from its body and its manager/player arguments.
[Readable source](../../recovered/engine/pad-manager-selection.c) recovers all
88 bytes under the same guest-memory API, with no external callees. The adjacent
12-byte metadata getter is matched. The
lookup itself matches in [bePadManager_GetPadForPlayer.c](../../src/unmatched/bePadManager_GetPadForPlayer.c).

Reflection handle `0x00588518` identifies `bePadManager`: `_padList` is word20,
`_is1pAllDevice` byte28 and `_isPadDisable` byte29. The lookup uses byte29 and
selects entry4 when it is nonzero. Otherwise it uses the supplied player when
the signed incoming register is less than4, and entry4 for all other values.
It reads the selected word through `_padList`'s backing pointer at16 and returns
its sign-extended pointer. It does not read the list count or byte28, clamp
negative players or guard a null selected record. The array index shift wraps
as an EE 32-bit operation; the behavioral adapter preserves that detail.

`python3 testing/test_selectctrl_retail.py` runs **4,506 cases** in total: the
4,089 manager cases, **201 direct pad-selection cases** and **216 real
manager/pad-lookup compositions**. The full three-body spans contain1,228 words;
all1,208 non-padding instructions run, with20 zero padding words checked.
Direct cases cover disabled-byte values0/1/255, the unused all-device byte,
ignored list counts, player boundaries and negative/noncanonical register
values, plus null and high-bit result pointers. Composed cases exercise all
four players and the fallback record through orientation/direction/confirm/
cancel paths. They compare complete RAM and ordered calls, without replacing
the getter's result with a fixture return. Pad record contents are
controlled input; this does not recover device sampling.

A read-only matching pass scored all347 missing direct hub functions:
zero automatic matches,265 mismatches,70 compile failures,8 SDK
exclusions and4 decompiler failures. Eleven mismatch candidates were within
three instruction words; this is a work queue, not decompilation credit.
The metadata getter probe's two address words
differ; an indexed union form uses the correct stack base but adds an instruction.
That probe form is not in `src/`.

Matching candidates should start from the measured residues, with the corrected
byte/ref/float field types. Open: full manager/widget/XDATA composition, the
physical pad/model services, and the remaining hub controllers and scripts.

The shared268-byte `igObject_Destroy` body used by the
retained work/list release path matches, as do192 bytes of base-window cleanup used by
metadata temporaries. [Object destruction](object-creation.md#destruction) records
the explicit single register-copy instruction and exact-byte validation. Those
bodies are not matching residues; the SELECTCTRL suite controls its
object-destruction calls, so this adds no combined lifetime acceptance by itself.
