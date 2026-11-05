# Combat Lua API: complete matching run

All **26 functions / 5,372 code bytes** at `0x00374800..0x00375d8c`
now rebuild byte-for-byte from readable C. The functions are in
[`src/lua/api.cpp`](../../src/lua/api.cpp) and
[`src/lua/combat.cpp`](../../src/lua/combat.cpp), in retail address order within
each unit. The [generated inventory](combat-inventory.md) lists every body,
its reviewed size and source. Finding [#1034](../findings/findings-1001-1250.md#f1034) records this checkpoint.

This is the caller API, not the calculation dispatcher. It assembles messenger
arguments, reads results and handles a few local decisions. The complete
41,864-byte GAMERAM callback containing FIGHTCALC matches as
`src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp`.
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
retail section. No new gameplay implementation or native integration is added.

The callback's post-module string-pool accessor also now has 76 bytes of matching
C at [`StringPool_GetInstance`](../../src/engine/StringPool_GetInstance.cpp)
([#1035](../findings/findings-1001-1250.md#f1035)). It lazily allocates 16 bytes and calls `StringPool_Construct`; failed
allocation leaves the cache null so a later call retries. The semantic name is
generated with the other combat dependency names. Neither that helper nor the
completed Lua API closes the calculation dispatcher. Its three immediate helpers
now also have matching source; the callback itself matches as
`src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp`.
