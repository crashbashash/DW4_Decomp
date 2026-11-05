# The `sd` callee-saved prologue: vendor library code, not MWCC

Two independent investigations (census A (archived outside the repository), census B (archived outside the repository)) reached the same conclusion: the functions that
save callee-saved registers with `sd` at 8-byte spacing are **Sony EE GCC output**, the SDK libraries and the CRI middleware linked into the
game, not Metrowerks code (finding [#1076](../findings/findings-1001-1250.md#f1076) is resolved by [#1078](../findings/findings-1001-1250.md#f1078)). A Sony EE GCC 2.96 build is kept
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
* The open-source [ps2sdk](https://github.com/ps2dev/ps2sdk) (cloned under `local/ps2sdk-ref/`, reference only) names the
  structures and call sequences of the libraries the Sony blocks contain. Its code is not copied; the recovered source is
  written from the retail bytes.
* Recovering one of these functions as C adds it to the decompiled and matched figures.
