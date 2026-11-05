# The guard family — the missing `sltu`, cracked

**Status: the 72-byte variant is solved and banked (550 functions). The 76-byte
variant (507 functions) is still open, and §5 records the boundary precisely.**

This is the family that blocked bulk decompilation for two sessions: ~1,057 small
functions whose retail code has an `andi ; sltu v0,zero,v0 ; bnez` flag test, where
MWCC 3.0 refused to emit the `sltu` for every source form anyone tried. Findings
**[#310](../findings/findings-0251-0500.md#f310)** (the refuted attempt), **[#311](../findings/findings-0251-0500.md#f311)** (the narrowing), **[#312](../findings/findings-0251-0500.md#f312)** (the answer),
**[#313](../findings/findings-0251-0500.md#f313)** (the open 76-byte variant), **[#314](../findings/findings-0251-0500.md#f314)** (the wrappers), and **[#315](../findings/findings-0251-0500.md#f315)** (a refuted flag
hypothesis).

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
   is still loaded only twice. Nothing else reaches that state:
   * a bare condition (`!(g->f & 4)`) compiles to `andi` + a branch, no `sltu`;
   * a `bool` *cast* (`(bool)(g->f & 4)`) is folded away;
   * a `bool` initialised in its declaration (`bool t = g->f & 4;`) loads the
     global before the null test, so the prologue order is wrong;
   * `bool t = g && (g->f & 4);` materialises *both* operands — a second `sltu`
     on the pointer, 76 bytes with `v1`.
2. **C++ mode.** Only C++ has `bool`, and MWCC picks the language from the file
   *extension* — so these are the repo's only `src/*.cpp` units.
3. **The global must be declared as a 16-byte array** (`extern struct G *DAT_x[4]`,
   declaration only). As a plain pointer it is small data and MWCC emits
   gp-relative `lw v0,-N(gp)`; retail uses absolute `lui at` + `lw`.

Verified byte-identical: **550 / 550** members of this variant (72 bytes, 5
relocations each), independently with `tools/verify.py` and in bulk by
`tools/automatch.py --only guard`.

## 3. Banked in bulk

`tools/automatch.py`'s **`guard`** template recognises the 18-instruction shape and
writes the `.cpp` above. `CPP_TEMPLATES` in that file records which templates need
C++ and why. Three build pieces treat `src/<name>.cpp` as a source unit:

| Where | Change |
| --- | --- |
| `Makefile` | `CPP_SRC` glob + a `$(BUILD)/src/%.o: $(SRC)/%.cpp` rule |
| `tools/check.py` | coverage looks for `src/<name>.c` then `.cpp` |
| `tools/linkgen.py` | the relink compiles whichever of the two exists |

`make check` → 3,345/15,974 (20.9 %) matching, `make link` → **BYTE-IDENTICAL**.

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

## 5. The 76-byte variant — the open boundary

**Not cracked.** What is established, so nobody repeats it:

* It is **not an optimisation-level difference.** The same source at `-O1`/`-O2`
  *does* produce 19 instructions with the pad, but with the *unscheduled* prologue
  (`sd ra,0(sp)` before `lui at`) and an unscheduled epilogue; retail B has the
  `-O3` schedule (`lui at` **before** `sd ra`). `-O3` deletes the pad. No `-O`
  level, `-opt` keyword or `-inline`/`-intrinsics` setting produces retail B.
* It is **not a C-vs-C++ difference.** The idiom in C mode
  (`unsigned char t; if (!g || !(t = (g->f & 4) != 0))`) emits the same `sltu` and
  the same 72-byte shape.
* It is **not an address-alignment artifact.** Every guard in both variants starts
  16-byte aligned, and the address mod 8/16 of the function has no correlation with
  the variant. The inter-function gaps (0, 8, 12 bytes) do not correlate either.
* **Exhausted source forms.** ~500 hand-written forms plus a 590-case grammar sweep
  (declaration × condition × statement-wrapping × dead-statement insertion, including
  `switch`/`goto`/`do-while` spellings) found nothing at 76 bytes; the materialising forms from
  finding [#311](../findings/findings-0251-0500.md#f311) were all tried.
* **The permuter did not find it.** `tools/permuter/FUN_00334460/run.sh` (the same
  harness shape as the A harness) ran to ~1.2 M iterations at ~900/s with base
  score 105 and **no improvement** — the mutation space cannot reach it from the
  72-byte base, because the missing property is a codegen artifact, not an AST shape.

* **The permuter did not find it, and its one "improvement" is a reward hack.**
  `tools/permuter/FUN_00334460/run.sh` (the same harness shape as the A harness) ran to
  ~1.65 M iterations at ~900/s with base score 105 and produced exactly one output,
  `output-65-1/` (score 65). That candidate inserts dead code —
  `if ((!g) && (!g)) { g++; g--; }` — which MWCC emits as a single `nop`, **but at index 4**
  (between the global load and the null test), not at index 11: 76 bytes with 7 wrong
  instructions. It is a genuine mechanism (MWCC emits a `nop` for a dead/empty block) but the
  `nop` lands *where the dead construct sits*, and every placement that would land it at index 11
  — inside the `if` body, or at the top of an explicit `call:` block reached by `goto` — is folded
  away by the -O3 optimiser. Score 65 is **not** progress toward retail; see §5 for what is left.

The likely explanation is that the pad is a front-end emission (it exists at `-O1`)
that the `-O3` scheduler normally removes, and B's file inhibited that specific
cleanup — a per-file codegen state we cannot yet express in one function's source.

**If you re-attack it:** the productive angle is probably the *file-level* split
(§4/§6), not more source forms. B's file is C++-mode-like for callees; A's is
C-mode-like. The two files differ in something that both keeps callee frames and
keeps the caller's pad, and the flag is likely expressible as a `#pragma` or a
per-file compile setting rather than a source statement.

## 6. Bonus: the one-call wrapper family, also cracked

The 28-byte and 32-byte "keep the frame for a single call" wrappers resisted for a
*related* reason — and the reason turns out to be **the same extension switch**:

> MWCC's **C** front end turns `void f(void){ X(); }` into a 2-instruction `j` tail
> call. Its **C++** front end keeps the frame. The retail wrappers are C++.

That is not visible from the source alone; it is a language-mode codegen difference.
1,085 functions are 28/32-byte single-call frame-keeping wrappers, and the two new
`automatch` templates reproduce **1,012** of them, all verified byte-identical:

| Template | Shape | Source (written to `.cpp`) |
| --- | --- | --- |
| `wcall` | 28 B: `addiu sp,-16 ; sd ra ; jal X ; nop ; ld ra ; jr ra ; addiu sp,sp,16` | `void f(void) { X(); }` |
| `wload` | 32 B: the same, with `lui aX,HI` before and `addiu aX,aX,LO` in the `jal` delay slot | `void f(void) { X(DAT_arg); }` |

The 73 not covered are different shapes: 19 of the 28-byte ones return a constant
(`li` in the `jal` delay slot), and 46 of the 32-byte ones have a `sync` barrier or
a `beq` in the body. The earlier claim that this family was "not a templating gap"
was wrong — it was a *language-mode* gap. `-O3` C++ is the setting.

**The same shape with arguments was closed later.** `wcall`/`wload` only cover a
call with no argument or one constant address; the rest of the family also sets up
argument registers (a constant, a pass-through of the enclosing parameter, a field
load, a global or parameter address). `automatch`'s **`wargs`** template decodes
that setup from the retail instructions and emits the wrapper as C++ — **55** more
of them verify (finding **[#332](../findings/findings-0251-0500.md#f332)**). The decode depends on the R5900 calling
convention, which passes the first **eight** integer arguments in `a0-a3` then
`t0-t3`, so a wrapper's `t`-register setup is an argument too, not a temporary.

## 7. Numbers

| | |
| --- | --- |
| before | 1,783 / 15,974 (11.2 %) |
| guard (variant A) | +550 → 2,333 (14.6 %) |
| wrappers (`wcall` + `wload`) | +1,012 → **3,345 / 15,974 (20.9 %)** |
| `make check` | 3,345 matching, 0 mismatched |
| `make link` | **BYTE-IDENTICAL** (4,541,184 bytes) |
| still open | guard variant B, 507 functions |
