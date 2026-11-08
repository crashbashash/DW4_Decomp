# Hand-written assembly sources

A few retail routines were written in assembly, not compiled. Their source is a `.S` file under
`src/`, assembled by the same Sony EE GCC driver and `ee-as` as the C of their unit
(`tools/eegcc_compile.py`), and verified byte for byte like any other function. `make check` puts them in
the `assembly` category and `tools/progress.py` counts them apart: they are recovered source, but
they are not C, so they are never in the C figures.

## The approval rule

A `.S` file may sit in `src/` only when the project owner has approved it. Each approved function
has a row in `config/assembly-sources.tsv` (`symbol`, `path`, the anchor of its evidence below).
Only the owner approves a row. An agent may write one only when the owner has explicitly told it to
add that specific routine, after reviewing its evidence; it never adds one on its own initiative or
as part of a broader request ("match everything", "clear the queue"). `tools/units.py` refuses any other `.S` file, so every tool that reads `src/`
stops on it. The table is one of the oracle's own files (`.githooks/oracle-files.txt`).

To propose a routine, write its evidence in this document's open questions and show it to the
owner. The evidence has to show both of these:

* **It is not compiler output.** Name the instruction pattern that no compiler build the project
  has produces, under the sources and flags tried: register saves C cannot spell, a `noreorder`
  delay slot, an upstream assembly source.
* **The C search is done.** List the compilers, flags and source shapes tried, with their best
  diffs. "Looks hand-written" is not evidence. Several newlib routines once judged hand-written
  have the structure plain C gives under 2.96 (see the open questions).

An approved `.S` file follows the upstream source where there is one, keeps one routine (or one
upstream file) per file, and spells instructions as mnemonics, never `.word`.

## Approved

### setjmp and longjmp

`FUN_00129880` (setjmp, 88 bytes) and `FUN_001298d8` (longjmp, 100 bytes): `src/newlib/setjmp.S`.

* Upstream newlib ships them as assembly (`newlib/libc/machine/mips/setjmp.S`). Sony's file is
  that one with each callee-saved register stored as a quadword (`sq`/`lq`: the R5900's general
  registers are 128 bits wide) and `$f24`-`$f31` added after `s8`. The jmp_buf layout follows:
  `s0`-`s8` at 0-128, the floating-point registers at 144-172, then `sp` at 176 and `ra` at 192.
* No C can write them. setjmp stores the caller's callee-saved registers, `sp` and `ra`, and
  longjmp restores them and returns into another frame. A compiler saves only the registers its own
  body uses, in its own frame.
* The delay slots are explicit `nop`s after `jr ra` and after longjmp's `bne`. `ee-as` fills both
  slots in reorder mode, so the file is `.set noreorder`, as in other EE assembly.
* The instructions are DW4's, byte for byte. What the assembler discards (comments, local label
  names, register spellings, `.ent`/`.frame`) cannot be read back from the binary, so those follow
  upstream, as matched C follows whatever spelling reproduces the code.

## Open questions

* **memcpy, memmove, memset, memchr, memcmp, strcpy, strcat, strlen, strchr, strcmp, strncat,
  strncmp, strncpy** were listed as possibly hand-written. They are not approved, because the C
  search is not finished. newlib's `memcpy.c`, given a 32-byte `lq`/`sq` block loop, compiles under
  2.96 `-O2 -G0 -g` to retail's instruction sequence; only the register choice and a few scheduled
  slots differ. strncat's byte tail comes out exactly under 2.9-ee-991111-01 (its `lui`/`ori` -1 and
  the assembler's short-loop `nop`s), and strchr and strncpy contain `movz`, which only 2.96's
  if-conversion emits. All of these look like compiled C with MMI `asm` statements.
