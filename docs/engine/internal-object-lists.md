# Internal pointer lists and retained ownership

Finding [#882](../findings/findings-0751-1000.md#f882) records **22 complete bodies / 2,324 code bytes** in
[behavioral C](../../recovered/engine/internal-object-lists.c): the full contiguous
raw/retaining list run `2ea4f0..2eade8` and factory `2c2670`. All 22 bodies /
2,324 bytes have matching source (lookup follow-up [#886](../findings/findings-0751-1000.md#f886)). Seven new matches add **884 bytes**: copy 160,
slack clearing 104, insertion 188, erase 84, append 136, retained destruction 48
and retained resize 164. Growth 232 and pointer-index lookup 68 match in
`src/unmatched/ObjectPointerList_EnsureIndex.cpp` and `src/unmatched/ObjectPointerList_FindIndex.c`; the corrected string-field
lookup adds 160 exact bytes in follow-up [#886](../findings/findings-0751-1000.md#f886). The shared pointer-index behavioral implementation
remains in the prior metadata recovery; no independent duplicate is introduced.

`ObjectPointerList` names describe recovered roles and a 16-byte ABI projection,
not a claim of an original C++ type name. The retained class is independently
identified as reflection class `__internalObjectList`, handle `5860d0`, vtable
`5327d0`. Its raw ancestor stamps `532770`. Both use buffer +8 / signed count +12,
with allocator byte capacity queried externally; there is no capacity member.
These differ from the public reflected `igObjectList`/`igMetaFieldList` layouts.

## Construction, copying and destruction

The internal factory switches between class registration/CreateInstance and raw
16-byte construction according to the object-system byte. It re-reads the class
handle after registration. The cold path preserves physical constructor argument
1, then invokes current virtual slots 44 and 36. Both slots are base no-ops here.
Allocation/construction success remains an original lower-service assumption.

The raw constructor (`2ea4f0`, 96) runs object header construction, stamps its
vtable, invokes the raw initializer, then selects its allocator and requests a
16-byte data buffer through slot 216. The initializer (`2ea550`, 60) resets header,
vtable, buffer and count. Constructor allocation does not explicitly initialize
the four pointer cells. The retained constructor/initializer (`2eab70` / `2eabb0`,
52 each) delegate and stamp the retained vtable.

Raw copy (`2ea590`, 160) delegates header copy, captures the source count and,
for a non-null source buffer, allocates exactly count times four bytes and copies
that captured byte count. It re-reads the source buffer after allocator callbacks.
A null source buffer produces a null destination buffer. A self-copy can overwrite
its own source buffer before the copy call; no alias-preserving replacement policy
is added. The retained copy wrapper (`2eabf0`, 52) only stamps its vtable afterward;
it does **not** independently retain the copied items. The wider original copy
protocol remains a separate dependency.

Raw destruction (`2ea630`, 84) frees a non-null captured buffer through the current
object allocator's slot 264, then calls base object destruction. It does not clear
the pointer member. Retained destruction (`2eac30`, 48) first resizes to zero using
the retaining operation, then delegates to raw destruction. This destructor is
independently backed by retained vtable byte slot 8.

## Capacity, mutation and lookup

`ObjectPointerList_EnsureIndex` (`2ea690`, 232) bypasses work only when the signed
requested index is strictly below capacity. Capacity is the low 32 bits of the
buffer's allocator byte size shifted right two, or zero for a null buffer. On the
growth path it re-reads buffer and capacity again. A zero capacity starts at four;
while index is not below capacity, capacity doubles below 512 slots and adds 512
at or above that threshold. It calls object storage slot-232 dispatch (`300e50`),
publishes its result, then zeroes only the newly allocated tail beyond the captured
old physical capacity. It does not zero existing inactive cells or update count.

`ClearUnused` (`2ea870`, 104) is a separate operation: it starts at a captured
count, re-queries current capacity on every iteration and zeroes current buffer
cells up to capacity. Callback changes to the buffer affect subsequent stores.

| Operation | Entry | Behavior |
| --- | --- | --- |
| Insert | `2ea8e0` | Ensure room using captured count; re-read count/buffer, shift right, store and increment count |
| Append | `2eaa60` | Ensure room using captured count; re-read count/buffer, store and increment count |
| Set count | `2ea9a0` | Ensure requested count as an index, then publish count; no release or clearing |
| Set cell | `2eaaf0` | Ensure requested index, then write it; count is unchanged |
| Erase | `2eaa00` | Reject index >= count, shift left, decrement count and return index; otherwise -1 |
| Find pointer index | `2ea820` | Captured buffer/count, first equal pointer or -1; signed nonpositive counts stop immediately |
| Find by string field | `2ea780` | Read each object's string member selected by a field descriptor and return the current matching object pointer, or zero |

These methods do not introduce lower-bound checks. Negative erase indexes can
mutate storage before the buffer; such instruction behavior is tested without
presenting it as a valid high-level caller contract. Erase does not clear the
vacated last cell. String-field lookup re-reads count each iteration and re-reads
the selected object pointer after the comparison callback. The prior offset-list
interpretation is refuted ([#885](../findings/findings-0751-1000.md#f885)); see [corrected selector evidence](metadata-callback-services.md).

## Retained operations

Retaining insert (`2eac60`, 28) and append (`2ead30`, 28) increment a non-null item's
full reference word before delegating. Retaining resize (`2eac80`, 164) captures
the original count and releases removed items in reverse order. It re-reads the
buffer for each item, decrements the full reference word and destroys the item
when its low 23 bits become zero. It then delegates count assignment. Callback
changes to count do not expand the captured release range. Growing does not add
retains to existing cells.

Retaining replacement (`2ead50`, 152) retains the new item, reads/releases the old
cell, then delegates raw set-cell. The old cell is read before any capacity growth.
An alias retain/release balances without destruction; an old-item destructor can
move the list buffer before the final store. This is the final list body before
the adjacent string-pool constructor, and is included in the module recovery.

## Verification and remaining boundaries

```sh
python3 testing/test_internal_object_lists_retail.py
python3 testing/test_reflection_registration_retail.py --internal-lists
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**379 original-instruction RAM/defined-return/ordered-call cases** cover all 22
bodies: factory modes, header/storage composition, copy/self-copy, growth thresholds,
strict boundary indexes, slot mutation, negative/empty searches, reference aliases,
reverse release, buffer/count changes during capacity/zero/compare/destruction
callbacks and a persistent factory/append/growth/shrink/destruction sequence. That
sequence leaves six externally owned items at their original counts and proves
both the replaced and final data buffers were freed.

**487 registration cases** now compose the actual field-list factory, constructors,
allocator dispatch, retaining append, growth, reallocation and zeroing under original
Work metadata/descriptors. Executed-entry assertions cover the reached list paths
and storage reallocation helper. The six fields force the fixture's initial four
slots to grow to eight, preserve the retained vtable and free the replaced buffer.
Existing schema, defaults, name, registry index and ownership assertions remain.

Allocator virtual methods/capacity queries, byte operations, destruction callbacks,
class/type queries and other bootstrap services remain controlled. The allocator
fixture reports explicit requested sizes; this does not infer retail allocator
rounding. Base/other class metadata remain synthetic where previously documented.
Full instance composition, concrete memory/array fields and gameplay receivers
remain required. Native gameplay is unchanged.

**Append return hypothesis ([#883](../findings/findings-0751-1000.md#f883)):** a matching `int` implementation returns the
old count left physically in `v0`. The direct call sites examined do not explicitly consume that value (two lead
straight to an epilog); no consuming caller establishes the original public return signature. Matching
source labels this as a compiler/ABI candidate. Behavioral oracles deliberately
exclude append and retaining wrappers from defined-return comparisons; the public
return type remains unconfirmed.
