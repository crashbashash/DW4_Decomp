# Scalar string fields, ownership and raw value encoding

Twenty-one complete bodies (2,548 code bytes) make up this family: the contiguous eighteen-body
scalar string-value run at `30a910..30b230`, its retained-slot helper (`1c8c00`),
and common reset/write dispatchers (`2fc500`, `2fc6f0`). Some shared methods retain
canonical derived `igStringArrayMetaField::vfunc_*` names; this recovery establishes
their scalar-value behavior, not complete string-array behavior.

Source is in
[string-field-values.c](../../src/engine/string-field-values.c),
[string-field-dispatch.cpp](../../src/engine/string-field-dispatch.cpp) and
one-function files under `src/unmatched/`, including raw encode (`30add0`,
184 bytes). Generic reset is 124 bytes, the three equality methods 288 and raw
decode (`30ab20`) 676. The 72-byte write dispatcher explicitly receives/forwards all
five physical arguments.

## Runtime field identity and value methods

`igStringMetaField_GetVTable` (`2b98c0`) constructs a temporary through `30b270`.
That initializer stores vtable `533180`, sets `_refCounted` (+56) and `_destruct`
(+53) to one, and selects shallow-copy method two. Raw vtable slots establish the
value operations below. The GetVTable path is more involved than the simple
constant patterns represented by the existing generated vtable snapshot; the
initializer and raw table are checked directly by the dependency regression.

| Address | Recovered operation |
| --- | --- |
| `1c8c00` | Assign a retained token from a source pointer cell into the instance member |
| `30a910` | Intern text from an input pointer cell and assign the resulting token |
| `30a9d0` | Output-first retained pointer copy: output a0, descriptor a1, source cell a2 |
| `30aa00` | Return value storage size four |
| `30aa10` | Intern text and replace the token in the descriptor's default cell |
| `30aab0` | Return persistent encoded size, including length word and padded text |
| `30ab20` | Decode a raw length/text record into a token cell |
| `30add0` | Encode a token cell into a raw length/text record |
| `30ae90`, `30aea0` | No-op value/hook entries |
| `30aeb0` | Re-intern the descriptor's default token text and assign it |
| `30af80`, `30aff0` | Retained value copies between instance members |
| `30b060` | Null-aware signed lexical comparison |
| `30b0b0` | No-op value construction |
| `30b0c0` | Destruct by assigning null when `_destruct` is nonzero |
| `30b110`, `30b170`, `30b1d0` | Pointer-fast-path, null-aware text equality |

Reflection identifies `_offset` +8, `_default` +32, `_persistent` +38,
`_construct` +52, `_destruct` +53 and `_refCounted` +56. Default storage is a
valid pointer cell; a null default value is distinct from a missing default cell.
The string value constructor is a no-op. Default assignment is a separate operation
selected by the generic object's field-reset path.

## Token ownership and callback-sensitive publication

The retained-slot helper computes the destination once, retains the incoming
non-null token, releases the previous token, then **re-reads the source cell**
for publication. It always performs token reference updates; it does not gate
this algorithm on descriptor ownership flags. Destination is captured before
release, unlike the concrete object-reference setter's re-read member offset.
A release callback changing `_offset` does not move this store; changing the
source pointer cell can change its published value. Token counts are full 32-bit
header words, with owner at token -8 and count at token -4.

Text assignment and default reset hold an interned temporary token, invoke that
helper and release the temporary afterward. Null input to these two wrappers
skips interning. Default-cell replacement and raw decoding instead call the
interner even for null input, preserving lazy pool setup and service order.
Value copies retain their source token before assignment and balance their
temporary after assignment. Aliasing source/destination preserves these increments
and decrements. Destruction checks `_destruct`, assigns null through the real
helper and leaves a zero member; later generic clear need not release it again.

Comparisons return zero for two nulls, negative/positive for null/non-null order,
and the original string comparator result otherwise. Equality first accepts
identical pointers (including null), rejects unequal null/non-null pairs, then
compares bytes. Shared equality bodies need explicit Boolean
normalization; the equivalent direct-zero-comparison draft emits different
instructions. No instruction padding or byte patches are used.

## Raw encoding and common dispatch

Encoded strings begin with a four-byte payload-size word. A null token writes
zero and returns four bytes, without invoking the swap hook. A non-null token
writes `align4(strlen + 1)`, optionally swaps that one length word, copies its
terminated text and returns payload size plus four. Padding after the terminator
is not zeroed. A non-null empty string occupies eight bytes, unlike null's four.
The size method returns zero only when field persistence is zero; otherwise it
reports the corresponding null/non-null encoded size.

The reader copies and optionally swaps length into a local cell. Signed lengths
below one clear the output through actual null interning and return four.
Positive lengths scan only their declared span for a terminator. An embedded
terminator permits direct interning of the input text. Otherwise the reader
allocates length+1 (allocator slot +216), copies exactly the declared bytes, adds a
terminator, interns, and frees the temporary (slot +264). Allocator selection is repeated before free, so an
interner callback can change the global mode/provider used for that free. It
returns the original positive declared length plus four, without adding another
alignment policy. Allocation failure and invalid lengths follow the lower services'
contracts; there is no bounds check or retry here.

The common reset dispatcher selects virtual slots 112/116/120 for reset-method
values 0/3/2 respectively; other values do nothing. The common persistent-value
writer rejects a zero persistence byte, adds field offset to the enclosing object,
forwards output/context/full swap arguments to field slot 200, and rounds the
returned byte count to four. Its restored five-argument matching signature removes
the prior draft's omitted output/context/swap parameters.

## Validation and remaining work

Run from the repository root:

```sh
python3 testing/test_lua_engine_dependencies.py
make check
make typed-check
make link
```

Final release clears the instance while retaining the descriptor's one default
reference; clearing that default returns the pool table to zero. Original messenger
registrar/descriptor construction remains open.

Five reviewed lifecycle roots are backed by constructor/raw-vtable evidence and
messenger Work/ArgData string descriptor types. Retail class-descriptor recovery
is still required. Original string/memory descriptor setup,
other memory fields and concrete gameplay receivers remain
part of the full Lua-dependent engine goal.
