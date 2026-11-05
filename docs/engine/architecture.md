# Engine Architecture

## High-level picture
Digimon World 4 is a **C++ engine** (Gap::Core / Gap::Bec / "ig" object system)
with **most gameplay logic written in Lua 4.0.1**. The C++ side exposes a large
native API to the scripts, and all persistent game state lives in a
`GAMERAM` object that the scripts read/write through named *properties* and
*methods*.

```
 ┌────────────────────────────────────────────────────────────────┐
 │  Lua 4.0.1 scripts (in NDMW.AFS)                               │
 │    be:SYSgetPlayerLevel()   be:sd('PLAYER','OFCTRL')           │
 │    be:MDLgetHp()            be:SYSsetGateStage(...)            │
 └───────────────┬────────────────────────────────────────────────┘
                 │ 116 native functions (SYS*/MDL*/BLT*/BLP*/DM*/…)
 ┌───────────────▼────────────────────────────────────────────────┐
 │  C++ game (Gap::Bec::*)                                        │
 │    GAMERAM property/method system  (named records)             │
 │    object graph rooted at *(0x0058a1c0)                        │
 │    be* gameplay structures (beBaseInfo, beModelCtrl*, …)       │
 └───────────────┬────────────────────────────────────────────────┘
                 │
 ┌───────────────▼────────────────────────────────────────────────┐
 │  ig* engine core (Gap::Core::)                                 │
 │    igObject / igNode / igTransform / igGeometry / …            │
 │    reflection ("MetaField") + igBinary serialization (.igb)    │
 └────────────────────────────────────────────────────────────────┘
```

## Namespaces / prefixes
| Prefix | Meaning | Examples |
| --- | --- | --- |
| `ig*` | engine core (Insomniac-Games-derived object system) | `igObject`, `igNode`, `igTransform`, `igGeometry`, `igVec3fMetaField` |
| `Gap::Core::` | core engine C++ namespace | `igTObjectList<...>` |
| `Gap::Bec::` | game ("Bec" = the game project) namespace | `beSaveDataDeliver`, `beNDMWMcSlotPS2`, `beModelCtrlData` |
| `be*` | game data structures / controllers | `beBaseInfo`, `beModelCtrl`, `beLuaDataObject` |
| `SYS*` | script-facing system/native functions | `SYSgetPlayerLevel`, `SYSctlPlayer` |
| `MDL*` | model/character native functions | `MDLgetHp`, `MDLsetSeq` |
| `BLT*` / `BLP*` | combat (bullet target / bullet player) functions | `BLTgetDamageValue`, `BLPgetStunTime` |
| `DM*` | demo/cutscene-dialog ("demonstration") controllers | `DMrun`, `DMmsgBox`, `DMchkSD` |
| `MAT*` | material/matrix helpers | `MATisPlayer`, `MATgetPlayerMatStat` |
| `g_*` | Lua global variables (script state) | `g_GateOn`, `g_HP0`, `g_SItemDB` |

## Two state systems
1. **Live/C++ state** — cached scalars + object graph in BSS (`0x0058xxxx`), e.g.
   the "MDL" (current model) HP at `0x0058a1f0`. Updated every frame. See
   `docs/engine/game-state.md`.
2. **Persistent/property state** — named records stored in the `GAMERAM` object
   (`LEVEL`, `EXP`, `HP`, `BIT`, …). Read/written by `SYS*` functions and
   serialised to the memory card. See `docs/engine/property-system.md`.

The two are bridged: e.g. `SYSgetPlayerLevel()` reads the `LEVEL` property record,
while `MDLgetHp()` reads the live global at `0x0058a1f0`.

## The object-method system
A generic dispatch mechanism used for higher-level actions:
| Function | Role |
| --- | --- |
| `0x38e5d0(obj, name)` | get a named method object |
| `0x38e5f0(obj, name, a2, a3, t0)` | invoke method (5-arg form) |
| `0x38e670(obj, name, subkey)` | invoke method with a sub-key |
| `0x38e060(obj, arg)` | invoke the previously-fetched method |
| `0x38f800(obj, idx)` | read a "player/result" slot: `*(*(*(obj+16)+40)+16+idx*4)` |
| `0x38f320(obj, idx)` | read a "result" slot: `*(*(*(obj+16)+20)+16+idx*4)` |
| `0x38f830`, `0x38f250`, `0x38f8f0` | further slot accessors |

Objects are addressed by **string key** (e.g. `"GAMERAM"`, `"PLAYERPOINT"`,
`"MODELCTRL"`, `"FIGHTCALC"`), dispatched through a registry.

## Reflection + serialization
- The engine has a runtime **reflection** system: every C++ class registers its
  fields as `MetaField` objects (`igIntMetaField`, `igVec3fMetaField`, …).
- Serialised object graphs use the **igBinary ("IGB")** format
  (`NDMW.IGB`, and the pre-Lua region of `NDMW.AFS` entries). See
  `docs/engine/reflection-metadata.md`.

## Lua integration
- Engine glue classes: `igLuaState` (`0x004ea180`), `igLuaGlue`
  (`0x004ea1b0`), `_luaManager` (`0x00501428`), `_luaInterface` (`0x00501610`).
- Script loaders: `_callLuaFile`, `_callLuaName`, `_callLua`.
- Game-side data: `beLuaState`, `beLuaInfo`, `beLuaData`, `beLuaDataObject`.
- Debug/UI: `beModelCtrlLUACALL`, `SHOW_LUACALL`, `HIDE_LUACALL`, `_isLuaCallDisp`.
- Full details in `docs/engine/script-engine-lua.md`.

## Save layer
- `beSaveDataDeliver` (serialiser), `beSvPs2McImage128k` ("128k" image wrapper),
  `beNDMWMcSlotPS2` / `...GC` / `...Xbox` (per-platform slots),
  `_mcUtilCtrl`, `_slotSaveData`, `_isHaveSaveData`.
- Backed by libmc (`mcman.irx`, `mcserv.irx`).
- Full format in `docs/systems/save-format.md`.

## Renderer note (out of scope but present)
- VU1 microcode with symbol table embedded (strings `vu1_entry_*` /
  `EXECUTE_PATH`, `TRANS_MVP`, `LIGHT_*`, `CLIP_*`, … at `0x0048dd60`,
  `0x00491910`).
- Not relevant to game-state/glitch work.
