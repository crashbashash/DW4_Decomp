# Load controller: `beNDMWLoadCtrl2`

`beNDMWLoadCtrl2` (messenger name `LOADCTRL2`) runs the Game Start load: it starts the memory-card
save utility, hands the screen to the load interface ([load interface](load-intf2.md)), passes
the result to `GAMERAM` and `TITLE2`, removes the utility and switches stage. Its common
interface (`beNDMWLoadCtrl2CommonIntf`) is shared with the load and save interfaces: per-player
step functions over the memory card, the message window and the text order the screens draw
through.

## Source

`src/game/beNDMWLoadCtrl2.cpp` is one translation unit, `ndmw_beNDMWLoadCtrl2`
(`0x003eba10`–`0x003f2d50`), compiled whole under the `-inline level=8,bottomup` profile.

| Start | Bytes | Symbol | Role |
|---|---:|---|---|
| `0x003eba10` | 708 | `TextOrder_Configure` | one text-control line: optional `ALIGN`, optional colour, `TEXTSET`, then `SWITCH SET` |
| `0x003ebce0` | 136 | `TextOrder_PublishLine` | `SWITCH CLR` of one line in one font |
| `0x003ebd70` | 72 | `TextOrder_ConfigureFont` | `TextOrder_Configure` with the font taken from `g_loadFontNames[player][font]` |
| `0x003ebdc0` | 60 | `TextOrder_ClearFont` | `TextOrder_PublishLine` with the font taken from `g_loadFontNames` |
| `0x003ebe00` | 588 | `beNDMWLoadIntf2TextOrder_PublishIdLines` | publishes a message's lines and runs `txt_mem.lua` or `txt_Tar.lua` for its text call; a follow-up message also plays the next entry's call |
| `0x003ec050` | 196 | `TextOrder_PublishLineListOnly` | publishes a message's lines only |
| `0x003ec120` | 808 | `TextOrder_ConfigureUnicode` | `TextOrder_Configure` with the text given as a unicode object (`REPLACEUNKNOWN` first) |
| `0x003ec450` | 1,444 | `beNDMWLoadIntf2MesWin__Update` | the message window: question (cursor up/down, confirm) and prompt (confirm) sequences on the `j_chrselmesswin` model, system messages, erasing |
| `0x003eca00` | 104 | `beNDMWLoadIntf2MesWin__IsSequencePlaying` | asks `MODELCTRL` whether a sequence still plays (`ISSEQNAME`) |
| `0x003eca70` | 36 | `beNDMWLoadIntf2MesWin__RequestOpen` | opens the window |
| `0x003ecaa0` | 44 | `beNDMWLoadIntf2MesWin__RequestClose` | erases and closes it |
| `0x003ecad0` | 16 | `beNDMWLoadIntf2MesWin__RequestMessage` | shows a message |
| `0x003ecae0` | 32 | `beNDMWLoadIntf2MesWin__RequestQuestion` | shows a two-choice question with a cursor |
| `0x003ecb00` | 28 | `beNDMWLoadIntf2MesWin__RequestPrompt` | shows a message that waits for confirm |
| `0x003ecb20` | 80 | `beNDMWLoadIntf2MesWin__Cancel` | ends the question or prompt and erases |
| `0x003ecb70` | 8 | `beNDMWLoadIntf2MesWin__GetIsCtrl` | whether a question or prompt still waits |
| `0x003ecb80` | 8 | `beNDMWLoadIntf2MesWin__GetCurPoint` | the chosen answer |
| `0x003ecb90` | 16 | `beNDMWLoadIntf2MesWin__RequestMesErase` | erases the text |
| `0x003ecba0` | 24 | `beNDMWLoadIntf2MesWin__RequestSystemMessage` | shows a system message over the current one |
| `0x003ecbc0` | 148 | `beNDMWLoadIntf2MesWin__EndSystemMessage` | ends it and restores the message, question or prompt underneath |
| `0x003ecc60` | 352 | `beNDMWLoadCtrl2CommonIntf__UpdateCutConnect` | polls the cards and flags every player whose slot lost its card (`_isCutConnect`) |
| `0x003ecdc0` | 648 | `beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion` | step: prompt, then question; returns 1 or 2 for the answer |
| `0x003ed050` | 644 | `beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard` | step: `REQUEST_USE_CHECK`, then `REQUEST_FILEFIND` |
| `0x003ed2e0` | 872 | `beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile` | step: message, `REQUEST_GETFREESIZE`, then `REQUEST_FILEMAKE` with the `MakeDataTime` timer |
| `0x003ed650` | 1,356 | `beNDMWLoadCtrl2CommonIntf__StepReadMedia` | step: `REQUEST_READ_MEDIA`; on success builds the slot player with four Digimon records from the delivered save and converts their names |
| `0x003edba0` | 128 | `FUN_003edba0` | out-of-line holder destructor |
| `0x003edc20` | 828 | `beNDMWLoadCtrl2CommonIntf__StepWriteSaveData` | step: packs the slot player's records (one replaced by the game's) and `REQUEST_WRITE_MEDIA` with the `SaveDataTime` timer |
| `0x003edf60` | 556 | `beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard` | step: `REQUEST_FORMAT` |
| `0x003ee190` | 184 | `beNDMWLoadCtrl2CommonIntf__GiveCtrlTo` | gives control to one player and parks the others |
| `0x003ee250` | 208 | `beNDMWLoadCtrl2CommonIntf__StartUtilFor` | starts the save utility for one player at a given state |
| `0x003ee320` | 364 | `beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer` | drops a player from the slot players and releases slot players nobody uses |
| `0x003ee490` | 56 | `beNDMWDegiData__CopyFrom` | copies another record's save block |
| `0x003ee4d0` | 440 | `beNDMWDegiData__UpdateFieldsFromData` | refreshes the record's fields from its save block |
| `0x003ee690` | 52 | `beNDMWDegiData__LoadFromBuffer` | reads the save block from a buffer |
| `0x003ee6d0` | 2,824 | `beNDMWDegiData__LoadFromProperties` | save block from the game RAM's player properties |
| `0x003ef1e0` | 996 | `beNDMWDegiData__CreateItem` | creates the item object an item id names (weapon, blue armour, yellow armour, ability chip or disk by bits 12-15) |
| `0x003ef5d0` | 6,020 | `beNDMWDegiData__StoreToProperties` | the reverse: save block into the player properties, items re-created from their ids |
| `0x003f0d60` | 208 | `beNDMWLoadSlotPlayer__WriteToBuffer` | packs the save blocks into the delivery buffer |
| `0x003f0e30` | 148 | `beNDMWLoadSlotPlayer__ReadFromBuffer` | unpacks them |
| `0x003f0ed0` | 540 | `beNDMWMcUtilCtrl__Init` | sets the messenger and creates the card slots for the hardware (5 PS2, 2 GameCube or 9 Xbox) |
| `0x003f10f0` | 128 | `FUN_003f10f0` | out-of-line holder destructor |
| `0x003f1170` | 128 | `FUN_003f1170` | out-of-line holder destructor |
| `0x003f11f0` | 128 | `FUN_003f11f0` | out-of-line holder destructor |
| `0x003f1270` | 120 | `beNDMWMcUtilCtrl__Generate` | `SAVEUTILITY GENERATE`; notes whether the utility exists |
| `0x003f12f0` | 144 | `beNDMWMcUtilCtrl__CheckReady` | `ISRDY` |
| `0x003f1380` | 68 | `beNDMWMcUtilCtrl__Remove` | `SAVEUTILITY REMOVE` |
| `0x003f13d0` | 136 | `beNDMWMcUtilCtrl__IsRemoved` | whether the utility is gone |
| `0x003f1460` | 48 | `beNDMWMcUtilCtrl__Request` | queues a request kind for a slot |
| `0x003f1490` | 1,360 | `beNDMWMcUtilCtrl__Update` | reads the card states (`GETDELIVER`) and runs the queued request through `ISBUSY` and `GETRESULT` |
| `0x003f19e0` | 156 | `beNDMWLoadCtrl2__ResolvePadManager` | takes the pad manager reference (slot 32) |
| `0x003f1a80` | 2,504 | `beNDMWLoadCtrl2__Update` | the per-frame state machine (slot 31): utility start, the load interface, result hand-off to `GAMERAM`/`TITLE2`, utility removal and the stage switch |
| `0x003f2450` | 12 | `beNDMWLoadCtrl2__GetInfoMeta` | returns the `beNDMWLoadCtrl2Info` meta object (slot 30) |
| `0x003f2460` | 36 | `beNDMWLoadCtrl2__RegisterReceiver` | registers the controller as receiver `LOADCTRL2` (slot 29) |
| `0x003f2490` | 1,832 | `beNDMWLoadCtrl2__OnMessage` | message handler (slot 34): creates the `CTRL` and `COMMONINTF` records, initialises the game data, answers `COMMONINTF` queries |
| `0x003f2bc0` | 128 | `FUN_003f2bc0` | out-of-line holder destructor |
| `0x003f2c40` | 128 | `FUN_003f2c40` | out-of-line holder destructor |
| `0x003f2cc0` | 128 | `FUN_003f2cc0` | out-of-line holder destructor |
| `0x003f2d40` | 12 | `beNDMWLoadCtrl2__GetMeta` | returns the `beNDMWLoadCtrl2` meta object (slot 20) |

## Per-player steps

The `Step…` functions are re-entered every frame. Each keeps its state in one of the four
`_sysStat` words of the player's `beNDMWLoadSavePlWork` (the `depth` argument picks which, and
clears the deeper ones on store) and returns 0 while running, 1 on success and 2 on failure.
Card requests go through `beNDMWMcUtilCtrl__Request`; the request kinds are 0 file make,
1 file find, 2 format, 3 use check, 4 read, 5 write, 6 free size, 7 game-data report.

## Data

- `g_loadMessageTable` is a table of `LoadMessage` (id in bits 0-19 with the group in bits 12-15,
  a follow-up flag in bit 20, the text call number, the line list), ended by an id of -1. Each
  `LoadMessageLine` names a text-control line and a font of `g_loadFontNames`.
- `g_loadFontNames` holds 20 font names per player (`font000`…).
- `DegiSaveRecord` is the save block a `beNDMWDegiData` points at (`_data`): one member per
  property of a player's game data (`ISUSE`, `UNIQUE`, `DIGIMONNAME`, `PLAYERNAME`, `LEVEL`, `HP`,
  …, the item folders, `BASE_*`). `playerName[0]` is 0xFFFF once the name has been converted to
  unicode.

## Open questions

- `igInsightCore_FindManager` (find an insight's object by meta object) and `StringPool_Allocate` (string-pool
  allocation) keep their address names; each has callers in more than forty files.
- `InitFromId` (the item slot that takes the item id after creation), `GiveCtrlTo` and
  `IsRemoved` are best guesses from what the code does.
- `beNDMWLoadIntf2TextOrder_PublishIdLines` reads the message table through byte offsets from
  its fields, and `beNDMWDegiData__StoreToProperties` reads the byte lists as
  `igUnsignedCharList` where the loader uses `igTDataList<unsigned char>`: the typed spellings
  give different code.
