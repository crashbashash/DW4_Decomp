# Digimon World 4 — documentation

How *Digimon World 4* (USA, `SLUS-20836`) works under the hood: the engine, the data formats and the
game systems, as recovered from the binary and from the game's own Lua.

Matching recovery and the native port share one repository. The
[build system](build-system.md) maps the dtk-template layout (config/<GAMEID>/, orig/<GAMEID>/,
configure.py, objdiff). Native implementation contracts are
indexed in [port documentation](../port/docs/README.md), with priorities in
[porting tasks](../port/docs/project/tasks.md).

Everything here is a recovery. The retail game shipped without symbols, so each page records what
was found, how it was found, and how sure it is. Claims are backed by numbered entries in the
[findings register](findings/README.md), and a claim without a finding is an opinion — statuses are
used honestly, including *refuted*.

New to the project? [`engine/architecture.md`](engine/architecture.md) is the overall picture;
[`engine/binary.md`](engine/binary.md) and [`engine/toolchain.md`](engine/toolchain.md) cover the ELF
and how it was built. [`../PROGRESS.md`](../PROGRESS.md) is the state of the work, and
[`systems/open-questions.md`](systems/open-questions.md) is what nobody has worked out yet.

The complete [combat Lua API run](systems/combat-lua-api.md) has matching source.
The [reference ownership dependencies](systems/combat-reference-helpers.md)
include fifteen complete matching bodies and retail unwind identities.
Content-pinned [per-unit compiler requirements](engine/unit-compilers.md) cover
its alternate-compiler bodies without changing unlisted units' compiler.
[Explicit emitted-function ownership](engine/emitted-functions.md) verifies and
places both bodies of the nearby-query compiler unit.
[Retail unwind recovery](engine/exception-unwind.md) decodes the complete combat
cleanup table and constrains automatic-object lifetimes.
[Dispatcher draft recovery](systems/combat-draft-recovery.md) records the
reviewed call interfaces and memory repairs while the full callback is unmatched.

## The game at a glance

| | |
|---|---|
| Game | *Digimon World 4* (USA), `SLUS_208.36` / `BASLUS-20836`, v1.01 |
| Binary | ELF32, MIPS R5900 (Emotion Engine), little-endian, entry `0x00100008`, one 4.5 MB section at `0x00100000` |
| Matching toolchain | Metrowerks CodeWarrior for PS2 (MWCCPS2 3.0 build `011126`) under wibo for the game and engine code; an alternate MWCC build, content-pinned per unit, for the bodies the default build cannot reproduce ([per-unit compiler requirements](engine/unit-compilers.md)); and Sony EE GCC 2.96 (`local/ee-gcc2.96`, via `tools/cc.py` / `tools/eegcc_compile.py`) for the ~100 Sony-built SDK/CRI units ([sd prologue](engine/sd-prologue.md)). CRI audio/video and the Sony SDK are statically linked in retail |
| Scripting | Lua 4.0.1, with 116 C++ functions exposed to scripts — see [`engine/script-engine-lua.md`](engine/script-engine-lua.md) |
| Data archives | `NDMW.AFS` (972 entries) and `AREA.AFS` (1,382 entries) — see [`engine/afs-archives.md`](engine/afs-archives.md) |
| Save file | 80 KB, two mirrored 40 KB blocks, per-block SUM checksum, level formula `n³ + 137n² − 77n − 61` — see [`systems/save-format.md`](systems/save-format.md) |
| Enemy stats | 649 rows in `AREA.AFS` (665 byte-identical copies): an i32 HP max, twelve i16 stats, then three u8 (critical, magic-critical, rarity) — see [`systems/enemy-data.md`](systems/enemy-data.md) |
| Classes recovered | 579 RTTI records, 478 vtables, 11,714 vfunc slots → `Class::vfunc_NN` names for the slot functions (47 shared bodies left unnamed). Named functions: see the "Recovered metadata" table in [`../PROGRESS.md`](../PROGRESS.md), which separates *any* recovered name (role names such as `*_Register` and `::vfunc_NN` included) from *semantic* names |
| Reflection metadata | 1,075 MetaObjects, 659 with fields → 3,680 fields with name, byte offset and type — see [`engine/reflection-metadata.md`](engine/reflection-metadata.md) |

## Contents

| Folder | |
|---|---|
| [`engine/`](engine) | How the binary and engine work: the ELF and toolchain, the architecture, RTTI/vtables, the Lua engine, live game-state globals, the property/method system, the archives, reflection and igBinary, and the matching-decompilation build |
| [`systems/`](systems) | Game data and mechanics: items, techniques, enemy data, spawns, drops, digivolution, flags, the critical path, the save format, and the debug stage-select |
| [`findings/`](findings/README.md) | The findings register: every hypothesis, confirmed fact and dead end, by number |
| [Reference](reference/README.md) | Retail reference write-ups and stage catalogue pages; raw evidence is in data/reference (outside the repository: `extras/reference/data-reference-README.md`) |

Each folder also has its own `README.md` listing what is in it.

## Finding things

| Looking for | Read |
|---|---|
| What is done and what is left | [`../PROGRESS.md`](../PROGRESS.md) |
| Full lobby, Central Area and shops recovery | [Hub completion contract](systems/hub-recovery.md), [generated dependency inventory](systems/hub-inventory.md) |
| Original hub menu selection and pad handling | [SELECTCTRL manager](engine/selectctrl.md), [shared shop selector widgets](engine/shop-selectors.md), [joint protocol oracle](engine/selector-manager-composition.md) |
| Shared shop page controls and chip-list text | [ListCtrl/chip-list helper recovery](engine/list-controller-chip-view.md) |
| Original allocation and cleanup behind hub controllers | [Object creation/destruction](engine/object-creation.md), [window object cleanup](engine/window-object-lifetime.md) |
| How much is done — the code and data numbers | [`engine/progress-metrics.md`](engine/progress-metrics.md), [`../PROGRESS.md`](../PROGRESS.md) |
| The debt ratchet — the counters that may only go down, and how to re-record them | [`engine/debt-ratchet.md`](engine/debt-ratchet.md) (`tools/progress.py --debt-check`, `config/debt-baseline.json`) |
| What all the non-code bytes are | [`engine/data-regions.md`](engine/data-regions.md) |
| Which code is the Sony SDK, and what a port has to replace | [`engine/platform-boundary.md`](engine/platform-boundary.md) |
| How much of the C is typed rather than casts, and why it matters for a port | [`engine/typed-coverage.md`](engine/typed-coverage.md) |
| What is still unknown, with status | [`systems/open-questions.md`](systems/open-questions.md) |
| Original loading-card selection and node timing | [Stage loading recovery](engine/stage-loading.md) |
| Native lobby loading screen and responsive stage preparation | [Stage loading](../port/docs/stage-loading.md) |
| Native Main Lobby NPC acceleration, routes and departure | [Lobby choreography](../port/docs/lobby-choreography.md) |
| Hard/Soft lighting and shadows | [Retail recovery](engine/light-modes.md), [native option](../port/docs/lobby-rendering.md#hardsoft-option) |
| Native Main Lobby rendering and retail frame comparison | [Lobby rendering](../port/docs/lobby-rendering.md) |
| Native port release scope and technical requirements | [Port technical specification](../port/docs/technical-spec.md) |
| Native main-menu stat text, cursors and retail fidelity | [Main-menu fidelity](../port/docs/main-menu-fidelity.md) |
| GPU-only normal rendering and remaining CPU graphics paths | [GPU rendering](../port/docs/gpu-rendering.md) |
| Native FMV sound, title music and menu/character cues | [Native audio playback](../port/docs/audio-playback.md) |
| Native equipment/inventory/skill record transactions | [Player transactions](../port/docs/player-transactions.md) |
| Native player stat and technique recalculation | [Player stats](../port/docs/player-stats.md) |
| Native prepared DBBase and STATUS species-name lookup | [String databases](../port/docs/databases.md) |
| Native Main Lobby movement, collision and original startup | [Lobby gameplay](../port/docs/lobby-gameplay.md) |
| Native Main Lobby message windows, portrait and greeting typography | [Lobby greeting UI](../port/docs/lobby-greeting-ui.md) |
| Workspace drop-table and enemy-stat analysis tools | [Analysis tools](../scripts/analysis/README.md) |
| Host dynamic-testing instructions and tools | [Testing](../testing/README.md) |
| The overall engine, and its two state systems | [`engine/architecture.md`](engine/architecture.md) |
| How the game boots to the title menu, and what a port must stand in | [`engine/front-end-boot.md`](engine/front-end-boot.md), [`engine/engine-boot.md`](engine/engine-boot.md) |
| Complete matching title/menu/options controller, behavioral oracle and remaining engine boundaries | [`engine/title-menu-controller.md`](engine/title-menu-controller.md), [`engine/common-model-controller.md`](engine/common-model-controller.md), [`../recovered/frontend/README.md`](../recovered/frontend/README.md) |
| The Game Start slot/character/name/difficulty/card controller family | [`engine/load-intf2.md`](engine/load-intf2.md) |
| When a model-controller ACTION completes — WAIT/WAITCHECK, the named timer, JOINTSET completion, the node clock and the EE float arithmetic under them | [`engine/system-clock.md`](engine/system-clock.md), [`engine/action2-timing.md`](engine/action2-timing.md), [`engine/action2-jointset.md`](engine/action2-jointset.md), [`engine/model-sequence-waits.md`](engine/model-sequence-waits.md) |
| How the binary was built, or how to import it into Ghidra | [`engine/binary.md`](engine/binary.md), [`engine/toolchain.md`](engine/toolchain.md) |
| A kernel syscall, its number, or a `libkernel` stub | [`engine/binary.md`](engine/binary.md) §Kernel syscall stubs, `../config/syscalls.txt` |
| Native original-bytecode execution and DM scheduling verification | [Lua integration](../port/docs/lua-integration.md) |
| Corrected Lua numeric recovery and affected progression evidence | [Lua numeric audit](engine/lua-numeric-audit.md) |
| The Lua native API and its calling convention | [`engine/script-engine-lua.md`](engine/script-engine-lua.md) |
| Engine code required by Lua and unresolved indirect dependencies | [Dependency inventory](engine/lua-dependencies.md), [material-contact recovery](engine/material-contact.md), [indirect-transfer frontier of the port-critical closure](engine/indirect-frontier.md) |
| Which retail functions the native port needs, and how far each is matched, typed and named | [Port-critical dependency map](../port/docs/project/critical-dependency-map.md) (`scripts/port_critical_map.py`) |
| Messenger byte/int/float/long/vector/matrix/object/string channels | [Result-channel recovery](engine/messenger-results.md) |
| Matrix copying, alignment/aliasing and translation | [Matrix primitive recovery](engine/matrix-primitives.md) |
| List capacity/growth, mutation/search and string/object ownership | [List service recovery](engine/list-services.md) |
| Pooled token interning, ordered lookup and final release | [String pool/table recovery](engine/string-pool.md) |
| Packed string-chunk storage, growth and coalescing | [String chunk recovery](engine/string-chunks.md) |
| A function name, a class's vtable or its base class | [`engine/rtti-and-vtables.md`](engine/rtti-and-vtables.md) |
| How to name a function, or where the names live | [`engine/naming.md`](engine/naming.md) |
| Live game state: player position, globals, pointer chains | [`engine/game-state.md`](engine/game-state.md) |
| Reading or setting a player stat by name | [`engine/property-system.md`](engine/property-system.md) |
| Something inside `NDMW.AFS` / `AREA.AFS` | [`engine/afs-archives.md`](engine/afs-archives.md) |
| A stage's sound effects, or the `.sfp` / `ps2_` bank format | [`engine/sound-format.md`](engine/sound-format.md) |
| How a model's geometry is laid out (vertices, strips, why there are no indices) | [`engine/model-format.md`](engine/model-format.md) |
| How a model's vertex streams are addressed by `(componentType, componentIndex)` | [`engine/igvertexarray2helper.md`](engine/igvertexarray2helper.md) |
| How a model is lit — the per-vertex colour the VU1 produces | [`engine/vertex-shading.md`](engine/vertex-shading.md) |
| How the destructible props are textured — the inline `igAttrSet` atlas and its orientation | [`engine/inline-textures.md`](engine/inline-textures.md) |
| An `.igb` file, or a reflection (`be*`) structure | [`engine/igbinary-format.md`](engine/igbinary-format.md), [`engine/reflection-metadata.md`](engine/reflection-metadata.md) |
| The decompiled game scripts | [`engine/lua-decompilation.md`](engine/lua-decompilation.md), [`engine/lua-tree-layout.md`](engine/lua-tree-layout.md) |
| The save file's byte layout, checksum or level formula | [`systems/save-format.md`](systems/save-format.md) |
| Item database lookup and returned-value contracts | [Item/database lookup](engine/item-database.md) |
| An item, weapon, core or mod ID | [`systems/items.md`](systems/items.md) |
| A technique, skill or X-Data slot | [`systems/techniques.md`](systems/techniques.md) |
| Combat calculation rules and matching-source coverage | [Damage/critical recovery](systems/combat-damage.md), [generated combat inventory](systems/combat-inventory.md) |
| Technique-row lookup and nearby target collection | [Immediate combat helper recovery](systems/combat-helpers.md) |
| Enemy models, the stat table, bosses | [`systems/enemy-data.md`](systems/enemy-data.md) |
| How enemies spawn (`GENERATER` / `GENE-xx`) | [`systems/enemy-spawn-system.md`](systems/enemy-spawn-system.md) |
| What enemies and boxes drop, and how the roll works | [`systems/drop-tables.md`](systems/drop-tables.md), `systems/drops/` (outside the repository: `extras/reference/drop-reports/`) |
| The RNG: its seed, every draw site, how to predict it | [`systems/rng.md`](systems/rng.md), [`systems/rng-sites.tsv`](systems/rng-sites.tsv) |
| How to reach any stage (the engine's own stage select) | [`systems/dev-stage-debug-menu.md`](systems/dev-stage-debug-menu.md) §6 |
| Which flags gate the ending, and the critical path | [`systems/critical-path.md`](systems/critical-path.md), [`systems/flags/`](systems/flags) |
| Digivolution unlocks and side-quest gating | [`systems/digivolution-and-sidequests.md`](systems/digivolution-and-sidequests.md) |
| A finding by number, or every finding on a subject | `python3 scripts/findings.py show <id>`; `grep -rn '<text>' docs/findings/` |
| A script to run | [Scripts](#scripts) |
| What you may reuse, and under what terms | [`../LICENSE`](../LICENSE), [`../NOTICE`](../NOTICE) |

- [Lua loading and ownership](engine/lua-loading-ownership.md): retail scene startup, duplicate names, global cleanup and coordinated SD/Lua/DM teardown ([#790](findings/findings-0751-1000.md#f790)–[#793](findings/findings-0751-1000.md#f793)).

## Scripts

Two trees, split by what they operate on. `scripts/` is analysis — reading the binary, its data, retail captures and
its intermediate files. The [analysis-script guide](../scripts/README.md) indexes
emulator probes, model/texture capture and stage/save evidence utilities. `tools/` is the matching build — proving that `src/` compiles back to
retail. Both take `--help`.

`scripts/`:

| Script | Purpose |
|---|---|
| `dump_function_extents.py` | Export reviewed contiguous function spans when a Ghidra body count would truncate the build; consumed by `tools/split.py` |
| `verify_systemclock.py`, `clock_dispatch_probe.py` | Compare timer lifecycle, system sample/render and scheduler order with retail instructions; independently check the logo scheduler chain in a savestate; [contracts](engine/system-clock.md) |
| `verify_modelwait.py` | Compare all four JUMP/WCHECK bodies with retail instructions, ordered writes and engine calls; [contracts](engine/model-sequence-waits.md) |
| `verify_action2time.py` (`ee_core.py`) | Compare the Action2 timer, WAITCHECK, JOINTSET, node-clock, float→int64, walker, driver and ISCOMEND bodies with retail instructions on an exact 64-bit/EE-float interpreter; [contracts](engine/action2-timing.md) |
| `verify_sectl.py` | Compare the complete selection-sound dispatcher with retail instructions, signed delays and ordered model messages; [mappings](engine/sound-format.md#pre-lobby-selection-mapping-780) |
| `verify_commdl.py` | Compare all ten common-model helper bodies with retail instructions, ordered memory writes and engine arguments |
| `verify_title_menu.py` | Compare the recovered title-menu C state machine with direct interpretation of retail MIPS instructions at a stubbed engine boundary |
| `dump_functions.py`, `dump_strings.py`, `dump_xrefs.py`, `dump_symbols.py` | Ghidra dumps → `../data/` |
| `dump_vtables.py`, `apply_vtable_names.py` | Recover `__RTTI__`/`__vt__` records, and write `Class::vfunc_NN` names back into the analysed program |
| `decompile_funcs.py` | Ghidra's decompiler, by address |
| `find_table_refs.py` | Find the instructions that reference an address range (locating data tables) |
| `igb_parse.py`, `igb_dir.py`, `igb_inst.py` | igBinary (`be*`) headers; the type-directory / `{type_id, ordinal, size}` descriptor chain; and the **instance records** (`{classIndex, recordSize, nameLen}{name}{fields}`, size-verified) — which read a stage's generator and drop rows offline |
| `lua_extract.py`, `lua_dump.py`, `lua_decompile.py`, `build_lua_tree.py`, `lua_tree.py` | Lua 4.0.1 chunk extraction, bytecode parsing, decompilation, and the `lua/` tree |
| `flag_xref.py`, `flag_meanings.py` | Every flag operation in the decompiled Lua → `systems/flags/` |
| `dw4_rng.py`, `p2s_ram.py` | MT19937 identification and draw sites; reading a savestate's RAM without the emulator |
| `match_func.py` | One-off matching harness: compile a candidate, diff it against the target |
| `sync_data.sh` | Refresh the committed `../data/` snapshot |
| `findings.py` | Show a finding, give the next free id, check the register, link citations |
| `progress.py` | Count what is committed (symbols vs `../src/`) into `../PROGRESS.md`, `progress.json` and the block at the top of `../README.md`; run by `make progress` and by CI on every push |
| `datamap.py` | Classify the image's data bytes (jump tables, RTTI vtables, strings, class handles, unclassified) for the data half of the progress numbers — see [`engine/progress-metrics.md`](engine/progress-metrics.md) |

`tools/` — method, measured yields and the approaches already ruled out are in
[`engine/m2c-bulk.md`](engine/m2c-bulk.md):

| Tool | Purpose |
|---|---|
| `split.py` | Write `../config/symbols.txt` and emit `../asm/`, the retail split |
| `layout.py`, `linkgen.py`, `linkcheck.py` | The relink: disjoint tiling → objects and a linker script → comparison with retail |
| `check.py` | Split round-trip and coverage; backs `make check` |
| `verify.py` | The oracle: compile one candidate and diff it against retail, relocation-aware |
| `automatch.py` | Bulk decompilation by instruction-shape template |
| `m2c_one.py`, `m2c_batch.py`, `m2c_context.py` | The bulk m2c pass: assembly in, cleaned C out, verified before writing |
| `m2c_loop.py`, `args_search.py` | The per-function loop: one candidate plus its aligned instruction diff, and the automatic leading-call-argument correction — see [`engine/m2c-bulk.md`](engine/m2c-bulk.md) §The per-function loop |
| `m2c_errors.py` | Triage a tier's compile failures: regenerate each candidate and bucket MWCC's first error message — see [`engine/m2c-bulk.md`](engine/m2c-bulk.md) §What blocks the rest |
| `queue_diag.py` | Cluster a worklist tier by *why* each function misses — the retail shape plus the per-instruction `retail -> ours` signature — instead of by diff count, and flag size-truncated rows whose diff count under-reports — see [`engine/m2c-bulk.md`](engine/m2c-bulk.md) §The queue, measured before it is worked |
| `platform_map.py` | Resolve the addresses the code forms and classify them against the EE's register blocks — which functions are platform code, and the game's call surface into the SDK — see [`engine/platform-boundary.md`](engine/platform-boundary.md) |
| `sdk_bindings.py` | Decode the eight SDK library descriptors at `0x481000+` (name, ASCII version, and whatever each library actually stores — register bases, function tables, DCT tables, string tables) into `data/sdk-bindings.json`, and report the function starts their tables imply — see [`engine/platform-boundary.md`](engine/platform-boundary.md) |
| `jumptables.py` | Recover the `switch`es' `.rodata` tables → `../config/jumptables.txt` |
| `syscalls.py` | Recover the EE kernel syscall stubs → `../config/syscalls.txt` (number per stub; the pipeline skips them) |
| `permuter_one.py`, `permuter/` | The `decomp-permuter` harness — see [`../tools/permuter/README.md`](../tools/permuter/README.md) |

Ghidra work needs the analysed project (`../ghidra-projects/dw4/`) and **one Ghidra process at a
time** — a second one against the same project fails with a project lock error.

## Data and working directories

Committed files, and the gitignored working directories the analysis writes to. Anything marked
*(local)* exists only on the machine doing the work and never enters the repo.

| Path | What | Produced by |
|---|---|---|
| [`../lua/`](../lua) | Every game Lua chunk decompiled, filed by stage with descriptive names; a stage folder's `_e<N>` is the pack entry and a file's numeric prefix its chunk index (`scripts/lua_tree.py`). Index: [`engine/lua-tree-layout.md`](engine/lua-tree-layout.md) | `scripts/lua_decompile.py`, `build_lua_tree.py` |
| [`../data/`](../data) | A snapshot of the Ghidra dumps and derived tables (`functions.json`, `strings.json`, `vtables.json`, `script_api.json`, item and enemy tables) | `scripts/dump_*.py`, refreshed by `scripts/sync_data.sh` |
| `../config/*.txt` | The build's generated tables: `symbols.txt` (the split), `layout.txt`, `jumptables.txt` (the `switch` tables), `syscalls.txt` (the 80 kernel syscall stubs and their numbers) | `tools/{split,layout,jumptables,syscalls}.py` |
| `../local/` *(local)* | Your copies of what cannot be committed: `wibo`, `mwcps2/`, `m2c/`, `decomp-permuter/`, `permuter-venv/`. The `DW4_*` variables default here | you |
| `../ghidra-projects/dw4/` *(local)* | The analysed Ghidra project and the live dump outputs | the `dump_*` scripts |
| `../roms/`, `../bios/` *(local)* | Your own copy of the game — the ISO and the extracted `game.elf` — and a PS2 BIOS image if you run it | — |
| `../pcsx2/` *(local)* | Emulator data: memory cards, `sstates/`, logs | PCSX2 |
| `../../scratch/`, `../../local/captures/`, `../../local/evidence/`, `../../local/snapshots/`, `../../local/testing/`, `../../local/extracted/` *(local)* | Working output: RAM dumps, verification images, extracted archives, savestates | the analysis scripts |

## Conventions

- **Findings are the evidence.** A hypothesis, a fact that needs its proof recorded, or a dead end
  gets an entry in the [findings register](findings/README.md), and the page that uses it cites the
  number (`#254`). `Evidence` names the artifact: a repository path when it is committed, otherwise
  the working file and how it was produced.
- **Statuses mean what they say — the criterion.** *confirmed* requires non-empty
  `evidence` naming a repository-relative artifact: a string reference, a caller/callee contract, a
  reflected offset, a vtable slot, a `tools/verify.py` / `make` line, or a live read with its
  savestate path. *unconfirmed* is everything else — the claim may be right, but nothing recorded
  lets a reader check it. *refuted* means the hypothesis **text is false**, with the evidence that
  shows it; it is not "the attempt failed" and not "a later finding has a better answer" (a
  superseded row is refuted only when its text is wrong, and then its notes name the superseding
  id). Refuted rows are kept rather than deleted, so nobody re-investigates them. A live-memory
  claim counts when a running game or an off-line savestate read confirms it — say which.
  `python3 scripts/findings.py check` (part of `make hygiene`) refuses a *confirmed* entry without
  evidence, so the rule cannot regress silently. `<scratch>/` in a row stands for a session file
  that was not retained; no repository path is claimed for it.
- **A savestate carries the loaded world in RAM**, so it cannot test a disc change. To test one, boot
  the disc and then load the stage.
- **Never write the pristine disc.** Work from a copy.
- **Regenerate, don't hand-edit:** `findings/`, `systems/flags/flag-xref.tsv`,
  `systems/flags/flag-meanings.{md,tsv}`, `../data/`,
  `../lua/`, `../config/{symbols,layout,jumptables,syscalls}.txt`,
  `../PROGRESS.md`, `progress.json`, the `<!-- progress:start -->` block in `../README.md`, and
  `../data/check-categories.tsv` (the per-unit verification category, written by a complete
  `make check` and read by `tools/progress.py` for the fully-verified / debt split).
  `make progress` writes the progress files, and CI re-runs it on every push. `../PROGRESS.md` is the
  single source of counts: other pages point at it rather than restating numbers that go stale.
- **CI counts; the oracle runner proves.** The hosted GitHub workflows can only run what needs no
  game and no compiler: the hygiene scan, the typed-coverage gate and `tools/progress.py`. The byte
  oracle (`make check`, `make link`) needs the retail ELF and the proprietary toolchains: the author
  of a change runs it on the final tree and quotes its lines, and the self-hosted
  [oracle runner](engine/oracle-runner.md) runs it again on every pushed commit. The **pre-push hook**
  (`.githooks/pre-push`, enabled by `scripts/install_git_hooks.sh`) does not run it a third time: it
  checks the pushed lines and commit messages for host details, and applies the oracle-change rule
  when a push touches the oracle's own files.
- **Game data stays out of the repo.** `.gitignore` enforces it; a disc image dropped into a working
  directory is easy to do and easy to miss, and `git add -f` is never the answer.
- **No host details, ever — and it is enforced.** Nothing that identifies a developer's machine or account (absolute home
  or container paths, hardware models, controller brands, driver/kernel versions, device ids, e-mail, credentials) goes into
  code, docs, test fixtures, the findings register or a commit message. The hard rules, the pre-commit/commit-msg hooks
  (`scripts/install_git_hooks.sh`), the CI job and `make hygiene` are in [host details policy](host-details-policy.md).
- **The repo is self-contained.** Everything it points at is either committed here or a gitignored
  working directory of this tree (`roms/`, `build/`, `states/`, `local/` for your toolchain copies).
  Reference paths relative to the project root, never a home directory or a machine-specific
  location, and keep machine-specific environment and setup notes out of the docs — a reader clones this
  onto their own machine. Saying a thing is *not* redistributed here (the compiler, the game) is
  useful; describing where one particular machine keeps it is not.
- **Addresses** are the ELF's virtual addresses, written `0x00……` so they paste into Ghidra.
- **Notation.** In the notes recovered from live sessions, `pine <read|write|find|snap>` means a
  read, write or search over PCSX2's PINE memory socket; `input <press|stick>` is pad input;
  `state <save|load>` is savestate save/load; `emu <pause|step>` is pausing and single-stepping the
  VM. These describe what was done, not programs shipped here.
