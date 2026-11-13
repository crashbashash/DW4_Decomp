# Items and database record lookup

Two units carry the item records. [beDBManager.cpp](../../src/game/beDBManager.cpp) holds the
`beDataBase` lookups, and [beNDMWItemBase.cpp](../../src/game/beNDMWItemBase.cpp) holds the
`beNDMWItem*` classes, which read their own record through them. Both are byte-identical to retail.
`beNDMWItemBase.cpp` is one C++ translation unit of 48 functions (`0x447bc0..0x448fd0`) built with
exceptions on; it reproduces its 21 retail exception records and its one table.

## Item classes

Every item is a reflected `beNDMWItem*` object: `_kindNo` at 8, `_recNo` at 12 and `_isEquip` at 16,
plus one class field.

| Kind | Class | Extra fields | Database |
| ---: | --- | --- | --- |
| 0 | `beNDMWItemWeapon` | `_revision`, `_pocket` | `weapon` |
| 1 | `beNDMWItemBlueArmor` | `_revision`, `_pocket` | `armor1` |
| 2 | `beNDMWItemYellowArmor` | `_revision` | `armor2` |
| 3 | `beNDMWItemAbilityChip` | | `abChip` |
| 4 | `beNDMWItemDisk` | `_kazu` (stack count) | `conItem` |
| 5 | `beNDMWItemInstant` | `_value` | `insItem` |
| 6 | `beNDMWItemImportant` | | `impItem` |
| 9 | `beNDMWItemWaza` | `_baseNo` | `pcTech` |

Each class has the same virtual slots:

- `vfunc_20` returns the class's metaobject.
- `vfunc_21` sends `DATABASE <name>` / `GETDATABASE` to the status messenger through
  `beNDMWItemBase_RequestDataBase` and returns the database object it answers with.
- `vfunc_22`, on disks and consumables, uses the item on a player.
- `vfunc_23` packs the item into an inventory word.
- `vfunc_24` unpacks an inventory word into the item.

The inventory word holds the record number in bits 0-9, the equipped flag in bit 10 and the kind in
bits 12-15. Weapons and blue armour add the pocket count in bits 16-19, and every weapon and armour
adds the revision in bits 20-30. A disk keeps its stack count in bits 16-19.

`beNDMWItemBase_GetRecordInt`, `_GetRecordBool` and `_GetRecordString` call `vfunc_21` with the
status and read the item's record (the current `_recNo`, read after that call) from the returned
database.

### Creating items

`beNDMWItem<Class>_Set` stamps the kind and record number, clears `_isEquip` and stores the class
fields; the disk's count starts at 0. The weapon and both armours also have `_SetRandom`, which rolls
the fields from the system's Mersenne Twister before calling `_Set`:

- `beNDMWItemRevisionPocketBase_RollPocket` (weapon and blue armour) draws `genrand() % 620 + 1`,
  less `(level / 10 + 10) / 10`. A result of 1 gives 5 pockets, below 4 gives 4, below 8 gives 3,
  below 16 gives 2, below 32 gives 1, and anything else 0.
- `beNDMWItemRevisionBase_RollRevision` draws `genrand() % 6000 + 1` and `genrand() % level + 1`.
  A first draw of 1 gives a revision of `level + 1`; below 3001, the second draw less a tenth of
  the first, floored at 0; otherwise 0.

### Prices and colours

`beNDMWItemRevisionPocketBase_GetPrice` returns the record's `HANBAI` (sale) value when asked for
`HANBAI`, and its `KAITORI` (buy-back) value for any other key. Yellow armour adds 100 (sale) or
25 (buy-back) per revision point. Weapons and blue armour add the same, plus a pocket bonus:

| Pockets | 0 | 1 | 2 | 3 | 4 | 5 |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| Sale | 0 | 500 | 1500 | 6000 | 12000 | 24000 |
| Buy-back | 0 | 250 | 750 | 3000 | 6000 | 12000 |

`beNDMWItemBase_GetRevisionColor` returns the RGB colour the list and shop controllers draw an item
name in. Ability chips, disks, consumables and key items are grey (0.9, 0.9, 0.9), and so are weapon
276, blue armour 31 and yellow armour 44. Other weapons and armour are coloured by revision:

| Revision | Colour |
| --- | --- |
| 1000 and above | (1.0, 0.0, 0.9) |
| 501-999 | (1.0, 0.6, 0.1) |
| 101-500 | (0.9, 0.8, 0.1) |
| 31-100 | (0.4, 1.0, 0.6) |
| 1-30 | (0.1, 0.9, 1.0) |
| 0 | grey |

The colour is an `igVec3f` returned by value. Its copy constructor runs on `return`, and that is what
gives this frameless leaf its exception record ([exception unwind](exception-unwind.md)).

`beNDMWItemBase_IndexOfRecNo` returns the index of the first item in an `igObjectList` with a given
record number, or -1.

### Using disks and consumables

`Gap__Bec__beNDMWItemDisk__vfunc_22` switches on the record number. Records 0-2 restore HP and 3-5
MP, by the record's `HP` or `MP` value; record 9 restores both. Record 6 fetches the player's
`GETPEBASEWORK` model work and, when the first entry of its timer list is running, clears it when
`genrand() % 10` is at most `8 - _poisonEndurance`: by that field, a poison cure. Record 7 sends `GAMERAM` the `P2PKOUKAMAGIC` fight calculation with the
player as source and target and -50. Record 8 sets the gate stage for the player and runs
`gatedisc.lua`; it is the only record that returns 1.

`Gap__Bec__beNDMWItemInstant__vfunc_22` reads the record's `UP` value and the player's `GAMERAM`
record. Record 0 pays bits: a random amount in a band chosen by the first player's `LEVEL`, raised by
its `BITRITSU` percentage, added to the player's `BIT` and kept in `_value`.

| `LEVEL` below | 19 | 39 | 60 | 94 | 108 | 144 | 203 | (else) |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Lowest | 10 | 55 | 87 | 162 | 232 | 340 | 446 | 566 |
| Highest (exclusive) | 55 | 100 | 195 | 350 | 520 | 700 | 860 | 1160 |

Records 1-3 add `UP` to the player's `XDATA`. Records 4-25 add it to one `UPCNT` counter (4-5
counter 2, 6-7 counter 3, 8-11 counter 0, then two records per counter from 4 to 10) and send
`RECALCPLAYER`; they return 1.

## Flat record indices and typed storage

The database's twelve fields at 8..52 are reflected pairs of column lists and value storage for
char, short, int, float, bool and string. `beDataBase_FindRecordValueIndex` captures the initial
column count as the record stride; zero stride returns -1. It finds the column with
`igProperty_FindByName` and the supplied key, returns -1 when that search returns null, and
otherwise re-reads the column count and data and finds the column by pointer equality. The result is
`capturedStride * record + column`; a column missing from the re-read array leaves -1 and the
multiplication is still added.

`beDataBase_GetRecordInt` tries signed char, then signed short, then signed int columns, sign-extends
the stored value and returns 0 if every lookup returns -1; a stored negative value is still a
successful lookup. `beDataBase_GetRecordBool` returns the stored byte without normalisation.
`beDataBase_GetRecordString` returns the entry's value pointer at 8, or the empty string for a null
value. Neither guards a missing index. `beDataBase_GetRecordCount` divides the first nonempty value
storage (string, char, short, int, float, then bool) by its column count, and returns 0 when every
column count is zero.

## Open questions

- The colour type is spelled `igVec3f` with an explicit copy constructor
  ([igVec3f.h](../../include/dw4/igVec3f.h)); the record proves a class with a non-trivial copy,
  not its name. `src/engine/maths/MathsLibrary.h` and `src/game/beWaterPlain.cpp` still declare
  their own `igVec3f`.
- Weapon 276, blue armour 31 and yellow armour 44 are drawn grey whatever their revision; what those
  records are is not established.
- `vfunc_22` passes its second argument both as the `GAMERAM` object (insight, system and messenger)
  and as the status the record getters take; which class callers pass is not established.
- The callees `FUN_00236f80` (find an object by metaobject in an insight), `FUN_003f9c80` and
  `FUN_003f9e20` (add HP and MP), `FUN_00447b00` and `FUN_00447b40` (test and clear the model work's first timer) and
  `FUN_003a9250` (find a list property by name) belong to other units and keep their placeholders.
