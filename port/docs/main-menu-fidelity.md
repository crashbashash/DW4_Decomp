# Main-menu retail fidelity

This page records how closely the native title, character selection, naming and
created-character summary screens reproduce the USA retail game, and what each
comparison does and does not prove. Positions, text and cursors come from the
original scripts, controllers and authored layout data; comparisons use the
same state and, where a model animates, a matching pose. Normal graphics follow
the GPU-only policy.

The [technical specification](technical-spec.md) requires original Lua 4.0.1
scripts and native engine bindings. The title screens run the recovered
[title controller](title-controller.md). The character-screen measurements on
this page are of the character UI adapter in `../src/frontchr.c`, which owns
its name/species/value publication and controls; its starter values are
constants. With a save library the slot screen runs in the `stagIS13` scene
described in [Save Keeper and interface scenes](save-keeper.md), and the
adapter is the Create flow for a host without one. Original assets alone do
not establish accurate layout or timing.

## Evidence and method

- Workspace-private `../local/captures/dw4-port/charsel/` holds paired retail
  PNG/GS references for Create/Call, all four species, naming, question/Yes/No
  and the created summary. Repository-relative paths to this directory start
  with `../local/`. Its `NOTES.md` and `RAM-NOTES.md` give capture provenance.
  The title and Options references are in
  `../local/captures/dw4-port/option-screen/`.
- `RAM-NOTES.md` establishes that the observed creation flow remains in
  `stagIS10` with NDMW entry 806. Separate character-stage script folders do
  not own this live flow; the scripts that matter are entry 806's
  `gameStart.lua` and its native controller/text dependencies.
- STATUS uses a separate original-script/authored-font path with its own
  validation. Its passing comparisons do not prove character-menu fidelity.
- Each verifier compares the native draw list, exported by a read-only observer
  that does not advance clocks, against one retail vsync interval of a GS dump.
  It requires equal triangle counts, a complete one-to-one assignment of whole
  triangles, byte-identical textures against VRAM, and XY/UV/reciprocal-Q/colour
  agreement. The allowances are 0.126 pixels and 0.002 UV at native 640×448
  geometry; no comparison on this page changed them.
- Animated models are compared at a diagnostic joint time fitted to the saved
  retail geometry. These times are not read from live RAM and do not prove live
  phase equivalence. The recovered sequence fraction quantizes nanoseconds with
  `>>18`, so the fitting objective has plateaus: a continuous scalar search
  misses passing poses and a fine discrete search is required.

## Title screen

Title image caching retains authored `igImage` identity instead of merging
records by filename. AREA 620 contains two different `mojips.png`
rasterizations: copyright and menu quads bind separate image IDs, and the three
names resolve four actual textures. The source-ID bindings and both atlas byte
arrays agree with retail, without selecting a texture from capture data at
runtime.

Settled title artwork uses retail neutral RGB 127 / alpha 128. Title X
coordinates scale from the authored 640-pixel width, independently of the
448-line Y coordinates, matching the character screen and the original image's
scaling to higher-resolution 4:3 output. Boot/loading cards keep their own
scaling and materials. This does not settle the widescreen fixed-composition
policy in the technical specification.

`verify_mainmenu_title.py` requires complete one-to-one logo, Game Start,
Option and copyright quads, all eight triangles and three byte-exact atlases,
including position/UV/Q/colours. Both settled retail row references pass at
640×448 and at hardware 1280×960: four comparisons, 96 vertices, maximum XY
error 0.0625 pixels. These quads exclude decorative selector/background
submissions and live timing. Original controller traces independently cover
title input, Options, cancellation/re-entry and the Game Start handoff over
3,497 retail/native ticks (see the [title controller](title-controller.md)).

## Selection cursors

Original NDMW 806 `j_linewin02` actions define WAIT00 as looping JOINTSET 0..15
and WAIT01 as 40..55. LINEON00/01 use the separate ranges 20..25 and 60..65.
The adapter samples only the authored idle ranges, with a quarter-second loop;
a longer host loop enters the confirmation poses during idle and changes the
texture coordinates. Original action dispatch and loop-boundary timing are not
recovered.

Create/Call draws both the original diamond and its EFRoot ring with retail
RGB 127 / alpha 128, at the authored centres (27,92)/(27,114). Yes/No uses the
same unscaled model at (29,159)/(29,176). There is no synthetic resting diamond
and no font-derived model scale.

`test_mainmenu_cursor` verifies 240 ordinary draw updates across these four
states: all forty diamond/ring triangles remain, idle UVs keep the correct
atlas rows, colours match, and no untextured diamond appears. Its explicit
diagnostic mode exports ordered actual UI submissions, textures and pose
metadata for `verify_mainmenu_cursor.py`. Each comparison covers forty
triangles/120 vertices:

| Retail reference | Diagnostic joint seconds within idle range | Maximum position error |
| --- | --- | --- |
| 05-slot-screen-settled, Create | 0.102329871 | 0.053650 px |
| 06-cursor-call-digimon, Call | 0.216982298 | 0.047035 px |
| 07-cursor-create-digimon, Create | 0.23358 | 0.0471573 px |
| 17-name-confirm-yes-no | 0.083913515 | 0.057312 px |
| 18-name-confirm-no-highlight | 0.167279094 | 0.051865 px |

Reference 07 needs the discrete search described above (over 0.225..0.240
seconds); no production model offset, interpolation or tolerance backs it. The
1280×960 GPU Yes fixture normalizes to the same matching geometry, and the
240-update hardware loop reports zero CPU graphics calls.

## Lower message text

`fronttext.c` loads the original NDMW 806 `txt_mem.lua` bytecode through its
beLuaData reference chain and executes it in Lua 4.0.1 (there is no
`txt_title.lua` chunk). The callback is self-contained: TXTgetCallNo selects
the localized Unicode indices, font rows and alignment; its local helper sends
native TEXTCTL ALIGN/TEXTSET/SWITCH commands.

The adapter publishes callbacks 161 plus 250 for Create/Call and its legend,
225 for species selection, 232 for naming, 235 for the question, 236 for
Yes/No and 240 for the created-card message. The display owner keeps the
authored FontTree transforms/widths and NORMAL/MINIMUM metrics from the
localized title pack. Indexed Unicode keeps the original START
triangle/fullwidth letters, spacing, capitalization and CR/LF codes. The shared
font layout ignores CR and handles LF; source strings contain CR/LF pairs, so
there is no added wrapping or character substitution.

The text VM is a display-only owner in the character adapter. It implements the
callback's TEXTCTL operations and fails explicitly on unsupported calls. It
does not replace the Game Start controller, stage VM or general scene
orchestration. Geometry is prepared on publication and retained until the next
TEXTSET; rendering samples it without executing Lua or advancing clocks.

Measured agreement of the visible message/legend glyph sets:

| Set | Comparisons | Vertices | Maximum position error |
| --- | --- | --- | --- |
| Both Create/Call rows, all four species, empty/two-letter/moved-key naming, question, Yes/No, created card | 13 retail captures | 4,476 | 0.062485 px |
| The same states as the twelve upper-field comparisons below | 12 retail captures | 4,626 | 0.062485 px |
| 1280×960 hardware GPU fixtures, normalized | 10 | 3,684 | 0.062485 px |

Textures are byte-identical to VRAM and colours and Q match exactly. The
hardware fixtures report zero CPU graphics calls. Models, full-frame pixels and
live transition timing are outside these glyph comparisons.

## Upper species, name and keyboard fields

Species selection publishes CHRSELFONT14/font000. Naming uses
CHRSELFONT13/font000..007 for entered characters and the dim preview,
CHRSELFONT11/font000..004 for the five visible keys, and
CHRSELFONT10/font000..002 for adjacent modes. The rows use their original
NORMAL metrics, row widths, parent matrices and CENTER alignment. Entered
glyphs are RGB 114 and the preview is RGB 64; both use alpha 121.
`fronttext_set` caches glyph geometry on publication, so repeated rendering
does not rebuild unchanged rows.

Twelve saved retail states pass complete upper-glyph triangle comparisons: all
four species, empty/two-letter/moved/backspaced naming, question, Yes/No, and
return after No. They cover 642 vertices with byte-identical textures, colours
and Q, and maximum XY error 0.0000305 pixels. Twelve 1280×960 CPU diagnostic
exports cover the same 642 vertices at maximum normalized error 0.0000305
pixels; these establish scaling, not hardware rendering. Visual inspection of
paired empty-name frames confirms the text anchors; background animation phases
differ.

### Naming edit rules

The original NameSel update at `0x3def80` establishes the edit rules, and the
native adapter implements them:

- `0x3df550..0x3df838` scroll/wrap the strip while retaining its edge column.
- Up decrements and Down increments the mode, restarting the strip while
  retaining the column (`0x3df914` / `0x3dfa8c`). Down from the initial mode
  selects uppercase; `test_frontchr` uses it for its uppercase/cancel/
  created-card scenario.
- Confirm saves the current mode/strip/column per cell. Backspace restores that
  saved selection (`0x3e0114..0x3e014c`), not the most recently browsed key.

`verify_mainmenu_navigation.py` executes the retail instructions, including
the original initializer, with model, font and formatting leaves controlled and
explicitly admitted edit waits. 203 Latin/digit edit states match. This is not
a live pad-repeat or timing test: held-input repeat timings in the adapter are
the estimates documented in `../README.md`. The check is part of
`make -C port check-retail`.

### Name length and keyboard table

The USA name-length limit is eight. Original `0x3de260` writes `_langID=1` at
`0x3de264`, then `_nameMojiMax=8` at `0x3de2a4` and mode bounds 0..3.
`0x3de990` branches on that language at `0x3de9b4` into the eight-row
CHRSELFONT13 publication path (`0x3dec78` onward). Its six-row branch is the
other language path and does not own the USA flow.

The original US keyboard table at `0x4cc860` contains lowercase and uppercase
Latin, digits and seven symbols `＆！？～ー・：`. The adapter's symbol repertoire
and its ASCII name/record boundary are reconstructed; its symbol mode is not
claimed to match the original.

### Name-field brackets, outlines and arrows

`L_KEYBOARD` uses neutral RGB 127 / alpha 128, matching the original GS
submissions (RGB 128 fails the comparison; the bracket topology, positions and
UVs are authored). All four complete 34-triangle bracket sets pass at zero XY
error (empty, two letters, moved key, backspace), 408 vertices in total,
including the degenerate authored triangles; texture bytes, reciprocal Q and
colours match. Four 1280×960 CPU diagnostic bracket exports pass all 408
vertices at maximum normalized error 0.0000124 pixels. `test_mainmenu_cursor`
asserts the complete bracket count and neutral colours through four naming
states, alongside its 240-update diamond/ring test.

Mode/key outlines and the naming direction arrows also use retail RGB 127 /
alpha 128. In naming reference 13 each outline independently passes a complete
46-triangle comparison (138 vertices) with byte-exact texture/colours/Q:

| Outline | Diagnostic phase | Maximum XY error |
| --- | --- | --- |
| Mode | 0.165 s | 0.0630035 px |
| Key | 0.219 s | 0.060242 px |

No authored position or scale is altered. The paired single-phase gate fails
(best candidate error 0.756378 px) because the two retail models are at
different phases in that frame. The independent pose checks establish shape and
placement agreement, not synchronized live clocks; no fitted phase offset is
applied to production.

## Created summary

The summary uses original `MINIMUM` glyph metrics and the localized title
FontTree's immutable transforms/widths. The name uses CHRSELFONT03/font000;
level and species use CHRSELFONT04/font000 and font010; HP/MP use
CHRSELFONT05/font000, font001, font010 and font011. The level is centred and
numeric values are right aligned, matching the captured retail geometry.

The Lv/HP/MP labels are the original `j_mainstatuswin` label geometry. Its
`moji.png` `beTextureCtrlAttr` resolves to the localized atlas in
`stagIS10/separate/USA_pack.igb` (AREA 620), not the character model pack's
first fallback texture. The atlas and the original model positions/UVs match
retail exactly.

`test_mainmenu` exercises all four species' summaries and cancellation back to
the preserved name, and exports the actual draw list.
`verify_mainmenu_summary.py` passes against both
`20-created-digimon-card-stats` and `21-created-press-start-prompt`: 6 label
triangles/18 vertices plus 40 glyph triangles/120 vertices for Dorumon `aa`.
Both textures are byte-identical to VRAM, colours and reciprocal Q match, the
maximum glyph position error is 0.000031 pixels and the labels match at zero
error. The 1280×960 hardware GPU fixture reports zero CPU graphics calls for
all four species and normalizes to the same retail foreground geometry, with
maximum label error 0.0000124 pixels.

This proves the static foreground submissions, not the background, full-frame
pixels or transition timing.

## GPU path

The shared layer shader reconstructs the source bytes of normalized RGBA8
samples before GS integer truncation, which keeps the retail menu's decoded
atlas bytes exact on the GPU path; without it a decoded byte of 240 samples as
239 on the GPU. An independent census of all 256 RGB byte values passes
exactly. The mismatch is not an interpolation error (that hypothesis was tested
and rejected), and no interpolation or tolerance change backs the fix. Retail
submission positions, colours and textures are unaffected by this
fragment-stage rule. See the
[GPU contract](gpu-rendering.md#rgba8-byte-recovery-before-gs-truncation).

Hardware-required fixtures and `verify_host.py` reject a software renderer
(llvmpipe) explicitly, before drawing. There is no CPU fallback, software-
renderer exception or renderer-label override; a menu GPU reference comparison
run under a software renderer is diagnostic evidence, not hardware acceptance.

On a hardware GPU, twelve upper-field, twelve lower-message and four
name-bracket comparisons at 1280×960 cover 5,676 vertices with maximum
normalized XY error 0.062485 px. Hardware fixtures also verify both sampled
mode/key outlines, all four species summaries, both retail summary references
and 244 cursor/naming updates. Each hardware fixture requires zero CPU graphics
calls.

## Checks

| Check | Covers |
| --- | --- |
| `check-mainmenu` (`test_mainmenu`) | Four species' summaries, cancellation back to the preserved name |
| `check-mainmenu-cursor` (`test_mainmenu_cursor`) | 240 diamond/ring draw updates, bracket counts and neutral colours in four naming states |
| `check-fronttext` | Original callbacks, glyph stability across repeated draws, visibility, resize, explicit unknown-callback failure, fresh-owner recovery |
| `test_frontchr` | Name/cancel/created-card behaviour of the adapter |
| `test_menu_gpu` | CPU/GPU menu image comparison within its existing allowances |
| `check-retail` | Original initializer and 203 naming edit states; 3,497 original title integration ticks |
| `check-status-boot` | The create/edit/No/cancel/create/login route and two STATUS open/close cycles, retaining world/player/HUD state |
| `check-status-gpu`, `check-gpu-entries`, `check-title-mesh-gpu` | Normal hardware paths report zero CPU drawing, software backends are rejected, forced GPU failure stops explicitly |
| `check-gl-post` (`test_gl_post`) | Clipped RGBA/opacity blits byte-for-byte against the original CPU loop |

`make -C port check check-retail -j8` passes on a host with a hardware GPU.
Optional private RAM pose/fog inputs skip explicitly when missing. The suite's
window-presentation comparison passes its allowance (99.985% identical, mean
RGB delta 0.017/0.018); it fails explicitly, with no capture-size exception,
when the two captured windows differ in size. The work on this page is
native-only: the matching recovery is not edited and its byte-identity gate is
unaffected.

## Reproducing a comparison

From the repository root, with an existing private output directory.

Created summary:

```sh
make -C port build/test_mainmenu
port/build/test_mainmenu ../local/extracted ../scratch/main-menu-fidelity
python3 port/tools/verify_mainmenu_summary.py \
  --dump ../local/captures/dw4-port/charsel/20-created-digimon-card-stats.gs.zst \
  --native-dir ../scratch/main-menu-fidelity
```

Cursor (state and diagnostic joint time from the table above):

```sh
make -C port build/test_mainmenu_cursor
port/build/test_mainmenu_cursor ../local/extracted ../scratch/main-menu-fidelity/yes-fit yes 0.083913515
python3 port/tools/verify_mainmenu_cursor.py \
  --dump ../local/captures/dw4-port/charsel/17-name-confirm-yes-no.gs.zst \
  --native-dir ../scratch/main-menu-fidelity/yes-fit --state yes

port/build/test_mainmenu_cursor ../local/extracted ../scratch/main-menu-fidelity/create-fit create 0.23358
python3 port/tools/verify_mainmenu_cursor.py \
  --dump ../local/captures/dw4-port/charsel/07-cursor-create-digimon.gs.zst \
  --native-dir ../scratch/main-menu-fidelity/create-fit --state create
```

Lower message text:

```sh
port/build/test_mainmenu_cursor ../local/extracted ../scratch/main-menu-fidelity/text-name name-empty 0.1
python3 port/tools/verify_mainmenu_text.py \
  --dump ../local/captures/dw4-port/charsel/13-name-entry-first.gs.zst \
  --native-dir ../scratch/main-menu-fidelity/text-name
```

Name-field bracket:

```sh
port/build/test_mainmenu_cursor ../local/extracted ../scratch/main-menu-fidelity/bracket-name-empty name-empty 0.1
python3 port/tools/verify_mainmenu_cursor.py \
  --dump ../local/captures/dw4-port/charsel/13-name-entry-first.gs.zst \
  --native-dir ../scratch/main-menu-fidelity/bracket-name-empty --state name-empty
```

Title:

```sh
port/build/test_mainmenu_cursor ../local/extracted ../scratch/main-menu-fidelity/title-create title-create 1
python3 port/tools/verify_mainmenu_title.py \
  --dump ../local/captures/dw4-port/option-screen/01-main-menu-game-start.gs.zst \
  --native-dir ../scratch/main-menu-fidelity/title-create
```

## Private reports

Reports, logs and generated images stay outside Git in the workspace's
`../scratch/main-menu-fidelity/`:

| File | Content |
| --- | --- |
| `text-comparisons.json`, `gpu-text-comparisons.json` | Thirteen lower-text comparisons and the ten hardware GPU text fixtures |
| `text-name.json`, `text-created.json`, `text-create.json` | Three individual lower-text comparisons |
| `upper-final-comparisons.json`, `large-upper-comparisons.json` | Twelve upper-field comparisons at 640×448 and at 1280×960 (CPU diagnostic) |
| `bracket-final-comparisons.json`, `large-bracket-comparisons.json` | Four bracket comparisons at both sizes |
| `bracket-checks.log`, `bracket-navigation.log` | Focused bracket checks and the original-initializer navigation run |
| `title-final-comparisons.json` | Four title comparisons |
| `name-mode.json`, `name-key.json` | Independent mode/key outline comparisons |
| `host-gpu-upper-comparisons.json` | Twelve upper, twelve lower and four bracket comparisons on a hardware GPU |
| `texel-byte-full-validation.log` | Focused menu, naming, title integration, the exact byte census and the GS UI bridge checks |
| `terminal-native-retail.log` | `make -C port check check-retail -j8` |
| `closure-hardware.log` | `check-status-gpu`, `check-gpu-entries`, `check-title-mesh-gpu`, `check-status-boot` |
| `closure-matching.log` | Root `make check typed-check link -j8` |

## Open items

- Live phase equivalence is unverified for every animated model: diagnostic
  poses are fitted to saved geometry. Original `j_linewin02` action dispatch
  and loop-boundary timing are not recovered.
- The paired mode/key outline gate fails at a single phase. Independent
  action-clock publication must be recovered before that gate can pass.
- Species arrows are not compared against retail submissions.
- The original symbol encoding, the name/record encoding and record publication
  are not recovered; resolve them together before replacing the adapter's
  symbol and name interfaces.
- The created summary's native controller is not executed: the adapter
  publishes names, species and values. The complete downstream controller
  lifecycle and its live timing, including pad repeat, are not recovered.
- Backgrounds, decorative title selector/background submissions, title/Options
  whole-frame pixels and full transition timing are not compared.

Broader fidelity and port work is tracked in the [task list](project/tasks.md);
update it together with this page.
