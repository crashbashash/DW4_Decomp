# Native XDATA shop (hub service)

The Central west Digi-Elf (`n_digilfm` slot 1) offers the XDATA stat-upgrade and chip-upgrade services. It is
reached only through original data: live Cross probe → `hit_n_digilfm.lua` →
`n_digilfm_01.lua` → `bML01003.lua` prompt → `xdatashop.lua`, which restores control, returns
the NPC to `SQ_WAIT` and issues `SUBWND GENERATE XDATA/I<player>`. The native window tree
then runs the recovered `beNDMWShopCtrl10` update (`4270a0..42860c`, evidence in
[XDATA controller](../../docs/engine/xdata-controller.md) and
[shop selectors](../../docs/engine/shop-selectors.md)). Retail evidence covers the XDATA service entry, the RECALCPLAYER flag and the sequence-set muteki clear.

## Ownership

| Piece | Source | Role |
| --- | --- | --- |
| Controller | `src/xdatashop.c`, `include/dw4/xdatashop.h` | `ShopCtrl10` primary/main/sub states, child creation and completion by child count, highlight scripts, quote, confirmation, charge, notice and continue loop. |
| Selector views | `src/statusview.c` (`DW4_STATUS_XDATAMENU`, `DW4_STATUS_XDATASTAT`, existing `SHOPSELECT00`) | `ShopSelect01` (entries 47e/48b/48e), `ShopSelect11` (seven-stat list, `j_shwin` `SQ_XDATASTATUSOPEN`, `RefreshStatCosts`) and the one-choice quote/notice dialogs, using the real SELECTCTRL manager. |
| Transactions | `src/playertransactions.c` | `dw4_xdata_price`, `dw4_xdata_stat`, `dw4_playertransactions_recalculate` and the atomic `dw4_playertransactions_xdata_upgrade`. |
| Recalculation | `src/playerstats.c` | `dw4_playerstats_recalculate_base`: RECALCPLAYER with the bool false. |
| Hub wiring | `src/hubruntime.c` | SUBWND mode 1 factory (shares STATUS's freeze/enter/restore), `GAMERAM RECALCPLAYER` receiver. |

## Behaviour

- **Menu**: 47e has three entries (stat upgrade, chip, exit/cancel). Entry 0 selects the stat list;
  entry 1 is the chip branch; cancel or any other result closes.
- **Stat list**: opening it sends `RECALCPLAYER(false)`, which publishes stats *without equipment
  bonuses*, then shows each price in `STWINFONT19` (`----` and the capped colour at 9,999 /
  99,999). Highlight changes run `txt_shop.lua` with `selected+1154`. Selections 0..6 are
  TSUYOSA, MAMORI, KASHIKOSA, SEISHIN, SUBAYASA, MHP, MMP using UPCNT slots 2,3,4,5,6,0,1.
- **Price**: `n = wrap32(stat-45)`, `q = n/5 + (n%5 != 0)` (toward zero), negative → 1, cap 400;
  zero stays zero. Verified against the documented boundaries.
- **Quote**: at or above the cap shows notice 1162, an unaffordable stat 1161; otherwise the
  prompt `11730 + 5*k` (k = stat index) with `+1` and the remaining XDATA in `STWINFONT41`. Quoting spends
  nothing.
- **Confirm**: entry 0 commits. The *current* stat is re-read and priced, XDATA is debited with
  32-bit wrap, the UPCNT slot is incremented, the player is recalculated **with** equipment and
  HP/MP are set to MHP/MMP, all on a private copy published together. `SUBWND UPDATE` follows,
  then the success notice (1165) and the continue question (1166).
- **Close**: `RECALCPLAYER` (with equipment) and HP/MP restore, then children close; the shared
  SUBWND restoration returns the world, audio and player control.

## Chip branch (beNDMWShopCtrlXdataChip 43aae0)

Main-menu entry 1 adds the chip window as a child of the controller (retail `child(…3b6940)`), and
the controller returns to its menu when that child finishes. The window follows the recovered
phases ([chip controller](../../docs/engine/chip-controller.md)):

- **List**: the player's DEVICEFOLDER chips (kind 3) in inventory order, twelve per page, shown in
  `STWINFONT14` (name) and `STWINFONT17` (`NEXTX`, or `----` below one), page labels in
  `STWINFONT30` and the highlighted row's `TXT` in `STWINFONT29` (`dw4_statuscontent_xdata_chip`).
  The `j_shwin` `SQ_XDATAITEMOPEN` window, the prompt (`txt_shop` 1110) and the `i_stcursorleft/right`
  arrows (`-146,25` / `236,25`) are tracked by one content owner. Paging uses `dw4_statuspage_turn`
  and `dw4_statusview_selector_restart`; an empty inventory shows notice 1169 and closes.
- **Quote**: `NEXTX` -1 gives notice 1170 and an unaffordable chip 1161. Otherwise an *equipped* chip is
  previewed on a private copy (record+1, equipment lists re-projected from their references,
  recalculated) and its staged stats go to the STATUS comparison owner; the dialog shows the
  next level's name, the first positive attribute of that level (prompts 11765, 11769, ... by stat)
  and the remaining XDATA. Quoting spends nothing.
- **Confirm**: a two-entry prompt (1171). `SUBWND OFPREVIEW` is always sent; entry 0 runs
  `dw4_playertransactions_chip_upgrade`: debit `NEXTX` (32-bit wrap), record+1 in DEVICEFOLDER,
  equipment projections follow, recalculate, publish together, then `SUBWND UPDATE` and the list
  restarts. Eligibility is not repeated at commit, as in retail.

## Verification (all headless)

- `make -C port check-hubtalk`: from the normal Central runtime, stick-walks a BFS-derived route to
  `n_digilfm[1]` (the NPC wakes by proximity), talks with the real probe, accepts the XDATA prompt
  and checks: main menu texts; every price against the live records; quote texts; no spending
  at quote; accept → exact XDATA debit, UPCNT +1, recalculated TSUYOSA +1 including equipment,
  HP/MP = MHP/MMP; decline unchanged; insufficient balance and capped stat refuse without
  charging; close restores control and input. Fixtures: the XDATA balance and, for the cap case,
  one UPCNT counter.
- `check-hubtalk` also drives the chip branch: equipped buy (record+1 and its pocket copy), decline,
  insufficient balance, a fully upgraded chip and an empty inventory.
- `make -C port check-playerinit`: chip preview isolation and upgrade atomicity (injected failure,
  non-chip and out-of-range index refused, equipment re-projection); price boundaries, selector mapping, atomic upgrade for all seven
  stats, injected recalculation failure leaves the record untouched, undefined selectors refused.
- `make -C port check-playerstats-retail`: 1,760 cases (440 with the false flag) against retail
  `3fab90`.

## Retail observations (PCSX2)

A level-99 save has story flag 1 on, so the Central XDATA Digi-Elf (`n_digilfm` slot 1, the "Data Keeper") only talks
(chunk 53 of the Central pack branches on `FLGisOn(1)`). Clearing flag 1 in live memory (the runtime flag table is a
1,024-byte 0/1 array in the heap, `0x7deef8` in that session; heap addresses change between states) makes it run its menu
branch: four introduction lines, then "View X Data Keeper Menu." / "Exit X Data Keeper.". Opening it shows the XDATA main
menu "Increase Digimon Parameter." / "Increase Ability Chip Parameter." / "Return to Main Lobby." beside the player's
stat panel (name, species, HP/MP, the nine stats, X Data, BITS, Next Level). With no chips in the device folder the chip
entry shows "No Ability Chip" and returns to the menu, matching the port's empty-inventory notice. The equipped-chip quote: a Wisdom Chip γ bought at the Chip Shop and equipped at the Digi-Lab (Exchange Weapon Unit,
first weapon socket, Edit Slot, Equip Ability Chip; plain STATUS Equipment cannot edit mods) lists as "Wisdom Chip γ" with 2400
in the Data column, and its quote reads "Wisdom Chip γ+120 / Wisdom 360 Remaining 7599 Data / OK?" with the continue arrow; the
left panel keeps its values (the capture character's Wisdom is already 9999, and the Data row is not previewed: it stays 9999
while the quote's Remaining shows the balance after the charge), as in the port's quote frame. Avoid Circle after leaving the lab: it reaches the log-out/save screen.

The raised-stat reference: a Dorumon Lv 40 with a bought Wisdom chip (upgrade cost 2400, +120 step) equipped,
written to a copy of the card with the port's save writer and called in retail, shows on the Data Keeper chip quote: Wisdom 600 -> 720 in cyan,
every other stat unchanged, the X Data row unchanged (6000), and the quote line "Wisdom 360 Remaining 3600 Data" (6000 - 2400). The panel
read 3074 HP and 418 Strength. `test_hubtalk` (`chip_projection`) reproduces exactly those figures from the same recipe. The projection is a
recalculation of the record, not the displayed value plus the step: lowering the live Wisdom value in memory (a heap copy of the stat
array, with the chip equipped) gives a projected stat that is not a reference (Wisdom 4907 in that capture).

With one chip in the folder (Assault Ram γ, bought for 24,000 BITS) the retail chip list shows the header "Ability Chip.",
a second column headed by the X Data symbol and "Data", the chip row, `----` in the cost column (cannot be powered up), the
page label "1/1" and the highlighted chip's description in the bottom panel ("Critical Rate up / Equip with WU only /
Cannot power-up with X data"). Selecting it shows "This Ability Chip cannot be increased." (the port's NEXTX -1 notice)
and returns to the list.

With a full folder the list shows twelve rows on page "1/2" with a page arrow, `----` for non-upgradable chips and 2400
for the upgradable ones; the highlighted chip's description reads e.g. "Strength up 240 pts. / Equip with WU only /
Power-up with X data OK". Selecting "PWR Medal γ" (cost 2400) shows the quote "PWR Medal γ+120" / "Strength 360" (cyan)
"Remaining 7599" (orange-red, 9999-2400) "X Data" / "OK?", then a two-entry confirmation, "Increase this Ability Chip's
Parameter." / "Choose another Ability Chip."; the second entry returns to the list with nothing spent. The port's quote
has the same layout and colours. The stat list shows "Parameter" and "Data" columns with `----` and orange names for
stats at the 9,999 cap, the prompt "Select the Parameter you want to increase." and a per-stat description.

Window chrome: retail draws the XDATA windows over the green `j_shback` backdrop with the player's STATUS
panel on the left, the "Data Keeper" header (with the Select/Confirm/Cancel legend) and the bottom message window. The port builds the
same root ([shop root](shop-root.md)): frames agree in layout and text, and the chip quote's stat preview shows in the left panel
(e.g. Wisdom 95 -> 125 in cyan). Remaining visible difference: the chip list's cursor is a small dot in the port at capture time and
a green diamond in retail; no pixel comparison was made.

## Boundaries

- The chip quote's stat-preview comparison is shown in the shop root's player panel; the quote's text colours match the retail
  capture.
- Retail's undefined out-of-range selector (reads an incoming register) is refused instead.
- The shared SD layer treats a numeric fifth argument as a delay, so the optional RECALCPLAYER
  boolean is sent as the data string `TRUE`/`FALSE`; this is a native encoding of the retail
  messenger bool, not a Lua-visible form.
- Rendering is only sanity-checked: `check-hubtalk` draws the stat list and quote through the
  headless CPU reference path (asserting triangles and lit pixels; running `build/test_hubtalk <extracted> <dir>` also
  writes PNGs). The captures were inspected and show the original *Parameter* list with the
  seven prices, the *Data* header, the description/prompt text and the quote dialog (`+1`,
  `Remaining`, `Data`, `OK?`). No retail pixel comparison was done; the frames also match the GLES3 GPU backend on hardware ([lobby rendering](lobby-rendering.md)), and the
  text colours of the quote are unverified. Controller-level retail instruction parity is covered by
  the recovered reference oracles, not by these native tests.
- Only player 0 is wired in the hub; local co-op shop ownership is not addressed.

## Arena control state

ShopCtrl10 and ShopCtrlXdataChip retain counters, selections, menu/parameter and page/cursor fields in their concrete arena instances. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).

## Arena filtered chip identities

ShopCtrlXdataChip `_itemBaseList` retains the actual filtered inventory item
objects. Its transaction index map is derived from inventory order, while
names/prices/preview inputs read the typed list projection. Rebuilding acquires
all new references before replacing the old list.
