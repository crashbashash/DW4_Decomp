# Original Lua execution

Normal created-card Main Lobby login uses original start/first scripts and
scene-owned actor/player movement, collision, motion/opacity publication and
restoration; see [the lobby contract](lobby-gameplay.md) for evidence and scope.
General gameplay and whole-frame parity are outstanding.

The native host includes Lua 4.0.1, loads original named bytecode from igBinary
packs, and exposes the recovered `be` method names through a typed native-call
boundary. Normal boot collects each scene’s ordered Lua-info rows and executes
original `func.lua` and `boot.lua` in a fresh VM after authored file-list
collection. Title audio executes the original
`snd_j_startback.lua` event to
select and play the entrance sound through the native audio service.

This is **in-progress integration**. Normal front-end scene orchestration
still uses its existing bounded adapters. The DM scheduler
is attached to the live 60 Hz session pump; general scene/gameplay script services
remain outstanding. Registering all method names does not implement all
116 retail overloads. No complete-game or resulting-behavior parity is claimed.

Scene-owned text resolves named font faces and their atlas references,
owns original-code glyph geometry, and follows authored font transforms,
switches and layer visibility. Native typed Unicode TEXTSET/REPLACEUNKNOWN
interfaces are available to engine owners; they do not introduce Lua userdata
syntax. See [text contracts and validation](dialogue-services.md).

Character-menu message/legend publication executes original NDMW 806
`txt_mem.lua` in a display-owned Lua 4.0.1 VM. Its TEXTCTL callbacks select
localized Unicode, authored font rows and alignment. The existing character
adapter still owns phase selection and dynamic upper fields; this is not
general Game Start controller execution. Thirteen retail glyph comparisons
and high-resolution GPU fixtures validate the scoped presentation; see
[main-menu text callbacks](main-menu-fidelity.md#lower-message-text).

## Runtime and bytecode contract

[Vendored source and alterations](../third_party/lua401/README.md) identify the
upstream archive, SHA256, original license and each host alteration. Make builds
the core and base/string/math libraries into both executables and their checks;
there is no system-Lua dependency or modern-Lua conversion.

The original chunks require four-byte instructions and serialized string lengths
and eight-byte numbers. On a 64-bit host, Lua retains full host pointers internally;
those pointers are never stored in recovered four-byte arena references. The
runtime changes instruction storage to `uint32_t`, reads original serialized
size fields as `uint32_t`, and exposes the existing protected parser as a
load-only API. The VM's opcode meanings, signed bias, branches and truthiness
remain stock Lua 4.0.1. Numeric zero is truthy; native boolean queries remain
numeric rather than being translated to modern-Lua booleans.

`dw4_script_load_pack` follows actual pack references:

```
beLuaData.name -> beLuaData._dataObject
              -> beLuaDataObject._dataSize / _data
              -> referenced memory pool block containing one Lua chunk
```

No script-name/magic scan selects executable content. Chunk lengths and nested
prototype counts are preflighted, and the protected parser compiles every pending
chunk before publishing replacements. A failed pack load preserves the previous
named closures. Loaded closures own their constants; the pack mapping may close
before execution. Loading does not run a chunk. Logical `dofile` resolves loaded
script names rather than the host filesystem. Each VM has independent globals
and locked chunk references; releasing it frees those references and its state.
The legacy VM is for trusted original code, not an untrusted-mod sandbox.

Finding **[#785](../../docs/findings/findings-0751-1000.md#f785)** records the signed-operand bias:
`MAXARG_S = 33554431`, not `33554432`. Retail PUSHINT at
`0x00258340..0x00258364` adds `0xfe000001` to `ins >> 6`. A decoder that uses
33554432 makes all signed literals one too small, has to compensate jumps with an
extra increment, and produces an apparent numeric-for step of zero.
Generated source remains
analysis material; execute original bytecode. Original title bytecode passes
with stock jumps, bounds and steps. The dump/decompiler, all 5,291 chunks,
index, cleaned tree and flag tables are regenerated with 33554431 ([#787](../../docs/findings/findings-0751-1000.md#f787)); the [numeric audit](../../docs/engine/lua-numeric-audit.md)
records affected progression evidence.

## Native calls, command groups and events

Synchronous NPC hit callbacks have an isolated matrix/kind/box/source-RAM
context for original position/rotation strings and damage-turn methods. Original
Central NPC entry executes through the authored hit-body consumer in headless
tests. Live Cross/receiver wiring and dialogue/service closure are described in
[NPC interaction contracts](npc-interactions.md).

[`script.h`](../include/dw4/script.h) defines nil/number/string values and a native
service callback. `be:method(...)` strips only `self` and forwards the complete
argument list, including explicit nil, negative IDs, literal delays and string
lengths. Generated method names come from the recovered retail descriptor table;
`tools/gen_script_api.py --check` detects drift. Missing or failed services stop
the protected script call and report the method. The original `_ERRORMESSAGE`
can call `MsgBox`; unsupported error-handler services cannot recurse indefinitely.

[`scriptengine.h`](../include/dw4/scriptengine.h) owns the native DM command groups
and connects recovered front-end state for ordinary flag bytes, counters,
difficulty, camera-folder clear bookkeeping and difficulty maximum. Flag reads
preserve the retail unsigned-byte result; flag 1000 routes to session services.
Other native methods route to the supplied engine callback and fail if absent.
This state bridge inherits the current front-end's storage limits; it is not a
replacement for recovered gameplay/save ownership.

Scheduling behavior (finding **[#786](../../docs/findings/findings-0751-1000.md#f786)**) is explicit:

- `DMsetSD` copies a command into the building group. Strings outlive the Lua call.
- `DMchkSD` copies a **while condition** into that group. `!=0`/`==1` waits while
  the query is true; `==0`/`!=1` waits while it is false. An absent receiver blocks.
- `DMrun` publishes the group and returns immediately. Lua does not yield.
- A simulation tick snapshots published groups and visits newest first. Each
  group advances in order until blocked, retaining its cursor for the next tick.
  Completed groups retire after dispatch.
- Positive command delays go to the engine service unchanged. The service owns
  timed messages and recovered timer arithmetic; DM publication is not a clock.
- `DMsetLua` runs a loaded named chunk when its command is reached. Groups it
  publishes become eligible on the following scheduler tick.
- Draws do not tick scripts. Pausing a session requires withholding simulation
  ticks and holding the engine-service clocks together.

Services receive `sd` for command application and `querySD` for receiver queries.
The session routes these through the native receiver registry and timed
message queue described below. SOUND delegates to the existing title audio
service. Prepared model slots, command-driven greeting windows and title/lobby camera services connect here; see [Scene controller services](controller-services.md). General model programs and stage-transition services remain outstanding.
DM switch/case groups and subwindow-aware counts run natively ([#788](../../docs/findings/findings-0751-1000.md#f788));
see the recovered rules below. General material/model/bullet/player context
still requires an engine service. `dw4_scriptengine_run` latches failures, discards unpublished commands and
prevents further ticking. The operation owner must close/recreate the engine
as part of Retry/Back; globals and native side effects already performed are not
rolled back. General script-error Retry/Back remains outstanding; scene-boundary reset
coordinates SD, Lua and DM as described below.

## DM switches and counts ([#788](../../docs/findings/findings-0751-1000.md#f788))

`DMswtSD` queues a receiver query with four or five arguments. The retail
builder has one switch latch: nested switches are ignored, `DMcase` outside a
switch is ignored, and `DMrun` leaves an unfinished switch unpublished until
`DMswtEnd`. An integer query selects the first matching `DMcase`, including
negative and zero values. There is no fallthrough: the next case skips through
the end marker. No match or a missing integer result selects no arm. Waits in
a selected arm retain the cursor and do not rerun its switch query on resumption.

`DMgetCount` returns the number of published groups, excluding the building
group. When that count is zero, it queries `SUBWND`, nil name, id 0, `ISRUN`;
a missing result returns zero, a nonzero result byte returns **-1**. Services
must implement that query rather than return an assumed window state.

`DMmsgBox(text, value)` queues an owned kind-6 record. Retail's scheduler jump
table skips kind 6; the native scheduler preserves that behavior. This does not
implement the separate original `MsgBox` error/retry UI.

The retail-instruction comparison covers five switch outcomes (signed, zero,
first duplicate, unmatched, missing integer result), kind-6 skipping and 24
published-count/window scenarios. Native fixtures additionally cover unfinished
switch publication, ignored nested/outside markers and a blocked selected arm.
Receivers and integer/window results are controlled service stubs; general scene receiver context, dialogue services and full window-manager latency remain outstanding.

## Receiver registry and timed messages

[`scriptservices.h`](../include/dw4/scriptservices.h) and `src/scriptservices.c`
implement native receiver selection and engine-owned delayed SD commands. The
live session registers its SOUND receiver here; unsupported categories fail
with the category and method in the diagnostic. A missing receiver within a
registered category produces nil, so a DM wait retains its cursor.

The ordinary receiver path follows retail `0x0038d860` and `0x0038e060`:

- Categories match exactly. Names match exactly when both sides have names;
  nil on either side matches every name. Empty strings remain distinct from nil.
- Selector ID -1 or receiver ID -1 matches every ID. Selector -2 selects the
  first inactive receiver, independently of its ID. Ordinary dispatch also
  reaches inactive receivers, matching the default cleared message-context mode.
- Matching receivers run in registration order. Queries expose the first
  non-nil callback result, as DM reads result slot zero. The original receiver
  virtual handlers' interception and result-array creation still belong to each
  manager; the host callback represents that boundary.

The queue follows `0x0038e8f0` and `beMessenger::vfunc_27` at `0x0038d0a0`.
Scheduling computes `world_ns + delay * 16666666` with signed 64-bit modular
arithmetic. Expiry is inclusive. Earlier deadlines run first; equal deadlines
retain publication order. Positive DM delays schedule messages; zero/negative
DM delays dispatch immediately (`0x0037ee40`). Direct `sd` calls with a numeric
delay schedule even zero/negative values. The five-argument numeric-delay
overload is distinct from the five-argument optional-string overload.

Messages copy their command payload, including string lengths and nil values;
the delay becomes the deadline and is not forwarded again at execution.
They resolve receivers at expiry rather than retaining a borrowed receiver
pointer. The tick samples world time and dispatches messages before DM, so a
completion query can observe the message's effects on that tick. Holds withhold
the service tick and preserve deadlines. A timed-service failure stops the
simulation before DM and latches the diagnostic until the owner recreates it.

Host lifetime tokens are separate from recovered four-byte references. Removing
a scope cancels its queued messages and unregisters its receivers; cancellation
alone preserves registrations. The live title cancels pending session messages
before replacing audio on lobby entry or title re-entry. Lobby-owned DM groups and named chunks share scope teardown (see below).
General stage event contexts and coordinated DM/SD teardown still need integration.

Immediate dispatch snapshots registration tokens and rechecks their validity
before each callback. Registration/removal and nested calls therefore cannot
leave stale array pointers. The timed pass uses the retail reusable-list budget
(initially 32 records, growing when filled). It detaches the executing message
before invoking its service so cancellation is safe. Reentrant scheduling of
negative delays has a measured discrepancy documented below. Full retail
cached-selector mutation and non-default context modes are not established by
the controlled comparisons. Manager-specific
`SEARCH`/`FIND_SPACE`, optional `I<...>`/`L<...>`/`V<...>`/`F<...>` argument
decoding and multi-type result arrays remain outstanding; optional values reach
callbacks as their original encoded strings.

`make check-script-retail` also runs `verify_scriptservices_retail.py`:
35 nil/named/empty-name and signed-ID selector cases execute the original lookup
and dispatch instructions; 24 expiry samples execute original enqueue and update
instructions, including negative/zero delays, delay 240, inclusive boundaries,
and equal-deadline ordering. Allocation, string interning, list operations and
receiver handlers are controlled leaves. The comparisons establish this boundary,
not complete model/camera/window manager behavior or gameplay outcomes.
The DM oracle additionally checks negative, zero and positive delay routing
against `0x0037ee40`.

The original title `first.lua` runs through this registry and queue in both area
branches in `make check-script`. Its direct PADINPUT delay 30 expires at
500,000,000 ns; its DM PAUSEOFF delay 240, published at the controlled camera
completion on tick 3, expires at 4,050,000,000 ns. An explicitly requested hold after publication
freezes queries and expiry without catch-up. Receiver state remains controlled
in this fixture; normal title orchestration continues to use its adapter.

`make check-scriptservices` covers owned argument storage, receiver replacement,
scope cancellation, removal during dispatch, immediate reentrancy and latched
failure. These lifetime checks and the integrated script checks pass ASan/UBSan
with leak detection disabled because LeakSanitizer cannot run under the runner's
ptrace environment.

## Verification and remaining integration

From `port/`:

```sh
make check-script
make check-scriptservices
make check-script-retail
make check
```

`DW4_ROMS` and `DW4_ELF` override the usual private archive/ELF inputs. No game
bytecode or ELF extract is committed. The runtime test loads **5,291 original
chunks from 98 NDMW entries**, executes both title area branches, checks the
original flag-reset loop's actual IDs/zero values, named events, globals, numeric
zero truthiness, group reversal, next-tick event publication and error routing.
It also rejects every truncated prefix of a test-owned chunk and a staged pack
with a corrupted chunk header while retaining the previously loaded closures.

The retail oracle interprets **the original MIPS scheduler at `0x0037ed70`** for
six controlled ticks. Its ordered command traces match native execution of
original `first.lua` in both title branches, including blocked camera/sequence
queries, retained cursors, completion and forwarding delay **240**. Receiver
lookup, query responses and delayed-message services are stubbed identically on
both sides. This proves the tested scheduler behavior at that boundary; it does
not prove real engine timer expiry, model completion or rendering.

The full native `make check` passes on the development host. The script tests
also pass AddressSanitizer and UndefinedBehaviorSanitizer, including switches
and counts, with leak detection disabled for the runner environment. Live texture,
presentation, pose and fog checks retain their existing environment-dependent skips.

Digi-Elf arrival movement, actor action selection, label/control state and numeric
completion waits run through the scene-owned executor; see
[Lobby actor sequences](actor-sequences.md). Original actor-program command traces,
360 full channel states and 1,080 queries match controlled retail instructions.
Bound WPOS AIMAP programs acquire targets through the original guide callback
with per-instance map state and scoped HP/output commits. Prepared KIND_OBJECT slots
bind persistent scene-owned RAM/record/HP state, preserving waypoint progression
across regeneration and native HP changes during callbacks; see
[state ownership and initialization](actor-sequences.md#persistent-prepared-object-state).
WPOS patrol timers/control consumers are implemented. Enemy/player health
owners still need collision, renderer publication and status/menu ownership.
See [dialogue services](dialogue-services.md).

The remaining work is to implement the missing native services, load stage
libraries in recovered manager order, route model/material/trigger events with
original receiver context, and remove each adapter only after matched retail
input/state traces verify its replacement. Full waits/events across gameplay,
error Retry/Back, pause/transition ownership, and resulting gameplay/audio/visual
behavior still require retail comparison. Windows and physical Steam Deck
runtime validation have not been performed.

## Native scene completion queries

`src/titleservices.c` registers the eight named title models at slot 0 and the
title camera with the session SD registry. Lua generation/sequence commands and
`ISRUN`/`ISSEQNAME` share `dw4_title_host` state with the menu controller. Nil
selectors are expanded by receiver callbacks to their own model names; active
eligibility updates after a command and before the next DM tick. Model schedules
remain the bounded title implementation: this binding does not recover the full
retail MODELCTRL dispatcher or establish its exact completion latency.

The `j_startback` OPEN/WAIT and entrance fade schedules cover original
`first.lua`. In the integration test both original title branches wait on the
actual camera and model state, rather than tick-dependent query stubs. Under
the deterministic native cadence, camera generation occurs on tick 1, its first
sample on tick 2, the OPEN model starts on tick 62 and TITLE2 RUN is observed on
tick 271. The queued PAUSEOFF expires at 5,033,333,333 ns. An explicitly requested hold freezes
service and model state. SOUND, TITLE2 RUN, layer and input handlers in this
test are explicitly controlled leaves. This test does not render the whole
entrance or establish the retail manager latency.

The static title camera resolves `beCameraCtrlInfo entry`'s slot-7 data reference
to `beCameraDemoData` and reads its eight-byte `_endTime` (1,000,000,000 ns),
rather than assuming a duration. The existing scene loader supplies its actual
camera matrix. `src/cameratime.c` follows `0x0037a900`: no source means no update;
freeze refreshes the previous sample without advancing; the zero previous-time
sentinel supplies zero delta; signed deltas cap at 50,000,000 ns; inclusive
completion clamps at the authored end. Finished demos hold. Default
`ISDEMOCAMERA` corresponds to the demo type and unfinished mode-1 state checked
at `0x00379f18..0x00379ff4`. `SETBOXCAMERA` leaves this demo mode; the title view
is static, so this boundary adds no general box-camera solver. Optional query
modes, other camera paths and interpolation remain unsupported.

On lobby publication, the session removes title receivers and their scope-1
messages and registers the five greeting models at scope 2. Their `ISRUN` and
`ISSEQNAME` query the actual UI phase; queries and draws never advance it.
Window OPEN/WAIT/CLOSE names were checked against NDMW 820 model-controller
records, independently of Action2 names. A Lua DM wait observes OPENL's actual
16-update transition. Authored window creation/close commands have an independent model executor; SELECTCTRL and font commands run original message/choice helpers; SUBWND
completion has native prepared-slot/window-tree ownership; concrete status/menu gameplay and player records are still pending ([contract](status-menu.md)). See [Scene controller services](controller-services.md) for command ownership, simulation order and validation. These windows are not SUBWND and are not substituted
for its `DMgetCount` query. Scope-2 receivers/messages are removed before scene
teardown.

Normal boot registers these services; the title continues to run its existing
startup adapter. Promoting the title's full `first.lua` requires its SOUND overloads,
TITLE2 RUN/input/layer effects and rendering clocks to be connected together;
the current live audio service still implements the sound event's PLAY subset.
Lobby library loading is implemented, and the created-card lobby login runs its
original start/first scripts (see [the lobby contract](lobby-gameplay.md)).

Validation: `make check-script` runs both original title branches with real
completion queries, the window wait and scope removal. `make check-script-retail`
includes `tools/verify_cameratime_retail.py`: 100 original-instruction clock-state
and supplied path-time comparisons, plus four default query states. Matrix/path
traversal and demo-data type selection are controlled oracle leaves. This does
not establish full model/window/camera rendering or gameplay parity.

The native `make check` and `make check-retail` suites pass, as do the focused
frontend checks and ASan/UBSan execution of the
Lua/model/camera/window tests (leak detection disabled).
Optional live pose/fog comparisons skip without their private dump inputs.
No emulator playthrough or Windows/Steam Deck run covers this
service slice.

## Live simulation pump

`src/simulation.c` supplies exact rational 60 Hz simulation samples through the
recovered clock adapter. Host elapsed time determines due ticks independently of
presentation. Each tick stores world time, advances the supplied message/service
clock boundary, and ticks DM before the existing scene/model adapters. DM list
snapshot/reverse traversal and next-tick event publication remain unchanged.
This is host cadence policy; it does not reproduce variable EE Timer 0 samples.

Retail ordering is checked against two logo CLOSE savestates: the serial
scheduler has 35 managers, DM (`0x0037ed70`) at slot 8 and Action2
(`0x00378bc0` / `0x003778d0`) at slot 17. Reproduce from the repository root:

```sh
python3 port/tools/verify_simulation_order.py <logo-close-savestate>.p2s
```

Normal title initialization creates a session-owned script engine, loads the
authored title file list, executes original func/boot and loads queued assets,
then publishes `snd_j_startback.lua`
as a named DM event. The first simulation tick executes its original SOUND PLAY
through the audio service. The engine wrapper and native state persist, but the
published lobby handoff replaces the title VM after coordinated SD/Lua/DM
cleanup. Standalone audio tests retain their separate VM. Reopened title audio uses an adapter-local origin on the continuing session
clock, and its sound event is republished through DM. General title `first.lua` still uses a bounded adapter.
The retail startup milestones are implemented separately below; these bounded
live adapters execute shared boot, supported events and helper definitions;
general native STAGE/FIRST publication remains outstanding.

The live SDL window accepts **P** to toggle manual pause and **R** to explicitly
resume manual pause. As agreed, focus loss clears held input but does
not latch a session hold: gameplay, rendering and audio continue in the background,
and focus return needs no resume key. Loss/gain within one event pump follows
the same rule.
The currently assigned single SDL pad's removal holds the session until a pad
with the same SDL GUID reconnects. Manual holds survive reconnection and focus changes.
Vulkan uses the same background-running and keyboard pause policy; its existing backend has no
controller assignment. Four-player ownership/departure and suspend detection
remain outstanding host input work.

Holds stop the VM/DM, service clock, title/character/loading adapters and lobby
simulation together. Entering, changing or leaving a hold discards due backlog
and fractional host time. The recovered timer pause/resume preserves world time;
resumption requires a fresh full 60 Hz interval, with no paused-time catch-up.
Held presentation reuses the last framebuffer. Active rendering stalls retain
due ticks; title/lobby catch-up ticks omit drawing and presentation. Loading
samples always present so catch-up cannot consume the reveal/lock wait offscreen;
see [stage loading](stage-loading.md). Character
selection still advances some animation in its draw adapter and therefore draws
catch-up ticks while omitting presentation. Deterministic headless/scripted
checks keep one simulation tick per input frame.

`make check-script` checks blocked DM cursor retention, frozen service clocks and
query counts across every hold reason and nested holds, no immediate resume tick,
exact tick samples, active 100 ms catch-up and backlog discard. Existing event
checks cover next-tick publication; SDL input checks cover focus latching and
focus loss/return without a resume key and virtual-pad removal/reconnection. The audio check executes
the original title sound event through a session VM, held before its first tick,
then resumed through DM. `make check-script-retail` retains the original instruction
oracle for both title branches. These are controlled boundary checks, not a
physical controller, desktop focus, Windows or Steam Deck playtest.

Background-focus regression: `make -C port check-background-focus`
injects SDL focus loss and return in the title, character creation and Main Lobby.
During each unfocused interval, the real controller-service world clock, frame
presentation and audio sample clock continue advancing. Title/lobby frame hashes
change, and focus return supplies no R key. A separate manual-pause interval
remains frozen across loss/return until an explicit R. An engine that latches a hold on focus loss fails
the background clock/rendering assertion. `check-background-focus-gpu` runs
the same fixture at 640×448 on hardware with zero CPU graphics calls. These are
real event-pump/backend checks using injected events and a virtual controller,
not a physical desktop Alt-Tab test.

## Shared retail random stream

`src/random.c` implements the engine's original MT19937, including its old
69069 seeding routine and boot seed 5150. `dw4_be_init` initializes the stream
in caller-owned state; closing/recreating a script engine does not reseed it.
The live session retains that state through title re-entry and lobby publication.
Future native combat/drop/AI consumers must use this same `dw4_random` instance,
rather than create a second generator. The state is runtime-only and adds no
memory-card save fields. Ownership will need to move with the remaining system
state recovery; it currently resides alongside the bounded frontend fields.

`SYSgetRandom` consumes exactly one draw, including modulus 1. It follows retail
unsigned 32-bit division and signed integer result conversion. Negative moduli
use their unsigned bit patterns; zero preserves the dividend as EE DIVU's
remainder, avoiding host division by zero. The binding accepts the existing
finite signed-32-bit numeric argument contract. Missing/invalid arguments fail
before consuming a draw.

`make check-script-retail` runs `tools/verify_random_retail.py` against the
private ELF: original Reset/seeding, twist/temper and SYSgetRandom instructions
match all 624 boot state words and 2,500 interleaved native/Lua-style draws,
including five twists and positive/zero/negative moduli. Only the base Reset
no-op is a controlled leaf. `make check-script` checks actual Lua calls,
interleaved native draws and three VM lifetimes on one state. It also executes
original NDMW 417 chunk 28 for 64 rail branch choices and gated repeats, checking
the emitted model sequence and shared state; the model handler is controlled.
This establishes the generator/binding, not gameplay draw frequency or full
scene outcomes. The model-event and native consumers below share this
stream; retail RNG positions during full gameplay remain unverified. The older
recovery RNG page's script modulus catalogue predates the signed-literal fix;
use original bytecode and the numeric audit when extending event integration.

The full native `make check` and `make check-script-retail` pass;
optional private-input pose/fog comparisons retain their skips. The Lua integration
tests, including this RNG slice, also pass ASan/UBSan with leak detection disabled
for the runner environment.


## Model callbacks and native RNG consumers

`dw4_scriptengine_model_event` executes a named chunk synchronously with a scalar
model snapshot: RAM/record numbers, current/maximum HP, info/call names and an
optional WPos output triple. The implemented MDL methods expose those values,
add HP with retail wrapping addition and signed-negative clamping (without a
maximum-HP cap), dispatch sequence/SD selectors, and set the numeric or
`V<x,y,z>` target. The evidence is retail `0x394400`, `0x394920`,
`0x373d00`..`0x373dc8`, and `0x374180`..`0x374200` plus their Lua dispatcher
wrappers. `MDLisCallName` returns numeric 0/1; zero remains truthy in Lua 4.
Unsupported model methods still fail through the service boundary.

Snapshots copy selector names before callbacks and retain no receiver pointer.
Nested native calls restore the outer host context; this is a tested host lifetime
policy, not a claim that retail's global context restores itself identically.
The owner conditionally commits HP only when persistent HP stayed unchanged,
as `0x394400` does. A scope removed during a call cannot commit its snapshot.
Published model DM groups inherit their scope, and cancellation safely marks
active groups until the DM traversal ends. Calls during DM retain the next-tick
publication boundary. The live SD bridge tags timed messages with the active
script scope; stage owners must cancel both DM and SD scopes before release.
The legacy scoped cache retains its host precedence policy. Live scene libraries
use the retail ordered-info lookup and whole-scene cleanup described below
([#790](../../docs/findings/findings-0751-1000.md#f790)–[#793](../../docs/findings/findings-0751-1000.md#f793)). Timed follow-up publication
uses the host ownership policy described in [#789](../../docs/findings/findings-0751-1000.md#f789) below.

The Main Lobby collects all 64 referenced rows through `beLuaInfo._dataList`,
executes its own `func.lua` and runs `aim_n_digilff.lua` callbacks after publishing
the prepared scene. The first WPos callback uses
RAM number 2 and HP 100; original bytecode normalizes HP to waypoint 1 then
advances to waypoint 2 `(20,10,-35)`. Later SQ_NEXT callbacks execute the same
chunk, including random two-way branching at waypoint 2. The native reader
loads this actor's MAP01 distance bounds and four AI lists. `src/modelai.c`
uses a raw shared draw's low four bits and the first absolute limit greater
than that draw; a single-choice list still consumes a draw. Timers use EE float
arithmetic before conversion to nanoseconds. The scene-owned
actor executor implements SQ_WALKON, AIMAP acquisition, patrol timers,
zone choices, direction and turn limits; see [actor sequences](actor-sequences.md).
Collision, renderer publication, exact full-scene update latency and patrol
trajectory parity remain unverified. Combat, loot, enemies and projectiles need
their owning native systems before their RNG consumers can be integrated.

`dw4_action2_host_random` binds recovered WAITCHECK execution to the same
caller-owned stream and shared rhythm float bits. R??S writes rhythm without
consuming a draw; other R waits consume one raw draw, including zero span.
The live lobby portal/ring hosts use this binding. Existing authored non-random
programs retain their draw frequency.

Validation: `make check-script` executes 128 original guide callbacks interleaved
with native draws, endpoint/middle targets, numeric-zero call-name behavior,
nested context restoration, HP overflow, cancellation during callbacks, deferred
scope removal and survival of session groups. It also checks shared Action2
rhythm and 32 random/zero-span waits. `make check-script-retail` runs
`tools/verify_modelai_retail.py`: 512 choices and full RNG states match the actual
retail instruction slices beginning after successful target acquisition; ten
frame durations follow the original float and integer-conversion helpers.
Target/timer acquisition and sequence dispatch are outside that oracle.
`test_lobby` drives an attached scene for 10,000 updates, checks repeated original
WPos events/AI choices, verifies drawing consumes no RNG, and closes the VM after
detaching. Runtime script failures currently report an actionable diagnostic and
stop the session; visible script-error Retry/Back remains outstanding. Failed
prepublication named loads use the existing loading Retry/Back path.

The full `make check` and `make check-retail` pass, including the existing
3,497-tick title instruction comparison. Lua and attached-lobby
integration tests also pass ASan/UBSan (`detect_leaks=0`); optional private-input
pose/fog comparisons retain their skips. These automated checks do not establish
physical-controller or Steam Deck validation.

## Scoped named chunks and lobby unload

The scoped loaders in `include/dw4/script.h` associate each named closure with
an explicit host lifetime token. A successful publication becomes the active
name; a repeated load of that name in the same scope replaces its old reference.
Other owners remain retained. Removing a scope releases its named references
and exposes the most recently published surviving owner. Logical `dofile` uses
the same lookup. Existing loaders use session scope zero, which is removable
like every other scope. Loading still has no execution side effects, and failed
individual or pack loads preserve all owners and their precedence.

This is a host cache/lifetime policy. It does not establish retail manager load
order, global-versus-stage precedence, or cache eviction timing. Executed chunks
share the VM's globals: removing a named reference does not undo global definitions
or native side effects, and globals can retain functions from an unloaded scope.
A closure already executing remains rooted by the Lua stack until it returns;
a nested lookup after removal sees the restored name. Model-event cancellation
still prevents snapshot commit and further native calls after owner unload.

`dw4_scriptengine_remove_scope` releases named references as well as cancelling
that owner's DM groups and model snapshots. SD scopes must still be removed by
the service owner before releasing receivers. The live lobby tags its
ordered info library with the supplied lifetime scope; detach releases those
rows. The scope remains a host lifetime tag and does not select a winning row.
Title re-entry reloads its own library and helpers into a fresh scene VM.

Validation: `make check-script` covers three-owner name resolution, hidden-owner
removal, repeated same-owner publication, logical `dofile`, every truncated prefix
of an override, corrupted original pack loads into existing/new owners, original
named-only pack ownership, unload during a call with nested lookup, and 128
unload/reload cycles. Existing model-event checks also unload an actively executing
scoped closure. `test_lobby` verifies the guide name becomes unavailable after
detach. These establish native cache/lifetime behavior, not retail scene outcomes.

The full native `make check` and `make check-script-retail` pass.
The Lua and attached-lobby checks also pass a separate headless ASan/UBSan build
(`detect_leaks=0`, `halt_on_error=1`). Optional live texture/pose/fog checks retain
their missing-private-input skips. No Windows, physical Steam Deck or retail
emulator playthrough covers this cache/lifetime slice.

## Timed callback follow-ups and ownership ([#789](../../docs/findings/findings-0751-1000.md#f789))

Timed dispatch temporarily installs the executing message's publication
scope. Follow-up messages inherit that owner rather than the most recent unrelated
publisher. The ambient scope is restored on return or failure; explicit changes
inside a callback apply locally. Removing the owner during dispatch cancels its
already-enqueued children and unregisters its receivers safely. This is a host
lifetime policy, not recovered retail stage ownership. A callback must stop using
released state after unload; this does not prevent subsequent calls from a stale
owner or integrate general stage transitions.

The retail oracle compares eleven reentrant samples: zero/positive children
alongside a due peer, plus two zero-delay chain passes. Retail snapshots the
reusable record list size, initially 32, so a self-scheduling zero-delay chain
runs 32 times per pass. Receiver execution and list/allocation remain controlled
leaves. Nested native ticks are rejected without changing the sampled clock.

Finding **[#789](../../docs/findings/findings-0751-1000.md#f789)** also preserves a discrepancy: a negative-delay child inserted
ahead of the executing retail record is removed by post-callback head recycling,
leaving the recycled idle parent ahead of a due peer. The fixture emits only
PARENT on retail; native emits PARENT, CHILD, PEER because it detaches the executing
record before callbacks. Native retains its existing lifetime-safe behavior.
This is an instruction-level edge case, not a demonstrated gameplay bug, and
the agreed individual bug-compatibility review has not decided its default.
Zero/positive comparison results do not establish negative-delay parity.

`make check-scriptservices` covers inherited and explicitly overridden scopes,
ambient restoration, cancellation/unregister during expiry, callback failure,
bounded callback chains and 128 service-owner recreation cycles. The focused
checks pass ASan/UBSan with leak detection disabled. Full native checks and the
script retail suite pass; platform playtests and general stage outcomes remain
outstanding.

## Recovered retail loading and ownership ([#790](../../docs/findings/findings-0751-1000.md#f790)–[#793](../../docs/findings/findings-0751-1000.md#f793))

[Retail loading and ownership](../../docs/engine/lua-loading-ownership.md)
establishes scene startup and teardown. The retail loader replaces its Lua
state before executing `func.lua`, then `boot.lua`; after asset/layer/text work
it executes `start.lua`, enables the system and executes `first.lua`. Shared
helpers belong to that scene VM. Whole-state release cleans arbitrary globals.

Retail named execution takes the first matching row in each collected Lua-info
object and continues through later infos, executing every such match. Only the
last status -1 triggers file fallback. This differs from the host cache's newest
surviving closure policy and its transactional preparse. Explicit fallback paths
do not restrict the info lookup. Original cleanup visits managers forward; three
offline title/lobby rosters establish SD, Lua and DM at slots 3, 7 and 8 before
model-controller release. DM has a separate RemoveAll deferral latch.

`make check-script-retail` includes 85 loading/lookup/cleanup instruction
samples. Optional `--state` inputs inspect loaded rosters and named-info tables.
Allocation, archive IO, Lua execution and receiver/destruction leaves are
controlled; this establishes contracts, not a complete transition playtest.
The native implementation supplies these ownership contracts. Collection
walks `beLuaInfo._dataList` in archive collection order, then resolves each
referenced `beLuaData` and `beLuaDataObject`. It retains duplicate rows and copies
names/bytes transactionally. Orphan data records are not executable through this
path. Collected rows survive pack unmapping and phase-3 VM recreation.
`dw4_script_run_named` executes the first equal row from every info in forward
order, continues after errors, and reports the final Lua status. Later global
assignments override earlier ones after all their side effects occur. It calls
the supplied mounted-file reader only on final -1, uses an explicit directory
only for fallback, and executes bytes before the first `[EOF]`. Missing files
return 2; read/marker failures return -1. No host filesystem access is implicit.
Logical `dofile` uses the ordered lookup once infos are collected; its equivalence
to every retail base-library file call remains unproved.

`dw4_scriptengine_startup` exposes three ordered milestones: SHARED recreates
the VM and executes `func.lua` then `boot.lua`; STAGE sends `TEXTCTL INITIALIZE`
and executes `start.lua`; FIRST executes `first.lua`. Callers finish supporting
collection before SHARED, finish stage collection/layer binding before STAGE,
and activate the system before FIRST. Script statuses are retained in
`dw4_script_start_status` without gating retail advancement. The regular engine
run API retains its separate host failure latch. This implements the recovered
Lua milestones. The file-list preparation layer below owns asset collection;
prepared native object ownership and layer binding are supplied by the [scene registry](stage-objects.md); controller commands remain the responsibility of each subsystem.

`dw4_scriptengine_remove_all` checks for active Lua/DM/SD calls before mutation,
then removes every SD message/receiver/category, releases all Lua infos and closes
the VM, and clears published and unfinished DM groups and the switch latch.
`reset_scene` additionally opens a fresh VM. Native flags, counters, progression
storage, RNG position and world time remain outside VM ownership. SD tokens stay
monotonic so stale owner tokens cannot unregister a replacement. Whole-scene
reset requested inside a callback is rejected; the owner must defer it to between
ticks before releasing borrowed controllers. DM-only RemoveAll has its own
retail latch: a request inside a DM pass preserves groups through the pass,
then clears published and building groups at unwind (`0x37f138..0x37f154`).

The live title-to-lobby publication, attract return and session shutdown use
this boundary before releasing receiver/controller owners. The destination
collects its own library and shared definitions. Loading keeps the old scene
until destination assets are ready, preserving the existing host Retry/Back
policy; failed script publication restores a fresh title library. The standalone
front-end scan also uses isolated scene VMs. Title and lobby run original func/boot asset preparation, as described below.
The created-card lobby login also runs original start/first; the title's live
start/first orchestration retains its bounded adapter. Original title
first.lua and message helpers have integration coverage; full live title startup
requires the remaining owning services.

Native calls snapshot selected info rows before execution so reentrant host
scope removal cannot invalidate active bytes. This callback-lifetime adaptation,
scoped tags and prepared-scene publication timing remain host policy. The legacy
newest-owner scoped cache is retained for isolated adapters and compatibility
checks; it does not participate in ordered retail lookup.

Validation: `test_script` checks first-row duplicates, all-info side effects,
last-error/later-success status, missing/read/marker/syntax fallback, explicit
paths, transactional corrupted packs, orphan records, functions/tables/global
cleanup, active info removal, preserved flags/RNG, ordered startup and error advancement, busy-boundary
rejection, deferred DM cleanup, receiver invalidation and stale-token safety.
The corpus audit collects 7,300 referenced named rows in 98 original libraries,
backed by 5,291 serialized chunks. Rows may share a data object: an independent
reference decode of entry 179 finds one info with 55 rows and 35 data objects.
`test_scriptservices` checks busy removal and recovery of a failed service at a
scene boundary. Attached-lobby callbacks and the frontend/loading regression
checks pass. Full native `make check` and `make check-script-retail` pass;
optional live pose/fog inputs retain their skips. Separate headless ASan/UBSan
script, service and attached-lobby checks pass (`detect_leaks=0`,
`halt_on_error=1`). No emulator playthrough
or platform playtest covers this recovery.

Remaining work:

- Prepared title/lobby native info routing and layer binding are implemented; see [prepared native scene objects](stage-objects.md). Extend owning command services and arbitrary-stage manager/cache ownership as those systems are implemented.
- Implement the general scene services required by boot/start/first scripts and
  validate full startup and stage transitions against retail.


## File-list asset preparation

`dw4_filelist` reads the authored `beFileListInfo._fnames` reference graph,
not bracket strings scanned from arbitrary pack bytes. It retains the first-use
`BecText.igb` and `_common/sbiallse.igb` resources, loads `/s` supporting entries
before the remaining entries, and publishes ordered Lua infos with scene scope.
Title loads sound entry 805 before script entry 806; Main Lobby loads sound 819
before script 820 despite the opposite order in its serialized list.

The live title and Main Lobby use this path, then run original `func.lua` and
`boot.lua`. `CFLclear` clears the filename queue; `CFLsetName` deduplicates exact
strings while preserving first publication order; `CFLgetFolderName` returns the
current stage. USA `SYSgetArea`, `SYSgetCountry` and `SYSgetIsPackOnly` return
numeric 1. Lobby boot receives the prepared player's model and primary weapon
asset names, participation snapshot and saved light mode. Other weapon slots
return nil. Title boot adds its AUS/USA packs; the starter lobby adds its actor,
weapon, USA pack and selected LH/LS light pack. Parsed packs remain resident
until coordinated scene replacement; first-use resources survive replacements.
The existing model/audio/render adapters still own their native resources.

Preparation rejects missing or invalid assets, unsupported boot queries and
unsafe startup boundaries. A failure blocks later milestones until scene reset;
partially prepared resources are released on the next boundary. The routing
callback borrows parsed packs, validates/publishes subsystem objects, then gates
STAGE and FIRST. The production path routes the stage directory and prepared packs into
scene-owned native info objects and binds their authored layers before receiver
publication; see [prepared native scene objects](stage-objects.md). Outside the
created-card Main Lobby login, existing adapters still provide scene choreography, and
general controller commands, renderer traversal and original live
`start.lua`/`first.lua` remain outstanding.

`make check-filelist` runs original title/lobby boot bytecode, checks supporting
order, queue clearing/deduplication, both light packs, missing-asset and query
failures, startup gates, preserved RNG words and 128 reloads. Scene/gameplay
commands in its STAGE/FIRST checks are controlled leaves, not gameplay evidence.
`make check-script-retail` additionally compares the CFL wrappers at `0x372a30`,
`0x372b50`, `0x372ce0` and USA constant wrappers at `0x371ed0`, `0x371ee0`,
`0x371f00` against retail instructions over 32 queue scenarios. String/list leaves
are controlled in that oracle; it establishes queue/query contracts only.

The file-list test also passes a separate headless ASan/UBSan build with
`halt_on_error=1` (leak detection disabled). Production loading Retry/Back and
ten-second minimum-hold checks pass with shared boot preparation enabled.
These checks do not establish full retail scene outcomes or platform playtests.

The full `make check` and `make check-script-retail` suites pass. The input test
requires `SDL_GAMECONTROLLER_IGNORE_DEVICES=<vendor>/<product>` so its
virtual pad is assigned instead of a connected physical gamepad.
The negative-delay reentrant SD discrepancy remains reported by the
retail oracle.

## Typed native object values

The host value bridge supports property-folder and database identities as
opaque Lua 4 userdata. Typed helpers share the existing pointer-sized value ABI
slot, so existing scalar callers retain their layout. Objects never become Lua
strings or numbers. A VM-private tag and membership check reject foreign
userdata. Repeated publication of a live kind/pointer/owner identity reuses the
same Lua identity; owner invalidation rejects old Lua arguments/host reads and
prevents reimporting expired cached descriptors. VM reset/close releases the
identity cache after Lua teardown, without destroying borrowed native objects.

GAMERAM and DATABASE native query receivers return these descriptors. The
live session publishes them through the existing registry. The recovered Lua
`sd` overloads are commands that discard receiver results; this remains intact.
There is no invented Lua `querySD` method. Tests use actual native query results
and the host value bridge, then validate userdata identity and ownership.

Native receiver checks cover GETCOMMON, GETPLAYER/GETPLAYER1/GETPLAYER4, prepared
shinka GETDATABASE, missing names, command void returns and separate owner
invalidation. Database values remain valid after archives/scene inputs are
released. This bridge supplies object transport; additional original object
operations need their own recovered bindings, rather than generic host-pointer
access from Lua.
