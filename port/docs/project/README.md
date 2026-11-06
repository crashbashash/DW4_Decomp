# Porting Digimon World 4 — goals, plan, and what the decompilation owes it

This folder holds the **project-level** plan for the native port. Recovery contracts are in
`docs/`; native subsystem contracts are in `port/docs`.

**The work list for goal B is [`tasks.md`](tasks.md)** — the road is decided there
(**source-level retarget**), and each workstream carries its status and first action. This file is
the *why*; that file is the *what next*. The one decision that has to be made before the platform
shims are written is [`pointer-model.md`](pointer-model.md) (32-bit guest arena, then a 4-byte handle
type; 64-bit host pointers are a later, optional widening).

The port's own code is in **[native source](../../README.md)**; its asset layer (native CRI
AFS + igBinary readers) is cross-checked against `scripts`.

## Current state of the port

The retail code the port depends on, and how far each piece is recovered, is the generated
[port-critical dependency map](critical-dependency-map.md). The resume point is in [tasks](tasks.md).

**Main Lobby.** [Main Lobby movement and original startup](../lobby-gameplay.md)
connect walking/jumping/falling, ambient portal animation and commander
instance masks, gate proximity and heal activation, owned
player/actor collision, authored motion/opacity publication,
original start/first and record/material restoration in normal created-card boot.

**Actor movement and AIMAP.** Digi-Elf movement/sequence services and scoped WPOS
AIMAP acquisition are implemented. Explicitly
bound actors execute original SQ_WALKON, select their own MAP01 and run original
WPos callbacks with per-instance targets and scoped HP commits. Validation covers
128 original callbacks and shared RNG state, 128 retail AIMAP instruction samples,
instance lifetime, reentrant dispatch and scoped cancellation. Full native/retail
checks and actor ASan/UBSan pass; controlled oracle leaves do not establish AI
update timing or full-scene parity.

Prepared KIND_OBJECT slots bind persistent scene-owned RAM/record/HP state.
GENERATE preserves nonzero-max health and initializes zero-max HP to 100; retail
record-default and 32 GENERATE health comparisons pass; 32 direct-sequence guards
also pass. Prepared reloads verify original waypoints/shared RNG, instance isolation,
reentry and scoped cancellation.

WPOS patrol timer/choice/direction/turn-limit and CTRL consumers are
implemented. Native scheduling verifies timer boundaries and shared RNG draws;
retail instruction comparisons cover exact service primitives. See
[actor sequence contracts](../actor-sequences.md#patrol-timers-and-control-consumers).

**Dialogue, selection and text.** Prepared font and
SELECTCTRL owners run original message and choice helpers with real model waits;
19,200 selection update states/traces match retail. See
[dialogue services](../dialogue-services.md).

Scene-owned text collects named faces and their own atlas references, supports
native typed Unicode TEXTSET/REPLACEUNKNOWN and draws verified glyph/line geometry
through authored font parents and layer masks. Original message/choice integration
passes; full-scene pixel parity remains separate.

**SUBWND and STATUS views.** SUBWND completion/removal
routes to an attached real owner. Native SUBWND slot/window-tree lifecycle matches 528 command states and
256 recursive update/close states.
See [status/menu contract](../status-menu.md).

Session-owned player folders and record-backed identity/weapon SYS queries
persist across VM recreation. Concrete STATUS root, WindowTitle/Title00 and
WindowSelect callbacks run in owned trees; 112 player queries, 9,600 root states,
15 title states and 72 selection states match controlled retail checks.
See [player records](../player-records.md).

Authored Title00–04/Select00 initialization runs original
status text through native model/font owners. Real selection and close waits,
172 retail initialization traces and scoped text callback lifetime checks pass;
see [concrete views](../status-views.md).

Native SUBWND UPDATE displays typed Unicode names and numeric stats;
preview colors, thirteen-value snapshots and HP/MP restoration match 96 UPDATE
and 192 preview retail cases. Prepared Title01 verifies authored data rows and
colors with controlled input records. Its species NAME lookup uses prepared
shinka database string ownership; native typed GETDATABASE results, ordered copied data and
retail instruction checks are documented in [databases](../databases.md).

**Player records and transactions.** Fresh created-card name/stat initialization uses copied numeric databases,
all three starter sockets and the recovered US converter. All four starters
match sixteen retail creation paths (624 scalar results plus names/base arrays/
sockets) and reach authored STATUS fonts; see [player records](../player-records.md#fresh-character-name-and-stats).

Staged equipment/inventory and per-species skill persistence primitives
match retail instruction checks; see [player transactions](../player-transactions.md).

Production stat/technique recalculation backs fresh creation and accepted
equipment commits; 1,760 retail cases match ([contract](../player-stats.md)).

**STATUS submenus.** Equipment/folder/skill orchestration and STATUS scene lifecycle ordering
have owned native callbacks and retail trace checks; see
[submenu boundaries](../status-submenus.md).

Item/pocket/DEVICE and skill content/resource leaves have retail/native
validation; see [content projection](../status-submenus.md#item-and-skill-content-projection).
The [owned skill controller](../status-submenus.md#owned-skill-controller-and-page-restart)
supplies all three modes, page input and selector restart with real close waits.
The [owned DEVICE selector](../status-submenus.md#owned-device-selector-and-inventory-preview-gate)
supplies scrolling, row decisions, retained acceptance/restart and equipment
identity/preview admission. [Owned equipment views](../status-submenus.md#owned-equipment-views)
cover complete slot/action/pocket routing and private stat projection.
Concrete [FOLDER ownership](../status-submenus.md#complete-folder-ownership)
connects DEVICE/detail, DISK, FLAG and currency transfer. Fresh records and
common flag aliases exist. The [complete root](../status-submenus.md#complete-status-root-assembly)
composes equipment, FOLDER and skill owners for all four slots.

**Loading.** Loading frames remain visible during live
catch-up. A windowed scheduling regression test covers the presentation gap;
see [stage loading](../stage-loading.md).

**Open.** Keep the arrival adapter
until matched transition/state traces verify its replacement. See the
[current task list](tasks.md#lua-integration) and
[Lua integration boundaries](../lua-integration.md).

## The two goals

**A. A decomp someone can use to mod the game and recompile it onto a PS2.** — the near-term goal.

**B. Digimon World 4 running natively on Linux and Windows.** — the long-term goal.

They are not the same finish line, and the difference is what the rest of this document is about.
Both objectives, however, share **one requirement: typed, named, documented code.** Byte-matched
`*(int *)((char *)p + 8)` satisfies goal A but is a dead end for goal B; real structs satisfy both.
That single observation is why the plan below changes what the decompilation prioritises.

## Goal A — moddable, recompilable, runs on hardware

**Already in place, and more than the coverage percentage suggests.** `make link` rebuilds the whole
section from a mix of decompiled C and, for the functions that have no C source yet, the retail bytes in the generated `asm/` split, byte-identically. So:

* **any** function is modifiable *today* — C where it is decompiled, its generated `asm/` unit where it has no C source yet;
* a mod's only footprint is the mod: everything else relinks bit-exact;
* the data side is well covered already (drops, item IDs, stats, spawn rows, save format).

**What it needs beyond that** (small, and none of it is "more percent"; items 1 and 3 are built,
items 2 and 4 are missing):

1. **An ISO relayout tool: built and verified.** An in-place patch
   cannot change a file's length; a rebuilt ELF is a different length, and it
   sits at LBA 289 with 17 files behind it and 14 free sectors at the end. The tool appends the file
   and re-points its ISO9660 directory record (extent+length are both-endian fields) and the volume
   size; the game's data never moves. Verified by booting a grown image.
2. **A mod-ELF step, which is the *other* half and is not built.** Measured: the
   space above the image is **not free — it is the C heap**, which the CRT startup hands the allocator
   with `SetupHeap(0x0058d280, -1)`, and it is in use from its first byte (~8.3 MB live). But that
   base is an **argument in code this repo re-links**, so a mod region can go at `0x0058d280`…`+N`
   with the heap moved up and segment 0's `FileSz`/`MemSz` grown by `N`. That needs the CRT startup
   built from source; it (`entry`, `0x100008`) has no C source yet and links from the retail image. Same-size edits need none of it
   and already work. Rules: `docs/engine/binary.md` §Rebuilding the image with a mod and
   §Memory map at runtime.
3. **A documented mod build recipe: built and verified** — a source patch goes all the way to a
   bootable disc (`patch src/` → `make link` → splice into the retail ELF → ISO relayout), and a
   worked example has a whole disc footprint of **15 bytes**. Two facts keep it small: the linker's own output boots as it
   stands (no ELF-container step needed), and `tools/linkgen.py` pins each unit to its retail
   address, so a modified function can change size without shifting the disassembly's baked-in
   addresses. What that leaves for *adding* code is item 2.
4. **Readable code where people actually mod** — which is goal B's requirement too.

**Done means:** any function can be edited, rebuilt, and booted on hardware; the systems people mod
are decompiled and named. *Not* 100 % coverage.

## Goal B — native on Linux and Windows

This is a larger, downstream project. The decompilation is a **prerequisite**, not the whole thing,
and its hardest parts are not helped by decompiling more game code:

| need | why it is hard | status |
| --- | --- | --- |
| **Real types and signatures** | m2c's output matches retail but is untyped; another compiler needs the structs the original had. The raw material exists — [`reflection.json`](../../../data/reflection.json) has 659 classes / 3,680 fields with offsets and types, already applied as Ghidra structs — but it is **not applied to the decompiled C** | **the biggest gap** |
| **The platform layer — replace, don't decompile** | the SDK is statically linked *inside* `game.elf` (libgraph, libdma, libpad, libmc, libcdvd, CRI), plus the 83 kernel syscall stubs, plus VU0/VU1 and the GS/DMA path; then the IOP side (pads, sound, files) behind RPC. On a port these become host shims (SDL2, file I/O, threads) | **mapped** ([`platform-boundary.md`](../../../docs/engine/platform-boundary.md)): the EE runtime is 410 functions at 0x100008..0x1137a8 (CRT + C++ runtime + libc + libkernel); its external surface is 127 entry points / 1,364 call sites, of which **41 are kernel syscall stubs** and 39 named OS functions — that named set *is* the OS shim list. CRI's file/stream middleware is a separate ~39 KB cluster at 0x2716f8, and the IOP side is 11 `.irx` modules + `IOPRP280.IMG`, named by their loaders |
| **The engine's own seam — 32 classes, not 18,661 functions** | the engine (an `ig*` cross-platform middleware family) is written against **generic** platform classes; the PS2 implementations sit under them. **32 `igPsx2*` classes, and 32 of 32 derive from a non-PS2 base** (`igPsx2File → igFile`, `igPsx2Controller → igController`, `igPsx2Thread → igThread`, `igPsx2VisualContext → igVisualContext`, …) — recovered from the registrar's base, so it is measured rather than assumed | **this is the boundary to build against**: implement those 32 interfaces natively and the engine's logic runs unchanged. Mapping: threads/sync → pthreads; `igLongTimer` → a monotonic clock; `igFile`/`igFolder`/`igMedia` → POSIX + an ISO reader; `igController` → SDL2; `igAudioContext` → SDL2/OpenAL; the `igVisualContext`/`igWindow`/image/vertex/shader-`*Ext` set → the new renderer; `igPsx2IopRpcConnection` (the one class whose base is `igObject`, i.e. the seam itself) → **deleted**, with the IOP modules' work done in native code |
| **What replaces libdma? Not a Linux API** | libdma drives the EE's DMA controller — chain lists to VIF1/GIF (rendering), SIF0–2 (the EE↔IOP path carrying pad/file/audio/memory-card traffic), IPU (FMV) and the scratchpad. There is no host bus to move data across, so no syscall or library takes its place | the "transfer" becomes an ordinary call consuming the same chain data from RAM: a **new renderer** for VIF1/GIF, **native code** where the IOP modules were, **ffmpeg** for the IPU path, and **no sync semantics** (`libdma: sync timeout` has no counterpart when the call is synchronous). Corollary: the SDK function *names* barely matter for a port — see [`platform-boundary.md`](../../../docs/engine/platform-boundary.md) §*The engine's own platform seam* |
| **The renderer** | VU1 microcode plus GS → a new renderer consuming the same scene data | biggest single sub-project; **not helped by more decompilation**. The microcode's own symbol table is recovered: `0x491910` in `game.elf` lists ~150 `vu1_entry_*`/`vu1_end_*` pairs with byte offsets (`UCODE_BEGIN;0` … `UCODE_END;109184`), which is the complete map of the renderer's microcode |
| **Asset loaders** | CRI AFS archives, textures, models, FMV → host formats. The *formats* are already documented ([`afs-archives.md`](../../../docs/engine/afs-archives.md), [`igbinary-format.md`](../../../docs/engine/igbinary-format.md), [`reflection-metadata.md`](../../../docs/engine/reflection-metadata.md)) | docs done; the native CRI AFS + igBinary readers are the port's asset layer ([native source](../../README.md)) |
| **The Lua logic** | 5,291 script chunks — the game's missions, quests and UI logic | **all 5,291 decompiled and load in the native Lua 4.0.1 runtime**; native engine services and scene validation remain in progress ([tasks](tasks.md#lua-integration)) |

**What goal B does *not* need: 100 % byte-matched C.** You can port with matched code for the engine
core and replacements everywhere else. But every *unmatched* function is one you must reverse by
hand later, so matching is still the right way to bank verified behaviour.

**Two cautions worth writing down:**

* **The risk is in the graphics and asset path.** If native really is the goal, the renderer and the
  asset loaders should start in parallel, because no amount of engine decompilation de-risks them.
* **There are two roads to "native":** retarget the decompiled C (needs types + shims, what this
  plan assumes), or *static recompilation* of the EE binary into C plus host shims (the N64-recomp
  approach). Our byte-identical split is a verified reference for either, but they want different
  priorities — the first wants game logic, the second wants complete instruction coverage.

## What a native build changes about the constraints

The ceilings a *console* mod hits are not really RAM — they are layout. Measured here: the image is
pinned to retail addresses (the undecompiled remainder's addresses are raw literals, so nothing may
move), it loads as one flat segment into a 32 MB address space, the heap starts at the image's end and
the stack occupies the last megabyte, and the disc's file layout is fixed by ISO9660 LBAs. Modding
fights all four; the RAM ceiling is real but it is one of several.

A native build replaces them, **if the code is relocatable** — which is the crux, and the thing that
separates the two roads:

| constraint | on console | source-level port | binary-level (static) recomp |
| --- | --- | --- | --- |
| RAM / address space | 32 MB, heap at the image's end, 1 MB stack at the top | gone — host virtual memory | contained in the emulated guest arena |
| code layout | pinned; literals in the remainder forbid movement | gone — relocations move anything | **stays**: guest addresses are baked into the recompiled output |
| segments / loader | one flat LOAD, `FileSz`/`MemSz` | gone — host loader | stays (guest layout is modelled) |
| disc layout | ISO9660 LBAs, fixed file positions | gone — assets are files | gone on the host side, but the *guest* file reads remain |
| how much you can add | slack you free, or the heap-move dance | anything, anywhere | code world geometry and extra allocated space, inside the guest address space |

So the honest answer to "a recomp could add and modify anything": a **source-level** one yes — relink,
run on host memory, add whole subsystems — and a **binary-level** one turns those ceilings into
emulation rather than removing them: it boots far sooner (no typed C needed) but you are still writing
into a fixed guest address space, so restructuring is the hard part, not adding.

What replaces the ceilings on the source-level road is a different and much more ordinary list:

- **Types.** Our matched C is byte-exact and written as `*(int *)((char *)p + 12)` — correct for MWCC
  and not portable C. A 64-bit host needs the real structs and signatures, which is why typed coverage
  (repo task T10) is the port's prerequisite. Note that this work is *neutral for matching* and
  essential here: different objective, same work.
- **32-bit pointer assumptions.** The game treats pointers as 32-bit ints, does pointer arithmetic and
  stores handles. A port either keeps a 32-bit guest arena (contained, and the simplest first step) or
  converts everything to typed host pointers (cleaner, more work).
- **The platform, which is reimplemented rather than decompiled**: the 41 kernel syscall stubs, the 56
  MMIO-touching functions, the VU1 microcode and the GS path, and the IOP services behind them
  (11 `.irx` modules + `IOPRP280.IMG`). The inventory exists — see
  [`platform-boundary.md`](../../../docs/engine/platform-boundary.md) — and none of it is a
  *space* problem.
- **Coherence, not capacity.** Adding a weapon, netplay or HD assets is unbounded in size, but each
  addition has to talk to whichever subsystem owns that domain — and where that subsystem is still a
  recompiled blob or the VU1 program, the addition is bounded by it.

The practical consequence for this project: the console-modding work (per-unit pinning, the isolated
disc patch, the heap-move design) serves **goal A only** and does nothing for a port; conversely
typed coverage and the undecompiled remainder are what a port needs, and the compiled-blob shortcut is
what makes a port run *before* that work is done.

## Scope decisions (settled)

| in scope | out of scope, and why |
| --- | --- |
| `SLUS_208.36` — the EE executable, every function and its embedded data | **`MODULES/`** — 11 `.IRX` + `IOPRP280.IMG`, 681,630 B, and **all of it is Sony/CRI SDK** (`SIO2MAN`, `PADMAN`, `MCMAN`, `MCSERV`, `LIBSD`, `SNDFI`, `USBD`, `MTAPMAN`, `SDRDRV`, `IGFILEIO`, `CRI_ADXI`, IOP kernel). No game logic. Replaced on a port, shipped as binaries for PS2 mods |
| the **Lua** scripts in `NDMW.AFS` (5,291 chunks, all decompiled) | **assets** beyond format documentation: `NDMW.AFS` 727 MB, `AREA.AFS` 511 MB, `NDMW.IGB` 106 KB are read-only inputs — "rebuild" means "copy" |
| the engine's **formats and tables** as documentation | **`OUTER.DAT`** (204 MB) — unexplored, and the one place *code* could still be hiding. Map it before treating scope as closed |

### Renderer and audio: reimplement, do not emulate (settled)

The port's advantage is speed, so both replaced subsystems are **reimplemented natively rather than
emulated**. In particular the GS is *not* going to be emulated: there is no plan for a GS register/
packet interpreter driven by the real VU1 microcode. The VU1's ~237 programs (map and image: [`vu1-microcode.md`](../../../docs/engine/vu1-microcode.md)) are treated as the **specification of what the pipeline computes** --
LIGHT (91 programs, 82 % of the code), TRANS, CLIP, TEXGEN, FOG, BLEND, MULTIPASS, COMPRESS -- and
the port implements those effects on the host GPU. The same applies to audio: CRI's ADX/Sofdec and
the SNDF sequence player are replaced, not emulated, and the `igAdx*`/`igSnd*` layer behind
`igAudioContext` is where the substitution happens.

What this makes load-bearing: the VU1 map's *semantics* (which effect each program computes) rather
than its instruction stream, and the GS *output* format only far enough to read what a draw was
asked to do while the engine still drives it.

## The decompilation consequences (tracked in the repo)

The work items this plan implies:

1. **Map the SDK boundary inside `game.elf`** — the SDK's own library-descriptor tables are already
   located in the data regions (the `PsIIlibgraph 2800` / `PsIIlibcdvd 2800` tables), so they should yield library names and entry points: label the SDK functions,
   exclude them from decompilation priority, and **count the game→SDK call surface**, which is the
   real size of the port's shim layer.
2. **Typed coverage as a published number** — apply the recovered structs and signatures to the
   decompiled C (`obj->field` instead of `+8`) and count what share of the code is typed. Note the
   subtlety: this was measured **neutral for matching** and that is expected — it is
   worthless for the matched-byte percentage and *essential* for this goal. It was never a dead end,
   it was aimed at the wrong objective.
3. **Keep byte-identity as the oracle**, and keep decompiling engine logic through the module loop —
   the engine logic is what a port reuses.
4. **Do not decompile the IOP/SDK modules**, and treat assets as documentation only.

## The numbers to publish

One headline per goal, so progress is legible without reading a tracker:

| number | what it answers | today |
| --- | --- | --- |
| **code matched** | how much of the binary is verified-correct C | percentage of code bytes, with the function count: read from [`PROGRESS.md`](../../../PROGRESS.md) (`code_bytes.fully_verified` and `functions.fully_verified` in [`docs/progress.json`](../../../docs/progress.json)) |
| **data identified** | how much of the non-code half is understood | percentage of data bytes identified: read from [`PROGRESS.md`](../../../PROGRESS.md) (`data_bytes` in [`docs/progress.json`](../../../docs/progress.json)) |
| **Lua decompiled** | how much of the game's logic is recovered | 100 % (5,291 / 5,291 chunks) |
| **typed coverage** | how much of the matched C is portable rather than int-soup | share of field accesses that use a recovered struct: read from `make typed-check` (also `typed` in [`docs/progress.json`](../../../docs/progress.json); `config/typed-coverage.json` is the gated baseline) |
| **shim surface** | how much platform code a port must replace | **measured** (T9): the EE runtime is 410 functions (`0x100008`–`0x1137a8`), the game reaches it through **127 entry points / 1,364 call sites**, 41 of those stubs are kernel syscalls; 56 functions touch hardware registers; the IOP side is 11 `.irx` modules + `IOPRP280.IMG` |

Definitions and the generator for the first two are in
[`../../../docs/engine/progress-metrics.md`](../../../docs/engine/progress-metrics.md).
