# SUBWND service-menu lifecycle

The complete lifecycle prefix **3d58f0..3d60d8**, the four emitted pointer-wrapper
cleanup helpers at 3d9bd0..3d9dd0 and the final metadata getter 3d9dd0 are recovered.
The nine bodies span **2,532 bytes**, serve all eleven service modes and four
owning-player arguments, and all match.

The whole manager region has eleven bodies /17,616 code bytes, including its9,820-byte
[command receiver](subwindow-command.md) and the5,264-byte
[preparation body](subwindow-preparation.md).
Menu-specific controllers, transactions and Lua callbacks also remain open.

## Correct function span

Ghidra's update body contains1,820 occupied addresses but spans1,832 bytes:
3d59b0..3d60d8. Its address set excludes three four-byte alignment NOPs at3d59f4,
3d5a5c and3d600c. Using the occupied-byte sum as a contiguous size truncated the
final12 bytes: saved-s0 restore, return and stack-release delay slot.

`scripts/dump_function_extents.py` now exports the actual address ranges as well
as size/end metadata. The regenerated
[reviewed spans](../../data/function-extents.json) supply the correct split;
`tools/split.py --symbols` and the normal layout/link generators own the output.
The correction adds12 classified code bytes and removes12 unclassified data
bytes; it does not add matching credit or change any retail image bytes.

The nine spans hold **633 instruction addresses**, three of them those reviewed
padding NOPs. Seven span regressions retain the earlier title/material/messenger/allocator
evidence and independently protect this full return sequence.

## Owner and initialization

Reflection identifies `beNDMWStatus` as a `beBaseInfoManager` derivative:

| Owner offset | Recovered field |
| --- | --- |
| 12 | `_insight` inherited from `igInfoManager` |
| 20 | `_messenger` inherited from `beBaseInfoManager` |
| 24 | `_infoList` inherited from `beBaseInfoManager` |
| 32 | `_windowPro`, retained root |
| 36 | `_whoGenerate`, owning player |
| 40 | `_subWndNo`, service mode |

RAM has `_isRun` byte20, state/counters24/28/32/36 and `_work`44. Initialize5960
registers the literal **SUBWND** through38d820 and clears `_isRun` only when the
info-list's count at+8 is exactly one. It is a list-count condition, not an info
kind enum. Other counts leave RAM untouched. Cleanup58f0 releases the root using
the low23-bit reference rule, then clears32 even if the destruction callback
changed it. Metadata getters return the current words at58ac30/58b028.

The existing RTTI/vtable-slot names are retained. Body-purpose labels here are
descriptions, not claims about original method spellings. The actual vtable at
53e7c0 binds init/update/cleanup/command at raw124/132/136/144 respectively.

## Opening and root ownership

Inactive RAM returns without changes. In state0, the manager calls preparation
3d8740, then sends **STAGECTL / ENABLE / PADINPUT**. It selects the mode's root:

| Mode | Named service | Constructor |
| --- | --- | --- |
| 0 | STATUS | 3bb1d0 |
| 2 | LABO | 3b7750 |
| 10 | CARD | 3b7eb0 |
| 1,3–9 | XDATA, BANK, CNOS, DISK, WPU, APU, CHIP, JUNK | 3b8d90 |

Mode0 switches WN01 and WN00 through **LAYERCTL / DISPOFF / SWITCH** before
construction. Allocation queries the object's allocator first, then uses the
selector at587110 when byte554c14 is zero. The complete eleven-entry jump table
at5168e0 and each constructor's actual JAL independently verify these groups.

The temporary root reference is a private frame word at sp+76. An incoming temporary reference is
released before constructor replacement; callbacks can change that storage.
Initialization3f63c0 receives root,0,`_insight`,`_whoGenerate`,0. The mode stored
on root+44 is re-read afterward. The manager retains the captured new root,
releases the old root, publishes32, performs nonzero-mode sound commands, then
releases the current temporary and advances RAM state. Retain precedes release;
publication follows the old destruction callback. Constructor selection and
later published mode are not assumed to remain equal across callbacks.

Nonzero modes send SOUND BGMSTOP/ENVSTOP, then PLAY RM_NSHOP. State advancement
increments the current word24 and resets36,32,28 in that order. The new root is
updated **in the same manager call**, not on an extra delayed tick. State1 uses
the same update/completion path. Other states go directly to finalization.
The manager re-reads its root after tree update and tests byte root+24.
There are no root-null or enum guards; the original requires valid
factory results.

## Completion and service-specific exits

On completion, the manager releases/clears its root, sends OFFREEZE to SOUND,
GENERATER and MODELCTRL, releases the message-time hold, and clears `_isRun`.
It queries GETPLAYER and ISUSE separately for slots0..3, sending ADDHP(player,0)
and ADDMP(player,0) for each nonzero **byte** result. These are the recovered
commands; their record math is a separate dependency. Participant flags are
queried as the loop runs, not captured as one earlier mask.

CARD then asks STAGECTL ISRESETSTART. If the returned low byte is zero, it sends
PLAYERPOINT SETGENERATEPOS(4) and STAGECTL NEXTSTAGE("stagML12"). It does not run
the ordinary layer/shop-exit branch. Other modes switch WN01/WN00 to DISPON;
nonzero modes locate the Lua receiver and execute **shopexit.lua** through
236f80/389ff0 with the original final argument0. STATUS mode0 omits that callback.
The Lua execution/scene-transition services remain explicit boundaries here.

A direct literal CARD caller is
[`entry0808/chunk0004`](../../lua/00-title-menus/05-character-select-1_e808/004-layer-setup-2.lua), after the
entry-camera handoff in the character-select pack. This establishes a front-end
caller and central-area return. The enum name alone does not identify the hub's
Booster Pack/album or Save Keeper implementations; those remain separate scope
items until their own controller/caller evidence is recovered.

The four128-byte reference helpers release their pointed object, conditionally
free their wrapper through100610 when signed-low16 flags are positive, and
return the incoming wrapper. Their exact template payload types are not inferred
from their identical instructions. Null wrappers and high reference/flag bits
retain their original distinctions.

## Checks and remaining work

```sh
python3 tools/test_function_extents.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

Actual shop stock, prices, purchases, appraisal, bank/lab/X Data/card/save
outcomes, UI behaviour and multiplayer menu ownership lie outside this lifecycle.

Continue exact matching and the concrete
service-controller/result dependencies for the [full hub goal](../systems/hub-recovery.md).
The ten alias matching residuals remain open; private compiler/permuter searches
did not produce a newly verified exact body.
