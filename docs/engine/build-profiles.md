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
  exceptions are on, so a unit with any recorded function (`config/SLUS-20836/exceptions.txt`) is
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
| reproduces the code | none | the ordinary category (`match`, `code-only`, …) | — |
| reproduces the code | row exists | the ordinary category; the row is stale | `override=unused` / `override=redundant` |
| fails | reproduces the code | **`foreign-profile`** | `override=foreign` |
| fails | fails | `mismatch`, naming both profiles | — |

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
  the exception mode agrees — a `.cpp` with exceptions on in an exceptions-off unit
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
table measured `config/SLUS-20836/units.tsv` at **4,987 units** —
154 library/Sony pieces, 2,143 class runs, 2,690 unlabeled runs — of which **554 are
provisional**. 1,678 units compile with exceptions on and 3,309 off (957 of those are
undetermined: frameless leaves only). Profiles: 2,933 × default `-O3`, 877 × combat
`-O3,p`, 623 × combat `-O3`, **400 × 3.0.3 `-O3`** (328 `ig*` engine classes, 71 `be*`
classes and one `lib*` run where the 3.0.3 build reproduces members the default and the
2003 builds split between them), 134 × Sony EE GCC `-O2 -G0` (`-Iinclude`/`-g` variants),
and a dozen others (`-O3,p` default, combat `-O4`/`-O4,p`, 2.4, b52 for Lua's
`luaV_execute`, `-bool off`). The per-function tables hold 673 flag rows and 605
compiler rows (all provisional); 699 functions keep an override.

`make check` on that tree: **15,342 match**, 2,356
code-only (2,307 `exc=missing` C units in exceptions-on units; no `exc=extra`
unit), 4 name-defect, 0 inventory-gap, **705
foreign-profile** (345,216 bytes), 0 mismatch. The foreign-profile set is: the pins
that disagree with their class run (combat `-O3`/`-O3,p` members in default or 3.0.3
units and vice versa), 89 compiler-unit owners that match only with exceptions off while
their unit carries retail exception records, and C leaves inside Sony `sd`-prologue
pieces that MWCC reproduces and the Sony compiler does not. The debt baseline's first
values are `foreign_profile.functions = 705` and `foreign_profile.bytes = 345,216`;
`orphan.bytes` is 23,524 (the 97 foreign-profile overrides
that still emit metadata retail lacks).
