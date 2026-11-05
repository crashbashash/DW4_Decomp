# Digimon World 4 — script progression gates

Findings **[#785](../findings/findings-0751-1000.md#f785)/#787**. These are static script predicates,
not a verified speedrun route. Decoding the script numbers with a signed bias one too large
gives incorrect flag IDs and values and a spurious Lua-to-save inversion. See the
[numeric audit](../engine/lua-numeric-audit.md).

## City teleporter predicate

`lua/05-city-overworld/01-stag0403-city-quest-hub_e709/034-layer-setup-2.lua:122` reads:

```lua
if be:FLGisOn(376) ~= 1 and be:FLGisOn(377) ~= 1 and be:FLGisOn(378) ~= 1
   and be:FLGisOn(379) ~= 1 and be:FLGisOn(380) ~= 1 then
    if be:FLGisOn(381) == 1 then
        -- generate/power on g_cytelep1; disable hitpopblockz040
    end
end
```

A `375..379 !=0 AND 380 ==0` reading of this condition is the signed-bias error. This predicate
alone does not establish the whole game's critical path or an area-to-flag
mapping. In particular, do not label it the only final-boss gate without
checking the stage-transition and persistent-folder services.

## Direct write sites

| Script evidence | Writes |
| --- | --- |
| `lua/11-bosses/01-boss01-apocalymon_e730/006-boss-bit.lua:87` | Apocalymon sequence: flag 67 = 1; scene flag 600 = 1 |
| `entry_0737` | BelialVamdemon sequence: flag 68; scene flag 603 |
| `entry_0744` | Lucemon sequence: flag 69; scene flag 607 |
| `entry_0425` | LordKnightmon sequence: flag 83; scene flag 609 |
| `lua/11-bosses/06-boss06-devimon-3_e765/005-boss-devl31.lua:105` | final phase: flag 70 = 1; conditional flags 86/610 = 1 |
| `lua/01-lobby-hub/06-lobby-quest-board_e824/104-npc-digilfm-16.lua` | flags 571..575, 409, 380 and 424 = 1; folder 11 SET |
| `lua/01-lobby-hub/06-lobby-quest-board_e824/106-npc-digilfm-18.lua` | flag 381 = 1 |

The final-phase difficulty test is `SYSgetDifficulty() > 0`; script difficulty
values are 0/1/2. Exact associations with observed save checkpoints need
validation. Retain raw save diffs separately from script-derived labels.

## Validation boundary

Generated [flag cross-references](flags/flag-xref.tsv) contain all 11,866
operations and their original entry/chunk/line evidence. Numeric source
regeneration is checked by `scripts/verify_lua_decode.py`. The native runtime
executes original bytecode; these readable scripts remain analysis output with
best-effort control-flow reconstruction. Progression outcomes still require
matched retail state/input comparisons.
