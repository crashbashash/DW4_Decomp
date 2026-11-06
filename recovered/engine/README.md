# Engine behavioral reconstructions

- [SUBWND lifecycle](../../docs/engine/subwindow-lifecycle.md):nine bodies /2,532
  bytes,1,072 original-instruction cases across all11 modes and four players.
  Covers all630 executable instructions plus three reviewed padding words;
  command/preparation bodies and concrete menu/record/scene services remain open.

- [Alias-pool runtime](../../docs/engine/alias-pool-runtime.md):54 bodies /4,160
  bytes with286 original-instruction cases covering all1,040 instructions.
  Original wrappers/backend/lifetime compose; concrete backing, locks, metadata,
  base lifetime, ownership and file services remain controlled boundaries.

- [Alias-pool factory and binding](../../docs/engine/alias-pool-binding.md):
  ten bodies /464 bytes;178 original-instruction cases cover factory branches,
  retained alias lifetime and all contiguous accounting controls. Allocation,
  metadata creation, destruction and virtual callbacks remain controlled leaves.

- [String chunks](../../docs/engine/string-chunks.md): twelve allocation/chunk
  bodies, 291 retail comparisons and ten real-chunk pool lifecycle calls.
  Allocator/delete and compiler contracts remain open. The cold registry
  also runs through real chunk storage in the 158-checkpoint integration below.

- [Interned cold registry](../../docs/engine/string-pool.md#cold-registry-interning-and-erase-byte-match):
  158 persistent checkpoints through real pool/table/chunk, registry, factories,
  lists, lifecycle and typed string channels. Canonical token identity, large
  names and final-release/coalescing/chunk deletion are checked; concrete
  field/registrar/allocator/byte/sync services remain controlled.

- [String pool and table](../../docs/engine/string-pool.md): fifteen complete
  lifecycle/search/reference bodies, 538 retail cases and actual pool/table
  integration in the messenger oracle. Allocation/chunk/byte/sync leaves remain.

- [List services](../../docs/engine/list-services.md): sixteen shared list and
  reference bodies, 1,350 original-instruction comparisons and real list
  integration into the messenger oracle. Metadata/allocation/byte/pool leaves
  remain controlled; library and compiler recovery remain open.

- [Matrix primitives](../../docs/engine/matrix-primitives.md): complete five-body
  copy/translation subgroup; 896 no-callee retail cases and actual matrix-copy
  integration into the messenger oracle. Two compiler residuals remain.

- [Reflection registration](../../docs/engine/reflection-registration.md): fourteen
  registrar/builder/binding bodies, 487 retail cases and actual Work descriptor
  tables. Eleven bodies match and two (field creation `2fdf40`, naming `2fe000`) are
  `foreign-profile`; main registration (`2fe9c0`) has no C source yet.
  Factories/type/system/vector/allocator/interner services stay
  controlled; complete bootstrap remains open.

- [String fields](../../docs/engine/string-fields.md): twenty-one value/lifetime/
  raw-codec/dispatch bodies, 255 retail cases and 42 owned-string checkpoints
  through actual pool storage and generic lifecycle. Nineteen bodies match; raw
  decode (`30ab20`) and raw encode (`30add0`) have no C source yet, and original
  class descriptor construction remains open.

- [Object fields](../../docs/engine/object-fields.md): fourteen cleanup/persistence
  and concrete reference-field bodies; 230 retail cases plus six owned-graph
  checkpoints through real creation and final release. Thirteen bodies match;
  `igObject_WritePersistentFields` (`2ffe10`) has no C source yet; actual class
  descriptors/other concrete fields remain open.

- [Object lists](../../docs/engine/object-lists.md): complete twelve-body list/
  property group plus name publication; 718 retail cases and twelve persistent
  cold-registry checkpoints through real object/generic lists. Eleven bodies match,
  `igProperty_FindByName` (`3022c0`) is `foreign-profile` and remove-first (`302000`)
  has no C source yet; lower field/pool/allocation/byte/receiver contracts remain.

- [Object creation](../../docs/engine/object-creation.md): twenty factory,
  reflection-allocation and construction/lifetime bodies; 249 retail comparisons
  and thirteen persistent cold-messenger integration checkpoints. Concrete field,
  registrar and allocator services remain controlled. Nineteen bodies match and
  field zeroing (`2ff930`) is `foreign-profile`.

- [Messenger memory](../../docs/engine/messenger-memory.md): complete four-body
  initialization/reset group plus reset forwarder; 254 retail comparisons
  through actual cold selection, lifecycle and reset. Factories and lower
  services remain controlled; all five bodies match.

- [Messenger lifecycle](../../docs/engine/messenger-lifecycle.md): ten full
  argument-clearing, delayed-delivery and context-nesting bodies; 464 retail
  comparisons through real selection/dispatch, including nested enqueue. Nine
  bodies match, among them three forwarding bodies with an 84-byte match; the expiry
  update (`38d0a0`) has no C source yet; lower services remain
  controlled.

- [Messenger dispatch](../../docs/engine/messenger-dispatch.md): complete fourteen-body
  receiver selection/registration/dispatch block, 1,561 retail comparisons; all
  fourteen bodies match, five of them forwarding wrappers. External services
  and receiver callbacks remain controlled.

- [Messenger results](../../docs/engine/messenger-results.md): complete 32-body
  typed channel block; 1,196 original-instruction return/RAM/call-order cases through real list,
  matrix, pool, table and chunk services; allocator/metadata/byte/sync leaves
  remain controlled.

These modules retain retail guest references behind explicit memory accessors.
They are excluded from the matching build and matching-progress counts.

- [Material contact](../../docs/engine/material-contact.md): complete seven-helper
  Lua MAT engine module, 61,549 original-instruction return/RAM comparisons with
  no controlled callee leaves. The adjacent producer is recovered below with
  explicit platform/service leaves.
- [Material runtime](../../docs/engine/material-contact.md#material-producer-and-receiver-lifecycle):
  five complete adjacent controller bodies, integrated recursive accumulation,
  instance initialization/update, receiver registration and message dispatch;
  3,055 retail cases include direct box-membership recovery and integrated
  update/search with that leaf. Platform, matrix and Lua leaves remain controlled.

`object-storage.c` / `object-storage.h` recover the complete ten-body object storage
helper run and encoded-selector dependency (716 bytes). The retail oracle checks
726 cases; registration composition adds 487 cases with original storage wrappers.
See [storage contracts and boundaries](../../docs/engine/object-storage.md).

`field-factories.c` / `field-factories.h` recover eighteen concrete descriptor and
base allocation/header bodies (1,752 bytes). The retail oracle checks 276 cases;
487 registration cases also compose actual Work factories and initialization.
See [factory contracts and limits](../../docs/engine/field-factories.md).

`metadata-bootstrap.c` / `metadata-bootstrap.h` recover ten metadata/registry/header
bodies (1,216 bytes). The retail oracle checks 214 cases; 487 registration cases
compose original metadata and descriptor factories with naming and retaining
registry insertion. See [metadata contracts and limits](../../docs/engine/metadata-bootstrap.md).

`internal-object-lists.c` / `internal-object-lists.h` recover the full raw/retaining
list run and internal factory (22 bodies / 2,324 bytes). The retail oracle checks
379 cases, including persistent lifecycle; 487 registration cases compose original
field-container allocation and growth. See [contracts and boundaries](../../docs/engine/internal-object-lists.md).

`object-base.c` / `object-base.h` recover ten original base bootstrap bodies;
unsigned descriptor construction adds three bodies through `field-factories.c`.
Thirty-three retail checkpoints prove the two real inherited header descriptors
and eight-field Work layout. See [base bootstrap contracts](../../docs/engine/object-base.md).

`metadata-callback-services.c` / `.h` recover six name-query/replacement and
initializer-array bodies (568 bytes, all exact source). Seventy-eight retail
checkpoints include original Work dependency dispatch; child callback bodies stay
controlled. See [contracts and corrected selector evidence](../../docs/engine/metadata-callback-services.md).

`list-descriptor-copy.c` / `.h` recover eleven memory-field construction/copy and
list-specialization bodies (1,468 bytes, all exact source). Ninety-five retail
cases compose actual lookup, cloning, replacement and publication. See
[copy contracts and boundaries](../../docs/engine/list-descriptor-copy.md).

`list-registration.c` / `.h` recover 32 list metadata/access/registration/provider
bodies (2,092 bytes), composing the original inherited schema and specialization
modules. Forty-eight retail checkpoints validate all four Work child-list metadata
paths and repeated initialization. See [contracts and boundaries](../../docs/engine/list-registration.md).

`memory-field-values.c` / `.h` recover 32 memory/scalar/support bodies (1,168 bytes).
The 113 retail checkpoints include actual registered Work/list instance creation,
string/integer/reference population and complete final release. See
[lifetime contracts and remaining services](../../docs/engine/memory-field-values.md).

`array-storage.c` / `.h` recover the aligned array allocator and named alignment
selector (two bodies / 564 bytes); the 228-byte allocator has exact source.
151 retail cases and the 113-checkpoint populated Work lifetime composition
verify allocation/status/initialization and retained registry behavior. See
[storage contracts and limits](../../docs/engine/array-storage.md).

`memory-field-copy.c` / `.h` recover four contiguous copy/print/visitor bodies;
`memory-buffer-services.c` / `.h` recover nine contiguous owner-directed buffer
helpers. The object-field adapter also recovers the original callback visitor.
Together: 14 bodies / 1,668 bytes; eleven bodies / 1,356 bytes match, the 256-byte
object visitor is `foreign-profile`, and the two 28-byte allocator tail dispatches
(`2ed4c0`, `2ed5a0`) have no C source yet.
167 retail cases and the extended 113-checkpoint Work lifetime suite verify the
[copy, buffer and traversal contracts](../../docs/engine/memory-field-copy.md).

`allocator-registry.c` / `.h` recover 13 owner/selector/allocation bodies (772 bytes),
including the shared-tail wrapper. Eleven bodies /692 bytes are exact source; the
shared-tail wrapper (`2ed1c0`) and the direct tail (`2ed240`) have no C source yet.
186 retail cases and a114-checkpoint Work/list/runtime-header composition verify
[registry contracts and remaining boundaries](../../docs/engine/allocator-registry.md).

`registry-bootstrap.c` / `.h` recover 17 registry/context bodies (1,512 bytes),
including original concrete selector/name lookup. Fifteen bodies /1,448 bytes are
exact source; list allocate/delete (`2fa6c0`, `2fa6e0`) have no C source yet.
191 retail cases and the116-checkpoint
Work/list/runtime-header/registry-lifetime composition verify
[bootstrap contracts and remaining boundaries](../../docs/engine/registry-bootstrap.md).

context-lifecycle.c / .h recover seven context lifetime/delegation bodies
(1,928 bytes), all seven exact. 244 retail cases and the210-checkpoint
context/Work/list composition verify [lifecycle contracts](../../docs/engine/context-lifecycle.md).
The slot204 allocator builder and concrete tracker/allocator backends remain open.

allocator-builder.c / .h recover the complete2,064-byte builder and metadata
lookup helpers (three bodies /2,140 bytes). 280 retail cases cover full dispatch,
recursive aliases and backing/publication policies. The16-byte default metadata
wrapper has exact source; the builder matches as
`src/unmatched/MemoryContext_BuildAllocator.cpp`.
See [builder contracts and backend boundaries](../../docs/engine/allocator-builder.md).

`selectctrl.c` / `.h` recover the complete concrete SELECTCTRL update and general
receiver (two bodies /4,824 bytes). 4,089 original-instruction RAM/ordered-call
cases cover all 1,187 non-padding words, ownership callbacks, input/command paths
and persistent generate/select/close cycles. Both bodies match
(`src/unmatched/Gap__Bec__beSelectCtrl__vfunc_31.cpp` and
`src/unmatched/Gap__Bec__beSelectCtrl__vfunc_33.cpp`);
[contracts and remaining dependencies](../../docs/engine/selectctrl.md).

`pad-manager-selection.c` / `.h` recover the complete88-byte player/fallback
record lookup used by SELECTCTRL. 201 direct cases and216 composed manager cases
run its original instructions; the combined suite has4,506 cases and1,208/1,228
instruction addresses (20 padding words). Physical pad sampling remains controlled;
[record-selection contract](../../docs/engine/selectctrl.md#original-pad-record-selection).

The [joint selector/manager oracle](../../docs/engine/selector-manager-composition.md)
composes the selector, manager, pad selection and empty presentation
close bodies in144 lifecycles /3,146 original-instruction checkpoints. Immediate
message delivery, initialization, model/device and primitive services remain
controlled; no matching code is attributed to this validation.

`list-controller.c` / `.h` and `chip-list-view.c` / `.h` recover five complete
shared paging/chip-view bodies (2,196 bytes). All five /2,196 bytes have matching
source, including both contiguous helper blocks. 3,149 original-instruction cases execute all544 non-padding words;
model/property/text/format services remain controlled.
See [ListCtrl/chip-list contracts](../../docs/engine/list-controller-chip-view.md).

`chip-controller.c` / `.h` recover the full7,232-byte chip transaction update.
Inventory filtering, preview record restoration, fresh confirmation debit and
error/close state behavior are compared with original instructions. The update
is `foreign-profile` in `data/check-categories.tsv` (code bytes identical only under a
provisional compiler override; `src/unmatched/Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_21.cpp`);
[contracts and limits](../../docs/engine/chip-controller.md).

`item-database.c` / `.h` recover the complete item request/value and database
index/value/count blocks plus the actual chip selector: ten bodies /1,168 bytes,
all exact in matching source. The474-case oracle composes existing property-name
lookup and checks all290 non-padding module words plus two padding words.
Messaging/receiver delivery and strcmp remain controlled;
[contracts and limits](../../docs/engine/item-database.md).
