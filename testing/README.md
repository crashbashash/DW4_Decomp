# `testing/` — dynamic testing

The testing tools, and the bugs and traps that waste time.

Relative command paths start at
the `DW4_Decomp` repository root; private data lives in the sibling `../local/`.
The Pi-environment automation
helpers (`pi-pcsx2`, `pi-pine`, `pi-pad`, `pi-input`, `pi-state`, `pi-emu` and `pi-screen`) are not available, so a command that uses them cannot be run as written;
offline analysis and saved-state reads remain useful.

Extracted game data lives in `../local/extracted/`.

Index: [documentation hub](../docs/README.md).

| File | Topic |
|---|---|
| `tools.md` | Ghidra pipeline, project tooling, dynamic-testing helpers, disassembly |
| `verify_models_offline.py` | Ground-truth check that the offline model extractor reproduces the live game's models from a saved EE RAM dump — 450 of NDMW.AFS entry 621's 549 attributes byte-identical, none unresolvable, and 383 of the 386 live-named models named identically |
| `texture-pack-groundtruth.tsv` | The 25 live-located texture buffers of entry 625 (name, size, palette/grid offset, `C`, dim) |
| `texture-pack-625-layout.tsv` | The complete derived 54-row pool layout of entry 625 (mirrors `docs/engine/texture-pack-625-layout.tsv`) |

Live recipes: [`../systems/dev-stage-debug-menu.md`](../docs/systems/dev-stage-debug-menu.md) §6
(stage select).

Shared regression commands run from the repository root:

```sh
python3 testing/test_name_live_models.py
python3 testing/test_story_state.py
python3 testing/test_gs_framebuffer.py
python3 testing/test_lua_engine_dependencies.py
python3 testing/test_m2c_compat.py
python3 testing/test_combat_initialization.py
python3 testing/test_combat_draft_repairs.py
python3 testing/test_combat_unwind.py
python3 testing/test_apply_names.py
python3 testing/test_hub_recovery_inventory.py
python3 testing/test_savekeeper_script_retail.py
python3 testing/test_xdata_script_retail.py
python3 -m unittest discover -s tools -p 'test_*.py'
```

- The model test verifies shape/list ownership using a synthetic RAM image.
- The framebuffer test checks PSMCT32 block/column addresses against primary tables, including block
  interiors and double-buffer bases.
- The Lua dependency test checks direct/indirect transfer classification and the seven retail MAT wrapper
  edges, the eight alias-runtime boundaries, vtable bindings, reflection fields and critical backend
  width/sign instructions.
- Story-state checks cover raw saves, card-entry error/closure handling, optional dependencies, ordered
  CLI reports and source preservation.
- `test_apply_names.py` checks explicit thunk naming precedence and same-basename C/C++ reference rewriting.
- `test_hub_recovery_inventory.py` checks source call parsing, actual shop/central mode prefixes and closed
  direct-edge accounting. Generate and check the [hub inventory](../docs/systems/hub-recovery.md) separately.
- `test_savekeeper_script_retail.py` reads the private NDMW.AFS without extraction or writes, resolves the
  actual Lua-info list/data-object/memory graph and checks the original delayed stagIS12 instruction sequence.
  No save UI or persistence is established. See
  [the owned dependency edge](../docs/systems/hub-recovery.md#save-keeper-named-script-edge).
- `tools/test_verify_relocations.py` checks decimal symbol sizes, indexed function-section relocation
  ownership, backward HI/LO ordering and independent GNU linking of a real multi-body MWCC object. Extra
  emitted code is rejected even when the selected method matches; see
  [compiler object evidence](../docs/engine/compiler-object-verification.md).
- `tools/test_function_extents.py` guards reviewed function spans.

Retail probes and capture helpers are indexed in [scripts](../scripts/README.md).
