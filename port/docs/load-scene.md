# Load / join screen (`stagIS13`, `beNDMWLoadCtrl2` + `beNDMWLoadIntf2`)

The Terminal's `n_digilff[0]` (the "log in / join" Digi-Elf) asks `STAGECTL NEXTSTAGE stagIS13` when the player
accepts. `stagIS13` is hosted natively by the same interface-scene host as the save screen
([Save Keeper](save-keeper.md), `src/savescene.c`): original pack 812 (stage data entry 811) with the native
`LoadCtrl2` and `LoadIntf2`. Everything is exercised headless by `make -C port check-hubload` (the real NPC) and
`check-hubnpcs` / `check-hubstages`.

## What the screen is in the hub

`LoadCtrl2` is the controller the pack's `first` chunk starts (`be:sd("LOADCTRL2", NULL, 0, "GENERATE")`). It is
`SaveCtrl` with a different interface and a different exit (recovered from `3f1a80` and `3f2490`):

| Step | Behaviour (hub mode, the GENERATE without integers) |
| --- | --- |
| GENERATE (`3f2490`) | Builds the controller and sends `GAMERAM GAMEDATAINIT` for every player 1..3 whose `ISUSE` is not 1 (a record of an unused slot is blank from session start; the native handler only accepts that case). |
| 1 | `SAVEUTILITY` card scan, as in `SaveCtrl`. |
| 2 | `j_chrselback` opens; `LOADINTF2_ALL GENERATE`; wait for the interface (`COMMONINTF +0x30` = 3); close every player (`+0xE`), fade out `SQ_BLOUT30`, `j_chrselback SQ_CLOSE`; `SETSELECT_DATA` (players that did not choose data are `GAMEREMOVE`d); publish `NINZU` = players that chose. |
| 3 | Release the card, then `PLAYERPOINT SETGENERATEPOS 4` and `STAGECTL NEXTSTAGE stagML11` (always the Terminal, even when nobody chose). |

`LoadIntf2` (`3e4750` update, `3e9430` receiver) is the same toolkit as `SaveIntf` (the 85 helpers `3d9de0..3f1460`:
model tracker, text order, message window, slot panels, card flows). For a player who already has a character, which is
every hub case (player 0), the flow is:

1. Item state 1 (entered when another player takes the floor) shows the notice `0x51C`; control state 0 opens `j_chrselbase`, reads `GAMERAM GETPLAYER ISUSE`, copies the record into the display, opens
   `j_chrselmesswin` and marks the player in use.
2. Control state 8 opens the player's own panel (`j_mainstatuswin` + the character summary) and marks the player
   **chosen** (`COMMONINTF` item `+0xD`).
3. When every player in use has chosen, notice `0x521` is shown: *"To log into the Digital World press the START button."*
   START (pad word `0x8`) sets the scene-finished flag (`COMMONINTF +0x30 = 3`) and clears every player's pad.
4. `LoadCtrl2` then closes the windows and exits as above. Nothing is saved: the record, `XDATA` and `LEVEL` are untouched,
   `NINZU` is published as 1, and the host card file is not written.

Players 1..3 have no pad in this port (co-op is out of scope), so they idle in control state 1 (waiting for a pad), exactly
as retail does without a connected pad, and are closed by the item closing state.

## What is ported and what is not

Ported literally from the m2c drafts (`src/saveintf.c`, `load_player_update`, `load_ctrl_body`): item states 1/0, 2, 7, 8 and
control states 0, 1, 2 and 8 (its notices, the START gate and the chosen counts). The states a player *without* data reaches are
control states 3 (new or loaded data), 4 (starter selection), 5 (name entry, `NameSel`), 6 (memory-card data chooser), 7 (data select),
the difficulty (`Diffselect`), commit (`GAMEDATAINIT`, `GAMESTART`, `BASE2CURRENT`, `hostLoad.lua`) and cancel (8.2) branches of state 8,
and item states 5/6 (card access and notice). They are reachable only for a joining player with a pad or for the title's Game Start
flow, neither of which exists in the single-player hub; they are ported for the title and run in `DW4_SCENE_TITLE`:

- **Call Digimon**: control states 6 (card chooser), 7 (data select) and 8 (difficulty and the log-in prompt) and item states 5 and 6
  (card access and notices); see [Save Keeper](save-keeper.md#calling-a-saved-character-from-the-title-port), findings [#999](../../docs/findings/findings-0751-1000.md#f999)-[#1002](../../docs/findings/findings-1001-1250.md#f1002).
- **Create/Call window**: control state 3 (`ld_create_call`). The title scene opens with the slot screen and runs player 0 from control
  state 0: the base panels, the Create/Call window, and Call's states 6 to 8 with the retail window change (the two-row window closes
  on `SQ_LINEON01`, the chooser opens), Circle on the chooser back to state 3 inside the scene, and no cancel at state 3 for player 0
  (only players 1..3 close it, sub 4).
- **Create**: control state 4 (the starter choice, `MakeChr`), state 5 (the name entry, `NameSel` `3de260`/`3def80`) and state 8's
  new-character commit (`GAMEDATAINIT` + `GAMESTART` with the starter's player model and the typed name, `UNIQUE` from the world
  clock), then the same log-in prompt; see [Save Keeper](save-keeper.md#creating-a-character-on-the-title-port).

State 3's cancel for a joining player 1..3 is coded from the draft but unexercised (the host connects only player 0's pad).
`LoadCtrl2`'s title mode (the GENERATE that carries integers, the `SQ_WTIN60` fade wait, `TITLE2 GAMESTART`, `gameStart.lua`) is not
ported: `dw4_loadctrl_generate` returns an error for it.

Findings [#971](../../docs/findings/findings-0751-1000.md#f971)-[#974](../../docs/findings/findings-0751-1000.md#f974) record the controller, the interface, the hub flow and the scene-layer fix.

## Boundaries

- `LoadCtrl2`/`LoadIntf2` come from m2c drafts, the ELF string/constant tables (message ids `0x51C..0x530`, whose texts are in
  the pack's `txt_mem.lua`) and the pack's Lua; the tests assert the retail order of the controller's sends and the observable
  results, not retail instruction results.
- `GAMEDATAINIT` of players 1..3 is accepted only for blank, unused records; resetting a record that holds data is not recovered.
- Retail run (PCSX2, fresh level-1 save from `warp_test/fresh_save_before_enter_world_1.p2s`): the Terminal's
  `n_digilff[0]` (the "Call Keeper", banner "Call Keeper") asks "Do you wish to call a friend to this server?" and offers
  "View Call Keeper Menu." / "Exit Call Keeper."; choosing the first loads `stagIS13`, which shows the four player panels
  (player 1: Lv. 1, HP/MP, name and species) and "To log into the Digital World press the START button."; START loads
  `stagML11` and returns to the Call Keeper station. The player's position read from live memory straight after the
  arrival is exactly (250.0, 40.0, 70.0), the same as the port's arrival at generate position 4
  (250.000, 40.000, 70.000).
- Windows are authored on the `GM01`/`BG02` layers; interface scenes draw every attached layer
  (`dw4_modelview_open_scene`). The rendered frame (four player panels, the character status window and the START notice)
  was inspected on the headless CPU path only; it is not compared against retail pixels and not run on the GLES3 backend.
- Only player 0 is wired; co-op is out of scope by decision.
