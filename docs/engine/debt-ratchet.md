# The debt ratchet — every debt counter may only go down

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
| `unmatched.functions` / `.bytes` | `config/SLUS-20836/symbols.txt` minus the definitions in `src/` | functions still linked from `asm/` |
| `struct.a`, `struct.b`, `struct.c` | `scripts/check_struct_conflicts.py` (imported, not re-implemented) | report groups: (a) the same view name with clashing layouts across units, (b) a receiver view disagreeing with the reflected class, (c) an offset-named member (`fNN`) whose number is not its offset |
| `m2c_idiom.units` | the matched units' source, comments and strings blanked, asm bodies excluded | files still carrying m2c spellings: `temp_*`, `var_*`, or an `argN` identifier |
| `raw_casts.reflected` | `tools/typed_coverage.py` (`typeable`) | raw `*(T *)((char *)this + N)` casts on the function's own receiver at an offset where reflection names the field — the mechanically convertible casts |
| `fun_dat_refs` | the matched units' source, comments and strings blanked, asm bodies excluded | occurrences of `FUN_<va>` / `DAT_<va>` identifiers (prototypes and calls), minus every occurrence of the name of each `FUN_` function the file defines (its definition and, in a C++ unit, its `extern "C"` prototype) |
| `foreign_profile.functions`, `foreign_profile.bytes` | `data/check-categories.tsv` | functions whose code bytes match only under a provisional per-function override (compiler, flags or exception mode) that differs from their translation unit's profile in `config/SLUS-20836/units.tsv`; never counted as `match` (see [build profiles](build-profiles.md)) |
| `orphan.bytes` | `data/check-categories.tsv` | exception-metadata orphan bytes: the `extra` + `differ` code-only bytes |

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
