# Alias-pool method run and allocation backend

Finding [#902](../findings/findings-0751-1000.md#f902) extends the [factory/binding checkpoint](alias-pool-binding.md)
through the complete contiguous method run **2d0560..2d163c**. Together with
factory2cd170, this is **54 bodies /4,160 bytes**. All have readable behavioral
recovery and original-instruction comparisons. This does not mean all54 are
byte-matched: **44 bodies /1,508 bytes** have matching source; **ten bodies /
2,652 bytes** retain assembly. The [#903](../findings/findings-0751-1000.md#f903) follow-up adds seven exact virtual tails
/160 bytes using per-unit exceptions-off settings; see
[compiler evidence](compiler-object-verification.md). Teardown108 adds **108 matched bytes** here.
The eight newly classified bodies add980 bytes to the code denominator, not
matched progress. Parent allocators, metadata, synchronization and file services
remain explicit dependencies; no native gameplay integration is claimed.

This run excludes the earlier reflection/registration block at2cd210..2cd5b8
and inherited implementations outside the run. Those remain separate dependency
modules;54 runtime bodies must not be read as complete reflection/allocator closure.

## Reviewed function boundaries

The following starts were absent from Ghidra's function table. Their raw
vtable5313a0 bindings and complete instruction extents establish the boundaries:

| Entry | Bytes | Raw slot | Behavior |
| --- | ---: | ---: | --- |
| 2d0ae0 |32|220| Allocate with explicit alignment through412 |
| 2d0b00 |104|224| Wrapped count×size, allocate at default alignment, zero on success |
| 2d0c00 |16|236| Pass reallocation arguments through412 |
| 2d0c10 |188|260| Forward block operation and report change in backing allocation |
| 2d0d80 |24|264| Free through412 using the full64-bit -1 sentinel |
| 2d0da0 |140|340| Allocation ownership query |
| 2d0e30 |20|336| Delegate allocation-size query to backing pool |
| 2d0e50 |456|348| Print aliased-pool statistics |

[`RecoverAliasPoolFunctions.java`](../../scripts/RecoverAliasPoolFunctions.java)
checks the retail vtable and entry instruction, rejects overlaps/different
existing extents, then creates only these reviewed functions. Run it against
the existing analyzed project with `-noanalysis`, dump through
`scripts/dump_functions.py`, and refresh with `sh scripts/sync_data.sh` and
`python3 tools/split.py --symbols`. The normal name-overlay workflow applies
the generated slot names and body/reflection-derived names. The private export
recipe and objdump are in `../scratch/lua-engine-recovery/alias-backend-*`.

The classified code total becomes3,374,876 bytes /19,292 functions. The retail
image bytes are unchanged. This corrects classification of980 previously unclaimed
bytes; it is not recovery credit for the new functions.

## Lock ownership, construction and teardown

The mode byte at raw136 controls the retained `_allocationLock` at+116. Mode0
retains a local reference, releases the stored reference, clears the slot, invokes
lock132(1) then lock96, and releases the temporary. Mode1 returns immediately if
already present; otherwise it obtains the object's allocator, creates through
2ba650, invokes lock92, retains the result, releases the current slot, publishes
and releases the temporary. Other byte modes only publish the current success
word. Initialization callback mutation of the slot is honored before replacement.
Statuses returned by the lock methods are not interpreted.

Lock2d0a10 invokes retained lock132(1); unlock2d0a50 invokes124. Both use
output-first temporary status cells. UnlockAndReturn2d0a80 preserves the supplied
result across unlock. These helpers compose with actual wrapper/backend bodies;
the lock implementation and OS concurrency remain controlled boundaries.

Initialize1500, Construct1540 and CopyConstruct1590 invoke their respective base
helper, publish5313a0 and clear lock116, tracker152 and alias180. Construct also
invokes Initialize on a non-null receiver. Base construction remains controlled;
this does not prove complete cloning or metadata/default initialization.

Teardown15d0 releases the alias reference without clearing180, invokes current
receiver392, then base teardown2f0030. The [exact teardown](../../src/engine/alias-pool-destruction.cpp)
uses the low23-bit reference lifetime and genuine C++ virtual dispatch. Parent392
must still be recovered to establish its own lock/tracker cleanup; this test does
not supply an invented complete close implementation.

## Allocation backend412

The backend at2d1210 locks before reading minimum alignment176. It compares the
low16 requested alignment with that minimum; when no replacement is needed, the
original argument bits remain. Free is selected by comparison with the **full
64-bit -1**, not just a low32-bit -1 value.

For ordinary allocation/reallocation, admission compares unsigned64-bit
`currentBytes + signExtend32(size)` against maxSize144, with wrapped arithmetic.
A failing admission calls receiver92(size,1); nonzero repeats admission and zero
returns null after unlock. The callback may change the limit. No new retry cap,
overflow guard or allocation-failure rollback is added.

Allocation delegates to backing220. Reallocation first subtracts the old size,
increments frees and returns ownership to the backing allocator, then calls236.
Those earlier accounting and ownership changes survive a failed reallocation.
With a null backing pool, allocation/reallocation simply leave the result null.
Free of null unlocks and returns zero. Non-null free subtracts the queried old
size, increments frees, transfers ownership, and calls backing264; the original
requires a valid backing pool on that path.

Successful allocation/reallocation adds signExtend32(size), updates unsigned64-bit
byte high-water160, increments the wrapped allocation count136, and updates
signed32-bit live-count high-water168 from allocations minus frees. The body does
not introduce an `_isActive` guard around these changes. Incoming ownership is
assigned to this proxy; outgoing ownership is assigned to the backing pool.
Reassignable113 selects backing372; otherwise original helpers2f0220/2f0320 run.
Backing pointers and flags are re-read at their original callback boundaries.

Default/explicit alignment, element-size allocation, calloc and reallocation/free
wrappers compose with412. Count×size wraps to signed32 before forwarding. Calloc
zeroing is conditional on both successful allocation and nonzero wrapped size.

## Other controller behavior

The getter/setter block preserves64-bit max/current/high values, word pool index
and element size, and halfword alignment, including output-first status writes.
The event tracker setter retains before release, including same-object assignment.

Ownership340 either compares the captured proxy index against backing380, or
uses2f0180's status and owner outputs. It re-reads the current success word after
that callback. The block-operation wrapper260 samples backing192 before and after
backing260 and, when `_updateStatistics`104 is nonzero, forwards a signed32-bit
delta through receiver200. It returns the captured block-operation result.
Forwarders248/252 publish failure without backing and otherwise preserve the
output-first callback;256 is a conditional void forwarder.

Statistics printing captures counts before its virtual queries, resolves the
backing name through two396 calls when present, truncates the relevant64-bit
statistics to signed32 argument words, and preserves all12 variadic log arguments.
Optional labels and final output retain their separate flush calls. Method344
is the original unsupported `dump()` notice: it optionally creates/opens a file,
writes the notice and closes/releases it, or prints directly without a filename.
Failure to open unlocks before releasing the file. It does not dump tracker data.

## Verification and remaining matching work

```sh
python3 testing/test_alias_pool_runtime_retail.py
python3 testing/test_alias_pool_binding_retail.py
python3 testing/test_allocator_builder_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

The runtime suite executes **286 RAM/return/ordered-call cases**, covering every
one of the **1,040 instructions** in the54 bodies. It exercises fresh construction
through actual factory/constructor/initializer calls, persistent lock/allocate/
reallocate/free/teardown, wrapped64-bit admission and32-bit counters, growth retries,
null/failure paths, ownership mutation, lock replacement/destruction, signed
statistics deltas, all12 logger arguments, output-first statuses and file failures.
The shared interpreter's virtual tail transfers execute the original delay slot.
Its backing allocator, base constructors, actual locks, file/print and ownership
services remain controlled leaves. Complete-body instruction coverage does not
establish complete game-state, hardware-threading or native gameplay coverage.

Ten bodies /2,652 bytes remain compiler residuals. The private typed backend
candidate has the original740-byte size and is down to eight differing words
(six temporary-result offsets and two retry/scheduling words); it is not banked as matching C. The lock
and diagnostic bodies also retain assembly; the seven simple virtual tails are
now exact ([#903](../findings/findings-0751-1000.md#f903)). No assembly
patches or fixed instruction encodings are inserted into C to count a match.

Active resume: finish exact matching of the contiguous alias module, starting
with backend740 and lock484; then close the parent allocator/ownership services
needed by the [full hub recovery contract](../systems/hub-recovery.md). Keep hub
SD receiver, service-menu, portal/progression and save closure visible alongside
this shared engine work. Native port acceptance remains separate.
