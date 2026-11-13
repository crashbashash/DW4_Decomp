# Game RAM: `beNDMWGameRam`

`beNDMWGameRam` (messenger name `GAMERAM`) holds the run-time game state: one common data list
shared by all players and one player data list per player (four). Each list is a list of named
data objects (`beDataObjInt`, `beDataObjIntList`, …) built from a static layout, and other
objects read and write them through the messenger and through `igProperty_FindByName` lookups by
property name. The save file stores the `BASE_*` arrays of these lists ([save format](../systems/save-format.md)).

## Source

`src/game/beNDMWGameRam.cpp` is one translation unit, `ndmw_beNDMWGameRam`
(`0x003f6620`–`0x00407080`), compiled whole under the `-inline level=8,bottomup` profile.

| Start | Bytes | Symbol | Role |
|---|---:|---|---|
| `0x003f6620` | 2,416 | `beNDMWGameRam_BuildDataList` | appends one named data object per layout row to a list |
| `0x003f7310` | 1,172 | `beNDMWGameRam_ResetPlayer` | rebuilds a player's data list (player 0 also rebuilds the common list): `BASE_LEVEL` 1, `BASE_SKILL` 1, twelve disks, `BASE_FLAG[960]` set |
| `0x003f77b0` | 464 | `beNDMWGameRam_Initialize` | creates the two list holders and resets the four players (slot 23) |
| `0x003f7980` | 720 | `beNDMWGameRam_ClearLists` | empties both lists (slot 24) |
| `0x003f7c50` | 484 | `beNDMWGameRam_ReleaseDataBases` | releases the eight cached database objects (slot 32) |
| `0x003f7e40` | 388 | `beNDMWGameRam_CreateInfo` | creates the `gameram` info and its ram record and registers it as receiver of `GAMERAM` (slot 25) |
| `0x003f80d0` | 8 | `beNDMWGameRam_Update` | empty per-frame update (slot 31) |
| `0x003f80e0` | 444 | `beNDMWGameRam_FindSpecies` | species row whose `MODEL_NAME` in the `shinka` database is the given model, else 0 |
| `0x003f82a0` | 1,212 | `beNDMWGameRam_SelectSpecies` | makes a species current: `DIGIMONNO`, `DIGIMONNAME`, and `LEVEL`, `EXP`, `SKILL`, `UPCNT` from the `BASE_*` arrays; player 0 also shares its flags and counters with the common list |
| `0x003f8760` | 548 | `beNDMWGameRam_StoreSpecies` | the reverse: current values back into the `BASE_*` arrays |
| `0x003f8990` | 768 | `beNDMWGameRam_GiveInitialWeapons` | replaces `DEVICEFOLDER` with the species' `INI_WEAPON1`–`3` |
| `0x003f8c90` | 1,832 | `beNDMWGameRam_EquipWeapon` | refills `POWERSOCKET`/`POWERSOCKETNAME` from the weapons in `DEVICEFOLDER`; with `apply` set it equips only the strongest weapon the species can use |
| `0x003f93c0` | 432 | `beNDMWGameRam_HasUsableWeapon` | whether a carried weapon fits the species (`SOUBI` mask) and its skill level (`SKILLPOINT`) |
| `0x003f9570` | 356 | `beNDMWGameRam_JoinPlayer` | enters a player with a model: species, weapons, stats, `ISUSE`, `BASE_ISUSE`, and the `NINZU` count |
| `0x003f96e0` | 772 | `beNDMWGameRam_JoinPlayerWithName` | joins and sets `PLAYERNAME` from text converted by the font |
| `0x003f99f0` | 436 | `beNDMWGameRam_JoinPlayerWithUnicodeName` | joins and sets `PLAYERNAME` from a unicode object |
| `0x003f9bb0` | 204 | `beNDMWGameRam_LeavePlayer` | clears `ISUSE` and recounts `NINZU` |
| `0x003f9c80` | 408 | `beNDMWGameRam_ChangeHp` | HP by delta or to an absolute value, clamped to `MHP`, and the `hpmt`/`hpnm` gauges |
| `0x003f9e20` | 344 | `beNDMWGameRam_ChangeMp` | MP by delta and the `mpmt`/`mpnm` gauges |
| `0x003f9f80`–`0x003fa2c0` | | `beNDMWGameRam_Add…Bonus` | add an item field of the `POWERSOCKET`, `POWERPOCKET`, `MAINSLOT`, `MAINPOCKET` or `SUBSLOT` items to a total |
| `0x003fa3b0` | 1,184 | `beNDMWGameRam_CalcMaxPoints` | `MHP` or `MMP` of a species from its `*_INI`/`*_GROW` columns and the level band, at most 99,999 |
| `0x003fa850` | 832 | `beNDMWGameRam_CalcAttribute` | one of `STR`, `AC`, `INT`, `MND`, `DEX` the same way, at most 9,999 |
| `0x003fab90` | 6,872 | `beNDMWGameRam_RecomputeStats` | every derived stat of a player, optionally with equipment, chip and skill modifiers |
| `0x003fc6f0` | 132 | `beNDMWGameRam_FindTechniqueRow` | WAZALIST base number to its database row |
| `0x003fc780` | 652 | `beNDMWGameRam_CollectNearbyNonzeroHp` | group members within radius 30 whose HP is nonzero |
| `0x003fca10` | 41,864 | `beNDMWGameRam_OnMessage` | message handler (slot 34); see the [combat dispatcher](../systems/combat-dispatcher.md) |
| `0x00407060` | 12 | `beNDMWGameRam_GetMeta` | returns the `beNDMWGameRam` meta object (slot 20) |
| `0x00407070` | 8 | `beNDMWGameRam_GetInfoMeta` | returns no info meta object (slot 30) |

The functions from `0x00406da0` to `0x00407050` are out-of-line copies of small accessors the
handler calls (list data, property value, object reference reads); their names carry their
address because every unit has its own copies.

## Data layouts

`g_commonDataLayout` and `g_playerDataLayout` are tables of `DataLayoutEntry` rows (type,
element count, name) ending in type `-1`. The type selects the data object: 0 int, 1 int list,
2 bool, 3 bool list, 4 string, 5 string list, 6 object list, 7 float list. Lists are sized to the
row's count and filled with the defaults in `g_dataObjDefaults` and `g_dataObjDefaultBool`.

## Growth

`MHP`, `MMP` and the five attributes grow by level band. `g_growthBandMaxLevel` holds the band
upper levels and `g_growthBandStartLevel` their first levels; a stat is the `UPCNT` bonus plus
`ini + grow * (base[band] + rate[band] * (level - start[band])) / 100`, with
`g_pointGrowthBandBase`/`Rate` for HP and MP and `g_attributeGrowthBandBase`/`Rate` for the
attributes. The column names come from `g_attributeInitialFields` and `g_attributeGrowthFields`.

## Open questions

- `FUN_00236f80` (find an insight's object by meta object), `FUN_002eb010` (allocate from the
  string pool's allocator) and `FUN_002caa70` (create an int list) keep their address names; each
  has callers in more than twenty files.
- The base call in `beNDMWGameRam_Initialize` is the `beBaseInfoManager` slot 23 body, still
  named `Gap__Core__igObject__vfunc_23`.
- `g_initialBaseFlag960` sets `BASE_FLAG[960]` on every reset; what the flag means is not known.
