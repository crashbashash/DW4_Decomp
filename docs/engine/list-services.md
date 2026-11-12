# Shared list growth, mutation, search and reference bridges

The twelve-body shared primitive run at `0x2d6670..0x2d6e60` (1,956 code bytes)
and four retained-reference bridges (584 bytes) are covered here.
Two bodies are in [list-services.inc](../../src/engine/core/list-services.inc) and [list-services_tail.inc](../../src/engine/core/list-services_tail.inc) of the Core library unit, and the
string-list bridge is in [list-services.inc](../../src/engine/scenegraph/list-services.inc) of the SceneGraph library unit;
the eight-byte -1 default keeps its generic name. The other bodies are in the unit's list runs. The two range insertions are
`List_InsertBytes` (`0x2d6810`, 232 bytes) and `List_InsertWords`
(`0x2d6b80`, 220 bytes).

## Primitive contracts

Every list exposes signed count at +8, signed capacity at +12 and a four-byte
buffer reference at +16. The [semantic name generator](../../scripts/seed_names_list_services.py)
names verified operations without asserting original method spelling or a
particular owning C++ specialization. The shared `0x2d6670` default returns -1;
its role remains unresolved and it is deliberately not given a guessed role name.

| Address | Operation |
| --- | --- |
| `0x2d6680` | Reserve capacity with descriptor-driven buffer allocation |
| `0x2d6790` | Grow/reserve and publish requested count |
| `0x2d6810` / `0x2d6900` | Insert / append a byte range with caller-supplied element stride |
| `0x2d69a0` | Remove one element with caller-supplied stride |
| `0x2d6a20` | Comparator-driven binary search with caller-supplied stride |
| `0x2d6b20` | Append one four-byte word without retaining it |
| `0x2d6b80` / `0x2d6c60` | Insert / append a four-byte word range |
| `0x2d6cf0` / `0x2d6d70` | Remove / binary-search four-byte words |
| `0x1c64e0` | Copy an indexed string token to an output and retain it |
| `0x1ca620` | Grow string list and append a retained input cell |
| `0x301e30` | Retain an object before appending its reference |
| `0x30cdf0` | Grow/zero or shrink/release string-list cells |

Reserve zero frees the old buffer, nulls its reference and publishes capacity
zero without changing count. A nonzero reserve gets metadata through the list's
virtual slot +88, looks up a signed field tag from `0x5867a0`, invokes the
descriptor's unit getter at virtual slot +100, masks that result to 16 bits and
requests `(capacity * stride) / unit` allocation units. Arithmetic wraps as EE
words. The allocation helper publishes the new data reference. Old storage is
copied for `min(old_capacity, new_capacity) * stride` bytes, including cells
beyond logical count, then freed. Count is not changed by reserve.

Resize starts at `max(current_capacity, 4)`, doubles below 1,024 and adds 1,024
at or above that threshold until capacity reaches the requested count. It calls
reserve even when capacity already suffices, then publishes count. It supplies
no negative-count guard of its own; callers establish their respective admission
rules. Overflow/nontermination behavior is not replaced with a host clamp.

Range insertion (`0x2d6810`) takes the list, index, range length, input pointer and
element stride; `0x2d6b80` takes the same first four with the stride fixed at four. Both do
nothing unless the index is between zero and the current count inclusive and the length is
positive. The new count is the old count plus the length: above capacity, resize
(`0x2d6790`) grows the list and publishes it; otherwise the routine stores it directly.
They then reload the buffer, move the tail up by `length * stride` bytes when the index is
not the old count, and copy `length * stride` input bytes to the index position.
Append range follows the same growth rule. Removal validates the index,
moves the tail if needed and decrements the re-read count. Search is retail's
comparator-driven midpoint loop plus final candidate check: it returns an actual
matched index or -1, not an insertion position or a first-duplicate guarantee.

## Reference and temporary ownership

String copy reads an indexed token without a range guard, writes it to the
output, reloads that output and increments a nonnull token's count at -4.
String append first resizes, then reads/retains the incoming cell, releases the
destination's old token and re-reads the incoming cell for publication. These
reads and the retain-before-release order preserve aliases. String resize grows
by zeroing new cells; shrink interns a null token, releases each old token using
the full header count, replaces cells and publishes the requested count. Free
calls carry both allocator and token-header address.

Object append retains at object +4 before either storing in spare capacity or
calling word append. Its retaining semantics are separate from the word append
primitive, which always calls resize. Allocation and interning failure routing
remain their owning services' contracts.

## Scope

String copy is 52 bytes, word append 84 and object append 88.

Sorted insertion and other list-library routines beyond this primitive span
are not covered here.
