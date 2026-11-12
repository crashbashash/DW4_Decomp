# Window tree and generic shop-root runtime

**Six bodies /2,980 code bytes** are recovered: the contiguous child-close,
context-binding and recursive-update helpers at3f6350..3f6618, plus the complete
ShopCtrl00 update4267b0..426f94 and its two adjacent128-byte scoped-reference
cleanups426fa0/427020. They hold **741 executable
instruction addresses**; four further zero words are padding.

Ghidra counts2,004 occupied bytes for the shop-root update, which spans **2,020 bytes**, with four internal
NOP holes. The occupied-byte size would end after restoring ra at426f80, losing
saved-s1/s0 restores, return and stack-release delay slot. Generated ranges and
split/layout include the full sequence. The three window helpers are in `src/game/beNDMWWindow.cpp`; the other three bodies are in
`src/unmatched/` (`Gap__Bec__beNDMWShopCtrl00__vfunc_21.cpp`, `FUN_00426fa0.cpp` and `FUN_00427020.cpp`).

## Window ownership and context

Reflection names the common fields used by all three helpers:

| Offset | Field |
| --- | --- |
| 8 | `_insight` |
| 12 | `_messenger` |
| 16 | `_padManager` |
| 20 | `_playerNo` |
| 24 | `_isRun` byte |
| 28/32/36/40 | `_st0` / `_st1` / `_st2` / `_st3` |
| 44 | `_entCode` |
| 52 | `_subWindow`, retained child list |
| 56 | `_mother`, retained parent |
| 80 | `_nowProcKazu`, WindowCtrl's child-count snapshot |

BindContext3f63c0 retains the incoming parent before releasing the old parent with
the low23-bit reference rule, then publishes the parent and insight. It queries
the insight collection through236f80 using the current published beMessenger
handle588f38 and bePadManager handle588518, storing the two results. Player and
entry code are published last. Original arguments remain captured across callbacks;
there is no fallback manager, extra initialization or null-success policy.

RequestChildrenClose3f6350 captures the signed list count, reloads list/data for
each child, and changes only children whose signed state28 is below2. It writes
state2 and clears40,36,32 in that order. Existing close states are preserved.
The body is 104 bytes.

## Recursive update and removal

UpdateTree3f6490 calls a running window's virtual method at raw vtable byte92,
then reloads its active byte and state. If inactive or in state2 or later, it
requests closure of the current children using the same field operations as
RequestChildrenClose. It then captures the child count for its recursive pass.

For each index it reloads the current list/data and recursively updates that
child. **After recursion it reloads the owner's list and the child at the same
index.** The child removed need not be the pointer originally passed to recursion
if a callback replaced the list. Inactive children are released before removal
through2d6cf0; the list pointer captured after recursion survives the destruction
callback. After removal it reloads that list's current count/data and explicitly
zeroes the vacated tail. Both the local index and local loop bound decrement so
shifted children are processed. New children appended during callbacks do not
increase the captured bound. There are no null-child or consistency guards.

## Root state0: common widgets

The concrete class vtable53feb0 raw92 selects update4267b0. In state0 it creates
these five widgets in order, using the original per-object/default allocator
choice (selector587110 when byte554c14 is zero):

| Factory | Metadata class | Bound entry code |
| --- | --- | --- |
| 3b3370 | beNDMWShopTitle00 | 0 |
| 3b3ac0 | beNDMWStatusTitle01 | 0 |
| 3b3900 | beNDMWStatusTitle02 | 0 |
| 3b36f0 | beNDMWStatusTitle03 | 0 |
| 3b31b0 | beNDMWShopTitle01 | Current root entry code |

Each result is stored in a distinct private frame reference cell76/72/68/64/60,
bound to the root parent/context/player through BindContext, appended to the
current child list, then released through the current temporary cell. Owner
fields and temporary cells are reloaded around service calls. State increments
and counters40/36/32 clear after all five widgets. Their concrete rendering,
text/input and controller bodies remain separate dependencies.

UpdateTree proceeds into the newly appended children in the same tick. It does
not defer their updates until another frame.

## Root state1: opening gate and service selection

With substate32=0, the root selects MODELCTRL / `i_messwn`, appends `SQ_STOPEN`,
dispatches ISSEQNAME, and waits **only when the returned low byte is exactly1**.
A byte2 or255 follows the construction path. With substate1 it skips construction
and performs the child-count comparison. Other substates return immediately.

The original ten-entry jump table51b370 and factory metadata handles establish:

| Entry code | Service | Factory / metadata class |
| --- | --- | --- |
| 1 | XDATA | 3b8b60 / beNDMWShopCtrl10 |
| 3 | BANK | 3b8630 / beNDMWShopCtrl30 |
| 4 | CNOS | 3b8400 / beNDMWShopCtrl40 |
| 5 | DISK | 3b81d0 / beNDMWShopCtrl50 |
| 6,7,8 | WPU,APU,CHIP | 3b6650 / beNDMWShopDevice |
| 9 | JUNK | 3b6310 / beNDMWShopJunk |
| Other | Raw fallback | 3b8b60 / beNDMWShopCtrl10 |

The selected concrete vtables expose seven distinct next update bodies: shared
title424160, Ctrl10 at4270a0, Ctrl30 at428790, Ctrl40 at429630, Ctrl50 at42a2e0,
ShopDevice43cc20 and ShopJunk42bc70. Their currently classified extents total
21,952 bytes after reviewed spans, before closing their own dependencies and reviewing full spans.
These are evidenced callback roots in the shared inventory, not invented direct
edges from the tree updater.

The outer SUBWND lifecycle uses dedicated roots for STATUS/LABO/CARD. This raw
fallback does not establish that those services should use the generic shop root.

The service reference occupies private frame56. The routine sets that cell to
zero, captures the selected factory, obtains the allocator, releases the **current**
cell, constructs/binds/appends the service and releases the current cell again.
The retail instructions retain pre-construction release branches that Ghidra's
decompiler removed as unreachable after assuming the local stays zero. Whether
ordinary allocation can change the caller's private frame in a live game is not
established.

The root captures the actual current child count in80, increments the current
substate and clears40/36. It then compares current count with the captured count.
**Any difference**, including growth, advances state and clears all three counters.
Child completion is observed through list changes rather than a service-result
boolean here. Changes made by the tree's child pass become visible on a later
root update.

## Root states2/3 and adjacent cleanup

State2 sends MODELCTRL / `i_bgclear` / OFFREEZE, then invokes3f5f80,3f5a40 and
RequestChildrenClose in that order. It increments the current state and clears
counters. See the [presentation/close helpers](window-presentation.md). State3 calls3f6090 and clears `_isRun` when its full return
register is nonzero. Other primary states do nothing.

The two adjacent scoped-reference cleanup bodies are byte-identical. They
release the pointed object using the low23-bit reference count, conditionally
free their wrapper through100610 when the signed low16-bit flags are positive,
and return the original wrapper. Their original template payload types and unwind
ownership are not inferred solely from adjacency or identical code.

## Checks and remaining work

```sh
python3 testing/test_lua_engine_dependencies.py
python3 tools/test_function_extents.py
make check
make link
make typed-check
```

Recover the concrete selected service controllers, actual prices/transactions and
[remaining hub scope](../systems/hub-recovery.md).
