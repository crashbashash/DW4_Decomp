# `engine/` — how the game works

Binary, engine architecture, formats and the runtime object/property system.
Index: [`../README.md`](../README.md).

- [Build profiles](build-profiles.md): **one translation unit, one profile** —
  `config/SLUS-20836/units.tsv` (compiler, flags, exception mode per unit, from the class runs,
  library blocks and retail exception records), per-function rows as provisional
  overrides, the `foreign-profile` debt category, how to review a provisional unit
  and how `tools/gen_unit_profiles.py` derives the table.
- [Per-unit compiler requirements](unit-compilers.md): content-pinned selection
  for the combat dependencies (the compiler is a unit profile in
  `config/SLUS-20836/units.tsv`, and this table holds provisional per-function
  overrides only).
- [Compiler-emitted function ownership](emitted-functions.md): explicit checking
  and placement of every body from a registered C++ compiler unit.

| File | Topic |
|---|---|
| `binary.md` | ELF/binary facts, entry point, Ghidra import, middleware, the 80 kernel syscall stubs (`../config/SLUS-20836/syscalls.txt`), baseline dumps |
| `camera.md` | How a stage's camera is read from its pack, the stage projection and the runtime camera controller's layout |
| `matching-patterns.md` | Functions that resist a source match, and the compiler pattern that blocks each one |
| `metafield-vtable.md` | The slot layout of the `igMetaField` family's vtables and the base bodies behind each slot |
| `stage-materials.md` | How world stages carry their materials and bind textures to meshes |
| `architecture.md` | Engine architecture, two state systems, object-method system, save layer |
| `script-engine-lua.md` | Lua 4.0.1 VM + the 116-function native API binding |
| [Lua dependencies](lua-dependencies.md) | Generated direct dependency closure of all 116 bindings, registration/dispatch, source coverage and unresolved indirect transfers |
| [Material contact](material-contact.md) | Complete seven-helper MAT engine behavioral recovery, matching Lua wrappers and original-instruction verification |
| [Allocator builder](allocator-builder.md) | Complete context slot204 allocation, aliases, backing policies and metadata selection |
| [Alias-pool factory and binding](alias-pool-binding.md) | Exact factory, retained alias lifetime and contiguous accounting controls; allocation backend remains open |
| [Alias-pool runtime](alias-pool-runtime.md) | Complete54-body behavioral recovery, allocation/accounting/ownership/locks and remaining ten matching residuals |
| [Combat unwind metadata](exception-unwind.md) | Bounded retail exception ranges, cleanup chains, frame layout and source-lifetime constraints |
| [Compiler object verification](compiler-object-verification.md) | Exact alias virtual tails with exceptions off; section-index ownership, decimal symbol sizes and GNU-link verification |
| [SUBWND lifecycle](subwindow-lifecycle.md) | All11-mode root selection/update/exit, CARD central-area return, scoped ownership and corrected update span |
| [SUBWND stock preparation](subwindow-preparation.md) | Complete work/currency/weapon/armor/chip/junk selection with original-instruction and lifecycle-composition evidence |
| [SUBWND commands](subwindow-command.md) | Complete seven-command receiver, status snapshots, preview colors/HP-MP restoration and all-mode lifecycle composition |
| [Shop-root metadata](shop-root-metadata.md) | Complete generic service-root factory/metadata block, exact published parent callback and concrete runtime update target |
| [Window object cleanup](window-object-lifetime.md) | Complete exact192-byte base-controller cleanup, inherited member order and signed deletion flag |
| [Window tree and shop-root runtime](window-tree-and-shop-root.md) | Full recursive child ownership/update and generic root widget/service selection, opening gate and close sequencing |
| [Window presentation and close queues](window-presentation.md) | Full model/text lifetime, close polling and shared title update; default-origin and sequence forwards |
| [XDATA controller](xdata-controller.md) | Full quote/confirmation/UPCNT debit flow, four-player record selection, script call-number publication and actual txt_shop pack ownership |
| [Item/database lookup](item-database.md) | Ten bodies /1,168 bytes, explicit value/status ABI and474 original-instruction comparisons |
| [Chip transaction controller](chip-controller.md) | Full inventory/preview/confirmation/record and XDATA flow at43aae0; original-instruction oracle |
| [ListCtrl and chip-list view](list-controller-chip-view.md) | Five complete paging/text helpers, 2,196 bytes; 3,149 original-instruction cases and caller ABI boundaries |
| [Shop selector widgets](shop-selectors.md) | Full selector publication/focus/close loop, XDATA one/two/three/seven-choice initialization, stat costs and exact focus predicate |
| [SELECTCTRL manager](selectctrl.md) | Pad-manager acquisition/registration plus full update/general receiver behavioral recovery and 4,089 manager cases plus real pad-record selection, 4,506 total comparisons. |
| [Context lifecycle and tracker delegation](context-lifecycle.md) | Original context construction/names, retained slots and special delegation/removal |
| [Registry bootstrap and context lookup](registry-bootstrap.md) | Original list lifetime/publication, context dispatch and concrete selector/name lookup |
| [Allocator registries](allocator-registry.md) | Original owner search, encoded indices, list lookup and complete allocation wrappers |
| [Memory-field copy and buffer services](memory-field-copy.md) | Original shallow/deep memory copying, owner-directed buffers and callback field traversal |
| [Array storage](array-storage.md) | Original aligned allocation, reference-only initialization and retained named-alignment selection |
| [Memory field values](memory-field-values.md) | Original memory reference lifetime and populated Work/list instance construction and teardown |
| [List registration](list-registration.md) | Actual inherited list schemas and original Work child-metadata callback registration |
| [List descriptor copying](list-descriptor-copy.md) | Original memory descriptor clone/copy chains and inherited list storage specialization |
| [Metadata callback services](metadata-callback-services.md) | Corrected string-field lookup, field replacement and real deferred callback arrays |
| [Object base](object-base.md) | Original base registration, reviewed callbacks and two inherited header descriptors |
| [Internal object lists](internal-object-lists.md) | Complete raw/retained internal list runtime and original field-container composition |
| [Metadata bootstrap](metadata-bootstrap.md) | Original metadata construction, ownership, names and registry indexing |
| [Field factories](field-factories.md) | Original Work descriptor factories, initializer chains and registration composition |
| [Object storage](object-storage.md) | Encoded allocator lookup, storage dispatch and registration composition |
| [Reflection registration](reflection-registration.md) | Original registrar state machine, field builders/layout and Work schema through retail descriptor tables |
| [String fields](string-fields.md) | Complete scalar string-value run, reset/write dispatch, token ownership, codec and owned-string lifetime validation |
| [Object fields](object-fields.md) | Generic cleanup/persistence, concrete reference-field construction/ownership and real owned-graph validation |
| [Object lists](object-lists.md) | Retained object-list operations, descriptor-based registry searches, corrected insertion-index contract and cold registry integration |
| [Object creation](object-creation.md) | Reflection allocation, construction/lifetime field passes, static initialization and real messenger factory composition |
| [Messenger memory](messenger-memory.md) | Complete initialization/reset group, temporary owners and reset forwarding; cold lifecycle/dispatch integration |
| [Messenger lifecycle](messenger-lifecycle.md) | Complete argument clearing, delayed enqueue/expiry and context nesting; real dispatch integration and original callback timing |
| [Messenger dispatch](messenger-dispatch.md) | Complete fourteen-body receiver selection/registration/dispatch and delayed-selection recovery, original special queries and verified ABI |
| [Messenger results](messenger-results.md) | Complete 32-body typed result-channel recovery, float/aggregate ABI and reference ownership |
| [Matrix primitives](matrix-primitives.md) | Copy/translation subgroup, alignment-dependent alias behavior, real matrix-copy integration and LQ oracle correction |
| [List services](list-services.md) | Shared reserve/growth/mutation/search and retained string/object bridges, composed messenger verification and remaining service boundaries |
| [String pool](string-pool.md) | Public pool/ordered-table lifecycle, token references, cold registry interning and remaining cleanup/synchronization boundaries |
| [String chunks](string-chunks.md) | Packed free-list allocation/coalescing, cross-chunk growth, allocator/delete boundaries and pool integration |
| `game-state.md` | Live game-state globals, `MDL` block, world position, pointer chains |
| `property-system.md` | `GAMERAM` property/method system (player stats, keys) |
| `afs-archives.md` | `NDMW.AFS` / `AREA.AFS` layout and Lua chunk storage |
| `model-format.md` | **Model geometry** — why a model is not a GS mesh: the `igGeometryAttr1_5` chain (`_vertexArray`/`_indexArray`/`_primType`/`_primLengths`), the two shipped representations (triangle strip from a strip-length array, triangle list with none), the `{positions, normals}` pair `_vdata` points at, the UV stream that follows it, the DCC part names on the `M_*Shape` object, and the self-checks (`sum(lengths)==numVerts`). 669 models extracted from one loaded stage (130 with normals, all with UVs, 599 named); **the offline pack form is solved** — all 549 of entry 621's attributes resolve from the file alone, 450 are byte-identical to the live game's, and 444 carry the DCC shape name recovered from the pack (`model-pack-621-attributes.tsv`) |
| `igvertexarray2helper.md` | **The `igVertexArray2Helper` binder** — the class that looks a vertex stream up by `(componentType, componentIndex)` and gets/sets its elements: the vtable (`0x5262a0`), the data classes (`igVertexArray2`/`igVertexData`/`igVertexStream` field offsets), the shared `FUN_0015f580` stream lookup called by 38 functions, the 28–39 / 40–54 accessor families, and the two measured walls (the duplicated-null-load dynamic-cast idiom, and MWCC's load scheduler / saved-register allocation) |
| `sound-format.md` | **The `ps2_` sound banks** — a stage's SE/BGM is a CRI `DTPK`/`TBLD`/`VAGD` container inside its sound pack; the chunk layout, the per-sound entry table, and the VAG ADPCM variant (sample-exact vs ffmpeg) |
| `reflection-metadata.md` | `ig*` reflection system and `be*` game-data types |
| `rtti-and-vtables.md` | MWCC RTTI/vtable layout and class-name recovery — 1,333 functions reachable from 478 vtables, 1,286 of them uniquely named — and the reflection-record region |
| `igbinary-format.md` | igBinary (`.igb`) format and the `NDMW.IGB` manifest |
| `texture-packs.md` | **The second container shape** — `NDMW.AFS` holds object/stage packs (621: the graph + the texture names) and **texture packs** (625/626/…: a descriptor table + a packed pool of palettes and index buffers); the descriptor entry, the interleaved image/clut sub-records, and the **solved pool-order key** (the pool is the data blocks in ascending object-id order; `texture-pack-625-layout.tsv` is the verified fixture) |
| `inline-textures.md` | **The destructible props' material** — the crate/barrel are textured by an `igAttrSet` *inside the stage pack* (`igTextureBindAttr -> igImage._pImage/_pClut`), not a texture pack; the `R G B A` palette order, the 32×32 atlas, and the **orientation** rule (the stored image is top-down; a renderer whose sampler indexes with `1 - v` must flip on decode) |
| `lua-decompilation.md` | The fully decompiled game Lua (5,291 chunks) |
| `lua-numeric-audit.md` | Corrected signed literals, regenerated corpus and progression-ID audit |
| `toolchain.md` | The original CodeWarrior PS2 build toolchain — which build it is, and why `.comment` can't tell you |
| `guard-family.md` | **The `sltu` guard family**: the source forms of its 72- and 76-byte variants, and the C-vs-C++ tail-call difference behind the one-call wrappers |
| `m2c-bulk.md` | **The bulk decompilation pipeline** — the vendored `m2c` over the functions templates cannot reach: the driver, the mechanical cleaner, the address-form problem, what it measured, the symbolizer's `%lo` bug, the measured negatives, and the pitfalls. |
| `naming.md` | **Naming and the module loop** — the committed `config/SLUS-20836/names/` overlay, `tools/apply_names.py`, why names live in the repo rather than only in Ghidra, and what counts as a recovered name |
| `progress-metrics.md` | **The two progress numbers** — what "code bytes matched" and "data bytes identified" each mean, the classification behind the data figure (strings, RTTI vtables, jump tables, class handles, the unclassified remainder), and how `PROGRESS.md` / `docs/progress.json` / the README block are generated |
| `function-inventory.md` | **The function inventory — the denominator** — how `config/SLUS-20836/symbols.txt` is built (the instruction model, the seven promotion rules and their counts, the `cut`/`merge` extent rows), the scan that keeps unowned code from growing back (`scripts/inventory_scan.py`, `make inventory-check`, debt counter `inventory.unsymbolised_bytes`), the residual classes and the before/after numbers |
| `debt-ratchet.md` | **The debt counters that may only go down** — code-only/name-defect/inventory-gap units, asm bodies, unmatched functions, struct-report groups, m2c idioms, raw reflected casts, `FUN_`/`DAT_` references, orphan bytes; `tools/progress.py --debt-check` against `config/debt-baseline.json`, and how an increase is recorded with its reason |
| `typed-coverage.md` | **How much of the matched C speaks in recovered structs** — current global measurement, completed 316-file typing pass, receiver hypotheses, descriptor validation and the recovery methods |
| `typed-game-layer.md` | **Struct recovery for the game layer** — current scoped measurement and the reference-field target table |
| `platform-boundary.md` | **What talks to the hardware** — which functions touch the EE's memory-mapped registers (56, all anonymous), the EE's own runtime at the front of the image (CRT + C++ runtime + libc + libkernel: 410 functions, 0x100008..0x1137a8, of which 41 of its 127 externally-called entry points are kernel syscall stubs), the eight decoded SDK library descriptors at `0x481000+` (only `libdma` carries a function table — the rest are library data), and where the SDK's names are *not* (nowhere in the shipped data beyond 22). Tools: `tools/platform_map.py`, `tools/sdk_bindings.py` |
| `data-regions.md` || `matching-decomp.md` | **The matching-decompilation build** — goal, layout (`config/SLUS-20836/symbols.txt`, `asm/`, `src/`), workflow, status, open items |

The `decomp-permuter` harness has its own README next to the code:
[`../../tools/permuter/README.md`](../../tools/permuter/README.md).

Related: game systems and data are in [`../systems/`](../systems); the analysis scripts are in
[`../../scripts/`](../../scripts), and the build tooling in [`../../tools/`](../../tools).

| [`platform-seam.md`](platform-seam.md) | The platform seam as an inventory — **32 `igPsx2*` classes, 31 of them under 30 generic interfaces with 153 fields** (`igPsx2IopRpcConnection` derives from `igObject` — it is the RPC seam and is deleted), recovered from the class hierarchy + reflection |
| [`engine-boot.md`](engine-boot.md) | **The boot chain** — the CRT entry (`0x100008`) → the game's `main` (`FUN_002595e0`) → the managers and the frame loop (`FUN_0025a580`/`FUN_0025a8c0`) |
| [`front-end-boot.md`](front-end-boot.md) | **The front-end boot — power-on to the title menu** — the logos → opening FMV → title → menu sequence is a chain of `NDMW.AFS` stage entries (800…814) that drive the scene stages `stagIS08/09/10/12`, switched by the Lua `STAGECTL NEXTSTAGE` API; and the controllers (`beNDMWStageCtl`, `beNDMWLoadCtrl2`, `beNDMWTitle2`, `beNDMWLogo`) |
| [`common-model-controller.md`](common-model-controller.md) | Common-model submission, reference lifetime and newest-first completion queues |
| [`title-menu-controller.md`](title-menu-controller.md) | Title runtime: nine functions, scoped references, three switch tables and exception metadata; remaining frontend modules |
| [`load-intf2.md`](load-intf2.md) | **The Game Start slot/character/name/difficulty/card family (`beNDMWLoadIntf2`)** — runtime block, object model, named working set, and message protocol; the master update/message handler and the **slot-selection**, **text-order** and **completion/selection** helpers, with the other controllers still open |
| [`action2-jointset.md`](action2-jointset.md) | **The `beAction2` JOINTSET contract** — reflected field layout, 60-fps frame-to-nanosecond conversion, loop/clamp behavior, and the recovered node-clock rebasing used by the title animations |
| [`action2-timing.md`](action2-timing.md) | **When an ACTION completes** — the node clock (2^18 ns quantum, EE round-toward-zero float math), the named `WAIT` timer, WAITCHECK start/update, JOINTSET strictness, the component walker/driver and the `ISCOMEND` predicate, with the logo OPEN/CLOSE thresholds and the unverified clock boundary |
| [`p2-renderer.md`](p2-renderer.md) | The `p2` EE-side renderer: its 6 register-touching functions, the **VU1 upload path** (program index → 48-byte record → transfer descriptor → SPR DMA), and the six functions that **name themselves** in their own strings |
| [`p2-lighting.md`](p2-lighting.md) | **What the EE packs for the VU1 light programs** — `p2lighting` (`0x1fb710`) decoded end to end: the 16-byte record stream, the runtime state/light tables, the ambient accumulation, and the measured limits (the parameter values are runtime-only) |
| [`vertex-shading.md`](vertex-shading.md) | **The per-vertex light model, recovered from a GS dump** — pairing a dump's VU1-lit RGBA with the pack mesh's own normals by primitive structure (not UV/projection), the exact model `floor(255 · 0.5 · clamp(amb + dif·max(0,N·L)))` with the `0.5` the GS's modulate convention (not a dim), the frame's per-draw state (one rig for world and props, linear filter, `ALPHA`/`TEST`), and why the constants stay a fit |
| [`vu1-microcode.md`](vu1-microcode.md) | The renderer's VU1 microcode map — **237 entry points** over a 109,184-byte image, by family; **lighting is 91 programs / ~90 KB** |
| [`module-map.md`](module-map.md) | Which region of `game.elf` is which library, from `config/SLUS-20836/regions.tsv`; **85 % of the unnamed mass and of the naming backlog is third-party middleware** (SDK, Intrinsic Alchemy, libpng, Lua, CRIWARE) |

- [Action2 timing and completion](action2-timing.md): timer, WAITCHECK, JOINTSET and `ISCOMEND` with the exact time/float model.
- [Model-sequence JUMP/WCHECK](model-sequence-waits.md): the four contiguous bodies.

- [System clock investigation](system-clock.md): verified logo WAIT duration, timer lifecycle and normal Action2 scheduling; raw cadence and game-pause/stage routing remain open.

- [Stage loading cards and node animation](stage-loading.md): localized preview/title selection and the complete nine-body runtime, verified against retail instructions.

- [Hard/Soft lighting](light-modes.md): LIGHTMODE handoff, authored versus overridden rigs, paired texture packs and unchanged Main Lobby shadows, verified against both retail modes.
- [Register allocation](register-allocation.md): how the pinned MWCC colours registers (simplify/select, vreg ids from declaration order), the trace/replay tools, and the source forms that move a colour.
- [beNDMWMdlPlayer::vfunc_44 recovery](near-miss-shapes-player-vfunc44.md): the idle player-number-badge handler, typed, and the 5-word cluster its C leaves different.
- [sd-prologue](sd-prologue.md): the `sd` callee-saved prologue is Sony EE GCC output (the SDK and CRI blocks); census, evidence, and how the Sony compiler builds these units.
- [getvtable-fold](getvtable-fold.md): the plain-family `*_GetVTable` stack-offset fold — the measured MWCC wall behind the 983 accessors, what was tried, and the family's generators.
- [assembly-sources](assembly-sources.md): hand-written `.S` routines the owner approved (`config/assembly-sources.tsv`), the evidence each needs, and the candidates still open.
- [source-approvals](source-approvals.md): inline `asm` and `volatile` the owner approved (`config/source-approvals.tsv`), and the `unapproved` category for the rest.
- [asm-body-matches](asm-body-matches.md): asm bodies are not kept in the repository (owner decision); what a function without C looks like, the generator for local study, assembler quirks.
- [Oracle runner](oracle-runner.md): the byte oracle (`make check`, `make link`, typed/hygiene/progress gates) on every push via a private self-hosted runner; what it proves, what it cannot block, install and rotation.
