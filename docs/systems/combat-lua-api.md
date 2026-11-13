# Combat Lua API: complete matching run

All **26 functions / 5,372 code bytes** at `0x00374800..0x00375d8c`
now rebuild byte-for-byte from readable C. The functions are in
[`src/game/be.cpp`](../../src/game/be.cpp), in retail address order. The [generated inventory](combat-inventory.md) lists every body,
its reviewed size and source.

This is the caller API, not the calculation dispatcher. It assembles messenger
arguments, reads results and handles a few local decisions. The complete
41,864-byte GAMERAM callback containing FIGHTCALC matches as
`src/game/beNDMWGameRam.cpp`.
Its [calculation rules and recovery blockers](combat-damage.md) remain separate.

## Recovered behavior

`BLTisPlayerBullet` classifies the signed cached attack number. It returns true
below 1,000, from 10,000 through 59,999, and from 80,000 through 89,999.
Negative values therefore also return true; no lower-bound validation is added.

The hit/damage wrappers optionally query a named object's returned object at
index one, then pass that object with the cached attack arguments to FIGHTCALC.
The damage wrappers cache the three returned integers at `0x58a330`,
`0x58a338` and `0x58a340`, and return the first. Their messenger field is reloaded
between calls. `BLTgetDamageValue` explicitly masks its supplied integer argument
to eight bits before appending it.

`BLTgetDamageRank` returns three for a nonpositive first argument. Otherwise it
uses the cached damage divided by the cached denominator as floats: rank two
when the ratio is not at most one-half, rank one when it is not at most
one-quarter, and zero otherwise. The negated comparisons are retained in source.
A cached flag of one raises rank zero to one. For ranks zero/one, the second
argument or attack categories two/three can add one. Argument/local names are
descriptive; original source spelling is not asserted.

Five BLT status timers first require signed attack number `/ 10000 == 4`,
then an exact signed remainder:

| Helper | Required remainder | Additional string argument |
| --- | ---: | --- |
| Poison | 20 | yes |
| Sleep | 90 | no |
| Bind | 95 | no |
| Attack down | 70 | yes |
| Power down | 85 | yes |

Failure returns zero before messaging. Success sends the corresponding
FIGHTCALC command with the cached attack arguments and returns integer result
zero. The [signed reciprocal recovery](../../tools/m2c_compat.py) preserves
the original division, including negative inputs. The damage-rank source also
retains its original common return join; an unnecessary inner return in the
decompiler draft produced an extra branch.

The enemy-to-player helpers assemble their distinct cached arguments, rather
than reusing the player-to-enemy order. `BLPgetDamageRank` raises a returned
zero to one when the cached flag equals one. Full source and exact instruction
comparison are the authority for each wrapper's argument order.

## Matching and remaining scope

Thirteen bodies in this run use the content-pinned alternate compiler; the other
thirteen keep their existing compiler. See
[compiler requirements](../engine/unit-compilers.md). All code words, including
interior zeros, and every relocation must match; close sizes are insufficient.
`make check` verifies each complete body, and `make link` verifies the rebuilt
retail section.

The callback's post-module string-pool accessor is 76 bytes of
C at [`StringPool_GetInstance`](../../src/game/beNDMWGameRam.cpp).
It lazily allocates 16 bytes and calls `StringPool_Construct`; failed
allocation leaves the cache null so a later call retries. The semantic name is
generated with the other combat dependency names. Neither that helper nor the
Lua API closes the calculation dispatcher. The callback itself is
`src/game/beNDMWGameRam.cpp`.

## The rest of `be.cpp`

The file is the Lua class `be`: `Gap::Bec::beLuaWrapper` (name `be`, base name `igInfoManager`) whose
`beLuaWrapper::registerFunctions` binds the 116 names in `g_luaApiFunctionNames` with the
type codes in `g_luaApiFunctionCodes` to `LuaAPI_Dispatch`, and the namespace class `Gap::BecLuaWrapper`
(`Bec`). Their start-up hooks' factories, `beLuaWrapper_Create` (after `be_EnsureRegistered`) and
`BecLuaWrapper_Create`, allocate the class from `g_luaGluePool` through a class-scope placement
`operator new`; the matching placement `operator delete` frees it again if the constructor throws,
which is the cleanup each factory's exception table records. A code's low byte is the binding kind
plus 512: 5 int, 9 bool, 11 float, 13 string, 7 long, 15 void. The dispatcher reads each argument
from the `LuaValue` array; a bool result is pushed through an unsigned conversion, an int result
through a signed one. The C++ class `be`
is an insight manager: `be_Start` finds the system, messenger, material controller and demo
manager into `g_beSystem`, `g_beMessenger`, `g_matCtrl` and `g_beDemoManager` and stores itself in
`g_be`; `be_Reset` empties its string list. The DM functions queue keep-messages on the demo
manager (`beDemoManager_AddKeepMes` kinds 0 send, 1 send on a false reply, 2 on a true one).

## Open questions

- `be`'s slots 21 to 27 take beSystem's names (same insight-manager interface); `be_AddToScheduler`,
  `be_RemoveFromScheduler`, `be_Stop` and `be_Update` are empty in `be`.
- `LuaAPI_RegisterClasses` is the empty per-library registration called at boot between the Bec
  and NDMW libraries' ones; the name is from that position.
- The overload suffixes (`sd_29`..`sd_32`, `DMsetSD_40`.., `MDLsetWorldPosTarget_78/79`) are API ids.
- The bytes `g_cardFolderSetValue` .. `g_flagFlipOnValue` are small-data constants (1 or 0) the
  setters store; whether the source spelled them as named constants is not established.
- `text_igInfoManager` takes `text_` because `igInfoManager` is a type name.
