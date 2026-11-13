# Save interface: `beNDMWSaveIntf`

`beNDMWSaveIntf` runs the in-game save dialogue, one copy of its state machine per player
(`beBaseInfoRam::_ramNo` 0..3). It borrows the load interface's children (message window,
memory-card slot selector, data selector, status windows, common model control) and the
load controller's common interface (`beNDMWLoadCtrl2CommonIntf`), so most of the work happens
in the functions [load-intf2](load-intf2.md) describes.

## Source

`src/game/beNDMWSaveIntf.cpp` is one translation unit, `ndmw_beNDMWSaveIntf`
(`0x00408100`–`0x0040dae0`), compiled whole under the `-inline level=8,bottomup` profile.

| Start | Bytes | Symbol | Role |
|---|---:|---|---|
| `0x00408100` | 156 | `beNDMWSaveIntf_AcquirePadManager` | takes the insight's `bePadManager` into `_padManager` when it is not set (slot 32) |
| `0x004081a0` | 16,352 | `beNDMWSaveIntf_Update` | per-frame update of one player's record (slot 31) |
| `0x0040c180` | 48 | `NewDataListRef_Construct_0040c180` | the inline constructor of the fresh data-list reference, emitted out of line |
| `0x0040c1b0` | 12 | `beNDMWSaveIntf_GetInfoMeta` | returns the `beNDMWSaveIntfInfo` meta object (slot 30) |
| `0x0040c1c0` | 88 | `beNDMWSaveIntf_RegisterReceivers` | registers the record as receiver of `SAVEINTF_ALL` and of `SAVEINTF` for its player (slot 29) |
| `0x0040c220` | 6,184 | `beNDMWSaveIntf_OnMessage` | message handler (slot 34) |
| `0x0040da50` | 128 | `CtrlDataRef_Destruct_0040da50` | destructor of the stack reference to the new control data |
| `0x0040dad0` | 12 | `beNDMWSaveIntf_GetMeta` | returns the `beNDMWSaveIntf` meta object (slot 20) |

The other stack-reference destructors the unit instantiates are kept from other units
(`config/SLUS-20836/unit-objects.json`, `duplicates`).

## Messages

`beNDMWSaveIntf_GetMessageEnum` (`0x003bcc20`) builds the `Message` enum the handler resolves:

| Value | Name | Handling |
|---:|---|---|
| 0 | `GENERATE` | creates the record's child list once and fills it: a `beNDMWSaveIntfCtrlData` (`_isRun`, player 0 entered), the common interface fetched with `SAVECTRL`/`GETCOMMON`, a text order, the common model control placed from `g_saveModelPlacement[player]`, a message window, a slot selector, a status-window controller with an upper and a lower `beNDMWLoadIntf2DegiState`, and a data selector, each linked to the others by property name |
| 1 | `LINKCOMMON` | appends the message's object to the child list |
| 2 | `ISENTRY` | counts the player in the messenger's first integer when `_isEntry` is set |
| 3 | `ISRDY` | the same for `_isRdy` |
| 4, 5 | `ONCTRL`, `OFFCTRL` | sets or clears the control data's `_isCtrl` |
| 6 | `SETSELECT_DATA` | sends `GAMERAM`/`GAMEREMOVE` for the player unless its work record is ready |

## Update

Each frame the update looks its children up by property name (`CTRL`, `COMMDLCTRL`, `MESWIN`,
`SELSLOT`, `COMMONINTF`, `DEGISTATECTRL`, `DATASELINTF`), polls the model control and the message
window, and reads the pad trigger when the player has control. Two state words drive it:

- The player's `beNDMWLoadSavePlWork::_sysStat0` (`PlayerStage` in the source): 0 runs the
  dialogue; 1 waits while another player uses the card (a countdown of `_sysCount0`, then the
  dialogue again); 2 closes the windows; 3 saves the chosen data; 4 accesses the card (check,
  create on request, format, find or make the slot's `beNDMWLoadSlotPlayer`, read); 6 shows a card
  error; 7 ends a card job for all four players; 8 hands control back.
  `beNDMWLoadCtrl2CommonIntf__StartUtilFor` puts one player into stage 3 or 4 and the others into 1.
- The control data's `_st0` (`SaveStep`): open the base model (and take the player's game-RAM
  record, creating the default player `でばっくん` for player 0), open the message window, ask
  whether to save (`0x502`), choose the card (`SelSlot`), prepare and run the data selection, ask
  whether to continue (`0x50E`/`0x510`, then `0x527`/`0x529`), wait until every entered player is
  ready (`0x51D`, `0x530`; Circle withdraws the player's readiness, and player 0's START with
  everyone ready ends the interface), done.

Message numbers are `(player << 16) | text`; texts that depend on the console add `0x1000`,
`0x2000` or `0x3000` for `_kindHard` 0, 1 and 2.

## Open questions

- The state and stage enum names, and the names of the card-utility and data-select steps the
  update calls (`beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard`, `__StepCreateSaveFile`,
  `__StepWriteSaveData`, `beNDMWLoadIntf2DataSelIntf__OpenSaveArea` and the rest), are read
  from how the update drives them; the memory-card utility's command numbers (`3`, `1`, `6`, `0`,
  `5`) are not identified.
- `beNDMWLoadIntf2DegiState__RequestConfirmClose` closes with `_closeKind` 1 (`SQ_LINEON00`);
  what the kind means to the player is not described.
- Calls whose callee returns a flag compare `(f(...) & 0xFF) == 1`: retail masks the result in
  the caller, which a `bool` or `unsigned char` prototype does not reproduce.
- `igInsightCore_FindManager`, which finds an insight's object by meta object, keeps its address name; it has
  callers in some forty files.
