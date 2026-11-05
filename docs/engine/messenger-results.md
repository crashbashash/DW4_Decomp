# Messenger result and argument channels

The complete contiguous 32-body block at `0x0038f0e0..0x0038f94c`
(2,032 code bytes) exposes `beMessenger`'s typed result/argument channels.
All bodies have readable [behavioral C](../../recovered/engine/messenger-results.c).
Twenty have matching C/C++ in [beMessengerResults.c](../../src/game/beMessengerResults.c)
and [beMessengerResults.cpp](../../src/game/beMessengerResults.cpp); twelve retain
retail assembly pending compiler recovery. Finding [#862](../findings/findings-0751-1000.md#f862) records this boundary.

Receiver selection and actual message routing have a separate complete
[behavioral recovery](messenger-dispatch.md); receiver virtual implementations
remain dependencies.

## Receiver, channels and signatures

Reflection identifies `beMessenger._argData` at +16 and its
`beMessengerArgData` fields. The original accesses independently agree:

| ArgData offset | Field | Element width / representation |
| --- | --- | --- |
| +8 | `_isRunCheck` | One byte, stored without normalizing truth |
| +16 | `_boolList` | One byte per result |
| +20 | `_intList` | Four-byte signed word |
| +24 | `_floatList` | Four-byte float bit pattern |
| +28 | `_longList` | Eight-byte integer |
| +32 | `_vec3fList` | Twelve-byte three-float value |
| +36 | `_matrix44fList` | Sixty-four-byte matrix |
| +40 | `_objectList` | Four-byte retained object reference |
| +44 | `_stringList` | Four-byte pooled string token |

Each channel list has count +8, capacity +12 and buffer reference +16.
The [name generator](../../scripts/seed_names_messenger_results.py) derives all
32 semantic names from those fields and verified operations. The names describe
recovered behavior; they do not assert original C++ method spelling.

Float append (`0x38f350`) receives the messenger in a0 and its float in f12.
Float get (`0x38f3d0`) returns in f0. Treating those values as integer registers
is wrong even though the decompiler initially proposed integer types. Vector
and matrix retrieval (`0x38f560/0x38f630`) use output in a0, messenger in a1,
index in a2; original aggregate-return spelling remains unresolved. Object append
(`0x38f670`) preserves incoming a1, omitted by the initial decompiler draft.

## Complete block behavior

Scalar/vector/matrix count getters expose their list count. Byte and integer
channels additionally have guarded setters and count-only clears. Vector clear
also clears only its count. Byte resize ignores a negative signed index/count,
stores a nonnegative count directly when capacity suffices, or calls list growth
with element width one. Append operations grow if count reaches capacity,
retain the old index, then reload the buffer before storing. Relocated-buffer
fixtures verify that the stale pre-growth buffer is not used.

Bytes preserve their low eight bits; integer stores preserve their low 32 bits;
longs preserve all 64 bits. Float stores/gets and vector copies preserve their
bit patterns without arithmetic. Matrix operations use the original matrix-copy
boundary `0x1908f0`. Direct getters have no bounds checks. Guarded byte/int setters
require a nonzero count and `0 <= index < count`. Signed parameters in the oracle
use the EE ABI's sign-extended word representation; arbitrary noncanonical upper
register bits are outside those typed signatures.

Object append delegates to the retaining object-list append. Object clear
releases every retained element using the low-23-bit object-reference destruction
rule, then reloads count and zeroes slots before clearing it. String append
accepts null tokens, otherwise lazily creates the shared pool at `0x586f20`,
interns the input, appends a copied temporary reference and releases that
temporary. Allocation failure still reaches interning with a null pool; this
reference preserves retail's behavior rather than adding a host failure policy.
String get copies an indexed temporary, releases it and returns the borrowed
token. String destruction tests the full string-header count, unlike the
low-23-bit object rule; its free call carries both allocator and header address.

## Verification and remaining dependencies

The deeper packed-storage checkpoint now passes **1,196 cases**. Prepared string
tokens are registered in their pool table and backed by an allocated block plus
the real end-footer free list. Normal string routes execute original versus
recovered chunk construction, allocation, split/coalescing and release. Persistent
fresh/cached/retrieval cases include growth beyond the starting block. One existing
upper-layer null-pool failure case keeps its controlled chunk boundary; allocator
failure/exception behavior remains unverified. The original 1,178-case matrix is
retained within this broader set. No production gameplay change is claimed.

`python3 testing/test_messenger_results_retail.py` passes **1,178 cases covering
every one of the 32 entry bodies**, comparing scalar/FPU return registers,
every runtime RAM byte and meaningful service-call arguments/order. Compiler
stack storage is excluded. Counts/capacities cover empty/full/growth and 8/9/17
boundaries, null/non-null references, noncanonical byte values, 64-bit payloads,
negative indices, relocated buffers, pooled-token references and allocation failure.
List growth/append/reference-copy now execute the [recovered list services](list-services.md)
against original instructions. Their metadata/allocation/byte services and
pool/table bodies now execute the [recovered string services](string-pool.md).
Their allocator/chunk/byte/synchronization dependencies remain controlled;
matrix copying executes the
[recovered primitive](matrix-primitives.md) against original instructions.
This does not establish complete SD dispatch
or native scene behavior.

Recovered float get, matrix get and object append add **104 matched code bytes**.
Both C++ wrappers require the original frame-preserving language mode. The other
seventeen source bodies were already matched; naming/folding preserves their
bytes. Full root matching checks, typed baseline and byte-identical relink are
required after the module fold. Compiler candidates and original Ghidra/objdump
exports are private under repository-relative `../scratch/lua-engine-recovery/`.

Next finish the twelve compiler residuals and recover the list metadata/allocator,
string pool and remaining matrix compiler bodies. Then integrate actual messenger selection and player result
production, so material update can consume these channels without controlled
matrix/selector results. The [Lua dependency inventory](lua-dependencies.md)
retains the wider receiver/virtual/update frontiers; this module does not close
the full Lua-dependent engine recovery goal.
