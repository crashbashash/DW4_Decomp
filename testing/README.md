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

`python3 -m unittest discover -s tools -p 'test_build_options.py'` checks the build tools'
explicit-path options with synthetic fixtures.

```sh
python3 testing/test_name_live_models.py
python3 testing/test_story_state.py
python3 testing/test_gs_framebuffer.py
python3 testing/test_status_composition.py
python3 testing/test_lua_engine_dependencies.py
python3 testing/test_material_contact_retail.py
python3 testing/test_material_runtime_retail.py
python3 testing/test_reflection_registration_retail.py
python3 testing/test_string_fields_retail.py
python3 testing/test_owned_string_field_retail.py
python3 testing/test_object_fields_retail.py
python3 testing/test_owned_field_graph_retail.py
python3 testing/test_object_lists_retail.py
python3 testing/test_messenger_interned_registry_retail.py
python3 testing/test_messenger_registry_retail.py
python3 testing/test_object_creation_retail.py
python3 testing/test_messenger_factories_retail.py
python3 testing/test_messenger_memory_retail.py
python3 testing/test_messenger_lifecycle_retail.py
python3 testing/test_messenger_dispatch_retail.py
python3 testing/test_messenger_results_retail.py
python3 testing/test_list_services_retail.py
python3 testing/test_string_pool_retail.py
python3 testing/test_string_chunks_retail.py
python3 tools/test_permuter_paths.py
python3 tools/test_verify_relocations.py
python3 tools/test_multiple_jump_tables.py
python3 testing/test_m2c_compat.py
python3 testing/test_combat_initialization.py
python3 testing/test_combat_helpers_retail.py
python3 testing/test_combat_draft_repairs.py
python3 testing/test_combat_unwind.py
python3 testing/test_matrix_primitives_retail.py
python3 testing/test_ee_quadword.py
```

The protocol suite uses a fake UNIX PINE server and checks virtual-pad lifecycle.
The model test verifies shape/list ownership using a synthetic RAM image.
The framebuffer test checks PSMCT32 block/column addresses against primary
tables, including block interiors and double-buffer bases.
The composition test rejects vertex-only triangle coverage, changed pipeline
fields, false opaque-prefix assumptions and ADC/no-sample classification errors.
Retail probes and capture helpers are indexed in [scripts](../scripts/README.md);

The Lua dependency test checks direct/indirect transfer classification and the
seven retail MAT wrapper edges. Material-contact recovery compares all seven
engine helpers against private retail instructions without controlled callees;
see [scope and evidence](../docs/engine/material-contact.md).


Story-state checks cover raw saves, card-entry error/closure handling, optional
dependencies, ordered CLI reports and source preservation.

The [messenger dispatch oracle](../docs/engine/messenger-dispatch.md) compares all
fourteen selector/registration/dispatch/delayed-selection bodies across 1,561
RAM/defined-return/ordered-call cases. Registry/list/pool/allocation/receiver
callbacks remain controlled; the result-channel oracle separately composes real
list, matrix, pool, table and chunk implementations.

The [messenger lifecycle oracle](../docs/engine/messenger-lifecycle.md) compares
ten complete clearing/queue/nesting bodies in 464 cases through real recovered
selection/dispatch, with explicit nested receiver enqueue and captured-clock/
iteration-bound assertions. Lower list/string/allocation and receiver services
remain controlled.

The [messenger memory oracle](../docs/engine/messenger-memory.md) covers five
initialization/reset/owner/forwarding bodies in 254 original-instruction cases,
including cold integration through actual recovered selection, dispatch, delayed
delivery, nesting and reinitialization. Factory and lower-service contracts remain
controlled.

The [object-creation oracles](../docs/engine/object-creation.md) cover twenty
reflection/factory/construction/lifetime bodies in 249 retail comparisons and
thirteen persistent cold-messenger checkpoints through their real shared paths.
Integration field metadata is synthetic, with concrete field/registrar/allocator
services controlled; original concrete field construction remains open.

The [object-list/registry oracles](../docs/engine/object-lists.md) compare thirteen
retained-list/property/name bodies across 718 cases and twelve persistent cold
messenger checkpoints. Actual registry lookup/name and object/generic list bodies
execute; concrete field/interner/allocator/byte services remain controlled.

The [interned-registry oracle](../docs/engine/string-pool.md#cold-registry-interning-and-erase-byte-match)
compares 158 persistent checkpoints through real pool/table/chunk storage, cold
registry/lifecycle and string channels. Allocator modes, optional synchronization,
long names, canonical token identity and final-release/non-head chunk cleanup are
covered; concrete fields/registrars and allocator/byte/sync primitives remain leaves.

The [object-field oracles](../docs/engine/object-fields.md) cover fourteen generic
cleanup/persistence and concrete reference-field bodies in 230 retail comparisons,
plus six persistent owned-graph creation/final-release checkpoints. Synthetic
metadata is explicit; actual reference-field and lifecycle bodies run, with
allocator/unrelated hooks/byte primitives remaining controlled.

The [string-field oracles](../docs/engine/string-fields.md) cover 21 scalar value,
codec and common dispatch bodies in 255 retail comparisons, plus 42 persistent
owned-string construction/serialization/final-release checkpoints through actual
pool/table/chunk storage. Metadata is synthetic; allocator/hooks/byte/endian
primitives remain controlled. Raw table/constructor/descriptor evidence supports
five additional reviewed virtual roots.

The [reflection-registration oracle](../docs/engine/reflection-registration.md)
compares fourteen registrar/field builder/binding bodies in 487 retail cases,
including callback re-entry and the original Work name/offset/handle tables.
Primitive factories, allocation, type/system/vector/interner services remain
controlled; original schema inputs do not imply complete runtime bootstrap.

Object storage: `python3 testing/test_object_storage_retail.py` checks 726 retail
cases across eleven complete bodies. `python3 testing/test_reflection_registration_retail.py --object-storage`
composes original lookup/allocation/free wrappers beneath all 487 registration
cases. Allocator virtual services remain controlled; see
[contracts and limits](../docs/engine/object-storage.md).

Descriptor factories: `python3 testing/test_field_factories_retail.py` checks 336
retail cases across 24 complete bodies. Add `--field-factories` to
`testing/test_reflection_registration_retail.py` to compose all 487 cases through
actual Work factories, initializer chains, defaults and storage wrappers. See
[factory contracts and boundaries](../docs/engine/field-factories.md).

Metadata bootstrap: `python3 testing/test_metadata_bootstrap_retail.py` checks 214
retail cases across ten bodies. `python3 testing/test_reflection_registration_retail.py --metadata`
composes all 487 registration cases through original metadata construction, names
and registry indexing, plus concrete descriptors and storage wrappers. See
[metadata contracts and boundaries](../docs/engine/metadata-bootstrap.md).

Internal lists: `python3 testing/test_internal_object_lists_retail.py` checks 379
retail cases across 22 complete bodies. `python3 testing/test_reflection_registration_retail.py --internal-lists`
composes the original internal field-list factory, construction and buffer growth
under all 487 registration cases. See [internal list contracts](../docs/engine/internal-object-lists.md),
including the explicitly unconfirmed append return signature.

Object base: `python3 testing/test_object_base_retail.py` checks 33 original-instruction
checkpoints across the complete base bootstrap and unsigned field constructor chain,
including Work registration with two inherited header descriptors. See
[base contracts and boundaries](../docs/engine/object-base.md).

Metadata callback services: `python3 testing/test_metadata_callback_services_retail.py`
checks 78 retail checkpoints across six complete bodies, including actual base
metadata lookup/replacement and original Work callback-array dispatch/cleanup.
See [contracts and limits](../docs/engine/metadata-callback-services.md).

List descriptor copying: `python3 testing/test_list_descriptor_copy_retail.py`
checks 95 retail cases across eleven bodies, including both original inherited
`_data` specialization callbacks. See [copy contracts and limits](../docs/engine/list-descriptor-copy.md).

List registration: `python3 testing/test_list_registration_retail.py` checks 48
retail checkpoints across 32 bodies, including the actual Work callback path and
all inherited list schemas. See [list registration contracts](../docs/engine/list-registration.md).

Memory field values: `python3 testing/test_memory_field_values_retail.py` checks 113
retail checkpoints across 32 bodies and actual populated Work/list instance lifetime.
It includes ownership, counters, string release, trimming and data-buffer cleanup.
See [lifetime contracts and limits](../docs/engine/memory-field-values.md).

Array storage: `python3 testing/test_array_storage_retail.py` checks 151 retail
RAM/ordered-call cases across aligned allocation and named alignment selection.
`python3 testing/test_memory_field_values_retail.py --array-storage` runs the
113-checkpoint Work lifetime suite with actual array allocation. See
[contracts and remaining services](../docs/engine/array-storage.md).

Memory copy/buffers: `python3 testing/test_memory_field_copy_retail.py` checks 167
retail RAM/defined-return/ordered-call cases across 14 bodies, including actual raw
buffer duplication and callback-driven object visitation.
`python3 testing/test_memory_field_values_retail.py --buffer-services` runs all113
lifetime checkpoints with recovered array/buffer services.
`python3 testing/test_apply_names.py` checks explicit thunk naming precedence and
same-basename C/C++ reference rewriting. See
[copy contracts and limits](../docs/engine/memory-field-copy.md).

Allocator registries: `python3 testing/test_allocator_registry_retail.py` checks
186 original-instruction cases across13 bodies and actual buffer composition.
`python3 testing/test_memory_field_values_retail.py --allocator-registry` checks
114 lifetime/runtime-header states with original array, buffer, owner and selector
services. `python3 tools/test_function_extents.py` guards the wrapper
span; `python3 tools/test_verify_relocations.py` guards MWCC backward HI/LO pairs.
See [contracts and remaining boundaries](../docs/engine/allocator-registry.md).

Registry bootstrap/context: `python3 testing/test_registry_bootstrap_retail.py`
checks191 original-instruction cases across17 bodies, including the concrete
46-record selector/name receiver.
`python3 testing/test_memory_field_values_retail.py --registry-bootstrap` checks
116 states with actual registry creation, context lookup, populated lifetime and
registry teardown. See [contracts and limits](../docs/engine/registry-bootstrap.md).

Context lifecycle: python3 testing/test_context_lifecycle_retail.py checks244
retail cases across seven bodies. python3 testing/test_memory_field_values_retail.py
--context-lifecycle checks210 states through original names,46 retained bindings,
populated lifetime and complete slot/context release. See
[contracts and limitations](../docs/engine/context-lifecycle.md).

Allocator builder: python3 testing/test_allocator_builder_retail.py checks280
retail RAM/ordered-call cases across the complete slot204 builder and metadata
lookup helpers, including recursive aliases and selector/name/delegate composition.
See [contracts and remaining backend work](../docs/engine/allocator-builder.md).

Alias factory/binding: `python3 testing/test_alias_pool_binding_retail.py` compares
178 original-instruction RAM/ordered-call cases across the factory and complete
contiguous binding/accounting block, covering all116 instructions. Callbacks and
allocation backends remain leaves; see [the contract](../docs/engine/alias-pool-binding.md).
`python3 testing/test_hub_recovery_inventory.py` checks source call parsing,
actual shop/central mode prefixes and closed direct-edge accounting. Generate
and check the [hub inventory](../docs/systems/hub-recovery.md) separately.

Alias runtime: `python3 testing/test_alias_pool_runtime_retail.py` compares286
RAM/return/ordered-call cases for all54 bodies /4,160 bytes, executing all1,040
instructions. Actual alias wrappers, backend, factory/initializer, locking and
lifetime controllers compose with controlled base/backing/file/ownership services.
The independent dependency suite also checks all eight alias-runtime boundaries, vtable
bindings, reflection fields and critical backend width/sign instructions.
See [runtime contract and compiler residuals](../docs/engine/alias-pool-runtime.md).

Compiler object verification: `python3 tools/test_verify_relocations.py` checks
decimal symbol sizes, indexed function-section relocation ownership, backward
HI/LO ordering and independent GNU linking of a real multi-body MWCC object.
Extra emitted code is rejected even when the selected method matches; see
[compiler object evidence](../docs/engine/compiler-object-verification.md).

SUBWND lifecycle: `python3 testing/test_subwindow_lifecycle_retail.py` compares
1,072 RAM/return/ordered-call cases across all11 modes, four players, factory and
reference lifetime, callbacks and CARD/ordinary exits.630 instructions execute;
the only three unexecuted words are Ghidra-reviewed NOP padding. Constructors,
menu preparation/tree, records, message and Lua services remain controlled leaves.
`python3 tools/test_function_extents.py` protects the 1,832-byte update
span and its full return. See [scope and remaining work](../docs/engine/subwindow-lifecycle.md).

Save Keeper script ownership: `python3 testing/test_savekeeper_script_retail.py`
reads the private NDMW.AFS without extraction/writes, resolves the actual Lua-info
list/data-object/memory graph and checks the original delayed stagIS12 instruction
sequence. The real-input host check passes; no save UI or persistence is accepted.
See [the owned dependency edge](../docs/systems/hub-recovery.md#save-keeper-named-script-edge).

The [concrete SELECTCTRL oracle](../docs/engine/selectctrl.md) runs with
`python3 testing/test_selectctrl_retail.py`: 4,089 original-instruction
RAM/ordered-call cases for both complete update/general receiver bodies.
All 1,187 non-padding words execute; 19 padding words are checked separately.
Registry/factory/pad/messenger/model/format/string services remain controlled;
this does not establish native shop acceptance or physical input/render timing.

That same SELECTCTRL command additionally runs201 direct pad-record selection
cases and216 real manager/lookup compositions:4,506 total comparisons and all
1,208 non-padding words across three bodies. Pad records are controlled input;
physical device sampling and model execution remain outside this acceptance.

Common owner/controller composition: run
`python3 testing/test_selector_manager_composition_retail.py` for144 lifecycles
/3,146 persistent RAM-and-call checkpoints through the real owner, SELECTCTRL
handler/update, pad lookup and empty close routines. Handler results replace
canned selection/completion responses. Immediate SD delivery, initialization,
model/device and primitive services remain controlled. See
[scope and measured coverage](../docs/engine/selector-manager-composition.md).

Shared page controls and chip view: run
`python3 testing/test_list_controller_chip_view_retail.py` for3,149 full-body
RAM/defined-return/ordered-call comparisons across ListCtrl's three methods and
two chip helpers. All544 non-padding words execute; five padding words are
checked separately. Pad lookup can execute its real body; model/property/text/
format services remain controlled. All five bodies have exact matching source
/2,196 bytes. [Contracts and limits](../docs/engine/list-controller-chip-view.md).

Chip upgrade controller: run `python3 testing/test_chip_controller_retail.py` for
1,076 RAM/ordered-call comparisons through the complete7,232-byte update. All
1,761 reachable non-padding words execute;15 padding and32 statically dead
literal-null words are checked. Four-player commit, preview restoration, fresh
price/wallet lookup and callback ordering are covered;18 cases compose the real
page-count and parent-binding bodies. Record/status/message/selector/rendering
services remain controlled. [Contracts and limits](../docs/engine/chip-controller.md).

Item/database record lookup: run `python3 testing/test_item_database_retail.py`
for474 full-return/RAM/ordered-call comparisons through ten bodies /1,168 bytes.
All290 non-padding module words and all47 property-search words execute; two
module padding words are checked. The chain includes real chip selection and
property lookup; database-message delivery and strcmp remain controlled.
[Contracts and limits](../docs/engine/item-database.md).
