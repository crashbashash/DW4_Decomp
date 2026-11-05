# Story flag sources

Where the original scripts set the flags that drive the Commander Room's story states and the Terminal's Outside World gate, and which
stage must run for each. Source: `lua/` write sites (`FLGset(N, 1)`), checked against the stage manifests in `NDMW.AFS`
(entries 150-164 list each stage's packs). Every row is a static script reading; none was replayed through a full retail playthrough.
The debug stage-select scripts (`14-misc/01-stage-select-list_e603/*flag-1-N.lua`) also set these flags, as presets for jumping into
the story; they are not a source in normal play and are left out below.

The port today reproduces the Commander Room end of each step with flag fixtures (`check-hubcommander`); the rows marked *field* or
*dungeon* need a stage the port does not run yet (it shows "Destination not available").

## The chain

| Step | Flag effect | Set by | Stage | Kind |
| --- | --- | --- | --- | --- |
| New game | 1 set | `05-lobby-quests_e820/009-layer-setup.lua`, on entering the hub while 2, 3, 4, 5, 6 and 86 are all clear | `stagML11` (Terminal) | hub, ported |
| Ophanimon's first briefing | 1 -> 0, 2 -> 1 (and 320) | `04-lobby-ofanimon-seraphimon_e816/094-npc-ofanim-2.lua` | `stagML02` | hub, ported |
| Leomon saved | 20 -> 1, then returns to `stagML02` | `12-goblimon-fortress/03-fortress-leomon_e786/012-npc-leomon.lua` (when the player enters with 20 clear) | `stagGF03` (pack 786) | field |
| Apocalymon defeated | 67 -> 1 (600 on Hard/Very Hard) | `11-bosses/01-boss01-apocalymon_e730/006-boss-bit.lua` | `stagBS01` (pack 730) | boss |
| Ophanimon's ID hand-over | 2 -> 0, 3 -> 1, 22 -> 1 (needs 2, 20 and 67) | `094-npc-ofanim-2.lua` | `stagML02` | hub, ported |
| Central quest-board puzzle | 324 -> 1, 330 -> 1 (needs 332, 3 and 324 clear) | `06-lobby-quest-board_e824/066-flag-329.lua`, a chain of switch hits 329 -> 331 -> 332 | `stagML12` (Central) | hub, not verified in the port |
| Alarm-off scene | 3 -> 0, 4 -> 1, 325 -> 1 (needs 3 and 324) | `04-lobby-ofanimon-seraphimon_e816/061-layer-setup.lua` | `stagML02` | hub, ported |
| BelialVamdemon defeated | 68 -> 1 (603 on Hard/Very Hard) | `11-bosses/02-boss02-belialvamdemon_e737/000-boss-belvam.lua` | `stagBS02` (pack 737) | boss |
| Ophanimon, second talk | 334 -> 1 (needs 4 and 68) | `094-npc-ofanim-2.lua` | `stagML02` | hub, ported |
| Seraphimon, talk | 82 -> 1 (needs 4, 68 and 334) | `04-lobby-ofanimon-seraphimon_e816/095-npc-seraph-2.lua` | `stagML02` | hub, ported |
| Central Leomon | 335 -> 1 (needs 4 and 82) | `06-lobby-quest-board_e824/099-npc-leomon.lua` | `stagML12` (Central) | hub |
| Seraphimon's report | 4 -> 0, 5 -> 1, 326 (needs 4 and 335) | `04-lobby-ofanimon-seraphimon_e816/070-npc-seraph.lua` | `stagML02` | hub, ported |
| Lucemon defeated | 69 -> 1 (607 on Hard/Very Hard) | `11-bosses/03-boss03-lucemon_e744/017-boss-luce-4.lua` | `stagBS03` (pack 744) | boss |
| Ophanimon's Lucemon briefing | 5 -> 0, 6 -> 1, 327 (needs 5 and 69) | `04-lobby-ofanimon-seraphimon_e816/069-npc-ofanim.lua` | `stagML02` | hub, ported |
| Final boss | 70, 86 -> 1 | `11-bosses/06-boss06-devimon-3_e765/005-boss-devl31.lua`; the Terminal's layer script then clears 6 | `stagBS06` (pack 765) | boss |

Flags 22, 320, 322, 323, 325-327 and 334 are the per-event "seen" markers set by the same scripts; they are not gates for another stage.

## What this means for the port

- **The hub half of the chain needs no new stage.** Every Commander Room step, and the Central Leomon talk, runs in a hub the port
  already loads. The Central puzzle (flags 329-332, then 324) is driven by bullet hits on `g_evenconsz05`; the port does not
  run bullets, so that step is not reachable by play yet. Flag 321, which the puzzle's first switch tests, has no `FLGset(321, 1)`
  write in the scripts; its source is open (it may be set by native code or a service).
- **The field half needs four destinations** to produce flags 20, 67, 68 and 69, in this order of the story:
  1. flag 20: `stagGF03`, the Goblin Fortress's Leomon room. It is reached `stag0101` (Goblin Pass) -> `stagGF01` -> `stagGF02` ->
     `stagGF03` (exits `01-stag0101-valley-entrance_e614/009-exit-to-staggf01.lua`, `12-goblimon-fortress/01-fortress-gate_e772/002-exit-to-staggf02.lua`,
     `02-fortress-hub_e779/006-exit-to-staggf03.lua`). The Outside World gate's first field list entry is `stag0001` (or `stag0101` after flag 503).
  2. flag 67: `stagBS01`, entered from the last floor of the Death Valley dungeon `dng103f2` (`06-dungeon-1/07-dng103f2_e226/061-exit-to-stagbs01.lua`).
  3. flag 68: `stagBS02`, entered from `dng206f2` (`07-dungeon-2/07-dng206f2_e281/027-exit-to-stagbs02.lua`).
  4. flag 69: `stagBS03`, entered from `dng310f3` (`08-dungeon-3/12-dng310f3_e372/028-exit-to-stagbs03.lua`).
  The Death Valley / Dry Land / Venom Jungle dungeons that lead to those boss stages (and the field stages between them) are the larger
  porting work; the boss and Goblin Fortress scripts are small by comparison.
- The Emergency Gate is separate: it needs flag 3 and a recorded gate stage (`SYSsetGateStage`, written by a dungeon on exit), so it
  opens only after a dungeon has been played.

## Method and limits

`grep -rn "FLGset(N, 1)" lua` for each flag, then reading the surrounding condition. Stage names for `NDMW.AFS` pack numbers come
from the `stagBS01`-`stagBS06` / `stagGF01`-`stagGF04` manifests (entries 155-164: packs 729/730 ... 785/786), which also corrects the
`12-goblimon-fortress` folder labels (see [drop tables](../../docs/systems/drop-tables.md)). The older, coarser
[flag meanings](../../docs/systems/flags/flag-meanings.md) table labels 2-5 "intro steps"; the Commander Room scripts show they are
story states 2 to 5 of the chain above. Static reading only: a branch guarded by a flag this table does not name was not followed.
