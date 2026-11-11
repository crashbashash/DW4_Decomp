# Matching decompilation (the build)

The [per-unit compiler requirements](unit-compilers.md) describe the
content-pinned alternate compiler for combat dependencies. Both verification
and linking apply these requirements; unlisted functions retain the global
compiler setting.

[Compiler-emitted function ownership](emitted-functions.md) covers the two
complete functions emitted by the nearby-query source. Every registered member
is verified and placed; unregistered extra code remains an error.

**Goal: rebuild `game.elf` from C with the original compiler, and prove every function
byte-for-byte.** This is a *matching* decomp — matching is the success condition, not
"the code looks equivalent". It is the stated goal of the repo.

Toolchain identity and how it was found: [`toolchain.md`](toolchain.md). In one line —
**MWCCPS2 3.0, build `011126` (CRC32 `C82F0A93`)**, driven by **wibo** (Wine fails its
FLEXlm license check).

## What this is for

The downstream goal is a decompilation someone can change and rebuild onto a PS2. This is possible
at the current coverage: `make link` rebuilds the whole section from a mix of decompiled C and the
generated split assembly, byte-identically, so any function can be edited — C where it is decompiled,
assembly where it is not — and everything else relinks bit-exact. What is missing here is **tooling,
not percentage**: an ISO relayout step (a rebuilt ELF changes size, and the current patchers
byte-patch precisely to avoid that) and a documented edit → build → burn recipe.

**Typing is not decoration.** m2c's output matches retail while spelling everything
`*(int *)((char *)p + 8)`, so reproducing the structs and signatures the original had is separate
work, and the recovered metadata — `data/reflection.json`'s 659 classes and 3,680 fields, the
object-model field maps, the vtable slot signatures — is a first-class deliverable. It measures as
*neutral for matching*, and that is exactly as expected: it buys nothing in the matched-byte
percentage. The SDK/IOP modules are outside decompilation scope, and the
[SDK boundary](platform-boundary.md) is recorded instead.

## Layout

| Path | What | Committed? |
| --- | --- | --- |
| `config/SLUS-20836/symbols.txt` | **the code layout** — one `va size name` line per function, sorted (the current function and byte counts are in [`../../PROGRESS.md`](../../PROGRESS.md)). The canonical answer to "what code exists and where" | yes (generated) |
| `config/SLUS-20836/jumptables.txt` | **the switches' jump tables** — `fn_va jtbl_va count` per table, recovered from the retail image (`tools/jumptables.py`). `verify.py` compares the compiled `.rodata` against these bytes and the relink places it at that address | yes (generated) |
| `config/SLUS-20836/layout.txt` | the **disjoint tiling** of the section (code, data, and a `jtbl` unit per table) that the relink places, one unit per address | yes (generated) |
| `asm/<name>.s` | the retail instruction words for every function, so the undecompiled remainder links (the "Ship of Theseus" build) | no (generated from your executable, gitignored) |
| `src/**/*.c` | the decompiled C, grouped by module (`src/lua/`, `src/engine/`, …) with unnamed functions under `src/unmatched/`. A file is a **translation unit** — one system, many functions, in retail address order — not one function; `tools/units.py` splits a function back out for the per-function tools (`check.py`, `linkgen.py`, `verify.py`) | yes |
| `build/` | objects | no |
| `tools/split.py` | writes `config/SLUS-20836/symbols.txt` and emits `asm/` from the retail ELF | — |
| `tools/jumptables.py` | writes `config/SLUS-20836/jumptables.txt` — the switches' `.rodata` tables | — |
| `tools/layout.py` | writes `config/SLUS-20836/layout.txt` — the disjoint tiling the relink places | — |
| `tools/check.py` | split integrity + coverage; the only number worth quoting | — |
| `scripts/match_func.py` | one-off: compile a candidate and diff it against a target | — |

`asm/` is **generated and not committed**: it is the retail code as text, so every clone
writes it from its own executable. `make asm` regenerates it; `make check` and `make report`
do so when the tree is missing or stale (`tools/split.py --ensure`, about half a
minute). Never hand-edit it. It is not committed because publishing it publishes the game's code.

Eight names occur at several distinct addresses (SDK-style stubs: `AddDmacHandler`,
`RFU116_SetSyscall`, …); `tools/split.py` suffixes the repeats with `__<va>` so nothing is lost and
linker symbols stay unique.

## Cached gates

A cold `make check` takes about 47 minutes on the full tree and a cold `make link` about 70, though each answer is a pure
function of its inputs. (The "~40 s" figures further down were measured at a
few thousand matched functions; they describe the thread pool's scaling, not the full tree's cold run time.) `tools/buildcache.py`
stores definite results in `build/cache/` (untracked), keyed by content:

* **`tools/check.py`** caches two sweeps: split integrity per `asm/*.s` unit (key: the assembly bytes, the retail bytes, the
  binutils versions and the tool source), and per-function coverage (key: the exact text the compiler sees — the file, or the one
  function extracted from it — plus flags, compiler binary, `wibo`, the retail ELF, the whole `include/` tree and every non-C file
  under `src/`, the config tables and the source of every tool module `check.py` imports). Only `matched` / `mismatched` are cached,
  never a compile failure.
* **`tools/linkgen.py`** caches each unit's object (compiled C units and the raw-bytes units), keyed the same way plus the layout and
  the owner's jump-table spans. A hit is accepted only when the object file on disk still has the digest recorded with it.
* A rerun after editing a few functions therefore recompiles only those. Any change to a header, the compiler, the ELF, a config
  table or a tool module changes every key (a coarse miss, never a stale hit). A run rewrites the store with only the entries it
  used, so it cannot grow without bound.
* **Run uncached before publishing a milestone:** `make check-fresh` / `make link-fresh` (or `--no-cache`, or `DW4_NOCACHE=1`). The
  cached and uncached `.text`/`.rodata` of a 256-unit range were compared and are identical; `testing/test_buildcache.py` covers the
  key and store rules. Whole-file comparison of raw-unit objects is not meaningful (their symbol tables embed a per-run temp path).
* Testing aids, not gates: `check.py --cover-limit N`, `linkgen.py --unit-range LO:HI`.

## Translation units

`src/` holds **translation units**, the way the original source was built: `src/lua/api.cpp`
defines 47 functions, `src/engine/igObject.cpp` the `igObject` class in retail order, `src/game/*.c` a
`be*` class each. Unnamed functions stay in `src/unmatched/`; named ones are grouped and folded
there by `tools/place_named.py` (see [`naming.md`](naming.md)). A unit's functions are
written in retail address order, because MWCC emits a unit's functions in source order — so
contiguity in the binary is what identifies the original file, and `tools/merge_units.py` folds
per-function files into a unit once a module is worked. (The Lua functions are one contiguous
run: the 116 real implementations occupy `0x371c70..0x375d90` with every gap between them ≤16
bytes of alignment padding.)

The matching build is still **per function**: `verify_one` compiles one function and compares
its words to retail. `tools/units.py` bridges the two by blanking every definition but the one
being checked, leaving the unit's `#include`s, prototypes and `extern`s in place. A symbol whose
declaration two functions disagree on (m2c guesses `int[4]` in one, `char[]` in another) is kept
as a block-scope `extern` inside each user, so no two functions have to agree.

The split is written as a short `dw4u_`-prefixed file in the unit's own directory. MWCC
reads a file's extension from the first dot, so it refuses a filename with a leading dot
(`unrecognized file contents or filename extension`), and it truncates paths past about
80 characters.

## Workflow

```sh
make symbols           # (re)generate config/SLUS-20836/symbols.txt
make asm               # (re)generate asm/  — generated from your executable, never committed
make check             # split integrity + coverage  (all cores; cached reruns are quick, a cold run is long — see Cached gates)
make report            # coverage only

# decompile one function
sed -n '1,40p' asm/FUN_XXXXXXXX.s      # read the retail code
$EDITOR src/unmatched/FUN_XXXXXXXX.c   # write candidate C
make check                             # or: scripts/match_func.py 0xVA src/unmatched/FUN_XXXXXXXX.c FUN_XXXXXXXX
```

A function is done when its compiled bytes are **identical** to retail. Mismatches print
the exact differing instruction; there is no "close enough".

## Status

**The counts live in one place: [`../../PROGRESS.md`](../../PROGRESS.md)** (regenerated by
`tools/progress.py` on every push; `docs/progress.json` is the same data). It carries the function
and code-byte totals, the matched share split into C/C++ and `asm` bodies, the fully-linked share
of the 4,541,184-byte section, the size bands and the median sizes. This page does not restate
them.

What is stable:

| | |
| --- | --- |
| Split integrity | every unit of the layout round-trips byte-exactly (`make check` prints `split : N/N`) |
| Compiler + flags | global default `-O3`; proven [per-unit compiler requirements](unit-compilers.md) and flag overrides for an alternate MWCC build and for Sony EE GCC 2.96 ([sd-prologue](sd-prologue.md)). A unique original build is not established |
| **Full section relink** | **BYTE-IDENTICAL** — all 4,541,184 bytes of the main section rebuild from the per-function objects (C/C++ where matched, `asm` bodies, retail bytes from `asm/` for the rest), including the switches' tables as `obj(.rodata)`; `make link` prints the object and byte accounting |

The function count flatters (it counts trivial leaves), so the byte figure is the headline.
Because the ELF *is* the engine (the proprietary, Insomniac-derived `ig` object model), finishing
means recovering the engine too, not just game logic.

## Gotchas

* **Never name a Makefile variable `AS`, `CC`, `LD`.** Make defines them as built-ins, so
  `AS ?= mipsel-linux-gnu-as` *silently keeps the host x86 `as`*, which then fails on MIPS input
  with `alignment not a power of 2` and warns about truncating instruction words. The variable here
  is `CROSS_AS` for that reason.
* **Never read instruction words out of `objdump -d`.** objdump elides runs of `0x00000000` as
  `...`, so every `nop` pair vanishes and a byte-exact split looks broken. `tools/check.py` and
  `scripts/match_func.py` take the symbol's offset and size from `readelf -s` and slice the raw
  `.text` from `objcopy -O binary` instead.

## Flags

**`-O3`, and the knob that matters is `-opt speed`, not the level.**

| | |
| --- | --- |
| `0x15e130` population count (`while(v){ if(v&1) n++; v>>=1; }`) | `-O3` **MATCH**, `-O4,s` **MATCH**, `-O4,p` differ, `-O2` differ, `-O1` differ |
| 16-function synthetic corpus (loops, nested ifs, switch, div/mod, float, str* loops, bsearch, rotate, clamp) | `-O3` vs `-O4,s`: **16/16 byte-identical**; `-O4,p` differs |

`-O4,p` is `-opt level=4,speed`; `-O4,s` is level 4 without speed; `-O3` is level 3.
Level 3's extra loop unrolling only fires *with* `-opt speed`, which is why `-O3` and `-O4,s`
agree and `-O4,p` does not. The game was built **without `-opt speed`**.

Trivial leaves cannot pin the flags: three 8-byte leaves match `-O4,p` by
coincidence (no optimisation level can tell `return -1;` apart), and only a real loop function
separates the levels.

**C89 note:** MWCC 3.0 defaults to C89 — `for (int i = 0; ...)` is a syntax error. Declare loop
variables at the top of the block.

**Relocations:** only functions with *no calls and no globals* can be compared as unlinked
objects. An object stores a relocation, not a final address (`lbu v1,-32112(gp)` becomes
offset 0 + `R_MIPS_GPREL16`), so anything touching a global or calling out cannot be compared until
its relocations are applied — the next section.

## Relocation-aware verification

`tools/verify.py` is the tool that makes the decomp *scale*, and it exists because of a
simple fact: **an unlinked object stores relocations, not addresses.** Raw object bytes can
only be compared for self-contained leaf functions (4 of 15,974). Everything else needs the
relocations applied first:

```sh
python3 tools/verify.py 0xVA src/unmatched/FUN_XXXXXXXX.c --verbose
make verify VA=0xVA SRC=src/unmatched/FUN_XXXXXXXX.c
```

It compiles the candidate with MWCCPS2 3.0 at `-O3`, reads the object's relocations
(`readelf -r`), resolves each symbol, applies them, and diffs per instruction. Resolved by
kinds, all three confirmed against retail:

| Reloc | Symbol resolution | Verified on |
| --- | --- | --- |
| `R_MIPS_HI16` / `LO16` | functions from `config/SLUS-20836/symbols.txt`; data from an **address-bearing name** (`D_0056df30`, `DAT_004d22e8`) — the bootstrap convention | `0x246780` — `if (p) *p = D_0056df30[2]; return D_0056df30[0];` |
| `R_MIPS_GPREL16` | same, plus `gp` | `0x130000` — the one-shot guard byte at `.sbss` `0x554b00` |
| `R_MIPS_26` | callee from the layout | `0x109ac8` — tail call passing `"[MPEG ERROR]%s\n"` (0x4d22e8) |

**`gp` comes from the ELF's `.reginfo`** (24 bytes: `gprmask`, `cprmask[4]`, `gp_value` at
`+20`) — it has to, because `__start` is `move gp, a0` (`0x001001c0`), i.e. the loader passes
it in. `gp = 0x0055c870`, and `gp - 32112 == 0x00554b00`, exactly the first byte of `.sbss`.

`make check` uses the same path for every unit under `src/` (`tools/srctree.py`), so coverage counts real matches
rather than leaf-only ones. A full data symbol map is not needed: Ghidra's `DAT_<addr>` labels
(6,562 of them, in `data/symbols.json`) and the address-bearing-name convention cover data references.

### Multiple switch tables and ELF section ownership

MWCC can emit several distinct sections all named `.rodata` in one function
object. GAMERAM has two 88-byte tables at `0x519310` and `0x519370`, with eight
padding bytes between them. Extracting by name overlays their bytes, and
combining both relocation lists applies case-address relocations twice.

The verifier maps each nonempty table section by its ELF index to one recorded
retail table, requiring matching section counts and sizes in compiler/table
address order. Local table symbols resolve through their defining section;
relocations are selected by their relocation section's `sh_info` owner. Both
tables and the complete function code must compare exactly. Padding is separate
raw layout data, rather than part of either compiled table.

For linking, only generated object section names change: duplicate table names
become `.rodata.dw4_<address>`, preserving payloads, symbol section indices and
relocation ownership. The linker pins each named input section independently.
`python3 tools/test_multiple_jump_tables.py` compares a real two-switch object
with an independent GNU link, checks preserved metadata and layout gaps, and
rejects corruption, missing/wrong-sized tables and unresolved relocations.

## Bulk decompilation (`tools/automatch.py`)

Hand-writing every function is not the way in. The same instruction shapes recur, so
`automatch.py` templates them, compiles each candidate, and **writes
`src/unmatched/<name>.c`** (or `.cpp` when the template needs C++ mode — see
[`guard-family.md`](guard-family.md))
**only when `verify.py` confirms the bytes match** — an auto-generated file is exactly as
trustworthy as a hand-written one; the tool saves typing, it does not lower the bar. Failures are
reported and nothing is written.

```sh
python3 tools/automatch.py --report        # yields per template, write nothing
python3 tools/automatch.py                 # write verified matches (never clobbers existing)
python3 tools/automatch.py --only gget --limit 50
```

| Template | Shape | Yield |
| --- | --- | --- |
| `guard` | 18-insn flag-guard body (`bool t; if (!g \|\| !(t = g->f & 4)) X();`) — `.cpp` | 550 / 550 |
| `wcall` | 28-byte single call, frame kept — `void f(void){ X(); }` — `.cpp` | 527 / 527 |
| `wload` | 32-byte single call with a constant-address argument — `.cpp` | 485 / 493 |
| `wargs` | any other frame-keeping single call: the argument setup is decoded (constant, pass-through, field load, global address, address of a parameter) — `.cpp` | 55 / 658 |
| `m2c` | *not a template* — drafts the harder shapes, verified before writing (`tools/m2c_batch.py`) | see [`m2c-bulk.md`](m2c-bulk.md) |
| `gget` | `lui at,HI ; jr ra ; lw v0,OFF(at)` → `return *(int*)ADDR;` | 601 / 609 |
| `ccall` | `lui a0,HI ; j TARGET ; addiu a0,a0,OFF` → `TARGET(OBJ)` | 591 / 591 |
| `empty` | `jr ra ; nop` | 184 / 184 |
| `fzero` | `sw zero,OFF(a0) ; jr ra ; move v0,a0` | 175 / 175 |
| `fget` | `jr ra ; <load> v0,OFF(a0)` (lw/lb/lbu/lh/lhu/lwc1) | 83 / 83 |
| `setter` | `jr ra ; sw aX,OFF(aY)` | 46 / 46 |
| `jthunk` | `j TARGET` | 39 / 39 |
| `rconst` | `jr ra ; li v0,K` | 31 / 31 |
| `jload` | `j TARGET ; lw a0,OFF(a0)` | 21 / 29 |
| `ident` | `jr ra ; move v0,aN` | 8 / 8 |

**Matching proves the code, not the types.** A 4-byte return load is byte-identical whether the
source said `int`, `unsigned`, `float` or a pointer, and an integer parameter list may really be
pointers. Every generated file says so in its header, so a verified *shape* is not mistaken for a
verified *signature*.

A census of 15,974 functions (10,059 distinct shapes; the top 40 shapes cover **31.6%**) is
what picks the templates.

**The two big families are solved by source idiom and
language mode, not by flags.** The full account is
[`guard-family.md`](guard-family.md); the short version:

* **The guard family (1,057 functions).** Retail's `andi ; sltu v0,zero,v0 ; bnez`
  flag test is the int→bool **value** conversion of an assignment to a *named* `bool` inside the
  short-circuit condition:

  ```cpp
  bool t;
  if (!g || !(t = g->f & 4))
      X();
  return G0[0];
  ```

  compiled as **C++** (only C++ has `bool`, and MWCC takes the language from the file extension, so
  these are `src/*.cpp` units). The pointer test stays a plain `beqz`, the global
  is still loaded exactly twice, and the global must be declared as a 16-byte array or MWCC
  addresses it gp-relative. These **550** are 72 bytes each. The other **507** members are
  the *same idiom plus one dead `nop`* before the merged `jal`. They match with `asm { nop }`
  under the default compiler, or without it under the alternate compiler at `-O3,p`
  (`tools/guard_b_gen.py`).
* **The one-call wrappers.** The 28/32-byte "single call, frame kept" wrappers are
  not a tail-call puzzle: **MWCC's C front end turns `void f(void){ X(); }` into a 2-instruction
  `j` tail call; its C++ front end keeps the frame.** Retail is C++, so these reproduce only as
  `.cpp` too (`wcall`, `wload`). The two exact shapes do not cover the rest of the family -
  wrappers that also set up arguments - so **`wargs` generalises them**: it decodes the
  argument setup from the retail instructions and lets `verify.py` decide.
  The decode hinges on the R5900 calling convention, which passes argument 5..8 in
  `t0-t3` rather than on the stack, so a wrapper's `t`-register setup is an argument too.
  The m2c pass needs the same thing: m2c's `MipsArch` models only
  `a0-a3`, so the pipeline runs its **`mipsee-mwcc-c`** arch with `t0-t3` renamed to `a4-a7`,
  which is what the class-registrar trampolines need.

**The rest, via m2c.** Functions beyond shape templates go through
[`m2c`](https://github.com/matt-kempster/m2c) with its
**`mipsee-mwcc-c`** target (the EE ABI), each draft verified before it is written.
Two things that pass depends on
are worth more than its yield: feeding m2c **symbolized** data references (`%hi`/`%lo`) rather
than raw `lui`/`lw` (its type context is useless without that), and **727 functions whose Ghidra
boundary cuts off the delay slot** — not functions at all, and unmatchable until `tools/split.py`
grows them (the link stays byte-identical). The pipeline, the cleaner, the measured failure
taxonomy and the near-miss worklist are in [`m2c-bulk.md`](m2c-bulk.md).

## Source idioms

Retail shapes that only one spelling reproduces:

* **`jal X; nop; nop` at a join**, a `nop` just before the label a preceding branch targets.
  This is not reachable from source under the default compiler: about 40 C and C++ spellings
  give a function one word short, as do all `-O` levels and the `-O3,s`/`-O3,p` variants. The
  alternate compiler at `-O3,p` emits it from ordinary source. Try that profile before anything else.
* **A `nop` before a label or `jr ra` is often a deleted branch's delay slot.** A branch to the next
  instruction is removed late, so its delay slot stays, and so does the load that fed it.
  `if (p->f) return;` as a whole function compiles to `lw v1,f(a0); nop; jr ra; nop`, where a plain
  read of `p->f` is dropped. `if (a == b) return 1; return 0;` after an earlier `return 0` leaves
  `xor; sltiu; nop` at the epilogue. Other reachable shapes give the same `nop`: an inlined compare, a
  struct view that keeps two loads apart, or the right profile for the unit. Look for those before
  writing `asm { nop }`.
* **A GCC wrapper that keeps its frame around one call** is not a tail call: `ee-gcc -O2` emits `j` for
  `void f(void) { g(); }`. On the 2.9-ee releases `int r = g(); return r;` keeps `jal` and the frame. On
  2.96 that still gives `j`, and an empty macro after the call does it: `g(); EMPTY();`, where `EMPTY()`
  is `do { } while (0)`. Neither `((void)0)` nor an empty block has that effect. A result that changes
  type with no conversion, such as `short g(); int f(void) { return g(); }`, also keeps the frame on both.
* **An empty GCC delay loop survives on its test.** `for (i = 0x1FFF; i > -1; i -= 32) { }` is kept with
  r5900 short-loop pad nops; the same loop tested with `i >= 0` is deleted.
* **A copy that hoists into an earlier delay slot** stays behind the read before it when it is written
  as an explicit cast, even to the same type: `object = (T *)input;`, where `object = input;` hoists.
  MWCC's `dmove` pseudo-op is not needed.
* **Local declaration order under b52.** The first-declared local takes the higher saved register and the
  higher stack slot, the opposite of the older compilers, so a source that matched under 3.0 or combat usually
  needs its locals reversed. That alone moved most of Alchemy Core's blocking functions. Past six locals, a greedy
  climb over line order beats a random sweep. A variable that no order moves belongs to an inlined helper:
  inline-scope locals are coloured after the function's own.
* **Compare spelling picks the register.** `a > b` gives `slt at,b,a`; `b < a` gives `slt reg,b,a`. `n > 1`
  differs from `n >= 2`, and `0 <= x` gives `slt at,v,zero`.
* **`igResult` compares.** `addiu v1,sp,N; lw v1,0(v1)` comes from a one-word class with a user copy constructor
  and `operator==(const R &)`, compared directly on the call's temporary. A named local folds the address away.
* **`daddiu reg,zero,N`** is a constant assigned to a `bool`, `short` or `char` variable.
* **An inline destructor always emits its out-of-line copy.** Its body must be spelled as retail's copy is, and the
  function needs a `duplicates` row in `unit-objects.json`, which the verifier checks against retail's bytes.
* **A field reloaded where the compiler would reuse an earlier load (`b52`).** Common-subexpression elimination
  merges two loads only when their types agree, and a `const` difference counts. Inline `const` accessors are the
  source shape this comes from:

  ```cpp
  L *list() const { return f8; }
  int count() const { return f8; }

  n = a->list()->count();
  e = a->list()->get(i);   // lw v0,8(a0) again on each pass of the loop
  ```

  What to try, in order:

  * A `const` parameter, when the function never writes through the pointer. No read needs changing.
  * A `const` accessor at the read that has to stay separate: a member on a struct the file declares, or
    `static inline int countOf(const List *l) { return l->_count; }` for a shared class. If the accessor on the first
    read gives other bytes, read plainly there and put it on the later read: `n = l->count; ... l->count = countOf(l) + 1`.
  * A `const T *view = p;` declared at function level, where an accessor changes the bytes.

  The same difference moves a load the scheduler would otherwise place later: a field declared `unsigned` and read
  plainly, or an accessor returning `unsigned`, loads in source order, where a `const` read does not. Rewriting the
  increment itself as `l->n++`, `+= 1` or `1 + l->n`, or changing `p[0]` to `*p`, does not separate the loads.

  A cast that only retypes the read, such as `*(const int *)&x` or `((const T *)p)->f`, forces the same bytes but is
  unlikely to be source. It does not make a match: the function keeps its `volatile` and stays `unapproved` until
  a spelling with a reason turns up.
* **A list search stores its key (`b52`).** `sw a1,60(sp)` with the key loaded back before a search loop is
  `igTDataList<T>::find` in `include/dw4/igTDataList.h`, which takes the key by value. The address of that parameter is
  what keeps the key in memory: a reference, or a read of the value itself, folds it into a register. Why the source
  took that address is not known. The executable holds the template's name, as `Gap::Core::igTDataList<...>`.
  Where the key's store comes before the read of the list, assign the list in the call: `(list = owner->_list)->find(key)`.
  `T` has to be a pointer: with `int` the store goes away. An append that stores its value to the stack before reading
  the count, and loads it back for the store, takes it the same way: `void append(T v) { /* grow */ const T *p = &v; _data[n] = *p; }`.
* **A local that lives in memory because it is an object (`b52`).** A reference held in a stack slot, reloaded before
  a store and released at the end of the function, is a smart-pointer object with a real inline destructor. Passing it
  by `const &` to an inline helper takes its address, which is what keeps it in memory:

  ```cpp
  #include "dw4/igSmartPointer.h"

  igSmartPointer<igProbe> held(create());
  setField(owner, held);   // static inline, takes const igSmartPointer<igProbe> &
  ```

  The name is the game's own: the executable holds the string `::~igSmartPointer<`. One definition serves every
  holder. Whether an inlined release reloads depends on the holder: an unnamed temporary does, a named holder built
  directly does not ([emitted functions](emitted-functions.md#one-reference-holder)).

  It is the non-empty destructor that keeps the local in memory: without one the compiler holds it in a register, and
  no `const &` is needed for the reload. Related shapes:

  * A hidden result pointer with `move v0,zero` is a class returned by value, and copy-constructing `*out` is the retain.
  * A release with no store before it is a retaining constructor followed by dropping the factory's reference.
  * Frame slots go holders first, then expression temporaries, then the locals of inlined helpers. A returned object
    used only inside an expression has to be a temporary, not a named local.
  * Reading `ref.p` inside a helper that takes `const Ref &` settles register ties; going through `get()` there can
    change them.

  * A `sb zero,N(sp)` just before a factory call, on a byte nothing reads, is an empty class passed by value, with one
    temporary for each call: `Ref a(create(0), Tag());`.

  The destructor's out-of-line copy often exists in retail: when the verifier reports one, name it as a `duplicates`
  row in `unit-objects.json`, with `__dl__FPv` in `externals`. Hundreds of retail copies are word-identical, so the
  address shows that the bytes exist, not which class a copy belongs to. A helper that only takes an address, a store through
  `*(void **)&slot`, or a union read at another type forces the same bytes but has no reason to exist, so none of
  them makes a match.
* **A value spilled and reloaded before every use.** A local declared `volatile` reproduces this, as
  `RT * volatile sp6C`, where a plain local adds a saved register. Read it once into
  a plain local for the final release so the object stays in `a0`. It is not a finished spelling: the
  function stays `unapproved` until the owner approves that use
  ([source approvals](source-approvals.md)), so look for what really keeps the value on the stack first.
* **The object graph's reference release** compiles only from
  `if (&obj->field) { release(obj->field); }` on a real struct with the field at its recovered
  offset. Retail emits a redundant `addiu vX,base,OFF; beqz vX` on the field's address before
  the value test. A value test, a `(char *)obj + N` expression and arithmetic on a `void **` do
  not reproduce it. The struct can be a shape: `void *fNNN` at the exact offset is enough, plus
  any byte field the code really reads. Its companions:
  * The 64-bit refcount mask `dsll32 vX,vX,9; dsrl32 vX,vX,9` is
    `((unsigned long long)((long long)v << 0x29) >> 0x29)`.
  * A refcount release reads +4; a handle release reads -4 with the pointer at -8.
  * Two vtable stamps are the base constructor then the derived one.
  * A destructor tail is `if (arg1 > 0) <thunk>(arg0); return arg0;` with `arg1` a 16-bit
    signed value.
* **A call wrapper whose retail body ends in a memory barrier** is the call followed by an
  inline `sync` statement: the barrier sits after the call's delay slot and before the frame
  restore. A variant adds a trailing `ei` and a zero return. Inline `sync` and `ei`
  compile to the exact retail words.
* **A function address stored repeatedly** goes through a function-pointer member, such as
  `void (*getEnum)(void)`, assigned the plain function. An `int` member with an `(int)fn` cast lets
  b52 keep the address in a saved register. Data names aliasing the function are rejected as
  `name-defect`, and this form needs none.
* **A loop invariant retail leaves inside the body** means b52 has hoisted the written form. Use
  labels: `i = 0; goto test; top: ...; i++; test: if (cond) goto top;`.
* **A guarded table store** reads the count twice:
  `if (t->count != 0 && i >= 0 && i < t->count) t->data[i] = v;` in a `static inline`. A local
  count changes the registers. A `const int &v` parameter keeps the value's load after the test.
* **Swapped operands of a commutative operation:** load into the variable, then use a compound
  operator: `v = p[0]; v |= p[1] << 8;`.
* **`movz` from a ternary** comes from enum constants, `b ? kOff : kOn`. Plain integers fold to
  `sltu` and `xori`.
* **A field added into or subtracted from memory** takes retail's register order through an
  unsigned temporary or a cast on the compound assignment: `{ unsigned q = r->f; r->f = q - n; }`,
  `*p += (int)x;`. The plain form swaps `v1` and `a0`.
* **A one-byte guard flag** is a scalar `extern char X;`. As `char X[4]` it loses gp addressing
  under `-sdatathreshold 2`.
* **The old compiler's workarounds go under b52:** `volatile`, inline `nop`s and function-address
  aliases usually give way to `&&` chains assigned to an int, `?:` for a minimum, `bool` with `^`,
  and an assignment inside the condition.
* **Frame slots under b52 `-O4,p`:** named locals take the top slots in declaration order, then
  expression temporaries in the order they are created, then the locals of inlined functions. A
  class local assigned from a returned temporary (`r = f()`) takes the temporary's place.
* **Exception tables follow holders.** Retail's several ranges come from holder classes with real
  releasing destructors, scoped per block and closed where the release happened. An empty
  destructor with hand releases gives one range. Each retail destructor address is one holder
  class; holders that share an address are one class with several constructors.
* **A loaded value kept as the second operand of a multiply** is a local copied to itself before
  use, `x = p->v; x = x;`, which stops the load being folded back into the expression.
* **A macro that declares a class** leaves the trailing `;` to its call, `REF(Name);`. A call
  without one runs into the next declaration, and the source scanner then reads the macro as a
  function definition and drops the classes.
* **A 24-bit mask under b52** is `unsigned int` with `& 0xFFFFFF`; `dsll32` and `dsrl32` are how
  it masks a 32-bit value. A `ULL` constant adds extensions.

decomp-permuter's assembler rejects EE MMI opcodes (`opcode not supported on this processor:
mips3`), so a function containing `lq`/`sq` cannot become a permuter project.

## The relink — byte-identical (`make link`)

```sh
make link     # layout -> one object per unit -> ld -> compare against game.elf
```

```
linked .text: vma=0x100000 size=4541184   retail: 4541184
linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly
```

Every byte of the merged `main` section (`0x100000..0x554b00`) reconstructs from one
object per layout unit (the count grows with the layout; `make link` prints it, and the
from-source accounting is in `PROGRESS.md`): the functions compiled from C/C++, the `asm`
bodies, the remaining code and data units as retail bytes, and the **`jtbl` units** — a
`switch`'s jump table, which the
compiler emits into `.rodata`. Those are the one
thing that is not `obj(.text)`: `tools/layout.py` carves each function's table span out
of the enclosing data unit, and `tools/linkgen.py` places `obj(.rodata)` of the owning
function's object there, checking the size against the layout. Duplicate-named
table sections use the individual names described above. Without that the table
would be orphaned and the retail bytes emitted twice. This is the Ship-of-Theseus proof
for the whole build — it demonstrates that the compiler reproduces retail code for every
decompiled function, that the tiling is exact, and that **every cross-reference
resolves**: calls into not-yet-decompiled functions, absolute data globals, gp-relative
small data, and a switch's own case labels. From here, each new function is a mechanical
swap: write C, verify, relink. No new infrastructure.

Pipeline: `tools/layout.py` (disjoint tiling) → `tools/linkgen.py` (units → objects +
linker script) → `mipsel-linux-gnu-ld -G0 --no-warn-mismatch` → `tools/linkcheck.py`.

## The build runs on every core (`--jobs`)

`make check` and `make link` are thread pools over the compiler and binutils
subprocesses. The work is subprocess-bound — which releases the GIL — so it scales
until the cores run out. The timings below were measured on a tree of a
few thousand matched functions; on the full tree a cold `make check` takes about 47
minutes (see *Cached gates*), and the scaling is what this table shows:

| step | serial | 16 threads |
| --- | --- | --- |
| `make check` (split + coverage) | 2 m 40 s | ~40 s |
| `tools/linkgen.py --all` | 4 m 59 s | ~28 s |
| `make link` (layout + linkgen + ld + compare) | 5 m 51 s | ~1 m 10 s |

`--jobs` defaults to the core count; `--jobs 1` forces the serial path. Two things
make the pool safe, and there is one trap:

* **Thread-tagged scratch paths.** Scratch files live in the process's private folder
  (`cc.scratch_dir()`, removed at exit). Names keyed on the *process* alone would make two workers
  collide on the same file, so `check.py` and `linkgen.py` use `verify.TMP_TAG()` (pid + thread ident), the
  same convention `m2c_batch --jobs` uses ([`m2c-bulk.md`](m2c-bulk.md) §*The loop runs
  on every core*).
* **Build the objects before emitting the script.** A jump-table unit reads its owner's
  `.rodata` size, so `linkgen` is two phases: build every object (parallel, one output
  path per unit), then walk the layout in order to emit `link.ld`. The serial error
  report is kept by reporting the first failure in layout order.
* **The trap: never let the compiler create its output in a large directory.**
  `build/link/` holds ~34k objects, and wibo/MWCC writes its output through a
  *freshly-named* temp file in the destination directory — creating a new name in a
  35k-entry directory costs **~160 ms** against ~5 ms in an empty one (measured), which
  alone is ~94 s of `linkgen --all`. Compiling to `/tmp` and copying the finished
  object in (a plain write, ~0.03 ms) takes linkgen from 106 s to 28 s. `make check` is
  fast for the same reason: `verify.py` compiles into `/tmp`.

`ld` itself is ~42 s of `make link` and does not parallelise — MIPS has neither `gold`
nor `lld` — so it is the current floor.

### Six things that have to be right, each of which fails silently or misleadingly

1. **Exact-size objects.** GNU `as` rounds *every* section up to 16 bytes — an 8-byte
   unit becomes 16 and shifts the whole layout. Retail units are therefore made with
   `objcopy -I binary` (exact size, alignment 1). MWCC's `.text` is already exact-size
   (8, 8, 12 for small functions); only its 16-byte alignment needs overriding, which
   the script's `SUBALIGN(1)` does.
2. **`--rename-section …,contents`.** Without the `contents` flag the renamed section
   keeps its size but is treated as having **no data**, so every unit links as zeros —
   which looks exactly like a placement bug.
3. **A disjoint tiling.** The Ghidra dump has **33 overlapping function pairs**;
   `tools/layout.py` truncates the earlier unit so each byte is emitted once. Nine function
   starts are 4-byte but not 8-byte aligned, so units use `.align 2` (a per-unit `.align 3`
   would insert padding).
4. **`_gp` and `-G0`.** `__start` is `move gp, a0`, so `gp` is not in the instruction
   stream; it comes from `.reginfo` (`0x0055c870`). Without defining it the C objects'
   `R_MIPS_GPREL16` relocs fail with *"small-data section too large"*.
5. **Never `. = <va>;` inside an output section.** `ld` treats it as an offset from the
   section start and silently prefixes **1 MB of zeros** (the section comes out exactly
   0x100000 bytes too big, which is a very confusing symptom).
6. **Compare at the file offset.** `objcopy -O binary` pads to the VMA, so the naive
   extraction is 1 MB too long with a leading hole. `tools/linkcheck.py` reads the
   section header instead.

Cosmetic residue: MWCC objects carry `e_flags 0x20924001` (noreorder, 5900, eabi64)
while `objcopy -I binary` units carry `0x0`, so `ld` warns *"linking 32-bit code with
64-bit code"*; `--no-warn-mismatch` is required and the warning does not affect the
code bytes.

## Open items

1. **Full ELF relink.** The *section* relink is byte-identical (`make link`, above); this item
   is about the ELF container. The build proves the 4,541,184-byte main section; it does not
   rebuild the ELF headers, program headers and `.reginfo` around it, which a from-source
   `game.elf` would need (entry `0x100008`, the single merged section at `0x100000`).
2. **Naming.** The current counts — any recovered name versus a *semantic*
   name — are the "Recovered metadata" rows of `PROGRESS.md`. Most functions still carry an
   address-derived or role name; decompiling them is possible, organising the work by module is
   what naming buys. Re-run `scripts/sync_data.sh` before trusting `data/functions.json`'s
   symbol coverage.

## Open questions

- A call that fills a local, followed by a compare stored to a one-byte global: besides the missing
  `nop`, its best spelling under the default compiler leaves a register-only residual: retail keeps the local's address in `v1` and the result in
  `v0`, where the draft uses `a0`.
