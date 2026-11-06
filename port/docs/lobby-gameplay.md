# Main Lobby movement and original startup

Normal created-card login executes the prepared Main Lobby's original `start.lua` and
`first.lua`. The first-arrival adapter remains for explicitly selected standalone reference
fixtures; normal boot does not use its NPC, greeting or restoration schedule. This page covers
the created first player in the Main Lobby and the hub behaviour that shares its lobby code
(labels, gate pads, NPC talk). It is not combat, saving, local co-op or arbitrary-stage
acceptance. Rendering is in [Main Lobby arrival rendering](lobby-rendering.md); travel between
hubs is in [hub travel](hub-travel.md).

## Startup and ownership

The file-list owner completes original func/boot collection, asset routing and layer binding
before startup. The session installs player, camera, model, window, dialogue, material and light
consumers before `start.lua`; `first.lua` then publishes the original DM groups. Stage input uses
the shared PADINPUT owner. The compatible Lua 4 runtime executes the original bytes, not the
prose decompilation or a generated arrival schedule.

Ordinary FLG reads/writes use the common record's FLAG view, which aliases player zero's
BASE_FLAG. This preserves the fresh character's actual flags; front-end unset bytes are not a
gameplay baseline. Record lookup occurs per call, so accepted record swaps cannot leave a cached
flag-buffer pointer. NINZU, gate state, BASE_ISUSE and the KAZU card query likewise read native
records. Numeric byte results keep their original values rather than becoming Lua booleans. The
records survive scene/VM recreation.

The player owns its MODELCTRL instance and publishes both PLAYER and MODELCTRL receivers for slot
zero. Their active selectors update after commands and clock sampling. Other prepared model
instances remain owned by the controller registry; the lobby borrows their state until detach.
Cancelling SD/Lua/DM precedes receiver, controller and asset destruction. The lobby detaches
collision/presentation peers before the controller registry closes.

The scene's SWITCHCTRL updates its referenced igSwitch; LAYERCTL REMOVE retires loading
attachments. Native layer indices remain stable with a retired entry, which ALL/SET cannot
revive. ENEMY, PLAYER2 and NDMWPANEL are declared empty manager categories only after checking
that this prepared roster has no matching infos/kinds. A broader roster requires its owning
consumers and is rejected. No synthetic receiver implements those gameplay services.

The original start script supplies the two Hard light overrides and music PLAY commands. Device
startup opens the audio device without also issuing adapter music commands. Normal
dialogue/terminal sound therefore follows the original script queue.

A failed original start/first does not enter the world presentation branch. The session tears
down the failed destination, releases its lobby, clears its join admission, restores the title
library and presents loading Retry/Back. The next attempt stages a fresh created record again.
GPU errors follow the explicit-failure policy, with no normal CPU graphics fallback
([GPU rendering](gpu-rendering.md)).

## Movement, collision and presentation

Each unfrozen model updates control/AI, yaw and movement, resolves collision, then polls action
completion. Collision changes the instance's position, not its movement channels. The next AI
update and the renderer read that corrected position. Inactive/frozen instances and snapshots do
not invoke collision. All authored Digi-Elf, Agumon and Leomon RAM slots bind the lobby collision
consumer; the rendered arrival actors publish independent transforms, selected motions and
elapsed motion clocks.

The solver consumes the original floor/wall geometry and the established 3/4/4 delivery defaults.
MUTEKI wall/floor gates select those probes independently. It permits sliding and chooses
supported floor heights. The wall half runs the recovered retail ray query and the floor half is
a bounded triangle solver (see [walking falls](#walking-falls)). The solver as a whole is not a
bit-exact port of complete HITWALL/HITWALLFULL traversal. Player movement keeps horizontal
progress when support disappears and enters authored falling; the bounded NPC/reference walking
probe keeps an edge hold. Player jumping uses the authored vertical channel and a bounded
descending floor-crossing probe.

Player input uses the recovered radial/sector admission and camera-relative player yaw. With host
stick +Y up, the original expression is:

`atan(cameraWorld +Z X, cameraWorld +Z Z) + atan(stickX, -stickY)`

The native EE arithmetic preserves the two atan calls and their addition. Reversing the camera
axis instead reverses horizontal input; the live retail comparison rules that out. Keyboard arrow
directions use the host mapping into the same movement demand; the pad D-pad does not walk
(retail ignores it in the world).

Weapon labels select the authored SQ_WAIT/SQ_WALK/SQ_ENTR/SQ_JUMP/SQ_FALL sections. The starter
slash walk uses Move 0.7/frame 6 and its authored runS motion; Stop 1/frame 4 keeps speed while
braking. Input does not scale movement speed or invent an animation name. Control-disabled work
keeps authored movement; STATUS holds the world and actor clocks, and manual/disconnect pause
uses the simulation hold without catch-up. Focus loss keeps the world and audio running (an
agreed requirement); returning focus needs no resume key.

Animation durations resolve through the addressed Action2 bank's animation database, not a
whole-pack name scan. RR LP/OS selection publishes its motion, duration and blend interval. The
Action2 host supplies native motion-clock leaves to the recovered Motion WAITCHECK; completion is
inclusive at the duration. The skin/shadow/weapon paths sample that owned state and blend
compatible outgoing local bone poses before skeletal composition. Bone-name and parent mismatches
reject a blend. Drawing cannot tick a controller or consume RNG.

Normal rendering samples the actual player's opacity and the authored fade/portal controllers.
Their generated transforms, JOINTSET clocks and alpha replace the corresponding adapter
presentation clocks. The box camera and material membership follow the corrected player position
after handoff. The [original box-camera transition](box-camera.md) retains and blends its
eye/interest transforms on region changes.

## Jump, gate proximity and heal activation

### Jump

Circle pressed edges enter the selected weapon's original SQ_JUMP from an eligible
SQ_WAIT/SQ_WALK. Dialogue, PADINPUT inhibition and STATUS holds keep their ownership. Jump
requests are consumed once per world update; drawing cannot reissue one. The authored PDMOVE
Stop/Move records supply airborne horizontal acceleration/braking, and onWalk consumes those
values without replacing the jump sequence. Jump/Fall movement keeps the recovered channel
arithmetic. WCHECK TurnY and Landing poll vertical channel activity, matching 392be0 mode 2 and
the recovered 394bf0 wait dispatcher. Landing's downward floor correction clears Fall before the
wait resumes. Ascending or unsupported airborne positions are not snapped back by the walking
floor probe.

All twelve authored jump motions (three phases for dual/slash/arm/gun) prepare with the immutable
player asset, including the separate shadow skin. Motion, previous-motion blending and
weapon-bone attachments use the selected native animation clock. Weapon changes update jump/fall
labels as well as idle/walk. This is a bounded Main Lobby jump implementation.

### Gate proximity

The exit, terminal and quest gates bind their own original MAP00 NEAR maps to the scene-owned
player. CTRL isLive admits the recovered zone/timer/choice consumer. Their squared distance
thresholds are 256/1600/3600; zone A requests SQ_SWON for three frames, zone B requests SQ_SWOF
for seventeen, and outer zones request SQ_WAIT for thirty-three or sixty/sixty-one frames. The
shared retail RNG and strict quantized timers are used, including single-choice draws. Unpowered
gates keep WAIT01 and do not acquire proximity choices. Authored OFF2ON/ONSW01/ON2OFF/OFSW01
clocks, opacity and generated transforms reach the renderer. Callbacks detach before registry
release. This binds the single created player; general nearest-target selection and live co-op
are not covered. Evidence: original manager 390f80.

### Heal gate and HP/MP recovery

The authored mate03 box is [105,0,-105]..[125,300,-85]. Changed membership executes the original
mate03.lua and its original nested funcHealGate from func.lua. Retail MATgetPlayerMatStat values
are outside 0, leaving 1, entering 2 and retained-inside 3 (38aea0). The callback answers them
through the shared material contact owner described under
[Shared material callback queries](#shared-material-callback-queries); for the single created
player the result is entering 2 or leaving 1 for slot zero and outside 0 for the unjoined slots.
The helper issues SQ_SWON
on entry and SQ_SWOF on departure, temporarily disables player control when recovery is needed,
waits out SQ_JUMP and restores control after its authored thirty-frame delay.

SYSctlPlayer HP/MP reads current/max values from the session record. Original GAMERAM
ADDHP/ADDMP commands apply recovered wrapped addition, dead-HP guard, optional absolute HP and
maxima clamps, then publish authored HUD meters/numbers. The helper's optional notice flag is
accepted, but the additional player x_250healhit00 particle effect is not published. Evidence:
3fca10 cases 9/10 and scalar leaves 3f9c80/3f9e20. No save is written by these
services.

### Jump, gate and heal validation

Validation uses four-starter takeoff/fall/landing/idle fixtures, three gate-bank
near/far/power-off fixtures and the normal original-startup SDL route. The live route damages
HP/MP in test-owned records, jumps using SDL Circle, walks into the heal box, checks full
recovery, leaves and re-enters without restarting the scene. The health oracle compares 450
additive/absolute/dead/overflow cases against retail instructions, alongside 324 restoration
cases. On a hardware GPU at 640×448 the SDL route runs with zero CPU drawing calls;
jump/active/loop/fall captures were inspected. Focused movement/actor/collision ASan/UBSan passes
with leak checking disabled under the tool runner. The FIRST rollback fixture waits for actual
failed callbacks before Retry/Back, so its two-failure and zero-world-tick assertions do not
depend on preparation duration.

Full-frame timing/pixel parity, heal particles, physical controller/audio and other stages are not
established by these checks.

## Stage portal, commander instances and walking falls

### Stage portal background animation

The blue stage-travel portal has an independent ambient background animation: BG02's compressed
spatial rotor 2187 and translated component 6236, using Z5SY73a1.png. Its authored cycle is
1,983,333,349 ns. BG02 samples its owned compressed spatial and UV sequences from the simulation
clock, including the lobby screens and floor decoration. With the background sequences frozen at
zero, updating the generated trigger's Action2 clock alone cannot animate this portal.
STATUS/manual holds retain the clock, and repeated drawing cannot advance it.
Source 1bf7d0 wraps mode 0/3 strictly after first+duration; the exact end sample is retained and
the authored duration is distinct from the last quantized key. Ninety-six original instruction
cases validate that boundary. The loop/fraction helpers keep their native signatures; matching
source is unchanged.

### Commander-room effect instances

The commander-room effect g_cytrerp2 has three authored Action2/model RAM slots. Only slot zero
is generated in Main Lobby startup. Retail slot-44 RAM has switch mask 1; slots 1 and 2 are
inactive, with template translations +15 and +30 X. After preparing scene eligibility, the four
portal switches publish only their generated first branch; a blanket ALLON enables the two
template copies and applies slot zero's generated placement to all three. Slot zero remains
anchored at (5,27,15); the authored -7 Y effect transform places the surface on the platform.
Rendering and diagnostics verify three allocated slots but one visible branch at the original
center. General multi-instance publication is outside this created-player lobby adapter.

### Walking falls

Walking player probes resolve walls and support independently, preserving corrected horizontal
movement on a miss instead of restoring the old position. The player publishes support/landing
results to the model owner. Retail 3926d0 then selects SQ_FALL on unsupported
non-upward/non-falling work, except SQ_SLEP. CTRL onFall/noFall controls admission. Downward
landing adjusts position and clears the vertical channel after wait polling, so the authored
Landing wait resumes on the following update, matching retail model-manager ordering. The
selected weapon's PDMOVE/Fall/jump*02/jump*03 commands keep their original horizontal/vertical
arithmetic and motion clocks. The wall half runs the recovered retail ray query
([hub travel](hub-travel.md#wall-solver)); the floor
half stays the bounded triangle solver. Walking off Main Lobby steps/platforms is implemented;
ride-on collision, body combat collision and other stages need separate retail checks.

Retail evidence comes from the pristine disc and the fresh-Dorumon slot 44 state (settled spawn
(60,10,-30)). A validated node-matrix placement starts at the stair platform (175,30,-40);
subsequent analogue-left presses use no Circle input. Live paused snapshots show support loss
near X=167, SQ_FALL/WAIT Landing, descent to Y=20, landing/WAIT Action and ordinary movement
resumption. A commander-side probe hits an authored wall; it is a counterexample, not a
successful edge traversal.

### Portal and walking-fall validation

Four-starter fixtures require both 30 -> 20 and 20 -> 10 walking falls, the fall animation,
supported landings, braking/idle and an airborne STATUS hold. The blue-portal regression pairs
its RGB texture identity 0xbcde2b3f with retail GS captures and requires all 24 submitted portal
triangles to change geometry under a fixed scene position/camera, rather than accepting unrelated
NPC or UV motion. A UV-only negative variant keeps all 24 blue-portal triangles but moves none
and fails the regression. The ordinary created-card SDL route opens the original startup, checks
one active commander effect, then walks down both steps without Circle. The floor-response oracle
compares 512 original branch states with geometry, movement queries and messenger operations as
controlled leaves. On a hardware GPU at 640×448 the route runs with zero CPU drawing calls;
stage-portal pair, single commander effect and walking-fall GPU captures were inspected. Focused
movement/portal/actor ASan/UBSan passes with leak checks disabled under the tool runner.

Optional private pose/fog inputs keep their explicit skips. These checks verify the
presentation/traversal paths; they do not establish full-frame phase/pixel parity.

## Shared material callback queries

Material callbacks use the typed seven-helper MAT contact owner. It publishes current/previous
mask bits and the current single-player existence roster only while Lua executes, then consumes
its deferred activation byte; the callback context is cleared before returning. Original hub exit
tests share the native helper owner. See
[hub travel](hub-travel.md#native-material-callback-queries) for the 61,602-case
original-instruction comparison and exact boundaries. Which regions the lobby dispatches is
listed under [Gate pads](#gate-pads).

## Name labels and the travel prompt

- **Labels.** The `matf*` material regions of every hub stage run their original scripts, which
  call `PintmessOpen`: the bottom band (`i_stpnl06`) shows the object's name and the arrow
  `i_pointcur` stands over it ("Gate to Outside World", "Gate to Commander Room", "Heal Circle",
  "Emergency Gate", "Call Keeper" in the Terminal; the Save, Bank, Digi-Lab, Data, Card and
  Appraisal Keepers in Central; the Disk, Weapon, Armor, Chip and Junk Shops and the Bank Keeper
  in the Shop Area). The Shop Area's Junk Shop region is only reachable at height 90. The label
  text sits within 1 px of retail on four compared Terminal labels.
- **Opening a label.** `PintmessOpen` opens `i_stpnl06` with `SQ_OPEN` (instance 4 for the single
  player), writes the name centred into `POINTFONT00/font04` and generates `i_pointcur` on the WN00
  layer at the target's world position (`V<pos>/V<rot>/SQ_OPEN4`). Leaving the region closes both.
  The Terminal's regions are `matf00` Gate to Outside World, `matf01` Gate to Commander Room,
  `matf02` Heal Circle, `matf03` Emergency Gate and `matf04` Call Keeper; `mate01` and `mate02` are
  the Commander Room and emergency travel triggers. Only `i_pointcur` is projected with the scene
  camera; the other WN models keep their screen layout.
- **Draw order.** The lobby UI's models (the HUD) are drawn first and the window-layer models
  after them. The label text (the original's FONT layer) draws between the window layers: after
  WN00/WN01 (the band, `i_stpnl06`, is WN01, like the HUD's `i_stpnl00`) and before WN02
  (`i_fadewn01`, `i_bgclear`, `i_stback`, which must cover a label left open). Two other orders
  fail: drawing the lobby HUD pass after the window-layer models lays the HUD's own bottom band
  (`i_stpnl00`, a 32x32 plate with source-alpha blending) over the side chevrons, which then draw
  at about 43% of retail's brightness; drawing the HUD first without moving the text between the
  window layers puts the name text under the band's plate (the glyphs at about 43%). The chevron
  blend (`igBlendFunctionAttr` src 4 / dst 5, `(Cs-Cd)*As+Cd`) and texels are not the cause:
  each chevron is three flat-UV arrows (v 0.10, 0.45, 0.85: texels (198,198,255), (140,115,255),
  (74,16,255)).
- **Measured.** Terminal "Gate to Outside World": left chevron brightest (198,198,253), mean of
  the lit pixels (131,99,253) against retail's (202,202,255) and about (131,107,236);
  `check-hubtalk` asserts both the chevrons and the glyph brightness.
- **Requirements.** The GENERATE parser takes `V<pos>/V<rot>/<sequence>`, `SYSgetGateStageNo` is
  served from `GATESTAGENO`, and the overlay view projects `i_pointcur` with the scene camera
  (the lobby view has +Z backward, so the camera passed to the overlay negates that column).
- **Tests.** `dw4_lobby_place_player` (original `MOVETRANS`) places the player for tests;
  `check-hubtalk` asserts all eleven names and the arrow.
- **Gate prompt.** A walking player returns to `SQ_WAIT` when control goes off (the travel
  prompt); otherwise the player's AI stops updating and a held stick leaves the player in the run
  sequence running in place. `check-hubtalk` holds the stick into a gate.

## Gate pads

The material dispatch in `control_tick` runs, on changed membership: `mate03` (heal) and the
label regions (`matf*`, `matg*`) always; with a travel owner also the bridges `matz00`/`matz01`
and every gate pad `mate*`: Terminal `mate00` (Gate to Outside World, field list), `mate01` (Gate
to Commander Room), `mate02` (Emergency Gate), Central `mate00` (second exit to the Shop Area,
point 2) and Shop `mate00` (second exit to Central, point 5). The original pad scripts decide
from story flags whether the pad is open; an open pad clears the point label (text, band, arrow)
before its prompt, so the label is down while the prompt is up. No or Circle returns control with
the label still down (the player is still inside its region); the label comes back only when the
region is entered again.

`mate01` travels to `stagML02` ([Commander Room](commander-room.md)). A field or dungeon
destination the build cannot load is shown as "Destination not available" with Circle: Back.
Routes, flags and tests: [hub travel](hub-travel.md#gate-pads-and-second-exits).
`dw4_lobby_material_region` returns an authored region's bounds for tests.

## NPCs in the scripted first Terminal

The first Terminal after Create or Call (the arrival with the greeting, or the called-character
arrival) runs in the engine's own lobby path (`session_lobby_start`: `dw4_lobby_native_models`
plus `dw4_lobby_native_npcs`), not the hub runtime.

- **Drawing.** `dw4_lobby_native_models` draws the three arrival actors: `n_digilfm` slot 0 and
  `n_digilff` slots 2/3. `dw4_lobby_native_npcs` adds every other `n_*` controller model as a
  world instance, as the hub's dynamic-world renderer does: the Call Keeper (`n_digilff` slot 0,
  at (270,40,50) under its `matf04` "Call Keeper" label), the other elves and Agumon draw and
  move. The Call Keeper was checked against a retail screenshot (elf at the console end of the
  walkway); there is no automated assertion.
- **Talk receivers.** The NPCs sit in the same controller registry as the hub's: each RAM slot
  whose authored HIT talk byte is set joins the HITPLAYERTALK group in `dw4_controllers_open`,
  with the original talk scripts bound. The lobby's Cross probe is `dw4_lobby_talk` -> kind60000
  box -> `dw4_controllers_talk`.
- **Cross.** The engine's first-Terminal branch feeds the lobby the stick, Circle (jump) and
  Cross. Cross passes with the hub's gate (input enabled, no STATUS scene, no pending stage
  change); the lobby itself refuses the probe without player control, in `SQ_JUMP`/`SQ_FALL` and
  before the greeting finishes, so the greeting's own Cross presses claim no receiver.
- **NEAR target.** `dw4_lobby_native_npcs` registers the player as the AI target of every `n_*`
  NEAR-map model (the arrival elves included), as the hub (`dw4_lobby_native_scene`) does for
  every NEAR-map model, and teardown clears it. Without the target the Call Keeper, the elves and
  Agumon do not run their authored distance behaviour (`SQ_SILENT` while the player is away).
  The gates have the same target.
- **Start.** Start opens STATUS only with player control and no pending stage change, as in the
  hub, so it cannot open over an NPC message.

`DW4_DEV_PLACE="<lobby frame>:x,y,z"` stands the player at a world position for inspection.
`DW4_DEV_TALK` works here in lobby frames when no `DW4_DEV_WARP` is set, and logs each Cross
probe's hit count.

Create route (`tools/test_dialogue_e2e.py --only First`, about five minutes; the player is stood
at the NPC 1750 lobby frames in, after Cross has paged the greeting and the D.S.G. messages): the
Call Keeper asks "I can call your friend to this server..." and offers "View Call Keeper Menu." /
"Exit Call Keeper."; the default entry loads `stagIS13` (the four player panels) through the hub
loader, as in retail. Agumon (`n_agumon[0]`, "I need to see Chief Leomon...") and the elf
`n_digilff[1]` talk with their faces, give control and the HUD back, and repeat three times each.
The log checks show all 15 greeting pages (`I<39>`..`I<53>`), that no Cross probe claimed a
receiver before the player stood at the NPC, and that each probe there hit exactly one.

Called route (`check-called-arrival`): a probe before the 121-tick hand-off claims nothing; at
the station elf `n_digilfm[0]` the probe hits one receiver, the NPC enters `SQ_TALK`, the talk
text opens, Cross pages close it with control back, and a second talk works the same. The arrival
assertions (no greeting, guide patrol, stations, entry rings, HUD at 121) hold alongside. Start
opens STATUS with control (checked on a run).

Not covered: `n_digilff[3]` and `n_digilfm[0]` stay in `SQ_WAIT` after first.lua where the hub
shows `SQ_SILENT` (an idle-motion difference, not compared with retail); flag-dependent lines
were seen only for a fresh Create and the called card's flags; the Call Keeper's speaker
nameplate reads "Digi-Elf" (the retail note in [load scene](load-scene.md) names a "Call Keeper"
banner, not compared); a dev placement of the player on the walking elf's path mid-message drops
the player off the floor (an artefact of `DW4_DEV_TALK` teleporting, not of talking).

## HUD and label during NPC messages

While an NPC message or choice page is showing, the lobby HUD ring/digits and the point-message
label (the `i_stpnl06` band, the `i_pointcur` arrow and the `POINTFONT*` text) are not drawn, as
in retail frames of every NPC conversation; they return when the message closes. Otherwise the
HUD ring sits over the speaker's portrait and the label stays up. `check-hubtalk` asserts the
talk opens at the Save Keeper after its label; the hiding itself was checked on rendered frames.

Retail timing: a retail trace at the Terminal Digi-Elf (a 1-frame Cross press,
then a fixed vsync count, then a single capture) shows that the HUD ring, digits, bottom band,
side chevrons and the arrow over the player are gone within one frame of the press (the point
label's text stays one frame longer), long before the window has opened (it opens over about 24
frames) or any text shows. On the final Cross the text clears by about frame 20 and the window has
collapsed by about frame 28. The HUD does not slide back: it is first visible at frame 33 after the
closing press and fades in over three frames (about 40%, 80% and full at frames 34, 35 and 36). The
hidden span brackets the speaker window's (`i_talkwn`) life, not the visible text.

`dw4_lobbyui_talk_open` therefore holds while any `TALKFONT*` text is visible
(`dw4_dialogue_talk_open`) and while the `i_talkwn` controller is active, which hides within 3
ticks (`check-hubtalk`). Keying on visible text alone hides at tick 20 and restores as soon as
the text clears. The return is a measured offset: in retail the HUD is first visible 33 frames
after the closing press, about 11 frames after the window's closing range (16 frames) starts,
while the window is still collapsing. `dw4_lobbyui_talk_open` ends the hidden span 11 frames
after `SQ_CLOSEL` begins (`check-hubtalk` asserts 10-13), not at the window's removal, and the port
draws the HUD at 1/3, 2/3 and full over the first three ticks after that. Only `i_stpnl06` gets
`SQ_CLOSE` from a script and no stage script names the HUD ring models, which points at an
engine-side hide tied to the message window; the exact trigger is not recovered.

## NPC dialogue end to end

`make -C port check-dialogue-e2e` (`tools/test_dialogue_e2e.py`, about ten minutes, not part of
`check`) boots the real headless engine, warps into each hub, stands the player in front of an
NPC (`DW4_DEV_TALK="<frame>:<model>:<slot>"`) and presses Cross through the whole conversation
while capturing frames. Frames are classified from pixels (world with HUD ring / message window /
service scene / limbo) and each conversation must show the window, the speaker's face, the HUD
ring gone while text is up, the return to the world with the HUD, and no stretch of world with
neither HUD nor window. Cases: Terminal Digi-Elf (`n_digilfm[0]`, which is not the Call Keeper)
and Agumon, Central Save, Bank Keeper and Digi-Lab, Shop Disk, and the three first-Terminal cases
(`--only First`).

Two constraints this test guards: (1) `i_stpnl06` is also the message panel's background, so
hiding it with the label must not remove the message panel (the symptom is a stuck frame with a
closed window and no HUD); (2) the stage-change iris (`i_fadewn01`) must cover the lobby HUD and
labels, which is why the lobby UI's models are drawn first and the window-layer models (face,
fade) after them, with the text between WN01 and WN02 (see
[Name labels](#name-labels-and-the-travel-prompt)); with the iris under the HUD, the HUD and the
"Save Keeper" label stay over the black screen.

Not covered: choice-menu navigation beyond the default entry; the pauses between pages (about
10-60 frames with only the nameplate) come from the original scripts and were not compared with
retail.

## Evidence and checks

Source anchors include player control `3d22f0` (yaw fragment `3d252c..2558`), model update
`395b50`, rotation refresh `3956e0`, GENERATE `396a80`, Work metadata `3511ac..3511c0` (control
defaults true), MDLisLive `373dd0`, and Motion WAITCHECK `376340`. Decompiler exports were
checked against retail objdump. `MDLisLive` ORs the result bytes of its query rather than taking
only the first result. GENERATE with only vector parameters, or bare, selects SQ_WAIT.

`verify_modelai_retail.py` includes 324 exact player-yaw instruction cases with camera-vector
construction and pad admission as controlled leaves. The movement/CTRL/turn/RNG oracles are
independent of it. `verify_playerrecords_retail.py` compares 188 original SYS query cases,
including startup's record queries; lookup/list allocation remains controlled. These are contract
comparisons, not full-frame or complete manager-latency claims.

Live fresh-Dorumon walk measurements use the isolated private PCSX2 build on the configured PINE
slot (`PINE_SLOT`; the number is test-host configuration, not recorded here) with the pristine
disc. Savestate slot 44 holds the settled spawn, captured from the slot-40 reference after Circle
closes STATUS. Thirty-vsync cardinal stick inputs and twelve-vsync neutral inputs read the
validated player Work, node matrix and movement channel while paused. Up decreases world Z, right
increases X, down increases Z and left decreases X; the speed reaches 0.7 and brakes to zero.
Camera interpolation and the 59.94-Hz retail cadence account for residual trajectory differences;
no fitted input/camera offset is applied.

The automated checks cover four starter movement/entry/animation banks,
acceleration/braking/collision/camera/material updates, repeated draws, independent probe gates,
record-backed VM resets, empty managers and MDLisLive byte reduction. Normal boot completes
original startup/greeting with either Cross or Circle prompts; real SDL controller and keyboard
events exercise walking, equipment replacement, three STATUS cycles, input inhibition and focus
recovery. SDL/hardware GPU entry/STATUS acceptance and focused ASan/UBSan runs cover the same
route. Explicit GPU tests keep zero CPU graphics calls and forced-error failure checks. A
controlled two-attempt FIRST failure fixture verifies Retry/Back and zero destination world
ticks. Missing private pose/fog inputs keep their explicit skips. Current tasks are in the
[task list](project/tasks.md).

## Open items

- The player `x_250healhit00` heal particle effect is not published.
- Gate proximity binds the single created player: general nearest-target selection and live
  co-op are missing. General multi-instance publication of generated effects is missing.
- The floor half of the collision solver is not a bit-exact recovery of retail collision.
  Ride-on collision, body combat collision and other stages need separate retail checks.
- General renderer traversal, complete wall/material visibility responses, other camera modes and
  live co-op framing.
- General gameplay audio and exact audible mixing.
- Full-frame timing, phase and pixel parity with retail; physical controller and audio checks.
- Complete portal destination menus/transitions for field and dungeon destinations.
- The exact trigger of the HUD hide/return around NPC messages is not recovered.
- The Call Keeper's drawing has no automated assertion; the items listed as not covered under
  [NPCs in the scripted first Terminal](#npcs-in-the-scripted-first-terminal) and
  [NPC dialogue end to end](#npc-dialogue-end-to-end).
- Not established by the checks on this page: general actor/model/event consumers, combat,
  traversal beyond the lobby, progression, save interoperability, local co-op and Windows/physical
  Steam Deck validation.
