# Stage loading cards and node animation

The USA game chooses a stage-specific loading scene, whose texture already
contains the preview and localized stage name.

## Stage and language lookup

`beFileListInfoManager::vfunc_27` (`0x0037fa30`, 5,776 bytes) initializes its
stage load in state 0. It copies the destination name into GameInfo `+0x38`,
then builds the loading filename in the mutable string at GameInfo `+0x48`:

1. Copy the bare destination (`stagML11`).
2. Erase its first two characters (`FUN_0030bbf0`, index 0, count 2).
3. Insert `ld` at index 0 (`FUN_0030b460`).
4. Append `.igb` and prepend `loadingUSA/`.
5. Request `loadingUSA/ldagML11.igb` through `FUN_003092f0`; retain the
   request in the manager's pending list `+0x2c`, and enter state 1.

The constants are at `0x0050e570` (`ld`), `0x0050e578` (`.igb`) and
`0x0050e580` (`loadingUSA/`). State 1 waits for request completion before
registering its objects. State 4 checks both the remaining file queue and the
loading node's play-limit predicate. Only when both complete does it lock the
loading animation through `FUN_0039adf0`, and advance through states 20/21/5.
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

## Byte-matched clock update

`FUN_0039a9e0` has complete, byte-identical typed C in
[`beNodeAnimClock.cpp`](../../src/game/beNodeAnimClock.cpp): **308 code bytes and
two relocations**. It uses the reflected `beNodeAnim` base
fields; the same clock routine serves derived loading nodes.

Keeping the
incoming timestamp in a `const` local, reading the previous play count into a
second `const` local, and then reusing the incoming parameter for elapsed time
reproduce both the original `a1` register and the addition's operand order;
without them four words differ in register allocation.
The explicit locked-time switch and compound 64-bit shift retain the original
control flow and arithmetic shape. The pinned alternate compiler with `-O3,p`
produces the entire retail body without inline assembly or compiler changes.

The full matching check has zero mismatches and the relink is
byte-identical. The reference/retail loading-node oracle also passes
all **2,631 comparisons** below.

## Complete contiguous runtime group

[`loadingnode.c`](../../recovered/frontend/loadingnode.c) and
[`loadingnode.h`](../../recovered/frontend/loadingnode.h) recover all nine
consecutive bodies from `0x0039a930` through `0x0039ae44` (1,232 instruction
bytes, excluding alignment). They are behavioral references, not
byte-matched CodeWarrior translation units; the clock routine `0x0039a9e0` is
byte-matched separately (above).

| Address | Contract |
|---|---|
| `0x0039a930` | Base-node traversal thunk, reverses context/node arguments |
| `0x0039a960` | Rebase `_timeBias` against the scaled clock |
| `0x0039a9e0` | Return locked time or advance/loop the node clock |
| `0x0039ab20` | First-time setup, context time push, child traversal, callback/pop |
| `0x0039ad80` | Register base-node traversal callback |
| `0x0039adc0` | Loading-node traversal thunk |
| `0x0039adf0` | Copy `_lockTime` to `_stopTime` |
| `0x0039ae00` | Strict predicate `_playLimitTime < _playTime` |
| `0x0039ae10` | Register loading-node traversal callback |

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

## Reproduction and boundaries

From the repository root:

```sh
python3 scripts/verify_loadingnode.py --elf orig/SLUS-20836/SLUS_208.36
```

The verifier executes retail instructions and recovered C in the same memory
world: **2,631 comparisons**, all nine bodies and all reachable body instruction
addresses, ordered non-stack stores, ordered leaf calls, final memory and
specified returns. Cases cover first traversal, allocation/growth, callbacks,
child return codes, clock truncation and unsigned conversion, stalls, strict
loop/ready boundaries, locking and a 650-tick evolving lifecycle. Float-to-int64
software helpers execute on the retail side; recovered C uses the shared EE
float model. External traversal/allocator callbacks are deterministic leaves;
their implementations and physical EE rounding are outside this proof.

FileListInfoManager and LayerCtl were decompiled for the relevant load and layer
contracts and checked against their original assembly. Their full runtime
modules have not been reconstructed as differential C references here. Stage
streaming, shutdown cancellation inside decoders, other stage transitions and
retail visual comparison remain separate work.

## Open questions

An unproven static reading of the stage change:

- `STAGECTL` is `Gap::Bec::beNDMWStageCtl` (runtime vtable `0x0053DEA0`, descriptor at `0x00515708`).
- `FUN_003cd500` is its six-state `NEXTSTAGE` coroutine (jump table `0x00515680`), which issues commands to
  STAGECTL, LAYERCTL, MODELCTRL and GENERATER.
- `beNDMWAfsStageLoad` and `beNDMWAfsSetup` sit beside it in the metadata and look like the pack streamers.
- The pending request is not held in the StageCtl object.
- The gate bookmark is separate: a stage calls `SYSsetGateStage(g_GateStage, g_GatePos)`, or
  `SYSsetGateStage("GateOff", -1)`, and `SYSgetGateStageName`/`SYSgetGateStageNo` read it back.
