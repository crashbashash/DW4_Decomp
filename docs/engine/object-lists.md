# Retained object lists and property lookup

The separate [unchecked entry-word getter](../../src/engine/ObjectList_GetAt_003e9260.c)
at `0x3e9260` uses the declaring base `igDataList::_data` and retains its exact
20 bytes. A LoadIntf2 `_system` receiver association for it is refuted;
see [GAMERAM ABI recovery](../systems/combat-draft-recovery.md) ([#1042](../findings/findings-1001-1250.md#f1042)/#1043).

The complete contiguous twelve-body group at `301c90..302540` contains 2,160
code bytes. Together with the 148-byte name setter at `2fecb0`, all thirteen
bodies have readable [behavioral C](../../recovered/engine/object-lists.c).
Findings [#873](../findings/findings-0751-1000.md#f873)/#874 record the recovery and correction of two historical property
lookup labels. One body, retained append (88 bytes), already has exact source in
[list-services.c](../../src/engine/list-services.c); twelve compiler residuals
remain. The behavioral C claims no new matching bytes.

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
can therefore affect these operations differently. The reference C preserves the
original reloads, rather than imposing one host container policy.

Append-list captures source buffer/count for the retaining pass, then reloads
both before calling generic word append. Single append retains before growth.
Remove-first/all release the selected object before generic removal, then reload
the buffer/count and clear the newly unused tail slot. Remove-all resumes at the
same index after removal, so adjacent duplicates are not skipped.

These entries retain original unchecked start/count behavior. In particular,
retained resize does not reject a negative shrink count. The oracle's bounded
negative-index fixtures demonstrate original accesses and stored counts; they do
not establish a valid gameplay caller contract. Guest pointer and word arguments
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

Older findings name `302480` `igProperty_GetByIndex` and `3023f0`
`igProperty_FindByIndexChecked`. Neither consumes a positional index. The former
returns an integer search/insertion position, not a record or count. Equality can
return a midpoint duplicate; it is not a guaranteed first-equal/lower-bound search.
Those findings keep the old names, with explicit correction
and a refuted standalone positional-getter interpretation ([#874](../findings/findings-0751-1000.md#f874)).

Text lookup captures count once but reloads the buffer and descriptor member
offset before subsequent comparisons. A comparator callback changing count to
zero and moving the buffer does not shorten the original scan. Pointer lookup
also captures count but explicitly skips null records; text and sorted lookup
retain their original valid-record assumptions. Numeric comparisons are unsigned
and tested across `7fffffff/80000000/ffffffff`; exact equality depends on canonical
EE word arguments, including their upper register bits.

## Name publication and messenger integration

`igNamedObject_SetName` (`2fecb0`) lazily obtains the global string pool, interns
the new text, releases the old token at object +8, then publishes the new token.
It interns before releasing, preserving aliasing when old and new text share a
token. Token release uses the full preceding count word and owner at token -8.
Pool failure policy and actual interning remain lower dependencies in this oracle.

A separate cold integration suite executes actual descriptor-based group lookup,
name publication, retained append/resize and generic list operations through
[factory creation](object-creation.md), [memory setup](messenger-memory.md),
[dispatch](messenger-dispatch.md) and [lifecycle](messenger-lifecycle.md). It uses
an actual registry list containing a named group, creates/registers another group
on a real lookup miss, finds and queries that group, queues/delivers its message,
performs context push/pop, resets and initializes again. Assertions prove registry
growth to two and reset to zero. Registry lookup and whole-list mutation are real
bodies, not controlled return values, in this composition.

## Validation and remaining boundaries

Run from the repository root:

```sh
python3 testing/test_object_lists_retail.py
python3 testing/test_messenger_registry_retail.py
python3 testing/test_object_creation_retail.py
python3 testing/test_messenger_factories_retail.py
python3 testing/test_messenger_memory_retail.py
python3 testing/test_messenger_lifecycle_retail.py
python3 testing/test_messenger_dispatch_retail.py
python3 testing/test_messenger_results_retail.py
make check
make typed-check
make link
```

The object-list suite passes **718 original-instruction RAM/defined-return/
ordered-call cases across all thirteen bodies**, with real recovered
[generic list operations](list-services.md). Cases cover growth/shrink, duplicate
and null references, aliased append, ownership before mutation, callback count
changes, returned removal counts/output words, descriptor nulls/member offsets,
text/pointer/sorted keys, duplicate unsigned keys, relocated lookup storage,
name-token alias/release and lazy pool creation.

The messenger registry suite passes **twelve persistent RAM/ordered-call
checkpoints** through real registry/name/object/generic list bodies and the cold
engine chain. It uses synthetic field metadata and controlled
concrete field/registrar/allocator/byte/interner/receiver services. Standalone
object-list destruction is controlled; the cold composition executes the recovered
shared object lifetime path with its remaining cleanup leaves. Actual pool/chunk
composition, concrete class descriptors/fields/receivers and lower service contracts
remain work. Twelve compiler drafts were rejected by exact verification and stay
outside `src/`; naming, recovery and these comparisons do not establish complete
Lua-dependent engine recovery or new native gameplay.

The [interned-registry composition](string-pool.md#cold-registry-interning-and-erase-byte-match)
replaces whole pool/table/chunk interning and release leaves through this cold
registry path. Its 158 checkpoints retain concrete field/registrar and allocator/
byte/sync primitives as controlled boundaries; the standalone suites above are
separate from it.
