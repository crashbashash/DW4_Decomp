# Reflection creation and messenger factories

Twenty complete bodies (2,616 code bytes) cover messenger factory/registration
forwarding, the contiguous three-body instance-creation group, static initializer
callbacks, the contiguous three-body construction/registration group, and the
contiguous five-body destruction/field-pass group.

Sizes include the eight factory/registration
wrappers (336), default creation (48), instance registration (180), the
static initializer runner (120), full object destruction (268) and
field zeroing `2ff930` (200). Sources are one-function files under `src/unmatched/`,
[beMessengerFactories.cpp](../../src/game/beMessengerFactories.cpp),
[igMetaObjectCreation.cpp](../../src/engine/igMetaObjectCreation.cpp), and the
the [instance registration source](../../src/unmatched/igObject_RegisterInstance.cpp).
Explicit allocator/return signatures preserve the retail bytes.

## Factory and creation behavior

| Class | Create | Ensure registration | Metadata handle |
| --- | --- | --- | --- |
| `beMessengerWork` | `358070` | `3581d0` | `588f88` |
| `beMessengerGroup` | `3584e0` | `358620` | `588fc8` |
| `beMessengerDelay` | `358950` | `358a90` | `588ff0` |
| `beMessengerArgData` | `358d80` | `358fa0` | `589038` |

Each factory saves its allocator, runs its registration wrapper, reloads the
metadata handle and returns `igMetaObject_CreateInstance(handle, allocator)`.
The original return register carries the new object, so the factories explicitly return
that reference. Registration wrappers dispatch the corresponding original class
registrar through `igMetaObject_RunStaticInit` (`2fe940`).

The static initializer runner calls its registrar, then, for a non-null returned
table, captures count +4 and calls entries from the table's buffer +0 in order.
It re-reads the buffer each iteration while retaining the captured count, and
finally calls table cleanup (`2d3420`, deletion flag 1). The source uses
a structural callback-table view, not an original recovered type name. Its
callbacks are declared without parameters; the byte-identical loop physically
leaves the table pointer in a0. Original callback declaration spelling remains open.

The contiguous allocation group is default creation (`2fda10`), ordinary creation
(`2fda40`) and creation for a pool (`2fdb40`). Default creation asks the global
allocator provider and forwards its result. Ordinary creation follows a replacement
metadata getter at +60 recursively when present, rejects abstract-state byte +26
only when exactly 1, and chooses an allocator when none was supplied. A nonempty
allocator name at +96 goes through the named lookup; a missing result falls back
to the default allocator.

Allocation invokes allocator vtable byte slot 216 with metadata prefix size +32
plus instance size +72. The object reference is the returned allocation plus the
prefix size, using original word arithmetic. It constructs that resulting reference
when nonzero. This is the original test on the adjusted reference; there is
no separate allocation-failure check. Creation for a pool first requires
metadata flag bit 4 at +36, then follows the same allocation selection and calls
the shorter pooled construction body. Replacement metadata follows the same
entry-specific checks recursively.

## Construction, field passes and registration

Full construction (`2ff1d0`) writes the metadata vtable (+92) at the runtime object
vtable offset (`[586dc8] + 916`), initializes the reference header at object +4,
sets the low 23-bit reference count to one and clears byte +6's high bit. It
queries allocation ownership through `300d30` / `2f04f0` and stores zero, or the
owner's virtual byte-slot-364 result, in header byte +7.

It then runs field zeroing, value construction, and default reset for fields whose
construct flag is false. Finally it invokes object virtual slots 44 and 36 (the
latter with zero), obtains metadata through slot 88, increments instance count
+44, and appends to tracking list +48 when present. Every virtual operation reloads
the object's current vtable, preserving callback-driven changes.

Pooled construction (`2ff2f0`) preserves the pre-existing upper reference-header
bits, sets the low count to one and performs the ownership-byte and field-zeroing
steps. It omits full value construction/defaulting and instance registration.
`igObject_RegisterInstance` (`2ff3a0`) separately handles that later phase: optional
virtual slot 80 when supplied metadata has a replacement getter, slots 12/52 with
zero, slot 36 with one, and instance count/tracking-list publication.

All field passes skip the base-field prefix counted by metadata at global
`587198`. Each pass captures the current type's field count and base count;
iteration re-reads the field-pointer buffer before each callback.

| Body | Operation |
| --- | --- |
| `2ff930` | Call field slot 132 (zero storage), subject to metadata bit 4 and the original system-byte conditions |
| `2ffa00` | Call field slot 124 (construct value), then object slot 12 with one |
| `2ffab0` | Call `igMetaField_Reset` for every non-base field, then object slot 52 with one |
| `2ffb50` | Call field slot 240 (construct flag), reset fields returning zero, then object slot 52 with one |

The zeroing condition is retained literally: run when metadata is non-null and
has flag bit 4, or system byte +20 is zero, or system byte +0 is nonzero.
Other paths retain original assumptions about valid metadata/system references.
See [reflection metadata](reflection-metadata.md) for field layouts and
`config/SLUS-20836/names/ObjectModel.tsv` for established MetaField slot roles. Semantic
labels describe these verified operations, not original C++ spelling.

## Destruction

`igObject_Destroy` (`2ff820`) does nothing when global system reference `586dc8`
is null. With system byte +0 zero it calls object slots 40, 48 and 8, then frees
the object reference. With that byte nonzero it obtains metadata, decrements its
instance count, removes an optional tracking-list entry, calls slots 72/40/48,
runs the original remaining cleanup helpers (`2ffc10`, `2ffcb0`), resolves the
allocation through `300d30`, and frees that allocation. Metadata/list helpers and
those cleanup bodies remain explicit dependencies. Slot dispatch reloads the
vtable after each callback.

The [matching destruction source](../../src/engine/igObject_Destroy.cpp) now
reproduces all67 instruction words and9 relocations. It uses a single C++
dispatch view with numbered virtual slots (an ABI projection, not an original
class declaration) and reflected `_instanceCount`44 / `_instances`48 fields.
The count decrement preserves the original wrapped word. One explicit four-byte
`dmove object,input` captures the receiver after reading the system mode;
plain assignment hoists the copy into the null-system branch's delay slot and
changes two words. CW's `dmove` emits the original64-bit DADDU and carries copy
dataflow; `move` emits32-bit ADDU, while generic `daddu` also changes call setup.
No original-source spelling or all-C++ claim is made: this matching body contains
one explicit register-copy instruction and C++ lifecycle logic.

## Validation and remaining work

Run from the repository root:

```sh
make check
make typed-check
make link
```

The original class registrars, exact field-descriptor tables and transitive concrete
field ownership are not established here. Recovering those bodies is still required.
Full Lua-dependent engine recovery remains open.

[Object lists](object-lists.md) cover the registry and object/generic list operations
reached through this creation path. [Object fields](object-fields.md) cover the
remaining cleanup passes and concrete object-reference field operations; original
class descriptors remain open.
