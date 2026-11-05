# Lua script decompilation

The game's runtime logic is written in **Lua 4.0.1** and shipped as compiled
bytecode chunks concatenated inside `NDMW.AFS` entries (the "stage packs").
All 5,291 chunks have been decompiled back to readable Lua.

## Deliverable

```
lua/
    <NN-region>/<NN-stage>_e<ENTRY>/     (98 AFS entries, filed by stage)
        <CCC>-<name>.lua                 chunk CCC of that entry
        _origin.txt                      the entry, its stage and chunk count
```

Tool: `scripts/lua_decompile.py` (custom Lua 4.0.1 decompiler).
Tree builder: `scripts/build_lua_tree.py` (index: [lua-tree-layout](lua-tree-layout.md)).

## Bytecode facts (verified against reference Lua 4.0.1 source)

- Instruction layout: `OP(6) | B(9 bits @6) | A(17 bits @15)`.
  `GETARG_U = ins>>6`, `GETARG_S = (ins>>6) - (2^25 - 1)`,
  `GETARG_B = (ins>>6) & 0x1ff`, `GETARG_A = ins>>15`.
- `OP_CALL`: **A = stack position of the function**, B = nresults;
  `nargs = top - A - 1` (args are everything above the function).
- `OP_PUSHSELF`: pops the receiver, pushes `[method, receiver]`.
- **Jump target = `pc + 1 + s`**, stock Lua 4.0.1. Finding [#785](../findings/findings-0751-1000.md#f785)
  supersedes [#119](../findings/findings-0001-0250.md#f119)'s extra-increment claim: the old decoder's bias was one
  too large. Original bytecode executes on the stock VM.
- Opcodes 38/39 are the **stock pop variants** (`JMPT` = jump-if-truthy-pop,
  `JMPF` = jump-if-falsy-pop), used for `if x` / `if not x` conditions.
  `JMPONT`/`JMPONF` (40/41) are **never emitted**, so the scripts contain **no
  `and`/`or` short-circuit**.
- `a and b` is compiled as **nested `if`s sharing one else target**; the
  decompiler flattens these into `a and b and c`.
- Local-variable names and line info are **stripped** (`nlocvars == 0`);
  locals are named `local_0`, `local_1`, … and closure params `arg_0`, ….
- Numeric-for loops use normal step 1. The old decoded step 0 was the
  signed-bias error, not a game-specific sentinel ([#785](../findings/findings-0751-1000.md#f785), superseding [#120](../findings/findings-0001-0250.md#f120)).

## Script-API recap (the `be:` object)

Scripts drive the engine through `be` — 116 native C++ functions bound to Lua
(see `docs/engine/script-engine-lua.md`). Common patterns:

```lua
be:sd("MODELCTRL", "g_door", -1, "GENERATE", "V<220,40,-200>/V<0,-90,0>")
be:DMsetSD("PLAYER", ...)          -- command to a game controller
be:FLGisOn(300) == 0               -- flag test (flags = game-state bits)
be:FLGset(408, -1)                 -- set flag
be:SYSgetPlayerLevel() / be:SYSctlPlayer("HP","GETHP",...)
be:DMsetLua("bML01001.lua")        -- run a named script file
be:DMrun()                         -- dispatch the current script
```

- `"SQ_*"` = sequence/animation names, `"I<N>"` = integer params,
  `"V<x,y,z>/V<rx,ry,rz>"` = position/rotation vectors,
  `"F<..>/F<..>"` = float params.
- `be:sd("ENEMY"/"PLAYER"/"STAGECTL"/"MODELCTRL"/"SOUND"/"LIGHTCTRL", ...)`
  are the main controller entry points.

## Structure of a stage pack (AFS entry)

Each AFS entry = `[igBinary reflection metadata][Lua chunks…]`. The chunks are
independent compiled scripts (source `=(none)`), concatenated in load order.
Most chunks are tiny event scripts (message boxes, flag sets, door/bomb/NPC
triggers); a few are large level-init scripts (the `funcStartLayerSet`,
`funcPlayerSet`, `_ERRORMESSAGE` library chunks).

## Notes / known quirks

- Dump/decompiler signed operands and branches are corrected and all 5,291
  chunks, their index, cleaned tree and flag tables are regenerated ([#787](../findings/findings-0751-1000.md#f787)).
  `python3 scripts/verify_lua_decode.py --afs <NDMW.AFS>` checks fixtures,
  all 81,856 branch targets and 2,805 numeric loops, and generated-source agreement.
  Numeric loops pair by their back edge, including nested loops and threaded
  empty-loop branches. Source reconstruction remains best-effort; execute
  original bytecode. See the [numeric documentation audit](lua-numeric-audit.md).
- `local_N` are unnamed locals; the original names were stripped at build time.
- The enemy/item **stats** are NOT in these scripts — they live in the
  igBinary `beBaseInfoData`/`beNDMWStatusInfo` objects (see `docs/systems/enemy-data.md`).
  The Lua only references them by name (`MDLgetHp`, `BLTgetDamageValue`, …).
