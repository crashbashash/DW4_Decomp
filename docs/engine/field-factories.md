# Concrete descriptor factories and initializer chains

Eighteen complete bodies / 1,752 code bytes are recovered in
[behavioral C](../../recovered/engine/field-factories.c). They cover the three
factory kinds referenced by Work's original field table, their constructor and
initializer chains, object header construction, raw allocation and the two concrete
post-construction default hooks. All eighteen bodies / 1,752 bytes match retail;
header initialization at `2fef20` (76 bytes) is `src/unmatched/igObject_InitHeader.c`.

Three new matches add **504 bytes**: `igMetaField_Init` (252),
`igObject_ConstructHeader` (140) and `igObject_AllocateRawStorage` (112).
Nine prior constructor/initializer matches are folded into
[field-descriptor-constructors.c](../../src/engine/field-descriptor-constructors.c)
with recovered receiver fields and explicit forwarded receivers. Three factories
and two default hooks are folded into
[field-descriptor-factories.cpp](../../src/engine/field-descriptor-factories.cpp).
Virtual classes there are ABI projections and must not be instantiated.

## Factory modes and original table

Work's six constructor-table entries at `4c5ce0` are, in order:

| Fields | Factory | Class |
| --- | --- | --- |
| group name, information name | `2b9750` | igStringMetaField |
| RAM number | `2c2cf0` | igIntMetaField |
| message | `2b9750` | igStringMetaField |
| RAM-number list, RAM-reference list | `2bce90` | igObjectRefMetaField |

When the object-system byte at `*586dc8` is nonzero, each factory runs its class
registration guard, re-reads the published class handle, and delegates to
`igMetaObject_CreateInstance(handle, allocator)`. This branch retains registration
and generic instance creation as lower dependencies in this module's oracle.

When that byte is zero, factories allocate 60 / 52 / 68 bytes respectively, with
zero prefix and the supplied allocator. They conditionally invoke their concrete
constructor with the original second argument 1, then unconditionally query the
result's current vtable and invoke slots 44 and 36 (the latter with argument zero).
The original assumes successful construction before those virtual calls; no new
null-success or allocation-failure behavior is introduced. The caller's physical
argument 1 is preserved; its original C++ meaning is not inferred here.

String and object-reference slot-44 hooks (`30a820` / `303350`) call the base
hook `2ff140`, then re-read the current vtable and invoke default setter slot 140
with null source. That base hook and the slot-36 base hook `2ff0e0` are original
no-ops, independently inspected with objdump.

## Constructor and initializer layers

| Class | Constructor | Initializer | Vtable |
| --- | --- | --- | --- |
| igObject header | `2ff010` | `2fef20` | `52f0f0` |
| igMetaField | `2fbf90` | `2fbfe0` | `52f230` |
| igRefMetaField | `305bf0` | `305c30` | `52ec50` |
| igIntMetaField | `2ea3e0` | `2ea420` | `532670` |
| igStringMetaField | `30b230` | `30b270` | `533180` |
| igObjectRefMetaField | `303bc0` | `303c10` | `532c80` |

Constructors run their ancestor constructor, stamp the current class vtable, then
conditionally invoke the class initializer. Initializers in turn run ancestor
initializers and stamp their own vtable. The repeated base initialization is
retail behavior, not replaced by a single synthesized initialization pass.

`2fef20` writes the base vtable, sets the low 23 reference bits to one while
preserving the upper bits, clears byte +6 bit 7, then clears allocator byte +7.
`2ff010` uses that initializer and, when the system is active, queries allocation
base and owner, storing the owner's virtual slot-364 result truncated to a byte,
or zero when no owner is found. Later initializer calls can clear that byte again;
this recovery does not invent a persistent ownership policy.

The base metadata initializer clears offsets, runtime flag, sizes, default pointer
and external publication handle, and sets type index to -1. It lazily constructs
the string pool if needed, interns null, then reads/releases the current field-name
token and publishes the interner result. Reading that member after the callback
matters: the decompiler initially hoisted it before the callback. It clears parent
and invariance pointers and the copy/reset/exact-comparison methods, sets deep
comparison method 1, shallow comparison method 2 and persistence 1. Padding and
unwritten bytes are preserved.

The reference initializer clears construct/destruct flags. Integer initialization
adds only its vtable. String initialization enables ref-counting and destruction
and sets shallow-copy method 2. Object-reference initialization clears pool name
and child metadata and enables ref-counting. Work's field adder subsequently sets
the two list child types and their construct flags through the original tables.

`30b270` was previously described as a constructor in string-field provenance.
It is the initializer called both by the actual constructor `30b230` and the
GetVTable temporary path. The vtable identity and existing lifecycle roots remain
valid; their wording and independent regression now identify the initializer.

## Raw allocation

`igObject_AllocateRawStorage` (`2ff790`) computes size plus prefix with 32-bit
wraparound. With no supplied allocator it queries the default allocator provider
using global `587018`. A non-null allocator dispatches slot 216 with the total
size and returns allocation plus prefix, even if the allocation result is zero.
If the provider also returns null, the libc allocation fallback receives the total
size and its result is returned **without adding the prefix**. Tests preserve this
branch distinction rather than imposing a uniform allocation policy.

## Verification and remaining boundaries

```sh
python3 testing/test_field_factories_retail.py
python3 testing/test_reflection_registration_retail.py --field-factories
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**276 original-instruction RAM/defined-return/ordered-call cases** cover all eighteen
bodies, bootstrap/runtime factory modes, registration-time handle changes, ancestor
initialization, reference flag preservation, allocator-owner code truncation,
default allocator/fallback selection, prefix arithmetic and allocation failures,
plus pool creation and callback-time field-name mutation/release.

The registration suite passes **487 composed cases** with the actual Work factories,
full constructor/initializer chain and post-construction defaults, together with
original storage wrappers. It asserts executed coverage of every new body and
checks actual final vtables, six allocated defaults, value sizes, persistence,
string flags, reference flags, names, offsets, reference counts, published handles
and Work child-type configuration. Three string descriptors, one integer descriptor
and two reference descriptors come from the original constructor table.

Allocator virtual methods, allocator table population, interning, type/size/alignment
queries, metadata factory/base registration, callback vectors and object-system
services remain controlled in that composition. Generic test-only descriptors in
other registration cases remain synthetic. This establishes the Work descriptor
construction path, not full original object-system bootstrap or live Work instance
creation. Memory/array fields, further class schemas and gameplay receivers remain
required.

The [base bootstrap recovery](object-base.md) extends the adapter/oracle with
`igUnsignedIntMetaField` factory/constructor/initializer (276 existing exact bytes).
The current factory oracle therefore covers 21 bodies / 2,028 bytes in 306 cases;
all 21 bodies / 2,028 bytes match. The original eighteen-body milestone above is unchanged.

The [memory descriptor extension](list-descriptor-copy.md) adds its factory,
constructor and initializer (340 existing exact bytes). The current factory
adapter/oracle covers 24 bodies / 2,368 bytes in 336 cases; all 24 bodies / 2,368 bytes
match.
