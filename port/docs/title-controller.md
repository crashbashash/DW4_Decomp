# Recovered title controller in the native port

The native boot loop executes the unchanged behavioural recovery of
`beNDMWTitle2::vfunc_31` (`0x003f2ef0`) once per 60 Hz simulation tick after the
backdrop opening. It owns Press START, the two-row menu, Options, cancellation
and the Game Start request. `engine.c` has no parallel input state machine for
these screens.

The slot screen that follows begins at the `LOADCTRL2 GENERATE_TITLE` boundary.
With a save library it runs in the `stagIS13` scene described in
[Save Keeper and interface scenes](save-keeper.md); the character UI adapter in
`../src/frontchr.c` is the Create flow for a host without one, and its retail
comparisons are in [main-menu fidelity](main-menu-fidelity.md).

The session's Lua MODELCTRL receivers share this controller's eight model
states. `GENERATE`/sequence requests, `ISRUN` and `ISSEQNAME` use the native
sequence state, not a separate completion stub. The title entrance OPEN/WAIT
and two entrance fade schedules cover original `first.lua` in integration
tests with bounded timing. The live startup uses its adapter. Camera state,
scope ownership and validation limits are described in
[Native scene completion queries](lua-integration.md#native-scene-completion-queries).

## Source and initialization

The files in `recovered/frontend/` are imported without edits from the matching
recovery in this repository. `provenance.json` stores content hashes and the
source HEAD; the hashes identify the actual working-tree content. The port
remains buildable with the canonical recovery in the same checkout.
`tools/check_title_reference.py` checks the hashes and, if available, compares
against the canonical files.

`titlehost.c` supplies host CTRL/OPTION records and the callback table. Initial
camera/light values come from the port's session settings (power-on Near/Hard),
with language mode zero. Displayed settings are separate from committed
settings: Left/Right updates the display, and either Circle or Cross on Return
commits only after the recovered close sequence. Cross on a setting does
nothing. Rows clamp; US Options skips the inaccessible language row. Direction
priority and input ignored during waits are decided by the imported code.

The host supplies analog threshold edges and pressed buttons. Retail pad repeat
production, generic engine allocation and save-file persistence are not
implemented by this adapter. Non-US country-reload callbacks fail explicitly
and are outside the initialized US path.

## Native model boundary

### Common-model queue

The adapter executes the imported common-model submission and poll helpers.
Opening/play and close/remove waits have separate lists; repeated requests
remain separate entries. Polling checks newest first and stops at the first
pending entry in each list. Open waits read MODELCTRL ISSEQNAME; close waits
read ISRUN. There are no per-model tracked/removing flags and no completion
scan.

`commdlhost.c` supplies native object/list storage and immutable title tokens.
It preserves the helper's reference-count and list operations, with a capacity
of 128 outstanding records; overflow stops the controller explicitly. Slots 0
and -1 are the supported title addressing domain. This adapter does not
implement general engine allocation, string interning or positioned generation.

### Model executor

The model executor tracks eight title models with action durations, sequence
successors, visibility and joint clocks. It answers the recovered helper's
queries. Rendering does not advance it. Unknown operations fail explicitly.
The logo runs its actual command program and recovered Action2 completion (see
the two sections below); the other seven models use bounded schedules. This
lower execution layer is **not proof of retail frame timing**. Its asset
sources:

| Asset | Source | Operations used |
|---|---|---|
| `j_startlogo` | AREA 620, Action2Info 7094 | OPEN joint 0–30 / fade-in 10; CLOSE wait/fade 30 |
| `j_startmenu01` | AREA 620, Action2Info 3379 | OPEN 0–15; LINESL00 loop 20–40 with Frame wait 1800; LINEON00 50–65 then CLOSE 1; TIMECLOSE wait 30 |
| `j_startmenu02` | AREA 620, Action2Info 902 | OPEN 0–15; down 50–70; up 80–100; confirm 110–125 or 170–185 then CLOSE 1; CANCEL wait 5 then CLOSE 1 |
| `j_optionwin02` | NDMW 806, Action2Info 1135 | AOPEN/BOPEN wait/fade 15; CLOSE wait/fade 15 |
| `j_optioncursor11` | NDMW 806, Action2Info 2462 | OPEN joint 360–375; MOVE wait 10; LINEON wait 5 then wait/fade 10; CLOSE empty action |
| `j_optioncursor12` | NDMW 806, Action2Info 2425 | OPEN joint 140–155; horizontal actions 10; CLOSE empty action |
| `j_startback` | AREA 620, Action2Info 707 | CLOSE wait 60; its sound Lua call remains outside this backend |
| `i_fadewn01` | NDMW 806, Action2Info 796 | WTOUT60 wait/fade 60; BLOUT30 wait/fade 30 |

These records can be inspected with the repository root's
`scripts/modelctrl_dump.py` using
`--afs <AREA.AFS or NDMW.AFS> --entry <620 or 806> --name <model>`. The model
sequence commands connect actions through WCHECK and JUMP. For models other
than the logo, the native backend collapses command-dispatch overhead into
those durations; that overhead, the exact action interpreter and its
sequence/running query semantics are not recovered at instruction level. A
tracked menu confirm play releases when LINEON changes to CLOSE; a tracked
close waits through removal.

### Consumers

Title UI geometry uses the backend's per-model joint time, fades and
visibility, including closing/reopening individual graphs. The Options
renderer uses the backend's visibility/fades and text publication gates, with
authored NDMW 806 joint ranges (see [Options presentation](#options-presentation)).
Text is drawn by the port's font/layout code, not the recovered messenger
implementation. Audio cues use the [front-end audio adapter](audio-playback.md).

Game Start hands camera/light arguments to the slot screen only when the
recovered controller sends `GENERATE_TITLE`. Attract expiry sends `stagIS09`
to the host 802→804→806 sequencer, then resets the title controller and
presentation clock. That sequencer keeps its logo/movie presentation
limitations; it is not a recovered stage loader.

## Logo command program ([#759](../../docs/findings/findings-0751-1000.md#f759)–[#760](../../docs/findings/findings-0751-1000.md#f760))

The logo walks its actual AREA 620 model program, extracted by
`tools/gen_logo_program.py` into `src/logo_program.h`. `--check` re-extracts it
and compares all commands and the pack hash. The generator requires the
workspace's analysis tools and the user's archive; the ordinary build uses the
checked-in text and remains standalone.

`src/logoseq.c` supplies a narrow native dispatcher for ACTION, WCHECK and
JUMP. WCHECK start/update and JUMP execute the unchanged imported
`modelwait.c`. OPEN reaches the asset's empty SQ_WAIT after Action completion;
CLOSE reaches SQ_ERAS. Reference replacement preserves the
intern-before-release order, including interruption of a pending OPEN/CLOSE.
Unsupported operations stop with an error.

The narrow dispatcher, virtual sequence selection/removal and the query adapter
are not recovered implementations of `0x00395250` or the retail message
handler. Fade/joint presentation is native. Joint completion (including strict
comparisons and shared-clock conversion) and generic command metadata dispatch
are unverified.

## Action2 completion and the clock ([#769](../../docs/findings/findings-0751-1000.md#f769)–[#770](../../docs/findings/findings-0751-1000.md#f770), [#772](../../docs/findings/findings-0751-1000.md#f772)–[#774](../../docs/findings/findings-0751-1000.md#f774))

### Action2

`action2time.{c,h}` and `eefloat.{c,h}` are imported unchanged and
hash-checked. `tools/gen_logo_program.py` also extracts the logo's OPEN/CLOSE
Action2 components into `src/logo_action2_program.h`, retaining their f32 bit
patterns. `src/action2host.c` supplies bounded records, metadata, WAIT property
allocation and messenger callbacks; it runs the recovered walker, per-frame
update and ISCOMEND predicate. The logo does not complete from an age count:
simulation ticks alone, with the clock held, do not finish it.

The adapter preserves timer storage and the node across action replacement
while clearing component state/index. This initialization is a native boundary
because the ACTION message path is not recovered. FADESET only supplies native
fade presentation parameters; it is not a recovered fade implementation.

### Clock source

`dw4_title_host_set_clock(host, raw_nanoseconds)` supplies the **raw source**;
it stays held until set again. The setter does not sample or dispatch models.
The next model tick runs the recovered timer read and system update, then
Action2, model WCHECK and common-model polling. An action started between model
ticks reads the last sampled world time. Without an external source the host
advances raw time by a provisional 16,666,667 ns per model tick, starting at
zero. That default step is a simulation model: it is not a measured mean, and
host elapsed time is not claimed to reproduce Timer 0.

### Clock lifecycle

`systemclock.{c,h}` is imported unchanged and hash-checked. `src/clockhost.c`
provides bounded little-endian timer/system records and a raw-source callback.
Each model tick invokes the recovered `0x00237730` update: read the long timer,
subtract the previous sample, multiply by the signed fixed-point scale with
retail 64-bit wrapping, arithmetic-shift by 18, and add to world time. The
model callback runs from the scheduler boundary after the world store. The
preceding dispatcher is an explicit no-op boundary: its receivers and the
complete manager graph are not ported, so this does not reproduce their
possible shared mutations.

`dw4_clock_host_pause(&host.clock)` and `dw4_clock_host_resume(&host.clock)`
invoke the recovered timer methods. Pause captures elapsed time once; resume
preserves it and excludes raw time spent stopped. They do not reset the system
sample or world time. `dw4_clock_host_scale` accepts a signed value with 18
fractional bits (`0x40000` is normal speed). These are clock operations, not a
binding for the game's pause button; model ticks still dispatch while time is
held. Presentation queries do not sample or advance the clock.

Native initialization explicitly chooses a running timer, zero origin/world and
unit scale. Menu re-entry does not call system start or reset the sample
baseline. The recovered system start resets the sample while retaining
accumulated timer and world time, so treating it as an ordinary resume could
double-count time. Full engine start/stop, reset/restart routing and renderer
profiling are not wired into this bounded title adapter.

### Clock evidence

Two stock-emulator logo savestates independently confirm WAIT duration
499,999,968 ns and the action→manager→system-clock chain. Static timer methods
and their captured vtable establish the source chain; the supplied clock uses
nanoseconds with 100 ns quantization. External sampling reports variable steps
near 60 Hz, without a retained raw sequence or frame counter. See
[system-clock evidence](../../docs/engine/system-clock.md). The timer lifecycle
and the normal world-store-before-Action2 order are recovered ([#772](../../docs/findings/findings-0751-1000.md#f772)–[#774](../../docs/findings/findings-0751-1000.md#f774)). No
exact completion frame was measured.

## Options presentation

The bound Options renderer samples each model's simulation clock; drawing does
not advance a clock. The window, row highlight and arrows use their authored
JOINTSET ranges from NDMW 806. Extract them with
`scripts/modelctrl_dump.py --afs local/extracted/NDMW.AFS --entry 806 --name NAME`
from the repository root, with `j_optionwin02`, `j_optioncursor11` or
`j_optioncursor12` as NAME. The renderer follows the controller's recovered
sequence requests; it has no renderer-side row slide.

| Model | Joint ranges (asset frames) |
| --- | --- |
| Window | AOPEN 40–50 LP → 50–109 LP; US BOPEN 160–170 LP → 170–229 LP |
| Highlight | OPEN 360–375 OS, fade in 5; rows 0/1/2/3 loop 0–59 / 90–149 / 180–239 / 270–329 |
| Highlight confirmation | Row N: 380+20N through 395+20N OS; fade out after the first 5 frames |
| Arrows | OPEN 140–155 OS; row N idle 50N through 50N+10 LP; Right +10…+20 OS, Left +20…+30 OS |

MOVE supplies a ten-frame wait without JOINTSET, so it retains the previous
joint and phase until the controller publishes the next row. CLOSE also retains
joint phase where no JOINTSET is present. The controller removes the arrows on
Return; the renderer honours model activity. Camera/light text honours each
published text bit during directional waits. The window's rotating row icons,
looping highlight, arrow feedback and confirmation deformation come from the
original keys. The unbound standalone preview keeps a legacy timeline.

The cursor also has texture-coordinate animation: NDMW 806 transforms 2700,
2704 and 2727 have `_target=9` and share sequence 2701. Its translation keys
scroll V from 0 to -1 over each row's one-second idle window; mesh transforms
alone leave the white strip frozen. `frontopt.c` applies
`dw4_scene_node_uv_offset` to each draw's UVs, using the same driven joint
clock and repeat sampler as the original asset. No synthetic strip is added.

`test_titlehost` checks retained joint phase, idle playback, directional
return, window fade visibility and Return confirmation/removal. `test_menu_gpu`
uses bound title models for opening, idle, directional and Return poses, checks
that drawing twice without a simulation tick produces identical pixels, and
verifies changing pixels along the stationary outline between idle ticks on
both rendering paths. Bound Options CPU/GPU comparisons at 640×448 have mean
RGB differences below 0.013/255. A native boot→Options→camera-toggle run was
rendered and visually inspected against the retail captures, which supply the
composition reference.

## GPU title trails

Windowed boot renders `j_startback`'s ordered material draws with GLES 3
(`src/gl_layer.c`). The recovered controller, animation, camera, lighting and
triangle generation in `frontlayer.c` are the same on both paths. The backend
batches only consecutive triangles with identical material state, retaining
draw order.

The shader implements affine colour/Z/fog interpolation, the fragment S/T/Q
divide, RGBA8-rounded bilinear samples, repeat/clamp, MODULATE and AREF. Depth
is cleared to zero and tested GEQUAL; masked draws preserve depth. Alpha and
additive blends consume premultiplied RGB once. This mirrors the CPU material
contract, including its legacy opaque-alpha option, untextured depth bypass and
subpixel sample offset.

Textures stay resident between frames. EGL and SDL contexts are restored around
each GPU pass, including SDL's GLX context on X11. In normal boot a GPU setup
or draw failure is an explicit error under the hardware policy
([GPU rendering](gpu-rendering.md)); explicit reference runs keep the CPU
fallback. `--software` selects the CPU reference path; headless boot keeps it
by default, with `--gl` enabling the GPU passes for comparisons. The lobby uses
its separate renderer.

At 1280×960, a 300-frame, uncapped title run measured approximately 25 ms/frame
on the CPU versus 7 ms/frame with GPU trails. This is a rendering performance
measurement, not retail timing equivalence. The normal 60 Hz
simulation/presentation limit remains enabled.

`test_gl_layer.c` compares modulation, blend, alpha/depth rejection, ZMSK, STQ,
filtering, wrap and coloured fog against the CPU, and checks preservation of a
peer EGL context. `test_title_gpu.c` compares seven opening/loop poses and
rejects unexpected CPU fallback. At 640×448 and 1280×960 the measured mean RGB
difference was below 0.05/255; rare triangle-edge pixels differ more. The test
allows a mean difference of 1/255 and at most 1% of pixels exceeding 4/channel;
it does not claim byte-identical GPU rasterisation. Both tests run in
`make check` when EGL/GLES is available.

## GPU title composition and legacy overlays

Normal title rendering draws the original backdrop on a GPU mesh owner with
quantized affine Gouraud lighting. Main clears, flashes/fades, legacy
panel/cursor primitives, fallback/error font strings and FPS bitmap/plate work
execute on GPU. Normal startup cards use their GPU owner for clears as well as
artwork. Explicit reference paths keep the CPU oracle; missing essential title
graphs stop instead of selecting the CPU placeholder.

The mesh and layer backends share context restoration and preserve peer EGL
lifetimes. All 300 title frames compare within the image allowances above; the
live three-cycle route with FPS reports zero CPU drawing counters. This does
not validate movie/startup presentation or standalone stage paths. See
[GPU rendering](gpu-rendering.md#gpu-mesh-main-clears-and-textfps).

Title texture caching follows authored image IDs: two `mojips.png` records
share a filename but contain different copyright/menu rasterizations, and four
actual image identities are retained under three names. Settled title artwork
uses retail RGB 127 and scales X from 640 pixels and Y from 448 lines, so
high-resolution 4:3 output does not displace the title horizontally.
Boot/loading card material and scaling rules are separate. Complete
logo/menu/copyright quad comparisons pass against both retail rows at original
and 1280×960 hardware sizes; see
[the evidence and scope](main-menu-fidelity.md#title-screen).

## GPU menu drawing

The title UI, Create/Call selector, species panels, naming, confirmation,
created card and options replay their ordered STQ triangle lists through the
same GPU backend. `gl_layer_ui` converts UI materials to depth-write-disabled
draws at a constant passing Z, preserving UI painter order without depth
occlusion. The animated BG02 field uses its original layer materials and a
separate cleared depth pass. Text atlases and pack textures remain resident;
cache identity uses the pixel buffer and dimensions, allowing temporary glyph
texture wrappers. Headless preview APIs remain CPU unless explicitly enabled.
Unsupported legacy UV lists or GPU failures use the CPU fallback only in
explicit reference runs; in normal boot a GPU failure is an explicit error.

The character screen replaces the title entirely, so the boot loop skips the
hidden title backdrop, trails, UI and flash whenever character selection is up.
Controller/input clocks still advance.

Character previews retain a GPU renderer for their separate authored viewport,
recreating it only when the viewport size changes. Transparent clear, mesh draw
and the original integer opacity/composite rule execute on GPU. Incoming and
outgoing species keep their pose clocks and display order. Selected reference
runs keep the CPU portrait path. `test_gl_post` compares clipped RGBA/opacity
blits byte-for-byte with the original CPU loop. See
[the GPU checkpoint](gpu-rendering.md#gpu-offscreen-and-pixel-composites).

`test_menu_gpu.c` compares CPU/GPU screens in lockstep through opening and idle
poses, four species transitions, naming/question/confirmation/created phases,
options, press-start and both main-menu selections. It rejects silent fallback,
uses the same image-difference limits as the title test, and verifies zero CPU
kernel/composite calls inside each hardware menu draw. It runs in `make check`;
optional output directory and width/height arguments support larger captures.
At 1280×960 on a desktop hardware GPU, 30 measured drawing frames after 10
warm-up frames took about 18 ms CPU versus 3.5 ms GPU for Create/Call, 21–22 ms
versus 5.8 ms for species selection, and 18–20 ms versus 3.4 ms for
naming/confirmation. These timings exclude window presentation. The mean RGB
difference was below 0.02/255 across the tested screens.

The character UI's created summary, idle cursors, lower messages and upper
species/name/keyboard fields use authored models, localized FontTree rows and
original text callbacks; their retail comparisons and limits are in
[main-menu fidelity](main-menu-fidelity.md) (the
[created summary](main-menu-fidelity.md#created-summary),
[selection cursors](main-menu-fidelity.md#selection-cursors) and
[upper fields](main-menu-fidelity.md#upper-species-name-and-keyboard-fields)).

## Login hand-off

The created-card Start hand-off uses a locked native CLOSE adapter and loads
Main Lobby into the boot window. It preserves name/species and draws the
first-arrival player/Digi-Elf greeting from recovered assets and text. See the
[boot contract's arrival evidence and remaining boundaries](boot-contract.md#created-card-login-and-first-arrival).
This hand-off is separate from the recovered title controller and is an
adapter, not full model/message control.

## Validation

- `build/test_titlehost`: clamping, direction priority, START-only entry,
  ignored input during movement, Cross/Return and Circle exits, delayed
  settings commit, cancel/re-entry, committed settings on reopening,
  two-argument handoff, independent opening/closing operations, sequence expiry
  and unknown-operation failure; repeated requests, replacement ordering,
  low-byte tracking flags, storage reuse and capacity failure; a 100-tick
  unresolved logo wait, non-Boolean completion (256 and -256), interruption,
  removal/re-entry and unsupported-sequence failure; and the Options poses
  listed above.
- `tools/verify_frontend.py`: the real executable, asset rendering,
  title→Options and Game Start→character/name flows. Inputs are spaced around
  the controller waits.
- Upstream `scripts/verify_title_menu.py`: 55,264 retail-versus-C cases. The
  import check makes those results applicable to the controller compiled by the
  port; it does **not** extend that equivalence claim to the native callbacks.
- The ten recovered common-model helper bodies pass 2,676 upstream retail/C
  checks, including ordered stores and engine calls.
- `tools/verify_title_integration.py`: **3,497** retail/native ticks agree.
  The oracle side executes original title, queue, logo JUMP/WCHECK, Action2
  (including the timing helpers and ISCOMEND) and clock lifecycle/update
  instructions against the same native lower model executor, and compares
  ordered helper calls/stores, clock/Action2 events and the complete
  controller/queue/logo state and adapter arena after each tick. Coverage:
  title, Options, movement waits, cancel/re-entry, settings commit, Game Start
  handoff, attract, large raw clock inputs (preserving the rounding of each
  absolute clock before subtraction), held clocks, pause/resume, half-speed
  scaling, interruption and re-entry. ACTION timing and native dispatch are
  shared boundaries; this does not establish the executor's timing or pixels
  against the running game.
- `tools/clock_retail_oracle.py` runs original timer and system-update
  instructions against the native arena, including the retail multiplication
  helper, then enters the same bounded model boundary. Ordered clock
  stores/calls are compared together with Action2 events and complete
  clock/model/queue snapshots. Independent native assertions cover held time,
  idempotent pause/resume, half/zero/reverse speed, render queries without
  updates and logo completion after resume.
- `make check-retail` runs the retail comparisons above with the canonical
  recovery tree and a retail ELF (override `DW4_ELF` if needed): the extracted
  logo program, the upstream 988 helper calls, the integration ticks, and the upstream
  **9,431-case / 585-instruction** clock differential with its four mutation
  checks against the imported reference. Ordinary `make check` remains usable
  without private retail inputs.
- Full `make check`, `make check-retail`, the imported-reference hashes and the
  title/queue address/undefined-behaviour sanitizer tests pass; the sanitizer
  runs have leak detection disabled. The matching build is unaffected: the
  imported files are unchanged and add no matched-byte claim.
- A 2,200-frame headless run verified one attract request, the 802→804→806
  route and a second title opening; title and Options frames were inspected.
- Window-presentation and live-dump pose/fog checks skip when their
  session/capture prerequisites are unavailable.

## Open items

- The model action interpreter and its ISSEQNAME/ISRUN semantics are not
  recovered. The bounded schedule behind the recovered queue layer has to be
  replaced by it for the seven models other than the logo, followed by
  synchronized retail/native interaction traces, frames and audio.
- No synchronized retail/native visual or audio equivalence is established: no
  console timing, rendering or audio comparison exists for the title, and no
  exact logo completion frame was measured. Raw hardware cadence and EE
  floating-point behaviour are unmeasured boundaries.
- Game-pause routing and clock initialization defaults are open.
- The Options bounded sequence durations, joint loop boundary arithmetic, fade
  evaluation and text typography need synchronized retail comparison; the
  current checks do not establish frame-for-frame equivalence with PS2
  execution.
- Retail pad repeat production is not implemented in the title host.
- The recovered messenger does not draw title or Options text.
- Live phase and transition equivalence of the character screens is open; see
  [main-menu fidelity](main-menu-fidelity.md#open-items).
