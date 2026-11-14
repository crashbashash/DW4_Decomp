# The front-end boot: engine → logos → opening → title → menu

How the game gets from power-on to the title menu. The *engine* boot
below it (CRT → heap → managers → frame loop) is [`engine-boot.md`](engine-boot.md); the script VM
and its native API are [`script-engine-lua.md`](script-engine-lua.md); the decompiled scripts are in
[`lua-tree-layout.md`](lua-tree-layout.md).

## The observed sequence

Power-on, no savestate: **Intrinsic Alchemy** (publisher) → **Sođec + ADK** (developer) → the
"DIGIMON WORLD" / "DIGITAL MONSTER" cards → the "Annihilation" opening FMV (with the "The Scourge of
the Royal Knights!" card) → the title ("DIGIMON 4 / DIGIMON WORLD", "▸ Press START button ◂") → the
**main menu: "Game Start" (highlighted) / "Option"**.

## It is a stage sequence, scripted in Lua

The front-end is not one function. It is a chain of **stage entries** in `NDMW.AFS` (800…814), each a
set of Lua chunks run in order, each driving a named 3-D scene stage. From the decompiled scripts
([`lua-tree-layout.md`](lua-tree-layout.md) §00):

| AFS entry | tree name | scene stage | what it is |
| --- | --- | --- | --- |
| 800 | `menu-database` | - | `DBBase` + font database load |
| 802 | `bandai-logo` | `stagIS09` | Bandai logo + rating splash |
| 804 | `opening` | `stagIS10` | the opening movie |
| 806 | `title-screen` | `AM_TITLE` | the title screen and its menu |
| 808 / 810 / 812 | `character-select-1..3` | | character select / difficulty |
| 814 | `endroll` | | staff credits |

The scene-stage names sit in one run of the ELF's `.data` at **`0x50e668`**:
`start.lua`, `first.lua`, `stagIS08`, `stagIS09`, `stagIS10`, `stagIS12` (the neighbouring strings
`ROOTATTR`, `Gap::Bec::beFileListInfoManager` are the same table's tail). The title's own Lua writes
the names lower-case (`stagis09`, `stagis10`); the ELF spells them upper-case, so one side is
normalised at lookup.

The front-end stages are in the game's own stage list (`data/lua_stages.txt`, recovered from the
master stage list, AFS entry 603): **`stagIS07`…`stagIS13`, `stagIS20`, `stagML02`, and
`stagML12`–`stagML14`** alongside the title's **`stagML11`**: `IS` for the interface scenes, `ML`
for the menu/title scenes. (The file is alphabetically sorted, so the front-end rows are adjacent but
that is the sort, not the running order.) The debug stage-select menu
(`14-misc/01-stage-select-list_e603/050-msg-80129.lua`, see
[`../systems/dev-stage-debug-menu.md`](../systems/dev-stage-debug-menu.md)) is just a `NEXTSTAGE` list
over these, which is why the same names appear in it.

## Who drives the transitions

- **`beNDMWStageCtl`** (vtable `0x53dea0`, RTTI `0x515708`) with its info record
  **`beNDMWStageCtlInfo`** (vtable `0x53d9d0`, RTTI `0x515238`) carrying `_stageName` (`0x501d00`),
  `_nextStage` (`0x501d10`) and `_isStageLoop` (`0x501d20`), the stage machine's own fields.
- **The Lua API does the switching.** Every front-end entry has a `dm-run` chunk that ends with the
  same template, differing only in stage name and mode:

  ```lua
  be:DMsetSD("STAGECTL", nil, -2, "NEXTSTAGE", "stagis09", 0)   -- logo → its scene stage
  be:DMrun()
  ```

  and the input gate `be:sd("STAGECTL", nil, -2, "PADINPUT", "ENABLE", 29)`. Seen with
  `stagis09` 0 (bandai-logo), `stagis10` 0 (opening) and `stagML11` 9 (title / menu-database /
  bandai-logo tails).
- **`beNDMWLoadCtrl2::Update` @ `0x3f1a80`** (2,512 B): the front-end **load controller**. Its
  name table (`0x518130…`) is the sequence of things it loads and does: `COMMONINTF`,
  `LOADINTF2_ALL`, `j_chrselback`, `SQ_OPEN` / `SQ_WTIN60` / `SQ_BLOUT30` / `SQ_CLOSE`,
  `SETSELECT_DATA`, `GAMERAM`, `GETCOMMON`, `NINZU`, `DIFFICULTY`, `CAMERAMODE`, `LIGHTMODE`,
  `TITLE2`, `GAMESTART`, `gameStart.lua`, `PLAYERPOINT`, `SETGENERATEPOS`, `STAGECTL`, `stagML11`,
  `NEXTSTAGE`, `LOADCTRL2`, `GAMEDATAINIT`.
- **`beNDMWTitle2`** (vtable `0x53e9a0`, RTTI `0x5186f8`): `vfunc_31` @ `0x3f2ef0` (**8,700 B**)
  references `stagIS08` and `stagIS09`, and `vfunc_29` @ `0x3f5320` references `TITLE2`, so the
  title controller also runs the logo scenes. Its menu rows are **`beNDMWTitle2Option`**
  (vtable `0x53dcf0`, RTTI `0x515450`), the "Game Start" / "Option" entries.
- **`beNDMWLogo`** (vtable `0x5409d0`, RTTI `0x51db88`) with `beNDMWLogoInfo` /
  `beNDMWLogoCtrlData`: the logo splash.

The small slot-29 wrappers are matching C++. `beNDMWTitle2::vfunc_29`
(`0x3f5320`) forwards `(this->_field14, callerArgument, descriptor 0x5186a8)` to
`beMessenger_RegisterReceiverFromInfo`; `beNDMWLogo::vfunc_29` (`0x44abc0`) is the same operation with descriptor
`0x51db38`. The middle argument matters: m2c drops it when the callee has no recovered
prototype, which makes a draft look like a two-argument call. The functions also need C++ mode;
MWCC's C front end tail-calls the helper, while retail keeps a framed call.

## The title screen itself

The title entry (806) is a normal stage script: `funcStartLayerSet` / `funcFirstLayerSet`, the
layer/`CFLclear` camera setup, then the `dm-run` template with `NEXTSTAGE stagML11`. Its `layer-setup-sq-open`
chunk is where the title becomes live: `SETDEMOCAMERA entry`, `PLAY "AM_TITLE"` (or `AM_TITLE2` when
`SYSgetArea() != -1`, i.e. resuming inside the game), `MODELCTRL j_startback GENERATE SQ_OPEN`,
`TITLE2 RUN`, then `funcFirstLayerSet()`, `SWITCHCTRL ALLON` and the input gate
`PADINPUT ENABLE 29`. The menu is therefore engine state (`beNDMWTitle2`) driven by the script, not a
script-drawn UI.

The **game-start** path is the `GAMESTART` / `gameStart.lua` / `PLAYERPOINT SETGENERATEPOS` block in
the `beNDMWLoadCtrl2` table, followed by another `NEXTSTAGE`.

## The title's 2-D UI tree

The logo, the copyright block and the two menu rows are **pack scene content**, not an engine
overlay. `AREA.AFS` entry 620 holds three `igModelCtrl` graphs beside the light-trail `j_startback`
graph (the tunnel layer, recovered separately):

| graph | nodes (world) | geometry | texture |
| --- | --- | --- | --- |
| `j_startlogo` | `rogo` y=+73 | `polySurfaceShape2`: x ∈ [−294.4, 294.4], y ∈ [−129.95, 164.45], z=400, full UV | `logo.png` (512×256) |
| `j_startlogo` | `kenri` y=−170 | `polySurfaceShape4`: x ∈ [−155, 155], y ∈ [−48.5, 27.5], z=400, UV v 0…0.4 | `mojips.png` (the copyright lines) |
| `j_startmenu01` | `start` | `polySurfaceShape5`: x ∈ [−160, 160], z=400, UV v 0.758…0.984 | `mojips.png` (the "Press START button" line) |
| `j_startmenu02` | `menu`, `null1` | `polySurfaceShape5` / `polySurfaceShape34`, z=600 | `mojips.png` (the "Game Start" / "Option" rows) |
| both menus | `null2`, `select` | `polySurfaceShape35/36/37`: `cursor.png` sampled at a constant texel | `cursor.png` (the highlight bars) |

The engine draws each geometry's four UV'd vertices in **screen space**: one model unit = one pixel
in a **640×448** space, +y up, origin at the framebuffer centre, `z` as painter depth (a larger `z`
is nearer). The material is the pack's own chain: `igAttrSet._attributes` (**ordinal 8**) → an
`igAttrList` (count at `+8`, array a block handle at `+0x10` whose members are still object ids) →
the `igTextureBindAttr._texture` (**ordinal 4**) → `igTextureAttr._image` (**ordinal 12**) →
`igImage` (`_px` 2 / `_py` 3 / `_pImage` 13 / `_pClut` 17 / `_bytesPerRow` 19 / `_pNameString` 22)
→ `igClut._pData` (**ordinal 5**). The ordinals are the class's descriptor slots, read from the
pack's class triples, *not* the `reflection.json` field-list index.

Each node carries an `igTransformSequence1_5` **pop-in** (scale (0,0,1) → (1,1,1)), so the
`igTransform`'s stored `_m` is a placeholder (zero x/y rows) and the visible resting layout is the
part of the timeline where the scale is (1,1,1).

The graphs are **animated by the pack's own `beAction2` schedule, not a frozen pose**: `j_startlogo`'s `OPEN` step is a `beAction2JOINTSET` `0…30` (60 fps frames, mode `OS`) with a
`beAction2FADESET IN` of 10 frames, and its `CLOSE` an `OUT` of 30; `j_startmenu01`/`02` `OPEN` is
`JOINTSET 0…15 OS` with 1-frame `IN`/`OUT` fades. `j_startmenu02`'s row steps are `LINEON00 110…125`,
`LINEDW01 50…70` (indicator down), `LINEUP00 80…100` (up) and `LINEON01 170…185`; its `select` node's
sequence carries the indicator's `y = −60 / −108` rest keys. A JOINTSET is a *time range* (a node's
`_time` is rebased onto it and clamped at the end for `OS`), not a joint count.

Beneath the layer and this UI sits the static **`stagML11` dome** (`NDMW.AFS` 806, `stagml11.igb`
ref 0: 208 meshes / 24 949 triangles), composed through the same recovered title camera and drawn
first. The game's order is backdrop → `j_startback` layer → UI. That pack carries no
lights, colours or textures, so its exact VU1 tone (and the mirrored "DIGIMON WORLD" reflection) is
engine runtime state that the pack does not encode and is not recovered.

Verified against the game's own menu framebuffer: the logo quad's red frame lands at **x 41…416**,
and the copyright quad at x 165…475 / y 367…432. The recovered `OPEN` is a pop-in: a degenerate logo
quad at `t=0` settling to the rest rectangle.

**How the controller addresses them.** `beNDMWTitle2`'s own message/target table in
`.data` runs `… TEXTORDER`, `j_startlogo`, `SQ_OPEN`, `j_startmenu01`, `MODELCTRL`, `SQ_LINESL00`,
`ISSEQNAME`, `i_fadewn01`, `GENERATE`, `SQ_BLOUT30`, `ISRUN`, so the graphs are named targets of
`MODELCTRL … GENERATE <seq>` exactly like `j_startback`, which is why the recovered layout *is* the
title's rendering path.

## The title's two states

The title is not one screen. The `mojips.png` atlas (256×128) holds three zones (**"Press START
button"** at v 0.78…1.0, the **"Game Start" / "Option"** rows at v 0.62…0.78 and the copyright block
at v 0.1…0.45), and the game shows the two menu zones **mutually exclusively**:

- **press-start** (the boot state): `j_startlogo` (logo + copyright) plus `j_startmenu01`, the single
  `start` line = "Press START button" (UV v 0.758…0.984). No rows, no highlight.
- **menu** (after START): `j_startlogo` plus `j_startmenu02`, the `menu`/`null1` rows = "Game Start"
  (highlighted) / "Option" and the `select` highlight bar. The "Press START button" line is gone.

The game advances on the
pad's **START** (Cross skips the opening FMV instead).

The opening effect runs first, on its own; see *The opening: traces, a white flash, then the UI* below.

## Title input, skipping and the Option screen

The controller is documented in [title-menu-controller](title-menu-controller.md). Its press-start gate accepts START alone. Option edits change displayed working values immediately and commit camera/light
after closing; Circle accepts those changes.

- **The opening cannot be skipped** (retail behaviour, reported by the project owner). The
  title controller agrees: `beNDMWTitle2Ctrl` reads the START bit only in `_st0=1/_st1=2/_st2=1`, after
  `beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty` reports the open queue empty for the logo's and
  `j_startmenu01`'s `SQ_OPEN` starts, so no button is read earlier.
  The stage script agrees
  (`lua/00-title-menus/04-title-screen_e806/004-layer-setup-sq-open.lua`): it generates `j_startback`
  `SQ_OPEN`, waits for that sequence to finish, plays the white fade, and only then sends `TITLE2 RUN` (the
  controller's `_st0=0` gate) and `STAGECTL PADINPUT ENABLE 30`. Not yet confirmed by a live retail run. Presses during the blue-trace opening are ignored until `SQ_OPEN` ends and the
  "Press START button" screen is up. (The opening FMV before it remains
  skippable with Start or Cross.)
- **START opens the Game Start / Option rows** once the opening is over; before that
  START does nothing.
- **Option** opens the settings screen (captured from the real game). It is the pack's own graphs in `NDMW.AFS` entry 806:
  `j_optionwin02` (band, legend panel, pill bars A–D) and the cursor `j_optioncursor11/12`, played on the
  three-slot pass of their sequences, with the front-end font's glyph quads over them. Rows: **Dungeon camera**
  (Near / Far), **Light** (Hard / Soft; power-on defaults Near and **Hard**) and **Return to Menu**. Up/Down
  moves the cursor (it slides over 10 frames), Left/Right flips the highlighted value and applies at once,
  Circle (or Cross on Return) closes, Start does nothing, and the menu comes back on Game Start. A white flash and a
  logo fade run around open and close.

## Game Start: the slot screen and character creation (static map and live captures)

Game Start fades the title out (rows ~1 s, logo a beat later, then a white flash near 2 s) and the
four-panel **slot screen** assembles over a rotating grid dome. The live flow, captured from the
pristine disc:

| state | what is on screen | input |
| --- | --- | --- |
| slot screen | panels 1 red / 2 blue / 3 yellow / 4 green, the menu window anchored to panel 1 (`Create Digimon.` / `Call Digimon.`) | Up/Down moves the highlight (jumps, no slide); Cross opens |
| `Select a Digimon.` | portrait, name, ◀ ▶; four species: Dorumon, Agumon, Veemon, Guilmon (wraps) | Left/Right cycle, Cross confirm, Circle back to the slot screen |
| name entry | field, left mode column (`&` `A` `0` `a`), a five-key scrolling letter row | Left/Right move, Up/Down change mode, Cross types, Circle backspaces (cancels when empty), Start finishes |
| name confirm | `Do you want to assign this name?` then `Yes, assign this name.` / `No, change name.` | Cross, Down; Circle back to the name |
| created card | `Lv. 1`, `HP 170/170`, `MP 60/60`, the typed name and species; `To log into the Digital World press START` | Start loads the Main Lobby; Circle cancels |
| `Call Digimon.` | `Select a memory card (PS2) to call a Digimon.` (slots 1 and 2) then `This memory card (PS2) contains no Digimon World 4 game file.` | Cross, Circle |

Creating a Digimon writes nothing to the memory card. No memory-card prompt appears anywhere in the
flow, and the four panels have no per-slot highlight: the menu is always on slot 1. The d-pad works
in these menus.

**Where the art is.** The whole screen is pack **806**, the title pack the Option screen already
uses; the live game stays in stage `stagIS10` (read from `beSystem` at `0x006FF110`, name pointer
cell `0x006FF148`) through the slot screen, species list, name entry and created card, and the stage
name does not change between them. The Lua chunks of entries 808/810/812 only build the neighbouring
stages (`CFLclear`, font trees, flag-folder copies per difficulty, `i_fadewn01`); the
Create/Call/name logic is engine code. Packs 810 and 812 carry subsets of the same graphs; 808 is the
shop-card stage (`j_shcard00…50`, `j_shbase`, `j_shbooster`, `j_shback`).

Entry 806's scenes: `h_agumon`, `j_digiselcursorleft1`, `i_fadewn01`, `j_chrselbase1` (896 nodes),
the base scene graph, `i_messcr`, `entry` (the demo camera) and an unnamed 18-node scene. Its
attribute roots include `j_slotbase`, `j_slotcursor`, `j_slotmark01/02`, `j_chrselmesswin`,
`j_digifacewin`, `j_mainstatuswin`, `j_memoryiconwin`, `j_namewin01/02`, `j_namecursor01/02` and
`j_namecursor{up,down,left,right,jp,us}`, `j_digiselcursorright`, `j_linewin01/02/03`,
`j_saveareawin01…04`, `j_saveareacursorr`, `j_savecheckwin`, and the portrait heads `h_dorumon`,
`h_girumon` (Guilmon), `h_vmon` and `h_agumon`.

- Inside `j_chrselbase1`, `BG01` is the dome (a 3D camera `cameraanim01`, z 130, plus four
  geometries) and `GM01/M01` is the four panels: each a `Root` group of `bits`, `base`, `plug`,
  `base1`, `plug1` and `Pno` (the player digit), one group per slot.
- **Panel colour is the texture's CLUT, not vertex colour.** Each panel is one 333-vertex triangle
  strip (ALPHA `0x44`, textured, Gouraud) whose vertices are all neutral grey `0x7F7F7F80`; the four
  panels use four 32x32 8-bit textures that differ only in palette (TBP0 `0x3C2400/0x3C2C00/
  0x3C3400/0x3C3C00`, CLUT `0x3C280…0x3C400`). Rendered bodies: red (249,110,110), blue (32,150,231),
  yellow (253,253,48), green (0,253,7).
- The `h_*` portraits are `igActor` models, not flat cards.
- Menu windows use the same `beModelCtrlNode2` pattern as the Option screen: one node per sequence
  pass at 15-frame offsets.

**The four starter Digimon** are `beNDMWDegiData` objects (vtable `0x53C9A0`; the new one lands at
`0x0137C298`, stat block at +56): Dorumon `p_dorumon` 170 HP / 60 MP, Agumon `p_agumon` 180 / 50,
Veemon `p_vmon` 160 / 70, Guilmon `p_girumon` 150 / 80, all Lv 1 (HP + MP = 230 for each). The
`_id` word at +44 is a hash (`0x5AAA67E4`, `0xE5AB8488`, `0xECBB18CC`, `0x5BEEB640` in that order).

The panels' rest key is the first 1.167 s of their sequence; later keys
(`(100,10)` at 2.167 s, `(90,-100)` at 2.5 s) are the exit pass.

Not yet recovered: the state machine that picks the windows, and how the panel palettes are chosen.

## The opening: traces, a white flash, then the UI

The title does not come up at once. Immediately after the FMV the game plays an opening effect with
**no logo, no "Press START button" and no copyright**, and the title UI appears only once it has
finished. Watched live, frame by frame (a no-input boot):

| phase | what the screen shows |
| --- | --- |
| ~2.4 s | on **black**, thick glowing **blue circuit-trace lines are drawn progressively**: segments appear and extend into a ring decorated with runes, with traces radiating out to the screen edges |
| then | the pattern turns white with a bright flare in the centre |
| when `SQ_OPEN` ends | a **full-screen white flash**: the stage's Lua runs `MODELCTRL i_fadewn01 GENERATE SQ_WTIN60`, which is `beAction2FADESET OUT _fadeTime=60 _fadeValue=1.0` on the fade model's joint 45 (white at alpha 1.0 fading to 0 over 60 frames) |
| then | a solid 3D **tunnel of concentric rings** with a bright white core, seen head-on |
| at the same tick | the **title UI** (logo + "Press START button" + copyright) over the tunnel |

The capture cadence is the emulator's screenshot hotkey (~5.2 fps), so those times are the order and
a rough length, not frame-exact. The layer's `SQ_OPEN`
(`beAction2JOINTSET 0.0 → 209.0`, 60 fps, then `SQ_WAIT`; 3.48 s) covers the same stretch, and the UI
nodes stay degenerate (sequence scale 0, not drawn) until it elapses.

**The traces are `j_startback` geometry** (see the title layer
below): the ring and trace strips of that graph, not a separate graph or loader screen. Its animated parent
groups carry **no scale keys and no keyframe before t≈2.0 s**, so the layer is static for the opening's first two seconds. The flash is
`i_fadewn01`'s `SQ_WTIN60`,
*not* the layer's one-frame node 895 `group9`, which is a different thing in a different model.

`i_fadewn01` is a family of full-screen fade actions: joint 45 is the white node and joint 5 the black
node. `SQ_BLIN30` is `beAction2FADESET OUT` on joint 5 over 30 frames, the mirror of `SQ_WTIN60`. The
rest are the same pair at 0/30/60 frames (`BLOUT00/30/60`, `BLIN60`, `WTOUT00/60`), plus
`BHLFIN30`/`BHLFOUT30` at 20 frames.

The title stage's own Lua (`lua/00-title-menus/04-title-screen_e806/`) is the driver and should be
read before the controller: `004-layer-setup-sq-open.lua` runs `SQ_BLIN30` (the fade the title
fades in from), `SETDEMOCAMERA "entry"`, `j_startback GENERATE SQ_OPEN`, waits on
`ISSEQNAME SQ_OPEN ==0`, then `SQ_WTIN60` and `TITLE2 RUN`; `003-camera.lua` names the graphs the
stage loads (`FontTree DBBase mainstatuswin savecheckwin startback startlogo startmenu01
startmenu02`).

The controller block at `0x3f4d80` does generate `j_startlogo` with `SQ_OPEN`, wait on `0x3e4280`,
then issue `MODELCTRL j_startmenu01 ISRUN`, but which state enters that block, and whether it is
gated on the layer's action, is **not yet recovered**.

## What the front end depends on

1. **A stage/script sequencer**: a front-end entry's chunk set is loaded, the chunks run in order,
   and they drive that entry's scene stage pack plus its fade. The front-end entries are ordinary stage
   entries in the same loader the world stages use; there is no separate menu code path.
2. **The `be:` API subset the front-end uses**: `sd` / `DMsetSD` / `DMchkSD` / `DMrun`, `FLGset` /
   `FLGisOn` / `COUNTERset`, `SYSgetArea` / `SYSgetDifficulty` / `SYSctlFlagFolder`,
   `LISsetDifficultMax`, `CFLclear`, `MsgBox`.
3. **The scene content**: the logo/opening/title packs, the FMV (CRI Sofdec, `igCriMovieCodec`),
   and the title menu rows.
4. **The input gate**: the title's "Press START" state; in the recorded test the *pad*'s START does not
   reach PCSX2, so it has to be rebound.

## The title layer: `j_startback`

The front-end UI pack is **AREA.AFS entry 620**: `j_startback` (the trail/tunnel layer, scene 3),
`j_startlogo`, `j_startmenu01/02`, 5 `igSceneInfo`, 5914 records.

The layer's chain is `igSceneInfo` -> `igAttrSet` `BG02` (texture bind -> `igImage` `sback00.png`,
128x64) -> `igSwitch` -> `beModelCtrlNode2` -> `igAttrSet`s -> `igTransform` groups
(`group9/10/11/15`, `BASE05_1`) -> `igGeometry` meshes. The captured additive draws (TEX0
`0x400714059d30b880`) are RGB-identical to `sback00.png`. `SQ_OPEN` runs action `OPEN` then jumps to
`SQ_WAIT`, which runs `WAIT01`; the title Lua starts it with `MODELCTRL j_startback GENERATE SQ_OPEN`.

`j_startback` is a 3D scene drawn in perspective down its axis, not a screen-space layer. Its meshes
form a tunnel: `pCylinderShape3` has radius about 500 and spans z +4.5 to -3309, with rings at z about
15, -103, -1600 and -2128, and the animated node translations along z drive the expanding rings. An
orthographic or screen-space read collapses the meshes onto one ring. There is no joint instancing:
each mesh is drawn once, on its node's own clock.

`polySurfaceShape97`/`98` and `pCubeShape2` are the *thick circuit-trace line strips* and
`polySurfaceShape109` the *rune ring*: the pack has the trace art as geometry. `pCubeShape8` is a
413×413 camera-facing quad at z = −1200 whose four UVs are all (0.9844, 0.9219), a single texel.

The opening "traces on black" are the same `j_startback` ring + trace strips seen before the tunnel
panels join; they are not a separate loader screen.

### Keyframes

Keyframes for the layer live in `igTransformSequence1_5`, reached by `igTransform._transformInput`
(+0x68), not in any `beAction2*` or `beModelCtrl*` record. `igTransform::vfunc_29` (`0x1dd080`) is the
link. Entry 620 has no `igSkeleton`, `igSkin` or `igAnimation`: the "joints" are `j_startback`'s 23
animated `igTransform` nodes, which share 12 sequences. A sequence holds `_xlateList` +0x08
(`igVec3fList`), `_quatList` +0x0c (`igQuaternionfList`), `_scaleList` +0x10, `_startTime` +0x18 (-1.0),
`_timeListLong` +0x38 (`igLongList`, int64 ns) and `_drivenChannels` +0x48 (1 translate, 3 translate +
rotate, 8 scale, 9 translate + scale). The `_interpolationData*` and `_compressedDataObject` slots are
NULL, so values come from the base lists.

Channels are identified by descriptor slot, not read order: slot 2 translation (`igVec3fList`), slot 3
rotation (`igQuaternionfList`), slot 4 scale (`igVec3fList`), slot 11 times (`igLongList`). A node may
carry only one vec3 channel, and a missing scale channel does not mean scale 0. Where a layer node's
`_m` is a placeholder it equals the t=0 key.

| node | timeline |
| --- | --- |
| `group8` (the traces) | scale 1 until 2.500 s, (0,0,1) from 2.517 s |
| `group9` | (0,1,0) except one (1,1,1) key at 2.500 s |
| `group10`/`group11` | translate x 0 to -200/+200 over 2.583-3.000 s |
| `group15` | moves z 0 to 800 over 2.583-3.500 s |

4.000-6.000 s is the `SQ_WAIT` loop.

The layer's UV scroll is an `igTransform` with `_target=9`: its translation applies to texture
coordinates, not the model. Exactly 8 of the 299 transforms in entry 620 have it, the unnamed
`j_startback` nodes 875, 878, 881, 884, 887, 890, 899 and 902, each parent of one trace mesh. Node 902
has x keys -0.80 (0 s), -0.84 (1.983 s), -1.00 (2.0 s), -0.80 (2.333 s), and the stream's u offsets
fall on that segment. The behaviour is confirmed; the enum name and the meaning "texture matrix" are
inferred.

### The title camera

The title camera is the `entry` `beCameraCtrlInfo`/`igSceneInfo` in `NDMW.AFS` entry 806, selected by
`SETDEMOCAMERA "entry"`. Its `beCameraDemoData` (`_cameraPath`, `_endTime` 1e9 ns, `_totalSec` 1) walks
an `igGraphPath` through `animCamera01_60`, `cameraanim_GP1` (+600), `cameraanim_group01`,
`cameraanim01` (+130) and `igCamera` `cameraanimShape01`. All four chain transforms have
`_transformInput` NULL and a static `_m`, so `beCameraMode::vfunc_28` (`0x37a900`, via
`igGraphPath_GetTransform`/`FUN_001c59f0`) composes the same matrix at every time: an on-axis eye at (0,~0,730) with
about 0.04 degrees of tilt. It is not a dolly; `_totalSec` only runs `_nowTimeL` to its end and latches
`_isEnd`. `beCameraCtrl::vfunc_31` (`0x379c40`) selects the box path `beCameraCtrl_UpdateBoxCamera` or the demo path
`beCameraCtrl_UpdateDemoCamera`. The `stagML11` box camera is the wrong camera for this layer: it gives an off-axis arc.

### Render state in the pack

The pack carries the per-draw render state, so the layer's blend, alpha test and texture are
recoverable from data:

| record | value | meaning |
| --- | --- | --- |
| `igBlendFunctionAttr` A | `_src=4 _dst=1 _eq=0` | `Cs*As + Cd`, additive (GS ALPHA 0x48) |
| `igBlendFunctionAttr` B | `_src=4 _dst=5 _eq=0` | `(Cs-Cd)*As + Cd`, ordinary alpha (GS ALPHA 0x44) |
| `igAlphaFunctionAttr` | `_func=4 _refValue=0.6` | alpha test GREATER 0.6 |
| `igAlphaStateAttr` / `igBlendStateAttr` | `_enabled=1` | both on |
| `igLightingStateAttr` | `_enabled=0` | lighting **off**; entry 620 has no `igLightAttr` for the layer |
| `igMaterialAttr` | `_diffuse=[1,1,1,1] _ambient=[1,1,1,1]` | white, unlit |
| `igColorAttr` ×265 | `_color=[0.9, 0.9, 0.9, 0.95]` | on the **265 font attribute sets** (`font00`, `font01`, … `font000`…): the UI text tint. *Not* the layer: 265 of 301 `igAttrSet`s resolve one and all are `font*`; none of the layer's 16 meshes does |
| `igTextureAttr` ×12 | filter/wrap = 1 | `_image` → `sback00.png`, `logo.png`, `base*.png`, `moji*.png`, `cursor.png` |

`igShadeModelAttr _mode=1`, `igCullFaceAttr _enabled=0`, `igDepthStateAttr`, `igFogStateAttr` (one
enabled), `igTextureStateAttr`/`igTextureMatrixStateAttr` `_enabled=1`.

**Blend mode is per mesh**: an `igBlendFunctionAttr` (`_src` ordinal 4, `_dst` 5, `_eq` 6) in the mesh's
own or the nearest ancestor `igAttrSet`. In `j_startback`, nodes 867-891 (`pCubeShape8/4/7`,
`pCylinderShape4/2`, `pCubeShape2`, `polySurfaceShape98/97/109`) inherit record B (ordinary) and nodes
894-907 (`polySurfaceShape101`, `pCubeShape3`, `pCylinderShape8/7/6`, `polySurfaceShape104`) inherit
record A (additive). `pCylinderShape3`, the tunnel, has no blend attribute and draws ordinary; that
default comes from the capture, not engine code. This is also the draw order.

The layer's *shade* is not pack data, but the
pack does bind the blend/alpha/test state and **a texture per node**:
`sback00.png` for the layer's 16 meshes, `logo.png` for `polySurfaceShape2`, `mojips.png` for the
panels, `cursor.png` for the ticks.

### GS draw state

Each title colour buffer (FBP 0 and FBP 140) is preceded by its own full-screen clear: a SPRITE pass
under TEST 0x30000 (ATE off, ZTST ALWAYS), black RGBAQ, five XYZ3/XYZ2 pairs tiling 64-pixel columns
over 640x448, writing colour and Z=0. A 256-pixel CT32 target at FBP 419 is also cleared each frame.

- **Material.** The trace-phase material is textured and Gouraud. PRMODECONT.AC=0 in every measured
  dump, so the GIFtag PRIM supplies only the primitive type and PRMODE supplies the flags: 0x78 (IIP,
  TME, FGE, ABE) and 0x58 (IIP, TME, ABE). TEX0 `0x400714059d30b880` is PSMT8 128x64 at TBP0 0x388000
  with a CLUT; the title proper uses `0x40078005e1313b80` (PSMT8 256x128). COLCLAMP=1, DTHE=0. The
  saturated blue comes from the texture. Read ALPHA per draw from the ordered writes: the freeze-state
  value is left over from the previous frame's last draws.
- **Sampling.** The GS samples `j_startback` unmirrored, with REPEAT wrap (CLAMP WMS=WMT=0) and linear
  TEX1. Stream u minus pack u is exactly 0 for static meshes and a `_target=9` key value for scrolled
  ones, at one time. `pCylinderShape4`'s constant u = -1/128 needs REPEAT and a floor lookup. The
  trace-phase captures sit at layer clock 1.78-2.03 s, not t=0, so the look of 0-1.78 s has no capture
  behind it.
- **Far clip and depth.** The stream omits every primitive with a vertex beyond view depth 2048 (64 of
  `polySurfaceShape101`'s 112 quads). GS Z is about 6.57e5/depth - 329, clamped at 0, larger nearer (a
  fit), tested GEQUAL with ZMSK=0; this removes the thin `polySurfaceShape101` quads that are drawn.
- **Alpha test.** `igAlphaFunctionAttr _func=4` (GREATER), `_refValue` 0.6 on node 862 'New Object', an
  ancestor of `pCylinderShape3`, and 0.1 elsewhere (inferred from the stream); AREF = floor(ref*128) =
  76 / 12, applied as `(At*Av)>>7 > AREF`.
- **Fog.** The tunnel's fog is the GS fog stage, linear in view depth: F = floor(255*(2000-depth)/1900),
  clamped to 0..255 (near 100, far 2000), FOGCOL white, C = Cs*F/255 + FOGCOL*(1-F/255), applied after
  texture modulation and before blending. It fits all 160 distinct depth/F pairs of `pCylinderShape3`
  exactly; truncation fits and rounding does not. `igFogStateAttr _enabled=1` is on node 862 only and 0
  on BG02, PromotedAttr and WN01, which gives the stream's FGE split under nearest-ancestor lookup. The
  near/far values are not in this pack and were fitted from one scene.
- **Registration.** Stream y sits 0.873 px below the pure projection's centre at 448 lines (empirical, dx -0.03). Later
  tunnel phases and UI are unchecked against these rules.
- **Title UI.** The logo, Press START text, the five-quad translucent band and the copyright quad share
  one GS state: ALPHA 0x44, TEST GREATER AREF 12, TEX1 linear, REPEAT wrap, vertex colour
  (127,127,127,128) = 1.0 with no tint, not the 0.9/0.95 of the font sets. Pack palette alpha is 0..255
  where the GS holds 0..128, so every pack texture needs `(a+1)>>1`; without it partial alpha clamps to
  opaque.

### The trace phase

During the trace phase the bright tunnel is drawn and then covered: later ordinary-alpha draws in the
same frame paint over it. In the ordered stream one 1393-vertex batch (PRMODE 0x58, ALPHA 0x44) lowers
mean RGB from 152.8 to 11.9; forcing ALPHA 0x48 throughout gives 179.1 instead of the final 12.9. Do
not replace this with a mesh-name hide or a global blend toggle.

Stream draws are attributed to meshes by per-vertex UV-multiset coverage against the pack, because a
run of vertices sharing (TEX0, PRIM) is not one mesh and vertex counts do not identify geometry. In a
trace-phase frame the ALPHA 0x44 runs are `pCylinderShape3` (1217/1223, 357/421, 698/698), so the
tunnel is submitted; the covering batch is the ordinary meshes (`pCubeShape4` 196/196, `pCubeShape7`
181/181, `pCubeShape8` 4/4); the ALPHA 0x48 runs are `polySurfaceShape101`, `pCubeShape3` and
`pCylinderShape6`. The order matches the mesh order.

## Open questions

- **What starts the very first entry** (the power-on `menu-database` stage) is not pinned yet; the
  tail of the engine boot chain ([`engine-boot.md`](engine-boot.md)) is the candidate.
- The `0x30xxxxxx` addresses in `data/strings.json` for several of these names (`start.lua`,
  `stagIS10`, `beNDMWStageCtlInfo`, `gameStart.lua`, `NEXTSTAGE`) are a second image in the dump, not
  the ELF's `.data`; the ELF copies are the `0x0050…`/`0x0051…` ones cited above.
- Unproven: the layer's vertex colours look lit, as `min(1, ambient + diffuse * max(0, N.L))` in the GS
  0x80 domain. A fit over 4,494 stream vertices gives ambient (0.5, 0.5, 0.55), L = (0.297, 0.414,
  0.861) and diffuse about 1.5 x (1, 1, 0.875), RMS 17 levels. It is not recovered data: entry 620 has
  no `igLightAttr` for the layer, the diffuse rests on about 100 vertices and the light's space is
  unsettled.

## What didn't work

What does not hide the tunnel during the trace phase:

- **Alpha test.** GS MODULATE gives `min(0xff,(At*Av)>>7)`, so texture alpha 128 and vertex alpha 128
  give 128, which passes GREATER AREF 76 (dividing by 255 is wrong); this settles that texel value only,
  and real texels change the result slightly.
- **Depth.** The frame clears Z to 0 and GEQUAL rejects some fragments, but about 93 % of the covering
  batch is written.
- **Back-face culling.** All-or-nothing for a tube, wherever the eye sits on its axis.
- **Per-action appearance swap.** `j_startback`'s `beAction2Data` records carry only `_comList`, and
  `_overrideAttrList` is empty.
- **Undriven channels as scale 0.** Blackens the whole layer.
- **Off-screen placement.** Its X/Y bounds cover the screen.
- **Pose.** The stream's silhouette agrees with a render of the pack's pose at IoU 0.90.

Sampling the layer's texture u-mirrored only appeared to work, because of rendering at t=0 with clamped
lookups.
