# Digimon World 4 native port technical specification

Draft. Release scope is agreed; detailed requirements remain under discussion.

The first release delivers the complete original Digimon World 4 game on PC, with
PC controls and display options. Gameplay changes and new content belong to later
releases. This specification defines the target behavior and technical contracts;
the [boot contract](boot-contract.md) records current implementation boundaries,
and the [port task list](project/tasks.md) tracks work.

## Agreed release scope

- Deliver the complete original game, including progression through its ending,
  original stages, playable characters, combat, equipment, quests and difficulty modes.
- Preserve the original gameplay while providing PC controls and display options.
- Treat a playable slice as an intermediate milestone toward the complete release.
- Keep gameplay redesigns and additional content outside the first release.

The existing project targets Linux and Windows using the USA retail game
(`SLUS-20836`) as its baseline. Other game regions follow later. Specific operating
system versions, hardware targets and the order of additional region support remain
to be decided.

## Established technical direction

These decisions come from the existing [porting plan](project/README.md)
and [pointer model](project/pointer-model.md).

| Area | Direction |
| --- | --- |
| Execution | Source-level retarget of recovered game and engine code to host libraries. |
| Platform services | Native implementations at the engine's platform interfaces. |
| Rendering | Native renderer implementing recovered pipeline behavior. |
| Audio and video | Native replacements for original playback services. |
| References | Preserve four-byte references through an arena and handle accessors; host pointer widening is optional later work. |
| Assets | Consume the original archive and pack formats through native readers. |
| Recovery | Preserve the decompilation's byte-identity oracle; validate host behavior separately. |

The production graphics/media backends and script-to-engine integration still
need explicit contracts. Prototype dependencies do not by themselves establish
release requirements.

## Agreed multiplayer requirements

The first release supports the original local co-op for up to four players.
Online co-op follows in a later release. Each player selects a character from
the shared local character library. Local co-op players join only from the main
menu, matching the original game; there is no joining during gameplay. Leaving
follows the original game's allowed points, with the agreed controller-disconnect
resolution as an explicit host behavior. If a participating player's controller
disconnects, pause the whole session until it reconnects or that player leaves.
The pause must stop gameplay simulation so players do not take damage or advance
gameplay timers while resolving the disconnect. Controller assignment, exact
leave handling and who can dismiss a disconnected player remain to be specified.

## Agreed display and timing requirements

The first release supports higher resolutions and widescreen. Gameplay runs at
60 fps and FMVs play at 30 fps. Display refresh rate and selected resolution must
not change gameplay or animation timing; movie playback must preserve audio/video
synchronization.

When rendering falls below 60 fps, preserve gameplay speed and skip rendered
frames as needed. Rendering delays must not slow the gameplay clock. This policy
does not guarantee performance on hardware unable to sustain the simulation itself;
reference hardware and sustained-overload handling remain to be specified.

Launch supports 4:3, 16:9, 16:10 and ultrawide displays. Widescreen shows more
world horizontally while preserving the original vertical framing. The gameplay
HUD anchors to the screen edges, with user-adjustable margins and UI scale.
FMVs preserve their original aspect ratio with borders where necessary.

The exact ultrawide range, UI scale and margin ranges, fixed-composition scene
framing and window modes remain to be specified. AI or algorithmic FMV upscaling
is a possible future enhancement, outside the first-release requirements.

### Agreed GPU rendering requirement

Normal play renders graphics on the GPU, including menu/status rasterization
and compositing. GPU unavailability or a draw failure must be reported explicitly;
normal play must not silently switch to CPU rasterization. The CPU renderer is
retained only for explicitly selected diagnostic/reference runs and automated
validation. CPU asset decoding, simulation and preparation of draw submissions
remain host work. The implemented boot, stage and movie entry points satisfy
this graphics boundary on the validated Linux host; see the
[normal-path audit](gpu-rendering.md#normal-path-audit).
Complete-game and broader platform release acceptance remain separate.

### Future unlocked frame rates

After the initial 60 fps release, support unlocking the rendering frame rate
without speeding up gameplay. Audit frame-dependent logic and convert suitable
updates to elapsed-time (delta-time) calculations. Preserve original durations,
movement speeds, combat windows, animation and script behavior across rendering
rates. A fixed simulation cadence may remain for systems whose original behavior
depends on discrete ticks; interpolation can support smoother rendering between
those ticks. The final timing design and fidelity checks belong to a later
implementation milestone.

Unlocked rendering does not change the agreed 30 fps playback rate of original
FMVs. Delta-time conversion must not globally replace recovered clock arithmetic
without checking its gameplay effects.

## Agreed save requirements

Preserve the PS2 game's save logic and gameplay save fields. The initial port
does not add or remove gameplay save entries, and no gameplay save-schema
migration is planned. The expanded native library, separate recovery saves and
co-op transactions still need storage organization, independent of those unchanged
gameplay fields. Define that organization without changing PS2 payload compatibility.

The first release uses native PC saves and supports importing and exporting PS2
saves through both memory-card images and individual exported save files. The
exact supported image and individual-file formats, slot mapping, native save
library metadata and write recovery remain to be specified. Interoperability acceptance must include
loading an imported PS2 save in the port and loading a port-exported save in the
original game through an agreed PS2 save container workflow.

Native PC saves provide a shared local character library with capacity beyond
the original PS2 slot limit. The native library is independent of PS2 save
containers; the PS2 format retains its original capacity. How users select
characters for export into those slots remains to be specified.

Original save points remain available. Autosaving is optional and writes a separate
recovery save, leaving manual saves untouched. It is enabled by default and can
be disabled. When enabled, it runs at safe stage transitions and after explicit
saves. In co-op, both manual saves and recovery saves capture every participating
character together from the same coherent session state. When a recovery save is
newer than the manual save, offer both "Continue recovery" and "Load manual save",
showing their timestamps. Do not silently choose or overwrite either save.
The exact safe transition boundary and storage transaction format remain to be specified.

## Proposed fidelity requirements

This section is proposed for review.

- Original combat rules, progression, item statistics, drops, quest gates and
  difficulty behavior remain the default.
- Simulation timing remains consistent with retail behavior when display refresh
  rate or rendering performance changes.
- Rendering preserves original composition, animation, materials, lighting, fog,
  effects and UI behavior, with explicit rules for higher resolutions and aspect ratios.
- Host control mappings preserve the original game actions. Convenience inputs
  such as keyboard or D-pad menu navigation may supplement them.

## Agreed bug compatibility policy

Assess original bug fixes individually while preserving original gameplay rules
and balance. Gameplay-changing fixes are optional. Each fix needs a documented
behavior difference and a regression case; the defaults for individual fixes
remain to be decided through that review.

## Agreed control requirements

The first release supports rebindable gamepads and keyboard controls, with mouse
support for menus only. Gameplay actions retain their original meaning. Specific
bindings, gamepad families, button prompts, dead zones and local co-op device
assignment remain to be specified.

## Agreed focus behavior

Alt-Tab leaves the game running in the background. Gameplay, animation,
rendering and audio continue when the window loses focus; returning focus
requires no resume key. FMVs retain their existing continuous playback.

Manual pause and controller-disconnect holds remain independent of window focus;
switching away and back must not dismiss them. Paused time must not produce
catch-up gameplay updates. Waking from system suspend must leave the session
paused until explicit resume; suspend detection and host device/resource
restoration remain outstanding. Manual-pause audio behavior remains unresolved.

## Agreed missing texture behavior

Apply an obvious debug texture when a requested texture is missing, so the
affected surface clearly identifies incomplete content. Record the unresolved
asset name and relevant model/material in diagnostics. The exact debug pattern
and treatment of other missing or corrupt asset types remain to be specified.

## Agreed failure handling

If an essential asset is missing or an operation fails, stop the affected
operation, explain the problem and offer retry/back. A failed save retains the
current session so the player can retry without losing unsaved progress. Preserve
the last valid on-disk save; do not report a failed or partial write as successful.
Back must not silently discard an active session after a save failure.

The missing-texture debug fallback remains the agreed recoverable visual case.
Errors that prevent safe stage loading must not publish a partially loaded world.
Exact recovery flows for each operation remain to be specified.

## Agreed loading-screen behavior

Present a loading screen when entering the lobby/hub, including on fast loads.
Keep the window responsive while destination assets prepare, and keep the loading
presentation visible for the duration of preparation on slower hardware. Activate
the destination only after successful loading; failed loads follow the agreed
retry/back behavior. Recreate the original stage-specific preview and localized
stage name from its loading scene, with the recovered loading-node reveal and
completion timing. Normal runs add no artificial inspection delay beyond those
original timing rules.
Provide an opt-in `--loading-min-seconds` inspection argument, including a
10-second minimum, without delaying asset preparation or advancing arrival.
The current adapter and remaining visual-parity work are documented in
[Stage loading](stage-loading.md).

## Agreed script execution

Run the original game scripts through a compatible Lua 4.0.1 runtime. Original
script behavior is the launch baseline; modern-Lua conversion and replacement
with native code are outside the agreed launch approach. Preserve the original
native bindings and script scheduling behavior. The runtime source, host build
integration, bytecode compatibility and error routing need explicit engineering
contracts and verification against the [recovered Lua integration](../../docs/engine/script-engine-lua.md).

## Agreed asset setup requirements

On first launch, players select a USA PS2 ISO. The port automatically extracts
and validates the required game assets. The source ISO is read-only; extracted
assets are kept separately. Additional game regions follow later.

The extraction destination, supported disc revisions, validation rules, progress
reporting and recovery from interrupted extraction remain to be specified.

## Agreed platforms and distribution

Launch targets desktop Linux, Windows and Steam Deck. Steam Deck validation
covers controls, UI readability and performance on a physical device. A device
is available for project testing; validation remains outstanding.

Provide both portable download-and-run distributions and installed distributions.
Specific package formats, minimum OS versions and bundled dependencies remain to
be specified. Both distribution types must support the same game and save formats.

## Agreed user storage locations

Use per-user storage by default for both installed and download-and-run builds.
Native Linux and Steam Deck builds follow the [XDG Base Directory Specification](https://specifications.freedesktop.org/basedir/0.8/).
The table shows defaults when the corresponding XDG variables are unset or empty.

| Content | Linux and native Steam Deck default | Windows default |
| --- | --- | --- |
| Main configuration file, including control bindings | `~/.config/dw4/config.ini` | `%LOCALAPPDATA%\DW4\config\config.ini` |
| Native save library and recovery saves | `~/.local/share/dw4/saves/` | `%USERPROFILE%\Saved Games\DW4\` |
| Extracted original assets | `~/.local/share/dw4/assets/` | `%LOCALAPPDATA%\DW4\assets\` |
| Asset overrides | `~/.local/share/dw4/mods/` | `%LOCALAPPDATA%\DW4\mods\` |
| Disposable generated caches | `~/.cache/dw4/` | `%LOCALAPPDATA%\DW4\cache\` |
| Logs and diagnostic state | `~/.local/state/dw4/` | `%LOCALAPPDATA%\DW4\state\` |

### Directory resolution

Linux resolves configuration under `$XDG_CONFIG_HOME/dw4`, saves/assets/mods
under `$XDG_DATA_HOME/dw4`, caches under `$XDG_CACHE_HOME/dw4`, and diagnostic
state under `$XDG_STATE_HOME/dw4`. Ignore relative XDG values and use the standard
fallbacks. Resolve the user's home directory rather than hard-coding an account
name or a Steam Deck installation path.

Windows resolves the bases using `FOLDERID_LocalAppData` and `FOLDERID_SavedGames`
through the Known Folder API. The displayed paths are the typical defaults;
folder redirection must be honored. The port chooses Local AppData for settings
including machine-specific display and device configuration. These Windows base
folders are defined in Microsoft's [Known Folder reference](https://learn.microsoft.com/en-us/windows/win32/shell/knownfolderid).

Keep manual saves, recovery saves and retained save backups beneath the save root
in separate `manual`, `recovery` and `backups` subdirectories. The character
library and transaction metadata also belong beneath that root; exact filenames
and schemas remain to be specified. Clearing caches or resetting configuration
must not remove saves.

### INI configuration files

User configuration files use the `.ini` extension and UTF-8 text, with named
`[sections]` and `key=value` settings. The main file is `config.ini` in the resolved
configuration directory and includes control bindings. Any additional configuration
files introduced later must also use INI format. Users can edit configuration
outside the game; settings changed through the game are persisted in the same format.

Warn about invalid settings, use the corresponding defaults, and retain valid
settings. When persisting an in-game change, preserve comments and unknown entries
and update only changed settings. Do not regenerate the whole file or discard
user annotations.

The current camera/light implementation defines the section/key schema, parser,
comment, duplicate-key, unreadable-file and write rules in
[Options configuration](configuration.md). Future controls and host display keys
still need schemas; this implementation does not complete all user-storage requirements.
Configuration format does not determine the native save format.

### Portable storage mode

Provide an explicit portable-storage option. The current configuration implementation
opts in through `--portable`. In that mode, use a `userdata` directory beside the executable:
`config`, `saves`, `assets`, `mods`, `cache` and `state` beneath it. Resolve this
root from the executable location, independently of the launch working directory.
The save subdirectory uses the same manual/recovery/backup layout as normal mode.
The main portable configuration file is `userdata/config/config.ini`.

Resolution of the other portable storage directories remains outstanding.

A portable distribution uses normal per-user paths until portable storage is
explicitly enabled. If the selected root is not writable, show the failing path
and require a usable location; do not silently switch save libraries. Switching
storage modes must not move or merge existing saves without an explicit user action.

### Storage lifecycle and user access

Create required directories on first use without administrator privileges.
Support paths containing spaces and non-ASCII characters. Keep extracted assets
separate from the source ISO, and allow selection of a different asset directory
for larger libraries or removable storage. PS2 imports read user-selected files;
exports write to a user-selected destination.

Settings should expose the resolved configuration, save, asset and override
locations and provide actions to open them. Application updates preserve user
storage; uninstall retains saves and configuration unless the user explicitly
requests their removal. The same save format applies in normal and portable modes.

### Storage validation

Verify default and overridden XDG paths, redirected Windows Known Folders,
portable mode, changed launch working directories, non-ASCII paths and write
failures. Verify that updates, cache clearing and configuration resets preserve
manual and recovery saves. These are proposed release checks, not claims that
storage management is already implemented.

## Agreed performance baseline

Target stable 60 fps on Steam Deck at its native display resolution, including
four-player local co-op. Validate on a physical device. Desktop performance
targets will be set separately. The Steam Deck model, power settings and exact
test configuration must be recorded with benchmark results.

### Proposed performance verification

The 60 fps cadence gives an approximately 16.67 ms frame interval. Measure
simulation, rendering and presentation costs separately, including frame-time
spikes. An average of 60 fps alone does not establish stable performance.

The test set should cover front-end operation, stage traversal and transitions,
combat with effects, and one- through four-player sessions. Include repeated
stage loads and longer sessions to expose resource growth. Loading transitions
need separate timing criteria rather than being silently excluded from results.
Exact test routes, allowed frame-time variation, loading limits and memory
budgets remain engineering decisions to establish through measurement.

## Agreed mod support

Launch includes a documented asset-override folder. Fuller mod tools follow later.
The override lookup rules, supported asset types and validation behavior remain
to be specified. An in-game mod manager and a gameplay mod API are outside the
agreed launch requirements.

## Proposed runtime architecture

These contracts are engineering proposals for review, rather than descriptions
of completed functionality.

| Boundary | Responsibility and contract |
| --- | --- |
| Application | Own setup, configuration, window lifecycle and transitions between front end and gameplay. |
| Game session | Own active players, world state, progression and gameplay clocks; disconnect pause freezes gameplay. |
| Input | Translate assigned devices and rebindings into original game actions for each player. |
| Simulation | Advance recovered game logic and scripts in verified retail order at the 60 Hz gameplay cadence. |
| Rendering | Consume scene and UI state at the agreed cadence, applying aspect-ratio and HUD policies without advancing gameplay. |
| Media | Schedule 30 fps FMV playback against its media clock; maintain audio/video synchronization independently of gameplay ticks. |
| Assets | Resolve original logical asset names through validated extracted archives and the documented override layer. |
| Saves | Capture coherent character/progression state, keep manual and recovery saves separate, and translate selected characters to and from PS2 save containers. |
| Platform | Supply windowing, devices, files, timing and audio behind host interfaces. |

The frame scheduler uses elapsed host time to determine due simulation ticks;
rendering may be skipped while due ticks advance. This decouples gameplay speed
from presentation without requiring variable-step gameplay logic for launch.
Pause and resume reset host-time accounting so paused time does not create a
backlog of gameplay updates. Tick catch-up limits and sustained-overload behavior
require measurement against the eventual gameplay runtime.

### State and memory ownership

Recovered engine objects use the established four-byte arena reference model.
Host services own their native resources through separate structures; host
pointers must not be truncated into recovered four-byte fields. Arena lifetime,
reference checks and allocation failure behavior need explicit contracts before
expanding the gameplay runtime.

### Stage transitions and saving

Stage loading prepares and validates the destination before publishing it as the
active world. The implementation must define when the transition becomes safe
for a recovery save and capture all participating characters from one coherent
session state. Manual and recovery writes should preserve the last valid save
if writing is interrupted. Failure handling and file replacement guarantees
require platform-specific verification.

Co-op saves use a session snapshot that includes all participating characters.
Publish it as a complete save transaction so interruption cannot expose a mixture
of old and new character states. This is a proposed storage contract for the
agreed requirement to save participants together; the native format must define
how recovery and the shared character library reference that transaction.

### Future online play

Device input and session updates should have explicit boundaries so later online
work can be added without scattering networking through the renderer or asset
readers. The launch architecture makes no promise of deterministic replay,
rollback or a particular networking model; those require a separate design and
behavioral validation.

## Proposed reference validation requirements

Reference comparisons must specify the same game state, input sequence, timing,
camera and output geometry. A reference capture or savestate is a validation input;
the released game must run independently of emulator captures and analysis tools.

Widescreen must preserve the original enemy-generator activation logic. The
[recovered spawn system](../../docs/systems/enemy-spawn-system.md)
documents script-controlled generators with direct, player-range and timer start
conditions. Preserve those conditions rather than introducing a camera-visibility
spawn rule. Any separate visibility-dependent gameplay behavior must be checked
against its recovered implementation before changing it.

### Save interoperability matrix

Test both memory-card images and supported individual save files through the
following routes:

1. Original PS2 save to native library: verify character identity, stats,
   inventory, progression and the ability to continue gameplay.
2. Native character to PS2 save: verify acceptance by the original game and
   equivalent character/progression state after loading.
3. Import, play, save and export: verify that supported state survives the full
   round trip through both interchange routes.
4. Multiple-character export: verify selected characters map to valid original
   slots without exceeding PS2 format capacity.

### Proposed release checks

| Check | Required evidence |
| --- | --- |
| Recovery provenance | Imported recovered modules identify their source and behavior checks; decompilation identity checks remain in the separate matching build. |
| Asset decoding | Native readers agree with independent reference decoders on supported formats and reject truncated or malformed inputs. |
| Gameplay fidelity | Controlled input/state comparisons cover timing, combat, progression and co-op behavior against retail. |
| Presentation | Matched reference frames verify original composition and effects; aspect-ratio tests verify horizontal expansion, HUD layout and FMV borders. |
| Persistence | Native save reloads, co-op transaction interruption checks and the PS2 interoperability matrix pass. |
| Platforms | Portable and installed builds pass setup, controls, playback and gameplay tests on Windows, Linux and physical Steam Deck. |
| Performance | The recorded Steam Deck configuration meets the agreed frame-time criteria across the benchmark routes, including four-player play. |

## Proposed implementation milestones

These milestones organize delivery toward the complete-game target. Completing
a milestone does not replace the final release acceptance criteria.

| Milestone | Exit condition |
| --- | --- |
| Runtime foundations | Explicit clock, input, memory and platform contracts; front-end-to-world lifecycle operates through them. |
| Playable vertical slice | One representative stage supports movement, combat, enemies, loot and progression using original assets and rules. |
| Persistence and local co-op | Native saves, recovery saves, PS2 interchange and main-menu joining work for one through four players. |
| Complete game | All original stages and progression paths work through the ending, with agreed character/difficulty coverage. |
| Release validation | Supported display modes, Steam Deck performance, packaging, setup and asset overrides pass the release matrix. |

## Requirements to resolve

| Area | Decisions required |
| --- | --- |
| Fidelity | Defaults for individual bug fixes and permitted presentation improvements. |
| Multiplayer | Controller ownership, exact leave handling, disconnect dismissal and simultaneous character selection. |
| Controls | Bindings, gamepad families, prompts, dead zones, device assignment and disconnect handling. |
| Display | Resolutions, ultrawide range, fixed-composition scenes, UI scale and margin ranges, window modes, frame pacing and sustained simulation overload. |
| Saves | Native library organization with unchanged PS2 gameplay fields, library capacity and management, safe autosave transition boundary, co-op transaction format, exact PS2 image/file formats, export slot mapping, recovery and write guarantees. |
| Lifecycle | Suspend detection/device restoration and manual-pause audio handling. |
| Assets and installation | Supported USA revisions, extraction destination, validation, setup recovery and later region support. |
| User storage | Finalize portable opt-in mechanism, INI section/key schema and parser rules, save transactions and storage migration. |
| Mods | Override lookup rules, supported asset types, validation and conflict handling. |
| Runtime architecture | Ownership and lifecycle of world state, entities, scripts, events, clocks and stage transitions. |
| Scripting | Compatible Lua 4.0.1 runtime source/build integration, bytecode handling, native bindings, scheduling and error routing. |
| Memory | Arena growth, handle lifetime, reference resolution and the boundary with host-owned objects (proposed contract: [arena object model](arena-object-model.md)). |
| Rendering | Scene submission contract, effects coverage, backend selection and fidelity tolerances. |
| Audio and video | User audio settings deferred; music and sequence playback, sound ownership, mixing, movie synchronization and device changes remain open. |
| Platforms and builds | Detailed build/dependency policy deferred; minimum OS versions, architectures, compiler/dependency versions, package formats and Steam Deck test coverage remain open. |
| Failure handling | Debug texture pattern and operation-specific retry/back flows for assets, backends, extraction and save failures. |
| Performance | Steam Deck test configuration and frame-time tolerances, desktop targets, loading limits and memory budgets. |
| Verification | Required automated checks, retail comparisons, platform coverage and completion evidence. |

## Proposed release acceptance

These are candidate acceptance criteria, pending the subsystem decisions above.

1. A normal launch reaches the original front end and allows character creation or
   loading, then enters gameplay without analysis flags.
2. A player can complete the game, save progress, exit, relaunch and continue.
3. Original content and progression work across the agreed character, difficulty
   and multiplayer coverage matrix.
4. Supported PC controls and display modes work without changing gameplay timing.
5. Local co-op works with one through four players across the agreed gameplay
   coverage. Players can join from the main menu and cannot join during gameplay.
6. High-resolution 4:3, 16:9, 16:10 and agreed ultrawide modes preserve gameplay
   at 60 fps. Wider gameplay views preserve vertical framing and reveal more world
   horizontally. HUD margins and scale are adjustable. FMVs play at 30 fps with
   synchronized audio and preserve their original aspect ratio.
7. PS2 save import and export pass the interoperability checks above.
8. Rebound gamepad and keyboard controls work in gameplay; menu mouse input works
   without requiring mouse gameplay controls.
9. First-run setup extracts and validates assets from a supported USA ISO without
   modifying the source image.
10. The native library stores more characters than the PS2 slot limit, and local
    co-op players can select their characters from that library.
11. Original save points work with autosaving disabled; enabling autosaving provides
    a separate recovery save at safe stage transitions and after explicit saves,
    without replacing manual saves. Autosaving is enabled on a fresh configuration.
12. Disconnecting a participating player's controller pauses the whole session;
    gameplay resumes only after reconnection or that player's departure.
13. Linux, Windows and Steam Deck release builds pass the agreed functional,
    fidelity and performance checks, including stable 60 fps at native resolution
    on physical Steam Deck in four-player co-op.
14. Portable and installed distributions support first-run setup, normal gameplay,
    configuration and save interoperability.
15. The documented asset-override folder can replace supported assets without
    changing the extracted originals.
16. On hardware meeting the simulation budget, induced rendering stalls skip
    presentation frames without changing gameplay speed or advancing paused time.
17. Co-op manual and recovery saves capture all participating characters from the
    same session state. Interrupted-write checks verify that a partial transaction
    cannot become the active save.
18. Configuration loads and persists as INI on all supported platforms and in
    portable mode, including settings edited outside the game. Invalid values
    fall back individually with a warning; settings writes preserve comments,
    unknown entries and unchanged settings.
19. Alt-Tab keeps gameplay, animation, presentation and audio running in the
    background; returning focus requires no resume key. Focus changes retain
    independent manual/disconnect holds. Waking from suspend requires explicit resume.
20. Missing textures use the debug fallback and report the unresolved asset in
    diagnostics.
21. A newer recovery save prompts a timestamped choice between recovery and
    manual state without silently replacing either.
22. Original scripts run through the compatible Lua 4.0.1 runtime with verified
    native-call and scheduling behavior.
23. Failed operations provide retry/back; failed saves retain the current session
    and last valid save. Failed stage loads do not activate partial world state.

## Current implementation boundary

The host includes Lua 4.0.1 and loads original named bytecode. Boot executes
original shared definitions and boot scripts after authored title/lobby file-list
preparation, including queued assets. Title entrance audio executes an original sound event.
The DM service boundary passes controlled title traces against retail scheduler
instructions. The live 60 Hz pump ticks DM before model adapters and holds script/service
clocks on manual pause and assigned SDL-pad disconnect. Focus changes leave
the simulation and audio running. A native receiver
registry and timed SD queue route session SOUND calls; receiver selectors,
timer expiry and ordering have controlled retail instruction comparisons.
Prepared scene-owned model slots, title/static-camera services, authored lobby
window commands and lobby camera queries expose native controller state.
Original title waits and Digi-Elf arrival actor services pass integration checks;
actor command/channel/query traces match controlled retail instructions. General model programs, renderer
traversal and live scene orchestration remain open. See [Scene controller services](controller-services.md). Coordinated
stage-owned SD/Lua/DM teardown is implemented. General native
bindings and scene/gameplay script orchestration remain outstanding; see [Original Lua execution](lua-integration.md).

The port has native asset readers and a front-end implementation integrating a
recovered title controller. The current created-card login executes the Main Lobby's original start/first
scripts through native owners, with collision-backed walking, player/Digi-Elf
motion rendering, greeting text and HUD/camera/control/material restoration.
See [the lobby contract](lobby-gameplay.md) for validation and limits.
Combat, general traversal/progression and saving remain outstanding; this lobby
milestone does not meet the complete playable-game requirement. See the [title integration record](title-controller.md#login-hand-off)
and [boot contract](boot-contract.md) for the detailed boundaries.

FMV soundtracks, original title/menu audio and bounded lobby arrival music,
ambience and terminal beep run through the
[front-end audio adapter](audio-playback.md). Field stages prepare their whole sound-pack catalogue
([stage catalogue](audio-playback.md#stage-sound-catalogue-and-the-gameplay-set)); general gameplay audio parity,
exact retail mixing/event scheduling and user audio controls remain outstanding.

## Decision record

Decisions in force:

- Retarget the port's game logic onto the decomp's authoritative structs held in arena memory, fight rules first, then the port-native game types module by module; the contract and plan are in [arena object model](arena-object-model.md) (proposal until its phases have exit evidence).
- The native save library stores the raw PS2-format save file as `saveimage.c` writes it (`BASLUS-20836savedata`, 81,920 bytes) under `$XDG_DATA_HOME/dw4/saves` (else `~/.local/share/dw4/saves`); memory-card slot N is character slot N of that file; every write is atomic and keeps the previous file as `.bak`; a damaged file is refused, never overwritten; no PS2 memory-card container, icon or `.psu`/`.max` export in the first release. See [Save Keeper](save-keeper.md).
- Run gameplay, rendering and audio in the background on focus loss; returning focus requires no resume key. Manual/disconnect holds and the separate suspend requirement remain.
- Require GPU rasterization/compositing during normal play; GPU failures are explicit, and CPU rendering is reserved for selected diagnostic/reference runs.
- Add an opt-in loading-screen minimum-duration argument for visual inspection; normal loads have no added delay.
- Show a responsive loading screen when entering the lobby/hub, retaining it until destination preparation completes.
- Loading screen: recover the original stage-card selection and node runtime, and render its preview/name artwork. The native transition preserves the authored play-limit wait before publication; the optional minimum remains an additional inspection hold.
- First release targets a faithful complete game with PC controls and display options; gameplay changes and new content follow later.
- Original local co-op ships at launch; online co-op follows later.
- Higher resolutions and widescreen ship at launch; gameplay runs at 60 fps and FMVs at 30 fps.
- Native PC saves and PS2 save import/export ship at launch.
- Original bug fixes are assessed individually; gameplay-changing fixes are optional.
- Rebindable gamepads and keyboard ship at launch; mouse support covers menus only.
- First-run setup automatically extracts and validates a selected USA PS2 ISO; other regions follow later.
- Widescreen reveals more world horizontally while preserving vertical framing; launch supports 4:3, 16:9, 16:10 and ultrawide.
- Local co-op uses a shared character library with native capacity beyond the original PS2 save limit.
- Gameplay HUD anchors to screen edges with adjustable margins and UI scale.
- FMVs preserve their original aspect ratio; AI or algorithmic upscaling may be explored later.
- Retain original save points and provide optional autosaving.
- Autosaving writes a separate recovery save at safe stage transitions and after explicit saves; manual saves stay untouched.
- A participating controller disconnect pauses the whole session until reconnection or that player's departure.
- Steam Deck is a launch target; a physical device is available for testing.
- Launch includes a documented asset-override folder; fuller mod tools follow later.
- Provide both portable and installed distributions.
- Autosaving is enabled by default and can be disabled.
- Preserve gameplay speed when rendering falls below 60 fps by skipping rendered frames as needed.
- Future unlocked FPS work includes auditing frame-dependent logic and converting suitable updates to delta time while preserving gameplay behavior.
- Local co-op joining occurs only in the main menu; join/leave behavior otherwise follows the original game, with the agreed disconnect resolution.
- Co-op saves capture every participating character together from the same session state.
- Target stable 60 fps on Steam Deck at its native resolution, including four-player co-op; desktop targets are set separately.
- PS2 save interchange supports both memory-card images and individual exported save files.
- Use the documented Linux and Windows user storage locations, with explicit portable storage mode.
- Configuration files use INI; the main file is `config.ini` in the resolved configuration directory.
- Preserve PS2 save logic and gameplay save entries; no gameplay schema migration is planned.
- Missing textures use an obvious debug texture.
- User audio settings and detailed build/dependency policy remain deferred decisions.
- Waking from suspend leaves the game paused until explicit resume.
- Invalid INI settings warn and fall back individually; valid settings remain in use.
- Settings writes preserve INI comments and unknown entries and update only changed settings.
- A newer recovery save offers timestamped recovery/manual choices.
- Run original scripts through a compatible Lua 4.0.1 runtime.
- Failed operations stop with an explanation and retry/back; save failures retain the current session.
- The first options configuration implementation uses `[options]` camera/light tokens and `--portable`; parser and selective-write behavior are documented in Options configuration. Other user-storage subsystems remain outstanding.
