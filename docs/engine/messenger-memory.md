# Messenger memory initialization and reset

The complete contiguous four-body group at `38bee0..38ca40` has readable
[behavioral C](../../recovered/engine/messenger-memory.c): initialization, two
temporary reference-owner destructors and reset, totaling 2,904 code bytes.
The same adapter includes the 28-byte `beMessenger::vfunc_26` reset forwarder,
for five bodies / 2,932 bytes. Finding [#871](../findings/findings-0751-1000.md#f871) records the recovery. All five
bodies match: the forwarder in [beMessenger.cpp](../../src/game/beMessenger.cpp), initialization in
[beMessenger_InitializeMemory.cpp](../../src/unmatched/beMessenger_InitializeMemory.cpp), reset in
[beMessenger_ResetMemory.cpp](../../src/unmatched/beMessenger_ResetMemory.cpp), and the two destructors as
compiler-emitted members of the units in
[beMessenger_EnqueueSelected.cpp](../../src/unmatched/beMessenger_EnqueueSelected.cpp) (`38c390`) and
[beMessenger_SelectReceivers.cpp](../../src/unmatched/beMessenger_SelectReceivers.cpp) (`38c410`).

The [name generator](../../scripts/seed_names_messenger_memory.py) identifies
initialization and reset from reflection and original instructions. The precise
instantiated owner types of the two destructors are unresolved, so they retain
`FUN_` names. The forwarder keeps its existing vtable-slot name.

## Initialization

`beMessenger_InitializeMemory` (`38bee0`) first constructs an argument-data
object and replaces the messenger's current argument reference (+16), retaining
the replacement before releasing the previous object and balancing the temporary
owner afterward. It then initializes three reusable pools:

| Messenger field | Offset | Requested count | Factory |
| --- | --- | --- | --- |
| `_workStack` | +24 | 64 | `358070` |
| `_delayStack` | +28 | 32 | `358950` |
| `_pushPopStack` | +32 | 4 | `358d80` |

Each pool's reserve condition uses its **count**, not capacity: it requests the
fixed capacity if count is at most the requested count. It then calls the original
retaining-object-list resize service (`301ee0`) to set that count. Every requested
slot gets a newly constructed object. Replacement retains the new object,
releases the previous slot, rechecks the list count before storing, then releases
temporary ownership. The original loop still constructs every requested object
if a destructor changes count during replacement; a failed range check suppresses
that slot's store. Recovery preserves these service boundaries and reloads.

Allocator choice is repeated for the initial context and for each pool element.
The function asks `301000` for the receiver's allocator, then uses the global
allocator service (`2f88e0` with global `587110`) when byte `554c14` is zero. A
factory callback changing that byte affects later allocations. Object factory
implementations remain separate dependencies.

Initialization clears nesting count (+36), then sets `_isMemoryAssign` (+48) to
one. It retains the registry/group list (+20) and freeze clock (+40). The function
itself is unconditional; its callers use the initialized flag when deciding
whether to invoke it. The oracle checks both normal initialization and repeated
direct initialization. Controlled factory null results are propagated by this
layer; this does not establish the factories' failure/retry policy.

## Reset and temporary ownership

`beMessenger_ResetMemory` (`38c490`) releases the current argument object and
publishes null. It clears the retained contents of group/work/delay/context
lists at +20/+24/+28/+32, in that order. Each list captures count for the release
pass, then re-reads count and backing storage for the zeroing pass. Destructor
callbacks can change the zeroing extent. After clearing count, reset requests
capacity four: the original condition checks the just-cleared count and does
not skip the call when capacity is already four or smaller. The list objects
and messenger references to them remain allocated.

Reset finishes by clearing nesting count, freeze clock and initialized byte.
The two temporary-owner destructors (`38c390`, `38c410`) release the object at
owner +0 using the low-23-bit reference rule; a positive signed 16-bit deletion
flag additionally deletes owner storage. They return the original owner reference.

The existing reset forwarder in [beMessenger.cpp](../../src/game/beMessenger.cpp)
now explicitly receives and forwards its messenger argument. Its prior source
omitted the argument despite the original call using incoming a0. The corrected
signature preserves all 28 original bytes. The two destructors match as
compiler-emitted members of the units named above.

## Verification and integration

Run from the repository root:

```sh
python3 testing/test_messenger_memory_retail.py
python3 testing/test_messenger_lifecycle_retail.py
python3 testing/test_messenger_dispatch_retail.py
python3 testing/test_messenger_results_retail.py
make check
make typed-check
make link
```

The memory oracle compares original instructions against the recovered adapter
for every body, including defined returns, all RAM outside temporary stack frames,
factory counts and ordered service calls. **254 cases** cover pool counts at
reserve boundaries (64/65, 32/33, 4/5), global/receiver allocator selection and
callback-driven switching, null factory results, temporary reference counts,
old-slot destructor mutation, repeated initialization, reset lists with
0/1/4/8/9/17 elements, capacity 4/32, count mutation during release, signed deletion
flags and null owners/references.

Persistent integration executes original memory initialization together with real
recovered [selection/dispatch](messenger-dispatch.md) and
[lifecycle](messenger-lifecycle.md): initialized-flag checking, cold selection,
immediate queries, enqueue/expiry, context push/pop, reset and reinitialization.
The fixture's factories create distinct work records, delay records and complete
argument contexts in disjoint storage, allowing the actual upper engine bodies
to run. Assertions confirm the original 64/32/4 pool counts and 101 direct factory
calls (five argument contexts, 64 work records, 32 delay records).

Object factories, registry behavior, list resize/reserve/mutation, pool/interner,
allocator/delete and concrete receiver handlers remain controlled. Factory
fixtures supply layouts required by the callers; they are not recovered factory
implementations. In particular, transitive constructor/destructor ownership and
allocation failure policy remain open. Native gameplay and complete engine
recovery are not established by this subgroup. Next work includes actual
factories/registry, lower-service composition and concrete receivers.

The subsequent [creation recovery](object-creation.md) executes the original
factory and shared reflection/construction/lifetime bodies through this memory
lifecycle. Its integration metadata and concrete field operations are controlled.
The standalone memory suite above retains its declared whole-factory boundary.
