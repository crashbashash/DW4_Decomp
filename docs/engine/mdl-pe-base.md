# Player/enemy model base: status effects (`beNDMWMdlPEBase`) and the evolution list (`beNDMWShinkaCtrl`)

`beNDMWMdlPEBase` is the `beModelCtrl` that `beNDMWMdlPlayer` and `beNDMWMdlEnemy` derive from
([player model controller](mdl-player.md)). It adds the status effects (poison, sleep, stun, bind,
attack/power down, speed/power up, refract, metal) and the status icons drawn over the model. The
per-model state is a `beNDMWMdlPEBaseInfoWork`, the `_work` of the ram's `ONE` record
(`beModelCtrlInfoRamData`); every entry point creates the ram's data list first when it is missing.

The same translation unit opens with `beNDMWShinkaCtrl`, which builds a player's list of reachable
digivolution forms.

## Source

`src/game/beNDMWMdlPEBase.cpp` is one translation unit, `ndmw_beNDMWMdlPEBase`
(`0x00443110`–`0x00447bc0`), compiled whole under the `-inline level=8,bottomup` profile.

| Start | Bytes | Symbol | Role |
|---|---:|---|---|
| `0x00443110` | 388 | `beNDMWShinkaCtrl_Setup` | finds the messenger and game RAM, fetches the `shinka` database and the player's parameter record, builds the form list |
| `0x004432a0` | 664 | `beNDMWShinkaCtrl_BuildFormList` | empties `_list`, then adds one `beNDMWShinkaObject` per form set in `BASE_ISUSE`; form 3 (Dorumon) goes to the front |
| `0x004435c0` | 832 | `beNDMWShinkaObject_Load` | a form's name (`shinka` database `NAME`), level (`BASE_LEVEL`), HP/MP maxima and attributes (game RAM), and its nine weapon skills (`BASE_SKILL`, nine per form) |
| `0x00443900` | 712 | `beNDMWMdlPEBase_ShowStatusIcon` | places a status icon model at the model's position (below) |
| `0x00443bd0` | 5,676 | `beNDMWMdlPEBase__UpdateStatus` | slot 46: the per-frame status update |
| `0x00445200` | 1,216 | `beNDMWMdlPEBase_OnSequenceChange` | slot 44 body, called by both subclasses after a new sequence starts |
| `0x004456c0` | 712 | `beNDMWMdlPEBase_LoadDownData` | the work's `_downDataList`: the player's `DOWNDATA`, or six zeroes for an enemy |
| `0x00445990` | 712 | `beNDMWMdlPEBase_LoadUpData` | the work's `_upDataList`: the player's `UPDATA`, or seven zeroes for an enemy |
| `0x00445c60` | 172 | `beNDMWMdlPEBase_RecalcPlayer` | for a player: `GAMERAM RECALCPLAYER`, then `GAMERAM ADDHP` 0 |
| `0x00445d10` | 6,816 | `beNDMWMdlPEBase__OnStatusMessage` | slot 47: the status message handler |
| `0x004477b0` | 836 | `beNDMWMdlPEBaseInfoWork__Destroy` | the work's slot 8 (destruction): clears a player's up/down data, erases the icons, drops the four status lists |
| `0x00447b00` | 56 | `beNDMWMdlPEBaseInfoWork_IsPoisoned` | the poison timer is running |
| `0x00447b40` | 88 | `beNDMWMdlPEBaseInfoWork_CurePoison` | removes the `POISON` timer and zeroes its count (the item cure) |
| `0x00447ba0` | 12 | `beNDMWMdlPEBaseInfoWork__GetMeta` | the meta object |
| `0x00447bb0` | 12 | `beNDMWMdlPEBase__GetMeta` | the meta object |

The status names and message names come from two meta enums built next to this unit:
`StatusName_GetMetaEnum` (`0x003c0440`: `POISON`, `ATTACKDOWN`, `POWERDOWN`, `BIND`, `REFRACT`,
`SPEEDUP`, `POWERUP`, `METAL`, `SLEEP`, `STUN`, `RARE`) and `MsgAction_GetMetaEnum` (`0x003c04a0`:
`SETPOISON` … `GETPEBASEWORK`, sixteen values). `DamageSeq_GetMetaEnum` (`0x003c03e0`) lists the
damage sequences (`SQ_SDMG` … `SQ_SDMGD`).

## Status lists

The work holds four twelve-entry lists indexed by the `StatusName` value, plus index 11 for the
summary icon:

- `_timerList`: the remaining duration (frames), or the remaining ticks for poison; non-zero means
  the status runs. Index 11 is set while any of the first eight statuses runs.
- `_isFirstList` (eleven bools): the status was just set and its timer must start.
- `_dispRamNoList`: the ram number of the status's icon model, -1 for none.
- `_dispPosNoList`: the display slot the icon was last placed at.

`_downDataList` (attack down 0–3, power down 4–5, metal 6) and `_upDataList` (speed up 0–3,
power up 4–6, refract 7–10) carry the stat changes a status applies; `RecalcPlayer` makes the game
RAM recompute the player after each change.

## Messages (slot 47)

The handler resolves the message through `MsgAction`. Any message other than `CHECKSTATUS` and
`CLEARSTATUS` first creates the four status lists if the work has none (timers 0, icons and slots
-1, flags false).

- `SETPOISON duration damage [endurance]`: `duration / 120 + 1` ticks, `_poisonDamage`, and
  `_poisonEndurance` when a third int is given.
- `SETSLEEP`, `SETSTUN`, `SETBIND frames`: the timer.
- `SETRAREICON value`: the `RARE` entry, which is not timed: non-zero shows the icon, at slot
  `value - 1`.
- `SETATTACKDOWN`, `SETPOWERDOWN`, `SETSPEEDUP`, `SETPOWERUP`, `SETREFRACT frames values…`: the
  timer and the status's range of the down or up data list (loaded first), then `RecalcPlayer`.
- `SETMETAL` / `CLEARMETAL`: starts or stops the metal timer; clearing zeroes the metal entry.
- `CHECKSTATUS name`: answers whether the named status runs.
- `ALLCLEARSTATUS`: stops poison, the downs, the ups and refract, zeroes both data lists and
  recalculates; then does what `CLEARSTATUS` does.
- `CLEARSTATUS`: stops sleep, stun and bind and sends the model `SQ_WAIT`.
- `GETPEBASEWORK`: answers the ram and the work as objects.

## Update (slot 46)

At zero HP every icon is erased (`SQ_ERAS`), all timers are zeroed and the icons forgotten.
Otherwise, while the model has control (`_isOnCtrl`), each running status starts its
`beBaseInfoRam` timer on its first frame (durations converted from frames at 60 per second) and acts
when the timer expires:

- **Poison** ticks every two seconds, taking `_poisonDamage` HP (not below zero) and, for a player,
  updating the `hpmt` meter and `hpnm` number. At zero HP a player is sent `SQ_DEAD`; an enemy is
  left at 1 HP. The poison ends when its ticks run out.
- **Sleep** plays `SQ_SLEP` and wakes with `SQ_WAIT`. **Stun** counts only while the model plays
  `SQ_STUN` and ends with `SQ_WAIT`. **Bind** ends with `SQ_WAIT`; while it runs, outside a damage
  sequence, every move object but the second is stopped.
- **Attack/power down, speed/power up, refract** zero their data range on expiry and recalculate.
- **Metal** adds 4 to its down-data entry every `ATTACKDELAY × 120` frames of the player.

Then every status's icon is placed: the first eight share display slots in order, so an icon whose
slot changed restarts its loop sequence; `RARE` uses its timer value − 1 as the slot. A stopped
status's icon is erased.

`ShowStatusIcon` reads the model's position from the `ONE` record's transform. Without an icon it
asks `MODELCTRL <icon> FIND_SPACE` for a free ram and `GENERATE`s it there with the slot's
`SQ_OPENnn` sequence; with one it optionally restarts `SQ_LOOPnn` and sends `MOVETRANS` to the
position.

## Sequence change (slot 44)

At zero HP the icons are erased and the lists reset as in the update. A sleep whose model left
`SQ_SLEP` is stopped. A running stun turns `SQ_WAIT` back into `SQ_STUN`; any other sequence stops
the stun and erases its icon.

## Open questions

- Why form 3 (Dorumon) is inserted at the front of the form list.
- What the individual entries of the down and up data ranges mean to the game RAM's recompute.
