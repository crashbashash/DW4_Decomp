# Status/menu ownership

`src/subwindow.c` owns prepared `beNDMWStatusInfo` RAM slots and their SUBWND
receivers. `src/menuwindow.c` supplies the recovered parent/child update boundary.
The dialogue owner creates and ticks this service in the normal session and
releases it before prepared packs. The concrete STATUS root, WindowTitle/Title00
and WindowSelect state machines run through owned native window callbacks in
`src/statusctrl.c`.

Normal boot installs the complete STATUS factory for the single created player
after the lobby introduction, including equipment, FOLDER and skill views,
authored drawing and scene/player/HUD restoration. The equipment, FOLDER and
skill controllers, the root assembly and the scene lifecycle are in
[submenu contract](status-submenus.md); the title/selection views and stat
commands are in [STATUS views](status-views.md); the records are in
[player records](player-records.md).

## Recovered contract

The retail manager module is `0x003d58f0..0x003d9ddc`. Initialization
`0x003d5960` clears the RAM active byte at +20. Message handler `0x003d60e0`
uses the seven command keys from the enum at `0x004ca090`: GENERATE, REMOVE,
UPDATE, GETSHOPDATA, ONPREVIEW, OFPREVIEW and ISRUN. The native owner implements
the GENERATE/REMOVE/ISRUN lifecycle and dispatches UPDATE, ONPREVIEW and
OFPREVIEW to the factory's stat callbacks (see
[registered SUBWND stat commands](status-views.md#registered-subwnd-stat-commands)).
GETSHOPDATA has no native handler.

Mode enum `0x004c9410` maps STATUS=0, XDATA=1, LABO=2, BANK=3, CNOS=4, DISK=5,
WPU=6, APU=7, CHIP=8, JUNK=9 and CARD=10. `/I<n>` supplies the owning player;
without it the integer argument defaults to zero. The host validates player
indices 0 through 3 and exact mode names. Repeated GENERATE while active is
ignored before parsing, preserving the existing player, mode and window tree.
Inactive GENERATE resets RAM state/sub/delay/latch and marks it active before
the first update. Retail stores player/mode and a root window on the manager,
not in the serialized RAM payload; the native owner preserves that split
with typed manager/RAM instances and a four-byte root handle.
No host pointer enters a recovered four-byte reference.

REMOVE resets an existing root to closing state 2 and clears its subordinate
counters. If active state is published before a root exists, retail releases its
world-disable flag and enqueues another SUBWND REMOVE with delay one. The native
owner preserves active state and uses the real SD queue for this retry. This
is not immediate completion. The concrete factory's scene lifecycle must handle
world/gameplay gating; it must not pause the menu's own simulation clock.

Retail manager update `0x003d59b0` constructs the root in state zero, then
updates it in the same call. It finishes when the root's active field is zero,
clears RAM state and restores scene services/player resources. STATUS uses
constructor `0x003bb1d0`; LABO uses `0x003b7750`; CARD uses `0x003b7eb0`; the
remaining modes use `0x003b8d90`. Their menu-specific state machines are separate
from this manager boundary.

Window update `0x003f6490` calls the active parent's virtual update first. If
that callback closes or deactivates it, all children with state below two enter
closing state and reset sub/delay/latch. Children update recursively in publication
order; inactive children are released and compacted out of the list. Descendant
callbacks that append siblings do not expand the current iteration limit.
A particular parent controller must retain its own active flag through any
child/model close waits; the recursive helper alone does not enforce that wait.

## Native lifetime and dependency boundary

The scene builds one receiver per authored RAM-list row, using the list index
as selector, and validates each row's class before publication. Duplicate info
collection rows do not duplicate ownership. Prepared ML11 has one status slot;
its serialized RAM number is not its accepted selector zero. Registry active
eligibility changes immediately after GENERATE and final completion, including
inactive-selector queries. DMgetCount reads the owner's numeric ISRUN through
the existing Lua boundary; queries and drawing never update menu state.

A `dw4_subwindow_factory` preflights the required records/assets and returns a
private, owned `dw4_menu_window` tree. Failed preparation frees that private tree
and leaves the inactive receiver unchanged. Its begin/end callbacks implement
the specific menu's scene freeze, layer/audio changes and player restoration;
the optional `activate` callback runs at accepted GENERATE (see the
[STATUS scene lifecycle](status-submenus.md#status-scene-lifecycle)).
Factories cannot be replaced while native slots are active or ticking. Window
callbacks may append owned children or request close; sharing and ancestor cycles
are rejected. Failed begin/update/end latches the owner for scene recreation,
retaining active completion state so Lua cannot continue as if the menu succeeded.
Scene reset cancels the SD scope before owner teardown; teardown releases both
prepared and installed trees. Borrowed-owner routing remains available
for isolated external services and tests.

The production owner deliberately has no placeholder factory. A complete
factory depends on session-owned GAMERAM GETPLAYER/property folders, inventory
and equipment records, character/save ownership, native preview models and the
specific menu state machines. The session supplies independent
[player property folders](player-records.md) and identity/weapon SYS queries.
Production fresh-player, inventory/stat and transaction owners
([player transactions](player-transactions.md), [player stats](player-stats.md))
and scene restoration back the normal mode-zero factory for the created first
player in the lobby. Prepared tests retain broader four-slot tree coverage.

## Arena ownership

Each native window's active byte, four counters, parent link and ordered child
handles/count live in `beNDMWWindow`-derived objects and `beNDMWWindowList` in the
session arena ([#2728](../../docs/findings/findings-2501-2750.md#f2728)/#2729). `dw4_menu_window` is a host facade for
callbacks/resources and child-owner lookup. `dw4_menu_window_data` resolves its
handle; `dw4_menu_window_count` reads the typed list. Tree growth preflights both
allocations before publication, pruning clears vacated slots, and recursive
teardown releases arena objects. Native ownership stays exclusive and the callback
boundaries are unchanged.

The STATUS root owns a real `beNDMWStatusCtrl00`. Its return selection, retained
menu and child-count snapshot use `_retCode`, `_statusMenu` and `_nowProcKazu`.
The root owns no host scalar-state buffer. Concrete title/selector
views use their reflected classes and temporary scalar adapters;
`dw4_statusview_context.parent_window` sends production root selection directly
to the arena. Legacy scalar selection sinks remain for isolated tests and the
per-feature adapters that have not been migrated.
Parent results publish before the following completion query, and later callback
writes survive. The STATUS controller regression checks both properties; a
negative build that restores delayed publication is rejected.

Each SUBWND slot owns `beNDMWStatus` and `beNDMWStatusInfoRam` instances. Manager
mode/player and the installed root's handle use `_subWndNo`, `_whoGenerate` and
`_windowPro`; activity/counters and info/manager links use the RAM fields.
Private prepared trees belong to host preparation until installation.
`dw4_subwindows_at` returns a diagnostic snapshot by value, and root-state
queries return typed arena views rather than host mirrors.

The standalone oracle builds include the authoritative headers and arena
dependencies through `tools/native_shared.py`; the window FFI resolves game
fields through handles instead of assuming a host facade layout.
See [arena migration boundaries](arena-object-model.md#shared-windowcontroller-arena-state)
for the concrete shop/submenu state and the general model-controller work that
remains.

## Concrete STATUS controllers

`src/statusctrl.c` ports STATUS root `0x0040de80`, WindowTitle `0x00424160`
with Title00 initializer `0x00424230`, and WindowSelect `0x004233f0` into
scalar callbacks and owned native window trees. STATUS creates Title00 first;
after i_stback leaves SQ_OPEN it hides BG01/BG02/BG03/GM01/GM03 and creates
Title01–03. It waits until i_messwn leaves SQ_STOPEN before creating Select00.
Title00 owns the opening background and remains the first child when cancellation
closes children after index zero. Factory identities follow their registered
metadata globals, not the preceding GetMetaObject symbol in address order; the
root does not create Title04's extra border.

The root remembers selections 0–2 and routes them to equipment, folder or skill
children. Cancellation preserves the last non-cancel selection. Child completion
uses the actual compacted list count. Selection creation advances its delay to
two in the same update; selector completion enters close and checks completion
in that same update. Root/title close stages retain their separate update
boundaries. Root cancellation closes children after the initial title, waits
for i_messwn to stop, restores the five layer masks, then closes the remaining
tracked models/text/tree. Completion waits for backend model state and actual
child pruning; it never uses a guessed elapsed duration.

The window owner creates Select00 callbacks itself. SELECT_INIT delegates its
record/text/model setup (`0x00423760`) to the backend: three choices,
(-83,209,0), i_stcursor02 and original txt_status.lua. The native implementations
of these initializers are in [statusview.c's owning contract](status-views.md),
which also owns Title01's dynamic stat refresh/comparison through SUBWND UPDATE's
Unicode-name/stat projection and comparison snapshot. Prepared database lookup and
equipment/folder/skill CREATE operations are backend dependencies. They must
append owned concrete children before returning. Close/text/completion callbacks
receive the owning child kind, keeping per-window resources separate. Failed
callbacks return errors while the lifecycle owner retains its completion hold.

The composition of this root with its real children is
[complete STATUS root assembly](status-submenus.md#complete-status-root-assembly).

## Live factory wiring

The live hub factory accepts mode 0 (STATUS), mode 1 (XDATA, see
[XDATA shop](xdata-shop.md)), mode 2 (LABO, see [Digi-Lab](labo-shop.md)),
mode 3 (BANK, see [NPC bank](bank-shop.md)), mode 4 (CNOS, see
[NPC appraiser](cnos-shop.md)), mode 5 (DISK, see [Digi-Disk shop](disk-shop.md))
and modes 6–9 (WPU/APU/CHIP/JUNK, see [equipment shops](equipment-shops.md)) for
the player named in the payload (the owner, see
[Owner by player slot](#owner-by-player-slot); the hubs only have player zero).
It rejects other modes, unjoined players and generator-bearing scenes.

The engine installs the concrete STATUS factory after lobby publication.
It supplies player/stat/database dependencies, record-backed weapon replacement,
health/HUD restoration, lobby sound dispatch and borrowed window presentation
peers. Post-intro Start admission, menu input sampling and overlay drawing are
connected, so Start in a normal boot reaches this menu. The live adapter presents
one joined player; prepared menu owners retain their four-slot validation.

Rendering and audio:

- Normal STATUS model/font rasterization uses a persistent session-owned GPU
  renderer; GPU failure is explicit. CPU drawing is retained for selected
  reference runs. The menu-model renderer is released before its borrowed
  controllers/scene.
- The engine honors BG02 eligibility instead of always drawing the bounded world
  under STATUS.
- Lobby audio metadata prepares in headless runs as well as live runs; playback
  starts only for a live audio session.
- The factory routes generic and specialized-window ACTION events to original
  lobby beSeData sound lookups; lobby audio preparation collects those mappings.

Records and restoration:

- Health publication carries the recovered ADDHP-zero dead-HP guard
  ([health boundary](player-records.md#live-health-restoration-boundary)) to the
  HUD: suppressed HP publication preserves its meter/digits while MP still updates.
- Empty weapon appearance rejects publication. Normal mode-zero Power supplies two
  actions and prevents selecting an empty first-weapon swap target, so an
  empty/unarmed appearance is not reachable through that valid menu path.

Input:

- STATUS executes its PADINPUT ENABLE command through the shared registered input
  owner. Disabled menus read neutral input while raw controller sampling continues.
- Paging receives trigger/repeat signals for analog directions and actual
  right/left digital bits, with the original ten-update first delay and
  six-update repeat interval. Shoulder buttons retain their own digital bits.
- STATUS and native dialogue use the recovered radial classifier and overlapping
  direction sectors for partial stick deflection; repeat delivery remains ten/six.
  Digital/keyboard menu convenience feeds the same axis adapter. Title-adapter
  navigation remains its separately documented behavior.

### Generator dependency

Retail GENERATER ONFREEZE/OFFFREEZE changes existing generator Work +8; its
update skips spawn scheduling while that Work flag is set. It does not freeze
the arrival ring effects. The fully prepared title and lobby each have zero
beGeneraterInfo entries. STATUS checks that roster before admission and uses the
verified no-Work behavior instead of storing an unused generator flag.
Generator-bearing scenes require their real spawn owner before this factory can
be used; this guard is not a general generator implementation.

## Owner by player slot

The retail shops start their window with
`SUBWND nil 0 GENERATE "<MODE>/I<g_messPlayerNo>"`, so the payload's player index
names the owner: the window tree, its stat owner (`dw4_statusstats_refresh`, the
chip quote preview) and its restoration all run on that player's records ([#2850](../../docs/findings/findings-2751-3000.md#f2850)).
`hubruntime.c` keeps the index in `h->owner`, set by `status_prepare` (the player
must have `ISUSE`), and uses it for the view context of the STATUS tree and of
every shop service; `status_input`, `status_appearance`, `status_update` and
`status_preview` accept only the owner. Only the owner's pad reaches the menu:
`status_input(player)` returns that slot's repeat-tracked words (`struct hub_pad`,
filled by `dw4_hubruntime_input` for slot 0 and `dw4_hubruntime_input_slot` for
slots 1-3), so another pad's Circle or Start is ignored; a Start while a menu runs
is refused by the scene phase. The weapon appearance is dressed on the owner's own
lobby model (a slot the lobby has not joined returns an error); the restore
publishes the hub HUD for player zero only.

This is plumbing: the hubs run one player. The limits are listed under
[Open items](#open-items).

## Verification

- `make check-dialogue-retail` executes retail `0x003d60e0` for 528 scalar
  GENERATE/REMOVE/ISRUN states and `0x003f6490` for 256 nested-window states.
  Enum/context lookup, virtual menu callbacks and list storage are controlled
  leaves. Comparisons cover command state, deferred-remove requirement, recursive
  update order, counter resets, retained close states, child pruning and releases.
  They do not prove native scene/audio/player restoration or any menu-specific
  controller behavior.
- `make check-dialogue` routes all 11 named modes and all four player arguments
  through the actual native slot/tree owner using controlled menu factories.
  Forty-four open/close cycles verify delayed REMOVE before first update,
  DMgetCount holds, mutation-free queries, factory rejection while active,
  failed preparation, repeated GENERATE and exactly-once tree release. Original
  15-page message and choice helpers and scene-owner reload checks also pass.
  Teardown/failure checks cover pending trees and failed scene freeze/player
  restoration without releasing Lua completion.
- `make check-statusctrl-retail` compares **9,600 STATUS root states and service
  traces**, **15 WindowTitle/Title00 states and traces**, and **72 WindowSelect
  scalar states** against retail instructions. Eight original registration/factory
  traces verify the root's class identities before the 9,600 state/effect
  comparisons. Constructors, model/layer/text services and list storage are
  controlled leaves; Select00 initialization is controlled. These checks do not
  validate authored data titles, original text setup, equipment transactions or
  full-screen output. SELECTCTRL has its separate 19,200-state retail check.
- `make check-statusctrl` exercises the actual owned tree through opening holds,
  selection, a skill child, retained selection, cancellation, delayed model close,
  recursive pruning, Title00 lifetime and callback failure. Its title/submenu/model
  leaves are controlled. The player-record tests and SYS query evidence that share
  these targets are in [player records](player-records.md#verification).
- `make check-menu-arena` verifies class identity, handle links, append/prune
  order, tail clearing, exhausted-arena rollback and complete release, including
  failed child-list growth without partial publication.
- Sixteen original GENERATER command cases verify byte-only Work changes and an
  exact no-op when Work is absent, with enum/query decoding controlled.
- A headless normal boot accepts two open/close cycles; a captured root shows
  populated stats and menu labels after publishing all native scene layers and
  clearing LOADING. Live close verifies held lobby/material/camera/NPC/AI state,
  and the boot route visits equipment, DEVICE and skill before closing/reopening
  the root and verifies a hidden world phase.
- `make check-status-live` drives an SDL virtual controller through the actual
  window event pump, with no engine input script (details below).
- `make check-status-gpu`: the normal STATUS GPU route passes three real
  restoration cycles; an injected draw failure stops explicitly.
- `make check-hubowner` injects player 1 into a live Central (an Agumon record,
  `ISUSE`, `NINZU` 2) and opens `STATUS/I<1>` through the script path: the tree
  shows player 1's name, Circle and a second Start on pad 1 do nothing and the
  world stays held, Circle on pad 2 closes it, a later Start on pad 1 opens
  `STATUS/I<0>` on the first player again.
- `check-statusviews`, the related retail instruction targets and the prepared
  complete STATUS tree (four-player coverage) also cover this module; the command/
  tree and STATUS instruction comparisons hold with the arena-backed windows.

The full native run is `make check check-retail -j8` on Linux with
`SDL_GAMECONTROLLER_IGNORE_DEVICES=<vendor>/<product>`; optional private live-input
checks skip. Sanitizer runs use ASan/UBSan with both set to halt on errors and
`detect_leaks=0`; the arena test separately checks complete block release, and
the focused `check-statusctrl` test also passes with leak detection enabled.

### SDL controller acceptance

In `check-status-live`, button edges and left-stick axes create a character,
complete the lobby greeting, open STATUS, accept a first-slot weapon swap, close
the tree, reopen and close again. The test asserts two actual scene
freezes/restores and a changed nonempty weapon graph. Production focus holds
remain active; the fixture sends an explicit resume event for dummy-window
focus loss. Host scheduling and startup media are controlled leaves; SDL input,
window presentation, menu/record/model/sound owners and restoration are real.

The second opening enters FOLDER through actual SDL stick/button events
and visits DEVICE detail, Key Folder, DISK and currency before returning
to the root. Constructor wrappers observe all four real child owners without
replacing their behavior. The disk route attempts to give an empty fresh disk
and acknowledges the original error; the currency route has no other joined
player. The route also observes two i_messwn OPEN and two CLOSE events resolving
to their original window sound cues before normal teardown, which verifies
the specialized controller-to-audio path with a dummy output device.

Menu navigation is driven with approximately 0.45 stick deflection through actual
controller-axis events. The test verifies suppressed confirm/cancel while PADINPUT
is disabled and restored input afterwards. The fixture anchors menu events to
lobby ticks, so asset preparation can take arbitrary time without missing its
input route, and exits through an SDL quit event after the second restore.

This is a dummy-video/audio regression test, not physical-controller or retail
full-frame parity evidence. Successful cross-player transfers keep their separate
prepared transaction/view checks and are not live co-op coverage.

## Open items

- Window model: complete retail reference-retain cycles and arbitrary list
  replacement are not implemented; some per-feature scalar adapters are not
  migrated to the arena.
- GETSHOPDATA is not implemented by the SUBWND owner.
- The other shop/card flows (CARD is mode 10), a live hub party and live co-op
  are missing; they need their owning services.
- Owner by player slot: the shop stock derives from player zero's LEVEL (as
  the recovered preparation does); the lobby ticks one player in the hubs; that
  Start on pad N sends `STATUS/I<N>` is an assumption.
- Generators: scenes with beGeneraterInfo entries are refused; standalone
  generator/StageCTL ownership beyond the bounded lobby is missing.
- Detailed transfer/timing and live-device/presentation acceptance are not done.
  No physical-controller, speaker-output, synchronized retail cue timing, emulator,
  retail full-frame, Windows or physical Steam Deck validation exists for this
  menu.
- Malformed or imported state that would produce an empty/unarmed weapon
  appearance has no recovery path.
- The broad `check-retail` target has a `verify_database_retail.py` fixture built
  around the removed host database layout and missing typed-loader dependencies;
  the native database/arena tests pass separately, so a full retail-target pass is
  not claimed for the arena-backed windows.
