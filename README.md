# Digimon World 4 — matching decompilation

A work-in-progress matching decompilation of the PS2 release of *Digimon World 4* (USA, `SLUS-20836`):
readable, evidence-named source that rebuilds the retail executable byte for byte. The repository also
holds the analysis tools, tests and reference evidence that support the recovery.

| Start here | |
| --- | --- |
| Status and findings | [Progress](PROGRESS.md), [documentation](docs/README.md) |
| Source and tools | [Source layout](src/README.md), [build tools](tools/README.md), [analysis](scripts/analysis/README.md), [analysis and capture scripts](scripts/README.md), [testing](testing/README.md), [reference](docs/reference/README.md) |
| Build and validation | `make check`, `make link`, `make typed-check` |

Run commands from the repository root. Game data and toolchains are never committed: see
[Installation](#installation) for where they go. Progress:

<!-- progress:start -->
| Region | Size | Matched | Readable |
| --- | ---: | ---: | ---: |
| Game | 1106 KB | 86.2 % | 6.0 % |
| Alchemy engine | 1563 KB | 69.7 % | 3.3 % |
| Lua 4.0.1 interpreter | 70 KB | 100.0 % | 100.0 % |
| CRI ADX | 138 KB | 39.2 % | 0.0 % |
| CRI Sofdec | 204 KB | 57.0 % | 0.0 % |
| libpng and zlib | 90 KB | 100.0 % | 100.0 % |
| Sony SDK | 96 KB | 58.2 % | 0.8 % |
| newlib | 84 KB | 100.0 % | 100.0 % |
| libgcc | 11 KB | 100.0 % | 100.0 % |
| Metrowerks runtime | 10 KB | 29.0 % | 0.0 % |
| Static initialisers | 10 KB | 41.5 % | 0.0 % |
| **Total** | **3383 KB** | **74.8 %** | **11.1 %** |

The full figures and the verification debt are in [PROGRESS.md](PROGRESS.md).
<!-- progress:end -->

- This repo contains a **work-in-progress matching decompilation** of *Digimon World 4* (USA,
  `SLUS-20836`) — an ELF32 MIPS R5900 (PS2 Emotion Engine) binary. Every matched function is verified
  byte-identical to retail with the original compiler; the table above shows how much is done.
- Code that is not decompiled yet is linked from your own retail executable. That is why the build
  comes out byte-identical to retail today: it does not mean the decompilation is finished.
- Naming and documentation of the source code and data structures are in progress; `PROGRESS.md`
  carries the current counts. The engine's own class names come from the binary's `__RTTI__` records.

The matching build produces the following artifact:

* `build/SLUS-20836/main.bin` — the game's merged load image, 4,541,184 bytes at `0x00100000`,
  `sha1: ffad4dab663cb290190bdfa34a8016d616a1652a` (`config/SLUS-20836/build.sha1`)

This repo does not include the game or the compilers. You need your own copy of the game; the
compilers are fetched from their public releases by `tools/download_tools.py`.

## Quick Start

You need an x86-64 Linux machine and your own *Digimon World 4* (USA, `SLUS-20836`) disc image.

**1. Install the prerequisites** for your distribution. The Sony EE GCC is a 32-bit program, so each
list includes the 32-bit C library.

Ubuntu:

```sh
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install -y binutils-mipsel-linux-gnu make git python3 libc6:i386
```

Fedora has no `mipsel-linux-gnu` binutils package, so build it from source (`mips64-linux-gnu` does not
work here):

```sh
sudo dnf install -y gcc make texinfo git python3 glibc.i686 tar xz
curl -LO https://ftpmirror.gnu.org/binutils/binutils-2.44.tar.xz
tar xf binutils-2.44.tar.xz
cd binutils-2.44
./configure --target=mipsel-linux-gnu --prefix="$HOME/.local" --disable-nls
make -j"$(nproc)" && make install
cd ..
export PATH="$HOME/.local/bin:$PATH"     # add this to your shell profile as well
```

Arch: enable the `[multilib]` repository in `/etc/pacman.conf`, then install the binutils package from
the AUR (`makepkg` checks its signature, so import the key it names or add `--skippgpcheck`):

```sh
sudo pacman -Syu --needed base-devel git python lib32-glibc
git clone https://aur.archlinux.org/mipsel-linux-gnu-binutils.git
cd mipsel-linux-gnu-binutils
makepkg -si
cd ..
```

**2. Get the code and the compilers.** They are fetched from their public releases into the gitignored
`local/` and checked by SHA-256.

```sh
git clone https://github.com/crashbashash/DW4_Decomp.git
cd DW4_Decomp
python3 tools/download_tools.py
```

**3. Add your disc image** to `orig/SLUS-20836/` (any name ending in `.iso`).

**4. Build and verify.** `make` extracts and checks `SLUS_208.36` from the disc image.

```sh
make check       # verify every decompiled function
make link        # relink the executable and compare it with retail
```

`make check` reports `0 mismatch`, and `make link` ends with `BYTE-IDENTICAL`. To make a disc from the build,
see [`make iso`](#step-3-build).

### Building in a container

If you would rather not install anything but Docker, [`docker/`](docker/Dockerfile) has a pinned Ubuntu
environment with every tool in it. Clone the repository, add your disc as in step 3, then run this from
the repository root:

```sh
docker build -t dw4-decomp docker/
docker run --rm --user "$(id -u):$(id -g)" -v "$PWD":/work dw4-decomp \
    sh -c 'python3 tools/download_tools.py && make check && make link'
```

The image holds tools only. Your repository and disc stay on your machine, mounted while it runs.

## Installation

### Linux

#### Step 1: Install dependencies

The build needs `mipsel-linux-gnu` binutils, Python 3, GNU make and the
[wibo](https://github.com/decompals/wibo) Windows-binary loader (the Metrowerks compiler is a
Windows executable; Wine dies on its FLEXlm license check).

Install them as in the [Quick Start](#quick-start), then fetch the toolchains:

```
python3 tools/download_tools.py
```

`tools/download_tools.py` puts every toolchain the build pins into the gitignored `local/`, each from
its public release and verified against the SHA-256 recorded in `config/SLUS-20836/units.tsv`:

| Path | What | Used for |
|---|---|---|
| `local/wibo` | wibo 1.2.0 | runs the Windows compilers |
| `local/mwcps2/3.0-011126/mwccps2.exe` | MWCC for PS2 3.0 (build 011126) | the default engine compiler |
| `local/mwcps2/combat/mwccps2.exe` | MWCC 3.0b38 (030307) | the game (`be*`) units; [unit compilers](docs/engine/unit-compilers.md) |
| `local/mwcps2/3.0.3-020716/`, `3.0b52-030722/`, `2.4/` | further MWCC builds | units pinned to them in `units.tsv` |
| `local/ee-gcc2.96/` | Sony EE GCC 2.96 | the Sony SDK and CRI library units ([sd-prologue](docs/engine/sd-prologue.md)); a 32-bit Linux executable |

Every compile command is built by `tools/cc.py` from the unit's profile in
`config/SLUS-20836/units.tsv` ([build profiles](docs/engine/build-profiles.md)); a missing or changed
compiler fails the build rather than falling back to another one. To keep the toolchains elsewhere,
point the build at them with `DW4_WIBO`, `DW4_MWCC` and the other `DW4_*` variables (`DW4_ELF`,
`DW4_M2C`, `DW4_M2C_DIR`, `DW4_PERMUTER`); each tool's `--help` names its default.

#### Step 2: Supply the game

Copy your disc image of the USA release into `orig/SLUS-20836/` (any `*.iso`). `make`
extracts `SLUS_208.36` from it and checks its hash against `config/SLUS-20836/config.yml`; another dump
of the same release works as long as the executable is identical. The disc image can be deleted
afterwards. If you already have the executable, put it at `orig/SLUS-20836/SLUS_208.36` directly. The
build never writes to it.

Nothing from the game is ever committed: `orig/` keeps only its `.gitkeep` files, the other working
folders are gitignored, and extracted game data sits beside the repository in `../local/`:

| Directory | Holds |
|---|---|
| `orig/<GAMEID>/` | your disc image and the extracted executable |
| `asm/` | the retail code as assembly, one file per function, generated from your executable (`make asm`) |
| `../local/extracted/` | the full disc extraction, which the analysis scripts and `make rules` read |
| `ghidra-projects/` | the analysed Ghidra project (`ghidra-projects/dw4/`) |

To extract all disc files, run `python3 tools/extract_iso.py <iso> --out ../local/extracted`.

#### Step 3: Build

See [build system](docs/build-system.md) for how the tree is laid out.

Run `make`. It generates the retail split in `asm/` from your executable when that folder is
missing or stale, then does two things, in order: reassembles the split and checks that it
round-trips byte-exactly, then compiles every `src/` function and diffs it against the game. A
function is only counted as decompiled when its bytes are identical; `make check` prints the
differing instruction otherwise.

```
make                      # build and compare (the default target)
make link                 # relink the whole section and compare it to the ELF
make verify VA=0x246780 SRC=src/unmatched/FUN_00246780.c    # one function, per-instruction diff
make report               # coverage only
make objs                 # compile objects, verify nothing
make symbols              # regenerate config/SLUS-20836/symbols.txt
make asm                  # regenerate asm/ (generated from your executable, never committed)
make iso                  # optional: a disc image with the built executable (see below)
```

`make iso` is a publishing step, not part of the build or CI. It relinks, then writes the executable
into a copy of your disc at `build/SLUS-20836/SLUS-20836.iso`; your disc is only read. It uses the disc
in `orig/SLUS-20836/`, or `make iso DISC=<path>` for one elsewhere. The result boots in an emulator, and
it is game data, so it stays in `build/` and is never committed.

The full list of variables, with the default first:

* `DW4_ELF`: path to the retail `game.elf`
* `DW4_MWCC`: path to `mwccps2.exe`
* `DW4_WIBO`: path to `wibo`
* `FLAGS`: compiler flags (default `-O3`, which is what the game was built with)
* `VA`, `SRC`: the function to check for `make verify`

## Project Structure

	DW4_Decomp
	├── asm: split disassembly of the retail code, one file per function (generated, gitignored)
	├── config: the build's symbol map, section tiling, and jump tables
	├── src: decompiled C source, one file per function
	├── tools: build and executable-format tools
	├── scripts: analysis tools: Ghidra dumps, format parsers, doc generators
	├── data: committed snapshot of the Ghidra dumps and derived tables
	├── docs: the documentation hub
	│   ├── engine: toolchain, binary layout, RTTI/vtables, reflection, igBinary, Lua
	│   └── systems: flags, spawns, drops, enemy stats, RNG, save format
	├── lua: every Lua 4.0.1 chunk from NDMW.AFS, decompiled and organised by world/area
	├── PROGRESS.md: how far the decompilation has got, rewritten on every push
	├── LICENSE: CC0 1.0 for this project's own work
	├── NOTICE: non-affiliation, trademarks, and what is not licensed
	├── build: output directory
	└── Makefile: check, link, verify, report, progress

`config/`, `data/`, `lua/` and `PROGRESS.md` are written by the
tools that own
them (`make symbols`, `tools/jumptables.py`, `scripts/sync_data.sh`,
`make progress`); `src/` and the prose docs are not.

`src/` is grouped by module, and every function that has no recovered name yet lives in
`src/unmatched/`. It holds **translation units**, the way the game was built — `src/lua/api.cpp`
is one file defining 47 functions, `src/engine/*.c` will be a system each — written in retail
address order, with a function moved out of `unmatched/` into its module once its purpose is
known. The per-function matching build (`check.py`, `linkgen.py`) splits a function back out
with [`tools/units.py`](tools/units.py), so a unit compiles as one and is still verified as
many. The module boundaries that are known are described in
[`docs/engine/architecture.md`](docs/engine/architecture.md).

Names are recorded in `config/SLUS-20836/names/`, one `.tsv` per module, merged over the Ghidra dump by
`tools/split.py` and applied to the tree (rename, call sites, `src/` folder, `asm/`) by
`tools/apply_names.py` — see [`docs/engine/naming.md`](docs/engine/naming.md).

## Status

The build is a **Ship of Theseus**: functions with C are compiled from it, everything else is
assembled from the original bytes, so the section always links whole while functions are decompiled
one at a time. [`PROGRESS.md`](PROGRESS.md) carries the numbers — functions and code bytes matched,
the size bands, where in the binary the work has reached, and what metadata has been recovered.

| | |
|---|---|
| Toolchain | MWCCPS2 3.0 `011126` via wibo at `-O3` for the game and engine; an alternate MWCC build and Sony EE GCC 2.96, content-pinned per unit — [`docs/engine/toolchain.md`](docs/engine/toolchain.md), [`docs/engine/unit-compilers.md`](docs/engine/unit-compilers.md), [`docs/engine/sd-prologue.md`](docs/engine/sd-prologue.md) |
| Relink | all 4,541,184 bytes of the main section rebuild byte-identical to retail (`make link`); the object count and the from-source accounting are in [`PROGRESS.md`](PROGRESS.md) |
| Documentation | [`docs/README.md`](docs/README.md) — the index of everything recovered so far |

## License and reuse

This project's own work — the build system, the tooling in `tools/` and `scripts/`, and the
documentation in `docs/` — is dedicated to the public domain under [CC0 1.0](LICENSE): use it,
change it and redistribute it for any purpose, commercial or not, without attribution.

The **game-derived material** — the decompiled source (`src/`), the
extracted metadata (`data/`) and the decompiled Lua (`lua/`) — is a derivative work of the retail game and is **not** covered by that dedication.
Copyright remains with the respective rights holders; it is included for preservation, research and
interoperability. See [`LICENSE`](LICENSE) for the scope in full and [`NOTICE`](NOTICE) for the
non-affiliation and trademark statement. No game binaries are distributed here — see
§Installation for what you must supply.

## Contributing

Pull requests are welcome. [CONTRIBUTING.md](CONTRIBUTING.md) is the place to start. The documentation index is
[`docs/README.md`](docs/README.md).
