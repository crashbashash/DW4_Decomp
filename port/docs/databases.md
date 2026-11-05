# Prepared databases

`src/database.c` collects the authored `beDBManagerInfo` objects from the prepared
scene registry in collection order. Each info's `_dataBase` selects its own
pack-local `beDataBase`; `_stringOffsetList` and `_stringData` select ordered
`igNamedObjectList` columns and values. The owner loads each `beDataBase` and what it reaches as typed
instances in its own arena (see below), so nothing points back into the pack. Equal ids in different packs do not alias. The owner
can outlive the registry, parsed descriptors and mounted archives; its borrowed
results remain valid until `dw4_databases_close`.

The title and Main Lobby session preparation create this owner before
controller publication completes, and release it on preparation failure, scene
reset and shutdown. DBBase is the original logical resource name used by the
scripts; the prepared USA lobby supplies `shinka` through
`stagML11/separate/USA_pack.igb`, not a host species-name table. Its three string
columns supply sixteen rows. Other collected databases retain their string
columns in the same owner. Signed char, short and int tables copy into this
owner as well, with validated list classes/counts/capacity/block sizes and complete
rows. Boolean tables have their own unsigned-byte accessor; float accessors
remain future work.

## Native lookup and STATUS

`dw4_databases_get(owner,name)` supplies the typed native
`DATABASE/name/GETDATABASE` result. It retains the first equal name in collection
order. `dw4_database_string(database,row,column)` finds the first equal column
name, then accesses the row-major string entry. Names are case-sensitive. A
present string object with a null name returns an empty string, matching retail.
Missing databases/columns and invalid rows return NULL. Host code never encodes
the object as a number or truncates its pointer into a recovered four-byte field.

`dw4_databases_shinka_name` is the native STATUS callback. Prepared Title01
uses it with the real database owner to display the species name in its authored
font row. Production fresh starter name/stat records reach Title01 in integration
checks; comparison previews additionally use controlled record mutations.
Normal-boot STATUS reaches these records through its scene-owned factory;
see [live STATUS integration](boot-contract.md#live-status-integration).

The scene publishes ordered DATABASE/name/GETDATABASE receivers, preserving
the existing SD selector and first-result rules. Native receiver queries return a
typed database descriptor. Lua can retain that result as opaque tagged userdata
through the host value bridge; retail Lua `sd` calls remain void. Native code
invalidates the database ownership domain before destroying its storage, or
closes/recreates the VM first. Database close unregisters its receivers; the
registry must outlive the owner.

`3a9540` addresses `_boolOffsetList` and
`_boolData` separately from numeric columns and uses LBU. The owner copies and
validates complete `igBoolList` rows; `dw4_database_bool` preserves unsigned
bytes. Chip WU/BLUEAB decisions use `dw4_playerstats_item_bool` rather than the
numeric getter. Retail checks compare thirty boolean results, including 128/255
and duplicate columns; native checks compare 79,328 authored boolean cells over
32 owners. Missing/bad columns and out-of-range rows are guarded instead of
retail's unchecked negative-index read.

## Retail evidence and host validation

Finding **[#794](../../docs/findings/findings-0751-1000.md#f794)** records the instruction boundary. `0x003a93a0` searches the
column list via `igProperty_FindByName` (`0x003022c0`), then computes
`row * column_count + first_equal_column` with wrapped 32-bit arithmetic.
An empty column list or missing name returns -1. `0x003a9580` reads the string
list at database +0x34 and its named object at +8; a null name returns the empty
string at `0x004e0858`. Manager dispatch `0x003a9780` publishes info +0x1c only
for GETDATABASE (command zero). The category is DATABASE at `0x005102a0`;
`0x00366070` constructs the one-entry GETDATABASE enum from `0x004c7348`.
The original shapes were checked with `mipsel-linux-gnu-objdump`.

Retail does not check the string row or missing-column index before dereferencing.
The host accessor explicitly rejects invalid rows and columns. Asset preparation
rejects wrong database/list/item classes, unresolved ids, counts above capacity,
short pool blocks and incomplete string rows. Failed preparation publishes no
database owner. These are host validation boundaries, not claims that malformed
retail input safely returns NULL.

`make check-database-retail` executes the original offset helper, named lookup,
string getter and manager dispatch. **656 offsets, 200 string results and five
GETDATABASE command cases** match, covering missing/null/duplicate columns,
empty lists, signed extrema, multiplication wrap and empty/null strings. strcmp,
command decoding, enum construction and object-result publication are controlled
leaves. Native fixture checks additionally preserve first-name selection and
case sensitivity; general receiver selection has its separate SD oracle.

`make check-database` compares **108,096 authored string cells across 32 owners**
with their original referenced string objects. It checks malformed copied assets,
invalid rows/columns, independent owners and results surviving registry/archive
teardown. `make check-statusviews` exercises the real prepared shinka NAME
lookup through Title01 alongside original text, models and selection waits.
All sixteen shinka NAME rows reach the authored font; an out-of-range species
fails dependency preflight before publishing text.

Full `make -C port all check check-retail -j8` passes on Linux with
`SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a`; optional private live-input
checks retain their skips. Database ownership and STATUS view/text checks
pass ASan/UBSan with `detect_leaks=1` and both sanitizers set to halt on errors.

These checks establish string data and ownership behavior;
general equipment/stat recalculation, complete STATUS gameplay, full-scene visual
parity, Windows and physical Steam Deck validation remain outstanding.


## Signed numeric tables and character creation

`dw4_database_number` follows `0x003a9460`: search `_charOffsetList`, then
`_shortOffsetList`, then `_intOffsetList`; first matching type/column wins.
Signed byte/short loads sign-extend; int values preserve all 32 bits. The native
accessor returns 0 for a found value, 1 with output zero for a missing column
(retail's fallback), and -1 for invalid inputs/rows in a selected table. Asset
preparation checks each corresponding igCharList/igShortList/igIntList; the
values are read from the typed lists in the owner's arena. Borrowers retain no archive references.

Finding [#795](../../docs/findings/findings-0751-1000.md#f795) and [fresh character records](player-records.md#fresh-character-name-and-stats)
use these values for shinka initial stats and all three starter weapon rows.
The numeric retail oracle adds 100 sign/precedence/fallback cases; the authored
fixture independently checks 22,425 numeric cells against raw IGB values.

## Typed arena databases

`include/dw4/arenapack.h` loads a pack's objects as typed instances (the decomp's `beDataBase`, `igNamedObjectList`, ... laid out as in
`include/dw4/reflected.h`) into the game arena, and `include/dw4/arenadb.h` reads them with clean-C ports of `beDataBase_GetRecordInt`,
`GetRecordBool` and `GetRecordString`. See the [arena object model](arena-object-model.md).

There are no host copies: `dw4_database` keeps only a name and a typed table; `dw4_database_number/bool/string/string_rows` and `dw4_database_describe` read the typed `beDataBase` in the owner's arena, and `dw4_adb_validate` carries the structural checks (the four malformed-pack modes of `check-database` still fail the open). `make -C port check-arenadb` compares the typed tables, on every row and column of the
real Main Lobby tables, with an independent decoding of the pack records kept in the test as the oracle.
