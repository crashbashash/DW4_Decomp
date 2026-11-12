# Title-menu controller recovery

The title controller is `beNDMWTitle2`. Its complete contiguous runtime block is
byte-matched: **nine functions / 9,876 code bytes**.
The 8,992-byte update is in [`src/game/beNDMWTitle2.cpp`](../../src/game/beNDMWTitle2.cpp),
including initialization and reference lifetimes.

The title scene and its asset graphs are described in
[front-end boot](front-end-boot.md). The state machine supplies the missing
control rules behind those graphs. The canonical scope is the contiguous runtime
block `0x003f2d50..0x003f540c`; its metadata/constructors live separately around
`0x003b2130..0x003b2bf8`.

## Runtime block

| Start | Bytes in split | Role |
|---|---:|---|
| `0x003f2d50` | 172 | Initialize option messenger/settings (`beNDMWTitle2Option_InitSettings`) |
| `0x003f2e00` | 228 | Resolve pad manager and release cached memory-card utility (`Gap::Bec::beNDMWTitle2::vfunc_32`) |
| `0x003f2ef0` | 8,992 | Per-frame title/menu/options controller, including its internal padding; C++, complete compiler unit |
| `0x003f5210` | 128 | Reference-wrapper cleanup |
| `0x003f5290` | 128 | Second reference-wrapper cleanup |
| `0x003f5310` | 12 | Info MetaObject return |
| `0x003f5320` | 36 | Slot-29 descriptor wrapper (C++) |
| `0x003f5350` | 168 | RUN/GAMESTART message handler |
| `0x003f5400` | 12 | Controller MetaObject return |

The update's 8,700-byte Ghidra body count is the sum of
its disjoint address ranges. The build's 8,992-byte contiguous span also includes
internal gaps. These are different measures; the matching oracle compares the
entire 8,992-byte span.

## Complete matching unit

The update is one 8,992-byte C++ function. Its content-pinned compiler and `-O3,p`
profile are recorded in `config/SLUS-20836/unit-compilers.tsv` and `config/SLUS-20836/unit-flags.tsv`;
`config/SLUS-20836/unit-objects.json` checks the complete compiler object:

- the primary body, including all 520 relocations;
- three switch tables at `0x518640`, `0x518660`, `0x518680` (7 / 7 / 10 entries);
- five complete 128-byte reference-destructor copies;
- the 12-byte exception index at `0x5538e0` and the exception table at `0x544d74`.

The standalone cleanup sources remain owners of their retail addresses.
The update's five compiler copies are declared as `duplicates`: each is compared
byte-for-byte, then discarded during placement. They receive no additional
matched-byte credit. The source-side `TitleRef` names and role tags distinguish
the cleanup identities; they are not recovered original template names.

The exception table occupies `0x544d74..0x544df4`: **127 payload bytes and one
zero padding byte**. The next external-table index record at `0x55391c`
independently names function `0x3f5410` and table `0x544df4`. The update uses a
240-byte frame, nine saved GPRs and fourteen protected ranges. Scoped wrappers
reproduce the full payload, including the shared cleanup suffixes:

| Reference role | Stack homes | Cleanup address |
|---|---|---|
| Work list | `+0xec`, `+0xd8`, `+0xd4`, `+0xd0`, `+0xcc`, `+0xc8` | `0x33e9c0` |
| CTRL | `+0xe8` | `0x3f5290` |
| COMMDLCTRL | `+0xe4` | `0x3eb880` |
| OPTION | `+0xe0` | `0x3f5210` |
| TEXTORDER | `+0xdc` | `0x3eb800` |

The outer work-list and CTRL references enclose the three short-lived child
references during initialization. Later ensure-list temporaries have their own
short scopes.

Relative to a raw m2c draft, the source restores seven inert cases to their nested
switches and uses word-sized reference-count reads, byte-sized `OPTION._isOK` accesses
and the actual queue-helper signatures. The Options state read belongs after property
lookup. Matching constructs retain fresh state-increment reads, a common exit,
the CTRL/model/text/OPTION declaration order and distinct camera/light values.
Boolean conditions avoid integer promotion; signed clamp tests written as
`n > k-1` produce the retail branch-condition registers. The destructor's
low-23-bit AND form preserves the retail receiver/deletion-flag colours.

Verification:

```sh
make verify VA=0x3f2ef0 SRC=src/game/beNDMWTitle2.cpp
make check
make link
make typed-check
make hygiene
```

The complete build relinks byte-identically; the live function figures are in
[`PROGRESS.md`](../../PROGRESS.md).
Two negative ownership configurations are rejected: selecting the adjacent
exception-index record, and redirecting CTRL cleanup to the byte-identical
`0x3f2bc0` body. In the latter test all code bodies still match, but the exception
table correctly fails its cleanup-identity comparison. Engine outcomes,
rendering and timing retain their separate verification boundaries.

## The four state fields

`beNDMWTitle2CtrlData` has `_gameMenuCnt` at `+0x18`, `_gameMenuNext` at `+0x1c`,
and `_st0`, `_st1`, `_st2`, `_st3` at `+0x20..+0x2c`. Advancing an outer state
resets the inner ones; each tick normally performs one action or one wait.

| `_st0` | Behavior |
|---:|---|
| 0 | Wait for the info record's `+0x18` RUN gate to equal 1, then enter 1. |
| 1 | Ensure `j_startlogo / SQ_OPEN`, wait for tracked operations, open `j_startmenu01`, then accept START. Play its `SQ_LINEON00`, wait for its close/remove queue, and enter 2. |
| 2 | Open `j_startmenu02`; initialize row and next-action to zero; process navigation, confirmation, or cancellation. |
| 4 | Open and operate Options, close it, commit settings, then reopen the logo and return to 2; includes the alternate country-reload path. |
| 7 | Start `i_fadewn01 / SQ_WTOUT60` and close `j_startback / SQ_CLOSE`. Wait for the close/remove queue, then enter 8. |
| 8 | Begin `LOADCTRL2`, append camera and light settings, dispatch `GENERATE_TITLE`, and advance the substate once. |

States 3, 5, 6, and 9 in the top-level ten-entry jump table fall through to the
return. The reconstructed switch keeps these as the single inert default, checked
against execution of the table in retail; an m2c draft that merges several nested
default cases into duplicate top-level C case labels is incorrect.

The press-start wait also queries `MODELCTRL j_startmenu01 ISSEQNAME
SQ_LINESL00`. When that is no longer true, it enters substates 1000–1003:
generate the fade, dispatch `SQ_BLOUT30`, wait for `j_startmenu01 ISRUN` to clear,
then request `STAGECTL NEXTSTAGE stagIS09`. This is a sequence-driven attract
handoff, not a recovered hardcoded inactivity timeout.

## Input and two-row menu

The pad record returned by `0x0039b810` supplies directional words at `+0x1c` and
`+0x20`, pressed buttons at `+0x48`, and a second button word at `+0x4c` (the pad-manager
producer and repeat timing are not established here). Direction tests OR the two direction words and the two button
words: Up uses `1 / 0x10`, Right `2 / 0x20`, Down `4 / 0x40`, Left `8 / 0x80`.
START (`0x0008`), Cross (`0x4000`) and Circle (`0x2000`) use `+0x48` alone.
This describes the controller's consumption; it does not by itself establish
physical D-pad behavior or repeat timing.

- Only START advances the press-start wait.
- Menu priority is Up, Down, Cross, Circle. Up clamps on Game Start; Down clamps on
  Option. Even an attempted move past an end enters the tracked-operation wait.
- An actual move plays `SQ_LINEUP00` or `SQ_LINEDW01`. Confirm plays `SQ_LINEON00`
  or `SQ_LINEON01` and sets `_gameMenuNext` to 1 or 2.
- Confirm waits for tracked operations, closes the logo, waits for close/remove,
  then enters state 7 (Game Start) or 4 (Option).
- Circle closes the menu with `SQ_CANCEL`, waits for close/remove, and returns to
  state 1. Returning from Options opens the menu afresh and selects Game Start.

## Options

The reflected `beNDMWTitle2Option` fields are `_selLang` (`+0x14`), `_ctrlPos`
(`+0x18`), `_isOK` (`+0x1c`), `_comConf`/`_lightConf` (`+0x20/+0x24`),
`_oldCountry` (`+0x28`), and the three displayed choices (`+0x2c/+0x30/+0x34`).
The matching update uses byte accesses for `_isOK` and word accesses for the
selectors and settings, following the retail instructions.

Initialization binds `_messenger`, sets `_selLang=0`, and either fetches
`GAMERAM GETCOMMON`'s `CAMERAMODE` and `LIGHTMODE` if global byte `0x00554e70` is
1, or supplies values 0 and 1. The power-on visual meaning is Near/Hard.

Opening copies the saved values into binary displayed choices (nonzero becomes
1), sets country and old-country to 1, and selects row 0. `_selLang=0` chooses
`j_optionwin02 / SQ_BOPEN` and skips row 2: the accessible internal rows are
0, 1, 3. Values 1 and 2 choose `SQ_AOPEN` and all four rows. Navigation clamps;
it does not wrap around the menu. Language choice wraps over 2..6 for mode 1
and 0..6 for mode 2. Mode 0 has no accessible language choice.

Up and Down precede Right and Left; Right precedes Left; button confirmation is
checked only after directions. Camera and light toggle on either horizontal
direction. Cross exits only on row 3, while Circle exits from any row. Both set
`_isOK=1`: **Circle is not a rollback**. The displayed values are committed to
`_comConf/_lightConf` after the cursor/text/window close sequence completes.
The visible choices respond immediately, but that differs from immediately
writing game RAM.

The window/cursor sequences and text operations include `SQ_MOVE`, `SQ_LINESL00..03`, `SQ_LINERT00..02`, `SQ_LINELF00..02`,
and `SQ_LINEON00..03`. Text IDs `0x000f0001..0x000f000d` are preserved.
No durations have been invented: the completion callbacks gate state advances.

The alternate `_oldCountry != 1` exit uses the black fade, writes both settings
back to game RAM, marks the option-valid byte, stops BGM/environment/SE, and
requests `stagIS08`. Normal opening assigns `_oldCountry=1`; the alternate
branch exists in retail and is not asserted to be reachable during normal
US title-menu interaction.

## Engine boundary

`0x003e4280` returns whether the list at the common-model controller's `+0x14`
has no entries; `0x003e44d0` does the same for `+0x18`. These are two separate
queues: opening, which also covers played sequences, and closing. `0x003e44f0` updates the model controller
before the input/state dispatch. The original transitions depend on these
queries, not on one fixed delay.

The model/text/messenger implementations, with their real timing, rendering,
audio, persistence and reference lifetimes, lie outside this controller. The
object-creation prologue lazily constructs a property list and the CTRL,
common-model, OPTION, and text-order objects.

## Boundary repair and verification

The message handler's Ghidra body counts 160 bytes but ends at `0x003f53f7`.
Using the count as a contiguous length dropped `jr ra` at `0x003f53f0` and its
stack-restore delay slot. A generated, reviewed
span file repairs this:

```sh
ghidra-post orig/SLUS-20836/SLUS_208.36 --project-path ghidra-projects/dw4 \
  --project-name dw4 --no-analysis -postScript scripts/dump_function_extents.py \
  --addr 0x003f5350 --out data/function-extents.json
python3 tools/split.py --symbols
```

`tools/split.py` merges only these reviewed spans. It rejects shrinkage,
misalignment, duplicate/missing entries, and overlap with the next function.
It does not reinterpret every Ghidra body at once. Regenerate this file with all
reviewed addresses when adding another entry; do not edit the generated JSON.

The message enumeration at `0x004c9710` contains `RUN=0`, `GAMESTART=1`. The
handler returns 1; with a non-null info list, RUN sets the info gate and clears
its three inner state fields, while GAMESTART marks global `0x00554e70` valid.

## Game Start path: `beNDMWLoadCtrl2`

`GENERATE_TITLE` hands the loaded title to `beNDMWLoadCtrl2`, whose contiguous
runtime block is `0x003f19e0..0x003f2d4c` and holds nine bodies:

| Start | Bytes | Role | Name |
|---|---:|---|---|
| `0x003f19e0` | 156 | Resolve pad manager and addref/release it | `vfunc_32` |
| `0x003f1a80` | 2,504 | Per-frame load-controller update | `vfunc_31` |
| `0x003f2450` | 12 | MetaObject return `*(int*)0x0058baf0` | `vfunc_30` |
| `0x003f2460` | 36 | Slot-29 descriptor wrapper (C++ mode) | `vfunc_29` |
| `0x003f2490` | 1,832 | RUN/GAMESTART message handler | `vfunc_34` |
| `0x003f2bc0`/`c40`/`cc0` | 128 each | Reference-release wrappers | |
| `0x003f2d40` | 12 | MetaObject return `*(int*)0x0058bef0` | `vfunc_20` |

The reference-counting idiom these wrappers share is plain C with no `asm`: a null test on the
receiver, the release of the held object (its count in the low 23 bits, `igObject_Destroy` at zero), then
the signed-`short` deletion flag. The `nop`s around it are the compiler's own output.
The generated symbol map supplies the contiguous extents above; they are
not Ghidra occupied-body counts.

### Recovered load-controller flow

The controller is `this = beNDMWLoadCtrl2` (`_insight` `+0x0c`, `_messenger`
`+0x14`, `_cameraMode` `+0x24`, `_lightMode` `+0x28`) plus a second argument, the
per-frame context, whose `+0x28` is a **named work registry**. `igProperty_FindByName`
searches that registry by name: `"CTRL"` (`0x518130`) yields the
`beNDMWLoadCtrl2CtrlData` state record and `"COMMONINTF"` (`0x518138`) the
`beNDMWLoadCtrl2CommonIntf`, whose `+0x34` is the model-controller sub-object.

The message handler (`vfunc_34`) reads the command through
`beMessenger_ResolveEnumValue(messenger, MsgClass, Info->_dataList)`; `RUN=0` and `GAMESTART=1`
build the work when absent (creating the `"CTRL"` state object, and for
GAMESTART reading `GAMERAM GETCOMMON` → camera/light, falling back to 0/1 when
there is no difficulty), then wiring the four slots (`GAMEDATAINIT`, or
`GETPLAYER` guarded by `ISUSE`) and starting the load interface with
`model_init(work+0x34, messenger, 0)`. Command 3 additionally creates the
`"COMMONINTF"` object; command 2 is inert.

The update (`vfunc_31`) is the `beNDMWLoadCtrl2CtrlData` state machine
(`_st0` `+0x14`, `_st1` `+0x18`, `_st2` `+0x1c`, `_st3` `+0x20`):

| `_st0` | Behavior |
|---:|---|
| 0 | (no action; the outer states start from 1) |
| 1 | Open the selector backdrop (`j_chrselback` / `SQ_OPEN` via `FUN_003f1270`) and wait (`FUN_003f12f0`); on completion enter 2. |
| 2 | The slot-selector machine. `_st1` 0: model `j_chrselback GENERATE` + `SQ_OPEN`. `_st1` 1–2: fade `i_fadewn01` and wait. `_st1` 3: poll `_intfStat` (+0x30) and drive the sub-controller (`FUN_003ecc60`). `_st1` 4: the four phases of `_st2`: `0` clear each slot, `1` wait for the `+0xe` "made" flags, `2` fade/`SQ_BLOUT30`/close, `3` wait for `ISRUN`, `4` publish `LOADINTF2_ALL SETSELECT_DATA` (slot count via `+0xd`), the `NINZU`/`DIFFICULTY`/`CAMERAMODE`/`LIGHTMODE` fields to `GAMERAM GETCOMMON`, and `TITLE2 GAMESTART`; then enter `_st0` 3. |
| 3 | GAMESTART hand-off. `_st1` 0 waits (`FUN_003f1380`); `_st1` 1 clears `0x0058a1e0`, runs `gameStart.lua` (`beLua__RunNamedChunk`) and `STAGECTL NEXTSTAGE stagML11`, then returns to 0. |

The sub-controller driven at `+0x34` (`FUN_003f1270`/`_12f0`/`_1380`/`_13d0`) is
the next module down: `beNDMWLoadIntf2`.

## Remaining main-menu family

The title runtime is closed. A remaining controller target is the
6,076-byte `beNDMWLogo::vfunc_31` at `0x449030`.
The downstream 18,616-byte `beNDMWLoadIntf2` update at `0x3e4750` matches as
[`src/game/beNDMWLoadIntf2Update.cpp`](../../src/game/beNDMWLoadIntf2Update.cpp); its message handler at `0x3e9430`
has matching C++. See [asm-body matches](asm-body-matches.md)
and [the load-interface contracts](load-intf2.md).

### Common-model boundary

The shared `0x003e3b80..0x003e46a4` helper group is described in
[common-model request queues](common-model-controller.md).
The action interpreter, exact sequence/running predicates, timing, rendering and
audio are outside that description. See `load-intf2.md` for the
master and slot controllers.

### Logo sequence

[Model-sequence waits](model-sequence-waits.md) recover the next contiguous
JUMP/WCHECK group. Action2 timing remains an unverified boundary.
