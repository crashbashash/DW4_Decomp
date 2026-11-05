# Context construction, record ownership and tracker delegation

Finding [#897](../findings/findings-0751-1000.md#f897) recovers seven bodies /1,928 bytes in
[context-lifecycle.c](../../recovered/engine/context-lifecycle.c): constructor152,
destructor188, name initialization116, retained slot setter184, allocation delete64,
and the contiguous special delegate668/removal556 pair. Four bodies /552 bytes
have matching source: destructor188/setter184 (**372 matched bytes**) in
[context-slot-lifetime.cpp](../../src/engine/context-slot-lifetime.cpp) and the two
helper bodies (180 bytes). Constructor and the
delegation/removal pair retain assembly and private candidates.

Six body-derived names are applied; the setter retains its evidenced generated
class/slot name. ABI projections describe observed layout and are not claims of
original C++ spelling.

## Constructor, destructor and original names

The actual constructor is 2f25d0. It calls the recovered base header initializer,
publishes vtable52f510, stores header8=30/flags12=0/parent16=0, sets one reference,
clears all6,624 record bytes and invokes current slot180. That method (2f49e0)
copies46 names from pointer table4c2170: each127-byte copy is followed by an explicit
zero at the128th byte. This establishes a128-byte inline name field, including the
original names Bootstrap, Default, Current and NonTracked.

The destructor is 2f2670, not the constructor that [#896](../findings/findings-0751-1000.md#f896) describes.
It skips null self; otherwise it republishes52f510, clears its reference word and
all record bytes, initializes names, releases parent16 using full-word decrement/
low23-bit destruction, then deletes the allocation for a positive signed low16 flag.
The parent cell is not cleared. Delete (2f8830) chooses generic object-allocation
release when the object system is active, or the lower free service otherwise.

Finding [#898](../findings/findings-0751-1000.md#f898) refutes that constructor interpretation while preserving [#896](../findings/findings-0751-1000.md#f896)'s
valid vtable-binding evidence. Destruction does not itself walk the allocator
pointers that were cleared; original slot removal is a separate path.

## Retained allocator slots

The setter at 2f28d0/vtable100 accepts0..45. An identical existing pointer causes
no ownership change. A different non-null old pointer invokes current slot212
before publication. It publishes the new pointer, increments its full reference
word and, for non-null values with index>=current header8, stores index+1 at header8.
Null assignments do not update that header. Its wider meaning is not inferred.

The210-checkpoint composition constructs the context, initializes all original
names, installs46 allocator bindings through this setter, runs original registry
creation and populated Work/list/header lifetime, removes every binding, then
destroys the context. The externally owned allocator changes reference1->47->1.
The context fixture sits in guest storage distinct from the metadata field-name
selector, so both recovered layouts coexist; an address overlapping the selector does not work.

## Special delegation and removal

Slot208 (2f64e0) calls the current slot204 allocator builder with output-first
temporary/context/selector/mode1. It captures the builder's status and current
record allocator. Record descriptor+60 supplies an optional feature string and
descriptor+80 overrides the system+124 tracker limit.

Context flag bit0 enables inherited tracking. An InhibitEventTracker substring
suppresses attachment. Context bit1 with selector!=1, or a UseEventTracker substring,
selects a newly constructed tracker through selector3, factory2c5780 and init2dcc40.
It invokes tracker92, attaches through allocator360 and releases its temporary
owned reference. Otherwise it obtains selector1's borrowed tracker through356
and attaches it if non-null, without releasing that borrowed reference. Without
context bit0, only the UseEventTracker request creates a tracker. The builder status
is always copied to the caller's output and is not used to add an error guard.

Slot212 (2f6780) captures a valid non-null allocator and clears the record pointer
first. Only an allocator whose low23 reference bits equal1 runs special cleanup:
optional188 predicate/348 preparation,128 close, then backing policy at record+136.
Bit0 takes precedence over bit1. The chosen bit is cleared before subsequent calls.

For bit0, a non-null104 backing pointer is detached through output-first96, its
owner is looked up and released, then the backing is freed if that owner exists.
For bit1,144 supplies a signed32 size,96 detaches the backing and global587218's
slot72 receives an output temporary, tracker, backing and sign-extended size.
All paths finally release the captured allocator reference. The original header8
condition is preserved literally: index==header8+1 stores index at header8. It is
not silently replaced with a conventional shrinking-count condition.

The [allocator builder recovery](allocator-builder.md) implements the
complete2,064-byte slot204 dispatcher and composes it into selector/name/delegate
oracles. Concrete allocator/tracker factories and virtual methods remain callbacks.

## Verification and remaining work

python3 testing/test_context_lifecycle_retail.py checks **244** original-instruction
RAM, defined-return and ordered-call cases across all seven bodies. It covers
null/signed16 destruction, parent flags/references, slot bounds/identity/replacement,
all tracking-option branches, inherited/owned tracker lifetimes, backing-policy
precedence, callbacks, special selector/name dispatch and the unusual header8 rule.

python3 testing/test_memory_field_values_retail.py --context-lifecycle checks
**210** states with original context construction/names/retained slots, metadata,
populated Work/list lifetime, runtime header copy, registry shutdown and context
slot release/destruction. Allocator values remain supplied fixture objects; their
backend implementations and global selector publication remain bounded. The other
modes retain their113/114/116 counts.

Twenty-one dependency tests verify constructor/destructor sites, concrete slots100/
180/208/212 and reviewed roots. Retail objdump confirms the complete shapes.
Native gameplay is unchanged. Next: context configuration/stack
control, actual allocator/tracker backends and remaining Lua gameplay receivers.
Private candidates/logs: repository-relative ../scratch/lua-engine-recovery/.
