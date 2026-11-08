# The `sd` callee-saved prologue: vendor library code, not MWCC

Two independent investigations reached the same conclusion: the functions that
save callee-saved registers with `sd` at 8-byte spacing are **Sony EE GCC output**, the SDK libraries and the CRI middleware linked into the
game, not Metrowerks code. A Sony EE GCC 2.96 build is kept
under `local/ee-gcc2.96/` and reproduces this prologue, so these functions *are* matchable as C — about a hundred of the Sony-built units
rebuild with it through `tools/cc.py` / `tools/eegcc_compile.py`, pinned per unit in `config/SLUS-20836/unit-compilers.tsv` (see
[the Sony compiler](#the-sony-compiler)). Until a unit is converted, its function is
without source: it links from the retail image and reads from the generated `asm/`.

* **Population:** 1,698-1,701 non-leaf functions (about 417 KB) in six contiguous blocks that hold 3,304 functions / 530 KB in total:
  `0x1029f8..0x130000` (Sony libgraph to libmc, newlib), `0x2252d8..0x225770` (libmtap), `0x22e4b8..0x230f50`
  (libgcc), `0x25b248..0x27ede0` (CRI ADX/AFS/ADXF), `0x280b98..0x2b5d50` (CRI CFT/M2V/MPS/MPV/Sofdec), `0x4820d0..0x4833c8` (Sony kernel-mode code,
  linked at `0x80074000` and up). `config/SLUS-20836/regions.tsv` holds these bounds.
* **Evidence:** the ELF carries `GCC2096 SCE2810` stamps beside each CRI library's build string; no `sq` saves and no `slt/sltu` into `at` inside the
  blocks; branch-likely instructions at 13.8 per 1000 words in the blocks and none in the 15,568 game functions; half the function starts are 8 mod 16
  (MWCC aligns to 16); `movn/movz` use 228 against 8 in the MWCC reference set.
* **MWCC cannot emit it:** four compiler builds at `-O0..-O4,p`, the hidden `--gcc-compat` options (`-mgp64`, `-mabi=64`, `-mcpu=r5900`, `-mips3`) all
  save with `sq`; there is no register-save, ABI or processor switch in `-help all`.
* **Share of the code:** the blocks are about 530 KB, roughly 11 points of the 4.5 MB code. 313 small leaf functions inside these blocks
  match from C. The census script is `scripts/analysis/sd_population.py`.

## The Sony libraries' compiler

The Sony runtime libraries (libgraph, libdma, libmpeg, libipu, libkernl, libcdvd, libpad, libsdr, libmc,
libmtap) are not built by the 2.96 below but by **EE GCC 2.9-ee-991111-01**, the Cygnus-based release of
the first SDK (`ee-gcc2.9-991111-01.tar.xz` in the decomp.me compiler releases, pinned as `ee-gcc-2.9`).
Of the 991111 releases only -01 writes two hazard `nop`s before a `div.s` (`FUN_00115a58`).

Two libraries were assembled differently. libkernl needs this release's own assembler (`ee/bin/as`),
which leaves a delay slot unfilled where a store could have moved into it (`FUN_0010c7b0`,
`FUN_00113398`). libmpeg needs one that fills it: the 2.96 kit's `ee-as` (2.10-ee), which
`FUN_00108cc8`, `FUN_0010a138` and `FUN_001071f0` show. libmpeg's units are pinned as `ee-gcc-2.9-as210`,
the same compiler with that assembler; `tools/download_tools.py` builds it from the two releases. The
other eight libraries match the same either way and stay on the release's own assembler.
It reproduces their signs: register saves at 16-byte spacing with `sd`, a frameless sibling `j` for a
function whose only call is a tail call (which 2.96 cannot produce), a final `jal` with an epilogue
after other work, unfilled delay slots, real `mult` for small constants, `lwu` zero-extension and
`__muldf3`-style libcalls. Every function of those libraries that matched under 2.96 still matches
under it apart from a few in libmpeg and libkernl, and raw m2c drafts match under it where none match
under 2.96. Its release keeps the assembler at `ee/bin/as`, which `tools/eegcc_compile.py` falls back
to. libmtap's `FUN_002252d8` is an empty varargs function under it. CRI, newlib and libgcc fail under
2.9-ee and stay on 2.96, as does the kernel-mode code until it is tested further.

## The CRI and newlib compiler

A Sony EE GCC 2.96 build (`2.96-ee-001003-1`, the `GCC2096` stamp in the ELF) is kept under `local/ee-gcc2.96/`
(public `ee-gcc2.96.tar.xz` from the decomp.me compiler releases, SHA-256
`0590d2ca9da8f5903889d66761220d14b47a8d14ba987ca53db84a1650a1fd0a`; a 32-bit Linux executable, so the host needs the i386 loader).
It reproduces the `sd` callee-saved prologue, so the functions above are matchable as C:

* Pin a unit to it with a `config/SLUS-20836/unit-compilers.tsv` row naming `local/ee-gcc2.96/bin/ee-gcc` and a flag row in
  `config/SLUS-20836/unit-flags.tsv` (`FUN_0025b968` builds with `-O2 -G0`). Everything that compiles a unit builds its
  command in `tools/cc.py`; an `ee-gcc` compiler runs through `tools/eegcc_compile.py`, because `ee-gcc -c` crashes inside
  `cc1` and the object is built with `-S` followed by the sibling `ee-as`, whose symbol table the script repairs for GNU ld.
* Data and unnamed callees use address-bearing names (`D_00498a38`) exactly as for MWCC units.
* The open-source [ps2sdk](https://github.com/ps2dev/ps2sdk) (reference only) names the
  structures and call sequences of the libraries the Sony blocks contain. Its code is not copied; the recovered source is
  written from the retail bytes.
* Recovering one of these functions as C adds it to the decompiled and matched figures.

### What rebuilds with it

* **CRI ADX/AFS and Sofdec/MPEG** units rebuild at `-O2 -G0`. A macro must be a plain block,
  since a `do/while(0)` macro changes scheduling; a switch becomes a jump table only when every table
  index is a case label; volatile statistics words change delay-slot filling.
* **newlib and libgcc** build at `-O2 -G0 -g` throughout (`0x11acc0..0x130000`, `0x22e4b8..0x230f50`):
  `ee-as` must receive `-g` so libcall delay slots keep their nops, and `-G0` so non-simple float
  literals use `lui`/`ori`/`mtc1`. Members without a libcall match either way.
* **newlib is a snapshot between 1.9.0 and 1.10.0.** fdlibm follows 1.10.0 with
  `_FLT_LARGEST_EXPONENT_IS_NORMAL` and `_FLT_NO_DENORMALS` (the `FLT_UWORD_*` macros), except
  `ef_asin.c`, which keeps 1.9.0's constants. `dtoa.c`, `strtod.c`, `mprec.c` and `signal.c` are 1.10.0;
  `sscanf`/`vfscanf` are 1.9.0 with 1.8.2's unsigned `n < width`, and `vfprintf.c` is 1.9.0 with a plain
  `double _fpvalue` and `expbuf[MAXEXP]`. The configuration: 64-bit `long`, 32-bit `__ULong`,
  `MALLOC_ALIGNMENT` 16, `SIZE_T_SMALLER_THAN_LONG`, no `__SCLE`, `FLT_ROUNDS` not 1 (strtod's fast
  path is compiled out), and each mallocr piece a separate object. A `static const` scalar whose every
  use folds into `lui`/`ori` has no retail `.rodata`, so it is written as a macro.
* **libgcc** is gcc's `libgcc2.c` (the 64-bit division, `__floatdi*` and `__fix*di` routines) and a
  Sony-modified `fp-bit.c` built with `US_SOFTWARE_GOFAST`, which is where the `dpadd`/`dpmul`/`dptoli`
  names in `config/SLUS-20836/compiler-runtime-symbols.tsv` come from. Sony's `fp-bit.c` does not round in
  `pack_d`, `dpmul` or `dpdiv`, flushes denormals to zero, and its `isnan`/`isinf`/`iszero` are inline
  functions (macros change the compare). Each division object carries its own `__clz_tab` copy.
  A `static __inline__` helper inlines under `tools/check.py` only from a header (`include/dw4/fp_bit*.h`).
* **`mprec.c` and `signal.c` are whole-file units** (`src/newlib/`; `0x1273e0..0x1283f8`, 17
  functions, and `0x129940..0x129c28`, 8 functions). A call compiles differently when its callee is
  defined earlier in the same file: `multadd` and `pow5mult` reproduce only after `Balloc` and `i2b`,
  and `__sigtramp_r`'s delay slot is `bnez` rather than `bnezl` only after `_init_signal_r`. Their
  profile adds `-ffunction-sections`, which leaves the code unchanged and gives each function its own
  section, as a whole-file object needs.
* **mallocr's `initial_top` is upstream's `(mchunkptr)(bin_at(0))`**: the same address spelled as
  `(mchunkptr)av_` moves a temporary in `malloc_extend_top` and changes its registers.
* **An ee-gcc object's own `.rodata`** (strings, `li.d` literals and switch tables together, as in
  `_dtoa_r`, `_vfprintf_r` and the fdlibm kernels) is owned through a reviewed row in
  `config/SLUS-20836/rodata-pools.tsv`, which `tools/verify.py` compares byte for byte with retail. A
  literal loaded through `$at` stays a literal in the C; an `extern double` compiles to a plain `lui`/`ld`.
* **The float-spilling varargs wrappers** `FUN_00265928`, `FUN_002658a8`, `FUN_002659a0`,
  `FUN_0027e2f0`, `printf` (`0x128528`), `FUN_002777f8`, `FUN_0029a320` and `FUN_0010d108` are Sony EE
  libc code built with gcc. No MWCC variant emits `$f12..$f19` spills in a varargs prologue, MWCC
  saves s registers with `sq` and puts `ra` at `sp+0` below the locals, and it re-materialises `lui`
  bases gcc keeps in a register. Callees: `0x12fde0` vsprintf, `0x10d108` buffered output, `0x12724c`
  memset. All but `FUN_0010d108` match.

### Recurring source shapes

* m2c drops pass-through arguments, so prototypes are read from the retail code.
* A final `jal` that is not a sibling call means an implicit-int function with no return statement.
* `lui`+`addiu`+access at `0(reg)` on a once-used global means it is volatile.
* The scheduler moves the last independent store of a run early, so source stores are in field order.
* Field types decide which loads may move above which stores, through type-based aliasing: a
  ring or chunk struct is `{char *start; int size; char *cur; int count}`, not four ints.
* Retail often leaves stale values in `a1`-`a3` at a call. The callee's own matched source gives
  its real arity, and an `int` callee whose result is ignored still differs from a `void` one.
* A function that keeps `v0` out of its body returns its first call's status:
  `r = f(h); if (r) return g(0, code); ...; return r;`.
* An explicit `return;` after a final call inside an `if` gives the `j` sibling call.
* `if (x & 0x10) return 0; return 1;` gives `andi`/`sltiu`; `(x & 0x10) == 0` gives a shift.
* Case bodies follow source order, and a sparse switch is a compare tree. Some trees need a case
  merged into `default`, whose value retail does not pin down.
* ee-gcc truncates decimal float literals, so a literal is written as the float's exact decimal
  value, such as `-25.0879993438720703125f`.
* Empty delay loops are plain C: `for (i = 0; i < 64; i++);` unrolls by 32,
  `i = 10000; while (i--);` gives the step-4 form, and `ee-as` pads short loops itself.
* Locals spaced 8 bytes apart on the stack are `long long`. A struct of ints assigned whole gives
  the `ldl`/`ldr` copy.
* Three symbols (`FUN_00298d78`, `FUN_002a4bc8`, `FUN_002ae2b8`) used to count the alignment `nop`
  after their return. The object's 8-byte alignment supplies that word.
* Fixed-table loops are count-up `for` loops; varargs use `__builtin_va_list`.
* The SDK libc follows newlib's source order.

`tools/m2c_batch.py` with the gcc target drafts these units.

### The assembler's overlapping copy

The 32-bit Sony `ee-as` (GNU assembler `2.10-ee-001003-1`) copies an expanded macro over itself with
an overlapping memcpy in `md_convert_frag` (`memcpy (fixptr - old, fixptr, new)`, old 4, new 12, for
a load from a label). glibc's SSSE3 memcpy gets that copy wrong at some alignments, so the first
instruction comes out as the last: `lui`, `addu`, `lw` becomes `lw`, `addu`, `lw` (or `ld`). Which
functions are hit depends on where the C library places the block, so results differ between systems
from identical assembly.

Native builds set `glibc.cpu.hwcaps=-SSSE3` (with `-SSE2`, so the choice does not depend on the CPU)
and `glibc.malloc.mmap_threshold=0`. A preloaded memcpy that calls memmove
([`docker/memmove_shim.c`](../../docker/memmove_shim.c)) gives a full match alone; the container uses
it with the settings. `MALLOC_PERTURB_`, disabling tcache, an empty environment, the locale and
disabling ASLR change nothing.

## Open questions

* **newlib functions without C.** `memcpy`, `memmove`, `memset`, `memchr`, `memcmp`, `setjmp`
  (`0x129880`), `longjmp` (`0x1298d8`) and the 128-bit string routines (`strcat`, `strchr`, `strcmp`
  `0x12a4a4`, `strcpy`, `strlen`, `strncat`, `strncmp`, `strncpy`) are assembly files, not ee-gcc 2.96
  output with a few MMI statements. 2.96 aligns every loop top with a padding `nop`, starts each object
  on 8 bytes, fills a short loop's delay slot and loads -1 as `li`; these keep unaligned loops,
  4-byte object starts, `bne; nop` loop ends (the form `ee-as` gives a reorder-mode `.s`) and the
  `lui`/`ori` pair of a hand-written `li 0xffffffff`. setjmp/longjmp save `s0`-`s8`, `sp` and `ra` with
  `sq` and keep `noreorder` slots; memcpy and memmove hold the destination in `t0`; strcat saves with
  `sq`. Some `pcpyud` operands are live, unrelated registers, which suggests compiler output kept and
  edited as `.S`. `__builtin_mips5900_*` casts between `V2DI` and TImode insert `por` moves. Open:
  `strncat`, `strncmp` and `strncpy` have gcc-style loop padding, and `strncat`'s byte tail follows
  2.9-ee-991111-01 output; a C-and-asm candidate matching under that compiler would place them.
* **The other Sony libraries' assembler.** Every matched function of libgraph, libdma, libipu, libcdvd,
  libpad, libsdr, libmc and libmtap matches with either assembler, so which one built them is open.
  `FUN_00114d88` also matches under `2.9-ee-990721`.
* **`FUN_00119138`** (904 bytes) has no source. It looks like a Sony libcdvd-style RPC wrapper
  `int f(int a0,...)`: it copies six variadic words into a global array, then dispatches on the first
  (`0x8130`, `0x8140`, `0x8160`, `0x8170`, `0x81a0`, `0x81b0`, `0x81d0`, `0x9000..0x90f0`) to
  `FUN_0010e2a8` with a different argument shape per command. It also saves and sets `gp`, which C
  cannot spell, so it waits with the other inline-`asm` functions.
