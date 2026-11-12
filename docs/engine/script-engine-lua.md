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
