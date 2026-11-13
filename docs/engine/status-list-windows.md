# Status screen list windows

`src/game/beNDMWListCtrl.cpp` is one translation unit: the shared `beNDMWListCtrl` page methods and the
status screen's controller windows. Every window is a `beNDMWWindow` whose `Update` slot (21) runs a
step machine on `_st0`..`_st3`: `_st0` is the phase (0 open, 1 run, 2 close, 3 wait for the close),
`_st1`/`_st2` are nested steps and `_st3` a per-step scratch value. Entering a step clears the levels
below it. A window that opens a child records the child count in `_nowProcKazu`; the child has
finished when the count changes, and its result is in the parent's `_retCode`.

## Windows

| Window | Update | Role |
| --- | --- | --- |
| `beNDMWStatusCtrl00` | `beNDMWStatusCtrl00_Update` | Status root: hides the field layers (LAYERCTL `BG01`..`GM03`), opens the titles, runs the status menu and opens equipment, folder or skill. |
| `beNDMWStatusCtrlEquip` | `beNDMWStatusCtrlEquip_Update` | Equipment menu; `_entCode` 0 is the status screen, 1 a shop. Opens a power socket, main slot or sub slot panel. |
| `beNDMWStatusCtrlBaseEquip` | `Gap__Bec__beNDMWStatusCtrlBaseEquip__vfunc_21` | Shared panel update: loads the player's slot lists and drives the panel slots below. |
| `beNDMWStatusCtrlD0` | `beNDMWStatusCtrlD0_Update` | Device folder list, twelve rows a page, filtered by `_kindList`. |
| `beNDMWStatusCtrlFolder` | `beNDMWStatusCtrlFolder_Update` | Folder menu: device folder, flags, disks, bits. |
| `beNDMWStatusCtrlFlag` | `beNDMWStatusCtrlFlag_Update` | Important-item (flag folder) list. |
| `beNDMWStatusCtrlDisk` | `beNDMWStatusCtrlDisk_Update` | Disk list: reorder, and send disks to another player. |
| `beNDMWStatusCtrlBit` / `beNDMWStatusCtrlSendBit` | `beNDMWStatusCtrlBit_Update`, `beNDMWStatusCtrlSendBit_Update` | Sending bits (money) to another player, edited digit by digit. |
| `beNDMWStatusCtrlSkill` | `beNDMWStatusCtrlSkill_Update` | Evolution list, skill points and technique list. |
| `beNDMWStatusSubMenu` | `beNDMWStatusSubMenu_Update` | Device sub-menu: discard, sort (`beNDMWStatusSubMenu_SortByRevision`, `beNDMWStatusSubMenu_SortByRecordNo`), give to another player. |

Each class's slot 20 is its `_GetMeta`, returning the class handle.

## Equipment panel slots

`beNDMWStatusPowerSocket`, `beNDMWStatusMainSlot` and `beNDMWStatusSubSlot` derive from
`beNDMWStatusCtrlBaseEquip` and implement slots 22..39, which the base update calls by position:
`RefreshPocket` (22), `PresentPanel` (23, open flag), `RefreshSlotList` (24), `OpenSlotList` (25),
`ShowSlotDescription` (26), `OpenSlotMenu` (27), `OnSlotMenuDecided` (28), `OpenDeviceFolder` (29),
`CanEquip` (30), `EquipSelected` (31), `PreviewSlotDevice` (32), `OpenPocketList` (33),
`ShowPocketDescription` (34), `OpenPocketMenu` (35), `OpenPocketFolder` (36), `EquipPocket` (37),
`ClearPocket` (38) and `PreviewPocketDevice` (39); for example `beNDMWStatusPowerSocket_CanEquip`
and `beNDMWStatusMainSlot_RefreshSlotList`. The sub slot has no pocket: its slots 33..39 are empty.

`beNDMWStatus_AssignEquipment` equips a device-folder entry into a slot list (toggling it off when it is
already there, and clearing other entries of the same family); `beNDMWStatus_PreviewEquipment` makes the
same change temporarily to publish the ONPREVIEW stats and restores it. The power socket's first
item is a power chip whose `_pocket` (`beNDMWItemBlueArmor`) gives the number of pocket lines.
`beNDMWStatusCtrlBaseEquip_PreviewSocketSwap` previews swapping two sockets,
`beNDMWStatusCtrlBaseEquip_ShowKindCursor` moves the `i_stcursor04` cursor and
`beNDMWStatusCtrlBaseEquip_QueuePanelText` queues the panel's text cells.

The text-refresh helpers `beNDMWStatusCtrlD0_RefreshText`, `beNDMWStatusCtrlFlag_RefreshText`,
`beNDMWStatusCtrlDisk_RefreshText` and `beNDMWStatusCtrlSkill_RefreshText` take two flags: rewrite the
rows, and rewrite the description of the selected row. `beNDMWStatusCtrlD0_UpdatePageCount` sets
`_maxPage`, fills `_decideList` for the current page and returns its row count;
`beNDMWStatusCtrlD0_GetSelectedIndex` is the absolute index of the selection (-1 for none).

## Source shapes

Player records are `beDataObj*` objects: `igProperty_GetRecordFolder` returns a `beDataObjObjectList`
whose `_data` is the object list, `igProperty_GetRecord` a `beDataObjInt`, and so on.

A bool passed to the list `append`/`set` helpers by `const bool &` becomes a one-byte `.sdata` constant
per call (the `0x5549f8`..`0x554a34` words); a literal `int` would be a `.rodata` word. Local
`const char *` arrays initialised from string symbols are copied from a `.data` template (the
`SQ_OPENnn` cursor sequences at `0x4cf6a0`). Both are anonymous `@N` objects whose
`unit-objects.json` rows are re-derived after every source edit.

Small accessor templates can change register allocation where a macro does not: the child count
is the `CHILD_COUNT` macro for that reason, and the reference release keeps its 64-bit mask form
(`RELEASE_REFERENCE`) where retail tests the count that way.

## Open questions

- Slots 22..24 of `beNDMWListCtrl` and slot 21 of `beNDMWStatusCtrlBaseEquip` keep their generated
  `vfunc_NN` names (`config/SLUS-20836/names/Vtables.tsv`); their roles are the page-arrow setup,
  previous page, next page and the panel update.
- `OnSlotMenuDecided` calls `EquipSelected` with two leftover argument registers; whether the slot had
  parameters is unknown.
- The int words at `0x4cf6d0`..`0x4cf6f0` (device kinds 0, 3, 1, 3, 2 pushed to `_kindList`) and the
  remaining copied tables (`0x4cf700`, `0x4cf730`..`0x4cf790`) are probably literal temporaries and local
  array templates like the ones above; they are still declared as data.
