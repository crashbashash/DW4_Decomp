# Concrete STATUS views and text callbacks

`src/statusview.c` supplies native WindowTitle and WindowSelect children for
Title00–04, Select00–01 and SelectE0–E1. They execute the original `txt_status.lua`, mutate
scene-owned TEXTCTL rows, dispatch to the prepared MODELCTRL/SELECTCTRL owners,
and retain tracked resources until native close completion. Scoped text calls,
Unicode player/stat display and comparison previews are implemented and verified.
Prepared shinka database ownership supplies the real species-name lookup
(see [string databases](databases.md)). Production fresh starter PLAYERNAME/stats reach the authored fonts.
The live STATUS factory uses these views.

## Retail root rendering comparison

Prepared STATUS roots render authored WN model geometry alongside original
fonts through [model replay](controller-services.md#authored-wn-model-rendering).
Repeat draws preserve controller/scene clocks and source node state.

### Acceptance state

Presentation: projection normalization and VU viewport (archived outside the repository)
passes all seventeen single-interval geometry/texture/depth/filter/color-mask
comparisons and one-to-one ordered pixel-bearing primitives. Original
mode-three normalization occurs before point projection, and the native path uses VU multiply/add and
positive-origin FTOI4 (without them two sampled corners fail). The paused root's
mean absolute RGB error is 0.4835 and its portrait occlusion is correct.
Prefix occlusion has an explicit opaque-background/depth certificate. Live
phase and complete pixel parity retain the documented limits.
Position/UV/Q allowances are those stated below.

Live frames: completed opening submissions (archived outside the repository)
compare five normal-engine reopening frames with retail GS intervals, without
observed-clock overrides. All 7,308 vertices and 2,015 ordered pixel-bearing
primitives pass with prefix certificates. Terminal closing UI passes separately;
visible world underlay and residual middle-phase lists keep broader trajectory/
full-frame acceptance open.

Seventeen-page vertex gate: with the
[transform fraction recovery](controller-services.md#authored-transform-interpolation-fractions),
128,352/128,352 vertices match in dump
vsync interval five for each capture, including all 26,136 text vertices.
`verify_status_render.py --retail-vsync 5` uses the parser interval metadata;
it does not combine candidates from different frames. The root rejects every
other tested interval. The tool checks PRIM.TME independently of ABE. This
vertex gate alone does not establish depth, draw order or pixel parity.

### Reference, export and comparator

The fresh retail Dorumon `aa` root has a PNG/GS reference and STATUS-open
savestate; see reference setup (archived outside the repository).
`test_statusviews` accepts an optional fourth command argument naming an existing
private output directory. It exports each of its four complete roots separately,
including the actual model/text vertices, normalized UVs, decoded textures,
rendered PNG, controller sequence/position/clock metadata and pack/id and
active/drawable metadata. Exports use `--root-only`. With exports enabled
the fixture uses `aa`, matching the reference's player name; normal checks retain
their existing `Root` record. Root 0 matches the retail first-player record.

`tools/verify_status_render.py` compares these submissions against retail GS
vertices grouped by byte-identical texture, requiring position, normalized UV,
color and exported reciprocal Q matches.
The strict comparison returns failure while any difference remains.
`--report-only` writes a diagnostic without asserting parity. This is a
native-to-retail candidate comparison, not a full-frame or bidirectional draw-set
comparison; matching text/panels does not prove that every retail primitive is
present. Prepared authored-view checks pass with the export enabled.

From the repository root (private output directories must already exist):

```sh
port/build/test_statusviews ../local/extracted /tmp/status-root.png /tmp/status-export --root-only
python3 port/tools/verify_status_render.py \
  --dump '../local/captures/dw4-port/status-validation-20261012/Digimon World 4_SLUS-20836_20261012193738.gs.zst' \
  --native-dir /tmp/status-export --root 0 --json /tmp/status-root-comparison.json
```

Evidence is workspace `local/captures/dw4-port/status-validation-20261012/`. The
passing root report at the observed clocks is `trivial-root-comparison.json`, with
exports in `native-trivial-root/` (see the projection section below).
`native-root/`, `root-comparison.json`, `root-comparison-visible.json`,
`native-phase-root/` and `phase-root-comparison.json` in the same folder are
exports and reports made without the cursor visibility, root title identities or
authored projection described below; they fail on the affected cursor,
help/header and background groups and are not the reference result. The folder also
holds `phase-root-manifest.json` and `phase-root-clocks.{json,tsv}`. Logs are workspace
`scratch/status-root-export*.log`, `status-root-comparison.log` and
`status-root-strict.log`.

### Cursor visibility

Original `377990` restores the instance switch bit before testing
same/current action, so a cursor's OPEN HIDE does not survive later ACTION
messages; native dispatch restores visibility at that boundary.
All four actual root cursors must be drawable in the fixture. This is a
visibility rule, not a clock alignment.
See [Action2 visibility](controller-services.md#action-replacement-restores-visibility).

### Observed-clock sampling

The native cursor is sampled at `SQ_WAIT00`, 150019824 ns; the exported clock
metadata alone does not establish the corresponding retail phase.

The renderer supports a diagnostic, read-only node-clock callback through
`dw4_modelview_draw_clocks`; ordinary drawing continues to use live native clocks.
`test_statusviews --root-only` reads optional `DW4_STATUS_REFERENCE_CLOCKS` rows
as `model_name slot nanoseconds`. The snapshot/clock invariants and repeat-draw
checks still run when reference sampling is enabled. This controls pose sampling
only; eligibility, actor state, opacity and lifecycle remain native. It therefore
does not establish live clock equivalence.

An optional fourth column limits a clock row to a `frames.tsv` view label.
This allows one fresh menu-export route to sample separately observed clocks
for each page; three-column rows retain their global behavior. The reference
label exists only during a diagnostic draw. Normal rendering still uses the
native model clock, and source scene/actor/clock invariants remain checked.

The observed-clock root reference is `Digimon World 4_SLUS-20836_20261012200529.gs.zst`; the capture needed
additional compositor-focused frame advances before it became complete. The
decoder walks 5,128 transfers and four vsync records. Slot 2's state carries the
observed Action2 node clocks near the beginning of that stream; this is a
multi-vsync candidate comparison, not an atomic single-frame proof.
The capture manifest and `phase-root-clocks.{json,tsv}` retain that scope.

Four-root checks, full authored views, root retail states,
eight factory identities, normal boot/SDL STATUS and prepared ASan/UBSan pass.

### Root title identities

Original registration/factory traces show `3b3c80` creates Title00, `3b3ac0` Title01,
`3b3900` Title02 and `3b36f0` Title03; assigning Title01–04 from neighboring
symbols is wrong. Native creates Title00 first and Title01–03
after background opening; the root has no Title04 border. Eight original
factory class traces are checked before the root state comparisons.

### Authored WN projection and reciprocal Q

Retail's 64×64 background texture submissions use perspective Q values from
0.0010984873 to 0.0064804908; the other root texture sizes use Q=1.

The background camera is encoded in the existing pack attributes, rather than
the lobby camera or a fitted focal length. NDMW 820 `igModelViewMatrixAttr`
record `0x65e54` translates view z by −300; `igProjectionMatrixAttr` record
`0x665a0` supplies the perspective matrix. The ordinary WN pair is at
`0x3e8c0`/`0x3e69c` and is affine. The scene loader retains these
attributes. Model replay resolves nearest inherited view/projection/viewport
attributes, applies world → view → homogeneous projection, and submits STQ with
reciprocal clip W. Attribute-free models retain their existing fallback.

Perspective triangles wholly outside a common clip plane are rejected; crossing
near/far planes are clipped before division. XY vertices crossing viewport edges
remain intact for raster scissoring, matching the retail offscreen submissions.
A full XY polygon clip introduces UV/position mismatches, and
a GS guard rejection also fails the comparison; neither is used.
Affine menu geometry retains its unclipped submission convention.

The comparator requires exported reciprocal Q as well as position,
normalized UV, color and byte-identical texture. At the observed root clocks,
`trivial-root-comparison.json` passes all **5,220 retained vertices**, including
756 background vertices, 3,378 other model vertices and 1,086 text vertices.
Maximum position error is **0.0721441 pixels**; maximum observed relative Q error
is **0.000023447**, within the combined `1e-8 + 2e-5 × |retail Q|` tolerance.
All eleven exported texture submissions match retail VRAM byte for byte.
A negative diagnostic replacing background Q with 1 while retaining XY/UV/colors
fails all 756 background vertices and exits nonzero. A comparison of normalized
UV alone cannot detect that error.

Evidence is workspace `local/captures/dw4-port/status-validation-20261012/`,
with exports in `native-trivial-root/`. Negative evidence is workspace
`scratch/status-validation-20261012/q-negative.json`. Logs are
`scratch/status-projection-*.log` and `scratch/status-trivial-root-comparison.log`.
Full native/retail, normal-boot STATUS, expanded SDL and prepared ASan/UBSan pass.
This report is native-to-retail candidate evidence over four vsyncs;
by itself it does not establish full-frame, reverse draw-set or live phase equivalence.

## Recovered initialization

| View | Retail initializer | Authored behavior |
| --- | --- | --- |
| Title00 | `0x00424230` | i_stback and i_bgclear SQ_OPEN/SQ_CLOSE |
| Title01 | `0x004242a0` | Label/data font ownership, text call 3, stat refresh, portrait and normal/shop base |
| Title02 | `0x00426100` | i_messwn SQ_STOPEN/SQ_STCLOSE |
| Title03 | `0x00426140` | i_staccount SQ_OPEN/SQ_CLOSE, three STWINFONT34 rows, text call 0 (the Select/Confirm/Cancel legend, top right) |
| Title04 | `0x004265c0` | i_sttitle SQ_OPEN/SQ_CLOSE, STWINFONT12/font000, supplied text call |
| Select00 | `0x00423760` | i_stmenu01 SQ_3LINEUPOPEN/SQ_CLOSE, three STWINFONT08 rows, text call 15 |

The pure `dw4_statusview_setup` boundary emits ordered model, text, resource,
script and refresh commands. The owned window API consumes those commands through
native services. Strings in emitted commands are borrowed only during the call;
tracked names are owned arena string handles (see [arena resource and selector ownership](#arena-resource-and-selector-ownership)). Closing dispatches each
model's actual close sequence, hides its tracked font rows, and polls ISRUN.
Missing or nonnumeric model queries fail explicitly. Completion checks the
query's low byte and actual descendant pruning; elapsed ticks do not substitute
for model completion. Failed view operations preserve the window's completion
hold so a containing owner can require scene recreation.

Title01 owns the twelve label fonts 030–039/060–061 in STWINFONT06, clears the
name/digimon/stat data rows with their recovered alignment, then runs text call 3.
Its `0x00425430` refresh path invokes SUBWND UPDATE, obtains DIGIMONNO, and
opens i_stdigiface at (-410,240,0). All sixteen portrait sequences and the
out-of-range Agumon default are recovered. The normal variant opens i_stbase
SQ_LOPEN and displays the 28 STWINFONT06 rows plus STWINFONT04/font001; the shop
variant opens j_shbase and hides those rows (`0x00425e60`, `0x00425fb0`).

The native Title01 API requires a real refresh callback and player records.
`dw4_statusstats_refresh` supplies that callback through the native dialogue
owner. It requires typed PLAYERNAME, the numeric records below, and a real
`shinka` database NAME lookup. Prepared [database ownership](databases.md)
supplies the authored shinka NAME lookup. Integration exercises all four
production starter name/stat records, followed by controlled preview mutations.
See [fresh character records](player-records.md#fresh-character-name-and-stats).

Select01, SelectE0 and SelectE1
initializers are implemented in the same resource owner. Prepared native checks execute calls
31/61/91 through original txt_status.lua and confirm/close actual submenu cursors,
including caller-owned row counts and copied disabled flags. See
[shared equipment and submenu views](status-submenus.md#authored-selectors-and-shared-equipment-base)
for record wiring and remaining concrete inventory/detail/page dependencies.

The CONTENT resource tracker
supports repeated item/pocket/DEVICE and skill projection with full description
strings and failure holds. Original STATUS Lua and production database strings
reach authored fonts; [content projection and remaining controller work](status-submenus.md#item-and-skill-content-projection) records the boundary.

## Player data and comparison state

`src/statusstats.c` implements SUBWND STATUS dispatch `0x003d60e0` commands
2 (UPDATE), 4 (ONPREVIEW) and 5 (OFPREVIEW). UPDATE copies the first PLAYERNAME
Unicode object into STWINFONT02/font000. LEVEL prints in STWINFONT04/font000,
with only an upper cap of 999; DIGIMONNO selects the shinka NAME string for
font001. HP/MP populate STWINFONT06/font000/001. MHP/MMP populate 010/011;
TSUYOSA, MAMORI, KASHIKOSA, SEISHIN, SUBAYASA, HONOOTEIKO, KOORITEIKO,
KAMINARITEIKO and YAMITEIKO populate 040–048. XDATA, BIT and remaining EXP
populate 049, 070 and 071. Remaining EXP is signed EE `NEXTEXP - EXP` with
32-bit wrap: negative results display `0`, capped levels display `----`.

The owner retains thirteen signed values in Work `_parameter` (`igIntList`),
in retail order: the eleven comparison
stats, then HP and MP. Preview publishes current stats with equal gray
(0.9,0.9,0.9), decrease red (0.94,0.4,0.25), or increase cyan (0,0.96,1).
Preview-off republishes baseline stats, sends DEFAULTCOLOR and restores HP/MP
records. It does not restore the eleven stat records; the equipment transaction
owner handles that separately. Snapshots belong to the receiving status owner
and reject a different player's preview. Missing records/database dependencies
fail before text publication. Sink failure invalidates the snapshot and requires
scene recreation; subsequent preview-off cannot mutate records from that state.
No missing stat, player name or species is synthesized.

The native facade returns snapshots by value and owns a Work record or borrows
stock's Work for the menu lifetime. Both `_parameter` and `_preview` are declared
`igIntList` by the retail constructor; the supported commands use `_parameter`.
SUBWND RAM binds that same Work. Direct arena edits drive preview-off display
and HP/MP restoration. Close windows before releasing the Work; close the stat
facade before reinitializing it. The pure snapshot rule ABI remains a transient
adapter for the original-instruction comparator, not another persistent store.


Select00's native window runs its initializer, then sends SELECTCTRL GENERATE
with three rows, the retained selection and (-83,209,0). WindowSelect's recovered
same-update GETSELECT/ISEND behavior writes its parent's result. Native selection
opening/navigation/confirmation/cancellation/closing executes in the existing
SELECTCTRL owner. The view's model/text close waits retain its lifetime after
selection completion. Each view captures the parent's last selection at creation.
It borrows its parent state until recursive teardown; factories must preserve
that parent lifetime and assign the real player's slot.

## Original text execution

Retail window helper `0x003f5920` stores the signed call number in global
`0x0058a220` and runs the named chunk. TXTgetCallNo `0x003747f0` reads that value.
`dw4_scriptengine_text_event` implements this through the original Lua runtime,
using the caller's scope. Nested text callbacks leave their last call number
published, matching the global contract; they restore the caller's execution
scope on return. VM recreation preserves the engine-owned last call number.

Unloading an active text scope invalidates its callback and blocks later native
calls. Whole-scene cleanup is rejected while a text callback is active, before
mutating VM/SD/DM owners. The original status text helper therefore retains its
call-number and ownership context without using Lua globals to represent host
pointers or replacing the shipped script with a native string table.

## Verification

`make check-statusviews-retail` compares **200 initialization service/resource
traces** against original instructions (172 without the Select01/SelectE0/SelectE1
initializers), covering all four player selectors,
all sixteen portraits plus invalid IDs, both Title01 variants and Title04 text
calls 30/60/90. String interning, list storage, window model/text helpers and
property lookup are controlled leaves. The portrait selector and variant/table
loops execute retail instructions. The comparator retains all four LQ/SQ lanes
for authored table copies; the shared scalar interpreter otherwise truncates LQ
to 64 bits. Six signed TXTgetCallNo reads also match retail instructions.

`make check-statusviews` prepares the original ML11 assets/shared scripts and
opens/closes all six native views. Original `txt_status.lua` populates authored
font rows, real MODELCTRL closes gate completion, and Select00 confirms rows
zero/two and cancels row one through native input/SELECTCTRL/model sequences.
The stat projection and preview use native owners and authored font rows. Only
input records and boot-only service projection are controlled; shinka NAME uses
the prepared native database owner.
Separate text tests verify nested call numbers, restored scopes, preserved state
across VM reset, cleanup refusal during callbacks and unload rejection.

`make check-statusstats-retail` compares 96 UPDATE traces/snapshots and 192
preview traces/HP/MP restorations against original instructions. All four player
slots, level boundaries, signed extrema and wrapped EXP subtraction are covered.
Property/database/string formatting and text dispatch are controlled leaves;
formatting branches, signed comparisons, snapshot writes and restoration execute
retail instructions. Native tests cover Unicode copying/type preservation, missing
dependencies, wrong-player snapshots and failure holds. Prepared Title01 tests
verify the chosen name, stats, species, remaining EXP, three preview colors and
restoration in actual authored font rows.

Full `make check check-retail -j8` passes on Linux with
`SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a`; optional private live-input
checks retain their skips. Headless view/text tests
and stat ownership tests pass ASan/UBSan with leak detection enabled and both sanitizers configured to
halt on errors. No Windows or physical Steam Deck validation is claimed; the
rendered-frame limits are in the [rendering comparison](#retail-root-rendering-comparison).

## Registered SUBWND stat commands

The native SUBWND owner dispatches UPDATE, ONPREVIEW and OFPREVIEW to
explicit factory stat callbacks. Encoded player arguments use I<0..3>; omitted
arguments retain the command's player-zero default. Missing owners and malformed
arguments fail before stat publication. The live STATUS factory supplies its
actual stat/preview owner and rejects commands outside its active lobby menu.
Currency reset/acknowledgement sends SUBWND UPDATE through this registry,
not through a private refresh path.

Prepared stat tests issue all three commands through the registered service
and observe production records, original fonts, preview colors and HP/MP
restoration. The original `3d60e0` checks match 96 UPDATE snapshots
and 192 preview traces. Factory callbacks remain borrowed for their menu/scene
lifetime.

## Arena resource and selector ownership

Model/font tracking uses the five recovered close lists with owned string
handles, preserving native deduplication, close order and completion holds.
Selector cursor, row/start/position and byte decisions are recovered fields;
restart publishes a replacement decision list only after allocation succeeds.
The context retains no parameter/enable-array mirror. Partial
construction and final release free strings, blocks and list objects. The pure
setup oracle retains its original controlled leaves; prepared and live tests
exercise the real owner. See [arena scope](arena-object-model.md#menu-resources-stock-and-retained-references).
