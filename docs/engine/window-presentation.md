# Window presentation, close queues and shared titles

This page covers the complete seven-body presentation run
**3f59b0..3f6348 /2,420 code bytes**, plus the complete shared title update
**424160..424230 /208 bytes**. The readable
[guest-reference implementation](../../recovered/engine/window-presentation.c)
passes **223 original-instruction RAM/return/ordered-call cases**, including real
root/tree/title/presentation closure. It executes **651/657 instruction addresses**:
four words are excluded zero padding; two belong to a contradictory branch under
the checked callee-save ABI. Neither is counted as exercised.

All eight bodies /2,628 bytes have exact source. ClearTextElement136 was already matched;
its five receiver accesses now use the recovered Window layout. New
[model forwards](../../src/game/window-model-forwarding.cpp) add **116 matched
bytes**: default-origin64 and model-sequence52. The other five bodies /2,376 bytes
match as `src/unmatched/beNDMWWindow_ClearQueuedText.cpp`,
`src/unmatched/beNDMWWindow_PresentModel.cpp`,
`src/unmatched/beNDMWWindow_PlayQueuedModelClose.cpp`,
`src/unmatched/beNDMWWindow_PollCloseComplete.cpp` and
`src/unmatched/Gap__Bec__beNDMWWindowTitle__vfunc_21.cpp`.
This does not establish shop transactions or native UI operation.

The run extends backward with the 144-byte
[message-script dispatcher](xdata-controller.md#script-call-number-and-pack-ownership)
at3f5920. The current presentation/title boundary is nine bodies /2,772 bytes;
the added body matches as `src/unmatched/beNDMWWindow_RunMessageScript.cpp`.

## Text close requests

ClearTextElement3f59b0 selects TEXTCTL with no named receiver and id-1, appends the
text type, text name and literal CLR, then dispatches SWITCH. It reloads the current
window messenger12 before each message call. ClearQueuedText3f5a40 captures the
signed count of `_textCloseTypeList`60 and fetches its type and the parallel
`_textCloseNameList`64 name for each index through the original retained-string
accessor. Each temporary is captured and released before sending the request.
Those captured tokens remain the request arguments even if a release callback
changes their private cells.

After issuing all requests, it reloads each current list pointer and clears the
lists. Clearing captures that list's signed count, captures each element address
before querying the string pool, obtains the original interned-null result,
releases the current old token at that address and writes the captured replacement
there. A release callback can change list backing storage; the captured element
address still receives the replacement. The count on the captured list becomes0.
The interned-null result is not assumed to be a null pointer.

String references use a full32-bit counter at token-4 and owner at token-8, distinct
from object low23-bit references. When a temporary or old element reaches zero,
30c940 receives the owner and token-8. Pool creation16/2eb010 and2eadf0 occurs only
when global586f20 is null; its returned value is published before2eaf60. Allocation
failure does not gain a new early return or alternative intern policy.

## Model presentation and queued close data

PresentModel3f5c90 accepts window, model name, ram number, requested sequence,
optional close sequence and a pointer to three float words. It queries MODELCTRL
ISRUN. A zero full return starts a new model: select name/id, append the sequence,
copy the vector **after** the sequence callback, append it and dispatch GENERATE.
A nonzero return sends the requested sequence to the existing model instead.

When the close-sequence argument is nonzero, it records parallel entries in:

| Window offset | Reflected field | Stored value |
| --- | --- | --- |
| 68 | `_modelCloseInfoNameList` | Interned model-name token |
| 72 | `_modelCloseRamNoList` | Low32-bit ram number |
| 76 | `_modelCloseSeqNameList` | Interned close-sequence token |

The model name can be null independently of the nonzero close sequence. Scoped
cells140/136 hold the two string references. The list append receives their actual
addresses; subsequent release reloads the current cell. The numeric append captures
list/count, resizes through2d6790 if needed, then reloads backing storage before
writing. Owner list fields remain live around callbacks.

PresentModelAtOrigin3f5f00 supplies the three original zero float constants at
4e1058/105c/1060 in its32-byte private frame and forwards all five incoming values.
SendModelSequence3f5f40 forwards MODELCTRL/name/id/sequence through SendNamed.
Both exact bodies retain full-width argument registers and the original framed
calls. A brace-initialized array candidate emitted extra initialization data/code;
explicit component assignments reproduce all64 retail bytes without substitutions.

PlayQueuedModelClose3f5f80 captures the signed model-name count. It gets/releases
the current name token, reloads the ram-number list, gets/releases the sequence
and sends the sequence request. It does not clear the records at this point.

## Close completion

PollCloseComplete3f6090 visits each tracked model name/id. It also fetches and
releases the corresponding close-sequence token, although that token is not used
in the ISRUN message. Those lifetime operations are retained. A model blocks
completion only when the signed full result count from38f0f0 is positive **and**
GetBool0's full return register is nonzero. Empty or negative result counts skip
the boolean read.

Once no tracked model blocks, the child-list count52 must be exactly zero.
Otherwise the routine returns0 and retains all queues. When children are empty,
it clears the current name string list, zeroes the current ram-number list count,
clears the current sequence string list and returns1. Clear/reset order, captured
list pointers and callback-time string ownership are preserved.

## Shared title update and composition

The title update is shared by the five root title widgets and other title classes.
In primary state0 it calls raw virtual byte96 for type-specific initialization,
then increments the current state and clears40/36/32. State1 does nothing. State2
executes PlayQueuedModelClose, ClearQueuedText and the recovered child-close helper,
then advances/reset counters. State3 clears active byte24 after PollCloseComplete
returns nonzero. Other states do nothing. The tree caller owns the active-byte
check; no second guard is inserted into this title body.

Tests compose the real generic shop root, common window tree, shared title update
and all presentation helpers on both sides. Factories create controlled widgets;
title-specific byte96 initialization and concrete text/model receiver services
remain leaves. This proves the lifecycle interaction, not real rendering, animation,
input or transaction parity.

## Span and coverage evidence

The title's old200-byte occupied-size split lost the final return/delay words.
Its actual208-byte span now includes both. Reviewing the selected service
controllers also removes trailing alignment padding formerly absorbed by the
jump-dispatcher growth heuristic:

| Body | Old classified size | Reviewed span |
| --- | ---: | ---: |
| Shared title424160 | 200 | 208 |
| Ctrl10 4270a0 | 5488 | 5484 |
| Ctrl30 428790 | 3616 | 3608 |
| Ctrl40 429630 | 3248 | 3240 |
| Ctrl50 42a2e0 | 5408 | 5400 |
| ShopDevice43cc20 | 1168 | 1168 |
| ShopJunk42bc70 | 2848 | 2844 |

These seven spans total21,952 bytes, a net24 fewer classified code bytes, with
retail contents unchanged. Generated Ghidra ranges own the symbols/layout/assembly;
independent tests check every final return against the ELF. The remaining six
service updates total21,744 bytes before their dependencies.

The two unexecuted nonzero words at3f5e54/5e58 are an inner null-close-sequence
branch. Entry moves the argument to callee-saved s2; the outer zero test skips the
whole tracking block, and the inner nonzero test therefore always skips those
words. A register-write scan verifies that s2 is written only at entry and final
restore. The tests do not corrupt callee-saved registers to manufacture coverage.

```sh
python3 testing/test_window_presentation_retail.py
python3 testing/test_lua_engine_dependencies.py
python3 tools/test_function_extents.py
make check
make link
make typed-check
```

Cases cover null strings, pool creation/failure, reference-count boundaries,
non-null interned-empty results, callback-changed temporary/messenger/backing
storage, resize relocation, negative counts, return-width distinctions and
persistent all-mode root/title close sequences. Private input frames are mapped
before execution; no retail output is copied into expected memory.

The 208-byte title matches as
`src/unmatched/Gap__Bec__beNDMWWindowTitle__vfunc_21.cpp`. Recover
the selected XDATA/BANK/CNOS/DISK/ShopDevice/JUNK controllers and their actual
record transactions against the [full hub contract](../systems/hub-recovery.md).
