# Shop windows

`src/game/beNDMWShopCtrl00.cpp` holds the shop service windows the SUBWND menu opens
([SUBWND lifecycle](subwindow-lifecycle.md)): each class's update (vtable slot 21, `<Class>_Update`)
and meta getter (slot 20, `<Class>_GetMeta`, which returns `g_<Class>_metaObject[0]`), plus the
helpers the updates call. `beNDMWShopCtrlSales_Update` has no source yet; its helpers do.

## Common shape

Every update is a state machine over the window's nested counters `_st0`.. `_st3`
([window tree](window-tree-and-shop-root.md)). `_st0` is the window state: 0 builds the window,
1 runs it, 2 closes it (queued model close, queued text clear, children close) and 3 waits for the
close poll before clearing `_isRun`. `_st1` is the step inside state 1 and `_st2`/`_st3` its sub-steps.
Advancing a counter clears the ones below it.

A child window is created with the owner's allocator when `g_useOwnerAllocator` is set and the
default selector's otherwise, held in an `igSmartPointer`, bound with `beNDMWWindow_BindContext`
and appended to `_subWindow`. The parent records the child count in `_nowProcKazu` and treats any
change of the count as the child having finished; the child's answer is the parent's `_retCode`.
Text is addressed by font group and cell (`STWINFONTnn` / `fontnnn`) through TEXTCTL messages;
the cells a window fills are queued on its text-close lists so the close state blanks them.
Messages shown in a message window are `txt_shop.lua` codes.

## Classes

| Class | Created by | Service |
| --- | --- | --- |
| `beNDMWShopCtrl00` | `beNDMWShopCtrl00_Create` (SUBWND modes 1, 3–9) | Root: titles, then the service window for the entry code |
| `beNDMWShopCtrl10` | `beNDMWShopCtrl10_Create` (entry 1 and fallback) | XDATA ([XDATA controller](xdata-controller.md)) |
| `beNDMWShopCtrl30` | `beNDMWShopCtrl30_Create` (entry 3) | BANK |
| `beNDMWShopCtrl40` | `beNDMWShopCtrl40_Create` (entry 4) | CNOS |
| `beNDMWShopCtrl50` | `beNDMWShopCtrl50_Create` (entry 5) | DISK |
| `beNDMWShopDevice` | `beNDMWShopDevice_Create` (entries 6, 7, 8) | WPU, APU and CHIP shops |
| `beNDMWShopJunk` | `beNDMWShopJunk_Create` (entry 9) | JUNK |
| `beNDMWShopCtrlA0` | `beNDMWShopCtrlA0_Create` (SUBWND mode 10) | CARD |
| `beNDMWShopCtrlDigilabo` | `beNDMWShopCtrlDigilabo_Create` (SUBWND mode 2) | LABO |
| `beNDMWShopCtrlA1` | `beNDMWShopCtrlA1_Create` | CARD: one player's card menu |
| `beNDMWShopCtrlA2` | `beNDMWShopCtrlA2_Create` | CARD: opening booster packs |
| `beNDMWShopCtrlEvolve` | `beNDMWShopCtrlEvolve_Create` | LABO: Digivolution list |
| `beNDMWShopCtrlEditBit` | `beNDMWShopCtrlEditBit_Create` | Bit amount entry (bank deposit/withdraw, junk donation) |
| `beNDMWShopCtrlSell` | `beNDMWShopCtrlSell_Create` | Sell menu: devices or disks |
| `beNDMWShopCtrlDeviceSell` | `beNDMWShopCtrlDeviceSell_Create` | Device buy-back list |
| `beNDMWShopCtrlDiskSell` | `beNDMWShopCtrlDiskSell_Create` | Disk buy-back list |
| `beNDMWShopCtrlSales` | `beNDMWShopCtrlSales_Create` | Shop stock list (WPU/APU/CHIP/JUNK) |
| `beNDMWShopCtrlXdataChip` | `beNDMWShopCtrlXdataChip_Create` | XDATA ability-chip upgrades |

## Root and services

- **Root** (`beNDMWShopCtrl00_Update`): state 0 opens `beNDMWShopTitle00`, `beNDMWStatusTitle01`..`03`
  and `beNDMWShopTitle01` (bound with the entry code). Once `i_messwn` has finished `SQ_STOPEN` it
  opens the service controller for `_entCode` and waits for it to close; the close state sends
  MODELCTRL `i_bgclear` OFFREEZE.
- **XDATA** (`beNDMWShopCtrl10_Update`): main menu (1150) for stat upgrades or chips. A stat upgrade
  costs one XDATA per started step of 5 above 45 points, at most 400; caps are 9,999 (99,999 for
  MHP/MMP). Paying debits XDATA, increments the stat's UPCNT slot, recalculates the player and refills
  HP/MP. Chips open `beNDMWShopCtrlXdataChip`.
- **BANK** (`beNDMWShopCtrl30_Update`): deposit or withdraw devices (a `beNDMWStatusCtrlD0` list moving
  items between DEVICEFOLDER, at most 36, and BANKDEVICE, at most 96) or bits (`beNDMWShopCtrlEditBit`,
  moving BIT and BANKBIT).
- **CNOS** (`beNDMWShopCtrl40_Update`): re-rolls a device for 300 bits. The device's level picks a band
  (40/100/200/300/400/above), its kind the database (`coweapon`, `coarmor1`, `coarmor2`); `genrand() %
  10000` walks the band's RATE column and the row's ID becomes the device's `_recNo`.
- **DISK** (`beNDMWShopCtrl50_Update`): buy consumable disks (ten `conItem` rows, a stack holds at most 9;
  `beNDMWShopCtrl50_ShowQuantity`/`_HideQuantity` show quantity and total) or sell through
  `beNDMWShopCtrlSell`.
- **WPU/APU/CHIP** (`beNDMWShopDevice_Update`): menu 1650/1750/1850; buy opens `beNDMWShopCtrlSales`
  with the entry code, sell opens `beNDMWShopCtrlSell`.
- **JUNK** (`beNDMWShopJunk_Update`): SUBWND GETSHOPDATA 9 supplies the stock and the lifetime donation
  total. Donating (EditBit mode 2) adds to GAMERAM COUNTER[1]; crossing one of the thresholds 1,000 ..
  3,956,000 runs `junkexit.lua` / `stagML13.lua` and ends the visit. Buying opens `beNDMWShopCtrlSales`.

## Lists, selling and chips

The buy-back and stock lists show twelve rows per page. `<Class>_UpdatePageCount` sets `_maxPage`,
refills the decide list (one bool per row: false greys a row out) and returns the rows on the page;
`<Class>_RefreshText(rows, description)` writes the rows (name, price, page digits) and the
highlighted item's TXT. Page turns go through the list window's paging virtuals (slots 22–24, shared
with `beNDMWListCtrl`) and put the `beNDMWWindowSelect` into its reload state. The row pointer model
`i_stcursor04` plays `SQ_OPENnn` for the row (`beNDMWShopCtrl50_MoveRowCursor`,
`beNDMWShopCtrlSell_MoveRowCursor`, `beNDMWShopCtrlSales_MoveRowCursor`). A decide-list fill with a
literal appends through one inline whose `true`/`false` argument binds a `const bool &`, so each literal is
an MWCC one-byte `.sdata` temporary the code loads. The inline declares the count before the list
pointer it casts from its argument: MWCC numbers the locals in declaration order, which is what puts
the list in the lower saved register in `beNDMWShopCtrlDiskSell_Update` and
`beNDMWShopCtrlSales_UpdatePageCount`.

- **Sell** (`beNDMWShopCtrlSell_Update`): greys out devices or disks when the player has none to sell,
  then opens `beNDMWShopCtrlDeviceSell` or `beNDMWShopCtrlDiskSell`. Selling adds the KAITORI price to
  BIT (capped at 9,999,999) and removes the device, or reduces the disk stack.
- **Sales** helpers: `beNDMWShopCtrlSales_CanPlayerUse` (chips always; weapons when the Digimon's bit is
  in SOUBI and its SKILL level reaches SKILLPOINT; armour when LEVEL reaches LVPOINT) and
  `beNDMWShopCtrlSales_PreviewSelected`, which stashes the equipped items
  (`beNDMWShopCtrlSales_StashEquipment`), equips the item, sends RECALCPLAYER and SUBWND ONPREVIEW, then
  restores them (`beNDMWShopCtrlSales_RestoreEquipment`).
- **XDATA chips** (`beNDMWShopCtrlXdataChip_Update`): lists the player's ability chips with their next
  level's NEXTX cost, refuses at the maximum level (1170) or with too little XDATA (1161), previews the
  chip one level up and, on confirmation, debits XDATA and raises the chip's `_recNo`.

## Card shop and Digilab

- **CARD** (`beNDMWShopCtrlA0_Update`): opens the account window and player titles, then a player picker;
  each player gets a `beNDMWShopCtrlA1`. A1 offers booster packs (`beNDMWShopCtrlA2`, entry code = packs
  held, disk record 10) and the album: 50 cards on 9 pages of 6 (`beNDMWShopCtrlA1_ShowFirstAlbumPage`,
  `_ShowAlbumPage`, `_CloseAlbumPage`); owned cards show their CARDINFO model, others the blank
  `j_shcard00`. A2 deals three cards, each by a 0..999 roll against the running KAKURITSU sum, sets
  CARDLIST and colours the name by RARE.
- **LABO** (`beNDMWShopCtrlDigilabo_Update`): snapshots the party (`_SnapshotParty`), then offers
  Digivolution (`beNDMWShopCtrlEvolve`), equipment (`beNDMWStatusCtrlEquip`) and a player switch. On
  leaving, a changed party (`_HasPartyChanged`) disables soft reset and runs `demo_digilab.lua`.
  Evolve lists the shinka entries eight to a page (`beNDMWShopCtrlEvolve_RefreshText`) and
  `beNDMWShopCtrlEvolve_ApplyEvolution` keeps the current stats as the base, switches the model,
  re-equips the strongest weapons and empties the four item slot lists.
- **EditBit** (`beNDMWShopCtrlEditBit_Update`): a seven-digit entry; the limit is the carried or banked
  amount, bounded so neither side exceeds 9,999,999 (999,999,999 for junk donations).

## Open questions

- Message codes are `txt_shop.lua` indices; what each says is inferred from where it is used.
- `beNDMWShopCtrlSales_Update` has no source.
