# Recovery and retail-analysis scripts

Run commands from the repository root. `scripts/` owns binary/asset analysis,
retail capture and evidence collection. The matching build remains in `tools/`;
regression tests live in `testing/`.

| Purpose | Entry points |
| --- | --- |
| Topic-specific drop and enemy-stat analysis | [Analysis probes](analysis/README.md) |
| Static recovery and formats | Ghidra `dump_*.py`, `igb_*.py`, `lua_*.py`; see the [script index](../docs/README.md#scripts) |
| Lua engine dependency recovery | [lua_engine_dependencies.py](lua_engine_dependencies.py) generates [direct coverage/frontiers](../docs/engine/lua-dependencies.md); [seed_names_material_contact.py](seed_names_material_contact.py) supplies verified MAT helper names |
| Main Lobby recovery scope | [hub_recovery_inventory.py](hub_recovery_inventory.py) records four core script packs, static call sites, SUBWND mode prefixes and the known direct native dependency lower bound; [completion contract](../docs/systems/hub-recovery.md) |
| Combat calculation recovery scope | [combat_recovery_inventory.py](combat_recovery_inventory.py) reads the retail FIGHTCALC tables, checks their bounds and inventories the contiguous combat Lua helpers and direct callees; [recovery contract](../docs/systems/combat-damage.md) |
| Combat decompiler ABI context | [gen_combat_context.py](gen_combat_context.py) combines the reflected receiver with reviewed call slots, aggregate widths and tables into flat m2c input |
| Combat unwind inventory | [combat_unwind_inventory.py](combat_unwind_inventory.py) decodes the bounded destroy-only retail table, checks return-PC endpoints and inventories cleanup chains; [format and limits](../docs/engine/exception-unwind.md) |
| Combat draft memory repairs | [repair_combat_draft.py](repair_combat_draft.py) guards 36 original words and 17 source changes; diagnostic only, with no automatic source banking; [scope](../docs/systems/combat-draft-recovery.md) |
| Combat initialization checks | [verify_combat_initialization.py](verify_combat_initialization.py) checks incoming-s0 paths and the valid-level skill-band bound against original instructions; [proof scope](../docs/systems/combat-damage.md#incoming-register-and-return-checks) |
| Combat helper names | [seed_names_combat_helpers.py](seed_names_combat_helpers.py) records the verified technique-row and nearby nonzero-HP roles; [whole-body recovery](../docs/systems/combat-helpers.md) |
| Reviewed alias-pool functions | [RecoverAliasPoolFunctions.java](RecoverAliasPoolFunctions.java) checks vtable/entry evidence and classifies eight missing method bodies in the existing Ghidra project; [runtime contract](../docs/engine/alias-pool-runtime.md) |
| Messenger result-channel recovery | [seed_names_messenger_results.py](seed_names_messenger_results.py) names the complete 32-body [result block](../docs/engine/messenger-results.md) from reflection and retail verification |
| Matrix copy/translation recovery | [seed_names_matrix_primitives.py](seed_names_matrix_primitives.py) names the complete five-body [primitive run](../docs/engine/matrix-primitives.md); the shared EE oracle preserves full LQ/SQ payloads |
| Shared list and reference recovery | [seed_names_list_services.py](seed_names_list_services.py) names verified [list operations](../docs/engine/list-services.md), preserving the unresolved shared default's generic name |
| Pooled strings and ordered table | [seed_names_string_pool.py](seed_names_string_pool.py) names fifteen verified [pool/table operations](../docs/engine/string-pool.md) |
| Packed string chunks | [seed_names_string_chunks.py](seed_names_string_chunks.py) names twelve verified [allocation/coalescing operations](../docs/engine/string-chunks.md) |
| Model and texture evidence | [livedump.py](livedump.py), [extract_live_models.py](extract_live_models.py), [name_live_models.py](name_live_models.py), [capture_scene.py](capture_scene.py) |
| GS and rendering analysis | [gsdump.py](gsdump.py), `gs_*.py`, [pack_inline_tex.py](pack_inline_tex.py), [pack_lights.py](pack_lights.py) |
| Save-format and item-ID probes | [ps2mc_extract.py](ps2mc_extract.py), [probe_items.py](probe_items.py), [probe_items2.py](probe_items2.py), [save_probe.py](save_probe.py), [diff_story.py](diff_story.py); [save format](../docs/systems/save-format.md) |

Offline regression checks, without a running emulator:

```sh
python3 testing/test_name_live_models.py
python3 testing/test_story_state.py
```

A contributor's own game data stays in `../local/`.

Story comparison accepts extracted 81920-byte USA savedata with no extra package.
Memory-card images use the existing optional `ps2mc` reader; no standalone save
editor is required. The command inspects the first mirrored block without
writing to its inputs.
