# The `sd` callee-saved prologue: vendor library code, not MWCC

Two independent investigations reached the same conclusion: the functions that
save callee-saved registers with `sd` at 8-byte spacing are **Sony EE GCC output**, the SDK libraries and the CRI middleware linked into the
game, not Metrowerks code. A Sony EE GCC 2.96 build is kept
under `local/ee-gcc2.96/` and reproduces this prologue, so these functions *are* matchable as C — about a hundred of the Sony-built units
rebuild with it through `tools/cc.py` / `tools/eegcc_compile.py`, pinned per unit in `config/SLUS-20836/unit-compilers.tsv` (see
[the Sony compiler](#the-sony-compiler)). Until a unit is converted, its function is
without source: it links from the retail image and reads from the generated `asm/`.

* **Population:** 1,698-1,701 non-leaf functions (about 417 KB) in six contiguous blocks that hold 3,304 functions / 530 KB in total:
  `0x1029f8..0x12fef0` (Sony libdma, libipu/libmpeg, libpad, libmc, kernel syscall stubs), `0x225300..0x225700` (libmtap), `0x22e4b8..0x230c78`
  (CRI helper), `0x25b248..0x27edb0` (CRI ADX/AFS/ADXF), `0x280b98..0x2b5848` (CRI CFT/M2V/MPS/MPV/Sofdec), `0x4820d0..0x4831e8` (SDK tail).
* **Evidence:** the ELF carries `GCC2096 SCE2810` stamps beside each CRI library's build string; no `sq` saves and no `slt/sltu` into `at` inside the
  blocks; branch-likely instructions at 13.8 per 1000 words in the blocks and none in the 15,568 game functions; half the function starts are 8 mod 16
  (MWCC aligns to 16); `movn/movz` use 228 against 8 in the MWCC reference set.
* **MWCC cannot emit it:** four compiler builds at `-O0..-O4,p`, the hidden `--gcc-compat` options (`-mgp64`, `-mabi=64`, `-mcpu=r5900`, `-mips3`) all
  save with `sq`; there is no register-save, ABI or processor switch in `-help all`.
* **Share of the code:** the blocks are about 530 KB, roughly 11 points of the 4.5 MB code. 313 small leaf functions inside these blocks
  match from C. The census script is `scripts/analysis/sd_population.py`.

## The Sony compiler

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

* **CRI ADX/AFS, Sofdec/MPEG and libgcc** units rebuild at `-O2 -G0`. A macro must be a plain block,
  since a `do/while(0)` macro changes scheduling; a switch becomes a jump table only when every table
  index is a case label; volatile statistics words change delay-slot filling.
* **fdlibm (double and float) and newlib** (strtol/strtoul, mallocr) rebuild from C at `-O2 -G0 -g`.
  For libm, `ee-as` must receive `-g` so libcall delay slots keep their nops, and `-G0` so non-simple
  float literals use `lui`/`ori`/`mtc1`.
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

* **A second compiler build.** `0x102c00..0x117db8`, sceMc `0x117e58..0x11a330`, sceMtap and soft-float
  `__floatdidf`/`__floatdisf` appear to come from a different build than the available
  `2.96-ee-001003-1`, probably the `GCC2096 SCE2810` build stamped in the ELF. Signs: 16-byte register
  save slots (`s0`@0, `s1`@16, `ra`@32) in 91 of 125 functions of the first range, final calls kept as
  `jal` with an epilogue where ee-gcc emits a sibling `j`, unfilled delay slots, real `mult`/`mult1`
  for small constants, `lwu` zero-extension, branch targets on 4-byte boundaries, and libcalls named
  `__muldf3` where ee-gcc calls `dp*`. About twenty `-m`/`-f` flags change none of these, so functions
  with these signs have no source until that build is available. `0x11acc0..0x12fe90` uses the normal
  8-byte spacing.
* **`FUN_0010d0d0`**, a printf-family wrapper into `FUN_0010cad8` inside the Sony block, has no source.
  Under MWCC, `void f(int a0,...) { char d[48]; FUN_0010cad8(a0, (char*)__builtin_next_arg(d) - 56); }`
  reproduces the frame (144, `ra` at `sp+0`, spills `sp+88..136`, `a0` unhomed) and differs only in the
  order of words 1-4, which about 130 spellings do not move; the order looks gcc-scheduled. Worth
  trying under the Sony compiler.
* **`FUN_00119138`** (904 bytes) has no source. It looks like a Sony libcdvd-style RPC wrapper
  `int f(int a0,...)`: it copies six variadic words into a global array, then dispatches on the first
  (`0x8130`, `0x8140`, `0x8160`, `0x8170`, `0x81a0`, `0x81b0`, `0x81d0`, `0x9000..0x90f0`) to
  `FUN_0010e2a8` with a different argument shape per command. Control flow is known in outline only.
