# FIGHTCALC direct callees

The [generated inventory](combat-inventory.md) lists 68 distinct bodies called directly from the FIGHTCALC region. The table covers
the size-1,228-and-up messenger bodies and the 6,872-byte stat recomputation, with the compiler-emitted destructors they own.
The 26-body BLT/BLP helper run is in [Combat Lua API](combat-lua-api.md).

Almost all of these need the content-pinned alternate compiler (`-O3,p`, see [unit compilers](../engine/unit-compilers.md)); the
stock compiler differs only in delay-slot fill and one alignment `nop`. Where a form looks odd (`volatile` reads, comma-ordered
reads, a separate local for a reference slot) it is a matching construct recorded in the file header, not a claim about the
original source.

| Address | Bytes | Function | Source |
| --- | ---: | --- | --- |
| `0x002d6790` | 120 | `List_Resize` (grow capacity: min 4, double below 1024, then +1024) | `src/engine/core/igDataList_tail.inc` |
| `0x002eaf60` | 172 | `StringPool_Intern` | `src/engine/core/StringPool.inc` |
| `0x002fba30` | 260 | `igMetaEnum_GetValueByName` | `src/engine/core/igMetaEnum_tail.inc` |
| `0x0038d860` | 2036 | `beMessenger_SelectReceivers` (calls the work-record holder destructor `0x0038c410`, 128, emitted after `beMessenger_InitializeMemory`) | `src/game/beMessenger.cpp` |
| `0x0038e6b0` | 576 | `beMessenger_PrepareDelayedSelection` | `src/game/beMessenger.cpp` |
| `0x0038ed70` | 476 | `beMessenger_PushArgContext` | `src/game/beMessenger.cpp` |
| `0x0038ef50` | 400 | `beMessenger_PopArgContext` | `src/game/beMessenger.cpp` |
| `0x0038f150`..`0x0038f8f0` | 908 | `beMessenger_AppendBool/Int/Float/Vec3/Matrix/String`, `GetString` (7 bodies) | `src/game/beMessenger.cpp` |
| `0x0038e060` | 1228 | `beMessenger_DispatchSelected` (+ emitted holder destructor `0x0038e530`, 128) | `src/game/beMessenger.cpp` |
| `0x0038e8f0` | 932 | `beMessenger_EnqueueSelected` (its cleanups are the destructors `0x0038c390`, emitted after `beMessenger_InitializeMemory`, and `0x00357a90`, 128 each) | `src/game/beMessenger.cpp` |
| `0x003fab90` | 6872 | player stat recompute (derived stats, WAZALIST rebuild, rates); owns the `0x003fc670` destructor and the `0x003fc780` query | `src/game/beNDMWGameRam.cpp` |
| `0x003f8760` | 548 | current-to-BASE save preparation (mirror of `beNDMWGameRam_SelectSpecies`) | `src/game/beNDMWGameRam.cpp` |
| `0x003f9c80` | 408 | HP gauge update (delta or absolute, clamp to [0, MHP], `hpmt`/`hpnm`) | `src/game/beNDMWGameRam.cpp` |
| `0x003f9e20` | 344 | MP gauge update (`mpmt`/`mpnm`) | `src/game/beNDMWGameRam.cpp` |
| `0x00447b00` | 56 | list slot nonzero test | `src/game/beNDMWMdlPEBase.cpp` |
| `0x00447b40` | 88 | list slot store from `DAT_004cfe80` | `src/game/beNDMWMdlPEBase.cpp` |

## What the three hardest shapes needed

- **`DispatchSelected`**: each of the four list appends needs fresh locals, as separately inlined AppendBool/AppendInt bodies
  would create; the first loop reads the element once into `have` and once inline; the lists are typed (`int *data`,
  `MsgRecvObj **data`). Its holder destructor `0x0038e530` is registered in `config/SLUS-20836/unit-objects.json`.
- **`EnqueueSelected`**: the insertion loop gets retail's separate index and byte-offset inductions when the list base goes through an
  inline static helper that takes it as a parameter; the row pointer is typed `unsigned`; the two stack-resident references are two
  classes (`RowRef`, `SavedRef`), emitted as two copies of the same destructor body.
- **`beNDMWGameRam_RecomputeStats`**: the register rotation was graph-colouring order, not declaration order. An offline replica of the compiler's
  optimistic colouring showed that `player` needs the late virtual-register index that small inline accessors
  (`GetPlayer`, `GetProp`) give it. The body is 6,872 bytes: the return sequence lies past the raw symbol extent and needs a reviewed
  row in `data/function-extents.json`. A retail destructor address can belong to one ownership group only, so the nearby query
  is written in this unit and both bodies are verified together.
  Helpers are struct static members because `tools/units.py` blanks free top-level helpers.

## Not reproducible from plain source

`strcmp` was written in assembly and is built from its `.S` source. `igMatrix44f_Copy` does not yield to the
register-colouring lessons above and needs inline assembly to reproduce, which is not recovered source.

- **`strcmp` (324 bytes).** newlib's R5900 `strcmp.S`, built from `src/newlib/strcmp.S` as owner-approved
  hand-written assembly ([assembly sources](../engine/assembly-sources.md)).
- **`igMatrix44f_Copy` (188 bytes).** The scalar path and the alignment test match. The aligned path differs only in the four-quad block:
  retail loads `lq a2,0 / a3,16 / t0,32 / t1,48` and stores `sq a2 / a3 / t0`, branches, then `sq t1`; the best C (`__int128` temporaries,
  all 576 load/store orders, struct copies, pointer increments, volatile, pragmas, 2.3.3 to 3.0 builds) loads the first-stored quad last
  into `v1`. The compiler colours in virtual-register order and tries `v1` and `a1` first; retail's `a2, a3, t0, t1` only appears if the
  quads stay live across the alignment test, and then the loads hoist above the branch. The neighbouring `FUN_001904f0` and
  `FUN_001906d0` are plainly hand-written (VU0 macro mode, `mtsab`/`qfsrv`), and the register choice looks human-picked too.
  Only a candidate with an `asm` block reproduces it.

The dispatcher itself (`0x3fca10`, 41,864 bytes), which contains the 22 FIGHTCALC commands, is
`src/game/beNDMWGameRam.cpp`.
