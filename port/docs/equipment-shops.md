# Native weapon, armor, chip and junk shops (hub services)

The Shop's Digi-Elves and its junk clerk offer four more services, all in `stagML13`. Each is reached only
through original data: live Cross probe → `hit_<npc>.lua` → the NPC's talk script → a prompt → the shop script
(`wpu`, `apu`, `chip` or `junkshop.lua`), which restores control, returns the NPC to `SQ_WAIT` and issues
`SUBWND GENERATE <MODE>/I<player>`.

| NPC (slot) | Mode | Service | Retail root |
| --- | --- | --- | --- |
| `n_digilfm[0]` | 6 `WPU` | weapon units | `beNDMWShopDevice` `43cc20` |
| `n_digilff[1]` | 7 `APU` | armor | `beNDMWShopDevice` `43cc20` |
| `n_digilfm[1]` | 8 `CHIP` | ability chips | `beNDMWShopDevice` `43cc20` |
| `n_metete[0]` | 9 `JUNK` | junk parts and the investment tiers | `beNDMWShopJunk` `42bc70` |

`n_metete`'s first conversation is an introduction; the shop is offered from the second. The native window tree
then runs the recovered controllers. They share STATUS/XDATA's scene freeze, restore and `SUBWND UPDATE` balance
refresh.

## Ownership

| Piece | Source | Role |
| --- | --- | --- |
| Roots, goods list and flows | `src/equipshop.c`, `include/dw4/equipshop.h` | `ShopDevice` / `ShopJunk` primary/main/sub states, `ShopCtrlSales` (goods list, preview, confirmation, purchase), child creation and completion by child count. |
| Stock | `src/shopstock.c`, `include/dw4/shopstock.h` | The recovered stock selection (`3d8740`) with the item rolls `448190` / `4480a0`; the four work lists persist in the hub runtime. |
| List text | `src/statuscontent.c` | `dw4_statuscontent_sales` (`4393e0`). |
| Price | `src/playerstats.c` | `dw4_playerstats_item_price` (`447ed0`): HANBAI / KAITORI with enhancement and grade surcharges. |
| Transactions | `src/playertransactions.c` | Atomic `dw4_playertransactions_shop_buy`, `junk_donate` and the equip-candidate `equip_preview`. |
| Sell branch | `src/diskshop.c` | `dw4_diskshop_sell_window_open` (the DISK `ShopCtrlSell` branch, shared). |
| Donation editor | `src/bankshop.c` | `dw4_bankshop_editor_open` mode 2 (`ShopCtrlEditBit`, shared with the bank). |
| Hub wiring | `src/hubruntime.c` | SUBWND modes 6–9: runs the stock selection, then opens the root; `dw4_hubruntime_shopstock` is a test accessor. |

Class mapping of the factories the controllers call (each factory sits just before its class's vtable):
`3b4d90` ShopSelect01 (menu), `3b4f50` ShopSelect00 (notice), `3b51b0` StatusSelectE1 (list), `3b6bc0`
ShopCtrlSales, `3b7360` ShopCtrlSell, `3b7520` ShopCtrlEditBit. `ShopCtrlA0/A1/A2` (`42c810`, `42d450`, `42eb80`)
are not on these paths.

## Stock selection (`3d8740`)

Preparation runs when the window is generated. It first caps every joined player's `BIT` at 9,999,999 and `XDATA`
at 9,999, then builds the mode's list unless it already holds entries (a built list persists, so bought slots stay
sold out for the hub session):

| Mode | Table | Row |
| --- | --- | --- |
| 6 | `shopWeapon` | species base 25/50/75/100/125/0 (150 with two or more joined players) + level tier (24 thresholds) |
| 7 | `shopArmor` | level tier (29 thresholds); columns 00–11 blue armor, 12–35 yellow armor or null |
| 8 | `shopChip` | level tier (29 thresholds) |
| 9 | `shopJunk` | common `COUNTER[1]` investment tier (1,000 … 3,956,000); below 1,000 the list is empty; each entry's kind is the `NNkind` column |

A column that is absent or holds -1 is retail's missing sentinel: null slot (omitted for junk). Weapons and blue
armor roll a pocket count and every weapon or armor an enhancement from the engine's MT stream, in column order
(`dw4_shopstock_pocket_roll`, `dw4_shopstock_revision_roll`); chips take no draws. A purchased slot is replaced by
the sold-out chip (record `0xB9`, name "Sold Out").

The junk stock is `DATABASE.$shopJunk` in `NDMW.AFS` entry 828, `beDataBase` id 1170: 9 rows, one per investment
tier, of 36 `(kind, value)` columns named `NNkind`/`NN` in `_shortOffsetList`. Kind 0 is a weapon id (grade E), 1 a
core index (id = 4096 + v), 2 a board index (id = 8192 + v). Tier 1,000 offers Filter Board; each later tier adds
items, up to cores 4123-4125 at 1,956,000 and Talis of Order (core 4126) plus Talis of Chaos (board 8235) at
3,956,000.

## Roots

- **Device root (6–8)**: a three-entry menu (calls `0x672` / `0x6D6` / `0x73A`: buy, sell, leave). Entry 0 opens the
  goods list, entry 1 the shared sell branch; a finished child returns to the menu.
- **Junk root (9)**: menu `0x79E` (donate, buy, leave). Donate opens the editor (mode 2), buy the goods list.

## Goods list (`ShopCtrlSales`, `438160`)

- Page count is `ceil((last present slot + 1) / 12)` (the list size when nothing is present, so an empty stock has
  0 pages and reads `0`); a page lists its leading present slots (1–12 rows). A null or sold-out row is disabled.
- Rows show the item's `NAME` in its rarity colour and the `HANBAI` price (or `----` for the sold-out chip); the
  page labels are in `STWINFONT30`. The highlighted slot adds its `TXT` (plus the pocket digit for weapons and blue
  armor). The stick turns pages with `i_stcursorleft/right`; the list returns to the page it was on.
- **Preview**: the highlighted item replaces the equipped weapon / blue armor / yellow armor on a private copy, the
  player is recalculated and the staged folder goes to the STATUS comparison owner (`ONPREVIEW`); `OFPREVIEW` is sent
  when nothing is highlighted and whenever the list closes. Records are never changed.
- **Choosing a slot**: a full `DEVICEFOLDER` (36) shows notice `0x686`, a short balance `0x622`. Otherwise the item's
  usability is checked (weapon: the Digimon is in its `SOUBI` mask and its `SKILL` level reaches `SKILLPOINT`; armor:
  `LEVEL >= LVPOINT`; chips always): usable gives the sentence `0x677` / `0x6DB` / `0x73F`, unusable the warning
  `0x7F8`; then a yes/no (`0x678` / `0x6DC` / `0x740`). Yes debits `BIT`, appends the stock item to `DEVICEFOLDER`
  and sells the slot out, then `SUBWND UPDATE`.

## Junk donation (editor mode 2, `4332d0`)

The editor is the bank's digit editor with `j_shwin SQ_JUNKOPEN`, one tracked `STWINFONT36` font and `txt_shop` 1378.
The limit is `min(BIT, 999,999,999 - BIT)`. A confirmed amount shows the question `0x7A9` ("Do you want to donate this
amount?"), which waits on Cross, then the Donate/Choose-another choice (`0x7AA`); Choose another gives -1. A completed donation adds the amount to the common `COUNTER[1]` and debits `BIT` in one
publication and sends `SUBWND UPDATE`. If a tier threshold lies above the investment remembered when the shop opened
and at or below the new one, the named chunk `junkexit.lua` runs and notice `0x7B2` ("Item development will start.")
precedes closing the shop.

## Price (`447ed0`)

`HANBAI` (buy) or `KAITORI` (sell) plus `revision * 100` (buy) / `* 25` (sell) for weapons and armor, and for
weapons and blue armor a grade table indexed by the pocket count (buy `0,500,1500,6000,12000,24000`, sell
`0,250,750,3000,6000,12000`); yellow armor adds only the revision; chips are unmodified. The shared sell lists
(including the DISK shop's) use it.

## Verification (all headless)

- `make -C port check-hubshops` (`tools/test_hubshops.c`): reaches each NPC by the real probe and scripts. WPU: the
  stock rows against the hub tables (names and prices), decline, insufficient balance, a full folder, a purchase
  (exact debit, the stock object appended with its roll, slot sold out), and a sale of an enhanced weapon at
  `KAITORI + 50 + 3000`. APU: blue/yellow stock, page turn and label, a page-two purchase, the return page. CHIP: the
  gap in the chip table and a purchase. JUNK: editor digits, cancel, decline, a confirmed donation, the tier
  notice with `junkexit.lua`, the empty stock below 1,000 and the first tier's purchase. Captures can be written by
  passing a directory.
- `make -C port check-playerinit`: price boundaries, rolls and level/investment rows, atomic purchase, preview
  isolation and the donation transaction.
- `make -C port check-hubnpcs`: the four NPCs count as implemented services.
- `make -C port check-statuscontent-retail`: the list helpers' oracle (its stubs cover `dw4_playerstats_item_price`, which the shop goods and sell lists call).

## Retail comparison

Disk sell prices are buy/4 rounded down; `Not enough BITS.` comes after the quantity step; the retail typo
`Abiliy Chip?` is original; per-row weapon prices differ by a random roll in both retail and the port. The junk
donation runs the same sequence as retail: the `0x7A9` question, Cross, then the choice. Not reached on retail: the
folder-full notice, the Device Folder sell list, the `Buy Junk Parts` list, Digi-Lab, Bank and Appraiser.

## Boundaries

- The window code is recovered from decoded m2c drafts, rodata and tables, not matched source. Retail's exact
  instruction timing and the base-window virtuals (page arrows, `+0x60/+0x64/+0x68`) are reproduced from the chip
  list's recovered shape.
- Unverified: the goods list's colour reset after close, the digit selector placement for editor mode
  2 (the deposit placement is used), the observable effect of `junkexit.lua`, and the preview's stat panel (not shown
  by these windows). No retail pixel comparison and no hardware-GPU run was done.
- APU columns 00–11 that lack a blue-armor entry would construct a record -1 in retail; the native stock refuses
  such a table with a named error (the shipped tables have all twelve).
- Item rolls follow the recovered formulas and the engine stream, but the stream state at a real visit differs, so
  individual enhancements are not comparable with a retail session.
- Only player 0 is wired in the hub; local co-op shop ownership is not addressed.

## Arena control state

ShopDevice, ShopJunk and ShopCtrlSales retain counters, selections, list pages/cursors and the junk gift threshold in concrete arena instances. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).

## Arena stock and item references

The persistent stock owner holds `beNDMWStatusInfoWork`: four typed
`beNDMWItemBaseList` payloads, the two constructor-declared integer buffers and
`_junkGift`. `_parameter` holds the thirteen STATUS comparison values; it is not
a player-folder reference. See [its ownership](arena-object-model.md#action2-hit-volume-and-stat-comparison-records).
The hub binds it to SUBWND RAM `_work`. The public stock facade owns handles;
item arrays are borrowed projections. Generation publishes a complete list;
a sold-out slot replaces its actual item reference and invalidates that view.
Root and Sales controllers retain their actual stock lists. Sales decisions
are `igBoolList` bytes. The item factory is shared with player records, and
all retained references release through their recursive owner API. Stock
persistence, prices, draws, purchase ordering and admission are as described above.

## Open questions

- The colour of a price the player cannot afford is unverified against retail. `4393e0` applies none.
