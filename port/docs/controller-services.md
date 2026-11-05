# Scene controller services

Prepared title and Main Lobby scenes own MODELCTRL instances and expose
creation, sequence selection, removal and completion queries through SD/DM.
Lobby windows execute authored programs and render their resulting joint clocks;
the lobby camera exposes its actual demo/box state. LAYERCTL retains the
authored mask dispatcher. Normal created-card Main Lobby login uses the original
start/first scripts and scene-owned actor/player movement, collision,
motion/opacity publication and restoration; see [the lobby contract](lobby-gameplay.md)
for evidence and scope. General gameplay and whole-frame parity are outstanding.

## Model ownership and commands

`src/controllers.c` walks prepared `beModelCtrlInfo` objects in collection order.
Repeated rows sharing a native object do not create duplicate instances. Each
referenced `beBaseInfoRamList` row supplies one independent runtime slot, numbered
from zero. Retail acceptance at `0x003787a0` writes that index to RAM +8
(`0x00378850`), along with the info and manager owners at +12/+16. Serialized
`_ramNo` values are not runtime selector numbers.

The owner registers MODELCTRL receivers with exact names and slots. Each command
and model update republishes active eligibility, so selector -2 can observe a
creation/removal immediately. Nil names, wildcard ids, query result ordering,
delayed SD delivery and scope cancellation remain the registry's responsibilities.
The complete prepared collections contain 190 title and 199 lobby model slots.
The eight title models and five greeting models use specialized owners for slot
zero instead of duplicate generic registrations; other slots remain independent
generic owners. The lobby's fade model remains in the generic owner.

`src/modelctrl.c` resolves each controller's pack-local sequence-info reference
and the same pack's named Action2 info. It owns decoded command arrays; instances
share immutable programs while retaining separate sequence cursors, waits and
Action2 clocks. Referenced strings borrow the mounted immutable pack. No host
pointer enters a recovered four-byte field. Owner teardown follows SD/Lua/DM
cleanup and precedes releasing prepared objects. Closing a controller owner alone
unregisters its tokens; scene teardown must also cancel the owning SD scope.

Supported commands are `GENERATE <sequence>[/V<x,y,z>]`, a direct authored sequence key,
`REMOVE`, `SQ_ERAS`, arrival `MOVETRANS`, `ONCTRL`/`OFCTRL`, `ONFREEZE`/`OFFREEZE`
([freezes](#active-model-freezes-for-status)) and `SETEFFECT`/`SETSOUND`
([effect and sound services](#effect-sound-and-attachment-services)).
Direct sequence messages leave inactive slots inactive. Queries return numeric `ISRUN` and `ISSEQNAME` results;
an inactive model cannot match a sequence. An empty sequence retains an active
model. Sequence exhaustion does not imply removal: removal follows an authored
`JUMP SQ_ERAS` or an explicit removal command.

The common program executor supports `ACTION`, `WCHECK Action` and
`JUMP`, plus actor MOVE/MOVEEX/MOVERL, LABEL/LABELCTRL, CTRL, MUTEKI and HITBOX.
Positive MUTEKI counts decrement at the original post-wait update boundary;
authored talk boxes, cached projection and the scoped player-contact callback
consumer are implemented. Talk registration, dispatch and the player probe are
described in [NPC interactions](npc-interactions.md).
[Lobby actor sequences](actor-sequences.md) records Digi-Elf arrival support and
its retail command/channel/query comparisons. Actions execute JOINTSET, FADESET
and Joint/Frame WAITCHECK components through the recovered Action2 timer/joint backend. Reachable programs
are checked before replacing a live sequence; unsupported components, missing
jump/action targets and immediate command cycles fail with a diagnostic.
Registering a model slot does not implement unsupported programs.
This is a native dispatcher over original data, not a recovered implementation
of retail `0x00395250` or the full MODELCTRL message handler `0x00396a80`.

Prepared KIND_OBJECT slots bind persistent scene-owned RAM/record/HP callback
state; see [actor state ownership](actor-sequences.md#persistent-prepared-object-state).
WPOS patrol timers/control consumers, positioned GENERATE, SELECTCTRL and font
commands are implemented.

### Arena records

The manager and per-slot RAM/Work/data/node records live in the session
arena, with slot/info/manager links and shared typed immutable sequence/command
closures. Work owns labels, waits, gates, direction and four typed movement
channels; AI state, named timers and PDMOVE templates are also arena objects.
Health is held by Work's numeric record references. Callback PODs are legacy
input/output projections with native-change precedence. Render/contact owners
copy the published node matrix. Immutable decoded lookup tables, native clocks,
callbacks and animation projections remain host backend context. This preserves
the native dispatcher and its documented supported-program boundary; it does
not establish full matched virtual dispatch. See [scope and validation](arena-object-model.md#model-controller-actor-and-status-work).

Supported Action2 owners keep their manager/info/RAM/Work, active components,
node and WAIT timer in actual recovered arena instances. Bounded addresses used
by the recovered API are translated at the boundary; fields contain four-byte
handles. Replacement and scene/clone teardown release their complete closures.
Animation names/current and previous timing, blend duration and model fade values
are typed records too. The native clock, animation decoder/sampler and material
rendering leaves retain their documented behavior limits. See
[the ownership and validation contract](arena-object-model.md#action2-hit-volume-and-stat-comparison-records).

### Specialized window presentation peers

`dw4_controllers_external` adds a read-only presentation peer for an authored
model/slot whose specialized owner already handles SD and clocks. Duplicate
identities fail. Generic collection does not register, tick, sample or destroy
that external model. Prepared checks verify renderer lookup, independent clocks,
borrowed lifetime after collection close and duplicate refusal. The original default
190/199 rosters are unchanged until an explicit peer is added. Lobby APIs
expose their actual window models; no duplicate live receivers are installed.
These external aliases are read-only presentation peers for greeting UI; the
player is not one of them (see [published player dependencies](#published-player-dependencies)).

### Read-only sequence and action queries

`dw4_modelctrl_action` returns the current Action2 data name while the model is
active, separately from `dw4_modelctrl_sequence`'s SQ_* program name. Neither
query advances the owner. The normal-engine SDL fixture can log both with actual
engine/node clocks, active/drawable state and opacity around root lifecycle
boundaries. Its shared message-window OPEN02/CLOSE02 durations lie inside measured
retail snapshot intervals. Source paused reads can stop mid-update and therefore
do not prove completed-frame pose ordering.

## Simulation and windows

The session samples model clocks before timed SD and DM, then advances object
models after DM at the model-manager boundary. Queries and rendering never tick
controllers. Holding the simulation withholds both sampling and model updates;
resumption uses the existing pump's discarded host-time backlog. Commands started
on scene re-entry use the current session clock rather than a fresh zero clock.

The five greeting models own their actual NDMW 820 sequence/action programs:
`i_messwn`, `i_talkwn`, `n_digilffic`, `i_messky` and `i_talkky`. Each model switches
from the greeting adapter to command ownership when it first receives
an accepted SD command. Their rendering samples those same Action2 clocks, and
models can open, wait, close or disappear independently. TEXTCTL and SELECTCTRL own
script-commanded text and page completion; see [dialogue services](dialogue-services.md).

The message window's SQ_OPEN contains an initial zero-length OPEN action before
OPEN01; talk-window and portrait OPENL/CLOSEL programs have their own Joint waits.
Their close programs jump to SQ_ERAS. Under the deterministic regression clock,
OPENL reaches SQ_WAITL after 17 samples through the recovered strict joint/timer
arithmetic. The unchanged greeting adapter retains its 16-update opening.
The checks preserve that distinction; no whole-manager latency parity is claimed.

## Active model freezes for STATUS

Native MODELCTRL accepts ONFREEZE/OFFREEZE on generated instances and ignores
both commands on inactive slots. The original enum table at `4c58f0/4c5980`
assigns indices 20/21; `396a80` checks RAM +20 and Work presence, publishes
animation rate zero/one through `3a84a0`, and changes Work `_isOnFreeze` (+69).
The object update at `395b50` skips control/AI while that flag is set.

The native owner holds its sampled model clock and skips AI, movement, sequence
and Action2 advancement while frozen. Menu controllers generated after the
accepted freeze keep separate, running clocks. Repeated sample/tick calls at the
same timestamp do not accumulate a second hold. Resumption excludes held time
rather than delivering catch-up movement, expired waits or AI choices. Removal
releases the native freeze state; a fresh instance has independent hold history.
Queries and renderer snapshots do not tick.

Thirty-two independent original-window lifetimes compare held/resumed model
sequence and animation clocks with an uninterrupted reference whose clock omits
the held interval. They also verify that a newly generated menu opens while the
world instance stays held. The actor, prepared-controller and complete
four-player STATUS-root checks pass with freezes in place. Eight active/inactive command admissions
execute original `396a80`, including FPR rate zero/one publication; property
lookup, enum parsing and animation hooks are controlled leaves. The raw enum
names/indices are checked directly. These checks do not compare complete original
animation-manager freeze clocks, rendered poses or audio/generator behavior
(finding [#807](../../docs/findings/findings-0751-1000.md#f807)).

## Retail subcommand phase and node locks

HITBOX executes `399d90` / `3998f0` / `399e20` over its actual arena
subcommands. Each model update adds `beSystem._frameTimeF` to `_runFrame`.
The first update reaching `_startFrame` sets `_isOneSet` and emits once,
even when it crossed `_endFrame`. Subsequent updates emit only while
`run < end`; expiry releases the entry, compacts the list and clears its tail.
The pass snapshots the entry count. Queries never update or emit; a callback
that changes the source sequence stops the old traversal while its current entry
is retained. Recursive ticks or destruction of the active owner are outside the
callback contract.

System frame time comes from `3a0020`: signed wrapped world-nanosecond delta,
converted through the original software-conversion boundary and divided by
16666667 with the EE float model. It has neither the named Frame
timer's 2^18 ns quantization nor its three-frame clamp. Managers, lobby player
and specialized UI owners supply one shared value per pass; fresh/inactive slots
do not accumulate time since creation. A frozen model skips the pass, and the
session pump withholds ticks during pause. The standalone model tick is a
convenience sampler; its first update supplies zero elapsed frame time.

Combat installs synchronous model sinks. The world samples the combat service's
session clock and player bindings before model updates. Delivery therefore runs
after waits and MUTEKI, before the floor response; there is no later
volume scan. Typed health/identity is published to callback transports before
delivery; deliberate callback edits are imported afterward. The contact body
retains its first projection for a session timestamp, following `3908e0`;
pose publication does not invalidate that same-frame cache. Individual source
models and combat can detach in either teardown order, while the registry,
records, databases and other borrowed services outlive gameplay callbacks.

The node attachment branch of `395b50` reads Work `_isPosLock`,
`_posLockNode` and `_posLockOffset`, retains the source node, copies its matrix
and applies `190a50` local translation to all four translation lanes. This
preserves scale/shear/W and skips movement-channel advancement. A parent facade
may close first: its retained node supplies the last pose until unlock or child
teardown. Sequence changes retain the lock; REMOVE and close release it.
Explicit MOVETRANS still publishes its requested pose immediately; the next
locked update follows the parent again. HITBOX's `_isPositionLock` field has no
active start/update/finish consumer; it is not an independent world-space lock.
Named-model/bone and track locks are described under
[effect, sound and attachment services](#effect-sound-and-attachment-services).

`check-modelsubcom-retail` covers 520 pulse/list states, 136 System-frame
samples, 128 attachment matrices and 370 producer payloads against
original instructions. Allocation, delivery and long conversion remain controlled
leaves and arithmetic uses the repository's modeled EE FPU. Native checks cover
source replacement, freeze, no query delivery, authoritative callback transports,
parent retention and both callback-owner teardown orders. These checks do not
establish full-scene manager order or complete combat/renderer parity. See
findings [#2738](../../docs/findings/findings-2501-2750.md#f2738)–[#2740](../../docs/findings/findings-2501-2750.md#f2740) and
[combat boundaries](combat.md#hitbox-scheduler).

## Effect, sound and attachment services

Work's subcommand list contains actual `beModelCtrlSCEffect`,
`beModelCtrlSCSound` and `beModelCtrlSCHitBox` records. MODELCTRL `SETEFFECT`
and `SETSOUND` decode the SD string transport into copied typed
operands. All entries use the shared System frame accumulator and first-start
rule. Effects/sounds inherit the constant-true subsequent update (`36f8b0`);
they neither repeat PLAY/GENERATE nor query backend completion on later ticks.
An unsuccessful or non-retained start drops its entry without calling finish.
HITBOX queries filter the mixed list, and HITBOX `AllClear` removes only that
class. Sequence/REMOVE clearing follows `399f20`: finish every sound/hitbox,
finish an effect only when `_isSeqDead` is nonzero, then release every entry.
Class clearing follows `39a130` and finishes/removes each match immediately.
Callbacks retain each entry and its owned strings through source replacement.
Recursive finish of the same list is rejected by a native guard.

### Effect generation

The prepared manager supplies the effect leaf. `FIND_SPACE` chooses the first
inactive owned RAM in accepted info/slot order, writes `_geneRamNo`, and
GENERATE selects the requested sequence. Effect/player-bullet/enemy-bullet
receivers apply `396340`'s parent-relative transform and inherited hit-parent
name/slot; ordinary receiver kinds retain their ordinary creation path. Follow
retains the source node and local offset. Initial XYZ rotations are radians,
applied locally before the sequence begins. Later following copies the parent
and offset again, as the original node-lock branch does. A sequence-dependent
entry keeps the generated slot identity and requests `SQ_ERAS` on finish.
Activity remains set until the child's next unfrozen update dispatches REMOVE;
the inactive-slot search cannot reuse it early. A fire-and-forget effect survives the producer's sequence change.
Manager close removes all owned models while every sibling still exists,
then releases models and retained track resource closures.

### Sound

SCSound receives a full signed 64-bit service token and the authored sound type.
`399c50` retains only a nonzero, non-minus-one token of type four. Finish sends
`SOUND VOLUMECTL DOWN` for that token; it does not issue STOP. The prepared audio
adapter assigns voice-generation tokens and ignores an old token after voice
replacement. DOWN requests the recovered ten-frame fade. The native
linear fade adapter advances from its supplied session clock; held simulation
time holds that fade. VOLUMECTL2 uses the same clock connection. Media device
time and PCM cursors remain independent. See
[audio bounds](audio-playback.md#model-subcommand-sound-ownership).
Gameplay stages prepare their whole sound-pack catalogue by record name
([stage catalogue](audio-playback.md#stage-sound-catalogue-and-the-gameplay-set)).

### Named-bone and track attachments

MOVERL reads its authored model/bone names. `JOINT` looks up TRC for the
same RAM slot, retains `beModelCtrlInfoDataTrc`, and copies the recorder's
64-byte `_mvm` at +96. It does not read the unrelated +32 payload. The prepared
lookup imports an authored TRC closure when present and samples its recorder
from a private scene-node copy at the source Action2 clock; a recorder absent
from that graph fails explicitly. The resource closure outlives every retained
lock. Other MOVERL names store the source model/bone names in Work and resolve
the same slot on each model update. Bone lookup uses the owning Action2
animation database and the skeleton/motion/blend backend, then computes
`local bone * source node` with `1906d0`'s arithmetic/order. Missing/inactive
receivers or missing bones retain the last matrix. Queries do not advance
model clocks or mutate the prepared scene. MOVE/MOVEEX/MOVERL release the lock
gate and recover the current facing before their next movement request; retained
references are released on overwrite/unlock/REMOVE/close.

An authored TRC scene has not been used for an end-to-end retail trace;
the recorder branch has a controlled typed-record test.

### Checks

`check-modeldependencies-retail` compares 768 mixed activation and
sequence/class-clear states, 64 full-width sound-handle states, 256 producer
payloads, 256 full matrix compositions and four pending-erase gates against
original instructions.
Virtual media/receiver, allocation and list leaves remain controlled; the VU
matrix fragment uses the repository's modeled EE float arithmetic. Native checks
cover mixed diagnostics, entry/string lifetime through callback replacement,
sequence cleanup, type/sentinel admission, recorder matrix selection and retained
references, missing bone/track results, an original heal effect and Digi-Elf
bone lookup from mounted assets. Dummy-device checks cover fade progression,
held clocks and stale voice tokens. ASan/UBSan cover mixed records, prepared
asset dependencies, retained callbacks, contact cache and field
teardown/attacks, including pending erase and inherited facing. See findings
[#2741](../../docs/findings/findings-2501-2750.md#f2741)–[#2743](../../docs/findings/findings-2501-2750.md#f2743).

## BIND movement consumer

Active PE models apply BIND to Work's movement list after control/AI and
before movement. Horizontal/turn channels stop outside the ten damage sequences;
vertical channels and HITBOX emissions remain eligible. The enum return status,
startup constants, timer boundary, instruction oracle and remaining status-order
limits are documented in [combat](combat.md#bind-movement-and-enum-gate).

## Published player dependencies

`dw4_lobby_publish_player` binds its player model to the prepared scene's
effect, sound, named-bone and track services before publishing the PLAYER and
MODELCTRL receivers. Both the normal created-card lobby and connected hub/field
runtimes use this entry point. `dw4_controllers_bind_model` claims the player's
unbound RAM info/manager identity and adds a service-lookup peer. It does not
register another SD receiver, append to the presentation roster, or tick/draw the
player. The lobby remains the player owner. Duplicate live identities and models
already associated with a manager are rejected.

The service table includes a release notification. Replacing or detaching it
finishes retained effect/sound entries in mixed-list order through the old
callbacks and releases
named/track attachments before releasing the context. Pending entries are
removed without PLAY/GENERATE. HITBOX entries and model activity are preserved.
An identical binding is a no-op. Replacement during a dependency callback,
finish traversal or release notification is rejected. A finish error still
completes detachment; it leaves the proposed new context with its caller and
reports failure. This is native ownership policy around the recovered event
handlers, not a claim that retail uses host callback tables.

The scene detaches specialized peers while its generated models, SD registry and
borrowed media still exist, then removes/closes its owned models, then releases
pose/track resources. A model closed first clears its peer and borrowed RAM links
before its records disappear; subsequent named lookups report it missing.
A manager closed first clears the surviving player's bindings and borrowed
info/manager references. Prepared infos, SD and media must outlive manager
cleanup. The notification runs before model record
release. Cloned model instances do not inherit another instance's service table.

Normal prepared scene graphs omit actor skins. Named-bone resolution lazily
loads a private actor pose graph from the receiver's own Action2 pack and database,
then shares it across that receiver's cached motions. It neither changes the
presentation roster nor advances simulation. The graph and animations live until
scene teardown. The local-bone × source-node arithmetic and missing-source
behavior are those of [named-bone attachments](#named-bone-and-track-attachments).
A direct-node attachment takes precedence over
named/track fields; original MOVERL does not clear that retained node.

`check-modelsubcom` covers replacement, pending/live cleanup, sound DOWN, release
ordering, reentrant rejection, finish failure, preserved HITBOX entries and model
close. `check-controllers` exercises an original Dorumon player, heal effect,
prepared cursor sound and RArm04 lookup with ordinary skin-omitting prepared
graphs. It verifies unchanged presentation counts/clocks and both close orders,
with arena baselines. The field `hitschedule` test exercises actual player
publication and leaves a generated effect alive across runtime teardown; it also
runs under ASan/UBSan. The related retail checks cover mixed-list detach order.
See finding [#2745](../../docs/findings/findings-2501-2750.md#f2745).

## Camera and layers

The title retains its static `entry` camera service. Main Lobby registers a
scene-owned CAMERA receiver for `camsp0101`, resolves its `beCameraCtrlInfo`
data reference and reads `beCameraDemoData._endTime` (4,000,000,000 ns).
`SETDEMOCAMERA` resets the demo clock; `ISDEMOCAMERA` reads unfinished demo state;
`ONFREEZE`/`OFFREEZE` refresh/hold the recovered camera clock;
`SETBOXCAMERA` selects the authored box rig. Selecting the box rig does
not advance windows or material timers. Rendering evaluates the demo path at the
same sampled time, holding its final sample after completion. Other demo paths,
optional query modes and a general camera solver are unsupported.

LAYERCTL SWITCH retains authored layer order and slash-separated CLR/SET/FLIP
mask changes, including recovered ALL behavior, timed publication and scoped
cancellation. Normal lobby actor/player/fade/portal rendering samples owned controller
state. General graph traversal remains separate. The lobby startup additionally
supports SWITCHCTRL ALLON/ALLOFF and retirement of loading attachments; see the
[lobby contract](lobby-gameplay.md).

## Authored WN model rendering

`modelview.c` prepares screen-space triangles for the native WN-layer model
instances. It resolves each same-pack Action2 root, model RAM branch, authored
layer attachment, mesh and indexed image. Standalone library images are included
in the texture catalogue; local image identity takes precedence over a named
library fallback. Missing textures produce an explicit model/mesh diagnostic and
an obvious magenta/black checker. Invalid mesh preparation fails.

Drawing observes active/HIDE eligibility, native layer masks, instance position,
Action2 node time, descendant switches/LOD, UV translation and authored color/
blend state. It copies node state into reusable sampling storage before applying
pose clocks, preserving all prepared scene nodes and clocks. Triangles and images
remain owned by this renderer; source packs, prepared objects and controllers
must outlive it. The renderer does not tick controllers or the scene. Templates
start hidden; generated instances select their own top-switch RAM branch instead
of mutating that immutable template mask.

Prepared STATUS checks render the root for all four players. They verify
repeat-draw equality, every controller clock and unique prepared scene remaining
unchanged, and zero draws while layers are disabled. The captured root includes
authored panels/portrait/cursor and original fonts with production records.
No retail pixel parity is claimed from those captures. UI layers are explicitly
activated in this prepared harness. Source nodes are sampled through private copies. WN-only
drawing is not a general world or actor renderer. The complete menu tree
passes its separate controller/record contracts (finding [#808](../../docs/findings/findings-0751-1000.md#f808)).

### Projection, depth and color masks

Replay honors inherited pack view, projection and viewport attributes.
Perspective STQ and clip handling are covered by the
[STATUS root projection comparison](status-views.md#authored-wn-projection-and-reciprocal-q).
Both sampled corners are resolved with original mode-three XY normalization and
VU viewport conversion. Ordinary draw remains read-only; observed reference
clocks are diagnostic only.

WN draws carry hardware depth, GEQUAL/ALWAYS and write policy through CPU/GPU
presentation, with model linear and font nearest filtering. The frame clears UI
depth once before model/text batches. Original disabled depth state bypasses
comparison and suppresses writes. Legacy draw constructors initialize the added
fields.

Settled menus have prefix occlusion by their opaque background. The original
fullscreen quad masks its color writes (FRAME.FBMSK=ffffffff). The scene loader
and native publication carry nearest-ancestor channel masks through CPU/GPU
rendering. Alpha/depth behavior and the UI bridge are checked; all seventeen
observed-clock menus match the source mask.

Seventeen single-interval comparisons include hardware depth and filter state,
and all seventeen ordered comparisons pass with the projection normalization.
Live phase comparisons remain open.

## Authored transform interpolation fractions

Native `igTransformSequence1_5` evaluation uses the original `1df040`
fraction: shift `(now-first)` and `(last-first)` by eighteen bits separately,
keep each low unsigned 32-bit tick count, convert with EE arithmetic and divide.
Shifting timestamps before subtracting is different. A duration below one tick
returns zero, matching the original denominator `< 1e-6` branch. The explicit
degree-XYZ camera adapter retains its separately validated timeline.

`check-sequencefraction-retail` executes the complete original helper for 876
controlled adjacent-key queries, covering signed starts, odd remainders, tiny
durations, unsigned tick conversion and low-word rollover. The native fraction
bits and original selected indices agree. The two alternatives fail:
full-nanosecond division on 703 cases and separate timestamp shifts on 547.
This verifies the fraction
boundary, not the surrounding loop, cache or interpolation-method dispatch;
the shared EE FPU model retains its documented hardware-measurement limit.
An actual scene translation test checks use of this fraction. Independently
read paused retail background matrices agree to a few millionths with this
fraction (errors were up to 0.00048 without it). All seventeen menu submissions pass
the unchanged geometry/UV/RGBA/Q allowances in a single dump vsync interval.

## Model fade presentation

`modelfade.c` recovers the FADESET IN/OUT value/direction arithmetic from
`376930/376680`, including the requested limit, fractional duration, initial
one-frame update, repeated timestamps and capped frame deltas. Each native model
owns its fade state, advances it only during an unfrozen model tick and exposes
opacity through a read-only query. Model replay multiplies authored alpha by
that opacity. HIDE remains separate eligibility. Completed IN restores ordinary
material eligibility; OUT retains zero opacity until REMOVE retires the instance's
default attributes.

5,080 fade value/direction steps compare against original `376680` with frame
delta and attribute operations controlled. An actual i_fadewn01 BLOUT30/BLIN30
owner verifies start/midpoint/completion, repeated alpha queries, freeze holds and
resumption without catch-up. The complete four-player root/render checks cover
the same fade state.

## Action replacement restores visibility

REMOVE also retires presentation opacity. Original `377d38..377f20` releases
the node's default attributes, clears their entries/count, clears the instance
switch bit, releases Work, resets the node and clears the active byte. Native
`dw4_modelctrl_remove` clears `fade_present`, so a later instance whose action
has only JOINTSET cannot inherit the previous OUT's zero opacity (Key/DISK
reopening depends on this). Twenty-one original fragment cases check zero,
scalar and unrolled attribute counts, masked reference counts, array canaries,
switch/Work retirement and inactive writes; allocation and reset are controlled
leaves. Prepared FOLDER tests and exported captures require positive panel alpha.

The STATUS cursor's authored OPEN uses FADESET HIDE, while LINESL00 and WAIT00
contain JOINTSET and no IN command. Original Action2 message dispatch `377990`
restores the addressed instance's switch bit before comparing requested/current
actions. The active branch `378268..3782ac` performs this even when no new
component program will be selected. Native model ACTION dispatch clears its
presentation HIDE flag at that same boundary, before the same-action shortcut.
HIDE remains effective until the next accepted ACTION; JOINTSET itself does not
restore visibility.

`check-actionvisibility-retail` executes 512 original HIDE/active-ACTION pairs
across 128 slot indices and four starting word patterns, checking all four words
and the original Work +16 write. It executes the two switch-bit fragments;
receiver decoding, allocation and component replacement remain outside this
verifier's scope. Prepared STATUS roots separately require the selected player's
actual cursor to be drawable. The original assembly remains the instruction
evidence.

Reference exports include pack/id and active/drawable state. Use the optional
`--root-only` final argument to `test_statusviews` for a fresh root fixture,
avoiding presentation peers left by preceding isolated submenu tests. This mode
reports only its own four-root/routing/close coverage. Full authored-view checks
remain a separate run. See [root comparison](status-views.md#retail-root-rendering-comparison).

## STATUS pad trigger, repeat and direction delivery

`padrepeat.c` implements the bePadData held/trigger/repeat countdown used by
both stick and digital channels. Changed input publishes new rising bits and
resets the first counter; unchanged input decrements the counter, publishes the
held mask at zero and reloads the repeat interval. The constructor at 39ae50
supplies first10/next6. Native STATUS paging receives trigger OR repeat. Digital
right/left carry 0x20/0x80; shoulders retain 0x400/0x800 rather than being
misrepresented as paging directions. Counter updates stop with simulation holds.

The host menu-axis values feed the recovered 39b110 radial/sector rules. The
constructor supplies a radius derived from
0.4 and angular overlap pi/4; sector comparisons retain their original strict
versus inclusive boundaries and EE float arithmetic. Partial deflections and
diagonals are therefore classified by sector rather than by independent 0.5
axis thresholds. Host
`atan2f` and square-root evaluation supply the mathematical leaves; square-root
results are adjusted to the EE toward-zero model.

`verify_padrepeat_retail.py` compares 1944 held-mask/countdown/interval states to
original 39af10 instructions, including unchanged/changed/released input, zero
intervals and signed countdown wrap. `verify_paddirection_retail.py` executes
1764 radial/sector cases, including
neighboring angle bit patterns, against original instructions with atan2 and
vector length controlled. Cartesian dead-zone/cardinal/diagonal probes also
pass. The SDL live route drives STATUS at about 0.45 axis deflection and
accepts the weapon swap/close/reopen sequence. Normal boot, HUD restoration and
layer masking pass the STATUS route; all four HUD fixtures pass ASan/UBSan with
leak detection disabled. These checks establish sector
logic and live delivery, not bit-identical transcendental-library behavior at
every possible input boundary.

## Shared STAGECTL pad-input ownership

The session owns the pad manager's disabled byte through a registered
STAGECTL/PADINPUT service. ENABLE clears it, DISABLE sets it, and STATUS returns
it. Missing/unknown optional values leave it unchanged. Raw sampling/repeat
updates continue; disabled getters choose the neutral fifth pad rather than
changing or stopping the real pad records. STATUS entry routes ENABLE through
this owner, and dialogue/page input plus Start admission use its getter. There
is no menu-local input boolean. Other stage commands require their
separate scene owners; this service advertises PADINPUT only.

`verify_stageinput_retail.py` compares 56 command flag/result and pad-slot cases
with original 3cd810/39b810, with enum/context/argument decoding controlled. The
SDL live route disables input while the root is open, sends confirm/cancel and
checks that the root stays at its input top; ENABLE then restores the ordinary
weapon-swap and two-close route. The native getter safely returns neutral for
negative player ids instead of retail's unchecked negative-index read.

## Validation

From `port/`:

```sh
make check-controllers
make check-script
make check-scriptservices
make check-stageobjects
make check-modelsubcom
make check-retail
make check
```

`make check-retail` includes `check-modelsubcom-retail`,
`check-modeldependencies-retail`, `check-actionvisibility-retail` and
`check-sequencefraction-retail`; the full native run is `all check check-retail -j4 -k`
or `make -C port check -j8`.

`test_controllers` loads original title/window model programs, checks opening,
wait/close/removal, empty active sequences, failed replacement, shared-program
lifetime, independent portrait rendering and repeated queries/draws without
clock changes. A test-owned Lua 4 source program drives delayed GENERATE and
DM completion waits through the real window service; teardown cancels queued
creation before releasing its receiver. Camera checks cover freeze/resume,
inclusive completion, box selection and demo restart. Four alternating prepared
scene reloads check the 190/199 slot rosters, ownership, inactive selection and
coordinated teardown. Original title first.lua tests, layer-mask tests
and full boot/greeting regressions, including the 15-page greeting UI test,
remain in the suite.

`verify_controller_slots_retail.py` runs the original acceptance instructions for
10 accepted/rejected roster cases, including 0/1/2/12/64 RAM rows. Class lookup,
list insertion and per-instance initialization are controlled leaves. The
camera, Action2, model wait, registry/SD, DM and layer retail checks establish their
respective boundaries. These do not establish complete native model dispatch,
resulting gameplay or visual parity against the running game.

Run conditions and limits:

- Sanitizer runs (controller, Lua, complete-root, model/controller/contact,
  field publication/effect teardown) use ASan/UBSan with `detect_leaks=0` and
  `halt_on_error=1`. Leak detection is unavailable under the runner, so the
  model and peer tests assert explicit arena baselines.
- The live SDL tests run with `SDL_GAMECONTROLLER_IGNORE_DEVICES=<vendor>/<product>`
  (the virtual-pad ignore override). The SDL disconnect assertion fails while a
  uinput virtual-pad helper is present; it passes with that helper stopped and
  physical controllers excluded. No input/runtime timeout is changed for this.
- Live SDL/Vulkan presentation captures are 99.998% identical (mean delta 0.004).
  Live STATUS input/restoration, hardware STATUS comparisons, live GPU rendering
  and explicit GPU draw-failure handling are part of the suite.
- Optional pose/fog checks skip without their private live captures.
- These checks leave the matching build untouched: `check typed-check link`
  keeps its baseline and a byte-identical relink. No matched code bytes or
  full-scene retail parity are claimed from this subsystem's checks.
- Physical-device/audio and full-frame parity remain explicit acceptance limits.

## Open items

- Model programs: general actor Action2 components and full scene renderer
  traversal. Unsupported programs report errors.
- Camera: other demo paths, optional query modes and a general camera solver.
- Freezes: complete original animation-manager freeze clocks and rendered poses
  are not compared.
- WN rendering: complete material and UV-matrix parity; live phase comparisons.
- Fade: non-default attribute replacement/material interactions need broader
  rendering verification.
- Effect/sound/attachment services: full sound type/priority/pan and gain
  behavior, all effect/particle/material programs, exact rotation trig,
  complete animation combiners, and full retail recorder traversal/order with an
  authored TRC end-to-end retail comparison. Other specialized UI/gameplay
  owners need their own integration before consuming these messages; live co-op
  service publication is open.
- Combat-facing limits: support admission, projectile stand-ins, complete-game
  and whole-frame presentation acceptance are unchanged by these services.
  Arena phase P3 of the [arena object model](arena-object-model.md#open-items)
  remains open.
- The broad retail target's older host-database fixture is separate harness work.
- Windows and physical Steam Deck validation.
