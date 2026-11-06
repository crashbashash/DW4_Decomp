# Native Digi-Lab (hub service)

Central's second Digi-Elf, `n_digilff` slot 1 in `stagML12`, offers the Digi-Lab (SUBWND mode 2, `LABO`): digivolve the
partner Digimon into another form it has unlocked, or exchange its weapon. It is reached only through original data:
live Cross probe → `hit_n_digilff.lua` → `n_digilff_01.lua` → the first prompt entry → the lab script (`entry_0824`
chunk 62), which closes the dialogue, restores control and issues `SUBWND GENERATE LABO/I<player>`. The native window
tree then runs the recovered `beNDMWShopCtrlDigilabo` update (`431760..432950`) with its `beNDMWShopCtrlEvolve` child
(`42f710..430d20`). Unlike the other services LABO has its own root constructor (`3b7750`, see the
[SUBWND lifecycle](../../docs/engine/subwindow-lifecycle.md)); natively the controller runs inside the
[shop root](shop-root.md) with entry code 2, which builds Digilabo's own widgets (the `j_shback` backdrop and `i_bgclear`,
the Select/Confirm/Cancel legend and the "Digi-Lab" header), and it shares STATUS's scene freeze, restore and
`SUBWND UPDATE` refresh. When the lab closes after a change the original closing script runs and Central travels on.

## Ownership

| Piece | Source | Role |
| --- | --- | --- |
| Controller and Evolve child | `src/laboshop.c`, `include/dw4/laboshop.h` | `Digilabo` primary/main/sub states, `Evolve` list/confirmations/commit, child creation and completion by child count. |
| Talk-window selectors | `src/statusview.c` (`DW4_STATUS_TALKSELECT03`, `DW4_STATUS_TALKSELECT02`) | `ShopSelect03` (`43eab0`, message in `TALKFONT01 font00`, cursor `i_messky`) and `ShopSelect02` (`43dc10`, `TALKFONT01 font01..` rows on `i_messcr`). |
| List text | `src/statuscontent.c` | `dw4_statuscontent_labo` (retail `430d20`): form rows, page labels, sixteen-value detail panel and `EXPLANATION`. |
| Form preview | `src/playerstats.c` | `dw4_playerstats_form`: a form's saved MHP/MMP, five stats and nine skills (`4435c0` with `3fa3b0`/`3fa850`). |
| Transactions | `src/playertransactions.c` | `dw4_playertransactions_weapon_check` (`3f93c0`) and `dw4_playertransactions_evolve` (the `4313b0` sequence). |
| Hub wiring | `src/hubruntime.c`, `src/shoproot.c` | SUBWND mode 2: the shop root with entry code 2 (ShopTitle00, StatusTitle03, ShopTitle01) and the lab controller as its service; embeds the STATUS equipment menu. |
| Player panel | `src/statusview.c` (`DW4_STATUS_TITLE01`, `dw4_statusview_window_title_variant`) | The lab's StatusTitle01: compact `j_shbase` base (context 1) and the switch to the full `i_stbase` panel and back (`425e60`/`425fb0`). |

Factory mapping used for the class names: `3b31b0` ShopTitle01, `3b3370` ShopTitle00, `3b4950` ShopSelect03, `3b4b10`
ShopSelect02, `3b4d90` ShopSelect01 (menu), `3b4f50` ShopSelect00 (notice), `3b51b0` StatusSelectE1 (list),
`3b8860` ShopCtrlEvolve and `3bace0` StatusCtrlEquip (the "Check" child).

`ShopSelect02` picks its rows by call:

| Call | Rows | Script |
| --- | --- | --- |
| 1 | three (`font01..03`) | `0x7F2` |
| 2, 3, 4 | four (`font01..04`) | `0x7EE` |
| 1262, 1268, 2003, 2005, 2008 | two (`font01..02`) | the call number |
| -1 | player chooser | |

## The GAMERAM commands behind the commit

The retail dispatcher `3fca10` switches on a 22-entry command table (`4cc410`: 11 `RECALCPLAYER`, 12 `BASE2CURRENT`,
13 `CURRENT2BASE`, 14 `WEAPONEQUIPCHECK`, 15 `WEAPONEQUIPSTRONG`). Their bodies:

- **CURRENT2BASE `3f8760`**: `BASE_LEVEL[d]`, `BASE_EXP[d]`, `BASE_SKILL[d*9..]` and `BASE_UPCNT[d*11..]` take the current
  `LEVEL`, `EXP`, `SKILL` and `UPCNT`, where `d` is `DIGIMONNO`. Already native as
  `dw4_playertransactions_current_to_base`.
- **BASE2CURRENT `3f82a0` (+ name lookup `3f80e0`)**: the argument is a model name. `3f80e0` returns the first of the sixteen
  `shinka` rows with that `MODEL_NAME` (else 0). The row's saved level, EXP, skills and upgrade counts become current,
  `DIGIMONNO` is set and `DIGIMONNAME` receives the `MODEL_NAME`. For player zero the common `FLAG`/`FLAGFOLDER`/`COUNTER`
  views are re-bound to `BASE_FLAG*`; the native records already model that alias.
- **WEAPONEQUIPCHECK `3f93c0`**: true when some owned weapon (`DEVICEFOLDER` kind 0) has `(1 << species) & SOUBI` and
  the skill level at its `SKILL` index is at least `SKILLPOINT`; the skills come from `SKILL` for the current form
  and `BASE_SKILL[species*9..]` otherwise (`dw4_weapon_eligible`).
- **WEAPONEQUIPSTRONG `3f8c90` (flag 1)**: every weapon is un-equipped, the three sockets are emptied and the eligible
  weapon with the highest `TSUYOSA` (the first one on ties) becomes the only equipped weapon; `POWERSOCKETNAME` then holds
  just its `MODEL` (or nothing).
- **WEAPONEQUIPSTRONG `3f8c90` (flag 0, the call from `FUN_003f9570`)**: rebuilds the sockets differently. It clears
  `POWERSOCKET` and `POWERSOCKETNAME`, then fills up to three sockets with the first weapons of `POWERPOCKET` in list
  order, adding each one's `MODEL` and marking it equipped.
- **`431670`**: empties and un-equips a list; it is applied to `MAINSLOT`, `SUBSLOT`, `POWERPOCKET` and `MAINPOCKET`.

## Controller (Digilabo)

Field names follow [the BANK controller](bank-shop.md): the primary state is `+1c`, `main`/`sub` are `+20`/`+24`, `_retCode`
(`+30`) is the selector result, and a child is finished when the child count changes.

- **Init (`4329d0`)**: the joined players, their `DIGIMONNO` and weapon sockets are snapshotted for the exit comparison.
  Only one joined player is implemented (co-op is out of scope); the player-chooser (`ShopSelect02` call -1, `main 5`) is not.
- **Menu**: every time the menu starts, `433290` presents the talk window (`i_messwn SQ_OPEN`, closed with `SQ_CLOSE` when
  the lab closes) and `433120` creates the lab's StatusTitle01 with context 1 (the compact name/level/portrait base
  `j_shbase`) or, when it exists, switches it back to that base (`425fb0`). `i_messwn` is polled with `ISSEQNAME SQ_OPEN`
  until that sequence ends, then `ShopSelect02` call 1 shows three `TALKFONT01` rows (script `0x7F2`): Digivolve Digimon,
  Exchange Weapon Unit, Return to Main Lobby. Cancel also leaves.
- **Digivolve**: opens the Evolve child. After a successful evolution it asks (`ShopSelect03` `0x4ED`, then yes/no `1262`)
  whether to check the weapon; yes opens the equipment menu, no returns to the lab menu.
- **Exchange Weapon Unit**: the player panel switches to the full STATUS panel (`425e60`: `i_stbase SQ_LOPEN`, the stat
  rows shown), then the STATUS equipment menu is embedded (`dw4_statusequipmentmenu_window_open_entry`, retail
  `beNDMWStatusCtrlEquip` `3bace0` bound with entry code 1 at `431e5c`). With entry code 1 (`+2c`) the equipment
  controller `40ee60` creates StatusTitle02 (`3b3900`: the bottom band, `i_messwn SQ_STOPEN`, closed with `SQ_STCLOSE`
  with that child) instead of its Title04 header (`3b3530`, call 30), and waits for `SQ_STOPEN` before its menu, so the
  "Digi-Lab" header stays. When it closes the talk window reopens (`433290`) and the equipment counts as checked.
- **Return to Main Lobby (`main 6`)**: only after an evolution or a check, the species and the weapon multiset
  (record ids) are compared with the snapshot (`432d30`). Unchanged: message `0x4FB`, `RECALCPLAYER`, close. Changed:
  message `0x4F3`, yes/no `1268`; no returns to the lab menu, yes recalculates and closes with the closing script.
- **Close**: the controller closes its children, and after a confirmed change queues the original closing script
  `demo_digilab.lua` (retail `389ff0` with pack `stagML12/lua`).

## Evolve child (`42f710`)

- **Opening**: the message window becomes the bottom band (`i_messwn SQ_STOPEN`, closed with `SQ_STCLOSE` with this window);
  the list is built once `ISSEQNAME SQ_STOPEN` no longer reports that sequence. Without this step the lab menu's large talk
  window stays behind the list and the description (a dark window from x=0 over the lower half).
  When the child closes, Digilabo reopens the talk window (`433290`).
- **List**: the player's forms (`BASE_ISUSE` members; species 3 first), eight per page, `STWINFONT20` name, `STWINFONT43`
  "Lv" and `STWINFONT21` level, page labels `STWINFONT31`, the highlighted form's sixteen values in `STWINFONT22` and its
  `shinka` `EXPLANATION` in `STWINFONT29 font000`. The frame is `j_shwin` (`SQ_SINKAONOPEN` with two pages,
  `SQ_SINKAOFFOPEN` otherwise), the arrows are `i_stcursorleft/right` at (-308,25) and (-51,25), and the list selector is
  `StatusSelectE1` at (-283,92). Levels, stats and skills come from the saved `BASE_*` arrays, never the current record
  (so the current form shows its saved level until `CURRENT2BASE`).
- **Selection**: the current form gets `SOUND CURSOR_NG` and notice `0x7E4`; a form with no usable weapon gets
  `CURSOR_NG` and notice `0x7E5`. Otherwise: yes/no `0x4E7`, notice `0x4E9`, yes/no `0x4EA`.
- **Commit (`4313b0`)**: one atomic `dw4_playertransactions_evolve` (CURRENT2BASE, BASE2CURRENT, RECALCPLAYER,
  WEAPONEQUIPSTRONG, list clearing, RECALCPLAYER), then `SUBWND UPDATE` and notice `0x4EC`. The change is final; the later
  "Return to Main Lobby" confirmation does not undo it.

## The result in the world

The lab changes only the record; the world shows it when the next stage is prepared. The live Central world keeps the old
model until then (retail also leaves the stage). The closing script `demo_digilab.lua` (entry 824 chunk 61) compares each
joined player's `SYSgetPlayerDigimon` with `COUNTER[8+player]`:

- **No Digimon changed** (only a weapon exchange): `PLAYERPOINT I<3>`, `NEXTSTAGE stagML12`. Central is prepared again
  from the records, so its lobby stands the same form with the new `POWERSOCKETNAME[0]` weapon graph and that weapon's
  motion label.
- **A Digimon changed**: `PLAYERPOINT I<0>`, `NEXTSTAGE stagML14`. `stagML14` is the digivolution demo, not a playable
  Central. It runs natively (next section) and ends at its own exit, Central point 3.

## The digivolution demo (stagML14)

`stagML14`'s stage list is NDMW 831 (sound bank, `DM_EVOLV`/`AM_EVOLV`) and 832 (scripts, the `entry` demo camera, two
camera boxes, no material regions, the effect models). It has no player: its `funcPlayerSet` and layer functions are empty
(832 chunk 1). The lobby cannot host it (it requires Central's world graph, regions, player and HUD; it fails with
`camera/material bounds`), so the hub runtime opens it as a scene host, `dw4/evodemo.h` (`port/src/evodemo.c`), like the save
screen: the same file-list, stage-object, controller and DM owners as a hub, with no lobby. What the original scripts do,
all run from the pack:

- **Model choice** (832 chunk 0, run by the file list): for each joined player, `COUNTERget(8+player)` (the species before the
  lab, stored by the lab's opening script, entry 824 chunk 62, before `SUBWND GENERATE LABO`) and `SYSgetPlayerDigimon` go through the chunk's own species table (sub-function 7: species
  0..15 -> `s_agumon` .. `s_susanoo`); when they differ both `_common/s_<name>.igb` packs are queued with `CFLsetName` and
  kept in `g_oldNameP1`/`g_nowNameP1`. The `s_` packs are the demo's own skinned, single-node show models (not the 16
  player packs `m_<name>`/`p_<name>`); each carries a `beModelCtrlInfo` with five RAM slots.
- **Start** (chunk 2): `FLGset(364,0)`; `i_evowipe` (`SQ_BLOUT00`), and with one joined player `g_changebg`, `i_evoline`,
  `g_dchange` and both forms (`SQ_HIDE`) are generated in RAM slot 4 with `GENERATE SEQ/V<position>/V<rotation>`.
- **First** (chunk 3): `CAMERA SETDEMOCAMERA entry`; `SOUND PLAYatPAUSE DM_EVOLV`/`AM_EVOLV`, wait `ISALLREADY`, then
  `PAUSEOFF` (AM_EVOLV 25 ticks later); `i_evowipe SQ_BLIN20`; the swap (chunk sub-function 0): `g_changebg SQ_OPEN`,
  old form `SQ_ENTR` until done, `SQ_ERAS`, `i_evoline SQ_CLOSE`, `g_dchange SQ_ACT2`, a white wipe (`SQ_WTOUT00`), the
  effects erased, `g_changebg2` generated, `SQ_WTIN20`, new form `SQ_ENJOY` until done, `g_changebg2 ONFREEZE`; then
  `i_evowipe SQ_BLOUT20` and, 120 ticks later, `PLAYERPOINT SETGENERATEPOS I<3>` and `STAGECTL NEXTSTAGE stagML12` on the
  hub's travel owner. The demo lasts 794 ticks (13.2 s) in the test; both cues are about 14.3 s long.

Native owners for it:

- `MODELCTRL GENERATE "SEQ/V<position>/V<rotation>"` (the form chunk 2 uses) is accepted like the existing `V<p>/V<r>` form.
- A stage without fonts still receives the engine's stage-start `TEXTCTL INITIALIZE`; the demo answers it and nothing else.
- `CAMERA`: `SETDEMOCAMERA entry` starts the `beCameraDemoData` clock (`_totalSec` 1 s), `ISDEMOCAMERA`, `ON/OFFREEZE`.
  The view is the deepest `igCamera` of the `entry` graph (`animCamera01_60 -> ... -> cameraanimShape01`) with the graph's
  sequences driven to that clock, inverted as the lobby's stage camera, with the engine projection (`DW4_SCENE_CAMERA_FOV`,
  horizontal 0.7·w/h) and that camera's near/far.
- `SOUND`: `dw4_frontaudio_prepare_stage` decodes the two named clips from the stage's bank (`DM_EVOLV` NDMW 40, `AM_EVOLV`
  NDMW 8, level -30) on the loading worker; `dw4_frontaudio_stage_service` holds `PLAYatPAUSE`, answers `ISALLREADY` and
  starts the clip on `PAUSEOFF`. The hub hands the session's device to this owner on publication and on to Central after.
- Drawing: `dw4_modelview_open_world` draws every layer in layer order, poses skinned meshes from the bank's
  `_animationDatabase` at the controller's motion time, blended from the previous motion (`dw4_actoranim`, the lobby's
  instance rule), places each world
  instance's `beModelCtrlNode2` at the actor matrix (the lobby's rule; the authored per-slot layout offset, x = 60 for slot 4, is replaced), and
  projects models without an authored camera through the demo camera; window models (`i_evo*`, WN02) keep their own camera.
  The frame is cleared to `beBkColorInfo._rgba`. The stage objects of the demo expand `igActor` skins
  (`dw4_stageobjects_actor_skins`) so the `s_` packs have geometry.
- The `s_` packs' scene graphs are referenced by no layer path; their top `igAttrSet` is named `PC01`, and the demo joins
  them to that layer by name, the binder's rule for authored roots.

**Fallback.** `DW4_EVODEMO=skip`, or a demo that cannot be prepared, prepares the request as its authored exit instead
(Central point 3) and logs `hub: stagML14 (digivolution demo) ...; continuing at its exit stagML12 point 3`, with the
reason. Central stands the record's new form either way.

The prepared lobby takes the form from `DIGIMONNAME` (shinka row 0..15 for the model pack and, through
`dw4_lobbyui_restore_hud`, the HUD portrait), the weapon from `POWERSOCKETNAME[0]`, and the HUD level/HP/MP from
`dw4_playerhealth_restore`. `dw4_lobby_player_row` and `dw4_lobby_hud_meter` expose the row and the meters for tests.

**Unarmed.** `WEAPONEQUIPSTRONG` leaves nothing equipped only when no owned weapon suits the form; the lab refuses such a
form (notice `0x7E5`) and the STATUS Power menu refuses an empty first socket, so an unarmed record comes only from
imported or edited state. Retail's player setup (`beNDMWMdlPlayer` vfunc 36, `3d3d88..3d3d98`) reads `POWERSOCKETNAME`
and skips `PLAYERARMS GENERATE` when the list is empty, so no weapon model and no weapon label is applied; a sequence
without a selected label enters at its first command, and the recovered dispatcher accepts the first `LABEL` section only.
In all sixteen player packs the first section of `SQ_WAIT`, `SQ_WALK`, `SQ_ENTR`, `SQ_JUMP` and `SQ_FALL` is `dual`
(`WAITD1`, `RUNND1`, ...). Natively, an empty `POWERSOCKETNAME` opens `dw4_lobby_open_row_stage_unarmed`: no weapon graph,
the first `SQ_WAIT` label of the player pack, and its wait and run motions (`waitD`). `dw4_lobby_weapon(..., "")`
publishes the same state live (the STATUS/lab appearance callback). The `dual` pose is derived from the recovered
dispatch; a retail character without a weapon stands in the same pose (see [Retail comparison](#retail-comparison)).

## Verification (all headless)

- `make -C port check-playerinit`: weapon check with the current and a saved form, refusals, atomic failure,
  CURRENT2BASE/BASE2CURRENT contents, cleared chip lists, weapon selection, evolving back, an empty inventory, and the form preview.
- `make -C port check-hublabo`: through the real Cross probe and original scripts it checks the lab menu rows, the list texts
  and sixteen detail values against `dw4_playerstats_form`, the three confirmations, the committed record, the post-evolve
  prompts, the exit confirmation and the closing script (`stagML14` requested because the Digimon changed); the same-form
  and no-weapon refusals; both decline paths; cancel; the unchanged exit (no stage request); and the weapon-exchange entry,
  whose swap of the first weapon makes the exit ask for confirmation and request `stagML12`. After the evolution and after
  the exchange it then performs the application's travel step (a destination prepared from the source runtime's records,
  state, input and clock; the source released) and checks the new world: the lobby's player row and model name match the
  record's form, the weapon graph is the record's `POWERSOCKETNAME[0]` with triangles submitted in a drawn CPU frame,
  the HUD meters match the record's HP/MP. After the evolution the `stagML14` request opens the native demo
  (`dw4_hubruntime_demo`, no lobby): chunk 0 chose `s_dorumon` -> `s_weregaru` from the lab's COUNTER and the record, the
  old form plays `SQ_ENTR` and the new one `SQ_ENJOY` (never both drawable), the white wipe runs, the `entry` camera ran
  to its end, both cues were started, a CPU frame with each form differs from the background over at least 5% / 20% of
  the frame, and the script's own exit requests Central point 3, where the new form stands. A fallback case sets
  `DW4_EVODEMO=skip` and checks the logged substitution arrives at Central point 3 with the evolved form. A third case evolves with no
  owned weapon (the transaction run directly, as the lab would refuse it): the destination opens unarmed with the `dual`
  label and no weapon graph, the player walks, and the live appearance goes armed (`w_common04`) and back to unarmed.
- `make -C port check-hubnpcs` classifies the lab NPC as an implemented service.
- Every drawn lab frame (`labo-menu`, `-list`, `-confirm`, `-evolved`, `-same`, `-check`) must show the header, the player
  name and the legend (`assert_shop_chrome`) and match the GPU backend; `labo-back` (the menu after the equipment check)
  checks the compact base, the header and legend and the absence of the full stat rows and the equipment description;
  during the check the header text must still be the lab's. `./build/test_hublabo <roms> <dir>` writes `xdata-labo-*.png` (CPU) and
  `gpu-labo-*.png`, and the demo frames `xdata-evodemo-old.png` (Dorumon in the letterbox over the `g_changebg` text
  columns) and `xdata-evodemo-new.png` (WereGarurumon over `g_changebg2`'s rings). The demo frames are CPU only; the hub
  GPU comparison helper is lobby-bound.

## Retail comparison

Retail GS captures (640x480, a level-99 Susanomon "BigDaddy" with maximum stats) are measured against the port frames with
`tools/compare_retail_frames.py RETAIL_DIR PORT_DIR` (both directories are arguments; the tool and the repository hold no
retail pixels). The port frame (640x448) is resampled to 640x480. Two masks apply to both frames: the animated green
backdrop (G >= 24, G > R + 16, G > 1.6 B; window interiors and frames never pass) and per-pair data rectangles (player name,
level and portrait, stat numbers, list rows, prices, description text), which are left out of the chrome difference only. Per
region (window, band, text block) it reports the edge-map shift (`dx`, `dy`, normalised cross-correlation over +-8 px with a
parabolic sub-pixel fit), the strongest frame lines, the text rows (top..bottom) and the mean absolute luminance difference
over the unmasked chrome (`mad`, both regions normalised). `--self-test` checks a synthetic window moved by (+3,-2).

Pairs (retail `rc-<id>` against the port frame):

| Pair | Retail | Port | Regions: largest abs(dx), abs(dy) | Text rows |
| --- | --- | --- | --- | --- |
| lab-menu | `labf1` | `xdata-labo-menu` | 0.1, 0.0 (base, header, legend, talk window) | 3 talk rows, identical tops and bottoms |
| lab-back | `q1` | `gpu-labo-back` | 0.1, 0.1 | 3 talk rows, identical |
| lab-list | `labg0` | `xdata-labo-list` | 0.1, 0.2 (list, Details, description, band) | Details 7 rows and description 3 rows within 1 px |
| lab-same | `labg1` | `xdata-labo-same` | 0.1, 0.0 (adds the notice) | notice row identical, band within 1 px |
| lab-check | `lw0` | `xdata-labo-check` | 0.1, 0.1 (STATUS panel, slot menu, description, band) | 10 panel rows within 1 px |
| chip-list | `chipb0`, `chipm1` | `xdata-chip-list` | 0.1, 0.1 (chip list, prices, page) | 10 chip rows within 1 px |
| chip-quote | `v1` | `xdata-chipquote` | 0.1, 0.2 (Data Keeper list, Data column, quote) | 3 quote rows within 1 px |
| dk-chrome | `dkm0` | `xdata-stats` | 0.1, 0.1 (top chrome and STATUS panel only) | 10 panel rows within 1 px |

Frame lines (window borders, title tabs, the talk window at y 331..467, the description window from x 252 and y 372, the band at
y 440..467) are at the same rows and columns in every pair; correlation peaks are 0.9..1.0 for the header, legend, talk window,
notice and band. No layout offset above 1 px exists. The 1 px differences are row tops of
different glyphs and the 448-to-480 resampling. The header `mad` is 3.5..4.6 where the text matches.

During the equipment check retail keeps the "Digi-Lab" header: it binds the equipment menu with entry code 1 (`431e5c`),
where `40ee60` creates the band (StatusTitle02) instead of the STATUS Title04 header. The port binds it the same way; the lab-check
header `mad` is 3.5 and its text rows match. Binding with entry code 0 creates the Title04 header, which reads "Equipment"
(header `mad` 11.2).

Differences that are content or phase, not layout: the data, the backdrop's animation phase, the cursor pulse phase
(`i_stcursor01`, `i_stcursor05`), the `base` region (portrait and name; `mad` 11..14 because the portrait sits partly outside
the data mask), and the STATUS panel's HP/MP labels: retail draws "HP"/"MP" on the panel's dark interior, while the port
shows the backdrop colour (0,48,15) behind the label glyphs on both backends (`panel-hpmp` correlation 0.4). That is a
texture-alpha difference in the shared STATUS panel (`i_stbase`/`j_shbase`), not specific to the shops, and it is not
fixed. The chip-list frame also shows an empty description window for the first chip, where retail `chipm1` shows the
first chip's description with the cursor on it; this was not traced.

Not compared: the evolution confirmations, the evolution notice, the post-evolve prompts and the exit messages (no retail
frames); the retail Data Keeper menu (`dkm0`) has no matching port state, so only its top chrome and STATUS panel are compared;
the equipment check's Weapon Slot/Mods lists and option menus (`lw1`..`lw7`) have no port frame (the test drives the
equipment transaction directly).

**Unarmed player.** The lab cannot produce one (with a single weapon the retail Exchange Weapon Unit option menu
greys "Remove Equipment"), but a card save with no weapon equipped can. A retail Susanomon loaded from such a card (the port save writer,
weapons removed from the device folder and every equipment reference cleared) stands in its idle pose with the arms down and no blades;
`dw4_lobby_open_row_stage_unarmed` renders the same pose (idle motion `waitD`, no weapon graph: `DW4_LOBBYROWS_UNARMED=1
DW4_LOBBYROWS_IDLE=1 ./build/test_lobbyrows` writes it with `DW4_LOBBYROWS_FRAMES`). Compared by eye; the facing differs because the
test arrival heading is not the retail character's.

**Digivolution demo audio.** The emulator's output was routed to a silent null sink and recorded while a card
character evolved. The recording shows the lobby music, then one loud sound starting when the demo begins (about 8.3 s into the recording) and
ending, after a fade, at about 22.5 s: a span of about 14.2 s, then about 6 s of silence while Central loads and Central's music. The
port's two demo clips are `DM_EVOLV` (686,080 frames, 14.3 s at 48 kHz) and `AM_EVOLV` (618,048 frames, 12.9 s), both started together by
the scripts' `PLAYatPAUSE`/`PAUSEOFF`; the retail span matches the longer clip starting with the demo. The recording was checked by its loudness
envelope only (the mix cannot be separated into the two clips), and no retail recording is kept in the repository.

## Boundaries

- The lab's engine routines are checked by native unit tests against recovered semantics, not by a retail
  instruction-level oracle; the recovered reference is the decompiled bodies cited above.
- The Digilabo root window itself (`3b7750`) is not a separate native window: the shop root with entry code 2 creates its
  widgets and sends its `i_bgclear OFFREEZE`, and the controller is that root's service child.
- After an equipment check the retail lab menu shows only the compact base, the "Digi-Lab" header with
  its frame and the legend, and no equipment description. The port closes the other base when the title variant switches and
  hides `STWINFONT29/font000` when the check ends; which retail call hides that description is not traced.
- `ShopSelect02` call -1 (player chooser) and multiple joined players are not implemented. `main 5` and the player rows
  in `4329d0` therefore exist only for one player.
- `PLAYERARMS GENERATE` (arm models regenerated on an unchanged exit) is not implemented in the native hub, so the live
  Central world keeps its weapon model until the next stage is prepared (an exchange through the embedded equipment
  menu still refreshes it through the STATUS appearance callback). The records are always current.
- The digivolution demo runs natively but has not been compared with retail frames; its audio is compared with a retail recording by its loudness envelope only
  (see [Retail comparison](#retail-comparison)). Known approximations:
  the models are drawn unlit (`beLightCtrlInfo` and the stage's light sets are not applied; the `s_` textures carry most of
  the shading), with no shadow (`beShadow01Info`); the camera projection is the lobby's engine projection, not read from
  the `entry` camera; joining the `s_` packs to `PC01` by their root name and placing instances at the actor matrix follow
  the native rules above, not a traced retail path; `ISALLREADY` reports ready because the clips are decoded before
  publication.
- Co-op demos (several joined players, `g_evocount` above one, RAM slots 0..3 and `i_evoclose`) are not reachable: the hub
  runtime admits one player.
- Whether `StatusCtrlEquip` reports its `0x64` result code to the lab only when equipment changed was not traced; natively
  the lab compares the actual state after the check, so a change is detected whenever the sockets differ.
- The closing script is queued as an engine event for the next DM tick (the hub's way to run a named chunk); retail's
  `389ff0` starts it directly.
- The retail comparison (above) is measured, not by eye, but covers only the frames listed there.

## Arena control state

ShopCtrlDigilabo and ShopCtrlEvolve retain counters, selections, evolution/check/demo flags and list pages/cursors in concrete arena instances. Evolve publishes its result to the parent window return code. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).

The initial comparison and form snapshots are arena-owned as documented below.

## Arena comparison and form snapshots

Initial player/species/weapon comparisons use the ordered integer lists and
nested weapon list in ShopCtrlDigilabo. Evolve owns a Shinka controller and typed
form objects containing the existing form calculation's name, level and sixteen
values. Allocation completes before publication and teardown releases the
nested trees. The one-player service/demo boundary still applies.
