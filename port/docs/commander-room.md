# Commander Room (`stagML02`)

The Commander Room is the D.S.G. headquarters reached from the Terminal's "Gate to Commander Room". Its scene pack is NDMW 816
(`lobby-ofanimon-seraphimon`, 160 named Lua chunks) with its support pack 815 (sound bank, model and window infos). The port
prepares it as an ordinary hub runtime (`hubruntime.c`) and runs every room event from the original bytecode. Headless check:
`make -C port check-hubcommander` ([test](../tools/test_hubcommander.c)).

## Travel

| From | Original event | Destination | Arrival group |
| --- | --- | --- | ---: |
| Terminal `stagML11` | `mate01.lua` (pad [-5..15]×[5..25], flag 424 clear) | `stagML02` ("Commander Room", `STCHGFONT00 I<59>`) | 0 |
| Commander Room `stagML02` | `mate00.lua` (pad [30..50]×[40..60]) | `stagML11` ("Main Lobby", `STCHGFONT00 I<321>`) | 0 |

Both scripts first clear the point label (`POINTFONT00` fonts, `i_stpnl06`, `i_pointcur`) and then call the shared
`funcStageChange` prompt, so Circle and No keep the player and Cross queues the fade and the `PLAYERPOINT`/`STAGECTL` requests.
Group 0 is the Commander Room's centre platform (-50, 10, 60) and the Terminal's (60, 10, -30); both run `funcStageIn("trans")`.
The application consumer loads the original USA card `loadingUSA/ldagML02.igb`. The room also has `gatedisc.lua` (chunk 63:
`SYSsetGateStage`, `SQ_EXIT`, `NEXTSTAGE stagML11` point 3), which no region or script in the room calls.

`lobby.c`'s material dispatch runs a stage's own regions through `stage_material_runs`, kept apart from the shared rule:
`matg00` and (with exit events) `mate00` in the Commander Room, and the Terminal's `mate01`. The shared `matf*` rule already runs
the room's `matf00`/`matf01`/`matf02`.

## What runs

| Script | Trigger | Behaviour | Port |
| --- | --- | --- | --- |
| `first.lua` (chunk 61) | arrival, flag 502 clear | Digi-Elf welcome (`n_digilfm` walk-in, demo camera `camsp0201`, TALKFONT02 281–294), sets 502 | runs |
| | flags 2 + 20, 322 clear | Leomon report (`ofani1`, `DM_LEOMN` fades, `ITEM_GET`, "Now we have the Boat Key!", `SYSctlFlagFolder SET 2`), sets 322 | runs |
| | flags 3 + 324, 325 clear | Seraphimon's alarm-off scene (`seratalk`, `alarmoff`, `g_indicatorz05 SQ_SWOF`, `AM_OFNI2`→`AM_LOBBY`, `QS_DOIT`, `DM_SERAF`): 325 and 4 set, 3 and 336 cleared | runs |
| `start.lua` (chunk 96) | arrival | lights, flag 1 when no later progress flag is set, `g_cytrerp2`/`g_indicatorz05`/`g_movepass01z05`, 11 `n_digilfm` and 12 `n_digilff` staff, `n_ofanim`, `n_seraph` (flags 3–6, 86), music by progress | runs |
| | flag 324 | `g_movepass01z05 SQ_SWON` and `HITLANDMODEL hitmovepass01z05 OFFHIT` | runs |
| `matg00.lua` | region [-10..60]×[30..70] | `PintmessOpen` "Gate to Main Lobby" (`I<371>`/`I<370>`) at (40, 30, 50) | runs |
| `matf00.lua` | region [190.6..209.4]×[-130..-70], in front of Ophanimon | three branches: first briefing (flag 1, 320 clear; `PLAYatPAUSE DM_OFNI`, `SQ_TURN`, `I<322>`–`I<337>`; sets 320, 1→2); Ophanimon ID hand-over (flags 2+67, 323 clear; `AM_OFNI1`, `indicator` camera, "Now we have the Ophanimon ID!", `I<338>`–`I<351>`; sets 323, 2→3, `SYSctlFlagFolder SET 3`); Lucemon briefing (flags 5+69, 327 clear; `I<352>`–`I<361>`; sets 327, 5→6) | runs |
| `matf01.lua` | region [150..180]×[-130..-70] | empty chunk (76 bytes) | runs (nothing) |
| `matf02.lua` | region [70..130]×[-209.4..-190.6], in front of Seraphimon | Seraphimon report (flags 4+335, 326 clear; `seratalk2`, `DM_SERAF`, `I<362>`–`I<369>`), 4→5, 326 set | runs |
| `mate00.lua` | exit pad | label clear, prompt to the Terminal | runs |
| `hit_n_ofanim`/`n_ofanim_00` | Cross | Ophanimon's progress talk by flags 1–6, 20, 67, 68, 86 (`I<430>`–`I<436>`, `I<338>`; flag 1→2; 2+20+67 → 3 and 22; 4 without 68 sets 334) | runs |
| `hit_n_seraph`/`n_seraph_00` | Cross | Seraphimon's talk | runs |
| `hit_n_digilff`/`hit_n_digilfm` → `n_digilf?_NN` → `bML02*` | Cross | the tutorial staff (Status, Digivolution, …) with their "Do you want to hear the explanation again?" loops; the two front Digi-Elves' plain talk | runs |

The flag conditions and writes in this table were read from the chunks' Lua 4 instructions (`FLGisOn`/`FLGset`/`SYSctlFlagFolder`
with their `PUSHINT` operands; all regions also require `MATisPlayer` and an idle DM queue). `lua/`
show only `matf00`'s third branch, and their chunk numbering for pack 816 has 155 files against 160 named chunks
(for example `003-chunk.lua` is not `matf01.lua`'s content). Read the bytecode, or the raw strings of the pack, when a
decompiled 816 chunk looks incomplete.

## Native owners for the room

- **Named demo cameras.** `load_demo_cameras` publishes every `beCameraCtrlInfo` of a non-Terminal hub whose slot 7 is a
  `beCameraDemoData`: its end time (ordinal 3) and the `igCamera` of the scene graph with the same name. `SETDEMOCAMERA <name>`
  restarts it at time zero; `ISDEMOCAMERA` and `SETBOXCAMERA` keep their existing meaning. The room has `camsp0201` (2 s),
  `ofani1` (1/6 s), `seratalk` (10 s), `seratalk2` (1/6 s), `alarmoff` (1.08 s) and `indicator` (1.33 s). The camera graphs
  use the Euler rotation that `camsp0101` uses; a camera with another interpolation is not published, so its use fails loudly.
- **Room audio.** `dw4_frontaudio_prepare_lobby_stage` prepares the room's own bank (`stagml02.igb`, NDMW 815): `ST_COMMA` and
  `AM_LOBBY` on the music and ambience voices, the shared lobby cues, the alternative tracks `AM_OFNI1`, `AM_OFNI2`, `DM_LEOMN`,
  `DM_SERAF`, `DM_OFNI`, `QS_HURRY`, `QS_DOIT` and the room's model sounds (`ofTURN`, `mlGATE01`, `icOFF2ON`, `icON2OFF`, …).
  A streamed track past the first two replaces the music voice (or the ambience voice for `AM_*`). `PLAYatPAUSE` holds a track,
  `querySD ISALLREADY` answers 1 (tracks are decoded during preparation) and `PAUSEOFF` starts it. `BGMSTOP <name>` stops the voice
  playing it; `VOLUMECTL2 "<name>/F<from>/F<to>/F<ticks>"` ramps that voice's gain multiplier linearly over 60 Hz session ticks.
  The engine receivers of `BGMSTOP` and `VOLUMECTL2` are not recovered: this is a host policy with the scripts' own timing.
- **`HITLANDMODEL <name> ONHIT/OFFHIT`.** Each `beHitLandModelInfo` lists the names it answers to in slot 9 (an
  `igNamedObjectList`); the room's `hitmovepass01z05` is a wall graph. The hub runtime's receiver removes or restores that graph
  in the walking collision (`dw4_lobby_collision_hit`, 710 → 702 wall triangles). Other keys fail.
- **`SYSgetTarget`.** The value function at `0x00371ef0` is `jr ra; li v0,1`; the USA PS2 build answers 1. A tutorial page
  (`bML02012`) chooses its line by it.

## Validation

`check-hubcommander` boots a created Dorumon in the Terminal, plays the introduction, stands on `mate01`, accepts the prompt and
prepares the Commander Room from the pending request (as the application consumer does). It then checks the welcome (demo camera,
14 pages, flag 502, restored HUD/box camera/control/materials), `ST_COMMA`/`AM_LOBBY`, the 23 staff Digi-Elves and Ophanimon,
the `matg00` label and arrow (`i_pointcur` instance 4, `SQ_OPEN4`) and its removal, the first briefing (`DM_OFNI` while Ophanimon
speaks, flags 1→2, `ST_COMMA` back), Ophanimon's talk, the exit prompt with Circle (stays) and Cross (`stagML11` point 0) and the
return to the Terminal with the progress kept. Five later story states run with progress-flag fixtures and check their first and
last pages, the flags they set and clear, the key items handed over (`FLAGFOLDER` 2 and 3) and the removed wall: with flag 324 a
stick walk from the ring crosses the moving pass to Seraphimon's desk, without it the wall stops the player at z = -124. Frames are drawn on the CPU and compared with the GPU backend
when a context exists; with a capture directory they are written as `commander-*.png`.

`check-hubnpcs` includes the room: every awake talker with both prompt answers. The dialogue end-to-end test
(`tools/test_dialogue_e2e.py --only Commander`) warps the real engine into the room (`DW4_DEV_WARP=StagML02:0`), lets the welcome
play and talks to the front Digi-Elf (`n_digilff` 0).

## Remaining differences

- Story states other than the fresh one are reached with flag fixtures; the field stages that set flags 2–6, 20, 67, 69, 324 and
  335 are not ported.
- `BGMSTOP`/`VOLUMECTL2` are host policies (see above); exact retail mixing is not claimed.
- Co-op: the room's scripts position four players (`MOVETRANS` per player) and draw four point labels; the runtime admits only
  player zero, as in the other hubs.

## Retail comparison

Retail (PS2 USA, a card character; story flags set with the retail state tool) against the port's `check-hubcommander` frames and assertions:

- **Gate and arrival.** The Terminal's Commander Room gate shows the "Commander Room" prompt ("Go to the destination." / "Stay here."); the
  arrival frame has the same camera, the red-button pad, the walkway outline, the Digi-Elf at the far end and roaming staff Digi-Elves.
- **Welcome (flag 502 cleared).** A top-down demo camera, then the elf's pages "So you're the new D.S.G members!", "You'll be a great
  help.", "We're locked inside this server due to a system error...", "Not many D.S.G. members are left here, so everyone was worried."
  The port's welcome shows the same pages in the same order (its pages 1-3 are the 2nd-4th above).
- **Label and exit.** Standing on (10,.,45) retail shows the bottom band "Gate to Main Lobby" with the arrow at the top right, as the port's
  label frame does (text, band and arrow positions agree); on (40,.,50) retail shows the "Main Lobby" prompt with the same two choices.
- **Story event (Ophanimon's first briefing).** With flag 1 set and 320 clear, stepping to (200,70,-100) opens Ophanimon's briefing ("So you
  have just joined the D.S.G. I've been waiting for you.", "Welcome to the D.S.G.! I'm the commander, Ophanimon." ...) and leaves flags 2 and
  320 set and 1 clear, exactly what `check-hubcommander` asserts.
- **Text start.** Retail's line starts are clean; the port's Commander Room talk frame is clean too. The dialogue draw insets the glyph UVs
  by a quarter texel (`dialogue.c`): a glyph rect whose left edge lands exactly on a texel boundary otherwise rounds to sample one column of
  the neighbouring atlas glyph, which shows as thin ticks beside narrow letters in NPC text ("I n|e|ed") on both renderers at 640x448 and
  640x480. Checked on rendered frames of the first Terminal's Agumon talk.

- **The five later story events** were run in retail with the same flag fixtures as `check-hubcommander` and the resulting flags compared:
  Leomon report (flags 2+20 -> 322 set), Ophanimon's ID hand-over (2+67 -> 3 and 323 set, 2 cleared), the alarm-off scene (3+324 -> the scene
  "Energy fully charged! Divine Aura full-blast!!" plays on arrival, 4 and 325 set, 3 cleared), Seraphimon's report (4+335 -> 5 and 326 set,
  4 cleared) and Ophanimon's Lucemon briefing (5+69 -> 6 and 327 set, 5 cleared). Every result equals the port's assertions.

Pixel difference (640x480, HUD region masked because the character differs; the port frame is its CPU capture, the retail frame a PS2 GS
dump scaled): arrival median 0.0 levels, mean 5.9, 80% of pixels within 3.3; label frame median 0.7, mean 7.4, 80% within 5.3. The residual is the
character and NPC models and the text antialiasing, not the room.

Three more pairs: Ophanimon's briefing page against the port's briefing frame matches (median 0.7, mean 8.1 levels, HUD included). Two
position frames ((-50,20,0) and (100,20,-60)) show the same room but not the same camera framing or standing position (retail lands the player on the
floor with its camera still settling; the port frame is at the placed height after a fixed idle), so they are not usable as pixel comparisons and
were not counted.

Welcome timing (no input pressed, retail screenshots every 1.2 s): the retail loading card stays up until about 17 s after accepting the prompt;
the world then appears with the Digi-Elf walking in; the first page ("So you're the new D.S.G. members!") appears about 6 s after the world and then
waits for Cross (still up 25 s later: retail does not auto-advance). The port's first page appears 8 s after the room's first tick (that includes the
fade-in and the walk-in) and also waits for Cross, which agrees within the screenshots' resolution (about 1.2 s). Retail's loading-card frames
are not message frames; counting them as message frames makes the cadences appear to differ.

Which script and stage sets each flag the later states test: [story flag sources](story-flag-sources.md).

`check-hubcommander` also runs the chain across hubs with no flag set by hand between the steps: with story flag 1 only the Terminal's Outside World pad is inert; after Ophanimon's first briefing (flag 1 -> 0, 2 -> 1) and the exit to the Terminal, the same pad opens the field list and accepting requests `stag0001`.

**Moving pass at the start of the game.** Retail hides `g_movepass01z05` until flag 324 is set (its `SQ_WAIT` default label plays `WAIT01`, joint frames 10-20, which is the folded-away pose; `SQ_SWON` selects `WAIT02`, frames 30-150). The port does the same: `dw4_scene_node_drive` sets a world instance's animation clock and updates its effective node time itself, because the whole-scene pass that recomputes node times never sees the instance copies (without that update every instance animation stays at its authored pose and the pass draws at full extent in every state). The Terminal-side pose at (100, 60, -100) shows no pass, as in the retail frame; the flag-324 state is covered by `check-hubcommander` (walk across the pass) but its visuals were not pixel-compared with retail.
