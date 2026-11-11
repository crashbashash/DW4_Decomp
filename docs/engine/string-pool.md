# Pooled strings and the ordered token table

Four public pool bodies, the complete ten-body ordered-table run at
`0x30c0c0..0x30c73c`, and the string-header release bridge at `0x30c940`
form this family. These fifteen bodies account for 2,228 code bytes. Four bodies
(pool/table destruction, table erase and header release, 384 bytes) and the other eleven
(1,844 bytes) are in two whole files: the pool in [StringPool.cpp](../../src/engine/StringPool.cpp)
and the table and its chunks in [StringTable.cpp](../../src/engine/StringTable.cpp).

The combat unwind table also identifies the complete 116-byte
[deleting string-wrapper cleanup](../../src/engine/StringRef_Destruct_00130720.c):
it preserves both owner and header arguments to the final-release bridge.
See [cleanup identities](../systems/combat-reference-helpers.md).

## Pool and token ownership

The 16-byte public pool stores table +0, chunk-chain head +4, default block
size +8 (16,384), and allocator +12. Construction selects the allocator through
the existing global mode/fallback path, allocates a 24-byte table with initial
capacity 1,024, and a 36-byte first chunk. The body has allocation-failure branches.
Pool destruction walks chunks,
captures next before each destructor, destroys the table and optionally deletes
the pool when its signed low-16-bit deletion flag is positive.

Interning null returns zero without lookup or allocation. Nonnull input first
uses retaining lookup. A miss measures length plus terminator, allocates chunk
storage, copies bytes and registers the new header. The allocator's first output
(a2) is the chunk pointer; its second (a3) is the string header. Token is header
+8; header +0 stores chunk owner and +4 the full 32-bit reference count,
initially one. Existing-token lookup increments this count in the search body.

## Ordered table and synchronization

The table is an ordered header-pointer array, not a hash map. Fields are pool
owner +0, count +4, search step +8, capacity +12, array +16 and cleanup counter
+20. Construction obtains the array through allocator virtual slot +216.
Search halves its stored step, compares input bytes with candidate header +8,
retains a match and publishes token/index outputs. A miss publishes insertion
position but leaves the token output untouched; Find initializes it to zero.

Insert doubles a full array's capacity, moves the suffix, stores the header,
increments count and advances search step at power-of-two boundaries. Erase
decrements count, moves the suffix and halves step when count falls below it.
Register initializes owner/reference fields and searches for placement; it
ignores the found flag, so duplicate text still inserts a header and retains
the existing matching header. RemoveHeader assumes membership; it has no
missing-header check before erase.

Find/Register/RemoveHeader/empty-chunk notification acquire/release optional
global synchronization at `0x5871c8`, re-reading it at the observed points.
SetSynchronization lazily creates/publishes it or clears/releases it with the
low-23-bit object destruction rule. Concurrency behavior is not established.

Empty-chunk notification initially increments the cleanup counter without deleting
the chunk. With a positive counter it unlinks the head or a later chunk and calls
its destructor. Header release removes the token from the table, measures payload
length plus nine bytes, releases storage, then consults chunk byte +32 to decide
whether to notify the table. RemoveHeader's retaining search occurs before
erasure, so that count write is preserved even during final release.

## Source conventions

The destruction/release sources declare their incoming
arguments explicitly. Short casts preserve the deletion tests without signed
shift expressions. Names come from [the generator](../../scripts/seed_names_string_pool.py)
and decoded roles, without asserting original C++ spelling.

## Cold registry interning and erase

The cold messenger chain runs through the pool, table, chunk and string-result
bodies, using the factory/memory/registry/object/generic-list,
selection/dispatch, queue/expiry and context-nesting bodies above them. All initial
owned names go through the original interning bodies, and the initial record name
triggers the lazy pool, table and chunk construction.

Group names reach cached lookup, exact-size or oversized additional chunks
according to their length. String append/retrieval through the typed string
channels returns text byte-equal to, and pointer-identical with, the registered
group name, with a positive header count and membership in the ordered table.

SetName/final release of a separate 20,000-byte name goes through table erasure,
free-list coalescing, empty notification, reuse and deletion of an empty non-head
chunk. The table count is unchanged afterward and the chunk deletion tail reaches
its delete service.

Concrete field/registrar, allocator/free, byte/string comparison/length and
synchronization primitives are separate services. Whether resetting messenger
objects releases every concrete owned name is not established, nor is hardware
concurrency.

`StringTable_EraseAt` is **104 code bytes**, in
[StringTable.cpp](../../src/engine/StringTable.cpp). A 24-byte target ABI view exposes
the recovered count, search step and pointer-array fields; a size assertion
protects its layout. The matching C projection retains an unspecified-parameter
byte-move declaration. The observed call still supplies destination, source and
byte count; this is not a claim about the original SDK prototype. A typed
three-parameter declaration emits an extra temporary and does not match.
No forced instruction padding or binary patching is used.

All fifteen bodies in this family match (2,228 bytes). Validate matching, typed coverage and relink with:

```sh
make check
make link
make typed-check
```
