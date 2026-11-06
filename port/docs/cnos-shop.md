# Native NPC appraiser (hub service)

Central's third Digi-Elf, `n_digilfm` slot 2, offers the item appraiser (SUBWND mode 4, `CNOS`). It
is reached only through original data: live Cross probe → the NPC's own script → prompt →
`SUBWND GENERATE CNOS/I<player>` (`entry_0824` chunk 60). The native window tree then runs the
recovered `beNDMWShopCtrl40` update (`429630..42a2d8`) over the shared `beNDMWStatusCtrlD0` item
list. It shares STATUS/XDATA's scene freeze, restore and `SUBWND UPDATE` balance refresh. The service
takes an *unidentified* piece of equipment (the `??????` placeholders weapon 276, armor1 31 and
armor2 44), charges 300 BIT and replaces its record with a randomly drawn real item of a tier chosen
by the player's level. The list prompt reads "Select the item to be appraised."

## Ownership

| Piece | Source | Role |
| --- | --- | --- |
| Controller | `src/cnosshop.c`, `include/dw4/cnosshop.h` | `ShopCtrl40` primary/main/sub states, child creation and completion by child count, notices, the conversion. |
| Item list | `src/statusdeviceview.c`, `src/statusdevice.c` | The shared D0 list with `unknown_enable=1` and `auto_close=0`; only rows decided as unknown equipment are enabled. |
| Tier, roll and conversion | `src/playertransactions.c` | `dw4_cnos_tier`, `dw4_cnos_roll` and the atomic `dw4_playertransactions_cnos_convert`. |
| Draw | `src/random.c` | The engine's shared MT19937 stream (retail `genrand`, vtable slot 24), owned by the hub state. |
| Hub wiring | `src/hubruntime.c` | SUBWND mode 4 factory beside XDATA and BANK; `dw4_hubruntime_databases` for the reroll tables. |

## Controller (ShopCtrl40)

Field names follow [the BANK controller](bank-shop.md): the window state is the primary state, `main`
and `sub` are the counters, `_retCode` is the selector result and the selected `DEVICEFOLDER` index
is kept at `+54`. Completion of a child is a change in the child count, as in retail.

| State / main | Behaviour |
| --- | --- |
| 0 | Prepares `STWINFONT29/font100` (the prompt box) with `3f5410`'s blank string and `LEFT` alignment, then starts at main 0. |
| main 0 / sub 0 | Opens the D0 list (`+6d`=1 unknown-only, `+6f`=0 no auto close) and runs `txt_shop` **1450** into the prompt box. |
| main 0 / sub 1 | A `-1` result goes to main 3. Once the list is held ready the selection is stored, `BIT` is read and the prompt hidden: `BIT` below **300** goes to main 2, otherwise main 1. |
| main 1 | `ShopSelect00` call **0x5AC** (1452, a one-entry confirmation), then `ShopSelect01` call **0x5AD** (1453, two entries). Entry 0 (yes) converts; either answer restores the selection, restarts the list and returns to main 0 / sub 1. |
| main 2 | `ShopSelect00` call **0x5AB** (1451, the insufficient-BIT notice), then main 3. |
| main 3 | Closes the list and waits for it to disappear, then advances the primary state. |
| 2 / 3 | Clears the queued text, requests the children to close and waits for them. |

## The conversion

- **Charge**: 300 BIT (`0x12C`), debited whether or not the draw lands on an entry.
- **Tier** from `LEVEL` with signed compares: below 41 → 1, below 101 → 2, below 201 → 3, below 301 → 4,
  below 401 → 5, otherwise 6.
- **Table** by item kind: `coweapon` (0), `coarmor1` (1), `coarmor2` (2). Row `tier*100` holds the entry
  count in its `ID` column; rows `tier*100+1..count` hold a result record `ID`, a `RATE` weight and a
  `RANK` (read by retail and discarded). The tables are numeric-only in the Central hub's database owner.
- **Draw**: one `genrand` word modulo 10000 (unsigned). The first entry whose running `RATE` sum is greater
  than or equal to the draw becomes the item's record; if none reaches it the record is unchanged. The
  tables' totals are below 10000, so a miss is possible and still costs 300 BIT.
- **Commit**: the debit, the new record and the equipment re-projections publish together
  (`dw4_playertransactions_cnos_convert`); an item that is equipped follows the new record. Stats are not
  recalculated (retail only sends `SUBWND UPDATE`).

## Verification (all headless)

- `make -C port check-hubcnos` (`tools/test_hubcnos.c`): reaches the NPC by the real Cross probe and the
  original scripts, then covers a weapon, an armor1 (second row, tier 6) and an armor2 conversion
  (BIT debit, record drawn from the authored tier row or unchanged, prompt hidden during the dialogs,
  list restart, cancel and restored control), declining at the yes/no menu, the insufficient-BIT notice
  (BIT 299), a list with no selectable row (ordinary equipment and a chip: Cross does nothing) and an
  empty inventory. Fixtures are BIT, LEVEL and the `DEVICEFOLDER` list; the hub's own random stream
  supplies the draw, so results are checked as members of the authored row set.
- `make -C port check-playerinit`: level-tier thresholds at every boundary, running-sum boundaries
  (draws 0/100/101/300/301/600/601/9999), empty, invalid and missing-row tables, the 300 BIT refusal,
  invalid index/kind/table arguments and projection of an equipped item. These pin exact draws, which the
  hub test cannot.

## Boundaries

- The window's initial `_retCode` is an inference: retail would close on its first update
  if the field started at `-1`, so it is taken as zero-initialised memory. The base window constructor was
  not traced.
- An empty inventory is unreachable in retail; there the list's single blank row would publish index 0.
  The native window ignores a selection that is not a weapon or armor and restarts the list.
- `SUBWND UPDATE` is issued after the atomic commit rather than between the debit and the record write;
  nothing reads the record in between.
- Rendering is only sanity-checked through the headless CPU reference path (the capture shows the
  *Device Folder* list, the `??????` row, the description and the "Select the item to be appraised."
  prompt). No retail pixel comparison and no hardware-GPU run was done.
- Only player 0 is wired in the hub; local co-op shop ownership is out of scope.

## Arena control state

ShopCtrl40 retains counters, selected inventory cursor and return/count snapshots in its concrete arena instance. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).
