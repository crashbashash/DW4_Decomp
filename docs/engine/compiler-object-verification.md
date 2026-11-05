# Compiler object ownership and exception settings

Findings [#903](../findings/findings-0751-1000.md#f903)–[#904](../findings/findings-0751-1000.md#f904). These are measured properties of MWCCPS2
3.0 build011126 and the matching pipeline. They do not change native-port
exception policy or mark a behavioral adapter as byte-matched source.

## Exact alias-pool tail calls ([#903](../findings/findings-0751-1000.md#f903))

Seven virtual wrappers have exact source in
[`alias-pool-tail.cpp`](../../src/engine/alias-pool-tail.cpp):

| Entry | Bytes | Operation |
| --- | ---: | --- |
| 2d09f0 |20| Element-size allocation through slot216 |
| 2d0ac0 |28| Default-alignment allocation through412 |
| 2d0ae0 |32| Explicit-alignment allocation through412 |
| 2d0be0 |20| Default-alignment reallocation through412 |
| 2d0c00 |16| Explicit reallocation argument forwarding through412 |
| 2d0d80 |24| Free sentinel/default-alignment forwarding through412 |
| 2d0e30 |20| Backing-pool allocation-size forwarding through336 |

All seven /160 bytes match at `-O3 -Cpp_exceptions off -Iinclude`. With the
same source and the compiler's default exceptions-on setting, the functions
retain a stack frame and `jalr`, while retail uses `jr t9`. The exception mode
is part of the unit's profile, which both check and link consume
([below](#the-unit-profile-comes-first)).
The compiler's own `-help all` output documents the exceptions-on default.

The C++ types are narrow ABI views, not recovered original class declarations.
No object is instantiated and no assembly encodings are inserted into C. The
default and explicit argument movements, halfword alignment, full -1 sentinel
and virtual tail transfer are verified instruction-for-instruction. Existing
286-case retail runtime comparisons still cover all54 bodies/4,160 bytes.

The alias runtime has44 exact bodies /1,508 bytes; ten bodies /
2,652 bytes retain assembly. The private740-byte backend candidate
differs at eight instruction words (six return-buffer offsets and two retry
branch/scheduling words). It remains outside `src/`. The exception setting alone
does not solve the larger bodies, and these seven matches do not establish an
exception configuration for every retail compilation unit.

## Function sections and relocation ownership ([#904](../findings/findings-0751-1000.md#f904))

Two properties of compiler objects, found on the reference-object candidates, shape the verifier:

1. MWCC can emit **several sections named `.text`**, one per ordinary or generated
   C++ helper body. Their symbols can all have value0 in different section indices.
   `objcopy -j .text -O binary` overlaps those sections at address0; it is not a
   way to select a particular function. Their `.rel.text` names and instruction
   offsets also repeat. Applying all relocations to the selected bytes corrupts
   the comparison with unrelated helper relocations.
2. GNU `readelf -sW` prints symbol **Value in hexadecimal and Size in decimal**.
   Decoding both as hex is a mistake a single-function object hides, because
   an oversized slice stops at the section's actual end.

`tools/verify.py` reads the selected symbol's indexed section bytes, decodes
the size as decimal, and selects relocation ownership using the relocation
section header's `sh_info`. Relocations are rebased within a selected symbol when
needed. ELF table order is retained, including backward HI16/LO16 pairs ([#895](../findings/findings-0751-1000.md#f895)).
Local text addresses resolve only within that selected section, unless a symbol
already has a canonical retail address.

The acceptance gate remains strict: **any additional emitted `.text` body rejects
the candidate**, even when the selected function's words match. The current
per-function linker requires an isolated body; no helper bytes may disappear
from matching or linking accounting. The diagnostic identifies extra code
instead of applying that code's relocations to the target. This is also why a
private class/inline model is not automatically bankable after its own method
looks close.

## Independent verification

```sh
python3 tools/test_verify_relocations.py
python3 testing/test_alias_pool_runtime_retail.py
python3 testing/test_lua_engine_dependencies.py
make check
make link
make typed-check
```

The four relocation tests cover decimal sizes, selected relocation offsets/order,
the backward HI/LO pair ([#895](../findings/findings-0751-1000.md#f895)), and a real MWCC object containing a preceding
unknown-call body plus the exact alias constructor. The latter has two
different sections both named `.text`, each with symbol offset0. The verifier
compares the constructor without importing the unknown helper relocation, but
still rejects the additional code. A separate GNU ld link concatenates and
aligns both input sections, places the constructor at its retail VA, and proves
its relocated bytes equal retail. The helper's link-only address is controlled
and its code is never executed.

The full check/link and recovered-access gate
validate the seven wrappers independently of the private compiler experiments.
Private logs and sources are repository-relative
`../scratch/lua-engine-recovery/alias-relocation-*`, `alias-verifier-*`,
`alias-tail-*`, `tail-noexcept-*` and `alias-core-member.*`.

## Oracle holes closed by the audit

An audit wrote four counterexamples against `igObjectSystem_FindMetaByNameDefault`
(0x2fe460, 16 bytes) that compile to the retail instruction words. Three of
them fail verification; the fourth is a documented limit. The
tests are `tools/test_oracle_holes.py` (the sources are embedded) and
`tools/test_exceptions.py`.

### Every allocated section needs a retail identity (standalone units)

The group path (`verify_emitted_object`) requires an object's allocated
sections to be exactly its bodies, its recorded jump tables and its declared
exception metadata. The standalone path holds a candidate to the same rule: `verify_one`
accounts for every allocated section: the function's `.text`, the jump
tables of `config/SLUS-20836/jumptables.txt`, and the `.exceptix`/`.exception` sections
retail keeps for the function (next section). Anything else fails with
`unowned allocated section .data (24 bytes)` naming each section, so a
candidate cannot carry initialised data, string literals, `.sdata` scalars or
`.bss` next to a matched body (counterexample 1b); reading only `.text` and
`.rodata` would let it.

### Symbol identity

A relocation symbol's name is a claim about retail, and `verify.sym_address`
is the one resolver that checks it; `tools/linkgen.py` resolves its
`PROVIDE` lines through the same function, not through a regex of its own.

* A **defined** symbol whose address-bearing name points outside the object's
  own bodies fails: `object defines g_objectSystem_00586dc8, which names retail
  address 0x586dc8 outside the function`. Such a candidate smuggles the datum
  (counterexample 2); references to it still relocate to the real address.
* `FUN_`/`thunk_` names resolve only to a recorded function start.
* Data names (`D_`, `DAT_`, `g_`, `s_`, `GPR_`, `PTR_`, `UNK_`, `FLOAT_`,
  `DOUBLE_`, `BYTE_`, `WORD_`, `DWORD_`, `QWORD_`, `data_`, `str_`) resolve only
  to an address that is not inside any function's code extent.
* Any other name resolves to a function start or to data, never to an address
  inside a function body. There is no address range check: scratchpad
  (`DAT_70000000`), hardware register and kernel-area names are honest targets.
* A name that **is** in `config/SLUS-20836/symbols.txt` must carry its own address when it
  carries one in the eight-digit bootstrap form (`_00586dc8`; `thunk_FUN_x`
  names its target by convention and is exempt, and the 60 such rows are the
  only disagreements in the map). The six-digit form is still accepted for
  unmapped names (`FUN_2e5ac0` is in use), but a mapped name is not held to
  it: `__adddf3` is the runtime helper's real name, not a claim.

Each refusal is a `symbol 'name': reason` line under the DIFFER header. Two
consequences the first sweep measured: about 1,070 units reach a function's
address through a Ghidra `DAT_` name (a function pointer stored as data; the
honest spelling is the function's map name) and 31 call unlisted retail code
in a gap between mapped functions (`FUN_002f00c0`; the map, not the source,
is incomplete). Both fail with their message; the fix is a rename or a map
entry, outside the oracle. `linkgen` still provides such a symbol at the
address it spells, so the relink stays byte-identical, and prints how many it
provided that way.

### Unsupported relocation types are errors

`object_relocs` raises
`unsupported relocation type R_MIPS_REL32 against 'x' at +0x8 in .rel.text`
for a relocation whose type it does not know, and `verify_one` reports that as
the failure; skipping it would compare words it never patched. A census of every C object in
the relink found only the five supported types.

### check.py's single-function mode

`check.py --function 0x... --cand file.c` runs `verify.verify_one` with the
per-unit tables, and its `FLAGS_DEFAULT` is the Makefile's `-O3 -Iinclude`.
Comparing only a prefix of the object's raw words with retail would pass a
candidate with trailing extra code or unapplied relocations.

### Categories (what `make check` counts)

The rules above are not weakened; instead every verified unit lands in exactly
one category (`verify.category`, `cat=` in the report head, listed per unit in
`build/check-categories.tsv`): `match` (bytes, exception metadata and symbol
rules all pass — the only thing the `cover :` line counts), `code-only` (bytes
identical, exception metadata `missing`/`extra`/`differ`), `name-defect` (bytes
identical at the address the name spells, but a data name sits on a function
start or a mapped name's eight-digit suffix is not its address),
`inventory-gap` (bytes identical, a reference lands in a symbol-map gap or
inside another function's extent), `mismatch` (bytes, size, tables or object
shape differ — smuggled data and unowned sections included) and `compile`.
Precedence: mismatch > inventory-gap > name-defect > code-only. The verifier
compares bytes at the spelled address of a refused name (what the relink
provides) precisely so a naming defect can be told apart from a mismatch.
`make check` exits 1 only for `mismatch`/`compile`; the debt categories print
with a `!! debt:` prefix.

### Known limits

* **A wrong function name with the right address** (counterexample 3b,
  `extern int whatever_002d3070(...)` for the map's
  `igObjectSystem_FindMetaByName` at 0x2d3070) still matches. The relocation
  resolves because 0x2d3070 is a recorded function start, and the retail
  bytes are the same `j 0x2d3070` either way; bytes cannot tell what the
  caller called it. Readability review has to catch it: a source that calls a
  mapped function by a made-up address name instead of its map name is wrong
  even when it matches.
* **A wrong data base compensated by an index** (counterexample 3,
  `g_notTheObjectSystem_00586dc4[1]` for the datum at 0x586dc8) also still
  matches: the compiler folds the +4 into the relocation addend and the bytes
  agree. Distinguishing it from a legitimate `g_array[1]` needs a data symbol
  map saying where each datum starts; `config/SLUS-20836/data-names.tsv` is a partial seed
  (5,400 rows, none for this address), not that map. Until there is one, a
  data name's base address is reviewed, not verified.

### Section census, orphan gate and the oracle-change rule

Three guards keep the oracle itself honest:

* **Section census.** `tools/verify.py` lists every section name an object of
  the relink may carry in `COMPARED_SECTIONS` (compared with retail or
  deliberately ignored, one reason each) and `DEBT_SECTIONS` (known, not yet
  compared — empty today). `tools/test_section_census.py` scans every
  `build/link/u_*.o` of the last `make link` (it skips, saying so, without one)
  and fails on any other name, naming the object and section, or on a
  `.data`/`.bss` with content. `make check` ends a whole-tree run with
  `sections: N objects, {name: count, ...}, K unknown` and exits 1 when K > 0.
* **Orphan gate.** `tools/linkcheck.py` prints, after `BYTE-IDENTICAL`, a
  `linkcheck: orphans:` line: the bytes the link placed outside `.text` must be
  `.exceptix`/`.exception` only and total no more than the orphan debt `make
  check` recorded (`; orphan N bytes` on the diagnostic of every exc=extra/differ
  unit in `data/check-categories.tsv`, N = the aligned size of the unit's
  exception sections). Anything else exits 1. The byte-gate parser in
  `.githooks/pre-push` (run by the oracle runner on every pushed commit) reads that
  line as gate 4 ("orphans ≤ recorded debt"); gate 5 is the exit code of
  `tools/progress.py --debt-check`.
* **Oracle-change rule.** The oracle's own files are listed, one pathspec per
  line, in [`.githooks/oracle-files.txt`](../../.githooks/oracle-files.txt) (the
  single source; the hook reads it). A push whose commits touch any of them must
  (a) pass `python3 -m unittest discover -s tools -p 'test_*.py'`, (b) show every
  counterexample test of `tools/test_oracle_holes.py` run and pass — i.e. the
  audit's sources still fail to verify, not skipped — and (c) carry a line
  starting `oracle-change:` in the message of every commit in the range that
  touches a protected file, saying what changed in the oracle. The hook prints
  `oracle a/c`, `b/c`, `c/c` lines; `testing/test_prepush_gate.py` exercises them
  on a throwaway repository with saved test output (`DW4_PREPUSH_ORACLE_ONLY=1`).

### The unit profile comes first

A function's compiler, flags and exception mode come from one profile per
translation unit, `config/SLUS-20836/units.tsv` ([build profiles](build-profiles.md)), not
from per-function pins. In the oracle:

* **Resolution.** `tools/verify.py`, `tools/check.py` and `tools/linkgen.py` ask
  `tools/unitprofiles.resolve` for a function's compiler, flags and exception mode.
  The exception mode is part of the profile: an exceptions-off unit compiles with
  `-Cpp_exceptions off`, so a `.cpp` file in a unit retail built without exception
  metadata does not emit an `.exceptix` record retail lacks (the `exc=extra`
  code-only debt), while a `.c` file in an exceptions-on unit owes its record
  (`exc=missing`). Duplicates of a compiler unit are compared under the
  profile of the unit their retail copy sits in.
* **Overrides are second.** A per-function row (`config/SLUS-20836/unit-flags.tsv`,
  `config/SLUS-20836/unit-compilers.tsv`) inside a unit must be marked `provisional`; an
  unmarked row is refused before compiling. The verifier compiles the unit profile
  first and the override only when the unit profile does not reproduce the code
  bytes. A function that matches only that way is **`foreign-profile`**
  (`cat=foreign-profile override=foreign` on the head line, the two profiles and the
  unit-profile attempt's own lines in the body): debt, excluded from `cover :`,
  counted by `tools/progress.py` as `foreign_profile.*` and ratcheted. A row the unit
  profile makes unnecessary is tagged `override=unused` or `override=redundant` and
  listed by `make check` as a stale override.
* **Cache keys.** `buildcache.unit_profile_sha` digests the unit row (compiler
  path and content digest, flags, exception mode, status), the override rows and the
  resolved profiles for the owner, the members and the duplicates of a compiler
  unit, so editing one unit's row recomputes exactly that unit's functions.
* **Outside every unit** (regional targets, fixtures) the per-function rows remain
  the whole profile; the regional build options and the fixture tests rely on
  that.

`tools/test_unitprofiles.py` covers the table, the override rules, the generator's
consistency report and the four category outcomes on the 16-byte counterexample
body.

### Group units: exception metadata per member

For a compiler unit declared in `config/SLUS-20836/unit-objects.json`,
`verify_emitted_object` attributes every exception record and
table to a member (`group_exception_sections`: word 0 of a record relocates
against the member, word 2 against a label in the member's own table; a record
of an unowned body is still a rejection) and compares each member's record and
table with `config/SLUS-20836/exceptions.txt` exactly as the standalone path does
(`expected_exception_records`): a placed body (owner, emitted) whose record is
reproduced is `ok`, emitted where retail keeps none is `extra`, absent where
retail keeps one is `missing`, different is `differ`; a verify-only duplicate is
compared only when both exist (its copy is discarded with its body, its retail
record belongs to the unit that placed the copy). The unit is `match` when the
bodies, tables and every record pass, `code-only` with `exc=…` otherwise; the
byte compare always runs first. Rejecting such an object before any byte
compare ("unowned code or runtime data in emitted object") whenever it carries
`.exceptix`/`.exception` sections and its row has no `exceptions` declaration
would leave about 35 groups passing only under a `-Cpp_exceptions off` override,
counted foreign-profile although their code matches. The `exceptions` row is an optional
assertion for the owner: it must agree with the recovered table, and it stands
in for the table in a fixture without one. A differing relocated word in a
table is reported with both targets — `[n] is a relocated address: ours
0x3d9bd0 (__dt__3RefFv), retail 0x1489a0 (<name>)` — so the source side can
re-point the duplicate. `isolate_emitted_body` keeps the selected member's
reproduced record and table, renamed `.exceptix.dw4_<index va>` /
`.exception.dw4_<table va>`, and `linkgen` places them like a standalone unit's
(from the verifier's placement record); every other copy is discarded and
retail's bytes stay.
