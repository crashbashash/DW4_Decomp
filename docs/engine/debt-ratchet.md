# The debt ratchet — debt counters may only go down

`make check` proves bytes; it does not stop the tree from accumulating *debt*: units whose
code bytes match while something else is unproven, functions with no C at all, m2c
idioms left in matched source, local struct views that disagree with each other, and the
`FUN_`/`DAT_` names that still stand where a real name belongs. The ratchet turns each of
these into a number that is **read from committed files alone** (no game, no compiler), and
refuses to let any of them rise above the recorded floor.

```sh
python3 tools/progress.py --debt-check                  # exit 1 naming each counter that rose (old → new)
python3 tools/progress.py --debt-baseline               # re-record config/debt-baseline.json; refuses an increase
python3 tools/progress.py --debt-baseline --allow-increase "<reason>"   # record the increase, reason kept next to it
```

`--debt-check` prints at most a few lines and ends with `debt: OK` or `debt: N counter(s)
rose`; the oracle runner runs it next to the byte oracle. `PROGRESS.md` §Debt shows the
baseline against the current value of every counter, and `docs/progress.json` carries the
same numbers under `debt`.

## The counters

All of them come out of `tools/progress.py` (`DEBT_COUNTERS`, `debt_summary`). A counter
whose source is missing is reported as *unavailable* and fails the check — it is never read
as zero.

| counter | source | what it measures |
| --- | --- | --- |
| `code_only.functions` / `.bytes` | `data/check-categories.tsv` (written by a complete `make check`) | decompiled units whose code bytes match retail but whose exception metadata is not reproduced (compile mode or cleanup scope) |
| `code_only.missing.*` | the unit's diagnostic line | retail keeps an exception record the unit does not produce |
| `code_only.extra.*` | the unit's diagnostic line | the unit emits exception metadata retail lacks (compiled with exceptions off, or as C) |
| `code_only.differ.*` | the unit's diagnostic line | both sides have exception metadata and it differs |
| `code_only.other.*` | the unit's diagnostic line | the first diagnostic line does not name the exception reason (a deferred duplicate, or a table/index line comes first) |
| `name_defect.*` | `data/check-categories.tsv` | code bytes match; a symbol name is wrong for its address |
| `inventory_gap.*` | `data/check-categories.tsv` | code bytes match; a reference lands in a symbol-map gap or inside another function's extent |
| `mismatch.*`, `compile.*` | `data/check-categories.tsv` | units whose bytes differ, or that do not compile (both 0 on a tree that passed `make check`) |
| `asm_body.functions` / `.bytes` | content of `src/` (an `asm` definition under `#pragma optimization_level 0`) | functions kept as an `asm` body — retail instructions kept as source, not recovered C, and in no matched figure |
| `inline_asm.other` | `tools/inline_asm.py`, over `src/` and `include/dw4/` | `asm` statements inside C without an approval. `sync` and `ei` are not counted: C cannot spell them and the owner has approved them all. A statement passes the byte check whether or not C could produce the same bytes, so `tools/inline_asm.py --test <source>` has to show its function fails without it. A statement stops counting once every function it reaches has a current row in `config/source-approvals.tsv`, an oracle file only the owner approves; a statement reaching one function without a row still counts |
| `unmatched.functions` / `.bytes` | `config/SLUS-20836/symbols.txt` minus the definitions in `src/` | functions still linked from `asm/` |
| `struct.a`, `struct.b`, `struct.c` | `scripts/check_struct_conflicts.py` (imported, not re-implemented) | report groups: (a) the same view name with clashing layouts across units, (b) a receiver view disagreeing with the reflected class, (c) an offset-named member (`fNN`) whose number is not its offset |
| `m2c_idiom.units` | the matched units' source, comments and strings blanked, asm bodies excluded | files still carrying m2c spellings: `temp_*`, `var_*`, or an `argN` identifier |
| `raw_casts.reflected` | `tools/typed_coverage.py` (`typeable`) | raw `*(T *)((char *)this + N)` casts on the function's own receiver at an offset where reflection names the field — the mechanically convertible casts |
| `fun_dat_refs` | the matched units' source, comments and strings blanked, asm bodies excluded | occurrences of `FUN_<va>` / `DAT_<va>` identifiers (prototypes and calls), minus every occurrence of the name of each `FUN_` function the file defines (its definition and, in a C++ unit, its `extern "C"` prototype) |
| `foreign_profile.functions`, `foreign_profile.bytes` | `data/check-categories.tsv` | functions whose code bytes match only under a provisional per-function override (compiler, flags or exception mode) that differs from their translation unit's profile in `config/SLUS-20836/units.tsv`; never counted as `match` (see [build profiles](build-profiles.md)) |
| `orphan.bytes` | `data/check-categories.tsv` | exception-metadata orphan bytes: the `extra` + `differ` code-only bytes |
| `profile_split.units` / `.bytes` | `config/SLUS-20836/units.tsv` by `config/SLUS-20836/regions.tsv` | units whose compiler, optimisation level, `-sdatathreshold` or `-inline` setting differs from the most common profile of their library. A library was one build, so each such unit is one whose members still match only elsewhere. The static initialisers are exempt: they are collected from every library |
| `opt_pragma.statements` | `src/` | optimiser pragmas (`opt_*`, `optimize_for_size`, `inline_depth` and the like). They change the optimiser for one function, which is a flag change written in the source; owner rule 2026-11-08: a rise needs the owner, as for `inline_asm` |

`m2c_idiom.units`, `raw_casts.reflected` and `fun_dat_refs` measure readability, which is a separate
job from matching ([matched and readable](../../CLAUDE.md#matched-and-readable)). They stay in the report
and may rise without a recorded reason, so a byte-matching change is never refused for them.

## Re-recording the baseline

Debt goes down when a wave recovers functions as C, settles exception metadata, names
functions or merges struct views. After such a commit, run `--debt-baseline`: it prints
every counter as `old -> new` and writes `config/debt-baseline.json`; commit the file with
the change so the lowered floor is reviewed with the work that earned it.

A counter can legitimately rise — a newly matched unit may be `code-only` until its
exception metadata is reproduced, a rename
may expose a struct clash the report had not seen. The ratchet does not forbid that; it
forbids it *happening silently*. `--debt-baseline` refuses to record a higher value unless
`--allow-increase "<reason>"` is given, and then the reason is stored next to the value
(`{"value": N, "reason": "..."}`) and shown in `PROGRESS.md`'s Debt table, so the increase
is a reviewed decision with its justification in the diff, not a drift.

Why read-only inputs: the gate has to run in a hook and in CI, neither of which has the
compiler or the game. Everything the counters need is committed — the categories table
from the last complete `make check`, the symbol map, the source tree, the reflection
headers — so a stale `data/check-categories.tsv` (its row count differs from the number of
decompiled units) makes the category counters *unavailable* rather than wrong, and the
check says so.
