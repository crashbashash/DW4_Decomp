# Demo manager

How the `be:DM*` script functions queue messages and how the demo manager plays them back
(`src/game/beDemoManager.cpp`, class `beDemoManager`).

## Building a demo

A script builds one demo at a time in `_buildData`, a `beDemoManagerWork` holding a
`beDemoKeepMesList` of `beDemoKeepMes` entries. The first DM call of a demo creates it
(`beDemoManagerWork_CreateInstance`); each call appends one keep-message whose `_kind` says what it does:

| `_kind` | Enumerator | Appended by | At play time |
| --- | --- | --- | --- |
| 0 | `DEMO_MES_SEND` | `DMsetSD` (`beDemoManager_AddKeepMes`) | sent through the messenger, after `_sendTime` when it is positive |
| 1 | `DEMO_MES_SEND_UNTIL_TRUE` | `DMchkSD` with `"==0"` / `"!=1"` | sent, then sent again every update until the bool reply is 1 |
| 2 | `DEMO_MES_SEND_UNTIL_FALSE` | `DMchkSD` with `"!=0"` / `"==1"` | sent, then sent again every update until the bool reply is 0 |
| 3 | `DEMO_MES_SWITCH` | `beDemoManager_SwitchSD` | sent; an int reply jumps to the case labelled with it, or to the switch end |
| 4 | `DEMO_MES_CASE` | `beDemoManager_Case` (`_ramNo` is the label) | reached in order, skips to the switch end |
| 5 | `DEMO_MES_SWITCH_END` | `beDemoManager_SwitchEnd` | nothing |
| 6 | `DEMO_MES_MSGBOX` | `DMmsgBox` (`beDemoManager_MsgBox`) | nothing |
| 7 | `DEMO_MES_LUA` | `DMsetLua` (`beDemoManager_SetLua`) | `g_mdlEntity` is cleared and the Lua chunk named by `_mesParam` runs |

Strings (`_groupName`, `_infoName`, `_message`, `_mesParam`) are interned in the game's string pool.
`_turningOK` is set while a switch is open: a second `SwitchSD` is ignored, `Case` is only accepted
inside a switch, and `SwitchEnd` closes it.

`DMrun` (`beDemoManager_Run`) moves the build data onto `_activeDataList`, unless a switch is still open.

## Playing

`beDemoManager_Update` walks the active demos from the last to the first. Each resumes at its
`_advancec` and plays entries until a wait (kinds 1 and 2) holds; the held entry is sent again on the
next update. A demo whose `_advancec` reaches the end of its list is released and removed.

`beDemoManager_Reset` releases every active demo and the build data. While an update is playing
(`_disableRemoveAll`), it only records the request in `_calledRemoveAll`, and the update calls it once it
has finished.

`beDemoManager_Start` looks up the messenger and the Lua manager through the insight core.

## Open questions

- `DMmsgBox` entries are queued but playing does nothing with them; nothing else found reads them.
