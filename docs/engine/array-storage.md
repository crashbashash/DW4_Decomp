# Array allocation and named alignment selection

Two complete bodies / 564 bytes. The 228-byte allocator
is in [array-allocation.cpp](../../src/engine/array-allocation.cpp); the adjacent
336-byte alignment selector is `src/unmatched/igMemoryRefMetaField_SetAlignmentType.c`.
These routines are storage services, with no element constructor loop.

## Aligned array allocation (`2fb190`)

The output-first arguments are status cell, memory field, enclosing object,
element count and allocator. The routine queries the element descriptor's virtual
size at slot100, truncates to 16 bits and multiplies by count with 32-bit wrap.
It reloads the descriptor and queries virtual alignment at slot108, also truncating
to 16 bits. Allocator slot220 receives the captured byte count and alignment.

On allocation failure, the output receives the word at `4fb418` and the object's
existing pointer is preserved. On success, the routine tests the current element
descriptor against the class handle at `585a60` (`igRefMetaField`). Only reference
field descendants trigger zero-fill. Other allocations retain their allocator
contents. The pointer is published through the field's current offset and the
output receives the current word at `4fb410`. The output is a status word, not
the allocated pointer. Both status words are zero in the pristine ELF; no status enum
values are inferred.

Descriptor, offset and status loads occur after callbacks where the original
instructions reload them. Size and multiplied byte count remain captured.
The source uses an unsigned byte-count local and unsigned multiplication;
virtual ABI projections describe observed slots and are not instantiable classes.
The constructor's declaration records the helper's void return.

## Named alignment selection (`2fb280`)

A null name sets `_alignmentType` at offset68 to -1. Otherwise the routine retains
the object list at `*(586dd0) + 44` and captures its signed count. Each iteration
reloads the retained list's data pointer, selects an entry and reads its name at
entry+8. A null entry name uses the **pointer stored at** `4c22f0`. A string match
publishes the row index. Missing names leave the previous alignment index intact.

Both match and miss paths release the captured list, even if a callback changes
the global publication. Retain/release update the full reference word; destruction
uses its low23 bits. The selected index is not itself the allocation alignment:
the allocator helper gets alignment from the element descriptor's virtual method.

## Remaining work

`testing/test_lua_engine_dependencies.py` checks original call/virtual-slot/class
and fallback-load evidence. The allocator is reachable through the
reviewed memory-construction root.

The subsequent [memory-copy/buffer checkpoint](memory-field-copy.md) recovers
copying, size and free dispatch. Allocator internals, owner registry search, type
queries/publication, object cloning and other gameplay receivers remain open.
