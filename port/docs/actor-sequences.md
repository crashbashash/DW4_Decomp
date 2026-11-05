# Lobby actor sequence services

The scene-owned MODELCTRL executor runs the original Digi-Elf arrival
programs from NDMW 820: female `SQ_WALK02`, male `SQ_WALK03`, the second
female's `SQ_WALK`, and their wait/talk sequences. Each prepared RAM slot has
independent movement channels, labels, control state and animation selection.
Programs remain shared and immutable. Direct sequence messages leave inactive
slots inactive; GENERATE creates them.

Normal created-card Main Lobby login uses the original start/first scripts and
scene-owned actor/player movement, collision, motion/opacity publication and
restoration through these controllers; see [the lobby contract](lobby-gameplay.md)
for evidence and scope. The original first.lua also queues patrol commands
during initial setup. The standalone [arrival adapter](lobby-choreography.md) is
kept as a reference fixture for the independent reference cases. Other
scene/controller programs still require their own transition/state checks;
general gameplay and whole-frame parity are outstanding.

## Commands and state

`MOVETRANS` accepts the arrival's `V<x,y,z>/V<rx,ry,rz>` optional string,
including fractional coordinates and signed degrees. It validates the whole
payload before changing an active actor. An inactive actor accepts the command
without moving, following retail case 24 at `0x003978b8`. The service stores
translation and authored Euler rotation; local movement uses the resulting yaw.
Retail's matrix assignment and subsequent `0x003956e0` rotation/collision refresh
are the evidence for this boundary. General optional-string decoding, scale and
rotation limiting beyond the recovered consumers remain separate work.
Main Lobby collision and renderer publication are connected as documented in
[the lobby contract](lobby-gameplay.md).

`MOVETRANS` **preserves movement channels**. Retail case 24 contains no channel
reset; the standalone adapter deliberately resets its departing actors during
relocation. Do not infer retail relocation behavior from that adapter reset.

`MOVE` supports Move/Stop/Push/Back on local Z and Jump/Fall on local Y.
Player SQ_JUMP/SQ_FALL consume PDMOVE and vertical TurnY/Landing waits;
prepared lobby gates bind NEAR MAP00. Player floor support publishes the
retail 3926d0 response after waits, including automatic SQ_FALL and onFall/noFall;
see [walking falls and portal ownership](lobby-gameplay.md#stage-portal-commander-instances-and-walking-falls). See [jump and gate contracts](lobby-gameplay.md#jump-gate-proximity-and-heal-activation)
for current ownership, evidence and validation limits.
`MOVEEX` supports TX/TY/TZ and RY with positive/negative ACC/DEC/TMP modes.
Original `_value`, `_frame`, `_playTime`, `_isSeqStop`, `_stopValue` and
`_stopFrame` bits reach the recovered EE movement-channel implementation.
Yaw updates precede local translation; movement precedes action completion
polling. Elapsed movement time uses 100 ns clock quantization and the original
16666667 denominator. Sequence selection clears yaw speed and expires marked
translation channels, preserving ordinary retained speed.

`MOVERL` attaches a model to a same-slot TRC recorder or a named bone; see
[named attachments and effect generation](#named-attachments-and-effect-generation).

`ACTION` selects the actor's own Action2 bank. Arrival `MOTIONSET RR/LP` selects
walk01/wait01/talk01 and its independent playback clock. Subsequent DELAY actions
use the recovered Action2 Frame timer without replacing the selected motion.
Reissuing the same action preserves its clock, matching Action2's named-component
replacement check. JOINTSET/FADESET/WAITCHECK object programs continue
through the same timer backend. Owned-bank RR LP/OS motion, inclusive Motion waits and compatible blend-pose
publication support lobby entry/movement. General animation/database and
other component modes still require their owning consumers. Selection and elapsed time are exposed in
`dw4_modelctrl_actor_state`.

`LABELCTRL <label>, <sequence>` replaces that instance's entry label for the
named sequence. Sequence selection starts **at** the first matching label.
Retail dispatch accepts the first LABEL and stops before the next LABEL;
it does not fall through DEF, DEM, WLK and STP sections. `WCHECK Action` retains
the cursor until recovered completion; `JUMP` selects the next sequence at
that instance's configured label. The female turn/walk program sets SQ_TALK's
DEM entry, avoiding DEF's invulnerability/control work.

`CTRL onWalk/toWalk/toWait/isLive` stores the recovered control mode.
`ONCTRL`/`OFCTRL` set control eligibility independently of authored movement.
`MUTEKI` stores its frame bits or toggles the authored wall/floor gates.
Sequence selection resets control mode and restores those gates.
Unsupported programs fail before sequence replacement.

`ISRUN` and `ISSEQNAME` expose numeric results. Sequence exhaustion leaves an
actor active. Queries and snapshots do not advance movement or animation.
The diagnostic command observer is read-only and must not mutate its owner.

STATUS model freezes hold native actor AI/control, motion channels, sequence
waits and animation clock; see [active model freezes](controller-services.md#active-model-freezes-for-status).

Player/enemy Work stops non-Y movement channels while bound (BIND) outside the
original damage enum. The gate runs after control/AI, before channel advancement,
and preserves HITBOX delivery. Freeze/control admission, enum status and retained
payload checks are described in [combat](combat.md#bind-movement-and-enum-gate).

## Arena records

Control/freeze/collision gates, cursor/labels/waits, MUTEKI, directions, AI
selection/target, named AITIMER and walk templates read recovered Work
records. Movement kernels copy a temporary payload and preserve the recovered
channel header. Instances share typed immutable command closures but own
independent Work/channels. Pose matrices publish at mutation boundaries;
render/contact copies do not advance simulation. Native Euler/motion projection
and Action2 clock services retain their contracts and fidelity limits.

Action2 command/joint/wait/timer state, current and previous animation timing,
blend duration and selected names live in recovered arena records. Public
actor snapshots read those records without advancing them; authored Euler and
matrix reconstruction remains a native pose backend. HITBOX entries belong
to Work's typed subcommand list. Original `39a500` producer math/group/geometry
matches 370 cases; entries advance through the
[retail subcommand scheduler and node locks](controller-services.md#retail-subcommand-phase-and-node-locks).
See [scope, ownership and limits](arena-object-model.md#action2-hit-volume-and-stat-comparison-records).

## AIMAP waypoint acquisition

The executor resolves each controller's `beModelCtrlInfoDataAIM._aIMapList`
through the same pack-local info used for its sequences. Immutable map names,
distance-bound and rotation-limit words share the program lifetime; each instance
owns its selected index and target. Read-only `dw4_modelctrl_aim_state` returns
that boundary without ticking AI or consuming RNG.

An explicitly bound owner runs original female `SQ_WALKON`: `AIMAP MAP01`
selects its own WPOS map, runs `aim_<info_name>.lua` synchronously with call name
`WPos`, and copies the resulting target. It then executes the authored label
changes and enters SQ_WAIT's WLK section (`CTRL toWalk`). `dw4_modelctrl_script`
borrows a scene engine, scope and persistent scalar model record; callers supply
actual RAM/record/HP identity and detach before releasing them. Standalone instances
start unbound and do not inherit another instance's HP or context. The prepared
live owner binds its slots as described under
[persistent prepared object state](#persistent-prepared-object-state); the
patrol consumers are described under
[patrol timers and control consumers](#patrol-timers-and-control-consumers).

The callback uses the MDL snapshot and scope rules. A native HP change
during the call takes precedence over its cached HP. Unloaded scopes cannot commit
HP or target output. Published DM groups inherit the model scope. Synchronous
REMOVE or sequence selection invalidates the outer dispatch cursor; the new
sequence wins without executing the old program's remaining label/jump commands.
This cursor rule is a tested host lifetime policy, not a recovered retail reentry
claim. Callback handlers must retain the model owner for the duration of dispatch.
Missing bindings and non-WPOS maps fail preflight; callback failure stops the
operation and does not roll back prior native effects.

Retail `0x00394920` looks up AIM/map records, stores the map's list index, sets a
temporary WPos output pointer, invokes `0x00394400` with `aim`, `WPos` and the info
name, publishes the three target words, clears the pointer and removes `AITIMER`
through `0x003a8580`. The native executor invalidates its AI timer on map acquisition. The acquisition
oracle retains timer removal as a controlled leaf; the timer consumer has its own
instruction comparisons (next section).

The AIMAP checks run 128 original WPos executions through
SQ_WALKON against independently computed waypoint/HP changes and the full shared
RNG state. They cover unbound preflight, instance separation, retained maps after
closing the source instance, snapshots without RNG draws, conditional HP commits,
reentrant selection/removal and scoped DM cancellation. The retail oracle runs
`0x00394920` for all 128 supplied targets and checks map lookup/index, callback
selectors, target-word publication, temporary-output clearing and the AITIMER
removal request. Lookup/Lua execution/timer removal are controlled leaves; map
metadata compares raw descriptor-selected words because the readable analysis
parser rounds float values. This comparison does not verify AI update timing.

## Patrol timers and control consumers

AI/control runs before sequence/movement updates, as retail manager `0x00395b50`
orders them. Enabled WPOS maps acquire one zone choice only when AITIMER is absent
or strictly expired. CTRL zero invalidates the timer; OFCTRL suspends acquisition
without consuming RNG. Distance uses EE float Z² + X² + Y² and strict map bounds.
Each acquisition consumes exactly one shared RNG draw, including single-choice
zones. Queries, snapshots and rendering consume none.

Timer starts reproduce unsigned low-word conversion and float quantization after
`ns >> 18`; expiration uses signed wrapped subtraction and a strict duration <
elapsed comparison. Authored frame durations, sequence, direction offset and map
turn limit are retained until acquisition. Direction uses the original EE atan
polynomial/quadrants rather than host atan2. Yaw turns by the shortest wrapped
arc, with the retail negative-direction tie; active yaw channels replace the turn
limit even when their current step is zero. Translation follows yaw.

CTRL fallbacks consume only SQ_NONE: toWalk/toWait select SQ_WALK/SQ_WAIT, and
onWalk changes movement phase using authored MOVECTRL Move/Stop values. The
walking flag compares SQ_WALK, not SQ_WAIT. Existing AI choices retain priority.
AIMAP callbacks refresh targets through authored sequence commands, not query ticks.

The model-AI oracle verifies 363 direction samples, 120 CTRL states, eight timer
starts, 24 expiry cases, 441 turn cases, 512 choices/full RNG states and ten frame
durations against retail instructions. Lookup, allocation, sequence dispatch and
movement start are controlled leaves. Native SQ_WALKON checks cover strict timer
boundaries, OFCTRL holds, resumption, invalidation and exact shared RNG draws.
These comparisons establish service primitives and native scheduling; full-game
patrol trajectories, collision and renderer publication remain unverified.

## Persistent prepared object state

The production scene owner passes its session Lua engine to `dw4_controllers_open`.
Each prepared KIND_OBJECT slot owns a stable `dw4_script_model` alongside its
MODELCTRL instance. Its RAM selector is the authored list index assigned at
acceptance, its info name comes from the exact prepared native info, and its
record number begins at **-1**. Retail Work metadata installs this default at
`0x3510e4..0x351104`, through `0x2ea4b0`. Binding does not invent a gameplay record
or execute a callback. KIND_ENEMY slots are bound the same way
(`src/controllers.c`); other kinds are not bound by this owner.

HP and max HP start at zero. Supported GENERATE programs initialize both to 100
only when max HP is zero, matching `0x396d74..0x396d98`. Direct sequence messages
do not initialize health. Preflight failure leaves health untouched. Removing and
regenerating a slot preserves existing nonzero-max health, so the guide's waypoint
index held in HP persists instead of restarting on every sequence selection.
The explicit standalone start API initializes health when creating an inactive
bound object; selecting an active sequence preserves it.

`dw4_controllers_model_state` copies the current scalar state without ticking or
consuming RNG. `dw4_controllers_health` lets native consumers update the same
owned HP/max-HP values, including during a synchronous callback. The
conditional callback commit preserves native HP changes. Scope cancellation
rejects cached HP/target commits while retaining native effects already performed.
Closing the scene unregisters receivers, detaches model callback bindings and only
then frees their owned scalar state. Lua/SD/DM scene cancellation still precedes
controller close; callbacks must not release the owner while dispatching.

`test_controllers` exercises the same prepared owner used by the session, through
real SD routing and original collected lobby bytecode across alternating scene
reloads. In each lobby it checks 128 guide-slot WPos changes against independently
computed endpoints and the complete shared RNG state, plus 128 callbacks on an
unmatched slot that must preserve health, zero output and RNG. Health survives
REMOVE/GENERATE, selector identities remain independent, snapshots draw no RNG,
and a controlled fallback checks MDL identity/record/HP queries, native mutation,
reentrant sequence selection and scope cancellation. The standalone
actor callback tests retain their coverage.

`verify_controller_slots_retail.py` executes the Work record-default
instructions and compares 32 native GENERATE health states against the retail
initialization slice, plus 32 native direct-sequence preservation guards. Cases
include zero, positive and negative values and active/inactive slots.
Allocation, other creation services and complete retail
message dispatch remain outside this comparison.

## Hub NPC animation databases and skinning

The generic hub renderer binds the authored beModelCtrlNode2 for each RAM slot
and samples its owned transform, selected motion, blend and opacity. Motion caches
resolve both animation and skeleton from that model's
beAction2Info._animationDatabase. Global joint-count matching is ambiguous in a
full pack: Princemamemon and Agumon both have 19-joint rigs. The legacy preview
entry point keeps its unique-global-rig policy; full hub owners use the scoped API.

MetalEtemon has 34 bones/21 joints and a two-word translation bitmask with declared
bitCount34. The native decoder reads declared masks up to its 64-bone limit.
Leomon has 27 bones/24 joints and two influences per vertex: its 2506-vertex mesh
carries 20048 weight bytes and 5012 palette-index bytes. The decoder accepts one
to four finite influences, validates both extents and palette indices and uses
authored weights without normalization. The player and Ogremon skins have one
influence per vertex; that is not a universal skin format.

The isolated runtime preflights each bound skeletal model's authored motion list
before publication. The four-starter animation regression and the three-area original
startup/render test cover this path. Full retail frame/pose parity, skipped-frame outgoing
one-shot blend history and general animation formats remain separate checks.
See [hub travel](hub-travel.md) for current application and testing boundaries.

## Named attachments and effect generation

Prepared generic models execute MOVERL's same-slot TRC or named-bone lookup.
Work owns the retained track or copied model/bone names, and updates copy the
recorder matrix or compose the sampled local bone with the source node. The
animation backend supplies names, clocks and blends; lookup copies
state without running a renderer or advancing a controller clock. Native
prepared tests use an original Digi-Elf rig and heal-effect program. The
full recorder traversal, animation-combiner and exact trig boundaries remain
open; see [ownership, semantics and validation](controller-services.md#effect-sound-and-attachment-services).

The published player participates in prepared scene attachment lookup without
joining a second update/draw roster. Its bone poses use a private graph decoded
on demand from the owning Action2 bank. Binding/detach, generated effects, sound
routing and remaining fidelity limits are documented in
[controller services](controller-services.md#published-player-dependencies).

## Verification

From `port/`:

```sh
make check-actorctrl
make check-script-retail
make check check-retail -j8
```

`test_actorctrl` loads the original female/male programs, checks independent
instances and shared-program lifetime, turn-before-walk, retained acceleration,
label-selected talk, braking, movement-preserving relocation, rejected transform
payloads and failed sequence replacement. A test-owned Lua 4 program uses the
arrival's real selectors/commands through SD and DM: delayed transforms and
sequence changes, numeric ISSEQNAME waits and held snapshots. It is a service
fixture, not execution of the complete lobby first.lua.

`verify_actorctrl_retail.py` independently resolves the original pack's banks and
sequences. It executes retail dispatch `0x00395250`, MOVE/MOVEEX `0x00393260`,
channel start/expire/update `0x00392d20/90/e10`, CTRL `0x00391a10`, MUTEKI
`0x00395070`, label registration `0x003943c0/0x00393c80`, label lookup
`0x003960f0`, and ISRUN/ISSEQNAME case bodies `0x00397100/18`.
Original CTRL/MUTEKI and label-section stop traces also match. Ten MOVETRANS
active/inactive placements execute case 24 at `0x003978b8`: matrix-building,
assignment and rotation/collision refresh are controlled leaves, while the
message gate, vector inputs, degree conversion and unchanged channel bytes are
checked. Female/male ordered command traces match; all **360 complete channel states**
(176 bytes each) and **1,080 numeric query results** match. Inactive and missing
work query cases also execute retail instructions. Frame durations use the
retail conversion instructions; completion uses the verified strict,
quantized Action2 timer contract.

Action playback/completion and sequence-message reentry are controlled leaves
in this oracle. String interning, list storage and class getters are controlled
host services. The comparison proves these command/channel/query boundaries,
not full manager latency, blend poses, world positions after collision or visual
parity against a running game. The separate
18,000-case movement oracle remains part of `check-retail`.

Run conditions and limits:

- The actor, controller and dialogue tests also run under ASan/UBSan in
  separate headless builds with `detect_leaks=0` and `halt_on_error=1`.
- The full run uses `SDL_GAMECONTROLLER_IGNORE_DEVICES=<vendor>/<product>` for the
  virtual-pad test.
- Optional live texture/pose/fog checks skip without their private inputs.
- No emulator-session, Windows, physical-controller or Steam Deck validation is
  claimed for these services.

## Open items

- General optional-string decoding, scale and rotation limiting beyond the
  recovered `MOVETRANS` consumers.
- General animation/database and other Action2 component modes beyond the
  owned-bank RR LP/OS motion, Motion waits and blend-pose publication.
- Full-game patrol trajectories, collision and renderer publication are
  unverified; the AIMAP comparison does not verify AI update timing.
- Full retail frame/pose parity, skipped-frame outgoing one-shot blend history
  and general animation formats for hub NPCs.
- Full recorder traversal, animation-combiner and exact trig boundaries for
  named attachments.
- The oracle reports a negative-delay reentrant SD discrepancy that is not
  resolved here.
- Other scene/controller programs need their own transition/state checks.
