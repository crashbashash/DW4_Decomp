# Retained object lists and property lookup

The separate [unchecked entry-word getter](../../src/game/beNDMWLoadIntf2.cpp)
at `0x3e9260` uses the declaring base `igDataList::_data` and retains its exact
20 bytes. A LoadIntf2 `_system` receiver association for it is refuted;
see [GAMERAM ABI recovery](../systems/combat-draft-recovery.md).

The complete contiguous twelve-body group at `301c90..302540` contains 2,160
code bytes. Together with the 148-byte name setter at `2fecb0`, that makes thirteen
bodies. Retained append (88 bytes), `igProperty_FindByName` (`3022c0`, 188 bytes) and
remove-first (`302000`, 248 bytes) are in [list-services_tail.inc](../../src/engine/core/list-services_tail.inc) of the Core library unit,
with the other list bodies of the group.

The [name generator](../../scripts/seed_names_object_lists.py) derives retained-list
and name-publication roles from verified accesses. Existing property roles live
in `config/SLUS-20836/names/Property.tsv`. These semantic labels are not original C++ names.
The group serves both messenger registries and the broader
[GAMERAM property system](property-system.md).

## Shared storage and retained operations

Lists store count +8, capacity +12 and a buffer reference +16. Elements are
four-byte object references. Object reference updates operate on the full header
word at +4; destruction is triggered when its low 23 bits become zero.

| Address | Recovered operation |
| --- | --- |
| `301c90` | Retain a replacement once per original element, release old elements, then fill using the re-read count and captured final buffer |
| `301d80` | Release elements and zero their storage without directly changing count |
| `301e30` | Retain and append one object; use generic append/growth when full |
| `301e90` | Retain source elements, then append using the re-read source count/buffer |
| `301ee0` | Resize retained references, zeroing growth or releasing/zeroing the removed range |
| `302000` | Remove the first pointer match from a starting index; publish the original success/failure word through output a0 |
| `302100` | Remove all pointer matches from a starting index; return removal count |
| `302240` | Return an existing pointer's first index, or append and return the original count |

Fill captures count for retain/release but reloads it for publication. Clear also
reloads count for its byte-zero service. Resize instead retains its original count
for release and zeroing, then publishes the requested count. Destructor callbacks
can therefore affect these operations differently.

Append-list captures source buffer/count for the retaining pass, then reloads
both before calling generic word append. Single append retains before growth.
Remove-first/all release the selected object before generic removal, then reload
the buffer/count and clear the newly unused tail slot. Remove-all resumes at the
same index after removal, so adjacent duplicates are not skipped.

These entries retain original unchecked start/count behavior. In particular,
retained resize does not reject a negative shrink count. Whether any gameplay caller
relies on negative indices or counts is not established. Guest pointer and word arguments
use the EE ABI's canonical sign-extended word representation.

## Property searches and corrected contracts

A property descriptor stores a member offset at +8. That offset selects the
record's text pointer, pointer key or numeric key; it is not hard-coded to a
particular class field. Messenger group names use offset eight.

| Address | Recovered contract |
| --- | --- |
| `3022c0` — `igProperty_FindByName` | With non-null descriptor and key, scan records and compare non-null selected strings; return the first record matching text |
| `302380` — `igProperty_FindByPointer` | With non-null descriptor, scan non-null records for exact selected-word equality, including a zero key |
| `3023f0` — `igProperty_FindBySortedKey` | Search using the insertion-index helper, then return the record only if its selected word equals the key |
| `302480` — `igProperty_FindInsertionIndex` | Binary-search sorted unsigned selected words; return an equal midpoint or an insertion position; return -1 for a null descriptor and zero for an empty list |

The older labels `igProperty_GetByIndex` for `302480` and
`igProperty_FindByIndexChecked` for `3023f0` are wrong: neither consumes a positional
index, and a standalone positional-getter reading is refuted. The former
returns an integer search/insertion position, not a record or count. Equality can
return a midpoint duplicate; it is not a guaranteed first-equal/lower-bound search.

Text lookup captures count once but reloads the buffer and descriptor member
offset before subsequent comparisons. A comparator callback changing count to
zero and moving the buffer does not shorten the original scan. Pointer lookup
also captures count but explicitly skips null records; text and sorted lookup
retain their original valid-record assumptions. Numeric comparisons are unsigned, so
`7fffffff` sorts below `80000000` and `ffffffff`; exact equality depends on canonical
EE word arguments, including their upper register bits.

## Name publication and messenger integration

`igNamedObject_SetName` (`2fecb0`) lazily obtains the global string pool, interns
the new text, releases the old token at object +8, then publishes the new token.
It interns before releasing, preserving aliasing when old and new text share a
token. Token release uses the full preceding count word and owner at token -8.
Pool failure policy and actual interning remain lower dependencies.

Messenger group lookup uses this descriptor-based search, reached through
[factory creation](object-creation.md), [memory setup](messenger-memory.md),
[dispatch](messenger-dispatch.md) and [lifecycle](messenger-lifecycle.md). A lookup miss
creates and registers another group in the registry list, and reset empties that list.

## Remaining boundaries

Run from the repository root:

```sh
make check
make typed-check
make link
```

[Generic list operations](list-services.md) and
[pool/table/chunk interning](string-pool.md) are described separately. Concrete class
descriptors/fields/receivers and lower service contracts remain work; naming and recovery
do not establish complete Lua-dependent engine recovery.
