# Save Keeper and the interface scenes (`stagIS11..13`)

The Save Keeper is the Central Digi-Elf `n_digilfm[0]` (not `n_prmame`, which is the disk-collector gift NPC,
[Prmame](prmame-npc.md)). Everything up to the save screen runs natively through original bytecode, and the
screen itself runs too: `stagIS12` is hosted natively (`src/savescene.c`) over the recovered `SaveCtrl`
(`src/savectrl.c`) and `SaveIntf` (`src/saveintf.c`) state machines, writing the player's character to the
native save library through the PS2 save-file codec ([save image](save-image.md)). The `SaveCtrl`/`SaveIntf`
bodies are m2c-draft recoveries with every retail send as a host callback, checked by sequencing tests, not by
instruction-level retail oracles (see *Boundaries*). `stagIS13` (`LOADCTRL2`, the Terminal's join screen) is hosted by the same
scene host: see [load scene](load-scene.md). `stagIS11` (SUBWND CARD) is hosted too: see [card album](card-album.md).

## What runs today

1. Live Cross probe → the slot-0 conversation (`entry_0824/chunk_0073` carries the choice and the `saveshop.lua`
   queue; `make -C port check-hubnpcs` drives it end to end): a two-choice prompt (`TALKFONT02` texts 3 and 4).
2. Choice 0 queues **`saveshop.lua`**, a named chunk in the Central pack (`beLuaInfo3100` position 112,
   655 bytes, [finding #906](../../docs/systems/hub-recovery.md)). Its original bytecode closes the dialogue,
   returns the NPC to `SQ_WAIT`, disables player control, starts the change fade and issues
   `STAGECTL NEXTSTAGE stagIS12` with delay 90. `make -C port check-hubnpcs` reaches this as a stage request.
3. Choice 1 closes the dialogue and returns control.

## What `stagIS12` is

`IS` is the interface-scene family ([front-end boot](../../docs/engine/front-end-boot.md)). The three packs that
the hub requests are paired NDMW.AFS entries (stage data / Lua pack), found by scanning the archive for the
lower-case stage names:

| Stage | Stage entry | Lua entry | Evidence for the role |
| --- | --- | --- | --- |
| `stagIS11` | 807 | 808 | `j_shcard00..` card models, `shbase`; requested by Central `n_digilff[2]` (card album) |
| `stagIS12` | 809 | 810 | `j_saveareawin01..04`, `j_savecheckwin`, `j_memoryiconwin`, `j_slotbase/mark/cursor`, `j_chrselback`; Lua loads `mainstatuswin`, `savecheckwin`, `icondata` |
| `stagIS13` | 811 | 812 | `j_namewin01/02`, `j_namecursorjp/us`, `j_saveareacursorr`, `j_slotcursor`; Lua generates `LOADCTRL2`; the Terminal's join/load screen, hosted natively ([load scene](load-scene.md)) |

A retail PS2 capture of the screen shows the four colored player
panels with a **MEMORY CARD slot 1 / slot 2** list and "Saving... Do not remove the memory card (PS2) or touch the
RESET button."

The Lua pack `entry_0810/chunk_0004` is the screen's start script: it mirrors the active story flags into the
per-difficulty snapshot flags (`FLGset(700..)`, `SYSctlFlagFolder("IS", n)`) and plays `RM_NSHOP`. It contains
**no save logic**: no card call, slot choice or confirm. The pack's `SQ_EXIT` for each joined player, change fade,
`PLAYERPOINT SETGENERATEPOS 3` and `NEXTSTAGE stagML11` (the Terminal) sequence is `gatedisc.lua` (chunk 0), which
the scene never runs (see *The scene's exit*).

## The retail native side

The decompiled controllers are messenger-driven state machines. Evidence is `tools/m2c_one.py` drafts, the
ELF string tables and the retail screenshots; nothing below is matched source.

| Piece | Address / size | Role evidenced |
| --- | --- | --- |
| `beNDMWSaveCtrl` update (`vfunc_31`) | `407120`, 2,368 bytes; `vfunc_34` `407aa0`, 1,484 bytes | From the m2c draft: phase 1 starts and polls a card scan (`3f1270` / `3f12f0`); phase 2 sends `SAVECTRL GENERATE`, queries a `DATABASE` receiver (`GETDATABASE`), runs `3ecc60`, resets the four slot objects (`+0xD` data present, `+0xE` ready) and waits for all four; phase 3 reads again (`3f1380` / `3f13d0`) and sends `SETSELECT_DATA` / `SAVEINTF_ALL` messages, with a `GAMERAM` message when a slot holds data |
| `beNDMWSaveIntf` update (`vfunc_31`) | `4081a0`, 16,352 bytes; `vfunc_34` `40c220`, 6,168 bytes | The slot/confirm/progress UI over the windows above |
| `SAVEUTILITY` receiver | `beNDMWMcUtilCtrl` (its update body was not located) | Message names in the ELF string table next to the save keys: `GENERATE`, `ISRDY`, `REMOVE`, `GETDELIVER`, `REQUEST_FILEMAKE / FILEFIND / FORMAT / USE_CHECK / READ_MEDIA / WRITE_MEDIA / GETFREESIZE`, `REPORT_GAMEDATA`, `ISBUSY`, `GETRESULT`; the request / `ISBUSY` / `GETRESULT` pattern suggests an asynchronous memory-card service (inferred) |
| Serialization | `beSaveDataDeliver`, `beSvPs2McImage128k`, `3ee6d0` / `3ef5d0` | The record ↔ image translation: **implemented** ([save image](save-image.md)) |

Messages dispatched by the native controllers use the receiver names `SAVECTRL`, `SAVEINTF_ALL`, `COMMONINTF`,
`LOADINTF2_ALL`, `SETSELECT_DATA`, which exist only in native code, so the original scripts cannot stand in for
them. Per the project rules no replacement save screen is substituted.

## How the scene is hosted (`dw4_hubruntime_prepare("stagIS12")`)

The lobby opens only the four `stagML` hub packs, so the save screen is not a lobby. `dw4_hubruntime_prepare`
recognises `stagIS12` and returns a runtime in **scene mode**: no lobby, a `dw4_savescene` that loads pack 809/810
through the same file-list, stage-object, model-controller, dialogue and script owners, runs the original
`boot/first/start` chunks, then ticks the scene's services, original Lua, `SaveCtrl` and `SaveIntf` once per
admitted world sample. The pad words are the hub's (`dw4_hubruntime_input`). The runtime reports `SaveCtrl`'s exit
as an ordinary pending travel request (`stagML12`, generate position 2), so the engine's existing loading,
publication and arrival path hands over to Central with the scene's records, session state and clock. In the
engine `dw4_hubruntime_enable_gpu` opens the scene's UI layer (`dw4_savescene_enable_gpu`) and
`dw4_hubruntime_adopt_audio` moves the output device through a scene-mode runtime (a placeholder owner, so the
device is not lost across the screen). A failed return to Central cannot restore a source (`dw4_hubruntime_cancel_travel`
is refused for the scene), which ends the run with the named error.

`stagIS13` is hosted the same way ([load scene](load-scene.md)); `LoadIntf2` shares the SaveIntf toolkit.
`stagIS11` is hosted by the same scene host ([card album](card-album.md)):

| Scene | What its pack starts | Native controllers | Size evidence |
| --- | --- | --- | --- |
| `stagIS11` (card album, pack 808) | `SUBWND GENERATE CARD/I<0>`, the dedicated CARD SUBWND root (SUBWND mode 10, with its own lifecycle and the album/Booster Pack windows) | **hosted**, [card album](card-album.md) | the SUBWND lifecycle/command receivers are recovered ([subwindow docs](../../docs/engine/subwindow-lifecycle.md)) |
| `stagIS13` (load / join screen, pack 812) | `LOADCTRL2 GENERATE` | `beNDMWLoadCtrl2` + `beNDMWLoadIntf2` over the SaveIntf toolkit: **hosted**, [load scene](load-scene.md) | `3f1a80`/`3f2490`, `3e4750`/`3e9430` |

The static tables behind `SaveIntf` (message table `4cda40`, area windows, card rows, panel positions, model table) are
decoded from the USA ELF by `tools/gen_saveintf_tables.py <SLUS_208.36> > src/saveintf_tables.inc`; the generated file is
committed so a build needs no private input.

## The native save library

The save library stores the **raw PS2-format save file** exactly as `src/saveimage.c` writes it
(`BASLUS-20836savedata`, 81,920 bytes: two mirrored blocks of four character records and the item ids), in a
per-user directory: `$XDG_DATA_HOME/dw4/saves`, else `~/.local/share/dw4/saves` (`dw4_memcard_default_directory`;
`DW4_SAVE_DIR` overrides it, which the tests use with temp directories, never anything under `DW4_Decomp/`).
Memory-card slot *N* is character slot *N* of that file. Every write is atomic (temp file, read-back, rename) and
keeps the previous file as `<file>.bak`; a damaged file is refused and never overwritten. There is **no** PS2
memory-card container, icon or `.psu`/`.max` export in this release. Tests: `make -C port check-saveimage`
(`.bak` equals the previous file, the XDG path, damaged-file refusal, six retail saves byte-identical round trip).

## Host memory card and the SaveCtrl rules

`src/memcard.c` is the native stand-in for retail's `SAVEUTILITY` receiver. A card is a directory holding one
`BASLUS-20836savedata` image of four character slots; the host never creates the directory and never writes outside
it. It covers the requests the controllers make (names from the ELF string table): `ISRDY` (`dw4_memcard_ready`),
`FILEFIND`/`READ_MEDIA` (`dw4_memcard_scan`, `dw4_memcard_load`), `WRITE_MEDIA` (`dw4_memcard_save`, atomic and read back)
and `GETFREESIZE` (`dw4_memcard_needed`). It is synchronous, so the asynchronous `REQUEST_*`/`ISBUSY`/`GETRESULT`
protocol collapses to a single call; `FORMAT`, `USE_CHECK` and `REPORT_GAMEDATA` have no host meaning. A save refuses a
damaged file instead of overwriting it, and an empty selection writes nothing. `make -C port check-saveimage` covers an
empty card, a missing directory, two characters in one file (slots 0 and 2), a reload that matches key for key, a corrupted
file (refused by scan, load and save with the bytes left untouched), and that no temporary file is left behind.

`dw4_savectrl_exit_stage` (in `src/savectrl.c`) is the recovered phase-3 exit of `beNDMWSaveCtrl` (`407120`): it counts the
players whose COMMONINTF item byte `+0xD` ("data chosen") is 1, not the used card slots. With none the scene leaves for the
title (`stagis10`); otherwise it sets `PLAYERPOINT SETGENERATEPOS 2` and requests `stagML12` (Central).

`SYSctlFlagFolder(op, index)`, which the IS12 start script calls to snapshot twelve story flags, is the same
`CTRLITEM` receiver as the disk and device folders, with the group `FLAG` over the **session** `FLAGFOLDER`
(`src/foldercalls.c`). SET stores 1 and answers true only from 0, CLR stores 0 and answers true only from set, and IS
answers the byte itself. `make -C port check-retail` compares 300 random folder states with retail `3fca10` run from the ELF.

## SaveCtrl, recovered (`src/savectrl.c`, `make -C port check-savectrl`)

`beNDMWSaveCtrl` is implemented natively as a state machine whose every retail messenger call is a host callback
(`include/dw4/savectrl.h`), so the order of the retail sends is the order the tests assert. `vfunc_34` (`407aa0`) is
its `SAVECTRL GENERATE` handler: it builds the state (phase 1, counters 0) once and a second GENERATE changes nothing.
`vfunc_31` (`407120`) before that only sends `SAVECTRL GENERATE`. Strings were decoded from the ELF (`517fd0`, `5194c0..519608`).

| Phase / step | Retail behaviour |
| --- | --- |
| 1.0 | `SAVEUTILITY GENERATE` with the count 4 (`3f1270`); a card is *present* when a receiver answered (`GetBoolCount > 0`). |
| 1.1 | Present card: wait for `SAVEUTILITY ISRDY` to answer true (`3f12f0`); absent card: ready at once. Then phase 2. |
| 2.0-2.1 | `MODELCTRL j_chrselback 0 GENERATE`, `SQ_OPEN`; advance once `ISSEQNAME SQ_OPEN` stops answering true. |
| 2.2 | `SAVEINTF_ALL GENERATE` (the interface starts). |
| 2.3 | Wait on COMMONINTF `+0x30`: 0 runs the slot scan (`3ecc60`), 2 only waits, 3 advances. |
| 2.4 | (a) every player item `+0xE=0`, `+0x24=2`, counters 0; (b) wait until all four `+0xE==1`; (c) `i_fadewn01 GENERATE`, `SQ_BLOUT30`, `j_chrselback SQ_CLOSE`; (d) wait until `j_chrselback ISRUN` is false; (e) `SAVEINTF_ALL SETSELECT_DATA`, `GAMERAM GETCOMMON`: each player whose `+0xD != 1` has its `BKCHIPSTAGE` entry cleared and `NINZU` = the count of players with `+0xD == 1`. Then phase 3. |
| 3.0-3.1 | `SAVEUTILITY REMOVE` when the card was present; wait until `ISRDY` turns false (absent card: at once); then the exit above. |
| 4 | The retail `switch` has no case 4, so the controller idles after the request. |

The test (`tools/test_savectrl.c`) scripts a host through a card that becomes ready late, polling waits in every step, an
interface that is still busy, a player that is not yet closed, a card that is released late, and both exits. It is a
sequencing test against the recovered body, **not** an instruction-level retail oracle (the controller needs the
messenger and property-bag objects, which are not modelled).

## The scene's exit

Pack 810 holds seven named Lua chunks, ordered by byte position: `gatedisc.lua` (chunk 0), `first.lua` (1), `boot.lua` (2),
`func.lua` (3), `start.lua` (4), `txt_mem.lua` (5), `txt_Tar.lua` (6). `gatedisc.lua` is the shared "disc gate" template: its
`SETGENERATEPOS 3` / `NEXTSTAGE stagML11` exit is not the screen's own exit. Only one function in the
executable names `gatedisc.lua`: `beNDMWItemDisk` `vfunc_22` (`4487a0`, loaded at `448a6c`), which runs when a disc item is
collected. Neither `stagIS12` pack (809, 810) contains an `ItemDisk` object, so that chunk is never run in the scene. The
scene's boot/first/start chunks (`380878`, `380d6c`, `380d04`) only prepare it. The exit is therefore `SaveCtrl`'s native one:
Central at generate position 2 when a player chose data (the Save Keeper's own room), the title when nobody did.
A retail run shows the arrival (PCSX2, two saves of a level-99 character from the Central Save Keeper):
the loader's stage strings changed from `stagML12` to `stagIS12/separate/...` for the scene and back to
`stagML12/separate/LH_pack` after the save, and the two post-save frames are identical: the character stands on the
Save Keeper platform in front of the Digi-Elf and the three monitors, with the camera framing the port renders at
generate position 2 and the area banner reading "Save Keeper". The destination stage and arrival area are therefore
confirmed visually. An exact retail coordinate was not obtained: the heap address tried as the player position
(`0x149b7c0`, floats at +0x10) changed between two reads of the same frame and is not the player.

The same pack serves both flows, selected by the player's record: `SaveIntf` state 0 takes the "in use" branch
(`GETPLAYER ... ISUSE == 1` -> `CURRENT2BASE`, state 1) for players that already have a character, and for a fresh boot with
no character it starts the game (`GAMESTART`, player 0 only) or skips (state 9).

## SaveIntf state map (`4081a0`, drafts only)

`beNDMWSaveIntf` runs once per player (`+8`). The state of the player's COMMONINTF item (`+0x24`, with `+0x28`, `+0x2C`, `+0x30`
as step counters) drives it; the scene mode is COMMONINTF `+0x38` (0..2, selecting the text sets `0x1xxx`, `0x2xxx`, `0x3xxx`
of the call numbers `(player << 16) | id`, e.g. `0x?024` prompt, `0x?004`, `0x?00E..0x?016` card-status notices).

Two nested machines: the **item state** (`+0x24` of the player's COMMONINTF item) and, inside item state 0, the **control
state** (`+0x24` of the `CTRL` property, 0..9).

| Item state | Evidence from the draft |
| --- | --- |
| 1 | Opening: message `0x51C`, a short timer in item `+8`. |
| 0 (control states 0..9) | Control 0: open `j_chrselbase` (`SQ_OPEN`), `GAMERAM GETPLAYER`, `ISUSE`: in use -> `CURRENT2BASE`, copy the record into the display data (`3ee6d0`), control 1; else player 0 `GAMESTART` / control 9. Control 1: open `j_chrselmesswin`. 2: yes/no prompt `0x502`. 4: slot list (`SELSLOT`, `3e1760`) with prompts `0x?024` / `0x?004`, accept or cancel. 5-6: the data-select list (`DATASELINTF`, `3da7c0..3dd6d0`), delete/confirm prompts `0x50B..0x50D`. 7: confirm prompts `0x50E`, `0x510`, `0x527`, `0x529`. 8: marks the player *done* (`+0xD = 1`), then waits for all participating players (counts at `3e90b0`/`3e90c0`), prompts `0x51D`, `0x51F`, `0x530`; a Circle press (`0x2000`) un-marks. 9: idle/skip. 0x64: close the lists. |
| 2 | Closing: `j_chrselmesswin` and `j_chrselbase` `SQ_CLOSE`, then `+0xE = 1`. |
| 3 | Data confirm: card status handling in `3ed050`, `3edc20`, `3ed2e0`, `3ecdc0`; result codes in `+0x14` (0..4). |
| 4 | Card access with status codes 2..12 (`temp_s0->unk34->unk20`), selecting notices per mode. |
| 6 | Card-status notice (`0x?00E..0x?016`) then to state 7. |
| 7 | All four items forced to state 8. |
| 8 | Finish: `unkF = 1`. |

This table is read from the m2c drafts and is unconfirmed; it names states and prompts, but the helper functions (91 in
`3d9de0..3f13d0`, about 40 KB) that create the windows, read the slot list, perform the card requests and format the notices are
not recovered. Findings [#965](../../docs/findings/findings-0751-1000.md#f965)-[#967](../../docs/findings/findings-0751-1000.md#f967).

## What is still open

1. **Retail confirmation**: the post-save stage (`stagML12`) and arrival area are confirmed by a retail run and
   matching frames (above). The exact arrival coordinate and the `PLAYERPOINT SETGENERATEPOS`/`NEXTSTAGE` values were
   not logged; a trace of those two sends, or a verified player-position address, would settle them to the unit.
2. **Boundaries of the hosted screen** (see below): no instruction-level oracle for `SaveCtrl`/`SaveIntf`, scripted-pad
   coverage of the save path only, no scene music/sound verified, rendering sanity-checked only.

## Boundaries

- `SaveCtrl`/`SaveIntf` come from m2c drafts, ELF string and constant tables and the pack's Lua; every retail send is a
  host callback and the tests assert retail order (`check-savectrl`, `check-saveintf`), not retail instruction results.
- Verified headless: the scene saves slot 0, the card scan sees it, the record round-trips through the codec
  (`check-savescene`, `check-hubsave`), the Save Keeper counts as an implemented service in `check-hubnpcs`, and the
  engine path compiles and links (`dw4_hubruntime_enable_gpu`, `dw4_hubruntime_adopt_audio`). The windowed engine run of
  the save screen (loading card, GPU layer, audio hand-over with a display and sound device) was **not** exercised.
- The tests drive the pad with a script (Cross to advance, Start for the final prompt); cancel and refusal paths of
  `SaveIntf` are covered by `check-saveintf`'s sequencing cases (Circle on the card chooser, failing `FILEFIND`).
- Only player 0 is wired; co-op is out of scope by decision. The scene's sound/BGM was not examined.

## Calling a saved character from the title (port)

The title's slot screen offers *Create Digimon* and *Call Digimon*. Retail runs **Call** as `beNDMWLoadIntf2` control states
3 -> 6 -> 7 -> 8 (finding [#999](../../docs/findings/findings-0751-1000.md#f999)), the same toolkit as the Save Keeper, in this order (a live retail run):

1. **Memory-card chooser** (state 6, `SelSlot`): "MEMORY CARD slot 1 / slot 2" with the three round icons and
   "Select a memory card (PS2) to call a Digimon." (text `0x1009`). Circle returns to Create/Call.
2. **"Accessing memory card (PS2). Do not remove the memory card (PS2) or touch the RESET button."** (`0x1004`) while item state 5
   runs the card checks (`USE_CHECK`, `FILEFIND`, `READ_MEDIA`); a card with no game file answers FILEFIND with result 4 and shows "This memory card (PS2) contains no Digimon World 4 game file." (`0x1028`, finding [#1003](../../docs/findings/findings-1001-1250.md#f1003)); other results show the notices of item state 6.
3. **Data select** (state 7, `DATASELINTF` in load mode): the 2x2 character areas (name and face icon, or "NO DATA"), the status panel
   of the highlighted area on top, "Select the Digimon to call." (`0x513`). Circle returns to the chooser.
4. **Select Difficulty** (state 8 sub 0): the `j_linewin02` window with Normal / Hard (`0x402`, `0x404`) when `hostLoad.lua` allows it
   (finding [#1001](../../docs/findings/findings-1001-1250.md#f1001): flag 77 -> three rows, flag 711 -> two rows, else none), then
5. the **log-in prompt** ("To log into the Digital World press the START button.", `0x51D`) with the character's status card; Circle
   returns to the chooser, START finishes.

The port runs those states unchanged from the verified behavioural recovery (`recovered/frontend/loadintf2.c`) over the SaveIntf toolkit
(`src/saveintf.c`: `ld_chooser`, `ld_data_select`, `ld_log_in`, `ld_card_access`, `ld_card_notice_state`; `diff_init`/`diff_update` are
`3ddb10`/`3ddb80`, finding [#1000](../../docs/findings/findings-0751-1000.md#f1000)). `dw4_savescene` has a `DW4_SCENE_TITLE` kind that hosts them over the `stagIS13` pack with
`dw4_loadintf_open_title` (player 0, control machine from state 0).

**The Create/Call window is the scene's (control state 3, `ld_create_call`).** Retail's state 3 (`recovered/frontend/loadintf2.c`,
case 3): sub 0 opens `j_chrselmesswin` once (CTRL `+0x15`) and the two-row `j_linewin02` (`SQ_OPEN`), marks the player in use and
puts the cursor (`+0x18`) on Create; sub 1 waits for `j_linewin02`'s `SQ_OPEN` to end (`3e4210`), sets text `0x401` (rows) and the
message `0x523` (`0x524` for players 1..3); sub 2 moves the cursor with `SQ_LINEUP00`/`SQ_LINEDW01` (no wrap and no sound at either
end), Cross plays `SQ_LINEON00`/`SQ_LINEON01`, and Circle only closes the window for players 1..3 (`SQ_CANCEL` + messwin `SQ_CLOSE`,
sub 4 -> state 2): player 0 has no cancel; sub 3 waits for the confirm sequence, clears `0x401` and goes to state 4 (Create) or
6 (Call). The engine opens the scene when Game Start opens the slot screen and warms it until the window takes the pad
(`dw4_saveintf_title_ready`), so the first slot-screen frame is the settled Create/Call screen (the
window, texts, cursor and footer match the character UI's own Create/Call window and the retail captures; only animated phases differ). It ticks the scene with the hub's pad
words, draws it on the shared resident frame and forwards each started window sequence to the title's menu sounds
(`dw4_savescene_set_sound`; the front-end audio table holds `j_linewin02` OPEN/CLOSE/LINEUP00/LINEDW01/LINEON00/LINEON01/CANCEL and
the `j_slotcursor`, `j_saveareacursorr`, `j_linewin03` cues). **Call** flows inside the scene: `j_linewin02` closes on `SQ_LINEON01`
and the chooser opens; Circle on the chooser returns to state 3 in the scene (the window reopens, cursor on Create). **Create**
also flows inside the scene (states 4, 5 and 8; next section). Without a save library the character UI (`frontchr`) keeps its own
Create/Call window and Create flow (Call
unavailable). On START of a called character the engine takes the chosen card area and difficulty row, rebuilds the character with
`dw4_memcard_restore` (a fresh record of the saved species, the stored keys loaded over it, `BASE2CURRENT` and `RECALCPLAYER`, finding
[#1002](../../docs/findings/findings-1001-1250.md#f1002)) and goes straight to the loading card.

`make -C port check-titlecall` drives the whole screen sequence on a card with two characters (one with flag 711 set, so the difficulty
window shows) and renders every screen (`DW4_TITLECALL_FRAMES=<dir>` writes PNGs); `tools/test_save_cycle.py` runs create -> save ->
relaunch -> call -> Terminal headless; check-titlecall also drives the Create/Call window (down, no wrap, Cross on Call; Circle at the
window ignored; Create -> starter choice -> Circle -> Call). Limits: only the four starter models can be called, the host exposes one memory
card (slot 2 shows as unavailable), and the slot screen's opening animations (base panels' and windows' `SQ_OPEN` at Game Start) are warmed
off-screen, as the character UI skips them.

## Creating a character on the title (port)

Findings [#1011](../../docs/findings/findings-1001-1250.md#f1011) (NameSel), [#1012](../../docs/findings/findings-1001-1250.md#f1012) (states 4 and 5), [#1013](../../docs/findings/findings-1001-1250.md#f1013) (GAMESTART) and [#1014](../../docs/findings/findings-1001-1250.md#f1014) (refuted by a retail capture: the keyboard reopens on a second name entry).

Retail's **Create** is the same `beNDMWLoadIntf2` update: control state 4 (the starter choice, `MAKECHR`), state 5 (the name entry, the
`NAMESEL` widget) and the new-character branch of state 8 (`GAMEDATAINIT` + `GAMESTART`), then the log-in prompt Call also uses. The port
runs all three in the title scene (`src/saveintf.c`: `ld_species`, `ld_name`, `ns_*`, `ld_create`), recovered from
`recovered/frontend/loadintf2.c` (cases 4, 5 and 8) and the m2c drafts of the NameSel functions `3de260` (init), `3de480`/`3de7a0`/`3de990`
(the key-row, key-strip and name-cell texts), `3def70` (the answer) and `3def80` (the update):

1. **Starter choice** (state 4). `j_digiselcursorleft`/`right` and the nameplate `j_namewin02` open; `_chaSelDegi` starts on Dorumon
   (index 3 of the starter table `4cd0e0`: agumon, vmon, girumon, dorumon); `j_digifacewin` opens with `SQ_<species>OPEN`; the nameplate
   text is `CHRSELFONT14` = `DATABASE shinka NAME` of that row; message `0x511` ("Select a Digimon."). The 3D preview is the scene's
   `h_<species>` model (`4cd0d0`): `GENERATE`, `ISRUN`, `MOVETRANS V<0,0,0>/V<0,0,0>` (the two `1ae1a0` vectors are zero), `SQ_ENTR`.
   Left/right wrap through the four starters: `SQ_EXIT` on the old preview, `SQ_ON00` on the arrow, `SQ_LINECG00` on the nameplate,
   `SQ_p_<species>` on the face window; the new preview is generated once the arrow animation ends. Cross (with the preview running)
   continues, Circle returns to the Create/Call window; both play `SQ_LINEON00`/`SQ_CANCEL` on the nameplate, `SQ_EXIT` on the preview and
   `SQ_CLOSE` on the face window and arrows.
2. **Name entry** (state 5, `NAMESEL`). `3de260` always sets `_langID` 1 (USA): eight cells (`_nameMojiMax`), the four key rows 0..3 of
   the table at `4cc860` (`{count; UCS-2 codes[32]}`, stride `0x44`): `ａ..ｚ`, `Ａ..Ｚ`, `０..９` and the seven symbols `＆！？～ー・：`.
   The window set is `j_namewin01`, `j_namecursor01/02`, `j_namecursorup/down/left/right` and the cursor `j_namecursorus`; the texts are
   `CHRSELFONT10` (the previous, current and next row heads), `CHRSELFONT11` (five visible keys) and `CHRSELFONT13` (the cells: a typed
   code in DEFAULTCOLOR, the live preview of the next cell in CANCELCOLOR). Left/right move the highlight over the five visible keys and
   scroll the strip (wrapping) at either edge; up/down change the row (wrapping), restart the strip and keep the column; Cross types the
   highlighted key and previews it in the next cell (`SQ_NAMEON0n`; the eighth cell ends the entry); Circle steps back one cell, restoring
   the key that cell was typed with (`SQ_NAMECANCEL`), and from the first cell leaves to the starter choice; START drops the cell being
   edited and ends the entry. Message `0x517`; the finished name shows `0x519` (continue) and `0x51B` (Yes/No, cursor on Yes). Yes
   (`3def70` with a1 = 1, the `li` at `3e66ec`) commits; No returns to the last typed cell. On a second entry into state 5
   (after a Circle back from the starter choice or from the log-in prompt) the keyboard reopens, so each entry starts from step 0,
   in retail and in the port (finding [#1014](../../docs/findings/findings-1001-1250.md#f1014), which read `_st1` (`+0x58`) as not reset by `3de260` and the window opening as skipped,
   is refuted by a retail capture).
3. **GAMESTART** (state 8 sub 0, CTRL `+0x1C`): `GAMERAM GAMEDATAINIT`, then `GAMESTART` with the player model `4cec70[_chaSelDegi]` and an
   eight-code name object built from the cells (zero padded), then `GETPLAYER UNIQUE` = the low word of the world clock
   (`sys+0x50` `_worldTime`), and the record copied into the player's display (`3ee6d0`). `hostLoad.lua` finds no difficulty flag on a new
   record, so the status card and the log-in prompt (`0x51D`) follow at once; Circle there returns to the name entry (`3de260(.., 0)`, the
   typed name kept), START finishes the scene.

The host's `player_create` builds the record with the native fresh-character owner (`dw4_playerrecords_create`), which takes the name as
text: the full-width codes become their ASCII forms and `ー`/`・` become `-`/`.` (the retail conversion of the name object inside
GAMESTART, `3f96e0` -> `382eb0`, is not recovered; `～` is dropped by the owner's character filter). The engine reads the created
record when the scene exits (title state 1 with card slot and area -1), rebuilds it in the session with the same API and the scene's
`UNIQUE`, and loads the lobby (difficulty 0, `gameStart.lua`). The starter preview is a skinned actor that the scene's
model view does not draw; the engine draws it over the scene frame with the character UI's portrait renderer
(`dw4_frontchr_draw_preview`, the pack 806 camera and `waitC` clip) while control state 4 runs.

`check-titlecall` drives Create on an empty card: down/up on the Create/Call window (no wrap), the starter choice (Dorumon first; right and
left wrap; the nameplate text), the name entry (row change, strip scroll past the fifth key, Cross, Circle, START), the question with No and
then Yes, the GAMESTART record (`p_agumon`, name "Agu", Lv. 1, ISUSE, a non-zero UNIQUE), Circle at the log-in prompt back to the name, and
START to the `stagML11` exit with title state 1. The engine route used by `test_save_cycle.py`, `verify_frontend.py` and the boot tests
creates Dorumon "ac" through the scene. Limits: the 3D preview is drawn by the character UI's renderer, not by the scene (no retail frame
of it was compared); NameSel's `_langID` is fixed to 1, so the Japanese (`j_namecursorjp`, six cells) and European (rows 0x18..0x1D) layouts
are not exercised; the second-entry behaviour was checked on retail (the keyboard reopens, so each entry starts from step 0; finding [#1014](../../docs/findings/findings-1001-1250.md#f1014) refuted); the name conversion of
GAMESTART is approximated; and `UNIQUE` uses the scene's clock (it starts at the slot screen, not at power-on).

**The hand-off script (finding [#1006](../../docs/findings/findings-1001-1250.md#f1006)).** After the log-in prompt the title pack's `gameStart.lua` runs (LoadCtrl2 state 3, title mode): it clears the
mission flags, flag folders and counter 2, applies the carry-over folder flags for the chosen difficulty and rebuilds the story flags from that
difficulty's snapshot block (the block the Save Keeper's start script wrote). The engine runs it between the record build and the stage library
switch, for a new character (difficulty 0) and a called one (the difficulty row of the Select Difficulty window).
