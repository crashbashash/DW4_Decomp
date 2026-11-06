# Matching patterns

Functions that resist a source match, and the compiler pattern that blocks each one.

## Open questions

- **`Gap__Bec__beGenerater__vfunc_33`** (`0x3853c0`, 1,112 bytes) has no source yet. The closest C++
  differs in one of 278 words (word 13: retail reads the incoming argument, the draft its saved copy),
  and that needs an unnatural operand spelling for an `addu`; the natural spelling differs in 2 words.
  Declaration shuffles do not remove it.
- **`Gap__Bec__beHitLandModel__vfunc_34`** (`0x3861d0`) has no source yet: the best draft is 1,392 bytes
  against 1,444, with about 169 of 361 lines different. Blockers: parameter registers (retail `s1` =
  message, `s0` = receiver), the allocator merge in the lazy-init blocks, 13 alignment nops, and the
  case 3/4 loop shapes.
- **`FUN_002b5b38`, `FUN_002b5b80` and `FUN_002b5ce0`** stay 2 words off: retail loads a global through
  `lui v1` / `ld v0` (and `lui v0` / `sd`), while MWCC uses `lui at` with a folded access for a single
  absolute global, and a plain 8-byte scalar goes gp-relative at a different size.
- **`FUN_001f0930`** is COP0/COP2 words and a `bc0f` poll loop with no C spelling.
- **`FUN_00200980`** (button-hint builder) and **`FUN_00178970`** (graphics-capture report) have no source
  yet: C rewrites reach 3,740 bytes against 3,720 and 5,164 against 5,256 but differ in register
  colouring and the narrowing of 64-bit deltas. No spelling is known.
