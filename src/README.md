# `src/` — the decompiled C and C++

Every function here compiles with the original compiler to the retail bytes. `make check`
proves it, and `make link` proves the relinked image is byte-identical.

| Folder | Holds |
| --- | --- |
| `engine/` | The Alchemy/`Gap::Core` engine layer: object model, metadata and reflection, memory pools, lists, strings, render attributes |
| `game/` | The game layer (`Gap::Bec`, the `be*` classes): menus and windows, messengers, status panels, camera, plus their class registrars |
| `audio/`, `movie/`, `menu/` | The ADX audio, CRI movie and GUI middleware classes |
| `lua/` | The Lua native API (`api.c`), the combat and material helpers it calls, and the Lua functions the game rewrote |
| `newlib/`, `libgcc/`, `sony/` | The C and maths library, GCC's runtime and Sony's runtime libraries, one file per archive object where the archive is known |
| `runtime/` | The Metrowerks C++ runtime's routines written as MWCC `asm` functions, each with an `asm-function` row |
| `third_party/` | Stock zlib, libpng and Lua, byte-identical to upstream and compiled whole; see its [README](third_party/README.md) |
| `unmatched/` | Matched units that are not **named** yet — every file here compiles to the retail bytes like everything else (`make check` proves it), but the function is still called `FUN_<va>` or `Class::vfunc_NN`. A unit leaves this folder when it gets a semantic name and a module (`tools/place_named.py`) |

## How a file is found

A file is named after the symbol it defines (`src/<folder>/<symbol>.c`, or `.cpp` where the
function needs C++). The folder never matters to the build: `tools/srctree.py` finds a file by
name at any depth, so moving a unit between folders is byte-neutral.

Related functions are folded into one translation unit named for what they do
(`engine/string-chunks.c`) or for the class they belong to
(`game/beCameraMode.c`). Functions sit in retail address order, the order the original compiler
saw them. `tools/units.py` hands the checker one function at a time, so folding changes no
bytes. See [naming](../docs/engine/naming.md) for how names are recovered and applied
(`tools/apply_names.py`, `tools/apply_data_names.py`, `tools/place_named.py`,
`tools/merge_units.py`).

Class boilerplate follows one pattern per class: `<Class>_Register.c` (the
`igMetaObject_RegisterClass` call, one argument per line with its role),
`<Class>_GetMetaObject.cpp` and `<Class>_InitFields`.

Files with a `.c` and a `.cpp` for the same class are deliberate: a method written for C mode
does not match when compiled as C++, so the two cannot be merged.

## Commands

```sh
make check        # compile everything here and diff against the retail ELF
make link         # relink with the matched units and compare the section byte for byte
make typed-check  # guard the count of member accesses that go through recovered structs
make report       # coverage counts
```

A function counts as decompiled when its compiled bytes are identical to retail, not when the
C looks right. `asm/` holds the retail bytes of the functions that are not decompiled yet, so the
tree always builds as a whole. The `asm` bodies under `src/` are the one hand-kept form of retail
instructions in the source tree; `PROGRESS.md` counts them apart from the C/C++ so the two are
never added together as "decompiled".
