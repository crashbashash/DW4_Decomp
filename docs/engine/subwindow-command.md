# SUBWND command receiver

`beNDMWStatus__OnMessage` is the SUBWND manager's message receiver (`src/game/beNDMWStatus.cpp`).
With the [lifecycle](subwindow-lifecycle.md) and the [work preparation](subwindow-preparation.md)
it makes up the manager.

## Dispatch and command contract

The receiver resolves the message's `_dataList` against the retail message enumeration
(`StatusMessage_GetMetaEnum`), whose seven names take the values 0..6. A value outside them returns
0; every recognised command returns 1, even when its state condition leaves it nothing to do.

| Value | Name | Behaviour |
| --- | --- | --- |
| 0 | GENERATE | Only while `_isRun` is 0: record the opening player and the service mode, start the state machine and freeze the world |
| 1 | REMOVE | Only while `_isRun` is exactly 1: ask the root window to close; without a root, release the freeze and queue SUBWND REMOVE |
| 2 | UPDATE | Ensure the work, rebuild the parameter snapshot and publish the player's status text |
| 3 | GETSHOPDATA | Return the WPU/APU/CHIP/JUNK sales list; JUNK also returns `_junkGift` |
| 4 | ONPREVIEW | Show the current stats coloured against the snapshot |
| 5 | OFPREVIEW | Restore the snapshot text and default colours and write the snapshot HP/MP back |
| 6 | ISRUN | Append `_isRun` |

`OFPREVIEW` is the shipped spelling. GENERATE reads the opening player as integer argument 0 and the
service name as string argument 0, resolved through `SubWnd_GetMetaEnum` (STATUS, XDATA, LABO, BANK,
CNOS, DISK, WPU, APU, CHIP, JUNK, CARD = 0..10). It sets `_isRun` and clears the state words first,
then stores `_subWndNo` and `_whoGenerate`, sends MODELCTRL and GENERATER **ONFREEZE**, sets the
message freeze and sends SOUND **ONFREEZE**. The mode is not validated.

REMOVE sets the root window's `_st0` to 2 and clears `_st3`, `_st2` and `_st1`. With no root it
sends the delayed SUBWND **REMOVE** through `beMessenger_SendDelayedGroup`; it never clears
`_isRun` itself. An `_isRun` of 2..255 blocks GENERATE but does not satisfy REMOVE.

GETSHOPDATA reads the work before its argument and never prepares it. Modes 6..9 return
`_weaponSalesList`, `_armorSalesList`, `_chipSalesList` and `_junkSalesList`; JUNK then appends
`_junkGift`. Any other mode returns nothing but is still handled.

## Status text and snapshot

UPDATE also reads the work before the player argument, and only a missing work runs
`beNDMWStatus__PrepareWork`. It empties the work's `_parameter` list and asks GAMERAM
**GETPLAYER** for the selected player, which differs from the preparation's fixed player 0.

The **PLAYERNAME** record is held in an `igSmartPointer`, retained and shown in STWINFONT02/font000.
LEVEL is capped at 999 for display. The shinka database maps **DIGIMONNO** to **NAME** for
STWINFONT04/font001. Current HP and MP go to STWINFONT06 font000 and font001. Eleven stats follow,
each shown and appended to the snapshot:

| Snapshot index | Record | STWINFONT06 label |
| --- | --- | --- |
| 0 | MHP | font010 |
| 1 | MMP | font011 |
| 2 | TSUYOSA | font040 |
| 3 | MAMORI | font041 |
| 4 | KASHIKOSA | font042 |
| 5 | SEISHIN | font043 |
| 6 | SUBAYASA | font044 |
| 7 | HONOOTEIKO | font045 |
| 8 | KOORITEIKO | font046 |
| 9 | KAMINARITEIKO | font047 |
| 10 | YAMITEIKO | font048 |

XDATA (font049) and BIT (font070) are shown without entering the snapshot. font071 shows the
experience to the next level, NEXTEXP minus EXP as a wrapping 32-bit subtraction: `----` at level
999, `0` when the difference is negative, otherwise the number formatted with `%d`. The HP and MP
read earlier are appended last, at indices 11 and 12. Each append reloads the list, since
`List_Resize` can move its storage.

## Preview and restoration

ONPREVIEW reads the selected player's eleven stats, compares each signed value with its snapshot
entry, shows the value and sends TEXTCTL **COLOR** with:

| Comparison | Red | Green | Blue |
| --- | --- | --- | --- |
| Equal | 0.9 | 0.9 | 0.9 |
| Lower | 0.94 | 0.4 | 0.25 |
| Higher | 0.0 | 0.96 | 1.0 |

Nothing is equipped or bought here.

OFPREVIEW shows the eleven snapshot values with **DEFAULTCOLOR**, then writes snapshot entries 11
and 12 back to the selected player's HP and MP. The other eleven stat records are not restored
here.

## Open questions

- Which callers send ONPREVIEW/OFPREVIEW, and whether the eleven stats are restored elsewhere, is
  in the shop controllers' scripts, not here.
