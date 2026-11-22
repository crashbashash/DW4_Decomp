# Naming: the committed name overlay and the module loop

Many functions in `config/SLUS-20836/symbols.txt` are still `FUN_<addr>` (the live counts are in
[`../../PROGRESS.md`](../../PROGRESS.md)). This page is how a name gets recovered and
applied, why the project does it a module at a time, and the rules a finished module
has to meet: one profile per translation unit, shared headers, decimal `fNN` members
and evidence-named strings.

**End state.** A module is complete only when every `DAT_`/`FUN_` reference inside it is
named, from the strongest evidence there is. Doubt about a name goes in the open questions of its topic document, not the source.
`FUN_`/`DAT_` names are a work-in-progress form, not a permanent one.

## Where a name lives

A name has to reach three things that all key off it: the C unit's filename, the
definition and call sites inside `src/`, and the `asm/<name>.s` unit that links the
undecompiled remainder. The build reads the layout from `config/SLUS-20836/symbols.txt`, which
`tools/split.py` regenerates from `data/functions.json`, a dump of the Ghidra
project. So a name that only exists in Ghidra is invisible to the repository: it
cannot be reviewed, and re-dumping is a manual round-trip.

`config/SLUS-20836/names/` is the fix. It is a directory of committed overlays, **one `.tsv`
per module**, that `tools/split.py` merges *over* the dump:

```
config/SLUS-20836/names/Lua.tsv      # the Lua native API
config/SLUS-20836/names/GapCore.tsv  # (future) a Gap::Core module
```

```
<va>\t<name>\t<module>
```

- `va`: the function address (the key; an address may be named once, so two
  modules disagreeing is an error rather than a silent last-wins).
- `name`: the recovered name. `::` is allowed and sanitised to `__` for C/as, so
  `Gap::Core::Foo` becomes the C identifier `Gap__Core__Foo`.
- `module`: the `src/` folder the unit belongs in (`Lua`, `Gap/Core`, …). Unnamed
  units are `unmatched`.
- `confidence` and `evidence` (optional fourth and fifth columns; `tools/split.py` reads the first three): the
  overlays written from decompiler evidence (`CoreNames.tsv`, `AlchemyCallees.tsv`, `GameBehaviour.tsv`,
  `GamePropagated.tsv`) carry `high` or `medium` and the sentence that justifies the name. Nothing lower is written.

The dump is still the source for every function the overlay does not name, so
adding an overlay never reduces coverage: it is merged, not substituted.

## The module loop

1. **Choose a module** with a recovered boundary and a name source (below).
2. **Write the names** into `config/SLUS-20836/names/<Module>.tsv`. Where a generator already
   holds the names (e.g. `scripts/seed_names_lua.py`), run it rather than typing
   them, so the overlay keeps its provenance.
3. **Apply the batch:**
   ```sh
   python3 tools/apply_names.py             # dry run: what would change
   python3 tools/apply_names.py --apply --check
   ```
   `apply_names.py` rewrites every reference to `<old>` in `src/` and `include/` (definition,
   declarations and call sites), the function columns of `config/source-approvals.tsv` and
   `config/assembly-sources.tsv`, the function keys of `config/SLUS-20836/unit-objects.json` (a `data`
   row that already spelled the function's new name goes, the function's own entry now holding it) and
   the function names in the subject documents of `docs/` (those `config/doc-subjects.txt` lists, which
   `scripts/check_doc_function_names.py` holds to the symbol table); a method document names no function, so
   one naming an old name is left as it is and listed, for its author to describe the shape instead;
   moves a one-function unit to `src/<module>/`, removes the stale `asm/<old>.s`,
   regenerates `config/SLUS-20836/symbols.txt` + `asm/`, and then runs `make check` and
   `make link`. Renaming one function by hand is a multi-file edit; a whole module
   at once is one verified commit. The dry run lists the files it would rewrite, the files it
   leaves because they already use the new names, and every refusal; a refused batch writes nothing.

A one-function file's **filename is its symbol**; a named function is resolved at
any depth, so moving it between modules never touches a build tool. One-function files are
legacy drafts: a function now lands inside its whole file, and the one-function files of a
range go when the range is folded.

### How a rename is applied

A reference is an identifier that names the function, told apart by reading the C around it. The
tool never rewrites:

- a string or character literal, or an `#include` path. A string is retail data: a library error
  string naming its own function must stay byte-exact in `.rodata`. An inline-`asm` operand is code,
  so the symbols in it are rewritten;
- a member (`.x`, `->x`, `Class::x`), a field, tag, label or macro name, a name used as an object
  (`x->`, `x.`), and a local, parameter, `typedef` or file `static` of the same name, with every use
  inside its scope;
- a comment word, when the old name is a plain lower-case word or is also an ordinary identifier. Any
  other comment word of the old name is renamed: the batch takes the old name out of the symbol table,
  so a comment keeping it would name nothing. (A member conversion, `tools/memberize.py`, leaves
  comments as they are: its C names stay the functions' retail names.)

Each file is rewritten in one pass, so a swap never renames its own result. A
`unit-objects.json` key (`emitted`, `duplicates`, `externals`, and a row's `symbol`) is renamed by
address: only when the address it holds is the renamed function's and the key is still the old name.
`data` keys are data names, `tools/apply_data_names.py`'s.

The tool refuses the batch when:

| Refusal | Why | Way out |
|---|---|---|
| an old name is also an ordinary identifier in the tree: a member, field, local, parameter, label, tag or macro (the error lists every file and use) | a generic word, such as the start-up symbol's, would be rewritten in every local, member, comment and string that spells it | rename those uses first, or `--generic <old>` to rewrite only the references the reading above finds |
| a batch reuses a name (one name moves to another address, and its old address takes a new one: a swap or a chain) and a file's text does not say which names it uses | text already written with the new names would be renamed a second time | the evidence is the file's other batch names (an old-only name: not yet renamed; a new-only name: already renamed) and whether its definitions are in address order under the old or the new names. A file on the new names is left as it is; `--assume-old <path>` or `--assume-new <path>` settles a file nothing decides |
| a file mixes old-only and new-only names around a reused one | it was half renamed by hand | finish it by hand, or `--assume-old`/`--assume-new` |
| a rewritten reference would fall in the scope of a local, parameter or C++ member of the new name, or a C++ file has a member of the old name used unqualified | the name would bind to the other entity | rename the local, or qualify the use |

### Folding a module into a translation unit

An automated match is banked one function per file, but the repository's source is
translation units (`src/game/be.cpp`, `src/engine/*.c`), the way the original was
built. Once a module is named, fold it:

```sh
python3 tools/merge_units.py --out src/<module>/<Unit>.c \
    --title "<what the unit holds>" --remove <the per-function files>
```

Functions are written in **retail address order** (the order the original compiler
saw, which is why the original file can be recovered from the binary at all), and
declarations every user agrees on are hoisted. A symbol two functions declare
differently (m2c guesses `int[4]` in one and `char[]` in another) is kept inside
each user as a block-scope `extern` instead, since a declaration has no effect on
the code being matched.

### Placing units that are already named

The RTTI/vtable names (`Gap::Bec::beCameraMode::vfunc_20`) are real but carry no
folder, so those units sat flat in `src/` root. Their name does say where they
belong, so one command places and folds them:

```sh
python3 tools/place_named.py            # dry run: what would move where
python3 tools/place_named.py --apply
```

It groups by class and folds each group with `merge_units.py`:

```
Gap__Bec__Class__vfunc_NN.c Gap__Bec__Class__vfunc_MM.c  ->  src/game/Class.c
```

Folders come from the namespace: `Gap::Bec::*` → `src/game/`, `Gap::Core::*` →
`src/engine/`, `Gap::igAdx*` → `src/audio/`, `Gap::igMovie*`/`igCriMovie*` →
`src/movie/`, `Gap::Gui::*` → `src/menu/`. A class whose methods need both C mode
and C++ mode keeps two files (`Foo.c` and `Foo.cpp`): a C-mode method compiled as
C++ does **not** match (measured 0 of 25 mixed classes), so that split is real.

`tools/units.py` keeps all of this compatible with the per-function build: it
scans a file for its definitions and hands `check.py`, `linkgen.py` and `verify.py`
one function at a time by blanking the others. `make check` and `make link` are the
gate, as always.

### One translation unit, one profile

The original build compiled a class or a source file once, with one compiler and one
flag set, so a folded unit must verify that way too. **Every method of a class, and
every function of a folded unit, verifies under the same compiler and flags**: the
rows in `config/SLUS-20836/unit-compilers.tsv` and `config/SLUS-20836/unit-flags.tsv` are per unit, not per
function. A per-function row that disagrees with its siblings (one method pinned to
the alternate compiler inside a class the pinned compiler builds, or `-O3,p` beside
`-O4`) is **provisional**: it stays banked, but its row is marked `provisional` and
names the sibling profile it failed under, it is re-attempted under that
profile before the unit is called complete, and reports count it separately until it
is resolved. A unit whose functions genuinely need two compilers is two source files
(as `.c`/`.cpp` already are), never one file with mixed rows.

### Offset members: `fNN` is decimal and temporary

A matched function that reads a field the reflection does not describe may spell it
as an offset member (`p->f12`). Two rules: the number is the **decimal** byte offset
(`f12`, never `f0xc` or `f0c`), so one field has one spelling across the tree and
`tools/typed_coverage.py` can pair it with the reflected layout; and an `fNN` member
is a temporary form: it is replaced by the recovered field name (through
`include/dw4/support/reflected.h` or a hand header) when the struct is typed, and a module
with `fNN` members left is not complete.

### One shared definition per class

A class or struct has **one definition**, under `include/dw4/<library>/<Module>.h` (the folder of the defining unit's library): the generated
`include/dw4/support/reflected.h` for every reflected class, or a hand-written header for a
struct the reflection does not describe. Matched files include that header instead of
restating the struct. A **local view** (a file-private struct covering only the offsets
one function touches) is allowed only where ABI dispatch needs it (a receiver whose
real class is undetermined, or a layout the compiler must see differently to colour
registers as retail), and it must not reuse a reflected class name: `struct
beSound_view` or `struct G`, never a second `struct beSound`. When the real class is
known, the local view is replaced by the shared header in the same commit.

## What counts as a name

A name is *recovered* from the strongest evidence available. Where nothing stronger survives, a best guess from what
the function, variable or struct does is a valid name, so long as it describes behaviour the code shows. The sources used so far, best first (per-source
counts are in [`../../PROGRESS.md`](../../PROGRESS.md) and the overlay files themselves):

| Source | Names | Where |
|---|---|---|
| RTTI / vtables | `Class::vfunc_NN` for RTTI-headed vtables | `docs/engine/rtti-and-vtables.md` |
| `GetVTable`-derived vtables | `<Namespace>::<Class>::vfunc_NN` for the vtables that have no `__RTTI__` record: the class comes from its own `<Class>_GetVTable`, the namespace from the nearest RTTI ancestor, the role from the slot | `scripts/seed_names_getvtable_slots.py` → `config/SLUS-20836/names/GetVTableSlots.tsv` |
| Lua native API table | the real implementations + dispatcher | `data/script_api.json`, `docs/engine/script-engine-lua.md` |
| Class registration (reflection) | `<Class>_Register` + `<Class>_InitFields` | `data/reflection.json` (per-class `register_site` / `post_init`), `scripts/seed_names_reflection.py` |
| MetaObject accessors | `<Class>_GetMetaObject` (t0 -> `_getMetaObjectFunction`; many are reached through the registrar's `j <accessor>; nop` thunk), `<Class>_GetVTable` (t3 -> `_vTablePointer`) + the `igMetaObject` methods | `scripts/seed_names_metaobject.py` (the registrar's `t0`, role read from the decompiler) |
| SDK `libkernel` syscalls | the syscall stubs | `config/SLUS-20836/syscalls.txt`, `docs/engine/binary.md` |
| SDK library functions | named from the function's *own* name in a string it references (`sceMtapPortOpen/PortClose/GetConnection/ChangeThreadPriority/GetModVersion`, `sceMcUdCheckNewCard`), plus functions attributed to a library (`libpad`, `libmc`, `libmtap`, `libdma`, the IOP-module loaders) which are attributions rather than names | `config/SLUS-20836/names/Sdk.tsv` (generated by `scripts/seed_names_sdk_strings.py`), [`platform-boundary.md`](platform-boundary.md) |
| Decoded semantics | hand-written, with the evidence in the topic document | `docs/engine/`, `docs/systems/` |
| Object-model core | `igMetaField` / `igMetaObject` / `igRefMetaField` / `igMemoryRefMetaField` / `igMetaEnum` methods, read off the decompiler against `data/reflection.json`, the class `GetVTable` functions and the vtable slot map | `config/SLUS-20836/names/ObjectModel.tsv`, `config/SLUS-20836/names/MetaFieldSlots.tsv` (generated by `scripts/seed_names_metafield_slots.py`) |
| Assert / log strings | `Class::method` names | `config/SLUS-20836/names/Methods.tsv` |
| CRI ADX and Sofdec libraries | CRI's own function names: the CRI PS2 SDK archives `libadxe.a` and `libmwsfde.a` (Sep 2002; [SkeletonPicture/recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri)) matched to the retail bodies by address-masked comparison and by unit order, and the Street Fighter III 3rd Strike libadxe (2003; [crowded-street/3s-decomp](https://github.com/crowded-street/3s-decomp)) matched the same way. The Persona 4 decompilation's CRI notes ([Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation)) corroborate. Sources are cited, never vendored. A masked-exact body, or agreement of both sources, is high; a near body, or the same position in order with equal size, is medium and names the alternative. A static name that CRI repeats across files takes the file stem as a prefix | `config/SLUS-20836/names/CriAdx.tsv`, `config/SLUS-20836/names/CriSofdec.tsv` (generated by `scripts/seed_names_cri.py` from `data/cri-names-worklist.tsv`); globals in `config/SLUS-20836/data-names.tsv` |
| Game-class constructors | `<Class>_Construct`, from the constructor shape below | `config/SLUS-20836/names/Constructors.tsv` (generated by `scripts/seed_names_constructors.py`) |
| Game slot families and registrar plumbing | `<Class>_<Method>` for a virtual named once per slot family (the vtable position, never the `vfunc_NN` number): the name read from the introducing class's callers where `scripts/game_slot_families.tsv` records one (carried to every member and replacing other spellings), else the introducing class's own name or the one name every named override agrees on, never a majority; the registrar plumbing by body shape (`_EnsureRegistered`, `_GetMetaObject`, `_GetMetaObjectFunction`, `_GetOrCreateMetaObject`, `_GetPublishedMetaObject`, `_Create`, the CoreNames conventions); compiler-emitted `igSmartPointer_<T>_Destruct` (the owning class added where two copies are the same instance) | `config/SLUS-20836/names/GamePropagated.tsv` (generated by `scripts/seed_names_game_propagated.py`, which moves the rows other overlays held for those addresses) |
| Game behaviour | `<Class>_<Method>`, and names for what a function does or holds: smart-pointer constructors and destructors, class destructors, message-enum accessors, static-init callbacks, traversal functions, shared helper instances | `config/SLUS-20836/names/GameBehaviour.tsv` (hand-written; the evidence column names the body, the callers or the unit-objects row that decides it, and the alternative a `medium` row leaves open) |
| Alchemy functions the game calls or overrides | the engine's own names for functions the game's matched C reaches (smart-pointer destructors, vector/matrix helpers, base-class destroy steps), from their callers and bodies | `config/SLUS-20836/names/AlchemyCallees.tsv` (hand-written, same columns) |

An assert string with a code xref is the only place a method name survives in the stripped binary, so
the function that logs it is that method. `igIGBFile::readFile` and `igArenaMemoryPool::checkHeap` are
the exception: each string is referenced by two functions, and the string alone does not decide
between them. `0x2e95e0` and `0x3125d0` carry the names in `config/SLUS-20836/names/Methods.tsv`;
`0x2e25a0` and `0x312790` stay `FUN_` names.

A game-class constructor has a recognisable shape: it calls `igObject_InitHeader` (`0x2fef20`),
stamps a class vtable at `+0`, then zeroes the class's reflected fields. The last vtable stamped at
`+0` is the most-derived class, which gives the class name from `data/vtables.json`; the body gives
the role. `scripts/seed_names_constructors.py` scans for this shape, resolving the vtable through
`lui`/`addiu`/`ori`/`move`/`addu` and skipping `ig*` middleware. The family is small: only 4
constructors in the binary call `0x2fef20` and stamp an RTTI-known vtable. The game's other
constructors stamp vtables with no RTTI record.

A name whose only justification is "it looks like a getter" is not ready; it
is a hypothesis for the topic document's open questions, not for `config/SLUS-20836/names/`.

## Conventions the game and Alchemy overlays follow

- **`<Class>_<Method>`.** A method is the reflected class name, `_`, the method name. A virtual takes its
  slot family's name (the vtable position, never the `vfunc_NN` number): `igInfoManager` slot 21 is
  `Activate` for every class that holds it. A family is named once, by reading the introducing class's callers
  and bodies, in `scripts/game_slot_families.tsv` (`<introducer> <slot> <method> <confidence> <evidence>`;
  a row whose introducer is `-` names the one address in its slot column). The same names are the
  virtual names of the dispatch views ([RTTI and vtables §7](rtti-and-vtables.md#7-virtual-calls-the-dispatch-views)).
- **`GamePropagated.tsv` is generated.** `scripts/seed_names_game_propagated.py` writes it from five routes: `slot`
  (a family's name carried to every override still `FUN_`/`vfunc_NN`, or spelled otherwise), `plumbing` (registrar
  functions recognised from their bodies), `emitted` (compiler-emitted copies, below), `engine` (the Alchemy
  registrar plumbing the game's matched C calls) and `class-name` (below). A name already held by another address,
  or given to two, is dropped, and the rows other overlays held for those addresses move into it (`--write`), so
  each address is named once. The generator reads the generated `asm/`, is idempotent, and is never edited by
  hand: change `game_slot_families.tsv` or the generator and re-run it.
- **Emitted copies of shared inlines.** A function the compiler emitted once per file from a shared inline is named
  by its instance and method, with the owning class (the class whose file emitted the copy) in front:
  `<OwnerClass>_<instance>_<Method>` (`beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Deref`,
  `beNDMWPanelWazaInfoWork_igIntList_SetAll`).
- **Emitted smart-pointer destructors.** `igSmartPointer<T>`'s destructor is `igSmartPointer_<T>_Destruct`; where
  two copies are the same instance each takes its owning class: `<Owner>_igSmartPointer_<T>_Destruct`
  (`beWeaponInfoRam_igSmartPointer_igObject_Destruct`).
- **Message enums.** The function that builds a class's message enum is `<Class>_GetMessageEnum`
  (`beSound_GetMessageEnum`, `beMatCtrl_GetMessageEnum`); that is the one spelling.
- **A class name registered in more than one namespace** is told apart by its library, not by an address: the
  copy registered by a game library takes that library's suffix (`Bec`, `Ndmw`) and the scene graph's takes `Sg`
  (`igModelViewMatrixBoneSelectListBec_*` beside `igModelViewMatrixBoneSelectListSg_*`); the Alchemy engine's
  registration keeps the bare name. A copy with no such library keeps its handle address in the prefix, which
  marks it as unresolved (`class_prefixes` in `scripts/seed_names_reflection.py`).

## Data symbols

Functions are named through `config/SLUS-20836/names/`; the `DAT_<addr>` data symbols the matched C
refers to have their own overlay, `config/SLUS-20836/data-names.tsv`, generated by
`scripts/seed_data_names.py` and applied by `tools/apply_data_names.py` (one `src/`
module at a time, then `make check` and `make link`). The build finds a data symbol's
address through that table (`tools/verify.py:data_symbols`), so a recovered name carries no
address, while `GPR_`, `D_`, `DAT_` and `FUN_` names keep theirs because they are not recovered. A
function passed by address takes the function's own symbol instead: `function-symbol` rows do not
resolve, so a row left behind after a rename cannot. A name given two addresses in the table stops
the build.

| Rule | Name | Evidence |
|---|---|---|
| `function-symbol` | the function's symbol | the address is a function entry in `config/SLUS-20836/symbols.txt` (a callback argument) |
| `class-handle` | `g_<Class>_metaObject` | `handle` of the class in `data/reflection.json` |
| `class-name` | `<Class>_className` | `name_ptr` of the class in `data/reflection.json` |
| `published-accessor` | `<Class>_GetPublishedMetaObject` | a 12-byte `lui at; jr ra; lw v0,lo(at)` leaf whose load is the class's `handle` slot; the same shape as the three accessors already named in `config/SLUS-20836/symbols.txt` |
| `callback-list` | `g_<Class>_callbackList` | the eleventh argument of the class's `igMetaObject_RegisterClass` call (docs/engine/reflection-metadata.md section 1); `scripts/format_registrars.py` lays those calls out one argument per line |
| `class-vtable` | `g_<Class>_vtable` | the address of a class's vtable record in `data/vtables.json` or `data/vtables-getvtable.json`; a class name registered twice takes its copy's prefix (`<Class>Bec`) |
| `string-literal` | `<TEXT>` | the printable NUL-terminated text at the address in the image |

An address that matches no rule keeps its `DAT_` name: it is not named until it has evidence,
and a module is not complete while such a `DAT_` is referenced.

**String literals** always take the `string-literal` row above: the printable text at the address,
sanitised to an identifier. The row marks the symbol as data and its type says it is a string, so it
has no prefix. Each further copy of a
text takes an ordinal in address order (`GAMERAM_2`). A text that cannot be a name, because it starts
with a digit or is a function's name, takes `text_` (`text_096`). The seed script derives the name
from the image; do not hand-write a different spelling for the same string.

**Different data under one name** keep `_<addr>` (`g_decodedParticle_00560ac0`). An ordinal would
hide that they are not yet understood, so they stay marked until a real name or type replaces them,
and a function using one does not count as readable.

## Receiver classes without names

Some matched `FUN_` functions cannot be named (the role is unknown) although their receiver
class is determined by evidence. `config/SLUS-20836/receiver-classes.tsv` records `<va> <class> <rule>`
for those, generated by `scripts/seed_receiver_classes.py`, and `scripts/retype_receiver_class.py`
reads it alongside function names. It is a type overlay: it never renames anything.

| Rule | Evidence |
|---|---|
| `vtable-slot` | The function is a slot of one class family's vtables (`data/vtables.json`, `data/vtables-getvtable.json`). The owner is the nearest common ancestor (`data/class-hierarchy.tsv`); bare `igObject` is rejected (a shared stub), and every offset applied to `arg0` must be a reflected field of the owner or an ancestor (offset 0 is the vtable pointer). |
| `vtable-stamp` | The function stores exactly one vtable at `+0` of its receiver and no other rodata address. A function that stamps several vtables is an inlined base-constructor chain and is excluded. |

All overlay rows are `ig*` middleware, so this raises
the typed count without adding game-layer structure. Propagating classes through callers
reaches almost nothing further ([measured](#what-didnt-work)): most remaining receivers are stack
temporaries or game structs that reflection does not describe, and need struct recovery.
The retyper does not check callee prototypes: thirteen files fail `make check` after it
and stay raw, so `make check` after `--apply` is mandatory.

## Coverage

`tools/progress.py` counts a function as named when its symbol is not `FUN_`/
`thunk_FUN_`. The live named/total counts, and the split by source (reflection
registrars and field initialisers, MetaObject accessors / vtable getters, RTTI
`vfunc_*`, Lua, object-model methods, assert strings, SDK and hand-named), are in
[`../../PROGRESS.md`](../../PROGRESS.md); this
page does not repeat them because they change with every batch.

The *denominator* is not fixed: `tools/split.py` passes recover functions Ghidra had
only labelled. `promote_gap_labels` promotes a gap label with a frame prologue;
`promote_data_labels` promotes a gap label a vtable points at whose
bytes form a leaf body. Both only add entries in unclaimed gaps and
never change an existing symbol's size, so the relink stays byte-identical, but each
one lowers the coverage *percentage* by growing the denominator while the matched
count is unchanged. A commit that changes the denominator (a split pass, an extent
override, a symbol split or merge) says so in its message with the before/after
counts, as `CLAUDE.md` requires.

## Not yet nameable

The 116 Lua **stubs** are branch targets *inside* the single function at
`0x00370780` (auto-analysis made the dispatcher and its stub table one function),
so there is no symbol to name. Naming them needs that function split first, which
is a layout change, not a naming one.

## What didn't work

**Propagating receiver classes through callers.** Measured over 859 unnamed functions with 1,677 raw
receiver casts: propagating classes through callers to a fixed point classes 3 functions with an
offset-fit check, 8 without. Blockers: 187 are called on stack objects whose other callees are also
unclassed, 162 have an argument loaded from memory, 90 are called only by other unclassed functions and
246 have no direct caller. Clustering functions that share an object gives 54 groups (201 casts); 449
functions (913 casts) share nothing.
