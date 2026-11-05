# Native NPC bank (hub service)

Central's Digi-Elf `n_digilff` slot 0 offers the bank (SUBWND mode 3, `BANK`). It is reached only
through original data: live Cross probe → the NPC's own script → prompt → `bankshop.lua`, which
restores control, returns the NPC to `SQ_WAIT` and issues `SUBWND GENERATE BANK/I<player>`.
The native window tree then runs the recovered `beNDMWShopCtrl30` update (`428790..429628`) with
the `beNDMWShopCtrlEditBit` money editor (`4332d0`) and the shared `beNDMWStatusCtrlD0` item list.
It shares STATUS/XDATA's scene freeze, restore and `SUBWND UPDATE` stat refresh. The bank is an
**item and money store**, not a currency exchange: items move between `DEVICEFOLDER` (36 records)
and `BANKDEVICE` (96 records), money between `BIT` (wallet) and `BANKBIT`.

## Ownership

| Piece | Source | Role |
| --- | --- | --- |
| Controller | `src/bankshop.c`, `include/dw4/bankshop.h` | `ShopCtrl30` primary/main/sub states, child creation and completion by child count, notices, transfers. |
| Money editor | `src/bankshop.c` (`struct edit`) | `ShopCtrlEditBit`: model, label/prompt scripts, `SHOPSELECT34` digit selector, up/down edit, acknowledgement. |
| Item list | `src/statusdeviceview.c`, `src/statusdevice.c` | The shared D0 list with `bank=1` (96 rows, STWINFONT40 page counter, `txt_shop` 1303). Owner hooks `dw4_statusdevice_window_refresh` (418ac0) and `_close`. |
| Digit text | `src/statuscontent.c` (`dw4_statuscontent_digits`) | `4402e0`/`440110`: seven `STWINFONT25` fonts (`font%03d`, `font01%d`, `font02%d`), zero-padded width. |
| Transactions | `src/inventorydetail.c` | Atomic `dw4_playertransactions_bank_item` / `bank_bit` (capacity, equipped/referenced refusal, reference re-projection). |
| Hub wiring | `src/hubruntime.c` | SUBWND mode 3 factory beside XDATA. |

## Controller (ShopCtrl30)

Field names follow [the XDATA controller](xdata-shop.md): window state is the primary state, `main`
`sub` `flag` are the counters, `_retCode` is the selector result and `menu` (`+84`) is the first
menu's choice. Completion of a child is a change in the child count, as in retail.

| main | Behaviour |
| --- | --- |
| 0 | `ShopSelect01` menu **1350 (0x546)**, three rows: 0 deposit, 1 withdraw, other leaves. A 0/1 result stores `menu` and goes to main 1; anything else closes the window. |
| 1 | Menu **1355 (0x54B)**, two rows: 0 items, 1 money. Items: deposit goes to main 2; withdraw goes to main 6 with notice **0x55E** if the bank is empty, else main 3. Money: main 4 (deposit) or 5 (withdraw). Cancel returns to main 0. |
| 2 / 3 | D0 list (`equip_disable=1`, `auto_close=0`; `bank=1` when withdrawing) and prompt **1357** / **1364**. A cancel (result -1) closes the list, hides the prompt and waits for its removal. A selection acts only while the list is held ready: **deposit** refuses with notice **0x54E** at 96 bank records, otherwise moves an unequipped item; **withdraw** refuses with **0x555** at 36 inventory records, otherwise moves the item and, if the bank is now empty, refreshes the rows and shows **0x55E**. After a move the list restarts. After a notice the list is closed and main 0 resumes. |
| 4 / 5 | The money editor. When it ends with an amount other than -1, BIT/BANKBIT are updated (no validation in retail; the native transaction validates) and `SUBWND UPDATE` is sent. |
| 6 | One-choice notice (**0x55E**) and return to main 0. |

Primary state 2 closes (no extra work here) and state 3 waits for the children to disappear.

## Money editor (ShopCtrlEditBit)

- **Resources**: model `j_shwin` `SQ_BITPUTINOPEN` (deposit) or `SQ_BITDRAWOUTOPEN` (withdraw); tracked
  `STWINFONT36` fonts 0..1 (0..2 for withdraw); `txt_shop` **1301**/**1375** (labels); tracked
  `STWINFONT29/font100` and prompt **1360**/**1367**.
- **Limit**: deposit `min(BIT, 9,999,999 - BANKBIT)`; withdraw `min(BANKBIT, 9,999,999 - BIT)`.
- **Display** (`STWINFONT25`): deposit shows the amount in `font00x` and the bank balance in `font01x`;
  withdraw shows the amount in `font01x`, the wallet in `font00x` and the bank in `font02x`.
- **Editing**: the `SHOPSELECT34` selector (variant 0 deposit, 1 withdraw) moves a cursor over seven
  digits; `dw4_statusbit_edit` (the same digit logic as the STATUS currency controller) applies
  up (wins over down) and down at the cursor place when `SELECTCTRL i_stcursor03 ISSELECTNOW` is
  true, clamped to 0..limit; a changed place redraws, a changed value also plays `CURSOR_MOVE`.
- **Finish**: Cross with a positive amount publishes it as the parent's result, hides the prompt and
  shows an acknowledgement (**0x552** / **0x559**); Circle or a zero amount publishes -1.
  The transfer happens in the parent *after* the acknowledgement closes.
- The selector keeps a move latch that clears only on a later input frame, so the first cursor tap
  after a move is consumed; this is faithful, not a defect.

## Verification (all headless)

- `make -C port check-hubbank` (`tools/test_hubbank.c`): reaches the NPC by the real Cross probe
  and scripts, then covers money deposit (digit editing, acknowledgement-before-transfer, exact
  balances, menu return, restored control), withdraw clamped by the bank and by wallet room, limit
  clamp / Circle / zero-amount cancel, item deposit, cancel, withdraw to empty with its notice, an
  empty-bank notice, a full-bank deposit refusal and a full-inventory withdraw refusal. Running
  `build/test_hubbank <extracted> <dir>` also writes PNG captures of the editor, the withdraw editor
  and the item list.
- `make -C port check-playerinit`: the transactions (capacity, equipped refusal, reference
  re-projection after a deposit, money bounds at 9,999,999, invalid flags/indices).
- `make -C port check-hubnpcs` classifies the NPC as an implemented service.

## Boundaries

- Mode 2 of `EditBit` (`txt_shop` 1378, `STWINFONT36` only; the junk-shop donation) is exported as
  `dw4_bankshop_editor_open` and documented in [equipment shops](equipment-shops.md).
- The deposit test `item+0x10 == 0` is taken to be the item's equipped flag (D0's equip-disable
  byte makes such rows unselectable anyway); equipment references to the item also refuse.
- Label and prompt strings come from the original `txt_shop.lua` messages; their colours, the exact
  digit-font geometry and the `ShopSelect34` cursor art were checked only against the authored
  resources and rendered captures, not compared pixel-for-pixel with retail.
- Only player 0 is wired in the hub; local co-op ownership is out of scope.
- Retail does not validate the transfer amount; this port's transaction does and fails the window
  if a record changed so that the transfer is invalid.

## Arena control state

ShopCtrl30 and ShopCtrlEditBit retain counters, return/count snapshots, bank menu and edit mode/amount/limit in their concrete arena instances. The editor returns through its parent window handle. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).
