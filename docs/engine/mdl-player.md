# Player model controller: `beNDMWMdlPlayer`

`beNDMWMdlPlayer` (kind `KIND_PLAYER`, messenger name `PLAYER`) is the model controller of a
player's Digimon. It is a `beModelCtrl` ([common model controller](common-model-controller.md))
that overrides the slots for the pad, the combo wait check, `GENERATE` and the events that close
the status panel. Its per-player state is a `beNDMWMdlPlayerInfoWork`, held as the `_work` of the
ram's `ONE` record (`beModelCtrlInfoRamData`); every slot creates the ram's data list first when
it is missing.

## Source

`src/game/beNDMWMdlPlayer.cpp` is one translation unit, `ndmw_beNDMWMdlPlayer`
(`0x003d2230`–`0x003d4980`), compiled whole under the `-inline level=8,bottomup` profile.

| Start | Bytes | Symbol | Slot | Role |
|---|---:|---|---:|---|
| `0x003d2230` | 96 | `beNDMWMdlPlayer__ResolveManagers` | 23 | finds the game RAM, pad manager and viewer scene-info manager in the insight |
| `0x003d2290` | 44 | `beNDMWMdlPlayer__IsKind` | 35 | `KIND_PLAYER` |
| `0x003d22c0` | 36 | `beNDMWMdlPlayer__RegisterReceiver` | 37 | registers the info under `PLAYER` |
| `0x003d22f0` | 3,700 | `beNDMWMdlPlayer__UpdateControl` | 38 | the pad, while the controller has control |
| `0x003d3170` | 128 | `__dt__9HitBoxRefFv` | | destructor of the lobby hit box reference |
| `0x003d31f0` | 1,104 | `beNDMWMdlPlayer__UpdateWaitCheck` | 39 | the `Atck01`–`Atck03` combo waits |
| `0x003d3640` | 2,736 | `beNDMWMdlPlayer__OnGenerate` | 36 | `GENERATE`: the info work, start matrix, stats and HUD |
| `0x003d40f0` | 328 | `beNDMWMdlPlayer__OnControlOff` | 40 | `OFCTRL`: closes the panel |
| `0x003d4240` | 328 | `beNDMWMdlPlayer__OnFreeze` | 41 | `ONFREEZE`: closes the panel |
| `0x003d4390` | 608 | `beNDMWMdlPlayer__OnSequenceChange` | 44 | a new sequence: the player-number badge, panel close, then `beNDMWMdlPEBase_OnSequenceChange` ([player/enemy base](mdl-pe-base.md)) |
| `0x003d45f0` | 556 | `beNDMWMdlPlayer__OnErase` | 43 | `SQ_ERAS`: the entry effect and panel close |
| `0x003d4820` | 328 | `beNDMWMdlPlayer__OnRemove` | 42 | `REMOVE`: closes the panel |
| `0x003d4970` | 12 | `beNDMWMdlPlayer__GetMeta` | 20 | the meta object |

The slot numbers are the `beModelCtrl` vtable positions. `beModelCtrl`'s message handler (slot 33)
calls slot 36 on `GENERATE`, 40 on `OFCTRL`, 41 on `ONFREEZE`, 42 on `REMOVE`, 43 when the new
sequence is `SQ_ERAS` and 44 after any other sequence starts; its update calls slot 38 while
`_isOnCtrl` is set.

## Pad

`UpdateControl` reads the pad of the ram's player (`bePadManager_GetPadForPlayer`):

- **Stick.** A direction (`_lStk`, 1–15) arms one of eight turn-attack timers
  (`g_stickTurnAttackSlot`, -1 for none) with `g_turnAttackTimerStart` (30) and counts every
  running timer down; all eight running marks the next attack as `SQ_ATCK2`. The stick angle plus
  the camera's yaw becomes `_targetDirection[1]`, and `_keyInput` says the stick is held.
- **Guard and body attack** (outside the main lobby). Pressing `0x8000` outside `SQ_JUMP` sets the
  key event `SQ_GUARD`; holding it runs `_bodyAtkSt0` through release, push, release and a second
  push in the same direction within 15 frames (`_bodyAtkTimer`), which sets `SQ_ATCK3`.
- **Panel buttons** (not in `SQ_JUMP` or `SQ_FALL`). With the status panel open it asks
  `NDMWPANEL ISCHECK`: a closed answer clears `_isPanel`, a chosen item sets `SQ_ITEM`, a chosen
  technique sets the `SQ_WAZA` label (`beModelCtrlInfoWork_SetSeqLabel`) and key event. Otherwise
  `0x2000` jumps, `0x1000` opens `GENEEMGHEAL`, and with the panel closed `0x400`, `0x800` and
  `0x200` open `GENERATEITEM`, `GENERATEWAZA` and `GENERATESTAT`.
- **Attack** (`0x4000`). In the main lobby it adds a `Set` hit box (`beModelCtrlHITBOX`, kind
  60000) to the sub-command. Elsewhere, unless `DROPITEM ACTION1` takes the button, it attacks
  once the `ATDELAY` timer has expired: `SQ_ATCK1` (or `SQ_ATCK2`, clearing the turn timers), then
  restarts the timer from the player's `ATTACKDELAY` (frames at 60 per second) and shows its level
  on the `i_stpnl05` panel model as `SQ_DLTM01`–`SQ_DLTM13` (`g_attackDelaySeqNames[(delay - 22) / 4]`).
- **Status window** (`0x8` pressed alone, stick idle): `SUBWND STATUS GENERATE`, or the `CURSOR_NG`
  sound while a panel runs.

## Combo wait check

`UpdateWaitCheck` follows `_wCheckName`. `Atck01` asks `ACTION ISCOMEND` each frame; when the
action ends it clears the name and either runs the next commands (`beModelCtrl_RunCommands`) or,
if the attack button was released during the wait, returns to `SQ_WAIT`. `Atck02` returns to
`SQ_WAIT` as soon as the button is released and runs the commands when the action ends; `Atck03`
runs them once the button is released.

## GENERATE

`OnGenerate` creates the info work (`_isPlayer`, `_directionLimiter` (0, 7, 0)) and its eight-entry
`_turnAtkTimer` list. Without a position in the message it asks `PLAYERPOINT GETMATRIX` for the
start matrix. It then takes the player record from `GAMERAM GETPLAYER`: `_hp` and `_mHp` hold the
`HP`/`MHP` records; a zero `HP` refills `HP` and `MP` from `MHP` and `MMP`; `UPDATA` and `DOWNDATA`
are reset; a player not yet in use (`ISUSE`) is started with `GAMERAM GAMESTART` and its default
name (`g_defaultPlayerNames`), and its `BASE_ISUSE` flags set. A `POWERSOCKETNAME` sends a delayed
`PLAYERARMS GENERATE`. `RECALCPLAYER` follows, then the HUD: the level (`lvnm`), the HP meter and
number (`hpmt`, `hpnm`) and the MP meter and number (`mpmt`, `mpnm`). On the stages in
`g_metalStageNames` it sends itself `SETMETAL`; on those in `g_mainLobbyStageNames` it sets
`_isMainLobby`.

## Player-number badge

While the sequence is `SQ_WAIT`, `OnSequenceChange` sends
`MODELCTRL <info name> SETEFFECT i_pcnumic SQ_OPENP<n> 480.0 <0,10,0> true true`: the badge
appears after 480 frames (about 8 s) of waiting. If the panel is open and the sequence is one of
`PanelCloseSeqList` (`SQ_SDMG`, `SQ_MDMG`, `SQ_LDMG`, `SQ_DDMG`, `SQ_DEAD`, `SQ_SLEP`, `SQ_STUN`),
it closes the panel (`NDMWPANEL REMOVE`).

## Open questions

- The slot names are best guesses from the message each slot answers; slot 39's caller is not
  traced.
- `igInsightCore_FindManager`, `StringPool_Allocate`, `igIntList_Create` (`igIntList` creation), `FUN_00191f30`,
  `Vec3f_TransformDirection` (matrix product and vector transform) and the zero vector `DAT_004e1098` keep their
  address names: each is used across many files. The base `beModelCtrl__OnGenerate` places the
  model from the message's start position.
- `UpdateControl` keeps its 18-float camera matrix and the `Scratch` temporary for the frame
  layout, and `OnGenerate` writes the `UPDATA`/`DOWNDATA` lists through a byte offset.
