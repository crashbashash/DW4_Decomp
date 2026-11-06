# Item and database record lookup

Two complete contiguous lookup blocks and the concrete
chip database selector are recovered: **ten bodies /1,168 bytes**, all byte-identical to retail.
Seven bodies add **952 exact bytes**. Three already-matched item wrappers
/216 bytes retain their bytes with corrected return and status-argument contracts.
The existing12-byte beDataBase metadata getter is preserved separately.

| Entry | Role | Bytes |
| --- | --- | ---: |
| 447bc0 | Request a named database through the status messenger | 72 |
| 447c10 | Item signed integer value, using current record number | 72 |
| 447c60 | Item raw boolean byte | 72 |
| 447cb0 | Item string pointer | 72 |
| 448640 | Ability-chip selector requests `abChip` | 32 |
| 3a93a0 | Find a column and calculate its flat record index | 192 |
| 3a9460 | Signed char/short/int lookup, in that order | 216 |
| 3a9540 | Raw byte from boolean storage | 56 |
| 3a9580 | String storage lookup with empty-string fallback | 88 |
| 3a95e0 | Record count from the first nonempty column family | 296 |

Matching source is in [beDataBase.c](../../src/game/beDataBase.cpp) and the
[item C](../../src/game/beNDMWItemBaseDatabase.cpp)/
[C++ dispatch](../../src/game/beNDMWItemBaseDatabase.cpp) units. The
[guest-address adapter](../../recovered/engine/item-database.c) passes
**474 full-return/RAM/ordered-call comparisons** with original EE instructions.
All290 non-padding module words execute; two padding words are checked as zero.
Composed cases also execute all47 words of the existing property-name search,
for337 executed instruction addresses in total. No retail output is copied into
expectations. These are synthetic-memory tests, not live-game or native acceptance.

## Item and virtual-selector contract

The reflected item `_recNo` is at12. Each value wrapper captures its key before
calling raw virtual slot92 with `(self,status)`, then reads the **current** record
number after that call and forwards the database, record and captured key to the
appropriate database accessor. The previous `void` drafts accidentally relied
on an unmodelled return register and implicit incoming status argument. Source
now explicitly returns signed full-register integer values, unsigned byte values,
or a string pointer, and explicitly forwards status through the virtual call.
The C++ dispatch class is only an ABI projection with the compiler's two-word
vtable prefix and21 preceding slots, not the original class declaration.

The concrete ability-chip selector supplies the literal `abChip`. The base
request captures `status->_messenger` at20 once, sends
`DATABASE / abChip / id0 / GETDATABASE`, then reads object result0 using that
same messenger, even if the first callback changes the status field. Message
selection/delivery and the DATABASE receiver remain controlled services; this
checkpoint does not recover database loading or asset ownership.

## Flat record indices and typed storage

The database's twelve fields at8..52 are reflected pairs of column lists and
value storage for char, short, int, float, bool and string. The index finder
captures the initial column count as the record stride. Zero stride returns-1.
It uses `igProperty_FindByName` with descriptor585be0 and the supplied key, then
returns-1 when that search returns null. Otherwise it stores the returned pointer
in its original private cell, re-reads column count/data and finds pointer equality.

The result is wrapped `capturedStride * record + column`. If a callback leaves
the named object absent from the subsequently scanned array, column becomes-1
and the multiplication is still added; this is not replaced by an unconditional
missing-index result. Capture and live-read boundaries are checked by mutation
fixtures. RecordColumns in matching C is a synthetic count/data prefix view;
it does not assert a concrete serialized class or inflate recovered typing credit.

Integer lookup tries signed char, then signed short, then signed int columns.
It sign-extends the stored value and returns0 if every lookup returns-1. A stored
negative value is still a successful lookup. Boolean lookup returns an unsigned
byte without normalization:128 remains128. Boolean and string accessors do not
guard a missing index, so tests preserve their before-array reads rather than
adding a safety policy. String entries are objects with value pointer at8; a
null value selects the empty string at4e0858. No extra null-object guard is added.

Record count chooses string columns first, then char, short, int, float and bool.
It divides the corresponding value count by the first nonzero column count.
All-zero columns return0; negative counts retain signed division behavior.
Fixtures include signed overflow division and wrapped index arithmetic.

## Matching and verification boundaries

The column finder's old184-byte occupied-address sum truncated its return and
stack restoration at3a9458/3a945c. Reviewed Ghidra spans restore the full192-byte
body; a regression checks the final instructions and the two internal padding
holes. Ten new reviewed rows make50 total. This adds8 classified code bytes,
without changing the retail image.

The matched lookup set contains48 bytes of explicit target scheduling: finder
two joins/five NOPs28 bytes, integer getter one NOP4 bytes, and count getter two
loads plus join/delay16 bytes. The other1,120 bytes are generated from C/C++.
The count getter's two-load projection retains the original v0/v1 selection;
register-binding pseudos introduce no extra words. An empty assembler directive
keeps the chip selector's original JAL/return instead of a tail transfer. No
post-compile patching, compiler override, opaque replacement body or original
source-spelling claim is used.

```sh
python3 testing/test_item_database_retail.py
python3 testing/test_object_lists_retail.py
python3 -m unittest discover -s tools -p test_function_extents.py
make check
make link
make typed-check
```

The composed chain executes item wrappers, actual chip selection, database
getters and property-name lookup. Messaging/DATABASE delivery and strcmp remain
leaves. Additional leaf fixtures check full-register return forwarding, fresh
record/value-list reads, captured messenger/stride, missing fields, scalar
boundaries and relocated column arrays. Full chip transaction matching,
recalculation, other lobby services and script outcomes remain in the
[hub recovery queue](../systems/hub-recovery.md).
