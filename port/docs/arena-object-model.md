# Arena object model — retargeting the port's game logic onto the decomp's structs

This page is the contract and the plan for holding the port's game state as the
decompilation's structs in arena memory. The agreed direction is to retarget the
fight rules first, then replace the port's game types with the decomp's
authoritative structs in arena memory; the model and the decisions below are
approved. The technical specification lists *arena lifetime,
reference checks and allocation failure behavior* as contracts needed **before the gameplay runtime expands**
([State and memory ownership](technical-spec.md#state-and-memory-ownership)); this page is that contract.
Phases P0, P1 and P2 (fight rules) are done and P3 is in progress. Phases are
proposals until their exit evidence exists; the pointer model ([`project/pointer-model.md`](project/pointer-model.md))
is settled and not reopened here.

## Current state

The session arena holds typed databases, player-property trees, stage-info
instances, the shared native window/controller state, concrete shop and STATUS
records, and the model controller, actor, status and Action2 records described
under [retargeted modules](#retargeted-modules). Host facades retain
callbacks, borrowed scene/asset contexts and native rendering/input/resource
owners. The completed and pending boundaries are listed below; the remaining
per-feature adapters are not a claim of a fully retargeted game runtime.

The decomp's `include/dw4/reflected.h` is the layout authority. The matching
build and `make reflected-check` verify its offsets; the native build includes
it with the port's own flags. Four-byte references remain arena handles.

## The model

1. **One game arena per session.** A single contiguous host allocation addressed by 32-bit offsets (`dw4_handle`, 0 = NULL, 16-byte
   aligned payloads, as the scene arena). Two regions: a *persistent* region (player records, databases, global services) and a
   *stage* region that is released as a whole when a stage is unloaded (matching retail's stage heap teardown). The existing scene
   arena stays the loader's staging area; its payloads are copied or adopted into the game arena at stage publication.
2. **Objects are the decomp's structs, byte for byte.** An object is `mo->size` bytes at its handle, laid out by
   `reflected.h` (field offsets are the authority). `_vtable` holds the retail vtable address (the generated schema
   already records it per class) and `_refCount` the 23-bit count with its flag bits, exactly as `igObject_InitHeader` writes them.
3. **Handle accessors, never host pointers in fields.** `dw4_arena_at(arena, handle)` resolves a handle to a host pointer for the
   duration of a call; `DW4_ARENA_OBJ(arena, Class, handle)` checks allocation bounds and size. Constructors and typed owner boundaries
   also validate the class through the registry (the vtable word maps to the class or a descendant). Reference fields stay 4-byte `int` and are read through these accessors. A host pointer is never stored in the
   arena (specification: host pointers must not be truncated into recovered four-byte fields).
4. **Allocation failure is explicit.** Allocation returns a NULL handle and records the reason; every constructing caller checks it
   and fails the operation through the port's retry/back path rather than continuing (specification: failure handling).
5. **Lifetime is the engine's.** Reference counting follows the engine's inline release idiom (`--refs; if ((refs & 0x7fffff) == 0) igObject_Destroy(o)`, matched `igObject_Destroy` at `0x2ff820`: the
   destructor slots 08, 10 and 00 in that order, then the buffer is freed); a stage teardown checks that its region holds no live object and reports leaks in diagnostic builds.
6. **Virtual dispatch through a class registry.** The retail vtable word identifies the class; a registry maps it to the class's host
   method table (`dw4_class`: name, metaobject, slot functions). Ported methods register by (class, slot). Calls the matched C makes
   through `obj->vfunc_N(...)` become registry calls, so retargeted code keeps the original dispatch order.
7. **Host-owned resources stay outside.** GPU textures, audio voices, windows and files are owned by host services; an arena object
   holds a 4-byte host-resource id resolved through a service table, never a pointer.
8. **Endianness and width.** The arena assumes a little-endian host (checked at startup, like the PS2); no field assumes
   `sizeof(void *) == 4`. Widening to host pointers stays optional later work.

## Plan

| Phase | State | Deliverable | Exit evidence |
| --- | --- | --- | --- |
| P0 | done | `include/dw4/arena.h` / `src/arena.c`: two-region allocator, bounds/liveness-checked handle accessors, class registry with inherited slots (`dw4_class_register_schema` loads every class with a known vtable from the generated schema), `igObject` reference counting with the `igObject_Destroy` destructor order (slots 08, 10, 00, then free); contract tests (alignment, NULL and stale handles, exhaustion, reuse, stage reset leak report, inherited slots, destructor order). | `make -C port check-arena` passes; a handle is a 4-byte offset (test). |
| P1 | done | `include/dw4/arenapack.h` / `src/arenapack.c`: a pack's objects as **typed instances** in the game arena (reflected layout, header and vtable word stamped, references and strings as handles, pool blocks copied); `include/dw4/arenadb.h` / `src/arenadb.c`: clean-C ports of `beDataBase_GetRecordInt/Bool/String` on `beDataBase`, `igNamedObjectList`, `igNamedObject` and the list classes. | `make -C port check-arenadb`: on the real Main Lobby pack, **12 databases, 228 columns, 25,889 numeric/bool cells, 3,502 string cells and 197 edge probes** (rows outside the table, missing columns, invalid input) agree with `dw4_database_*` exactly; the answers survive releasing the pack, the host owner and the mount. |
| P2 | fight rules done | The fight rules read **typed tables**: `dw4_dbtable` (arena + `beDataBase` handle, `include/dw4/arenadb.h`) replaces the host database in `fightcalc.c`, `fightstatus_p2e.c`, `fightstatus_e2p.c`, `fightmagic.c`, `technique.c` and the combat owner's contexts; `dw4_databases_open` loads each `beDBManagerInfo`'s `beDataBase` closure (about 200 KB each) into the session arena and `dw4_databases_table` / `dw4_database_typed` hand it out. The formulas are unchanged, so behavior follows from the accessor equivalence of P1. | **`make -C port check-fieldstage` passes unchanged** (retail P2E/E2P damage, hit/critical and EXP anchors, plus source-derived status/magic integration checks; the mission route has its own target), plus the database, hub and player-init tests. The direct fight-record reads are under [fight record reads](#fight-record-reads). |
| P3 | in progress | Module-by-module replacement of the remaining port-native game types, each behind an equivalence test, deleting the host-private type when its last user moves. Completed modules are listed under [retargeted modules](#retargeted-modules); what is left is under [open items](#open-items). | `make -C port check` passes unchanged (the full suite, including `check-fieldstage` and the four malformed-pack modes of `check-database`); `make -C port check-arenadb` compares the typed tables and the owner's own twin with an **independent decoding of the pack records** (the former host builder, kept in the test as the oracle) on every cell, string and edge probe. |

Rules for every step: the matched C is the source of behavior; the port version is clean C (matching-only constructs such as
`volatile`, dummy virtuals, `asm` padding and declaration-order tricks are not copied); each retargeted function names its source
in a comment and its behavior check (specification: recovery provenance); retail comparisons that already pass must keep passing.

## Decisions

| Decision | Options | Decided |
| --- | --- | --- |
| Arena size | fixed 32 MB (retail's) / growable | **Fixed**, retail-sized: handles stay stable, exhaustion is a defined error, and growth can be added later behind the accessors. |
| Persistent vs stage region | single region / two regions | **Two**, so a stage unload is one release plus a leak check. |
| Virtual dispatch | registry / generated switch per class | **Registry**: smallest change, mirrors retail's vtable word. |
| Property folders (`igProperty`) | keep host-side until recovered / recover now | The folders live in the session arena as typed `beDataObjList` trees (`beDataObjInt/String/IntList/StringList/BoolList/FloatList/ObjectList`, `igIntList`/`igBoolList`/`igFloatList`/`igStringRefList`, `beNDMWItem*`, `beUnicodeObj`) behind the same `dw4_property_*` accessors; no `igProperty` class is needed. |
| Pace | all at once / module by module | **Module by module**, in the order of the port task list's open work. |

## Generic loader rules

* **The generated schema lists a class's own fields only**, so a class whose fields are all inherited (every list: `igNamedObjectList`,
  `igIntList`...) receives no values from `dw4_object_from_record`. The loader builds an ancestor-merged class description (ancestors'
  fields first, absolute offsets) per class and builds instances against it (`dw4_object_from_record_with`); existing callers are unchanged.
  Zero-field ancestors skip the null-source zero-byte copy in `arenapack.c`; the independent database closure comparison passes with it.
* **A pool block's contents have no kind of their own**: the list class that points at it decides. The `igObjectList` family (169
  classes) stores object ids, which the loader rewrites into handles (once per shared block); other list families (int, string, vector)
  keep their raw contents until a reader needs references there.
* **Retail quirk kept**: a wrapped cell index of exactly -1 is indistinguishable from "column not found" in `0x3a93a0`; the typed accessor
  mirrors it, as the host database did.

## Retargeted modules

### Session arena and property folders

There is one process-wide session arena with owned-block lists and a recursive
lock. Property folders and databases use it.

`src/playerrecords.c` keeps its API; a folder is a `beDataObjList` of typed `beDataObj*` records in the session arena (value kinds, the
item classes by `_kindNo`, nested folders, unicode objects; the list class under an object-list record tells folders, items and unicode
arrays apart). Commits swap payloads after a full preflight and publish swaps list handles; closing an owner frees its tree recursively.
The equivalence evidence is a comparison with the former host implementation as an oracle: 40 rounds of 400 random operations (all
setters, copy, commit, commit-pair, publish, join, snapshot, nested folders; every read compared, session arena empty at the end). That
host implementation no longer exists.

### Stage objects

`dw4_stageobject` does not hold a host-decoded `dw4_object`: each pack's info records are loaded shallowly
(`dw4_arena_pack_load_roots`: values and strings only, references NULL because the asset layer still follows them in the pack) as typed
instances in the session arena, and readers use `dw4_stageobject_class/name/kind_string/rgba/same/ref_id` over the recovered
`igNamedObject`, `beModelCtrlInfo` and `beBkColorInfo` layouts. The transient pack decoders (`fieldgen`, `script`, `playerpoint`, which
read a record and discard it) keep `dw4_object` as a loader helper, not game state.

### Host database

`dw4_database` holds only a name, a script-object view and a typed table; every `dw4_database_*` accessor (shops, status views, player
records, field generators, memory card, technique, the fight rules) reads the typed `beDataBase` instance in the owner's arena (the
session arena). There
are no host copies of the columns, strings and numeric tables. The structural checks of the former host builder (list classes, counts
against capacities, block sizes, whole rows, column objects) live in `dw4_adb_validate`.

### Fight record reads

The calculation and both status-time modules resolve scalar, SKILL and
WAZALIST records through the authoritative `beDataObj*`, `igIntList` and
`beNDMWItemWaza` layouts in the owning arena. Those rules do not use a
copied technique-item view. The borrowed record-reference API
reuses the name/alias/type lookup and reacquires on every read; record
publication and recalculation cannot leave cached references in the fight code.

`check-fightrecords` passes 47,318 comparisons with the former property readers,
including mutations and staged publication, and `check-fightrecords-retail`
passes 384 original-instruction technique lookups with controlled property
lookup. Formula and RNG code is unchanged. See [combat validation and limits](combat.md#fight-records).

### Shared window/controller arena state

Window, STATUS root, shop root, view and SUBWND state is typed arena state:

| Owner | Arena state | Host facade |
| --- | --- | --- |
| Every `dw4_menu_window` | `beNDMWWindow`-derived instance: active byte, four counters, parent handle, `beNDMWWindowList` count/capacity/ordered child handles | Callback/resource owner and child-wrapper lookup array; no scalar/count mirror |
| STATUS root | `beNDMWStatusCtrl00`: return selection, retained menu and child-count snapshot | Scene/record/view context; rule adapters are temporary stack values |
| Generic shop root | `beNDMWShopCtrl00`: entry/player, child-count snapshot and common lifecycle | Factory, stat/view services and error text |
| Concrete STATUS views | Reflected title/selector instances and common state, including selector start point; resource and selector fields as under [menu resources](#menu-resources-stock-and-retained-references) | Public context as construction input; the native adapter's deduplication, resource limits and service order |
| SUBWND slot | `beNDMWStatus` manager and `beNDMWStatusInfoRam`, including root handle, mode/player and active/counters | Registry token, callbacks and private unpublished preparation tree |

Parent and child handles preserve the native tree's exclusive lifetime:
children close before their parent, and typed allocations release during teardown.
The parent link is borrowed under that contract; complete retail parent-retain
reference cycles and unrestricted callback list replacement are not implemented
by this adapter. Native virtual callbacks remain host services. This does
not establish a complete Alchemy object graph or virtual-method retarget.
Pure scalar test inputs and host resource contexts
are not themselves persistent game objects and need not be placed in the arena.

`check-menu-arena` checks typed identities, four-byte links, bounded append/prune
order, cleared tails, exhaustion cleanup and complete teardown, and passes under
ASan/UBSan. Original command/tree and STATUS scalar oracles still compare against
retail instructions; prepared views exercise all four player slots. See
[window ownership](status-menu.md) and [shop root](shop-root.md).

### Concrete shop and STATUS records

Concrete service controllers allocate their recovered classes and retain
mutable control fields in the session arena. XDATA and chip
upgrades, bank/editor, appraisal, disk buy/sell, equipment/junk sales, Digi-Lab
and card A0/A1/A2 store their primary/substate/flag, return selection,
child-count snapshot and applicable menu/page/cursor/quantity/price fields there.
Card player identity uses `_playerNo`; `_account` is the borrowed panel handle.
The card root's ordered player list is an `igIntList`.

STATUS equipment/FOLDER/skill, Power/Main/Sub, DEVICE, detail, disk, flag and
CtrlBit/SendBit likewise own concrete arena instances. Pure rule functions keep
their scalar input ABI: owners reconstruct a stack projection for the call and
publish it back, with no authoritative host scalar record between updates.
Private callback borrows end with the update. Child selection sinks use
`parent_window`, never a pointer into that temporary projection. The STATUS submenu diagnostic
`*_window_state` APIs return snapshots by value; `*_window_is` tests ownership.

Recipient identities and DEVICE-detail inventory counts are typed `igIntList`
fields. DEVICE kind filters and byte decisions use `igIntList`/`igBoolList`,
including the recovered restriction flags. Replacement allocates before
publication; failure preserves the old field, and controller teardown releases
the list and its data. Shared player records remain owned by their record owner.

Validation includes the unchanged shop acceptance routes, all four prepared STATUS
players and the related original-instruction rule oracles. `check-menu-arena`
adds direct arena mutation across updates, snapshot isolation, 128 repeated
submenu/equipment lifetimes, scalar-list failure preservation and complete
teardown, including ASan/UBSan with leak detection disabled.
This validates the native ownership adapter, not additional retail
visual parity or unsupported co-op service flows.

### Menu resources, stock and retained references

The view owner stores its model names, RAM slots, close sequences and font
group/name pairs in the recovered `_modelClose*`/`_textClose*` fields, using
`igStringRefList` and `igIntList` with owned arena string blocks. The native
adapter's deduplication, resource limits, service order and final close/poll
boundaries are preserved. Selector cursor names, row/start/position values and
`igBoolList` decisions also live in their actual selector instances; the public
context is construction input rather than a persistent parameter mirror.

Digi-Lab's initial player/species/weapon comparisons use `_playerNoList`,
`_digimonNoList` and nested `_wpuNoListList`. STATUS skill and Evolve own
`beNDMWShinkaCtrl` / `beNDMWShinkaObjectList` snapshots with the form
calculation's sixteen values. Card album model names and RAM slots use the
recovered A1 string/int lists. These records keep the one-player
service admission boundaries; they do not add co-op shop/demo behavior.

Explicit property-list leases keep the actual item/folder payload alive across
replacement, publication and owner teardown. Ordinary borrowed APIs retain their
lifetime. Equipment's seven reference fields use those leases; DEVICE
detail retains its actual D0 window through parent pruning and releases it at
the recovered completion boundary. A pruned retained window is detached, with its
complete facade/resource tree kept until the final release. Parent links remain
borrowed and native child ownership remains exclusive; unrestricted retail
reference cycles and callback tree replacement are not implemented.

Persistent stock is a `beNDMWStatusInfoWork` with the four actual item lists,
parameter comparison list and `_junkGift`, bound to the hub SUBWND RAM Work
field. Generation uses a private stack image and publishes a complete typed
list. Sold-out updates retain list identity and replace the item reference.
Shop roots/Sales and XDATA chip filters retain those actual lists/items; page
admission decisions use byte lists. Host item views and transaction-index maps
are derived projections, not a second stock store. See [shop ownership](equipment-shops.md#arena-stock-and-item-references).

### Model controller, actor and status Work

Each native model instance owns typed `beBaseInfoRam`,
`beModelCtrlInfoRamData`, the appropriate `beModelCtrlInfoWork` subclass and a
`beModelCtrlNode2` pose record. The manager owns `beModelCtrl` and its ordered
info list. RAM links identify its slot, info and manager. Per-instance Work
holds sequence/cursor/label state, wait names, control/freeze/collision gates,
invulnerability and direction state. Four `beModelCtrlMoveObject` instances
hold channel state; the EE rule ABI is a temporary bit-pattern projection that
never overwrites object headers. Walk templates are typed PDMOVE records, and
AI selection/target/sequence and AITIMER state use `beModelCtrlInfoAI` and
`beBaseInfoRamTimer`.

Sequence/command closures load into the session arena once per shared immutable
program owner. `_comData` points to its actual typed sequence; clones share the
program closure and have independent RAM/Work. Current pose matrices are
published at mutation boundaries and copied by rendering/contact consumers.
The host pose backend retains authored Euler/animation projections to preserve
its float round trips. Queries do not advance clocks or pose state.

Player/enemy Work stores status timer/first/icon/stat lists and poison values.
Named status timers use actual RAM timer records; pure status rules operate on
call-local projections. The `dw4_status *` query is a read-only compatibility
projection, refreshed from Work, never rule storage. Native icon markers retain
the unrendered-icon boundary rather than claiming actual retail icon
instances. Health/record/slot values use Work's typed numeric records and RAM.
Legacy callback state is an input/output bridge: only edits since its last
publication are imported, preserving later native writes and callback precedence.
Native sampler, callback and Action2 services remain host contexts; their
documented timing/fidelity limits are unchanged.

Validation combines direct arena mutation, independent clones, retained-reference
replacement/teardown, original-instruction actor/health/freeze/contact oracles,
prepared/live/GPU STATUS and service acceptance, plus actor/typed-program
lifetimes and the mission route. Explicit arena block baselines check complete
teardown. The contact ctypes fixture checks its size/offsets against its C header,
and the pure view oracle's unused close leaf aborts if executed.
The empty-inventory purchase copy skips a null-source zero-byte memcpy;
this changes no purchase rule or RNG calculation.

### Action2, hit-volume and stat comparison records

The supported Action2 programs own `beAction2`, info/RAM/Work, action data,
component/list/string, node and WAIT timer records in the session arena.
The recovered timing API translates its bounded addresses at the call boundary;
object fields and list entries contain actual handles. The manager/info/RAM and
active-data/component links are traversable. Component replacement preserves the
native timer/node lifetime, releases replaced components and clears list tails.
Owners close explicitly before reinitialization, scene teardown or clone release.
The retail oracle compares a normalized diagnostic image, never host addresses.

Joint bounds/states, wait/index/freeze state and named-timer values are read
from the actual records. Current and previous `igAnimationState` / `igAnimation`
objects hold names, time biases, duration and blend duration. MODELCTRL action
selection and fade values/step/limit/state also use the actual data/Work fields;
rule PODs and public observations are temporary projections. Native clock
sampling, loop/clamp policy, Euler reconstruction, decoded animation resources,
render events and fade sampling history remain backend context. The bounded
adapter does not implement unrestricted Alchemy dispatch, material attributes,
FLASHSET rendering or the complete original animation combiner.

Work `_subCommand` owns `beModelCtrlSubCom` / `igObjectList` and actual
`beModelCtrlSCHitBox` objects. Producer `39a500` establishes `_startFrame`,
`_endFrame`, kind, bullet mode and geometry: length `-1` becomes `100000000`,
otherwise the endpoint is the EE float sum of start and length. Consumers read
that endpoint without a subtract/add round trip. Native eight-volume admission is retained. Sequence changes/AllClear and
teardown release the list entries. Entries advance through the
[scheduler](#subcommand-scheduling-and-retained-node-locks); effect/sound
subcommands and named-bone/track locks are under
[mixed subcommands](#mixed-subcommands-and-attachment-resources).
Support-volume admission is unchanged; these records do not establish retail
combat timing or geometry parity.

STATUS comparison values occupy Work `_parameter`, a thirteen-element
`igIntList`. The retail field constructor declares both `_parameter` and
`_preview` as integer lists; `3d60e0` UPDATE/ONPREVIEW/OFPREVIEW consume
`_parameter`. `_preview` is constructed empty; no use is inferred for it.
`_parameter` is not a player folder. Stock and preview share the actual Work through a borrowed binding;
other STATUS owners allocate their own Work. SUBWND RAM points to that Work.
Player admission and service callbacks remain facade context; returned snapshots
are isolated values. Failure invalidation clears the list, and Work outlives its
windows and is released by its stock or stat owner.

Validation includes 128 Action2/preview lifetimes, direct arena edits, independent
model clones, the original title/Action2 tick oracle, stat preview traces and the
`check-modelsubcom-retail` producer oracle (370 signed-kind, sentinel,
rounding and geometry cases). Full/oversize program replacement, cleared tails,
freeze and signed clock extremes are also checked.

### Subcommand scheduling and retained node locks

Work's HITBOX list advances through the original frame accumulator and
first-start/strict-end/removal rules. Native emitters call combat synchronously
at the recovered model phase; there are no birth timestamps, outer volume scans
or once-per-activation caches. System frame input is distinct from the
quantized/clamped named Frame timer. Source callback transports publish current
arena metadata before dispatch and preserve callback-write precedence.

Node attachment uses the actual Work flag, retained node reference and local
offset. Parent close retains the last matrix; unlock/REMOVE/teardown releases it.
The complete parent matrix is preserved, and movement channels are held while
locked. Same-frame hit-body caching retains its original session-time boundary.
The callback contexts detach when either owner closes. The field fixture
releases its temporary source scene after the destination takes its snapshot,
so arena-baseline checks are complete.

See [phase, clocks, limits and validation](controller-services.md#retail-subcommand-phase-and-node-locks).
The instruction oracle compares
520 scheduler states, 136 frame samples, 128 node-lock matrices and 370 producer
payloads. Native ownership/phase tests cover source replacement, retained entries,
freeze, query isolation and both teardown orders.

### Mixed subcommands and attachment resources

SCEffect owns its copied model/sequence strings, generated slot and flags;
SCSound owns its copied name and exact 64-bit backend token. All three command
classes share Work's actual list and common frame payload. Aggregate release
keeps strings alive through retained callbacks. Selective versus sequence-wide
clear follows the recovered virtual finish rules. Named lock names and retained
TRC handles live in Work, and manager-owned imported recorder closures remain
alive until every model lock has been released. Native bone/motion caches own
copied lookup names and decoded resources; no host pointer occupies these fields.
Prepared manager teardown finishes all sources before freeing any sibling.
See [behavior, validation and remaining limits](controller-services.md#effect-sound-and-attachment-services).

## Validation

- `make -C port check-arena`, `check-arenadb`, `check-menu-arena`,
  `check-fightrecords`, `check-fightrecords-retail`, `check-fieldstage` and
  `check-modelsubcom-retail` are the focused targets named above; the full
  native suite is `make -C port check`.
- Sanitizer runs use ASan/UBSan with leak detection disabled; explicit arena
  block baselines check complete teardown instead.
- Normal live STATUS input/restoration and GPU success/explicit-failure checks
  are part of the acceptance for the window, record and model modules.
- The capture-dependent pose/fog checks skip without their private captures.
- The matching build is unaffected: `check typed-check reflected-check link`
  keeps its baseline and a byte-identical relink.
- The broad retail target's older host-database fixture is separate test work.

## Open items

- **P3 remains open.** Audit the other runtime families and unsupported
  controllers, including player input/attack adapters, scene/controller services
  and the remaining renderer/resource interfaces.
- The prepared generic effect/sound and attachment services have typed
  ownership; general media coverage, full recorder traversal and Alchemy
  animation/material execution remain implementation gaps.
- Transient `dw4_object` pack decoders remain loader helpers.
- Complete retail parent-retain reference cycles, unrestricted callback
  list/tree replacement, a complete Alchemy object graph and a virtual-method
  retarget are not implemented by the window adapters.
- Co-op shop/demo service flows are not added by the arena records.
- Widening handles to host pointers is optional later work.
- The separate gameplay/rendering/timer acceptance gaps stay in the owning
  subsystem documents.
