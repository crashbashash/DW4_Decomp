# Lobby arrival choreography

Normal created-card Main Lobby login uses original start/first scripts and
scene-owned actor/player movement, collision, motion/opacity publication and
restoration; see [the lobby contract](lobby-gameplay.md) for evidence and scope.
The bounded arrival adapter described below is the script-less path that its
regression tests use; general gameplay and whole-frame parity are outstanding.

The bounded Main Lobby arrival adapter runs independent movement channels for
the male Digi-Elf, female guide and second female. Each actor retains its own
position, rotation, movement speed and animation clock throughout dialogue.

## Movement and completion

`src/npcmotion.c` recovers the complete consecutive movement-channel group at
`0x00392d20`, `0x00392d90` and `0x00392e10`. Its 44-byte state uses the existing
EE float implementation. MOVE starts at retained speed, adds
`value / (frame * frame / 2)` per frame, and caps at the authored value. Thus
Move's value 0.14 and frame 6 reach full speed after about 18 updates, rather
than applying 0.14 immediately. Stop uses value 1 and frame 4; it brakes from
retained speed instead of resetting position or speed abruptly.

The guide's WALK02 and male's WALK03 use the pack's RYPACC channel, including
its timed acceleration and subsequent stop-value/stop-frame braking. Rotation
is updated before local forward translation. The Action2 wait durations load
from each actor's own action bank: female DELAY03 is 18, DELAY01 is 65;
**male DELAY02 is 18**, whereas female DELAY02 is 90. Absolute-clock completion
uses a strict `elapsed > duration` comparison, with frame-to-nanosecond
conversion through EE arithmetic. Movement runs before the completion poll;
new movement commands take effect on the following update. The greeting starts
when the guide's walk action completes.

Movement delta uses the host clock's 100 ns quantization and retail division by
16666667. The channel preserves the retail zero-remaining-time behavior: a
playTime that becomes exactly zero is no longer decremented. Quantized clock
deltas avoid the perpetual turn that an artificial all-1.0 cadence can produce.

`tools/gen_lobby_arrival.py` generates the opening talk schedule, the male's
20-tick walk delay and the final 10/120-tick delays from original Lua bytecode.
It decodes signed operands using Lua 4's
[MAXARG_S definition](https://www.lua.org/source/4.0/llimits.h.html):
`(((1 << 26) - 1) >> 1)`, or 33554431; with 33554432 the integer literals
come out one lower. The generated arrival
header carries the original pack SHA256.

## Collision, route and departure

The adapter loads the authored collision meshes independently of drawable scene
roots. NDMW 820's beHitLandModelInfo kind 1 is floor (geometry attribute 1064,
226 triangles); kind 2 is wall (attribute 139, 286 triangles). The collision
probe uses the retail reflection defaults: halfWidth 3, upRange 4, downRange 4,
confirmed at `beHitLandDelivInfoRam_InitFields` (`0x0035e860`) and in an offline
slot-3 EE-RAM read. The examined `.03.p2s` has SHA256
`8ca05974afad7df435ab7409610174f1565db5cff2c7f27b7baad66694e7f0db`;
delivery RAM at `0x0112be58` carries vtable `0x00536230` and those defaults. Wall probes use the recovered 1.42 width multiplier and
lower probe height; the native solver resolves wall planes and permits sliding.
Four floor-corner probes choose the highest supported floor within the strict
vertical window. An unsupported move retains the last supported position.

The second female keeps her authored yaw-78.8 walk throughout the camera and
all dialogue pages, including arbitrarily long message dwell. She reaches the
lobby wall and stays within the collision surface rather than freezing at the
camera endpoint or walking through a wall. Her walk animation remains active
until the script's final SQ_WAIT. The male also continues WALK03 through the
message sequence, starting after his own 18-frame turn action.

After the final message window closes, both departing actors brake. Ten updates
later, the second female moves to `(240,40,-150)`, yaw 0, and the male moves to
`(258.187,40,174)`, yaw 180. Relocation clears their movement channels so residual
speed cannot displace those placements. Introduction completion follows at
120 updates after window closure.

The guide independently starts the first `SQ_WALKON` departure leg when that
window closes. She turns toward `(20,10,-35)`, accelerates using the same Move
channel, and plays `walk01` through the control handoff. She brakes into `wait01`
inside the authored five-unit arrival radius; she is never relocated with the
other Digi-Elves. Draws and held Cross cannot restart or advance the departure.

`gen_lobby_arrival.py` verifies the immediate `ONCTRL`/`SQ_WALKON` command order
and extracts the first destination directly from the literal tables in original
`aim_n_digilff.lua` bytecode. Its route has X `130/20/60`, Y `10/10/10` and Z
`-35/-35/-10`. The script's one-based RAM number 2 identifies the guide; initial
HP 100 becomes waypoint 1 and the first WPos callback advances to waypoint 2.
The native reader resolves this actor's AIM/MAP01 through `beModelCtrlInfo`,
loading squared arrival distance 25 and rotation limiter 0.174533 radians.
Retail `0x00390f80` selects distance zones and AI actions; `0x003956e0` limits
rotation by elapsed frame time before movement. These bodies were inspected in
the analysed Ghidra project and checked against retail MIPS disassembly.
Without attached scripts this remains the bounded departure leg used by the
arrival regression. The live session attaches original WPos bytecode and the
shared RNG before scene publication, then continues MAP01 choice selection and
SQ_NEXT targets. Movement/sequence scheduling is still bounded; exact dispatcher
latency and full patrol scene parity remain unverified. See
[model callback integration](lua-integration.md#model-callbacks-and-native-rng-consumers).

## Verification and boundaries

Run from the repository root:

```sh
python3 port/tools/gen_lobby_arrival.py --check
python3 ../scripts/verify_npcmotion.py --elf ../local/extracted/SLUS_208.36
make -C port check
make -C port check-retail
port/build/lobby_frame ../local/extracted 339 /tmp/arrival.png /tmp/arrival.tsv --ui
```

The movement oracle executes retail R5900 instructions and compares every byte
of channel state plus returned float bits: 18,000 comparisons across all six
movement modes, zero-frame acceleration, retained speed, expiration and variable
deltas. It also checks the collision-default initializer instructions.
`test_lobby` checks gradual acceleration, guide turn completion, all four player
assets, both short dialogue and an 80-second first-page dwell, stable wall-limited
walking, all greeting groups, exact tenth-update relocation, zero residual
movement and 120-update completion. `test_lobbycollision` covers wall sliding,
slopes, unsupported edges and vertical walking limits. The arrival frame is
also rendered and visually inspected. Full `make check` and `make check-retail`
pass.

Collision is a bounded native triangle solver, not a bit-exact recovery of the
complete HITWALL/HITWALLFULL traversal. Falling, ride-on collision, the guide's
the complete WALKON AI dispatcher, player movement and player collision remain outside this arrival adapter.
The bounded HUD/camera/control restoration is described below. The movement-channel oracle
does not establish frame-identical retail dispatcher latency or full-sequence
pixel equivalence.

## Control handoff

The original flag-500 bytecode queues six commands with the same 120-tick delay:
`WN01/SET`, `WN00/SET`, `SETBOXCAMERA`, model `ONCTRL`, player `SQ_WAIT`, and
MATCTRL `RESTART`. `tools/gen_lobby_arrival.py --check` verifies their order and
shared delay against the original NDMW 820 chunk. The native adapter publishes
those eligibility gates together on tick 120 after final window closure. Its
`dw4_lobby_control` diagnostic reports the handoff tick, selected camera region,
camera world matrix and material-query tick count/membership mask. Repeated input
cannot restart the handoff; drawing cannot advance its timers.

The status presentation uses the original `i_stpnl00`..`04` graph branches for
one joined player, their pack JOINTSET ranges and species portrait sample. Panels
resolve named shared images from Terminal Area's AREA 674 language library;
standalone images in that library are not necessarily reachable through its own
texture-attribute graphs. The name and starter level/HP/MP use the original
MINIMUM font and the same recovered starter values as the created card. Numeric
controller geometry rewriting remains unimplemented, so its bind-pose zero digits
are suppressed in favor of font text. This is a bounded HUD presentation, with
retail typography/placement, dynamic gauges, additional
player slots and configurable margins/scale still requiring their own work.

**Player-number badge (implemented as an approximation of the native SETEFFECT).** Retail shows a dark hexagon with
the player number and a leader line beside the player in the hubs. It is not scripted: `beNDMWMdlPlayer::vfunc_44` (`0x3d4390`)
sends the native messenger command `MODELCTRL <player> SETEFFECT i_pcnumic SQ_OPENP<n> 480.0 V<0,10,0> true true`.
`i_pcnumic` is a WN00-layer model in each hub pack (like `i_pointcur`) whose `SQ_OPENP0..3` sequences pick one of four
`igBillboard` children drawing `pShape1`. The port has no `SETEFFECT` handler; instead `badge_tick` in `src/lobby.c` drives the same
owned `i_pcnumic` controller through `dw4_controllers_send`: `GENERATE "V<x,y+10,z>/V<0,0,0>/SQ_OPENP0"` once the player has been under
control and idle (no stick, jump or talk input) for 480 frames (not during the greeting or a conversation, as in retail frames), `MOVETRANS` every tick, `REMOVE` when control is lost,
and `src/modelview.c` projects it with the scene camera exactly like `i_pointcur`. The Terminal free-control pose (60,10,-30)
matches the retail frame to within a few pixels (the leader line's animation phase differs); `test_hubruntime` asserts the
badge is absent before control and live in Terminal, Central and Shop. **Idle delay:** the badge is not shown while the player is active. Live in the Terminal, after a
stick push it is absent at 20-420 idle frames and present at 540 and 700, so `480.0` is the delay before it shows (8 s at 60 fps);
input clears it (`vfunc_38` sets the `+0x124` flag, `vfunc_44` then sends the clearing message). The window is 420-540 frames
(captures add a few frames of latency) and only stick input was tried as the reset. `badge_tick` gates on 480 frames since the
player's sequence was last something other than `SQ_WAIT` (the recovered handler only sends the badge in `SQ_WAIT`, see
[vfunc_44](../../docs/engine/near-miss-shapes-player-vfunc44.md)), or since the last stick/jump/talk input or regained control; `test_hubruntime` asserts it is absent at 300 idle frames and live at 540. Unrecovered: the two
flags, the exact trigger message and the badge's closing sequence; the badge's `igBillboard` nodes face the camera at all times (`billboard_matrix` in `src/modelview.c` replaces the node's world rotation with the inverse view rotation, as for the `i_pointcur` arrows), so it looks the same whatever the player's heading; only player 0 is drawn (sequence `SQ_OPENP0`), co-op numbering
(`SQ_OPENP1..3`) is untested.

The camera reads the 17 corresponding geometry bounds, eye transforms and
interest transforms from `beCameraBoxData` in NDMW 820. Initial handoff copies
the selected rig directly, as retail does when its old region is zero. Subsequent
region changes run the [recovered retained-eye/interest transition](box-camera.md),
including interruption and faster stationary completion. Options camera modes and
live multi-player framing remain open. `PLAYER SQ_WAIT` rebases the player idle once; attached appearance models
share that clock when present. Control eligibility does not implement
movement, combat, collision or interaction input.

MATCTRL resumes sampling the 11 authored `beMatCtrlData._chkBox` volumes on each
simulation tick. Membership masks update after handoff.
General component/view-disable dispatch and renderer visibility responses
remain outstanding; this does not establish retail wall-fade equivalence. Portal
animation remains on its independent recovered model clocks throughout.

`test_lobby` checks all four starters, hidden/disabled state through tick 119,
all gates enabled on tick 120, a finite authored camera, stable handoff identity
under 180 further Cross inputs, continuing material queries, no remaining message,
a visible HUD contribution and no simulation advancement during draws. The
existing short and long dialogue cases retain exact NPC relocations. Set
`DW4_LOBBY_TEST_FRAME=/tmp/handoff` to save post-handoff frames for all four species.
`test_lobbyui` checks that the four HUD portraits differ using their UV-driven
atlas samples. `test_lobby_gpu` also advances the complete greeting and renders
post-handoff frame 1100 through both backends. `make check` and `make check-retail`
pass; focused checks cover the HUD portrait UV/composition path.
The arrival validation compares the complete
retail route with the native SDL2 window and virtual controller, including all
15 greeting pages and the final handoff. Physical-controller and optional live
pose/fog checks remain environment-dependent.

The departure regression checks all four starters, including the long message
dwell: no guide translation before closure, immediate walk animation at closure,
gradual acceleration on subsequent ticks, turns bounded to ten degrees per frame,
movement before HUD/control restoration, braking within the original arrival
radius, unchanged delayed placements of the other NPCs, and draw-independent
guide state. The deterministic checks do not establish retail AI dispatcher
latency, randomized later patrol behavior or full-frame pixel parity.
`make -C port check check-retail -j8` passes, including
CPU/GPU lobby checks and 18,000 retail movement-channel comparisons. A rendered
post-handoff frame was inspected. Optional Wayland presentation and live pose/fog
checks skip without their session/dump inputs; the departure has no emulator comparison.


## STATUS world hold boundary

The lobby owner exposes a STATUS hold that stops its world/choreography tick
and suppresses the arrival/HUD UI adapter while the menu owns presentation.
Window/service clocks remain separate. Original scripted NPC/AI state, animation
samples and control/material counters stay unchanged over the native hold test;
releasing it advances exactly one world tick without catch-up. Sound sampling
uses the shared supplied service clock, preserving menu repeat deadlines.

A validated level/HP/MP/maxima tuple reaches the HUD's numeric owner. Fresh
lobby publication supplies actual created-player records; original fallback
values remain for standalone diagnostic lobbies. The health restore contract is
in [player records](player-records.md#live-health-restoration-boundary).
Meters, appearance replacement, UI-layer/receiver handoff and the production
STATUS factory still need connection; normal-boot Start remains gated.

## Circle advances greeting dialogue

The bounded greeting/terminal-message adapter receives a pressed edge from
either Cross or Circle. Circle follows the same admitted page-advance and final
window-close path; opening, closing, beep and departure waits retain their
existing gates. Holding a button does not generate another edge. Circle does
not skip the entire introduction or change original choice-menu cancellation.

`check-status-boot` runs the same create/login/greeting/two-STATUS-cycle route
with Cross and then Circle for all greeting-page prompts. A Cross-only bridge
would leave the Circle variant in the introduction. The original shared
message/choice services receive both button masks as well.

## Called-character arrival (flag 501 set)

A character that has already seen the greeting (story flag 501 set, e.g. any called, progressed save) skips the
first branch of `first.lua` (`lua/01-lobby-hub/05-lobby-quests_e820/042-layer-setup-2.lua`). The live
session runs the original scripts on the scene-owned controllers, so none of the bounded adapter's `phase[]`,
`message`, `relocation` or `guide_departure_tick` state takes part; the native lobby only presents what the
scripts publish. Lobby-tick trace of that path (the script starts on tick 0; queued commands count from tick 1):

| Tick | Original command | Owner |
|---|---|---|
| 0 | stage start (`009-layer-setup.lua`): `n_digilfm` 0 GENERATE `(258.187,40,174)` yaw 180, `n_digilff` 3 GENERATE `(240,40,-150)` yaw 0 | the two other Digi-Elves start at their final stations; no MOVETRANS is needed |
| 0 | stage start: `n_digilff` 2 GENERATE `(60,10,-10)` yaw 180 **only** for flag 1, 2 with 20 clear, 4 with 82, 5, 6 or 86 | the guide exists only in those story states |
| 5 | `i_fadewn01 SQ_BLIN60` | fade-in starts |
| 25 | `n_digilff 2 SQ_WALKON` (and `n_agumon 0 SQ_WALKON` at 14) | guide's MAP01 patrol (SQ_WALK/SQ_WAIT/SQ_NEXT on the shared RNG) |
| 31 | `PLAYER <name> SQ_ENTR` (queued with delay 30) | player TRNSS1: 50-tick fade and the `x_100trnsin01` rings at run frames 0/6/12 |
| 121 | `PLAYER ONCTRL`, `PLAYER SQ_WAIT`, `MATCTRL RESTART` (delay 120) | HUD/control hand-off |

**Entry effect.** The rings and their `y_100trnsin01` stars are the `beActionStarterInfo x_100trnsin01` rows of
the player's `TRNSS1` action, which `SQ_ENTR` selects. With scene-owned models attached the lobby arms
the entry on the first PLAYER `SQ_ENTR` the scripts dispatch (`dw4_lobby_player_service`): tick 31, 26 ticks
after the fade-in starts, matching retail 0.5 s frames of a called Lv.99 character (ring at +0.5 s and +1.0 s,
HUD at about +1.8 s). Starting them on the greeting's generated `LOBBY_PLAYER_ENTRY_DELAY` (180), whatever the
scripts do, would put a called character's ring about three seconds after the fade-in instead of half a second.
The greeting's DM-queued `SQ_ENTR` (delay 180) is dispatched on tick 181, so the live
greeting's rings start on the same tick as the player's own entry fade. The
script-less adapter and its tests keep the generated 180.

**Guide.** The guide needs no native special case. With flag 2 set and 20 clear the guide is generated at
`(60,10,-10)` and walks from tick 25 along its authored route (X 20..60, Z -35..-10 in the first 600 ticks,
pausing and turning back), drawn from the first frame of the fade-in, as in retail. A private test save that
shows no guide has flags 2 **and** 20 set (plus 320, 383, 501–508, 701, 707, 725, 804, 960), so the original
stage start does not generate `n_digilff` RAM 2 and the queued `SQ_WALKON 25` has no receiver. The retail
capture used a different Lv.99 save whose flags were not read; it shows the guide, consistent with one of the
GENERATE conditions holding there.

`make -C port check-called-arrival` (`tools/test_called_arrival.c`) boots the real title → Call Digimon → log-in
route on a synthesized card (p_agumon with flags 2, 501, 508) and checks: fade-in on tick 5, rings 20–35 ticks
later (31), HUD hand-off on tick 121, the guide drawn from tick 0 and walking by tick 25–40 within the Terminal
floor, and both other Digi-Elves at their stations. With a fixed 180-tick entry delay it fails (rings on tick 180).
