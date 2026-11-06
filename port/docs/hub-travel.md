# Connected hub travel

The normal application travels between the Terminal (`stagML11`), Central
(`stagML12`), the Shop (`stagML13`) and the Commander Room (`stagML02`) through
the original exit scripts, loading each destination behind its original stage
card. Run port acceptance headlessly.

The hub services run through the same prepared runtime:

- From Central: NPC interaction ([NPC interactions](npc-interactions.md)), the
  XDATA stat and chip services ([XDATA shop](xdata-shop.md)), the NPC bank
  ([NPC bank](bank-shop.md)), the NPC appraiser ([NPC appraiser](cnos-shop.md)),
  the Digi-Lab ([Digi-Lab](labo-shop.md)) and the Prmame's folder services
  ([Prmame](prmame-npc.md)).
- From the Shop: the Digi-Disk shop ([Digi-Disk shop](disk-shop.md)) and the
  weapon, armor, chip and junk shops ([equipment shops](equipment-shops.md)).
- All of these but the Digi-Lab run under the native generic shop root that
  draws the retail chrome ([shop root](shop-root.md)).
- Hosted scenes: the Save Keeper's `stagIS12` save screen runs as a hosted scene
  mode of the runtime over the native `SaveCtrl`/`SaveIntf` and returns to
  Central through an ordinary pending travel request
  ([Save Keeper](save-keeper.md)); the Terminal's `stagIS13` load/join screen
  ([load scene](load-scene.md)) returns to `stagML11` at position 4; the card
  album `stagIS11` ([card album](card-album.md)) returns to `stagML12` at
  position 4. All three arrivals were compared with retail runs (the Terminal
  arrival matches exactly at (250, 40, 70)).
- The PS2 save-file codec is done ([save image](save-image.md)).

These do not imply that the connected demo is complete; what is missing is under
[Open items](#open-items).

## Original exit requests and arrival groups

The Lua 4 runtime executes the original pack-local `func.lua` and material
callbacks, not the prose decompilation's empty helper definitions. Real prepared
MODELCTRL, SELECTCTRL and TEXTCTL owners drive the confirmation, No and Circle
branches. The point is the **second** `funcStageChange` argument; the fourth
argument is a different travel parameter and must not select arrival placement.

| From | Original event | Destination | Arrival group |
| --- | --- | --- | ---: |
| Terminal (`stagML11`, NDMW 820) | `matz00.lua` | `StagML12` | 0 |
| Terminal | `matz01.lua` | `StagML13` | 0 |
| Central (`stagML12`, NDMW 824) | `matz00.lua` | `StagML11` | 1 |
| Central | `matz01.lua` | `StagML13` | 1 |
| Shop (`stagML13`, NDMW 828) | `matz00.lua` | `StagML11` | 2 |
| Shop | `matz01.lua` | `StagML12` | 1 |
| Terminal | `mate01.lua` (Commander Room gate, flag 424 clear) | `stagML02` | 0 |
| Commander Room (`stagML02`, NDMW 816) | `mate00.lua` | `stagML11` | 0 |

The Commander Room's own contract (welcome, events, label, audio, validation) is
in [Commander Room](commander-room.md).

Retail exit triggers fire on box membership alone, with no walk-in: placing the
player at (20,40,-40) in Central, inside the `matz00` box (x 10..30, z -50..-30),
opens the Terminal Area prompt, and confirming loads `stagML11` with the player at
(0,10,-40). The prompt waits for an answer.

Keep original name casing in the request. Asset resolution supplies its existing
case-insensitive stage lookup. The callbacks reject incomplete material player
membership and busy DM execution. The helper checks the triggering player's HP,
opens the authored travel window and selector, then queues its original fade and
same-delay PLAYERPOINT / STAGECTL requests on confirmation. Cancellation restores
MODELCTRL control and PADINPUT through the script; it does not issue a direct
PLAYER ONCTRL. Restoration after No and Circle, including the externally
registered player MODELCTRL peer, is exercised in the integrated scene by
`check-hubruntime` and `check-hubgates`.

The stage-change confirmation window (`i_zzstchgwb`/`i_zzstchgwn`, layer WN03)
shows its area name: the header text (`STCHGFONT00`, e.g. "Central Area") is
drawn by `dw4_dialogue_text_split` in the pass after WN02 and above, as the
original FONT layer follows the window layers. Drawing all text below the WN02
split puts the header under the window. Retail and port frames at the Terminal's
west bridge match.

## Gate pads and second exits

With a travel owner (`dw4_lobby_exit_events`), the lobby's material dispatch
(`port/src/lobby.c`, `control_tick`) runs every `mate*` travel region besides the
`matz00`/`matz01` bridges, on changed membership, through the original pad
scripts (Terminal pack NDMW 820, Central 824, Shop 828). The heal pad `mate03`
and the label regions (`matf*`, and `matg*` for the Commander Room's `matg00`)
also run without a travel owner. The scripts apply their own story-flag and
`MATisAllPlayer` guards; the port adds no flag logic. Each Terminal pad lies
inside its label region and its script clears the label first
(`POINTFONT00/font00..04/CLR`, `i_stpnl06` and `i_pointcur` `SQ_CLOSE` on every
instance), so the label is down while the prompt is open. After No or Circle the
player still stands in the label region, so the label stays closed until the
region is left and entered again; stepping back onto the pad opens the prompt
again.

| Pad | Script (`lua/01-lobby-hub/…`) | Open when | Prompt | Accept requests |
| --- | --- | --- | --- | --- |
| Terminal `mate01`, Gate to Commander Room | `05-lobby-quests_e820/030-exit-to-stagml02.lua` | flag 424 clear | `funcStageChange` Yes/No ("Commander Room") | `stagML02` point 0 |
| Terminal `mate00`, Gate to Outside World | `05-lobby-quests_e820/037-msg-70000.lua` | flag 2, 4, 5, 6 or 86 set and 409 clear; or 409 set | field list (`STCHGFONT01`, `i_zzstchgcur`), Circle cancels | flag 2: `stag0001` (503 clear) or `stag0101` (503 set); flags 4/5/6/86 add `stag0201`/`stag0301`/`stag0401`, each point 0; flag 409: `stag0401` point 3 |
| Terminal `mate02`, Emergency Gate | `05-lobby-quests_e820/020-msg-70029.lua` | flag 3 and 409 clear and a recorded gate stage (`SYSgetGateStageName` not `GateOff`) | Yes/No naming the gate stage (`STCHGFONT00` 60-80) | the recorded stage at `SYSgetGateStageNo`; accepting runs `gateclear.lua`, which resets the record to `GateOff` |
| Central `mate00` (region [505..525]×[-350..-330]) | `06-lobby-quest-board_e824/071-exit-to-stagml13-2.lua` | always (no busy DM) | `funcStageChange` Yes/No ("Shop Area") | `stagML13` point 2 |
| Shop `mate00` (region [425..445]×[90..110]) | `07-lobby-shops_e828/050-exit-to-stagml12-2.lua` | always (no busy DM) | `funcStageChange` Yes/No ("Security Area") | `stagML12` point 5 |

A closed pad behaves as in retail: its script runs and does nothing, so the
label stays, no prompt opens and control stays with the player. In a new game
the Outside World gate stays closed until Ophanimon sets flag 2 in the Commander
Room (`04-lobby-ofanimon-seraphimon_e816/094-npc-ofanim-2.lua`), and the
Emergency Gate until a dungeon records its gate stage. In its flag 6 branch the
Outside World script clears the label before its `MATisAllPlayer` test (the other
branches test first), so with several players the label would close as soon as
one of them steps on; with one player it makes no difference.

`mate01` does not set `g_StChangeKind` (the bridges set `"run"`, the second exits
`"trans"`), so `funcStageChange` keeps whatever value the global last had; with
none it takes the non-`"trans"` arm (player `SQ_DEMOWAIT`, then `SQ_EXIT`).

With one joined player the existence bytes are `{1,0,0,0}` and `MATisAllPlayer`
is the player-zero test; with a party the `MATisAllPlayer` exits wait for every
joined player
([dungeon floors](dungeon-floors.md#local-co-op-in-the-hubs)).

### Destinations without a runtime

`dw4_hubruntime_destination_available` accepts the hub (`stagML…`) and interface
(`stagIS…`) stages and the field and dungeon stages whose runtime is brought up
(`dw4_field_stage_ready`: `stag0001`, `stag0101`, `stag0102`, `stagGF01`,
`stagGF02`, `stagGF03`, `dng101b1`, `dng101b2`, `dng102b1`, `dng102b2`,
`dng102b3`; [combat foundation](combat.md)). `dw4_hubruntime_prepare` refuses the
rest with a "not available" error. The application does not start a loading
worker for them: after the original fade it shows the destination's loading card
with "Destination not available" and "Circle: Back" (no Retry), and Circle
returns to the retained source through the failed-load Back path (original
`SQ_BLIN60` fade, MODELCTRL ONCTRL and PADINPUT ENABLE after 30 ticks). This is a
port policy until those stages exist; retail loads the stage. The Emergency
Gate's record is already cleared by the script when the player accepts, so after
Back that gate is closed, as it would be after a retail trip.

## Native handoff boundary

`src/stagetravel.c` supplies an owner for STAGECTL NEXTSTAGE/PADINPUT and
PLAYERPOINT SET/GETGENERATEPOS. It borrows the existing pad-input owner. SD owns
and consumes delays before delivery; the receiver copies the destination and does
not retain Lua or queue storage. It latches requests without destroying a scene
inside a callback. A between-ticks consumer can snapshot the request, retain it
for retry and acknowledge it after safely retaining or publishing the handoff. A
newer NEXTSTAGE replaces the retained destination. There is no hard-coded
destination allowlist in the request receiver.

The relevant retail command sites are `3cd868..3cd9b8` (owned stage value) and
`39c3c0..39c3e8` (signed generate-position storage/query). The host handoff is
not recovery of the entire retail stage controller. The normal engine registers
this owner under STAGECTL and PLAYERPOINT; its between-ticks loading consumer is
described under [Application loading and publication](#application-loading-and-publication).

## Authored spawn transforms

`src/playerpoint.c` follows bePoint01Info._dataList → beGroupKeepList →
beGroupKeep._childList → the joined player's igTransform._m. The inherited child
list is at runtime +28 / serialized ordinal7. It copies the local 64-byte matrix
as retail `39c1c0` does; scene graph ordering and first-transform searches do not
choose the point. An index above the last group falls back to group zero. The
three authored hub lists have no null groups. Retail copies global4e0ef0 for a
null group; its initialized value is outside this resolver, so null groups fail
explicitly. Invalid negative host indices, absent player rows and malformed
packs also fail without modifying the output matrix.

The Terminal constructor uses this resolver for its original first-arrival group
zero. The other groups resolve through it too, independently of the Terminal's
switch id 8839. The environment preparation, the destination runtime and the
application publication all take their arrival group from it.

## Destination environment preparation

`dw4_lobby_open_stage` prepares the original Terminal, Central and Shop assets
at a requested arrival group. `dw4_igfile_open_stage_pack` resolves
beFileListInfo._fnames → igNamedObjectList → named rows, selecting scene versus
`/s` support entries in authored order. It does not select packs by the physical
order of bracket strings: Terminal lists its model bytes before sound, while
Central has sound before models. Scene and support selections are checked
against NDMW 820/819, 824/823 and 828/827 respectively.

The shared environment loader retains each destination's lights, normal camera
clip planes, fog, scoped Hard/Soft textures and projective-shadow resources.
Terminal-only arrival choreography/effects remain isolated from other areas.
The normal box camera uses `cameraShape00`; Central's separate animated demo has
a different far plane and must not supply the normal camera's clip range.
Camera regions allocate from the authored list count; there is no fixed
32-entry limit.

Actor-aware `dw4_scene_load_world` also retains the explicit kind1/floor and
kind2/wall switchgraphs referenced by beHitLandModelInfo, outside the drawable
scene graphs. Collision preparation concatenates their transformed vertices and
rebases triangle indices; Shop's two floor graphs are both included. Walls are
queried by the recovered retail wall query ([Wall solver](#wall-solver)); the
floor half is the bounded walking/falling solver. This is not exact recovery of
complete retail collision traversal.

| Environment | Camera entries | Floor triangles | Wall triangles |
| --- | ---: | ---: | ---: |
| Terminal | 17 | 226 | 286 |
| Central | 37 | 385 | 674 |
| Shop | 24 | 187 | 356 |

`make -C port check-hubscene` prepares all three environments with Dorumon,
verifies model/support ownership, region/geometry counts and groups1/2 return
positions against the verified point resolver. The four-starter Terminal walking
regression also passes with info-owned collision graphs. Prepared frames retain
the original black startup fade before activation. An explicit
`dw4_lobby_draw_environment` diagnostic omits UI/fade solely to inspect the
unpublished world; repeated draws are identical and the three environments
differ. CPU headless diagnostic captures of Central/Shop were inspected. These
are not screenshots of playable travel or a retail pixel-parity claim.
Ungenerated NPC/player instances are not supplied by the environment diagnostic.

### Wall solver

`dw4_lobby_collision_check` runs the recovered retail wall query (`CHECKWALL`,
FUN_00386780): rays at `y + downRange`,
`r = 1.42 * halfWidth`, three broad rays, a stage-1 push back along the heading
by `2r - dmin` (no slide) and a stage-2 push along the hit's face normal by
`r - dist` (the slide), one-sided (a triangle blocks only when
`n . dir < -5e-7`, `n` the unit normal of `(v1-v0)x(v2-v0)`), and no query on a tick where x and z
did not change. The floor half is the bounded solver.

The retail ray/triangle test is `FUN_0018b9e0(ray, v0, v1, v2, hit, normal, faceType)`. It takes the
unit normal `n` of `(v1-v0)x(v2-v0)` and `d = n . dir`, with `dir` unit length. Face type 0 rejects
`d >= 0`, 1 rejects `d < 0`, 2 tests both sides; types 0 and 1 also reject `|d| <= 5e-7`. Every HitLand
ray uses type 0 (`FUN_00388640`), so a triangle blocks only when `d < -5e-7`. It then requires
`0 <= t <= length` (the lower bound is a sign-bit test) and that the three cross products about the hit
point, dotted with `n`, share a sign bit. It returns `t`, or -2, -3 or -4 for facing, range and outside.

`FUN_001cef70` walks the geometry. Only triangle lists and strips are tested, and geometry whose vertex
format has bits in `0xf00` or `0xf0` is skipped. Odd strip triangles swap their last two vertices unless
the face type is 2; odd means the position in the whole geometry, not within the strip. `FUN_001ceab0`
resumes after each hit, and the hit procedure `FUN_00386030` appends the hit to the order and returns 0,
so every hit is collected.

Not ported: the previous-hit latch that skips the broad test, the
`_checkSwitch` initial bits, `HITWALLFULL` for ride-on models, and the stage-2
normal's y component.

Which wall infos a model queries is retail's per-model rule on its check flag
(`dw4_hitland_info_applies`, `check-hitkinds`), ordinal 12 of
`beHitLandDelivInfoRam`. The order kind is the check flag with bit 0 cleared. An
info takes part when `(info.kind & order.kind & 0x1FF) != 0`; an info with 0x800 is
skipped by an order with 0x800, and an order with 0x1000 sees only infos with
0x1000.

| Check flag | Models | Collides with kinds |
| ---: | --- | --- |
| 7 | players (all `p_`/`m_`/`q_` records and hub `h_*`) | 2, 4, 0x402, 0x802, 0x1403, 0x1405 (not 8) |
| 11 | regular enemies | 2, 8, 0x402, 0x802, 0x1403 |
| 2051 | shots, bullets and `g_bbarrel` | 2, 0x402, 0x1403 (never the 0x802 air walls) |
| 3 | several bosses and NPCs | 2, 0x402, 0x802, 0x1403 |

The `stagML12` pack's hub player record carries 3, but the live player reads 7.

In the port:

- The player (flag 7) also queries the static kind 4 (`limit_Circle`), and the
  player and hub actors (3) the static kind 0x802 (the arena boundaries: the
  practice stage's walls are 0x802, `check-arenawalls`).
- The dynamic 0x402 prop proxies (bushes, rocks, boxes, barrels: one box proxy
  per live model slot) are queried for players and hub actors
  (`check-fieldstage-propwalls`; the slot-activity enable rule is
  unconfirmed).
- Enemies (check flag 11) query the kind-2, 8 and 0x802 graphs and the dynamic
  props too: they walk and hop with the player's walking and airborne
  solvers, so no floor edge holds them and an unsupported enemy falls
  (`SQ_FALL`) unless a wall is in the way (`check-fieldstage-enemyfall`: the
  corridor wall and the practice arena's 0x802 wall hold a hopping enemy, a live
  bush stops a chasing one;
  [dungeon floors](dungeon-floors.md#enemies-fall-off-ledges)).
- The hub actors' edge hold (`dw4_lobby_collision_check_for`'s floor step) stays
  for NPCs.

### Dynamic prop proxies

A kind-0x402 info's ordinal-8 `_checkSwitch` subtree holds one `beCopyTransform` box
proxy per ram slot: eight outward-wound triangles, four sides, y 0..50, `igAABox`
±7.07 (not the prop's visual mesh, ordinal 7 `_switchgraph`). Node i takes its matrix
from the `beModelCtrlNode2` of ram slot i of the model with the info's name. The xz
prefilter is the proxy bound plus the matrix translation only (unrotated, inclusive).
A live bush stops the player about 9.3-11 units from its centre, a `rock02` about
14.4. On retail the player stops against a crate and walks through its position once
it is erased.

A rotated dynamic prop collides as the port models it: `g_d1bkwall` at (95,10,120) in
`dng101b2`, turned -90 degrees, stops a westward walk at x 104.29 on retail (port
104.26), and past it the static wall stops the player at 74.29 (74.26). Retail's
block spans about z 97..143 and the port's 96..145: the port's corner contact blocks
z 96 and 144, which are free on retail, consistent with a slightly shorter authored
extent or a narrower end ray. This does not decide the translation-only prefilter,
since the proxy bound already covers the whole wall.

### Retail collision dispatch

Read from the code, not traced on retail. `beHitLandDeliv::vfunc_33` (`0x385890`) takes
{`HITWALL`, `HITWALLFULL`, `HITFLOORCHECK`, `HITFLOORADJUST`, `HITFLOOR`} and forwards on
group `HITLANDMODEL` to `beHitLandModel::vfunc_34` (`0x3861d0`), {`CHECKWALL`,
`CHECKWALLFULL`, `CHECKLAND`, `ONHIT`, `OFFHIT`}. The solvers are `FUN_00386780` (wall),
`FUN_003876b0` (wall-full, ride-on only, 8 radial rays) and `FUN_00388010` (floor). Each
`beHitLandModelInfo` also passes an xz bounding-box test (`FUN_003885e0`); `_checkSwitch`
bits enable nodes, and 0x400 marks moving objects.

## Native material callback queries

`src/materialcontact.c` ports the seven [recovered MAT helpers](../../docs/engine/material-contact.md)
to a typed callback snapshot: four existence bytes, current/previous player masks,
material index and deferred activation index/value. MATgetPlayerNo chooses the
first **entering** existing player; it does not choose the first currently present
player. No existing players makes MATisAllPlayer true. Shift counts retain the
EE low-five-bit rule. MATsetRun preserves the low byte and records a deferred
change and does not change membership during the callback.

The Terminal heal callback uses this owner, ends its context after Lua returns
and consumes in-range deferred run-byte changes before the next material. The
exit callbacks and the route tests use the same owner, ending the context before
DM executes queued commands. Native MAT calls outside an active callback fail
explicitly.

`make -C port check-materialcontact-retail` compares 61,602 native returns /
deferred requests with the original seven helper bodies, with no callee stubs.
It covers every four-player contact/existence mask, noncanonical existence bytes,
high bits, wrapped shifts, and activation byte truncation. Script-facing invalid
host argument/context checks are bounded safety policies. Geometry search and
callback dispatch retain their separate integration boundary.

## Destination runtime

`hubruntime.c` prepares an independently owned destination from a complete
private player-record snapshot and copied engine/RNG state. It copies PADINPUT
and starts SD/controller clocks at the admitted session timestamp before running
original func/boot/start/first. Loading time must not advance the candidate's
arrival; subsequent ticks accept monotonic session timestamps. The source remains
alive, frozen and untouched until a caller publishes or discards the candidate.
Failed preparation destroys only candidate owners. Audio is CPU-prepared; device
and GPU publication remain the application's responsibility.

The runtime preserves all four record payloads. It admits one to four joined
players (NINZU) in the four hub worlds and the field stages; the digivolution
demo (`stagML14`) and the interface scenes (`stagIS…`) require the single joined
player-zero owner and refuse a party with a named error
([dungeon floors](dungeon-floors.md#local-co-op-in-the-hubs)). The
equipped first power-socket model is retained and not replaced with a starter;
an empty `POWERSOCKETNAME` opens the unarmed appearance (see
[Digi-Lab](labo-shop.md#the-result-in-the-world)).

A `stagML14` request (the digivolution demo) prepares a scene host instead of a
lobby (`dw4/evodemo.h`, [Digi-Lab](labo-shop.md#the-digivolution-demo-stagml14)):
its original scripts run the swap and request their own exit, `stagML12` point 3,
on the runtime's travel owner; records and state pass through it unchanged apart
from the script's own writes. `DW4_EVODEMO=skip`, or a demo that cannot be
prepared, prepares that exit directly and logs it.

Native model binding follows each authored RAM-slot beModelCtrlNode2, instance
transform and Action2 bank. NPC renderers preflight the bank's own skeletal
clips; equal-joint-count rigs elsewhere in the pack cannot supply a skeleton.
Camera, material, light and switch consumers use the prepared destination.
Original first.lua, not host flag guesses, establishes Terminal return state:
the tested intro sets flag501, while flag500 remains zero.

Only a runtime with a travel owner opts into the original matz00/matz01
callbacks. They use the existing corrected player position and inclusive
authored boxes, execute once on changed membership, and retain native MAT
context/deferred run changes. Standalone fixtures retain their heal-only
boundary. Normal created-card boot enables exits alongside its application
loading consumer.

The generic WN view renders travel models and selectors, followed by native text
and HUD. The five lobby-owned greeting windows remain separate to avoid duplicate
geometry. Original fade geometry includes JOINTSET colour and FADESET opacity,
and the generic path uses that authored fade geometry; applying the legacy
whole-frame multiplier on top of it blacks out the travel window. Headless
confirmation captures have been inspected; this is not a retail pixel-parity
claim.

The runtime installs the concrete mode-zero STATUS factory. A separate full WN
roster includes the shared windows while STATUS holds the world. Original root
opening/closing, text rendering, health publication, appearance callback,
layer/audio/model freeze and restore use the existing menu contracts. The other
SUBWND modes belong to the services linked at the top of this page.

## Application loading and publication

The normal engine admits both exit materials in the initial Terminal area,
retains a split WN travel view alongside the existing STATUS owner, and consumes
NEXTSTAGE between updates. It resolves the destination's original USA loading
card before starting the CPU worker. The current session remains owned and frozen
while the card renders and window events continue. Loading samples consume host
presentation cadence without incrementing the session's simulation tick; neither
source nor candidate VM/SD/controller owners advance. On publication, host pacing
credit is reset so preparation time cannot become an arrival catch-up burst.
The original reveal/lock rules and optional loading minimum still gate publication.

After successful preparation, graphics initialize on the presentation thread.
Audio commit moves the existing mixer, stops borrowed source clips before freeing
that scene and replays the destination's original prepared PLAY state. It does not
open a second lobby device. Original source SD/Lua/DM cleanup precedes model,
collision, texture and record release. Input, tick, draw and STATUS then use the
new runtime; the legacy simulation dispatcher does not also tick the old VM.
Shutdown joins a transition worker before changing any borrowed source owner.

Failed preparation publishes no candidate and offers Retry/Back. Retry retains
the source and request. Back reuses the retained area/records and schedules original
MODELCTRL ONCTRL and PADINPUT ENABLE after 30 ticks, with the original SQ_BLIN60
full-black arrival fade. This is a host failure-recovery policy implementing the
agreed PC Retry/Back requirement, not a recovered retail disc-error flow. It resets
the retained generate-position value to the source's actual arrival group. It does
not return an active player to character creation. The no-optional-string SD delay
uses the fifth numeric overload; sending nil plus delay as a six-argument call
delivers a fifth argument to ONCTRL, which is wrong.

## Verification

All checks run headless. The application checks (`check-hub-boot*`) run from the
repository root with DISPLAY/WAYLAND_DISPLAY unset; all SDL surfaces use dummy
drivers.

```sh
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy make -C port check-hubtravel
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy make -C port check-playerpoint-retail
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy make -C port check-materialcontact-retail
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy make -C port check-lobbywalk
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy make -C port check-hubscene
make -C port check-hubruntime
make -C port check-hub-boot
make -C port check-hub-boot-failure
make -C port check-hub-boot-shutdown
make -C port check-hub-boot-gpu
make -C port check-hubgates        # every pad: label clear, prompt, accept/No/Circle routes, re-entry, closed flags (about 3 minutes)
make -C port check-hub-boot-gate   # application: Outside World gate of a fresh save -> stag0001 loads through the loading card and worker -> control returns after its introduction
make -C port check-hubedges
```

**Route suite (`check-hubtravel`).** Executes all six original bridge exits with
confirm, No and Circle (18 flows), plus their incomplete-membership guards, and
runs `mate01` and both second exits standalone (accept/No/Circle and the
incomplete-membership guard). It checks authored visible confirmation text,
original destination/point requests, neutral input admission, copy lifetime,
equal-deadline spawn ordering, retained snapshots and cancellation of undelivered
messages at unload. HP, geometry membership and world/audio consumers are
controlled leaves. The queries over the supplied material masks use the native
contact projection; this suite does not prove collision-triggered exits, player
restoration, loading or session publication, which the runtime and application
checks below cover.

**Point suite (`check-playerpoint-retail`).** Independently decodes the three
private packs and executes original `39c1c0` instructions. All 68
matrices/deliveries match: five Terminal, six Central and three Shop groups,
four player rows each, plus high-index fallback for each pack/player. Message
matrix delivery is controlled. Host invalid-input checks are a bounded safety
policy, not claims about retail unsafe reads. Assets and executable input remain
private; no binary extracts are saved in Git.

**Runtime (`check-hubruntime`).** Executes the real first intro, carries its
records and RNG through destination owners and exercises exit choices against
live native player/material/controller owners. Tests relocate to an authored
arrival point, then use ordinary camera-relative stick input to walk the bridge
into the exit; they do not call the exit script directly or supply a membership
mask. This is a bounded approach fixture, not navigation from arbitrary world
positions. The consumer in this test calls destination prepare directly after
NEXTSTAGE: responsive loading screens, application publication and Retry/Back
are covered by `check-hub-boot`, not by this test. The six-route bridge-approach
chain passes original accept/No/Circle (18 flows), arrival control restoration,
STATUS cycles, source isolation and equipped-record retention, and passes under
ASan/UBSan (detect_leaks=0).

**Application (`check-hub-boot`).** Drives the actual SDL dummy application
pump, original character creation/startup, threaded destination preparation,
stage cards and normal publication. Fixture relocation chooses each bridge's
original arrival point; ordinary camera-relative stick input then reaches the
material. The test does not supply contact masks or directly execute an exit
script. It exercises accept, Circle and No, STATUS before each exit, all six
destinations/groups, owned source records and strict clock continuity after
loading. It seeds nonzero BIT/XDATA fixture values and verifies their retention.
A catch-up injection requires every loading sample to be presented. The input
fixture waits for actual PADINPUT admission before opening STATUS. This is a
bounded bridge approach fixture, not an arbitrary-position pathfinding or
complete collision-fidelity claim.

Measured application results:

- The six-route run passes seven area visits, six STATUS cycles, all 18
  accept/No/Circle flows, all 3263 loading samples/presentations and six
  held-clock boundaries.
- A headless GPU run (`check-hub-boot-gpu`) passes Terminal → Central → Shop, two
  STATUS cycles and zero additional CPU drawing calls.
- A confirmed blocked worker/window-close fixture (`check-hub-boot-shutdown`)
  joins preparation before source teardown and publishes no candidate.
- The later-scene ASan/UBSan run passes two transfers, two Central→Shop failures,
  Retry/Back and source restoration (four destination attempts, 6019/6019
  loading presentations and three held-clock boundaries).
- An independent initial-source failure run passes two failures, Retry/Back,
  restored original source control, then successful travel to Central (678
  loading samples/presentations, nonzero currency retained).
- Normal Cross/Circle STATUS boot and initial loading
  Retry/Back/inspection-hold regressions pass.

`DW4_HUB_LEGS` bounds a focused lifecycle run (default six);
`DW4_HUB_FAIL_LEG=1 DW4_HUB_FAIL=1 DW4_HUB_LEGS=2` exercises Back after the
first transferred scene. `DW4_HUB_CLOSE_LOAD=1` blocks a confirmed worker until
window close releases it, then requires safe joining/cleanup. The focused
application sanitizer run uses `DW4_HUB_TICK_BATCH=8` to exercise production
catch-up/render-skipping while retaining every simulation update and loading
presentation. The six-route CPU and two-transfer GPU runs render at their
ordinary test cadence. The later-source sanitizer run passes (detect_leaks=0).

**Gates (`check-hubgates`, `port/tools/test_hubgates.c`).** Prepares each hub
with flag fixtures and places the player with `dw4_lobby_place_player` at the
authored region centres (`dw4_lobby_material_region`): outside the label region,
inside it with the label up, then on the pad. It asserts the label
text/arrow/band before the pad, the label closed when the prompt opens, the
destination and point on accept (all five field entries, the 409 entry, the
recorded gate stage and its clearing), restored control with the label still
closed after No and Circle, the label back on re-entering the region and the
prompt again on the pad, and that closed pads (424; no story flag; `GateOff`;
409) open nothing.

**Edges (`check-hubedges`, `tools/test_hubedges.c`, part of `check`).** Places
the player at the retail start points, holds the stick for seven seconds and
compares the stop positions with the retail ones (8 of 8 equal within 3 units,
most within 1). `HUBEDGE_GRID=1` prints the Terminal wall map,
`HUBEDGE_CGRID=<x>,<z>` the Central floor/wall map, `HUBEDGE_MAP=1` the arrival
platform's reach in 16 headings, `HUBEDGE_TRACE=1` the position every 15 ticks.

## Hub verification against retail

A read-only retail pass (fresh level-1 fixture) paired the hubs with the port:

| topic | result |
|---|---|
| Disk Shop prices and sell prices | equal (100/500/1200/160/680/1560/150/200/120/3000; sell = buy/4) |
| shop flows and strings (quantity step, confirm, Buy / Choose another, `Not enough BITS.`, sold-out rows, `Cannot equip this Item yet.`, junk donation) | equal |
| Central Card Keeper at flag 1 clear / set | equal (menu only with the flag clear) |
| Central south lip, Terminal bridge limits, Terminal north and east rims, stick headings | equal within about 1 unit |
| Central north-west and west holds (retail reads stopped at (-99.8,-73.5) and (-109.3,15.3)) | not blocks: those are where a 2.5 s hold ends; an 8 s hold ends at (-156.0,40.9,-138.3) and (-245.3,40,131.8) on retail and in the port |
| Terminal ring south passage (retail walks through to a ramp down to y 10 at (16.1,-47.9)) | equal with the one-sided `CHECKWALL` solver: retail's wall query only blocks motion against a triangle's face normal (back faces are ignored); two-sided walls jam the player at a wall at z=-60 and make it arc at x 6-14 |
| loading cards (retail sampled at 1 Hz, +-1 s, from the confirm) | not a parity target: the port's shorter cards are a deliberate quality-of-life choice. Retail shows 3-4 s of black before the card in every sample; Terminal to Central shows the card from 6.5 to 16 s with the first HUD frame at about 17 s, Central to Shop from 7.6 to 17 s with the first HUD frame at about 18 s |

## Open items

- **Destinations without a runtime.** Field and dungeon stages outside
  `dw4_field_stage_ready` show "Destination not available"; retail loads them.
- **Emergency Gate under flag 3.** Flag 3 (Emergency Gate closed during the hub
  invasion) is not exercised: a Terminal with flag 3 set runs an invasion
  start-up whose audio command the runtime does not serve.
- **Central and Shop `mate00` pads.** The pads have floor (heights 40 and 70);
  whether ordinary walking reaches them was not established.
- **Wall solver.** The parts listed as not ported under
  [Wall solver](#wall-solver), and the unconfirmed slot-activity enable rule of
  the 0x402 prop proxies.
- **Collision and approach.** The floor half is the bounded walking/falling
  solver; the travel tests use bounded bridge-approach fixtures, not navigation
  from arbitrary positions.
- **Parties.** The digivolution demo and the interface scenes admit only the
  single player-zero owner.
- **Pixel parity.** The travel window, confirmation captures and the prepared
  environments are inspected headless captures, not retail pixel-parity claims.
- **Retail stage controller.** The host handoff does not recover the entire
  retail stage controller, and the failure Retry/Back screen is a host policy,
  not a recovered retail disc-error flow.

## Open questions

- **When a dynamic wall is solid.** Unproven: a dynamic wall is solid while its slot is
  generated and shown. In one savestate the dynamic masks read as per-slot activity
  (`g_bush01z01` 0xfff for slots 0-11, `g_cannon01` 0x3, `g_torchz01` 0x1) while static
  infos read 0xffffffff, and every dynamic mask starts at 0 in the pack;
  `g_woodencasez01` reads 0x3f against three entrance spawns. Who sets the bits is not
  found in the recovered code.
- **Kind 4 winding.** Kind 4 (`limit_Circle`, 32 triangles at (403,0,93)-(517,250,207)
  in 98 stages) is wound inward and applies to players, so a one-sided treatment must
  not trap a player inside it.
