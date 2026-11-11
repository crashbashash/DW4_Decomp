# Memory-reference values and actual Work instance lifetime

This page covers **32 complete bodies / 1,168 code bytes**: the contiguous
seven-body memory value/lifetime run, generic scalar defaults/no-ops and the exact
metadata/trim/base hooks used by Work and its lists. Five memory bodies total 788 bytes: construction 200,
destruction 88, add-reference 164, release-reference 200 and default reset 136.
The two scalar default-copy bodies (24 each) are in the field class's run of the Core library unit,
[igMetaField_tail2.inc](../../src/engine/core/igMetaField_tail2.inc).

## Memory-reference construction and default dispatch

The memory field value size is four bytes. Its word-default wrapper (`2fa9e0`)
preserves a temporary input cell and invokes current virtual slot 140 with that
cell's address. It is distinct from passing the word itself as the default pointer.

Construction (`2faa10`) does nothing when `_construct` is zero. Otherwise it asks
its element descriptor for low 16-bit value size and computes the original unsigned
rounded count `(memSize + size - 1) / size`. The computation wraps at 32 bits and a
zero size takes the EE divide-by-zero quotient. A nonempty pool name uses named
allocator lookup, falling back to the enclosing object's allocator; missing/empty
names directly use that allocator. It calls the output-first
[array allocator](array-storage.md), including its reference-only zeroing and
status output, with field, object, element count and allocator.

Generic scalar defaults (`2fc580` / `2fc5a0`) copy `_size` bytes from `_default` to
object plus `_offset`. Generic construction/destruction/zero/clear leaves and reset
method3's leaf are original no-ops; scalar `IsConstruct` returns zero. These are
preserved rather than replacing all field operations with blanket initialization.
The two default-copy wrappers execute their tail delay slots before the
byte-copy service.

## Reference walks and memory teardown

Add/release references first require the field's ref-counting flag, a non-null
element descriptor and a positive type-query result for object-reference metadata.
They then read the object's current buffer. A null buffer ends the walk. Otherwise
they capture allocator byte capacity divided by four and visit **all capacity
cells**, not the enclosing list's logical count. Null elements are skipped.

Retain increments the full reference word. Release decrements it and destroys an
element when the low 23 bits become zero. The buffer/count are captured for the
walk; callbacks do not expand its range. The code does not clear visited cells.

Destruction (`2faae0`) requires the field's destruct flag, releases element
references, then re-reads offset and buffer before freeing through `2ed460`, even
for a null buffer. It re-reads offset again before clearing the pointer cell.
Callbacks can therefore change which cell is freed or cleared.

Reset (`2facc0`) releases current element references, optionally releases the
current allocation through `2ed5d0`, and reads the current default pointer cell.
A non-null default passes through `2ed530`; zero remains zero. That
helper [duplicates raw storage](memory-field-copy.md); it does not retain
the default buffer itself. It publishes that
result through the current offset, then adds element references. It does not copy
raw bytes or assume an allocator/reference-header policy for those lower services.

## Populated instances and final release

The base/Work/list metadata pipeline includes inherited header descriptors and both
`_data` specializations. Generic instance creation in the object system's runtime
state then produces an actual Work object with an integer-list child and a
RAM-reference-list child, created through their metadata and concrete reference fields.

A new instance holds one owned reference, zero scalar/string defaults and empty child
storage, with one instance recorded in each concrete class metadata. Field loops begin
after the two base header descriptors.

Elements appended to the RAM list are retained by the list's retaining methods. Final
release of Work's owned reference through the public object-list release path runs
Work/child/base-object destruction, pre-teardown list trimming, memory-element releases,
concrete field destruction/clearing and allocation release.

Afterwards Work, both children, all retained elements and replaced/final list buffers
are freed, all corresponding metadata instance counters are back to zero, the holder is
null and an assigned string token has no remaining reference.

The slot204 builder remains external; see [allocator contracts](allocator-registry.md).
The beBaseInfoRam gameplay schema and other unexecuted content paths remain open.

## Verification

```sh
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

Twenty dependency regressions independently validate original memory-field virtual
roots and concrete list teardown/metadata hooks. The source uses observed
reference/default-pointer/virtual-slot ABI projections and reflected members; these
are not new original C++ type-name claims. The append return signature is unconfirmed.
