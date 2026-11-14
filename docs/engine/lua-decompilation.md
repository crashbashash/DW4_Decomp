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
- **Jump target = `pc + 1 + s`**, stock Lua 4.0.1, with no extra increment: the old
  decoder's bias was one too large. Original bytecode executes on the stock VM.
- Opcodes 38/39 are the **stock pop variants** (`JMPT` = jump-if-truthy-pop,
  `JMPF` = jump-if-falsy-pop), used for `if x` / `if not x` conditions.
  `JMPONT`/`JMPONF` (40/41) are **never emitted**, so the scripts contain **no
  `and`/`or` short-circuit**.
- `a and b` is compiled as **nested `if`s sharing one else target**; the
  decompiler flattens these into `a and b and c`.
- Local-variable names and line info are **stripped** (`nlocvars == 0`).
  The decompiler runs each prototype twice: the first pass records how every
  local binding is used, `scripts/lua_names.py` names it from that use
  (`showText`, `ramNo`, `playerIndex`, `count`, `i`; the rules are in its
  docstring and [lua-tree-layout](lua-tree-layout.md#local-names)), and the
  second pass renders with those names. A local with no qualifying use stays
  `local_N` (closure params `arg_N`, a vararg function's table `arg`).
- Numeric-for loops use normal step 1. The old decoded step 0 was the
  signed-bias error, not a game-specific sentinel.

## How the source is rebuilt

- A value left on the stack across a statement is a local: Lua 4 keeps every
  local in the slot its initial value was pushed to and leaves nothing else
  there between statements. Before each statement (call, assignment, `if`,
  `while`, `for`, `return`, block-end `POP`) the decompiler emits
  `local NAME = expr` for any such value not yet declared, so declarations land
  between the statements their values were computed between. This includes
  local functions (`local showText = function(text, ...)`).
- `OP_CLOSURE A B` takes prototype `A` (`ins >> 15`) and closes over the `B`
  values on top of the stack; the scripts never use upvalues (`B` is always 0).
  A vararg function prints as `function(...)` and its slot after the
  parameters is Lua 4's `arg` table.
- `OP_RETURN U` returns the values from slot `U` up; the slots below are the
  function's locals, so a bare early `return` prints as `return`.
- Two conditions join with `and` only when the second is a pure expression
  jumping to the same target; a statement or declaration between them keeps
  the nested `if`.
- Lua threads a jump to the end of a block straight to that block's exit. A
  conditional or `else` jump past the end of the enclosing block therefore
  means "to the end of this block", which keeps an `if` that ends a `then`
  part inside it rather than swallowing the outer `else`.
- Table constructors print their list part and record part separated by `;`
  (`SETLIST B` and `SETMAP U` consume `B` items and `U` pairs).

Recompiling the rebuilt text with stock Lua 4.0.1 `luac -s` reproduces 4,183
of the 5,291 chunks exactly (instruction words, constant tables, parameters,
vararg flag and stack size, in every nested prototype); 69 more differ only in
operands, 435 more only inside equal-length code. The rest recompile to
different control flow, so the original bytecode stays the authority.

## Script-API recap (the `be:` object)

Scripts drive the engine through `be`, 116 native C++ functions bound to Lua
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
  chunks, their index, cleaned tree and flag tables are regenerated.
  `python3 scripts/verify_lua_decode.py --afs <NDMW.AFS>` checks fixtures,
  all 81,856 branch targets and 2,805 numeric loops, and generated-source agreement.
  Numeric loops pair by their back edge, including nested loops and threaded
  empty-loop branches. Source reconstruction remains best-effort; execute
  original bytecode. See the [numeric documentation audit](lua-numeric-audit.md).
- Inferred local names are readability aids, not the original names; `local_N`
  is a local no naming rule covers.
- The enemy/item stats are not in these scripts. They live in the
  igBinary `beBaseInfoData`/`beNDMWStatusInfo` objects (see `docs/systems/enemy-data.md`).
  The Lua only references them by name (`MDLgetHp`, `BLTgetDamageValue`, …).
