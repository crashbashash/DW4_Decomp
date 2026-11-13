# The `sd` callee-saved prologue: vendor library code, not MWCC

The functions that save callee-saved registers with `sd` at 8-byte spacing are **Sony EE GCC output**,
the SDK libraries and the CRI middleware linked into the game, not Metrowerks code. A Sony EE GCC 2.96
build is kept under `local/ee-gcc2.96/` and reproduces this prologue, so these functions *are*
matchable as C. The Sony-built units
rebuild with it through `tools/cc.py` / `tools/eegcc_compile.py`, pinned per unit in `config/SLUS-20836/unit-compilers.tsv` (see
[the Sony compiler](#the-sony-libraries-compiler)).

* **Population:** 1,690-1,694 non-leaf functions (about 415 KB) in five contiguous blocks that hold 3,295 functions / 527 KB in total:
  `0x1029f8..0x130000` (Sony libgraph to libmc, newlib), `0x2252d8..0x225770` (libmtap), `0x22e4b8..0x230f50`
  (libgcc), `0x25b248..0x27ede0` (CRI ADX/AFS/ADXF), `0x280b98..0x2b5d50` (CRI CFT/M2V/MPS/MPV/Sofdec).
  `config/SLUS-20836/regions.tsv` holds these bounds. libkernl's kernel patches (`0x481f28..0x4834c8`) are
  EE GCC code too, but linked at `0x80074000` and up and kept as data.
* **Evidence:** the ELF carries `GCC2096 SCE2810` stamps beside each CRI library's build string; no `sq` saves and no `slt/sltu` into `at` inside the
  blocks; branch-likely instructions at 13.8 per 1000 words in the blocks and none in the 15,568 game functions; half the function starts are 8 mod 16
  (MWCC aligns to 16); `movn/movz` use 228 against 8 in the MWCC reference set.
* **MWCC cannot emit it:** four compiler builds at `-O0..-O4,p`, the hidden `--gcc-compat` options (`-mgp64`, `-mabi=64`, `-mcpu=r5900`, `-mips3`) all
  save with `sq`; there is no register-save, ABI or processor switch in `-help all`.
* **Share of the code:** the blocks are about 530 KB, roughly 11 points of the 4.5 MB code. The census script is `scripts/analysis/sd_population.py`.

## The Sony libraries' compiler

The Sony runtime libraries (libgraph, libdma, libmpeg, libipu, libkernl, libcdvd, libpad, libsdr, libmc,
libmtap) are not built by the 2.96 below but by **EE GCC 2.9-ee-991111-01**, the Cygnus-based release of
the first SDK (`ee-gcc2.9-991111-01.tar.xz` in the decomp.me compiler releases, pinned as `ee-gcc-2.9`).
Of the 991111 releases only -01 writes two hazard `nop`s before a `div.s` (`sceTimerBusClock2Freq`).

The libraries were not all assembled the same way. libkernl needs this release's own assembler (`ee/bin/as`),
which leaves a delay slot unfilled where a store could have moved into it. libmpeg, libgraph and libdma need one
that fills it: the 2.96 kit's `ee-as` (2.10-ee), which `sceMpegInit`, `sceGsResetPath` and `sceDmaReset` show. Their
units are pinned as `ee-gcc-2.9-as210`, the same compiler with that assembler; `tools/download_tools.py` builds it
from the two releases. The other six libraries match the same either way and stay on the release's own assembler.
It reproduces their signs: register saves at 16-byte spacing with `sd`, a frameless sibling `j` for a
function whose only call is a tail call (which 2.96 cannot produce), a final `jal` with an epilogue
after other work, unfilled delay slots, real `mult` for small constants, `lwu` zero-extension and
`__muldf3`-style libcalls. Every function of those libraries that matched under 2.96 still matches
under it apart from a few in libmpeg and libkernl, and raw m2c drafts match under it where none match
under 2.96. Its release keeps the assembler at `ee/bin/as`, which `tools/eegcc_compile.py` falls back
to. CRI, newlib and libgcc fail under 2.9-ee and stay on 2.96.

### Sony's prebuilt libraries

DW4's libraries are release 2.8.0 (their descriptors; libmc 2.8.1), which is not public. The runtime
libraries of the July 2005 SDK, release 3.0.3 (Internet Archive item
`PlayStation2July2005SDKversion3.0.3`, installer `RTLibs&ToolchainSetup.exe`), are later, but a
function Sony left unchanged is still DW4's bytes: 173 functions of 64 bytes or more match one DW4
function each, with only the linker-filled words differing (libkernl 114, libcdvd 16, libpad 13,
libdma 11, libmpeg 5, libipu 5, libgraph 3, libsdr 3, libmc 3). They carry the library's own names
(`config/SLUS-20836/names/sony-sdk.tsv`), and their units sit in `src/sony/<library>/`.

* Every one of those objects is C (it carries `gcc2_compiled.`) and has no `.mdebug.eabi64` section.
  ee-gcc 2.96 writes that section into every object and 2.9-ee does not, so this confirms the
  2.9-ee build independently of the code shapes above.
* A function smaller than 64 bytes is not named this way: once its relocated words are masked, short
  wrappers match unrelated code (a 28-byte HTTP function matches a game function).

### libmtap is one file

libmtap (`src/sony/libmtap/libmtap.c`, `0x2252d8..0x225764`) is a whole-file unit: its seven functions
sit together, its five 40-byte `sceSifClientData` clients and the 64-byte-aligned 128-byte RPC buffer
are one contiguous `.bss` block (`0x56d6c0..0x56d840`), and its error strings run in code order from
`0x4e7858`. The file's first function, `debug_printf`, is an empty varargs `static` that every libmtap
error message goes to, the release build's disabled debug print; the version-mismatch report alone
goes to the runtime's real print routine. `sceMtapInit` binds mtapman.irx's servers
`0x80000901..0x80000905`, one per call that follows it, and checks the module's major version is 3.

* Under 2.9-ee `-ffunction-sections` leaves the code unchanged, as under 2.96. `.rdata` comes out as
  `.rodata`, and both 2.9-ee assemblers write REL relocations.
* The `static` clients and buffer are `.lcomm`s the assembler lays out in declaration order with the
  buffer's 64-byte alignment, which is retail's layout, so they are the file's own `.bss` rather than
  externs.
* `"libmtap: bind failed\n"` is the file's first string, so it is written in each bind loop, before the
  version check: the compiler merges the five identical `debug_printf`-and-`return 0` blocks into one, which
  is retail's single target of the five `bltz`. Written once after a `goto`, the string moves after the
  version messages.

## The CRI and newlib compiler

A Sony EE GCC 2.96 build (`2.96-ee-001003-1`, the `GCC2096` stamp in the ELF) is kept under `local/ee-gcc2.96/`
(public `ee-gcc2.96.tar.xz` from the decomp.me compiler releases, SHA-256
`0590d2ca9da8f5903889d66761220d14b47a8d14ba987ca53db84a1650a1fd0a`; a 32-bit Linux executable, so the host needs the i386 loader).
It reproduces the `sd` callee-saved prologue, so the functions above are matchable as C:

* Pin a unit to it with a `config/SLUS-20836/unit-compilers.tsv` row naming `local/ee-gcc2.96/bin/ee-gcc` and a flag row in
  `config/SLUS-20836/unit-flags.tsv` (a CRI unit builds with `-O2 -G0`). Everything that compiles a unit builds its
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
  literals use `lui`/`ori`/`mtc1`. Members without a libcall match either way. newlib adds
  `-fno-builtin`, as its own build does: fdlibm calls `fabs` as a function, and the builtin would
  inline it.
* **newlib's names and files come from Sony's `ee001003_1` `libc.a` and `libm.a`.** Each `src/newlib/`
  file is one archive object in retail order, and an object is placed only where its whole `.text`
  matches with relocated words masked and every call lands on the function of that name. A symbol the
  object keeps local has its name from the object's symbol table, and so does a datum, through the
  object's `lui`/`lo` relocations. Where one name has several retail copies, a copy takes its object as
  a suffix: `__sprint_vfiprintf`, `__sbprintf_vfiprintf`, `Zero_fmod` (`ef_fmod.o` keeps `Zero` as its
  own static) and `huge_ceil`, `huge_floor`. Wrappers that differ only in their callee, such as `realloc` and
  `memalign`, are told apart by that call.
  `src/sony/libkernl/` holds what the objects call by name: `_exit`, `close`, `lseek`, `isatty`, `fstat`,
  `getpid`, `kill`.
* **newlib is a snapshot between 1.9.0 and 1.10.0.** fdlibm follows 1.10.0 with
  `_FLT_LARGEST_EXPONENT_IS_NORMAL` and `_FLT_NO_DENORMALS` (the `FLT_UWORD_*` macros), except
  `ef_asin.c`, which keeps 1.9.0's constants. `dtoa.c`, `strtod.c`, `mprec.c` and `signal.c` are 1.10.0;
  `sscanf`/`vfscanf` are 1.9.0 with 1.8.2's unsigned `n < width`, and `vfprintf.c` is 1.9.0 with a plain
  `double _fpvalue` and `expbuf[MAXEXP]`. The configuration: 64-bit `long`, 32-bit `__ULong`,
  `MALLOC_ALIGNMENT` 16, `SIZE_T_SMALLER_THAN_LONG`, no `__SCLE`, `FLT_ROUNDS` not 1 (strtod's fast
  path is compiled out), and each mallocr piece a separate object. A `static const` scalar whose every
  use folds into `lui`/`ori` has no retail `.rodata`, so it is written as a macro.
* **libgcc** is gcc's `libgcc2.c` (`src/libgcc/libgcc2.c` and one file per division object) and a
  Sony-modified `fp-bit.c` built with `US_SOFTWARE_GOFAST` as `dp-bit.o` and `fp-bit.o` (`src/libgcc/dp_bit.c`,
  `fp_bit.c`), which is where the `dpadd`/`dpmul`/`dptoli` names come from. The routine names are those of
  the 2.9-ee `libgcc.a`, whose objects hold the same routines in nearly the retail order. GCC-built objects
  call the same code as `__adddf3`, `__muldf3`, `__divdf3` and `__floatsidf`, which
  `config/SLUS-20836/compiler-runtime-symbols.tsv` resolves. Sony's `fp-bit.c` does not round in
  `__pack_d`, `dpmul` or `dpdiv`, flushes denormals to zero, and its `isnan`/`isinf`/`iszero` are inline
  functions (macros change the compare). Each division object carries its own `__clz_tab` copy.
  A `static __inline__` helper inlines under `tools/check.py` only from a header (`include/dw4/dp_bit.h`,
  `fp_bit.h`, `libgcc_longlong.h`).
  Open question: the name `__thenan_df` at `0x4e83a8` follows upstream gcc 2.96's shared constant; the 2.9-ee
  archive has a per-object `thenan` instead, and no 2.96 `libgcc.a` is available to confirm it.
  `__muldi3` at `0x22e440` sits just below the region's start in `regions.tsv`.
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
* **The float-spilling varargs wrappers**, such as `printf` (`0x128528`), are Sony EE
  libc code built with gcc. No MWCC variant emits `$f12..$f19` spills in a varargs prologue, MWCC
  saves s registers with `sq` and puts `ra` at `sp+0` below the locals, and it re-materialises `lui`
  bases gcc keeps in a register. Callees: `0x12fde0` vsprintf, `0x10d108` buffered output, `0x12724c`
  memset.

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
  `i = 10000; while (i--);` gives the step-4 form. The compiler, not `ee-as`, pads a short loop: before a
  backward branch closing fewer than five counted instructions it writes `nop`s up to five, and an `asm`
  statement counts as one however many lines it holds, so the pad count tells how many statements a loop had.
* Locals spaced 8 bytes apart on the stack are `long long`. A struct of ints assigned whole gives
  the `ldl`/`ldr` copy.
* Three symbols used to count the alignment `nop`
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

* **newlib strings and the `huge` copies.** `C_locale`, `empty_locale` and the `*_format` strings are
  named by their text, since the objects hold them in unnamed `.rodata`. `huge_ceil` and `huge_floor`
  follow upstream's `static const double huge`, whose local symbol the objects do not keep.
* **The second `free` thunk** (`0x2f0050`) is a second jump to `free` beside the first; what separates the two
  in Alchemy is not known.
* **newlib's R5900 assembly.** setjmp, longjmp and the string and memory routines come from
  `libc/machine/r5900/*.S` in Sony's `ee001003_1` `libc.a`, and are `.S` sources here
  ([assembly sources](assembly-sources.md)). Which compiler first generated those files is open.
* **The other Sony libraries' assembler.** Every matched function of libipu, libcdvd, libpad, libsdr, libmc
  and libmtap matches with either assembler, so which one built them is open.
* **libmtap's names.** `sceMtapChangeThreadPriority`'s two arguments are named as mtapman's high and low
  thread priorities by guess. The SIF RPC bind and call routines it uses and the print routine keep
  their address names, shared with every other Sony library.
