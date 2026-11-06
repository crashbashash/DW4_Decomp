# Third-party libraries

The game links three stock libraries. Each `.c` and upstream header here is **byte-identical to the
upstream release**, and each compiles whole to retail's bytes ([whole-file units](../../docs/engine/emitted-functions.md#whole-file-units)).
Do not edit them: a difference from retail is a build setting to find, not a source change. Each
library keeps its own licence, not the project's.

| Folder | Release | SHA-256 of the upstream archive | Licence | Retail range |
| --- | --- | --- | --- | --- |
| `zlib/` | zlib 1.1.3 | `cae5847bc0e1cf113d3f70d037400da3e47c2e2b7b1c96b0b08447a5fbb906f4` | zlib licence, in `zlib/zlib.h` and `zlib/README` | `0x221870`-`0x2252d8` |
| `libpng/` | libpng 1.0.8 | `a324c3ba03e1f1c6bfd6c74a09ed91dc9b1964dfc4350919c50f56a86f8e255c` | `libpng/LICENSE` | `0x20e750`-`0x221870` |
| `lua/` | Lua 4.0.1 | `df746e149cf6939e90009d2e540eee918d585b4d1bc6d68b19316a050d484d2a` | `lua/COPYRIGHT` | `0x246d30`-`0x2590c0` |

Only files the game linked are here. `lua/lib/` keeps upstream's split, and `lua/` holds upstream's
`src/` and `include/` headers together.

## What is ours

- `libc/` declares only what these files include; the game links Sony's newlib-based libc. It is
  part of the build, not a libc: `abs` must stay declared for libpng to match.
- `libpng/libpng_prefix.h`, `lua/dw4_lualib_config.h` and `lua/dw4_lvm_config.h` are the game's build
  configuration, passed with `-prefix` so upstream's text stays untouched. A `-prefix` file is named
  bare and found through `-I`.

## Lua's two game files

The game rewrote `lmem.c` and `lstate.c`: `lua_open` takes a memory pool, and `luaM_realloc` calls
that pool's virtual functions. Those two files are therefore not stock and not here. They live in
`src/lua/lmem.c` and `src/lua/lstate.c`, keep upstream's text wherever the game did, and build as
whole-file units under the library's profile. `include/dw4/lua_game_state.h` adds the pool to
`lua_State` without touching `lstate.h`.

## Rows

The rows in `config/SLUS-20836/unit-objects.json` and `units.tsv` are measured by
`tools/whole_file_rows.py`, never typed. Where stock text fits several retail starts, its `--at`
arguments carry the evidence: `png_get_uint_32` and `png_get_int_32` by caller counts, and
`png_set_gray_1_2_4_to_8` and `png_set_tRNS_to_alpha` by how `FUN_001681c0` calls them.
