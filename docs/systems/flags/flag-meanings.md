# Flag meanings — Digimon World 4

Curated story/progression flags plus heuristic labels for the rest.
Confidence: **high** = decoded from direct evidence (set-on-defeat,
level gate, quest completion), **medium** = by pattern, **low** = heuristic.

## Story progression (high value)

| flag | meaning | evidence |
| --- | --- | --- |
| 1 | intro step 0 (game start) | set in lobby cutscene e0816 |
| 2 | intro step 1 | set in e0816; checked by Leomon (e0820) |
| 3 | intro step 2 | set in e0816 |
| 4 | intro step 3 | set in e0816 |
| 5 | intro step 4 | set in e0816 |
| 6 | main story underway (intro done) | set e0816/e0820; checked in city hub e0709 |
| 20 | intro flag (checked with 2 in e0820) | set e0603/e0786 |
| 22 | intro sub-step | set in e0816 |
| 27 | shop NPC dialogue (bank) | e0828 |
| 28 | shop NPC dialogue (disk) | e0828 |
| 30 | shop NPC dialogue | e0828 |
| 31 | shop NPC dialogue | e0828 |
| 32 | shop NPC dialogue | e0828 |
| 35 | shop NPC dialogue | e0828 |
| 64 | shop counter interaction | e0828 |
| 67 | Boss 1 (Apocalymon) defeated | set=1 in boss stage e0730 |
| 68 | Boss 2 (BelialVamdemon) defeated | set=1 in e0737 |
| 69 | Boss 3 (Lucemon) defeated | set=1 in e0744 |
| 70 | Final boss (Devimon) defeated | set=1 in e0765 |
| 71 | city gate/lever state 1 | e0709; also set on quest completion |
| 72 | city gate/lever state 2 | e0709 |
| 83 | Dungeon 4 (LordKnightmon) cleared | set=1 in e0425 (dng412b4) |
| 85 | lobby story beat | set in e0816 |
| 86 | Final boss / main story cleared | set=1 in e0765; checked with 6 in e0709 |
| 89 | valley river event | e0628 |
| 90 | valley river event | e0628 |
| 91 | valley river event | e0628 |
| 92 | valley river event | e0628 |
| 93 | valley river event | e0628 |
| 94 | valley river event | e0628 |
| 95 | valley river event | e0628 |
| 96 | valley river event | e0628 |
| 97 | valley river event | e0628 |
| 98 | valley river story event done | set in e0628; checked in shops e0828 |
| 292 | dungeon checkpoint (block 1-2) | set at dungeon finales |
| 293 | dungeon checkpoint (block 2-3) | set at dungeon finales |
| 294 | dungeon checkpoint (block 3-4) | set at dungeon finales |
| 362 | city intro battle (Infermon/Megadramon) done | set=1 in e0709 |
| 371 | shop quest state | checked in e0828 |
| 375 | shop story event | e0828 |
| 376 | quest 1 done | set=1 in e0820 |
| 377 | quest 2 done | set=1 in e0820 |
| 378 | quest 3 done | set=1 in e0820 |
| 379 | quest 4 done | set=1 in e0820 |
| 380 | quest 5 done | set=1 in e0820 |
| 381 | quest chain complete (final gate) | checked in e0709 |
| 384 | quest 1 sub-step | paired with 376 in e0820 |
| 385 | quest 2 sub-step | paired with 377 in e0820 |
| 386 | quest 3 sub-step | paired with 378 in e0820 |
| 387 | quest 4 sub-step | paired with 379 in e0820 |
| 388 | quest 5 sub-step | paired with 380 in e0820 |
| 389 | quest final sub-step | paired with 381 in e0820 |
| 392 | shop event sub-flag | e0828 |
| 393 | shop event sub-flag | e0828 |
| 409 | quest/act in-progress marker (1=done, 0=reset) | reset in 902/906 fail chunks |
| 415 | quest board completion sub-flag | e0824 |
| 416 | quest board completion sub-flag | e0824 |
| 417 | quest board completion sub-flag | e0824 |
| 418 | quest board completion sub-flag | e0824 |
| 419 | quest board completion sub-flag | e0824 |
| 420 | quest board completion sub-flag | e0824 |
| 424 | quest/act in-progress marker | reset with 409 |
| 430 | quest board completion sub-flag | e0824 |
| 469 | quest board reward 1 | e0824 |
| 471 | quest board reward 2 | e0824 |
| 473 | quest board reward 3 | e0824 |
| 508 | stage-intro tutorial gate | set in every stage; checked in act-start chunk |
| 571 | quest/act in-progress marker | reset with 409 |
| 572 | quest board chain progress 1 | e0820/e0824 |
| 573 | quest board chain progress 2 | e0820/e0824 |
| 574 | quest board chain progress 3 | e0820/e0824 |
| 575 | quest board chain progress 4 | e0820/e0824 |
| 576 | quest board chain progress 5 | e0824 |
| 594 | shop story flag | e0828 |
| 600 | Boss 1 story scene done | set=1 in e0730 |
| 603 | Boss 2 story scene done | set=1 in e0737 |
| 607 | Boss 3 story scene done | set=1 in e0744 |
| 609 | Dungeon 4 story scene done | set=1 in e0425 |
| 610 | Final boss story scene done | set=1 in e0765 |
| 905 | city entryway state | set in e0709 from persistent folder 8/9 |
| 908 | level gate: player Lv >= 16 | e0828 |
| 909 | level gate: player Lv >= 46 | e0828 |
| 910 | level gate: player Lv >= 76 | e0828 |
| 931 | quest board slot 1 availability | e0824 |
| 932 | quest board slot 2 availability | e0824 |
| 933 | quest board slot 3 availability | e0824 |
| 934 | quest board slot 4 availability | e0824 |

## Persistent flag folder (memory card, namespace 0-11)

| flag | meaning | evidence |
| --- | --- | --- |
| `folder:0` | persistent story flag 0 | SYSctlFlagFolder |
| `folder:1` | persistent story flag 1 | SYSctlFlagFolder |
| `folder:10` | LordKnightmon ID (Electro Mine) | save observation; separate from script-derived labels |
| `folder:11` | persistent quest-chain marker | SET in e0824/chunk_0104; corrected signed decoding |
| `folder:2` | persistent story flag 2 | SYSctlFlagFolder |
| `folder:3` | persistent story flag 3 | SYSctlFlagFolder |
| `folder:4` | persistent story flag 4 | SYSctlFlagFolder |
| `folder:5` | persistent story flag 5 | SYSctlFlagFolder |
| `folder:6` | persistent story flag 6 | SYSctlFlagFolder |
| `folder:7` | persistent story flag 7 | SYSctlFlagFolder |
| `folder:8` | persistent story gate 8 | checked in city hub e0709 |
| `folder:9` | persistent story gate 9 | checked in city hub e0709 |
