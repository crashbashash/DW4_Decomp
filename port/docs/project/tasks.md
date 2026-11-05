# Port task list — source-level retarget

The goal and scope live in [README.md](README.md). This file is the work list for **goal B** (native on
Linux/Windows): what is left to do, the resume point, and a compact record of what is done. The subsystem
documents in [`port/docs/`](../README.md) own the description of each result; this file links them and
does not repeat them.

The road is decided: **source-level retarget** — rebuild the decompiled C against host libraries, so
relocations move anything, host memory replaces the 32 MB ceiling, and whole subsystems can be added.
Static recompilation of the EE binary is not chosen (see [README.md](README.md)).

Status values: `todo` · `in-progress` · `done` · `blocked`.

Conventions used below:

- `check-*` names are targets of `make -C port`; `make -C port check` is the port's regression suite.
  Names given as modes (`loot`, `deathflow`, `statusflow`, …) are modes of `check-fieldstage`.
- `#NNNN` is a finding in the [findings register](../../../docs/findings/README.md).
- Paths starting with `../scratch/`, `../local/` or `../extras/` are repository-relative and lie outside
  Git (private evidence, captures, handoffs).
- A bare source file name (`render.c`, `engine.c`, `fightmagic.c`, …) is a file in `port/src/`; a bare
  script name (`igb_pool.py`, `retype_initfields.py`, …) is a file in `scripts/`.

## Resume point

**Active objective: the first dungeon (the Humid Cave), then the next dungeon.** Play `dng101b1` and
`dng101b2` natively from `stag0101`'s exit to the Terminal teleporter (boss Blossomon), for one player
and then local co-op, with the gameplay sound set, validated against retail where a number is claimed;
then the next dungeon (`dng102b1`, `dng102b2`, `dng102b3`, boss Mammothmon) in the same way. Contract,
route and blocker list: [dungeon floors](../dungeon-floors.md).

Where the work stands:

- **Humid Cave: plays end to end headlessly.** One to four players play `stag0101` -> `dng101b1` waves
  -> `dng101b2` waves, heal circle -> Blossomon down (flag 119) -> the Terminal, where the party arrives
  and takes control (`check-dungeonroute`, `COOP=2/3/4`); checked by the full
  `make -C port -j14 -k -O check`.
- **Next dungeon: plays end to end headlessly.** `dungeonroute2` (`check-dungeonroute2`, COOP 1-4,
  level-60 fixture) runs `stag0101` -> `stag0102` -> `dng102b1` -> `dng102b2` -> `dng102b3` to the
  Terminal with Mammothmon killed and flag 150 set.

Resume here:

1. **Humid Cave, retail side.** The revive sparkle effect and the `SQ_DEAD` sequence before the downed
   model is erased; wave refill behaviour in a live fight; Blossomon's attacks and damage ranks; audio
   beyond the entry music pair; a clean-boot repeat of the wave and damage reads.
2. **Humid Cave, port side.** A physical multi-pad run; the party point-message band in the hubs; the
   breakable wall, damage floor and chest drops in the stick walk; the pickup sound.
3. **Next dungeon.** Port: in `stag0102` the barrel cannon, the pit scripts and the Blossomon gate
   fight are unexercised (the leg is stick-walked only from the arrival to `matz00`); chest drops on
   the floors are open. Retail: a pad-only Mammothmon kill; the charge cycle (the intro charge timeline
   is settled); the two-motion census entries beyond ITEMH2 and MDMG01; the rendered `CAMERA SHAKE`;
   doors other than `doorwall05`; chest item categories and the boss reward's identity; co-op;
   `dng102b1`/`dng102b2` beyond the flags at arrival.
4. **Field stages.** A Start press from pads 2-4 in co-op; retail's field SOUND freeze.
5. **Practice floor grid.** Widening the light-block rotation rule beyond `stag0001` needs a retail GS
   dump (see the practice floor-grid row in [Dungeons](#1-dungeons-active-objective)).
6. **The other World-1 dungeons**, then the real boss fight in a full World-1 run (see the boss fixture
   in [Agreed requirements and decisions](#agreed-requirements-and-decisions)).

Details of each item are in [Dungeons](#1-dungeons-active-objective).

Not claimed for the dungeon floors: rendering, audio or timing parity with retail.

## Agreed requirements and decisions

The [technical specification](../technical-spec.md) and its decision record are the authority for
requirements. The decisions below govern this work list.

| decision | where it is recorded |
| --- | --- |
| The port is a source-level retarget of the decompiled C; static recompilation is not chosen | [README.md](README.md) |
| Renderer and audio are reimplemented, not emulated: the GS is not emulated and the VU1 programs are the specification of what to compute, not code to run | [README.md](README.md), [VU1 microcode](../../../docs/engine/vu1-microcode.md) |
| 32-bit pointer policy: a contained 32-bit guest arena, aiming at a 4-byte handle type that is layout-identical so the conversion is incremental and gated by `make check`; widening to 64-bit host pointers is a later, optional step. Forced by measurement: 43 % of reflection fields (1,567 / 3,680) are reference-typed, the heap is `SetupHeap(0x0058D280, -1)`, and 1,013 literal pointer-arithmetic sites exist in the matched C | [pointer model](pointer-model.md) |
| The port's game logic is retargeted onto the decomp's authoritative structs held in arena memory: fight rules first, then the port-native game types module by module (P0 arena core and class registry, P1 typed `beDataBase` instances, P2 fight rules, P3 module-by-module replacement) | [arena object model](../arena-object-model.md), [specification, decision record](../technical-spec.md#decision-record) |
| The decomp's generated structs (`include/dw4/reflected.h`) are the authoritative layout of the game's objects. The port builds with `-I../include`, declares no struct under a reflected class name (`scripts/check_port_struct_duplicates.py`), and `check-decomp-headers` compiles the headers with the port's flags and asserts the arena-model facts (`igObject` is two words, subclass offsets, a reference field is as wide as `dw4_handle`) | [typed game layer](../../../docs/engine/typed-game-layer.md) |
| Hub, combat and dungeon workstreams are tested **headlessly**, reuse original Lua 4 bytecode and recovered controllers, preserve the matching build's byte identity, and are designed for one to four local players | this file |
| Native milestones (connected hubs, combat, dungeons) take priority over the broad lobby matching queue; the full-hub decompilation objective is unfinished | this file |
| Local co-op (one to four players, joined from the main menu) is in scope for the first release | [specification, decision record](../technical-spec.md#decision-record) |
| Normal play uses GPU rasterization and compositing; no GPU error selects a CPU fallback; explicit software/headless reference paths remain available | [specification, decision record](../technical-spec.md#decision-record), [GPU rendering](../gpu-rendering.md) |
| Gameplay, animation, rendering and audio keep running when the window loses focus; returning focus needs no key; manual pause and controller-disconnect holds stay independent | [specification, decision record](../technical-spec.md#decision-record), [live simulation pump](../lua-integration.md#live-simulation-pump) |
| Production clocks use the agreed rational 60 Hz policy; no fitted phase offset is applied to production to make a retail frame comparison pass | this file |
| The native save library stores the raw PS2 save file under `$XDG_DATA_HOME/dw4/saves`, with a `.bak` | [specification, decision record](../technical-spec.md#decision-record), [Save Keeper](../save-keeper.md) |
| The Machinedramon fight in `check-fieldroute` uses a progressed-save fixture (starter at level 40, stats from the recalculation; levels 15/25 lose, level 1 cannot win). The owner accepts this until the real boss fight is tested in a full run after the other World-1 dungeons, including the Abyss of Grief | this file |
| Hub loading cards are shorter than retail's disc-bound ones (intentional) | this file |
| The pad D-pad drives menus only (retail ignores it for walking); keyboard arrows still walk | [boot contract](../boot-contract.md) |
| The first-lobby controller open stays on the main thread: moving it to a worker thread was rejected as unsafe (shared single-threaded VM and service registry) | this file |
| The sound IOP module is not analysed (not planned); the items that depend on it stay open | [audio playback](../audio-playback.md) |
| The baked scene light rig is the fitted rig, no response curve is shipped, and the `dw4asset` tools stay analysis tools that the game never depends on | [P4.4 results](#p44-the-games-shading-results), [boot contract](../boot-contract.md) |

Planned order of the engine workstreams (a plan, not an agreed requirement): see
[Order of the workstreams](#order-of-the-workstreams).

## Open work

Groups are ordered by the objective they belong to, the active objective first. Within a group, items
are what is missing.

### 1. Dungeons (active objective)

Owning document: [dungeon floors](../dungeon-floors.md).

| item | what is missing | evidence |
| --- | --- | --- |
| `stag0102` (route into the next dungeon) | The barrel cannon, the pit scripts and the Blossomon gate fight are unexercised; the stick walk covers the arrival to `matz00` inside `dungeonroute2` only | [#2971](../../../docs/findings/findings-2751-3000.md#f2971) |
| Chest drops | Open on the next dungeon's floors; not in the Humid Cave stick walk; on retail the chests are unconfirmed and the chest item categories are not reached | [#2980](../../../docs/findings/findings-2751-3000.md#f2980)-[#2984](../../../docs/findings/findings-2751-3000.md#f2984) |
| Mammothmon kill by stick | The default pilot of `check-dungeondoors2-full` needs a placement next to the boss before each swing: a stick-only walk-in swinging from 15-31 units never damages it, and stick-only melee does not connect on retail either. The pad-only pilot (`BOSSSMART=1`: R1 ice casts from 45 units, or standing 9 units from it and swinging) kills it without placement (`check-dungeondoors2-boss`, about 45 s, 1,648 ticks); no WAIT window exists in the port's boss loop and jump and guard do nothing there. Retail has not been tried with this pilot | [#2974](../../../docs/findings/findings-2751-3000.md#f2974), [#2977](../../../docs/findings/findings-2751-3000.md#f2977), [#2978](../../../docs/findings/findings-2751-3000.md#f2978), [#3030](../../../docs/findings/findings-3001-3250.md#f3030)-[#3034](../../../docs/findings/findings-3001-3250.md#f3034) |
| Mammothmon against retail | The charge cycle (the intro charge timeline is settled: [#3012](../../../docs/findings/findings-3001-3250.md#f3012), [#2978](../../../docs/findings/findings-2751-3000.md#f2978), [#3072](../../../docs/findings/findings-3001-3250.md#f3072)); the two-motion census entries beyond ITEMH2 and MDMG01 ([#3051](../../../docs/findings/findings-3001-3250.md#f3051)); boss damage is unconfirmed and the boss reward's identity is not reached | [#2980](../../../docs/findings/findings-2751-3000.md#f2980)-[#2984](../../../docs/findings/findings-2751-3000.md#f2984) |
| Next dungeon, not reached on retail | The rendered `CAMERA SHAKE`; doors other than `doorwall05`; co-op; `dng102b1`/`dng102b2` beyond the flags at arrival | [#2968](../../../docs/findings/findings-2751-3000.md#f2968), [#2979](../../../docs/findings/findings-2751-3000.md#f2979) |
| Revive presentation | The port erases the downed model at the capsule and revives it at the caster with `SQ_CMBK` (fade-in). Open: the sparkle effect (no effect model is named by the recovered code) and the `SQ_DEAD` sequence before the erase. The retail capture route is in `../extras/handoffs/` | [#2925](../../../docs/findings/findings-2751-3000.md#f2925), [#2930](../../../docs/findings/findings-2751-3000.md#f2930), [#2951](../../../docs/findings/findings-2751-3000.md#f2951), [#2953](../../../docs/findings/findings-2751-3000.md#f2953) |
| Humid Cave waves against retail | Refill behaviour in a live fight (the per-player-count counts are the same generator files); a clean-boot repeat of the wave and damage reads (the fixture states carry crowns) | |
| Blossomon against retail | Attacks and damage ranks | |
| Dungeon audio against retail | Everything beyond the entry music pair: boss effect sounds, volumes, fades, anything audible | [#2795](../../../docs/findings/findings-2751-3000.md#f2795) |
| Damage/EXP number fade | The fade length against retail | [#2872](../../../docs/findings/findings-2751-3000.md#f2872) |
| Number-model camera | Unconfirmed: its data trace says WN00 sets no screen-space camera and the number models have the structure of the retail-verified point-message cursor; no engine path is traced | [#2798](../../../docs/findings/findings-2751-3000.md#f2798) |
| Pickup sound | Not ported: the recovered code sends none | |
| Stick walk coverage | The breakable wall, the damage floor and chest drops are not in the stick walk | |
| Pads 2-4 | A physical multi-pad run (the engine's device routing for pads 2-4 is wired but exercised only by scripted pads); a live Start press on pad 2-4, in the hubs and in field stages | |
| Party point-message band | The party point-message band in the hubs | |
| Field SOUND freeze | Retail's field SOUND freeze | |
| Practice floor-grid light rule | The VU1 light-block rotation count is confirmed for `stag0001` only ([#3105](../../../docs/findings/findings-3001-3250.md#f3105)); the generalisation is unconfirmed ([#3106](../../../docs/findings/findings-3001-3250.md#f3106)). Widening it (other field stages, the Main Lobby hubs, a rotating or scaled ancestor, the fresh-block events of `FUN_001f9430`) needs a retail GS dump with k > 0 draws in Hard and Soft; the guard in `lobby_light_rotations` stays until one matches | [#3105](../../../docs/findings/findings-3001-3250.md#f3105), [#3106](../../../docs/findings/findings-3001-3250.md#f3106) |
| Other World-1 dungeons | The other World-1 dungeons and the real boss fight in a full World-1 run | |

### 2. Combat

Owning document: [combat foundation](../combat.md).

| item | what is missing |
| --- | --- |
| Support techniques against retail | Only the Heal Lt HP gain is retail-measured. The R1 panel, technique firing, status effects, Cure, Speed, Resist and Power are port readings |
| Technique bullets | Bullet geometry, speed and lifetime are stand-ins; the enemy-hit leg of the `technique` test is skipped until `modelcontact.c` answers the class-4 status timers |
| Raise | The Raise technique is an API only (`dw4_magic_apply_raise_refund`, `dw4_combat_set_downed`) |
| Support wiring assumptions | The volume's producer and timing, the MUTEKI bypass, area membership with a second player, KO keeping `UPDATA` |
| Statuses | A live check of whether a button press breaks a player's `SQ_STUN` / `SQ_SLEP`; the retail named-timer clock domain; enemy-to-player status effects |
| Targeting | Whether retail's ties and KO'd targets behave as the nearest-player rule implies |
| Weapons and forms | Per-weapon swing lengths; the 16 forms beyond the basic Cross chain (all 16 run it, `check-fieldforms`; only Dorumon-line numbers are retail-measured); per-form attack behaviour |
| Application path | Beyond the gate-to-`stag0001` load (`check-hub-boot-gate`): Retry/Back and the other field stages |
| Record persistence | Persistence of the record across a real save |
| Field collision | Walking off `stag0101`'s start platform falls out of the world in the port; not compared with a live retail walk |
| Windowed field stages | Windowed in-world camera, HUD and audio of field stages |
| Retail co-op tooling | The retail login crash (duplicate SIF-RPC completion of the SFSV service) is parked |
| Acceptance gaps kept separate | Complete-game, renderer, status-clock, status-order and projectile acceptance |

### 3. Audio

Owning document: [audio playback](../audio-playback.md).

- The sound-bank backend is an RPC into the sound IOP module ([#2766](../../../docs/findings/findings-2751-3000.md#f2766)). The event byte after the note,
  the `WINDOW_OPEN2` two-event wait (96 cues stay silent), the handle maximum and the audible mapping of
  sound-bank effect levels and fades need that module analysed, which is not planned.
- Positional mixing, audible playback and the timing of the cues a fight requests: the headless flows
  prove only that the requests resolve ([#2778](../../../docs/findings/findings-2751-3000.md#f2778)).
- General player and enemy sound coverage is not claimed.
- The `DTPK`/record field meanings marked unknown in
  [sound format](../../../docs/engine/sound-format.md).

### 4. Hubs, services, save and title

| item | what is missing | document |
| --- | --- | --- |
| Service checks in co-op | `check-hubtalk`, `check-hubbank`, `check-hubcnos`, `check-hubdisk`, `check-hublabo`, `check-hubshops` and `check-playerinit` cover one player; party behaviour in the hubs is checked by `coopmenus` and `test_hubowner` | [dungeon floors](../dungeon-floors.md) |
| Digivolution demo (`stagML14`) | Retail frame/audio comparison, scene lighting and shadows in the demo, co-op demos | [Digi-Lab](../labo-shop.md#the-digivolution-demo-stagml14) |
| Digi-Lab menu after an equipment check | Leftover full panel, hidden header row and leftover description have no retail capture | [Digi-Lab](../labo-shop.md#retail-comparison) |
| Unarmed records | A hub opens the unarmed appearance (no weapon graph, first authored motion section); the Terminal's first lobby and the session STATUS path in `engine.c` still reject unarmed records | [Digi-Lab](../labo-shop.md) |
| Save Keeper and join screen | The `LoadIntf2` states a player without data reaches; a retail trace of the post-save arrival; an instruction-level oracle for `SaveCtrl`/`SaveIntf`; one host memory card only | [Save Keeper](../save-keeper.md), [load scene](../load-scene.md) |
| Create on the title | The starter's 3D preview is drawn by the character UI's renderer; `NameSel`'s second entry (after a Circle back) follows the recovered code, which skips the window opening, and needs a retail capture; GAMESTART's name conversion (`3f96e0` -> `382eb0`) | [Save Keeper](../save-keeper.md#creating-a-character-on-the-title-port) |
| Called-character arrival | A retail read of the captured save's flags and the frame-exact ring phase | [lobby choreography](../lobby-choreography.md) |
| Commander Room story states | Later states need the stages that set flags 67/68/69 (`stagBS01`/`02`/`03`) and the Central puzzle's 324. Flag 20 is set by `stagGF03`'s Leomon scene, which `check-fieldroute` runs | [Commander Room](../commander-room.md), [story flag sources](../story-flag-sources.md) |
| Retail parity audit leftovers | Audio, real memory-card save/load and story-progress branches are unpaired | report in `../extras/handoffs/` and `../scratch/parity-audit/` |
| Heal gate | Heal particles | [lobby gameplay](../lobby-gameplay.md) |
| Main-menu fidelity | Original symbol/name encoding, independent mode/key and species action clocks, the complete downstream controller lifecycle, decorative selector/background pixels and full transition timing; shared live phase equivalence of the Create/Call/Yes/No outlines is unverified | [main-menu fidelity](../main-menu-fidelity.md) |
| Arrival | Window/cursor animation phase and full-frame parity, including wall fading; general randomized guide patrol and retail dispatcher-latency parity | [lobby choreography](../lobby-choreography.md) |
| Camera | Live co-op framing | [box camera](../box-camera.md) |
| Loading card pacing | The hub loading card runs at about 55 fps (work 15 ms; the CPU prepare worker competes with the main thread), and the first one to two seconds after a hub publication run unpaced (118 and 142 frames per second), to be checked against the loading-card animation clock | [Frame pacing](#frame-pacing-and-draw-cost) |
| Power-on entry | Which function starts the first front-end entry at power-on (the boot-chain tail) | [#606](../../../docs/findings/findings-0501-0750.md#f606), [#502](../../../docs/findings/findings-0501-0750.md#f502), [#505](../../../docs/findings/findings-0501-0750.md#f505), [front-end boot](../../../docs/engine/front-end-boot.md) |

### 5. STATUS and menus

- Extend STATUS acceptance to the complete opening/closing trajectory, atomic full-frame pixel parity,
  physical controller/speaker output and live joined-player transfers. The Terminal closing UI matches
  retail but its visible world underlay is not paired. Keep the current factory restrictions until
  their owning services are integrated. Documents: [STATUS menu](../status-menu.md),
  [STATUS submenus](../status-submenus.md), [STATUS views](../status-views.md).
- Successful transfers and four-slot ownership are prepared evidence, not live co-op acceptance.

### 6. Arena object model

P0 (arena core and class registry), P1 (typed `beDataBase` instances) and P2 (fight rules on typed
tables) are done; P3 (module-by-module replacement) is in progress. Remaining modules:
[arena migration backlog](../arena-migration-backlog.md). Also open: other specialized owners, live
co-op service publication, full recorder traversal and the remaining animation/material services.

### 7. Lua integration and engine services

See [Lua integration](#lua-integration).

### 8. Platforms and release validation

- Windows, a physical Steam Deck, physical speaker and controller output are not validated.
- Full-frame (whole-frame) parity with retail is not claimed for any scene.
- Running from the disc image: an ISO9660 reader in the port's file layer (P2.3).

### 9. Test harness

- The broad retail target carries an older host-database fixture with harness compile failures that
  predate the fight-record retarget; the focused retail oracles pass and the fixture needs separate
  test work.
- The optional pose and fog checks skip when their private captures are missing.
- P6.2, the differential verification harness, is `todo`.

## Lua integration

Status: **in-progress**. Contracts and verification: [Lua integration](../lua-integration.md).

Vendored Lua 4.0.1 loads all 5,291 original chunks; the recovered signed-operand bias is `2^25-1`
([#787](../../../docs/findings/findings-0751-1000.md#f787)). Native boot loads named stage bytecode, runs shared definitions, and original start/first
scripts run for the title, the hubs and field stages through scene-owned controllers.
The live 60 Hz session pump dispatches DM before the model adapters (retail manager slots 8 and 17) and
holds script and service clocks across manual pause and assigned SDL-pad disconnect without resume
catch-up.

Open:

- General actor animation and AI consumers beyond the ported sequences; remaining non-text encoded
  overloads; special receiver queries.
- General engine bindings and stage/event receiver ownership; general renderer traversal.
- Validation of full startup and stage transitions against retail.

Done (each line is owned by the linked document):

| service | findings | document |
| --- | --- | --- |
| Ordered script loading, override precedence, whole-VM globals cleanup, SD → Lua → DM teardown order | [#790](../../../docs/findings/findings-0751-1000.md#f790)–[#793](../../../docs/findings/findings-0751-1000.md#f793) | [Lua integration](../lua-integration.md) |
| DM scheduler boundary, switches, subwindow-aware counts, kind-6 skipping; receiver selection and timed SD messages | [#788](../../../docs/findings/findings-0751-1000.md#f788) | [Lua integration](../lua-integration.md) |
| Authored file-list collection, first-use text/sound residency, original func/boot asset queues; prepared packs routed into a scene-owned info registry with authored layer bindings | | [Lua integration](../lua-integration.md), [stage loading](../stage-loading.md) |
| Prepared MODELCTRL slot ownership, object creation/sequences, authored window commands, lobby camera, completion queries | | [controller services](../controller-services.md) |
| Digi-Elf arrival MOVETRANS, MOVE/MOVEEX, ACTION selection, LABEL/LABELCTRL/JUMP/WCHECK, CTRL/ONCTRL/OFCTRL/MUTEKI, ISRUN/ISSEQNAME | | [actor sequences](../actor-sequences.md) |
| WPOS AIMAP acquisition, patrol timers/choices/direction/turn limits and CTRL consumers; persistent RAM/record/HP state of prepared KIND_OBJECT slots | | [actor sequences](../actor-sequences.md) |
| Fonts, SELECTCTRL, original message/choice helpers, scene-owned text (TEXTSET, REPLACEUNKNOWN, glyph geometry) | | [dialogue services](../dialogue-services.md) |
| Byte-to-Unicode text codec (`textcodec.c`, table generated by `port/tools/gen_textcodec_table.py` from the original 424-pair table at `4c8880`, conversion `382eb0`) | | [dialogue services](../dialogue-services.md) |
| SUBWND slot ownership, GENERATE/REMOVE/ISRUN lifecycle, recursive window-tree update/close/pruning | | [STATUS menu](../status-menu.md) |
| Session property folders, record-backed SYS queries, STATUS root, WindowTitle/Title00, WindowSelect | | [player records](../player-records.md), [STATUS menu](../status-menu.md) |
| Title00–04/Select00 views, SUBWND UPDATE/ONPREVIEW/OFPREVIEW stat projection | | [STATUS views](../status-views.md) |
| DBBase string ownership and typed GETDATABASE results | [#794](../../../docs/findings/findings-0751-1000.md#f794) | [databases](../databases.md) |
| Fresh character PLAYERNAME and numeric stat initialization | [#795](../../../docs/findings/findings-0751-1000.md#f795) | [player records](../player-records.md) |
| Staged equipment commits/previews, inventory compaction, CURRENT2BASE skill persistence | [#796](../../../docs/findings/findings-0751-1000.md#f796) | [player transactions](../player-transactions.md) |
| General stat/technique recalculation and item attributes | [#797](../../../docs/findings/findings-0751-1000.md#f797) | [player stats](../player-stats.md) |
| Equipment/folder/skill controller orchestration, STATUS scene lifecycle, Select01/SelectE0/SelectE1, item/pocket/DEVICE and skill-page content, owned skill controller, owned DEVICE selector, owned Power/Main/Sub equipment views | [#798](../../../docs/findings/findings-0751-1000.md#f798), [#800](../../../docs/findings/findings-0751-1000.md#f800), [#801](../../../docs/findings/findings-0751-1000.md#f801), [#802](../../../docs/findings/findings-0751-1000.md#f802) | [STATUS submenus](../status-submenus.md) |
| DISK, DEVICE-detail and currency outer lifecycles; submenu factory identities (outer FOLDER order is DEVICE, FLAG/Key Folder, DISK, BANK) | [#824](../../../docs/findings/findings-0751-1000.md#f824), [#825](../../../docs/findings/findings-0751-1000.md#f825), [#826](../../../docs/findings/findings-0751-1000.md#f826), [#828](../../../docs/findings/findings-0751-1000.md#f828) | [STATUS submenus](../status-submenus.md) |

## Done

Each row is a finished milestone. The linked document describes the result, its evidence and its limits.

### Dungeons and field stages

| result | checks | findings | document |
| --- | --- | --- | --- |
| Humid Cave route for one to four players, `stag0101` to the Terminal | `check-dungeonroute` (`COOP=2/3/4`) | | [dungeon floors](../dungeon-floors.md) |
| Doors and walking in `dng*` floors: `HITLANDMODEL doorwallNN` holds closed doors; a stick-only player is pushed into every closed door and through it once open, presses the button (flag 128), and the boss door holds | `check-dungeondoors` | [#2856](../../../docs/findings/findings-2751-3000.md#f2856), [#2857](../../../docs/findings/findings-2751-3000.md#f2857) | [dungeon floors](../dungeon-floors.md) |
| Loot: drop models (`g_000*`), item classes, rolls, 8-unit pickup, device-folder 36 / disk stack 9 / key rules, BIT and x-data, UPCNT items, item name label, got-item effect, field-world text; the boss's `impItem 0` drop sets `FLAGFOLDER[0]`; a pickup press that delivers does not swing; the Action2 host holds 32 components so the item models' FLASH1 blink-out runs | `loot`, `lootmodels`, `test_loot` | | [dungeon floors](../dungeon-floors.md) |
| KO flow: capsule after the measured 120 ticks, BKCHIP stash, `DEADRESTART`, game over when all players are down, the end chunk's tutorial/short variants by flag 508, revive at the caster with `SQ_CMBK` | `deathflow`, `deathcoop` | [#2859](../../../docs/findings/findings-2751-3000.md#f2859)-[#2861](../../../docs/findings/findings-2751-3000.md#f2861), [#2887](../../../docs/findings/findings-2751-3000.md#f2887) | [dungeon floors](../dungeon-floors.md), [combat foundation](../combat.md) |
| Hubs with a party (NINZU 2-4 in the four hubs, mates' pads routed to their players) and pads 2-4: the talk shooter is the pressing slot, selectors read their own pad, the R1 technique panel and the STATUS/shop owner follow the slot | `coopmenus`, `test_hubowner` | | [dungeon floors](../dungeon-floors.md), [boot contract](../boot-contract.md) |
| HUD and popups: per-player panels in field worlds and (for a party) in the hubs, boss gauge, damage/EXP numbers drawn from the number controllers' digit plates (orange-top gradient matches a zoomed retail frame), fading in over 12 frames and out from frame 32 | | [#2900](../../../docs/findings/findings-2751-3000.md#f2900), [#2910](../../../docs/findings/findings-2751-3000.md#f2910)-[#2915](../../../docs/findings/findings-2751-3000.md#f2915) | [dungeon floors](../dungeon-floors.md) |
| Difficulty: the hub runtime opens the generator set of the save's `DIFFICULTY` (retail Hard read: rows 17/27/85) | | [#2858](../../../docs/findings/findings-2751-3000.md#f2858), [#2873](../../../docs/findings/findings-2751-3000.md#f2873) | [dungeon floors](../dungeon-floors.md) |
| Next dungeon opens: `dng102b1`, `dng102b2` (camera from the box rig pack, no demo cameras), `dng102b3` (Mammothmon: `RUNN02`/`RNDS`/`RNDE`, `IP` loop, `MOVEEX TZMTGD`, `bshp11`, bullet names, `CAMERA SHAKE`) and `stag0102` | `check-dungeonroute2` | [#2960](../../../docs/findings/findings-2751-3000.md#f2960)-[#2971](../../../docs/findings/findings-2751-3000.md#f2971) | [dungeon floors](../dungeon-floors.md) |
| Next dungeon by stick: 21 doors held closed and crossed, 7 buttons, exits by stick to the Terminal (the quick form is in `check`) | `check-dungeondoors2-full`, `check-dungeondoors2-boss` | [#2972](../../../docs/findings/findings-2751-3000.md#f2972)-[#2974](../../../docs/findings/findings-2751-3000.md#f2974), [#3030](../../../docs/findings/findings-3001-3250.md#f3030)-[#3034](../../../docs/findings/findings-3001-3250.md#f3034) | [dungeon floors](../dungeon-floors.md) |
| Mammothmon charges like retail (the `WHit` LUACALL registration, the wall callback, the model's own delivery size): after the intro it stands at (-595.3, 129.3) against retail's (-595.1, 129.3) | | [#3000](../../../docs/findings/findings-2751-3000.md#f3000)-[#3004](../../../docs/findings/findings-3001-3250.md#f3004) | [dungeon floors](../dungeon-floors.md) |
| Action2 motion timing: the host starts each `MOTIONSET` when the component walk reaches it, `WAITCHECK Motion` waits for that motion and for the next motion's blend (`SQ_ATCK3` lasts 103 ticks / 1.72 s, retail 103.0-103.1; this lengthens 392 damage, flinch and pose actions); the two-motion damage and attack actions of 56 models play both motions | `check-motionset` | [#3005](../../../docs/findings/findings-3001-3250.md#f3005), [#3010](../../../docs/findings/findings-3001-3250.md#f3010)-[#3015](../../../docs/findings/findings-3001-3250.md#f3015), [#3050](../../../docs/findings/findings-3001-3250.md#f3050), [#3051](../../../docs/findings/findings-3001-3250.md#f3051) | [dungeon floors](../dungeon-floors.md) |
| GENE-09 refill and its region gate; enemy death lasts 155 ticks on the flat floor and the drop comes in the destroy tick; the lethal hit snaps the victim to face the attacker and the hop flies a straight 16.35 units | `check-gene09refill` | [#3072](../../../docs/findings/findings-3001-3250.md#f3072), [#3073](../../../docs/findings/findings-3001-3250.md#f3073), [#3080](../../../docs/findings/findings-3001-3250.md#f3080)-[#3083](../../../docs/findings/findings-3001-3250.md#f3083) | [dungeon floors](../dungeon-floors.md) |
| Walls and floors: wall sets selected per model by check flag; the 0x802 and kind-4 graphs for players and hub actors (the practice arena has a boundary); dynamic 0x402 props (bushes, rocks, boxes, rotated props) are solid; enemies use the special wall kinds and the props, fall off ledges that have no wall (the retail floor response, unsupported -> `SQ_FALL`, runs for enemy models and no floor edge holds a walking or hopping enemy), and a model's LUACALL hit callbacks live only until its next sequence; the void air walk | `check-arenawalls`, `check-fieldstage-propwalls`, `check-fieldstage-enemyfall`, `check-fieldstage-room-stagGF03` | [#3100](../../../docs/findings/findings-3001-3250.md#f3100), [#3102](../../../docs/findings/findings-3001-3250.md#f3102), [#3103](../../../docs/findings/findings-3001-3250.md#f3103), [#3107](../../../docs/findings/findings-3001-3250.md#f3107)-[#3110](../../../docs/findings/findings-3001-3250.md#f3110), [#3112](../../../docs/findings/findings-3001-3250.md#f3112), [#3113](../../../docs/findings/findings-3001-3250.md#f3113) | [dungeon floors](../dungeon-floors.md) |
| Field-stage Start menu; HUD hide, return and fade-in at NPC dialogue; the light rule in Goblin Pass and `dng101b2` | `check-fieldstage-startmenu` | [#3095](../../../docs/findings/findings-3001-3250.md#f3095), [#3111](../../../docs/findings/findings-3001-3250.md#f3111), [#3114](../../../docs/findings/findings-3001-3250.md#f3114), [#3115](../../../docs/findings/findings-3001-3250.md#f3115) | [dungeon floors](../dungeon-floors.md) |
| Practice floor-grid brightness: retail's VU1 rotates the packed light block in place on every draw that follows a hardware matrix upload, and the EE re-sends a fresh block only after a model-view upload; the port counts that rotation k per static `BG02` mesh in field stages (`dw4_scene_node_light_rot`, applied in `lobby_vertex_color`); k = 1, 2, 3, 3 for nodes 2184/2186/2189/2191, draw colours within one count of the retail dump, k = 0 draws unchanged | `check-practicelight` | [#3105](../../../docs/findings/findings-3001-3250.md#f3105) | [lighting](../../../docs/engine/p2-lighting.md#the-vu1-rotates-the-light-block-in-place), [combat foundation](../combat.md) |
| Presentation defects fixed: stale atlas from the shared GPU-layer texture cache on the next loading card; practice tutorial text under its window; save scene's stale textures and leaked layer reference; plain loading cards showing text instead of retail's black screen; Digimon info card text under its window | `check-loadingstale`, `check-practicetext` | [#3090](../../../docs/findings/findings-3001-3250.md#f3090)-[#3094](../../../docs/findings/findings-3001-3250.md#f3094) | [stage loading](../stage-loading.md), [combat foundation](../combat.md) |

Retail confirmations of the Humid Cave (savestates from the crown-mod work; stat reads cross-checked
against the ISO): entry hop, spawn, HUD layout, entry music pair ([#2795](../../../docs/findings/findings-2751-3000.md#f2795)), entry camera pose ([#2796](../../../docs/findings/findings-2751-3000.md#f2796)), the
camera option record (`CAMERAMODE` 0 -> Near eye z 90, written to 1 before the stage load -> Far eye z
98, [#2855](../../../docs/findings/findings-2751-3000.md#f2855), [#2888](../../../docs/findings/findings-2751-3000.md#f2888)), a real KO of a level-1 save (BKCHIP stash, capsule, Terminal arrival with HP
restored, tutorial vs short message, [#2859](../../../docs/findings/findings-2751-3000.md#f2859)-[#2861](../../../docs/findings/findings-2751-3000.md#f2861)), the EXP loss at level 5 (3500 -> 3257, [#2887](../../../docs/findings/findings-2751-3000.md#f2887)), the
boss floor's generator rows and Blossomon's HPMAX 2640 with `BT_SBOSS` playing ([#2873](../../../docs/findings/findings-2751-3000.md#f2873), [#2874](../../../docs/findings/findings-2751-3000.md#f2874)), the kill
in four hits with flag 119 and the ID Key (`FLAGFOLDER[0]` 0 -> 1, [#2875](../../../docs/findings/findings-2751-3000.md#f2875)), a damage number at the hit
enemy's position ([#2805](../../../docs/findings/findings-2751-3000.md#f2805)), the two-player KO and revive on a clean cold boot ([#2925](../../../docs/findings/findings-2751-3000.md#f2925), [#2930](../../../docs/findings/findings-2751-3000.md#f2930): a Raise Disk
used with Cross next to the capsule gives the sparkle effect, one disk used, HP 100, model at the
caster), the ISREADY rule against the typed source ([#2788](../../../docs/findings/findings-2751-3000.md#f2788)) and a level-1 starter losing to the first
Numemon like the port ([#2789](../../../docs/findings/findings-2751-3000.md#f2789), [#2929](../../../docs/findings/findings-2751-3000.md#f2929)).

Retail confirmations of the next dungeon (dev-world stage select, level-99 fixture): Mammothmon row 97
/ HP 302, the `dng102b3` generator rows, boss sequences, music and the defeat timeline match the port
([#2977](../../../docs/findings/findings-2751-3000.md#f2977), [#2978](../../../docs/findings/findings-2751-3000.md#f2978)); the `CAMERA SHAKE` ([#2968](../../../docs/findings/findings-2751-3000.md#f2968), [#2979](../../../docs/findings/findings-2751-3000.md#f2979)), the hit-box names, the wave tables and fills, the
button flags and the boss damage rule ([#2980](../../../docs/findings/findings-2751-3000.md#f2980)-[#2984](../../../docs/findings/findings-2751-3000.md#f2984); chests and boss damage unconfirmed). The findings
sweep settled all of [#2960](../../../docs/findings/findings-2751-3000.md#f2960)-[#3034](../../../docs/findings/findings-3001-3250.md#f3034) except the ones noted in [dungeon floors](../dungeon-floors.md): the
blend wait is confirmed live at 103 ticks, GENE-09, fixture resistances and the contact-hit formula are
read, the Square guard is wired and the drop roll is fixed. Later passes settled [#3041](../../../docs/findings/findings-3001-3250.md#f3041), [#3051](../../../docs/findings/findings-3001-3250.md#f3051), [#3061](../../../docs/findings/findings-3001-3250.md#f3061) and
[#3071](../../../docs/findings/findings-3001-3250.md#f3071), the intro charge timeline and the GENE-09 refill with its region gate ([#3012](../../../docs/findings/findings-3001-3250.md#f3012), [#2978](../../../docs/findings/findings-2751-3000.md#f2978), [#3072](../../../docs/findings/findings-3001-3250.md#f3072)), and
read 117 victims and the outside-the-box drop timing ([#3081](../../../docs/findings/findings-3001-3250.md#f3081), [#3082](../../../docs/findings/findings-3001-3250.md#f3082)).

### Combat foundation

Owning document: [combat foundation](../combat.md). From the connected hub the first mission stage is
entered and fought headlessly.

| result | checks | findings | document |
| --- | --- | --- | --- |
| Mission route: one headless process from a fresh save (flag 503 clear) at the Terminal Outside World gate through the practice stage `stag0001` (four lessons and the arena, played by a pilot bot), `stag0101` → `stagGF01` → `stagGF02` → `stagGF03` (each exit region's own script and Cross-confirmed prompt), the Machinedramon kill by Cross swings, the Leomon scene (flag 383, flag 20, `NEXTSTAGE stagML02` point 1) and `stagML02` prepared from the record with flag 20 kept; game over (`end_g_000bcaps.lua`) returns to `stagML11` | `check-fieldroute`, `check-hub-boot-gate` | | [combat foundation](../combat.md) |
| Field stage runtime: `stag0101` prepared as a field world with original start/first scripts, `GENERATER` through the authored generator packs, enemy actors (database rows/HP, ENEMY receivers, script state, NEAR AIMAP), the scripted `e_goburi` introduction, revisit by flag 355, `gatedisc.lua` exit to `stagML11` point 3 | `check-fieldstage` | | [combat foundation](../combat.md) |
| Player attack path, retail-checked: hit/crit/damage/EXP/level-up/skill growth/technique damage, P2E single-hit damage (five TSUYOSA values, boss row 60) and E2P boss hits (`check-fieldstage` mode `retail`), one-player EXP (+133 for row 388), the level 1→2 stat record, Heal Lt arithmetic, jump momentum stop on control loss, co-op EXP splits for 2/3/4 players, practice-wave sizes, nearest-player targeting, the all-players-on-the-gate rule | `attack`, `hurt`, `retail`, `check-fieldforms` | | [combat foundation](../combat.md) |
| From matched source and self-consistency tests (not retail-compared): status-time rules (`fightstatus_p2e.c`, `fightstatus_e2p.c`), support techniques (`fightmagic.c`), area query / heal / cure / raise application (`magicapply.c`), buff apply/timer/expiry (`buffapply.c`), status application on models (`statusapply.c`) | `statusapply`, `statusflow`, `statusflow_e2p` | | [combat foundation](../combat.md) |
| Statuses on the running models: `MDLsetSD` `SETxxx` / `CLEARSTATUS` / `ALLCLEARSTATUS` reach a per-model `dw4_status`, `MDLisStatus` is the `CHECKSTATUS` query, the sequence-change hook `FUN_00445200`, the `BLT` / `BLP` `get*Time` wrappers (retail base-number gate 20 / 90 / 95 / 70 / 85) | `statusapply`, `statusflow`, `statusflow_e2p` | | [combat foundation](../combat.md) |
| Technique firing: R1 panel (open/close, cursor, Cross swallowed while open), MP charge, DEBOUNCE/DELAY/NG locks, `SQ_WAZA` with the pcTech LABEL and a stand-in bullet (`port/src/technique.c`, `dw4_combat_fire`) | `technique` | | [combat foundation](../combat.md) |
| Support techniques through the R1 panel: Heal Lt / Heal, Cure Lt / Cure, Speed, Resist, Power (`dw4_combat_cast_support`; the original `hit_p_<species>.lua` support branch and `BLPcalcKoukaMagic`); buffs live in the model's `dw4_status` and expire on the hub tick (1/60 s units, 2^18 ns completion steps) | `supportheal`, `supportbuff`, `supportcure`, `supportraise`, `supportcast` | | [combat foundation](../combat.md) |
| Drop tables decode and roll; sums equal the live-measured ones | `droptables` | | [combat foundation](../combat.md) |
| BIND movement-list/enum gate | | [#2744](../../../docs/findings/findings-2501-2750.md#f2744) | [combat foundation](../combat.md) |
| Fight status/calculation read the recovered `beDataObjInt/IntList/ObjectList`, `igIntList` and `beNDMWItemWaza` instances through arena handles | `check-fightrecords`, `check-fightrecords-retail` | [#2727](../../../docs/findings/findings-2501-2750.md#f2727) | [combat foundation](../combat.md) |
| Arena core, class registry and typed databases (`port/src/arena.c`, `port/src/arenapack.c`, `port/src/arenadb.c`); fight rules read typed tables (`dw4_dbtable`); the host `dw4_database` holds only a name and a typed table; the session arena holds the databases, the player-record property folders (typed `beDataObjList` trees) and stage-object infos (`dw4_stageobject_*`) | `check-arena`, `check-arenadb` | | [arena object model](../arena-object-model.md) |
| `dw4_object_init_header` (`port/src/object.c`) retargeted onto the decomp headers | `check-igobject-header`, `check-decomp-headers` | | [typed game layer](../../../docs/engine/typed-game-layer.md) |
| Shared window/controller/shop/STATUS arena module; concrete shop and STATUS records; menu resources, stock and retained references; MODELCTRL manager/RAM/Work/node records | `check-menu-arena` | [#2728](../../../docs/findings/findings-2501-2750.md#f2728)-[#2734](../../../docs/findings/findings-2501-2750.md#f2734) | [arena object model](../arena-object-model.md), [STATUS menu](../status-menu.md) |
| Action2 manager/info/RAM/Work, typed HITBOX subcommands, STATUS preview on the thirteen-value `_parameter` list | | [#2735](../../../docs/findings/findings-2501-2750.md#f2735)–[#2737](../../../docs/findings/findings-2501-2750.md#f2737) | [arena object model](../arena-object-model.md) |
| Retail subcommand scheduler and Work node locks; SCEffect/SCSound scheduling, attachment (MOVERL), sound handles; published player dependencies | | [#2738](../../../docs/findings/findings-2501-2750.md#f2738)–[#2743](../../../docs/findings/findings-2501-2750.md#f2743), [#2745](../../../docs/findings/findings-2501-2750.md#f2745) | [controller services](../controller-services.md) |
| Stage sound catalogue from the sound packs' `beSoundData` records (`stagesound.c`), `dw4_frontaudio_prepare_gameplay`, the retail effect pool, music change, stream fade and stop rules | | [#2757](../../../docs/findings/findings-2751-3000.md#f2757)–[#2768](../../../docs/findings/findings-2751-3000.md#f2768) | [audio playback](../audio-playback.md) |

Three test-environment rules keep the full suite stable: `port/tools/crosscheck.sh` pins `LC_ALL=C`,
`port/tools/verify_audio.py` allows 120 s per run, and `test_input` tolerates a connected physical
gamepad.

### Connected hubs and services

| result | checks | findings | document |
| --- | --- | --- | --- |
| Terminal ↔ Central ↔ Shop travel through original exits (confirm, No, Circle), loading card, destination placement, restored control; deferred stage requests owned by the native stage-request owner; application loading and publication with a CPU prepare worker | | | [hub travel](../hub-travel.md) |
| Hub verification against retail: all 19 headless hub checks pass; shops, Card Keeper flag states and most edges equal retail; the walking and enemy wall query is the recovered one-sided ray solver (the Central holds were hold-end artefacts, [#3086](../../../docs/findings/findings-3001-3250.md#f3086) refuted) | `check-hubedges` (8 of 8, part of `check`) | [#3084](../../../docs/findings/findings-3001-3250.md#f3084)-[#3088](../../../docs/findings/findings-3001-3250.md#f3088) | [hub travel](../hub-travel.md) |
| NPC contact and live talk: authored HIT talk flags, body projection/probe, live Cross, `CHKBULLET` to every active receiver | `check-hubtalk`, `check-hubnpcs` | | [NPC interactions](../npc-interactions.md) |
| All 38 Terminal/Central/Shop talker cases classified: none stuck, missed or unimplemented (22 implemented services); SUBWND CARD is requested by no hub pack | `check-hubnpcs` | | [NPC interactions](../npc-interactions.md) |
| XDATA stat and chip upgrades | `check-hubtalk` | | [XDATA shop](../xdata-shop.md) |
| NPC bank (SUBWND mode 3), NPC appraiser (mode 4), Digi-Lab (mode 2), Digi-Disk shop (mode 5), weapon/armor/chip/junk shops (modes 6–9) | `check-hubbank`, `check-hubcnos`, `check-hublabo`, `check-hubdisk`, `check-hubshops`, `check-playerinit` | | [NPC bank](../bank-shop.md), [NPC appraiser](../cnos-shop.md), [Digi-Lab](../labo-shop.md), [Digi-Disk shop](../disk-shop.md), [equipment shops](../equipment-shops.md) |
| Generic shop root (`ShopCtrl00`) under XDATA, BANK, CNOS, DISK and the WPU/APU/CHIP/JUNK shops; LABO runs under it with entry code 2 and Digilabo's own widgets (StatusTitle03 is the legend, not an account window) | | | [shop root](../shop-root.md), [Digi-Lab](../labo-shop.md#retail-comparison) |
| The Digi-Lab's result reaches the world (form, `POWERSOCKETNAME[0]` weapon, HUD portrait row, level/HP/MP in the next prepared hub); the digivolution demo `stagML14` (NDMW 831/832) runs as a hub scene host (`dw4/evodemo.h`); `DW4_EVODEMO=skip` keeps the substitution as a logged fallback | `check-hublabo` | | [Digi-Lab](../labo-shop.md#the-digivolution-demo-stagml14) |
| Central's disk-collector Prmame (`n_prmame`) and the `SYSctlDiskFolder` / `SYSctlDeviceFolder` services | `check-hubprmame`, `check-playerinit`, `check-playertransactions-retail` | | [Prmame](../prmame-npc.md) |
| Commander Room (`stagML02`, NDMW 815/816): round trip from the Terminal's `mate01` gate, welcome, label, briefing, every NPC's talk, exit choices and five later story states | `check-hubcommander`, `check-hubnpcs`, `port/tools/test_dialogue_e2e.py --only Commander` | | [Commander Room](../commander-room.md) |
| All six portal destinations prepare and run | `check-hubstages` | | [hub travel](../hub-travel.md) |
| Save codec (two mirrored blocks, four character records, item ids, atomic file write), byte-identical on six retail-written saves | `check-saveimage` | | [save image](../save-image.md) |
| Host memory card (`port/src/memcard.c`), `beNDMWSaveCtrl` (`port/src/savectrl.c`), `SaveIntf` (`port/src/saveintf.c`), the save scene host (`port/src/savescene.c`), `SYSctlFlagFolder`, the save library; pack 810's `SETGENERATEPOS 3 / stagML11` chunk is the disc-gate template that no object in the scene runs | `check-savectrl`, `check-saveintf`, `check-savescene`, `check-hubsave`, `port/tools/test_save_cycle.py` | [#967](../../../docs/findings/findings-0751-1000.md#f967) | [Save Keeper](../save-keeper.md) |
| Join screen `stagIS13` (`LoadCtrl2`/`LoadIntf2`; player 0's panel, START, return to `stagML11` point 4) | `check-hubload` | | [load scene](../load-scene.md) |
| Card album `stagIS11` (SUBWND CARD: `ShopCtrlA0/A1/A2`, Booster Pack draw, album pages) | `check-hubcard` | | [card album](../card-album.md) |
| Title *Call Digimon* runs the original screens (`LoadIntf2` states 6 to 8, item states 5 and 6, DIFFSELECT) in a `DW4_SCENE_TITLE` scene and rebuilds the loaded character with BASE2CURRENT; *Create* runs the starter choice (`MakeChr`, state 4), name entry (`NameSel` `3de260`/`3def80`) and state 8's GAMESTART in the same scene | `check-titlecall` | [#999](../../../docs/findings/findings-0751-1000.md#f999)-[#1002](../../../docs/findings/findings-1001-1250.md#f1002) | [Save Keeper](../save-keeper.md) |
| All sixteen player forms stand in the world: the lobby opens by shinka row (`dw4_lobby_open_row_stage`), the hub reads the model from the record's `DIGIMONNAME`, the HUD portrait atlas covers WAIT01..WAIT16, name codes from retail saves display as ASCII; a retail level-999 Susanoomon save called from the title reaches the Terminal | `check-lobbyrows` | [#1005](../../../docs/findings/findings-1001-1250.md#f1005) | [lobby gameplay](../lobby-gameplay.md) |
| Called-character arrival with flag 501 set: entry rings/stars follow the scripts' PLAYER `SQ_ENTR` (tick 31); the guide is generated only in some story states (flag 1, 2 without 20, 4 with 82, 5, 6, 86) and then patrols from `SQ_WALKON 25` | `check-called-arrival` | | [lobby choreography](../lobby-choreography.md) |
| Service-window frames (XDATA, bank, labo, disk, CNOS, shops; 29 in all) match the CPU oracle on the offscreen GLES3 backend on a hardware GPU | | | [lobby rendering](../lobby-rendering.md) |
| Retail parity audit (Near/Hard options): lobby, hub travel, NPC dialogue, Save Keeper path, STATUS root, walking speed and jump height equal retail; the player's visible graph and weapon cast projective shadows; the player-number badge is drawn | `check-retail` | [#1090](../../../docs/findings/findings-1001-1250.md#f1090) | [lobby choreography](../lobby-choreography.md) |
| Paired equipped weapons: both authored PC01 hand branches publish | | | [lobby rendering](../lobby-rendering.md) |

### Main Lobby, STATUS and rendering

| result | checks | findings | document |
| --- | --- | --- | --- |
| Main Lobby movement and original startup: created-card boot runs original start.lua/first.lua through scene-owned services; authored weapon-label sequences, acceleration/braking, collision | | [#848](../../../docs/findings/findings-0751-1000.md#f848)–[#849](../../../docs/findings/findings-0751-1000.md#f849) | [lobby gameplay](../lobby-gameplay.md) |
| Jump (Circle), three proximity gates, the heal material callback (original `mate03.lua`/`funcHealGate`) | | | [lobby gameplay](../lobby-gameplay.md) |
| Stage portal rotor, commander switch instances, walking falls (`SQ_FALL`, 30 -> 20 -> 10) | | | [lobby gameplay](../lobby-gameplay.md) |
| Camera region smoothing (`beCameraCtrl` transitions, 120-frame timing) | | [#850](../../../docs/findings/findings-0751-1000.md#f850) | [box camera](../box-camera.md) |
| Bounded lobby rendering: actor shadows, arrival timing, conditional visibility, portal states, clipping/GS raster corrections; retained environment RGB error 10.6747 → 1.2044/255 | | | [lobby rendering](../lobby-rendering.md) |
| Arrival against retail: all 15 greeting pages pass retained vertex/texture comparisons (4,758 vertices; maximum 0.062515 px); the naming Yes/No cursor is the original `j_linewin02` diamond/ring; the guide departs on the first WALKON leg at final dialogue closure | | | [lobby choreography](../lobby-choreography.md) |
| HUD: record-backed meters, authored number geometry, no synthetic player-name glyph row; Cross or Circle advance the greeting | `check-status-boot` | | [lobby greeting UI](../lobby-greeting-ui.md), [lobby rendering](../lobby-rendering.md) |
| Main-menu fidelity: summary labels, Create/Call, Yes/No and naming cursors, title texture bindings and scaling; the USA name limit is eight | | | [main-menu fidelity](../main-menu-fidelity.md), [title controller](../title-controller.md) |
| Normal mode-zero STATUS for the created first player: equipment, FOLDER and skill trees, transactions, authored model/font rendering, world/audio/player/HUD freeze and restoration; seventeen settled menus match retail (128,352 pipeline vertices, 27,772 ordered pixel-bearing triangles) | `check-status-boot`, `check-status-live`, `check-status-gpu` | [#806](../../../docs/findings/findings-0751-1000.md#f806) (first-child Title01 clause refuted), [#820](../../../docs/findings/findings-0751-1000.md#f820) (reset clause refuted), [#824](../../../docs/findings/findings-0751-1000.md#f824)-[#828](../../../docs/findings/findings-0751-1000.md#f828) | [STATUS menu](../status-menu.md), [STATUS submenus](../status-submenus.md), [STATUS views](../status-views.md) |
| STATUS uses a session-owned persistent GPU renderer for model and font passes (about 3 ms for the prepared passes at 1280x960 against about 40 ms on the CPU path) | `check-status-gpu` | | [GPU rendering](../gpu-rendering.md) |
| GPU-only normal rendering for boot, loading, HUD/overlays, front-end effects, offscreen passes, movie and stage entry points; required mode rejects CPU pixel calls before writes | `check-gpu-entries`, `check-title-mesh-gpu`, `check-status-gpu`, `check-gl-mesh`, `check-gl-post`, `check-fefont-gpu` | | [GPU rendering](../gpu-rendering.md) |
| Background focus behaviour | | | [Lua integration](../lua-integration.md#live-simulation-pump) |
| Loading presentation: the live catch-up loop presents every loading sample (an SDL-dummy live-loop test injects a ten-tick stall and compares loading samples with presentations) | | | [stage loading](../stage-loading.md) |
| Front-end boot: power-on → opening FMV → title presented and waiting for input → character select → Main Lobby, with the light-trail layer generated from the pack and its camera recovered from the pack | `port/tools/verify_frontend.py` | [#447](../../../docs/findings/findings-0251-0500.md#f447), [#605](../../../docs/findings/findings-0501-0750.md#f605), [#606](../../../docs/findings/findings-0501-0750.md#f606), [#608](../../../docs/findings/findings-0501-0750.md#f608), [#610](../../../docs/findings/findings-0501-0750.md#f610)–[#612](../../../docs/findings/findings-0501-0750.md#f612), [#628](../../../docs/findings/findings-0501-0750.md#f628), [#630](../../../docs/findings/findings-0501-0750.md#f630), [#631](../../../docs/findings/findings-0501-0750.md#f631) | [boot contract](../boot-contract.md), [front-end boot](../../../docs/engine/front-end-boot.md), [port README](../../README.md) |

### Frame pacing and draw cost

Trace with `DW4_FRAME_TRACE=1`; tools `port/tools/profile_lobby.py` and `make -C port profile-hubstages`
([port documentation](../README.md)).

- Pacing is an absolute schedule with MAILBOX present (FIFO on a 144 Hz display alternated 2 and 3
  vblanks per tick). The Vulkan present window handles gamepad input.
- The lobby mesh loop splits the per-mesh vertex cache into position and shading stages, rejects whole
  meshes and single triangles against the frustum, and fast-accepts triangles wholly inside the view.
  Main Lobby work time is about 10.5 ms idle and 13–14 ms in Digi-Elf dialogue against the 16.7 ms
  budget (60–61 fps).
- The lobby draw, title frame, Option screen, character/login screens, loading cards and the FPS counter
  run as resident frames through `dw4_gl_layer_defer`/`dw4_gl_layer_share`, so no GPU pass round-trips
  the CPU framebuffer. At 2560x1440 on Vulkan and SDL every screen measures 60.5-60.7 fps: Terminal
  7.4-8.5 ms work, Central 12.7-13.2, Shop 8.9-9.4, main menu 11-12, Option 12.3-12.6, character
  creation 4.4, loading card 6.3.
- `dw4_modelctrl_open_info` borrows the caller's already-open pack (read only; the model keeps no
  reference to it), so `dw4_controllers_open` takes 13 ms and the first-lobby handoff about 113 ms; the
  remaining handoff cost is file-list begin 17 ms + route assets 58 ms. Hub-to-hub handoffs take about
  3 ms.
- Live GPU window (Vulkan, 1280x960, scripted Terminal → Central → Shop with `DW4_DEV_WARP`): Terminal
  arrival 60.6 fps / 10.2 ms work, Central 60–61 fps / 12.8 ms, Shop 60.6 fps / 10.7 ms, 0–1 frames per
  second over budget.
- Remaining per-frame lobby cost is the GPU passes (shadow ≈ 0.9 ms, world ≈ 3.2 ms) and the
  dialogue/native UI (≈ 3 ms); Central (`StagML12`) is the heaviest hub stage on the CPU side.

## Engine workstreams

Each workstream says why it is needed, what exists, and its status.

### P1 — Typed, named code (the prerequisite)

**Why.** Matched C is byte-exact int-soup (`*(int *)((char *)p + 8)`). It satisfies the matching oracle
and cannot be recompiled by another compiler. Every workstream below consumes *typed* engine code.

**Metric.** `tools/typed_coverage.py`, gated by `config/typed-coverage.json`; the gate is on the
**count** of recovered accesses, never the ratio (the m2c loop keeps adding untyped C). `make
typed-check` reports the current count ([typed coverage](../../../docs/engine/typed-coverage.md)). Five
routes to more are measured dry — the receiver rule (named reflected classes exhausted), vtable
membership, call-site propagation, object-ref chains via `_metaObject`, and the assert-string source —
so what is left is manual per-module work ([#442](../../../docs/findings/findings-0251-0500.md#f442)).

| id | task | state | status |
| --- | --- | --- | --- |
| **P1.1** | **Receiver typing** — rewrite `*(T *)((char *)(arg0) + N)` to `arg0->_field` where the function name gives the class | `scripts/retype_receiver_class.py` applies the reflection structs where the receiver class is unambiguous, width-checked against `reflected.h`, so it cannot change codegen (`make check` is the test) | done |
| **P1.2** | **Signature recovery** — a table of recovered return/parameter types for engine functions (`igMetaObject_GetFieldAt(...) -> igMetaField *`) | `config/SLUS-20836/signatures.tsv`, seeded from the recovered object model and applied to the 416-function `<Class>_InitFields` family including inherited fields (1,310 accesses across 550 files; [#437](../../../docs/findings/findings-0251-0500.md#f437)–[#440](../../../docs/findings/findings-0251-0500.md#f440)). Of 1,389 offset casts inside class-named matched functions only 46 have the receiver as their base; the rest are on temporaries holding a call result. After it, 2,621 of the 2,826 remaining raw casts are in unnamed `FUN_*` units, so the next lever is naming (P1.3); the table should still grow | done (first increment) |
| **P1.3** | **Name receivers** (tracker T6) — the naming loop | Scope ([#488](../../../docs/findings/findings-0251-0500.md#f488)): the backlog is 68 game functions / 289 casts; the other 85 % is third-party middleware (Intrinsic Alchemy 801 casts, Sony SDK+C runtime 140, CRIWARE 112, Lua 88, CRI audio 57, libpng 20), which a port replaces wholesale and which is not typed at all. `docs/engine/module-map.md` (generated by `scripts/module_map.py`) is the region map; `scripts/typed_worklist.py --by-region --game-only` is the queue. Sources used: game-class constructors named from the RTTI vtable by constructor shape (`scripts/seed_names_constructors.py`, [#501](../../../docs/findings/findings-0501-0750.md#f501)); `<Class>_GetVTable` resolves the vtable for 958 / 980 classes (499 without an `__RTTI__` record), naming 1,177 RTTI-less slots (`config/SLUS-20836/names/GetVTableSlots.tsv`, [#529](../../../docs/findings/findings-0501-0750.md#f529)/#530; all 499 are `ig*`, so it does not feed the receiver pass); `retype_receiver_class.py --class-regex be`; `scripts/retype_block_receiver.py` types an unnamed `FUN_*` bracketed by two vfuncs of one reflected class when every `arg0`/`this` cast matches a field of that class ([#539](../../../docs/findings/findings-0501-0750.md#f539)). The typing passes are re-run after each bulk bank (`retype_initfields.py`, [#538](../../../docs/findings/findings-0501-0750.md#f538)). Measured dry: a receiver class inferred from the offsets it touches is unique for 0 of 78 unmatched game functions, and `vfunc_*` adjacency recovers the class but not the role, so the remaining game-side queue needs a role source (a caller, a string, or the live route P1.4) | in-progress |
| **P1.4** | **Object identity from a live instance** (`+0` is the class vtable; [#415](../../../docs/findings/findings-0251-0500.md#f415)/#416) | The one route that supplies identity without naming the receiver first. 171 of 478 classes are instantiated in a loaded stage, so a batch can be scoped to what the game builds. Needs the emulator; evidence goes to the findings store | todo |
| **P1.5** | **32-bit pointer policy** | Decided: [pointer model](pointer-model.md) (see the decisions table) | done |

### P2 — The platform seam (32 interfaces, not 18,661 functions)

**Why.** The engine is written against generic platform classes; the PS2 implementations sit under
them. All 32 `igPsx2*` classes derive from a non-PS2 base (`igPsx2File → igFile`, `igPsx2Controller →
igController`, `igPsx2Thread → igThread`, `igPsx2VisualContext → igVisualContext`, …). Implement the
*generic* classes natively and the engine logic runs unchanged. `igPsx2IopRpcConnection` (the one class
based on `igObject` — the seam itself) is deleted.

| id | task | state | status |
| --- | --- | --- | --- |
| **P2.1** | Host backend skeleton | The seam is an inventory ([#497](../../../docs/findings/findings-0251-0500.md#f497)): 32 `igPsx2*` classes, 31 under 30 generic interfaces with 153 fields; [platform seam](../../../docs/engine/platform-seam.md) has the interface→fields table (gated by `make rules`). `port/include/dw4/platform.h` declares it, `port/src/host.c` carries the table, `dw4asset platform [-v]` reports it and `port/tools/verify_platform.py` pins the totals. The engine prints `1 implemented, 2 input, 28 stub`: `igFile` is implemented (`port/src/igfile.c`) and `igPsx2Controller`/`igPsx2ControllerManager` are `DW4_IF_INPUT`. Next: the ops each interface needs (`igThread`/sync, `igAudioContext`, `igVisualContext`/`igWindow`), then P2.2 | done (first increment) |
| **P2.2** | Threads / timers | pthreads + a monotonic clock (`igLongTimer`); the 39 named OS functions in [platform boundary](../../../docs/engine/platform-boundary.md) are the shim list | todo |
| **P2.3** | Files | `port/src/igfile.c` is the host `igFile`: a plain file, an AFS entry, a manifest name, or the n-th `[pt.entry]` reference of a stage file, all mapped (the archives are 727/511 MB, so nothing is slurped). `dw4_igfile_open_stage_ref()` is the engine's own route to a stage's packs ([#445](../../../docs/findings/findings-0251-0500.md#f445)). Open: an ISO9660 reader, for running from the disc image rather than a directory of extracted assets | done (first increment) |
| **P2.4** | Pad / audio | Keyboard and SDL gamepad input reach `dw4_input_state` with the game's mapping (`port/src/input.c`, `dw4_window_pump`; `SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS=1` is set before `SDL_Init` because SDL drops controller events without input focus); native audio is described in [audio playback](../audio-playback.md) | in-progress |
| **P2.5** | Delete the IOP seam | Reimplement what the 11 `.irx` + `IOPRP280.IMG` did (pad, sound, files, memcard) in native code; the EE↔IOP RPC path disappears | todo |
| **P2.6** | **Runtime object model** — `igObject`/`igMetaObject`/`igMetaField` plus reflection-driven field access, running | The loaded stage (NDMW.AFS 621+622) instantiates 39,341 records over 203 distinct classes using 17 named MetaField types (`igObjectRef` dominating at 30,242 values), and the port constructs each record as a reflection-typed object ([#500](../../../docs/findings/findings-0251-0500.md#f500)): `port/include/dw4/object.h` + `port/src/object.c`, schema generated from `data/reflection.json` (`port/tools/gen_reflection.py` → `port/src/reflection_data.c`, 1074 classes / 3680 fields); `dw4asset reflect` reads fields by name; `port/tools/verify_object.py` diffs 39,341 records / 70,077 field values against the decompilation's independent decoder with 0 disagreements. The generator merges `data/vtables-getvtable.json` with `data/vtables.json`, so the schema carries a vtable address for 976 of the 1,074 classes ([#529](../../../docs/findings/findings-0501-0750.md#f529)), including `igPsx2Image` 0x525630, `igTextureAttr` 0x522c60 and `igPrimLengthArray1_1` 0x526590. Open: the `igObject` vtable interface block / MetaObject method slots ([#359](../../../docs/findings/findings-0251-0500.md#f359)) — construction and reflection access work, method dispatch does not; the slot-to-method signatures; class `0x5284f0` (the largest live class); the census uses the pack's records, not the live 171-of-478 instantiated set ([#415](../../../docs/findings/findings-0251-0500.md#f415)) | in-progress |

### P3 — Asset loaders

**Why.** The formats are documented and the loaders are independent of further engine decompilation.

| id | task | state | status |
| --- | --- | --- | --- |
| **P3.1** | AFS archives | `port/src/afs.c` reads the entry table, extracts entries and hands out entry views; `make check` agrees with the repository's decoders on `NDMW.AFS` (972 entries). [AFS archives](../../../docs/engine/afs-archives.md) | done |
| **P3.2** | The virtual FS manifest | `port/src/manifest.c` + `port/src/mount.c` decode `NDMW.IGB` as the filesystem (`beNDMWAfsSetupData` names the archives, `igAdxAfsFile._ptNumber`/`_fileNumber` are archive/entry, [#444](../../../docs/findings/findings-0251-0500.md#f444)) and open both archives mapped: `mount <roms> ls\|cat\|refs\|check`. All 2,080 names agree with the repository's decoder; 2,079 resolve (the 2,080th is the manifest's own `NONE` sentinel); `find stag0102.igb` round-trips to AFS entry 140's bytes. A stage's `[pt.entry]` packs resolve too (`[0.620]`/`[0.621]` = entries 620/621, [#445](../../../docs/findings/findings-0251-0500.md#f445)). `scan <roms> <class>` shows which entries carry a class | done |
| **P3.3** | igBinary object graph | Class directory + record stream + content pool decoded in C and cross-checked (`port/src/igb.c`). An `igObjectRef` id indexes the pack's remap table between the two object sections ([#460](../../../docs/findings/findings-0251-0500.md#f460)); an `igMemoryRef` value is the id of its pool block, whose offset is the `_memSize` prefix sum over the `igMemoryDirEntry` ids ([#464](../../../docs/findings/findings-0251-0500.md#f464)). C API `dw4_igb_refs_open()` / `dw4_igb_ref()` / `dw4_igb_block()`, CLI `refs`; `make check` diffs its numbers against `igb_ids.py` + `igb_pool.py` on entries 622/183/140/621. [igBinary format](../../../docs/engine/igbinary-format.md) | done |
| **P3.4** | Textures / clut | `port/src/texture.c` decodes 8/4-bit indices with an RGBA8888 or PS2 CSM1 palette (pixel-exact in `port/tools/verify_texture.py`); `port/src/png.c` writes PNGs with no dependencies. Textures live in separate texture packs (625/626/618/619: directory + string table + records + a flat pool of palettes and index buffers); stage/object packs (621) carry the object graph and the `beTextureCtrlAttr` names but no texture buffers ([#467](../../../docs/findings/findings-0251-0500.md#f467)). The packing rule ([#472](../../../docs/findings/findings-0251-0500.md#f472)/#473/#476) is in `port/src/texpack.c` (`dw4asset texpack <file>\|--afs A --entry N [--list] [--decode NAME --out F]`): the pool is the pack's data blocks in ascending id order (`offset = pool_base + sum(smaller ids' sizes)`; a clut is 1024 B, an image `W*H` with its grid one byte into the block); `pool_base` and the pad total come from the header (`hdr[6] == sum + 4*(nclut+2)`, `hdr[7] == nclut+nimg+3`); the records are serialised igObjects (`_pImage` +52 is the grid id, `_pClut` +68 the palette reference, `_pNameString` +88 the name); the pack carries an id→class table, and `_pClut` resolves by its rank among the ids of its class to the r-th `igClut` record in file order, whose `_pData` is the palette block. All 26 textures of entry 625 decode pixel-for-pixel against the live dump; `make check` diffs C against `igb_texpack.py` on 6 packs / 117 textures (`port/tools/verify_texpack.py`); fixture `docs/engine/texture-pack-625-{layout,textures}.tsv` (`testing/texture-pack-groundtruth.tsv` is the reverse-engineering ground-truth table, not the fixture). At runtime `beTextureCtrlData._tex` → `igTextureAttr._image` → `igImage._pImage`/`_pClut` are ordinary pointers ([#448](../../../docs/findings/findings-0251-0500.md#f448)); `extras/dw4-tools/retail-live/live_textures.py --all` dumps 46 textures with their real names (palette 32-bit R,G,B,A, textures bottom-up, unswizzled). Names: `beTextureCtrlAttr._name` ([#466](../../../docs/findings/findings-0251-0500.md#f466)) in the object pack, `igImage._pNameString` in the texture pack. Open: the pad *positions* are scored by palette alignment (their total is exact from the header); the multi-asset packs (646/676/713/720) are refused rather than guessed. [Texture packs](../../../docs/engine/texture-packs.md) | done |
| **P3.5** | Models / animation | Geometry ([#455](../../../docs/findings/findings-0251-0500.md#f455)): a model's geometry is an `igGeometryAttr1_5` object (vtable `0x005238c0`, 0x38 B): `_vertexArray` +0x0c → `igVertexArray`, `_indexArray` +0x10 (NULL on 1,005 of 1,006), `_primType` +0x14, `_numPrims` +0x18, `_primLengths` +0x30 → `igPrimLengthArray1_1` (vtable `0x00526590`). There is no index array: `_primType` 4 = triangle strip (`sum(stripLengths) == numVerts`, `L-2` triangles each), `_primType` 3 = triangle list (`3*_numPrims == numVerts`). Normals are `igVertexArray._vdata[1]` of a `{positions, normals}` pair; the UV is an 8-byte `{u,v}` stream ([#457](../../../docs/findings/findings-0251-0500.md#f457)/#458). Offline ([#477](../../../docs/findings/findings-0251-0500.md#f477)–[#480](../../../docs/findings/findings-0251-0500.md#f480)): the chain resolves with no replay — `_vertexArray` (an `igObjectRef` id) → `igVertexArray1_1`, whose `_vdata` names a block listing the array's stream ids and whose `_numVerts` is the count; a stream block's `_memSize` is its content size exactly (`12*_numVerts` positions, `8*_numVerts` UVs); the pool lays every block out 4-byte aligned (`offset = pool_start + Σ align4(_memSize)`); field offsets come from `data/reflection.json`; a shape's name is the `igGeometry` record's ordinal-2 value and ordinal-8 is its `igAttrList`. All 549 of entry 621's attributes resolve, 450 are byte-identical to the live game's models, 444 are named (383 of the 386 live-named models get the identical name). Port reader: `dw4asset models` (`port/src/models.c`, `port/include/dw4/models.h`; `--list`/`--tsv`/`--out-dir`/`--obj`); `port/tools/verify_models.py` diffs it against `scripts/igb_models.py` over four packs (621/179/642 and the player's 861, 1,529 models) with byte-identical OBJ output; fixture `docs/engine/model-pack-621-attributes.tsv` + `scripts/verify_models_layout.py`. Loader ([#481](../../../docs/findings/findings-0251-0500.md#f481)): `port/src/scene.c` turns a pack into a guest arena plus 32-bit handles (`handle = arena offset`); `dw4asset scene --check` asserts every id placed in order, every payload byte-identical to the file's (50,497 ids, 0 differ) and every mesh handle resolving; `port/tools/verify_scene.py` and `testing/verify_models_offline.py` check each link. Id → pointer pass ([#482](../../../docs/findings/findings-0251-0500.md#f482)): reference fields are rewritten into handles and the kind comes from the value's own descriptor (type 0 an object id or NULL, type 7 a pool-block id or NULL; `scripts/verify_field_kinds.py` in `make rules`; `37,816 rewritten, 21,875 NULL, 0 NEITHER`). Live extraction: `scripts/name_live_models.py`, `scripts/extract_live_models.py`. Open: the *contents* of a memory block (a `_vdata` block holds the ids of the streams it lists; a block can be shared and the item kind is a property of the field that points at it). [Model format](../../../docs/engine/model-format.md), [testing tools](../../../testing/tools.md) | done — live and offline |
| **P3.6** | CRI audio / FMV | FMV: the 3 `.sfd` movies are CRI Sofdec = MPEG-1 video + ADX audio ([#447](../../../docs/findings/findings-0251-0500.md#f447)); `dw4asset media` runs them through ffmpeg. Sound: a stage's SE/BGM is CRI `ps2_` banks (`DTPK`/`TBLD`/`VAGD`) in its sound pack — six banks per stage, named by the pack's `beCriSfpData` records; the VAG ADPCM decodes offline and the sounds are named ([#450](../../../docs/findings/findings-0251-0500.md#f450), [#452](../../../docs/findings/findings-0251-0500.md#f452); all 33 stage sounds of `stag0102` verified against ffmpeg); `dw4asset sfp` lists them and writes WAVs; `port/tools/verify_sound.py` matches ffmpeg sample-for-sample (all 6 banks, 773,472 samples). Open: the field meanings [sound format](../../../docs/engine/sound-format.md) marks unknown | done (first cut) |

### P4 — The renderer

**Why.** The biggest single sub-project and the biggest risk. VU1 microcode + the GS path become a new
renderer consuming the same scene data. It is not helped by more decompilation.

| id | task | state | status |
| --- | --- | --- | --- |
| **P4.1** | Microcode map | `0x491910` parses to 237 entry points / 236 end markers over a 109,184-byte ucode image ([#489](../../../docs/findings/findings-0251-0500.md#f489)); the image is at `0x467178` ([#490](../../../docs/findings/findings-0251-0500.md#f490)). [VU1 microcode](../../../docs/engine/vu1-microcode.md) groups it by family: LIGHT 91 programs / ~89,984 B (82 % of the pipeline), TRANS 34/19,392, CLIP 25/8,896, COMPRESS 11/8,112, MULTIPASS 19/7,184, PARTICLE 4/4,336, BLEND 8/3,632, VIEWPORT 8 + CALC 10, FOG 3, TEXGEN 4, EXECUTE 10, DECOMPRESSION 2, CULL 4, XGKICK 1; 35 start offsets carry more than one name. The engine selects programs by name (`0x20d790` parses the string once, token base `0x57c2b0`). A second VU table at `0x48dd60` (201 `NAME;flags;;code;;;;` records) gives each program attribute words; 25 of its 29 flag bits are proven by set equality ([#494](../../../docs/findings/findings-0251-0500.md#f494)), so (family, flags) is an engine-authored spec of each of the 201 programs. The EE-side seam is mapped ([#491](../../../docs/findings/findings-0251-0500.md#f491), [p2 renderer](../../../docs/engine/p2-renderer.md)): `p2` (`0x1f0000`-`0x20d000`, 169 functions, 6 touching a register) and the VU1 upload path (`FUN_00169e30`, `FUN_00203c50`, `FUN_00203580`, `FUN_001f0960`). Next: the pipeline semantics | done |
| **P4.1 (VU1 effects)** | Implement the VU1 families as GPU effects (the microcode map is the spec) | FOG: the three `FOG_LINEAR`/`FOG_EXP`/`FOG_EXP2` programs are implemented on both backends as a depth blend ([#516](../../../docs/findings/findings-0501-0750.md#f516)). BLEND: the runtime per-vertex stream is `igVertexArray1_1._blendWeights` (+0x20, f32/vertex) and `_blendIndices` (+0x24, u8/vertex), and the bone map is `igBlendMatrixSelect._blendMatrixIndices` (+0x28, an `igIntList` of 33 entries over 24 matrix slots) ([#532](../../../docs/findings/findings-0501-0750.md#f532)); `port/src/skin.c` and `scripts/live_skin.py` skin as `v' = M[slot[bone]] * v` with the palette matrix row-major and its translation in elements 12..14, byte-identical over every 24-matrix palette (`port/tools/verify_skin.py`, [#540](../../../docs/findings/findings-0501-0750.md#f540)). For a free mesh no field links it to its `igBlendMatricesAttr._matrixCache` (+0xc), so that palette is picked by index; an `igActor` owns `_boneMatrixCacheArray` (+0x24) and `_blendMatrixCacheArray` (+0x28) ([#535](../../../docs/findings/findings-0501-0750.md#f535)). The player's pose is solved offline from a GS dump: [pose results](#p41-the-player-pose-results). Open: CLIP (25 — GL already clips the near plane; the projected-MVP path), TEXGEN (4 — procedural UVs), MULTIPASS (19), COMPRESS (11, GS-packet compression, likely moot once the GS is gone) | in-progress |
| **P4.2** | Scene-data capture | The camera/scene-animation chains are in the pack ([#483](../../../docs/findings/findings-0251-0500.md#f483)): `igSceneInfo` → `igGraphPathList` → `igGraphPath` → `igNodeList` → node chains with names, `igMatrix44f` transforms, children and geometry references (18 scenes / 99 nodes on entry 621; `dw4asset scene --graph`); front-end packs root their `_sceneGraph` at an `igAttrSet` and animated `igTransform` nodes keep their transform in an `igTransformSequence1_5` evaluated at `dw4_scene_set_time(ns)` ([#611](../../../docs/findings/findings-0501-0750.md#f611)). Object placement is not in the pack (`beModelCtrlNode2`'s attr list is empty in all 1,075): `scripts/capture_scene.py` reads `igGeometry` objects and their `_parentList` chains out of a saved EE RAM dump and emits each node's world matrix ([#487](../../../docs/findings/findings-0251-0500.md#f487)); `--pack <AFS:ENTRY>` content-matches each live attr to the pack mesh with the same vertex buffer and writes the pack `igGeometryAttr` id, on which `dw4` and `dw4asset render` join ([#519](../../../docs/findings/findings-0501-0750.md#f519)); `scripts/camera_match.py` writes the whole scene TSV ([#521](../../../docs/findings/findings-0501-0750.md#f521)): [scene capture results](#p42-scene-capture-and-materials-results) | done (first increment) |
| **P4.2/P4.3** | Stage camera | `dw4asset scene --cam` composes a camera node's ancestor chain (child × parent) and inverts it ([#495](../../../docs/findings/findings-0251-0500.md#f495)/#496); `stage0102` node 4 `cameraShape00` composes to (0, 102.490, 74.565), pitched ~35° down; projection 39.60° vertical FOV, `0.7·w/h` aspect (448/640). `dw4asset render --camera [NAME]` and `dw4 --camera [NAME]` derive the view from the pack; the host places one instance per live capture row (195,868 verts / 130,194 triangles) ([#510](../../../docs/findings/findings-0501-0750.md#f510)/#511); `port/tools/verify_render.py` pins the composed position and a deterministic framed render | done |
| **P4.3** | A first renderer | Software: `dw4asset render` ([#484](../../../docs/findings/findings-0251-0500.md#f484)) — perspective projection, z-buffered barycentric scan with perspective-correct depth ([#548](../../../docs/findings/findings-0501-0750.md#f548)), near-plane clipping to `z >= 0.05` ([#545](../../../docs/findings/findings-0501-0750.md#f545)), `--name`/`--attr`, `--limit`/`--cols`, `--wire`, `--texture <name> --texentry <n>` ([#485](../../../docs/findings/findings-0251-0500.md#f485)), `--scene` ([#487](../../../docs/findings/findings-0251-0500.md#f487)). GPU: `dw4 --gl` on EGL + GLES 3 into an offscreen FBO (`port/src/gl_render.c`) with a UV attribute and sampler, the FOG family, the shared light rig (`--ambient`/`--light`/`--lights`, one `dw4_light`/`dw4_fog` for both backends) and a bbox-fit fallback (`dw4_render_fit_view`); `dw4asset render --scene … --gl` and `--name … --gl` ([#515](../../../docs/findings/findings-0501-0750.md#f515)/#516). GPU and software scene frames are geometrically identical (silhouette IoU 1.000); `port/tools/verify_render.py` and `port/tools/verify_host.py` pin coverage and determinism. `igGeometryAttr1_5` has no material reference (ordinals 5/9/11/12 are NULL in all 549): the mesh→texture binding is a load-time assignment. Remaining: the per-family VU1 work (TRANS/CLIP/TEXGEN/MULTIPASS/COMPRESS). The game's own lobby, title and STATUS rendering is described in [lobby rendering](../lobby-rendering.md) and [GPU rendering](../gpu-rendering.md) | done (first increment) |
| **P4.3 (materials)** | Node-held materials and the live texture source | `port/src/livetex.c` (runtime `igPsx2Image._pImage` +0x34 / `_pClut` +0x44 are pointers): `dw4asset livetex <ram> [--list\|--decode NAME --out F]` and `render --scene … --livedump RAM`; `scripts/texture_map.py` reads a material off the shape's parent node (`igAttrSet._attributes` +0x20), 136 attrs / 52 pack ids ([#533](../../../docs/findings/findings-0501-0750.md#f533)/#534). The player in the Goblin Pass capture is Susanoomon, not `ogre_skinShape` (an Ogremon NPC; [#531](../../../docs/findings/findings-0501-0750.md#f531) refuted by [#535](../../../docs/findings/findings-0501-0750.md#f535)) | done |
| **P4.4** | **The game's shading** | `p2lighting` (`0x1fb710`) is decoded end to end ([lighting](../../../docs/engine/p2-lighting.md), [#498](../../../docs/findings/findings-0251-0500.md#f498), [#499](../../../docs/findings/findings-0251-0500.md#f499), [#554](../../../docs/findings/findings-0501-0750.md#f554)) and the per-vertex model, rig, fog and texture state are recovered from GS dumps: [P4.4 results](#p44-the-games-shading-results). Open items are listed there | in-progress |

#### P4.1 the player pose (results)

Findings [#594](../../../docs/findings/findings-0501-0750.md#f594)–[#599](../../../docs/findings/findings-0501-0750.md#f599), solved offline from a same-instant combat GS dump.

- The per-vertex bone indices are in the pack (blocks 5483/5595/5566 in pack 861, one u8 per vertex);
  the neighbouring 4-byte-per-vertex blocks are constant 1.0f, so the pack holds no weight data.
- The palette the GPU skinned with is a 24-matrix per-bone array staged in the VU/DMA packet area (four
  byte-identical copies 0x1b743dc0/0x1b53f40/0x1b64040/0x1b741c0), indexed directly by the bone byte;
  the `igBlendMatrixSelect` list is not consulted for the player. Shape1 fits the native GS draw at
  median 0.0057 model units, 100 % within 0.05, single-bone; the combiner palette 0x16df680 (21 slots,
  slot-mapped) fits about 7× worse.
- Shape0 is not drawn in that frame (0/354 UVs in the draw union): the visible draw is Skin0Shape1+2,
  so the character TSV row carries ids `5485,5882`.
- Port: `--pose-select 0` (identity map) `--pose-palette 0x1b753b0 --pose-count 24` lands the character
  metric box at 22.8–23.9, pinned by `port/tools/verify_pose.py` (skips without the dump/artifacts).
- The player is `P_susanoo_Skin0Shape0/1/2` in `NDMW.AFS:861` (`common/p_susanoo.igb`; `m_`/`q_`/
  `s_susanoo.igb` = 845/877/893), reached through node 0x016de170 -> `igLod` -> three `igActor` LODs ->
  `igAppearance._skin` -> `igSkin._skinnedGraph` (`igBlendMatrixSelect` 0x01667468); the port resolves
  it from a second pack (`camera_match --character-pack`, `dw4asset render --pack2`) ([#535](../../../docs/findings/findings-0501-0750.md#f535), [#555](../../../docs/findings/findings-0501-0750.md#f555)).
- Dead ends: `../scratch/pose-solve/gs_char_model.npy` is a wrong model-space conversion (recompute
  from `gs_char_world_union.npy`); shape0's UV stream is all zeros and shape0 is absent, so neither UV
  pairing nor a palette search works for it ([#599](../../../docs/findings/findings-0501-0750.md#f599)). The "posed copies" at 0xdadfbc/0xdb53fc/0xde760c
  are the pack's bind stream chunked into DMA/VU1 scratch, not a posed buffer; the `_pBlendedVertsList`
  route is closed (of all 882 live `igPsx2VertexArray1_1` only the Ogremon's carries a blended list)
  ([#594](../../../docs/findings/findings-0501-0750.md#f594)).
- Open: the character box residual (about 22–23) is the reference framebuffer's striping/overlay plus
  the port's character shading (the game's vertex colours come from the posed normals); shape2's blend
  bones (9/10/11) are unresolved but sub-pixel at this camera.

#### P4.2 scene capture and materials (results)

The Goblin Pass crate/barrel capture, findings [#519](../../../docs/findings/findings-0501-0750.md#f519)–[#525](../../../docs/findings/findings-0501-0750.md#f525), [#545](../../../docs/findings/findings-0501-0750.md#f545)–[#556](../../../docs/findings/findings-0501-0750.md#f556).

- The capture is live stage `stag0101`, model pack `NDMW.AFS:614` (`stag0101.igb` resolves to `[0.613]`
  387,440 B with 0 geometry attrs + `[0.614]` 4,793,568 B with 566); all 605 live geometry attrs
  content-match pack 614 (388 resolve by vertex buffer; the 217 misses are `font*`). Pack names repeat
  (475 named meshes over 290 distinct names) and the largest meshes are unnamed, so the join is by pack
  id, not name ([#519](../../../docs/findings/findings-0501-0750.md#f519)).
- The ground-truth TSV regenerates byte-identically from `goblin_pass_crate_barrell.p2s` via
  `scripts/livedump.py` (a `.p2s` → 31 MB RAM image at base `0x00100000`; feeding `p2s_ram.py`'s 32 MB
  output shifts every address by `0x100000` and every graph comes back empty) + `camera_match.py --from
  --pack NDMW.AFS:614`.
- Camera: the 4x4 at EE `0x6eb0d0` is the eye world matrix (translation `(365.078,117.886,-77.307)`);
  its inverse maps `_avgPos (421.83,72,-110.07)` to `(0.003,-0.101,-80)`; fov `0.6912` rad, aspect
  `0.7*w/h = 1.0` at 640x448.
- The environment is authored in stage coordinates: 117 of the 832 live `igGeometry` shapes have no
  usable matrix and identity is their placement (`capture_scene.py --keep-unplaced`) ([#520](../../../docs/findings/findings-0501-0750.md#f520)). The world
  set is large AND 3D AND unplaced AND textured (`camera_match --min-z DZ`, default 1.0; `--keep-placed`,
  `--include-untextured`, `--drop-id`); attr 38907 (246 verts, no texcoords) is in the pack and undrawn
  for an unknown reason, so [#550](../../../docs/findings/findings-0501-0750.md#f550) stays unconfirmed ([#545](../../../docs/findings/findings-0501-0750.md#f545), [#549](../../../docs/findings/findings-0501-0750.md#f549), [#550](../../../docs/findings/findings-0501-0750.md#f550)).
- Props: `M_BK17v1_barrelsShape` at `0x014df9d0` (barrel) and `M_BK19a0_boxShape` at `0x0130a858`
  (crate), named by the `beModelCtrlNode2`'s own child `igNodeList` at `+0x1c`; their materials are
  inline `igAttrSet` atlases in the stage pack (`g_bbarrelsz01`, `g_woodencasez01`: a 32x32 8-bit image
  plus a 256-entry `igClut`, palette order R G B A), decoded by `scripts/pack_inline_tex.py`
  ([inline textures](../../../docs/engine/inline-textures.md), [#549](../../../docs/findings/findings-0501-0750.md#f549), [#552](../../../docs/findings/findings-0501-0750.md#f552), [#553](../../../docs/findings/findings-0501-0750.md#f553)). The crate's mid-height
  metal band and corner posts are the game's own look ([#557](../../../docs/findings/findings-0501-0750.md#f557)/#558; [#556](../../../docs/findings/findings-0501-0750.md#f556) refuted).
- Wall and floor: the wall is the BG ground set's `n` variant `P11G00n` (`NDMW.AFS:618/619`, a 256x128
  atlas carrying the rock and the blue light-dash band) and the floor its `s` variant `P11G00s`; the
  floor/wall split is floor iff `n[1] > 0.5` and `|n[0]| + |n[2]| < 0.15` (floor 31788, wall/dome shell
  21835; `--ground-tex`/`--wall-tex`) ([#551](../../../docs/findings/findings-0501-0750.md#f551), refuting [#547](../../../docs/findings/findings-0501-0750.md#f547)). The wall shell has no recoverable per-mesh
  binding (it is RamData/packet-drawn, [#543](../../../docs/findings/findings-0501-0750.md#f543)). The GS world draw's TEX0 (`0x40060805e1312fc0`, TBP
  `0x2fc000`, 256x128 PSMT8, CBP `0x304000`) decodes out of VRAM to an index map byte-identical to
  `P11G00n` flipped vertically (32768/32768) and its STQ matches the pack UVs of the `P11G00n` meshes,
  which resolves [#566](../../../docs/findings/findings-0501-0750.md#f566) in favour of `P11G00n` ([#569](../../../docs/findings/findings-0501-0750.md#f569)–[#571](../../../docs/findings/findings-0501-0750.md#f571)).
- Material binding: the source binding is the material attr set — `beTextureCtrlAttr._attrSet` (+0xc) ->
  `igAttrSet`, whose `+0x1c` child list holds the shapes and whose `+0x20 _attributes` list holds
  `igTextureBindAttr._texture` -> `igTextureAttr._image` (+0x30) -> `igPsx2Image._pNameString` (+0x58)
  ([#525](../../../docs/findings/findings-0501-0750.md#f525)); the world material records list their shapes, so a shape's texture maps to a pack attribute
  by `(primType, numPrims)` ([#565](../../../docs/findings/findings-0501-0750.md#f565), [#572](../../../docs/findings/findings-0501-0750.md#f572)). The world materials are built at load time and are not in the
  pack (`beTextureCtrlInfo` → `beTextureCtrlAttr._attrSet`; 90 sets in the Goblin Pass dump, read by
  `scripts/live_materials.py`; [#563](../../../docs/findings/findings-0501-0750.md#f563)). `FUN_00169840` (`igPsx2VisualContext`, vtable `0x525870`) and
  `FUN_00140060` (`igSetRenderDestinationAttr`, vtable `0x522f50`) with `_pBufList` (+0x364) and
  `_pTexList` (+0x144) are render-to-texture/destination setup, not the world-mesh source binding
  ([#524](../../../docs/findings/findings-0501-0750.md#f524) corrects [#523](../../../docs/findings/findings-0501-0750.md#f523)). The GS command stream is not in EE RAM, so per-draw state comes from a PCSX2
  `.gs` dump parsed by `scripts/gsdump.py`, which reads the dump's freeze state and walks the packed
  register cycle ([#567](../../../docs/findings/findings-0501-0750.md#f567), [#568](../../../docs/findings/findings-0501-0750.md#f568)). The frame's `NREG=3` packets are the `STQRGBAXYZF2` type (STQ + RGBA +
  XYZF2), so the per-vertex colour is real ([#569](../../../docs/findings/findings-0501-0750.md#f569)–[#571](../../../docs/findings/findings-0501-0750.md#f571) refute [#568](../../../docs/findings/findings-0501-0750.md#f568)'s "no colour register").
- Captures: `../local/captures/dw4-port/live-camera/`.

#### P4.4 the game's shading (results)

Owning documents: [lighting](../../../docs/engine/p2-lighting.md),
[vertex shading](../../../docs/engine/vertex-shading.md),
[inline textures](../../../docs/engine/inline-textures.md), [port README](../../README.md).

- **Per-vertex model.** `rgb8 = floor(255 · 0.5 · clamp(ambient + diffuse·max(0,N·L), 0, 1))`, one-sided,
  with the live rig. It fits the barrel to 0.139/255 over 84 distinct normals (two-sided 27.0, no 0.5
  60.4; [#577](../../../docs/findings/findings-0501-0750.md#f577)), the world to within 1/255 on all 332 paired vertices of 368 (mean 0.189, pairing at
  median 0.062 px / max 0.0995 px; two-sided 16.33/255, scale 1.0 72.1/255; [#583](../../../docs/findings/findings-0501-0750.md#f583)) and the crate's 415
  vertices to 0.051/255 ([#589](../../../docs/findings/findings-0501-0750.md#f589)). The 0.5 is the GS modulate convention `(Cv·Ct)>>7`, not a capture dim
  ([#579](../../../docs/findings/findings-0501-0750.md#f579)/#580; [#578](../../../docs/findings/findings-0501-0750.md#f578) refuted). Tools `scripts/gs_barrel_shading.py`, `scripts/gs_world_shading.py`.
- **Rigs.** The light values are runtime-only (`0x56AF40` is NULL and `0x56AF94` is 0 in all 17 saved
  states; the pack has no `Light` class). The live rig is ambient (0.25,0.20,0.35) plus one directional
  (1.20,1.15,1.20) along (0.3214,-0.866,0.383), readable only mid-render
  (`extras/dw4-tools/retail-live/live_rig.py`); the packs' `igLightAttr` are prototypes with the same
  directions and different colours. The baked scene default is the fitted rig — ambient
  `0.3005,0.2444,0.2986` + one directional `0.7931,0.7938,1.3141` along `(0.3482,-0.9370,0.0272)`
  (`port/tools/fit_light_rig.py`, [#574](../../../docs/findings/findings-0501-0750.md#f574)) — which is better or tied nearly everywhere ([#592](../../../docs/findings/findings-0501-0750.md#f592) refutes
  [#591](../../../docs/findings/findings-0501-0750.md#f591)'s recommendation of the live rig). All lit draws (world, terrain, floor, barrel, crate) share one
  rig ([#580](../../../docs/findings/findings-0501-0750.md#f580); [#564](../../../docs/findings/findings-0501-0750.md#f564) refuted).
- **Interpolation.** The scene default is the game's per-vertex path: light each vertex and interpolate
  the colour affinely in screen space (the GS has no Q on the colour); `--per-pixel` reverts ([#592](../../../docs/findings/findings-0501-0750.md#f592)). The
  scene path interpolates the pack's unit-length normal stream; `--flat` is the faceted baseline
  ([#559](../../../docs/findings/findings-0501-0750.md#f559)/#560).
- **Per-draw state** (`scripts/gs_draw_state.py`, 25 state groups): `TEX1 MMAG 1 MMIN 1` (linear, read
  from the freeze state because the record stream never rewrites `TEX1`); opaque lit draws are `PRIM
  TME 1 ABE 0 IIP 1`, `ALPHA A0 B1 C0 D1`, `TEST ATE 1 ATST 6 AREF 0xc ZTE 1 ZTST 2`; unlit overlays
  carry a constant RGBA (127/0) with `ABE 1`. The port samples linearly by default (`--nearest`
  reverts): of the 323 `igTextureAttr` records behind packs 614/621's material sets, 300 carry
  `_magFilter = _minFilter = 1` with `_mipmapMode = 0` ([#562](../../../docs/findings/findings-0501-0750.md#f562)).
- **Texel path.** The GS texel map (the GS's own VRAM texture sampled through its own STQ) reproduces
  the port's `--unlit` world-rows render at region ratio `1.000/1.000/0.999`, mean `|Δ| 1.07` over the
  whole frame, so the world's texel/UV/filter path is closed, wall included ([#585](../../../docs/findings/findings-0501-0750.md#f585); tool
  `scripts/gs_shade_raster.py`).
- **Fog.** The per-draw excess over `texel × Cv` ([#590](../../../docs/findings/findings-0501-0750.md#f590)) is the GS FOG stage ([#603](../../../docs/findings/findings-0501-0750.md#f603)): `F = (dword44>>4)&0xff` of
  the packed `XYZF2` vertex and `fb = pred*(F/255) + FOGCOL*(1-F/255)`. `F` is linear in view-space
  depth: `FOG_LINEAR`, near 60 / far 300 (free fit 59.54 / 299.45 at MAE 0.254/255), toward `FOGCOL
  0xE5CCE5 = (229,204,229)` (#604). The engine keeps the fields on `igPsx2VisualContext` (`_fogEnable`
  +0x514, `_fogDensity` +0x518, `_fogMode` +0x51c, `_fogColor` +0x520, `_fogNear` +0x530, `_fogFar`
  +0x534). Port: `dw4_render_game_fog()` in `render.c`, `F` per vertex from view-space `z`, interpolated
  affinely, applied by default on the scene path (`--fog` overrides, `--no-fog` drops); the blend is
  gated on `mode != OFF` so `--no-fog` is byte-identical to the pre-fog frame; `port/tools/verify_fog.py`
  pins the metric.
- **Frame metric.** The reference `real-goblin-pass.png` is 640×480 (the 448-line framebuffer scaled by
  480/448); `port/tools/frame_metric.py` rescales it ([#573](../../../docs/findings/findings-0501-0750.md#f573)). With fog at `--blur 1.2`: whole 10.96,
  floor 9.19, wall 11.80, barrel 8.28, crate 14.36, character 21.89 (from 14.70 / 9.36 / 13.83 / 12.17 /
  16.71 / 23.13 without fog). The wall metric box (120,60)-(250,110) is 6389/6500 wall-atlas pixels
  ([#600](../../../docs/findings/findings-0501-0750.md#f600)).
- **Guards in `port/tools/verify_render.py`:** `scene normals`; the default equals `--gouraud` and
  differs from `--per-pixel`; the modulate identity (`--unlit --texture` × `--gouraud` / 255 equals
  `--gouraud --texture` on every drawn pixel); `near-plane`; the default applies fog.
- **Traps.** `dw4asset.c` negates the view's third row before `dw4_render_set_view`, so an external
  projection must negate indices 8..11 of the VIEW string. A PSMCT32 page's 8x8 blocks are interleaved
  by the page-block table, not row-major ([#588](../../../docs/findings/findings-0501-0750.md#f588)). The cross-product barycentric `w0 = cross(b−a,
  P−a)/det` is the third vertex's weight ([#586](../../../docs/findings/findings-0501-0750.md#f586)/#587). Inline pack textures are stored top-down and are
  flipped on load (`rgba_flip_rows`, [#579](../../../docs/findings/findings-0501-0750.md#f579)/#580; this resolved the props' pale metal trim, [#576](../../../docs/findings/findings-0501-0750.md#f576)).
- **Dead ends (do not retry).** A global response curve ([#601](../../../docs/findings/findings-0501-0750.md#f601)/#602; the excess is fog). A crate shading
  fix ([#589](../../../docs/findings/findings-0501-0750.md#f589): its shade, UVs and texels are each the game's). One-sided `N·L` on the per-pixel path
  (no-op), a white per-mesh tint (worse), specular (negligible), the stage pack's own rig (not closer)
  ([#559](../../../docs/findings/findings-0501-0750.md#f559)/#560). Affine vs perspective colour interpolation (byte-identical); `--flat` (wall mean
  unchanged); a `P10G00n` wall swap (fixes the hue, not the metric). Back-face culling (`--cull`/
  `--cull-front`/`--no-cull`: measured no-op). The texture matrix: it is a UV offset (54 live
  `igTextureMatrixAttr`, all identity + translation in elements 12..13) and `BGGround00n` carries none
  ([#567](../../../docs/findings/findings-0501-0750.md#f567)). A floor crease exclusion ([#584](../../../docs/findings/findings-0501-0750.md#f584) refuted by [#586](../../../docs/findings/findings-0501-0750.md#f586)/#587).
- **Open.** The character box (see the pose results). Two region-mean outliers after fog: the
  overlay-covered floor box reads below the prediction, and the bright character group at TBP
  `0x37c000` is over-predicted ([#603](../../../docs/findings/findings-0501-0750.md#f603)). The `TEST` alpha cutout and the unlit overlay draws are not
  implemented in the scene renderer.

### P5 — Lua

**Why.** 5,291 chunks — missions, quests, UI. All decompiled.

| id | task | state | status |
| --- | --- | --- | --- |
| **P5.1** | Embed Lua 4.0.1 and integrate native services | See [Lua integration](#lua-integration) and [actor sequences](../actor-sequences.md) | in-progress |

### P6 — Port scaffolding

| id | task | state | status |
| --- | --- | --- | --- |
| **P6.1** | A host build | The port builds the native executable `dw4` (`port/src/main.c` + `port/src/engine.c`, via the port's Makefile). The boot's manager phase is the engine's: `FUN_002595e0` calls three `_Create` factories (`igEnbayaContextPool_Create` `0x1a1ae0`, `igAnimationCombinerBoneInfoPool_Create` `0x1a7cc0`, `igAnimationStatePool_Create` `0x1a67c0`; names in `config/SLUS-20836/names/Managers.tsv`), which the port constructs as reflection-typed instances ([#502](../../../docs/findings/findings-0501-0750.md#f502)–[#504](../../../docs/findings/findings-0501-0750.md#f504)). The frame context is the engine's one-shot acquire/run/release ([#512](../../../docs/findings/findings-0501-0750.md#f512), correcting [#506](../../../docs/findings/findings-0501-0750.md#f506)): `FUN_0025a580` increments `+0xe8` to 1, writes the per-frame fields (`+0x94`/`+0x98`/`+0x9c` = 0.1, `+0xa0` = 1.0, `+0x5e`/`+0xa8` = 1, `+5`/`+0x5c`/`+0xb4`/`+0xd5` = 0), decrements it and at ≤0 releases the `+0xec`/`+0` refs and frees the object, gated on the app's `+0x18`; `port/tools/verify_host.py` pins it. The reference-release idiom compiles only from `if (&obj->field) { release(obj->field); }` with a real struct at the recovered offsets ([#509](../../../docs/findings/findings-0501-0750.md#f509)); these teardown paths are what a port's `igObject` reference release maps onto. Decomp status of the boot functions (`0x234900`/`0x234d70`, `0x25a580`/`0x25a8c0`, `FUN_002595e0`): [engine boot](../../../docs/engine/engine-boot.md), [#505](../../../docs/findings/findings-0501-0750.md#f505). Not yet: the decompiled `src/` compiled as portable C — that needs P1's types; the host reimplements the object model over `reflection.json` and the game logic follows the [arena object model](../arena-object-model.md) | in-progress |
| **P6.2** | Verification harness | Differential testing: run the decompiled function/engine and compare against emulator state | todo |

### Order of the workstreams

1. **P1.2** (signature recovery) — the measured multiplier for P1, and P1 gates everything.
2. **P2.1/P2.4** started in parallel — bounded, and stops P2 from being discovered late.
3. **P3.2/P3.3** (loader) and **P4.1** (microcode map) in parallel — the risk is the graphics/asset
   path and no decompilation removes it.

### What does not move goal B

- More byte-matched percentage per se (bank verified behaviour, but it is not the finish line).
- Decompiling the SDK/IOP (`MODULES/`) — those are replaced.
- The console-modding work (per-unit pinning, isolated disc patch, heap-move) — goal A only.

## Private evidence outside Git

| topic | location (repository-relative) | files |
| --- | --- | --- |
| Stage portal, commander instances, walking edges | `../scratch/lobby-portals-edges/` | `terminal-native-retail.log`, `hardware-final.log`, `portal-edge-native7.log`, `loop-retail.log`, `floor-retail.log`, `retail-stairs.json`/`.log`, `asan-*.log`, `matching.log` |
| Lobby jump, gates, heal | `../scratch/lobby-parity/` | `terminal-native-retail.log`, `hardware-capture.log`, `moving-jump.log`, `health-near2.log`, `records-closure.log`, `loading-audio.log`, `asan-*.log`, `link.log`, `captures/` |
| Background focus | `../scratch/background-focus/` | `focused-final.log`, `hardware.log`, `before-regression.log`, `live-status.log`, `contracts.log`, `application-build.log`, `matching.log` |
| Camera region smoothing | `../scratch/camera-runtime/` | `native-retail.log`, `live-boot-gpu.log`, `live-camera-final.log`, `final-focused.log`, `asan.log`, `matching.log` |
| Lobby movement and startup | `../scratch/lobby-runtime/` | `terminal-native-retail.log`, `normal-boot-final.log`, `normal-live.log`, `hardware-final.log`, `startup-failure.log`, `asan-*.log`, `matching.log` |
| HUD/dialogue and main-menu fidelity | `../scratch/main-menu-fidelity/` | `hud-dialogue-*.log`, `terminal-native-retail.log`, `closure-hardware.log`, `closure-matching.log`, `host-gpu-upper-comparisons.json`, `title-final-comparisons.json`, `host-gpu-control-comparisons.json` |
| GPU-only rendering | `../scratch/` | `gpu-entry-acceptance.log`, `gpu-strict-live.log`, `gpu-final-native-retail.log`, `gpu-final-matching.log` |
| STATUS acceptance | `../local/captures/dw4-port/status-validation-20261013/` | `wnprojection-validation/`, `native-live-frames/`, `live-frame-validation/`, `live-phase/`, `background-phase-diagnostic/` |
| STATUS retail references | `../local/captures/dw4-port/status-validation-20261012/`, `../scratch/status-validation-20261012/` | `trivial-root-comparison.json`, `native-trivial-root/`, `native-menus/`, `weapon-coded-comparison.json`, `native-coded-menus/`, `root-comparison-visible.json`, `retail-root-action-clocks.json`, `PCSX2/sstates/` |
| STATUS checkpoints | `../scratch/` | `status-resume-*.log`, `status-disk-outer-*.log`, `status-detail-outer-*.log`, `status-currency-outer-*.log`, `status-positioned-retail.log`, `status-currency-wrapper-retail.txt`, `status-visibility-*.log`, `status-root-identity-*.log`, `status-projection-*.log`, `status-string-to-unicode.txt`, `status-text-encoding.txt` |
| Retail parity audit | `../scratch/parity-audit/`, `../extras/handoffs/` | report and evidence |
| Earlier handoffs | `../extras/handoffs/` | `status-integration-pre-audit-20261013.txt`, `todo-temp-20261011.txt` |
| Front-end captures | `../local/captures/dw4-port/` | `boot/`, `frontlayer-native/`, `presentation/` |
| Fog, fragment and pose analysis | `../scratch/frag590/`, `../scratch/pose-solve/` | `fog_params.py`, `fog_params_result.txt`, `fog_verify.py`, `fog_verify_result.txt`, `analyze_curve.py`, `curve_fit_result.txt`, `crate_cv.npz`, `full_scene.npz`, `crate_implied_cv.png`, `gs_char_world_union.npy` |
