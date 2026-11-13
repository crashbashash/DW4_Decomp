# `tools/`: the matching build and its helpers

Run everything from the repository root. The Makefile calls the build tools; the rest are used while recovering functions. Analysis, capture and evidence scripts live in [`scripts/`](../scripts/README.md), and regression tests of these tools sit beside them as `test_*.py`.

## Build and verification

| Tool | Purpose |
| --- | --- |
| [`check.py`](check.py) | coverage and correctness for the matching-decompilation build |
| [`verify.py`](verify.py) | verify a candidate C function against the retail binary, WITH relocations |
| [`linkgen.py`](linkgen.py) | build the relink inputs from config/SLUS-20836/layout.txt |
| [`linkcheck.py`](linkcheck.py) | compare a relinked section against the retail binary |
| [`make_iso.py`](make_iso.py) | `make iso`: write the built executable into a copy of your disc image, in `build/` |
| [`layout.py`](layout.py) | turn the symbol map into a DISJOINT, ordered tiling of the section |
| [`whole_file_rows.py`](whole_file_rows.py) | measure a stock library's whole-file rows from retail: members, duplicates (profile twins included), stripped functions, data and externals |
| [`split.py`](split.py) | lay out the retail code and emit one assembly unit per function |
| [`buildcache.py`](buildcache.py) | a content-addressed result cache for tools/check.py and tools/linkgen.py |
| [`units.py`](units.py) | resolve a symbol to its definition in a multi-function source file |
| [`srctext.py`](srctext.py) | read a source as the compiler sees it, with a unity-built unit's `#include "src/..."` fragments expanded |
| [`asmsources.py`](asmsources.py) | the owner-approved hand-written `.S` sources in `src/` (`config/assembly-sources.tsv`); refuses any other |
| [`srctree.py`](srctree.py) | resolve a filename to its path when `src/` is not flat |
| [`jumptables.py`](jumptables.py) | find the switches' jump tables and record them in a config file |
| [`syscalls.py`](syscalls.py) | recover the EE kernel syscall stubs → `config/SLUS-20836/syscalls.txt` |
| [`unitflags.py`](unitflags.py) | per-unit compiler-flag overrides (config/SLUS-20836/unit-flags.tsv) |
| [`unitcompilers.py`](unitcompilers.py) | Content-pinned compiler selection for proven matching units |
| [`cc.py`](cc.py) | the one place a compile command is built: MWCC under wibo, or the Sony EE GCC for a unit pinned to it; verify, check and linkgen all go through it |
| [`project.py`](project.py) | per-version build helpers behind the Makefile: the executable check and disc extraction, the image hash check, and `objdiff.json` with the rules for the objdiff objects |
| [`inline_asm.py`](inline_asm.py) | counts the `asm` statements inside C for the debt ratchet, leaving out those the owner approved, and `--test` shows which ones a function verifies without |
| [`target_asm.py`](target_asm.py) | objdiff target assembly: the retail words of a function with their relocations restored (`.reloc` + masked `.word`) |
| [`eegcc_compile.py`](eegcc_compile.py) | compile one C file with the Sony EE GCC 2.96 (`-S` then the sibling `ee-as`, with the symbol table repaired for GNU ld); used for the Sony-built library units |
| [`unitobjects.py`](unitobjects.py) | Explicit ownership of additional functions emitted by a compiler unit |
| [`regions.py`](regions.py) | read config/SLUS-20836/regions.tsv, the record of what each part of the image is |
| [`check_regions.py`](check_regions.py) | test that table against the retail image |
| [`unitprofiles.py`](unitprofiles.py) | resolve a function's translation-unit build profile (config/SLUS-20836/units.tsv) and tell a provisional per-function override from it |
| [`roll_profile.py`](roll_profile.py) | move whole units onto a profile when every member still verifies there |
| [`gen_unit_profiles.py`](gen_unit_profiles.py) | draft units.tsv from the pins, the sweeps and the retail exception evidence; rewrites the per-function tables so only dissenting members keep a row |
| [`progress.py`](progress.py) | the repo's progress numbers, computed from committed files only |
| [`datamap.py`](datamap.py) | how much of the binary's *data* the repo has identified |
| [`typed_coverage.py`](typed_coverage.py) | Measure typed coverage: how much of the decompiled C speaks in structs |
| [`typed_scope.py`](typed_scope.py) | Typed coverage of the game layer |

## Naming and tree maintenance

| Tool | Purpose |
| --- | --- |
| [`apply_names.py`](apply_names.py) | apply `config/SLUS-20836/names/` to the tree as one verified batch |
| [`apply_data_names.py`](apply_data_names.py) | apply `config/SLUS-20836/data-names.tsv` to the matched C sources |
| [`place_named.py`](place_named.py) | move named units out of `src/` root into their module folder |
| [`merge_units.py`](merge_units.py) | fold per-function unit files into one translation unit |

## Drafting and matching (m2c, permuter, near-miss repair)

| Tool | Purpose |
| --- | --- |
| [`m2c_batch.py`](m2c_batch.py) | bulk m2c → verify → bank, over the not-yet-matched functions |
| [`m2c_one.py`](m2c_one.py) | feed one retail function through m2c (mipsee-mwcc-c) |
| [`m2c_loop.py`](m2c_loop.py) | the per-function iteration harness for the m2c phase (M7) |
| [`m2c_run.py`](m2c_run.py) | Run the vendored `m2c` with the pipeline's compatibility guard applied |
| [`m2c_context.py`](m2c_context.py) | build an m2c `--context` file from the recovered metadata |
| [`m2c_compat.py`](m2c_compat.py) | Guard the vendored `m2c` against recovery errors this pipeline can trigger |
| [`m2c_errors.py`](m2c_errors.py) | bucket the worklist's compile failures by MWCC's own error message |
| [`m2c_typed_fields.py`](m2c_typed_fields.py) | m2c_typed_fields.py DRAFT.c [--only VAR,...] - retype raw offset accesses of an m2c draft as struct fields |
| [`automatch.py`](automatch.py) | bulk-decompile the idiomatic shapes, and let verification decide |
| [`autofix.py`](autofix.py) | iteratively repair m2c drafts MWCC rejects, using the compiler's |
| [`args_search.py`](args_search.py) | restore the call arguments m2c drops, over the near-miss tier |
| [`flag_sweep.py`](flag_sweep.py) | retry every near-miss draft under other MWCC optimisation flags |
| [`perm_fixed.py`](perm_fixed.py) | permute the drafts that only became compilable after the compile-repair pass (`autofix.py`) |
| [`permuter_one.py`](permuter_one.py) | turn one function into a decomp-permuter project and run it |
| [`perm_refine.py`](perm_refine.py) | search a permuter project in rounds that build on each other, merge the small changes of near-best outputs, and refuse candidates that lose the target's calls or stores |
| [`cxx_sweep.py`](cxx_sweep.py) | search honest respellings of one C or C++ function (declaration order, scopes, statement order, loop tests, temporaries, loop forms, inline helpers), scored by the oracle standalone or inside a whole-file unit; refuses dead code, new `&x`, `volatile`, `asm` and byte-forcing casts |
| [`restore_dropped_args.py`](restore_dropped_args.py) | recover m2c's dropped/gap call parameters (M7 near-miss tier) |
| [`retype_struct_member.py`](retype_struct_member.py) | bank the near-miss tier's mechanical source shapes |
| [`scan_near.py`](scan_near.py) | compile every unmatched build/m2c draft, record its instruction diff |
| [`queue_diag.py`](queue_diag.py) | cluster the unmatched queue by *why* each function misses |
| [`asm_body_gen.py`](asm_body_gen.py) | emit a function as an MWCC `asm` body from the retail bytes, for local study (asm bodies are not committed) |
| [`guard_b_gen.py`](guard_b_gen.py) | emit the 76-byte 'guard variant B' accessor as C++ |
| [`register_gen.py`](register_gen.py) | emit the `<Class>_Register` registrars from the retail assembly |
| [`initfields_gen.py`](initfields_gen.py) | retarget a verified `<Class>_InitFields` translation unit to another class (declaration order follows the unit's compiler) |
| [`getvtable_members_gen.py`](getvtable_members_gen.py) | two-member (object-ref / string-chunk) stack-object *_GetVTable accessors as C++ (verify with the alternate compiler, -O3,p mostly) |
| [`getvtable_ptr_gen.py`](getvtable_ptr_gen.py) | getvtable_ptr_gen.py [--out DIR] [--search] NAME... - stack-object `*_GetVTable` accessors with pointer locals |
| [`getvtable_stack_gen.py`](getvtable_stack_gen.py) | emit the stack-object `*_GetVTable` accessors as C |
| [`getvtable_union_conv.py`](getvtable_union_conv.py) | getvtable_union_conv.py DRAFT NAME SIZE |

## Targets and platform images

| Tool | Purpose |
| --- | --- |
| [`platform_map.py`](platform_map.py) | Map the platform boundary of the image: which functions touch EE hardware |
| [`mips_literals.py`](mips_literals.py) | Resolve the addresses MIPS code forms, from the `lui` that starts them |
| [`sdk_bindings.py`](sdk_bindings.py) | Decode the SDK's library descriptors in game.elf's rodata |

## Tests

`test_regions.py`, `test_debt_readability.py`, `test_function_extents.py`, `test_multiple_jump_tables.py`, `test_permuter_paths.py`, `test_perm_refine.py`, `test_build_options.py`, `test_definitions.py`, `test_asm_body_counting.py`, `test_asmsources.py`, `test_target_asm.py`, `test_whole_file_units.py`, `test_srctext.py`, `test_verify_cache.py`, `test_elf_tables.py`, `test_cxx_sweep.py`, `test_unitcompilers.py`, `test_unitobject_metadata.py`, `test_unitobjects.py`, `test_verify_relocations.py`

## Subfolders

- `permuter/`: per-function decomp-permuter projects written by `permuter_one.py`.
- `mwcc_irdump/`: the b52 compiler's optimizer IR dump (`make_dump_compiler.py` writes a copy with the dump switched
  on, outside the repository; `dump.py` compiles a file with it; `ph.py` reads the log) and gdb scripts that read IR
  node flags and the comparisons common-subexpression elimination rejects
  ([method](../docs/engine/understanding-shapes.md#mwccs-optimizer-ir-dump)).
