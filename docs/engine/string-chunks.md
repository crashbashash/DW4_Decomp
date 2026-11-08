# Packed pooled-string chunk allocator

The twelve allocation/chunk bodies surrounding the separately recovered header
release bridge account for 1,272 code bytes. Seven bodies (376 bytes) are in
[string-chunks.c](../../src/engine/string-chunks.c) and
[string-chunks.cpp](../../src/engine/string-chunks.cpp), including adjacent-block merge
and storage initialization. `StringChunk_AllocateToken` (`0x30c830`, 264 bytes) is in
[StringChunk_AllocateToken.c](../../src/unmatched/StringChunk_AllocateToken.c) and TakeBlock
(`0x30ca40`, 236 bytes) in
[StringChunk_TakeBlock.c](../../src/unmatched/StringChunk_TakeBlock.c). The other three bodies (396 bytes)
are the table and chunk allocation wrappers (`0x30c740`, `0x30cce0`)
and ReturnBlock (`0x30cb80`). Names come
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
Zero distance terminates the list. Arithmetic truncates to 16 bits and counts in
words, with exact footer writes; there is no overflow policy.
The matching merge uses a partial four-byte head-reference
view, not a guessed complete object layout.

TakeBlock scans in list order and takes the first sufficient region from its
front. A split reduces its footer length. Exact fit removes its footer from the
chain, updating the previous distance and/or head. Success invalidates the largest
size cache; failure publishes the largest observed free length in bytes.

ReturnBlock takes the block address and byte size, rounds the size up to
four-byte units and computes the block's end. With an empty list, or an end below
the head, that end becomes the new head. Otherwise it walks the address-ordered
chain to the first footer at or above the end, remembering the previous two
footers. It writes the new footer's length and its distance to the next footer
(zero when last), then points the previous footer's distance at it. If the previous
footer sits exactly at the block's start, it merges left and the footer before that
becomes the predecessor. If the next block starts exactly at the end, it merges
right. Merge updates head and the preceding link, sums packed lengths and returns
the resulting size. Release raises a known largest-size cache only when that cache
is below the resulting size; an unknown (negative) cache stays unknown. It sets
empty only when the resulting size equals the chunk capacity.

## Cross-chunk allocation and service boundaries

AllocateToken rounds payload storage to four bytes and adds the eight-byte
string header. It checks each chunk's cached maximum before searching, follows
the next chain, and creates a new chunk when needed. New capacity is the larger
of the request and the **starting chunk's** capacity. It publishes chunk/header
outputs in that order, clears the selected chunk's empty byte, and returns header
+8. The table/chunk allocation wrappers reorder size/allocator arguments and tail
jump through virtual slot +216. Delete wrappers forward through `0x2ed4b0` to the
underlying delete service; storage release forwards directly to `0x2ed460`.

## Current limits

Merge is **68 code bytes**. Construction/destruction/deletion sources
keep their incoming arguments
explicit and use a short deletion-flag cast. Open: allocator/delete/
synchronization contracts, then composing original producers and stage receivers
through this storage. This subgroup does not complete the allocator platform layer
or the full Lua-dependent engine recovery.

## Storage initializer

`StringChunk_InitializeStorage` is **116 bytes**. Its
C++ declaration supplies only the observed allocator vtable slot at +216 and
the recovered 36-byte chunk fields. Its 52 reserved method declarations are
slot padding, not original names or implementations; never instantiate this
view. Four-byte references remain integers.

Keeping the footer-end pointer local preserves the observed single head load
and sequential packed writes. Typed fields also prevent an extra saved-register
address temporary. A class-size assertion protects the layout.

The two virtual forwarding routines emit frames in C++
source.
The permuter driver honors `--outdir` in normal/pilot modes and defaults projects
to `build/permuter/`, keeping target objects/search
artifacts private. Four path regressions and a real build-only override smoke
check pass.

The [cold registry/interner path](string-pool.md#cold-registry-interning-and-erase)
reaches this storage through name lookup, typed string channels and final-release
coalescing/deletion in the messenger engine chain.
