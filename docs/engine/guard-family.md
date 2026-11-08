# The guard family — the missing `sltu`, cracked

**The 72-byte variant has 550 functions; the 76-byte variant (507 functions)
has a source form under each compiler (§5).**

The family is ~1,057 small
functions whose retail code has an `andi ; sltu v0,zero,v0 ; bnez` flag test, where
the `sltu` is a value conversion of the flag test, so it needs a source form that converts it (§2).

## 1. What the functions are

They are per-object accessors with an "initialise if not ready" guard, and they
call message-specific wrappers around a logging/init routine. Example,
`FUN_00130060` at `0x130060`:

```
addiu sp,sp,-16          ; lui at,%hi(DAT_0055ebc0)
sd    ra,0(sp)           ; lw v0,%lo(DAT_0055ebc0)(at)
beqz  v0,.Lcall          ; nop
lw    v0,36(v0)          ; andi v0,v0,0x4
sltu  v0,zero,v0         ; bnez v0,.Lend
nop                      ; nop
.Lcall:  jal FUN_001301c0 ; nop
.Lend:   lui at,%hi(DAT_0055ebc0) ; ld ra,0(sp)
         lw v0,%lo(DAT_0055ebc0)(at) ; jr ra ; addiu sp,sp,16
```

Semantics: `if (!g || !(g->f36 & 4)) X(); return g;` — the global is loaded exactly
twice (null test, return) and the flag test is *materialised*.

A census over the whole image finds the motif `andi + sltu rd,zero,rs + bnez rd`
**1,083 times in 1,071 functions** (the rest are larger functions that embed it).

## 2. The answer

```cpp
struct G *g = DAT_0055ebc0[0];
bool t;
if (!g || !(t = g->f & 4))
    FUN_001301c0();
return DAT_0055ebc0[0];
```

Three details are all load-bearing:

1. **The flag test must be an assignment to a *named* `bool` inside the
   short-circuit condition.** `!(t = g->f & 4)` forces MWCC to convert the `int`
   expression to `bool` — a *value* conversion, which is exactly the
   `sltu v0,zero,v0` — while the pointer test stays a plain `beqz` and the global
   is still loaded only twice. The test has to be spelled as a value:
   * under 3.0b52, `bool t; ... !(t = g->f & 4)` differs, and `((g->f & 4) != 0) == false` or
     `int t; ... !(t = (g->f & 4) != 0)` gives the bytes; all three give them under the default compiler;
   * a bare condition (`!(g->f & 4)`) compiles to `andi` + a branch, no `sltu`;
   * a `bool` *cast* (`(bool)(g->f & 4)`) is folded away;
   * a `bool` initialised in its declaration (`bool t = g->f & 4;`) loads the
     global before the null test, so the prologue order is wrong;
   * `bool t = g && (g->f & 4);` materialises *both* operands — a second `sltu`
     on the pointer, 76 bytes with `v1`.
2. **C++ mode.** Only C++ has `bool`, and MWCC picks the language from the file
   *extension*.
3. **The global must be declared as a 16-byte array** (`extern struct G *DAT_x[4]`,
   declaration only). As a plain pointer it is small data and MWCC emits
   gp-relative `lw v0,-N(gp)`; retail uses absolute `lui at` + `lw`.

Each member of this variant is 72 bytes with 5 relocations. Check one with
`tools/verify.py`, or all of them with `tools/automatch.py --only guard`.

## 3. Generating the family

`tools/automatch.py`'s **`guard`** template recognises the 18-instruction shape and
writes the `.cpp` above. `CPP_TEMPLATES` in that file records which templates need
C++ and why. Three build pieces treat `src/<name>.cpp` as a source unit:

| Where | Change |
| --- | --- |
| `Makefile` | `CPP_SRC` glob + a `$(BUILD)/src/%.o: $(SRC)/%.cpp` rule |
| `tools/check.py` | coverage looks for `src/<name>.c` then `.cpp` |
| `tools/linkgen.py` | the relink compiles whichever of the two exists |

## 4. The two variants of the family

The family is **not uniform** — it is the same source idiom compiled in two
*contiguous regions*, so the split is per-file, not per-function:

| Variant | Count | Size | Regions (in address order) | The dead `nop` |
| --- | --- | --- | --- | --- |
| **A** | 550 | 72 B (18 insns) | `0x130060` ×501, `0x44b8d0` ×49 | none |
| **B** | 507 | 76 B (19 insns) | `0x334460` ×483, `0x4586f0` ×24 | one, at index 11 |

B is A with one extra `nop` immediately before the merged `jal`, and both branch
displacements one word larger (`beqz +7`/`bnez +4` instead of `+6`/`+3`). It is
**dead code on the fall-through path**, and it is skipped by the null-test branch
(which targets the `jal`, not the `nop`).

The variant correlates with the shape of the *callee*: the A guards call 3-instruction
`j` tail-call wrappers, the B guards call 32-byte frame-keeping wrappers (§6).

## 5. The 76-byte variant

Under the default compiler the dead `nop` is written: `asm { nop }` after the flag
branch inside `if (g) { ... }`, with the call outside it and a `goto` to the return.
Under b52 the comparison with `false` gives the same bytes with no `asm`
(`src/unmatched/FUN_00334460.cpp`):

```cpp
struct G *g = DAT_00587628[0];
if (!g || ((g->f & 4) != 0) == false) {
    FUN_003344f0();
}
return DAT_00587628[0];
```

Under combat and 3.0.3, `-O3` and `-O3,p` keep the `sltu` for an `unsigned char` flag
compared with 0 and pad the branch target themselves, so no `asm` statement is needed.
The alternate compiler at `-O3,p` also matches from C++ that assigns the flag test to
an `int` or `bool` temporary.

`tools/guard_b_gen.py` generates the source from the retail words and skips functions
off the retail shape. Generate for all 76-byte symbols, verify each row and keep only
the passes. Other 76-byte rows are different shapes (`sd` prologues, lazy-singleton
get/release pairs).

## 6. Bonus: the one-call wrapper family, also cracked

The 28-byte and 32-byte "keep the frame for a single call" wrappers resisted for a
*related* reason — and the reason turns out to be **the same extension switch**:

> MWCC's **C** front end turns `void f(void){ X(); }` into a 2-instruction `j` tail
> call. Its **C++** front end keeps the frame. The retail wrappers are C++.

That is not visible from the source alone; it is a language-mode codegen difference.
1,085 functions are 28/32-byte single-call frame-keeping wrappers, and two
`automatch` templates cover their plain shapes:

| Template | Shape | Source (written to `.cpp`) |
| --- | --- | --- |
| `wcall` | 28 B: `addiu sp,-16 ; sd ra ; jal X ; nop ; ld ra ; jr ra ; addiu sp,sp,16` | `void f(void) { X(); }` |
| `wload` | 32 B: the same, with `lui aX,HI` before and `addiu aX,aX,LO` in the `jal` delay slot | `void f(void) { X(DAT_arg); }` |

Other members have different shapes: 19 of the 28-byte ones return a constant
(`li` in the `jal` delay slot), and 46 of the 32-byte ones have a `sync` barrier or
a `beq` in the body. This is a *language-mode* gap. `-O3` C++ is the setting.

**The same shape with arguments.** `wcall`/`wload` only cover a
call with no argument or one constant address; the rest of the family also sets up
argument registers (a constant, a pass-through of the enclosing parameter, a field
load, a global or parameter address). `automatch`'s **`wargs`** template decodes
that setup from the retail instructions and emits the wrapper as C++. The decode depends on the R5900 calling
convention, which passes the first **eight** integer arguments in `a0-a3` then
`t0-t3`, so a wrapper's `t`-register setup is an argument too, not a temporary.

## What didn't work

None of these produces the 76-byte form under the default compiler:

* **An optimisation level.** The same source at `-O1`/`-O2` *does* produce 19
  instructions with the pad, but with the *unscheduled* prologue (`sd ra,0(sp)` before
  `lui at`) and an unscheduled epilogue; retail B has the `-O3` schedule (`lui at`
  **before** `sd ra`). `-O3` deletes the pad. No `-O` level, `-opt` keyword or
  `-inline`/`-intrinsics` setting produces retail B.
* **C mode.** The idiom in C mode (`unsigned char t; if (!g || !(t = (g->f & 4) != 0))`)
  emits the same `sltu` and the same 72-byte shape.
* **Address alignment.** Every guard in both variants starts 16-byte aligned, and the
  address mod 8/16 of the function has no correlation with the variant. The
  inter-function gaps (0, 8, 12 bytes) do not correlate either.
* **Source forms without `asm`.** ~500 hand-written forms plus a 590-case grammar sweep
  (declaration × condition × statement-wrapping × dead-statement insertion, including
  `switch`/`goto`/`do-while` spellings and the materialising forms) found nothing at
  76 bytes.
* **One translation unit with the callee.** Compiling a guard with its callee, in either
  order, does not produce the pad.
* **The permuter.** `tools/permuter/FUN_00334460/run.sh` (the same harness shape as the
  A harness) ran to ~1.65 M iterations at ~900/s with base score 105 and produced exactly
  one output, `output-65-1/` (score 65), which is a reward hack. That candidate inserts
  dead code — `if ((!g) && (!g)) { g++; g--; }` — which MWCC emits as a single `nop`,
  **but at index 4** (between the global load and the null test), not at index 11:
  76 bytes with 7 wrong instructions. MWCC does emit a `nop` for a dead or empty block,
  but the `nop` lands *where the dead construct sits*, and every placement that would
  land it at index 11 — inside the `if` body, or at the top of an explicit `call:` block
  reached by `goto` — is folded away by the `-O3` optimiser.
