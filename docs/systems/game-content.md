# Game Content Inventory

Extracted from the **Lua string constants** in `NDMW.AFS` (17,239 unique strings
→ 5,291 chunks). Full lists in `ghidra-projects/dw4/lua_*.txt`.

## Playable Digimon: 16
Models come in pairs: `_common/p_<name>.igb` (player) and
`_common/m_<name>.igb` (monster/NPC variant).

| Script name | Likely Digimon |
| --- | --- |
| `agumon` | Agumon |
| `alpha` | Alphamon |
| `angelr` | Angelerimon? |
| `beelzeb` | Beelzemon |
| `bwargrey` | BlackWarGreymon |
| `dorumon` | Dorumon |
| `dukecrim` | Dukemon Crimson Mode |
| `girumon` | Guilmon |
| `hekabut` | HerakleKabuterimon? |
| `impdrafm` | Imperialdramon Fighter Mode |
| `impdrapm` | Imperialdramon Paladin Mode |
| `metalgaru` | MetalGarurumon |
| `susanoo` | Susanoomon |
| `vmon` | Veemon |
| `wargrey` | WarGreymon |
| `weregaru` | WereGarurumon |

## Enemy roster: 29 types
Extracted from `e_*` names. A `/I<n>` suffix denotes a stat/AI variant
(e.g. `e_skulgrey/I<0>` = the boss version).

| # | Script name | Likely Digimon |
| --- | --- | --- |
| 1 | `e_anomalo` | Anomalocarimon |
| 2 | `e_arachne` | Arukenimon |
| 3 | `e_blosso` | Blossomon |
| 4 | `e_cockatri` | Cockatrimon |
| 5 | `e_diabolo` | Diaboromon |
| 6 | `e_geko` | Gekomon |
| 7 | `e_goburi` | Goburimon |
| 8 | `e_impdra` | Imperialdramon |
| 9 | `e_infermo` | Infermon |
| 10 | `e_ldknight` | LordKnightmon |
| 11 | `e_mammos` | Mammothmon |
| 12 | `e_mecha1` | Machinedramon variant 1 |
| 13 | `e_mecha2` | Machinedramon variant 2 |
| 14 | `e_mecha4` | Machinedramon variant 4 |
| 15 | `e_mecha4bs` | Machinedramon variant 4 (boss) |
| 16 | `e_mecha5` | Machinedramon variant 5 |
| 17 | `e_megadra` | Megadramon |
| 18 | `e_minotaru` | Minotarumon |
| 19 | `e_mummy` | Mummymon |
| 20 | `e_nume` | Numemon |
| 21 | `e_ogre` | Ogremon |
| 22 | `e_otama` | Otamamon |
| 23 | `e_pharaoh` | Pharaohmon |
| 24 | `e_rare` | Raremon |
| 25 | `e_scum` | Scumon |
| 26 | `e_skulgrey` | SkullGreymon |
| 27 | `e_tonogeko` | TonosamaGekomon |
| 28 | `e_torta` | Tortamon |
| 29 | `e_tyrano` | Tyrannomon |

Plus `leomon` / `leomon2` / `n_leomon` (`AM_LEOMN`, `DM_LEOMN`) = **Leomon**, a
boss/NPC outside the `e_` namespace.

### Enemies include bosses
The `e_*` namespace is a **single unified enemy roster**; bosses are the same
types spawned in boss encounters, flagged by:
- Battle types `BT_BOSS1/2/3`, `BT_SBOSS` ("super boss"), `BT_WIN03`.
- Boss HP bars `i_bosshp01` … `i_bosshp17`.
- Boss globals `g_bossRest`, `g_bossgate`, `g_dbossgate`, `g_bossymbolz01..04`,
  `hitbossgatez01..03`, `i_bosshp01..17`.

Observed boss → HP-bar mapping:
| Enemy(ies) | Battle type | HP bar |
| --- | --- | --- |
| (story bosses) | `BT_BOSS1/2/3` | `i_bosshp01/02/03` |
| `e_blosso` | `BT_SBOSS` | `i_bosshp10` |
| `e_mammos` | `BT_SBOSS` | `i_bosshp11` |
| `e_skulgrey` | `BT_SBOSS` | `i_bosshp12` |
| `e_pharaoh`,`e_mummy`,`e_mecha1`,`e_mecha2`,`e_anomalo` | `BT_SBOSS` | `i_bosshp13` |
| `e_tonogeko` | `BT_SBOSS` | `i_bosshp14` |
| `e_diabolo` | `BT_SBOSS` | `i_bosshp15` |
| `e_mecha5` | `BT_SBOSS` | `i_bosshp16` |
| `e_ldknight` | `BT_SBOSS` | `i_bosshp17` |
| `e_mecha4` | `BT_SBOSS` | (none in chunk) |

## Missions: 18 (`AM_*`)
```
AM_TITLE AM_TITLE2 AM_START AM_LOBBY AM_OFNI1 AM_OFNI2 AM_DUNGE AM_DESER
AM_FORR1 AM_FORR2 AM_GOBLI AM_RIVER AM_MACHI AM_VALLE AM_EVOLV AM_BOS01
AM_DEVI3 AM_LEOMN
```
(`AM_` = "Area/Mission".)

## Stages: 41 (`stag*`)
```
stag0001
stag0101 stag0102 stag0103 stag0104
stag0201 stag0202 stag0203 stag0204 stag0205
stag0301 stag0302 stag0303 stag0304
stag0401 stag0403 stag0404
stagBS01..BS06   stagGF01..GF04   stagIS07..IS13 stagIS20
stagML02 stagML11 stagML12 stagML13 stagML14
stageLocalFuncQuickSandOn/Off   stageLocalFuncSlippedFloorOn/Off
```

## Script files: 269 named `.lua`
Organized as `b<stage><no>.lua`:
- `b0001001.lua` … `b0001010.lua`
- `bML01001.lua` … `bML01055.lua` (Mission Level 01)
- `bML02001.lua` … `bML02xxx.lua` (Mission Level 02)
- utility scripts: `armorshop.lua`, `saveshop.lua`, `xdatashop.lua`,
  `gameStart.lua`, `hostLoad.lua`, `putitemyes.lua`, `txt_mem.lua`,
  `txt_Tar.lua`
- loaded via `_callLuaFile`.

## Script globals: 515 `g_*`
Shared script state. Categories:
| Category | Examples |
| --- | --- |
| Entity HP | `g_HP0` … `g_HP7` |
| Item flags | `g_IFLG00` … `g_IFLG27` |
| Item DB | `g_SItemDB`, `g_SItemID`, `g_TItemDB`, `g_TItemID` |
| Gate/exit | `g_GateOn`, `g_GatePos`, `g_GateStage` |
| State change | `g_StChangeKind` (294 uses) |
| Loadout | `g_000weapon`, `g_000armor`, `g_000item`, `g_000bit`, `g_000access`, `g_000boost1`, `g_000bcaps`, `g_000xdata1/2` |
| Combat check | `g_DmgChk0/1/2`, `g_Poschk`, `g_bPosCheck0/1/2`, `g_DRILLchk` |
| Boss | `g_bossgate`, `g_bossRest`, `g_bossymbolz01..04`, `g_dbossgate` |
| Level objects | `g_bossgate`, `g_bluemagnet00..04`, `g_button01..03`, `g_bush01/02z*`, `g_breakdoorz03`, `g_breakinggatez05`, `g_annihilativebomz06`, `g_barrelshotz01`, `g_atcksabtnz02`, `g_boatz01`, `g_boathp`, `g_agumon01MapBlock`, `g_Rocksh0..3`, `g_UFOPos`, `g_StgPos` |
| Misc | `g_act`, `g_ground`, `g_FBSwitch`, `g_FIYCHACK`, `g_RNo0..3`, `g_Ramno`, `g_31ram0/1`, `g_enemyAmount`, `g_gobuMode` |

Full list: `lua_globals.txt`.

## Action sequences: 367 `SQ_*`
Animation/action state machine states. Examples:
```
SQ_GAMEOVER SQ_CLEAR SQ_TALK SQ_JUMP SQ_GUARD SQ_STUN SQ_WAIT SQ_WALK02/04
SQ_OPEN SQ_CLOSE SQ_ENTR SQ_EXIT SQ_BOSS SQ_BUTTON
SQ_SDMG SQ_MDMG SQ_LDMG SQ_DDMG      (damage tiers: small/med/large/…)
SQ_SWON SQ_SWOF SQ_BLIN SQ_BLOUT SQ_BHLFIN/BHLFOUT
SQ_STCHANGE01 SQ_STCHANGELP SQ_STOPEN SQ_POWERON SQ_SILENTON
SQ_STUN SQ_SETPOISON/SLEEP/BIND/…
```
Full list: `lua_sequences.txt`.

## Asset paths: 117 `.igb`
| Prefix | Kind | Examples |
| --- | --- | --- |
| `_common/p_*` | player models | `p_agumon`, `p_dorumon`, `p_vmon`, … (16) |
| `_common/m_*` | monster models | `m_agumon`, `m_alpha`, … (16) |
| `/separate/e_*` | enemy models | `e_arachne`, `e_skulgrey`, `e_tonogeko`, `e_torta` |
| `_common/w_*` | weapons | `w_sword01..06`, `w_katana01..06`, `w_gun01..08`, `w_axe0*`, `w_glave0*`, `w_maul0*`, `w_saber0*`, `w_cutlas0*`, `w_dagger0*`, `w_arm0*`, `w_common0*`, `w_sp0203` |
| misc | other | `pack.igb`, `ACMR_pack.igb`, `aaaCamera.igb`, `generatorH/N/V.igb` |

## Player-facing / UI vocabulary
- **Player-slot method codes**: `PCWA PCCA PCSA PCMA PCBA PCTK ENAT PCMK ENSP`.
- **Stat/model types**: `beBaseInfo`, `beBaseInfoRam`, `beNDMWStatusInfo(Ram)`,
  `beNDMWPanelWazaInfo(Ram)`.
- **Status names**: `poison`, `sleep`, `stun`, `guard`, `powerdown`,
  `attackdown`.
- **Menu/UI**: `SAVEUTILITY`, `REQUEST_FORMAT`, `REQUEST_READ_MEDIA`,
  `REQUEST_WRITE_MEDIA`, `REQUEST_FILEFIND`, `REQUEST_FILEMAKE`,
  `REQUEST_GETFREESIZE`, `REQUEST_USE_CHECK`, `REPORT_GAMEDATA`, `ISRDY`,
  `ISBUSY`, `SAVECHECKWIN`.
