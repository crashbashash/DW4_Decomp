# Memory-reference values and actual Work instance lifetime

Recovery covers **32 complete bodies / 1,168 code bytes** in
[memory-field-values.c](../../recovered/engine/memory-field-values.c): the contiguous
seven-body memory value/lifetime run, generic scalar defaults/no-ops and the exact
metadata/trim/base hooks used by Work and its lists. All 32 bodies / 1,168 bytes
have matching source; add-reference 164 and release-reference 200 are `foreign-profile` in
`data/check-categories.tsv` (the code bytes are reproduced only under a provisional
per-function override) and the other 30 are `match`. Five new memory bodies add **788 exact bytes**: construction 200,
destruction 88, add-reference 164, release-reference 200 and default reset 136.
The two scalar default-copy bodies (24 each) match in `src/unmatched/igMetaField_SetToDefault.c`
and `src/unmatched/igMetaField_CopyDefaultToValue.c`.

## Memory-reference construction and default dispatch

The memory field value size is four bytes. Its word-default wrapper (`2fa9e0`)
preserves a temporary input cell and invokes current virtual slot 140 with that
cell's address. It is distinct from passing the word itself as the default pointer.

Construction (`2faa10`) does nothing when `_construct` is zero. Otherwise it asks
its element descriptor for low 16-bit value size and computes the original unsigned
rounded count `(memSize + size - 1) / size`. The portable adapter preserves 32-bit
wrap and EE divide-by-zero quotient behavior. A nonempty pool name uses named
allocator lookup, falling back to the enclosing object's allocator; missing/empty
names directly use that allocator. It calls the existing output-first array
allocator with field, object, element count and allocator. The isolated oracle
retains that boundary; `--array-storage` composes the subsequently recovered
[original allocator](array-storage.md), including reference-only zeroing and
status output, into all 113 checkpoints.

Generic scalar defaults (`2fc580` / `2fc5a0`) copy `_size` bytes from `_default` to
object plus `_offset`. Generic construction/destruction/zero/clear leaves and reset
method3's leaf are original no-ops; scalar `IsConstruct` returns zero. These are
preserved rather than replacing all field operations with blanket initialization.
The two default-copy wrappers execute their original tail delay slots before the
controlled byte-copy service.

## Reference walks and memory teardown

Add/release references first require the field's ref-counting flag, a non-null
element descriptor and a positive type-query result for object-reference metadata.
They then read the object's current buffer. A null buffer ends the walk. Otherwise
they capture allocator byte capacity divided by four and visit **all capacity
cells**, not the enclosing list's logical count. Null elements are skipped.

Retain increments the full reference word. Release decrements it and destroys an
element when the low 23 bits become zero. The buffer/count are captured for the
walk; callbacks do not expand its range. The code does not clear visited cells.
Type queries and object destruction remain bounded services in the isolated cases;
the actual instance composition below runs the recovered object destruction path.

Destruction (`2faae0`) requires the field's destruct flag, releases element
references, then re-reads offset and buffer before freeing through `2ed460`, even
for a null buffer. It re-reads offset again before clearing the pointer cell.
Callbacks can therefore change which cell is freed or cleared.

Reset (`2facc0`) releases current element references, optionally releases the
current allocation through `2ed5d0`, and reads the current default pointer cell.
A non-null default passes through `2ed530`; zero remains zero. The subsequently
recovered helper [duplicates raw storage](memory-field-copy.md); it does not retain
the default buffer itself. It publishes that
result through the current offset, then adds element references. It does not copy
raw bytes or assume an allocator/reference-header policy for those lower services.

## Real metadata to populated instances and final release

The oracle first executes the original base/Work/list metadata pipeline, including
inherited header descriptors and both `_data` specializations. It switches the
object system to its runtime state and invokes original generic instance creation.
The result is an actual Work object with an integer-list child and RAM-reference-list
child created through their real metadata and concrete reference fields.

Assertions check one owned reference per instance, zero scalar/string defaults,
empty child storage and one instance recorded in each concrete class metadata.
Original field loops begin after the actual two base header descriptors.

The test then assigns an interned string, appends integer values 7/9 and creates
two base objects. It appends those objects to the RAM list through original retaining
methods and releases their temporary caller ownership. Finally it transfers Work's
owned reference to a fixture holder and clears it through the real public object-list
release path. This runs original Work/child/base-object destruction, pre-teardown
list trimming, memory-element releases, concrete field destruction/clearing and
allocation release.

The final state proves Work, both children, both retained elements and replaced/
final list buffers are freed; all corresponding metadata instance counters return
to zero, the holder is null and the assigned string token has no remaining reference.
The holder alone is an ABI fixture; the instances and their metadata/field layouts
are produced through recovered original algorithms, not synthetic schema rows.

The default isolated fixture keeps array allocation and buffer services controlled.
`--array-storage` composes the [original array allocator](array-storage.md).
`--buffer-services` runs both original array and owner-directed buffer services
across all113 checkpoints, including actual default-buffer duplication, size queries
and free dispatch. The subsequent `--allocator-registry` mode uses original owner/index/wrapper
services and adds a runtime header-copy checkpoint (114 total). Allocator virtual
methods, scalar publication, type checks and byte operations remain controlled.
The later `--registry-bootstrap` mode runs original list creation/shutdown and
concrete46-record context lookup, adding two checkpoints (116 total); record
initialization, special context delegation and stack control remain bounded.
The later --context-lifecycle mode constructs and releases original context records
and46 retained bindings (210 checkpoints); the slot204 builder remains external. See [allocator contracts](allocator-registry.md). The beBaseInfoRam
gameplay schema and other unexecuted content paths remain open.
Native gameplay is unchanged.

## Verification

```sh
python3 testing/test_memory_field_values_retail.py
python3 testing/test_memory_field_values_retail.py --buffer-services
python3 testing/test_list_registration_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

**113 original-instruction RAM/defined-return/ordered-call checkpoints** cover all
32 bodies and populated instance lifetime. Isolated cases include ref flags/type/
null-buffer combinations, constructor name/fallback paths, free/offset mutation,
reference destruction, reset defaults and all supporting leaves. Instance tests
compose the original generic/public list methods and retained-reference/string
operations with the new memory value methods.

Twenty dependency regressions independently validate original memory-field virtual
roots and concrete list teardown/metadata hooks. Matching source uses observed
reference/default-pointer/virtual-slot ABI projections and reflected members; these
are not new original C++ type-name claims. Earlier compiler residuals and the
unconfirmed append return signature remain tracked separately.
