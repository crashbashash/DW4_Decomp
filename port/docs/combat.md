# Combat foundation and the first mission stage

Native combat is built in ordered milestones, each validated against retail before it is claimed. This page owns the plan,
the evidence behind each choice and the current boundary. Recovered rules live in the decompilation docs
([FIGHTCALC](../../docs/systems/combat-damage.md), [dispatcher](../../docs/systems/combat-dispatcher.md),
[enemy spawn system](../../docs/systems/enemy-spawn-system.md), [drop tables](../../docs/systems/drop-tables.md)).
Task status and the resume point are in [porting tasks](project/tasks.md). The dungeon floors, local co-op in the world,
the field HUD, loot delivery, drop models and the Mammothmon fight are in [dungeon floors](dungeon-floors.md).

## Milestones

| # | Milestone | Status |
| --- | --- | --- |
| 1 | Enter the first mission stage through the deferred stage request, with its original start/first scripts | headless entry, first-visit introduction and original exit work (`check-fieldstage`); the application path (loading card, worker, publication) is run for the practice stage `stag0001` (`check-hub-boot-gate`), the other field stages use the same path without an application test of their own |
| 2 | Player attack path: input → weapon sequences → hit boxes → damage → HP/MP/status → KO | the Cross chain, the Square guard, techniques (R1 panel, MP, `SQ_WAZA`, a stand-in bullet), status and support effects, damage in both directions, EXP, level-up, skill growth, KO, the capsule, the revive and game over run headlessly. Retail-measured: P2E and E2P damage, hit chance, critical rate and multiplier, the EXP split, level-up, skill growth, the Heal Lt gain. Not ported: the spin attack `SQ_ATCK2`, `SQ_ATCK3`, the delay gauge. What is unmeasured is listed per section and under [Open items](#open-items) |
| 3 | Enemy actors: spawn, AIMAP/WPOS behaviour, attacks, damage taken, death, drops, rewards | spawn, the authored NEAR `AIMAP`, attacks, damage taken (the original hit chunks), death, EXP, drops and pickups work; drop delivery and drop models are in [dungeon floors](dungeon-floors.md#loot-delivery) |
| 4 | Stage completion: clear conditions, flag writes, result flow, return to the hub with the record updated | **route runs headlessly** (`make -C port check-fieldroute`): Terminal gate → `stag0001` → `stag0101` → `stagGF01` → `stagGF02` → `stagGF03`, the Machinedramon boss, the Leomon scene, flag 20, `stagML02` point 1 and its arrival from the record; with a progressed-save stat fixture for the boss and no retail comparison of the boss fight as a whole |
| 5 | Boss and later stages | out of scope for this foundation; the first two dungeons and their bosses are in [dungeon floors](dungeon-floors.md) |

## Stage order

The Outside World gate (Terminal `mate00`; `lua/01-lobby-hub/05-lobby-quests_e820/037-msg-70000.lua`: flag 2 on, flag 409 off) requests the practice stage
`stag0001` while flag 503 is clear and `stag0101` once it is set ([hub travel](hub-travel.md#gate-pads-and-second-exits)). The practice stage's own
first script sets 503 on entry (`lua/14-misc/02-stage-clear-sequence_e607/009-layer-setup.lua`).

- `stag0001` is NDMW entry 607, [the practice stage](#the-practice-stage-stag0001).
- `stag0101` (Goblin Pass, NDMW 613/614) is the first field stage the gate offers. It has 79 authored generators, wall/floor
  collision, per-enemy damage chunks in its Lua pack and exits to the Terminal (point 3), `stag0102`, `stagGF01` and `dng101b1`.
- `stagGF03` (the Leomon room, which sets flag 20) is only reachable through `stag0101` → `stagGF01` → `stagGF02`
  ([story flag sources](story-flag-sources.md)). It cannot be the first stage; it is the target of the flag-20 step later in the chain.

## The field stage runtime (`make -C port check-fieldstage`)

`dw4_hubruntime_prepare` accepts `stag0101` (`dw4_hubruntime_destination_available`) and prepares it as a field world:

- The world, authored player point, box camera and walking collision (271 floor / 446 wall triangles) are the same owners the hubs use
  (`open_stage` in `lobby.c` accepts any `stag0…` name; the hub runtime's ready list names the playable field stages). A field world has no
  lobby UI: the stage's message and selection windows (`i_messwn`, `i_messky`, …) run as ordinary controllers instead of lobby-UI peers, which lets
  prompts and dialogue wait and finish headlessly, the HUD is the field HUD ([dungeon floors](dungeon-floors.md#local-co-op-in-the-floors)) and Start opens
  the status screen where the stage carries a `beNDMWStatusInfo` ([dungeon floors](dungeon-floors.md#the-start-menu-in-field-stages-and-floors)).
- Field worlds run every authored material region (the hubs run a whitelist).
- The original `start` and `first` scripts run. `GENERATER START/STOP/RESTART/RESET` is a native service (`fieldgen.c`) over the authored
  `beGeneraterData` records in the stage's difficulty pack (`stag0101/separate/generator{n,h,v}.igb`, NDMW 615/616/617). The set is chosen by the
  common `DIFFICULTY` record ([dungeon floors](dungeon-floors.md#difficulty-and-the-generator-sets)). A generator's `START` on a running or
  finished generator changes nothing (the Leomon room script restarts `GENE-00` on every entry), `RESTART` re-arms. Started generators spawn their
  enemies ([below](#enemy-data-generators-and-models)).
- Field `SOUND` requests go to the audio service; the sound side of field and dungeon stages is in
  [audio playback](audio-playback.md#dungeon-stages) and this page makes no audio claim.
- `DW4_SD_TRACE=1` prints every SD/querySD call with its result, the quickest way to see what a script is waiting for.
- Model hit-volume timing uses each model's own clock (the lobby clock restarts per stage). A motion the animation database lacks plays nothing.
  Demo cameras whose interpolation is not the recovered Euler one run on their authored timing without an animated pose.

Measured by the test (three headless scenarios, one process each):

- **Revisit** (flag 355 set): the arrival script restores player control after about 240 ticks at authored point 0 (460, 50, 230); the player
  holds still without input, moves with stick input, and a frame draws.
- **First visit** (flag 355 clear): the arrival script runs the scripted introduction. `GENERATER START GENE-21` spawns one `e_goburi`
  (enemy row 0 → model `e_goburi`, HP 50 from the `enemy` database, matching the Goblin Pass value recorded in
  [enemy data](../../docs/systems/enemy-data.md)), the info window opens and closes, `ENEMY e_goburi SQ_ERAS` removes it and control returns
  after 594 ticks. The spawn point (180, 66, -300), the 594-tick figure and the timing of every step are the port's output; none is measured
  against retail.
- **Exit**: running the original `gatedisc.lua` chunk (the Gate Disc / escape sequence, stage chunk 23) plays the players' `SQ_EXIT`, the
  `STCHANGE` fade, then requests `stagML11` at point 3; a Terminal runtime prepares from the field runtime's record and arrives. The chunk is
  run by the test; in the game the Gate Disc item selects it, and disk use is not ported
  ([dungeon floors](dungeon-floors.md#loot-delivery)).

The collision of this stage has not been compared against a live retail walk; do that before trusting it. What happens at an edge with no floor
below is the recovered rule in [dungeon floors](dungeon-floors.md#enemies-fall-off-ledges).

### Enemy data, generators and models

- **Stat table** = the `enemy` database (AREA entry 3 through the existing database owner): column `MODEL`, int `HPMAX`, shorts `TSUYOSA MAMORI
  KASHIKOSA SEISHIN SUBAYASA RES_FIRE RES_ICE RES_THUNDER RES_DARK RES_STUN RES_POISON EXP`, bytes `CHIMEIRITSU MAHIRITSU RARITY`; the sibling
  `eneatk` database is the attack table the enemy-to-player rules read. A generator's `_geneEnemyId` is a row of the `enemy` table.
- **Generator packs** carry per-player-count rows (`_playerDataList` has up to four entries; `count[4]`/`max_count[4]` in the port):
  `_geneCount`/`_geneMaxCount` are looked up by the number of joined players, so the spawn rule scales with co-op by construction (3 of 25
  `stagGF01` generators change their wave size; the practice stage's first goblin group has 1, 3, 3 and 4 enemies at one to four players); the radar test takes a list of player positions.
- **Spawn rules** follow [the spawn system notes](../../docs/systems/enemy-spawn-system.md): direct/radar (squared radius against `_pos`)/timer
  (`BOOT_TIMER` in frames), fill modes wipeout/add/timer, cursor over `_genePosList` wrapping, facing × 57.29578, the model pool refusing a spawn
  when full. Radar uses the full 3-D squared distance, which is an assumption. The first wave, the refill/`remaining` accounting and the stop outside the region were
  compared with retail on one generator only ([dungeon floors](dungeon-floors.md#gene-09-refill-against-retail)).
- **Models**: `MODELCTRL <model> <slot> GENERATE "V<pos>/V<0,yaw,0>/SQ_ENTR"` on the stage's existing enemy controllers. Enemies are
  registered under `ENEMY` as well as `MODELCTRL`, carry script state (row, HP) like objects do, and run the authored NEAR `AIMAP`
  (zone distances and weighted `SQ_WALK`/`SQ_ATCK1` choices, the recovered `modelai` code) with the nearest player of the group as target
  (`dw4_controllers_nearest`); retail enemies walk toward the nearest player whatever the slot, with ties and KO'd targets not measured
  ([co-op measurements](#co-op-in-retail-join-flow-and-measurements)). Enemies collide with the stage and fall off unwalled ledges
  ([dungeon floors](dungeon-floors.md#enemies-fall-off-ledges)).
- **Enemy program commands**: `beModelCtrlHITBOX Set` (fields `_kind`, `_start`, `_length`, `_offset`, `_boxSize`) is recorded per sequence step and
  exposed through `dw4_modelctrl_hitboxes`; kind 70000 is a body volume with start 0 and length -1, 70009/70010 are timed attack volumes
  (frames 6..122 across the stage's enemy and player packs). The bullet name of a kind is table[kind/10000] (names and kinds in
  [dungeon floors](dungeon-floors.md#second-dungeon-against-retail)). `WCHECK Moving` waits for the horizontal move channels to finish, a hypothesis.
  Enemy Action2 programs run the damage-blink `FLASHSET` (presentation only).
- **Hit and damage chunks** are named Lua files in the stage pack (`hit_e_goburi.lua`, `hit_p_dorumon.lua`, `bht_x_200fire01.lua` bullets,
  `aim_<model>.lua`); the script engine runs model hit events for object models too.

## The practice stage (`stag0001`)

`check-fieldroute` starts here. A fresh Dorumon plays the introduction (Cross through the
dialogue), lesson 1 (e_goburi row 638, EXP 3), lesson 2 (e_ogre 640), lesson 3 (e_nume 642: a level-1 starter needs about 20 swings because most miss), lesson 4 (Lua-placed rocks/bushes
and the g_boxfield generator, see [Breakable props](#breakable-props)) and the arena, 33,600 ticks
with the pilot bot (EXP 18, no level-up). The closing "Good luck!" message waits for Cross while the player already has control; until it is dismissed the exit region's script
(`MATisAllPlayer() == 1 and DMgetCount() == 0`) does nothing. Region `matz00` then asks (chunk_0001/0013) and requests `stag0101` point 0; its first-visit introduction follows.

What the stage needs from the port: the texture-pack scanner accepts image records of any 4-aligned size 104..140 (the record grows with the name; stag0001 uses 112), a field `SUBWND` stub (ISRUN is 0),
`PLAYERgetDataStr(group, player, 0)` (the authored arrival point string), field ADDMP/ADDHP, and a lift's collision group may be the stage's only wall.

**Retail checks.** The retail fresh-save state taken just before the practice stage ends (Girumon, level 1) holds EXP 18, which is exactly the port's total after six lesson/arena kills (6 × EXP 3,
the pristine rows 638/640/642); and its whole level-1 record (HP 150, MP 80, strength 77, defence 120, wisdom 75, spirit 70, speed 65, accuracy 88, weapon skill 2, weapon record 268, attack delay 22, ...) equals the port's
created Girumon field for field, as the retail Dorumon record equals the port's Dorumon (`check-fieldstage retail`). Only created starters can be compared with retail records field for field: FORM-switching a Dorumon record to another species keeps the Dorumon weapons. **Not measured:** the practice stage's timings and per-swing numbers against retail (the retail practice stage was only observed on a modded disc); the 2-player graduation branch (rows 644/645) is not run.

### Breakable props

`check-fieldstage lesson4` covers practice lesson 4. Props are not hit through a stat row and not through FIGHTCALC. The practice stage places `g_bush01z01`, `g_rock01z01` and `g_rock02z01` with
`MODELCTRL ... GENERATE` (no row in the `enemy` table); they are `KIND_OBJECT` models with the HIT player-bullet flag and 100 HP, the shared
object default of `GENERATE` (0x396d74..98). A player volume that overlaps their body boxes runs the pack's own `hit_<model>.lua` through the same
consumer as enemies (`dw4_modelctrl_bullet_hit`). The practice pack (NDMW entry 607: `lua/14-misc/02-stage-clear-sequence_e607/`
`012-damage-calc`, `016-damage-calc-2`, `017-damage-calc-3`) holds the per-prop scripts: a fixed `MDLaddHp(-20)`, `(-50)` or `(-34)` per hit
(unrelated to the attacker's strength), `SQ_SDMG` while HP stays at or above the threshold, else `SQ_DDMG`. The prop's own `SQ_DDMG` is
`MUTEKI ON`, `DEAD01`, `JUMP SQ_ERAS`, so a destroyed prop erases itself (receiver inactive, HP left at or below 0). The stage-end chunk
(`chunk_0019`) `SQ_ERAS`es every leftover prop by name and regenerates a subset for the arena; retail `GENERATE` keeps an existing object's HP,
so a regenerated prop that was destroyed keeps HP 0 (as implemented, not retail-observed).

**Where a prop's durability comes from.** It depends on how the prop is placed. Props spawned through a generator (the `GBOX-*` family of crates, barrels and cases, whose entries carry a stat row, such as practice
`GBOX-01` = row 371) take HP from the row's HPMAX and their crown from its RARITY: patching the `g_*` rows gives those crates 1300 HP and a pink crown. Props placed by `MODELCTRL` have no row, so only the 100 default
applies and the stat table cannot reach them. The 100 is not in the prop object: a RAM scan of ±0x100 around all 66 prop instances finds no 100 or HP-like field. All 86 value objects of vtable `0x535230` (value at +0x0C)
read 100 at rest, including both value objects (+0x08, +0x0C) of all 41 `SQ_WAIT`/`SQ_WAIT01` sequence nodes (vtable `0x537EE0`, name +0x14, prop sub-object +0x18), a uniform fill rather than per-object data.

**Retail HP cells (practice lesson 4).** A prop's HP sits in field objects of vtable `0x00535230`, value at +0x0C, with a sibling max cell 0x18 earlier, and one rock carries four mirror cells that all start at 100.
Short taps take a cell down 20 per hit (100 to 0 in five hits), one held press takes all four cells from 100 to 66, and attacks on empty ground drain nothing, so only a landed hit drains HP. Do not overwrite the max
cells blindly: doing so crashes the game with a jump to the unaligned address `0x40`.

Port wiring: `controllers.c` registers `KIND_OBJECT` receivers as bullet targets next to the `ENEMY` receivers; an object only reacts when the
loaded packs carry `hit_<model>.lua` (`dw4_scriptengine_has_script`), so doors, NPCs and decor ignore bullets. The mode `lesson4` runs the
pilot through the lesson and asserts: at least 30 props appear, swings leave damaged props on legal HP values (100 minus whole -20/-34/-50 steps),
destroyed props go inactive, and the script reaches the arena generators on its own. The stage-clear branch after the arena
(`HITLANDMODEL hithideliftz00 OFFHIT`) is not part of this mode.

Unmeasured/unreconciled: which prop model uses which of the three amounts (the log shows all three across the three models); whether the
live numbers (20 per tap, 34 per held press) are the same scripts selected by the attack kind (`funcTameWazaHitCheck` is the
charge-attack branch) -- the script constants agree with 20 and 34, the 50 is not among the live numbers.

### Presentation

**Window rules and the floor grid.** A retail-capture sweep (stored PS2 screenshots against headless port frames) covers two points of the practice stage. The tutorial window's yellow rules: the pack authors REPEAT (`igTextureAttr` `_wrapS`/`_wrapT` = 1 is GS REPEAT) and slides the rules' UVs below zero, so the native UI window draws sample their texture repeated (a clamped sample draws the rules opaque and full length); asserted in `check-practicetext`. The rules (model `i_messwnsp`, WN03) use the 32x32 texture `messwinmstsp.png`, whose alpha is 255 at u 0..0.1 and 0 from u 0.5; the UV-offset sequence holds u at -0.52/-1.0, so the fade exists only when the texture repeats. `savescene.c`, `evodemo.c` and the engine's status models also call `dw4_modelview_draw` with the global wrap off, and their windows have not been compared with retail. The floor grid: retail lights the additive overlay meshes with much darker constant vertex colours than a saturated 127 (retail (96,87,109), (37,30,50), (40,33,53) for nodes 2184, 2186 and 2189/2191; a saturated 127 is 2.5-5x too bright). The mechanism is recovered and confirmed for these stag0001 values: retail's VU1 program `CALC_INFINITE_4` rotates the packed light block **in place** (`l <- M3x3 * l`) on every draw that follows a hardware matrix upload (`FUN_001fbce0` sets the one-shot draw-submit flag `DAT_0056b5f8`), and the EE re-sends a fresh eye-space block only after a model-view upload, so the k-th draw after a fresh block is lit with the light turned k further times: `n_eff = n_world . (V3 . R)^k` ([the rule and its evidence](../../docs/engine/p2-lighting.md#the-vu1-rotates-the-light-block-in-place)). The scene walk counts k per mesh from the depth-first order of a `BG02` root (`dw4_scene_node_light_rot`: root start and target-0 transform enter/leave are a fresh block, a target-9 texture transform or a texture-matrix scope is a pending upload, the pending flag being boolean) and `lobby_vertex_color` turns the normal by the view k times; stag0001's floor gives k = 0 for ground00 and nodes up to 2180 (still 127), 1 for node 2184, 2 for 2186, 3 for 2189 and 2191, and the draw list reads (96,87,109), (37,30,50), (40,33,52) within one count per channel (the floor quantiser is deliberately untouched; the green excess over the floor at x 380..500, y 120..200 is max 44 / mean 4.0 against max 178 / mean 10.4 without the rule, retail max 36 / mean 4.0; `check-practicelight`). **Scope, deliberately narrow:** static meshes of the scene's own `BG02` root in field stages only (never a Main Lobby hub, whose k > 0 meshes no retail dump has confirmed; actors, instances, skinned meshes, shadows, effects and arrival objects set the model-view per draw and stay k = 0), only where the node's world 3x3 is the identity, only where the transform-event model and the texture-matrix-scope model agree on k, and a root that contains any node class other than attribute set, group, geometry and transform, a transform with another target, a switch or a light/lighting-state attribute leaves every later mesh at k = 0. **Not covered (unconfirmed):** other stages (the same rule extrapolated, no second retail dump has k > 0), the hubs, the event model beyond stag0001 (whether leaving a texture-matrix transform uploads on its own, what re-emits a fresh block in the draw-begin path `FUN_001f9430`), the object-space/`sel` program variants, positional and spot lights, and a scaled or rotating ancestor (`(V3 . R)^k` is an extrapolation there).

**Digimon info card.** `DMINFOFONT` text (window `i_dminfown`, WN03) is a FONT-layer text and is drawn as a late text group in field and dungeon stages, so it is not under its window (`check-dminfotext`). The practice stage carries no `beNDMWStatusInfo` and ignores Start (`check-dminfotext` asserts it); the field Start menu of the other stages is in [dungeon floors](dungeon-floors.md#the-start-menu-in-field-stages-and-floors).

**Tutorial text order.** The tutorial window is a WN03 model and its text (`TALKFONT05/font00`, 54..) belongs to the FONT layer, which follows WN04 in the stage's layer list. Field stages (no lobby UI) draw `TALKFONT` text after the models of the layers from WN02 on (`dw4_dialogue_talk_late`); drawn between WN01 and WN02 the window covers it and it reads dark (brightest text pixel 172 against 590 for a Digi-Elf's text). `make -C port check-practicetext` requires full brightness. The lobby UI keeps its own window/text order.

## The mission route (`make -C port check-fieldroute`)

One headless process drives the original scripts end to end from a fresh save, each hop through the exit region's own script and prompt confirmed with Cross, the next stage prepared
from the previous runtime's record:

1. **Terminal gate.** `stagML11` `mate00` (Outside World) with story flag 2 set sends a save with flag 503 clear to the practice stage; with flags 2 and 503 set it offers
   `stag0101` first (the original field list, Cross selects).
2. **The practice stage** (above), which ends in `stag0101` point 0.
3. **`stag0101` → `stagGF01` → `stagGF02` → `stagGF03`**: region `matz01` of each stage requests the next one at point 0 (`matz00`/`matz02` lead back and
   to the other neighbours; `mate00` of GF01/GF02 asks for `stagML11`).
4. **The Leomon room.** The room's `GENE-00` (row 57, `e_mecha4`, HP 333 on Normal) is spawned by the start script; its sequences run the `LUACALL` commands
   (`bck`, `ded` → `<name>_e_mecha4.lua` when the sequence starts; `wh1`/`wh2` have the mode `WHit` and run on a wall contact), the AI, the E2P attack path and the player's swing. When the wave is gone the generator's `_callLua`
   (`gene00.lua`) opens the lift and sets flag 383. The boss drops `insItem` id 1 (x-data) at its death position and the route walks onto it right after the kill ([Drops](#drops)). Region `math00` in front of Leomon then runs the original scene (demo cameras `leomon`/`leomon2`, dialogue,
   `SQ_EXIT`, fade) which ends with `FLGset(20,1)` and `NEXTSTAGE stagML02` point 1 — the step the story table lists for flag 20. `stagML02` prepares from the record and keeps flag 20.
5. **Defeat** follows [KO, the capsule and game over](#ko-the-capsule-and-game-over): the engine's `end_g_000bcaps.lua` runs the GAMEOVER fade, a message, a Cross-confirmed
   prompt, then `NEXTSTAGE stagML11` point 0.

The route asserts the boss's HP, not only the flag, which guards the generator restart rule and the per-model clock above.

**The boss fixture.** The boss fight uses a progressed-save fixture, the starter at **level 40** with every stat derived by the recovered recalculation (HP 3074, strength 418, defence 375;
no hand-set stats, real damage taken: it ends with about 2300 HP). A level-1 record cannot survive the boss (a pilot bot with live AI on stag0101 — `check-fieldstage` mode `grind`, an
informational run — dies after roughly ten goblin hits having dealt 28 damage; levels 15 and 25 also lose to the boss, 40 and 60 win). The damage and EXP/level-up arithmetic are retail-measured
([below](#retail-measurements-of-the-fight-rules)); the boss fight as a whole is not. The project owner accepts the level-40 fixture: the real boss fight is to be tested in a full run once the other World-1 dungeons
(including the Abyss of Grief) are in. Until then the boss fight is a headless smoke test of the stage's mechanics (boss AI, E2P damage, generator `_callLua`, Leomon scene, flag 20), not a retail-balance claim.

**Known gap: no arena wall for the player in the Leomon room.** In retail the boss's sequences stay on authored waypoints and the room's walls hold a knocked-back player. The port's knock-back and chase of the player are not
stopped by the arena walls: with some random streams the boss knocks the player far north (z 26 → 91 → 119 in 20 cycles) and chases it to z 137–164, so a pilot following the boss walks into the `math00` strip
(z 150..160) and starts the Leomon exit scene with the boss alive, or falls off the floor edge. The test pilot returns to the arrival spot when the boss is beyond z 100 (`check-fieldstage room`
passes for several random streams, one with the player down to 301 of 3074 HP). The walls/knock-back limit for the player is not recovered; enemies are held by the kind-0x802 and kind-8 walls
([dungeon floors](dungeon-floors.md#enemies-fall-off-ledges)).

## The application path

`make -C port check-hub-boot-gate` drives the real engine loop from the title to the Terminal, takes the gate with a fresh save (flag 503 clear) and requires the **practice stage `stag0001`
to load through the loading card and worker, publish, and give control back after its introduction**. The windowed title opening ignores input, so the hub-boot pad script (`base` in
`tools/test_hub_boot.c`) starts 280 frames in, after the opening; `check-hub-boot`,
`-failure`, `-shutdown` and `-gate` run with a clean config/data directory. Field stages other than `stag0001` go through the same path and are not separately exercised by the application
test; the in-world camera, HUD and audio of field stages in the real loop are not claimed.

## The combat pipeline

`check-fieldstage attack` runs the player-to-enemy path, `check-fieldstage hurt` the enemy-to-player path.

1. **Input.** In a field world a Cross press (`pressed & 0x4000`) with player control, outside `SQ_JUMP`/`SQ_FALL`, requests `SQ_ATCK1` (decoded from
   `beNDMWMdlPlayer::vfunc_38`, 0x3d22f0). The `DROPITEM` check runs first: a pickup that takes the press starts no swing
   ([dungeon floors](dungeon-floors.md#drop-models)); an open technique panel takes the press too ([Technique firing](#technique-firing)). The decoded `ATDELAY` timer
   (`5 × ATTACKDELAY` frames, an inference from the nanosecond arithmetic) does not gate the next swing ([Swing cooldown](#swing-cooldown)). The field player runs the
   full `p_<species>.igb` model, the hubs the talk-only `m_<species>.igb`. Not ported: the stick-spin `SQ_ATCK2`, the Square-held stick double-tap `SQ_ATCK3`
   (`_bodyAtkSt0`, 15 frames; the held word 0x8000), the delay gauge.
2. **Weapon sections.** `SQ_ATCK1..3` and `SQ_ATCKTM` start at the weapon label (`slash` for the starter axe). The chain follows the player's wait
   `Atck01/02/03` (`vfunc_39`, 0x3d31f0, decoded from the instructions): `Atck01` continues into `KATCS1` only if Cross was held throughout the first
   action, else `SQ_WAIT`; `Atck02` leaves for `SQ_WAIT` the moment Cross is released; `Atck03` continues once it is released, into the jump-slash
   finisher `SQ_ATCKTM`, which carries the player forward and waits for `Landing`.
3. **Volumes.** `HITBOX Set` records `{kind, start, length, offset, size}`; `AllClear` drops them. Kind 60000 is the hub talk probe; kinds below 1000, 10000–59999
   and 80000–89999 are player support bullets, which `dw4_combat_tick` does not offer to enemies (a cast delivers them through `dw4_combat_fire` to the caster, and a
   model's own 8xxxx HITBOX is delivered to the caster's body, see [Support technique wiring](#support-technique-wiring)). A volume's world box is the model matrix
   applied to the offset with half extents `size / 2` (the talk probe is the same shape at (0,4,7), 3³). When a volume emits is the
   [HITBOX scheduler](#hitbox-scheduler); each emitted player volume is offered to every active `ENEMY` receiver and to the `KIND_OBJECT` props that carry a hit script.
4. **Receiver.** `dw4_modelctrl_bullet_hit` tests the receiver's `HIT` body boxes (`_isHitPlayerBullet` must be set), skips receivers that are inactive, control-off or
   MUTEKI, and runs the original `hit_<model>.lua` with kind, box and shooter slot. The hit-once rule is carried by MUTEKI in the damage sequences and was not compared with
   retail as a rule (the retail hit-chance measurement below is consistent with it: a first hit leaves the boss briefly protected); the gates of the bullet consumer copy the talk consumer's.
5. **Script calls.** The original chunk calls `BLTisHitCheck`, `BLTisCritical`, `BLTgetDamageValue`, `BLTgetDamageRank`, `BLTgetAttributeStr`, `BLTcalcSkillUp`,
   `BLTcalcEXPUp`, `MDLaddHp`, `MDLdspDamage`, `MDLsetSD SETLABEL`, `MDLsetSeq`. The BLT calls reach `fightcalc.c`, the port of the matched `FIGHTCALC`
   cases P2EISHITCHECK (hit chance `MEICHURITSU × (30·SUBAYASA + 20·S + 6000) / (enemy SUBAYASA)` per 10,000), P2EISCRITICAL (`CHIMEIRITSU`/200), P2EDAMAGE
   (`(6·TSUYOSA + 4·S) / (MAMORI − defence-down)`, the elemental bonus applied only when the resistance is below a 0..999 draw,
   critical bonus by skill band, ±5 % spread with the 1-in-4 high roll), P2ESTUNTIME, P2ESKILLUP and P2EEXPUP with the level-up loop. The defence-down term
   is the target's own `_downDataList` power-down entry, zero when no status is applied. RNG draws use the shared retail stream
   in the retail order of the source. `MDLgetBulletName` derives the name from the bullet kind (table[kind/10000]); `MDLisStatus` answers through
   `CHECKSTATUS` (`modelctrl.c`, `dw4_status_check`). The floating damage and EXP numbers (`MDLdspDamage`, `MDLdspExp`, `MDLdspDamageP`) are in
   [dungeon floors](dungeon-floors.md#local-co-op-in-the-floors).
6. **Result.** HP changes through `MDLaddHp`; the damage rank selects `SQ_SDMG/MDMG/LDMG/DDMG` with the element label; `SQ_DDMG` ends in `SQ_ERAS`. EXP goes to every
   living joined player split by the session's player count (the attacker's share is `exp × …/50`).
   Flinch length: the flinch actions of the enemy models play their `MOTIONSET`s in order (`MDMG01` = `Sdmg01`, Motion wait, `Sdmg02`, Motion wait; `LDMG04` = `Ldmg03` then `Ldmg06`), so a medium flinch lasts the sum
   of both motions, with the blend wait (the Action2 host starts each `MOTIONSET` when the component walk reaches it; mechanism, census and the retail reads in
   [dungeon floors](dungeon-floors.md#mammothmons-charge)).

Measured by the `attack` test (port output): a level-1 Dorumon (TSUYOSA 94) hits the Goblin Pass `e_goburi` (row 0: HP 50, MAMORI 90) for 5–6 per hit — base
`(6·94 + 4·S)/90` — in about a third to a half of its swings, kills it in 11 swings (some swings hit twice because several volumes fire), the goblin plays its damage
sequences, dies, is erased and 10 EXP is paid. The Goblin is held still by removing its AI target in the fixture. A clean retail cold boot agrees (two created level-1
Dorumon, Normal difficulty, no crown-mod RAM): the retail `stag0101` goblins read enemy row 0 with HP 50 and a level-1 Dorumon's sword hits them for 5, 5, 5 and 6.

Retail evidence for the damage rules: the live savestate measurements recorded in [combat damage](../../docs/systems/combat-damage.md) (skill 0 / 1500 / 5000 against
the Goblin row, strength 2000, normal and critical hits) all lie inside the ranges the port produces (`check-fieldstage` damagelive). That check needs a
defence term of MAMORI − 3 (125 against the table's 128); the source of those 3 points in the measured state is unidentified. The other retail anchors are under
[Retail measurements of the fight rules](#retail-measurements-of-the-fight-rules).

### Guard (Square)

Outside the main lobby, when the sequence is not `SQ_JUMP` (`SQ_FALL` is allowed), a Square *press edge* (`pad._trigger & 0x8000`, the
word the pad code names `hold` in `vfunc_38`) requests `SQ_GUARD`; the test is the first of the non-lobby branch and is not gated by the panel byte. The port
issues it for all four slots (`guard_request` in `hubruntime.c`; the main-lobby check is "the stage has a combat owner", which equals retail's four-name stage table; the
player-control gate mirrors the Cross request). Retail's test is `beNDMWMdlPlayerInfoWork._isMainLobby` (+293). Its one writer, `beNDMWMdlPlayer::vfunc_36`, runs once per player per stage load and compares the stage name with the four-name table at `0x4cc800` (`stagML02`, `stagML11`, `stagML12`, `stagML13`); the same flag also gates the Cross talk/probe branch and the Square-edge state machine for `SQ_ATCK3`. A same-frame Cross request wins, as in retail (later write). While the player is in `SQ_GUARD` the enemy-hit chunk skips its whole hit branch (no
damage, no hit check) and ends in `SQ_GUARDR`. `SQ_GUARD` plays `GURDx1` (the model's `Frame 15` wait: 15 frames, 0.25 s at 60 Hz; the port measures 15 ticks), then
`SQ_GUARD2` plays `GURDx3` (7 frames; 8 ticks measured) and returns to `SQ_WAIT`; only the `SQ_GUARD` phase blocks damage. `check-fieldstage-guard` covers it (the
guard request, no damage and `SQ_GUARDR` on a guarded Goblin hit, damage when not guarding). Not read: any stamina or cooldown rule for the guard (`vfunc_38` has none;
the request repeats on every press), and nothing was measured on retail.

### Swing cooldown

Retail measurement. The player's current sequence is the pointer at `info+0x14` of the player's InfoWork (0x158bfc4 in the boss state: `SQ_WAIT` becomes `SQ_ATCK1` on Cross). With the boss's AI byte at 0 (nothing to
hit, nothing hitting back) and the player teleported to open floor, Cross was pressed twice at fixed gaps (frames between the presses): a press during the swing (gaps 8–28) does not restart it;
the swing lasts about 0.517 s (31 frames, Susanomon slash); from gap 36 to 260 every second press (10 of 10 at each of 40, 80, 120, 150, 165, 175, 190, 220, 260) started a second swing. So the decoded
`ATDELAY` timer (5 × ATTACKDELAY = 170 frames for the record's 34) does **not** delay the next swing and the port has no such gate (`hubruntime.c`); what ATDELAY gates (the delay gauge, the chain) is unmeasured.
The port's swing length depends on the equipped weapon (22 ticks with the starter weapon models; retail 31 for the Susanomon sword): per-weapon swing lengths are not compared.

### Control off mid-jump

When a prompt takes control away (`PLAYER OFCTRL`, e.g. the area-change dialogue) while the player is running and jumping, retail drops it straight down (an owner parity note, measured). In the original, OFCTRL clears `_isOnCtrl`
(InfoWork+0x44) and calls the model hook in vtable slot 42, which for the player (`vfunc_42`, 0x3d4820) only clears the "technique panel open" byte (+0x124); the per-frame update `FUN_00391cf0`
skips the control hook (vtable +0xa0) when the byte is 0, and the only writer of the stick-active byte (+0x70) is `vfunc_38`, inside that hook. Live check: clearing the byte on the player in a jump with the stick held
leaves the position unchanged horizontally (about 0.7 units over the whole arc) while the height arc continues, the same as releasing the stick. In the port `ai_tick` stops the forward motion channel while the player is
in SQ_JUMP/SQ_FALL with control off (`check-fieldstage jumpstop`); with the channel left running the player drifts 27 units in 38 ticks. Not compared: the exact jump arc height and duration (retail apex about +13 units).
What retail does with the stale stick-active byte is not traced; the observable result is what is matched.

### HITBOX subcommands

MODELCTRL Work `_subCommand` owns the actual subcommand/list/HITBOX instances.
Producer `39a500` copies start/kind/geometry, computes the signed-kind receiver
group and stores end as start plus length; only a length of exactly `-1` gets the large
sentinel endpoint (`100000000`), other negative lengths are not indefinite.
`make -C port check-modelsubcom-retail` compares 370 full payloads with the
original instructions, including signed-kind boundaries and float rounding.
Consumers read the actual endpoint, avoiding a subtraction/addition round trip.
Sequence replacement/AllClear and teardown release entries; returned volume
arrays are read-only projections. Effect/sound subcommands, named
attachment resolution and full bullet behavior remain open.

### HITBOX scheduler

HITBOX activation follows original `399d90`/`3998f0`/`399e20`: add the
system frame delta, emit on the first start crossing, then emit on subsequent
updates only while before end and remove expired entries in list order. A first
crossing past end (including a zero-length command) still emits once. No native
birth-time interval test or once-per-volume cache schedules delivery.
Combat receives emissions at each source model's post-wait/MUTEKI subcommand
phase. It samples the shared session clock before models run, preserving
`3908e0`'s same-timestamp body cache. Querying volumes or refreshing combat
bindings does not emit. Player/enemy/caster admission and
support-MUTEKI assumptions are separate, unverified gameplay boundaries.

Actual Work node-lock fields drive the retained-parent matrix branch.
HITBOX's own position-lock byte has no active handler; named-bone/track lookup
and effect following are separate consumers. Source replacement and owner
teardown safely release retained in-flight entries/callback resources.
See [the detailed contract and oracle limits](controller-services.md#retail-subcommand-phase-and-node-locks).
`check-modelsubcom` exercises these native boundaries; `check-modelsubcom-retail`
compares the original scheduler and matrix arithmetic. `check-fieldstage` mode
`hitschedule` covers both owner teardown orders and complete arena baselines.

### Enemy attacks on the player

`check-fieldstage hurt`: the generated `e_goburi` runs its authored NEAR AIMAP, chooses `SQ_ATCK1` and its `HITBOX`
volumes (kinds 70000–79999) are delivered to the joined players' body boxes (`_isHitEnemyBullet`). The player model is script-bound (`hit_<species>.lua`), its HP is
synchronised with the record around each delivery, and the chunk's `BLP*` calls reach the E2P rules of `fightcalc.c` — E2PISHITCHECK (guard draw, then hit draw
with the `eneatk` row), E2PDAMAGE (TYPE 0 strength/defence with element resist and critical, TYPE 1 magic, TYPE 2 percent of MHP), E2PDAMAGERANK and the stun time
(case 7) — ported from the matched source; the damage and the hit check are retail-checked ([below](#retail-measurements-of-the-fight-rules)). A level-1 Dorumon (170 HP) took 17 from the first Goblin hit
(`eneatk` row 1: MEICHURITSU 90, TSUYOSA 125) and reached KO after ten hits (SQ_DDMG; the HUD sink received 90 % / 153 and finally 0). The hit script's
`METERCTRL/NUMBERCTRL` HP updates reach the field HUD ([dungeon floors](dungeon-floors.md#local-co-op-in-the-floors)). Attack rows that carry an effect (`KOUKA` other than `none`:
stun, poison, ashidome …) go through the [enemy-to-player status rules](#enemy-to-player-status-rules); the table spells "no element/effect" as the string `none`. The knock-back carries the player off the start
platform in the fixture, which puts it back. What follows KO (the PLAYER2 capsule, the BKCHIP stash, game over and the return to the Terminal) is described in [KO, the capsule and game over](#ko-the-capsule-and-game-over).

The enemy-to-player hit chunk (`hit_p_<species>.lua`, stage chunk 3, a `damage-calc` chunk of each stage pack) runs on the receiver, the player (unconfirmed): `if MDLisSeqName("SQ_GUARD") ~= 1` then the hit check (`BLPisHitCheck`) decides; a miss, a zero damage or a stun-free guard sets the
player's own `SQ_GUARDR` (`MUTEKI ON`, `MOVE Back`, `WCHECK Moving`: a 4-9 unit knock-back and a short invulnerable recoil), a hit sets `SQ_SDMG`/`MDMG`/`LDMG` after `MDLaddHp`, and a player already in `SQ_GUARD`
skips the whole branch and ends in `SQ_GUARDR` without damage. The flinch interrupts the player's own swing. On the damage path the chunk calls `BLPisHitCheck`, `BLPgetDamageValue`, `MDLaddHp`, `MDLdspDamageP`, `BLPgetDamageRank(hp_after, damage)` (rank 3 is a KO and sets `SQ_DDMG`),
then `BLPgetStunTime`, `BLPgetBindTime` and `BLPgetPoisonTime`, publishes the HP to `METERCTRL hpmt<N> SETPERCENT F<pct>` and `NUMBERCTRL hpnm<N> SETVALUE I<hp>`, and moves `MODELCTRL i_stpnl02` per player.

## Fight records

`fightcalc.c`, `fightstatus_p2e.c` and `fightstatus_e2p.c` read player and
common state through the recovered layouts in `dw4/reflected.h`.
Their shared `src/fightrecord.c` resolves `beDataObjInt._data`,
`beDataObjIntList._data` → `igIntList` and
`beDataObjObjectList._data` → `beNDMWItemBaseList` → `beNDMWItemWaza` through
the owning arena. WAZALIST lookup reads `_baseNo` and `_recNo` directly, following
the matching `beNDMWGameRam_FindTechniqueRow` at `0x3fc6f0`; it does not create
the host `dw4_item_record` view for these rules. Database reads use typed
`beDataBase` instances. Stat writes and recalculation use the typed
record setters and their ownership.

`dw4_property_reference` performs the name/alias/type lookup and lends
an arena/record handle pair. Reads resolve handles for the current call and
reacquire after mutation, record publication or recalculation; no record pointer
or copied item array is cached. Empty, missing and wrongly typed records fail as
they do through the property API. Invalid list counts and handles fail explicitly.
The native null-item projection (base/row zero) remains compatible;
the retail oracle uses actual technique objects and makes no null-item claim.

Validation:

- `make -C port check-fightrecords`: **47,318 comparisons** with the
  property API, including signed values, duplicate technique bases, null slots,
  empty/wrongly typed records, staged commits, snapshots, aliases and malformed
  list/handle rejection. Owners release all arena allocations.
- `make -C port check-fightrecords-retail`: **384 queries** agree with original
  `0x3fc6f0` instructions, including empty lists, first-match duplicates, signed
  rows/bases and unchanged output on a miss. Property lookup is a controlled leaf.
- The record comparison also passes AddressSanitizer and UndefinedBehaviorSanitizer
  (leak detection disabled; the test separately checks that all arena blocks are released).

`check-fightrecords-retail` is separate from the wider `make -C port check-retail` target, for which no full
retail-suite pass is claimed: its player-record and window/controller oracles pass and its remaining limitation is
the older host-database fixture, recorded under the [window arena migration](status-menu.md#arena-ownership).

The record layer adds no retail measurement of status durations/chances,
technique geometry, KO/revive or full gameplay timing. The field-stage
retail anchors and the status/support integration tests are the behavior checks
for those boundaries.

## Retail measurements of the fight rules

Measured live in the private PCSX2 build on the retail disc. `check-fieldstage` mode `retail` asserts the anchors below unless another mode is named.

### P2E damage

From the savestate `in_boss_fight_goblin_fortress` (stagGF03, boss `e_mecha4` row 60: live HP 3194 = HPMAX,
MAMORI 150 in the port's table, a level-999 Susanomon whose SKILL array reads 9999). The boss's HP cell (`[InfoWork+0x0c]+0x0c`) was reset before each swing, the
player's TSUYOSA written (record at the 0x7d4000 block) and one Cross swing delivered next to the boss, teleported and faced with the retail state tool. Single-hit swings:

| TSUYOSA | retail HP loss per swing | port `dw4_fight_p2e_damage` range (4000 draws) |
|---|---|---|
| 9999 | 647–695 (6) | covers it |
| 5000 | 443–454 (3) | 442–489 |
| 2500 | 350–380 (4) | 347–384 |
| 1000 | 301–320 (5) | 290–321 |
| 400 | 279–285 (5) | 267–296 |

`(6·TSUYOSA + 4·SKILL[skill]) / MAMORI` with the 0.95/0.975/1.0/1.025 roll and the up-to-2.5 % spread therefore predicts retail's numbers.
Swings that delivered about twice the single-hit value (610, 569, 1360) are two-hit swings; one 1796 swing is consistent with a critical on one of two hits. A level-1 swing against
row 388 (MAMORI 185) measured 2 HP, consistent with `(94·6 + 4·SKILL)/185` and the 0.95 roll. The savestate carries the retail enemy table of its build.

### E2P damage

**Goblin Fortress boss (same state, attack TSUYOSA 160 = `eneatk` row 9/13/16/19):** with the player's DEFENCE written live (the authoritative HP copy is the info-work one, not the record) the boss's single hits cost
3618–3946 HP at DEFENCE 150 (port 3611–3990) and 949/951 at 600 (port 902+; `3564·160/DEFENCE`), and a critical swing cost 1918 (2x). Which `eneatk` row each hit used was not identified (only the TSUYOSA product was fixed).

**Mammothmon on `dng102b3` (`check-fieldstage` mode `e2pboss`):** with MAMORI 100, SUBAYASA 1, KAIHIRITSU 0, BOUGYORITSU 0 the formula gives plain 177..196 for the contact boxes (70000 = `eneatk` row 0, base 187 x 100 / 100) and 284..313 for the charge (70016 = row 16, base 299); the retail samples 177-196 and 284-309 lie inside. Critical factor 1.90 / 1.92 (`eneatk.CHIMEIRITSU/2 + 90` percent before the spread), contact criticals 337..372 at 8 %; 256 retail contact hits were 239 plain at 177-196 and 17 criticals at 339-370 (6.6 %), which refutes a reading of criticals up to 386 at about 1 in 5. The hit check is the recovered `vfunc_34` case 0 expression: SUBAYASA 1 always hits, SUBAYASA 9999 hits 1 % of the time against the boss. The measurement and its fixture are detailed in [dungeon floors](dungeon-floors.md#second-dungeon-against-retail).

**TYPE 1 (magic)** damage is enemy KASHIKOSA × `eneatk` TSUYOSA / player SEISHIN, then scaled by the element resistance in three tiers: `res < 1001`: × `((1000 - res) / 20 + 50) / 100`; `res < 4201`: × `((5000 - res) / 80) / 100`; otherwise / 10. The damage-calc chunk plays `SQ_GUARDR` on 0 damage, so Mammothmon's `SQ_FIRE` (`eneatk` row 15, ice, base `16375 / SEISHIN`) does 0 and flinches a player with SEISHIN 9999 and resistance 9999. `SQ_FIRE` is not measured on the unmodified fixture.

### EXP and level-up

**EXP (one player):** from `normal_lvl1_before_crown_enemy` (stag0102, level-1 Dorumon, crown goblin row 388, table EXP 133), with the goblin's HP cell set to 1 and the player's HP kept up in the record and info-work
copies, the player swung until it died: the player's EXP record went 170 → 303 = +133, the port's `dw4_fight_p2e_expup` share for one player. The split for two to four players is under [Co-op](#co-op).

**Level-up (1 → 2):** with EXP set to NEXTEXP−1 (340) the same kill gave LEVEL 2, NEXTEXP 341 → 968, MHP 170 → 181, MMP 60 → 70, TSUYOSA 94 → 105, MAMORI 110 → 119, SUBAYASA 60 → 69,
KASHIKOSA 65 → 75, SEISHIN 75 → 87 and EXP 473. `dw4_fight_p2e_expup` loops LEVEL+1 → `dw4_playerstats_recalculate` (the ported FUN_003fab90) while EXP ≥ NEXTEXP, refills HP/MP, and reproduces all of
those numbers. Retail also runs FUN_003f8760 and queues the level-up display; neither is ported.

### The retail AI switch

`OFCTRL` clears the byte `_isOnCtrl` at `beModelCtrlInfoWork+0x44` (vfunc_33 @0x396a80, jump-table entry 19 at 0x397660 `sb zero,68(s0)`; ONCTRL sets it).
For an enemy that object is its `beNDMWMdlPEBaseInfoWork` (vtable 0x0053D3E0). Poking it to 0 in live RAM freezes the boss's movement and attacks (it finishes
an attack already running) — **and the boss then ignores hits**, so rate measurements set the byte to 1 for about 0.7 s around each Cross swing and back to 0 afterwards (the control
connect rate rises from 35 % with the AI live to 83 %).

**Stun as an alternative:** the enemy's `_timerList` (InfoWork+0xF8, 12 ints) is recomputed by the engine, so writing a STUN/SLEEP/BIND timer there does not stick. Raising the
player's MAHIRITSU (stun rate, record field after CHIMEIRITSU at 0x7bfe94 in the boss state) to 9999 makes the first hit stun the boss for a long time (P2ESTUNTIME): over 40 following swings it attacked
once and barely moved, hits kept their normal value (about 680 at strength 9999 / skill 9999), but only 23 of 40 swings connected (57 %, against 83 % with the `_isOnCtrl` gating), so the gating is the
preferred setup for rate measurements and the stun is a way to keep the boss from hitting back.

### Hit chance

Player SUBAYASA `s`, MEICHURITSU `m` and SKILL 0 written into the record, boss row 60 (SUBAYASA 388);
the ported rule gives q = `m·(30·s + 6000)/388/10000` per roll. A swing reaches the boss with two volumes and the second rolls again after a miss (a first hit leaves the boss briefly
protected), so P(swing damages) = control·(1 − (1 − q)²): eight conditions (m 700/257/130/500/60/1, s 1/300/3000, 40–110 swings each, 1,165 swings in all) lie within 2.5 σ.
The single-roll rule alone does not fit (retail was 1.4–1.7× higher at q 0.2–0.4). SUBAYASA matters as the rule says (m 60: s 1 → 17 %, s 300 → 43 %, s 3000 → 92 %).

### Critical rate and multiplier

**Rate:** per hit, classified from the HP lost (one hit 400; critical 494–528 = +30 % at SKILL 0, the recovered `S/20 + 30` rule; two hits ≈ 800): CHIMEIRITSU 20 / 60 / 120 gave
6 of 60, 17 of 52 and 32 of 47 hits critical against 10.4 % / 30.9 % / 60.4 % from the port's `rand % 200 < CHIMEIRITSU`, all within 2.5 σ. Critical damage at SKILL 9999 is
about 2.7× in one swing and matches the recovered tiers within the roll spread.

**Multiplier at mid skill (every swing critical, single-hit swings, TSUYOSA 9999):** skill 800 / 1500 / 3000 / 6000 gave mean critical / base damage 1.709 / 1.883 / 2.096 / 2.385 against the recovered tiers
(+S/20+30 %, +(S−1000)/50+80 %, +(S−2000)/100+100 %) 1.70 / 1.90 / 2.10 / 2.40, the port's means 1.698 / 1.901 / 2.100 / 2.399 (asserted within 2 %).

### Skill growth (P2ESKILLUP, weapon skills)

Ported as `dw4_fight_p2e_skillup`: below the level cap (30·L to level 36, 20·L+360 to 107, 10·L+1430 to 227, then 8·L+1884) one draw `rand % 100000`
is made per hit against `table[level group][skill band][normal | critical] · growth · 500 / 1000` (tables and the 21 band bounds read from the retail image; growth is the shinka column for the weapon skill, 100 or 130); success adds 1 to
`SKILL[WEAPONSKILLNO]` and recalculates the record (which also rewrites WEAPONSKILLNO from the equipped weapon). Retail, boss state with LEVEL and SKILL[1] written and the gated-AI swings (60 swings per condition):
level 36 / skill 500 normal: 13 raises in 75 hits (port 17.0 % per hit, expected 12.8 ± 3.3); the same with critical hits: 7 in 56 (expected 11.5 ± 3.0); level 999 / skill 5000: 5 in 77 (6.5 %, expected 5.0 ± 2.2);
level 36 / skill 1100 (above the 1080 cap): 0 in 76 (expected 0). **Other weapon skills (same setup, level 36 / skill 500, 60 swings each):** skill 0 (BLUNT, growth 130 for Susanomon) 19 raises in 77 hits (port 22.9 %, expected 17.7 ± 3.7), skill 3 (BASH) 11 in 74 (expected 12.7 ± 3.2),
skill 5 (CRUSH) 17 in 74 (expected 12.0 ± 3.2, +1.6 σ): all inside 2.5 σ; skills 2 and 4 were not run separately (same table, growth 100). Not ported: FUN_003f8760 (run after a raise) and the skill-up display messages.

The drops of the measured kills were not read.

## The 16 forms

`make -C port check-fieldforms` runs the attack test once per DIGIMONNO 0..15 (the record's species and `p_<name>` model from the shinka row, level-1 stats from the recovered
recalculation): each form's own SQ_ATCK1 sequence and weapon-labelled hit volumes land, `hit_e_goburi.lua` runs, FIGHTCALC deals damage (4–8 HP at level 1 against the
50-HP Goblin Pass goblin) and the goblin is killed with the EXP award. **Not measured:** every form's swing against retail (only the Dorumon-line formula numbers above are),
the techniques/skills beyond the basic chain, form-specific weapon timing, evolution itself.

## Techniques

### Technique attack rules (attack number / 10000 == 4)

Ported in `fightcalc.c` with the `pcTech` database (`dw4_fight_ctx.tech`): the learned technique is the player's WAZALIST item whose base number
(`_baseNo`, the `revision` of the host item view) equals `attack % 1000`, its row is the item's `_recNo` (`record`); critical = `rand % 1000 < (CHIMEIRITSU + 100) · (10000 / (RES·12/10 + 50)) / 100` for an elemental technique (`rand % 100 < CHIMEIRITSU`
without element); damage = `(5·SKILL[row.SKILL] + 20·(−row.HP) + 10·KASHIKOSA) / enemy SEISHIN`, scaled by `(1000 − enemy RES_<element>)/1000`, then the same critical tiers (using the technique's skill value) and
spread as weapon hits; skill growth uses the row's SKILL index and a flat `table · 100` chance.

Retail (boss state of the [retail measurements](#retail-measurements-of-the-fight-rules): R1 opens the technique list, the panel-open flag is the byte at InfoWork+0x124, the cursor
stops at the top row, D-pad Down moves it, Cross casts and the list stays open; MP spent identifies the cast): Fire (row 4, element fire, boss RES_FIRE 650) single hits 228–251 in 16 casts = the port's 228–251
(the resistance scaling matters: unscaled it would be about 684); Impact (row 29, no element) 696–740 in 7 single-hit casts against the port's 684–757; Impact casts hit up to four times. Technique skill growth at
level 999 (Fire casts): 5 raises in 77 hits at skill 5000 (port 13.5 %, expected 10.4 ± 3.0, −1.8 σ) and 10 in 77 at 9000 (16.0 %, expected 12.3 ± 3.2). The available techniques and their tiers depend on the skill values
(a list rebuilt by the game: with SKILL[6] low Fire and Impact drop out), so tests keep the skills at or above every threshold.

**Not measured:** the technique critical rate, technique stun/status effects (poison, sleep, bind, attack/power down), the technique hit count per cast, MP costs other than Heal Lt's, the other elements, the support techniques other than the Heal Lt gain.

### Technique firing

`src/technique.c`, `check-fieldstage technique`: the R1 panel, MP, `SQ_WAZA` and the bullet. The player's technique list and cast are ported as a per-slot panel module plus one stand-in for the bullet. Recovered rules below are static analysis of the
USA ELF (no emulator or Ghidra run); everything the port had to choose is listed under **Assumptions**. All frame counts and numbers are the
port's output and the recorded rules, **not compared with a running retail game**.

**Recovered (static, from `asm/` and the reflection data).**
- Owner. The list is not part of the player model: `beNDMWPanelWaza` (messenger group `NDMWPANEL`, vtable `0x53e020`, update `vfunc_31` `0x3cfe50`, messages
  `vfunc_34` `0x3d0bc0`) keeps one state machine per player. The player's control hook (`beNDMWMdlPlayer::vfunc_38` `0x3d22f0`) sends `GENERATEWAZA` on R1 (`0x800`) when
  its panel byte (`InfoWork+0x124`) is clear and the sequence is not `SQ_JUMP`/`SQ_FALL` (the whole input section returns early there), sets the byte when the message
  is answered, polls `ISCHECK` every frame while it is set (a missing answer clears it) and does not handle Cross at all while it is set (the swing code is in the closed branch).
- Input (`vfunc_31`). Accepted only once a frame counter (`Ram+0x24`, capped at 2) is at least 2 **and** the named timer `FIRE` has elapsed. Up = stick direction value 1 or D-pad `0x10`,
  Down = stick direction value 4 or D-pad `0x40`; the cursor is a four-row window without wrap (`FUN_003ce7e0`/`003ce890`). R1 closes the panel (there is no Circle or
  Triangle handling). Cross fires when the list is not empty (the player-work gate `s6` is taken as 0).
- Fire (`PanelObjectWaza::vfunc_22` `0x3ceed0`). Row colour 1 (MP below `pcTech.MP`) or strictly less MP than the cost refuses (`CURSOR_NG`, nothing spent). Otherwise the
  `MP` property is decremented at once by `pcTech.MP`, the label is `pcTech.LABEL`, `FIRE` is started with `pcTech.DELAY * 1e9 / 60` ns and `_retIsFire`/`_retWazaLabel` are
  set. A refused press starts `FIRE` with `0x0fe502aa` ns (about 16 frames). `ISCHECK` returns and clears `_retIsFire`; the player then requests `SQ_WAZA` with the label as the
  extra string (`FUN_00393c80`). Because `ISCHECK` is not polled in the air, a cast fired in `SQ_JUMP`/`SQ_FALL` waits for the landing with MP and lock already spent.
- List (`PanelObjectWaza::vfunc_21` `0x3ce960`). A copy of `WAZALIST` (`playerstats.c` builds it), colour 0 usable, 1 MP short, 2 disabled by stage flags (`NOHEALING`, `NOPARAUP`,
  `NOCURELING`). The cursor resets only when the count changes.
- Data. `SQ_WAZA` of every `p_<species>.igb` has one LABEL section per `pcTech.LABEL` (`fire1` ... `bind`); each is `MOVE Stop`, `ACTION H...`, `WCHECK Action`, `JUMP SQ_WAIT`, with
  no HITBOX (except `reanimation`, kind 80050). The bullet is an effect model of the stage pack (`x_200fire01`, `x_200ice01` ..., `KIND_PBULLET`) whose HITBOX kind is
  `40000 + family base`; support techniques use `x_250*hit01` volumes of kind `80000 + base` that land on the caster (`hit_p_<species>.lua` then calls `BLPcalcKoukaMagic`).
  The bullets are spawned by `beActionStarterInfo` rows matched by (player model, ACTION name): for `HFIRE1` the muzzle row is `{SQ_ATCK01, delay 0, offset (0,6,5), locked}` and the projectile row `{SQ_ATCK02, delay 0, offset (0,6,0), not locked}`.

**What runs.** `dw4_technique_*` (`include/dw4/technique.h`), one panel per slot (arrays of four; pads 2-4 drive their own slot's panel, see
[dungeon floors](dungeon-floors.md#pads-2-4-talk-selectors-technique-panel-status)):
- `hubruntime.c` `dw4_hubruntime_input`: the R1 edge (`h->digital.trigger & 0x800`), the D-pad/stick repeat, and Cross go to the panel first. While the panel owns the frame
  Cross starts no `SQ_ATCK1`, no talk probe and is hidden from the attack-chain hold (retail: the closed branch only). `dw4_hubruntime_tick` then polls the pending fire
  (`dw4_technique_poll`, not while airborne), selects the LABEL (`dw4_modelctrl_label(player,"SQ_WAZA",label)`), requests `SQ_WAZA` and launches the bullet; the panel closes when
  the player loses control (retail `vfunc_42`). The page is always 0 (L1/R2 pages and `GENEEMGHEAL` are not ported).
- MP is charged inside the panel at the press, exactly `pcTech.MP`, and a press with `MP == cost` is allowed. The FIRE lock is `DELAY` frames (75 for the attack techniques,
  60 for support, 90 for Venom) and blocks cursor, R1 and the next cast; the refused-press lock is 16 frames. With the port's clocks a second cast is accepted exactly `DELAY`
  frames after the first and refused one frame earlier (tested).
- Attack number: `40000 + base` (`WAZALIST` revision) for attack and status techniques, `80000 + base` for the support families (bases 40, 45, 50, 55, 60, 65, 75, 80). It is
  delivered as a player bullet owned by the casting slot through `dw4_combat_fire` (`combat.c`), so the existing class-4 rules resolve it on the enemy:
  always-hit, critical, technique damage `(5*SKILL + 20*(-HP column) + 10*KASHIKOSA) / SEISHIN` scaled by the element resistance, skill growth and EXP. `dw4_combat_tick` does not
  offer 8xxxx volumes (the `reanimation` section's 80050) to enemies.
- Support bullets: `dw4_combat_fire` offers an 80000+base volume to the caster's body (as an enemy-group bullet, the only group the player's hit data accepts), so `hit_p_<species>.lua` runs its
  80000 branch and `BLPcalcKoukaMagic` applies the effect. The path is run end to end by `check-fieldstage supportcast` (see [Support technique wiring](#support-technique-wiring)); a Raise cast launches no stand-in bullet because its
  `reanimation` section carries the volume.

**Assumptions (made by the port, not recovered).**
1. The bullet. The action-starter dispatcher and the bullet's `MOVE Push` speed are not recovered, and the effect models are not spawned (their `LUACALL bht` and `CTRL isLive` semantics are
   open). The port flies one 4x4x4 box (the size of `x_200fire01`'s HITBOX kind 40000, applied to every family) from the projectile row's offset `(0,6,0)` along the caster's heading at the
   cast frame, 2 units per frame, for 75 frames (the inferred retail lifetime is 73 to 83), spawned on the frame the cast request is accepted (starter delay 0 for every family; `SPEDU1` rows have 16).
   It ends on its first contact (taken from the `bht` script, whose 123-byte chunk is `MDLsetSeq("SQ_ERAS")`, registered for body/wall/floor hits), so a single bullet hits at most one receiver and
   multi-volume techniques (Impact up to four hits, Venom ticks, Cutter, Bomb) are one hit here. Wall hits and the muzzle effect are not modelled. Speed, lifetime and a 2-unit step are guesses.
2. The request is immediate (like the weapon swing), so a cast interrupts a swing in progress; retail's pending-request priorities are unread.
3. `FIRE` survives a close and reopen (the message does not clear the named timer); the cursor survives too (count unchanged).
4. Walking stays active while the panel is open (retail: unmeasured). Keyboard arrows therefore walk and move the cursor at once.
5. The retail gate `s6` is taken as 0 and no HP or status check is added: a downed or stunned player is stopped only through lost control (the panel closes and the poll needs an active, controlled player).
6. Casting uses the world clock of the previous tick (`now_ns` at input time), so locks are whole frames of the 60 Hz world clock.

**Tests (`make -C port check-fieldstage`, mode `technique`).** Level-1 Dorumon (`WAZALIST` = Petty Ice, row 5, 16 MP, DELAY 75, label `ice1`, action `HICEE1`): R1 opens the panel
on row 0; Cross on the next frame is swallowed (debounce); a press with 15 MP changes nothing and enters no sequence, and the next press 15 frames later is still locked while 16 frames later
it fires; a fire spends exactly 16 MP, enters `SQ_WAZA` (19 ticks, recorded 18 to 20) and never `SQ_ATCK1`; Cross and R1 inside the DELAY window do nothing and the second cast is accepted at
exactly `DELAY` frames; the list stays open after a cast; after R1 closes it Cross swings again; a cast pressed in `SQ_JUMP` waits for the landing with its MP spent. Per slot (the module is
driven directly with two slots): independent open flags, cursors (a six-entry list scrolls and stops at both ends), MP, locks and DELAYs (Venom 90 vs Ice 75).
**Enemy leg.** An `e_goburi` placed 9 units ahead takes the bullet (contact within three frames): one contact, bullet consumed, damage 44 against the 41 to 59 range of
`dw4_fight_p2e_damage` for attack 40005 / enemy row 0, and an unobstructed bullet ends by lifetime without a contact.

**Unresolved (retail checks).** Frame gap between two accepted casts for DELAY 75/60 and the 16-frame refusal lock; whether the stick walks with the panel open and moves the cursor; cursor
persistence across close/open and page switches; the real gate `s6` (guarding, stunned, bound, asleep, finisher); bullet spawn offset, speed, lifetime, whether it passes through the enemy or
stops on contact, wall behaviour, per-family starter delays against the 18-frame cast; casting while airborne and the deferral; the Triangle emergency heal (`GENEEMGHEAL`); stage flags that grey
rows (`NOHEALING` etc., colour 2); the item and status pages; Raise's receivers and support areas (see [Support technique wiring](#support-technique-wiring)); technique critical/stun rates.

## Status rules

### Status times (P2E cases 14-19)

Ported in `src/fightstatus_p2e.c` (`include/dw4/fightstatus.h`) from the matched source of `beNDMWGameRam::vfunc_34`; the stun weapon rule stays in `fightcalc.c`.
Internally tested by `check-fieldstage fightstatus` (consistency, determinism, bounds, draw counts); **not compared with retail**. Technique base number is
`attack % 10000`; the row is found through the player's WAZALIST; `S` = the player's `SKILL[pcTech.SKILL]`; every chance uses one draw `next % 1000` (unsigned), and
the duration on success is `pcTech.TIME + KASHIKOSA / 2` (0 is returned as -1). Columns were resolved from the ELF string table (read at the source's `DAT_` addresses).

| Case | Selector (`what`) | Result |
|---|---|---|
| 14 P2ESTUNTIME | none | The source has a single formula and **no technique branch**: `chance = (MAHIRITSU + 50·damage/MHP + 100 − RES_STUN)/2` per 100, time `(200 − RES_STUN)·(30·damage/MHP + 3·MAHIRITSU)/400` (`dw4_fight_p2e_stun_time`, weapon and technique alike). |
| 15 P2EPOISONTIME | `TIME` | chance `band(S, 750, 1000, 1200)·(1000 − enemy.RES_POISON)/1000`; draw; time as above. Other selector: `−(pcTech.HP / 5)`, no draw. |
| 16 P2ESLEEPTIME | none | chance `band(S, 550, 800, 1000)·100 / enemy.SEISHIN`; draw; time as above. |
| 17 P2EBINDTIME | none | identical to sleep (same enemy column `SEISHIN`, same bands). |
| 18 P2EATKDWNTIME | `TIME` | as sleep. `SUBAYASA`: `−max(pcTech.SUBAYASA − S/20, −enemy.SUBAYASA·80/100)`. `CHIMEIRITSU`: `−pcTech.CHIMEIRITSU`. `MAHIRITSU`: `−pcTech.MHIRITSU`. `KAIHIRITSU`: `−pcTech.KAIHIRITSU`. |
| 19 P2EPOWDWNTIME | `TIME` | as sleep. `TSUYOSA` / `MAMORI`: `−max(pcTech[col] − S/20, −enemy[col]·80/100)`. |

`band(S, b0, b1, b2)` = `S/4 + b0` for `S < 1001`, `(S − 1000)/5 + b1` for `S < 2001`, else `(S − 2000)/10 + b2`. An unknown selector in cases 18/19 leaves the reply empty
in retail (the port returns 1). Unresolved: the meaning of the unused fifth argument of case 14 and of the selector strings the Lua wrappers pass (taken from the
source's `strcmp` constants: `TIME`, `SUBAYASA`, `CHIMEIRITSU`, `MAHIRITSU`, `KAIHIRITSU`, `TSUYOSA`, `MAMORI`). The hit script applies the replies to the enemy's status
([Status wiring](#status-wiring)).

### Enemy-to-player status rules

`src/fightstatus_e2p.c`, `check-fieldstage fightstatus_e2p`.

FIGHTCALC cases 7-12 of the second switch of `beNDMWGameRam::vfunc_34`, ported from the matched source, strings and tables resolved from the
retail ELF. Not compared against a retail run: the test mode only checks internal consistency (bounds, `-1`/`0` for resisted, determinism
for a fixed stream, monotonic in the resisting stat). Every draw is `next % n` unsigned from the one engine stream, in source order. Output
convention (the value the retail rule appends to the messenger): `0` = effect did not land / no roll applies, `-1` = the effect landed but
the time rounded to 0 (retail turns 0 into -1), otherwise the time. `KT` = eneatk `KOUKATIME`, `KR` = `KOUKARANK`, `KASH` = enemy
`KASHIKOSA` (row = GetInt 1), `SEI` = player `SEISHIN`. Division by zero returns an error instead of the EE's undefined quotient.

| Case | Rule | Formula |
|---|---|---|
| 7 E2PSTUNTIME (player, row, attack, damage, rank) | eneatk `TYPE` selects the term: 0 (needs rank 1 or 2): `s8 = enemy.MAHIRITSU - down[2]`; 1: `s1 = eneatk.MAHIRITSU`, active if `s1 > 0`; 2: active at rank 1 or 2 | one draw `r = %100` when active: `lo = damage*50/MHP`; if `r < (MAHITEIKOU + lo + 100 + s1 + s8)/2` then `t = (MAHITEIKOU + lo + 30 + s1 + s8)/4`; `t == 0` becomes -1 |
| 8 E2PPOISONTIME (player, attack; string mode) | `TIME` with KOUKA `doku` | draw `%100`; if `r < DOKUTEIKOU + KR*15 + 30` then `t = DOKUTEIKOU/2 + KT`; 0 becomes -1; other KOUKA: 0, no draw |
| | `DAMAGE` | `MHP * KR / 100` (no draw) |
| | `GEDOKU` | eneatk `GEDOKU` (no draw) |
| 9 E2PSLEEPTIME (player, row, attack) | KOUKA `sleep` | `s0 = (KASH*3)/SEI + 100 - SEI/40`; draw `%10000`; if `r < KR*5*s0` then `t = KT*s0/100`; 0 becomes -1 |
| 10 E2PBINDTIME | KOUKA `ashidome` (bind) | `TYPE != 2`: same `s0`, draw `%10000`, lands if `r < KR*5*s0`, `t = KT*s0/100`; `TYPE == 2`: no draw, `t = KT`; 0 becomes -1 |
| 11 E2PATKDWNTIME (string mode) | `TIME`, KOUKA `freeze` | draw `%10000`; lands if `r < (KR*160/100)*s0`; `t = KT*s0/100`; 0 becomes -1 |
| | `SUBAYASA` / `MEICHURITSU` | write player `DOWNDATA[0]` / `[1]` = table `0x4cf5d8` / `0x4cf5e0` (only when the list is that long), recalculate the player (`FUN_003fab90(game, player, 1)`), then `v = clamp(KR + ((KASH*150)/SEI)/100 - SEI/80, 20, 80)`, result `property * v / 100` |
| 12 E2PPOWDWNTIME | `TIME`, KOUKA `powerdown` | identical to case 11 `TIME` |
| | `TSUYOSA` / `MAMORI` | `DOWNDATA[4]` / `[5]` = table `0x4cf5e8` / `0x4cf5f0`, recalculate, same `v`, result `property * v / 100` |

An unrecognised mode string appends nothing (the port returns 1). The DOWNDATA write plus recalculation is delegated to the caller through
`dw4_fight_status_ctx.apply_down` because it must happen before the property read.

Resolved strings: eneatk `0x5191d0 TYPE`, `0x5191f0 KOUKA`, `0x519200 KOUKARANK`, `0x519210 KOUKATIME`, `0x519228 GEDOKU`; KOUKA values `0x5191f8 doku`,
`0x519230 sleep`, `0x519238 ashidome`, `0x519248 freeze`, `0x519250 powerdown`; modes `0x5191b8 TIME`, `0x519220 DAMAGE`; player properties
`0x5189a0 MAHITEIKOU`, `0x5189b0 DOKUTEIKOU`, `0x518b78 DOWNDATA`.

Unresolved / caveats:

- The four tables `0x4cf5d8/e0/e8/f0` are single words that are only loaded (at `0x404564`, `0x4047ac`, `0x404d7c`, `0x404fc4`) and hold 0 in the
  ELF image; the port keeps them in `dw4_fight_status_down_value` as 0. If a live savestate shows another value, change that array. With 0 the
  DOWNDATA entry is zeroed and the result is only the (recalculated) stat scaled.
- The test picks the first eneatk row per KOUKA kind (doku 17, sleep 39, ashidome 18, freeze 41, powerdown 56); which enemies use which rows is not established. The hit
  script applies the returned times ([Status wiring](#status-wiring)).
- `dw4_fight_e2p_stun_time` in `fightcalc.c` is the same case 7 rule without the `0 -> -1` mapping; `dw4_fight_e2p_status_stun` is the faithful one and the one `BLPgetStunTime` uses.
- The calling Lua (`BLPgetStunTime` etc.) and the attacker `_downDataList` entries (`mahi_down`) are inputs here, not recovered state.

## Status application on models

Read from the retail disassembly (`asm/Gap__Bec__beNDMWMdlPEBase__vfunc_46.s`, `..._vfunc_47.s`, `FUN_00445c60/4456c0/445990/3a7a20/3a7e90/3a8580`; the
Lua side from `lua/`); implemented in `src/statusapply.c` (`include/dw4/statusapply.h`), tested by `check-fieldstage statusapply`. The times and values come
from the hit script (`BLT/BLPget*Time` results, see [Status rules](#status-rules)); the model only stores and counts them down. How the running fight reaches it is under
[Status wiring](#status-wiring).

**Who does what.** The hit script applies a status with `be:MDLsetSD("SETxxx", "I<a>/I<b>/...")` (SD message to the model) and chooses the reaction sequence itself
(`MDLsetSeq("SQ_STUN")`, `MDLsetSeq("SQ_SDMG")`, ..., `MDLaddHp`, `MDLdspDamage`). Scripts that only read the state call `MDLisStatus(name, ramNo, "BIND")` (the only name used).
The native model class `beNDMWMdlPEBase` (vfunc_47 @0x445d10 handles the messages, vfunc_46 @0x443bd0 is the per-frame update) owns the numbers. Other messages sent by scripts:
`CLEARSTATUS` (boss phase changes), `ALLCLEARSTATUS` (stage end, `sd("PLAYER", nil, -1, ...)`), `SETMETAL` (event scripts, players); `SETRAREICON` is native-only.

**Message table** (names @0x4caa00; jump table @0x51d510; case = index): 0 SETPOISON, 1 SETSLEEP, 2 SETSTUN, 3 SETBIND, 4 SETATTACKDOWN, 5 SETPOWERDOWN, 6 SETRAREICON,
7 SETSPEEDUP, 8 SETPOWERUP, 9 SETREFRACT, 10 SETMETAL, 11 CLEARMETAL, 12 CHECKSTATUS, 13 CLEARSTATUS, 14 ALLCLEARSTATUS, 15 GETPEBASEWORK. The status enum (@0x4ca9a0) is the
`_timerList` index: 0 POISON, 1 ATTACKDOWN, 2 POWERDOWN, 3 BIND, 4 REFRACT, 5 SPEEDUP, 6 POWERUP, 7 METAL, 8 SLEEP, 9 STUN, 10 RARE. The lists are created on first use
(0x445e68..0x446668): `_dispRamNoList` and `_dispPosNoList` 12 entries of -1, `_timerList` 12 zeros, `_isFirstList` 11 bytes of 0. **CHECKSTATUS / `MDLisStatus` is exactly
`_timerList[id] != 0`** (0x447108): a status set with time 0 does not report as set.

**Applying (vfunc_47).** Every SETxxx writes `_isFirstList[id] = 1` and `_timerList[id] = argument 0`, except poison. A second application overwrites the first (no stacking, no
maximum): the next tick re-arms the named timer from zero with the new time. Stat arguments overwrite the slot values; they are not added. Times are **frames at 60 per second**: the
tick arms a named timer `time * 1e9 / 60` ns long (0x22e4b8 is the signed 64-bit divide).

| Message | Timer / flag | Values written |
|---|---|---|
| SETPOISON `I<t>/I<dmg>[/I<end>]` (0x4466c8) | `_timerList[0] = t / 120 + 1` (signed division; the number of two-second ticks plus the one consumed at the start) | `_poisonDamage` (+0x100) = dmg; a third argument (players) goes to `_poisonEndurance` (+0x104) - **no reader found in the model class** (the Cure rule reads it, see [Area queries](#area-queries-and-healcureraise-application)) |
| SETSLEEP `I<t>` (0x446790), SETSTUN (0x4467f8), SETBIND (0x446860) | `_timerList[8 / 9 / 3] = t` | - |
| SETATTACKDOWN `I<t>/I<a>/I<b>/I<c>/I<d>` (0x4468c8) | `_timerList[1] = t` | `_downDataList[0..3] = a,b,c,d` = SUBAYASA, CHIMEIRITSU (critical), MAHIRITSU (paralysis/stun), KAIHIRITSU (evasion) |
| SETPOWERDOWN `I<t>/I<a>/I<b>` (0x446a40) | `_timerList[2] = t` | `_downDataList[4] = a` (TSUYOSA, attack), `[5] = b` (MAMORI, defense) |
| SETSPEEDUP (0x446b48) / SETPOWERUP (0x446cc0) / SETREFRACT (0x446e00) | `_timerList[5 / 6 / 4] = t` | `_upDataList[0..3]` / `[4..6]` / `[7..10]` = the following arguments |
| SETMETAL (0x446f78) / CLEARMETAL (0x447000) | `_timerList[7] = 1` / 0 | `_downDataList` created if missing; slot 6 write is dropped (see below) |
| SETRAREICON `I<rank>` (0x4470a0) | `_timerList[10] = rank` | icon only |

The `_downDataList` slot meaning is confirmed from the readers in the matched `beNDMWGameRam::vfunc_34` (data[3] = evasion in P2E hit, [5] defense in P2E damage, [4] attack and
[1] critical in E2P damage, [2] in E2P stun time); the written values are the positive "reduction" numbers the status-time functions return (`P2EATKDWNTIME` returns
`-max(...)`, a positive reduction). A negative or zero element is simply stored; the fight rules subtract it (`enemy.TSUYOSA - down[4]`). Writes are guarded by the list
count (`slti`): for a non-player model `0x4456c0` allocates `_downDataList` with **6** entries and `0x445990` `_upDataList` with **7**, so the REFRACT slots 7..10 and the METAL
slot 6 are silently dropped (the timers still run). For a player model both lists are fetched from the player's game-RAM record (`GAMERAM GETPLAYER` fields `DOWNDATA` /
`UPDATA`, strings @0x51d4d8/0x51d4e8) and, after every stat-changing message and every expiry, `0x445c60` sends `GAMERAM RECALCPLAYER` so the player's derived stats are rebuilt.

**Per-frame update (vfunc_46).** Every block is guarded by the byte at InfoWork+0x44, `_isOnCtrl`, written by ONCTRL / OFCTRL (port: `ready`, set from `actor.enabled`). A model whose HP object (+0x0c) is 0 loses every
timer (`_timerList` all 0, icons erased with `MODELCTRL SQ_ERAS`, 0x443cf8); the isFirst flags, named timers and the lists are left. Otherwise, in this order:

- **POISON** (0x443f10). `_isFirstList[0]`: arm the named timer `POISON` for `0x77359400` ns (2 s), `_timerList[0] -= 1`, flag cleared. When the timer has elapsed (strictly more than the
  duration): `HP = max(HP - _poisonDamage, 0)` - the model pays itself; no damage number and no hit reaction. For a player the HP meter (`METERCTRL hpmt SETPERCENT`, `NUMBERCTRL hpnm
  SETVALUE`) is updated. If HP > 0: `_timerList[0] -= 1`, ending (timer 0, named timer deleted) at <= 0, otherwise re-armed for 2 s. If HP reached 0: a player is sent `SQ_DEAD`;
  **an enemy's HP is set to 1** (poison cannot kill it); the status ends in both cases. A start value below 120 frames therefore never ticks (timer 1 minus the start tick = 0).
  Total ticks = `t / 120`, at 2 s intervals starting 2 s after the status started.
- **SLEEP** (0x4441e8). First frame: arm `SLEEP` (`t` frames) and, unless the current sequence name (InfoWork+0x14, compared with `igStrCmp`) is already `SQ_SLEP`, send `SQ_SLEP`. On expiry send
  `SQ_WAIT`, delete, `_timerList[8] = 0`. The sequence-change hook `FUN_00445200` (below) cancels the sleep when any sequence other than `SQ_SLEP` starts, so the script's `MDLsetSeq("SQ_xDMG")` wakes the sleeper.
- **STUN** (0x444340). The whole block (arming and expiry) runs only while the current sequence is `SQ_STUN`; the E2P zero-damage script sets that sequence right before `SETSTUN`, the damage paths do NOT (the hook turns the damage sequence's `JUMP SQ_WAIT` into `SQ_STUN`). Duration `t` frames,
  expiry sends `SQ_WAIT`. The hook ends the stun (timer removed, flag and time cleared) when any sequence other than `SQ_WAIT` or `SQ_STUN` starts. Duration source: `BLTgetStunTime` /
  `BLPgetStunTime`, the argument of `SETSTUN`.
- **BIND** (0x444480). Timed movement lock for `t` frames; expiry sends `SQ_WAIT`.
  The list at InfoWork+0xc8 contains movement channels. Every channel except Y
  (index 1) has `_isRun` and `_speed` cleared when the current sequence is absent
  from the damage enum. HITBOX delivery continues. BIND retains the current sequence until expiry; sequence
  retention does not imply continued walking. See the
  [verified gate](#bind-movement-and-enum-gate).
- **ATTACKDOWN / POWERDOWN / SPEEDUP / POWERUP / REFRACT** (0x444628..0x444e20). First frame: arm the named timer (`ATKDOWN`, `POWDOWN`, `SPEEDUP`, `POWERUP`, `REFRACT`) for `t` frames.
  On expiry: timer 0, named timer deleted, the slots the message wrote are set to 0 (down[0..3] / down[4..5] / up[0..3] / up[4..6] / up[7..10]) and the player recalculation runs.
- **METAL** (0x444e20). Partly read, not ported: the first frame zeroes down[6] and arms `METAL` with 0 ns; each expiry adds 4 to down[6] and re-arms for `2 * ATTACKDELAY` seconds
  (`120 * ATTACKDELAY / 60`, ATTACKDELAY from `GAMERAM GETPLAYER`); with the 6-entry enemy list the write is dropped. Purpose unresolved.
- **Icons** (0x444fc8). Statuses 0..7 that are set take consecutive positions 0,1,2,... in enum order (`_dispPosNoList`); 8 (sleep), 9 (stun) and 10 (rare) are shown without a position;
  `_timerList[11]` is set to 1 when any of 0..7 is set (the icon frame, `i_stdownic00`). A status that is no longer set has its icon erased and `_dispRamNoList[i] = -1`.
  Icon names @0x4cfc50: stdownic01..05, 09, 10, 06..08 for statuses 0..9, `i_rareicon` (10), `i_stdownic00` (11); `_dispRamNoList[i]` is the model's display id for the icon object.

**CLEARSTATUS** (0x447608) deletes SLEEP, STUN and BIND (flags and timers) and sends `SQ_WAIT`. **ALLCLEARSTATUS** (0x4471a8) first does the same for POISON, ATTACKDOWN, POWERDOWN,
SPEEDUP, POWERUP and REFRACT, zeroes both lists, runs the player recalculation, then CLEARSTATUS. Neither touches METAL or RARE.

**The sequence-change hook.** `beModelCtrl::vfunc_33` (`asm/Gap__Bec__beModelCtrl__vfunc_33.s`) resets the control kind (+0x3c), phase (+0x40) and wait name (+0x4c) on every by-name sequence set (0x39816c..0x3981e8), runs the command runner `FUN_00395250`
and then calls vtable slot 44 (`lw t9,184(t9)` at 0x3983f4). For `beNDMWMdlEnemy` and `beNDMWMdlPlayer` slot 44 (`vfunc_44`, 0x3d1ce0 / 0x3d4390) is `FUN_00445200` (`igStrCmp` 0x12a4a4 returns 0 when equal). The JUMP executor `FUN_00394ae0` calls slot 33, so a JUMP takes the same path. The hook:
HP 0 (and the lists exist): every timer zeroed, icons erased; else if `_timerList[8]` (SLEEP) is set and the new sequence is not `SQ_SLEP`: the SLEEP named timer is removed, flag and timer cleared; else if `_timerList[9]` (STUN) is set: new sequence `SQ_WAIT` -> the model is sent `SQ_STUN`,
`SQ_STUN` -> unchanged, any other -> the STUN timer removed, flag and timer cleared. Consequences: damage wakes a sleeper (the hit script's `MDLsetSeq("SQ_xDMG")`); the **damage-path stun** works because `SETSTUN` arrives during `SQ_MDMG` / `SQ_LDMG` (the scripts do not set `SQ_STUN`, only the E2P zero-damage branch does),
whose `JUMP SQ_WAIT` runs the hook and becomes `SQ_STUN`, after which the manager's STUN block arms. Sleep expiry (0x4442e8..0x444340) sends `SQ_WAIT` first, then zeroes the timer (the hook cancels first; same net result);
stun expiry (0x444420..0x444478) zeroes the timer and removes the named timer first, then sends `SQ_WAIT`, so the hook does not redirect it.

**InfoWork+0x44 is `_isOnCtrl`.** ONCTRL / OFCTRL write `sb ...,68(s0)`; `vfunc_46` tests `lbu v1,68(s0)` at 0x4441e8, 0x444340, 0x444480 and 0x444628; `FUN_00391cf0` calls the control hook (slot 38) only when it is set. No store to +0x44 exists in `vfunc_46`, `vfunc_47` or `FUN_00445200`: SETSTUN / SETSLEEP / SETBIND do not touch it.
The port's `ready` is set from `actor.enabled`. The blocks do not run while control is off; the port's named-timer clock keeps running meanwhile (assumption), so a status that would have ended meanwhile ends on the first tick after `ONCTRL` (`statusflow_e2p`).

**The movement and input lock is structural.** The per-frame manager 0x395b50 (`Gap__Core__igObject__vfunc_31.s`) runs the control consumer `FUN_00391cf0` only when InfoWork+0x3c (control kind) is non-zero, then vtable slot 46 (the status update), then movement `FUN_00392fa0`; none of 391cf0 / 392fa0 / 3951e0 / 3926d0 / 394bf0 reads the status lists.
The by-name set zeroes +0x3c / +0x40, and in the census of the retail sequence programs `e_goburi` `SQ_SLEP` and `SQ_STUN` are `HITBOX Set` + `MOVE Stop` + `ACTION` only, `p_dorumon` `SQ_SLEP` is `MOVE Stop` + `MOVE Fall` + `ACTION`, `SQ_STUN` `MOVE Stop` + `ACTION`: no `CTRL`, `AIMAP`, `WCHECK` or `JUMP` (`SQ_WAIT` has `CTRL toWalk`).
A sleeping or stunned model therefore cannot walk, and its AI / stick control is off for as long as it stays in that sequence. The port needs no status check in the input path (`statusflow_e2p`: stick held 60 ticks while asleep moves the player 0.000 units; `ai_tick` already gates on `actor.control`).

### BIND movement and enum gate

BIND's `444480..444628` block stops movement outside the damage-sequence enum.
`beModelCtrlInfoWork._moveObjectList` is at +200; each entry is a
`beModelCtrlMoveObject`, with `_isRun` at +8 and `_speed` at +28. The loop clears
only those two fields on every entry except index 1 (Y). It preserves vertical
jump/fall motion, acceleration, mode, duration and sequence-stop parameters.
There is no HITBOX/subcommand access in this block, so the port suppresses no
attack volume of a bound model on either side.

`3c03e0` builds the ten-entry enum from `4ca940`/`4ca970`: `SQ_SDMG`, `SQ_MDMG`,
`SQ_LDMG`, `SQ_DDMG`, `SQ_DEAD`, `SQ_SDMGC`, `SQ_SDMGF`, `SQ_SDMGI`, `SQ_SDMGT`
and `SQ_SDMGD`. `igMetaEnum_GetValueByName` writes two separate outputs: lookup
status and enum value. `4445d4` compares the status with `4fb410`, so **every
found name bypasses the stop**, including `SQ_SDMG` with enum value zero.
Startup `2d16c8..2d16e0` initializes success `4fb410` to zero and failure
`4fb418` to one. Both were zero in the static ELF image; using the uninitialized
image without startup concealed the missing-name branch. This is static and
instruction-execution evidence, not a live-memory observation.

Native `dw4_status_bind_movement` reads the actual PE Work timer, control flag,
sequence name and channel list. Active, unfrozen model updates apply it after
control/AI and before movement, preventing a newly issued walk command from
bypassing the stop. Damage-sequence channels continue. `OFCTRL` bypasses this
status gate, and frozen/inactive models do not run it. BIND expiry uses
`3a7e90`'s strict comparison with both clock samples truncated to 2^18 ns steps.
Expiry clears the status and requests `SQ_WAIT`; clear messages also release the
gate. Other status clock-source and complete manager-order questions remain open:
the host status timer/HP pass precedes model control, while this
movement consumer is placed after control. This does not establish full retail
status-manager scheduling or complete combat parity.

`make -C port check-bind-retail` executes the original startup status stores,
BIND branch and enum lookup against 1,140 combinations of names, control flags,
positive/negative/zero timers, first-use/expiry states and lists of 0, 1, 2, 4 and
7 channels. The full 44-byte channel payload is compared, including padding and
unrelated retained state. Enum allocation, string/list access and timer/sequence
services are controlled leaves. A further 100 timer-boundary cases execute the
original timer routines and compare native BIND expiry at the sampled clocks.

Native actor checks cover arena ownership, frozen/control gates, preservation of
Y motion and cleanup. The original-script `statusflow_e2p` regression requires a
bound player to remain horizontally stationary under stick input and still hit
and damage an enemy; attacks also work after `ALLCLEARSTATUS`.

### Storage

Player/enemy Work owns its timer/first/icon/down/up lists, poison values
and named RAM timer records. The status rules are call-local
projections; public status pointers are read-only compatibility snapshots.
Player-record load/store callbacks are the stat mirror.
Typed health records preserve the callback/native-write precedence,
including zero-max GENERATE initialization. See [ownership validation](arena-object-model.md#model-controller-actor-and-status-work).
The arena storage does not close the timer-domain and icon fidelity gaps listed under [Unresolved](#unresolved-status).

### Status wiring

The status modules ([Status rules](#status-rules) and the model state above) are called from the running fight. Evidence is the retail disassembly and Lua bytecode; everything the port prints is **the port's own output, not retail-measured**.
Tests: `check-fieldstage` modes `statusapply` (unit: hook, list sizes, ready gate, contact wrappers), `statusflow` (goblin, headless `stag0101`) and `statusflow_e2p` (the starter as target).

**What is wired.**

| Piece | Where | Behaviour |
|---|---|---|
| Status work per model | `struct dw4_modelctrl` (`modelctrl.c`), accessor `dw4_modelctrl_status`, `dw4_controllers_status` | Enemies (`KIND_ENEMY`) and players (`KIND_PLAYER`) own a `dw4_status`; objects, NPCs and bullets have none. Re-initialised on `GENERATE` of an inactive slot and on remove, so nothing leaks into a respawn |
| `MDLsetSD` messages | `dw4_modelctrl_service` | `SETPOISON/SLEEP/STUN/BIND/ATTACKDOWN/POWERDOWN/SPEEDUP/POWERUP/REFRACT/RARE` (n = 5) and `CLEARSTATUS` / `ALLCLEARSTATUS` (n = 4) call `dw4_status_message`; ignored on an inactive slot like the other direct messages; a bad argument string is an error |
| `MDLisStatus` | `hubruntime.c` / `engine.c` bindings, `querySD` in `modelctrl.c` | `MDLisStatus(name, ram, status)` is the message `MODELCTRL <name> <ram> CHECKSTATUS <status>` (`asm/MDLisStatus.s` 0x374410: SelectReceivers, AppendString, Dispatch; the reply is read as a bool when exactly one answer came back). `CHECKSTATUS` is `_timerList[id] != 0` (0x447108). |
| Sequence-change hook | `status_hook` after `start_sequence` and after any `dispatch` that selected another sequence (JUMP, script) | `FUN_00445200`, see below |
| Per-frame manager | `dw4_modelctrl_status_tick`; enemies: `dw4_controllers_tick` before each model's tick; players: `dw4_combat_status_tick`, called from the hub tick right before `dw4_controllers_tick` | One `dw4_status_tick` per simulation tick on the model's own clock (a frozen model holds it); `ready` = the model's control flag; the result's sequence (`SQ_SLEP`, `SQ_WAIT`, `SQ_DEAD`) is started when the model has it |
| Poison | enemies: the receiver's script-visible HP; players: the record's `HP` | An enemy is floored at 1 HP and the status ends; a player at 0 gets `SQ_DEAD` (the [KO flow](#ko-the-capsule-and-game-over) then runs) |
| P2E status times | `modelcontact.c` + `combat.c: p2e_status` | `BLTget{Poison,Sleep,Bind,AttackDown,PowerDown}Time` answer 0 **without calling the rule, drawing nothing,** unless the attack is a technique (`attack / 10000 == 4`) of the wrapper's own base number: 20, 90, 95, 70, 85 (src/lua/combat.cpp 0x374de0, 0x374f00, 0x375010, 0x375120, 0x375240). Otherwise the rule runs with the shooter's context and the target's enemy row. Poison, attack-down and power-down take the selector string, sleep and bind none |
| E2P status times | `modelcontact.c` + `combat.c: e2p_status`, `apply_down` | The BLP wrappers do not gate (the rules answer 0 for a row whose KOUKA does not match): sleep/bind `(player, enemy row, attack)`, poison `(mode, player, attack)`, attack/power-down `(mode, player, row, attack)` (api.c:451-523). `BLPgetStunTime` is the faithful `dw4_fight_e2p_status_stun` (0 / -1 / time) with the attacker's `down[2]`. The `apply_down` hook of the attack/power-down modes writes the record's `DOWNDATA[slot]` (7 entries) and runs `dw4_playerstats_recalculate`, always, before the stat is read |
| `_downDataList` readers | `combat.c`, via `receiver_status` / `source_status` in `dw4_model_contact` and `dw4_model_bullet.source_status` | P2E hit uses the RECEIVER's `down[3]`, P2E damage `down[5]`; E2P damage the ATTACKING enemy's `down[4]` and `down[1]`, E2P stun its `down[2]`. These are the only five readers (`vfunc_34` lines 2823, 2967, 4166, 4250, 4613); the P2E time rules (cases 15-19) read no list. `is_hit` / `damage` / `e2p_damage` / `e2p_stun` of `dw4_model_fight` take a `const dw4_status *` argument |
| Player lists | `combat.c: host_load / host_store` through `dw4_status_player_host` | A player's lists are its record's `DOWNDATA` (7) and `UPDATA` (11), not copies: loaded into the status before every message, tick and hook, stored back when `lists_dirty`, and every result with `recalc_player` runs the recalculation (0x445c60). `dw4_status` is sized 6/7 for an enemy and 7/11 for a player |
| Bind movement lock | `dw4_status_bind_movement`, after model control/AI | Clear horizontal/turn channel activity and speed outside the damage enum; preserve Y and HITBOX delivery |
| `ALLCLEARSTATUS` | `lobby.c` passes it on | `be:sd('PLAYER', nil, -1, 'ALLCLEARSTATUS')` (98 stage and gate chunks) reaches the player's status; like `CLEARSTATUS` it ends with `SQ_WAIT` (0x447608 sends it unconditionally to a model that has work; the port skips the start when the model is already in `SQ_WAIT`) |

Seams for tests: `dw4_combat_fight` (the rules as a `dw4_model_fight`), `dw4_combat_hit_player` (one synthetic enemy bullet through the real `hit_p` chunk, geometry skipped),
`dw4_hubruntime_combat_owner`, `dw4_controllers_status`. The slots `attack_element` and `p2p_magic` of `dw4_model_fight` are filled by the [support technique wiring](#support-technique-wiring).

**Port API.** `dw4_status_init(&s, is_player)`; `dw4_status_message(&s, "SETPOISON", "I<300>/I<7>", &r)` for the hit script's `MDLsetSD` string (or the typed `dw4_status_set_*`);
`dw4_status_tick(&s, dt_ns, current_sequence, &hp, &r)` once per frame (the result carries the sequence to request, the poison damage, the KO and the expired mask);
`dw4_status_check(&s, "BIND")` for `MDLisStatus`; `dw4_status_down(&s, DW4_DOWN_EVASION)` etc. for the fight rules; `dw4_status_apply_down_slot` is the `apply_down` hook of the E2P status rules.

**Verified facts about the scripts.**

- Only two chunk families set statuses: the BLT-bearing enemy hit chunks (209 chunks) and the BLP-bearing player hit chunks (83); `ALLCLEARSTATUS` appears in 98 stage / gate chunks (`lua/06-dungeon-1/01-dng101b1_e179/001-dm-run.lua:7`), `SETMETAL` / `CLEARMETAL` in 10 event chunks, `MDLisStatus` in 249 chunks and only ever asks `'BIND'`. (`lua/` drops the result assignments of Lua 4.0 stack locals, so the call sequences come from `scripts/lua_dump.py` bytecode of `NDMW.AFS`, read-only.)
- The enemy hit chunk (`NDMW.AFS` entry 614 = `stag0101`, chunk 38) for damage 0: `BLTgetSleepTime`, then (while the result is 0) `BLTgetBindTime`, `BLTgetAttackDownTime('TIME')` (then `'SUBAYASA'`, `'CHIMEIRITSU'`, `'MAHIRITSU'`, `'KAIHIRITSU'` -> `SETATTACKDOWN I<t>/I<a>/I<b>/I<c>/I<d>`), `BLTgetPowerDownTime('TIME')` (then `'TSUYOSA'`, `'MAMORI'` -> `SETPOWERDOWN`); a failed chance roll returns -1 (stops the chain), a technique that is not that status returns 0 (the chain goes on).
  With damage > 0: rank < 3 and `MDLisStatus(..., 'BIND') == 1` forces `SETLABEL` / `SQ_SDMG`; rank 1 or 2 asks `BLTgetStunTime`; any rank but 3 then `BLTgetBindTime`, and `BLTgetPoisonTime('TIME')` / `('DAMAGE')` -> `SETPOISON I<t>/I<d>`. `SETSTUN` there is NOT preceded by `MDLsetSeq('SQ_STUN')`.
- The player hit chunk (entry 614 chunk 3; kinds 80000-89999 are the support branch): for damage 0 only kinds 70002 / 70046 ask the stun (`MDLsetSeq('SQ_STUN')` then `SETSTUN`), then the sleep, bind, attack-down and power-down chain; with damage the rank picks `SQ_xDMG` with `SETLABEL`, rank != 3 asks stun, bind and poison (`I<t>/I<damage>/I<GEDOKU>`: the third argument is a player's `_poisonEndurance`).
  `hit_p` / `hit_e` are shared by every species / enemy: stag0101 has one BLT hit chunk and one BLP hit chunk, the chunk-to-name mapping (`hit_e_goburi.lua`, `hit_p_<species>.lua`) was not verified.

**Assumptions and inferences (not verified).**

- BIND does not suppress attack volumes: `_moveObjectList` is movement state, not HITBOX state ([BIND movement and enum gate](#bind-movement-and-enum-gate)).
- Whether a stunned or sleeping player can break out with a button press: `beNDMWMdlPlayer::vfunc_38` (0x3d22f0-0x3d3160) has no status test, so a press would request `SQ_ATCK1` / `SQ_JUMP` and the hook would cancel the status. The port leaves the input ungated (the hub's Cross handler excludes only `SQ_JUMP` / `SQ_FALL`); inference from absence in the disassembly, not a measurement.
- Enemy `SPEEDUP` / `POWERUP` / `REFRACT` and `down[0]` (SUBAYASA) have no gameplay reader in the model or FIGHTCALC code: presumably inert for enemies. For a player the effect is only through the record recalculation.
- The named timers run on the model's own clock (`dw4_modelctrl_now`, frozen by `ONFREEZE`), like the port's HITBOX timing; the retail clock domain is not established. The retail comparison also quantises elapsed time in 2^18 ns steps, reproduced for BIND and the three support buffs; other status durations may differ by a frame (`statusflow`: a 1250-frame sleep ends after 1249 frames, a 175-frame stun lasts 176).
- The status tick of a player writes the record's HP only. Retail's poison block also updates the HP meter and number for a player (`METERCTRL hpmt SETPERCENT`, `NUMBERCTRL hpnm SETVALUE`, see the per-frame update above); the port's status tick sends neither.
- `dw4_status` and `dw4_buffs` ([Buff application, timers and expiry](#buff-application-timers-and-expiry)) both implement `SPEEDUP` / `POWERUP` / `REFRACT`. The model's `SETSPEEDUP` / `SETPOWERUP` / `SETREFRACT` messages go to `dw4_status`, the one owner per model class, so the record's `UPDATA` is written once; `dw4_buffs` is the reference model ([Support technique wiring](#support-technique-wiring)).

**What the tests show (port output).** `statusflow`: a landed Sleep (base 90, pcTech TIME 1200 + KASHIKOSA/2) puts the goblin in `SQ_SLEP` on the next frame (`MDLisStatus`-style query 1) and releases it after 1249 frames; a weapon hit on the sleeper ends the sleep; a weapon hit of rank >= 1 with a raised `MAHIRITSU` sets `SETSTUN 175` during `SQ_MDMG`, the goblin enters `SQ_STUN` 17 ticks later and leaves it after 176; a bound goblin hit below rank 3 plays `SQ_SDMG` instead of `SQ_MDMG`;
Venom (base 20) lands `SETPOISON` with `-(pcTech HP / 5)` per tick (16), ticks at 20 HP leave 4 and then the floor of 1; Freeze (70) and Power Down (85) write `down[0..5]` = (80, 3, 3, 5, 12, 72) which equal the selector replies, the next weapon hit's HP loss equals the P2E rules replayed on a copy of the random stream with the status values (2191 against 437 with no down values: a Power Down of 72 on the goblin's defense), and both lists return to 0 on expiry;
REMOVE / GENERATE clear every timer. `statusflow_e2p`: the five effect rows (doku 17, sleep 39, ashidome 18, freeze 41, powerdown 56) through the real `hit_p` chunk land `SETPOISON` (damage `MHP*KOUKARANK/100`, endurance = `GEDOKU`), `SETSLEEP` (`SQ_SLEP`, stick moves nothing, `OFCTRL` holds it, `ONCTRL` ends it), `SETBIND`, `SETATTACKDOWN` / `SETPOWERDOWN` (the record's `DOWNDATA` becomes (30, 40, 0, 0, 47, 55, 0) and SUBAYASA 60 -> 30, TSUYOSA 94 -> 47, MAMORI 110 -> 55; `ALLCLEARSTATUS` restores them);
a strength down on the attacking goblin lowers the E2P damage by the replayed amount; poison takes the record's HP every 120 frames (170 -> 165 -> 160) and a tick that reaches 0 sets `SQ_DEAD` and, through the KO flow, the Terminal request. `dw4_fight_status_down_value` is 0, so the DOWNDATA slots the E2P rules write before reading are zeroed first.

### Unresolved (status)

1. Whether the retail player can break `SQ_STUN` / `SQ_SLEP` by pressing a button: `vfunc_38` has no status gate (0x3d22f0-0x3d3160) but a live check is needed.
2. The complete status-manager clock and ordering (the BIND list and enum are resolved above).
3. Whether JUMP goes through exactly the same by-name branch of `vfunc_33` as `MDLsetSeq`: `FUN_00394ae0` calls slot 33 with the target name; the branch at 0x398068 was read only as far as the hook call at 0x3983f4. The port runs the hook after the whole `dispatch` that selected a new sequence, not inside each nested JUMP.
4. The retail clock domain of the named timers (engine clock vs per-model, behaviour under hit-stop, menus, slow motion and pause; the port advances an explicit nanosecond clock).
5. The values of the E2P DOWNDATA tables 0x4cf5d8/e0/e8/f0 at run time and what an unmatched selector (rule return 1) makes the Lua wrapper return (the port fails the call loudly).
6. Which hit chunks carry which name (`hit_e_goburi.lua`, `hit_p_dorumon.lua`, the other 15 `hit_p_*`) and where the `bht_x_*` bullet scripts live: no status call exists in any chunk other than the shared BLT / BLP hit chunks (the `bht` bodies in this pack are `MDLsetSeq("SQ_ERAS")`).
7. The names of pcTech rows 20 / 70 / 85 / 90 / 95 (Poison / Attack Down / Power Down / Sleep / Bind) are inferred from the technique-family numbers, not read from the table.
8. Who consumes enemy-side `SPEEDUP` / `POWERUP` / `REFRACT` and `down[0]`.
9. METAL's purpose (the player lists' sizes are 7 and 11, the record's) and any reader of `_poisonEndurance` in the model class; the area radius (30) and caster handling for `BLPcalcKoukaMagic` are read from the retail code ([Area queries](#area-queries-and-healcureraise-application)) but unmeasured in a real multi-player session.
10. Whether `GetInt` of a missing script argument reads 0 (the port rejects malformed strings).
11. Who sets RARE ranks other than the spawn code.

## Support techniques

### Support rules and the attacker's element

`fightmagic.c`, `fightmagic.h`; FIGHTCALC cases 20 `P2PKOUKAMAGIC` and 21 `GETPATKZOKUSEI`, ported from the
matched source (`check-fieldstage fightmagic`: hand-computed values at level 999, all SKILL 9999, KASHIKOSA 9999). The status-time rules of the same port
(`fightstatus_p2e.c`, `fightstatus_e2p.c`) are under [Status rules](#status-rules); their tests check internal consistency only.
Strings were resolved from the retail ELF data. The outputs are the integers the source appends to its messenger sends; the sends themselves (the PLAYER area query around the
caster's GETMATRIX, the SET*/RAISE receiver calls) are applied by `magicapply.c` and the status owner (below), the `x_250*hit00` effect particles are not ported. No rule uses a random draw except the poison cure.
- Element (case 21, args player, attack): `attack / 10000 == 4` → the learned row's `ZOKUSEI` string (`fire`/`ice`/`thunder`/`dark`/`poison` = 0..4, anything else −1); otherwise the player's `ATTACKZOKUSEI` property.
- Case 20 (args caster, target, attack) does nothing unless target == caster; the family is `attack % 10000` (C remainder, so −50 stays −50) and the row is the learned WAZALIST row of that base number. Rows are tiers (row − base = 0..4).
- Heal Lt 40 / Heal 45: `ΔHP = row.HP + SKILL[row.SKILL] + KASHIKOSA` (no division), applied to the caster with the HP-gauge rule `FUN_003f9c80` (ignored when HP is 0, clamp to 0..MHP); Heal also repeats it for each player the area query returns (the caster is not appended there).
- Cure Lt 55 / Cure 60 (poison): per poisoned target (`FUN_00447b00`), `(row − base + 5) − poison endurance >= rand % 10` cures it (`FUN_00447b40`); one draw per poisoned target in list order, the caster first; Cure also covers the area.
- Raise 50 (revive, area only, caster not included): sends RAISE(matrix, a, b) with table pairs (a, b) {59,68,77,86,95} and {100,400,1600,3200,6400} (equal to the row's HP column); attack −50 (item) sends {59,100}.
- Speed 65 (SETSPEEDUP, area with the caster appended, per target): `TIME + KASHIKOSA`, `SKILL[row.SKILL]/5 + row.SUBAYASA`, row `CHIMEIRITSU`, `MHIRITSU`, `KAIHIRITSU`.
- Power 80 (SETPOWERUP): `TIME + KASHIKOSA`, `SKILL/5 + TSUYOSA`, `SKILL/5 + MAMORI`, `SKILL/5 + MAXHP` (row columns). Resist 75 (SETREFRACT): row `TIME`, `FIRE`, `ICE`, `THUNDER`, `DARK`.
- Rows 70..74 and 81..84 (other families) are not handled by this case. The Lua wrappers `BLPcalcKoukaMagic` and `BLPgetAttackZokusei` are wired to these functions
  ([Support technique wiring](#support-technique-wiring)); `BLPgetDamageValue` is the E2P rule.

**Retail spot check, the one value that is directly readable: Heal Lt** (pcTech row 44, HP 19200) cast from the R1 list
on the player with HP set to 1000 gained exactly `row HP + SKILL[7] + KASHIKOSA` in every cast: 39198 (SKILL 9999 / KASHIKOSA 9999, 8 casts), 21001 (1234 / 567), 19300 (0 / 100), 34199 (5000 / 9999), and 960 MP each; the port's
`dw4_fight_p2p_magic` returns the same four values (`check-fieldstage retail`). **Not measured:** poison/sleep/bind/stun/attack-down/power-down durations and chances (no technique with those effects in the Susanomon list; the E2P ones
need the enemy attacks that inflict them), Speed/Power/Resist durations and magnitudes, Cure's poison-cure rate, Raise, the area rules (radius, caster inclusion), and how the receivers apply the numbers.

### Area queries and heal/cure/raise application

Source: FIGHTCALC case 20 in `Gap__Bec__beNDMWGameRam__vfunc_34` (`src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp`), checked against the retail disassembly. Ported as `src/magicapply.c`
(`check-fieldstage magicapply`: hand-computed values from the evidence below; self-consistency only, **not retail-measured**).

**The PLAYER area query** is `beNDMWGameRam_CollectNearbyNonzeroHp` (0x3fc780, `src/game/beNDMWGameRam_CollectNearbyNonzeroHp.inc`). Heal, Cure and the buffs call it with group `"PLAYER"` (0x5190a8) and `excluded` = the caster's
player index; Raise calls it with group `"PLAYER2"` (0x519290) and `excluded` = -1.
- Centre: the caster's position, from `SendNamed("PLAYER", <caster DIGIMONNAME>, <caster index>, "GETMATRIX")` (0x519030), `GetMatrix(0)`, `Matrix44_GetTranslation` (x, y, z).
- Candidates: `SendGroup(group, "GETMATRIX")` (3fc7f4..); every answering member's translation is read (`GetInt(i)` = member id = player index, `GetMatrix(i)`). A member is skipped when `id == excluded` (3fc844 `beq`).
- Shape: 3D sphere, squared distance `dx^2+dy^2+dz^2 < 900.0f` (3fc86c `lui 0x4461` = 900.0, `c.lt.s` at 3fc8c0 with `bc1f` skip): radius 30 units, strict. No height cap, no cone.
- Filter: `PushArgContext; SelectReceivers(group,0,id); SetRunCheck(1); DispatchSelected("GETHP")` (0x519040); the member is appended to the result when `GetInt(0) != 0` (3fc910 `beqz`). For PLAYER this drops a player at HP 0 (dead)
  and, because only players with a model object answer the group, players not joined/not in the stage (inferred from the group mechanism, not traced). List order = the group's answer order (assumed ascending slot; not traced).
- The caster is not in the Heal/Cure list (excluded by id) and is handled directly before the list. Dead players are in neither the area nor affected by Heal (`FUN_003f9c80` also refuses HP 0).

**Heal** (case 20, attack 40 Lt / 45): `delta = pcTech[row].HP + SKILL[pcTech[row].SKILL] + KASHIKOSA` (measured live for the caster). The caster gets `FUN_003f9c80(gameram, caster, delta, -1)`.
Heal (0x2D) then calls the same function with the **same full delta** on each list member (no distance falloff, no split), and per target sends `PrepareDelayedSelection("PLAYER", name, id)` + strings `x_250healhit00` / `SQ_HEALEFONLY`
(0x5190b0 / 0x5190c0) + float 1.0 + vec3 + bool 0 + bool 1, `EnqueueSelected("SETEFFECT")` (visual only). No effect message goes to the caster. `FUN_003f9c80` (`src/game/beNDMWGameRam_VitalsDelta.cpp`): with absolute = -1, HP 0 returns 0
(unchanged); else `HP += delta` clamped to 0..MHP, then `METERCTRL hpmt SETPERCENT 100*hp/mhp` and `NUMBERCTRL hpnm SETVALUE hp` (HUD only) = `dw4_fight_apply_hp`.

**Cure** (attack 55 Lt / 60): `SendNamed("PLAYER", name, caster, "GETPEBASEWORK")` (0x519260) returns two objects: `GetObject(0)` (`obj0`) and `GetObject(1)` = the target's PE base work. Poisoned test `FUN_00447b00(work)`: work+0xf8
(`_timerList`) exists and its first element is non-zero. If poisoned: `chance = (row - base + 5) - work._poisonEndurance (+260)`; one draw `rng->vX() % 10` (the system rng at `_system+0x30`); if `chance >= draw` then
`FUN_00447b40(work, obj0)`: `FUN_003a8580(obj0, "POISON")` and `_timerList[0] = *(int*)0x4cfe80` (0 in the ELF image, i.e. the poison timer slot is cleared; the global is never written in the sources read). Order: the caster first, then (Cure 60,
0x3C) the area list in order, each repeating GETPEBASEWORK / test / draw / cure and then sending the effect `x_250curehit00` / `SQ_CUREEFONLY` (0x519270 / 0x519280) to that member (not to the caster). No draw for a target that is not poisoned.
`dw4_magic_apply_cure` takes the poisoned flag and endurance from the caller, which reads them from the target's `dw4_status`.

**Raise** (attack 50 or -50): the centre is the caster's GETMATRIX translation; the query is `("PLAYER2", -1)`; for each list member `SelectReceivers("PLAYER2",0,id)`, `AppendMatrix(caster matrix)`, `AppendInt(a)`, `AppendInt(b)`, `DispatchSelected("RAISE")`
(0x519298), with `a = {59,68,77,86,95}[row-50]` (0x4cf600) and `b = {100,400,1600,3200,6400}[row-50]` (0x4cf620); the item version uses index 0 (59, 100). Receiver: the `PLAYER2` model class `beNDMWMdlPlayer2`
(registered with `RegisterReceiverFromInfo(.., "PLAYER2")`, 0x3d49f0); its message handler is vfunc_47 at 0x3d50c0 (also handles GENERATE, REMOVE, GENESTAGE). In the RAISE branch (0x3d5310..):
`GetInt(0)` = `a` and `GetInt(1)` = `b`. After a gate (an object looked up from the handler's `+40` reference by name `ONE`, its `+20->+240` must be >= 10; meaning unresolved), it asks `SendNamed("PLAYER",0,idx,"ISRUN")` and
scans the bool answers; **if the PLAYER model is not running** it sets the player's property `HP` = `b` (absolute, 3d551c..3d5524: no clamp to MHP, no gauge message) and spawns the player model with `MODELCTRL GENERATE` using the caster matrix and sequence `SQ_CMBK`.
Then, in all cases, it refunds the stashed bank-chip data of that slot (GETCOMMON `BKCHIPDATA`, `BKCHIPSTAGE`, `BKCHIPNAME`, `BKCHIPPOS`): `BIT += BKCHIPDATA[2i]` (entry cleared), and when the player's `DIGIMONNAME` equals `BKCHIPNAME[i]`, `EXP += BKCHIPDATA[2i+1] * a / 100`
(0x51eb851f divide-by-100 multiply; entry cleared) - so `a` is the **percent of the dropped EXP recovered** and `b` the **revive HP**; then `SendDelayedNamed("PLAYER2",0,idx,"SQ_EXIT")` and clears `BKCHIPSTAGE[i]`. Raise targets are the downed-player (`PLAYER2`) objects, not the live PLAYER group.
`dw4_magic_apply_raise` does the HP part and reports the percent; `dw4_magic_apply_raise_refund` is the bank-chip refund. The death-side stash (the second case 20, `BKCHIPBITEXP`) is `dw4_magic_bkchip_bitexp`; the gate object `ONE` is the capsule's tick counter (`Player2::vfunc_38` counts it up to 10): see [KO, the capsule and game over](#ko-the-capsule-and-game-over).

**Unresolved:** what the `PLAYER2` objects answer to `GETHP` (the filter that must be non-zero for a Raise target); the group's answer order and exact membership rule; what `FUN_003a8580(obj0,"POISON")`
removes (effect model of the poison status beyond clearing `_timerList[0]`); whether `0x4cfe80` is ever non-zero at run time. The Speed/Power/Resist receivers (`SETSPEEDUP` 0x5192a0, `SETPOWERUP` 0x5192d0, `SETREFRACT` 0x519300) go to the area **and** the caster (the caster appended to the
list; effect messages only to non-casters); they are the next section.

### Buff application, timers and expiry

`src/buffapply.c`, `check-fieldstage buffapply`. Evidence is the retail disassembly (retail virtual addresses; the two functions involved have no matched source). The port implements the state machine of the
Speed (65), Power (80) and Resist (75) support techniques whose messages `fightmagic.c` builds. Tested for consistency with the disassembly only (hand-computed values);
**not compared against a running game.**

**Receiver.** Case 20 of `beNDMWGameRam::vfunc_34` ends each buff with `DispatchSelected` of the message string `SETSPEEDUP` (`0x5192a0`), `SETPOWERUP` (`0x5192d0`) or
`SETREFRACT` (`0x519300`) to the PLAYER area. These are values of the `MsgAction` enum (names `0x5122e0..0x5123c0`, name table `0x4caa00`, registered by `FUN_003c04a0`):
`SETPOISON`=0, `SETSLEEP`, `SETSTUN`, `SETBIND`, `SETATTACKDOWN`, `SETPOWERDOWN`, `SETRAREICON`, **`SETSPEEDUP`=7, `SETPOWERUP`=8, `SETREFRACT`=9**, `SETMETAL`, `CLEARMETAL`, `CHECKSTATUS`, ...
The receiver is `Gap::Bec::beNDMWMdlPEBase::vfunc_47` (`0x445d10`, 0x1aa0 bytes): it maps the message name to the enum with `0x38d4a0` and switches through the
16-entry jump table at `0x51d510` (case 7 `0x446b48`, 8 `0x446cc0`, 9 `0x446e00`). The data owner is the `beNDMWMdlPEBaseInfoWork` (base of the player, enemy and Player2 info works);
the update that expires buffs is `vfunc_46` (`0x443bd0`). `GetInt(i)` is `0x38f320`.

**Storage.** The lists are fields of the info work (`port/src/reflection_data.c`, `mo_f270`): `_timerList` (+0xf8, ints), `_isFirstList` (+0xfc, bytes), `_downDataList` (+0x108),
`_upDataList` (+0x10c, 11 ints for a player). The handler writes:

| message | `_isFirstList[i]`, `_timerList[i]` | `_upDataList` |
|---|---|---|
| SETSPEEDUP `0x446b48` | i=5; first=1 (byte at `gp-32172` = 1), timer=int0 (TIME+KASHIKOSA) | [0..3] = int1..int4 (SUBAYASA term, CHIMEIRITSU, MHIRITSU, KAIHIRITSU) |
| SETPOWERUP `0x446cc0` | i=6; first=1, timer=int0 | [4..6] = int1..int3 (TSUYOSA, MAMORI, MAXHP) |
| SETREFRACT `0x446e00` | i=4; first=1, timer=int0 | [7..10] = int1..int4 (fire, ice, thunder, dark) |

Every store is preceded by a `count > index` test (`slti`), so a list that is too short is skipped. A null `_upDataList` is created first by `0x445990`: for a player
(`_isPlayer`, +0xec) it is the **player record's own `UPDATA` property array** (`GETPLAYER`, then property `UPDATA`; strings `0x51d4b8`, `0x51d4e8`), so the buffs write the record
directly; otherwise a fresh zero list of **7** ints, so an enemy ignores Resist's slots 7..10 (guards `slti 8..11`).

**Slot meaning.** `dw4_playerstats_recalculate` reads exactly these slots: `plus[0]` joins SUBAYASA, `plus[1]` -> CHIMEIRITSU, `plus[2]` -> MAHITEIKOU, `plus[3]` -> KAIHIRITSU / CHOHATURITSU,
`plus[4]`/`plus[5]` -> TSUYOSA/MAMORI, `plus[6]` -> MHP, `plus[7..10]` -> the four resistances. The receiver's slots equal these, so a buff only changes `UPDATA`
and requests the recalculation.

**Recalculation.** After the stores a player calls `0x445c60`, which sends GAMERAM `RECALCPLAYER` (`0x51d4f0`, argument the work's player index at +8) and then GAMERAM `ADDHP`
(`0x51d500`, arguments index and 0). `RECALCPLAYER` is GAMERAM case 11 = `FUN_003fab90(index, bool default true)`: the full recalculation with equipment. An enemy only gets the list stores.

**Time unit and countdown.** The integer in `_timerList` never counts down. The update (`vfunc_46`) runs one block per buff while `_isOnCtrl` (info work +0x44) is set and `_timerList[i] != 0`
(Speed `0x4448ac`, Power `0x444af0`, Resist `0x444c70`). If `_isFirstList[i]` is set it computes `1e9 * timer / 60` (the `dsll/daddu` chain ending in `dsll a0,v0,9` multiplies by 1953125 * 2^9 = 1e9;
`0x22e4b8(x, 60)` is a signed 64-bit divide) and calls `0x3a7a20` (`a2_timer_start`, [action timing](../../docs/engine/action2-timing.md)) with that duration, naming the timer `SPEEDUP` (`0x51d490`),
`POWERUP` (`0x51d498`) or `REFRACT` (`0x51d4a0`) on the object passed as the update's second argument, then clears `_isFirstList[i]` (bytes `gp-32224/-32220/-32216` = 0).
So **TIME is in 1/60 s units on the engine's nanosecond clock** (wall time, not a per-call count); completion is `0x3a7e90`: `duration < elapsed`, strict, elapsed in 2^18 ns steps.

**Stacking / refresh.** Applying a buff again while it is active overwrites the timer integer and the `UPDATA` slots (no summing, no longest-wins) and sets the first flag again; the next
update re-arms the named timer (`a2_timer_start` rewrites the start clock), restarting the full duration. The three buffs are independent. A recalculation is requested immediately at apply time.

**Expiry.** When `0x3a7e90` reports complete (a missing timer also reads complete) the block calls `0x3a8580` (remove the timer), stores the zero words at `0x4cfd..` into `_timerList[i]` and the
buff's `UPDATA` slots, then `0x445c60` (RECALCPLAYER + ADDHP 0) for a player. Port: `dw4_buff_apply` / `dw4_buff_update` in `buffapply.c`, fed with the `dw4_magic` of `fightmagic.c`.

**Unresolved.** The caller and cadence of `vfunc_46` (its buff blocks are time based, so the cadence does not change durations); whether the timer's scale is 1.0 and whether the clock pauses (menus, hit stop);
the `ADDHP(index, 0)` handler body; `_isOnCtrl` semantics beyond "model control active"; the `x_250*hit00` / `SQ_UPEFONLY` effect sends after the dispatch; the buff display
(icons, STATUS window). A running fight reaches the buffs through the model's `dw4_status`; the owner decision is under [Support technique wiring](#support-technique-wiring).

### Support technique wiring

Heal Lt, Heal, Cure Lt, Cure, Speed, Resist and Power are cast through the real R1 panel, deliver an 80000+base volume to the caster's own body, run the original
`hit_p_<species>.lua` support branch and apply their effect through `BLPcalcKoukaMagic`. Raise is wired as an API and through the capsules of the KO flow (see below). **Retail-measured: the Heal Lt HP gain
(`row HP + SKILL[7] + KASHIKOSA`, four anchors) and nothing else of this section.** Everything else is the port's output over the recovered rules and is labelled so.

**Verified (static reading; the bytecode listing is kept outside the repository).**
- The shared player hit chunk (`hit_p_<species>.lua`, stage chunk 3, present in all 83 stage packs) calls `BLPcalcKoukaMagic()` when the bullet kind is 80000..89999, then
  `BLTcalcSkillUp(result, 0)` and jumps to the end of the chunk, skipping the tail that publishes the HP gauge. The decompiled Lua omits the call; the bytecode has it.
  `BLPcalcKoukaMagic` (0x375cf0) sends GAMERAM `P2PKOUKAMAGIC` with the receiver's RAM slot (`MDLgetRamNo`), the shooter's (`BLTgetShootRamNo`) and the kind (`MDLgetBulletKind`) and returns
  `GetInt(0)`; case 20 does its work only when receiver == shooter and then appends 1 (even for a number that matches no family). `BLTcalcSkillUp` ignores the argument.
  A support volume therefore has to strike its own shooter's body.
- The Revive item is the other caller: `beNDMWItemDisk::vfunc_22` (0x4489e8..0x448a3c, read from `asm/`) sends `P2PKOUKAMAGIC(slot, slot, -50)`.
- `p_<species>.igb` carries exactly one 8xxxx HITBOX in all 16 species, the `reanimation` section of `SQ_WAZA` (kind 80050, start 0, length 1 frame, offset 0, size 1). The other support
  sections (`healsingle`, `healall`, `curesingle`, `cureall`, `speedup`, `damageshield`, `powerup`) have no HITBOX. Player bodies accept the enemy-bullet group only.
- `BLPgetAttackZokusei` (0x375690) stores the FIGHTCALC `GETPATKZOKUSEI` reply in the cached element that `BLTgetAttributeStr` reads and returns that string.

**What is wired.**

| Piece | Where | Behaviour |
|---|---|---|
| `BLPcalcKoukaMagic` | `modelcontact.c` -> `dw4_model_fight.p2p_magic` -> `dw4_combat_cast_support` (`combat.c`) | The reply is the script's number: 1 for a self hit, the receiver slot otherwise (inference, harmless) |
| `BLPgetAttackZokusei` | `modelcontact.c` -> `attack_element` -> `dw4_fight_attack_element` | Returns the element string and caches it for `BLTgetAttributeStr` (technique: the learned row's `ZOKUSEI`; otherwise the player's `ATTACKZOKUSEI`; poison / none read as `common`) |
| Delivery of a cast | `dw4_combat_fire` (`technique.c` stand-in bullet, once, on the first tick of the cast) | The volume is offered as an enemy-group bullet to the shooter's body only (`deliver_support`). The script binding, the record HP sync and the HP write-back are shared with the enemy-to-player path; the volume is counted as `support_hits`, not `player_hits` |
| Delivery of the model's own volume | MODELCTRL subcommand phase | A kind 80000..89999 HITBOX in the caster's sequence emits under the retail first-start/strict-end rules of the [HITBOX scheduler](#hitbox-scheduler) and is offered to the caster's body, never enemies. Raise launches no stand-in bullet: the section's own volume delivers it. |
| Heal Lt 40 / Heal 45 | `dw4_magic_apply_heal` | `row HP + SKILL[row SKILL] + KASHIKOSA` to the caster, then (Heal) the same full delta to each player the area query finds (3D sphere, radius 30, strict, HP != 0, caster excluded, ascending slot); a dead player is left alone; every changed player publishes its HP gauge (`percent = 100.0f * hp / mhp`, `FUN_003f9c80`) through `dw4_combat_hud`; with one joined player the caster is healed alone |
| Cure Lt 55 / Cure 60 | `dw4_magic_apply_cure` + `dw4_modelctrl_cure_poison` | One `rand % 10` draw per poisoned target, the caster first then (Cure) the area; cured when `(row - base + 5) - poison endurance >= draw`; a cure clears the POISON timer of the target's status (`dw4_status_cure_poison`). The poison state is the status wiring's (`dw4_status`) |
| Speed 65 / Power 80 / Resist 75 | `dw4_buff_message` + the model's `SETSPEEDUP` / `SETPOWERUP` / `SETREFRACT` service message | The area around the caster, then the caster last (`dw4_magic_buff_targets`); each target's status stores the timer and the record's `UPDATA` slots and the player is recalculated; the gauge is republished after the recalculation (`ADDHP(index, 0)`); expiry zeroes the slots and recalculates again |
| Raise 50 / item -50 | `dw4_magic_apply_raise` + `dw4_magic_apply_raise_refund` | The PLAYER2 (downed) group (capsules made by the KO flow, ready once their `ONE` counter is 10), HP = `b` unclamped for a model that is not running, then BIT += `BKCHIPDATA[2i]`, EXP += `BKCHIPDATA[2i+1] * a / 100` when `BKCHIPNAME[i]` is the same digimon, entries and `BKCHIPSTAGE[i]` cleared. The KO flow, the death stash (`dw4_magic_bkchip_bitexp`), `DEADRESTART` and game over are in [KO, the capsule and game over](#ko-the-capsule-and-game-over); the downed player's model is erased with the capsule and the revive generates it again at the caster with `SQ_CMBK` (see the KO section) |
| Seams | `combat.h` | `dw4_combat_cast_support(receiver, shooter, attack, view, &result)` (the code the callback runs; `view` NULL derives membership from the stored models), `dw4_combat_players`, `dw4_combat_view_current`, `dw4_combat_set_downed`, `dw4_combat_hud`, `dw4_combat_error`; stats `heals cures raises buff_applies buff_no_model buff_expiries recalcs support_hits support_missed skill_draws` |

**One owner for Speed / Power / Resist (decision).** The model's `dw4_status` (the status wiring's per-model state, `statusapply.c`) owns the three buffs for players: it mirrors the record's
`UPDATA` / `DOWNDATA`, is ticked once per simulation tick by `dw4_combat_status_tick` (the hub tick), holds the `_isOnCtrl` guard, and recalculates the player on every apply and expiry. The cast sends the
retail `SET*` message to the target's model, so there is exactly one copy of each timer and list. `dw4_buffs` (`buffapply.c`) stays as the reference model of the same receiver: `check-fieldstage buffapply`
checks its 2^18 ns completion rule, `supportbuff` asserts that `dw4_buff_apply` and the live owner produce the same time and `UPDATA` values, and `dw4_buff_message` (the text of the message) lives there.
The Speed / Power / Resist blocks of `statusapply.c` use the retail `FUN_003a7e90` completion test (`dw4_status_timer_complete`,
both clock samples truncated to 2^18 ns steps), as BIND does; the tick of the other statuses compares unquantised. A buff on a model without status work (an enemy-style 7-entry list) drops the Resist slots.

**Assumptions (made by the port, not recovered).**
1. The producer of the 80000+base volume for Heal Lt, Heal, Cure Lt, Cure, Speed, Resist and Power is not traced. The port delivers it on the first tick of the cast (the stand-in bullet of [Technique firing](#technique-firing),
   a box at the caster) and routes it as an enemy-group bullet because that is the only group the player body accepts. Cast frame and MP timing are unmeasured.
2. A support volume ignores the receiver's MUTEKI counter (`dw4_modelctrl_bullet_hit`, kind 80000..89999 in the enemy group). The port's player carries a positive count on the cast tick (6 MUTEKI frames in the test; their source was not traced) and a damage sequence
   leaves 30 frames of it, so honouring it would drop a Heal cast; the gate of 0x396a80 case 6 for these kinds was not read. A retail check (cast Heal Lt right after taking damage) decides it.
3. The support volume is offered to the shooter's body only (`deliver_support`), so the hit chunk and its `BLTcalcSkillUp` skill-growth draw run once per cast; mates are reached by the area query inside `p2p_magic`.
4. Area membership = a running player model with HP != 0, in ascending slot order, positions = the models' feet (`dw4_modelctrl_actor.position`, standing in for the GETMATRIX translation); a downed slot answers non-zero to GETHP.
5. The reply value for receiver != shooter and the clear value of the poison timer (the word at 0x4cfe80 is 0 in the ELF image and never found written) are inferences.
6. The buff timers run on each model's own clock (`dw4_modelctrl_now`), like the status wiring; the retail named-timer clock and its behaviour under menus and hit stop are unmeasured.
7. A buff cast at a target without an active model is skipped and counted (`buff_no_model`); a joined retail player always has a model, so this only guards the seam.

**Unresolved / not measured.** Everything numeric except the Heal Lt gain: Speed / Power / Resist durations and magnitudes (including the 2^18 ns quantised expiry, which differs from the nominal edge by up to a frame),
Cure's rate and its poison-endurance term, Raise, the area radius and caster inclusion, the effect particles (`x_250*hit00`, presentation only), the retail cast frame and MP timing, whether a KO keeps a buff's `UPDATA` while the timers
are zeroed (the recovered code does; a raised player would keep a permanent buff), what a `PLAYER2` capsule answers to `GETHP` (the port assumes non-zero), the sparkle ring of the revive, the retail timings of the KO / revive flow
(the flow itself is in [KO, the capsule and game over](#ko-the-capsule-and-game-over); the `ONE` gate is the capsule tick counter, >= 10), and support casts with second to fourth
players in the world. The area and the mate's buff are exercised through the combat seam with a second record and a second player model made from the first one's programs, not in a two-player world.

**Tests (`make -C port check-fieldstage`, each its own line).** `supportheal`: the delta, the four retail anchors (39198 / 21001 / 19300 / 34199 at row 44), the strict 3D sphere (29.9 in; 30 and (0,1,29.99) out), the caster handled
separately (dead caster, dead mate), clamp to MHP, HUD updates, no random draw, receiver != shooter, an unlearned family as a loud error, `BLPcalcKoukaMagic` / `BLPgetAttackZokusei` through the contact layer, membership derived from the models.
`supportbuff`: Speed on the area and the caster (UPDATA, timer `TIME + KASHIKOSA`, recalculated SUBAYASA / rates, agreement with `dw4_buffs`), expiry within a frame of the nominal edge with one recalculation per slot, the mate out of range,
`ALLCLEARSTATUS`, control off (nothing arms or expires), refresh at 50 % (values replaced, the full duration restarts), Resist / Power / Speed on independent timers, KO (timers zeroed, `UPDATA` kept, no recalculation), target order (area, caster last).
`supportcure`: the draw order against a replayed stream for Cure Lt and Cure, the 2000-cast rate, the poison cleared, and the real hit chunk (cure draw, then the skill-growth draw). `supportraise`: the API above.
`supportcast`: the real hub, R1 panel and Cross: Heal Lt (the gain, the MP, the gauge, no enemy hit although an enemy stands on the caster, no growth draw above the level cap and exactly one below it), Speed (UPDATA, timer, recalculation,
expiry on the hub tick, gauge republished), Raise (one self hit from the `reanimation` section's own volume). Species 15 at level 30 learns Heal Lt, Cure Lt and Speed from the recalculation; Heal, Cure and Raise (families it does not learn)
are fabricated into `WAZALIST` after the last recalculation, and every recalculation rebuilds that list, so the tests set it again where they need it.

## KO, the capsule and game over

`src/combat.c` `dw4_combat_ko_tick`, `src/magicapply.c`; `check-fieldstage deathflow` / `deathcoop`. Every rule below names its source; **verified** means read in the matched source
or the Lua packs, **inferred** means the code does not state it, **measured** is a live observation.

| Step | Rule | Status |
|---|---|---|
| Damage to the player | The hit chunk (`lua/06-dungeon-1/01-dng101b1_e179/034-damage-calc-2.lua`) calls `MDLaddHp(-dmg)`, `MDLdspDamageP`, and picks `SQ_DDMG` for damage rank 3. No Lua handles the death. What `SQ_DDMG` / `SQ_DEAD` lead to lives in `p_<species>.igb`. | verified; the sequences' outcome unrecovered |
| Trigger | `beNDMWMdlPlayer::vfunc_43` (0x3d45f0) creates the capsule; **what calls it is inferred** to be the death sequence. The port treats "record HP is 0 on a joined player that was seen above 0" as the KO (so poison, hits and edits all count) and creates the capsule `DW4_KO_CAPSULE_DELAY` = 120 ticks later: the 120 comes from a live measurement (the BKCHIP record is written ~120 frames after the KO), not from code. | trigger inferred, delay **measured** |
| Capsule creation | `vfunc_43`: `MODELCTRL g_000bcaps[slot] GENERATE` at the player's matrix with `SQ_ENTR<n>P`; if the capsule `ISRUN`, `GAMERAM BKCHIPBITEXP(slot)`; then `NDMWPANEL REMOVE` when the panel flag is set. The port creates the capsule record at the player's feet position (no capsule model is drawn, the panel is not modelled). | verified (the strings at `0x516228..0x516538` checked in `data/strings.json`) |
| Capsule start | `beNDMWMdlPlayer2::vfunc_36` (0x3d4a20): a new `ONE` counter object, then `GETCOMMON` `BKCHIPSTAGE[slot]` = the loaded stage name and `BKCHIPPOS[3*slot..]` = the capsule's translation. `dw4_magic_capsule_start`. | verified |
| Death stash | `BKCHIPBITEXP` = `beNDMWGameRam::vfunc_34` outer case 20 (command table index 20). `BKCHIPNAME[i]` = `DIGIMONNAME`; `BKCHIPDATA[2i]` = `BIT`, `BIT` = 0; unless `LEVEL` is 1 or 999: `EXP` loses `(g(L-1,L) - g(L-2,L-1)) * 2 / 10` but never drops below `g(L-1,L)` (`g(d,x) = 200d + (x+139)d^2`, i.e. `NEXTEXP` of the previous level; `playerstats.c` computes the same curve), and the loss goes to `BKCHIPDATA[2i+1]`. At level 1 or 999 the loss entry is **not written** (a stale value stays). `dw4_magic_bkchip_bitexp`. | verified; hand-computed tests; the level-5 loss was read on retail (below) |
| Capsule tick | `Player2::vfunc_38` (0x3d4ea0), every frame: the `ONE` counter counts up to 10; `PLAYER NEAR` finds the nearest living PLAYER, and with one the capsule toggles `SQ_SWON` / `SQ_SWOF` around the threshold 900.0. The test is on a squared distance: `PLAYER NEAR` reaches `FUN_003a63b0`, whose NEAR branch calls `FUN_003a5cc0`, and that stores `dx^2+dy^2+dz^2` in `0x58a5f0`, the float `FUN_003a68d0` returns. `SQ_SWON` / `SQ_SWOF` therefore toggle at 30 units, the same radius as the Raise area test, and the port's squared comparison is the retail one. With **no** living PLAYER it runs `end_g_000bcaps.lua` (string `0x516630`). A living PLAYER is a joined, running player model, so a KO'd player still inside its 120-tick delay counts as living. | verified |
| Game over | The chunk reached by that name is the pack's `016-flag-409.lua` (`COUNTER 2` = 902 / 906 branches or its default else branch): `ENEMY` / `PLAYER2` `OFCTRL`, the `i_fadewn01` `SQ_GAMEOVER` fade, a message with a `SELECTCTRL` wait, `PLAYERPOINT SETGENERATEPOS 0`, `STAGECTL NEXTSTAGE stagML11`. It is due for 1 player and co-op alike once every joined player has a capsule. The retail code calls it on every capsule tick; whether the Lua manager ignores repeats is unrecovered, the port starts it once (`stats.gameovers`). | verified; the repeat guard unrecovered |
| Revive | `Player2::vfunc_47` RAISE (0x3d50c0): returns early unless the capsule's `ONE` counter is >= 10; if the PLAYER model is not running sets `HP` = `b` and generates it with `SQ_CMBK` at the caster's matrix; refunds `BIT` and `a`% of the lost EXP (same `DIGIMONNAME` only); `SQ_EXIT` to the capsule; `BKCHIPSTAGE[i]` cleared. The port: a capsule younger than 10 ticks is not a Raise target (`dw4_combat_view.young`); a ready one gets `dw4_magic_apply_raise` + `dw4_magic_apply_raise_refund` and the slot stops being downed. | verified |
| After game over | `GAMERAM DEADRESTART` (message 16, `vfunc_34` ~2235): for each slot with `ISUSE` non-zero `HP` = `MHP`, `MP` = `MMP`, no gauge message. **Its sender is not in any Lua**; the port sends it when the end chunk's `NEXTSTAGE` request becomes pending (`hubruntime.c`), before the destination snapshot is taken (inference). | rule verified, sender inferred |

**What the port does and does not have.**
- **Model removal.** The player packs end `SQ_DEAD` (`DEAD*1`, then `JUMP SQ_ERAS`), and retail's downed model disappears 2-3 s after the KO, about when the capsule appears (the link between the two is an inference from the timing). The port creates the capsule 120 ticks after the HP record reads 0 and erases the slot's model controller at that moment (`MODELCTRL REMOVE`, the same call `SQ_ERAS` makes): the slot is not active, not drawn (the lobby's drawable-driven hide), its PLAYER / MODELCTRL receivers report inactive (`dw4_lobby_services_sample` syncs every joined slot), enemies and the NEAR queries skip it, and its records and weapon sections stay. What differs from retail: the port does not play `SQ_DEAD` / the lie-down animation before the capsule (the HP poll is the trigger, not the death sequence, so the model keeps whatever it was doing for the 120 ticks), and the erase is tied to the capsule rather than to the end of `DEAD*1`.
- **Revive sequence.** `revive_model` (`src/combat.c`) re-generates the erased player model with `MODELCTRL GENERATE "SQ_CMBK/V<caster pos>/V<0,caster yaw,0>"`. `SQ_CMBK` exists in the player pack read (`p_dorumon`; the other species were not listed): per weapon section (`dual`/`slash`/`arm`/`gun`) `MUTEKI 120.0`, `ACTION REVE?1` (a `FADESET HID` step, a `waitX` loop, a 1-frame WAITCHECK), `JUMP SQ_CMBK02`, which runs `ACTION REVE?2` (`FADESET IN` 60 frames, a 60-frame WAITCHECK) and jumps to `SQ_WAIT`. The section follows the player's `SQ_WAIT` section (`dw4_modelctrl_label_copy`). The model is hidden for the first frame and fades in over one second while invulnerable (120 frames of MUTEKI). The pack spells the hide step of `REVE?1` `HID`, not `HIDE`; the host reads only the first letter (0x376930), so the loader accepts `HID`. A model that was never erased (a fixture slot set with `dw4_combat_set_downed`) is moved and sent the same sequence; a pack without `SQ_CMBK` falls back to `SQ_WAIT`.
- **Sparkle ring (not done, unconfirmed).** The recovered RAISE receiver names no effect model: it generates the PLAYER with `SQ_CMBK`, refunds, and sends `SQ_EXIT` to the capsule (`PLAYER2`, the `g_000bcaps` instance). Nothing in the matched code or the Lua packs names an effect for the revive. The stage packs hold `g_000bcaps` (the capsule marker: `SQ_ENTR1P..4P` -> `SQ_WAIT` with the `OFFnP`/`ONnP` labels toggled by `SQ_SWON`/`SQ_SWOF`, `SQ_EXIT` -> `DEAD0n` 60 frames -> `SQ_ERAS`) and an effect model `x_000bcaps` (`SQ_ENTR1..4`, `SQ_EXIT1..4`, a `WAITnn` loop per slot, each exit ending in `SQ_ERAS`) that no recovered string, script or function references (it appears only in the pack's own name list). The retail ring may be `g_000bcaps` `SQ_EXIT` or `x_000bcaps`, but that is a guess, so the port plays no revive effect.
- No capsule model (`g_000bcaps`, `SQ_ENTR<n>P`, `SQ_SWON/SQ_SWOF`, `SQ_EXIT`) is drawn or sequenced: the `SW` toggle is state only (`dw4_combat_capsule.near_player`). `GENESTAGE` (re-creating a slot's capsule when `BKCHIPSTAGE` equals the loaded stage after a stage reload) is not ported.
- Enemy targeting: once the model is erased (capsule created) the NEAR query and the bullet delivery skip the slot, as retail's player lookup finds only the survivor; during the 120 ticks between the KO and the capsule enemies can still pick the downed player (what retail targeting does in that window is unmeasured).
- The retail comparison is the capture below and the measured 120-tick delay; the BKCHIP formulas come from matched code and are checked against hand-computed values.

**Tests.** `check-fieldstage deathflow`: the stash arithmetic (level 5 EXP 3500 -> 3257 with 243 stashed; floor 3104; level 2 floor 341; levels 1 and 999 untouched; independent slots; Raise refund round trip 243 * 59 / 100 = 143), the capsule-start records and `DEADRESTART`.
`check-fieldstage deathcoop`: two players in `dng101b1`; one is KO'd and its capsule appears after exactly 120 ticks (stage, position, name, BIT and EXP stash), the downed slot's model is then not active, not drawn and has no sequence while the survivor's is drawn, a Raise on the young capsule changes nothing, 12 ticks later the item Raise revives it (HP 100, EXP refund, capsule gone, the model generated again at the caster in `SQ_CMBK`, then `SQ_CMBK02` with an alpha between 0 and 1 mid fade-in, then `SQ_WAIT` and drawn; `DW4_KO_SHOT=<prefix>` writes frames of the capsule and revive steps), the revived player is KO'd again, the living partner walking away toggles the capsule's near state, the partner goes down, the end chunk starts once and `stagML11` point 0 is requested, and `DEADRESTART` refills both records.

**Retail capture of a real KO.** A level-1 Normal save was killed by goblins in `stag0102`: HP 0 with the red-X HUD ring, a capsule marker at the fall point, BIT 67 -> 0
stashed in `BKCHIPDATA[0]` (`[1]` = 0, EXP stays at level 1), `BKCHIPNAME[0]` = `p_dorumon`, `BKCHIPSTAGE[0]` = `stag0102`, `BKCHIPPOS` = the fall position, then the end chunk's message pages
and `NEXTSTAGE stagML11` with the player at (60, 10, -30), HP restored to MHP and BIT still 0. This agrees with the recovered rules above. The first KO of a fresh save shows eight tutorial pages
(flag 508, set by the Terminal arrival while flag 501 is off and by the stage-select scripts, cleared by the chunk); later KOs show only "The team is completely destroyed. Sending the data of all members to the Main Lobby." (retail, same save with flag 508 cleared). Writing 0 into the HP record in retail does **not** start the KO, so the
trigger is the damage path and the port's HP-record poll is a stand-in. The EXP loss at level 5 (records edited to LEVEL 5, EXP 3500 for the run) read 3500 -> 3257 with `BKCHIPDATA` [67, 243], the number `deathflow` computes. A two-player retail run (cold boot, two created Dorumon, stag0101, arriving at (460, 50, 230) and (460, 50, 250)) showed the downed slot's model removed (one player object left), the HUD ring with a red X and 0, the camera on the survivor, the chip entry for slot 2 (`p_dorumon`, `stag0101`, (463.8, 50.0, 196.1)) and a capsule marker in the slot colour (blue for slot 2) with a dotted ring, standing at the fall position, while the goblins kept attacking the survivor. The revive: a Raise Disk (the revive disk, recNo 7, count written to 3 as a save edit) used with Cross next to the capsule played a sparkle ring, took one disk, removed the capsule and brought the slot back at HP 100 with its model at the caster, which is the port's revive numbers and placement. Not measured: the down animation length, the revive sequence length and the BIT/EXP refund.

## Co-op

The combat state is per slot: the shooter's slot selects the GETPLAYER record for hit, damage, critical and EXP; E2P takes the target slot; generators carry per-player-count rows;
P2EEXPUP splits by NINZU. `check-fieldstage coop` creates slots 1–3, sets NINZU 2/3/4 and asserts the
attacker/mate EXP split from the matched source (row 388, 133 base: 124/62 for 2 players, 106/53 for 3 and 4 — the matched rule gives 3 and 4 players the same integer result here) and the retail-measured
splits below. Two to four local players in the world (input, models, camera framing, the per-player HUD, enemy targeting, per-player pickups, the party in the hubs) are in
[dungeon floors](dungeon-floors.md#local-co-op-in-the-floors).

### Co-op in retail: join flow and measurements

Measured live (two level-1 Dorumon created on slots 1 and 2, PCSX2 with a second pad):
- **Joining happens on the main menu**, not in the world: after Game Start the screen splits into four slots; an unjoined slot shows "Press (Cross)" and the first Cross on that slot's pad opens its own Create / Call Digimon menu. Each slot then creates independently (pick species, name, confirm). Slot 1's Start logs everyone in; slots that finished first wait ("Please wait...").
- **Fresh two-player save in the Terminal**: the Digi-Elf intro plays for the group, flag 2 is clear so the Outside World gate does nothing (the elf sends the group to the Commander Room). Setting flag 2 live and standing **both** players on the `mate00` box (x -5..15, z -105..-85) opened the gate menu (a single entry, "Death Valley"); Cross loaded `stag0001` (practice stage). The gate script tests `MATisAllPlayer() == 1`: every joined player must be on the material; the port's material regions report the mask of the players standing in them ([dungeon floors](dungeon-floors.md#local-co-op-in-the-floors)).
- **Live state**: two player records exist (HP/MHP/LEVEL at 0x879xxx and 0x87bxxx in this build, 0x2938 bytes apart, the unjoined slots' records read all zero); the player search finds exactly the joined players (`emu_state.players`), and both appear in the HUD. Arrival in the practice stage places them at (65, 10, 0) and (85, 10, 0), 20 units apart.
- **EXP split, four players (measured):** four level-1 Dorumon in the practice stage, player 2's pad attacking alone, four lesson-1 e_goburi kills (row 638, EXP 3): every kill gave the shooter **+2** and each of the three mates **+1** (totals 8 / 4 / 4 / 4). That equals the port's rule (`value*200/5`, attacker `/50`, mates `/100`: 2 and 1); `check-fieldstage coop` asserts it. **Two players (measured):** with both players' EXPRITSU poked to 4333 (value 3·4433/100 = 132) each practice-stage award gave the shooter **+123** and the mate **+61**, exactly the rule's `132·140/3` split (/50, /100); at base 3 it is +2/+1. The awards were not necessarily enemy kills (that part of the stage also breaks crates); the formula only sees the base EXP and NINZU. **Three players (measured):** a genuine three-player session (three slots created and logged in; the third pad needs the multitap), same boost: the shooter **+105**, each mate **+52** per kill, again exactly the rule (`132·160/4`, /50 and /100); `check-fieldstage coop` asserts it. The first practice wave at three players was three goblins (table 1/3/3/4). The gate menu only opened once all three players stood on the gate box, confirming the `MATisAllPlayer` rule for three players. Only the row-388 figures (124/62, 106/53) remain source-derived. **Wave size (measured, two players):** the first practice wave spawned three e_goburi (row 638), one after another over a few seconds, as the stage table gives for two players (`GENE-a00` count 1/3/3/4 for 1-4 players; the ogre and nume groups `a01`/`a02` and `b00`-`b02` use the same 1/3/3/4, the other groups are fixed); the four-player state showed four. `check-fieldstage gencounts` (STAGE=...) prints a stage's tables. **Targeting (measured, two players, first e_goburi of the practice stage):** with the emulator paused, both players were teleported to chosen distances from the goblin (read from its scene node), the game ran for about two seconds, and the goblin's displacement was compared with the bearings to each player. In every clear case it walked towards the **nearer** player regardless of slot: near player 1 (cos 0.93 / 0.96 towards it, 0.17 / -0.85 towards the far one), near player 2 (0.92 / 0.95), including margins of about 7 units (48 vs 55) and 9 units (51 vs 60). Two trials were inconclusive (the goblin barely moved) and exact ties were not isolated (distances drift while the enemy is knocked about). This agrees with the owner's observation that enemies switch players when the nearest is knocked back. The port's `NEAR` AI target (`dw4_controllers_nearest`) picks the nearest player of the group; not measured: other enemy types, the boss, whether any enemy prefers a target by another rule, and what happens when a target is KO'd.
- **Four players**: all four slots join and create (verified). Logging in or creating with three or four players crashed the emulated game in about half of the attempts (an intermittent null SDK RPC request: a null object at `FUN_0010dbb0`, a small method that clears a flag bit and a field of `this`; next item), while logging in with two players works. A four-player login that worked left a savestate in the Terminal that reloads reliably with all four players, and four players enter the practice stage from it (flag 2 set, all four on the gate) at (65,10,0), (85,10,0), (75,10,-10), (75,10,10). It is not known whether the crash is the game, the multitap emulation or the profile.
- **The three/four-player login crash, what the register dump shows** (private emulator build that prints `ra`/`sp`/argument registers at the first TLB faults): the fault is in `FUN_0010dbb0` called from `FUN_0010dc40`, the SDK's SIF-RPC completion handler, with `ra=0x10dcf0`, the callback frame in the interrupt stack and `s1 = 0x571778`, the **RPC client record of a game-specific IOP service bound by `FUN_00280b98` with id `0x53465356` ("SFSV")**. `FUN_00282038` issues the asynchronous `sceSifCallRpc` on it (rpc number 0x8000, 2624-byte send buffer at 0x570d00, 16-byte reply, end function 0x281d80). The completion handler releases the request with `FUN_0010dbb0(*client)` and then zeroes `*client`, so a **second completion for the same request** reaches it with `*client == 0` and faults on a null request. This is a duplicate or late end-of-RPC for the SFSV service (a double reply from the IOP side or the SIF command being handled twice), which is timing-sensitive: it hit about half of the four-player attempts with both multitaps configured and every attempt with a single multitap. Not established: what the SFSV service is, why a second reply appears with three or more players, and whether it is the game's IRX or the emulator's SIF/IOP timing. The in-world measurements above are unaffected (they came from sessions that logged in).

Savestates of the two-player practice-stage start are kept outside the repository.

## Drops

`fieldgen` decodes each generator's drop lists from the difficulty pack (`beGeneraterPlayerData` `_itemDataList`/`_itemLastDataList` → `beGeneraterItemData` →
`beGeneraterItemDataOneList` → `beGeneraterItemDataOne`: category = record name, ordinals 3/4/5 = item id / rank / rate) and rolls them with the recovered
FUN_00384800 rule (`RNG % 10000`, subtract each rate, the first entry at which the running remainder is `<= 0`; the generator's final enemy uses the "last" list) whenever a generated enemy is removed.
`check-fieldstage droptables` asserts the decoded stagGF01 lists against the sums measured live (Goburimon generators 3502/3170/4050 on
Normal/Hard/Very Hard, box list 4330, GENE-19 empty) and walks all 10,000 draws. The boss room drops `insItem` id 1 (rate 7000) at the boss's death position.

**Pickup (`src/loot.c`):** BIT, x-data (`insItem` 1-3, the row's `UP`: 5 / 20 / 100) and UPCNT items (`insItem` 4-25) are taken by a living player within 8 units (squared 3-D distance below 64, the nearest player wins);
weapons, armour, chips, disks and the keys are named models: a player in range holds a label and picks the drop up with Cross (weapon / armour / chip into `DEVICEFOLDER` with the rolled pocket and revision, refused at 36;
disk +1 in `DISKFOLDER`, refused at nine; key sets `FLAGFOLDER[record]`). Rules, tables and what is not ported: [dungeon floors](dungeon-floors.md#loot-delivery). One x-data pickup of record 1 is x5:
the Leomon-room boss's drop leaves the starter with XDATA 5 (`check-fieldstage room`). The drop models, name labels and got-item effects are ported ([dungeon floors, Drop models](dungeon-floors.md#drop-models)); the pickup sound is not, and the 8-unit radius is the recovered rule, not a retail measurement.

**Not done:** the disk use effects, the pickup sound and the PERFECTDROP flag. The roll draws from the world random stream at removal time, the item roll right after it; retail's draw order is not measured.

## Design constraints

- **One to four players from the start.** Combat state keys damage attribution, targets, drops, rewards and camera framing by player slot;
  `dw4_hubruntime_prepare` admits NINZU 1-4 in the field worlds, dungeons and the four hub worlds. No co-op parity is claimed
  beyond what is measured against retail.
- **Reuse the matched dispatcher.** FIGHTCALC (`beNDMWGameRam::vfunc_34`, 22 commands) rebuilds byte-for-byte; the port's damage,
  critical, status-time, EXP and skill-gain rules are derived from that source and checked with instruction-level comparisons like the
  other recovered rules (`port/tools/verify_*_retail.py`).
- **Measure retail before encoding it.** Timings, trigger order and numbers come from savestate or live reads (`dw4-retail-state`), never from
  memory of how the game plays.
- **Scripts own the stage.** Enemy introductions, damage chunks (`MDLaddHp`, `MDLsetSeq`) and exits are original Lua; native code supplies the
  services they call (`ENEMY`, `PLAYER2`, `MODELCTRL` for generated objects, `CAMERA`). Missing services must fail loudly rather than be
  declared empty; the `PLAYER2` category is declared without receivers, so scripts that address it do nothing.

## Open items

Each section lists what it has not measured or ported. The items that bound the foundation as a whole:

- **Input.** The stick-spin `SQ_ATCK2`, the Square-held double-tap `SQ_ATCK3` and the delay gauge are not ported; what `ATDELAY` gates is unmeasured; per-weapon swing lengths are not compared with retail.
- **Retail measurements missing.** The starter's swing frames and the sequence timings; the hit-once rule as a rule; the technique critical rate, hit count per cast, MP costs and the other elements; all status
  durations and chances in both directions; Speed / Power / Resist, Cure and Raise numbers; the KO down animation, the revive sequence length and the BIT/EXP refund; every form's swing; the practice stage's
  timings and per-swing numbers.
- **Stand-ins.** The technique bullet (speed, lifetime, single contact; the effect models are not spawned); the producer of the support volumes and their MUTEKI bypass; the HP-record poll as the KO trigger; no
  capsule model, no revive sparkle; the named-timer clock domain.
- **Level-up and skill-up presentation.** FUN_003f8760 and the level-up and skill-up display messages are not ported.
- **Collision.** No arena wall holds the player in the Leomon room; the `stag0101` collision has not been compared with a retail walk.
- **Stage flow.** The Gate Disc and the other disk use effects; the 2-player graduation branch of the practice stage; the application path for field stages other than `stag0001`.
- **Co-op.** A support cast with a mate in the world; the cause of the three- and four-player login crash in the emulator (the SFSV RPC completion) is not established.

## Open questions

- **Where `GAMERAM DEADRESTART` is sent from.** Unproven. The engine may send it on the return to `stagML11` after the game-over chunk, which is what the port assumes, or the hub may send it at its start.
- **A KO in the Goblin Fortress guard room can stall.** A KO in `stagGF01` on a run with no earlier death has been seen to stall. The BKCHIP record is written as usual about 120 frames after the KO, with the current stage, and the game-over chunk's `ENEMY`/`PLAYER2` `OFCTRL` takes effect (enemy idle, player model and HUD gone), but the `i_fadewn01` `SQ_GAMEOVER` fade and the message never follow. An earlier death elsewhere reportedly avoids the stall. The BKCHIP contents are not the cause: seeding the record with the values a Death Valley death leaves does not prevent the stall, and the death overwrites them with `stagGF01`. Why the chunk stops after `OFCTRL` is unknown.
- **E2P damage terms unproven against retail.** In E2PDAMAGE a TYPE 1 critical adds its bonus (bytes at 0x402994) where TYPE 0 multiplies, and the attack-down and critical-down terms come from the attacking enemy's work `_downDataList`.
