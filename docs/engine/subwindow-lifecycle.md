# SUBWND service-menu lifecycle

`beNDMWStatus` is the SUBWND manager: it opens the window of one service menu (status, X Data, lab,
bank, CNOS, disk, the four shops and the card window), runs it until it closes and restores the
world afterwards. Its source is `src/game/beNDMWStatus.cpp`; the
[command receiver](subwindow-command.md) and the [work preparation](subwindow-preparation.md)
are the other two parts of the same unit.

## Owner, RAM and methods

Reflection makes `beNDMWStatus` a `beBaseInfoManager` derivative:

| Field | Role |
| --- | --- |
| `_insight` | inherited from `igInfoManager` |
| `_messenger` | inherited from `beBaseInfoManager` |
| `_infoList` | inherited from `beBaseInfoManager` |
| `_windowPro` | the retained root window |
| `_whoGenerate` | the player that opened the menu |
| `_subWndNo` | the service mode |

Its RAM is a `beNDMWStatusInfoRam`: `_isRun`, the `_st0`..`_st3` state words and `_work`, a
`beNDMWStatusInfoWork`.

The class's vtable slots carry the same roles as in the sibling `beNDMWLoadCtrl2` and
`beNDMWLoadIntf2` managers:

| Slot | Method |
| --- | --- |
| 20 | `beNDMWStatus__GetMeta` |
| 29 | `beNDMWStatus__RegisterReceiver` |
| 30 | `beNDMWStatus__GetInfoMeta` |
| 31 | `beNDMWStatus__Update` |
| 32 | `beNDMWStatus__ReleaseWindow` |
| 34 | `beNDMWStatus__OnMessage` |

`beNDMWStatus__RegisterReceiver` registers the receiver name **SUBWND** and clears `_isRun`, but
only when the info list holds exactly one entry; any other count leaves the RAM untouched.
`beNDMWStatus__ReleaseWindow` drops one reference of the root (the count is the low 23 bits of
`_refCount`), destroys it at zero and clears `_windowPro`.

## Opening and root ownership

`beNDMWStatus__Update` returns at once while `_isRun` is clear. In state 0 it calls
`beNDMWStatus__PrepareWork`, sends **STAGECTL / ENABLE / PADINPUT** and builds the root window for
the mode. The modes are the retail `SubWnd` enumeration (`SubWnd_GetMetaEnum`):

| Mode | Service | Root window |
| --- | --- | --- |
| 0 | STATUS | `beNDMWStatusCtrl00_Create` |
| 1, 3–9 | XDATA, BANK, CNOS, DISK, WPU, APU, CHIP, JUNK | `beNDMWShopCtrl00_Create` |
| 2 | LABO | `beNDMWShopCtrlDigilabo_Create` |
| 10 | CARD | `beNDMWShopCtrlA0_Create` |

STATUS first switches the WN01 and WN00 layers off through **LAYERCTL / DISPOFF / SWITCH**. The
allocator is the object's own one when `g_useOwnerAllocator` is set, otherwise the default
selector's.

The new window is held in an `igSmartPointer`; a previous one in the holder is released before it
is replaced. `beNDMWWindow_BindContext` receives the window, 0, `_insight`, `_whoGenerate` and 0,
and the window's `_entCode` takes `_subWndNo`. The manager then retains the new window, releases
the old root and publishes the new one in `_windowPro`, in that order. Every mode other than
STATUS stops the BGM and ambient sound (**SOUND / BGMSTOP**, **ENVSTOP**) and plays **RM_NSHOP**.
Advancing the state increments `_st0` and clears `_st3`, `_st2` and `_st1`.

The window is updated through `beNDMWWindow_UpdateTree` in the same call it was created, and on
every later call in state 1, until its `_isRun` clears. Any later state goes straight to
completion. Nothing checks the factory result or the mode for validity.

## Completion and service-specific exits

On completion the manager releases and clears its root, sends **OFFREEZE** to SOUND, GENERATER and
MODELCTRL, releases the message freeze and clears `_isRun`. For each of the four player slots
whose **ISUSE** flag is set it sends **ADDHP** and **ADDMP** with an amount of 0; the flags are
queried slot by slot as the loop runs.

CARD then asks STAGECTL **ISRESETSTART**. When that is false it sends PLAYERPOINT
**SETGENERATEPOS**(4) and STAGECTL **NEXTSTAGE**("stagML12"), and skips the layer and shop-exit
branch. Every other mode switches WN01 and WN00 back on (**DISPON**); a mode other than STATUS
then runs **shopexit.lua** through the Lua manager with a final argument of 0.

A direct literal CARD caller is
[`entry0808/chunk0004`](../../lua/00-title-menus/05-character-select-1_e808/004-layer-setup-camera.lua), after the
entry-camera handoff in the character-select pack, so the card window is the front end's way back
to the central area. The enumeration alone does not identify the hub's Booster Pack/album or Save
Keeper implementations.

The four item holders of the preparation each emit a 128-byte destructor: they drop one reference
of the item, destroy it at zero and free the holder when the delete flag is positive.

## Open questions

- `ReleaseWindow`, `PrepareWork` and the two enumeration names (`SubWnd`, `StatusMessage`) are
  descriptive; the retail strings name only the enumerations' values.
- Shop stock, prices, purchases, appraisal, bank/lab/X Data/card/save outcomes and multiplayer menu
  ownership are in the window controllers, not here.
