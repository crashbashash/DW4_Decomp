# Tooling

> The Pi-environment automation helpers are not available. Commands using `pi-*` or the
> `pi_re` package cannot be run as written; the observations recorded with them hold.
> Live scripts use the host probes (`extras/testing/host-probes.md`, outside the repository);
> use that guide for the controls.

## Analysis pipeline (Ghidra)
The `ghidra-post` wrapper runs **PyGhidra** (CPython 3)
scripts against a binary with the `analyzeHeadless`-style `-postScript` CLI.
It is not part of the current setup; the commands here show the scripts, their arguments and outputs.

```sh
GAME=dw4
ELF=orig/SLUS-20836/SLUS_208.36
PROJ=../local/ghidra-projects/$GAME

# import + analyse once, dump the function list
ghidra-post "$ELF" --project-path "$PROJ" --project-name $GAME \
    -postScript ../local/scripts/dump_functions.py \
    --out ../local/ghidra-projects/$GAME/functions.json

# string table
ghidra-post "$ELF" --project-path "$PROJ" --project-name $GAME \
    -postScript ../local/scripts/dump_strings.py \
    --out ../local/ghidra-projects/$GAME/strings.json

# cross-references
ghidra-post "$ELF" --project-path "$PROJ" --project-name $GAME \
    -postScript ../local/scripts/dump_xrefs.py \
    --target 0x00123456 --direction both --format txt
```
Reusing the same `--project-path/--project-name` reopens the analysed program, so
the (expensive) analysis is paid once.

### Stock dump scripts
| Script | Output |
| --- | --- |
| `dump_functions.py` | `functions.json` — 15,167 functions (address, name, signature, size) |
| `dump_strings.py` | `strings.json` — 28,784 strings with incoming xrefs |
| `dump_xrefs.py` | xrefs in/out of an address or symbol |

## Project-specific tools (written for this analysis)


`scripts/gs_ordered_probe.py` replays the scoped opening-ring GS pipeline offline, preserving
primitive boundaries and ordinary/additive draw order. See the ordered replay investigation (archived outside the repository) for inputs, controls and model limitations.

Standalone mod-build tooling is outside Git in `../extras/dw4-tools/`.
See the workspace archive `../extras/testing/mod-build-tools.md`.

### `lua_dump.py` — Lua 4.0.1 chunk disassembler
Parses standard Lua 4.0.1 bytecode and prints the header, per-function proto,
string constants, number constants, locals and a decoded disassembly
(opcode + operands).
```sh
# extract the Lua region of an AFS entry first, then:
python3 ../local/scripts/lua_dump.py /tmp/lua_179.bin --limit=2
```
Implements the exact `lundump.c` layout:
- header (21 bytes): `1B "Lua" 40 01 04 04 04 20 06 09 08 <test double>`
- recursive `Proto` parse (`source, lineDefined, numparams, is_vararg,
  maxstacksize, locals, lines, constants{strings,numbers,protos}, code`)
- opcode decode (`SIZE_OP=6, SIZE_B=9, SIZE_A=17`) with the 0..48 opcode enum.

### `lua_extract.py` — batch string extractor
Walks every entry of `NDMW.AFS`, finds `1B "Lua"` chunks, parses each, and emits
a JSONL of `{entry, chunk, off, size, source, line, params, strings}`.
```sh
python3 ../local/scripts/lua_extract.py \
    ../local/extracted/NDMW.AFS /tmp/dw4_lua_strings.jsonl
# -> parsed 5291 chunks
```

### `lua_decompile.py` — Lua 4.0.1 decompiler
Fully decompiles the game's Lua bytecode back to readable Lua source.
Handles linear code, `if`/`elseif`/`else`, `while`, `repeat`, numeric `for`,
closures, method calls, table constructors, and flattens the game's
`a and b and c`-as-nested-ifs pattern. This is the tool that produced
`lua/` (see `docs/engine/lua-decompilation.md`).
```sh
python3 ../local/scripts/lua_decompile.py ../local/extracted/NDMW.AFS \
    --out=build/lua_decompiled
python3 scripts/build_lua_tree.py          # files the chunks by stage into lua/
```
Key facts it relies on (all verified against the reference Lua 4.0.1
compiler in `/tmp/lua-4.0.1`):
- instruction layout `OP(6) | B(9 @6) | A(17 @15)`
- **jump target = `pc + s + 2`** (NOT stock `pc + 1 + s` — the game's jump
  offset is encoded one less)
- `OP_CALL`: A = stack position of function, B = nresults
- opcodes 38/39 = stock `JMPT`/`JMPF` (pop variants); `JMPONT`/`JMPONF` are
  never emitted, so there is no `and`/`or` short-circuit
- local names are stripped (`local_0`, `local_1`, …)

### `ps2mc_extract.py` — PS2 memory-card save extractor
Lists/extracts saves from a `.ps2` memory-card image using the `ps2mc` library,
**handling both** ECC-included images (528-byte pages) and PCSX2-style ECC-less
images (512-byte pages) via superblock auto-detection.
```sh
python3 scripts/ps2mc_extract.py list    ../local/testing/memcards/Mcd001.ps2
python3 scripts/ps2mc_extract.py extract ../local/testing/memcards/Mcd001.ps2 out/
python3 scripts/ps2mc_extract.py extract card.ps2 out/ --only DATA.BIN
```
Depends on: `pip install --break-system-packages ps2mc`.

### Story-state comparison

These read-only utilities use the repository save reader. An extracted USA
`BASLUS-20836savedata` payload is 81920 bytes and needs only Python's standard
library. Memory-card inputs use the existing optional `ps2mc` dependency above.
Flags, flag-folder bytes and counters are taken from the first mirrored block.

```sh
python3 scripts/diff_story.py before.savedata after.savedata
python3 scripts/dump_story_all.py --directory /path/to/saves before.savedata after.savedata
```

The summary command reports the supplied progression order. With no filenames,
it retains the dated checkpoint order and reports missing private saves explicitly.
Input files are never modified; malformed payloads and missing card entries fail
with a diagnostic. `python3 testing/test_story_state.py` checks this behavior offline.

### Standalone `save_edit.py` — DW4 save editor (edit + checksum + repack)
Reads the DW4 save (`BASLUS-20836savedata`) out of a `.ps2` image, applies u32
field edits (block-relative offsets, applied to **both** mirrored blocks),
recomputes the per-block SUM checksums, and writes everything back (ECC
recomputed by `ps2mc`).
```sh
python3 ../extras/dw4-tools/save_edit.py <src.ps2> <dst.ps2> <offset>=<value> [...]
# e.g. give 999999 bits + level 50:
python3 ../extras/dw4-tools/save_edit.py Mcd001_second.ps2 Mcd001_edit.ps2 \
    0x68=999999 0x788=50 0x50=50
```
Useful offsets (see `docs/systems/save-format.md` for the full map):
`0x50` menu level, `0x54/58/5c/60` HP/MHP/MP/MMP (menu-only),
`0x68` BIT, `0x6c..0x8c` device folder, `0x2e4/8/c` weapon slots,
`0x788` real level, `0x7c8` EXP.

Depends on: `pip install --break-system-packages ps2mc` (and `numpy` for the
level-fit scripts).

### Standalone `tech_edit.py` — technique/skill editor (edit + checksum + repack)
Symbolic editor for the per-species technique/skill arrays (see
`docs/systems/techniques.md`). Supports technique names, raw SKILL slots, level/EXP,
UPCNT, BASE_FLAG bytes, BASE_COUNTER, and raw u32/u8 offsets — all applied to
both mirrored blocks with the checksum fixed.
```sh
python3 ../extras/dw4-tools/tech_edit.py <src.ps2> <dst.ps2> [--species 3] \
    tech:bash=9 tech:shot=5 level=50
# technique names: blunt slash stab bash shot crush (slots 0..5)
# also: skill:<slot>=<v>, exp=<v>, upcnt:<idx>=<v>, flag:<byte>=<v>,
#       counter:<i>=<v>, u32:<off>=<v>, u8:<off>=<v>
```

## Dynamic-testing / reverse-engineering helpers

> **Where the scripts live.** The decompilation pipeline (Ghidra dumps, vtable naming, Lua
> decompilation, flags, findings index) is committed in the decompilation repo and reached as
> `../local/scripts/` (= `scripts`). Emulator-driving, save-editing and
> stage-harvesting tools live **inside** the shared repo in `scripts/`. The tables below use
> the current location.

| Tool | What it does |
|---|---|
| `../local/scripts/decompile_funcs.py` | **PyGhidra decompile by address**. Run as `ghidra-post <elf> --project-path ../local/ghidra-projects/dw4 --project-name dw4 --no-analysis -postScript ../local/scripts/decompile_funcs.py`. **Run `ghidra-post` calls sequentially** — concurrent calls fail with a project `LockException`. |
| `../local/scripts/p2s_ram.py` | Extract `eeMemory.bin` (and other entries) from a PCSX2 2.x `.p2s` **offline**, without the emulator. A 2.x `.p2s` is a zip whose entries are **zstd** (method 93) — `unzip` rejects it (`rc=81`), so the script walks the zip by hand and calls libzstd via ctypes. EEK addresses are identical to `pi-pine` addresses. |
| `../local/scripts/xrefs_multi.py` | Dump incoming xrefs for several addresses in one Ghidra session. |
| `scripts/live_skin.py` | **Export a skinned character mesh (bind + posed) from a paused EE RAM dump.** The per-vertex blend stream is runtime-only, so it is not in the model pack: reads `igVertexArray1_1._blendWeights` (+0x20) / `_blendIndices` (+0x24), the `igBlendMatrixSelect._blendMatrixIndices` bone→slot map and the `igBlendMatricesAttr._matrixCache` palette, and skins `v' = M[slot[bone]] * v` (row-major, translation in elements 12..14). `DW4_Port`'s `dw4asset skin` is the C mirror and `tools/verify_skin.py` diffs the two OBJs. |

The general rule: **read a savestate offline where possible** — it is far faster and safer than
PINE reads, and the emulator cannot get stuck.

## Generated data files (`../local/ghidra-projects/dw4/`)

> A committed snapshot of these dumps lives in the repo at `data/` — refresh
> it with `scripts/sync_data.sh` after re-dumping.
| File | Contents |
| --- | --- |
| `functions.json` | all 15,167 functions |
| `strings.json` | all 28,784 strings + xrefs |
| `script_api.json` | the 116 script-API functions (id, name, descriptor, stub, real) |
| `lua_all_strings.txt` | all 17,239 Lua script strings (with use counts) |
| `lua_globals.txt` | 515 `g_*` script globals |
| `lua_filenames.txt` | 269 `.lua` script filenames |
| `lua_igb_paths.txt` | 117 `.igb` asset paths |
| `lua_stages.txt` | 47 stage identifiers |
| `lua_sequences.txt` | 367 `SQ_*` sequences |
| `lua_missions.txt` | 22 `AM_*` missions |
| `lua_strings.txt` | script strings from a few representative entries |
| `afs_strings.txt` | strings from AFS entries incl. reflection type names |

## GUI save editor (`../DW4_Save_Editor/`)
A full tkinter GUI save editor wrapping `dw4save.py` — character stats,
techniques, X-Data power-ups, device folder (items/cores/boards/mod chips,
rarity +N bonus), BIT, XDATA. Normal mode caps values; advanced mode allows
crash IDs and over-cap (but never past the data-type max). `run.py` + `setup.sh`
/ `setup.bat` for the tester's host (no venv committed). See [`save-editor.md`](../../extras/testing/save-editor.md)
for the full feature list.

## Findings

Findings are in the [register](../docs/findings/README.md): `python3 scripts/findings.py show <id>` prints one,
`next` gives the next free id and `check` validates the register.

## Tooling limitations and gotchas

Hard-won lessons that cost hours; each of these looked like a bug in the game and was not. Read
before a dynamic session.

| Gotcha | Detail / workaround |
|---|---|
| **Live model probing needs a PAUSED VM** | The heap mutates every frame, so reads taken while running are not reproducible (an object's fields move between two reads of the same address). `pi-emu pause` first; `pi-emu resume` after. Both live scripts assume this. |
| **Never chase pointers with one PINE read each** | A `name_live_models.py` that does that (~tens of thousands of round trips over 826 `M_*Shape` objects) never finishes. Read EE RAM once into a local buffer and resolve offline — `--dump`/`--from` exist for exactly this, so a dump also survives the emulator being torn down. |
| **Model names are DCC names, not game names** | Geometry is named after its art source: `M_BK17v1_barrelmShape`, `pCylinderShape3`, `barrelbody`. They hang off a `M_*Shape` object (vtable `0x00528e70`, name at `+0x08`), which owns its geometry attr via the **single** `+0x20` `igAttrList` — not a chain (the lists are a packed shared arena). The `+0x1c` wrapper attr is only a fallback. Full chain: `docs/engine/model-format.md` (findings [#455](../docs/findings/findings-0251-0500.md#f455)/#457/#458). |
| Live model extraction needs the vertex buffer walked **in order** | There is no index array (1 of 1,006 live attributes has one): `_primType` 4 walks a strip-length array (`sum(L) == numVerts`), `_primType` 3 walks the buffer in triples (`3*numPrims == numVerts`). `igVertexArray._vdata` is a `{positions, normals}` pair, **not** a `{start,end}` descriptor — size the read from `_numVerts`; `_vdata[1]` is 0 on the 539 unlit/2D meshes, and the 8-byte `{u,v}` UV pair follows the last 12-byte stream at `align8((normals or positions) + 12*numVerts)`. See `docs/engine/model-format.md` (findings [#455](../docs/findings/findings-0251-0500.md#f455)/#458). |
| **`pi-emu step` does not process pad input** | FrameAdvance (F5) advances the world but does **not** poll the controller, so you cannot walk frame-by-frame. Use real-time `pi-input stick … --ms N` for movement. Frame-stepping still works for **autonomous** processes (area loads, cutscenes). |
| Real-time stick needs a settle + a long enough burst | `resume; sleep 0.2; stick --ms 800; pause` moves the player; `resume; stick --ms 300; pause` (no delay) often does not. |
| `pi-state load` needs **resume first** | Loading while paused is flaky (`pi-emu pause` may report "already paused"). Resume, then load, then pause. |
| `pi-pine snap` is slow | ~107 s per 32 MB ee-ram (≈0.29 MB/s). **Pause before snapping** so the image is coherent, and prefer extracting RAM from a `.p2s` offline (`p2s_ram.py`, ~0.07 s). |
| **PINE reads only plain mapped EE memory** | VU1 (`0x11004000`), EE regs/MMIO (`0x1000…`), and the scratchpad (`0x70000000`) all read back **0**, and writes there do nothing. It is not a `pi-pine` bug: the client sends the raw address and the protocol has no memory-space selector — PCSX2's server resolves the address as `vtlbdata.pMem[addr>>12] + addr` and returns 0 for gated/unmapped pages instead of dispatching the register handler. So VU1/MMIO need PCSX2's own debugger (`-debugger`, Memory view) or a savestate (every `.p2s` carries `vu1Memory.bin`/`vu1MicroMem.bin`), not PINE. (Patching `pcsx2-qt` to call `vtlb_memRead`/`vtlb_memWrite` would fix it, but PCSX2 is kept stock.) Findings. |
| PCSX2 re-applies `patches/*.pnach` after a state load | A pnach survives loading an *unpatched* state, which is how the MP-9999 patch corrupted unrelated saves. Also, the `extended` type was written as a **single byte** in this build — use explicit per-byte lines. Keep the patches dir empty unless a pnach is intended (see [`../mods/crown-elite-mod.md`](../../extras/mods/crown-elite-mod.md) §7.7). |
| Whole-RAM diffs are unusable | Animation phase alone makes the same state differ by ~10⁵ words; the crown work's pink-vs-no-crown dumps were 865k words apart. **Signature searches beat diffs** — a high-entropy byte-pattern scan found the MT state instantly where diffs found noise. |
| MIPS builds 32-bit constants with `lui`+`ori` | Searching for a raw 32-bit constant in the ELF finds almost nothing; search the **imm16 pairs** instead. |
| Pad1 binds to SDL player 0 | A real controller (e.g. a physical gamepad) steals SDL-0 and `pi-input --backend pad` silently does nothing. Start PCSX2 with `SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a`, and check `pi-pad status` (it must say player id 0). |
| `pi-input` face-button mapping (verified) | `Cross` → `BTN_SOUTH` → SDL `FaceSouth` → PCSX2 `Cross` (`SDL-0/FaceSouth`). |
| Ghidra xrefs in bulk | `../local/scripts/xrefs_multi.py` dumps incoming xrefs for several addresses in one Ghidra session. Run `ghidra-post` calls **sequentially** (concurrent calls hit a project `LockException`). |

## Quick disassembly fallback
```sh
mipsel-linux-gnu-objdump -d --start-address=0x00123400 --stop-address=0x00123500 \
    orig/SLUS-20836/SLUS_208.36
```

## Asset-layer tools (port side)

GS framebuffer checks: `python3 testing/test_gs_framebuffer.py` validates the
PSMCT32 block/column address map used by `scripts/gs_shade_raster.py`. Within a
block, columnTable32 interleaves two rows at a time; words are not row-major.
Inspect both framebuffer bases and the captured screenshot before identifying
the displayed image: FRAME may address a partly rendered back buffer. STATUS's
paused pixel checkpoint (archived outside the repository)
records that case and supersedes the inner-word/identical-buffer clauses of [#588](../docs/findings/findings-0501-0750.md#f588).

The native asset readers and their checks live in [`../port`](../port/README.md):

| command | what it does |
| --- | --- |
| `cd port && make` | builds `port/build/dw4asset` (C99, no dependencies) |
| `cd port && make check` | the regression suite: the C readers vs this repo's Python decoders on real archives, plus the media and texture checks (~1 min) |
| `port/build/dw4asset mount <roms> ls [substr]` | every name in `NDMW.IGB` with its archive, entry and size — the fastest way to find which AFS entry a file is |
| `... mount <roms> refs <stage>.igb` | a stage's `[pt.entry]` pack references resolved to entries and sizes (`[0.621]` = `NDMW.AFS` entry 621) |
| `... scan <roms> <class>` | which AFS entries contain a class (a directory walk per entry, ~1.6 s for both archives) |
| `... media <roms> probe\|convert <name>` | the 3 `.sfd` movies through ffprobe/ffmpeg |
| `... texture <src.raw> <out.png> --w --h --bits 8\|4 --pal <clut.raw> [--flip]` | indexed texture → PNG |
| `python3 scripts/extract_live_models.py --list` | every live `igGeometryAttr1_5` with vertex/prim counts (needs a **paused** game — the heap mutates every frame otherwise) |
| `... --out-dir ../local/evidence/models` | extract them all as OBJ (669 from the loaded `stag0102` scene, ~3.7 MB; `vn`/`vt` written when present) |
| `... --from ../local/evidence/models/ee-pre-leomon.bin --out-dir dir/` | re-extract with **no emulator** from a saved paused EE-RAM dump (0.15 s for all 669) |
| `... --addr 0x1260d88 --out m.obj` | one model; the barrel is `0x1260d88` (DCC shape name `polySurfaceShape1`) |
| `python3 scripts/name_live_models.py --dump /tmp/ee.bin --tsv ../local/evidence/models/model-names.tsv` | map every live geometry attr to its model part name (reads EE RAM **once**; needs a paused game) |
| `... --from /tmp/ee.bin --rename-dir ../local/evidence/models` | redo that mapping later with **no emulator** — `model_<addr>.obj` becomes `<M_*Shape name>.obj` |
| `python3 testing/test_name_live_models.py` | offline self-test of the name walk (synthetic heap, no emulator) |
| `python3 scripts/extract_live_models.py --addr … --pack <AFS>:621` | also prints/annotates the model's offset in the stage's model pack |

| Gotcha | Detail / workaround |
|---|---|
| **The live-object scan is blind to the engine's `ig*` classes** | `extras/dw4-tools/retail-live/live_objects.py` keys on the **478 recovered RTTI vtables**, and the engine's `Gap::Core::ig*` objects are **not** among them (a live `igImage` is `0x00525630`, an `igTextureAttr` `0x00522c60`, an array class `0x00526590`). So `--class igImage` reports **0 instances even when they exist** — reach them by following a pointer from a class the scan *does* see (`beTextureCtrlData._tex` → `igTextureAttr._image` → `igImage`, finding [#448](../docs/findings/findings-0251-0500.md#f448)), not by vtable. |
| **A texture's buffers are load-time ordinals offline** | In a pack, `igImage._pImage`/`_pClut` are **not** offsets (finding [#433](../docs/findings/findings-0251-0500.md#f433)/#446) — ordering the pack's blocks does not find them. Use the live route (`extras/dw4-tools/retail-live/live_textures.py` (outside the repository: `extras/dw4-tools/retail-live/live_textures.py`), which needs a running game and a `live_objects.py --scan` index), or solve the replay (tracker T14). |
| **`pi-pine read … --raw` writes to stdout** | `--out -` is not supported; either use `--out <file> --raw`, or `--raw` alone to pipe. `--size` takes a **decimal** int (not `0x…`). |
| Live texture decode is only trustworthy by eye | Verified so far: the status-screen label atlas, `stcngmoji.png` ("Go to the destination."), gradients and ramps — 46 dumped PNGs in `../local/evidence/screenshots/dw4-textures`. Palette is 32-bit R,G,B,A and textures are **bottom-up** (`--flip`). |
