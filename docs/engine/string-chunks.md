# Packed pooled-string chunk allocator

The twelve allocation/chunk bodies surrounding the separately recovered header
release bridge have complete [behavioral C](../../recovered/engine/string-chunks.c).
They account for 1,272 code bytes. Seven matching bodies (376 bytes) are in
[matching C](../../src/engine/string-chunks.c) and
[matching C++](../../src/engine/string-chunks.cpp), including adjacent-block merge
and storage initialization. `StringChunk_AllocateToken` (`0x30c830`, 264 bytes) matches in
[StringChunk_AllocateToken.c](../../src/unmatched/StringChunk_AllocateToken.c). Four bodies (632 bytes) have no C
source yet: the table and chunk allocation wrappers (`0x30c740`, `0x30cce0`), TakeBlock
(`0x30ca40`) and ReturnBlock (`0x30cb80`). Names come
from [the semantic generator](../../scripts/seed_names_string_chunks.py), not
assertions about original C++ method spelling.

## Layout and packed free list

The 36-byte chunk stores table owner +0, next +4, previous +8, byte capacity +12,
storage base +16, storage end +20, free-list head +24, cached largest free size
+28, and empty byte +32. Initialization allocates storage through allocator
virtual slot +216, then represents the whole region as one free block. Construction
sets the cache to -1 (unknown) and the empty byte to one. Destruction releases
storage and optionally deletes the object when the signed low-16-bit deletion
flag is positive.

Free-list references point to block **ends**. At each end, two unsigned halfwords
store next-end distance at -4 and block length at -2, both in four-byte units.
Zero distance terminates the list. The reconstruction preserves 16-bit truncation,
word arithmetic and exact footer writes; it does not substitute a generic heap
or a new overflow policy. The matching merge uses a partial four-byte head-reference
view, not a guessed complete object layout.

TakeBlock scans in list order and takes the first sufficient region from its
front. A split reduces its footer length. Exact fit removes its footer from the
chain, updating the previous distance and/or head. Success invalidates the largest
size cache; failure publishes the largest observed free length in bytes.

ReturnBlock rounds byte size up to a four-byte unit, inserts its end into the
address-ordered chain and merges adjacent left and right regions. Merge updates
head and the preceding link, sums packed lengths and returns the resulting size.
Release raises a known largest-size cache when appropriate; an unknown cache
stays unknown. It sets empty only when the merged size equals the chunk capacity.

## Cross-chunk allocation and service boundaries

AllocateToken rounds payload storage to four bytes and adds the eight-byte
string header. It checks each chunk's cached maximum before searching, follows
the next chain, and creates a new chunk when needed. New capacity is the larger
of the request and the **starting chunk's** capacity. It publishes chunk/header
outputs in that order, clears the selected chunk's empty byte, and returns header
+8. The table/chunk allocation wrappers reorder size/allocator arguments and tail
jump through virtual slot +216. Delete wrappers forward through `0x2ed4b0` to the
underlying delete service; storage release forwards directly to `0x2ed460`.

The oracle mediates these service tail jumps after their original delay slots,
then returns through the real link register. It does not pretend those private
allocator targets contain fixture MIPS code or change the shared EE interpreter.
Allocator/delete are the remaining leaves for the standalone chunk comparisons.
Successful-allocation fixtures do not establish allocator failure/exception policy.

## Verification and current limits

`python3 testing/test_string_chunks_retail.py` passes **291 whole-function
RAM/return/ordered-call cases**, covering all twelve bodies, split/exact-fit/miss
searches, head/non-head links, every release order for four adjacent allocations,
both-sided coalescing, cache updates, storage initialization, deletion flags and
cross-chunk growth.

The pool suite passes **548 cases**, including ten successful
constructor/intern/cache-hit/release/destructor calls with actual chunk bodies
on both sides. Those routes retain only allocator/byte/synchronization leaves.
The upper-layer allocation-failure cases retain their explicitly controlled
chunk-constructor boundary. The messenger suite passes **1,196 cases**
with registered tokens in real packed storage and recovered chunk bodies on
normal routes. Eighteen of its calls cover persistent fresh allocation,
cached append and retained retrieval for six payload lengths, including requests
that exhaust and grow the starting chunk. The null-pool allocation-failure
case retains its controlled boundary rather than inventing lower failure behavior.

Merge is **68 matching code bytes**. Construction/destruction/deletion sources
match with their incoming arguments
explicit and a short deletion-flag cast. Root matching, typed and byte-identical
link gates remain required. Open: the four bodies without C source and allocator/delete/
synchronization contracts, then composing original producers and stage receivers
through this storage. This subgroup does not complete the allocator platform layer
or the full Lua-dependent engine recovery.

## Storage initializer byte match

`StringChunk_InitializeStorage` matches all **116 retail bytes**. The matching
C++ declaration supplies only the observed allocator vtable slot at +216 and
the recovered 36-byte chunk fields. Its 52 reserved method declarations are
slot padding, not original names or implementations; never instantiate this
view. Four-byte references remain integers. Host consumers use the separate
memory-accessor reconstruction rather than this target ABI view.

Keeping the footer-end pointer local preserves the observed single head load
and sequential packed writes. Typed fields also prevent an extra saved-register
address temporary. A class-size assertion protects the layout. Full matching/
typed/link gates retain byte identity; the 291 primitive cases and 1,196 composed
messenger cases pass.

The two virtual forwarding routines emit frames in C++
source and have no C source yet. A branch-sensitive, 60-second TakeBlock permuter
search reached a comparison score of 1,601 but produced no exact match;
`tools/verify.py` rejects the best result. Scores are not completion evidence.
The permuter driver honors `--outdir` in normal/pilot modes and defaults projects
to `build/permuter/`, keeping target objects/search
artifacts private. Four path regressions and a real build-only override smoke
check pass.

The [cold registry/interner composition](string-pool.md#cold-registry-interning-and-erase-byte-match)
adds 158 persistent checkpoints through real chunk storage, name lookup, typed
string channels and final-release coalescing/deletion in the messenger engine
chain. Concrete field/registrar/allocator/byte/sync services remain controlled.
