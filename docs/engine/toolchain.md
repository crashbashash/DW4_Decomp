# Original Compiler (Metrowerks CodeWarrior for PS2)

Status: **identified, running, and reproducing the retail code byte-for-byte.**
The default matching compiler reproduces thousands of recovered functions, but
its identity is not proof of the exact original compiler build. The complete
combat Lua run now also needs a content-pinned alternate compiler for thirteen
of its bodies. See [per-unit requirements](unit-compilers.md) and findings
[#1034](../findings/findings-1001-1250.md#f1034)/#1036; the earlier unique-build conclusion in [#302](../findings/findings-0251-0500.md#f302) is unconfirmed.

## Summary

`game.elf` was built with **Metrowerks CodeWarrior for PlayStation 2**. This is the
proprietary (never open-sourced) MWCCPS2 toolchain, discontinued ~2005 and now owned
by NXP (via Motorola → Freescale). It is *not* legally redistributable, but the decomp
community (decomp.me ecosystem) archives it as abandonware, exactly like the IDO/SGI
compilers the SM64/OOT decomp projects use.

`tools/mwcps2/` is **not** in this repo (proprietary, and the rule here is that only
analysis text is committed). Put your copy under the gitignored `local/mwcps2`, or,
anywhere else, with `DW4_MWCC` pointing at it.

## Evidence in the binary

| Signal | Value | Where |
| --- | --- | --- |
| `.comment` section | `MW MIPS C Compiler (2.4.1.01)` + `PlayStation2` | `readelf -p .comment game.elf` — **not identifying, see below** |
| Linker layout | single merged `main` section (unnamed PROGBITS, `WAX`) at `0x00100000` — text+data+rodata joined | `readelf -S` section [4] |
| Overlays | none (`MWo` header absent) — whole 4.5 MB in one section, fits in RAM | `strings -a game.elf | grep MWo` → empty |
| ISA | `e_flags` `0x20924000` (`EF_MIPS_MACH_5900`, eabi64, mips3) | `readelf -h` |

The `.comment` string is written by the **linker (MWLD)**, and (per
[decomp.wiki/compilers/MWCC](https://decomp.wiki/compilers/MWCC)) a version
number can be shared across multiple MWCCPS2 releases. The `2.4.1.01` string is
therefore necessary-but-not-sufficient evidence; see "Fingerprinting" below.

## Local archive (gitignored)

```
local/
├── wibo                                    ← the Win32 loader that works
└── mwcps2/
    ├── 3.0-011126/mwccps2.exe   CRC32 C82F0A93   <- default matching compiler
    ├── 2.4/       mwccps2.exe   CRC32 D37D90D4   <- near miss (.comment matches, codegen does not)
    ├── 2.3.3/     mwccps2.exe
    └── mwcps2-{2.4-001213,2.3.3-000906}.tar.gz
```

Source (GitHub releases of `decompme/compilers`):
```
https://github.com/decompme/compilers/releases/download/compilers/mwcps2-3.0-011126.tar.gz
https://github.com/decompme/compilers/releases/download/compilers/mwcps2-2.4-001213.tar.gz
https://github.com/decompme/compilers/releases/download/compilers/mwcps2-2.3.3-000906.tar.gz
```
And the loader: `https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64`

SHA-256:
```
0ebe09436b4163c3a109b0431517281501d2de1bd5a0b049d33057710a943e3e  mwcps2-2.4-001213.tar.gz
c2a4e463f8f7b324350d6bfb26d6daed83f4d5cb46df8b20dcfec8617b22ad5d  mwcps2-2.3.3-000906.tar.gz
```

All executables are **PE32 console binaries for x86 Windows** (`file` confirms),
so they must run under a Win32 loader. Use **wibo**, not Wine — see "Running it".

## Move-idiom fingerprint: useful exclusion, incomplete identity

`.comment` is `MW MIPS C Compiler (2.4.1.01)`, and that string is emitted by more
than one release — 2.4 *and* 3.0 both produce it, and `mwldps2.exe` reports it in
every version. It is a **backend/linker version string, not a build id**. Verified by
compiling a fingerprint function and diffing `.comment`:

| Build | `mwccps2.exe` CRC32 | fingerprint `int f1(int a){return a;}` | object `.comment` |
| --- | --- | --- | --- |
| 2.3.3 (000906) | — | `paddub v0,a0,zero` | `2.3.1.01` |
| 2.4 (001213) | `D37D90D4` | `paddub v0,a0,zero` | `2.4.1.01` |
| 3.0.1b87 / b119 / b145 | — | other | `3.0.0` |
| **3.0 (011126)** | **`C82F0A93`** | **`move v0,a0`** | **`2.4.1.01`** |
| `game.elf` (retail) | — | **`move v0,a0`** (413×) and **`paddub` 0×** | `2.4.1.01` |

The register-move comparison rejects incompatible candidates for this source
spelling: the retail ELF contains **zero** `paddub v0,a0,zero` and 413
`daddu v0,a0,zero` (what `move` encodes as). A compiler that emits the former for
the simple identity function fails this fingerprint. Agreement alone cannot
prove original provenance; the complete combat bodies demonstrate the limit.

## Running it

```sh
# wibo is the transport that works; Wine fails on the FLEXlm license check
local/wibo local/mwcps2/3.0-011126/mwccps2.exe -c -O4,p f.c -o f.o

# or via the harness (compares against the retail ELF in one step)
python3 scripts/match_func.py 0x151090 cand.c f1
```

**Wine does not work.** Under Wine the compiler aborts with
`License check failed: Cannot find license file ... Feature: Win32_Plugins_MIPS_PS2`
(FLEXlm). The decompme archives ship no `license.dat`, and the community's
`archive.org/details/compilers-no-license` collection is explicitly *"compilers …
[that] don't contain licenses needed to activate them, so they need to be cracked"*.
Under **wibo** (the N64/PS2 decomps' loader; `decompals/wibo`, one static binary) the
same binary compiles with no license prompt at all — no patching needed. Other real
PS2 decomps do the same (`WIBO := $(BIN_DIR)/wibo` in 3s-decomp's Makefile).

## Verified matches

First three targets, all byte-identical at `-O4,p` (see `scripts/match_func.py`):

| Target | Source | Result |
| --- | --- | --- |
| `0x151090` | `int f1(int a) { return a; }` | MATCH |
| `0x10b5c8` | `int f1(void) { return -1; }` | MATCH |
| `0x124d40` | `void f1(void) { return; }` | MATCH |

So **`-O4,p` reproduces retail code, and `wibo` + `3.0-011126` is the build to use.**
These are deliberately trivial leaf functions; the real test is a function with calls,
globals and control flow, which is the next step below — do not read three 8-byte
matches as "the whole toolchain question is settled".

## Fingerprinting — reproducible, with an incomplete provenance conclusion

The original comparison: compile a function whose codegen differs between
candidates and diff it against the ELF. `scripts/match_func.py` automates it
(`--flags`, `--mwcc`, `--wibo`). To test another candidate build, point `--mwcc` at it
and use `0x151090` with `int f1(int a){return a;}`. A differing move idiom rules
out that build for this source spelling; agreement does not uniquely identify
the original toolchain. Complete-function comparisons remain necessary.

Still open: the other optimisation sub-flags (`-O4,p` matches on the three above, but
`-O3` produces the same code for them, so the level is not yet pinned by evidence from
a function that can distinguish them), and the `main`-section merge /
`.init`/`.ctor` static-init emission.

## Legal note

CodeWarrior for PS2 is proprietary (Metrowerks / NXP). These archives circulate
as abandonware; using them to *understand* the original codegen is the same
gray area as the N64 decomp scene, not a clean open-source tool. The compiler
itself should not be redistributed further from here.

## References

- https://decomp.wiki/compilers/MWCC — MWCCPS2 codegen quirks, `main` section, overlay headers, active PS2 MWCC decomp projects
- https://github.com/decompme/compilers — compiler archive source
- https://github.com/Raikaru/mwccps2-debugger — matching-decomp tooling
- https://daniel-mccarthy.github.io/MW/ — Metrowerks CodeWarrior release catalog
