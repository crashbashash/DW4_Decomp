# Slot, character, name, difficulty and card controllers: `beNDMWLoadIntf2`

The Game Start path hands off from `beNDMWLoadCtrl2` (see
[title-menu-controller](title-menu-controller.md) §*Recovered load-controller
flow* and [load controller](load-ctrl2.md)) into `beNDMWLoadIntf2`, the interface
that runs the join, new-or-load, Digimon choice, name, memory-card slot, save data
and difficulty screens of one player before the Main Lobby loads. This page covers
the translation unit that holds it: its layout, its object model, its message
protocol and what each screen controller does.

## Source layout

`src/game/beNDMWLoadIntf2.cpp` is one whole-file C++ unit, `ndmw_beNDMWLoadIntf2`,
covering `0x003d9de0..0x003eba10` in `config/SLUS-20836/units.tsv`. Its functions
are, in retail order:

| Range | Class | Functions |
|---|---|---|
| `0x003d9de0`–`0x003da7c0` | `beNDMWLoadIntf2DegiState` | `beNDMWLoadIntf2DegiState__Init`, `__RequestOpen`, `__RequestChange`, `__RequestClose`, `__RequestConfirmClose`, `__DrawStatusText`, `__ClearStatusText`, `__Update` |
| `0x003dafb0`–`0x003dd6d0` | `beNDMWLoadIntf2DataSelIntf` | `beNDMWLoadIntf2DataSelIntf__Init`, `__ClearStatesFrom`, `__OpenSaveArea`, `__UpdateSelection`, `__CloseAll`, `__ShowSelectedStatus`, `__RestoreSaveArea`, `__CloseStatusWindows`, `__OpenSlotSaveArea`, `__OpenAreaCursor`, `__CloseSaveArea`, `__ShowAccessPlayers` |
| `0x003ddb10`–`0x003ddb80` | `beNDMWLoadIntf2Diffselect` | `beNDMWLoadIntf2Diffselect__Init`, `__Update` |
| `0x003de260`–`0x003def80` | `beNDMWLoadIntf2NameSel` | `beNDMWLoadIntf2NameSel__Init`, `__DrawRowLetters`, `__DrawColumnLetters`, `__DrawEnteredName`, `__SetAnswer`, `__Update` |
| `0x003e0b80`–`0x003e3070` | `beNDMWLoadIntf2SelSlot` | `beNDMWLoadIntf2SelSlot__Reset`, `__Init`, `__Open`, `__UpdateSelection`, `__PublishCursor`, `__Close`, `__RefreshSlotMarks` |
| `0x003e3b80`–`0x003e44f0` | `beNDMWLoadIntf2ComMdlCtrl` | `beNDMWLoadIntf2ComMdlCtrl__Start`, `__StartAt`, `__Play`, `__IsSequence`, `__IsOpenQueueEmpty`, `__Close`, `__IsRunning`, `__IsCloseQueueEmpty`, `__Poll` |
| `0x003e46b0`–`0x003eba00` | `beNDMWLoadIntf2` | `beNDMWLoadIntf2__ResolvePadManager`, `beNDMWLoadIntf2__Update`, the out-of-line accessor copies, `beNDMWLoadIntf2__GetInfoMeta`, `beNDMWLoadIntf2__RegisterReceivers`, `beNDMWLoadIntf2__OnMessage`, `beNDMWLoadIntf2__GetMeta` |

The other members of the compiler object are copies the compiler emits out of line:
the `igSmartPointer<beLoadIntf2ComMdlData>` destructor (`0x003e3d80`) after `Start`;
after the update, the owned-reference destructor (`ObjectRef_Destruct_003e9010`), the
small accessors `DataList_GetData_003e9090` … `ObjectRef_Get_003e93b0`
(with `beNDMWLoadSavePlWork__SetIsCtrl`/`__GetIsRdy`/`__GetIsEntry`,
`ObjectRef_Release_003e9110`, `Vec3f_Copy` and the new-list constructor at
`0x003e9330`); and after the message handler, one `igSmartPointer<…>` destructor per
child class it creates (`0x003eb480`–`0x003eb980`). The accessor copies keep
address-suffixed symbols because other units (`beNDMWSaveIntf`) call these copies,
the ones the retail linker kept.

### Why the update is defined early

The unit compiles with `-inline level=8,bottomup`: a function defined earlier in the
file is inlined into a later caller. `beNDMWLoadIntf2__Update` calls the DegiState,
DataSelIntf, Diffselect, NameSel, SelSlot and ComMdlCtrl functions, and retail calls
each of them, so its definition sits right after `beNDMWLoadIntf2DegiState__Init`,
before all of them; the compiler still emits it at its retail place. The small
helpers it does inline (step bookkeeping, the pad and player-work accessors, the
name copy) are `static inline` functions and helper classes defined just before it.
Under bottom-up inlining the update is larger than the total-size limit, so each
inline holder is expanded at its call site while the inline calls inside it stay
calls; their out-of-line copies are the members right after the update listed above.
A large inline helper stops inlining the calls inside it, which is why several
screens repeat short call sequences instead of sharing one bigger helper.

## Object model

Recovered from `data/reflection.json` (layouts in `include/dw4/reflected.h`); the
base of every `…CtrlData`/`…Intf` record is `beBaseInfoData` and every interface
of a manager derives from `beBaseInfoManager`.

| Class | Role (from its recovered field names) |
|---|---|
| `beNDMWLoadIntf2` | Manager: `_system`, `_padManager`, `_kindHard`, `_difficultMax`. |
| `beNDMWLoadIntf2CtrlData` | Master state record: `_isRun`/`_isRdy`/`_isEntry`/`_isCtrl`/`_isCansel`/`_isMesWin`/`_isSystem`/`_isNoSelMdl`, `_newLoadSel`, `_isNewMake`, `_isRdyCancel`, `_oldPadData`, `_st0.._st3`. |
| `beNDMWLoadIntf2SelSlot` | Slot select: `_selMax`, `_selPoint`, `_mcSelPoint`, `_mode`, `_mcStat`, `_isOpen`/`_isSelect`/`_isCansel`/`_isReOpenReq`/`_isEnd`, `_st0.._st3`. |
| `beNDMWLoadIntf2DataSelIntf` | Save-area data select: `_mcSelPoint`, `_svDataSelPoint`, `_kind`, `_plNo`, `_mesKind`, `_result`, `_isEnd`/`_isCancel`, `_isSaveArea`/`_isUpStatWin`/`_isDownStatWin`/`_isSlotWin`/`_isSelCur`. |
| `beNDMWLoadIntf2MakeChr` | Character creation: `_chaSelDegi`, `_degiName`, `_nameCur`, `_mojiSelPoint`. |
| `beNDMWLoadIntf2NameSel` | Name entry: `_selDataNo`, `_langID`, `_tateMax`/`_tateMin`/`_tatePoint`, `_yokoPoint`/`_yokoCurPos`, `_nameMojiMax`/`_nameCurPos`, `_isEnd`/`_isMakeName`/`_isQuestion`/`_isAnswer`/`_isNameOK`/`_isSideCur`, `_st0.._st3`. |
| `beNDMWLoadIntf2Diffselect` | Difficulty: `_selectPoint`, `_maxSel`, `_plNo`, `_result`, `_kind`, `_isEnd`/`_isCancel`, `_st0.._st3`. |
| `beNDMWLoadIntf2MesWin` | Message window: `_isWinOpen`/`_isWinClose`/`_isSelect`/`_isSystemMes`/`_isMesErase`/`_isMesCom`/`_isCtrl`/`_isDisp`, `_kindCtrl`, `_statCtrl`, `_ramNo`, `_curPoint`, `_mesNo`/`_sysMesNo`/`_sysStat`. |
| `beNDMWLoadIntf2DegiState` | Per-Digimon status window: `_plNo`, `_dispPos`, `_isEnd`/`_isAnmEnd`, `_closeKind`, `_kind`, `_dataNo`, `_isUseData`, `_st0.._st3`. |
| `beNDMWLoadIntf2DegiStateCtrl` / `…List` | Holder of the two status windows (`_statDataList`). |
| `beNDMWLoadIntf2ComMdlCtrl` | Common model controller: `_openDataList`, `_closeDataList`, `_pos`. |
| `beNDMWLoadIntf2TextOrder` | Text order: `_messenger`, `_lua`. |
| `beNDMWLoadSavePlWork` / `…List` | Per-player work: `_isEntry`/`_isRdy`/`_isClose`/`_isCtrl`/`_isCutConnect`, `_utilReturn`/`_utilNext`, `_isHaveSaveData`/`_haveSaveData`, `_sysStat0..3`, `_sysCount0`. |
| `beNDMWLoadSlotPlayer` / `…List` | Slot player: `_connectNO`, `_saveDataList`, `_accessPlList`. |

Links the controllers follow:

- A child's `_commonIntf` is the `beNDMWLoadCtrl2CommonIntf` the load controller
  owns. Its `_flagWork` is a `beNDMWLoadSavePlWorkList` of the four per-player
  `beNDMWLoadSavePlWork` records; a record's `_haveSaveData` is a
  `beNDMWLoadSlotPlayer` whose `_saveDataList` holds the four save areas
  (`beNDMWDegiData`); `_gameUseData` is the `beNDMWDegiDataList` of the Digimon each
  player is playing; `_mcUtilCtrl` is a `beNDMWMcUtilCtrl` whose `_slot` list holds the
  `beNDMWMcSlot` records (`_isConnect`).
- A Digimon record (`beNDMWDegiData`) shows its name from `_dmNameUni` (unit 0 is a
  marker, the name starts at unit 1), its species through `_dmkind`, which is matched
  against `g_playerModelRow` (sixteen `{model, openSequence, faceSequence}` rows:
  `p_agumon`, `SQ_agumonOPEN`, `SQ_p_agumon`, …) to find the face sequences and the
  database row of the species name.
- The pad words are `bePadData._trigger/_repeat` (edges) and `_lTrg/_lRpt` (held,
  stick directions); Cross confirms and Circle cancels on every screen.
- The NameSel object registers 288 bytes but its reflection lists fields only to
  `+100`; the rest (`NameSelWork` in the source) holds, per character of the name,
  where the letter cursor stood when it was entered, the character's state and the
  typed name itself (UTF-16 at `+236`), plus six bytes the unit clears and never reads.
- Unconfirmed: the object behind DataSelIntf's `_statDisp` (the DegiStateCtrl the
  handler links there) and `_svData` have no reflected class of their own.

## Named working set and message protocol

The message handler builds the family under the receiving record's data list
(`beBaseInfoRam._dataList`; the interface's player number is its `_ramNo`),
addressing each child by name through `igProperty_FindByName`, the same lookup
`beNDMWLoadCtrl2` uses:

| Name | Child |
|---|---|
| `COMMONINTF` | `beNDMWLoadCtrl2CommonIntf`, fetched from the load controller |
| `CTRL` | `beNDMWLoadIntf2CtrlData` (master state) |
| `MAKECHR` | `beNDMWLoadIntf2MakeChr` |
| `COMMDLCTRL` | `beNDMWLoadIntf2ComMdlCtrl` |
| `MESWIN` | `beNDMWLoadIntf2MesWin` |
| `SELSLOT` | `beNDMWLoadIntf2SelSlot` |
| `NAMESEL` | `beNDMWLoadIntf2NameSel` |
| `TEXTORDER` | `beNDMWLoadIntf2TextOrder` |
| `DEGISTATECTRL` | `beNDMWLoadIntf2DegiStateCtrl` |
| `DATASELINTF` | `beNDMWLoadIntf2DataSelIntf` |
| `DIFFSELECT` | `beNDMWLoadIntf2Diffselect` |

`beNDMWLoadIntf2__RegisterReceivers` registers the record under `LOADINTF2_ALL`
(`beMessenger_RegisterReceiverFromInfo`) and under `LOADINTF2` with its `_ramNo`
(`beMessenger_RegisterReceiver`). `beNDMWLoadIntf2__OnMessage` resolves the message
through the `Message` meta-enum (`LoadIntf2Message_GetMetaEnum`, names and values
from the tables at `0x004cb710`/`0x004cb730`):

| Value | Message | Effect |
|---|---|---|
| 0 | `GENERATE` | builds the family (below) once, when the record has no data list yet |
| 1 | `LINKCOMMON` | not handled by this receiver |
| 2 | `ISENTRY` | adds one to the messenger's integer 0 when `CTRL._isEntry` is 1 (appended as 0 when absent) |
| 3 | `ISRDY` | the same count for `CTRL._isRdy` |
| 4 / 5 | `ONCTRL` / `OFFCTRL` | set / clear `CTRL._isCtrl` |
| 6 | `SETSELECT_DATA` | sends `GAMEREMOVE` for this player when its `_flagWork` record is not ready |
| 7 | `SETDIFFICULTMAX` | latches `_difficultMax` from the messenger's integer 0 |

The commands other than `GENERATE` look up `CTRL` and `MAKECHR` first (the `MAKECHR`
result is not used) and do nothing when the record has no data list.

### Family build order

`GENERATE` creates the household in this fixed order, each through its `_Create`
function and an owning `igSmartPointer` that releases it once the list holds it:

1. `beNDMWLoadIntf2CtrlData_Create`: `_isRun` = 1, `_isRdy` = 0, `_isCtrl` = 1 and
   `_isEntry` = 1 for player 0, 0 for the others.
2. `LOADCTRL2 GETCOMMON`: the load controller's common interface is appended.
3. `beNDMWLoadIntf2MakeChr_Create`.
4. `beNDMWLoadIntf2ComMdlCtrl_Create`: `_messenger`, and `_pos` from
   `g_interfaceKindPositions[_ramNo]` (four `{x, y, z}` rows).
5. `beNDMWLoadIntf2TextOrder_Create`: messenger and Lua node.
6. `beNDMWLoadIntf2SelSlot_Create`: `_ramNo`, `_messenger`, `_padManager`, and
   `_comMdlCtrl`/`_textOrder`/`_commonIntf` from the `COMMDLCTRL`/`TEXTORDER`/`COMMONINTF`
   lookups.
7. `beNDMWLoadIntf2NameSel_Create`: `_ramNo`, `_messenger`, `_padManager`,
   `_comMdlCtrl`, `_textOrder`.
8. `beNDMWLoadIntf2MesWin_Create`: `_ramNo`, `_messenger`, `_padManager`, `_textOrder`.
9. `beNDMWLoadIntf2DegiStateCtrl_Create`, whose `_statDataList` receives two
   `beNDMWLoadIntf2DegiState_Create` entries, each wired by
   `beNDMWLoadIntf2DegiState__Init` with the player, `COMMONINTF`, `TEXTORDER`,
   `COMMDLCTRL`, the messenger and display position 0 (upper) or 1 (lower).
10. `beNDMWLoadIntf2DataSelIntf_Create`: `_padManager`, `_comMdlCtrl`, `_textOrder`,
    `_commonIntf`, `_mesWin` (`MESWIN`) and `_statDisp` (`DEGISTATECTRL`).
11. `beNDMWLoadIntf2Diffselect_Create`: `_padManager`, `_comMdlCtrl`, `_textOrder`,
    `_commonIntf`, `_mesWin`.

## Master update (`beNDMWLoadIntf2__Update`)

The per-frame update of one player's interface (18,616 bytes, nine switch tables).
It finds the named working set under the record's data list (creating the list when
it is empty), samples the player's pad through the pad manager
(`beNDMWLoadIntf2__ResolvePadManager` takes the reference on first use), returns early
while `CTRL._isSystem` is set, polls the model queues, and then advances two state
machines:

- the screen state `CTRL._st0` (with `_st1`–`_st3` as its steps): join, the
  Create/Call choice (3), the Digimon choice through MakeChr (4: the four starters'
  select-screen models `g_starterSelectModelNames` are generated and moved with
  `MOVETRANS`, their names read from the database), the name entry (5), the
  memory-card chooser (6, SelSlot, text `0x1009`), the data select (7, DataSelIntf in
  load mode with the status window following the cursor, `0x513`) and the difficulty
  window and log-in prompt (8, `0x51D`; for a created character the commit:
  `GAMEDATAINIT` and `GAMESTART` with the typed name, `GETPLAYER UNIQUE`);
- the player's card stage `_sysStat0`–`_sysStat3` of its `beNDMWLoadSavePlWork`
  record: notice question, card check, save-file creation, media read and card
  format through the `beNDMWLoadCtrl2CommonIntf__Step…` functions, with the
  card-access notice `0x1004`.

Cross (`0x4000`) confirms and Circle (`0x2000`) cancels; the stick bits of
`_lTrg/_lRpt` are tested together with the D-pad bit of the same direction.

Details of the body that are easy to get wrong:

- In the case-1 preamble retail resets the per-player work record, not `CTRL`;
  resetting `CTRL` removes the state-2 re-entry.
- `beNDMWLoadIntf2NameSel__Init` is called with `resetName` 1 when a name entry
  starts and 0 when it resumes; `beNDMWLoadIntf2NameSel__SetAnswer` gets 1 on Yes and
  0 on No.
- The vectors handed to `beNDMWLoadIntf2ComMdlCtrl__StartAt` and
  `beMessenger_AppendVec3` are three floats, filled by `Vec3f_Copy` from the model
  controller's `_pos`; the starter preview's two `MOVETRANS` vectors are zero
  (`Vec3f_Set`).
- The function's local declaration groups and the explicit snapshots of
  controller reads keep retail's register allocation and read order; the name copy
  advances its source by two bytes per character, stops at eight and zero-fills the
  rest.

## Screen controllers

Each controller is a passive `beBaseInfoData` record (its vtable keeps the shared base
update and message slots); the master update calls its functions every frame and
reads the result. Each keeps its own `_st0`–`_st3` step counters: entering a level
clears the levels below it.

### Digimon status window (`beNDMWLoadIntf2DegiState`)

Two of these sit in the DegiStateCtrl's list: display position 0 is the upper pair
of windows (`j_digifacewin` face and `j_mainstatuswin` status), position 1 the
save-check window (`j_savecheckwin`). The record shown is save area `_dataNo` of
player `_plNo` when `_kind` is 0, else the Digimon the player is using.

- `beNDMWLoadIntf2DegiState__Init` stores the messenger, model controller, text
  order, common interface, player and display position and goes idle.
- `__RequestOpen` / `__RequestChange` store which record to show and enter the open
  (1) or change (3) request; `__RequestClose` / `__RequestConfirmClose` set
  `_closeKind` (the confirm form always 1) and enter the close request (2).
- `__DrawStatusText`: for a record in use, the name (eight UTF-16 units,
  zero-padded), the species name read from the database through its model row, and
  level, HP/max HP and MP/max MP in `CHRSELFONT03/04/05`; for an unused record the
  empty-window lines. Positions 0 and 1 use different text slots.
- `__ClearStatusText` clears those slots.
- `__Update` runs one step of the request. Open starts the windows with the
  species' open sequence (or the `noface` ones), waits for the open queue and draws
  the text; change plays the face sequence and redraws at once; close closes the
  windows with `SQ_CLOSE`, `SQ_LINEON00` or `SQ_CANCEL` by `_closeKind` (or
  `SQ_NOCLOSE`), clears the text and waits for the close queue. Each request ends
  idle with `_isEnd` set, which `__Update` returns.

### Save-area data select (`beNDMWLoadIntf2DataSelIntf`)

The four save areas of a memory card in a 2×2 grid (`j_saveareawin01`–`04`, names in
`g_saveAreaWindowNames`; cursor `j_saveareacursorr` with `SQ_AAREAOPEN`–`SQ_DAREAOPEN`;
line sequences `g_saveAreaLineSelectSeqs`, `g_saveAreaLineOnSeqs`). `_kind` 0 is the
load screen, 1 the save screen (`beNDMWSaveIntf` drives the same class).

- `__Init` stores player and kind and clears the selection, window flags and steps;
  `__ClearStatesFrom` resets the step at a level and below.
- `__OpenSaveArea` opens the four area windows (an area without a Digimon kind is
  shown unused), the cursor, the prompt (load `0x513`, "already in use" `0x515` when
  another player has that Digimon, save `0x503`) and the upper status window, then
  writes the area names in `CHRSELFONT08`.
- `__UpdateSelection` moves the cursor across the grid and refreshes the status and
  prompt; Cross on the load screen copies the chosen area's Digimon into the player's
  game slot (only when no other player has it), on the save screen hands control to
  the player (`beNDMWLoadCtrl2CommonIntf__GiveCtrlTo`); Circle cancels; the cursor
  then closes.
- `__CloseAll`, `__CloseStatusWindows` and `__CloseSaveArea` close their window sets
  and wait for the close queue; `__ShowSelectedStatus` swaps the area windows for the
  lower status window of the selected area and `__RestoreSaveArea` swaps back;
  `__OpenSlotSaveArea` opens the areas with the upper status window showing the
  player's own Digimon; `__OpenAreaCursor` reopens the cursor at the selected area;
  `__ShowAccessPlayers` plays every area's face sequence and writes the names for
  each player in the access list.

### Difficulty (`beNDMWLoadIntf2Diffselect`)

`__Init` stores the kind and player and sets `_maxSel` to 2 (kind 0, `j_linewin02`) or
3 (kind 1, `j_linewin03`). `__Update` opens the window at the model controller's
position with text `0x402`/`0x403` and prompt `0x404`, moves `_selectPoint` with
`SQ_LINEUP00/01` and `SQ_LINEDW01/02`, stores `_result` on Cross or sets `_isCancel` on
Circle, closes with the chosen line's `SQ_LINEON` sequence or `SQ_CANCEL`, and returns
`_isEnd`.

`hostLoad.lua` (title pack, AFS entry 806) runs `LISsetDifficultMax` from story
flags 77 and 711 of the loaded character and so decides whether, and with how many
rows, the difficulty window shows (`SETDIFFICULTMAX`: 0 none, 1 two rows, 2 three
rows).

### Name entry (`beNDMWLoadIntf2NameSel`)

The letter grid is `g_nameEntryLetterRows` (`0x004cc860`: rows of
`{int letterCount; u16 letters[32]}`, stride `0x44`, 30 rows): rows 0–3 full-width
lower case, upper case, digits and symbols; 4–23 hiragana and katakana; 24–27 the
Latin rows again and 28–29 accented letters. Rows are *tate* (up/down), columns
*yoko* (left/right). `_langID` 0 (Japanese, `j_namecursorjp`) uses rows 0–23 and six
characters, 1 (English, `j_namecursorus`) rows 0–3 and eight, 2 rows 24–29 and eight.

- `__Init` forces `_langID` to 1 and sets the length and row range; with
  `resetName` 1 it clears the name and the per-character states. It restores the
  cursor saved for the current character, marks that character as being chosen and
  clears every flag and step (`_st1` included: a second name entry opens the
  keyboard again).
- `__DrawRowLetters` shows the first letter of the previous, current and next row
  (`CHRSELFONT10`), `__DrawColumnLetters` five letters of the current row from
  `_yokoPoint`, wrapping (`CHRSELFONT11`), `__DrawEnteredName` the typed name with the
  character being chosen highlighted (`CHRSELFONT12`, six slots, Japanese;
  `CHRSELFONT13`, eight). Each clears its slots when passed 1.
- `__SetAnswer` records the answer to "is this name right?" (`_isNameOK`) and sets
  `_isAnswer`.
- `__Update` opens the face (`SQ_<species>OPEN`), name and cursor windows, then
  while typing: up/down change the row, left/right move the cursor or scroll the
  five-letter strip, Cross (`SQ_NAMEON0n`) enters a letter, Circle
  (`SQ_NAMECANCEL`) erases the last character and puts the cursor back where it was
  (erasing past the first character gives up), START asks the question; Yes sets
  `_isMakeName`, No returns to typing. The last phase clears the text, closes every
  window and returns `_isEnd`. After Cross the code zeroes the character after the
  new position; at eight characters that write lands in the unread bytes after the
  name.

### Memory-card slot (`beNDMWLoadIntf2SelSlot`)

The slot layouts are two slots (`g_slotModeSelectSeqs`: `SQ_SELECT01`/`SQ_SELECT02`)
or a multitap (`g_slotMarkSelectSeqs`: `SQ_SELECT1A`–`1D` and slot 2), each entry
`{sequence, index in beNDMWMcUtilCtrl::_slot}`; the hardware kind (`_kindHard`: PS2,
GameCube, Xbox) sets the entry count (5, 2, 9).

- `__Reset` clears the flags and steps; `__Init` resets, selects entry 0 and copies
  the hardware kind.
- `__Open` opens `j_slotbase` (two-slot or multitap form, by `_isMtap`) and
  `j_memoryiconwin`, the `j_slotcursor` at the selected entry, a mark
  (`j_slotmark01`/`02`) for each slot holding a card, and the title (`0x100C`),
  slot-name (`0x1100`–`0x1105`) and no-card (`0x102E`) lines; `_isOpen` once the open
  queue drains.
- `__UpdateSelection` refreshes the marks and the no-card line every frame, asks for a
  reopen when a multitap is plugged in or pulled out, and reads the pad: up/down jump
  to the first or last entry, left/right step through the multitap ports; Cross on a
  slot with a card hands control to the player and records `_mcSelPoint`; Circle
  cancels.
- `__PublishCursor` replays the cursor of the current entry; `__Close` closes the
  windows, clears the lines and marks and sets `_isEnd` when the close queue drains;
  `__RefreshSlotMarks` redraws the marks treating one entry as disconnected.

### Model requests (`beNDMWLoadIntf2ComMdlCtrl`)

`__Start` sends `GENERATE` and an opening sequence to the `MODELCTRL` receivers
named `(infoName, ramNo)` (`__StartAt` also sends the position); with its last
argument 1 the request (ram number and the pooled names) is queued on
`_openDataList`. `__Play` sends a sequence, queuing it the same way; `__Close` sends
the closing sequence and queues it on `_closeDataList`. `__IsSequence` (`ISSEQNAME`)
and `__IsRunning` (`ISRUN`) query a model. `__Poll`, called each frame by the update,
walks each queue from the newest request, drops open requests whose model has reached
its sequence and close requests whose model has stopped, and stops at the first one
still pending; `__IsOpenQueueEmpty`/`__IsCloseQueueEmpty` report the queues empty.
See [common-model request queues](common-model-controller.md).

### Text order

The text helpers the screens call (`TextOrder_Configure`, `TextOrder_PublishLine`,
`TextOrder_ConfigureFont`, `TextOrder_ClearFont`,
`beNDMWLoadIntf2TextOrder_PublishIdLines`, `TextOrder_PublishLineListOnly`,
`TextOrder_ConfigureUnicode`) are in `src/game/beNDMWLoadCtrl2.cpp`; see
[load controller](load-ctrl2.md). A text control id is
`(_ramNo << 16) | message`.

## Call and Create flows

The title's two character flows:

- **Call Digimon**: the memory-card chooser (SelSlot, text `0x1009`), the card-access
  notice (`0x1004`) while the player's card stage checks and reads the card, the
  data select (`0x513`), then the difficulty window and the log-in prompt (`0x51D`).
- **Create**: Create/Call, the Digimon choice (MakeChr), the name entry (NameSel) and
  the new-character commit (`GAMEDATAINIT` + `GAMESTART` with the typed name).

## Open questions

- **Address-suffixed accessor copies.** `DataList_GetData_003e9090` …
  `ObjectRef_Get_003e93b0` are this unit's out-of-line copies of shared inline
  accessors; other units call them, and their names keep the address until the
  shared inlines have one name each.
- **Name guesses.** `beNDMWLoadIntf2DegiState__RequestChange` (the request that swaps
  the shown record without reopening the windows),
  `beNDMWLoadIntf2NameSel__DrawRowLetters`/`__DrawColumnLetters`/`__DrawEnteredName`,
  language 2 as European, the DataSelIntf prompt ids, the SelSlot hardware kinds
  (1 GameCube, 2 Xbox, from the entry counts), `g_starterSelectModelNames`
  (`h_agumon`…, the models shown on the Digimon choice) and the meaning of the text
  slot columns (0/10, 1/11, …) the status window writes.
- **SelSlot `lostEntry`.** `__RefreshSlotMarks` compares its argument with the entry
  index, while `beNDMWSaveIntf` passes a card-slot index; the two agree only in the
  two-slot layout.
- **Unidentified objects.** `_svData`'s object and the six bytes after the NameSel
  name have no recovered meaning.
