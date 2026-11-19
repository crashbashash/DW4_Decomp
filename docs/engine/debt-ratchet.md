# The debt ratchet: debt counters may only go down

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
whose source is missing is reported as *unavailable* and fails the check; it is never read
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
| `asm_body.functions` / `.bytes` | content of `src/` (an `asm` definition under `#pragma optimization_level 0`) | functions kept as an `asm` body: retail instructions kept as source, not recovered C, and in no matched figure |
| `inline_asm.other` | `tools/inline_asm.py`, over `src/` and `include/dw4/` | `asm` statements inside C without an approval. `sync` and `ei` are not counted: C cannot spell them and the owner has approved them all. A statement passes the byte check whether or not C could produce the same bytes, so `tools/inline_asm.py --test <source>` has to show its function fails without it. A statement stops counting once every function it reaches has a current row in `config/source-approvals.tsv`, an oracle file only the owner approves; a statement reaching one function without a row still counts |
| `unmatched.functions` / `.bytes` | `config/SLUS-20836/symbols.txt` minus the definitions in `src/` | functions still linked from `asm/` |
| `struct.a`, `struct.b`, `struct.c` | `scripts/check_struct_conflicts.py` (imported, not re-implemented) | report groups: (a) the same view name with clashing layouts across units, (b) a receiver view disagreeing with the reflected class, (c) an offset-named member (`fNN`) whose number is not its offset; a member whose name a source gives (`config/sourced-member-names.tsv`, e.g. the CRI SDK's `d0`/`d1`) is not offset-named |
| `m2c_idiom.units` | the matched units' source, comments and strings blanked, asm bodies and stock `src/third_party/` excluded | files still carrying m2c spellings: `temp_*`, `var_*`, or an `argN` identifier |
| `raw_casts.reflected` | `tools/typed_coverage.py` (`typeable`) | raw `*(T *)((char *)this + N)` casts on the function's own receiver at an offset where reflection names the field (the mechanically convertible casts) |
| `fun_dat_refs` | the matched units' source, comments and strings blanked, asm bodies excluded | occurrences of `FUN_<va>` / `DAT_<va>` identifiers (prototypes and calls), minus every occurrence of the name of each `FUN_` function the file defines (its definition and, in a C++ unit, its `extern "C"` prototype) |
| `foreign_profile.functions`, `foreign_profile.bytes` | `data/check-categories.tsv` | functions whose code bytes match only under a provisional per-function override (compiler, flags or exception mode) that differs from their translation unit's profile in `config/SLUS-20836/units.tsv`; never counted as `match` (see [build profiles](build-profiles.md)) |
| `orphan.bytes` | `data/check-categories.tsv` | exception-metadata orphan bytes: the `extra` + `differ` code-only bytes |
| `profile_split.units` / `.bytes` | `config/SLUS-20836/units.tsv` by `config/SLUS-20836/regions.tsv` | units whose compiler, optimisation level, `-sdatathreshold` or `-inline` setting differs from the most common profile of their library. A library was one build, so each such unit is one whose members still match only elsewhere. The static initialisers are exempt: they are collected from every library; so is a unit of owner-approved assembly sources, which is assembled, not compiled |
| `opt_pragma.statements` | `src/` | `#pragma` lines that change the code or data b52 emits: the optimiser (`optimization_level`, `optimize_for_size`, `peephole`, `global_optimizer`, every `opt_*` switch b52 accepts), inlining (`auto_inline`, `dont_inline`, `always_inline`, `inline_depth`, `inline_bottom_up`, `defer_codegen`, `inline_intrinsics`), the MIPS back end (`schedule`, `conditional_move`, `tailcall`, `far_call`, `interrupt`, …) and data placement and types (`pool_strings`, `dont_reuse_strings`, `explicit_zero_data`, `reverse_bitfields`, `unsigned_char`, `enumsalwaysint`, …); the list is `OPT_PRAGMAS` in `tools/progress.py`, the effects are in [MWCC pragmas](mwcc-pragmas.md). Not counted: `push`, `pop`, `cplusplus`, the runtime's `exception_*`, names b52 ignores (`scheduling`, `opt_peephole`), and `readonly_strings` between `push` and `pop`, which the rule allows ([understanding shapes](understanding-shapes.md#types-and-values)); outside a closed `push`/`pop` it counts. They change the compiler for one function, which is a flag change written in the source; owner rule 2026-11-08: a rise needs the owner, as for `inline_asm` |
| `decl.local_externs` | `src/`, `include/` (`tools/declarations.py`) | declarations, in a unit's own text, of a symbol another unit defines ([declarations](#declarations)) |
| `decl.varargs` | `src/`, `include/` | prototypes that leave out the parameters a symbol has: `(...)` or a C `()` |
| `decl.type_conflicts` | `src/`, `include/` | declarations whose type differs from the symbol's C definition |
| `decl.header_conflicts` | `src/`, `include/` | symbols declared in two or more headers that disagree on the type |
| `decl.named_placeholders` | `src/`, `include/`, `config/SLUS-20836/symbols.txt`, `data-names.tsv` | `FUN_<va>`/`DAT_<va>` identifiers for an address that already has a recovered name |
| `free_methods.functions` / `.bytes` | `config/SLUS-20836/symbols.txt`, `src/`, `include/dw4/support/reflected.h` | functions of C++ units written as `<Class>_<Method>` free functions with C linkage, for a class reflection names, where the original most likely had member functions |
| `vfunc_slots.functions` | `config/SLUS-20836/symbols.txt`, `src/` | virtual methods known only by their slot (`Gap__<Lib>__<Class>__vfunc_N`) |

`m2c_idiom.units`, `raw_casts.reflected` and `fun_dat_refs` measure readability, which is a separate
job from matching ([matched and readable](../../CLAUDE.md#matched-and-readable)). They stay in the report
and may rise without a recorded reason, so a byte-matching change is never refused for them. So may the
free-method counters, which measure how far the C++ units are from the original's member functions: every C++
function matched under the current `<Class>_<Method>` convention adds to them until a member-function convention
is decided.

## Declarations

The convention: a symbol is declared once, in a header (`include/dw4/<library>/<Module>.h`, in the folder of the library whose unit defines the subject, or the module's own
header), with the type its definition has, and the file that defines it includes that header. A
library header that copies other libraries' symbols (`src/engine/core/CoreLibrary.h` and the other
`*Library.h`) is not their home. `tools/declarations.py` reads every declaration in `src/` and
`include/` (comments, strings, preprocessor lines and `#if 0` arms blanked; class and function bodies
skipped, `extern` inside a function body read) against the definitions in `src/`;
`python3 tools/declarations.py --list local|varargs|conflicts|headers [PATH]` lists what it counts.
Stock source under `src/third_party/` is its authors' text: its declarations are not counted, its
definitions are the reference for the code that calls into it.

- **`decl.local_externs`**: a declaration of a symbol *another unit defines*, in a unit's own text: its
  `.c`/`.cpp` file, the `.inc` fragments it includes, and any header no other unit includes (a library's
  unity header). A function prototype, file-scope `extern` data and `extern` inside a function body all
  count. A declaration of the unit's own symbol (a C++ unit's `extern "C"` line for its own function, a
  library header's own prototypes, a forward declaration) is linkage, not debt. Not counted either: an
  unnamed placeholder (`FUN_<va>`, `DAT_<va>`), and a symbol with no C definition that only one unit
  declares; until it is named or decompiled, the unit that uses it is its home. A symbol with no C
  definition that two or more units declare counts in each.
  A copy the owner approved (a `local-decl` row in `config/source-approvals.tsv`, anchored to its measured reason in
  [source approvals](source-approvals.md#kept-local-declarations)) is not counted while the tree holds exactly the row's count of
  copies of the symbol, and its `(...)`, `()` or differing type is no `decl.varargs` or `decl.type_conflicts` debt either; `--list local`
  still prints it, marked `[approved #anchor]`.
- **`decl.varargs`**: a prototype whose whole parameter list is `(...)`, unless a C definition of the
  symbol is itself variadic. A symbol with no C definition counts: `(...)` states no type, and no
  definition says the list is variable. A C `()` list (no parameters stated) counts when the C definition
  takes parameters. A list with named parameters before `...` is a real signature and is judged by
  `decl.type_conflicts`.
- **`decl.type_conflicts`**: a declaration whose type differs from the symbol's C definition: data type,
  array against scalar or array length, data declared for a function (`char X[]`) or the reverse, return
  type, parameter count and types. Both sides are normalised first: whitespace, parameter names,
  `struct`/`class`/`union`/`enum` keywords, integer spellings (`unsigned int` is `unsigned`), typedefs
  with one meaning across the tree, macros every definition of which only decorates (a calling convention,
  a memory model, an attribute or nothing: libpng's `PNGAPI`, zlib's `FAR`), array parameters as pointers,
  top-level `const` on parameters and return types. Functions are compared when both sides have C linkage
  (a C++ declaration with other parameters names another overload); data is always compared. A `(...)` or
  C `()` list compares the return type only. A symbol with no C definition, or whose C definitions disagree
  with each other, has nothing to compare against and is not counted here. A difference found that way is
  checked again as the compiler reads both sides, in each unit that defines the symbol (the declaration in
  those of them that include it, else in the units that do): the object-like macros defined before each
  line expanded (a newlib `RARG` parameter macro), and a typedef the tree gives two meanings (libgcc's
  `FLO_type`, double in one unit and float in another) read as that unit defines it. It counts only when
  the two still differ. A function-like macro, one that is `#undef`-ed, and one defined under a condition
  the tool cannot decide (anything but an include guard, `#if 0`/`#if 1` or `__cplusplus`) are not
  expanded. The C `()` check of `decl.varargs` reads the definition the same way.
- **`decl.header_conflicts`**: a symbol (data, or a function with C linkage) declared in two or more
  headers whose declarations disagree with each other. It needs no definition, so a symbol still in
  assembly counts.
- **`decl.named_placeholders`**: a `FUN_<va>` or `DAT_<va>` identifier in the code of `src/` or `include/`
  (comments and strings aside, macro bodies included) whose address the symbol map or `data-names.tsv`
  names. The build binds a call to it by address (the unit's `externals` in `unit-objects.json`), so it
  links and matches under either name, and `tools/apply_names.py` renames only the spelling of the old name,
  so such a copy outlives every rename of its symbol. Spell it by its name and include the name's home.
  `--list placeholders` prints each with the name it stands for.

The README's Readable column applies the same rules per function (the `declarations` check): a function
fails when a symbol its body uses (a call or a read, not a member after `.`, `->` or `::`) is declared,
in the text the compiler sees for its unit (the unit's files and every header they include), by a
counted local extern (an approved copy is not one), a counted `(...)`/`()` prototype, or with a conflicting type.

## Re-recording the baseline

Debt goes down when a wave recovers functions as C, settles exception metadata, names
functions or merges struct views. After such a commit, run `--debt-baseline`: it prints
every counter as `old -> new` and writes `config/debt-baseline.json`; commit the file with
the change so the lowered floor is reviewed with the work that earned it.

A counter can legitimately rise: a newly matched unit may be `code-only` until its
exception metadata is reproduced, a rename
may expose a struct clash the report had not seen. The ratchet does not forbid that; it
forbids it *happening silently*. `--debt-baseline` refuses to record a higher value unless
`--allow-increase "<reason>"` is given, and then the reason is stored next to the value
(`{"value": N, "reason": "..."}`) and shown in `PROGRESS.md`'s Debt table, so the increase
is a reviewed decision with its justification in the diff, not a drift.

Why read-only inputs: the gate has to run in a hook and in CI, neither of which has the
compiler or the game. Everything the counters need is committed (the categories table
from the last complete `make check`, the symbol map, the source tree, the reflection
headers), so a stale `data/check-categories.tsv` (its row count differs from the number of
decompiled units) makes the category counters *unavailable* rather than wrong, and the
check says so.
