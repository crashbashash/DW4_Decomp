# Messenger memory initialization and reset

The complete contiguous four-body group at `38bee0..38ca40` holds
initialization, two
temporary reference-owner destructors and reset, totaling 2,904 code bytes.
With the 28-byte `beMessenger::vfunc_26` reset forwarder,
that makes five bodies / 2,932 bytes. All five
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
that slot's store. One initialization therefore makes 101 direct factory calls: five
argument contexts (the current one and the four pool elements), 64 work records and
32 delay records.

Allocator choice is repeated for the initial context and for each pool element.
The function asks `301000` for the receiver's allocator, then uses the global
allocator service (`2f88e0` with global `587110`) when byte `554c14` is zero. A
factory callback changing that byte affects later allocations. Object factory
implementations remain separate dependencies.

Initialization clears nesting count (+36), then sets `_isMemoryAssign` (+48) to
one. It retains the registry/group list (+20) and freeze clock (+40). The function
itself is unconditional; its callers use the initialized flag when deciding
whether to invoke it. A null factory result is propagated by this
layer; the factories' failure/retry policy is not established.

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

## Verification and remaining work

Run from the repository root:

```sh
make check
make typed-check
make link
```

Transitive constructor/destructor ownership and
allocation failure policy remain open. Complete engine recovery is not
established by this subgroup. Next work includes actual
registry behaviour, lower services and concrete receivers.
[Object creation](object-creation.md) covers the
factory and shared reflection/construction/lifetime bodies.
