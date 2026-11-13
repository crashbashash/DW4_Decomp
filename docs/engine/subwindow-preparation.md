# SUBWND work and shop-stock preparation

`beNDMWStatus__PrepareWork` creates the SUBWND manager's work, caps the party's BIT and X Data and
fills the shop stock lists (`src/game/beNDMWStatus.cpp`). The [lifecycle](subwindow-lifecycle.md)
calls it when a menu opens and the [command receiver](subwindow-command.md) when UPDATE finds no
work. It does not implement prices, buying, selling or the service transactions.

## Work, currency and player selection

A missing RAM `_work` is created through `beNDMWStatusInfoWork_Create`, with the object's own
allocator when `g_useOwnerAllocator` is set and the default selector's otherwise. The new work is
held in an `igSmartPointer`, retained, the old RAM work is released and the new one published.

Each of the four player slots is fetched through GAMERAM **GETPLAYER**. A set **ISUSE** flag
counts the player into the party and caps BIT at 9,999,999 and XDATA at 9,999; negative values are
kept and slots not in use are untouched. A capped record is looked up again before it is written.
Player 0's **LEVEL** is then read for every mode, even one without stock or with a list already
filled: the stock follows player 0, not `_whoGenerate`.

The work's lists are `_weaponSalesList`, `_armorSalesList`, `_chipSalesList` and `_junkSalesList`,
followed by `_junkGift`. Only an empty list (count below 1) is rebuilt: `List_Reserve` makes room
for 36 entries, `ObjectList_FillRetained` resets it, and columns `00` through `35` are read from
the shop database.

## Stock selection

| Mode | Database | Row | Missing entry (-1) |
| --- | --- | --- | --- |
| 6 WPU | shopWeapon | species base + level tier, tier capped at 24 | append null |
| 7 APU | shopArmor | level tier, capped at 29 | columns 00–11 still create blue armor; 12–35 append null |
| 8 CHIP | shopChip | level tier, capped at 29 | append null |
| 9 JUNK | shopJunk | common counter tier -1..8 | skipped, no placeholder |

The level tiers start at these levels:
`10,17,22,27,32,37,42,47,52,61,68,73,78,83,88,93,98,103,108,113,118,128,138,148,158,168,178,188,198`.
A level below 10 is tier 0. WPU uses the first 24 thresholds; APU and CHIP use all 29. The
comparisons are signed.

WPU uses base row 150 when two or more players are in the party, without reading the species.
Otherwise player 0's DIGIMONNO selects:

| DIGIMONNO | Base |
| --- | --- |
| 1, 4, 12 | 25 |
| 2, 7, 14 | 50 |
| 3, 9 | 75 |
| 6, 10 | 100 |
| 8, 11, 13 | 125 |
| other | 0 |

JUNK reads entry 1 of GAMERAM **GETCOMMON**'s **COUNTER** list. Its tiers start at
`1000,6000,26000,86000,206000,456000,956000,1956000,3956000`; below 1,000 the row is -1 and no
stock is made. A rebuild stores the counter in `_junkGift`; a filled list skips that write. For each
present entry the column's `kind` entry (the column key with `kind` appended) chooses 0 weapon,
1 blue armor or 2 yellow armor; any other kind skips the entry.

## Items and ownership

| Item | Factory | Initialiser |
| --- | --- | --- |
| Weapon | `beNDMWItemWeapon_Create` | `beNDMWItemWeapon_SetRandom` |
| Blue armor | `beNDMWItemBlueArmor_Create` | `beNDMWItemBlueArmor_SetRandom` |
| Yellow armor | `beNDMWItemYellowArmor_Create` | `beNDMWItemYellowArmor_SetRandom` |
| Ability chip | `beNDMWItemAbilityChip_Create` | `beNDMWItemAbilityChip_Set` |

Items are allocated through the NDMW allocator selector after the same owner/default choice.
Weapon and armor initialisers receive the item, the id, the manager and player 0's level; the chip
initialiser receives the item and the id. Each new item is held by an owning reference, appended
through `ObjectList_AppendRetained` and released when the holder goes out of scope. Every item kind
has its own holder class, which is why four holder destructors are emitted.
