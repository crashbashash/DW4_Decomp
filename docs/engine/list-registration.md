# Original inherited list metadata registration

**32 complete bodies / 2,092 code bytes** cover metadata
allocation/readiness, publication callbacks, vtable access, initializer forwarding,
registrar tuples, the three inherited schema callbacks and default element selectors.
[Portable behavior](../../recovered/engine/list-registration.c) composes with the
original metadata, descriptor-copy and callback-array implementations. The two
specialization bodies delegate to their existing recovery rather than duplicate it.

All 32 bodies / 2,092 bytes have matching source. Two reviewed parent getters
add **24 newly classified and matched bytes**. The four vtable getters of 60 bytes,
the RAM-list allocation getter 68 and ready getter 76 match in per-function files
under `src/unmatched/`. Existing matched registrar/public-accessor wrappers now explicitly return
the callback state or metadata pointer consumed by their callers.

The two twelve-byte parent accessors were previously data gaps. The recovery script
checks exact words, registrar literals, contiguous extents and lack of overlap,
then regenerates analysed Ghidra function/symbol snapshots without analysis. See
[the reproducible script](../../scripts/recover_list_parent_callbacks.py). Classified
code and function count increase 24 bytes/two functions; retail bytes are unchanged.

## Four list classes and inherited schemas

| Class | Published handle | Registrar | Vtable | Parent |
| --- | --- | --- | --- | --- |
| igDataList | `586788` | `2c8580` | `5309b0` | igObject |
| igObjectList | `585b60` | `2bd7b0` | `5249b0` | igDataList |
| igIntList | `586880` | `2caba0` | `531b70` | igDataList |
| beBaseInfoRamList | `589d20` | `36a1a0` | `534890` | igObjectList |

All four registrars preserve their original eleven-argument tuples, size 20, callback
addresses and feature-initialization calls. The RAM-list registrar has no own field
adder and appends its original dependency table at `4c7b98`; the beBaseInfoRam
registration callback reached from it remains a controlled gameplay/type boundary.

`igDataList_InitFields` (`2c8600`, 160) captures the inherited count, creates three
fields from constructor table `4c1380` and selects the third. It supplies the
unsigned-byte element descriptor to that memory-reference field, enables its
destruct/release-on-copy/release-on-reset flags, then binds the original names,
publication handles and offsets through `4c1390/4c13a0/4c13b0`.

The resulting runtime schema has five fields: two original igObject header fields,
then `_count` +8, `_capacity` +12 and `_data` +16. The parent schema is built by
original code; it is not substituted with rows from the static table export.
The object and integer specializers then clone/replace only inherited `_data`
through the already recovered original copy chain. The RAM list inherits the
object-list clone without making another descriptor.

## Allocation-only, ready and published metadata access

Each class has an allocation-only getter used by construction/reflection paths.
It queries allocator key `587040`, calls the actual metadata factory and publishes
a missing object, then re-reads the global handle. It does not register fields or
set validity 4. Work's reference descriptors use these getters, so their initial
child handles can exist before the deferred child-registration callbacks execute.

The ready getters check both pointer presence and validity bit 4; if either is
missing they invoke the class's original initializer wrapper and re-read the
published handle. Existing pure forwarding/publication accessors preserve the
same distinct behavior. The two parent-publication leaves at `143720` and
`130c00` simply read data-list and object-list metadata respectively, without
allocation or registration.

Vtable getters initialize the original temporary object header, stamp their own
table and read through object-system offset 916. The adapter reserves 320 scratch
bytes for the temporary and shared registration operations. Tests compare the
defined result, not incidental temporary stack contents.

## Default element descriptor instances

The providers at `2b7660`, `2bd2e0` and `2c3090` read cached **field descriptor
instances**, not class metadata. Their publication slots are `585768`, `585b28`
and `586100`; a missing cache calls the corresponding scalar-class initializer
wrapper, then re-reads the slot.

These are the default `igUnsignedCharMetaField`, `igObjectRefMetaField` and
`igIntMetaField` descriptor instances. In particular, the raw data-list element
selector is unsigned char, not the separate `igCharMetaField` class. The independent
class record for handle `585760` and the provider's original load establish this.
The scalar publication/class-initialization bodies remain controlled in this
checkpoint; fixtures supply descriptor ABI views with their observed tables,
value sizes and ownership.

## Verification and integration

```sh
python3 testing/test_list_registration_retail.py
python3 testing/test_list_descriptor_copy_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**48 original-instruction RAM/defined-return/ordered-call checkpoints** cover all
32 bodies, allocation-only reuse, ready/cached registration, vtable-offset access,
published aliases, default-selector cache hits/misses and the complete original
Work deferred-registration path. The fixture allocator supplies unique metadata,
descriptor, list, default and callback allocations, avoiding synthetic metadata
rows or shared allocation addresses.

The end-to-end path proves six valid metadata objects: base object, Work, data
list, object list, integer list and RAM list. Work has eight fields, each list has
five and size 20, with the real inherited names and offsets. The raw/object/integer
`_data` descriptors are distinct, have distinct default buffers, select the correct
scalar descriptor instances and preserve the parent field. The RAM list shares
the object-list descriptor. Final descriptor counts are 1/2/1 for raw/object/integer
storage; their shared name has three references. Work's two child-type pointers
match the registered integer/RAM metadata. Repeated Work initialization performs
no further allocation.

Fifteen independent dependency regressions verify reviewed getter words/extents,
registrar callback arguments and unsigned-byte selector identity. These extend
explicit roots without inventing edges through generic dispatch.

Remaining boundaries include scalar singleton publication and wider type-system
initialization, type-query services, feature initialization, allocator/owner/byte
services, the parent child-list factory and beBaseInfoRam's gameplay schema. Actual
Work/list instance construction and complete teardown, memory/array value methods
and other Lua-dependent gameplay receivers remain active work. Native gameplay
is unchanged.

The [memory-value follow-up](memory-field-values.md) now connects this metadata
to actual Work and child-list instances, populates strings/integers/retained
references and executes original final release. Array allocation and wider
allocator/type/publication services remain controlled.
