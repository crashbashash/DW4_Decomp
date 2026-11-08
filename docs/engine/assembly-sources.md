# Hand-written assembly sources

A few retail routines were written in assembly, not compiled. Their source is a `.S` file under
`src/`, assembled by the same Sony EE GCC driver and `ee-as` as the C of their unit
(`tools/eegcc_compile.py`), and verified byte for byte like any other function. `make check` puts them in
the `assembly` category. The original source was assembly, so they count as matched in `README.md`,
`PROGRESS.md` and `functions.fully_matched`, and as readable once they have a recovered name, since
the approval records that no C reproduces them. They are not C, so figures labelled C/C++ leave them out,
as do `make check`'s `match` count and `functions.fully_verified`, which the oracle compares.

## The approval rule

A `.S` file may sit in `src/` only when the project owner has approved it. Each approved function
has a row in `config/assembly-sources.tsv` (`symbol`, `path`, the anchor of its evidence below).
Only the owner approves a row. An agent may write one only when the owner has explicitly told it to
add that specific routine, after reviewing its evidence; it never adds one on its own initiative or
as part of a broader request ("match everything", "clear the queue"). `tools/units.py` refuses any other `.S` file, so every tool that reads `src/`
stops on it. The table is one of the oracle's own files (`.githooks/oracle-files.txt`).

To propose a routine, write its evidence in this document's open questions and show it to the
owner. The evidence has to show that **the original source was assembly**. Strongest first:

* **The original build records it:** an object naming a `.S` source and lacking the compiler markers
  its C siblings carry.
* **An upstream assembly source** that the routine follows.
* **Code no compiler produces:** instructions it never emits, or saves and restores of another
  frame's registers.

A failed C search, with the compilers, flags, source shapes and best diffs tried, can support the
case but never makes it: it shows that C has not been found, not that the original was assembly.
"Looks hand-written" is not evidence. Several newlib routines once judged hand-written have the
structure plain C gives under 2.96. A function that is compiler output stays unmatched until its C
is found, however long the search has run.

An approved `.S` file follows the upstream source where there is one, keeps one routine (or one
upstream file) per file, and spells instructions as mnemonics, never `.word`.

## Approved

### setjmp and longjmp

`setjmp` (`0x129880`, 88 bytes) and `longjmp` (`0x1298d8`, 100 bytes): `src/newlib/setjmp.S`.

* Upstream newlib ships them as assembly (`newlib/libc/machine/mips/setjmp.S`). Sony's file is
  that one with each callee-saved register stored as a quadword (`sq`/`lq`: the R5900's general
  registers are 128 bits wide) and `$f24`-`$f31` added after `s8`. The jmp_buf layout follows:
  `s0`-`s8` at 0-128, the floating-point registers at 144-172, then `sp` at 176 and `ra` at 192.
* Sony's own build agrees: the `setjmp.o` of the `ee001003_1` toolchain's `libc.a` is DW4's bytes
  and records its source as `src/newlib/libc/machine/r5900/setjmp.S`.
* No C can write them. setjmp stores the caller's callee-saved registers, `sp` and `ra`, and
  longjmp restores them and returns into another frame. A compiler saves only the registers its own
  body uses, in its own frame.
* The delay slots are explicit `nop`s after `jr ra` and after longjmp's `bne`. `ee-as` fills both
  slots in reorder mode, so the file is `.set noreorder`, as in other EE assembly.
* The instructions are DW4's, byte for byte. What the assembler discards (comments, local label
  names, register spellings, `.ent`/`.frame`) cannot be read back from the binary, so those follow
  upstream, as matched C follows whatever spelling reproduces the code.

### The R5900 string and memory routines

`memchr`, `memcmp`, `memcpy`, `memmove`, `memset`, `strcat`, `strchr`, `strcmp`, `strcpy`, `strlen`,
`strncat`, `strncmp` and `strncpy`: one `src/newlib/<name>.S` each, named as the archive members
name them (`config/SLUS-20836/names/newlib.tsv`).

* DW4 links them from the `libc.a` of Sony's EE toolchain release `ee001003_1` (2.96-ee-001003-1,
  the compiler of the rest of newlib). Each member's `.text` is DW4's bytes exactly; `strcat.o`
  differs only in its unrelocated `jal strcpy`.
* Each member records its source as `src/newlib/libc/machine/r5900/<name>.S`. The C members of
  the same archive record `.c` files (`libc/stdlib/strtol.c`) and carry the compiler's
  `gcc2_compiled.`/`__gnu_compiled_c` symbols and an `.mdebug.eabi64` section; these carry none.
* Their local labels are compiler-style (`$L3`, `$L9`, `$L14` in `strcat.o`), so the `.S` files
  were most likely compiler output that was edited and kept as assembly. That is why plain C with
  MMI `asm` statements comes close under the 2.9-ee releases and 2.96 but never matches: a C
  search found near misses for all thirteen and a match for none.
* `strcat` saves `ra` with `sq`, which no tried compiler emits; it is a non-leaf routine (it
  calls `strcpy`).
* The files keep the archive objects' own local labels (`$Ln`) and their `noreorder` delay slots,
  and assemble to the archive's bytes.

## Open questions

* **Which compiler generated the R5900 `.S` files** before they were edited. Their `lui`/`ori` -1
  and loop scheduling point at a 2.9-ee release; a few details (`daddu` in strchr, filled `ld` loops
  in strlen) point at 2.96.
