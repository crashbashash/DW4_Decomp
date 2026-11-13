# Stage loading cards and node animation

The USA game chooses a stage-specific loading scene, whose texture already
contains the preview and localized stage name.

## Stage and language lookup

`beFileListInfoManager::vfunc_27` (`0x0037fa30`, 5,776 bytes) initializes its
stage load in state 0. It copies the destination name into GameInfo `+0x38`,
then builds the loading filename in the mutable string at GameInfo `+0x48`:

1. Copy the bare destination (`stagML11`).
2. Erase its first two characters (`igStringObj_Erase`, index 0, count 2).
3. Insert `ld` at index 0 (`FUN_0030b460`).
4. Append `.igb` and prepend `loadingUSA/`.
5. Request `loadingUSA/ldagML11.igb` through `igResource_LoadDirectory`; retain the
   request in the manager's pending list `+0x2c`, and enter state 1.

The constants are at `0x0050e570` (`ld`), `0x0050e578` (`.igb`) and
`0x0050e580` (`loadingUSA/`). State 1 waits for request completion before
registering its objects. State 4 checks both the remaining file queue and the
loading node's play-limit predicate. Only when both complete does it lock the
loading animation through `beLoadingNode_Lock`, and advance through states 20/21/5.
State 6 orders layers, then sends `LAYERCTL`, `LOADING`, `SET`, `SWITCH` before
attaching layer nodes. These calls and constants were cross-checked against
retail `mipsel-linux-gnu-objdump` output, not inferred solely from decompiler C.

The layer dispatcher (`beLayerCtl::vfunc_34`, `0x00389170`) resolves the named
layer in its `igSwitch`; `SET` enables its mask bit. `LOADING` is the authored
scene root, not a font-generated replacement.

NDMW.IGB's inherited `igFileName._pathList` (serialized ordinal 3) disambiguates
identical loading filenames. For `ldagml11.igb`, directory `loadingusa` selects
AREA.AFS **1321**; `loadingeng` selects **831**. A basename-first lookup
therefore selects a different regional card. USA ML02 is entry
1320.

## Node clock and traversal

The first nine bodies of [`bePadData.cpp`](../../src/game/bePadData.cpp)
(`0x0039a930`..`0x0039ae44`) run the animation clock of `beNodeAnim` and its
derived `beLoadingNode`; the rest of the file is the [pad record](selectctrl.md#pad-record-update).

| Address | Function | Contract |
|---|---|---|
| `0x0039a930` | `beNodeAnim_TraversalFunction` | Traversal callback: receives traversal then node, calls `beNodeAnim_Traverse` with node then traversal |
| `0x0039a960` | `beNodeAnim_SetTime` | Rebase `_timeBias` so the clock reads a given time now |
| `0x0039a9e0` | `beNodeAnim_UpdateTime` | Return the stop time, or advance and loop the node clock |
| `0x0039ab20` | `beNodeAnim_Traverse` | First-time rebase, push an `igTimeAttr` with the node time, traverse the children, pop it |
| `0x0039ad80` | `beNodeAnim_RegisterTraversalFunction` | Register the callback for `beNodeAnim` |
| `0x0039adc0` | `beLoadingNode_TraversalFunction` | Same operation for `beLoadingNode` |
| `0x0039adf0` | `beLoadingNode_Lock` | Copy `_lockTime` to `_stopTime` |
| `0x0039ae00` | `beLoadingNode_IsPastPlayLimit` | Strict predicate `_playLimitTime < _playTime` |
| `0x0039ae10` | `beLoadingNode_RegisterTraversalFunction` | Register the callback for `beLoadingNode` |

The registration passes the class's lazy metadata accessor result
(`beNodeAnim_ResolveMetaObject`, `beLoadingNode_ResolveMetaObject`) to
`igTraversal_RegisterFunction`, which gives the class a traversal index on first
use and stores the callback at that index of the function list in `DAT_00562640`.

The reflected `beNodeAnim` fields are start/loop1/loop2/stop at
`+0x20/+0x28/+0x30/+0x38`, first-time flag `+0x40`, time scale `+0x50`,
bias `+0x58`, previous clock `+0x60`, and accumulated play time `+0x68`.
`beLoadingNode` adds lock `+0x70` and play limit `+0x78`.

On first traversal, the clock rebases to the authored start time. While
unlocked, accumulated play time gains the complete clock delta, but animation
progress compensates for deltas greater than **33,333,333 ns**. Scaled clock
math keeps unsigned low-32-bit `clock >> 18`, performs EE float multiplication
and float-to-int64 conversion, then shifts back by 18. If local time reaches
loop2, the code subtracts loop2 while local time is **strictly greater**, adds
loop1, and rebases. This unusual equality/subtraction behavior is retained.
A nonzero stop time returns immediately without advancing play time.

`beNodeAnim_Traverse` takes an `igTimeAttr` from the traversal's time pool
(`igObjectPool_Grow` with `igTimeAttr_CreateInstance` when it is empty), sets the
traversal time, pushes the attribute on its attribute stack
(`igAttrStackManager_MarkStackChanged` after the push and after the pop), runs
`igTraversal_TraverseChildren`, runs the stack's pop procedure on the top entry and
pops. It returns 2 when the children stopped the traversal, otherwise 0.

The USA ML11 asset serializes start 16,666,666 ns, loop1 1,666,666,666 ns,
loop2 4,666,666,666 ns, lock 4,733,333,333 ns, and play limit
1,666,666,666 ns.

## Geometry, title and preview

AREA 1321 contains one 256×256 inline `ldimg01.png` texture, twelve meshes and
seventeen instances under `LOADING`. The picture and “Home Server” /
“Main Lobby: Terminal Area” text are regions of this atlas, placed by
`M_imageShape` and `M_textsetShape`. They require no new font string or
screenshot capture at load time.

`G_load` and `G_load1` use ordinary transform sequences. Fifteen sources use
`igCompressedAnimationSequenceQS`, including the cover panels, mirrored
triangular masks, edge highlights and texture-coordinate transforms. Serialized
ordinals 2/3/4 identify unsigned-short translation/quaternion/time lists;
5/6 and 7/8 hold each component's scalar base and quantization step. Slot 9
is duration, slot 13 the interpolation method. Components decode as
`base + ushort * step`. Time keys are **sign-magnitude**, with bit 15
indicating negative time and the low 15 bits multiplied by **2^23 ns**. Retail
getter `0x001bf790..0x001bf7cc` reads the ushort, masks the sign and shifts by 23;
the encoder at `0x001bf400..0x001bf440` takes the absolute time, shifts right by
23 and sets bit 15 for negative input. A duration/65535 interpretation
is incorrect: it collapses the ML11 trace's last key from 4,831,838,208 ns to
42,481,118 ns, leaving it static after the first few frames. Node target 9 means
UV translation rather than geometry translation. Depth is authored in mesh
positions, so sorting solely on transform Z loses this composition.

`M_heckeflineShape` inherits an additive `igBlendFunctionAttr` with source 4,
destination 1; its target-9 parent animates the atlas offset through the authored
hexagon outlines. The hexagon fill, scrolling bands and edge lights also inherit
this additive blend, while preview/name and black cover use 4/5 ordinary alpha.
Visible trace phases were inspected from the original asset; their direction has
not been compared with a running PS2 capture. Exact compressed-sampler EE rounding
remains unverified. This recovery establishes asset selection, visible content and
node-runtime behavior.

## Boundaries

Physical EE rounding of the clock conversion is not established.

FileListInfoManager and LayerCtl were decompiled for the relevant load and layer
contracts and checked against their original assembly. Their full runtime
modules are not covered here. Stage
streaming, shutdown cancellation inside decoders, other stage transitions and
retail visual comparison remain separate work.

## Open questions

An unproven static reading of the stage change:

- `STAGECTL` is `Gap::Bec::beNDMWStageCtl` (runtime vtable `0x0053DEA0`, descriptor at `0x00515708`).
- `Gap__Bec__beNDMWStageCtl__vfunc_31` is its six-state `NEXTSTAGE` coroutine (jump table `0x00515680`), which issues commands to
  STAGECTL, LAYERCTL, MODELCTRL and GENERATER.
- `beNDMWAfsStageLoad` and `beNDMWAfsSetup` sit beside it in the metadata and look like the pack streamers.
- The pending request is not held in the StageCtl object.
- The gate bookmark is separate: a stage calls `SYSsetGateStage(g_GateStage, g_GatePos)`, or
  `SYSsetGateStage("GateOff", -1)`, and `SYSgetGateStageName`/`SYSgetGateStageNo` read it back.
