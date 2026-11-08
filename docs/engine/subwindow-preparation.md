# SUBWND work and shop-stock preparation

The complete **3d8740..3d9bd0 / 5,264-byte** preparation body called by the
[service-menu lifecycle](subwindow-lifecycle.md) is recovered, with **1,222 executable
instructions**. The94 remaining words are zero padding excluded by Ghidra's address ranges
in the generated [reviewed extents](../../data/function-extents.json).

It matches as `src/unmatched/FUN_003d8740.cpp`. Database access,
record lookup, item construction/initialization, list operations, allocation and
destruction are separate services. It does not implement prices, buy/sell,
service transactions or NPC menus.

## Work, currency and player selection

Missing RAM `_work`44 is constructed through3b5ec0. Allocation first queries
301000, then uses the default selector587110 when byte554c14 is zero. The
224-byte private frame's temporary at220 holds a retained reference; the old
RAM work is released before publication and the current temporary is released
afterward. The published work is cached before that last release. Destruction
callbacks may change RAM or temporary storage between these steps.

Every mode queries GAMERAM GETPLAYER separately for all four slots. A nonzero
**ISUSE byte** includes the player in the participant count and caps signed BIT
at9,999,999 and XDATA at9,999. Negative values are retained; unjoined records
are untouched. When capping, the property is looked up again before writing;
the second result need not equal the first. Player zero is queried again for
LEVEL even for a non-stock mode or an already populated stock list. The manager
uses player zero's level rather than the `_whoGenerate` player.

Reflection names the work's list fields `_weaponSalesList`16,
`_armorSalesList`20, `_chipSalesList`24 and `_junkSalesList`28, followed by
`_junkGift`32. Only signed counts below1 trigger rebuilding. The routine asks
2d6680 for36 elements of4 bytes, resets the current list through301c90, then
builds columns `00` through `35`. It reloads each work list field after service
calls; the work pointer itself remains cached.

## Stock selection

| Mode | Database | Row | Missing numeric entry (full64-bit -1) |
| --- | --- | --- | --- |
| 6 WPU | shopWeapon | Species base + level tier, capped at24 | Append null |
| 7 APU | shopArmor | Level tier, capped at29 | Columns00–11 still construct blue armor;12–35 append null |
| 8 CHIP | shopChip | Level tier, capped at29 | Append null |
| 9 JUNK | shopJunk | Common investment tier -1..8 | Omit entry; no placeholder |

The level thresholds, in row order, are
`10,17,22,27,32,37,42,47,52,61,68,73,78,83,88,93,98,103,108,113,118,128,138,148,158,168,178,188,198`.
A level below10 selects tier0. WPU uses only the first24 thresholds; APU and CHIP
use all29. Comparisons are signed.

WPU selects base150 with two or more joined players and does not query species
in that branch. Otherwise player zero's DIGIMONNO selects:

| DIGIMONNO | Base |
| --- | --- |
| 1,4,12 | 25 |
| 2,7,14 | 50 |
| 3,9 | 75 |
| 6,10 | 100 |
| 8,11,13 | 125 |
| Other | 0 |

JUNK fetches GAMERAM GETCOMMON / COUNTER through the property's list/data chain.
Its signed investment thresholds are
`1000,6000,26000,86000,206000,456000,956000,1956000,3956000`.
Below1,000, row-1 produces no stock. When rebuilding it stores the investment
in `_junkGift`; an existing list skips that write even though common investment
was fetched. For each present numeric entry it queries the same row's literal
`kind`:0 weapon,1 blue armor,2 yellow armor. Other kinds skip the entry. This is
one kind per row, not an independently numbered kind column per item.

## Items and ownership

| Item | Factory | Initializer | Private temporary |
| --- | --- | --- | --- |
| Weapon | 3c8c90 | 4482e0 | 216 WPU;200 JUNK |
| Blue armor | 3c8b00 | 448430 | 212 APU;196 JUNK |
| Yellow armor | 3c8970 | 448580 | 208 APU;192 JUNK |
| Ability chip | 3c87f0 | 448660 | 204 |

Item allocation uses selector587108 after the same object/default allocator
choice. Weapon/armor initialization receives item,id,owner,player-zero level;
chip initialization receives item,id only. The current temporary is appended
through301e30, then the current temporary is released with the low23-bit rule.
Callbacks can replace the temporary between initialization, append and release.
The database result is used at full width, so
`0xffffffff` is distinct from the64-bit missing sentinel.

## Verification and remaining work

```sh
python3 tools/test_function_extents.py
```

Continue the concrete service-controller/result paths and stock
services, against the [full hub completion contract](../systems/hub-recovery.md).
