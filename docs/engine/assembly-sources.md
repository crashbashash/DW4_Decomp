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

### libkernl syscall stubs

The system-call stubs of Sony's libkernl: `src/sony/libkernl/klib.S`, each `li $3,N; syscall; jr $31; nop`.

* Sony's own build records it. The SDK 3.0.3 `libkernl.a` holds them in one member, `klib.o`, whose file symbols
  name `klib.s` and which has none of the compiler markers its C siblings carry. Its whole `.text` appears once in
  the executable, byte for byte, and its syscall numbers agree with `config/SLUS-20836/syscalls.txt`. The
  executable's library string is `PsIIlibkernl2800`, the 2.8 release of the same file.
* The file was generated from the member's symbol names and the executable's numbers; nothing of Sony's text is in
  it. It is assembled in `noreorder` mode, as the member was, so the delay slots stay explicit `nop`s.
* The member holds 138 stubs. Only those with a symbol in `config/SLUS-20836/symbols.txt` are in the file; the
  executable keeps the others in ranges the layout treats as data.

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
* No 2.96 C can produce ten of them. Every function ee-gcc 2.96 compiles at `-O2` starts with
  `.p2align 3` and pads each loop top to 8 bytes, so its object's `.text` is 8-aligned: all 217 C
  members of the same `libc.a` are. `memchr`, `memcmp`, `memcpy`, `memmove`, `memset`, `strcat`,
  `strchr`, `strcmp`, `strcpy` and `strlen` are 4-aligned members with loop tops at 4 mod 8 (`memcpy`
  at `+0x24`, `+0x5c`, `+0x8c` from an 8-aligned start). `strncmp` is 8-aligned but its loop at `+0x8c`
  is not. `strncat` compares against `lui`/`ori` -1, which 2.96 writes `li` (`addiu`), and with
  `strncpy` needs `psubb`, which has no C spelling. A 2026-11 search under the unit profile (newlib's
  `memcpy.c` shapes with a TImode block, goto loops, 20 `-f` variants) was 164 to 180 bytes against
  176 for `memcpy`, with no match, so all thirteen stay assembly.
* `strcat` saves `ra` with `sq`, which no tried compiler emits; it is a non-leaf routine (it
  calls `strcpy`).
* The files keep the archive objects' own local labels (`$Ln`) and their `noreorder` delay slots,
  and assemble to the archive's bytes.

### The start-up file

`_start` (`0x100008`), `_exit` and `_root`: `src/runtime/crt0.S`.

* Sony ships the start-up file as assembly, `crt0.s`, and a CodeWarrior project assembles it as its first file: the stationery linker file places `crt0.s (.text)` first and aligns to 16 after it. The image has that shape: two `nop`s, the entry point, `_exit` and `_root` each after `.align 3`, zero fill to the next 16-byte boundary.
* From the main-thread setup to `_root` the instructions are Sony's file one for one; a register-clearing head, a byte/quadword/byte `.bss` clear, `_InitSys`, and the static constructor and destructor calls around `main` are added.
* No compiler writes it: it zeroes every register including `sp`, `gp` and `ra`, sets `gp` and `sp` from system-call results, and `_root` ends in a system call with no return.
* Register copies are encoded as `or`, which is how CodeWarrior's assembler writes `move` (its listing of Sony's file shows it); MWCC's inline assembler writes `addu` and `ee-as` writes `daddu`. The file spells them `or` so `ee-as` reproduces the bytes.
* The two leading `nop`s and the `_args` block stay outside the file: a function's object may hold only its own code.
* `tools/check.py` needed one fix for it: an `R_MIPS_26` jump to a local label keeps its offset in the instruction field (ELF REL), and `verify.apply_relocs` now adds that in-place addend.

### libkernl TLB trap

`_kTLBException` (`0x113bc0`, 284 bytes), `_kExitTLBHandler` (`0x113d00`, 244 bytes) and `_kDebugException`
(`0x113e00`, 288 bytes): `src/sony/libkernl/tlbtrap.S`.

* Sony's own build records it. The SDK 3.0.3 `libkernl.a` holds the three functions in one member, `tlbtrap.o`, whose
  file symbols name `tlbtrap.s` and which has none of the compiler markers its C siblings carry. Its `.text` is the
  executable's, relocated words masked: three functions at offsets `0x0`, `0x140` and `0x240`, which the executable
  keeps 64-byte aligned, and a debug function one padding word longer in the executable than in the member.
* No compiler writes them. They are kernel exception entries with no frame: each saves the general registers with
  `sq` through `k0`, reads HI, HI1, LO, LO1 and SA with `mfhi1`, `mflo1` and `mfsa`, reads Status, Cause, EPC and the
  bad-address registers, points EPC at a stub, clears EXL in Status and leaves through `eret`; the stub calls the
  registered handler with `sp` at the frame and ends in a `syscall` (`-84`) or a `break`. `_kExitTLBHandler` is the
  function that system call reaches: the syscall table at `0x4822a8` installs it as call `0x54`. It clears IE, EXL and
  the mode bits in Status, restores EPC, HI, HI1, LO, LO1, SA and the registers with `lq`, sets IE, EXL and user mode
  in Status (`ori 0x13`) and returns from the exception with `eret`.
* The file keeps the member's name for each register-save datum, which is data of the image (`EEREG`, the frame and
  the top of the handler stack, `EERH0`, `EERH1`, `EERL0`, `EERL1`, `EERSA` and `EEEPC`, at `0x55a700` and
  `0x55a900` to `0x55a928`), and takes the handler words `_kTLBRefillHandler` and `_kDebugHandler` from `tlbfunc.c`.
  Instructions are mnemonics in `noreorder` mode, as in the other kernel files; the member's two local labels, which
  the stubs' addresses are formed from, are the stub's own.
* No upstream text of the file exists. The `.S` is written from the member's symbols and the executable's code, as
  the syscall stubs are, and assembles to the executable's bytes.

### libkernl alarm patch: the user-mode dispatcher

`UserModeDispatcher` (40 bytes of `eenull`, copied by `alarm.c` to `0x82000`): `src/sony/libkernl/kpatch/eenull.S`,
a kernel patch source (`config/SLUS-20836/kernel-patches.tsv`), not an image function.

* No compiler writes it. The alarm interrupt returns into it in user mode: it sets `sp` to `0x81fc0` with no frame,
  calls the handler in `$3` with `jalr`, and goes back to the kernel through `syscall` with `$3 = -8`; it never
  returns.
* The SDK 3.0.3 `alarm.o` keeps the 40 bytes as its own `eenull` array beside the patch, with no symbol for the
  routine, and they equal DW4's. The five trailing zero words are the link's: `.p2align 4` and the `QUAD(0)` closing
  `.text` in `config/kernel-patch.ld`.
* The file assembles to those bytes under both `ee-as` builds.

`CallUserHandler` and `ReturnFromUserHandler` (`src/sony/libkernl/kpatch/alarmuser.S`, the other half of the
`srcfile` patch): the kernel side of an alarm handler's trip through user mode.

* No compiler writes them. `CallUserHandler` has no prologue: it keeps `ra` and `sp` through `$k0` in `.bss`,
  writes EPC with `mtc0`, moves the handler and its arguments into `$3..$6`, sets the Status UM and EXL bits and
  leaves through `eret`. `ReturnFromUserHandler` is system call 8: it masks Status with `~0x1b`, restores `ra` and
  `sp` and returns to `CallUserHandler`'s caller. C has no spelling for `$k0`, the COP0 writes or `eret`.
* The SDK 3.0.3 `alarm.o` holds the bytes inside its `srcfile` array with no symbols of their own, and they equal
  DW4's. The file assembles to them under the 2.10 `ee-as` that builds the patch.

## Open questions

* **Which compiler generated the R5900 `.S` files** before they were edited. Their `lui`/`ori` -1
  and loop scheduling point at a 2.9-ee release; a few details (`daddu` in strchr, filled `ld` loops
  in strlen) point at 2.96.
