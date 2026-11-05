# Native Digi-Disk shop (hub service)

The Shop's first Digi-Elf, `n_digilff` slot 0 in `stagML13`, offers the disk shop (SUBWND mode 5,
`DISK`). It is reached only through original data: live Cross probe → `hit_n_digilff.lua` →
`n_digilff_00.lua` → the first prompt entry (`entry_0828` chunk 3) → `diskshop.lua` (chunk 43), which
closes the dialogue, restores control, returns the NPC to `SQ_WAIT` and issues
`SUBWND GENERATE DISK/I<player>`. The native window tree then runs the recovered `beNDMWShopCtrl50`
update (`42a2e0..42b7f8`) and its sell branch. It shares STATUS/XDATA's scene freeze, restore and
`SUBWND UPDATE` balance refresh. The service buys Digi-Disks from the ten-row `conItem` catalogue and
sells back both unequipped devices and disks at their `KAITORI` price (devices include the enhancement and grade
surcharges of the retail price rule, see [equipment shops](equipment-shops.md)).

## Ownership

| Piece | Source | Role |
| --- | --- | --- |
| Controller and sell branch | `src/diskshop.c`, `include/dw4/diskshop.h` | `ShopCtrl50`, `ShopCtrlSell`, `ShopCtrlDeviceSell` and `ShopCtrlDiskSell` primary/main/sub states, child creation and completion by child count, notices, cursor marker, page turns. |
| Two-row sell menu | `src/statusview.c` (`DW4_STATUS_SHOPSELECTB0`) | `ShopSelectB0` (`440a20`): `i_stmesscr`, tracked `STWINFONT29` `font100/000/001`, script 1573, per-row `DEFAULTCOLOR`/`CANCELCOLOR`, decide list. |
| List text | `src/statuscontent.c` | `dw4_statuscontent_sell_device` (436060), `dw4_statuscontent_sell_disk` (437ae0), `dw4_statuscontent_kaitori`. |
| Transactions | `src/inventorydetail.c` | Atomic `dw4_playertransactions_disk_buy`, `disk_sell` and `sell_item`. |
| Hub wiring | `src/hubruntime.c` | SUBWND mode 5 factory beside XDATA, BANK and CNOS. |

Class mapping of the factories the controllers call (each factory sits just before its class's vtable):
`3b4d90` ShopSelect01 (menu), `3b4f50` ShopSelect00 (one-choice notice), `3b4410` ShopSelect52 (quantity),
`3b51b0` StatusSelectE1 (list), `3b3f40` ShopSelectB0 (two-row sell menu), `3b7360` ShopCtrlSell,
`3b70e0` ShopCtrlDeviceSell, `3b6e60` ShopCtrlDiskSell.

## Controller (ShopCtrl50)

Field names follow [the BANK controller](bank-shop.md): the window state is the primary state, `main` and
`sub` are the counters, `_retCode` is the selector result (`+30`), `+54` the list cursor, `+58` the listed
disk, `+5c` the held count, `+60` the quantity and `+64` the unit price. Completion of a child is a change
in the child count, as in retail.

| main | Behaviour |
| --- | --- |
| 0 | `ShopSelect01` menu **0x60E** (1550, three rows): 0 buy (cursor reset to 0, main 1), 1 sell (main 4), other leaves (primary state advances). |
| 1 / sub 0 | Presents `j_shwin` `SQ_WAIT`, the hidden page arrows `i_stcursorleft`/`i_stcursorright` at (-146,25,0)/(236,25,0), tracks `STWINFONT13/font000`, runs `txt_shop` **0x5DD** and writes the ten rows: `STWINFONT14 font00i` = `NAME`, `STWINFONT17 font00i` = `HANBAI` (right aligned), `STWINFONT29 font000` blank. |
| 1 / sub 1 | Closes the `i_stcursor04` marker, sends `j_shwin` `SQ_CWINOPEN` and opens a `StatusSelectE1` list (10 rows, start = cursor, at (-121,128,0)) with its own `STWINFONT29/font100` prompt, script **0x611**. |
| 1 / sub 2-3 | While the list is open each highlight change writes the selected row's `TXT` to `STWINFONT29 font000`. A selection stores the cursor, opens the marker `SQ_OPEN%02d`, reads the held count from DISKFOLDER (entry whose record equals the row) and goes to main 5 with notice **0x623** at nine held, else main 2. A cancel closes the content (queued models and texts) and returns to main 0. |
| 2 | `j_shwin` `SQ_DWINOPEN`; `ShopSelect52` with `9 - held` rows (start on the last row, so the quantity starts at 1) at (52,-69,0), prompt script **0x624**, labels script **0x5DE** (`STWINFONT32 font010` quantity, `font021` total, `font020`). Each highlight change rewrites quantity = `9 - held - row` and total = quantity x `HANBAI`. A selection goes to main 3; a cancel hides the labels and returns to the list. |
| 3 | A balance below quantity x `HANBAI` goes to main 5 with notice **0x622**. Otherwise `ShopSelect00` **0x613** (1555), then a `ShopSelect01` yes/no **0x614**. Entry 0 charges `BIT`, raises the disk's quantity and sends `SUBWND UPDATE`; either answer hides the labels and returns to the list. |
| 4 | The sell controller (below); its end returns to main 0. |
| 5 | The notice, then the labels are hidden and the list setup runs again. |

Primary state 2 closes the content owner and children; state 3 waits for them.

## Sell branch

**ShopCtrlSell (434790).** State 0 reads DEVICEFOLDER (any record) and DISKFOLDER (any disk with a positive
quantity). With neither, `ShopSelect00` **0x628** is shown and the window closes. Otherwise a `ShopSelectB0` menu
(script **0x625**) opens whose decide list is `{0,1}` with no devices, `{1,0}` with no disks and none when both
exist; disabled rows use `CANCELCOLOR`. Entry 0 opens the device list, entry 1 the disk list, and either ending
recomputes availability and reopens the menu. Any other result closes.

**ShopCtrlDeviceSell (4353e0).** `j_shwin` `SQ_AWINOPEN`, arrows at (-146,25,0)/(236,25,0), prompt script
**0x676**, title **0x3E8**, twelve `STWINFONT14`/`STWINFONT17` rows and `STWINFONT30 font000/font001` page labels.
The list is the player's DEVICEFOLDER, twelve per page: each row shows the equipped marker (`81 ba`/`8a 71`) with
`NAME`, `KAITORI` right aligned, the item colour, and an enable flag (unequipped and `KAITORI` > 0) that becomes
the selector's decide list and recolours the price (`DEFAULTCOLOR`/`CANCELCOLOR`). Pages turn through the shared
`dw4_statuspage_turn` and `dw4_statusview_selector_restart`. A selection opens the cursor marker, then notice
**0x619** and a yes/no **0x61A**; yes credits `KAITORI` to `BIT` (capped at 9,999,999), removes the item (the
equipment references are re-projected) and sends `SUBWND UPDATE`. The cursor then moves back one row (one page when
it was the first row) and arrows hide on the first and last page. Selling the last item closes the window.

**ShopCtrlDiskSell (436ac0).** `j_shwin` `SQ_WAIT`/`SQ_EWINOPEN`, a twelve-row list of
`STWINFONT14` name, `STWINFONT15` held digit and `STWINFONT17` `KAITORI`, with a decide list of disks held at least
once. A selection opens the cursor marker and a `ShopSelect52` at (52,-104,0) with `held` rows (`j_shwin`
`SQ_BWINOPEN`, scripts 0x624 and 0x5E1 for the `STWINFONT30` labels). The same notice and yes/no follow, and yes
credits quantity x `KAITORI` and lowers the held count.

## Transactions

- `dw4_playertransactions_disk_buy(record, quantity, price)`: quantity 1..9, price >= 0; refuses (`*result` 0) with
  too little `BIT` or more than nine held; otherwise debits and raises the entry whose record matches, in one commit.
- `dw4_playertransactions_disk_sell(index, quantity, price)`: refuses more than held; credits with the retail cap.
- `dw4_playertransactions_sell_item(index, price)`: an equipped or referenced item is refused; the credit uses the
  same cap. Invalid indices are -1 for all three.

## Verification (all headless)

- `make -C port check-hubdisk`: from the normal Shop runtime, the live Cross probe and the original script chain
  reach the shop. It checks every price row against `conItem`, quantity and total labels, the exact charge and the
  raised quantity, a declined purchase, an unaffordable purchase and a nine-held refusal (no change), then the sell
  branch: device list, `KAITORI` credit, item removal, the disk list with quantity selection and credit, the
  disabled device row, the nothing-to-sell notice and restored control. Captures (`build/test_hubdisk <extracted>
  <dir>`) show the "Disk Shop" list, the "How many?" selector and the "Device Folder" list.
- `make -C port check-playerinit`: the three transactions, including refusals, the nine-disk limit, the credit cap
  and re-projection after a device sale.
- `make -C port check-hubnpcs`: the Shop NPC counts as an implemented service.

## Boundaries

- The three controllers were recovered from the retail assembly with an m2c draft and the data tables, not matched
  as source. The ShopSelectB0 initializer, the E1 and quantity selectors and the cursor helpers were read; the base
  window virtual that creates the page arrows (`+0x60`) was not, so the arrows' initial sequences follow the chip
  list's page arrows (hidden left, `SQ_SELECT` right when there is more than one page).
- Retail resets the primary state in one call; natively the content owner is closed and drained over a few updates.
- The prompt on the device list reads "Select the disk to sell." because that is original text 372 shared by both
  lists, not a native substitution.
- Retail adds nothing when the disk is missing from DISKFOLDER but still charges; the native transaction refuses.
  All twelve records exist from creation, so this is unreachable.
- Rendering was only checked through the headless CPU path; there is no retail pixel comparison and no
  hardware-GPU run.
- Only player 0 is wired in the hub; local co-op shop ownership is out of scope.

## Arena control state

ShopCtrl50, ShopCtrlSell, ShopCtrlDeviceSell and ShopCtrlDiskSell retain their counters, selections, pages/cursors and buy/sell quantities/prices in concrete arena instances. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).

## Arena page admission

DeviceSell page decisions use the recovered `igBoolList` field. The item
array remains a derived rendering projection of the authoritative property
inventory. Selectors copy their caller's decisions into their own arena list;
no view borrows a temporary flags array.
