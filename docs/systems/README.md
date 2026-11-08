# `systems/` — game data and mechanics

Content, save format, and the data-driven systems. Index: [`../README.md`](../README.md).

| File | Topic |
|---|---|
| `game-content.md` | Content inventory: Digimon, enemies, bosses, missions, stages, scripts |
| [Hub recovery](hub-recovery.md) · [generated inventory](hub-inventory.md) | Full Terminal/Central/Shop/Commander recovery contract, script call sites and direct dependency frontier |
| `save-format.md` | Save byte map, checksum, level formula, save-editor recipe |
| `open-questions.md` | Unresolved items and how to close them |
| `items.md` | Item/device database, name table, weapon/armor/core/mod IDs |
| `techniques.md` | Technique/skill/X-Data storage |
| [Combat calculations](combat-damage.md) · [generated inventory](combat-inventory.md) | FIGHTCALC rules, recovery boundary, switch commands and direct dependencies |
| [Combat helper recovery](combat-helpers.md) | Three immediate helpers / 912 bytes; row/query behavioral comparisons and compiler-owned destructor |
| [Combat draft recovery](combat-draft-recovery.md) | Reviewed call interfaces, guarded byte/word/stride repairs, corrected list receiver and matching parent Message enum |
| [Combat Lua API](combat-lua-api.md) | All 26 BLT/BLP helpers / 5,372 bytes; messaging, local rank/category rules and remaining dispatcher scope |
| [Combat reference helpers](combat-reference-helpers.md) | Fifteen ownership/string/allocator bodies / 1,732 bytes; retail unwind identities, retain/release order and packed reference word |
| [FIGHTCALC direct callees](combat-callees.md) | 19 callee bodies (4,356 bytes) plus one emitted destructor; five harder callees and their blockers |
| [GAMERAM combat dispatcher](combat-dispatcher.md) | `vfunc_34` (41,864 bytes, 22 FIGHTCALC commands); ownership, switch tables, exception data and the register-colouring method |
| `enemy-data.md` | Enemy roster, model namespaces, the 649-row stat DB |
| `digivolution-and-sidequests.md` | Digivolution unlocks and side-quest gating |
| `dev-stage-debug-menu.md` | Dev stage `stag0000` + the engine's stage-select warp recipe |
| `enemy-spawn-system.md` | `GENERATER`/`GENE-xx` spawn system (field map, triggers, model swap) |
| `drop-tables.md` | Item drop tables and the weighted roll |
| `rng.md` + `rng-sites.tsv` + `rng-verification.md` | The one RNG: MT19937, seed **5150**, every draw site (Lua + native), the new-game draw timeline, and how to predict/shift it |
| `critical-path.md` | Flag-by-flag path to the ending (speedrun reference) |
| `flags/` | Flag data — see its own [`README.md`](flags/README.md) (map, meanings, `flag-xref.tsv`) |

Related: engine internals are in [`../engine/`](../engine); what is still unknown is indexed in
[`open-questions.md`](open-questions.md).
