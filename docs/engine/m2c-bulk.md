# Bulk decompilation with m2c

The shape templates of [`guard-family.md`](guard-family.md) cover the
550-member `sltu` guard family and the one-call wrappers. Every other function without C is beyond
shape templates and goes through [`m2c`](https://github.com/matt-kempster/m2c). This page records
**how the pipeline works, what it measured, and what has already been ruled out**; the live function
and byte counts are in [`PROGRESS.md`](../../PROGRESS.md), and the remaining work is per-function.

The candidates include functions Ghidra had only *labelled*, which `tools/split.py` promotes to real
ones: **883 with a frame prologue**, **1,804 vtable-referenced leaf stubs**, and
**613 `j`-thunk stubs**. The promoted stubs are m2c's best shape,
because a `j <accessor>; nop` stub is a one-call tail-call wrapper.

`m2c` is the right instrument because it has a **`mipsee-mwcc-c` target**: it knows the Emotion
Engine's CodeWarrior ABI and emits C in that idiom. It is vendored under the local tool directory
(`DW4_M2C_DIR`, default `local/m2c`) exactly like `decomp-permuter`.

## The pipeline

```sh
python3 tools/m2c_one.py 0x130060            # one function -> m2c's C
python3 tools/m2c_batch.py --report 200      # sample the yield, write nothing
python3 tools/m2c_batch.py --max-size 64 --write --worklist build/m2c_worklist.tsv
python3 tools/m2c_errors.py --all            # bucket a tier's compile failures by MWCC's message
```

`tools/m2c_one.py` builds the assembly m2c wants from the retail bytes (`config/SLUS-20836/symbols.txt` gives
the VA and size). Two fixups are required or it refuses the file:

* **registers need `$`** — objdump prints `lui at,0x0`, m2c expects `$at`;
* **branch and jump targets must be labels** — objdump prints `beqz v0,0x13008c`; the targets are
  recomputed from the encoded offset and rewritten to `.L<addr>` labels (inserted in the listing)
  or to a symbol name for `jal`/`j`.

`tools/m2c_batch.py` then runs m2c **in-process**. That is not a micro-optimisation: `m2c.py`
costs ~2.1 s of interpreter startup per function (0.5 functions/s), while importing `m2c.main`
once and re-invoking it costs **0.003 s** (~300 functions/s). The rest of the batch time is MWCC
compilation for verification.

The result is written to `src/` **only when `tools/verify.py` proves the bytes identical** — the
same fail-closed rule as `automatch.py`. m2c's draft is a starting point, never an authority.

One class of function is **skipped**: the 80 EE kernel syscall stubs (`tools/syscalls.py` →
`config/SLUS-20836/syscalls.txt`). They are Sony SDK assembly with no game C to recover (and MWCC cannot
spell `syscall`), so the worklist marks them `sdk` and the pass does not score them as compile
failures — see [`binary.md`](binary.md) §Kernel syscall stubs.

### The mechanical cleaner

m2c's output is not compilable C, and its addresses are in the wrong *form*:

| Problem | Fix |
| --- | --- |
| `s32`/`u8`/`f32`… | mapped to real C types |
| `?` as a return type | `int` |
| `?32` (an unknown type with a known *width*) | the width's C type (`char`/`short`/`int`/`long long`); leaving the digits after `?`→`int` produces an undeclared `int32` |
| `extern int FUN_x;` (a `FUN_<addr>` used only as an *address*, never called) | `int FUN_x();` — otherwise MWCC treats it as small data and reaches `&FUN_x` gp-relative, where retail uses absolute `lui`/`addiu` |
| `(long long) &X` (an address cast to 64-bit) | `&X` — the cast makes MWCC zero-extend the 32-bit address with `dsll32`/`dsrl32` before the `sd`; retail stores the sign-extended pointer |
| `*(int *)X = &FUN_x;` | `= (int)&FUN_x;` — a function address stored into a word slot (a vtable entry) is an int; without the cast MWCC rejects `int (*)()`→`int` |
| `func_0012CAF0`, `D_0055EBC0` | `FUN_0012caf0`, `DAT_0055ebc0` (the repo's naming) |
| a numeric address used as a **bitwise** operand (`0x5586C0 \| 0x20000000`, the PS2 uncached alias) | `(int)DAT_005586c0 \| 0x20000000` — the address is an int *value* here, not a pointer base, and a bare `DAT_x` is `char[] | int`, which MWCC rejects |
| `p += N`, `N + p`, `(void *)X + N` (a declared `void *`) | the `(char *)` form — MWCC rejects `void *` arithmetic in **every** spelling, with three different messages |
| `arg->unk4` on a `void *` | `*(int *)((char *)(arg) + 4)` (a general base-expression scan, since the base is often parenthesised, e.g. `(*(int *)DAT_x)->unk4`) |
| `*(expr)` with no type | defaulted to a word load |
| an assignment whose two sides disagree about pointer-ness (`void *t = *(int *)X`, `*(int *)X = &DAT_x[0]`, `int *t = (char *)p - 8`, `DAT_x[0] = &FUN_x`) | the *value* is cast to the target's type (`fix_pointer_types`, below) |
| `*(int (**)())X()` | `((int (*)())X)()` |
| `NULL` | `0` (no headers are included) |

**The address form cannot be decided from the source, so both are tried.** MWCC materialises a
*literal* address through a scratch register with `ori`, and a *symbol* address straight into the
destination with `addiu` — so whether `0x555048` should become `DAT_00555048`
depends on the encoding retail chose. The batch tries three spellings and keeps whichever verifies:

* `symbol` — every in-range address becomes `DAT_xxxxxxxx` (+ an `extern char DAT_xxxxxxxx[];`);
* `literal` — none do;
* `hybrid` — an address used as a *base* (`*(T *)ADDR`, `(T *)ADDR`, `ADDR->unkN`) becomes a symbol,
  a bare `= 0xADDR` stays a literal.

The range matters and is **not** the relinked section: the section is `0x100000..0x554b00`, but
`.sbss` starts at `0x554b00` and the first `PT_LOAD`'s memsz runs to **`0x58d280`**. `load_bounds()`
reads it from the program headers. Hard-coding the section end silently leaves every global above
it as a literal; a sweep with the section end hard-coded had 6,976 compile failures.

### Repairing a draft that does not compile

`repair` runs as one more variant of every candidate, so a draft that already compiles is unaffected
and `tools/verify.py` still decides each match. It turns m2c's `(bitwise T)` and `(unaligned T)`
annotations into C, casts a loaded word before calling it, fixes a double dereference, drops an `int`
stack placeholder beside a typed local, and gives a builtin's wrapper back the arguments it left in
registers. `repair_error` then follows the compiler: it reads the line a report blames, mends that line
and compiles again, for up to twelve rounds. A draft holding `M2C_ERROR` or `saved_reg_` uses an
instruction or register C cannot express, such as the MMI `qfsrv` and `pextlb`, and stays out of reach.

`expand_asm` rewrites instructions m2c does not know before it drafts: `adda.s` and `madd.s` become a sum of products, which C writes as `a + b + c * d`; `c1` with function 4 is `sqrt.s`; and `ldl`/`ldr` and `sdl`/`sdr` pairs become 64-bit moves, though they are really a whole-struct copy of a type under 8-byte alignment, so such a draft needs its struct written by hand.

`argument_variants` restores what m2c loses when a value only passes through registers, which retail states outright: an unused parameter, a value left in `a0` for the callee, a tail call's delay-slot argument, a word loaded but stored narrower, a byte offset left on an `int *`, which C would scale twice, a word widened for a 64-bit shift (`igObject`'s 23-bit reference count, 31 functions), and a global released through a local, which retail reads once (23 more). Nearly all near misses of one or two instructions had one of these causes, and random mutation found almost none of them.

`unrotate_loops` turns `loop: if (c) { ...; goto loop; }` back into a `while`, which MWCC lays out differently. `place_arguments` compares each call with the argument registers retail sets before it: m2c numbers arguments from `a0`, so `X(0)` may be a zero in `a3`, or `a0` may be a value passed through. These two improved 144 drafts and matched only 2, since a function with a rotated loop usually has other differences too.

`tail_call_drafts` writes a function that is straight-line code ending in a tail call without m2c: it evaluates the instructions and reads the argument registers, `a4`-`a7` and `f12` onwards included, at the jump. A parameter's type shows in the schedule. MWCC moves a load into the delay slot only when no conversion stands between the load and the argument, so `lbu` there means the callee takes `unsigned char`, and a `lw` done first means a conversion, which an enum parameter would explain.

## The EE ABI: `mipsee`, `a4-a7`, and the 168 registrar trampolines

The R5900 passes integer arguments 5–8 in the hardware registers **`t0-t3`**, not on the stack
(measured from MWCC itself). m2c has two MIPS arches and neither models that by
default: the `mips-mwcc-c` target selects `MipsArch`, whose integer argument slots stop at `a0-a3`
(so a five-argument call loses its last argument), while the EE arch selected by `mipsee-mwcc-c`
(`MipseeArch`) names the extra slots `a4-a7` — registers the R5900 does not have, and which the
disassembly therefore never mentions. The pipeline feeds m2c the **`mipsee-mwcc-c` target** and
renames `t0-t3` to `a4-a7` in the assembly (`m2c_one.asm_for(ee_abi=True)`), which is the whole
bridge: m2c then sees arguments 5–8 instead of an unmodelled temporary.

The EE pipeline reaches functions `mips-mwcc-c` cannot:
they are mostly **100–149 bytes and calls `FUN_002fe9c0`** — the per-class MetaObject registrar
trampolines (T1) whose registration call takes **11 arguments**, of which a four-register
model sees four.

Retail has 1,075 `jal FUN_002fe9c0` sites in 484 distinct caller functions (some register several classes).
The 100-byte ones need the EE ABI; the 108–116-byte ones pass a **function pointer** as the 9th
argument and need two more cleaner rules: m2c declares an address-only `FUN_<addr>`
symbol `extern int FUN_x;` (a small-data object, so MWCC reaches `&FUN_x` gp-relative) and casts the
address to `long long` (so MWCC zero-extends with `dsll32`/`dsrl32`). Declaring it a *function* and
dropping the cast reproduces them. The
other sites sit in unclaimed Ghidra gaps as `LAB_` labels — the gap-label
promotion adds them (§*883 functions Ghidra only labelled*).

The EE arch also models float arguments as `f12-f19` rather than `f12-f15`, which is what the
few non-registrar matches (e.g. `FUN_00182420`, three pointers plus a float parameter) need.

## 883 functions Ghidra only labelled

`data/functions.json` is Ghidra's *function* list, but Ghidra also records addresses it knows only as
labels — `LAB_<addr>`, branch targets and referenced stubs it never promoted to function objects.
When nothing branches into one and nothing takes its address as code, it stays a label and falls in
the **unclaimed gap** between two functions: absent from `config/SLUS-20836/symbols.txt`, invisible to the
split, impossible to decompile. The 592 gap-held class-registrar trampolines are exactly this:
each alone in its own 116–404-byte gap, with `LAB_001301d0` sitting on its
`addiu sp,sp,-48`.

`tools/split.py` has a **third derivation rule** (beside the delay-slot and jump-table-body rules)
that promotes such a label when it looks like a function start — a non-leaf frame
prologue `addiu sp,sp,-N` that is *not* reachable by fallthrough (the preceding word is padding, or
the previous function's `jr ra` / its delay slot) — and sizes it to the word after the last `jr ra`
before the **next label of any kind** (bounding by the next *promoted* start would swallow a sibling
stub). Result: **883 promoted, 15,974 → 16,857 functions, +131,532 bytes**. Nothing moves — the newly
claimed bytes were already linked as raw data — so `make link` stays **byte-identical** and the split
round-trips. Decompiling them reproduces the registrars among them, plus a few others.

The 291 non-registrar promotions are real functions, not data — `FUN_0010a418` calls `0x10a558`,
`FUN_001308c0` calls the reflection driver `0x2fdf40`. The registrars need one further cleaner
rule: the `(long long)` cast also has to come off
a **data** address (`(long long) &DAT_x[0]`), not just a function one. With the rule limited to
function addresses 528 of the 592 registrars match; generalised to any address-of, **592/592**.

## The vtable-referenced leaf stubs

The frame-based rule above cannot see a *leaf* function: a leaf has no frame, and its stubs are the
ones a class vtable is full of — the 8-byte `jr ra; li v0,N` getters, the 8-byte `jr ra; nop`
default methods, the `lui at,hi; jr ra; lw v0,lo(at)` accessors, and the 12-byte bodies that
tail-call a shared implementation with `j`. Ghidra labels each `LAB_` but never makes it a function,
because nothing *branches* into it — only a vtable holds its address, and Ghidra follows branches
and `jal`, not data references. So `tools/split.py` has a **second promotion pass**,
`promote_data_labels`, whose evidence is the data pointer instead of the prologue:

* the label sits in an unclaimed gap, and its address appears as a 4-byte little-endian word in the
  image (a vtable or function-pointer table holds it as code);
* the bytes from it form a **leaf body** — exactly one terminating `j`/`jr`, where the `jr` may be of
  any register (so a `jr t9` tail call counts) and a plain `j` counts, and there is no prologue
  anywhere in the body;
* it is not reachable by fallthrough (the preceding word is padding, or a `jr ra` / its delay slot);
* its size runs to that terminator's delay slot, bounded by the next ***plausible start***, not the
  next label of any kind — a function with an internal loop carries branch-target labels of its own,
  and those must not cut its body short (bounding by any label hides `igMetaField`'s `+0xd0`
  byte-swap at `0x2fd170`). Sibling stubs are referenced like the first, so they do bound it.

A body with two terminators is left alone: it is either a merge of two stubs or a real multi-return
function, and either way ambiguous. Result: **1,804 promoted, 16,857 → 18,661 functions, +42,872
bytes**, verified 1,804 added / 0 removed / 0 changed / 0 overlaps with an existing function or with
one another. Every claimed byte was already linked as raw data, so `make link` stays
**byte-identical** and the split round-trips. A promotion makes the coverage percentage *fall*,
because the denominator grows by real functions while the matched count is unchanged.

## The `j` thunks of the class registrars

`promote_j_thunks` (`tools/split.py`) finds the `j <accessor>; nop` stubs from the literal a registrar
passes. A class registrar builds all nine register arguments at once, so `lui t0,hi` and its
completing `addiu t0,t0,lo` can sit up to 11 instructions apart. The literal search therefore needs a
window of at least 12 instructions; it uses 16. With the default 8 most registrar thunks stay
unclaimed. `scripts/seed_names_metaobject.py` resolves a thunk from its bytes, so it names the accessor
and `thunk_<accessor>` whether or not the thunk already has a symbol, which keeps it idempotent.

## What each fix closed

Each fix below closed a class of candidates, and each accepted function is still proved independently.
The yield of a full sweep drops as the reachable functions are taken. The totals are in [`PROGRESS.md`](../../PROGRESS.md).

- the first mechanical cleaner
- address range (0x58d280) + member-access fixes
- `%hi`/`%lo` **data symbolization** (see the metadata section)
- `%%lo` escaping fix + 727 delay slots restored
- the `%lo` sign double-correction fix — no other change
- **gp-relative small data symbolized** (`%gp_rel(GPR_…)($gp)`), narrow member widths kept, and the `DAT_x` declaration deduplicated by *declaration* rather than mention
- **the EE ABI**: `mipsee-mwcc-c` + the `t0-t3`→`a4-a7` rename, plus the `addiu $r,$gp,disp` gp-address fix and the `?32` width fix
- **the registrar function-pointer rules**: `extern int FUN_x;` → `int FUN_x();` and `(long long) &X` → `&X`
- **the gap-label promotion**: `split.py` promotes code-shaped `LAB_` labels in unclaimed gaps to functions, with the EE/registrar cleaner
- **the word-slot cast**, on a full sweep of the 16,857-function set with the EE ABI and the cleaner rules above
- **the member-access rewrite** — chains, member access on a call result, slot calls and value members (§*The member rewrite folds the innermost member first*)
- **`void *` arithmetic in its other forms** — a bare `temp = arg0 + 0x3E8` and a slot call through a dot member
- **the `%lo` register-lifetime rule** — a `lui` register's *later* base uses complete a `%lo` too, not only the first (§*A `lui` register keeps its `%hi` for its lifetime*)
- **the leaf promotion** with candidate selection through `tools/units.py` — a flat `os.listdir(src/unmatched)` would re-sweep the named functions the module tree moved
- **the cleaner's casts made to agree with the types m2c already declared** (`fix_pointer_types`: pointer and function-pointer targets, stores through `*(int *)`, pointer arithmetic — §*Casts agree with the types m2c declares*)
- **the store-width class**: `fit_widths` decodes m2c's `temp_sN` local names to their register as well as `argN`, so an untyped *store* through a saved-register local keeps retail's `sb`/`sh`/`sd` (§*A store through a local takes its width from retail*)
- **the C++ virtual-call transform**: `virtualize_calls()` re-spells m2c's vtable call as a C++ virtual call in a `.cpp` variant (§*Virtual calls are C++, not C*)
- **the virtual-call transform's four details**: the `_vcall_obj` regex order (the member-load base shape), `this`-vs-explicit-first-argument, `(T (*)(...))` casts and `sp<hex>` declarations (§*Virtual calls are C++, not C*)
- **nested virtual calls**: `_vc_rewrite` recurses into argument lists (and splits them at top-level commas), so a vtable call inside another call's arguments is rewritten too instead of staying a plain `jalr v0` (§*Virtual calls are C++, not C*)
- **four-byte struct-returning virtual calls**: the statement-level variant re-types the stack word, assigns the real C++ class return, and reads its `.w0`, producing the hidden-return-buffer ABI (`a0` buffer, `a1` `this`); it also recognises m2c's redundant explicit `this` after the hidden buffer
- **argument-preserving C++ one-call wrappers**: restore the enclosing function's second argument that m2c dropped from the callee with no prototype, and compile the wrapper in C++ mode so MWCC keeps retail's framed call instead of a C tail call
- **restore m2c's dropped/gap call parameters** (`tools/restore_dropped_args.py`): rebuild each parameter list as register slots `0..maxIndex`, keeping the recovered `argN` and filling the holes with unused dummies, so the recovered value occupies the register retail uses
- **the virtual-call `this`-strip normalised** (`tools/m2c_batch._vc_obj_key`): m2c spells the object as `((char *)(X) + 0)` in the vtable base but as the bare `X` in the explicit first argument, so a textual `this`-strip misses and the object is passed twice
- **the 64-bit arithmetic class**: a function whose retail body is `ld`/`lwu` + `dsubu` needs the *result* type `long long`, not only the load widths — the `width` shape alone leaves `lw`/`subu`
- **the low-diff tier** with the virtual-call transform and the dropped-argument shapes (`leadcall`, `width`)

The yield is strongly size-dependent, and the clean shapes are a minority of the work: the simplest
call-and-compare leaves (`FUN_001002a0`: `return dpcmp() == 0;`) match first try, and small functions
close far more often than large ones.

Restoring the delay slots (§*727 functions ended one instruction short*) removes most m2c failures, so
most of them are not m2c's fault. What remains are the large MMI-heavy bodies
(`lq`/`sq`, 128-bit moves) m2c does not model.

The queue (`build/m2c_worklist.tsv`, `name, va, size, status, diffs, mode`) is what per-function
work starts from. Its `status` separates `compile` (the best spelling does not compile),
`mismatch` (with the number of differing instructions in `diffs`) and `sdk` (the EE kernel stubs,
skipped). It is scratch written by a sweep, so it describes the tree and the pipeline of that sweep
and goes stale for every function matched afterwards.

Regenerating the pipeline's scratch artifacts (they live in `build/`, which is not committed):

```sh
python3 tools/split.py --symbols && python3 tools/split.py     # config/SLUS-20836/symbols.txt + asm/
python3 tools/jumptables.py --write                           # config/SLUS-20836/jumptables.txt
python3 tools/layout.py                                       # config/SLUS-20836/layout.txt
python3 tools/m2c_context.py                                  # build/m2c_context.c
python3 tools/m2c_batch.py --max-size 100000 --write --jobs 8 --worklist build/m2c_worklist.tsv  # ~5 min
```

## m2c drops an argument the body never reads

m2c names a recovered parameter **`argN` by its EE register index**, and it silently drops
any argument the retail body never reads: a *leading* one (a wrapper whose first touched
register is `a1` is recovered as `(int arg1)`, and MWCC then passes it in `a0`), or a *gap*
(a function that reads `a0` and `a2` is recovered as `(void *arg0, int arg2)`, and the `arg2`
value lands in `a1`). The wrapper then misses by one or two instructions — the shape of a
large fraction of the near-miss tiers.

The fix is mechanical and lives in **`tools/restore_dropped_args.py`**: take a draft
from `build/m2c/`, rebuild each parameter list as slots `0..maxIndex`, keep the recovered
parameter in its own slot, fill every hole with an unused `int dummyN`, and re-verify. A
`.cpp` is chosen when the draft carries C++ syntax (the virtual-call transforms emit
`class `/`extern "C"`), because the extension selects MWCC's front end. The same pass closes a 64-bit-load cast
(`FUN_0038f480`: retail `ld`, m2c `lw`, needs a `(long long *)`) and two argument-preserving
wrappers that forward all of their own arguments (`FUN_0029cb48`, `FUN_0032cf50`).

A wrapper that shifts its argument registers and tail-jumps (the 12-byte form
`move a0,a1; j T; move a1,a2`) is the same defect: it drops its own first argument and forwards the
rest. The fix is an unused leading parameter: `void f(int unused, int a, int b) { T(a, b); }`. A vfunc
of this shape keeps the repository's flat extern-C symbol name and must be a `.c` file, because C++
mode frames the call at 32 bytes instead of the 12-byte tail jump. Examples: `FUN_0016cdd0`,
`FUN_0015ad30` (forwards 7 of 8), `FUN_00328f70`.

m2c also loses an argument set up in a delay slot: it decompiles `j X` with a setup instruction there
as a call to `X` without that argument (the same for `addiu`, `li`, `lw` and `move`). For a `void *`
base it widens a narrow store to a word, which MWCC then spells `dsll32`/`dsra32`/`sw`. For the 8-byte
functions these are `tools/automatch.py` templates (`setter` and `fget` widths, `fset`, `rbase`,
`tsetup`), which catch such shapes when a later promotion adds them.

## `%lo` halves are already sign-extended

`m2c_one.asm_for` builds an absolute address from a `lui`/`addiu` (or `lui`/`lw`) pair. objdump
prints an `addiu` immediate **already** sign-extended (`addiu v1,v1,-24064`) and a load displacement
too (`lw v0,-8392(at)`), so only the raw 16-bit `ori` case needs the correction
`(hi << 16) + (off - 0x10000 if off & 0x8000 else off)`. Applying it to all three names every address
whose low half has bit 15 set 0x10000 too low — and `verify.py` resolves a symbol by the address in
its name, so those relocations are patched to the wrong place and **can never match**. About a third of
the candidate functions touch at least one such global, which makes this the largest
single result on this page.

The A/B is unambiguous: over two equal samples from one address region, with one cap on size, functions
with a bit-15 `%lo` reference matched after this fix and the control sample without one did not,
and per function: running the *same* assembly with only the double-corrected names substituted in
fails `FUN_00130310`, `FUN_00130440`, `FUN_00130f60` and `FUN_00131160`, all of which match with the
correct names.

The convention lives in exactly one place, `automatch.eff_addr(hi, off, is_addiu)`. The lesson
generalizes: **a symbol name that encodes an address is load-bearing here**, so a naming bug is a
silent relocation bug — anything that synthesizes a name from an address needs a test that
round-trips the address back out of the name.

## A `lui` register keeps its `%hi` for its lifetime

A register loaded by `lui $r,HIGH` **keeps** that high half until it is written again, and
*every* load/store that uses it adds the `%lo` of the object being addressed. Pairing a `lui`
with only the first use inside a 4-instruction window leaves a second
use after a branch numeric, and m2c then adds that displacement **on top of** the
named `%hi` base. `FUN_00270db0` is the minimal case:

```
270DB4  lui $v0, %hi(DAT_004a927c)     270DBC  sw $zero,%lo(DAT_004a927c)($v0)
270DC8  lui $v1, %hi(DAT_004a9280)     270DCC  sw $a0,-28036($v0)   <- the same object,
                                         reached across the `bnez`
```

With first-use pairing m2c emits `DAT_004a927c.unk-6D84` — the base `0x4a927c` minus `0x6D84`,
i.e. `0x4a24f8`. The address is wrong, so no C can match. A detector finds
such a use in about 1.2 % of the candidates.

The pass therefore tracks `hi_by_reg` for the register's **lifetime**: every later base use
completes a `%lo`, and any write to the register clears it. Two ordering details matter,
and each one is a way a naive lifetime rule is worse than first-use pairing:

* the first-use search must recognise the **`addiu $dst,$dst,lo` completion before treating
  that same instruction's write as a kill.** Testing the write first leaves every jump-table
  base numeric, and m2c then refuses the dispatch with `Unable to determine jump table for
  jr` — **133 functions** go from working to m2c failures;
* it must tolerate **`addu $dst,$dst,$idx`** between the `lui` and the `lw %lo($dst)` — the
  classic indexed switch form — or 13 more dispatch functions fail the same way.

With both, the lifetime-vs-first-use m2c-failure A/B is **0**, the missed-`%lo` detector reads **0**,
and what the rule closes was a compile failure under first-use pairing (compile tier
3,913 → 3,866). Naming a `%hi` base also reaches a **latent crash in the vendored m2c**:
`m2c/evaluate.py:fold_shift_bgez` simplifies a `bgez`/`bltz` over `x << n` to
`!(x & (1 << (31 - n)))` with no bounds, so a shift of 32 or more raises
`ValueError: negative shift count` and aborts the decompile. Naming a `%hi` base makes m2c
fold a register to a constant it otherwise leaves symbolic, which is what reaches the buggy
folder. Not folding an out-of-range shift is always sound (`handle_bgez` falls back to
`expr >= 0`), and because `m2c` is fetched rather than committed the guard lives in our own
wrapper, [`../../tools/m2c_compat.py`](../../tools/m2c_compat.py), imported by
`m2c_batch.run_m2c`; `tools/m2c_run.py` is the subprocess equivalent for `m2c_one.py`.
Without it, the naming rule alone turns 133 working functions into aborts.

## Decompiler corrections, contexts and projections

### Combat signed reciprocal recovery

The attack-category quotient in the combat helpers uses signed multiply-high
by `0x68db8bad`, an arithmetic shift by 12 and addition of `(u32)x >> 31`.
The complete expression is signed `x / 10000`, rounding toward zero. Upstream
m2c folds the partial product and shift into division before seeing the
correction, then emits `x / 10000 + ((u32)x >> 31)`. This is wrong for negative
inputs: `-10000` becomes zero instead of minus one.

`tools/m2c_compat.py` keeps reviewed partial expressions intact until the complete
32-bit signed pattern is available. The finite list covers divisors 5, 10,
20, 40, 50, 80, 100, 400, 1000 and 10000 from the full combat dispatcher.
Logical sign-bit addition and equivalent arithmetic-sign subtraction are
recognized; a different numerator, a wrong correction, an unsigned product or
a 64-bit shift cannot trigger them. Both the in-process batch runner and the
subprocess wrapper receive the correction. Unmerged partial expressions remain
explicit multiply-high operations rather than an incorrect completed division.

Run `python3 testing/test_m2c_compat.py`. Its integer proof checks both endpoints
of every `/10000` constant-quotient interval across all signed 32-bit inputs.
For every reviewed pair, let `S = 2^(32+shift)`, `M*d = S+E`, and
`Q = floor(2^31/d)`. The tests establish `E > 0` and
`Q*E + M*(d-1) < S`. Writing `|x| = q*d+r` bounds the residual for all inputs:
positive values use floor, negative values use ceil plus the sign correction.
AST near-misses and synthetic MIPS pipelines test the recovery rule separately.
m2c-dependent tests skip
when the local decompiler is absent. This corrects recovery semantics; it does
not establish a byte match for a combat function.

### Full combat ABI context

`python3 scripts/gen_combat_context.py` writes `build/combat-context.c` for m2c's
`--context` argument. It combines the generated reflected GAMERAM receiver with
reviewed call slots, the unused middle callback argument, matrix/vector widths,
`f12` float append and skill/resistance table layouts. m2c contexts do not
process include directives, so this generator emits a flat definition rather
than maintaining a second receiver layout by hand.

These are decompiler semantic types with four-byte reference words, not claimed
original typedef spelling. The output is analysis input; a draft still requires
standalone declarations, byte-correct pointer strides, control-flow cleanup and
the full instruction/table oracle before it can enter `src/`. See the
[combat recovery boundary](../systems/combat-damage.md).

### Explicit call-result projection

The optional `--materialize-calls` mode gives every nonvoid call result an
explicit temporary at its translation site. This exposes lifetimes that nested
call expressions can hide. The ordinary source rendering stays unchanged.

```sh
python3 tools/m2c_one.py 0x3fca10 --context build/combat-context.c --materialize-calls
python3 testing/test_m2c_materialization.py
```

`tools/m2c_run.py` consumes the flag before invoking the vendored parser.
In-process callers can use `m2c_compat.materialize_function_calls()` around a
single serial `run_m2c` invocation. Nested scopes and exceptions restore the
previous translator. Its diagnostic counter includes inference passes and is
not a count of distinct retail calls. Four tests check call count/order,
void-call handling, restoration and subprocess parity.

For the combat callback at `0x3fca10`, default output is the ordinary rendering;
opt-in output equals the separately reviewed materialization experiment. The
mode is a source-recovery aid. Access widths, arithmetic and ABI projections
still need original-instruction review, and banking requires the full code and
switch-table oracle. See [combat draft recovery](../systems/combat-draft-recovery.md).

### Named calls and consumed remainders

`--materialize-boundaries` is an alternative to `--materialize-calls`. It gives
named nonvoid calls explicit results and captures modulo expressions at consumed
MIPS `mfhi` instructions. Indirect calls remain nested, so a virtual RNG call
and its bound can remain one expression. An unused HI value from a quotient-only
`div` does not create a remainder temporary. The two flags are mutually exclusive.

```sh
python3 tools/m2c_one.py 0x3fca10 --context build/combat-context.c --materialize-boundaries
```

The equivalent serial API is
`materialize_function_calls(direct_only=True, remainders=True)`. Named calls
unwrap `AddressOf(GlobalSymbol)` and require a function type; a global function
pointer is still indirect. Eight tests cover both projections, including named
calls, bounded virtual calls, unused remainders and conflicting flags. Full
callback output reproduces the reviewed private experiment; default and
all-call output are unaffected. This is a diagnostic projection, subject to
the same complete code/table verification requirement.

## The loop runs on every core — `--jobs`

The sweep is not CPU-serial: the work is mostly `wibo`+`mwccps2` **subprocesses**, which
release the GIL, so a `ThreadPoolExecutor` scales it. `m2c_batch.py --jobs N` scores N
candidates concurrently and is **4.0× on 8 threads** (3,000 candidates: 149 s → 37 s; 16
threads gave no more than 8). The worklist is unchanged by it — `map` preserves candidate order and
a worker only returns, never appends — and `jobs=1` is the default.

Two things make that safe and fast, and the second is the one that is easy to misread:

* **No global-stdout capture.** `m2c.main` is not thread-safe, and capturing its output with
  `contextlib.redirect_stdout` rebinds the **global** `sys.stdout`: a progress
  `print` from the aggregating thread lands inside a worker's `StringIO` and is spliced
  into the m2c draft, so 1–2 rows out of ~1,100 flip to `compile` *non-deterministically*.
  `_ThreadStdout`/`_capture_stdout()` route writes through a thread-local buffer; m2c itself
  is serialised by `_M2C_LOCK` (it also mutates `sys.argv`).
* **The GIL-bound half dominates.** A thread pool reaches only **1.5×** if
  `verify_one` re-reads and re-parses the 4.5 MB ELF, `config/SLUS-20836/symbols.txt` and
  `config/SLUS-20836/jumptables.txt` on **every** call (up to three times per candidate).
  `functools.lru_cache` on `read_elf`/`load_symbols`/`load_jumptables` speeds the sequential
  sweep up too and takes the parallel one to 4.0×. `verify.TMP_TAG` is a function for the same
  reason: a module constant freezes the importing thread's id, so every worker would write
  the same scratch path.

Documented command: `python3 tools/m2c_batch.py --max-size 100000 --write --jobs 8 …`.
`tools/m2c_errors.py` runs sequentially.

## Type metadata: what the repo has, and what it is worth

m2c's `--context` is where recovered types would be expected to pay off. The repo has three
candidate sources, and one of them is empty:

| source | contains | verdict |
| --- | --- | --- |
| `data/reflection.json` | 659 classes with fields, 3,680 fields with **byte offsets** and `ig*MetaField` types, and each class's **handle address** (`0x55ebc0` = `igVisualContextAttrDefaultManager` — the guard family's global) | used |
| `data/vtables.json` | 478 vtables, 1,286 named vfuncs with their owning class | used (`--vtables-protos`) |
| `data/functions.json` signatures | **all 15,974 are `undefined f()`** — the dump never recovered parameters | useless |

`tools/m2c_context.py` builds `build/m2c_context.c` from the first two: 659 flat structs
(absolute offsets, gaps as `char padN[]`, widths from the *same* `NOMINAL` table
`scripts/apply_reflection_names.py` derived empirically, so the layout is exact), 659
handle globals, and optional vfunc prototypes. `--globals array|pointer` controls how the
handle globals are declared.

**But the context is inert unless m2c is fed *named* globals.** From raw `lui`/`lw` pairs m2c
invents an anonymous literal (`*(void **)0x55EBC0`) that no
context declaration can ever match, and the recovered types measure as a complete
no-op. The asm generator therefore emits `%hi(SYM)` / `%lo(SYM)` (what spimdisasm does), and *that*
is where the win is. A/B on the same 300 unmatched functions, same cleaner:

| pipeline | match | compile-fail | mismatch |
| --- | --- | --- | --- |
| raw `lui`/`lw` | 0 | 169 | 131 |
| `%hi`/`%lo` symbolized | **3** | 218 | 79 |
| symbolized **+ context** | 2 | 219 | 79 |

Two readings:

* **Symbolization is the real improvement.** It converts 52 compile failures into
  *comparable* candidates (131 → 79 mismatches), and it makes the output readable —
  `FUN_00100bc0` came out as `extern void *DAT_00555048[4]; … temp_v1 = DAT_00555048[0];`
  instead of `*(void **)0x555048` with pointer casts the compiler rejects.
* **The context is neutral** (2 vs 3 is noise at n=300), and it is structurally narrow:
  only 1.7 % of the candidates read a class handle global at all.
  Matching is decided by the *instructions*, and m2c already recovers those, including the
  field offsets (it printed `unk24` for `+0x24` without any metadata). The recovered types
  mostly change how the C is *spelled*, not what it compiles to.

  **The `void *` compile failures are not a context problem either.** They are neither
  about parameter types nor about anything m2c fails to recover: the drafts *declare* the
  recovered types, and a cleaner that casts against them is what fails to compile
  (§*Casts agree with the types m2c declares*: 81 functions, compile tier 3,913 → 1,258).
  "The type names in the C do not match" and "the types are unknown" are
  different problems, and only the second one is a context problem.

The named globals also need the **array trick** the guard family needed:
m2c emits `extern void *DAT_x;`, which is 4 bytes and therefore small data → gp-relative
`lw`, where retail uses absolute `lui at`/`lw`. The cleaner rewrites the declaration to
`extern void *DAT_x[4];` and the uses to `DAT_x[0]`.

**Conclusion:** the metadata is kept — it makes the generated C readable, it is a
prerequisite for any context work, and `--vtables-protos` is one flag away — but its
measured value for matching is in symbolizing the data references, not in typing them.

## 727 functions ended one instruction short

m2c refuses **728 functions (4.6 %)** of Ghidra's function list with
`Last instruction is missing a delay slot`. They are
not m2c's fault: Ghidra's function boundaries cut them one instruction short. `FUN_00100240` ends at
`jr $ra` (0x100284) and the `addiu sp,sp,16` that the hardware requires after it sits at 0x100288 —
inside the *next layout unit*. The link does not notice, because those bytes are emitted as a data
unit and the section still links byte-identically; but such a symbol is not a function, no C can
match it, and m2c cannot read it.

`tools/split.py` grows a function by one delay slot when its last word is a
branch/jump (`is_terminator`: opcodes 1–7, or `jr`/`jalr`) **and** the next symbol does not start
inside that word (2 of 728 overlap, and `tools/layout.py` already resolves those). 727 are
extended; on Ghidra's 15,974 functions that takes code bytes 3,174,984 → 3,177,892 and the relink's
layout units 28,260 → 27,998, with the function count, the split round-trip (15,974/15,974) and the
byte-identical `make link` unchanged.

No matched function is affected (none is among the 728 — a matched function cannot be,
since its compiled form contains the delay slot). This is a derivation rule in `split.py`, so
`data/functions.json` stays the raw Ghidra dump and regeneration keeps the rule.


## Switch dispatchers: case bodies and jump tables

Ghidra stops at a `switch`'s indirect `jr $v0` and never follows the jump table, so the case
bodies — and the shared `jr $ra` epilogue they all branch to — are left in the *unclaimed* gap
before the next symbol. On its function list **155 functions (401,160 bytes) branch outside their
own symbol, and a function whose source matches never does.** `FUN_00204840` is recorded as 52 bytes, just

```
sltiu at,a0,14 ; beqz at,0x204904 ; move v0,zero ; lui v0,0x4e ; sll v1,a0,2
addiu v0,v0,21168 ; addu v0,v1,v0 ; lw v0,0(v0) ; jr v0
```

and its 14 case bodies plus the epilogue sit at `0x204874..0x204910` attributed to nobody (2,556
out-of-range targets land in such gaps). m2c rejects a fragment like that outright:
`Cannot find branch target .L00204904`.

`tools/split.py` grows the symbol to the next one when every out-of-range **pc-relative**
branch lands in the unclaimed gap (none inside another function; growth capped at 8 KB). 151
functions grow by 15,908 bytes. With the delay slots, that is 878 functions given their correct
extent (code bytes 3,174,984 → 3,193,800 on Ghidra's 15,974 functions); the split round-trips,
`make link` stays **byte-identical**, and no matched function is affected (a matched function
cannot branch outside itself).

With the extent corrected m2c **parses 104 of the 151**, but a dispatcher's table is something m2c
cannot see unless the assembly carries it. Its error states the contract exactly:

> Unable to determine jump table for jr instruction … There must be a read of a variable before the
> instruction which has a name starting with `jtbl`/`jpt_`/`lbl_`/`jumptable_`.

So `tools/m2c_one.py` emits the table: it detects the base address, reads the entries from the
retail image, names the symbol `jtbl_<addr>`, inserts `.L<case>` labels, and appends a
`.section .rodata` block of `.word .Lcase` lines (m2c's own test suite shows this format).

**The table is part of the match.** A compiler-generated switch table goes to
`.rodata`. A verifier that compares only the symbol's bytes in `.text` would call a switch function
matched while never looking at its table, and a linker that places only `obj(.text)` would orphan
the table (breaking byte-identity). So
`tools/verify.py` compares the compiled `.rodata` against the retail bytes at the retail table
address (relocation-aware — `R_MIPS_32` is a `REL` reloc, so the addend is the word itself, and the
dispatcher's `HI16`/`LO16` reference MWCC's anonymous local table symbol `@21`, resolved by placing
our `.text` at the function VA and our `.rodata` at the table VA). An object that carries `.rodata`
for a function with **no** recorded table is a hard failure, so a table cannot go
unchecked. `tools/jumptables.py` recovers the tables from the dispatcher shape into
`config/SLUS-20836/jumptables.txt`; `tools/layout.py` gives each function's table span its own `jtbl` unit, and
`tools/linkgen.py` places the compiled `obj(.rodata)` there (retail bytes while the function has no
C), requiring the sizes to match. `make link` is **byte-identical** with the
switch functions compiled from C — the tables really do land at 0x4ea200, 0x4eb250, …

| | |
| --- | --- |
| tables | **180** (18 functions have 2–9 tables, MWCC 16-byte-aligns each) |
| entries | 2,694 words = 10,776 bytes; 11,044 bytes of span |
| of the 151 functions `split.py` grows | 47 have a table; the rest are grown for loops / other out-of-range branches |
| match once the table is visible | **3** (408 bytes) — `FUN_0023cd00`, `FUN_00204150`, `FUN_0024a700` |
| the other 135 | **122 compile-fail / 14 mismatch / 2 m2c-fail** |

Two readings:

* **The table fixes m2c's *parse*, not the match.** It emits a complete, readable `switch`
  (m2c's output for `FUN_0024a700` is the retail case set), and the tier's composition barely
  changes: 107 of the 138 candidates contain `lq`/`sq`/`ld`/`sd`, 89 declare a `void *temp_*`, and
  the top compile errors are int→`void *` conversions, the undeclared `s128` and the
  `arrayize_globals` redeclaration. Declaring those `void *temp_*` locals `int`
  turns compile failures into mismatches and produces no matches, so it is not applied.
  This is the **spelling law** this page keeps measuring: a fix to how the C is spelled turns compile
  failures into comparable candidates, not matches.
* **One source idiom is real.** m2c's `switch (arg0)` over cases 32..41 compiles its index
  adjustment as `addi`, where retail has `addiu` (0x2482ffe0): MWCC lowers a bare switch over int
  constants to the *signed* subtract even when the parameter is unsigned. Writing the adjustment
  explicitly — `switch ((unsigned)(arg0 - 32))` with cases 0..9 — reproduces retail
  (`FUN_0024a700`). Only 1 of the 14 mismatches is this, so it is a hand fix, not a template.

## `loosen_prototypes` must not match a call statement

`loosen_prototypes` rewrites m2c's callee declarations to `T f();` so that every call site is
accepted. In its pattern the name must be separated from the type tokens by whitespace or `*`
(`[\s*]+`). A pattern that ends

    ^(\s*(?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*\s*\**\s*)([A-Za-z_]\w*)\s*\([^;]*\)\s*;\s*$

lets `([A-Za-z_]\w*)` be split. For the call statement `WatchDma(arg3);` the match is
group(1) `    FUN_00102`, group(2) `d08`, so the rewrite replaces the whole line with
`    WatchDma();` — **the argument is deleted**. Every bare call statement in every candidate
loses its arguments, and because this is a text pass there is no error to notice: the candidate just
compiles to one or two instructions that do not match retail.

That is exactly the shape of the "cheapest" tier. `FUN_001033f8` (0x001033f8, 52 bytes) then differs
in one word — retail's `move a2,a3` against our `nop`. The function is

```c
int FUN_001033f8(void *arg0, unsigned int arg1, int arg2, int arg3) {
    if (arg2 == 1) {
        return (unsigned int) *(int *)((char *)arg0 + 16) < arg1;
    }
    WatchDma(arg0, arg1, arg3);
    return 0;
}
```

and with the call's arguments kept every word agrees. A call statement has no type
token, so it cannot match the `[\s*]+` form, and the declarations the pass is meant to touch still do
(`int FUN_x(int);`).

Committed `src/` files that contain a bare argument-carrying call statement are not exposed to a
cleaner defect of this kind: every one was verified before it was written, and `clean()` is never
applied to `src/`. `make check` is what keeps them honest. A worklist written by a sweep with such a
defect has `status`/`diffs` columns computed on corrupted candidates, and is regenerated with the
same sweep command.

## A global is declared once

`clean()` adds `extern char DAT_x[];` for a numeric address, while m2c's own
`extern void *DAT_x;` for the same address (seen through `%hi/%lo`) is arrayized above to
`extern void *DAT_x[4];`. MWCC rejects the pair outright:

    identifier 'DAT_0055f5d0' redeclared
    was declared as: 'char[]'
    now declared as: 'void *[4]'

so the cleaner emits its declaration only for a symbol the draft does not already *declare*.
Declared twice, the pair is the top blocker of the compile-failure tier: of a stratified
120-row sample of that tier, **104 compile** (and are compared) once each global is declared once,
and 16 still fail. The
diff counts stay large — the spelling law again: a cleaner improvement turns compile failures
into *comparable* candidates, not matches — but it is what makes the tier reachable by the
per-function loop at all.

## Casts agree with the types m2c declares (`fix_pointer_types`)

m2c recovers types and **declares** them correctly: `void *temp_a0;`, `int *temp_a1;`, a
`void *arg0` parameter, `int (*temp_v1)(int, int, int);`. `clean()` writes an
unknown-width access as a bare `int`, and it strips `void *` from both directions with two
blanket rules (`= (void *)` → `= (int)`, `*(void *)` → `*(int *)`). Neither looks at the
lvalue, so without a further pass the draft stops compiling wherever the two disagree:

| draft | MWCC's first error |
| --- | --- |
| `void *temp_a0_2 = *(int *)((char *)(arg0) + 88);` | `'int'` → `'void *'` |
| `*(int *)((char *)(arg0) + 0) = &DAT_00532a50[0];` | `'int *'` → `'int'` |
| `int *temp_a1 = (char *)temp_v1 - 8;` | `'char *'` → `'int *'` |
| `DAT_00569238[0] = &FUN_001f4100;` | `'int (*)(...)'` → `'void *'` (the element of an arrayized `void *DAT_x[4]`) |
| `temp_v1 = *(int *)((char *)(temp_v0) + 64);` (`int (*temp_v1)(int)`) | `'int'` → `'int (*)(int)'` |

These *are* the top buckets of the compile tier without that pass — 1,826 first errors of the
tier are `'int'` → `'void *'` — which makes the tier look like a missing type model. It is not: the
types m2c recovers are already in the draft, and `--context` cannot supply the missing
information because nothing is missing.

`fix_pointer_types` runs at the end of `clean()` and reads the types the draft itself declares
— pointer locals, **function-pointer** locals, parameters, the element type of an arrayized
`void *DAT_x[4]`, callee return types, and the scalars, so it can tell which side of an
assignment is which. Each assignment's value cast is then made to agree with its target: a
pointer target gets `(T)(expr)`, an `int` target — including the cleaner's own
`*(int *)(...)` store — gets `(int)(expr)`.

Every rewrite is a cast between a 32-bit pointer and a 32-bit integer, so the instructions
cannot change (`lw`/`sw` either way). The 64-bit types are deliberately excluded: casting a
`long long` to a pointer would truncate it, which *is* a code change.

Over the whole compile tier this pass makes many compile failures comparable and matches a small share
of them. A stratified sample of the same *shape*, where over half became comparable and none matched,
reads as a refutation and is not one: it is under-powered. The spelling law — a spelling fix does not
match — is a statement about a low rate, not an impossibility, and it takes a whole-tier sweep to tell a
low rate from zero.

## The member rewrite folds the innermost member first

A member pass that rewrites *identifiers only* and scans the base left-to-right against the
**original** text produces C that is semantically wrong, and no per-function iteration inside the
m2c draft can find a match from wrong C. This is the cleanest counter-example the project has
to the spelling law, because the difference is one of **correctness**, not spelling. Three symptoms,
one cause:

| raw m2c | identifier-only rewrite (wrong) | the cleaner's rewrite |
| --- | --- | --- |
| `arg0->unk8->unk8` | `**(int *)((char *)(((char *)arg0 + 8)) + 8)` — a load from `arg0+16`, the inner deref dropped | `*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8)` |
| `FUN_x(a, b)->unkC` | `FUN_x*(int *)((char *)((a, b)) + 12)` — the call's parens and argument list destroyed | `*(int *)((char *)(FUN_x(a, b)) + 12)` |
| `slot->unk28(args)` | `*(int *)((char *)slot + 40)(args)` — "call of non-function" | `((int (*)())*(int *)((char *)slot + 40))(args)` |
| `arg0->unk1C = FUN_x(arg0 + 0xC, 1)` | `arg0 + 0xC` on a `void *` — "illegal type" | `FUN_x((char *)arg0 + 0xC, 1)` |
| `DAT_x.unk4` (m2c's dot form for an unknown-type global) | left as a member of an `int` — "not a struct/union/class" | `*(int *)((char *)&(DAT_x[0]) + 4)` |
| `arg0->unk-8` (a **negative** offset, e.g. a container-of) | a scan that requires a hex digit right after `unk` never rewrites it — uncompilable | `*(int *)((char *)(arg0) - 8)` |

The first row is the shape that dominates: a nested pointer member. With an identifier pre-pass
rewriting `arg0->unk8` and a general scan then taking the **cast's
argument** as the base, `a->unk4->unk8` becomes one load from `a + 12` instead of two
dependent loads. Every function with a 2-deep access is then uncompilable or silently wrong.

The rewrite is one left-to-right pass that folds the **innermost** member first and
**rescans**, so the outer member's base is the deref the pass just emitted;
`_primary_start` recognises an identifier, an array element (`DAT_x[0]`), a call result
(`f()`), a parenthesised expression and a deref-cast (`*(int *)(...)`). The width cast
(`= (u8) …`, `(u8) …`) belongs to the **outermost** access, so it is read only once the
member is isolated. A separate `fix_void_arith` casts `(p + N)` for a declared `void *p`
to `((char *)p + N)` — MWCC rejects void arithmetic (751 rows of "illegal type").
In the compile tier's first-error buckets, `pointer/array required` falls **520 → 95** once chains
and calls are no longer destroyed, and `illegal type` **751 → 90** once `void *` arithmetic is cast.

Everything it closes was a `compile` failure without it. Two further
shapes — a bare `temp = arg0 + 0x3E8` (beside the parenthesised `(arg0 + …)`) and a call through
a **dot** member (`DAT_x.unk0(...)`, which needs the same call wrapper as the `->` branch) — close
more `void *` arithmetic.

Most of what it closes is a `->unkN->unkM` chain, then a member access on a call
result (`f(...)->unkN`) and `void *` arithmetic, and rarely a call
through a slot.

In the negative-offset row, `unk-N` is rarely the sole blocking error
(`FUN_0022a740` is a case where it is). It is handled because the emitted address would otherwise be wrong, not
merely badly spelled — the same test as the member rewrite itself.

The lesson for the loop: **the spelling law does not apply to a correctness bug.** "Converting a compile failure into a mismatch yields no matches" was
measured three times, but all three fixes changed how the same instruction was *typed or
spelled*. When the C is wrong (a dropped deref, a destroyed call), the candidate is not
reachable by per-function iteration at all — and fixing it is worth checking against the
whole tier, because the affected functions are not the near-misses.

## The per-function loop

`tools/m2c_loop.py` is the loop's instrument: for one function it generates the m2c draft, cleans it
in all three address forms, keeps the closest, writes `build/m2c/<name>.c`, and prints an **aligned
instruction diff** (`retail mnemonic | ours mnemonic`, a marker on each differing word). The raw
verify report gives differing *words*, which cannot be read; the disassembly is what tells you
whether m2c chose the wrong loop shape, the wrong register, or the wrong number of arguments.
`--bank` copies a candidate into `src/` once `verify.py` agrees.

`tools/args_search.py` closes two measured families automatically. m2c often emits a call with fewer
arguments than retail passes, and the missing ones are the **leading** arguments — either the
enclosing function's own parameters, which m2c does not carry as live to the call, or a **small
integer constant** the retail form materialises into an argument register (`FUN_0016cde0` is
`j FUN_00207420` with `li a0,1` in the delay slot; m2c wrote `FUN_00207420()`). It tries, per call
site, prefixes of the parameter list and the constants `0..8, -1, 10, 16, 32, 64, 100, 128, 255, 256,
1000` as leading arguments and at every later position, hill-climbing on the instruction-diff count
with `verify.py` as the oracle (fail-closed: nothing is written unless the bytes agree).

The family is real but small, and `diffs` ≤ 3 is a poor proxy for cheap: its matches come from the
constant rule (`li 1/2/3`, and a `(void *)0x3D` cast) and the parameter rule.

Over the whole ≤3-instruction tier (`diffs` ≤ 3), two readings stand out, and the second contradicts the
premise that the lowest `diffs` are the cheapest subset:

* **Size, not `diffs`, predicts the yield.** Functions under 48 bytes almost never close, while the
48–63-byte band often does. That band is where one source idiom lives:
`if (*(int *)((char *)arg0 + 8) < *(int *)((char *)arg0 + 12)) FUN_002d6680(arg0, temp, K);`, a
container append with many callers of `FUN_002d6680`. The cheap axis
is *whether an idiom has been recognised*, not how many instruction words differ.
* **A one-instruction difference can still be a reverse-engineering problem.** The rest of the sample
is not argument errors: `FUN_0016cde0` (`void f(void){ FUN_00207420(); }`) dropped a **constant**
argument — retail is `li a0,1`, closed by `args_search.py`; `FUN_00109378` differs only in the
register chosen for a load (retail `v0`, ours `v1`); `FUN_002648e8` differs only in the address temp
(retail `lui v1`, ours `lui at`, and none of array / plain / pointer / literal / `volatile` spellings
reproduces it); `atan2f` has a 20-byte tail-call-with-frame shape (`addiu sp,-16; sd ra; ld ra;
j X; addiu sp,16`) that neither the C nor the C++ front end produced from a one-call body (the
sibling **frame-keeping** wrappers that set up arguments are covered by automatch's `wargs`
template); and the 16-byte BIOS wrappers need a `syscall`
idiom (m2c emits `M2C_ERROR(/* unknown instruction: syscall */)`). Each of those is a per-function
investigation, and the instruction diff is where it starts, not a measure of how close it is.

## Small data: the 480 functions that reach globals through `gp`

Retail reaches its small-data objects with a signed displacement off `gp`, e.g. `FUN_002f2260` is
just `lbu v1,-32476(gp); jr ra; sb v1,104(a0)`. The symbolizer rewrites `lui`/`lui`+`addiu`
addresses into `%hi`/`%lo`; a `($gp)` operand left numeric makes m2c model
`gp` as an ordinary saved register and emit `saved_reg_gp->unk-7EDC` — undeclared, uncompilable,
and the top of the `undefined identifier` buckets (265 rows).

`tools/m2c_one.asm_for(gp=…)` names the target address: `gp` (0x0055c870 from `.reginfo`) plus
the sign-extended displacement gives the object's VA, and the operand becomes
`%gp_rel(GPR_<addr>)($gp)`. m2c then emits a real global, and MWCC hands back the same gp-relative
access. **The name carries the addressing mode, not just the address:** `arrayize_globals` pushes a
`DAT_` global out of small data on purpose (the array trick above, for objects retail
reaches absolutely), so a gp-relative object must not be named `DAT_`. It is `GPR_`, which the
cleaner leaves the size m2c inferred.

There are **480 such functions and 1,547 gp-relative operands** — `lbu` 1,072, `sb` 241, `lwc1`
163, `lb` 40, `ld` 29, `lh`/`sh` 1 each. Every one is a load/store displacement, so the rewrite is a
single instruction-local substitution; a gp address computed with `addiu $r,$gp,disp` is symbolized
too. `verify.py`
resolves `R_MIPS_GPREL16` with `gp` from `.reginfo` (the relinker needs it too), and the
hand-matched `FUN_00130000` is the proof, so this is a matter of what m2c is *fed*, not of the
verification model. Functions on this path are reachable only through it.

The narrow-access width sits in the same family and is what the `sb` side needs: m2c
spells a store into an unknown member by truncating the value (`arg0->unk10 = (s8) …`), and that cast
**is** the access width. Rewriting the member to an `int` store turns retail's `sb` into a `sw`, one
word off. The rewrite keeps the width on both sides (store `= (u8) …`, load `(u8) base->unkN`),
which matches the five `Gap__Bec__beNDMWItem*__vfunc_24` functions that sit at `diffs=1` without it.

The three rules of this family do different jobs:

- `off($gp)` → `%gp_rel(GPR_addr)($gp)` closes gp-relative functions and removes the top `saved_reg_gp` failures.
- Narrow member access keeping its cast width closes a few.
- Emitting `extern char DAT_x[]` whenever the symbol is not already *declared* closes none alone, but makes
  functions such as `FUN_00296028` comparable.

### A store through a local takes its width from retail

`fit_widths` reads the real width from the retail instruction at the same (base register,
offset). It decodes the base of a **local** as well as `argN` → `aN`; decoding only `argN`
leaves a store through a local at the cleaner's default
`int`. `igDisplayListAttr_InitFields` has `*(int *)((char *)(temp_s1) + 52) = 1;`, which MWCC compiles
to `sw` where retail has `sb`, while the same function's `+56` store is right, which makes it look
like a one-word fluke. m2c names a held value after its register (`temp_s1` is `s1`, and a second value
in the same register is `temp_s1_2`), so the decode is a name parse: `m2c_batch._base_reg()` maps `argN`
→ `aN` and `temp_X[_K]` → `X`, and `ACCESS_RE` accepts any base name. Six of six sampled `_InitFields`
become exact. The store width is the family's single biggest cluster (`sb v0,N(s1)` vs `sw`).

### `_InitFields` saved registers

Two more rules close `<Class>_InitFields` near misses, both tried as variants that verification
decides:

* m2c types the loaded MetaObject handle `int`, so MWCC loads it into the first argument register and
  saves it (`lw a0,DAT; move s0,a0`) where retail loads the saved register and moves
  (`lw s0,DAT; move a0,s0`). Declaring the local `void *` and casting the load
  (`void *a; a = (void *)DAT_x[0];`) keeps the value in `s0`. `m2c_batch.retype_global_loads` tries
  this for any `NAME = DAT_x[0];` local declared `int`, which closes nearly every near miss of this shape.
* Larger bodies are a pure saved-register swap. MWCC assigns saved registers by declaration order, m2c
  declares the field count before the field pointer, and retail has the pointer in `s1` and the count
  in `s2`. `m2c_batch.order_pointer_decls` puts pointer locals before integer locals, tried after
  `retype_global_loads`, which closes many of the near misses of this shape. The rule is a type-class one and does not
  generalise to other declaration orders.

## `void *` arithmetic in four spellings

`fix_void_arith` casts `name + N` to `(char *)name + N`. The *same* machine arithmetic reaches m2c's
output three
more ways, and each fails with a **different** MWCC message, so a failure
taxonomy does not group them: `p += N` / `p -= N` (`illegal type`), `N + p`
(`pointer/array required`, via the `char[] | int` shape), and a `(void *)` cast used as an
arithmetic base (`illegal operand`). All of them are handled, and a bitwise-context address
is kept an int. The `(char *)` cast is **load-bearing, not cosmetic**: probed directly,
MWCC rejects `p = p + 4`, `p += 4`, `p = p + n`, `p = 4 + p`, `p = n + p` and
`*(int *)(p + 4) = 1` for a `void *p` — all six.

Over the whole tier, the three extra spellings and the bitwise rule make functions compile and match
none. That is the spelling law in its purest form, and its third confirmation:
*a compilability fix makes functions comparable, it
does not make them match.* The one that comes closest is `FUN_002e24e0` — a compile failure
without them, **1 diff** with them — and its remaining diff is an addend order (`addu v1,v1,a0` vs
`addu v1,a0,v1`), because MWCC canonicalises `X + (T *)Y` to `(T *)Y + X`, so the *cast*
decides the operands, not the expression order.

## The framed tail call is not an optimisation flag

The largest structural class in the queue (~379 of the ≤3-diff rows) is retail keeping a
frame around a tail call — `addiu sp,sp,-16; sd ra,0(sp); ld ra,0(sp); j target; addiu sp,sp,16`
— where m2c's `void f(void){ g(); }` gives an 8-byte frameless jump. Fifteen flag combinations
were measured on that source and **none** produces the 20-byte retail shape: `-O3`, `-O3,p`,
`-O3,s`, `-O4`, `-O4,p`, `-O4,s` and `-opt speed/space/full/size` all emit the frameless jump;
`-O2`, `-O2,p`, `-O1`, `-O0` and `-opt off` emit a 32-byte function with the frame **and a real
`jal`**. Retail sits between the two. So this class is a reconstruction problem, not an
optimizer setting — and m2c is *semantically* right while being byte-wrong.

## The queue, read before it is worked

`tools/queue_diag.py` clusters a worklist tier by *why* each function misses rather than by how many
instructions differ. It reruns the pipeline, verifies verbosely, and records two signatures per
candidate: the retail **shape** (the mnemonic skeleton with constants and register numbers folded) and
the **diffsig** (each differing instruction as `retail -> ours`). A large `(shape, diffsig)` cluster is
the next mechanical block; a large shape with scattered diffsigs is register allocation, which no
one-line transform fixes.

Run over a whole queue, it measures two things the counts
hide:

* much of the worklist's *1–3 diff* tier is **size truncations**, not near
  misses: `verify.py` compares over `min(len(ours), len(retail))`, so a short reconstruction reports a
  deceptively small diff. Their largest class is an m2c **tail-call collapse** (retail's framed 20-byte
  function becomes `j target; nop`, and MWCC will not re-emit the frame from any source form tried);
  the size pair is what separates the two, and the tool records it.
* the remaining true same-size near misses are a long tail, not a block, whose biggest cluster is the
  store width above; most of the rest is register allocation and scheduling/reorder.

So the same-size near-miss tier is a long tail of small clusters, and so is the
compile tier (led by `illegal type`, `pointer/array required`, `illegal operand` and m2c's own
undeclared `sp0`/`s128`/`sp4` spellings). The one large family in that queue is the C++ virtual call, below.

## Virtual calls are C++, not C

**Every function containing a
`jalr t9` carries the vtable-call idiom** (`lw t9,K(t9)` immediately
before the `jalr t9`). MWCC's **C** front end emits `jalr v0` for an indirect call,
while the **C++** front end emits the MIPS C++ ABI sequence, `lw t9,0(a0); lw t9,K(t9); jalr
t9` — so compiled as C, **zero** functions with a `jalr t9` match. The gap is not the cleaner, the
symbolizer or the width model: it is the language the
source is written in. 211 of the 1,449 carry a recovered name.

The mechanism is proven, not inferred. `Gap__Attrs__igBlendFunctionAttr__vfunc_12` (0x13c260, 80 B) is a call through a
function pointer held in the object at `+88`, its result fed to `igMetaObject_CountInstances`,
then `Gap::Core::igObject::vfunc_10(arg0)`. As C it is **3 instructions off**, all three in the
call (`lw v0,0(a0); lw v0,88(v0); jalr v0` against retail's `lw t9,0(a0); lw t9,88(t9); jalr
t9`). As C++ it is **byte-identical**:

```cpp
extern "C" {
  int Gap__Core__igObject__vfunc_10(void *);
  int igMetaObject_CountInstances(int, int);
  void Gap__Attrs__igBlendFunctionAttr__vfunc_12(void *arg0);          /* extern "C": a plain C++ decl mangles the name */
}
class C { public:
  virtual void v0(); ... virtual void v19();   /* 20 preceding slots put the target at +88 */
  virtual int vX();
};
void Gap__Attrs__igBlendFunctionAttr__vfunc_12(void *arg0) {              /* arg0 IS the object: retail loads the vptr from a0 */
  if (igMetaObject_CountInstances(((C *)arg0)->vX(), 1) == 0) { DAT_0055f4c0[0] = 0; }
  Gap__Core__igObject__vfunc_10(arg0);
}
```

Three things have to be right, and each is a trap: the class needs **20 preceding virtuals**
(MWCC reserves 2 vtable slots, so N preceding virtuals put the target at `8 + 4N`); `arg0` is
the object, not a pointer to it (retail's `lw t9,0(a0)` reads the vptr, not a pointee); and the
file must be a **`.cpp`** with the declarations in `extern "C"`. `tools/units.py` and
`tools/verify.py` dispatch on the extension. Every one of these functions sits in the mismatch
tier, not the compile tier, because the C m2c produces for it is *valid but wrong*.

**The transform.** `tools/m2c_batch.virtualize_calls()` recognises what the
cleaner makes of m2c's vtable call (`((int (*)())*(int *)((char *)(X) + K))()` from `X->unkK()`) and
re-spells it as a synthesized virtual call on a class with `K/4 - 2` leading slots. It is tried as a
`+vcpp` variant by both `m2c_batch.score_candidate` and `m2c_loop.prepare`, and `--write` picks
the `.cpp` extension from the winning variant's tag. It recovers the object address from the
base m2c wrote — `(*E)` or a word load `*(int *)((char *)(E) + 0)`, both "load the word at E" —
and re-spells the call as `((DW4VC_K_N *)(E))->vX((int)(A1), …)`, wrapping the declarations in
`extern "C"`.

Three traps, each invisible until it produces a *wrong* file
rather than an error: the callee declarations must be **variadic** (`int f(...);`), because C++
reads `int f();` as taking no arguments and the cleaner strips arguments from every prototype;
the function's own forward declaration must carry its real signature inside `extern "C"`, or the
definition is mangled and `verify.py` cannot find the symbol; and the scan must keep the text
*before* each match (dropping the preamble presents as "no
rewriteable call" because the function's name never appears in the rebuilt body).

Four further details decide the pattern coverage:

* **`_vcall_obj`'s regex order.** A generic `^\*(.+)$` branch tried first matches
  `*(int *)((char *)(s0) + 0)` and returns the *cast text* instead of the load address, so the
  **member-load base shape never fires at all** — m2c's commonest spelling for a vtable call on an
  object it already loaded. The parser strips the leading `*`, then an optional `(T *)` cast,
  and returns what follows as the address. A sample on which "the rewrite fires" does not show
  this: it can be firing only on the `(*E)` shape.
* **C++ passes the object as `this`**, so an explicit first argument that *is* the object is
  dropped; kept, it is passed twice — retail has no second `move a1,a0`.
* **`(int (*)())` must become `(int (*)(...))`** in C++, because `T (*)()` is a pointer to a
  function taking *no* arguments. That is what `function call does not match prototype` means for
  the vtable calls nested inside another call's argument list.
* **`declare_stack_placeholders` must declare m2c's `sp<hex>` slots** (`spD0`, `sp14`, …), not just
  bare `sp`. In C an undeclared identifier is an implicit int; in C++ it is a hard
  `undefined identifier`, which is how this path surfaces it.

The last two are compilability rules on their own — together they take the compile tier
**1,063 → 855** and match nothing (the spelling law, fourth confirmation).

**Nested calls.** A vtable call sitting *inside* another call's arguments has to be
rewritten too: left a plain indirect call, MWCC compiles it `jalr v0` where
retail has the ABI's `jalr t9`. `_vc_rewrite` therefore rewrites the argument list recursively (and
splits it at *top-level* commas, because a nested call carries its own), which takes `FUN_0013b6f0`
from 8 diffs to 2.
The class is small: only ~13 functions in the population contain the nested shape.

**The remainder is register-shaped.** The residual is not a general "argument-setup
difference": it is **specific and register-shaped**. (A near-miss count read off a worklist older
than the transform does not measure it, because the transform has already closed most of those rows.)
A census of `jalr t9` units by the register the vptr is loaded from:

| vptr from | units |
| --- | ---: |
| `a0` | 684 |
| `s0` | 196 |
| **`a1`** | **129** |
| `v0` | 122 |
| `s1` | 85 |
| `s2` / `s3` / `s4` / `s5` / `s6` | 75/52/42/38/7 |
| `v1` / `a2` / `a3` | 10/3/3 |

The int-returning rewrite alone closes units with the vptr in `a0`, `s0`, `v0`, `s1` and `s2`, and **no `a1` unit**.
The reason is the ABI, and it is proven against the compiler rather than inferred: **when the slot's
method returns a class by value, MWCC passes the hidden return buffer in `a0`, so `this` shifts to
`a1` and the vtable is loaded from it** —
`lw t9,0(a1); lw t9,K(t9); jalr t9; addiu a0,sp,N`. The int-returning rewrite *correctly* emits
`move a0,a1`, which retail does not have, so those functions can never match as spelled. MWCC uses
an `sret` buffer for a struct return of **any** size (a 4-byte struct included), and
`FUN_0013e6a0` reproduces **byte-identically** as a struct-returning virtual call:

```cpp
struct DW4SR1 { int w0; };
/* class DW4VC_280_1 has 68 preceding virtuals */
void FUN_0013e6a0(void *arg0, void **arg1) {
    *(int *)((char *)(arg0) + 12) = ((DW4VC_280_1 *)(arg1))->vX().w0;
}
```

the buffer's **size** deciding the frame offset (the same call spelled with a 16-byte struct misses
by 2 instructions).

**The four-byte statement shape.**
`virtualize_calls(..., sret=True)` keeps the ordinary int-returning call as a separate candidate,
then recognises only a discarded-result call whose first argument is exactly the address of an
`int` stack local. It re-types that local as `DW4SR4`, assigns the real C++ virtual return, and
rewrites the other word uses through `.w0`. This is deliberately narrow: an address-first virtual
call can also be an ordinary output parameter, so byte verification—not the source shape—decides.
`Gap::Core::igGeometryMaskAttr::vfunc_26` (`0x0013e6a0`) matches byte-identically this way.

In functions containing `lw t9,0(a1)`, most rows within three instructions share one spelling:
m2c retains the C ABI's explicit object argument after the hidden buffer,
`vX(&out, object, arg)`. The C++ spelling already supplies that object as `this`; dropping only an
exact `(int)(object)` immediately after the buffer makes them byte-identical. The transform stays
fail-closed and does not infer the duplicate from its position alone.

The two residuals are different mechanisms, not more struct-return shapes. In
`Gap::Core::igAlphaFunctionAttr::vfunc_26`, a nested slot returns a `float` in `f0` and retail passes
it to the outer call in `f12`, while the synthetic virtual class still declares every slot as
integer-returning. `Gap__Attrs__igBlendFunctionAttr__vfunc_26` differs only in instruction scheduling around its final virtual
call: retail materialises the address in the `jalr` delay slot, while the compiler moves `this`
there for the available source spelling. Neither is reached by the transform; each needs its own
mechanism.

### The `this`-strip must normalise the object spelling

The transform strips an explicit first argument when it *is* the object, so the object is not passed
twice. A textual equality is not enough for that test, because m2c spells the same object two ways:
the vtable base is
`((char *)(arg1) + 0)` (its cast and sized load) while the restated argument is the bare `arg1`. A
textual strip never fires for that spelling and the call carries one argument too many. Both sides
are therefore normalised — peel balanced parentheses, a trailing `+ 0`, and a leading `(char *)` cast
(`tools/m2c_batch._vc_obj_key`), as in `FUN_001b26f0` and `Gap::Bec::beNDMWMcUtilCtrl::vfunc_07/08`.

## What blocks the rest — the failure taxonomy

`tools/m2c_errors.py` is the instrument: it regenerates each candidate of a tier with the current
pipeline, reads MWCC's first `Error:` block (caret and source-echo lines dropped, identifiers
normalised to `DAT_x`/`0xN`/`@N`), and counts the buckets (`python3 tools/m2c_errors.py --all`). It
re-runs every row, so it measures the live tier, not the worklist's recorded one.

**The compile tier is not a type-model problem.** While the cleaner's casts disagreed with the types
the drafts declare, a 3,866-row compile tier (161 distinct messages) was led by `int`→`void *`/
`void **`/`int *` conversions (2,294 rows) and `int *`→`int` (201), and read as missing per-function
type inference. Those buckets belong to the cleaner (§*Casts agree with the types m2c declares*). With `fix_pointer_types` a full sweep reads
**1,258 compile / 9,759 mismatch / 102 m2c-fail / 80 sdk**, the compile tier in 144 distinct
messages, and what is left is not typing: `illegal type`
235, `pointer/array required` 206+19, `illegal operand` 141, `undefined identifier 'sp0'` 116 and
`'sp4'` 33, `'s128'` 62, `int` to `void *` 54, `'bitwise'` 27. Later rules shrink the tier without
changing that picture: the `void *` arithmetic spellings (1,261 → 1,063) and the C++
`(int (*)(...))` and `sp<hex>` rules (1,063 → 855).

These are understood and are **not** missing declarations:

* **`s128`** is the MMI type and appears only as a **type**, in casts (`(s128) *(int *)(...)`) and
  local declarations (`s128 sp20;`) for the `lq`/`sq` values; typing it was measured and matches
  nothing (§*What didn't work*).
* **`sp0`/`sp4`** are m2c's names for *stack slots* — the EE arch's spelling of the
  outgoing-stack-slot model (`subroutine_arg0/1` without the EE arch). `FUN_00277fa0`'s retail body is
  `move a1,sp; jal; lw v0,0(sp)`: m2c's `sp` is the frame base used as a value and `sp0` the word at
  frame offset 0, so an `int sp0;` declaration cannot place it; the frame has to be modelled.

The declaration families left are small: `bitwise` (27) needs a union recovery per function, and
the bare `saved_reg_<reg>` reads are functions whose source stores the `gp` value itself, which has
no C spelling.

The **mismatches** are m2c's CodeWarrior heuristics disagreeing with
retail on structure:

* **64-bit argument/return idioms** — retail's `dsll32 a0,a0,0` for passing a `long long`;
* **m2c's `var_*`/`temp_*` locals** — they change MWCC's register allocation and scheduling, e.g.
  `FUN_00102d90` came out one instruction larger;
* **loop shape** — m2c prefers `do { … } while (…)`, retail's `-O3` output often does not.

## Measured negatives — don't burn time here again

| Tried | Result |
| --- | --- |
| the permuter on the near-miss tier | closes almost nothing; the tier is very small, so scaling it buys little |
| m2c `--context` from `reflection.json`/`vtables.json` | neutral; few candidates read a class handle |
| grinding the mechanical cleaner | fixes convert compile failures into mismatches, not matches |
| declaring m2c's `void *temp_*` locals `int` | a few fewer compile failures across the switch tier and no extra matches — the spelling law again |
| **judging the re-typing of a load to match its local on a sample** — `void *temp = *(int *)X` → `*(void **)X` | an under-powered reading, not a negative: the shape is part of `fix_pointer_types`, whose rate only shows over the whole tier. Measure a rate over the tier, not over a sample |
| **merging m2c's illegal `switch` labels** — adjacent repeats (`case 0: case 0:`) and labels left outside any `switch` | not applied. m2c emits one label per *table index*, so repeated jump-table values repeat the label; the merge is positionally sound but the family is tiny, and for the stray case the real problem is that m2c's switch reconstruction is broken, so a loud compile failure is the better signal |
| **typing m2c's 128-bit `s128`** — both a scalar (`unsigned long long`) and the width-correct 16-byte struct | no matches either way — `s128` is fixable (a 16-byte struct is 16 bytes and copies with `lq`/`sq`) but it is not where the MMI bytes are; the block is m2c's 64/128-bit *access* modelling |
| the jump tables, once emitted | the table fixed the *parse*, not the match |

## The near-miss tier is four machine-checkable source shapes

The measured tier is not a long tail of unrelated misses: a run over the whole mismatch queue
with `diffs <= 20` (5,307 candidates) shows the residual is dominated by a handful of *source
spellings* the cleaner does not emit. `tools/retype_struct_member.py` prepares a candidate exactly
as `m2c_batch.py` does, generates the spellings below, and banks only what `verify.py` proves
byte-identical:

| Shape | What retail does vs m2c | The source spelling |
| --- | --- | --- |
| **struct** | keeps the base pointer (`move sX,aN; sb K(sX)`) where m2c CSEs `argN+K` (`addiu sX,aN,K; sb 0(sX)`) | give the base — a parameter **or a pointer local** — a struct type with a field at each accessed offset and read `base->fK`; the field widths come from retail, so one variant also carries the width fix |
| **width** | `sb`/`sh`/`lb`/`lbu`/`lh`/`lhu`/`sd`/`ld` where m2c emitted `sw`/`lw` | cast the deref to the width the retail instruction uses. `fit_widths` decodes only `argN`/`temp_sN` bases, so a base that is a saved copy of a parameter (`sN`) or a nested deref keeps `int`; the offset-only lookup excludes the frame registers (`sp`/`ra`/`gp`/`at`) or a stack slot at the same offset makes the width ambiguous |
| **leadfn** | the body reads `a1`/`a2` where m2c's `arg0` is `a0` | prepend 1-3 dummy parameters to the definition, so the body's `argN` names shift into the right registers (the 14-row `Gap__Bec__beNDMWMdl*__vfunc_35` family) |
| **leadcall** | retail loads an argument register before the `jal` where m2c emits a shorter argument list | prepend a prefix of the enclosing function's own parameters — or a small constant — to the call's argument list (the `args_search.py` family, applied automatically here) |

The shapes compose: a `struct` variant can carry a `leadfn` shift, and the struct field widths are
taken from retail, which is why `struct` is the largest single bucket.

**The measured limit.** A second pass of all four shapes over the `diffs <= 3` tier returns nothing.
What is left there is the **framed tail call**
(20-byte retail `addiu sp,sp,-N; sd ra,N(sp); j target` against m2c's 8-byte `j`, which 15 flag
combinations could not reproduce), pure `v0`/`v1` or `aN` register renames, and `sp`-frame
layout differences — none of which a source respelling reaches. The struct cluster lives in the
**4-80 diff band**, not in the near-miss tier, which is why the sweep must be run over the whole
queue and not only over `build/near3.tsv`. `FUN_0025a580` (the 832-byte frame loop) is unchanged by
all four shapes; its source is `src/unmatched/FUN_0025a580.cpp`.

## Repairing a draft by hand

Repair a draft before changing compiler. Fix dropped or forwarded leading arguments, use real pointer
and `long long` types, turn `loop_N`/`goto` loops into `for`/`while`, and use C++ classes with dummy
virtuals for `lw t9`/`jalr t9` calls, then retry the [alternate compiler](unit-compilers.md). Drafts
that fail unchanged often match once the source is right, including drafts that did not compile at
all; group those by compiler error.

**Calls and arguments.**

* A stale `a0` call argument is usually the forwarded real `arg0` that m2c dropped.
* Declare a `thunk_*` symbol as a function; as data it goes gp-relative.
* Give float callee parameters to floats m2c prints as `int` arguments.
* Read an old value after the call, not hoisted above it as m2c prints it, which costs a saved
  register.

**Widths and addresses.**

* Take the width and sign of every load and store from the retail opcode (`lbu`, `lhu`, `sb`, `sh`).
* Element stride: m2c writes `(int *)DAT_x + (i * N)`, and because `DAT_x` is already `int *` the shift
  comes out four times too large. Use a typed element array (`&DAT_x[i]`, or a `long long` or struct
  array for 8- or 64-byte elements), as in `FUN_001f8830`.
* Address materialisation: a fallback spelled as an integer constant gives `lui`+`ori`, while an
  address gives retail's `lui`+`addiu`, so write `(int)&DAT_004f7910[0]`
  (`Gap::Core::igMemoryPoolContextInfo::vfunc_54`).

**Control flow.**

* `if (x) {} else y = F` becomes `y = x ? a : F`.
* An `if`/`else` with duplicated tails becomes `if (c) { A; return; } B;`.
* `0 < cnt` gives the fused `slt at,zero,cnt` loop entry.
* Switch dispatch needs `break` arms, not `return`, to reach the shared epilogue.
* A one-case `switch` reproduces a `beq` plus `b` pair.

**Reloads.**

* A `volatile` member read reproduces a reload after a call.
* A `volatile` stack slot plus a non-volatile copy for the tests reproduces a reload from memory.
* `volatile` struct pointers with signed bit-fields force a second byte load.

**Registers.** Brute-force the local declaration order for up to five locals to close register-only
diffs the id trace cannot. Sorting the block by a rule does not work (§*What didn't work*).

**Classes.**

* Run all three `GetVTable` generators (stack, pointer, members), not one.
* A C++ vtable slot index is `(offset - 8) / 4` dummy virtuals.
* A stack-resident key class template covers a family of list searches, with a unit-objects entry
  pointing at the existing destructor copy.
* The 128-byte deleting reference-wrapper destructors (refcounted member, `igObject_Destroy`, then
  `FUN_00100610`) match as typed C with the refcount as `int r[1]` masked with `0x7fffff` and a `short`
  second argument: on the default compiler when the null-test delay slot is empty, on the alternate
  compiler at `-O3,p` when it holds `move a0,s1`. The `(long long)` loads of the m2c draft are the only
  defect.

**Varargs.** Under MWCC `__builtin_next_arg(x)` returns the frame top whatever `x` is. Passing a local
array keeps it, and its size sets the frame: `void f(int a0,...) { char d[48]; __builtin_next_arg(d); }`
gives `FUN_002252d8`'s 128-byte frame with `a0` never homed. Passing `a0` homes it and shrinks the
frame. The `FUN_00308320` `va_start` family (`FUN_00308390`, `FUN_003081d0`) uses
`__builtin_args_info(2)` with `__builtin_next_arg(arg0)`, matches only under the alternate compiler at
`-O3`, and differs only in its leading constant. `__builtin_args_info(1)` is an internal compiler
error; `(3)` is wrong for one named parameter.

**Symbols and units.** A function that matches every word but draws m2c's `missing jr $ra` warning has
a short symbol extent: the fix is a reviewed extent row, not source. When unit-objects merges declare
one body as both emitted and duplicate, keep emitted.

These rules do not close parameter-copy colouring (an `s0`/`s1` swap), member-first `GetVTable`
`v0`/`v1` second-vtable colouring, framed empty tail calls, smart pointers kept in stack slots, or
symbol extents with trailing zero padding that nothing emits.

## Pitfalls

These are properties of the tools, not of this binary.

1. **m2c's `--context` is inert unless the assembly references *named* data symbols.** Feed it
   `%hi(SYM)`/`%lo(SYM)`, not raw `lui`/`lw` — otherwise it invents anonymous literals that no
   declaration can match, and the context measures as a no-op.
2. **`?` is both m2c's "unknown type" and the ternary operator.** A blanket `?`→`int` corrupts
   `(a == 0) ? 4 : 2`; use `fix_unknown_type()`, which separates them by what precedes the `?`.
3. **Named globals need `extern T DAT_x[4];` used as `DAT_x[0]`.** As a plain 4-byte `extern` the
   object is small data, so MWCC addresses it gp-relative where retail uses absolute `lui`/`lw`.
4. **The address form cannot be decided from the source** — a literal comes out as scratch+`ori`, a
   symbol as destination+`addiu`. Compile all three spellings and keep the one that
   verifies.
5. **Data addresses run to `0x58d280`** (the first `PT_LOAD`'s memsz), not to the relinked
   section's `0x554b00`. Hard-coding the section end leaves every `.sbss` global as a literal.
6. **`objdump` needs `-z`**, or it elides runs of four or more zero words as `...`: every address
   in such a run is missing from the table and every function containing a nop block looks truncated
   (`automatch.disassemble`; 1,007,872 entries without it, 1,082,834 with it — 74,962 addresses).
7. **Scratch paths must be unique per process and thread.** With fixed `/tmp` names in `verify.py`,
   `m2c_loop.py`, `m2c_batch.py`, `automatch.py`, `check.py`, `linkgen.py` and `split.py`, two
   *processes* collide just as two threads do, and it fails in disguise — a per-function loop beside
   `make check` produces `struct.error: unpack_from requires a buffer of at least 56 bytes` and, with
   a shared `.c` source, `object defines no symbol 'FUN_x'` for a function that compiles fine (a
   collision of this kind is also behind a wrong "0/15" permuter reading). The paths carry
   `verify.TMP_TAG()` (pid + thread ident). And because `objcopy -I binary` names its symbols after the
   *path*, a varying temp path silently breaks hard-coded `--localize-sym`/`--redefine-sym` arguments
   in `linkgen` (every raw unit links as an undefined symbol); the linker script derives that prefix
   from the path it used.
8. **The permuter's score 0 ignores branch targets**, so it is not proof; always re-verify.
9. **`permuter.py --print-diffs` reads stdin** and dies with `EOFError` under `> log 2>&1 &`; use
   `--better-only`.
10. **m2c in-process is not thread-safe** (it mutates `sys.argv` and redirects global stdout).
    Serialise those calls; parallelise only subprocesses.
11. **A per-function `m2c.py` subprocess costs ~2.1 s** of interpreter startup; importing `m2c.main`
    once and re-invoking it costs ~0.003 s.
12. **`build/m2c/*.c` is scratch, so a census over it measures whatever was prepared last.**
    A count of "103 functions with duplicate switch labels, 11 % of the code bytes" came from
    that directory while it happened to hold the 30 *largest* compile-tier functions of one
    run — a biased sample wearing a whole-tree number. `tools/m2c_batch.py` prepares
    candidates to that directory and cleans up after itself, and `--keep-all` does not survive
    the cleanup. To census a tier, prepare the tier: `loop.prepare` returns the cleaned source
    (`res[6]`), or sweep the tier and analyse as it goes.
13. **A tier's `status` column is only as good as the pipeline that wrote it, and a negative `diffs`
    is not a diff.** `m2c_batch` records `diffs = -1` for a candidate that does not compile, so a
    cap written as `0 <= diffs` makes `m2c_loop.py --sample N --status compile` silently select
    **nothing**. The cap applies only to rows that have a diff.
14. **A verification helper must not index retail with an object-side offset.** `verify.solve_gp`
    reads the retail immediate at each `R_MIPS_GPREL16` relocation offset, and a candidate that
    compiles *larger* than the retail function (`off + 4 > len(retail)`) would raise `struct.error`
    and kill the whole sweep with nothing written. It skips relocations past the retail buffer, so
    the candidate simply fails as a mismatch. Anything
    that can raise inside the per-candidate loop has to fail closed for the *candidate*, not the run.

## Where the remaining work is

The mechanical pass cannot be pushed much further with regexes. A
*correctness* fix — the cleaner's casts — converts far more compile failures into matches than a
*spelling* improvement to the cleaner. The difference is that the second changes
what the C *means*, not how it is spelled, so check for mis-generated C before calling a bucket a
type problem. The jump tables
follow the same law: they fix a tier's *parse*, not its match. What is left
is **per-function**:

1. **Per-function correction, with `verify.py` as the oracle.** `tools/m2c_loop.py` is the loop
(write `build/m2c/<name>.c`, read the aligned instruction diff, iterate, `--bank` on a match).
`build/m2c_worklist.tsv` (`name, va, size, status, diffs, mode`) is the queue and
`tools/args_search.py` closes the dropped-leading-call-argument family automatically. **The
measurement above is the reason to be careful with the queue**: `diffs` ≤ 3 is not a proxy for
cheap. Only the 48–63-byte band yields much, and the residual is dominated by codegen idioms (address-temp register, a
constant argument, a tail-call-with-frame shape, `syscall` wrappers) that each need their own
investigation. `m2c_batch.py` reports `diffs = -1` for a candidate whose best mode does not
compile, so a compile failure cannot masquerade as a 0-diff near miss.
2. **The compile-failure tier.** It is not a typing problem (§*What blocks the rest — the failure
taxonomy*): what is left is stack-slot modelling (`sp0`/`sp4`), the MMI type (`s128`), a union
recovery per function for `bitwise`, and the `saved_reg_<reg>` reads that have no C spelling.
3. **m2c context files.** Feeding m2c a `--context` file with recovered struct types and function
signatures (the reflection/RTTI work in [`rtti-and-vtables.md`](rtti-and-vtables.md) and
[`reflection-metadata.md`](reflection-metadata.md) names real classes) does not fix a class
of `void *`/`unkN` output at once. It measures **neutral** for matching, and **`fix_pointer_types` explains
why**: the `void *` failures were never about missing types — m2c had already recovered and
declared the types, and the cleaner was casting against them — so the context has nothing to add,
and the same reasoning says it cannot help the MMI tier either.
4. **The MMI tier** (most switch candidates, and the functions m2c cannot parse at all)
has no route: `lq`/`sq` and the 128-bit moves are not modelled.
`s128` itself has a spelling (a 16-byte struct copies with `lq`/`sq`), but typing it matches nothing:
the block is m2c's 64/128-bit access modelling.

## What didn't work

**Hand-spelling the stack-slot family (`sp0`/`sp4`).** m2c models the outgoing-argument stack slot as a
value while retail passes its address (`move a1,sp`) and reloads it. Ten variants (`int`, `unsigned`,
`void *`, array, `float`, two locals, initialised, return through a dereference) all compile to one
shape that differs from retail by the same four words: the local at `sp+28` with `ra` at `sp+0`, where
retail has the local at `sp+0` and `ra` at `sp+16`. A union spelling of `bitwise` compiles, but MWCC
then uses `dsll32`/`dsrl32` for `& 0x7FFFFFFF` where retail has `lui`/`ori`/`and`, and `fabsf`
tail-calls, so the original union has to be recovered per function.

**Recompiling the frame/tail-call near misses as C++.** Small near misses either fail to compile as C++
or still differ, and few frame/tail-call cases are the single-call wrapper shape. Many lose a delay-slot instruction instead: `lui a0,0xB000; j X; ori a0,a0,0x1000`
(`FUN_001147f0`) becomes the constant `0xB0000000`. A general frameless tail-call template matches almost nothing, because MWCC materialises a recovered literal through a scratch
register (`lui v0; ori a0,v0`) where retail writes the destination directly. The group needs a
delay-slot fix in m2c or the symbolizer, not a language change or a template.

**Reordering the local declaration block by a rule.** Sorting by the register m2c's name implies,
reversed, and scalars-first does not close rows whose differences are all register names.
The pointers-before-ints rule for `_InitFields` does not generalise. The rest are ABI and
argument-setup differences, such as which argument register a constant lands in (`FUN_00242560`).

**Spelling `s128`.** MWCC has no 128-bit scalar: `(s128)x` from an int is `illegal explicit conversion`.
A 16-byte struct is the only width-correct spelling, and C99 compound literals such as `(s128){x,0}`
compile. Leaving it undefined does more damage than a wrong type: after `s128 spF0;` MWCC's C parser
reports every later declaration in the same scope as an `undefined identifier`, so part of those
buckets is this cascade and not missing declarations (`FUN_001ebc10` is an example). Spelling does not
fix the frame either: `qsort` stores a word (`sw a1,0(sp)`) into the slot m2c types as a
quadword, so the frame layout that follows from m2c's outgoing-argument model is wrong however `s128`
is declared.

## Open questions

- A wrapper that copies or tests a word and keeps the value in `v0` may need to return that value
  rather than be `void`; a `void` spelling allocates `v1`. Unproven. Forms seen:
  `return *(T *)dst = *(T *)src;` for three-instruction copies, an early `return 1; ... return 0;` to
  keep a compare load in `v0`, and returning the stored pointer (`FUN_002b50c8`). The rule was stated
  for MWCC, but `FUN_00109368` shows the form under the `ee-gcc` profile, so which compiler it applies to is unsettled.
