# Memory-field copying, buffer services and object visitation

This page covers **14 complete bodies / 1,668 code bytes**: the contiguous
four-body memory-field copy/print/visitor run (1,044 bytes), nine contiguous
buffer services (368 bytes), and the generic object visitor (256 bytes).
Deep copy436, print244 and field visitor212 are in
`src/engine/core/igMemoryRefMetaField_tail.inc`. The two
allocator tail dispatches are 28 bytes each (`2ed4c0`, `2ed5a0`).
Names in `config/SLUS-20836/names/MemoryBuffers.tsv` describe observed behavior; they do not
assert original C++ spelling. Slot240 remains address-named because its meaning
has not been established.

## Raw buffers are duplicated

The complete `2ed460..2ed608` helper family:

| Entry | Recovered operation |
| --- | --- |
| `2ed460` | `Memory_FreeBuffer`: skip null buffer, find owner, skip null owner, invoke owner slot264 |
| `2ed4b0`, `2ed5c0` | Original tail aliases of the guarded free |
| `2ed4c0` | Takes the buffer and allocator; tail-dispatches the allocator's slot264 with the buffer, without owner lookup |
| `2ed4e0` | Find owner and query its slot336 for buffer size |
| `2ed520` | Tail alias of owner search `2f04f0` |
| `2ed530` | Duplicate a buffer using its owner and size, then copy bytes |
| `2ed5a0` | Takes the buffer and allocator; tail-calls the allocator's slot240 with the buffer; return semantics remain unresolved |
| `2ed5d0` | Find owner and invoke slot264, without the guarded free's null checks |

`Memory_DuplicateBuffer` queries size, separately finds the owner, allocates through
`2ed1c0(size, owner)`, queries the original size **again after allocation**, then
calls the byte-copy service. It returns the new allocation. It does not retain or
share the original buffer and does not add an allocation-failure guard: a failed
allocation still reaches the copy call with a zero destination, which is not a claim
that such a failure is safe in the running game. The first size-query argument and
unchecked free's owner-query argument are explicit in the sources.

## Shallow and deep memory-field copy

Both copy forms share a prefix: release the destination's current element references, conditionally
free its old allocation when `_releaseOnCopy` is set, duplicate the current source
buffer if non-null, then publish through the field's current offset. Callbacks can
change the offset before later reads and publication.

Shallow copy (`2faf10`) then retains the copied element references through the
original add-reference helper. It shares elements, but its raw buffer is distinct.
Its 152-byte body is in
[igMemoryRefMetaField_tail.inc](../../src/engine/core/igMemoryRefMetaField_tail.inc).

Deep copy (`2fad50`) queries the current element descriptor. Object-reference
fields capture source/destination buffers, require both to be non-null, then clone
each non-null element through virtual slot84 with argument1. Memory-reference
fields duplicate each nested non-null buffer instead. Other element types keep
the raw byte copy. The nested-memory branch has **no additional null-buffer guard**.
Both loops capture their buffer pointers and capacity-derived count, then reload
individual cells as they proceed. Deep copy does not finish with the shallow
copy's add-reference walk. Clone implementations remain callbacks.

## Printing and callback traversal

Print (`2fafb0`) captures the buffer, emits `%s%s = 0x%x\n` through `304430` and
calls `304680`. A nonzero mode and non-null captured buffer enable further work:
query element slot104 for its full32-bit stride, divide capacity by that stride,
type-check the current descriptor and print non-null object-reference cells through
`300490`. This uses allocator capacity, not a logical list count. The loop compares
the quotient as signed32; a zero stride takes the EE zero-divisor quotient.
Debug output and per-object print implementations remain callbacks.

The routine named `igMemoryRefMetaField_ReleaseElements` (`2fb0b0`, slot168)
**does not decrement references**. It type-checks for object-reference metadata,
captures the buffer and capacity/4 count, then invokes each non-null object's
slot72. It reloads that cell afterward and calls the generic object visitor with
the supplied callback/context.

`igObject_VisitFields` (`300b00`) first invokes `callback(object, null, context)`.
Exactly1 suppresses traversal. Otherwise it calls object slot72, gets metadata via
slot88, captures its field-list/count and starts after the actual igObject base
header-field count. Each row reloads the field-list data pointer. The callback
receives object/field/context; exactly1 skips that field, while other results invoke
field slot168 with field/object/callback/context. The field receiver is captured
before the callback. Its 256-byte body is in
[igObject_tail2.inc](../../src/engine/core/igObject_tail2.inc).

## Remaining boundaries

Eighteen dependency tests verify original slots144/152/164/168,
duplicate-buffer calls, type handles and prior roots.

The intrinsic-discard interpretation does not hold; the historical symbol alone does not establish
that behavior.

In `apply_names.py`, explicit alias names win over target-derived thunk names, and
reference rewriting visits both halves of same-basename C/C++ pairs.
`python3 testing/test_apply_names.py` covers both cases in an isolated naming batch.
Existing string delete wrappers keep their exact alias targets.

The [allocator registry](allocator-registry.md) covers
owner traversal and encoding plus complete allocation wrappers. Registry bootstrap,
allocator virtual implementations/slot240, object cloning,
per-object print, scalar/type publication and broader gameplay remain open.
