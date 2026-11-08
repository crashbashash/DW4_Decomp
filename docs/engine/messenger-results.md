# Messenger result and argument channels

The complete contiguous 32-body block at `0x0038f0e0..0x0038f94c`
(2,032 code bytes) exposes `beMessenger`'s typed result/argument channels.
Twenty bodies are in [beMessengerResults.c](../../src/game/beMessengerResults.c)
and [beMessengerResults.cpp](../../src/game/beMessengerResults.cpp); the other twelve
are in [beMessengerArgs.cpp](../../src/game/beMessengerArgs.cpp) (seven) and in one-function files
under `src/unmatched/` (five).

Receiver selection and actual message routing are covered in
[receiver dispatch](messenger-dispatch.md); receiver virtual implementations
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
retain the old index, then reload the buffer before storing, so the stale
pre-growth buffer is not used.

Bytes preserve their low eight bits; integer stores preserve their low 32 bits;
longs preserve all 64 bits. Float stores/gets and vector copies preserve their
bit patterns without arithmetic. Matrix operations use the original matrix-copy
boundary `0x1908f0`. Direct getters have no bounds checks. Guarded byte/int setters
require a nonzero count and `0 <= index < count`. Signed parameters
use the EE ABI's sign-extended word representation; arbitrary noncanonical upper
register bits are outside those typed signatures.

Object append delegates to the retaining object-list append. Object clear
releases every retained element using the low-23-bit object-reference destruction
rule, then reloads count and zeroes slots before clearing it. String append
accepts null tokens, otherwise lazily creates the shared pool at `0x586f20`,
interns the input, appends a copied temporary reference and releases that
temporary. Allocation failure still reaches interning with a null pool.
String get copies an indexed temporary, releases it and returns the borrowed
token. String destruction tests the full string-header count, unlike the
low-23-bit object rule; its free call carries both allocator and header address.

## Remaining dependencies

List growth/append/reference-copy are described in [list services](list-services.md), pool
and table bodies in [string services](string-pool.md) and matrix copying in
[matrix primitives](matrix-primitives.md). Allocator failure/exception behavior remains
unverified, and complete SD dispatch is not established by this block.

Both C++ wrappers require the original frame-preserving language mode.

Material update consumes these channels once actual messenger selection and player result
production are integrated. The [Lua dependency inventory](lua-dependencies.md)
retains the wider receiver/virtual/update frontiers; this module does not close
the full Lua-dependent engine recovery goal.
