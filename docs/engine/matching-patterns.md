# Matching patterns

Compiler patterns that keep a source shape from reaching retail, and the function that shows each one.

## Open questions

- **`Gap__Bec__beGenerater__vfunc_33`** (`0x3853c0`, 1,112 bytes): at word 13 retail reads the incoming
  argument where a C++ spelling reads its saved copy. Reaching it needs an unnatural operand spelling for an
  `addu`; the natural spelling differs in 2 of 278 words. Declaration shuffles do not remove it.
- **`Gap__Bec__beHitLandModel__vfunc_34`** (`0x3861d0`): a draft comes to 1,392 bytes
  against 1,444. The blockers are parameter registers (retail `s1` =
  message, `s0` = receiver), the allocator merge in the lazy-init blocks, 13 alignment nops, and the
  case 3/4 loop shapes.
- **`FUN_002b5b38`, `FUN_002b5b80` and `FUN_002b5ce0`**: retail loads a global through
  `lui v1` / `ld v0` (and `lui v0` / `sd`), while MWCC uses `lui at` with a folded access for a single
  absolute global, and a plain 8-byte scalar goes gp-relative at a different size.
- **`FUN_001f0930`** is COP0/COP2 words and a `bc0f` poll loop with no C spelling.
- **`FUN_00200980`** (button-hint builder) and **`FUN_00178970`** (graphics-capture report): C rewrites
  reach 3,740 bytes against 3,720 and 5,164 against 5,256 but differ in register
  colouring and the narrowing of 64-bit deltas.
