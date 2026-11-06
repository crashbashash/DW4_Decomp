# The boot contract: one run, from power-on to playing the game

The target the port is being built towards, stated once so it can be worked towards deliberately:

> Running the port boots the game.  It plays the intro, gets into the menu, and from there you can
> create or call a Digimon and play the game as usual.

This page records what that means concretely, what the port does, and the work between the two. It
is written against the code, so each item names the file and the function that carries it and the
check that proves it. The subsystem documents linked from each section hold the evidence and the
detailed limits.

Private assets sit in the workspace sibling `local/` (`../../local/` from `port/`). The launcher
searches this location relative to its executable, including when launched from another working
directory.

## The target flow and its state

| # | The game does | The port |
|---|---|---|
| 1 | power-on, Bandai logo, attract | presents the original startup cards ([Startup cards](#startup-cards)) |
| 2 | the opening FMV (`aus_opening.sfd`, 64 s) | plays it, with its ADX soundtrack |
| 3 | the title screen: backdrop + logo + `Game Start` / `Option` + cursor, **waiting for input** | presents it from the game's own packs and waits for the pad ([Title screen](#title-screen)) |
| 4 | `Game Start` → character-select 1/2/3 | runs the slot screen: Create Digimon and Call Digimon ([Game Start](#game-start-create-and-call)) |
| 5 | create a Digimon (name, species, digivolution path) | runs the original create states and builds the fresh record |
| 6 | hand off into the Main Lobby: Terminal Area (`stagML11`) | loads it behind the original loading card and runs the original start/first scripts ([Created-card login and first arrival](#created-card-login-and-first-arrival)) |
| 7 | the player moves, fights, the world keeps running | runs the four hub worlds with their services, STATUS, travel and local co-op, and the field and dungeon stages that have a runtime ([Hubs](#connected-hubs-and-their-services)); the rest of the game is outstanding ([Open items](#open-items)) |

Normal created-card Main Lobby login uses the original start/first scripts and scene-owned
actor/player movement, collision, motion/opacity publication and restoration
([lobby gameplay](lobby-gameplay.md)). General gameplay beyond the stages named here and whole-frame
parity with retail are outstanding.

## Running the port

`dw4 --roms <dir>` (no other flag) boots the front-end and **stops at the title**, presenting it and
waiting for the pad; `--boot` is the same path explicitly, and `--headless` runs it offscreen (frames
to `--out-dir`). It walks the boot/attract chain and stops at the title:

      [0] entry 800 menu-database      NEXTSTAGE stagML11
      [1] entry 802 bandai-logo        NEXTSTAGE stagis09    scene stagis09
      [2] entry 804 opening            NEXTSTAGE stagis10    scene stagis10  FMV aus_opening.sfd
      [3] entry 806 title-screen       NEXTSTAGE stagML11    scene stagML11
                                       TITLE2 RUN, PADINPUT ENABLE 29, PLAY "AM_TITLE"
          title: menu rows 'Game Start' / 'Option' + cursor, waiting for input
          font: font00.png 512x512 atlas, 138 glyph(s) from bectext.igb
          backdrop: stagml11.igb [ref 0], 208 mesh(es), 24949 triangles
          dw4 front-end: stopped at the title, awaiting input  ok

- `dw4_frontend_boot` (`src/frontend.c`) runs only the boot chain (entries 800→806) and returns with
  the title menu installed; `dw4_frontend_game_start` runs the Game Start branch when the pad asks
  for it. `dw4_engine_boot` (`src/engine.c`) draws the title and runs the input loop.
- `--frames 0` (the default when a window presents) means **run until the window closes**; a headless
  run keeps a bounded frame count and exits on it. `--input-script` supplies a scripted pad for a
  headless run.
- `dw4 --skip-logos` bypasses the startup logo cards (entry 802) for testing, retaining the opening
  FMV (entry 804), menu-database and title initialization (800/806). The title opening animation and
  later attract playback retain their normal behavior. `DW4_SKIP_MOVIE` skips the FMV while retaining
  the startup cards.
- `engine_frame` (`FUN_0025a580`) advances the frame object once per presented frame and runs each
  frame in the title loop and the stage loop.

### Simulation pump and script runtime

The live title-to-lobby loop uses the 60 Hz simulation pump described in
[Lua integration](lua-integration.md#live-simulation-pump). DM precedes model adapters; manual pause
and assigned SDL-pad disconnect hold the script/service clocks, freeze their ticks and discard
host-time backlog.

- Title and Main Lobby prepare authored file lists, load original named chunks into Lua 4.0.1 and
  execute original `func.lua` and `boot.lua`, including their queued assets. First-use text/sound
  packs remain resident across scenes. See [Original Lua execution](lua-integration.md) for contracts
  and limits.
- Each scene VM executes its supported original events through DM. DM has controlled
  retail-instruction verification and runs before model updates. The title-to-lobby publication and
  attract return use SD → Lua → DM cleanup before releasing controllers, then load the destination's
  own library and helper definitions. Coordinated SD/Lua/DM teardown and fresh scene VMs are
  implemented. The engine wrapper and native flags/RNG persist across VM replacement.
- Session SOUND calls pass through a native receiver registry. Timed SD messages dispatch against the
  world clock before DM, with scoped cancellation before audio replacement. Selector and timer rules
  pass controlled retail instruction comparisons.
- Prepared title/lobby native infos and authored layer bindings gate receiver publication. Window
  commands, WPOS patrol consumers, SELECTCTRL and font services are implemented
  ([native scene objects](stage-objects.md)).
- Prepared scenes own MODELCTRL RAM slots, command-driven greeting windows and authored title/lobby
  camera completion state ([controller services](controller-services.md)). The common object-program
  service is integrated with the simulation pump. Prepared KIND_OBJECT slots bind persistent
  RAM/record/HP callback state with retail zero-max GENERATE initialization.
- The actor executor supports explicitly bound WPOS AIMAP selection and original waypoint callbacks
  ([actor sequences](actor-sequences.md#aimap-waypoint-acquisition)). WPOS patrol consumers and
  original message/choice helper services run natively ([dialogue services](dialogue-services.md)).
- The session script state owns the retail seed-5150 MT19937 stream. `SYSgetRandom`, model AI and
  attached Action2 waits share it; VM recreation preserves its position. Original rail-script branch
  tests and full-state retail instruction comparisons validate the binding
  ([Lua integration](lua-integration.md#shared-retail-random-stream)). Full gameplay draw frequency
  is unverified.
- The retail startup milestone API is implemented and tested.

The title's scene sequencing is still a bounded native adapter ([Title screen](#title-screen)). In
the lobby, normal boot runs the original scripts and the first-arrival adapter remains only for
standalone reference fixtures.

## Startup cards

Windowed boot and attract display Bandai, Intrinsic Alchemy, then Sofdec/ADX before the movie, in the
same window. `frontend.c` presents the `j_bandailogo` graph from the US `aus_pack.igb`
(`AREA.AFS 600`) and the `j_rating` subtree from `NDMW.AFS 802` using `frontui.c`'s original
mesh/material renderer. Despite its name, `j_rating` contains middleware logos, not an ESRB card.
The model's action data supplies OPEN/CLOSE waits (15 ticks), 30-tick fades, 150-tick holds, and
rating JOINTSET samples 10/20 separated by 30 hidden ticks. The startup presentation lasts 12 seconds
at 60 Hz. Closing the window stops boot; headless checks only sequence the stage.

This is a native adapter for these action schedules, not general execution of the logo stage's Lua
or memory-card dialogs. `make check-bootcards` checks the original assets, distinct visible cards,
and fully hidden alpha; optional test output captures all three cards for inspection.

## Title screen

The title frame is drawn in `dw4_engine_boot` (`src/engine.c`) in the game's own composition order:
the static `stagML11` backdrop through the recovered title camera, the generated
additive `j_startback` trail, then the recovered UI tree over both. The dark field and the game-font
rows remain only as the fallback when the pack graphs are unavailable.

**Two states (`src/frontui.c`).** The title boots to the **press-start** screen (logo +
copyright + the "Press START button" line, the `j_startmenu01` graph) and only **START** advances to
the **"Game Start" / "Option"** rows (`j_startmenu02`); Cross confirms once inside the menu. Before
the UI draws at all, the `j_startback` layer's `SQ_OPEN` plays **alone** — the game shows no title UI
until its 209-frame opening (3.48 s) has finished, so the UI's clock is offset by
`dw4_frontlayer_open_ns()` and its nodes stay degenerate until then.

**Controller.** The title/Options input loop uses the imported recovered controller; see
[the integration record](title-controller.md) for the model backend and remaining limits. Named title
MODELCTRL receivers and the static entry CAMERA expose native state; lobby publication replaces them
with queries for the five rendered greeting models. Original title `first.lua`
completes against model/camera state in integration checks, while the live title scene orchestration
is the bounded adapter.

**Trail layer (`src/frontlayer.c`).** The backdrop's animated additive layer
is generated from the pack's own model controller. `src/frontlayer.c` loads `AREA.AFS` entry 620's
`j_startback` graph and its `sback00` texture (its 8 bpp `igImage` grid through the `igClut` its
`_pClut` names) and plays the scripted schedule: `SQ_OPEN` frames `0…209` one-shot, then `SQ_WAIT`
frames `240…360` looping (`beAction2JOINTSET` is a *time range* with a loop mode, not a
joint count). It recomputes each animated `igTransform` node's time from the host's 60 fps engine
clock (`_time = ((int64)(_timeScale*(engineTime>>18)))<<18 + _timeBias`), then draws
the graph's 16 `igGeometry` meshes / 3184 triangles once each additively in a
perspective screen space. The layer moves every frame and needs nothing but the game's assets.
`sback00.png` is a 128x64 byte-per-pixel grid (`_imageSize` 8192) read through a 256-entry palette with
RGBA in the four entry bytes, not the texture packs' layout; decoded this way it reproduces the game's
uploaded `sback00` texture pixel for pixel.

**UI tree (`src/frontui.c`).** The logo, the copyright block and the rows
are pack data, not hand-placed. `src/frontui.c` loads `AREA.AFS` entry 620's `j_startlogo` /
`j_startmenu01` / `j_startmenu02` graphs through the shared `dw4_scene`, resolves each geometry
node's mesh and its material texture through the pack's own chain (`igAttrSet._attributes` →
`igAttrList` → `igTextureBindAttr._texture` → `igTextureAttr._image` → `igImage`/`igClut`), decodes
`logo.png`/`mojips.png`/`cursor.png` from the arena and draws the quads in the recovered screen-space
(one unit = one pixel in a 640x448 space, +y up, `z` as painter depth). It draws `j_startlogo`'s
`rogo`/`kenri` and the `j_startmenu01`/`02` rows and plays their recovered `beAction2`
opening/selection/closing schedule on the engine clock. `src/scene.c` carries the two
resolution passes (`add_materials`, `link_nodes`) and the inline-image table.

**Text (`src/fefont.c`).** The game's own font is decoded from `bectext.igb` on the disc — the
`font00.png` 512x512 grid + its linear `igClut` + the NORMAL `igCharMetricsList` (484 glyphs) — and
drawn through the renderer's glyph primitive. For the title rows it is the fallback text path.

**Audio.** FMVs include their ADX soundtrack. Title and character creation play original music and
menu cues through the [native audio adapter](audio-playback.md). Title entrance audio runs original
`snd_j_startback.lua` through the session DM queue and native sound binding. Lobby music/ambience
start on arrival and the terminal beep plays. Exact retail sound-event scheduling/mixing and general
gameplay sound parity are outstanding (field stages prepare their stage catalogue; see the audio
notes).

**Not recovered.** The backdrop's engine-runtime tone: `stagml11.igb` carries no
lights/colours/textures, so a labelled placeholder tint remains.

**No capture replay.** The front-end needs no analysis artefact: there is no capture directory, no
captured texture and no `--menu-*` flag or `$DW4_MENU_*` variable. `src/uireplay.c` stays only for
`dw4asset`'s analysis paths (`--ui/--ui-only/--ui-seq`). The asset root stays a parameter (a port
needs the game's data). The bright panel under the logo is in the original game too (the same region
of `boot-09-main-menu-game-start.png` and of a layer-only render both hold a ~100 px-wide, ~30-row
run of >235); the game's white rows sit inside a wide dark band that covers the panel's lower half,
so an exposed white rectangle there is a composition error, not a decode or blend bug.

**Proved by** `tools/verify_frontend.py` (in `make -C port check`): the boot stops at the title (no
`entering the first playable stage` line without input), the font decodes, the generated layer
resolves with no flag (`front-end layer: j_startback, 16 mesh(es)`), the recovered UI tree resolves
(`front-end UI: N item(s), ... logo=logo.png`) and its logo quad's rectangle matches the recovered
640x448 placement to ±0.5 px, and a title frame is written; a second run asserts the layer animates
every frame (first ≠ last over four seconds) and composes at 640x480.

## Input

- `dw4_window_pump` (`src/window.c`) decodes keyboard and SDL gamepad events into `dw4_input_state`
  (`src/input.c`), which applies the game's own mapping — **Cross = confirm/attack, Circle =
  cancel/jump, Square = guard, L1 = item window, R1 = MP technique, R2 = status effects, Start =
  status screen**.
- The host accepts D-pad and keyboard arrows for menus, alongside the retail analogue navigation,
  sharing the stick navigation edge/repeat behavior. Retail's pad D-pad moves menu cursors but never
  the player (measured), so the pad D-pad (`DW4_BTN_DPAD_*`) feeds `dw4_input_menu_axes` only, while
  keyboard arrows (a PC control) and the stick also feed `dw4_input_walk_axes`. Held digital
  directions override both stick axes to suppress drift; opposite directions cancel.
- `SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS=1` is set before `SDL_Init`: SDL otherwise drops pad
  events while the window has no input focus, which is the normal state of a port window under a
  compositor, and the pad is silently dead.
- `src/host.c` implements the seam's controller side: `igPsx2Controller` (2 field(s)) and
  `igPsx2ControllerManager` (1) are `DW4_IF_INPUT`, filled from a real pad source. The seam table
  holds 1 implemented interface, 2 input interfaces and 28 stubs
  ([Platform seam](#platform-seam)).
- **Proved by** `tools/verify_frontend.py`: a scripted pad (`--input-script 5:cross`) reaches the
  title, presses Cross on `Game Start`, opens Create Digimon, cycles the four species, and cancels
  back to the slots. It also verifies that incomplete creation cannot enter the lobby.

Pads 2-4 are described under [Local co-op in the hubs](#local-co-op-in-the-hubs-and-the-pads-of-players-2-4).

## Game Start: Create and Call

Cross on `Game Start` opens the slot screen.

**With a save library**, the slot screen is the hosted `stagIS13` scene for both rows, running the
original `LoadIntf2` states: the Create/Call window, Create's starter choice (control state 4), the
`NameSel` name entry (state 5, retail key rows) and state 8's GAMESTART and log-in prompt; Call runs
its card chooser, data select, difficulty window and log-in prompt there too. The engine rebuilds the
created or called record in the session
([Save Keeper](save-keeper.md#creating-a-character-on-the-title-port)).

**Without a save library**, the character UI (`src/frontchr.c`) is the fallback. It also draws the
starter's 3D preview for the scene and the created card after a failed load. Its flow:

- **Species previews.** Game Start opens the four panels over `BG02`. Left/Right cycles the four
  species with wraparound; each draws its native `waitC` skeletal idle through the pack's
  camera/viewport and enabled light rig. Integer-scaled depth prevents hidden surfaces from
  overwriting faces. See the
  [implementation and remaining limits](../README.md#create-digimon-species-screen).
- **Naming.** Cross on a species opens the original keyboard frame; directions select keys/modes,
  Cross types, Circle backspaces or cancels when empty. Start opens the question, Cross opens Yes/No,
  No preserves the edit, and Yes creates a name/species summary. Only Start on that summary enters
  the lobby. The caller retains the creation result (name/species) across loading.

Shared by both paths:

- **Messages.** Create/Call, species, naming, question/Yes/No and created-card messages execute
  `txt_mem.lua`, retaining original localized Unicode and authored fonts. Thirteen retail glyph
  comparisons pass.
- **Created summary.** Original localized label quads and authored MINIMUM-font rows; two retail
  foreground comparisons pass. Character naming and created-card START prompts use the original
  NORMAL-font glyph 8869 (the shaded START triangle).
- **Fresh name and stats.** Created-card login publishes one eight-code PLAYERNAME object,
  current/base stats and all three starter weapon sockets from authored databases. Retail US
  conversion filters unsupported punctuation; 16 creation paths and 624 scalar results match
  controlled retail checks ([player records](player-records.md#fresh-character-name-and-stats)).
  Fresh characters include empty equipment arrays, native identity references and fresh
  disk/card/bank/flag records with the common aliases.

## Created-card login and first arrival

**Closing transition.** The boot window stays alive through loading. The caller-owned creation
record retains name/species; inputs are ignored during CLOSE. Start on the created card runs a locked
CLOSE transition: `src/frontchr.c` drives NDMW 806 `j_chrselbase` CLOSE: joint frames 70..100,
WAITCHECK 30, OUT fade 30, joint frames 101..130, WAITCHECK 30. Its final black frame is presented
before `src/engine.c` opens the lobby. Naming/card overlays are hidden during this interval. M01
contains an original orthographic projection (horizontal scale 0.003125); discarding transformed Z
there alone does not prove that perspective is missing. BG02 is a separate perspective layer. The
adapter drives the panel sequences together and retains the background loop. The full dome recession
and controller scope are not compared against the transition captures.

**Loading card.** The original USA `loadingUSA/ldagml11.igb` scene (AREA 1321) is presented before
lobby preparation. Its stage preview/name, cover effects and moving bands use the asset geometry and
recovered loading-node clock. Loading samples also present during live catch-up, so the reveal cannot
be consumed offscreen. Successful publication waits for the authored play-limit predicate and
presents the original lock sample. Windowed preparation runs on a CPU worker while the boot loop
remains responsive; failures offer Retry/Back and preserve the created card. See
[stage loading](stage-loading.md) for ownership, headless timing and the remaining retail
visual-parity boundary.

**Destination.** The first hub is `stagml11`, model pack 820: its flag-500 arrival uses `camsp0101`,
female Digi-Elf instance 1 and messages 39..53. `stagml02` (commander room, model pack 816) and its
flag-501 greeting are not the first arrival; the checks reject ML02, `camsp0201` and greeting 281.

**Environment (`src/lobby.c`).** It opens `stagml11.igb` reference **0** (NDMW 820); reference 1 is
sound pack 819. It selects BG02's 111 meshes, `camsp0101`, and 18 named world textures from scoped
NDMW 821/822. `beTextureCtrlAttr` supplies a name and exact attribute-set target where
`igTextureBindAttr._texture` is NULL. Every graph occurrence of that target receives the binding;
meshes inherit through their own material ancestry. Pack 820's controller at 0x217f4 targets attr-set
14185 with `ML01GR00_n.png`. The canonical IGB id/pool map supplies palette/index data.

**Camera and presentation.** Camera demo data 1800 declares four seconds. Its degree-Euler sequence
runs to 240 ticks then holds. Euler handling is explicitly enabled only for the arrival graph,
preserving established frontend quaternion behavior. The lobby computes inverse-camera translation
with the inverse rotation's columns. The generated portal controllers run recovered default/off,
rise, active and fall Action2 programs. The bounded presentation supports instance visibility,
projective actor shadows, asset-driven entry/screen fades and clipped GS-grid geometry. BG02 has no
transform sequences. Authored switch masks and skin/LOD visibility are implemented; general
progression-driven portal dispatch is a separate runtime workstream. Recovery evidence, validation
and the remaining retail frame-parity limits are in [lobby rendering](lobby-rendering.md).

**Scripts.** Normal created-card login executes the prepared lobby's original `start.lua` and
`first.lua` ([lobby gameplay](lobby-gameplay.md)); the scene-owned executor runs the original
Digi-Elf arrival movement/action/label programs with controlled retail trace validation
([actor sequence services](actor-sequences.md)). The live session executes original WPos bytecode and
shared-stream MAP01 choices for continued patrol; full model sequence/update timing is bounded
([model callbacks](lua-integration.md#model-callbacks-and-native-rng-consumers)).

**First-arrival adapter.** The bounded adapter, used by standalone reference fixtures, follows
`lua/01-lobby-hub/05-lobby-quests_e820/042-layer-setup-2.lua` (flag 500), without executing malformed
decompiled loops:

- It reads the first bePoint01 spawn transform from switch 8839 (bePoint01Info's `_switch` field),
  loads the selected species' authored near LOD and schedules SQ_ENTR at tick 180, with its 50-tick
  fade, three rings and delayed star particles. The independent low skin casts the player's
  projective shadow.
- The original species/weapon databases select the first starter model, whose `slash` branch resolves
  to `waitS`. Its textured graph follows the animated `RArm04` attachment bone and shares the entry
  fade; see [player appearance evidence and comparison](lobby-rendering.md#player-starter-appearance).
- It loads both male and female Digi-Elf skins with their walk01/wait01/talk01 motions. The female
  guide starts at 60/10/-10, yaw 117; the second female at 63.12/10/-55.8, yaw 78.8; the male at
  69.11/10/-13.79, yaw -90.
- The opening talk/wait schedule is generated from original Lua bytecode, with its correct
  signed-integer bias (20/50/60/100/110/160/180/190/210/220). After the camera, the guide's WALK02 and
  male's WALK03 run independent accelerated movement and timed rotation/braking channels. The male
  starts 20 ticks after the camera and uses his own DELAY02 (18), followed by walking. MOVE/Stop
  parameters and actor-specific Action2 wait durations load from the stage pack; the greeting follows
  the guide's completed 65-frame walk action. The second female continues walking throughout
  dialogue. Authored wall/floor triangles constrain all three routes. Ten ticks after the final
  window closes, the male and second female relocate to their scripted placements with zero residual
  movement. See [choreography and validation](lobby-choreography.md) for recovered arithmetic,
  original-bytecode evidence and collision boundaries.
- The guide immediately resumes the first WALKON departure leg toward the original `(20,10,-35)`
  waypoint, with asset-driven turn limiting, accelerated walking and braking inside the authored
  arrival radius.

**Greeting.** Original UTF-16 messages `mswk67051`..`mswk67065` load from AREA 674 `usa_pack.igb`.
Groups are TALKFONT02 39..41, 42..46, 47..48, TALKFONT01 49..50, then TALKFONT02 51..53. The script's
beep/DELAY01 blocks input for 90 ticks before the terminal announcement (the original `mlBEEP01` plays
at the start of this wait). The [greeting UI](lobby-greeting-ui.md) draws the original `i_talkwn` and
`i_messwn` windows, Digi-Elf portrait, NORMAL body font and yellow MINIMUM speaker font with
disc-backed layouts. All five page groups close and reopen their windows; text and Cross input wait
for opening completion and the greeting accepts Cross edges. The final 120-tick delay starts when the
last window closes. Exact messenger/selector dispatcher latency and the animated bottom decoration's
retail phase are unverified.

**Control handoff.** On the 120th simulation tick after the final close, both HUD-layer eligibility
gates are restored, the single player's original status panels are published, the camera switches
from the held demo to the authored box-camera rig, player/model control eligibility is enabled, the
equipped idle restarts for `PLAYER SQ_WAIT`, and per-tick MATCTRL membership queries resume. The
transition happens once, independently of draws or held Cross input. See
[control handoff](lobby-choreography.md#control-handoff) for data, checks and remaining fidelity
limits. The lobby then supports player walking/jumping and bounded collision, gate proximity
animations and heal activation ([lobby gameplay](lobby-gameplay.md)).

**Checks.** `make -C port check` asserts the Terminal Area destination and ordered model/sound refs,
target-14185 binding and distinct inherited materials, all four player assets, messages 39..53 with
the 90-tick announcement wait and final 120-tick delay. The 880-frame frontend test checks name
retention, input edges, a black frame before loading, textured arrival, and rejects
ML02/camsp0201/old greeting 281. The four-species test passes AddressSanitizer and
UndefinedBehaviorSanitizer with leak detection disabled. Optional live checks skip without the
required environment.

## Live STATUS integration

Start opens the complete native STATUS tree after the lobby introduction, through its scene-owned
SUBWND factory. Window/model clocks continue while the lobby world and active model clocks hold.
Original authored panels, fonts and selectors render over the world; scene publication enables its
native layers and clears LOADING. Actual root completion restores sound/model/world eligibility and
publishes current player health into authored HUD meters/numbers.

What the tree is built from:

- **Owner and lifecycle.** Prepared SUBWND slots have a native owner and verified
  GENERATE/REMOVE/ISRUN plus recursive window-tree lifecycle. Session-owned folders and record-backed
  identity/weapon queries persist across VM recreation ([player records](player-records.md)). The
  resume point and verification limits are in [status/menu ownership](status-menu.md).
- **Views.** Title00–04/Select00 initialization and owned model/font lifetimes execute through native
  controllers and original `txt_status.lua`. Scoped text callbacks provide retail TXTgetCallNo
  behavior. Real selection confirmation/cancellation and model close waits pass native integration
  checks; 172 view initialization traces match retail. Title01 stat refresh/preview use native typed
  records and authored fonts; 96 UPDATE and 192 preview retail cases match. Prepared shinka NAME and
  all four production initial name/stat records reach authored fonts
  ([concrete STATUS views](status-views.md)).
- **Records and transactions.** Staged commits and private previews, CTRLITEM DEVICE operations and
  CURRENT2BASE persistence pass retail instruction comparisons. Production
  [stat/technique recalculation](player-stats.md) supports those transactions and fresh creation,
  with production database item attributes ([player transactions](player-transactions.md)).
- **Submenus.** Equipment/folder/skill orchestration and scene freeze/entry/restoration ordering have
  owned native callbacks and retail checks. Authored Select01/SelectE0/SelectE1, shared
  equipment-base orchestration and accepted transaction IO are available. Concrete equipment,
  DEVICE, skill, DEVICE-detail and important-item owners are implemented with the validation
  boundaries in [STATUS submenus](status-submenus.md).
- **FOLDER tree.** The complete owned FOLDER tree routes DEVICE/detail, DISK, important items and
  currency transfer through authored resources/selectors and production records. Currency/disk cap
  and cancellation checks pass with atomic transfer publication
  ([ownership boundaries](status-submenus.md#complete-folder-ownership)).
- **Root.** The complete authored tree opens and closes for every player slot in prepared
  original-asset checks, including all three equipment children and retained root/equipment
  selections. Actual root, model and child completion drive its lifecycle
  ([root assembly](status-submenus.md#complete-status-root-assembly)).
- **Bindings.** Typed GAMERAM/DATABASE object-return bindings, fresh disk/card/bank/flag records and
  the owned equipment, DEVICE, DISK, important-item, currency and skill trees are connected.

**Rendering.** Normal STATUS model/font rasterization uses a session-owned persistent GPU renderer,
including when Vulkan presents the host framebuffer. GPU preparation or draw failures are reported
explicitly without STATUS CPU fallback. Explicit software/headless reference runs retain the CPU
oracle.

**Validation.** The normal-boot route exercises equipment, DEVICE and skill views, then closes and
reopens STATUS. Runtime checks reject restoration if world/material/camera/NPC/AI state advanced
during the hold. Live SDL controller and keyboard routes pass three open/close cycles. Shared-window
durations and observed retail root-state order have measured comparisons. Seventeen settled-menu
submission comparisons and five actual live opening-frame submission pairs pass. Prepared transfer
and outer-lifecycle comparisons pass; prepared menu trees retain four-slot coverage.

**Owner by pad.** `dw4_hubruntime_input` is pad 1 and `dw4_hubruntime_input_slot` pads 2-4; each
slot's pad words reach the dialogue owner and the status-page trackers, the talk probe's shooter is
the pressing slot, the R1 technique panel is per slot, and STATUS/shops run on the owner named in the
SUBWND payload (`I<player>`) and read only that pad
([floors](dungeon-floors.md#pads-2-4-talk-selectors-technique-panel-status),
[owner](status-menu.md#owner-by-player-slot)). That Start on pad N sends `STATUS/I<N>` is an
unconfirmed assumption. The interface scenes open one player. A dungeon floor opens STATUS on Start
(`check-fieldstage-startmenu`, `dng101b1`); the practice stage has none.

**Not verified.** Complete transition and pixel parity, physical input/audio and live co-op,
including an actual live co-op transfer. This integration does not establish retail full-frame parity or complete gameplay.

## GPU policy of normal boot

Normal windowed or explicitly requested GL boot selects the hardware-required policy; explicit
software runs, or headless runs without GL, retain diagnostic mode. The GLES probe rejects
software/unsupported renderer labels before startup, and the common
UI/title-trail/character-background/lobby error branches stop with an explicit error instead of CPU
fallback.

- The normal boot's title backdrop, main/loading/card clears, primitive fades, legacy font batches
  and FPS bitmap/plate use GPU operations. Startup/loading card owners use GPU passes. The mesh
  backend preserves caller EGL/SDL contexts and peer display lifetime, owns its readback buffer and
  supports the reference Gouraud mode.
- Movie FPS, complete startup cards/movie handoff, automatic stage GPU rendering and hardware
  SDL/Vulkan presentation satisfy the normal graphics policy. Normal Vulkan resizing is GPU work;
  channel packing remains a byte transfer. The character closing fade uses exact GPU integer
  division.
- Required-mode CPU pixel calls are blocked before writes, and GPU/presentation errors reach failed
  entry exits. Direct CPU raster/composite calls are audited by `DW4_GPU_POLICY_TRACE`. Explicit
  software/headless/dummy test routes retain their stated reference/transport roles.
- The 300-frame title comparison and three-cycle live route with FPS pass with zero CPU drawing
  counters. All normal hardware acceptance routes report zero CPU drawing calls; see
  [the final audit](gpu-rendering.md#normal-path-audit) and
  [GPU rendering](gpu-rendering.md).

This closes graphics execution paths, not the complete-game or platform release.

## Connected hubs and their services

The normal engine consumes the original Terminal/Central/Shop exits, retains the source while a
destination worker loads behind original USA stage cards, and routes the published session to its
private original-script runtime. Loading holds session clocks, and failure Retry/Back preserves the
source records. All six application routes with original choices/STATUS, initial-source Retry/Back,
confirmed in-flight shutdown, a headless GPU two-transfer run and later-source sanitizer recovery
pass. See the [hub travel contract](hub-travel.md) and [task handoff](project/tasks.md).

Running in the hubs:

- live Cross NPC interaction ([NPC interactions](npc-interactions.md));
- Central's XDATA stat and chip services ([XDATA shop](xdata-shop.md)), NPC bank
  ([NPC bank](bank-shop.md)), NPC appraiser ([NPC appraiser](cnos-shop.md)), Digi-Lab
  ([Digi-Lab](labo-shop.md)) and the disk-collector Prmame with the native
  `SYSctlDiskFolder`/`SYSctlDeviceFolder` services ([Prmame](prmame-npc.md));
- the Shop's disk shop ([Digi-Disk shop](disk-shop.md)) and its weapon, armor, chip and junk shops
  ([equipment shops](equipment-shops.md));
- the Save Keeper's `stagIS12` save screen, the `stagIS13` load/join screen and the `stagIS11` card
  album as hosted scenes ([Save Keeper](save-keeper.md)). The save screen writes the character to the
  native save library.

The Terminal's gates reach the Commander Room and the field and dungeon stages that have a runtime;
a stage without one shows "Destination not available" and returns to the source
([hub travel](hub-travel.md), [combat](combat.md), [dungeon floors](dungeon-floors.md)).

## Local co-op in the hubs and the pads of players 2-4

The destination runtime opens the four hub worlds (`stagML11`, `stagML12`, `stagML13`, `stagML02`)
for a party of 2-4 (`dw4_hubruntime_prepare`; the digivolution demo and the interface scenes still
need the single player-zero owner), and the Humid Cave route continues through its exit into the
Terminal.

The engine feeds the pads of players 2-4 to the hub: `dw4/pads.h` opens the controllers after the
first one, `dw4_window_pump_mates` / `dw4_vk_pump_mates` fill one `dw4_input_state` per mate while a
hub runs, and `dw4_hubruntime_input_mates` applies them through `dw4_hubruntime_input_slot` (walk
stick, jump, Cross swing; on this engine path the menus, shops, STATUS and the technique panel stay
on pad 1). The per-slot Start and R1 handling of `dw4_hubruntime_input_slot` is exercised only by the
checks.

The engine has no party source of its own: a party exists once the main-menu join or a load puts
NINZU above 1 in the records, so the pad path is validated headless (`check-hubstages`), not in a
physical multi-pad run. The details, the tests and the open list are in
[dungeon floors](dungeon-floors.md#local-co-op-in-the-hubs).

**Hub HUD of a party.** A hub with NINZU 1 keeps the single-player lobby HUD (`lobbyui`, verified
against retail frames). With NINZU 2-4 (`hubruntime` `party_hud`) the lobby HUD draws nothing
(`dw4_lobby_party_hud`) and the five panels `i_stpnl00..04` that the chunks' own
`funcPlayerStatusGenerate` generates (one set per joined slot at x = -260, -110, 40, 190, y = -160)
draw in the model view (`dw4_modelview_open_field`, as a field world's) with the stage pack's gauges
and plates (`dw4_fieldhud_open` reads `hpmt1..4`/`mpmt1..4` and `lvnm/hpnm/mpnm1..4` from the hub
packs unchanged). Each tick the slots' LEVEL/HP/MP/MHP/MMP records drive the number plates and the
HP/MP meter targets; the panels follow the lobby HUD's state (hidden until its restore and while a
message window is open: `dw4_modelview_hide_hud`). `i_stpnl06`, which the same chunks also generate
once per joined player, is the point-message band, not a player panel. Details and open points:
[dungeon floors](dungeon-floors.md#the-hub-hud-of-a-party).

## Platform seam

`src/host.c` lists the `igPsx2*` classes behind the generic interfaces: 1 implemented (`igPsx2File`),
2 input (the controller pair) and 28 stubs. The stubs the game's own systems need to run:

- `igPsx2VisualContext` (28 fields — the render-side context);
- the `igPsx2VertexArray*`/`igPsx2VertexStream` family (the geometry the game submits);
- `igPsx2Thread`/`igPsx2ThreadManager` (10 + 2);
- `igPsx2Audio*` for sound.

## Rules for this contract

* **The analysis tools stay analysis tools.**  `dw4asset render/scene/models/records/...` is how the
  decompilation is verified; the game must never depend on them.  A feature that only exists behind
  `dw4asset` is not part of running the port.
* **Change the boot contract deliberately.**  `tools/verify_frontend.py` (in `make -C port check`)
  asserts the flow (the boot stops at the title; a scripted Cross advances). When the flow changes,
  the check moves with the code in the same commit and is not worked around.
* **Environment-neutral text.**  The repo is read on GitHub and cloned onto machines that resemble
  this one in no way; reference the project tree relatively and leave host detail out.
* Never write the pristine disc image.  Patch a copy.

## Open items

Flow:

- **Startup.** The startup cards are an adapter for the action schedules; the logo stage's Lua and
  the memory-card dialogs are not executed.
- **Title.** The live title scene orchestration is a bounded adapter. The backdrop's engine-runtime
  tone is a placeholder tint.
- **Character menus.** Upper dynamic fields, cursor/message/transition work and complete
  controller/transition equivalence of the character screens
  ([main-menu fidelity](main-menu-fidelity.md)); complete retail exit/arrival equivalence of the
  created-card login; the dome recession of the closing transition against the captures.
- **Arrival.** Full model sequence/update timing is bounded; messenger/selector dispatcher latency
  and the bottom decoration's phase are unverified; general progression-driven portal dispatch;
  retail comparison and real window/pad tests of the arrival.
- **Run loop.** A headless run exits on a frame count, not on the game's own tick.
- **The playable world.** Field and dungeon stages without a runtime, and with them the rest of the
  game's progression, content and whole-frame parity.

Systems:

- **Platform seam.** The stubs listed under [Platform seam](#platform-seam).
- **Audio.** Exact retail sound-event scheduling/mixing and general gameplay sound parity.
- **STATUS.** Transition and pixel parity, physical input/audio, a live co-op transfer, and whether
  Start on pad N sends `STATUS/I<N>`.
- **Co-op.** A party source in the engine, a physical multi-pad run, and a party in the digivolution
  demo and the interface scenes.
- **Random stream.** Full gameplay draw frequency.

Known warts:

- The default output directory is the current directory, so an exploratory `--frames` run drops
  `frame_*.png` into the repo root — hundreds of megabytes of it.  `--out-dir` should default to a
  scratch location, or the run should refuse to write without one.
- `--spin` defaults to 8°/frame in the standalone diagnostic stage path. The booted lobby uses its
  own recovered arrival camera and does not use that diagnostic rotation.

## Definition of done

One command, no analysis tool, no hand-placed flags: `dw4 --roms <dir>` opens a window that shows
the intro, then the title menu, accepts input, follows `Game Start` into character creation, and
lands in the Main Lobby with the player in control — with `make check` green and the boot contract's
check asserting the flow.
