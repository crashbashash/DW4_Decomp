# Slot, character, name, difficulty and card controllers: `beNDMWLoadIntf2`

The Game Start path hands off from `beNDMWLoadCtrl2` (see
[title-menu-controller](title-menu-controller.md) §*Recovered load-controller
flow*) into `beNDMWLoadIntf2`, the interface that runs the slot/character/name/
difficulty/memory-card screens before the Main Lobby loads. This page inventories
the module: its runtime block, its object model, its named working set, its
message protocol, the per-screen helpers and where each function's source is.

## Source layout

- The runtime block `0x003e46b0..0x003eba0c` is 36 functions in
  one translation unit, `beNDMWLoadIntf2_3e46b0` in `config/SLUS-20836/units.tsv`.
- Named functions are in `src/game/` and `src/engine/`. Functions that still
  carry a `FUN_` or `Gap__Bec__…__vfunc_NN` symbol are in `src/unmatched/`: their
  names and module placement are not settled.
- What is not recovered is listed under [Open items](#open-items).

Byte sizes on this page are the function extents in
`config/SLUS-20836/symbols.txt`.

## Runtime block

| Start | Bytes | Symbol | Role | Source |
|---|---:|---|---|---|
| `0x003e46b0` | 156 | `Gap__Bec__beNDMWLoadIntf2__vfunc_32` | reference/pad wrapper: takes the pad-manager reference into `_padManager` when it is not set | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e4750` | 18,616 | `Gap__Bec__beNDMWLoadIntf2__vfunc_31` | per-frame update (the master flow) | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9010`–`0x003e93b0` | 19 functions | see the next table | accessors / per-controller helpers | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e93c0` | 12 | `Gap__Bec__beNDMWLoadIntf2__vfunc_30` | MetaObject return | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e93d0` | 88 | `Gap__Bec__beNDMWLoadIntf2__vfunc_29` | descriptor wrapper: registers the record as receiver of `LOADINTF2_ALL` and `LOADINTF2` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9430` | 8,272 | `Gap__Bec__beNDMWLoadIntf2__vfunc_34` | message handler (builds the family, answers the commands) | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003eb480`–`0x003eb980` | 11 × 128 | `FUN_003eb480` … `FUN_003eb980` | destructors of the handler's owning stack references (`CtrlDataRef` … `DiffSelRef`), one class per created child, emitted with the handler | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003eba00` | 12 | `Gap__Bec__beNDMWLoadIntf2__vfunc_20` | MetaObject return | `src/game/beNDMWLoadIntf2.cpp` |

The accessors and per-controller helpers:

| Start | Bytes | Symbol | Source |
|---|---:|---|---|
| `0x003e9010` | 128 | `ObjectRef_Destruct_003e9010` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9090` | 8 | `DataList_GetData_003e9090` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e90a0` | 8 | `beNDMWLoadSavePlWork__SetIsCtrl` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e90b0` | 8 | `beNDMWLoadSavePlWork__GetIsRdy` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e90c0` | 8 | `beNDMWLoadSavePlWork__GetIsEntry` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e90d0` | 32 | `ObjectRef_Retain_003e90d0` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e90f0` | 20 | `DataList_GetWordAt_003e90f0` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9110` | 68 | `ObjectRef_Release_003e9110` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9160` | 188 | `ObjectList_SetAtRetained_003e9160` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9220` | 28 | `FUN_003e9220` (three-float copy, `+0/+4/+8`) | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9240` | 20 | `DataList_GetWordAt_003e9240` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9260` | 20 | `ObjectList_GetAt_003e9260` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9280` | 28 | `FUN_003e9280` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e92a0` | 8 | `FUN_003e92a0` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e92b0` | 124 | `ObjectRef_Assign_003e92b0` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9330` | 48 | `FUN_003e9330` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9360` | 8 | `FUN_003e9360` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e9370` | 56 | `Memory_SelectAllocator_003e9370` | `src/game/beNDMWLoadIntf2.cpp` |
| `0x003e93b0` | 8 | `FUN_003e93b0` | `src/game/beNDMWLoadIntf2.cpp` |

## Object model

Recovered from `data/reflection.json` (layouts in `include/dw4/reflected.h`); the
base of every `…CtrlData`/`…Intf` record is `beBaseInfoData` and every interface
of a manager derives from `beBaseInfoManager`.

| Class | Role (from its recovered field names) |
|---|---|
| `beNDMWLoadIntf2` | Manager: `_system`, `_padManager`, `_kindHard`, `_difficultMax`. |
| `beNDMWLoadIntf2CtrlData` | Master state record: `_isRun`/`_isRdy`/`_isEntry`/`_isCtrl`/`_isCansel`/`_isMesWin`/`_isSystem`/`_isNoSelMdl` (+0x10..), `_newLoadSel`, `_isNewMake`, `_isRdyCancel`, `_oldPadData`, `_st0.._st3` (`+0x24..+0x30`). |
| `beNDMWLoadIntf2SelSlot` | Slot select: `_selMax`, `_selPoint`, `_mcSelPoint`, `_mode`, `_mcStat`, `_isOpen`/`_isSelect`/`_isCansel`/`_isReOpenReq`/`_isEnd`, `_st0.._st3`. |
| `beNDMWLoadIntf2DataSelIntf` | Save-slot data select: `_mcSelPoint`, `_svDataSelPoint`, `_kind`, `_plNo`, `_mesKind`, `_result`, `_isEnd`/`_isCancel`, `_isSaveArea`/`_isUpStatWin`/`_isDownStatWin`/`_isSlotWin`/`_isSelCur`. |
| `beNDMWLoadIntf2ChrDataSel` | Character data select: `_selMax`, `_ramNo`, `_selPoint`, `_mcSelPoint`, `_isCansel`/`_isEnd`, `_st0.._st3`. |
| `beNDMWLoadIntf2MakeChr` | Character creation: `_chaSelDegi` (`+0x30`), `_degiName` char array (`+0x10`), `_nameCur` (`+0x34`), `_mojiSelPoint` (`+0x38`). |
| `beNDMWLoadIntf2NameSel` | Name entry: `_selDataNo`, `_langID`, `_tateMax`/`_tateMin`/`_tatePoint`, `_yokoPoint`/`_yokoCurPos`, `_nameMojiMax`/`_nameCurPos`, `_isEnd`/`_isMakeName`/`_isQuestion`/`_isAnswer`/`_isNameOK`/`_isSideCur`, `_st0.._st3`. |
| `beNDMWLoadIntf2Diffselect` | Difficulty: `_selectPoint`, `_maxSel`, `_plNo`, `_result`, `_kind`, `_isEnd`/`_isCancel`, `_st0.._st3`. |
| `beNDMWLoadIntf2MesWin` | Message window: `_isWinOpen`/`_isWinClose`/`_isSelect`/`_isSystemMes`/`_isMesErase`/`_isMesCom`/`_isCtrl`/`_isDisp`, `_kindCtrl`, `_statCtrl`, `_ramNo`, `_curPoint`, `_mesNo`/`_sysMesNo`/`_sysStat`. |
| `beNDMWLoadIntf2DegiState` | Per-Digimon state display: `_plNo`, `_dispPos`, `_isEnd`/`_isAnmEnd`, `_closeKind`, `_kind`, `_dataNo`, `_isUseData`, `_st0.._st3`. |
| `beNDMWLoadIntf2DegiStateCtrl` / `…List` | Controller / list for the Digimon state rows (`_statDataList`). |
| `beNDMWLoadIntf2ComMdlCtrl` | Common model controller: `_openDataList`, `_closeDataList`, `_pos`. |
| `beNDMWLoadIntf2TextOrder` | Text order: `_messenger`, `_lua`. |
| `beNDMWLoadIntf2Info` | Info record (no own fields). |
| `beNDMWLoadSavePlWork` / `…List` | Save-player work: `_isEntry`/`_isRdy`/`_isClose`/`_isCtrl`/`_isCutConnect`, `_utilReturn`/`_utilNext`, `_isHaveSaveData`/`_haveSaveData`, `_sysStat0..3`, `_sysCount0`. |
| `beNDMWLoadSlotPlayer` / `…List` | Slot player: `_connectNO`, `_saveDataList`, `_accessPlList`. |

### Typed receivers and links

The slot, data-selection and card-utility functions read reflected fields, not
private offset views:

| Receiver | Reached through | Fields used |
|---|---|---|
| `beNDMWLoadIntf2SelSlot` | the `SELSLOT` record passed by the master | `_commonIntf`, `_comMdlCtrl`, `_textOrder`, `_kindHard`, `_ramNo`, `_selPoint`, `_mode`, `_mcStat` |
| `beNDMWLoadCtrl2CommonIntf` | `common` in the master | `_inforam`, `_flagWork`, `_mcUtilCtrl`, `_kindHard` |
| `beNDMWLoadIntf2DataSelIntf` | `dataSelection` in the master | `_comMdlCtrl`, `_textOrder`, `_statDisp`, `_plNo`, `_kind`, `_mesKind`, `_st0`–`_st3`, the window flags |

- `_flagWork` is a `beNDMWLoadSavePlWorkList` whose per-player records hold the
  four step states `_sysStat0`–`_sysStat3`.
- `_mcUtilCtrl` is a `beNDMWMcUtilCtrl` whose `_slot` list holds `beNDMWMcSlot`
  records; the "slot state == 1" test is `_isConnect`.
- `_gameUseData` is a `beNDMWDegiDataList` of the per-player Digimon records, and
  `_haveSaveData` is a `beNDMWLoadSlotPlayer` whose `_saveDataList` holds the
  four save areas.
- The pad words read by `0x003db780` are `bePadData._lTrg/_lRpt/_trigger/_repeat`.
- Unconfirmed: the object behind `_statDisp`, the property block
  `0x003ee6d0` fills (`beNDMWDegiData._data`) and `_svData`'s object have no
  reflected class and stay private views in the sources.

In the master update, slot connection numbers and `_sysCount0` are words; pad
connections, property flags and system/control flags are byte accesses.

## Named working set and message protocol

The message handler builds the family under the record's data list (`+0x28` of
the per-frame context; the interface's kind is at `+8`), addressing each
child by name through the registry lookup `0x003022c0` (`igProperty_FindByName`),
the same lookup `beNDMWLoadCtrl2` uses:

| Name | Token | Child |
|---|---|---|
| `COMMONINTF` | `0x5172a0` | per-player working set (list at `+0x28`) |
| `CTRL` | `0x5172b0` | `beNDMWLoadIntf2CtrlData` (master sub-state) |
| `MAKECHR` | `0x5172b8` | `beNDMWLoadIntf2MakeChr` |
| `COMMDLCTRL` | `0x5172c0` | `beNDMWLoadIntf2ComMdlCtrl` |
| `MESWIN` | `0x5172d0` | `beNDMWLoadIntf2MesWin` |
| `SELSLOT` | `0x5172d8` | `beNDMWLoadIntf2SelSlot` |
| `NAMESEL` | `0x5172e0` | `beNDMWLoadIntf2NameSel` |
| `TEXTORDER` | `0x5172e8` | `beNDMWLoadIntf2TextOrder` |
| `DEGISTATECTRL` | `0x5172f8` | `beNDMWLoadIntf2DegiStateCtrl` |
| `DATASELINTF` | `0x517308` | `beNDMWLoadIntf2DataSelIntf` |
| `DIFFSELECT` | `0x517318` | `beNDMWLoadIntf2Diffselect` |

The update also drives the front-end UI objects/animations by token
(`GAMERAM`, `GETPLAYER`, `MODELCTRL`+`GENERATE`/`ISRUN`/`SQ_ENTR`/`SQ_EXIT`,
`j_chrselmesswin`/`j_linewin01`/`j_linewin02`/`j_digifacewin`/`j_mainstatuswin`
with `SQ_OPEN`/`SQ_CLOSE`/`SQ_CANCEL`/`SQ_LINEON00/01`/`SQ_LINEUP00`/`SQ_LINEDW01`,
`DATABASE`+`GETDATABASE`, …).

Messages: `LOADINTF2_ALL` (`0x5175d8`) starts the whole family; `LOADINTF2`
(`0x5175e8`) the interface alone; `LOADCTRL2` (`0x5175f8`) a single child;
`GETCOMMON` (`0x517608`) reads the saved common block; `GAMEREMOVE` (`0x517618`)
tears the family down. `vfunc_29` registers the record under `LOADINTF2_ALL`
through `0x0038d820` (`beMessenger_RegisterReceiverFromInfo`) and under
`LOADINTF2` with its `_ramNo` through `0x0038d560`
(`beMessenger_RegisterReceiver`). The handler reads the per-kind table at
`0x004cd0a0` (stride `0x0c`, three floats, indexed by the interface's kind).

### Family build order

Command `0` (`RUN`) creates the whole household once, when the record has no data list
yet, in this fixed order (constructor addresses from the retail `jal`s; classes
from the meta-object handle each constructor instantiates):

1. `0x003c43c0`: `beNDMWLoadIntf2CtrlData`, with `_isRun` (`+0x10`) = 1,
   `_isRdy` (`+0x11`) = 0, `_isCtrl` (`+0x13`) = 1 and `_isEntry` (`+0x12`) = 1
   for kind 0, 0 for the other kinds.
2. `LOADCTRL2 GETCOMMON` (`0x0038e5f0`, `beMessenger_SendNamed`) and `0x0038f800`
   (`beMessenger_GetObject`): the load controller's common block is appended to
   the list.
3. `0x003c40c0`: `beNDMWLoadIntf2MakeChr`.
4. `0x003c6ea0` (`beNDMWLoadIntf2ComMdlCtrl_Create`): `_messenger`, and `_pos`
   from the three floats of the `0x004cd0a0` kind table.
5. `0x003c76c0` (`beNDMWLoadIntf2TextOrder_Create`): `+0x10` messenger, `+0x14`
   lua node.
6. `0x003c2e60`, `beNDMWLoadIntf2SelSlot`: `_ramNo` = kind, `_messenger`,
   `_padManager`, and `_comMdlCtrl`/`_textOrder`/`_commonIntf` from the
   `COMMDLCTRL`/`TEXTORDER`/`COMMONINTF` lookups.
7. `0x003c27c0`, `beNDMWLoadIntf2NameSel`: `_ramNo`, `_messenger`,
   `_padManager`, `_comMdlCtrl`, `_textOrder`.
8. `0x003c6b00`, `beNDMWLoadIntf2MesWin`: `_ramNo`, `_messenger`, `_padManager`,
   `_textOrder`.
9. `0x003c3900`: `beNDMWLoadIntf2DegiStateCtrl`, whose `_statDataList` receives
   two `beNDMWLoadIntf2DegiState` entries (`0x003c3e40`), each wired by
   `0x003d9de0` with the kind, `COMMONINTF`, `TEXTORDER`, `COMMDLCTRL`, the
   messenger and its index 0 or 1.
10. `0x003c3560`, `beNDMWLoadIntf2DataSelIntf`: `_padManager`, `_comMdlCtrl`,
    `_textOrder`, `_commonIntf`, `_mesWin` (`MESWIN`) and `_statDisp`
    (`DEGISTATECTRL`).
11. `0x003c31e0`, `beNDMWLoadIntf2Diffselect`: `_padManager`, `_comMdlCtrl`,
    `_textOrder`, `_commonIntf`, `_mesWin`.

### Other commands

The remaining commands look up `CTRL` and `MAKECHR` first and return without
effect when the record has no data list:

| Command | Effect |
|---|---|
| `2` | adds one to the messenger's integer 0 when `CTRL._isEntry` is 1 (the integer is appended as 0 when absent) |
| `3` | the same count for `CTRL._isRdy` |
| `4` / `5` | set / clear `CTRL._isCtrl` |
| `6` | issues `GAMEREMOVE` with the kind for an unused slot (the `COMMONINTF._flagWork` record of that kind has `_isRdy` not 1) |
| `7` | latches `_difficultMax` from the messenger's integer 0 |

## Hand-off from the load controller

`beNDMWLoadCtrl2`'s update drives the sub-controller at
`beNDMWLoadCtrl2CommonIntf._mcUtilCtrl` (`+0x34`) through
`FUN_003f1270`/`FUN_003f12f0`/`FUN_003f1380`/`FUN_003f13d0` (start / wait /
close / done), and `FUN_003ecc60` is the release path the load controller calls
when the selector reports `_intfStat == 0`. Those four model-controller wrappers
are the seam between the load controller and this interface. All five are
in `src/unmatched/`.

## Where the controller logic lives

The `beNDMWLoadIntf2*` `…CtrlData`/`…Intf` classes are **passive
`beBaseInfoData` records**: their vtables resolve their update/message slots
(`vfunc_31`/`vfunc_34`) to the shared base bodies `0x002ff0e0`/`0x002ff150`
(only `beNDMWLoadIntf2MesWin` overrides, `0x003cb2f0`/`0x003cb390`). So the slot
grid, the portrait/naming entry, the difficulty rows and the card utilities are
not each a virtual method; they run inside the master update `0x003e4750` and
its helper functions (`0x003eba10`, `0x003ebe00`, `0x003ec120`, `0x003ec450`,
`0x003ecdc0`–`0x003ee4d0`, `0x003ee6d0` (2,824 B), `0x003ef1e0`, `0x003ef5d0`
(6,020 B)), against the records' reflected fields.

## Master update `0x003e4750`

`vfunc_31` ensures the eleven named works, samples the pad through the pad
manager, early-returns on the `_isSystem` gate, then switches on the per-player
record's `+0x24` state with a nested sub-state machine on `CTRL`'s `+0x24..+0x30`
(states 0–8, the slot/portrait/font/difficulty/model panels, their open/close
animations and `LOADINTF2`/`MODELCTRL` messages). The control states identified
so far:

| State | Screen |
|---|---|
| 3 | Create/Call |
| 4 | `MakeChr`, the starter choice |
| 5 | `NameSel`, the name entry |
| 6 | memory-card chooser (`SelSlot`, text `0x1009`) |
| 7 | data select (`DATASELINTF` in load mode: four areas, a status panel following the cursor, `0x513`) |
| 8 | the difficulty window and the log-in prompt (`0x51D`); for a created character, the commit (`GAMEDATAINIT` + `GAMESTART` with the typed name, `GETPLAYER UNIQUE` = the low word of `sys+0x50`) |

Per-player item state 5 checks and reads the card behind the card-access notice
(`0x1004`). Face buttons: `0x4000` (Cross) is confirm/advance and `0x2000`
(Circle) is cancel/back, in `vfunc_31` (st0==3 and st0==2) and in the slot update
.

Details of the body that are easy to get wrong:

- In the case-1 preamble (`0x3e4e90`–`0x3e4eac`) retail resets the **per-player
  record** returned by `0x003e9240` (`+0x24`/`+0x30`/`+0x2c`/`+0x28`), not `CTRL`.
  Resetting `CTRL` removes the state-2 re-entry and changes the flow to
  `0x3e3e00(JCHRSELBASE)` where retail emits `0x3e3e00(JLINEWIN01)`.
- In the CTRL `st0==0`, `st1==4` path retail writes `CTRL+0x1d = 0` (`0x3e51c8`)
  before setting state 8.
- `0x003de260(int, char)` reads its second argument. The two call sites pass
  different values: `0x3e6534` inherits `a1=1` from `li a1,1` at `0x3e64ec`,
  `0x3e7b54` does `move a1,zero`.
- The Yes branch calls `0x003def70` with a1 = 1 left by the `li a1,1` at
  `0x3e66ec`; the No branch
  passes 0 in the delay slot at `0x3e6734`.
- The `0x3e3e00` send's 6th register is set per call site (the slot-open cursor
  publish carries `t1=1`, the mark publishes 0). Its vec3 temporary is filled by
  `0x003e9220`, a three-float copy (`+0/+4/+8`) of the source record's `+0x1c` vec3.
- The play/close helpers take five arguments and the sequence query four; the
  fifth (wait) argument comes from retail `t0=1` definitions.
- The starter preview's two `0x1ae1a0` vectors (MOVETRANS) are zero (`mtc1 zero`).

### Matched source

The update sits in [`src/game/beNDMWLoadIntf2.cpp`](../../src/game/beNDMWLoadIntf2.cpp)
between `vfunc_32` and the helpers that follow it in retail. It is the complete body:
**18,616 code bytes / 4,654 instructions**, including the
initial eleven context ensures, input sampling, every nested screen/card state
and all ownership exits. The source uses reflected receivers for the common,
control, creation, model, message, slot, name, text, status, save-selection and
difficulty records.

Under the unit's bottom-up inlining the update is larger than the total-size limit, so each
inline holder is expanded at its call site while the inline calls inside it stay calls. Their
out-of-line copies are the unit's own members right after the update: the owned-reference
destructor at `0x003e9010`, the release at `0x003e9110` and the copied-reference constructor at
`0x003e9330`. The name owner is an `igSmartPointer<beUnicodeObj>`, whose destructor copy
the linker kept at `0x003832d0`. Identical code does not make the two destructors' exception
identities interchangeable. The unit check also covers all nine jump tables
(78 entries / 312 bytes), exception index `0x005535b0`, and the 191-byte
table at `0x00544890` with its one padding byte. The next independent index at
`0x0055361c` bounds that table at `0x00544950`. All sixteen cleanup ranges, stack
homes and destructor identities match.

What the match depends on:

- Both vector objects and the four source arrays contain **three floats**,
  although argument homes are spaced sixteen bytes apart. Treating them as
  larger leaves a 20-byte frame gap (the near miss recorded, which is
  refuted as a roadblock).
- The name-copy helper advances UTF16 pointers by two bytes, limits the name to
  eight characters and zero-fills the rest using an indexed loop.
- Explicit snapshots preserve the instruction-proven ordering of published
  pointer/player/selection reads.
- Scoped constructor acquisition of the retained selected-save reference makes
  its lifetime begin after retention, reproducing the original protected range.
- Declaration groups, unsigned result normalization and natural early returns
  preserve register allocation, non-trapping switch bias and exact branch
  targets.

No inline assembly or compiler modification is needed. The compiler digest and
flags are pinned in the per-unit configuration.

```sh
python3 tools/check.py --function 0x3d9de0 --cand src/game/beNDMWLoadIntf2.cpp
```

## Per-screen helpers

### Slot selection

The `beNDMWLoadIntf2SelSlot` helpers. The slot-selection screen runs
in CTRL state 6 of the master update. The record
is the `SELSLOT` record the master passes as `a0`; its pointers are `+0x14` pad
manager, `+0x18` CommMdlCtrl, `+0x1c` TextOrder, `+0x20` the common interface.

| Entry | Bytes | Symbol / source | Contract |
|---|---:|---|---|
| `0x003e0b80` | 40 | `FUN_003e0b80`, `src/game/beNDMWLoadIntf2.cpp` | clears `+0x34`/`+0x35`/`+0x36`/`+0x38` and `+0x4c..+0x58` |
| `0x003e0bb0` | 140 | `beNDMWLoadIntf2SelSlot__Init`, `src/game/beNDMWLoadIntf2.cpp` | reads the manager's `+0x38` mode → SELSLOT `+0x24`/`+0x2c` (0→5, 1→2, 2→9) |
| `0x003e0c40` | 2,848 | `beNDMWLoadIntf2SelSlot__Open`, `src/game/beNDMWLoadIntf2.cpp` | open/refresh: publishes `j_slotbase`/`j_memoryiconwin`, the `j_slotcursor` line and the marks, reconciles `+0x48`; returns `+0x34` |
| `0x003e1760` | 4,888 | `beNDMWLoadIntf2SelSlot__UpdateSelection`, `src/game/beNDMWLoadIntf2.cpp` | samples the pad through `+0x14`, moves the `+0x3c` cursor on the direction bits (`0x10` up / `0x40` down / `0x20`,`0x80` cross), cancels on `0x2000` (`+0x36`), commits/selects on `0x4000` via `0x3ee190` (`+0x40`), publishes the marks; returns `+0x35` |
| `0x003e2a80` | 140 | `beNDMWLoadIntf2SelSlot__PublishCursor`, `src/game/beNDMWLoadIntf2.cpp` | resets `+0x35`/`+0x4c..+0x58`, publishes one `j_slotcursor` line from the mark table |
| `0x003e2b10` | 1,364 | `beNDMWLoadIntf2SelSlot__Close`, `src/game/beNDMWLoadIntf2.cpp` | finishes the mark publish (tracked closes of `j_slotbase`/`j_slotcursor`/`j_memoryiconwin`, and the marks), returns SELSLOT `+0x38` |
| `0x003e3070` | 2,832 | `beNDMWLoadIntf2SelSlot__RefreshSlotMarks`, `src/game/beNDMWLoadIntf2.cpp` | re-publishes the marks, suppressing the selected row (`param_2 == loop index`), reconciles `+0x48` |

The two mark tables are `0x004cd090` (`SQ_SELECT01`/`SQ_SELECT02`, 2 rows) and
`0x004cd060` (`SQ_SELECT1A..1D` + `SQ_SELECT02`, 5 rows), `{u32 name; u32
modelIndex}` each; the per-row model "made" flag is
`SELSLOT+0x20 → +0x34 → +0x2c → +0x10 → [modelIndex] +8`.

The screen opens only after the open queue drains, so it never opens while the queue
stays full. `SELSLOT+0x35` settles exactly when the queue empties; cancel sets `+0x36`;
confirm arms the per-player records.

### Text order

The six consecutive bodies `0x003eba10..0x003ec114` publish and configure the
screens' text lines (`beNDMWLoadIntf2TextOrder`).

| Entry | Bytes | Symbol / source | Contract |
|---|---:|---|---|
| `0x003eba10` | 708 | `TextOrder_Configure`, `src/game/beNDMWLoadCtrl2.cpp` | optional ALIGN, optional colour, TEXTSET, SWITCH SET, in order |
| `0x003ebce0` | 136 | `TextOrder_PublishLine`, `src/game/beNDMWLoadCtrl2.cpp` | publish one line: `0x38d860(ctx,0x5179b0,0,-1)`, then `0x38f830(ctx,name)`, `0x38f830(ctx,font)`, `0x38f830(ctx,0x517a10)`, `0x38e060(ctx,0x517a08)`; `ctx = owner+0x10` |
| `0x003ebd70` | 72 | `TextOrder_ConfigureFont`, `src/game/beNDMWLoadCtrl2.cpp` | resolve the font from set/index, then configure (seven original arguments) |
| `0x003ebdc0` | 60 | `TextOrder_ClearFont`, `src/game/beNDMWLoadCtrl2.cpp` | resolve the font from set/index, then SWITCH CLR |
| `0x003ebe00` | 588 | `beNDMWLoadIntf2TextOrder_PublishIdLines`, `src/game/beNDMWLoadCtrl2.cpp` | scan the id table, publish the id's line list, latch `0x0058a220`/`0x0058a1e0` from the entry's 2nd word, fire `0x389ff0` with `0x517a28` (id&0xf000 ∈ {0x1000,0x2000,0x3000}) or `0x517a18` (0), and when `flag==1` and the entry carries bit 20 latch the **next** entry's 2nd word into `0x58a220` and repeat the animation dispatch |
| `0x003ec050` | 196 | `TextOrder_PublishLineListOnly`, `src/game/beNDMWLoadCtrl2.cpp` | close variant: publish the id's line list only (no globals, no animation) |

- A control id is `(mode << 16) | token`; it is matched against the low 20 bits
  of the words in the id table at `0x004cda40` (stride `0xc`: `{u32 id; u32
  text-ptr; u32 line-list}`; 360 entries, `0xffffffff` terminator).
- The line list is a chain of `{u32 name; u32 fontSet; u32 fontIndex}` triples
  terminated by a zero name; the font pointer is
  `0x004ceb30 + fontSet*0x50 + fontIndex*4`. Font selection does not
  bounds-check.
- `owner` is the `TEXTORDER` record, with `+0x10` the interface messenger and
  `+0x14` the lua node. Retail reloads `owner+0x10` before every engine call, so
  a cached pointer is wrong when a callback changes it. That the real messenger
  changes it during normal play is not shown.
- Alignment 0/1/2 emits LEFT/CENTER/RIGHT. Colour 0/1 emits
  DEFAULTCOLOR/CANCELCOLOR. Other values preserve the respective setting by
  omitting its command. Each command starts a fresh TEXTCTL message containing
  the name and font. These are command semantics, not recovered font metrics,
  glyph rendering or colour values.
- The bit-20 path latches the next entry's text pointer and repeats the
  animation dispatch; it does **not** publish the next entry's line list.
- `0x3ec050` has no sentinel check, so a missing id would run off the id table;
  callers always pass present ids.
- In `0x003ebe00`, id `0x503` (`id & 0xf000 == 0`, bit 20 set) fires the off-token, and a
  missing id such as `0x7ffff` hits the `0xffffffff` sentinel and makes no calls or writes.
- In `0x003eba10`, the two nops at `0x003eba64` and `0x003ebb8c` are unreachable
  padding; `0x003eba10`, `0x003ebd70` and `0x003ebdc0` hold 208 reachable instructions.

### Completion and selection

The two CommMdlCtrl queue queries and the confirm selection.

| Entry | Bytes | Symbol / source | Contract |
|---|---:|---|---|
| `0x003e4280` | 20 | `beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty`, `src/game/beNDMWLoadIntf2.cpp` | `CommMdlCtrl(a0)._openDataList(+0x14).count(+8) <= 0` (an `igObjectList`: `+8` count, `+0x10` data) |
| `0x003e44d0` | 20 | `beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty`, `src/game/beNDMWLoadIntf2.cpp` | the same predicate on `_closeDataList(+0x18)` |
| `0x003ee190` | 184 | `FUN_003ee190`, `src/game/beNDMWLoadCtrl2.cpp` | over the four per-player `beNDMWLoadSavePlWork` records of `COMMONINTF._flagWork` (`+0x28 → +0x10 → [i*4]`): arm rows 0–3 (`_sysStat0` `+0x24` = 1, `+0x28`/`+0x2c`/`+0x30` = 0, `_isCtrl` `+0xf` = 0, `_sysCount0` `+8` = `0x3c`), then clear the selected row (`+0x24` = 0, `+0xf` = 1, `+8` = 0) |

`0x3e4280`/`0x3e44d0` are called with the `COMMDLCTRL` record; `0x3ee190` is
called with the `COMMONINTF` record. The queues these predicates read are filled
by the common-model submission helpers and drained by `0x003e44f0`
(`beNDMWLoadIntf2ComMdlCtrl__Poll`), which polls and drains and does not fill
([common-model request queues](common-model-controller.md)).

### Difficulty

The `beNDMWLoadIntf2Diffselect` pair and the script that sizes the
window.

| Entry | Bytes | Symbol / source | Role |
|---|---:|---|---|
| `0x003ddb10` | 112 | `beNDMWLoadIntf2Diffselect__Init`, `src/game/beNDMWLoadIntf2.cpp` | cursor 0, rows 2 (kind 0, `j_linewin02`) or 3 (kind 1, `j_linewin03`), player, flags clear |
| `0x003ddb80` | 1,748 | `beNDMWLoadIntf2Diffselect__Update`, `src/game/beNDMWLoadIntf2.cpp` | open (`SQ_OPEN`, text `0x402`/`0x403`, notice `0x404`), cursor with `SQ_LINEUP00/01` and `SQ_LINEDW01/02`, Cross stores the row at `+0x1C`, Circle sets `+0x25`, then `SQ_LINEON00..02` or `SQ_CANCEL` and `+0x24 = 1` |

`hostLoad.lua` (title pack, AFS entry 806) runs `LISsetDifficultMax` from story
flags 77 and 711 of the loaded character and so decides whether, and with how
many rows, the difficulty window shows (`+0x2C` of the load controller: 0 none,
1 two rows, 2 three rows).

### Name entry

The `beNDMWLoadIntf2NameSel` functions.

| Entry | Bytes | Symbol / source | Role |
|---|---:|---|---|
| `0x003de260` | 540 | `beNDMWLoadIntf2NameSel__Init`, `src/game/beNDMWLoadIntf2.cpp` | `_langID` = 1 always; `_nameMojiMax` 8 and rows 0..3 (lang 1), 6 cells and rows 0..0x17 (lang 0), 8 cells and rows 0x18..0x1D (lang 2); with a1 = 1 clears the cells and sets `_nameCurPos` -1; restores the row/strip/column saved for the current cell, marks it as the live preview, clears the flags and `_st0`–`_st3` |
| `0x003de480` | 796 | `FUN_003de480`, `src/game/beNDMWLoadIntf2.cpp` | `CHRSELFONT10` fonts 0..2: the first key of the previous, current and next row (a1 = 1 clears) |
| `0x003de7a0` | 492 | `FUN_003de7a0`, `src/game/beNDMWLoadIntf2.cpp` | `CHRSELFONT11` fonts 0..4: the five keys from `_yokoPoint` (wrapping) |
| `0x003de990` | 1,492 | `FUN_003de990`, `src/game/beNDMWLoadIntf2.cpp` | the name cells, `CHRSELFONT12` (6, lang 0) or `CHRSELFONT13` (8): a typed code in colour 0, the live preview in colour 1, the rest cleared |
| `0x003def70` | 16 | `beNDMWLoadIntf2NameSel__SetAnswer`, `src/game/beNDMWLoadIntf2.cpp` | the Yes/No answer: `_isNameOK` = a1, `_isAnswer` = 1 |
| `0x003def80` | 7,168 | `beNDMWLoadIntf2NameSel__Update`, `src/game/beNDMWLoadIntf2.cpp` | open (face window `SQ_<species>OPEN`, seven windows `SQ_OPEN`, cursor `SQ_NAMESL0n`), typing (left/right/up/down, Cross `SQ_NAMEON0n`, Circle `SQ_NAMECANCEL`, START), question (`_isQuestion` until `_isAnswer`), close; returns `_isEnd` |

`0x003de260` ends with four stores of zero to `+84`, `+96`, `+92` and `+88`
(`_st0`, `_st3`, `_st2`, `_st1`; the last sits in the delay slot of the return
at `0x003de478`). A second name entry therefore opens the keyboard again; the
hypothesis that `_st1` survives and the open step is skipped is refuted by the
code and by a retail capture.

Data: the key rows at `0x004cc860` (`{int count; u16 codes[32]}`, stride `0x44`,
30 rows; USA rows 0..3 are `ａ..ｚ`, `Ａ..Ｚ`, `０..９`, `＆！？～ー・：`), the starter
preview models `0x004cd0d0` (`h_agumon`, `h_vmon`, `h_girumon`, `h_dorumon`) and
player models `0x004cd0e0`.

### Card selection and card utilities

The step functions the load and save masters share. Every one
reads the reflected receivers listed under
[Typed receivers and links](#typed-receivers-and-links).

| Entry | Bytes | Symbol / source | Note |
|---|---:|---|---|
| `0x003db780` | 2,052 | `beNDMWLoadIntf2DataSelIntf__UpdateSelection`, `src/game/beNDMWLoadIntf2.cpp` | data selection; reads the `bePadData` words |
| `0x003dbf90` | 844 | `FUN_003dbf90`, `src/game/beNDMWLoadIntf2.cpp` | |
| `0x003dcab0` | 428 | `FUN_003dcab0`, `src/game/beNDMWLoadIntf2.cpp` | |
| `0x003ed050` | 644 | `FUN_003ed050`, `src/game/beNDMWLoadCtrl2.cpp` | |
| `0x003ed2e0` | 872 | `FUN_003ed2e0`, `src/game/beNDMWLoadCtrl2.cpp` | |
| `0x003edc20` | 828 | `FUN_003edc20`, `src/game/beNDMWLoadCtrl2.cpp` | |
| `0x003edf60` | 556 | `beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard`, `src/game/beNDMWLoadCtrl2.cpp` | sets `_isFormatRun`: the card-format step |
| `0x003ee6d0` | 2,824 | `beNDMWDegiData__LoadFromProperties`, `src/game/beNDMWLoadCtrl2.cpp` | the property loader: takes a `beNDMWDegiData` record and fills the block at its `_data` field (`+28`) |

The other helpers of the master update in this range:
`0x003ec120` (`FUN_003ec120`, `src/unmatched/`), `0x003ec450`
(`beNDMWLoadIntf2MesWin__Update`, `src/game/`), `0x003ecdc0` (`FUN_003ecdc0`,
`src/unmatched/`), `0x003ee4d0` (`beNDMWDegiData__UpdateFieldsFromData`,
`src/game/`), `0x003ef1e0` (`FUN_003ef1e0`, `src/unmatched/`) and `0x003ef5d0`
(`beNDMWDegiData__StoreToProperties`, `src/game/`).

## Call and Create flows

The title's two character flows run these states:

- **Call Digimon**: control states 6, 7 and 8 in order: the
  memory-card chooser (SelSlot, text `0x1009`), the card-access notice
  (`0x1004`) while item state 5 checks and reads the card, the data select
  (`0x513`), the difficulty window and the log-in prompt (`0x51D`).
- **Create**: states 3 (Create/Call), 4 (`MakeChr`), 5 (`NameSel`)
  and the new-character commit of state 8.

## Open items

- **Names and placement.** The functions in `src/unmatched/` named on this page
  keep `FUN_` or `vfunc_NN` symbols: the message handler `0x003e9430`,
  `vfunc_32`, `vfunc_29`, the eleven destructor copies, `0x003e0b80`,
  `0x003ee190`, the name-entry text helpers `0x003de480`/`0x003de7a0`/
  `0x003de990`, the card-utility steps `0x003dbf90`/`0x003dcab0`/`0x003ed050`/
  `0x003ed2e0`/`0x003edc20`, `0x003ec120`, `0x003ecdc0`, `0x003ef1e0`, the
  hand-off wrappers `0x003f1270`–`0x003f13d0` and `0x003ecc60`, and the child
  constructors `0x003c27c0`–`0x003c6b00`.
- **Unidentified objects.** The object behind `_statDisp`, the property
  block `0x003ee6d0` fills and `_svData`'s object have no reflected class.
- **Not described.** The `making`/`GAMEREMOVE` transitions and the interaction
  with `beNDMWLoadSavePlWork`.
- **Outside this block.** `0x003e3b80` (`beNDMWLoadIntf2ComMdlCtrl__Start`, 504
  bytes), the common-model start helper; see
  [common-model request queues](common-model-controller.md).
