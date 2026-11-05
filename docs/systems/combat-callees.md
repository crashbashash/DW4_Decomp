# FIGHTCALC direct callees: second matching pass

The [generated inventory](combat-inventory.md) lists 68 distinct bodies called directly from the FIGHTCALC region. 44 of them
had matching source; two passes matched **22 more** (all of the size-1,228-and-up messenger bodies and the 6,872-byte stat
recomputation included), plus six compiler-emitted destructors, so **66 of 68 bodies (17,932 of 18,444 bytes)** now rebuild
byte-for-byte. `make check` reports 9,591 exact functions (9,565 before) with zero mismatches and `make link` stays byte-identical.
The 26-body BLT/BLP helper run was already complete ([Combat Lua API](combat-lua-api.md)).

Almost all of these need the content-pinned alternate compiler (`-O3,p`, see [unit compilers](../engine/unit-compilers.md)); the
stock compiler differs only in delay-slot fill and one alignment `nop`. Where a form looks odd (`volatile` reads, comma-ordered
reads, a separate local for a reference slot) it is a matching construct recorded in the file header, not a claim about the
original source.

| Address | Bytes | Function | Source |
| --- | ---: | --- | --- |
| `0x002d6790` | 120 | `List_Resize` (grow capacity: min 4, double below 1024, then +1024) | `src/unmatched/List_Resize.c` (stock flags) |
| `0x002eaf60` | 172 | `StringPool_Intern` | `src/unmatched/StringPool_Intern.c` |
| `0x002fba30` | 260 | `igMetaEnum_GetValueByName` | `src/unmatched/igMetaEnum_GetValueByName.c` |
| `0x0038d860` | 2036 | `beMessenger_SelectReceivers` (+ emitted destructor `0x0038c410`, 128) | `src/unmatched/beMessenger_SelectReceivers.cpp` |
| `0x0038e6b0` | 576 | `beMessenger_PrepareDelayedSelection` | `src/unmatched/beMessenger_PrepareDelayedSelection.cpp` |
| `0x0038ed70` | 476 | `beMessenger_PushArgContext` | `src/unmatched/beMessenger_PushArgContext.cpp` |
| `0x0038ef50` | 400 | `beMessenger_PopArgContext` | `src/unmatched/beMessenger_PopArgContext.cpp` |
| `0x0038f150`..`0x0038f8f0` | 908 | `beMessenger_AppendBool/Int/Float/Vec3/Matrix/String`, `GetString` (7 bodies) | `src/game/beMessengerArgs.c` |
| `0x0038e060` | 1228 | `beMessenger_DispatchSelected` (+ emitted holder destructor `0x0038e530`, 128) | `src/unmatched/beMessenger_DispatchSelected.cpp` |
| `0x0038e8f0` | 932 | `beMessenger_EnqueueSelected` (+ emitted destructors `0x0038c390` and `0x00357a90`, 128 each) | `src/unmatched/beMessenger_EnqueueSelected.cpp` |
| `0x003fab90` | 6872 | player stat recompute (derived stats, WAZALIST rebuild, rates); owns the `0x003fc670` destructor and the `0x003fc780` query | `src/unmatched/FUN_003fab90.cpp` |
| `0x003f8760` | 548 | current-to-BASE save preparation (mirror of `FUN_003f82a0`) | `src/game/beNDMWGameRam_SaveBase.c` |
| `0x003f9c80` | 408 | HP gauge update (delta or absolute, clamp to [0, MHP], `hpmt`/`hpnm`) | `src/game/beNDMWGameRam_VitalsDelta.c` |
| `0x003f9e20` | 344 | MP gauge update (`mpmt`/`mpnm`) | `src/game/beNDMWGameRam_VitalsDelta.c` |
| `0x00447b00` | 56 | list slot nonzero test | `src/unmatched/FUN_00447b00.cpp` |
| `0x00447b40` | 88 | list slot store from `DAT_004cfe80` | `src/unmatched/FUN_00447b40.cpp` |

## Round two: what closed the three near-misses

- **`DispatchSelected`**: each of the four list appends needs fresh locals, as separately inlined AppendBool/AppendInt bodies
  would create; the first loop reads the element once into `have` and once inline; the lists are typed (`int *data`,
  `MsgRecvObj **data`). Its holder destructor `0x0038e530` is registered in `config/SLUS-20836/unit-objects.json`.
- **`EnqueueSelected`**: the insertion loop gets retail's separate index and byte-offset inductions when the list base goes through an
  inline static helper that takes it as a parameter; the row pointer is typed `unsigned`; the two stack-resident references are two
  classes (`RowRef`, `SavedRef`), emitted as two copies of the same destructor body.
- **`FUN_003fab90`**: the register rotation was graph-colouring order, not declaration order. An offline replica of the compiler's
  optimistic colouring showed that `player` needs the late virtual-register index that small inline accessors
  (`GetPlayer`, `GetProp`) give it. The body is 6,872 bytes, not 6,860: the return sequence lies past the old symbol extent, now fixed by a reviewed
  row in `data/function-extents.json`. A retail destructor address can belong to one ownership group only, so the nearby-query
  source (`beNDMWGameRam_CollectNearbyNonzeroHp.inc`) is included by this unit and both bodies are verified together.
  Helpers are struct static members because `tools/units.py` blanks free top-level helpers.

## Remaining (2 of 68): not reproducible from plain source

Both were attempted a third time with the register-colouring lessons above; neither can be matched without inline assembly, which is
not recovered source.

- **`igStrCmp` (324 bytes).** The retail code is hand-written. It builds `0x0101010101010101` and `0x8080808080808080` in `a3`/`a2`
  (`lui`/`ori`/`dsll`/`ori`/`dsll`/`ori`) before an alignment dispatch with three paths: 16-byte (`lq`, `psubw`, `pcpyud`, `pcpyld`,
  `pnor`, `psubb`, `pand`), 8-byte (`ld`, `nor`, `dsubu`, `and`) and byte-wise (`lb`/`lbu`), sharing one byte-loop tail at `0x12a5d4`
  and relying on branch-likely delay slots. The pinned compiler has no MMI or 128-bit vector builtins (its strings show the MMI
  mnemonics only in the inline-assembler opcode table; its intrinsics are `__abs`, `__mulhi`, `__strcpy`, `__sqrt`, `__rsqrt`, `__memcpy`, `__sel`).
  `__int128` only moves data (copies compile to `lq`/`sq`; any arithmetic or bitwise operator fails with "illegal data size" on the
  pinned build, the default build, 2.4 and all 15 scratch 3.0.x builds; the 2.3.3 build accepts the operators but lowers them to 64-bit
  operations on the low half). The best plain-C candidate (a `u64` `(x - K1) & ~x & K2` zero-byte test) differs in constant
  construction, alignment-test layout, loop inversion and sign extension, and lacks the 16-byte path entirely.
- **`Matrix44_Copy` (188 bytes).** The scalar path and the alignment test match. The aligned path differs only in the four-quad block:
  retail loads `lq a2,0 / a3,16 / t0,32 / t1,48` and stores `sq a2 / a3 / t0`, branches, then `sq t1`; the best C (`__int128` temporaries,
  all 576 load/store orders, struct copies, pointer increments, volatile, pragmas, 2.3.3 to 3.0 builds) loads the first-stored quad last
  into `v1`. The compiler colours in virtual-register order and tries `v1` and `a1` first; retail's `a2, a3, t0, t1` only appears if the
  quads stay live across the alignment test, and then the loads hoist above the branch. The neighbouring `FUN_001904f0` and
  `FUN_001906d0` are plainly hand-written (VU0 macro mode, `mtsab`/`qfsrv`), and the register choice looks human-picked too.
  A candidate with an `asm` block matches but is not banked.

The dispatcher itself (`0x3fca10`, 41,864 bytes) and the 22 FIGHTCALC commands remain assembly.
