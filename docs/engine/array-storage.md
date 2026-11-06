# Array allocation and named alignment selection

Two complete bodies / 564 bytes are recovered in
[array-storage.c](../../recovered/engine/array-storage.c). The 228-byte allocator
has byte-identical matching source in
[array-allocation.cpp](../../src/engine/array-allocation.cpp). The adjacent
336-byte alignment selector has no C source yet: its readable recovery passes the
retail behavioral oracle, but the private compiler candidate still differs.
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
the allocated pointer. Both status words are zero in the pristine ELF; the oracle
seeds distinct values to verify the branch and publication order without inferring
unproved status enum values.

Descriptor, offset and status loads occur after callbacks where the original
instructions reload them. Size and multiplied byte count remain captured.
The matching source uses an unsigned byte-count local and unsigned multiplication;
virtual ABI projections describe observed slots and are not instantiable classes.
The constructor's declaration now records the helper's void return.

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

## Verification and remaining work

`python3 testing/test_array_storage_retail.py` compares **151** original-instruction
RAM and ordered-call checkpoints. It covers reference/nonreference storage,
allocation failure, zero count, low16 truncation, multiply wrap, callback-time
descriptor/offset/status changes, aliased output, null/missing/fallback names,
empty/negative captured counts, changing count/data/global publication, and
retained-list final destruction with packed reference flags. The test overlays
writes onto ELF-backed data so changed status words and fallback pointers are
actually observed by both executions.

`python3 testing/test_memory_field_values_retail.py --array-storage` passes the
existing **113** checkpoints with original array instructions composed into memory
construction and populated Work/integer-list/RAM-list creation and teardown. The
portable path uses recovered allocation behavior instead of its former controlled
helper. Integer allocations start with nonzero allocator bytes; reference storage
is zeroed by the recovered helper. The isolated mode remains separately runnable.
Seventeen dependency tests independently check original call/virtual-slot/class
and fallback-load evidence. The allocator is already reachable through the
reviewed memory-construction root; this checkpoint adds no speculative roots.

The subsequent [memory-copy/buffer checkpoint](memory-field-copy.md) recovers
copying, size and free dispatch. Allocator internals, owner registry search, type
queries/publication, object cloning and other gameplay receivers remain open. This is evidence for these
storage contracts, not native gameplay completion.
