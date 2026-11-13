# Script Engine (Lua 4.0.1 + native API)

The [generated dependency inventory](lua-dependencies.md) maps all 116 binding
implementations and their direct retail call closure, retaining unresolved virtual
and their direct retail call closure, retaining unresolved virtual
and register transfers. [Material-contact helpers](material-contact.md) cover
the complete first engine module, with matching Lua wrappers.

A timed-message callback can re-enter enqueue during the update. A negative delay
inserts ahead of the executing record, which exposes retail head recycling. What that
means for gameplay or general stage-unload behaviour is not established.

## Version
The embedded VM is **stock Lua 4.0.1** (not Lua 5.x):
- Version string `"Lua 4.0.1"` @ `0x004eb1b8`.
- Bytecode chunks begin `1B 4C 75 61 40`: `ESC "Lua"`, version byte **`0x40`**
  (Lua 4.0's `VERSION`).
- Lua 4.0 error strings present: `"bad signature in \`%.99s'"` (0x004ec4b0),
  `"virtual machine mismatch in \`%.99s':\n  %.20s is %d but read %d"`
  (0x004ec4d0), `"\`%.99s' apparently contains more than one chunk"` (0x004ec650),
  `"syntax error"`, `"\`dostring' cannot run pre-compiled code"`.
- Lua 4.0 API strings: `gettagmethod`, `settagmethod`, `settag`, `gettable`,
  `settable`, `getglobal`, `setglobal`.

## Integration classes (C++ side)
| Address | Symbol |
| --- | --- |
| `0x004ea180` | `igLuaState` |
| `0x004ea190` | `_luaState` |
| `0x004ea1b0` | `igLuaGlue` |
| `0x00501428` | `_luaManager` |
| `0x00501610` | `_luaInterface` |
| `0x00501b00` | `_callLuaFile` |
| `0x00503270` | `_callLuaName` |
| `0x00504f38` | `_callLua` |
| `0x005047f8` | `beLuaState` |
| `0x00504810` | `beLuaInfo` |
| `0x00504830` | `beLuaData` |
| `0x00504870` | `beLuaDataObject` |
| `0x00503f80` | `beModelCtrlLUACALL` |
| `0x00504730/40` | `SHOW_LUACALL` / `HIDE_LUACALL` |
| `0x005047e0` | `_isLuaCallDisp` |

Error handlers: `igLuaState::runString()/runFile()/runBuffer() failed - reason %s`,
with reason codes `LUA_ERRRUN`, `LUA_ERRFILE`, `LUA_ERRSYNTAX`, `LUA_ERRMEM`,
`LUA_ERRERR` (0x004ea9c8–0x004eaa08).

## Source files of the binding library
The Alchemy Lua binding library (`0x23c440`–`0x246d28`, before stock Lua's `lapi.c`) was compiled one
file at a time, not as one translation unit: runs of inline methods close files in the middle of it,
where a library-sized unit would have one run at its end. All four files share
`src/engine/lua/LuaLibrary.h`.

- **The library front**, `src/engine/lua/LuaRegistration.cpp` (`0x23c440`–`0x23c858`): the
  `LuaLibrary` registration latch, igLuaState's and igLuaGlue's metadata (meta-object getters, vtable
  readers, registrars, igLuaState's two reflected fields `_luaState` and `_memPool`), then igLuaGlue's
  inline methods. igLuaGlue has no virtual function out of line, so its vtable and inline methods are
  emitted here; two of them only call the glue's start-up and shutdown in the binding code.
- **The binding**, `src/engine/lua/LuaBinding.cpp` (`0x23c860`–`0x2442dc`): types and value
  conversion (`LuaType_*`, `LuaValue_*`), bound functions and their overload resolution
  (`LuaFunction_*`), objects and their fields (`LuaObject_*`), classes (`LuaClass_*`), the typed
  array classes (`Lua<Type>Array_Delete`/`_Get`/`_Set`/`_New`) and `LuaGlue_Initialize`. It ends with
  the base class's two empty virtual slots, `LuaClass_RegisterConstants` and
  `LuaClass_RegisterFunctions`: every array class's vtable and the game's `be` class point at them,
  and MWCC emits inline virtuals after a file's last ordinary function, so they close the file.
- **The state**, `src/engine/lua/LuaState.cpp` (`0x2442e0`–`0x24683c`): `LuaBoolArray_Set`,
  `LuaGlue_Shutdown` and the field-table walker, the script functions `new` and `cast`, the binding's
  hash tables, the thread-local slots, igLuaState's out-of-line methods (`igLuaState_Open`,
  `igLuaState_Close`, `igLuaState_Run*`), the error handler and igLuaState's slot-22 getter, which
  igLuaState's vtable is emitted with.
- **The last file**, `src/engine/lua/LuaRuntime.cpp` (`0x246840`–`0x246d28`): the thread-local
  table's internals and the game's `lua_dofile`.

The cut at `0x2442e0` has three kinds of evidence. `LuaBoolArray_Set` reads its own copies of
`"%s: Non-number array access"` and `"Value to set must be number"`, where the other array setters
share one pair, and MWCC pools equal literals within a file. The field-table walker's destructor, valid
test and getter exist twice with identical bytes, one copy on each side. And the inline-virtual run
above ends the binding. No retail call crosses any cut with the register knowledge a `static` callee
compiled earlier in the same file gives its caller
([emitted functions](emitted-functions.md#whole-file-units)).

The base Lua class's vtables (`g_Lua*ArrayClass_vtable`) stay retail data: under the engine profile
MWCC writes an RTTI pointer into a class's first vtable word, where retail Alchemy vtables hold 0.
The array classes store their vtable in an inline constructor, and calls through it go through a view
class that declares the slots without defining them.

### Hash tables
The binding keeps six chained hash tables: fields, functions, classes, properties, constants and
enums, each with a shift, a bucket count, an entry count, a bucket array and a busy count. Their
insert, link, resize and remove functions are identical but for the table; a property is linked
through its second base, so the property table's link and resize adjust the pointer between the
entry and its link. The growth rules are the thread-local table's below, with each table's own
minimum size.

### Script functions
`new(table)` follows the table's `base` fields to the class at the root, runs its `<Class>Peer`
constructor when the globals hold one (else the class's own), and makes the argument the new object's
base. `cast(className, object)` returns the object as userdata of the named class when that class
derives from the object's; it tests the derivation twice the same way round, so the reverse direction
is never accepted.

### Thread-local values
The binding keeps values per thread, such as the Lua state its start-up stores, in a hash table of
24-byte entries: the key (the current thread's object xored with the slot number), the bucket chain's
next and previous entries, the slot, the value and the thread. The thread comes from the thread
manager. A key's bucket is `(bucketCount - 1) & (key ^ (key >> shift))`. The bucket array is
allocated on the first insertion, 16 buckets, and freed when the last entry goes. An insertion resizes
the table before it links the entry, a removal after it unlinks one: the table doubles when it holds
more entries than buckets and halves, down to 16 buckets, when it holds fewer than half. A lookup
raises a busy count while it walks a chain; a resize does nothing while the count is raised, and the
lookup resizes afterwards if the number of entries changed meanwhile.

### `lua_dofile`
The game replaced Lua's `lua_dofile`, which reads through stdio, with one that reads through an
Alchemy `igFile` opened `"rb"`: it seeks to the end for the size, allocates the buffer with
`luaM_realloc`, reads the file whole and runs it with `lua_dobuffer` under the file's name. It returns
`LUA_ERRFILE` when the open fails and `LUA_ERRMEM` when the buffer cannot be allocated. `luaB_dofile`
and `igLuaState`'s `runFile` call it; the retail linker dropped stock `ldo.c`'s copy.

## The native-function binding
Scripts call C++ through an object called **`be`** (e.g. `be:SYSgetPlayerLevel()`).
The 116 exposed functions are bound through four parallel tables.

### 1. Name table: `0x004c8560`
An array of 116 `char*` pointers to the API name strings. The names are stored
around `0x0050c700`–`0x0050cfa0`, e.g.:
```
[  0] -> 'MATsetRun'          [  9] -> 'SYSctlPlayer'
[ 19] -> 'SYSgetPlayerLevel'  [ 57] -> 'SYSgetPlayerLevel' (index)
...
[108] -> 'SYSgetWeaponName'   [112] -> 'GETCOMMON'
[113] -> 'GETPLAYER1'         [114] -> 'GETPLAYER2'   [115] -> 'GETPLAYER3'
```

### 2. Descriptor table: `0x0050cfc0`
Variable-length records. Per entry:
```
word0 : descriptor
          name_index = (word0 >> 13) & 0x1ffff
          subcount   = (word0 >>  8) & 0x1f
          flag bit30 (selects base table), bit31
          id         =  word0        & 0xff
word1 : value word
word2..: subcount extra words
```

### 3. Dispatch jump table: `0x0050d620`
116 entries (u32), each pointing at a 1–4 instruction **stub** in
`0x003707f0`–`0x00371798`. Each stub `jal`s the real implementation, then
returns to the common epilogue `0x003717c8`.

### 4. Dispatcher: `0x00370780`
```
370780: addiu sp,sp,-48
370784: li    a1,-1
370790: move  s1,a0
370794: jal   0x247290          ; s0 = get "self" object (arg -1)
3707a0: lhu   v0,42(v0)         ; v0 = *(u16*)(obj+42)
3707a4: andi  v0,v0,0xfff        ; v0 &= 0xfff
3707a8: beqz  v0,0x3707c0
...
3707c8: sltiu at,v1,116         ; v1 = *(s16*)(obj+40) = function id
3707cc: beqz  at,0x3717a8       ; out of range -> error
3707d8: addiu a0,a0,-10720       ; a0 = 0x0050d620 (jump table)
3707e0: lw    v1,0(v1)           ; v1 = jump_table[id]
3707e4: jr    v1
```
So each script-API call routes: object → id (`obj+40`) → jump table → stub →
real C++ function.

### Registration
`LuaAPI_Register` calls the generic registrar:
```
0x23f4f0(L, 0, 0x00370780, 0x004c8560, 116, 0x0050cfc0, 0)
          ^dispatcher  ^names   ^count ^descriptors
```

## Full 116-function table
Machine-readable copy: `ghidra-projects/dw4/script_api.json`.

> **`SYSgetRandom` (id 4) is the game's only RNG entry point.** It is
> `igMersenneTwisterRandomNumber::genrand() % M`, seeded once at boot with the
> constant **5150**. Every one of its 112 call sites (and the 69069-based
> seeding) is catalogued in [`../systems/rng.md`](../systems/rng.md).

Columns: **stub** = dispatcher target; **real** = C++ implementation the stub calls.

| id | name | stub | real impl |
| --- | --- | --- | --- |
| 0 | `SYSisJoinPlayer` | `0x003707f0` | `0x00371c70` |
| 1 | `SYSgetPlayerName` | `0x00370818` | `0x00371ca0` |
| 2 | `SYSgetPlayerNinzu` | `0x00370838` | `0x00371d70` |
| 3 | `SYSgetWeaponName` | `0x00370860` | `0x00371cd0` |
| 4 | `SYSgetRandom` | `0x00370888` | `0x00371f10` |
| 5 | `SYSgetDifficulty` | `0x003708b0` | `0x00371da0` |
| 6 | `SYSsetDifficulty` | `0x003708d8` | `0x00371dd0` |
| 7 | `SYSgetCameraMode` | `0x003708e8` | `0x00371e10` |
| 8 | `SYSgetLightMode` | `0x00370910` | `0x00371e70` |
| 9 | `SYSgetArea` | `0x00370938` | `0x00371ed0` |
| 10 | `SYSgetCountry` | `0x00370960` | `0x00371ee0` |
| 11 | `SYSgetTarget` | `0x00370988` | `0x00371ef0` |
| 12 | `SYSgetIsPackOnly` | `0x003709b0` | `0x00371f00` |
| 13 | `SYSsetGateStage` | `0x003709d8` | `0x00371f60` |
| 14 | `SYSgetGateStageName` | `0x003709f0` | `0x003720f0` |
| 15 | `SYSgetGateStageNo` | `0x00370a10` | `0x00372150` |
| 16 | `SYSctlDeviceFolder` | `0x00370a38` | `0x003721b0` |
| 17 | `SYSctlDiskFolder` | `0x00370a70` | `0x003722c0` |
| 18 | `SYSctlFlagFolder` | `0x00370aa0` | `0x003723c0` |
| 19 | `SYSgetPlayerLevel` | `0x00370ac8` | `0x00372590` |
| 20 | `SYSgetPlayerDigimon` | `0x00370af0` | `0x003725c0` |
| 21 | `SYSisGetShinkaDigimon` | `0x00370b18` | `0x003725f0` |
| 22 | `SYSctlCardFolder` | `0x00370b40` | `0x00372640` |
| 23 | `SYSctlBit` | `0x00370b68` | `0x003724a0` |
| 24 | `SYSctlShinka` | `0x00370b98` | `0x003727d0` |
| 25 | `SYSctlPlayer` | `0x00370bc8` | `0x00372970` |
| 26 | `CFLclear` | `0x00370bf8` | `0x00372a30` |
| 27 | `CFLsetName` | `0x00370c08` | `0x00372b50` |
| 28 | `CFLgetFolderName` | `0x00370c18` | `0x00372ce0` |
| 29 | `sd` | `0x00370c38` | `0x00372ff0` |
| 30 | `sd` | `0x00370c58` | `0x00373060` |
| 31 | `sd` | `0x00370c78` | `0x003730a0` |
| 32 | `sd` | `0x00370ca0` | `0x00373120` |
| 33 | `MATisPlayer` | `0x00370cc0` | `0x00373160` |
| 34 | `MATisAllPlayer` | `0x00370ce8` | `0x00373180` |
| 35 | `MATgetPlayerNo` | `0x00370d10` | `0x003731a0` |
| 36 | `MATisRidePlayer` | `0x00370d38` | `0x003731c0` |
| 37 | `MATisRideOffPlayer` | `0x00370d60` | `0x003731f0` |
| 38 | `MATgetPlayerMatStat` | `0x00370d88` | `0x00373220` |
| 39 | `MATsetRun` | `0x00370db0` | `0x00373250` |
| 40 | `DMsetSD` | `0x00370dc0` | `0x00373280` |
| 41 | `DMsetSD` | `0x00370de8` | `0x003732d0` |
| 42 | `DMsetSD` | `0x00370e08` | `0x00373310` |
| 43 | `DMsetSD` | `0x00370e28` | `0x00373350` |
| 44 | `DMchkSD` | `0x00370e48` | `0x00373390` |
| 45 | `DMchkSD` | `0x00370e70` | `0x003734b0` |
| 46 | `DMswtSD` | `0x00370e90` | `0x00373620` |
| 47 | `DMswtSD` | `0x00370eb0` | `0x00373660` |
| 48 | `DMswtEnd` | `0x00370ed0` | `0x003736a0` |
| 49 | `DMcase` | `0x00370ee0` | `0x003736c0` |
| 50 | `DMsetLua` | `0x00370ef0` | `0x003735c0` |
| 51 | `DMmsgBox` | `0x00370f00` | `0x003735f0` |
| 52 | `DMrun` | `0x00370f18` | `0x003736f0` |
| 53 | `DMgetCount` | `0x00370f28` | `0x00373710` |
| 54 | `FLGisOn` | `0x00370f50` | `0x003737b0` |
| 55 | `FLGset` | `0x00370f78` | `0x00373840` |
| 56 | `FLGflip` | `0x00370f90` | `0x003738e0` |
| 57 | `COUNTERset` | `0x00370fa0` | `0x003739f0` |
| 58 | `COUNTERget` | `0x00370fb8` | `0x00373aa0` |
| 59 | `MDLgetInfoName` | `0x00370fe0` | `0x00373b30` |
| 60 | `MDLgetRamNo` | `0x00371000` | `0x00373b20` |
| 61 | `MDLgetRecNo` | `0x00371028` | `0x003742d0` |
| 62 | `MDLgetMHp` | `0x00371050` | `0x00373d00` |
| 63 | `MDLgetHp` | `0x00371078` | `0x00373d10` |
| 64 | `MDLgetPosStr` | `0x003710a0` | `0x00373b40` |
| 65 | `MDLgetRotStr` | `0x003710c8` | `0x00373c10` |
| 66 | `MDLaddHp` | `0x003710f0` | `0x00373d20` |
| 67 | `MDLsetSeq` | `0x00371100` | `0x00373d50` |
| 68 | `MDLsetSD` | `0x00371110` | `0x00373d90` |
| 69 | `MDLisLive` | `0x00371128` | `0x00373dd0` |
| 70 | `MDLgetBulletKind` | `0x00371150` | `0x00373e80` |
| 71 | `MDLgetBulletName` | `0x00371178` | `0x00373e90` |
| 72 | `MDLgetBulletBoxNo` | `0x00371198` | `0x00373ee0` |
| 73 | `MDLdspDamage` | `0x003711c0` | `0x00374100` |
| 74 | `MDLdspDamageP` | `0x003711d0` | `0x00374120` |
| 75 | `MDLdspExp` | `0x003711e0` | `0x00374140` |
| 76 | `MDLsetDMGTurn` | `0x003711f0` | `0x00374160` |
| 77 | `MDLisCallName` | `0x00371200` | `0x00374180` |
| 78 | `MDLsetWorldPosTarget` | `0x00371228` | `0x003741d0` |
| 79 | `MDLsetWorldPosTarget` | `0x00371240` | `0x00374200` |
| 80 | `MDLgetKyoriSquare` | `0x00371250` | `0x00374260` |
| 81 | `MDLisSeqName` | `0x00371280` | `0x003742e0` |
| 82 | `MDLisStatus` | `0x003712a8` | `0x00374410` |
| 83 | `BLTisPlayerBullet` | `0x003712d8` | `0x00374800` |
| 84 | `BLTgetShootRamNo` | `0x00371300` | `0x00374880` |
| 85 | `BLTisHitCheck` | `0x00371328` | `0x00374890` |
| 86 | `BLTgetDamageValue` | `0x00371350` | `0x00374a40` |
| 87 | `BLTgetDamageRank` | `0x00371378` | `0x00374bb0` |
| 88 | `BLTisCritical` | `0x003713a0` | `0x003749a0` |
| 89 | `BLTgetStunTime` | `0x003713c8` | `0x00374d00` |
| 90 | `BLTgetPoisonTime` | `0x003713f0` | `0x00374de0` |
| 91 | `BLTgetSleepTime` | `0x00371418` | `0x00374f00` |
| 92 | `BLTgetBindTime` | `0x00371440` | `0x00375010` |
| 93 | `BLTgetAttackDownTime` | `0x00371468` | `0x00375120` |
| 94 | `BLTgetPowerDownTime` | `0x00371490` | `0x00375240` |
| 95 | `BLTcalcSkillUp` | `0x003714b8` | `0x00375360` |
| 96 | `BLTcalcEXPUp` | `0x003714d0` | `0x00375410` |
| 97 | `BLTgetAttributeStr` | `0x003714f8` | `0x00374cc0` |
| 98 | `BLPisHitCheck` | `0x00371518` | `0x003754a0` |
| 99 | `BLPgetDamageValue` | `0x00371540` | `0x00375540` |
| 100 | `BLPgetAttackZokusei` | `0x00371568` | `0x00375690` |
| 101 | `BLPgetDamageRank` | `0x00371588` | `0x00375730` |
| 102 | `BLPgetStunTime` | `0x003715b0` | `0x00375830` |
| 103 | `BLPgetPoisonTime` | `0x003715d8` | `0x00375980` |
| 104 | `BLPgetSleepTime` | `0x00371600` | `0x00375a30` |
| 105 | `BLPgetBindTime` | `0x00371628` | `0x00375ad0` |
| 106 | `BLPgetAttackDownTime` | `0x00371650` | `0x00375b70` |
| 107 | `BLPgetPowerDownTime` | `0x00371678` | `0x00375c30` |
| 108 | `BLPcalcKoukaMagic` | `0x003716a0` | `0x00375cf0` |
| 109 | `TXTgetCallNo` | `0x003716c8` | `0x003747f0` |
| 110 | `PLAYERgetPos` | `0x003716f0` | `0x003744a0` |
| 111 | `PLAYERgetDataStr` | `0x00371718` | `0x003744e0` |
| 112 | `PLAYERgetPosStr` | `0x00371740` | `0x00374620` |
| 113 | `LISsetDifficultMax` | `0x00371770` | `0x00375d90` |
| 114 | `MsgBox` | `0x00371780` | `0x00374730` |
| 115 | `ShutDown` | `0x00371798` | `0x00374740` |

## Calling convention (important)
The EE ABI used here passes arguments 5–8 in **`t0`–`t3`**, not on the stack.
Example (`bePlayer_GetStruct`):
```
371c10: lui   v0,0x4d
371c18: sll   v1,a0,2            ; a0 = player index+1
371c1c: addiu v0,v0,-30944       ; v0 = 0x004c8720 (player-slot table)
371c28: addu  v0,v0,v1
371c2c: lw    a0,-24128(at)      ; a0 = *(0x0058a1c0) main object
371c30: lw    t0,0(v0)           ; t0 = 5th arg = method name from table
371c40: jal   0x38e5f0           ; call method(obj, "GAMERAM", 0, 0, t0)
```

## Script loading / chunk storage

Retail startup, duplicate-name execution, whole-VM globals cleanup and coordinated
SD/Lua/DM teardown are recovered in [Lua loading and ownership](lua-loading-ownership.md).
- Scripts are compiled Lua 4.0.1 chunks concatenated inside `NDMW.AFS` entries.
- All chunk headers carry `source='=(none)'` (compiled from in-memory strings).
- Named scripts (`bML01001.lua`, `armorshop.lua`, …) appear as **string
  constants** passed to `_callLuaFile`; 269 unique names found.
- Parsing/disassembly tooling: `scripts/lua_dump.py`, `scripts/lua_extract.py`.

## Lua bytecode format (written from lundump.c)
Header (21 bytes):
```
1B 4C 75 61   ESC "Lua"
40            version (Lua 4.0)
01            endianness (1 = little)
04 04 04      sizeof(int/size_t/Instruction)
20            SIZE_INSTRUCTION (bits) = 32
06            SIZE_OP = 6
09            SIZE_B = 9
08            sizeof(Number) = 8 (double)
<8 bytes>     test number
```
`Proto` (recursive):
```
source        : size_t len + bytes (len includes trailing NUL; 0 => NULL)
lineDefined   : int32
numparams     : int32
is_vararg     : u8
maxstacksize  : int32
locals        : n(int32) * { varname:str, startpc:int32, endpc:int32 }
lines         : n(int32) * int32
constants     : nkstr(int32)+strings; nknum(int32)+doubles; nkproto(int32)+Protos
code          : n(int32) * u32 instruction
```
Instruction: 32 bits → opcode[0:6], B[6:15], A[15:32]; single `U` arg = bits[6:32].

> **Signed operands and jumps:**
> `MAXARG_S = ((1 << 26) - 1) >> 1 = 33554431`; decode
> `s = (ins >> 6) - MAXARG_S`. Jump target is stock Lua 4.0.1
> `pc + 1 + s`. A `pc + s + 2` target only compensates for a
> decoder using the wrong bias; that bias also makes every PUSHINT literal
> one too small and turns normal numeric-for step 1 into apparent step 0.
> The tools and generated corpus use the stock decode; see the
> [numeric audit](lua-numeric-audit.md).
Opcode enum (0..48): `OP_END, OP_RETURN, OP_CALL, OP_TAILCALL, OP_PUSHNIL, OP_POP,
OP_PUSHINT, OP_PUSHSTRING, OP_PUSHNUM, OP_PUSHNEGNUM, OP_PUSHUPVALUE, OP_GETLOCAL,
OP_GETGLOBAL, OP_GETTABLE, OP_GETDOTTED, OP_GETINDEXED, OP_PUSHSELF,
OP_CREATETABLE, OP_SETLOCAL, OP_SETGLOBAL, OP_SETTABLE, OP_SETLIST, OP_SETMAP,
OP_ADD, OP_ADDI, OP_SUB, OP_MULT, OP_DIV, OP_POW, OP_CONCAT, OP_MINUS, OP_NOT,
OP_JMPNE, OP_JMPEQ, OP_JMPLT, OP_JMPLE, OP_JMPGT, OP_JMPGE, OP_JMPT, OP_JMPF,
OP_JMPONT, OP_JMPONF, OP_JMP, OP_PUSHNILJMP, OP_FORPREP, OP_FORLOOP, OP_LFORPREP,
OP_LFORLOOP, OP_CLOSURE`.

## Script semantics (observed)
- Native calls look like `be:FUNCNAME(args)`; `be` is the global API object.
- `sd` (Lua-facing name `sd`, ids 29–32) is a **generic set/query dispatcher**:
  ```
  be:sd('PLAYER','OFCTRL')
  be:sd('SUBWND','REMOVE')
  be:sd('ENEMY','ALLCLEARSTATUS')
  be:sd('PLAYER', 'ALLCLEARSTATUS')
  ```
- Object controllers invoked with action keys: `MODELCTRL` (`GENERATE`,
  `SETGENERATEPOS`), `PLAYERPOINT` (`GETGENERATEPOS`), `STAGECTL` (`NEXTSTAGE`),
  `NUMBERCTRL`, `FIGHTCALC`.

## Open questions
- The thread-local table's names (`ThreadLocalTable_*`, `g_threadLocal*`) describe what it does; no
  string or symbol names it.
- `LuaGlue_Initialize` and `LuaGlue_Shutdown` are named from what they do (build the array-type
  conversions and run the registered start-up hooks; undo them). igLuaGlue's virtual slots that call
  them have no recovered names.
- Kind 16 (`LUA_KIND_STATIC`) is named from where it is accepted; what a value of that kind holds is
  not established.
- The sixth hash table (`LuaEnumTable_*`, `g_luaEnum*`) is named from its place after the constant
  table; nothing names what it holds, and only its link, resize and remove survive in the image.
- `LuaProperty`'s first base is shaped as a plain hash link; what it is for is not established.
- `igLuaState_Open` and `igLuaState_Close` (igLuaState's slots 7 and 10) are named from what they do;
  `beLuaState` inherits slot 7.
- Strings `LuaState.cpp` reads (`"base"`, `"%sPeer"`, `"function"` and the tag-method event names)
  are at the same addresses as the binding's, which fits two files only if the linker merged equal
  strings across files.
- The hash-table run (`0x244dd0`–`0x245e7c`) and the thread-local table in `LuaRuntime.cpp` follow
  igLuaState's slot-22 getter's file in the way template instances end a file, which would put more
  cuts in both; the binding calls those functions, so this is unresolved.
- Whether `-RTTI off` belongs in the Alchemy profile, which would let the array classes' vtables be
  compiled instead of kept as retail data, is the owner's decision.
