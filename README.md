# Digimon World 4 decompilation

A work-in-progress matching decompilation of *Digimon World 4* for the PS2 (USA, `SLUS-20836`). The goal is
readable source that rebuilds the retail executable byte for byte.

<!-- progress:start -->
| Region | Size | Matched | Readable |
| --- | ---: | ---: | ---: |
| Game | 1106 KB | 90.3 % | 20.5 % |
| Alchemy engine | 1563 KB | 75.3 % | 20.9 % |
| Lua 4.0.1 interpreter | 70 KB | 100.0 % | 100.0 % |
| CRI ADX | 140 KB | 72.3 % | 6.8 % |
| CRI Sofdec | 209 KB | 69.5 % | 0.0 % |
| libpng and zlib | 90 KB | 100.0 % | 100.0 % |
| Sony SDK | 99 KB | 64.4 % | 2.4 % |
| newlib | 84 KB | 100.0 % | 100.0 % |
| libgcc | 11 KB | 100.0 % | 100.0 % |
| Metrowerks runtime | 10 KB | 34.7 % | 1.5 % |
| Static initialisers | 10 KB | 41.5 % | 0.0 % |
| **Total** | **3394 KB** | **81.0 %** | **24.2 %** |

The full figures and the verification debt are in [PROGRESS.md](PROGRESS.md).
<!-- progress:end -->

Functions that haven't been decompiled yet are assembled from your own copy of the game, so the build always
comes out identical to retail. A byte-identical build does not mean the decompilation is finished; the table
above shows how far it has got.

The build produces `build/SLUS-20836/main.bin`, the game's load image (4,541,184 bytes at `0x00100000`,
SHA-1 `ffad4dab663cb290190bdfa34a8016d616a1652a`).

## Quick start

You need an x86-64 Linux machine and your own *Digimon World 4* (USA) disc image. The repository contains
neither the game nor the compilers.

**1. Install the prerequisites.** The Sony EE GCC is a 32-bit program, so each list includes the 32-bit C
library.

Ubuntu:

```sh
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install -y binutils-mipsel-linux-gnu make git python3 libc6:i386
```

Fedora has no `mipsel-linux-gnu` binutils package (`mips64-linux-gnu` won't work), so build it from source:

```sh
sudo dnf install -y gcc make texinfo git python3 glibc.i686 tar xz
curl -LO https://ftpmirror.gnu.org/binutils/binutils-2.44.tar.xz
tar xf binutils-2.44.tar.xz
cd binutils-2.44
./configure --target=mipsel-linux-gnu --prefix="$HOME/.local" --disable-nls
make -j"$(nproc)" && make install
cd ..
export PATH="$HOME/.local/bin:$PATH"     # add this to your shell profile too
```

Arch: enable `[multilib]` in `/etc/pacman.conf`, then install binutils from the AUR (`makepkg` checks a
signature; import the key it names, or pass `--skippgpcheck`):

```sh
sudo pacman -Syu --needed base-devel git python lib32-glibc
git clone https://aur.archlinux.org/mipsel-linux-gnu-binutils.git
cd mipsel-linux-gnu-binutils
makepkg -si
cd ..
```

**2. Get the code and the compilers.** The compilers are downloaded from their public releases into
`local/` and checked against pinned SHA-256 hashes.

```sh
git clone https://github.com/crashbashash/DW4_Decomp.git
cd DW4_Decomp
python3 tools/download_tools.py
```

**3. Add your disc image** to `orig/SLUS-20836/` (any file name ending in `.iso`).

**4. Build and check.**

```sh
make check       # compile every decompiled function and compare it with retail
make link        # relink the executable and compare it with retail
```

`make check` should report `0 mismatch`, and `make link` should end with `BYTE-IDENTICAL`.

### Docker

If you'd rather not install anything except Docker, [`docker/`](docker/Dockerfile) has an Ubuntu image with
every tool. Clone the repository, add your disc as in step 3, then run from the repository root:

```sh
docker build -t dw4-decomp docker/
docker run --rm --user "$(id -u):$(id -g)" -v "$PWD":/work dw4-decomp \
    sh -c 'python3 tools/download_tools.py && make check && make link'
```

The image only contains the tools; your repository and disc stay on your machine.

## Installation

### Toolchains

The build needs `mipsel-linux-gnu` binutils, Python 3, GNU make, and [wibo](https://github.com/decompals/wibo)
to run the Windows Metrowerks compilers (Wine fails on their FLEXlm licence check). `tools/download_tools.py`
puts these into `local/`:

| Path | What |
|---|---|
| `local/wibo` | wibo 1.2.0 |
| `local/mwcps2/<build>/mwccps2.exe` | the Metrowerks CodeWarrior for PS2 builds the game was compiled with (3.0b52 for most of the engine and game, plus 3.0, 3.0.3, 3.0b38 and 2.4) |
| `local/ee-gcc2.96/` | Sony EE GCC 2.96, for the Sony SDK and CRI middleware |

Each source file is compiled with the compiler and flags recorded for it in `config/SLUS-20836/units.tsv`
([build profiles](docs/engine/build-profiles.md), [unit compilers](docs/engine/unit-compilers.md)). A missing
or changed compiler stops the build instead of falling back to another one. To keep the toolchains
somewhere else, set `DW4_WIBO`, `DW4_MWCC` and the other `DW4_*` variables; each tool's `--help` lists them.

### The game

Copy your disc image into `orig/SLUS-20836/`. `make` extracts `SLUS_208.36` from it and checks its hash, so
any dump of the USA release works. You can delete the image afterwards, or put the executable at
`orig/SLUS-20836/SLUS_208.36` yourself. The build never modifies it.

Nothing from the game is committed. These folders are generated or ignored:

| Folder | Holds |
|---|---|
| `orig/SLUS-20836/` | your disc image and the extracted executable |
| `asm/` | the retail code as assembly, one file per function, generated from your executable (`make asm`) |
| `../local/extracted/` | the extracted disc files the analysis scripts read (`python3 tools/extract_iso.py <iso> --out ../local/extracted`) |
| `ghidra-projects/` | the Ghidra project, if you use one |

### Make targets

```sh
make                      # build and compare (same as make check)
make link                 # relink the executable and compare it with retail
make verify VA=0x246780 SRC=src/unmatched/FUN_00246780.c    # one function, with an instruction diff
make report               # coverage only
make asm                  # regenerate asm/
make iso                  # a disc image with the built executable
```

`make iso` writes the rebuilt executable into a copy of your disc at `build/SLUS-20836/SLUS-20836.iso`
(or `make iso DISC=<path>` for a disc elsewhere). The result boots in an emulator. It is game data, so it
stays in `build/`.

See [build system](docs/build-system.md) for how the build works.

## Repository layout

	DW4_Decomp
	├── src        decompiled source
	├── include    shared headers
	├── config     symbol map, build profiles, unit tables (per game version)
	├── tools      build and matching tools
	├── scripts    analysis scripts
	├── data       recovered data tables
	├── lua        the game's Lua scripts, decompiled and filed by area
	├── docs       documentation
	├── testing    testing notes and fixtures
	└── docker     container build environment

`src/` is laid out the way the game was built: one file per original source file wherever that is known
(for example `src/game/beCameraCtrl.cpp`, or the engine libraries as unity builds in `src/engine/<library>/`),
in retail address order. Functions whose file isn't known yet live in `src/unmatched/`. See the
[source layout](src/README.md) and [architecture](docs/engine/architecture.md).

Names come from the game's own RTTI and strings where possible and are recorded in
`config/SLUS-20836/names/` ([naming](docs/engine/naming.md)). `config/`, `data/`, `lua/` and
`PROGRESS.md` are generated by tools; edit what they're built from instead.

More: [documentation index](docs/README.md), [tools](tools/README.md), [analysis scripts](scripts/README.md),
[testing](testing/README.md), [reference](docs/reference/README.md).

## Licence

This project's own work (the build system, tools, scripts and documentation) is dedicated to the public
domain under [CC0 1.0](LICENSE).

The game-derived material (the decompiled source in `src/`, the data in `data/` and the Lua in `lua/`) is a
derivative of the retail game and is **not** covered by that dedication. Copyright stays with its owners;
it's included for preservation, research and interoperability. See [LICENSE](LICENSE) for the full scope
and [NOTICE](NOTICE) for the non-affiliation and trademark notice. No game files are distributed here.

## Contributing

Pull requests are welcome. Start with [CONTRIBUTING.md](CONTRIBUTING.md).
