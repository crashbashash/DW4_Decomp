# Port documentation

Native implementation lives in `port/` inside the shared `DW4_Decomp` repository.

- [Dungeon floors](dungeon-floors.md): the first dungeon (Humid Cave, `dng101b1`/`dng101b2`): the blockers closed in dependency order (separate camera packs, the Dungeon camera option, material regions, Blossomon's rig), the validating recipe and the open work.
- [Arena object model](arena-object-model.md): the contract and plan for retargeting the port's game logic onto the decomp's authoritative structs in arena memory (fight rules first, then the port-native game types).
- [Arena migration backlog](arena-migration-backlog.md): generated inventory (`scripts/port_type_inventory.py`) of the port-native game types still to move onto decomp structs in the session arena.
- [String databases](databases.md): prepared DBBase ownership, typed native GETDATABASE results, authored shinka NAME lookup and retail instruction checks.
- [Player transactions](player-transactions.md): staged equipment commits/previews, inventory identity/compaction, chip exclusion, signed eligibility and per-species skill persistence.
- [Player stat and technique recalculation](player-stats.md): shared production growth, equipment bonuses, technique selection and retail verification.
- [Player records](player-records.md): session-owned property folders, retail SYS identity/weapon queries and remaining schema/save/object-return boundaries.
- [Concrete STATUS views](status-views.md): original title/selection setup, scoped TXTgetCallNo callbacks, typed player/stat display, comparison previews and native model/text lifetime checks.
- [Equipment/folder/skill orchestration](status-submenus.md): owned Power/Main/Sub actions/pockets/transactions and error retries, retained DEVICE/detail giving, verified DISK and CtrlBit/SendBit outer timing, skill pages, positioned model/selector resource ownership and STATUS scene restoration dependencies.
- [Status/menu ownership](status-menu.md): native SUBWND slots, verified recursive window lifecycle, deferred removal and concrete STATUS root/title/selection callbacks and remaining gameplay dependencies.
- [Native dialogue services](dialogue-services.md): original message/choice helpers, custom byte-to-Unicode conversion, scene-owned named fonts/typed Unicode/glyph geometry/parent-layer rendering, selection state, model completion and SUBWND ownership boundary.
- [Hub NPC interactions](npc-interactions.md): live Cross probe, ordered talk-receiver registry, authored talk geometry, scoped hit callbacks, invulnerability timing and wake, verified Central dialogue/choice flows and the remaining NPC/service boundaries.
- [Native XDATA shop](xdata-shop.md): the Central XDATA Digi-Elf service — recovered ShopCtrl10 stat upgrade over native selector windows, retail price rule, atomic charge/recalculation, the chip-upgrade branch and headless acceptance.
- [Generic shop root](shop-root.md): the native `ShopCtrl00` root of hub SUBWND modes 1 and 3..9 — the `j_shback` backdrop, player panel, message window, Select/Confirm/Cancel legend and the `i_sttitle` header (txt_shop call by entry code; the Digi-Lab, mode 2, uses its own root's widget set), the service wait by child-count change and the `i_bgclear OFFREEZE` close.
- [Native NPC bank](bank-shop.md): Central's bank Digi-Elf (SUBWND BANK) — recovered ShopCtrl30 with the ShopCtrlEditBit money editor and the shared item list, atomic item/money transfers with capacity limits, and headless acceptance.
- [Native Digi-Lab](labo-shop.md): Central's lab Digi-Elf (SUBWND LABO) — recovered Digilabo and Evolve controllers, the GAMERAM evolution commands, the talk-window selectors, atomic evolve transaction and headless acceptance.
- [Native weapon, armor, chip and junk shops](equipment-shops.md): the Shop's WPU/APU/CHIP Digi-Elves and junk clerk (SUBWND 6–9) — recovered stock selection with item rolls, the goods list with equip preview, atomic purchase, the junk donation and tier threshold, the shared price rule and headless acceptance.
- [Save Keeper and interface scenes](save-keeper.md): the Central Save Keeper's `saveshop.lua` chain, what `stagIS11/12/13` are (card album, save, load screens run by native controllers), the hosted save scene (`stagIS12`: native `SaveCtrl`/`SaveIntf` over the host memory card, the save-library decision, XDG directory, `.bak`), `SYSctlFlagFolder`, the title's Call Digimon and Create (starter choice, name entry, GAMESTART) in the `stagIS13` scene; `check-hubsave`, `check-titlecall`, `check-savescene`, `check-saveintf`, `check-hubstages`, `check-saveimage`, `check-savectrl`
- [Card album](card-album.md): `stagIS11` (SUBWND CARD: `ShopCtrlA0/A1/A2`) as the card Digi-Elf's hosted scene, the player chooser, the Booster Pack draw and the nine-page album.
- [Load / join screen](load-scene.md): `stagIS13` (`LoadCtrl2` + `LoadIntf2` over the SaveIntf toolkit) as the Terminal Digi-Elf's hosted scene and the title's Game Start screens (Create and Call), its START gate and what is ported.
- [PS2 save-file codec](save-image.md): the 81,920-byte `BASLUS-20836savedata` layout (two mirrored blocks, four character records), item ids, atomic file write/read, verified byte-identical on six retail-written saves (`check-saveimage`)
- [Central disk-collector Prmame](prmame-npc.md): `n_prmame` (a gift NPC, not the Save Keeper) and the native `SYSctlDiskFolder` / `SYSctlDeviceFolder` engine services over the `CTRLITEM` receiver, checked against retail `3fca10` and driven through the real NPC (`make -C port check-hubprmame`).
- [Native Digi-Disk shop](disk-shop.md): the Shop's disk Digi-Elf (SUBWND DISK) — recovered ShopCtrl50 with its device/disk sell branch, the ShopSelectB0 menu, atomic buy/sell transactions and headless acceptance.
- [Native NPC appraiser](cnos-shop.md): Central's appraiser Digi-Elf (SUBWND CNOS) — recovered ShopCtrl40 over the shared item list, the level-tiered coweapon/coarmor reroll tables, the 300 BIT atomic conversion and headless acceptance.
- [Commander Room](commander-room.md): `stagML02` from the Terminal's gate and back — the Digi-Elf welcome, Ophanimon's and Seraphimon's story events by flag, named demo cameras, the room's music commands, `HITLANDMODEL`, the "Gate to Main Lobby" label, the tutorial staff and `check-hubcommander`.
- [Combat foundation](combat.md), including the [BIND movement/enum gate](combat.md#bind-movement-and-enum-gate): the ordered combat milestones, why `stag0101` (not `stagGF03`) is the first mission stage, the field-world runtime (generator registry, arrival hand-off, `DW4_SD_TRACE`), measured limits and the one-to-four-player design constraints; `check-fieldstage`.
- [Story flag sources](story-flag-sources.md): which original script and stage sets each flag behind the Commander Room's story states and the Outside World gate, and which field/boss stages the port still needs for them.
- [Main Lobby movement and original startup](lobby-gameplay.md): collision-backed player/actor publication, jump/landing/walking falls, ambient stage-portal animation, commander instance masks, gate proximity and heal callbacks, original start/first ownership, restoration and validation limits.
- [Authored box-camera transitions](box-camera.md): retained eye/interest rigs, original quaternion interpolation, region interruption and moving/stopped transition timing.
- [Lobby actor sequences](actor-sequences.md): original Digi-Elf movement/actions, label/control flow, scoped WPOS AIMAP acquisition, persistent prepared-object callback state, patrol timers/choices/turn limits, numeric completion waits and retail instruction traces.

- [Scene controller services](controller-services.md), including [published player dependencies](controller-services.md#published-player-dependencies): owned model slots, authored object sequences, command-driven windows, lobby camera, model update order and completion/lifetime checks.

- [Prepared native scene objects](stage-objects.md): ordered native info ownership, pack-local identities, authored layer roots, publication gates and retail layer-dispatch checks.

- [Original Lua execution](lua-integration.md): Lua 4.0.1 source, named bytecode loading, native-call/DM contracts, receivers/timed messages, native model/camera/window queries, shared retail RNG, model callback/lifetime routing, scoped named chunks and lobby unload, ordered retail info loading, startup milestones and coordinated scene cleanup, native AI/Action2 consumers, retail comparisons and remaining live integration.
- [Setting up a machine from a disc image](#setting-up-a-machine-from-a-disc-image): `tools/extract_iso.py` extracts and validates the disc files the port reads; and [performance profiling](#performance-profiling): the live and headless frame-cost tools.
- [Technical specification](technical-spec.md): agreed release scope, established technical direction and requirements under discussion.
- [GPU rendering in normal play](gpu-rendering.md): remaining CPU raster/compositing paths, hardware-backend policy and the active conversion/validation work order.
- [Options configuration](configuration.md): persistent camera/light settings, INI preservation, user and portable paths, failure handling and validation.

- [Stage loading](stage-loading.md): responsive Main Lobby preparation, original loading bands, Retry/Back and worker ownership.

- [Boot contract](boot-contract.md): current front-end and gameplay boundaries, including created-card login and
  the Main Lobby first-arrival adapter.
- [Recovered title controller](title-controller.md): native integration, source
  provenance, model backend, GPU title trails and menu drawing, validation and remaining equivalence work.
- [Main-menu retail fidelity](main-menu-fidelity.md): title/character-menu
  corrections, authored stat/name layout, original Lua message publication,
  retail/hardware evidence and remaining full-parity limits.

- [Lobby rendering](lobby-rendering.md): saved Hard/Soft lighting and texture selection, atlas orientation, recovered vertex shading and fog, inherited materials, portal state clocks, projective actor shadows, source-timed entry rings/particles and fades, authored switch/LOD visibility, viewport clipping and GS integer sample coverage, GPU execution/performance roadmap and retail frame comparison, including database-selected starter weapons and named hand-bone attachments.

- [Lobby greeting UI](lobby-greeting-ui.md): original message windows, portrait, font layouts, page-group transitions and retail vertex/texture verification.

- [Audio playback](audio-playback.md): synchronized FMV sound, original title music,
  menu/character cues, lobby music/ambience and terminal beep, asset provenance, checks and remaining audio boundaries.

- [Lobby arrival choreography](lobby-choreography.md): recovered acceleration/turn channels, Action2 completion, bounded collision, continued NPC routes, delayed relocation and the bounded HUD/camera/control handoff.


- [Connected hub travel](hub-travel.md): original exit/choice requests, authored arrival matrices, headless checks and the remaining native loading/publication work.

Project planning: [porting plan](project/README.md), [tasks and resume point](project/tasks.md),
and [pointer model](project/pointer-model.md).

## Setting up a machine from a disc image

The port and its tests read extracted disc files, not the ISO. `tools/extract_iso.py` (Python 3 only, never writes to the ISO)
reads the image's ISO9660 file system, copies the files to a directory you choose and validates them:

```sh
python3 tools/extract_iso.py "/path/to/Digimon World 4 (USA).iso" --out /path/to/extracted --skip OUTER.DAT
python3 tools/extract_iso.py --check /path/to/extracted      # re-validate later
```

- `--out` is required and has no default; point later runs at it with `--roms /path/to/extracted` (or `DW4_ROMS=...` for `make`).
  Without that, the port looks for `../local/extracted` relative to the repository.
- It refuses a disc that does not boot `SLUS_208.36` or lacks `NDMW.AFS`, `AREA.AFS`, `NDMW.IGB` or `SLUS_208.36`, and checks the
  retail sizes. `--strict` also requires the pristine disc MD5 (`3185f04230b1dabd853db750e4b51108`); without it a different MD5 is
  accepted, so patched discs still extract.
- `OUTER.DAT` (204 MB) is not read by the port; `--skip OUTER.DAT` leaves it out. A re-run keeps complete files, replaces truncated
  ones, and writes through `.part` files so an interrupted run never leaves a short file under the real name.
- Extracting the pristine USA disc gives files byte-identical to the existing `local/extracted` (all 19 files).
- `python3 tools/extract_iso.py --self-test` needs no game data and runs in `make check`.
- This is a developer/testing tool. The agreed first-run setup flow inside the shipped game (ISO picker, progress, recovery) is
  still a specification item; see the [technical specification](technical-spec.md#agreed-asset-setup-requirements).

### Profiling-only machine (minimum setup)

A machine used only to measure performance needs no retail comparison, no tests and no image libraries:

1. Install a C compiler, GNU make, `pkg-config`, `python3` (standard library only for the profiler) and the development packages for
   SDL2 plus Vulkan (or EGL/GLES). The live profile needs a display and a GPU driver.
2. Extract the assets: `python3 tools/extract_iso.py <iso> --out <dir> --skip OUTER.DAT`.
3. From `port/`: `make -j4 build/dw4`, then
   `DW4_ROMS=<dir> python3 tools/profile_live.py --roms <dir> --configs vulkan:1280x960 --dwell 900`.
   Add `sdl:1280x960` (and `vulkan:2560x1440`) to the `--configs` list to compare backends and resolutions.
4. Record, next to the results, what the machine is (CPU, GPU, RAM, driver) outside the repository, since the figures only mean
   something against that hardware; do not commit host details.

Copy the "work ms" and "over/s" columns for each stage; those are the figures to compare with the 16.7 ms budget.

### Fresh-machine checklist (build, test, profile)

1. **Clone** the repository. Nothing in it needs the other workspace folders; the port reads its assets from a directory you name.
2. **Install**: a C compiler and GNU make; `python3`; `pkg-config`. For the window and GPU paths add the development packages
   for SDL2, EGL/GLES and Vulkan. Each backend is probed and compiles out cleanly when its headers are missing, so a machine without
   them still builds and runs the headless checks (window/present tests are skipped). For the Python tools that decode or compare
   images install Pillow and numpy (`verify_present.py` also needs Xvfb and ImageMagick; `verify_options_menu.py`, `verify_title_mesh_gpu.py` and
   `test_dialogue_e2e.py` import them; `frame_metric.py` skips itself without them). A few analysis-only tools also want scipy.
3. **Extract the assets** (above): `python3 tools/extract_iso.py <iso> --out <dir> --skip OUTER.DAT`.
4. **Build and test** from `port/`: `DW4_ROMS=<dir> make -j"$(nproc)" check`. Use `-j4` or less on a small machine; the full run
   is long and an audio test can time out under heavy parallel load (rerun it alone with `make check-audio`). On a many-core desktop
   `make -j14 -k -O check` (keep going, output grouped per target) passed with no failures in about half the serial time (measured once; a failure that
   appears only in parallel is rerun serially before it is believed). `check-fieldstage` on its own is one long chain and gains nothing from `-j`. The `crosscheck.sh`
   step compares sorted manifest output and fails under some non-C locales: run with `LC_ALL=C`.
5. **Retail-oracle checks** (`DW4_ROMS=<dir> make check-retail`) need the extracted boot file `SLUS_208.36` from the same directory
   and nothing else private. Checks that compare against private captures or savestates skip themselves when those are absent.
6. **Profile**: on a machine with a display and GPU run `python3 tools/profile_live.py --configs vulkan:1280x960 --dwell 900`
   (or `sdl:`); headless, `make profile-hubstages`.

## Performance profiling

Frame cost is measured from the engine's own trace (`DW4_FRAME_TRACE=1`): frames per second, average and worst CPU work per frame against
the 16.7 ms budget, seconds that went over budget, and a per-phase split (mesh loop, shadows, world, UI). Run these from `port/` after a
normal build; the private game assets must be found as for any run.

| Tool | Needs | Measures |
| --- | --- | --- |
| `python3 tools/profile_live.py --configs vulkan:1280x960,sdl:1280x960 --dwell 900` | A display and GPU | A real window scripted through the title, character creation, login and the Terminal, Central, Shop and Commander Room hubs (about 2.5 minutes per configuration). One row per stage: fps, average work ms, worst ms, over-budget seconds per second, lowest fps. The run to use on a weaker PC. |
| `make profile-hubstages [PROFILE_BUDGET_MS=8]` | Nothing (headless) | CPU-only cost of every hub and interface scene; fails when a stage exceeds the budget. |
| `python3 tools/profile_lobby.py [--budget-ms X]` | Nothing (headless) | CPU cost of the Main Lobby from boot through the arrival greeting. |

Notes for comparing machines:

- Use the same `--configs` resolution and `--dwell` on both; compare the "work ms" column (CPU time the port spends per frame), not
  fps alone, because pacing holds 60 fps until the work exceeds the budget.
- Set `SDL_GAMECONTROLLER_IGNORE_DEVICES` when a physical pad is attached so it does not feed the scripted route.
- Frame time varies with other load on the machine; repeat a run, or alternate two builds, before trusting a difference smaller than
  about 0.5 ms.
- Long soak runs (leaks, slow growth) are a separate exercise: pass a larger `--dwell`, or watch the process memory while the engine
  idles in one stage.
