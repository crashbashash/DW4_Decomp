# Matching patterns

Compiler patterns that keep a source shape from reaching retail.

## Open questions

- **An incoming argument read where C reads its saved copy.** Retail reads the incoming argument where a
  C++ spelling reads its saved copy. Reaching it needs an unnatural operand spelling for an `addu`; the
  natural spelling differs in two words. Declaration shuffles do not remove it.
- **A lazily initialising message handler.** A draft comes out shorter than retail. The blockers are
  parameter registers, the allocator merge in the lazy-init blocks, alignment nops and the loop shapes.
- **A global read through a named register.** Retail loads a global through `lui v1` / `ld v0` (and
  `lui v0` / `sd`), while MWCC uses `lui at` with a folded access for a single absolute global, and a plain
  8-byte scalar goes gp-relative at a different size.
- **COP0/COP2 words and a `bc0f` poll loop** have no C spelling.
- **Long report builders.** C rewrites come within about 100 bytes of retail but differ in register
  colouring and the narrowing of 64-bit deltas.
