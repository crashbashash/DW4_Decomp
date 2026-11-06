# Lua numeric recovery audit

The original VM uses signed bias
`33554431` and target `pc + 1 + s`. Subtracting `33554432` is wrong: the extra
jump increment hides that error for branches, but every
PUSHINT/ADDI signed operand comes out one too low. Numbers stored as floating-point
constants and digits inside strings are unaffected. Do not add one to every
number in a document, save, model record or message string.

The dump and decompiler tools use the correct bias. All **5,291** chunks in `lua/` and the generated flag
cross-references/meanings are generated with it.
Numeric loops pair with their own FORLOOP back edge; an empty-loop jump can be
threaded beyond the immediate loop end. Cleaned filenames containing numeric
IDs carry the corrected numbers; original entry/chunk numbers are stable.

From the decompilation repository root:

```sh
python3 scripts/lua_decompile.py <NDMW.AFS> --out=build/lua_decompiled
python3 scripts/build_lua_tree.py
python3 scripts/verify_lua_decode.py --afs <NDMW.AFS>
python3 scripts/flag_xref.py lua docs/systems/flags
python3 scripts/flag_meanings.py lua docs/systems/flags
```

Verification checks signed/jump/PUSHNILJMP/nested-for fixtures, **81,856**
branch targets, **2,805** numeric loops, and exact agreement between regenerated
text and the generator. It does not prove every reconstructed conditional or
control-flow heuristic. Native integration runs original bytecode.

## Audited examples and documentation boundaries

| Evidence | Off-by-one decoding (wrong) | Correct decoding |
| --- | --- | --- |
| Title `lua/00-title-menus/04-title-screen_e806/004-layer-setup-2.lua`, delayed PAUSEOFF | 239 | 240 |
| Title `chunk_0006.lua`, scratch loop | 99..318, step 0, writes -1 | 100..319, step 1, writes 0 |
| Shops `lua/01-lobby-hub/07-lobby-shops_e828/004-npc-digilfm.lua`, level predicates | flags 907/908/909, levels 15/45/75 | flags 908/909/910, levels 16/46/76 |
| City `lua/05-city-overworld/01-stag0403-city-quest-hub_e709/034-layer-setup-2.lua:122` | 375..379 !=0 and 380 ==0 | 376..380 !=1 and 381 ==1 |
| Final phase `lua/11-bosses/06-boss06-devimon-3_e765/005-boss-devl31.lua` | writes 69/85/609 =0 | writes 70/86/610 =1 |
| Reward `lua/01-lobby-hub/05-lobby-quests_e820/011-npc-digilfm-9.lua` | thresholds 278/301, difficulty -1/0/1 | thresholds 279/302, difficulty 0/1/2 |
| Quest board `lua/01-lobby-hub/06-lobby-quest-board_e824/104-npc-digilfm-16.lua` | persistent folder 10 | persistent folder 11 |

The [critical-path page](../systems/critical-path.md),
[digivolution page](../systems/digivolution-and-sidequests.md), and
[flag reading guide](../systems/flags/README.md) distinguish corrected
script evidence from historical save interpretations. Runtime curated flag
keys and script-derived level thresholds in the flag generators are corrected.
Persistent-folder labels from save observations are retained separately.

The older reading of save flags as byte `0x01` = `FLGset(N,0)` and `0x00` = `FLGset(N,-1)`, and of
difficulty as Normal -1 / Hard 0 / Very Hard 1, is refuted. Older notes on boss-defeat flags, the title
mirror/restore system, the world-4 end state, side-quest flags and rewards, and transient flags keep their
raw observations but are unconfirmed where they combine those observations with off-by-one Lua numbers.
The [save-flag map](../systems/flags/flag-map.md) retains its historical evidence
with a correction notice: its claimed Lua-to-save inversion is invalid, and
old boss/quest labels must not guide runtime implementation. This audit does
not relocate observed save bytes or prove a new persistent-folder meaning.

Other older prose may contain Lua-derived literals; recheck a claim
against original entry/chunk evidence before importing it into the native port.
