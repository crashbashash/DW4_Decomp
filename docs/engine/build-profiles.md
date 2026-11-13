# Build profiles: one translation unit, one profile

The retail ELF was linked from
translation units, and a compiler, a flag set and an exception mode belong to a unit,
never to one function: every function of a unit was compiled by the same command.
Recording those settings only **per function**
(`config/SLUS-20836/unit-compilers.tsv`, `config/SLUS-20836/unit-flags.tsv`) allows what the build-settings audit
measured: 58 % of the address-contiguous class runs mixing compilers in
ways no single build could produce, 349 rows pinning a profile the function also
matches without, and 1,684 `.cpp` units emitting exception metadata retail never had
because the exception mode is not a recorded setting at all. The unit table is what the gate in
[CLAUDE.md](../../CLAUDE.md) ("One translation unit, one profile") stands on.

## The model

`config/SLUS-20836/units.tsv` holds **one row per translation unit**:

```
@compiler  <id>  <repository-relative executable>  <SHA-256>
<lo>  <hi>  <name>  <compiler id>  <flags>  <exceptions>  <status>  <source>
```

* `lo`/`hi`: a unit covers every function whose start address satisfies
  `lo <= va < hi` (`hi` is the end of its last function). Units never overlap and
  never cross a function.
* `compiler`: an id declared by an `@compiler` line in the same file, which names the
  repository-relative executable and its SHA-256. `tools/unitprofiles.py` refuses a
  missing or changed executable rather than falling back to another build.
* `flags`: the complete flag string except the exception mode.
* `exceptions`: `on` or `off`. `off` adds `-Cpp_exceptions off` to every MWCC compile
  of the unit (C files included: the C front end ignores it, measured over every C
  unit in the sweep); nothing is passed for `on` (the compiler default) or for the Sony
  EE GCC, which has no such switch. The mode is read from retail: MWCC emits a 12-byte
  exception index record for every function with a stack frame or a call when
  exceptions are on, and for a frameless leaf that inlined a member function (an
  inlined free function gives none), so a unit with any recorded function (`config/SLUS-20836/exceptions.txt`) is
  `on`; a unit whose non-leaf functions have no record is `off`; a unit of nothing but
  frameless leaves decides nothing and is recorded `off` with the reason in `source`.
* `status`: `-`, or `provisional` when the members' evidence has no common profile
  (below).
* `source`: the evidence, in words: how the boundary was drawn, the exception
  evidence (`exceptions on: 12/14 functions have retail index records`), the pins the
  members carried and how many members each candidate reproduces.

`tools/unitprofiles.resolve(va, …)` is the one place that turns an address into a
profile. `tools/verify.py`, `tools/check.py` and `tools/linkgen.py` all go through it,
and `tools/buildcache.unit_profile_sha` keys every cached answer on the unit row, the
compiler digests and the per-function rows it resolves with, so a profile change
invalidates exactly the functions it touches.

### Per-function rows are overrides, and overrides are provisional

`config/SLUS-20836/unit-flags.tsv` (`va  flags  status  reason`) and `config/SLUS-20836/unit-compilers.tsv`
(`va  executable  SHA-256  status  reason`) survive as **override** tables. Where a
unit covers the function a row is accepted only with `status = provisional`
(`tools/unitprofiles.resolve` raises otherwise, and the function reports
`compile failed`). The verifier compiles the function under its unit profile first and
tries the override only when the unit profile does not reproduce the code bytes:

| unit profile | override | category | head token |
| --- | --- | --- | --- |
| reproduces the code | none | the ordinary category (`match`, `code-only`, …) | - |
| reproduces the code | row exists | the ordinary category; the row is stale | `override=unused` / `override=redundant` |
| fails | reproduces the code | **`foreign-profile`** | `override=foreign` |
| fails | fails | `mismatch`, naming both profiles | - |

`foreign-profile` is debt, never a match: `cover :` excludes it, `tools/progress.py`
counts it (`foreign_profile.functions`, `foreign_profile.bytes`) and the debt ratchet
(`config/debt-baseline.json`) lets it only fall. The relink builds a foreign-profile
function with its override (the only profile known to reproduce it) and the orphan
accounting treats any exception metadata that compile emits exactly as it treats a
`code-only` `extra` unit. `make check` lists stale rows after the category table
(`!! stale overrides:`); delete them.

Outside every unit (a regional target's tables, a test fixture) the rows are the whole
profile and need no status. `tools/unitprofiles.units_path`
picks `config/SLUS-20836/units.tsv` for the repository's symbol map and a `units.tsv` beside any
other map, when there is one.

## Where the unit boundaries come from

`tools/gen_unit_profiles.py` draws them from evidence, in this priority order (a unit
never crosses a function):

1. **Library and Sony blocks.** The six Sony EE GCC blocks of
   [sd-prologue](sd-prologue.md) and the libpng and Lua regions of
   [module-map](module-map.md), cut at the module map's address-contiguous runs (a
   run of functions separated from the next by data is the closest proxy for the
   library's object files). A Sony run is cut again where the prologue kind changes,
   because those blocks also hold Metrowerks runtime objects: a body that saves
   registers with `sd` is Sony EE GCC output, one that saves with `sq` is MWCC, and a
   body that saves nothing follows its predecessor.
2. **Class runs.** Consecutive functions carrying the same class label
   (`<Class>_<Method>`, `Gap__<Lib>__<Class>__vfunc_N`), unlabeled functions between
   two members included: MWCC emits a unit's functions in source order and the linker
   places whole objects, so a run is a lower bound on one unit.
3. **Unlabeled runs.** Everything else, as consecutive unlabeled functions. No boundary
   evidence exists there, so a run is cut where the retail exception evidence changes
   (a recorded function beside a non-leaf function without a record) and where the
   pins change. Such a unit never claims a conflict it cannot see; its `source` says
   so.

The audit's grouping script (`groups2.py`, address-contiguous class runs as the unit
proxy) is what rule 2 implements.

## How a unit's profile is chosen

The candidates are the members' current pins plus, for a unit whose pins disagree, the
3.0.3 build (`local/mwcps2/3.0.3-020716`): the audit found it reproduces the engine's
"default-only" members where the 2003 betas do not. A candidate is scored by the
members it reproduces. The evidence is the result files the generator is given
(`--results`: JSON lines with `va`, `compiler`, `flags`, `ok` and, when present,
`cat`), read conservatively:

* a function's own pin reproduces it (the tree verifies that today);
* a result whose category is `match`, `code-only`, `name-defect` or `inventory-gap`
  reproduces the code bytes under that compiler, flags and exception mode;
* a `mismatch` or `compile` category is a definite no;
* a bare `ok = false` (the audit's older result files) is a no only when the metadata
  could have passed, i.e. the function is fully verified under its pin and, for C++,
  the exception mode agrees: a `.cpp` with exceptions on in an exceptions-off unit
  fails verification on its `.exceptix` record whatever its code did.

Pairs the evidence does not decide are written out (`--sweep-tasks`) or verified on the
spot (`--sweep RESULTS`): `tools/verify.py` with the tables disabled, so the compiler
and flags are exactly the candidate's and the exception mode is the unit's. The best
candidate wins; ties go to the pin most members already carry, then to the Makefile
default. Members the winner does not reproduce keep an override row and the unit is
marked `provisional`. An emitted body or duplicate of a compiler unit
(`config/SLUS-20836/unit-objects.json`) is not compiled on its own, so a pin on such an address
that differs from its unit's profile is kept as an untested override.

A stub cannot decide a unit's profile, since a 12-byte `vfunc_20` matches under both
compilers. The `beNDMWShopDevice` unit (`0x43cc20`-`0x43d0bc`) looks like default `-O3` on
its stub alone; `vfunc_21` reproduces only under the 2003 beta at `-O3,p` with exceptions on.

## Reviewing a provisional unit

A provisional unit is a claim that its members cannot have been built by one command,
which is impossible for a real translation unit. One of three things is true:

1. **The boundary is wrong.** Two classes of the same name in different objects, a
   library run that is really several objects, an unlabeled neighbour that belongs to
   the next unit. Check the retail layout (`config/SLUS-20836/layout.txt`, `asm/`) and the names;
   if the run must be cut, regenerate with the evidence that says so (add the rule to
   `gen_unit_profiles.build_units` or hand-split the row, keeping the `source`).
2. **The dissenting source is wrong.** The function's C/C++ was shaped to match under
   a different compiler or flag set; the same bytes are usually reachable under the
   unit's profile with a different source shape. The work is to re-attempt
   under the unit profile (`tools/verify.py <va> <file>` does exactly that), and
   when it matches delete the override row. `make check` reports a row the unit profile
   has made unnecessary as `override=unused`.
3. **The profile is wrong.** The majority pin is itself the anomaly (a dozen functions
   matched by the default compiler because they are small, one large one that only the
   2003 build reproduces). Re-verify the members under the dissenter's profile; if
   they all pass, change the unit row and delete the override.

Until one of those is done the function stays `foreign-profile` and the unit stays
`provisional`. Never pin a profile to make one function pass while its unit says
otherwise.

A per-function pin on an emitted body breaks every unit that names it as a duplicate.
`0x357a90` and `0x38c390` are emitted by the `beMessenger` unit at `0x38e8f0` (combat
`-O3,p`, exceptions on), and default-compiler pins on them made `0x38ed70`, `0x38ef50`,
`0x38e6b0` and `0x38bee0` fail on the kept copy's delay-slot scheduling.

## Adding or changing a unit by hand

* Keep `lo`/`hi` on function boundaries (`config/SLUS-20836/symbols.txt`) and the rows sorted and
  disjoint; `tools/unitprofiles.parse` refuses overlaps.
* Name the compiler by an `@compiler` id; add an `@compiler` line (path and SHA-256)
  for a build the file does not know yet.
* Put the evidence in `source`, not in a commit message alone: which functions have
  retail exception records, which members were verified under the profile.
* A new override row needs `provisional` and a reason; it makes the function
  `foreign-profile` until the unit profile reproduces it.
* Then `make check` (the cached run recomputes only the functions whose profile
  changed) and, before a commit that touches these tables, `make check-fresh` and
  `make link-fresh` as CLAUDE.md requires.

## Regenerating

```
python3 tools/gen_unit_profiles.py --results <sweep results...> [--sweep more.jsonl] --write
```

The generator prints the consistency report (every unit whose members' evidence has an
empty intersection, with the members that keep an override), the row counts before and
after, and writes the three tables. The sweep result files are evidence, not
configuration; they live outside the repository, and the `source` column carries their
conclusions.

## First-generation measurements

`make check` and `tools/progress.py` carry the current numbers. The first generation of the
table measured `config/SLUS-20836/units.tsv` at **4,987 units**
(154 library/Sony pieces, 2,143 class runs, 2,690 unlabeled runs), of which **554 are
provisional**. 1,678 units compile with exceptions on and 3,309 off (957 of those are
undetermined: frameless leaves only). Profiles: 2,933 × default `-O3`, 877 × combat
`-O3,p`, 623 × combat `-O3`, **400 × 3.0.3 `-O3`** (328 `ig*` engine classes, 71 `be*`
classes and one `lib*` run where the 3.0.3 build reproduces members the default and the
2003 builds split between them), 134 × Sony EE GCC `-O2 -G0` (`-Iinclude`/`-g` variants),
and a dozen others (`-O3,p` default, combat `-O4`/`-O4,p`, 2.4, b52 for Lua's
`luaV_execute`, `-bool off`). The per-function tables hold 673 flag rows and 605
compiler rows (all provisional); 699 functions keep an override.

The `foreign-profile` set has three sources: the pins
that disagree with their class run (combat `-O3`/`-O3,p` members in default or 3.0.3
units and vice versa), compiler-unit owners that match only with exceptions off while
their unit carries retail exception records, and C leaves inside Sony `sd`-prologue
pieces that MWCC reproduces and the Sony compiler does not.

## What each library was built with

`scripts/analysis/profile_sweep.py` compiles every matched MWCC function under each candidate profile
with the unit tables disabled. Functions that all candidates reproduce say nothing, so these figures
are over the ones where candidates disagree.

**The optimisation flags split by library.** Metrowerks' runtime, `main`, AdxMovie, Bec, Ndmw and
Viewer are `-O3,p`; every other Alchemy library is `-O3`. Of 8,700 functions in the `-O3` libraries, 5
reproduce only with `,p`; of 5,870 in the `-O3,p` libraries, 1 reproduces only without it.

**The compilers split by kind of function, not by library.**

| Kind | `-O3` libraries: 3.0 / 3.0.3 / b38 | `-O3,p` libraries: 3.0 / 3.0.3 / b38 |
| --- | --- | --- |
| `_GetVTable` | 0 / 69 / 100 | 0 / 58 / 100 |
| `_GetMetaObject` | 100 / 100 / 4 | 60 / 60 / 40 |
| `_InitFields` | 93 / 93 / 7 | 63 / 63 / 37 |
| methods | 63 / 70 / 91 | 18 / 19 / 82 |

`combat` is the 3.0b38 build; b50, b52 and 3.0b22-020926 behave like it, and every 3.0.1 build from b51
to b151 reproduces none of the three generated kinds. The table measures the source as written, not
the compilers: these files were spelled against the build that first matched them.

**`_GetMetaObject` has three retail shapes, and they follow the source.** All 550 in the `-O3` Alchemy
libraries test the validity bit with an `sltu`. Viewer's 24 are the same with one more `nop`. Bec, Ndmw
and AdxMovie's 483 are a bare call: the game's macro, not Alchemy's. So Viewer is Alchemy source built
with the game's flags, and AdxMovie was written alongside the game.

**The kinds split by spelling.** The `sltu` comes from comparing a `bool` with `false`:
`((g->_validity & 4) != 0) == false` matches under 3.0, 3.0.3, b38, b50 and b52 alike, where
`!(t = g->_validity & 4)` matches only under 3.0 and 3.0.3. `_GetVTable` is the same:
One `_GetVTable` accessor differs under 3.0.3 by two swapped registers as a `union`, and matches under
3.0.3 and b38 as a `struct`.

**Two EE GCC builds.** CRI, newlib and libgcc are 2.96-ee-001003-1 (`ee-gcc`); the Sony runtime
libraries are 2.9-ee-991111-01 (`ee-gcc-2.9`; libmpeg with the 2.96 kit's assembler, `ee-gcc-2.9-as210`),
whose frameless sibling calls 2.96 cannot produce
([the `sd` prologue](sd-prologue.md)).

**3.0b52 with `-sdatathreshold 2` builds most of the game.** Alchemy is `-O4,s`, and the Metrowerks
runtime, `main`, AdxMovie, Viewer, Ndmw and Bec are `-O4,p`; the runtime is the exception to the threshold and
builds at `-sdatathreshold 0` ([Metrowerks runtime](runtime-metrowerks.md)). Bec, Ndmw and every unit of an
`alchemy-*` region (`p2` and Viewer included) also take `-inline level=8,bottomup`. In Bec and Ndmw
holder destructors inside inlined helpers are expanded in retail, which needs an inline depth of at
least 2, and every Bec and Ndmw function that matched without it still matches at depth 8 (depth 2
breaks four `GetVTable` functions). The `inline_depth` pragmas written before were standing in for
it, and 13 of them went. `bottomup` explains the largest functions: in bottom-up mode MWCC stops expanding
the calls inside an inlined body once the caller's size passes `inline_max_total_size` (10000 by default,
counted in expression nodes after inlining, so an inline accessor counts more than the field it reads). Such
a function gets the depth-1 shape everywhere: each holder destructor is expanded at the site and the release
it calls stays out of line, while the small out-of-line copies of the same destructors expand it. Top-down
inlining has no such limit. In bottom-up mode an inline helper whose own inline callees would take it past
`inline_max_size` (256 by default) is expanded with those callees left as calls, all of them (the next
paragraph). The runtime, `main` and AdxMovie match the same with or without `level=8`, so their setting is
undetermined. 4,810 of the 4,840 MWCC units are on
b52, 13 of them at `-O3` or `-O3,p` because their members pass only there. Viewer starts at `0x4583f0`, not at
its registrar: four out-of-line holder destructors come first, called only from Viewer and matching
only Viewer's `-O4,p`. At the other library boundaries such copies also sit just before the next
registrar, but both sides there share a profile, so those boundaries are not moved. A unit moved only when every member matched under it, so the rest keep their earlier profile;
`profile_split.units` in the debt ratchet counts them.
zlib and libpng are the exception that is settled: they build with `combat` and fail under `b52`.

**Alchemy builds bottom-up.** Retail keeps out-of-line copies of Alchemy's smallest inline members, and only
bottom-up inlining leaves calls to them.

- **The copies.** `igVec3f::igVec3f()` (`0x19ace0`, `jr ra; move v0,a0`), `igVec3f::set` (`0x1ae1a0`) and
  `igVec4f::set` (`0x1ae1b0`) are in SceneGraph, and `igVec4f::igVec4f()` (`0x151090`) is in Gfx. Each is the one
  copy the linker kept, from the first unit that emitted it. Game code expands the same constructors (an
  `igVec3f` local costs nothing in Bec and Ndmw), so they are inline, and a unit emits a copy of an inline
  function only where it left a call to it.
- **The constructor that reaches the size limit.** `__sinit_igViewerGuiFactory.cpp` (`0x521790`, Viewer)
  constructs one global. Its inline constructor has 110 inline callees: 41 member constructors (28
  `ViewerRect`, 3 `igVec3f`, 10 `igVec4f`) and 69 setters (56 `igVec2f::set`, 3 `igVec3f::set`, 10
  `igVec4f::set`). Retail expands the constructor into the initialiser and calls every one of the 110, in 2732
  bytes. With all of them inline in the source:

  | `-inline` | initialiser | rest of the unit |
  | --- | --- | --- |
  | none, or `level=8` (top-down) | 1836 bytes, no calls | matches |
  | `level=1` | 2732 bytes, the 110 calls | `igViewerGuiFactory_CreateAction` 164 bytes for 272: its holder helpers stay calls |
  | `bottomup`, or `level=8,bottomup` | 2732 bytes, the 110 calls | matches |

  The limit is `inline_max_size`: a test constructor with four two-vector members and one `igVec3f` goes from
  fully expanded to all calls at 10 setters, at 21 under `#pragma inline_max_size(512)` and at 4 under
  `inline_max_size(128)`. A local object in an ordinary function behaves the same, so the static initialiser is
  not special, and top-down inlining never leaves the calls. `-inline level=1` breaks 5 of the 20 Viewer owners
  and 16 of the 76 Alchemy owners.
- **The same shape inside Alchemy.** The copies' other callers are class constructors expanded into a function
  with their member constructors left as calls (`igProjectiveShadowShader_GetVTable`,
  `igPlanarShadowShader_GetVTable`, `igPsx2VisualContext_GetVTable`) and a reset helper in
  `igAnimationCombiner_RemoveAllStates` whose three setters are calls. Those sources still call them as free
  functions, so the flag is not tested on them.
- **Every owner matches with the flag.** All owners with a source in the `alchemy-*` rows verify under it. One
  function needed its source respelled: `0x164f50` in Gfx assigned its pool slots through a helper that called
  inline retain and release helpers, which is over the limit; with the counted assignment written in place in
  the helper it matches with and without the flag.
- **A duplicate is compared under its retail unit's profile.** `igViewerGuiFactory.cpp` emits the four copies
  above and names them `duplicates`; the verifier compiles the file again under the SceneGraph and Gfx profile,
  which has to be bottom-up for the copies to exist there.

The static-initialiser placeholder rows and `enbaya` keep `-O4,s -sdatathreshold 2 -RTTI off`: an initialiser
follows its owner when it moves, and `enbaya` matches with and without the flag, so nothing decides it.

**A library is one build, so a unit never crosses a library boundary.** Retail records two of the builds.
Alchemy carries one stamp, `Intrinsic Alchemy v3.2 -0810 (Static/Release)`, dated 10 August 2004. CRI's
module strings fall into two batches on 6 October 2004, Sofdec from 11:36:10 to 11:36:36 and ADX from
11:47:17 to 11:47:45, each with `Append: GCC2096 SCE2810`. `SNDF Ver.2.09c`, built on 4 October, is Sofdec's first
module. The second data section keeps the Sony and newlib strings in code order, which is how
`config/SLUS-20836/regions.tsv` divides that block, and the descriptors say `2800` except libmc's `2810`.
A static initialiser follows the library that owns it: one calling AdxMovie needs `,p`, unlike Alchemy's own.

**newlib and libgcc build with `-g`.** Its signs are a `nop` after each `jal`, saves kept apart from the body, and code larger than the same source without `-g`.

**The size or speed mode follows the library, without exception.** Compiled both ways at `-O4`, every function
that passes in only one mode agrees with its library: all of Alchemy, `p2` and `enbaya` need `,s`, and the
Metrowerks runtime, `main`, AdxMovie, Bec, Ndmw and Viewer need `,p`. Only the static initialisers mix,
since each follows its owner. An emitted group cannot be tested this way when a shared copy's retail home
is in a library of the other mode: forcing one mode everywhere breaks that copy.

**Alchemy, `p2` and `enbaya` build with `-RTTI off`.** Every vtable those libraries emit has a zero first
word, where MWCC with RTTI writes a pointer to the class's type record. All 478 vtables that carry one
are emitted by the game's `-O4,p` libraries (Bec, Ndmw, AdxMovie); the type records of Alchemy classes
such as `Gap::Core::igObject` exist only as the bases those game classes list, and nothing calls a
`dynamic_cast` or `typeid` runtime. The flag only
drops the type records and their name strings: every unit of the profile, whole-file and per-function,
verifies the same with and without it. With it, a whole-file unit compiles its classes' vtables
instead of keeping them as retail data, and each `.vtables` section is a `data` row of
`config/SLUS-20836/unit-objects.json`. The game's libraries keep RTTI, so a vtable they compile brings
its type records, base lists and class-name strings as `data` rows too.

**The data threshold comes from the stock libraries and the small-data block.** zlib, libpng and Lua are
the only code with its original declarations, and they verify at thresholds 1 and 2 and fail at 4 and
above. Retail's small data, `0x554880`-`0x554e80`, holds one-byte objects and one `short` in `.sbss`
(`0x554b04`), which a threshold of 1 cannot place. The game's own sources cannot separate thresholds: all 11,871
matched functions pass at 1, 2, 4, 8 and with no flag, because their `[4]` declarations hide the size.

**Every 4- and 8-byte gp-relative object is a compiler literal.** `0x554880`-`0x554970` holds floats and
doubles such as π, 2π, `FLT_MAX`, `0.01` and `1e20`. Written as a literal, b52 emits the same
`lwc1 $f0, 0(gp)` through `R_MIPS_LITERAL` into `.lit4`, which is how retail reaches them. An
`extern float` naming one of these addresses compiles to `lui`/`lwc1` instead and does not match, so
the source writes the value ([literals](compiler-object-verification.md#compiler-literals)).

These respellings carry a unit across:

* A parameter may be reassigned: a function can take a second argument only to overwrite it, which is why its pointer sits in `a1`.
* A float constant is a literal, not `extern float`, and a chain such as `a = b = c = 1.0f` keeps its order.
* `_GetMetaObject`, and every accessor of the same shape, compares the validity test with `false`, as
  above. The `asm { nop }` the older spelling needed goes away.
* `_InitFields` declares the meta pointer last, which puts it in `s0`.
* A library's registered flag is a scalar byte: the threshold keeps one-byte data gp-relative, so a
  `[4]` declaration no longer reaches it.
* A `.c` body in an exceptions-on unit becomes `.cpp`, since only the C++ front end emits the index
  record ([GetVTable](getvtable-fold.md)).
* Local declarations are reordered where only register allocation differs.

A unit holding the retail copy of a `duplicates` entry in `unit-objects.json` stays on its profile:
`tools/check.py` compares every emitted copy under that unit's profile, so moving it changes what
other units must match.

**Status objects are returned by value.** The functions that yield the success result (`g_resultSuccess`) return a one-word
class through a hidden pointer, which is why retail passes a stack slot as the first argument and
reads it back through its address. Such a function matches only when written that
way, with `operator!=` as a member. 132 source files use that constant and may hide the same shape.

The two status objects, `g_resultSuccess` (`0x4fb410`) and `g_resultFailure` (`0x4fb418`), are `const` objects of
the result class, `igResult` in `src/engine/core/CoreLibrary.h`: one `int` with a copy constructor and `operator==`/
`operator!=` taking `const igResult &`, the one class every Core function returning a status uses. The Core
library's static initialiser constructs them, and the object system's first set-up writes them again. Writing a
`const` object takes a `const_cast`, the one cast on them in the library's source.
MWCC refuses a plain assignment and a non-`const` redeclaration; a `mutable` member compiles, but the code that
reads the constants then loads them once where retail loads twice; a placement `new` adds null tests retail
lacks. Retail keeps them in `.rodata`: MWCC gives each `const` object it constructs at start-up a `.rodata`
section of its own, in definition order. They lie between
the strings of `igResource` (`"igSceneWrapper"`, `0x4fb400`) and of `igShortMetaField` (`"%hd%n"`, `0x4fb420`),
success first, so the original defined them in that order at that point of the library's one translation unit,
most likely in a source named for the result class. The tree defines them in that order with the library's other
globals at the end of the unit; the initialiser is the same for either order of the two.

The Core unit also defines the 46 memory-pool objects, `kIGMemoryPoolHandle<Name>` (`0x587018`..`0x587180`) of
type `igMemoryPoolHandle`; their names are in `g_memoryContextNames`.

Code that tests a call's result against the failure constant and then returns or stores the constant reads it
twice, the first read ahead of the comparison. That is how MWCC compiles the plain statement
`if (call() == g_resultFailure) return g_resultFailure;`, for a `const` object and a writable one alike
([understanding shapes](understanding-shapes.md#loads-shared-or-kept-apart-b52)). It needs the constant read as
the result class itself: a view of it through a cast to another class shares the two reads.

## Open questions

* **The remaining units.** Some units sit off their library's profile (`profile_split.units`): MWCC
  units on 3.0, 3.0.3 or combat, b52 units at the wrong optimisation level, and Sony units still on
  2.96 because a member is spelled for it or for an MWCC stand-in. Each holds a member that still differs
  under its library's profile. A unit holding the retail copy of a shared inline
  destructor also needs every other unit's copy of it to match under the new profile: the copy at
  `0x130140` is in the Attrs library unit, and the movie renderer's exception table refers to it, so
  the movie unit's own copy was most likely discarded at link time in favour of the Attrs one;
  `tools/check.py` compares that copy under the Attrs profile.
  `tools/roll_profile.py` lists the members. Respelling for b52 moved the rest: most members differed
  only in register order, because b52 gives the first-declared local the higher register.
* **Why an `asm { nop }` stood in.** An empty true arm before `else { x = 0; }` was an inlined cast: `static inline void *cast(void *o) { if (o != 0 && igObject_IsKindOf(o, meta) != 0) { return o; } return 0; }`, with the meta read inside it.
* **`-O3` or `-O4`.** Neither level fits every function. Some functions pass only at `-O4` and others
  only at `-O3`, in spite of
  the same search at the other level. Descending load orders in some of them suggest struct copies or
  inlined vector methods, which that search cannot write. b50 and b52 are not separated.
* **Why Viewer takes `,p`.** Its build settings are the game's, not Alchemy's, though nothing in the image
  says why.
* **Alias names in one-function files.** 38 one-function files under `src/engine/` still spell the status
  objects and pool handles by their alias names (`g_statusSucceeded`, `g_allocatorFailureStatus`,
  `g_defaultAllocatorSelector`, `g_ndmwAllocatorSelector`, `DAT_005870xx`, ...), resolved through rows in
  `config/SLUS-20836/data-names.tsv`. Moving them to `g_resultSuccess`/`g_resultFailure`/`kIGMemoryPoolHandle*`
  needs `tools/verify.py`'s `defined_outside` check to exempt the defining unit's own data rows; until then the
  alias rows stay.
