# Pooled strings and the ordered token table

Four public pool bodies, the complete ten-body ordered-table run at
`0x30c0c0..0x30c73c`, and the string-header release bridge at `0x30c940`
have readable [behavioral C](../../recovered/engine/string-pool.c).
These fifteen bodies account for 2,228 code bytes. Four matches
(pool/table destruction, table erase and header release, 384 bytes) are folded in
[matching source](../../src/engine/string-pool.c). The other eleven (1,844 bytes)
match in one-function files under `src/unmatched/`.

The combat unwind table also identifies the complete 116-byte
[deleting string-wrapper cleanup](../../src/engine/StringRef_Destruct_00130720.c):
it preserves both owner and header arguments to the final-release bridge.
See [cleanup identities](../systems/combat-reference-helpers.md).

## Pool and token ownership

The 16-byte public pool stores table +0, chunk-chain head +4, default block
size +8 (16,384), and allocator +12. Construction selects the allocator through
the existing global mode/fallback path, allocates a 24-byte table with initial
capacity 1,024, and a 36-byte first chunk. Allocation failure branches are retained;
this is not a new host failure-recovery policy. Pool destruction walks chunks,
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
the existing matching header. RemoveHeader assumes membership; it does not
add a missing-header check before erase. Tests use valid internal removal
requests rather than changing this retail contract.

Find/Register/RemoveHeader/empty-chunk notification acquire/release optional
global synchronization at `0x5871c8`, re-reading it at the observed points.
SetSynchronization lazily creates/publishes it or clears/releases it with the
low-23-bit object destruction rule. Synchronization primitives remain leaves;
these instruction comparisons do not establish concurrency behavior.

Empty-chunk notification initially increments the cleanup counter without deleting
the chunk. With a positive counter it unlinks the head or a later chunk and calls
its destructor. Header release removes the token from the table, measures payload
length plus nine bytes, releases storage, then consults chunk byte +32 to decide
whether to notify the table. RemoveHeader's retaining search occurs before
erasure, so that count write is preserved even during final release.

## Verification and remaining work

`python3 testing/test_string_pool_retail.py` passes **548 whole-function cases**.
538 cover all fifteen bodies, returns, every runtime RAM byte and meaningful
callee arguments/order. Cases include ordered misses/hits, count/step/growth,
duplicate registration, persistent intern/hit/release, synchronization enabled/
disabled, allocator fallback/failure branches, signed deletion flags and cleanup.
Allocator/chunk/byte/synchronization services remain explicit leaves.
The other ten are successful lifecycle calls through actual chunk
allocation/free/coalescing ([chunk recovery](string-chunks.md)); the failure
cases keep their upper-layer controlled chunk boundary.

The messenger oracle runs original versus recovered construction, interning,
search/registration/removal and header release alongside real list and matrix
bodies. All **1,178 cases** pass. Its allocation test model takes the
chunk/header output order from the original allocator stores. Nested pool scratch is distinct from live
caller/list temporaries. Fixture byte services reject unbounded movements
instead of hanging on malformed test state.

The matching destruction/release sources declare their incoming
arguments explicitly. Short casts preserve the deletion tests without signed
shift expressions; original bytes match. Names come from [the generator](../../scripts/seed_names_string_pool.py)
and decoded roles, without asserting original C++ spelling.

Open: chunk composition through all messenger routes, allocator/
metadata and synchronization dependencies, then actual messenger receiver/result
production. These subgroups do not complete the string allocator, list library
or full Lua-dependent engine recovery.

## Cold registry interning and erase byte match

The composed cold-messenger chain extends through actual pool, table,
chunk and string-result bodies. The
[registry/interner oracle](../../testing/test_messenger_interned_registry_retail.py)
passes **158 persistent original-instruction RAM/defined-return/ordered-call
checkpoints** across both allocator-selection modes and optional synchronization.
All initial owned names are seeded through the original interning bodies rather
than arbitrary raw pointers. The initial record name triggers actual lazy pool,
table and chunk construction.

The suite then executes real factory/memory/registry/object/generic-list,
selection/dispatch, queue/expiry and context-nesting bodies. Group names of
1/15/16,375/16,385 bytes exercise cached lookup, exact-size and oversized additional
chunks. String append/retrieval runs through real typed string-channel bodies;
assertions prove byte equality, pointer identity with the registered group name,
positive header count and membership in the ordered table. Registry grows to
five groups before reset, and at least three chunk objects are constructed.

Two actual SetName/final-release cycles for a separate 20,000-byte name exercise
table erasure, free-list coalescing, empty notification, reuse and deletion of an
empty non-head chunk. Assertions prove unchanged table count afterward and that
the original chunk deletion tail reached its delete leaf. Tail mediation executes
each original delay slot before supplying allocator/delete results. Reset and
reinitialization remain part of each persistent run.

Concrete field/registrar, allocator/free, byte/string comparison/length and
synchronization primitives remain controlled. Remaining field-cleanup leaves mean
this test does not claim that resetting messenger objects releases every concrete
owned name. It proves the original interning/storage path through the tested
engine operations; it does not establish hardware concurrency or native gameplay.
The standalone oracles retain their explicitly documented service boundaries.

`StringTable_EraseAt` matches **104 code bytes** in
[string-pool.c](../../src/engine/string-pool.c). A 24-byte target ABI view exposes
the recovered count, search step and pointer-array fields; a size assertion
protects its layout. The matching C projection retains an unspecified-parameter
byte-move declaration. The observed call still supplies destination, source and
byte count; this is not a claim about the original SDK prototype. A typed
three-parameter declaration emits an extra temporary and does not match.
No forced instruction padding or binary patching is used.

All fifteen bodies in this family match (2,228 bytes). Root matching, typed coverage and relink are validated
separately from these behavioral comparisons. Run:

```sh
python3 testing/test_messenger_interned_registry_retail.py
python3 testing/test_string_pool_retail.py
python3 testing/test_string_chunks_retail.py
python3 testing/test_messenger_results_retail.py
make check
make link
make typed-check
```
