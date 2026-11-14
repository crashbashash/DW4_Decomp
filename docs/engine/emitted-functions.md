# Explicit compiler-emitted function ownership

The player stat recompute (`0x3fab90`) and the nearby query are written in one
compiler unit, `src/game/beNDMWGameRam.cpp`. It emits two further real
retail functions besides the owner: the 652-byte query at `0x3fc780` and a
128-byte deleting destructor at `0x3fc670`. The
compiler puts them in distinct sections both named `.text`. Both bodies must
match and both must be placed in the retail layout; ignoring the destructor
would hide code generated from the recovered source.

## Ownership overlay

`config/SLUS-20836/unit-objects.json` is a hand-authored overlay keyed by the normal
top-level function's stable retail address:

```json
{
  "0x003fab90": {
    "emitted": {"__dt__10IntListRefFv": "0x003fc670",
                "beNDMWGameRam_CollectNearbyNonzeroHp": "0x003fc780"},
    "externals": {"__dl__FPv": "0x00100610"}
  }
}
```

`emitted` maps a compiler symbol to another complete retail function.
`externals` records explicit call-target bindings needed by this compiler unit.
The delete-entry alias is established by the matching deleting-wrapper call
site; it does not claim recovery of the callee's own 96-byte assembly body.
The class name in the emitted symbol belongs to the source's ABI projection,
not a claim about the original class/template spelling.

The owner supplies compiler and flag settings to every member. Source discovery
adds members only when the owner's actual definition exists. Extraction of a
logical member compiles that owner's source, including its class definition.
Thus source coverage, `make check`, `make link` and progress agree on both
physical bodies. Diagnostic verification accepts `unit_objects`; the check,
verify and link CLIs also accept `--unit-objects`.

## Duplicates, switch tables and exception data

A larger unit (the GAMERAM combat callback, `0x3fca10`) also needs three things the
two-body case did not. Each stays fail-closed: anything not declared is still an
unowned section.

* `duplicates` maps a compiler symbol to the retail address of a function the
  compiler emits into this object but retail contains **once**, in a unit the linker
  saw first (an inline destructor or helper that several units instantiate). The
  copy must be a complete `.text` section with the exact retail size and bytes after
  relocation, but it is never placed and gives no source ownership; it is linked as
  an ordinary reference to the independently placed unit. Its `.exceptix` record and
  `.mwcats` section are discarded with it (the linker dropped them too), and only a
  structural check applies to that record: 12 bytes, one relocation to the copy.
* **Profile twins.** Retail's kept copy was compiled with *its* unit's compiler and
  flags (`config/SLUS-20836/unit-compilers.tsv`, `config/SLUS-20836/unit-flags.tsv` row of the duplicate's
  address, else the tool defaults), not the owner's. A copy built under a different
  profile cannot equal the owner object's bytes (observed: delay-slot scheduling of
  a four-instruction reference release differs between the two profiles). Such a
  duplicate is only required to exist in the owner's object, and
  `verify_emitted_unit` then recompiles the **same source** with the duplicate's own
  profile and compares it exactly. No body is skipped without that second exact
  comparison, and a profile that fails to compile or match rejects the unit.
* **Switch tables.** The owner's `.rodata` sections are matched to the owner's
  entries in `config/SLUS-20836/jumptables.txt` (count and byte size), relocated against the
  member symbols and compared with the retail tables. Linking places them with the
  owner exactly as for an isolated function; a non-owner placed member with
  `.rodata` is rejected.
* `exceptions` is `{"index": <retail record>, "table": <retail table>, "table_size": N}`.
  The owner's 12-byte `.exceptix` record (function, code size, table pointer) and its
  `.exception` bytes, with every cleanup pointer relocated to the member or external
  that retail names, must equal the retail bytes; the table region may end in up to
  three zero bytes of padding, which must be zero. The data stays in the normal
  retail layout (it is not relinked); the comparison is what ties the draft to it,
  and the index record carries the code size, so it cannot match at a wrong length.
  Without the declaration the sections are rejected as before.

Example overlay entry (the dispatcher draft's is `wip/dispatcher/unit-objects.json`;
it moves into `config/SLUS-20836/unit-objects.json` when the function is banked, together with
a `config/SLUS-20836/unit-flags.tsv` row `-O3,p -Iinclude` and a `config/SLUS-20836/unit-compilers.tsv`
row for the pinned combat compiler):

```json
{"0x003fca10": {"emitted": {},
  "duplicates": {"__dt__14RecoveryRef<1>Fv": "0x003d9d50", "__dt__14RecoveryStringFv": "0x00130720"},
  "externals": {"__dl__FPv": "0x00100610"},
  "exceptions": {"index": "0x00553b80", "table": "0x00544fd4", "table_size": "0x1a0"}}}
```

`emitted` may be empty when the owner is the only placed body. A row may also carry
**externals and an `exceptions` record alone**, with neither emitted nor duplicate
bodies: the unit whose RAII helpers are out of line in retail (`beNDMWPanelWaza::vfunc_31`,
`0x3cfe50`, calls the `StringRef` constructor at `0x3cc550` and the destructor at
`0x130720` instead of instantiating them). The externals bind those calls
and the record's cleanup pointers; a row with externals and no record, or a record and
nothing to bind, is still refused.

A row may list **`stripped`** destructor bodies: MWCC emits an out-of-line copy of a
local class's inline destructor even when every use is inlined, and the retail linker
dead-stripped such copies (the local views in the `*_GetVTable` functions). A stripped
name must start with `__dt__` (see [whole-file units](#whole-file-units) for the exception), be a complete `.text` section of its own, be referenced by
nothing the object keeps, and have no copy in retail (relocated words masked; a retail
copy is named as a duplicate instead). Its record and table are dropped with it, and it
is removed before linking. Linking drops all
duplicates, `.exceptix`, `.exception` and `.mwcats` and fails if any other allocated
section remains besides `.text` and the owner's tables.

## Whole-file units

A stock library file (zlib, libpng, Lua, newlib's `mprec.c` and `signal.c`) is kept as upstream wrote it and compiles whole, so its
row covers the file rather than one function. An ee-gcc file builds with `-ffunction-sections`:
`tools/eegcc_compile.py` then renames each `.text.<function>` to `.text` and points the calls the
assembler resolved through a section symbol back at their function, the object shape MWCC writes. Lua's `lmem.c` and `lstate.c`, which the game rewrote,
are whole-file units too, from `src/lua/`:

```json
{
  "0x00223ec0": {
    "whole_file": true,
    "emitted": {"inflateEnd": "0x00223f30", "inflate": "0x00224150"},
    "stripped": ["inflateSync"],
    "externals": {"calloc": "0x00123730"},
    "data": {"inflate_mask": "0x00497b20"},
    "anon": ["0x004e7490"]
  }
}
```

The owner is the file's first retail function and `emitted` names the others; the file has one
`config/SLUS-20836/units.tsv` row, so every member shares its profile. `tools/whole_file_rows.py`
measures the rows from retail and stops if a retail function in its range has no compiled copy; its
docstring gives the command, and [`src/third_party/`](../../src/third_party/README.md) holds the
sources. A recovered source file that still lacks some of its functions is measured with `--partial`:
the retail functions it does not define keep linking from the retail image between its members, and
each gains its place in the file when its C is written; `--write` keeps the rows of such a function
that still builds from its own source. The tool follows what `verify` keeps live: each member's body
and retail exception table, then every datum and function they reach in turn. A function out of the
range that is reached this way, whether a member calls it, passes its address, a kept vtable names
it or an exception table names it, becomes a `duplicates` row at the address the retail field holds
(an inline virtual function the retail linker kept from another file is never `stripped`: `verify`
rejects a stripped body anything kept still names). When that copy is a
[profile twin](#duplicates-switch-tables-and-exception-data), the tool compiles the same source
under the twin's unit profile, as `verify_emitted_unit` does, and requires that copy at the retail
extent there. A datum only an exception table names, such as the type string of a `throw()`
specification, is listed like any other. A call out of the file that only a duplicate makes
(`operator delete` in an inline destructor) is an `externals` row too, read from the `jal` of
retail's copy. So is a function out of the file that only an exception table names, such as a
base-class destructor that is declared but never called and appears only as a cleanup pointer. It
is read from the retail table word and must start a retail function, and `verify` still compares
the whole table with retail. An owner the source defines under another name than symbols.txt's (a
C++ file's mangled name, or a `static` that several files define and symbols.txt tells apart by a
file suffix) keeps that name in the row's `symbol`.
Recovered files of both compilers are whole-file units: the CRI middleware and the Sony libraries
under EE GCC in `src/cri/` and `src/sony/`, and game classes under MWCC, such as `src/game/`'s, in
C++ with exceptions on.

An ee-gcc file that defines its own strings or statics refers to them through its section symbols.
`tools/eegcc_compile.py` gives each non-empty data section a `@<section>` symbol (`@rodata`, `@data`,
`@bss`), and the row's `data` gives each section's retail address. `verify` compares `.rodata` and
`.data` byte for byte with retail, and a `.bss` with the zeros the retail loader fills past its
segment's file bytes, so the statics' layout is proved through every reference to them. Both the 2.96
`ee-as` and the 2.9-ee assemblers write REL relocations, so each reference's offset into the section
is read from its instruction field. A `.rdata` directive comes out as `.rodata`.

Compiling the file whole is what the original build did, and under both compilers it decides code,
so a member can match only when the functions before it in the file are present:

- **EE GCC 2.96.** A call to a function compiled earlier in the same file is known not to throw,
  which changes how delay slots are filled.
- **MWCC.** The compiler knows which registers a `static` function compiled earlier in the same
  file writes, and the caller keeps a value in a caller-saved register the callee leaves alone
  instead of saving it in an `s` register first. An external function gets no such knowledge even
  when it is defined above the caller, so the callee keeps its `static`. `return helper(a) +
  other(a);`, where `helper` only reads `a0`:

  ```
  # helper only declared, or external  # static helper defined earlier
  sq    s0,0(sp)                       jal   helper
  jal   helper                         sq    s0,0(sp)
  move  s0,a0                          jal   other
  move  a0,s0                          move  s0,v0
  jal   other
  move  s0,v0
  ```

  The knowledge also moves registers before the call: a value the caller is done with goes in a
  temporary the callee writes anyway rather than in `v0`.

  Neither inline expansion nor anything else changes under the game's profiles (`-inline` without
  `auto` inlines only functions declared `inline`). The retail effect is visible: a read of `a0`-`a3`,
  `t0`-`t9`, `v1` or `$f2`-`$f19` after a `jal`, with no write in between. `scripts/same_file_calls.py`
  lists every such call. It is evidence that the callee was `static` and compiled first, so every
  function that calls it belongs to the same file.

Most Alchemy libraries compiled as one translation unit each, not one per class. MWCC emits a class's
inline virtual functions after the last ordinary function of the unit, so every class's slot-20
metaobject getter lands in one run at the end of the library's code, in the order of the library's
vtable block in `.data`; a library compiled per file instead ends each file with its own short run.
The run also holds the inline methods of classes whose only other code is in the registration block at
the library's front, and a function emitted in the run is a getter or an empty slot named after
whichever vtable a disassembler scanned last, not after its owner. A unit's `.rodata` strings run in
code order across all its classes. A library-sized unit is built and measured like any whole file: one
row over the library's range, its members in retail order. A member that matches only under another
profile argues against one unit. An equal float literal read from two pool addresses does not: the
retail linker gave each literal reference its own lookup in a hash table of pool entries where a newer
entry of another value in the same slot replaces the older one, so a later reference to the same
compiled literal can get a new entry ([compiler literals](compiler-object-verification.md#compiler-literals)).
The game's generated front units (the
register list, latch and data classes of a game library) compiled the same way under the game profile,
exceptions on; their run can also hold a copy of an inline method of a class whose own file comes later,
and retail keeps that copy, so it is a member of the front unit.

Such a unit is written as the original most likely was, a unity build: `src/engine/<library>/<Library>.cpp`
(`src/game/<library>/` for a game library) holds only `#include` lines, the library header with the shared
declarations first, then one `.inc` fragment per class run in retail order, named after the class
(`<Class>_tail.inc` when a class's code resumes later; `LibraryFront.inc` for the latch and register list,
`InlineTail.inc` for the trailing getter run). MWCC opens files without regard to case, so of two classes
whose names differ only in case the later one's fragment takes a suffix (`<Class>_Command.inc`). The
includes are repository-relative (`#include "src/engine/<library>/<Class>.inc"`), since MWCC searches its
working directory, not the including file's. The compiler sees the same text a single file would give, so
the object is identical; tools that read definitions from source go through `tools/srctext.py`, which
expands those includes, and the fragments are never scanned on their own.

A C++ file's object names are mangled while `symbols.txt` keeps the plain names its source
and callers use, so `emitted` and `externals` carry the mangled names and `symbol` gives the owner's.
Two stock files may each keep a `static` of one name: the row that places the name says which is the
retail function. Four things differ from an ordinary group:

- **The source is never split.** `tools/units.py` hands the file to the compiler unchanged, so its
  statics and macros stay in place. K&R definitions are read as definitions.
- **`stripped` is any function the retail linker dropped**, not only a destructor. It must still be
  a complete `.text` section that nothing kept references. The search for a retail copy is skipped:
  a stock getter matches any getter once its relocated words are masked, and a stripped name earns
  no credit and is never linked.
- **`data` and `anon` give each datum a retail address.** A named datum is a `data` row: a symbol
  the object defines, or a name it only references. An anonymous datum (`@183`, a string, a switch
  table, a type name) or function-local static (`watchNames$14`, and its guard
  `@GUARD@translation$16608`) has no name to key a row: MWCC numbers these by a counter that every
  declaration of the translation unit advances, headers included, so one more enum in a shared header
  renumbers them all. Such a datum is listed by its retail address alone, in `anon` (ascending), and a
  numbered label is refused as a `data` row. `verify` binds each compiled one from its references
  (`verify.bind_anonymous`): the placed bodies and named data are read first, then the exception
  tables; a reference names the address that makes its relocated field equal retail, the first binds
  the datum and its own references are read from there. Every reference of the bodies and data must
  name the same address, it must be in `anon`, and no two anonymous data may share it; otherwise the
  datum is a `DIFFER anonymous datum` line, its references stay unresolved and the unit is a mismatch.
  An anonymous datum the object keeps that nothing compared refers to rejects the object. Each
  defined section is then compared byte for byte with retail, relocations applied, and references
  resolve to its address. A table that disagrees with a body is left to the table comparison
  (`exc=differ`). Switch tables are anonymous data here, since they belong to a member rather than
  the owner, and their retail `jtbl` units stay. A float or double literal is not a row: as in a
  group, each reference reads the pool entry its retail instruction names (`verify.fold_literals`),
  so one literal may sit at several entries; the literals only stripped bodies reach go with them.
  `@STRING@<function>` strings keep `data` rows: MWCC names them after the function, and the linker
  merges the copies of one name across files.
- **`duplicates` are read from retail.** An inline destructor or helper the file emits whose kept
  copy is in another file is a duplicate when a member still calls it or names it in its exception
  table: its address is the one the retail `jal` or table word holds, and its body must fit there.
  Two inline destructors of one shape fit the same start; `--drop` names the one that is not the
  file's own.

With exceptions on, each member's index record and table are compared as in an ordinary group, and
the object has one verdict. A member whose record retail keeps but the file does not produce makes
the whole file `code-only`, and a member whose bytes differ makes it a mismatch, so such a function
stays out of the file under `--partial` until it reproduces.

A data section no placed body or declared datum reaches went with the functions the retail linker
dropped, so it needs no row and is not linked. A section a placed body does reach must have a row,
or the object is rejected as unowned. The data itself is never linked from the object: the isolated
body refers to `DAT_<address>`, which `tools/linkgen.py` provides, and retail's bytes stay in place
after being compared.

## Static initialisers

MWCC compiles the construction of a file's global objects into one function, `__sinit_<file>`, named
after the source file, in a section of its own named `.init`. A 4-byte `.ctor` word points at it, and with
exceptions on it has an index record like any function. The retail linker put every object's `.init` after
all `.text` (`0x51fd00` up to `0x522438`) and every `.ctor` in the table `__init_cpp` walks (`0x522440` up to
`0x522480`, [Metrowerks runtime](runtime-metrowerks.md)), both in link order, so the table lists the owning
files in the order they were linked. A function of that range is not code of its own: it is the initialiser
of the file that defines the objects it constructs, and it compiles from that file.

The owning file's whole-file row names its initialiser in `emitted`, under the compiler name
`__sinit_<file>`, at the retail initialiser's address; that row is the one record of the pairing, and the
table entry is the one retail entry holding that address. `tools/whole_file_rows.py` reads the address from
retail: the table entry whose function the compiled `.init` fits, relocated fields masked (`--at
__sinit_<file>=<va>` settles a fit to several; a file that still lacks some of its range's functions needs
`--partial`). The file's `units.tsv` span still ends at its last `.text` function, and the objects the
initialiser constructs are `data` rows like any datum (a global in `.bss` is compared with the zeros the loader
fills). A `const` object with a constructor sits in `.rodata`, so retail's initialiser stores into read-only
data. An object that `data-names.tsv` already names keeps that name, defined by the owning file, and its
`data-names.tsv` row goes; each other whole-file unit that references it lists it as a `data` row. All sixteen
initialisers of the range compile from their owning files, so no `units.tsv` row covers `0x51fd00` up to
`0x522438`. A translation unit has one initialiser, so a row places at most one: a range retail serves with two
initialisers is two files. `tools/progress.py` counts each initialiser with its owning unit's library in the
README's region table; `regions.tsv` and the module map keep the range, which describe the image.

`symbols.txt` names each initialiser of the range by that same string, dot included (`__sinit_be.cpp`), from
`config/SLUS-20836/names/StaticInitializers.tsv`: `tools/split.py` keeps the dot of a `__sinit_` name, which C
never spells and GNU as accepts in a label, so the generated `asm/__sinit_be.cpp.s` and the `emitted` key agree.
An initialiser has no source text of its own, so `tools/progress.py` judges its readability on its file's global
definitions: the file, comments and strings blanked, without its function definitions.

`verify` compares the `.init` body like any member, its index record with `exceptions.txt`, and the `.ctor`
word, relocated, with its table entry. An object whose `.init` the row does not name is rejected, as is any
other shape (two `.init` sections, a `.ctor` word that points elsewhere), and an initialiser whose bytes
differ makes its file a mismatch. MWCC pads the initialiser's names (its own, its table word's, its
record's) with blanks and leftover bytes that change from one compile to the next, so `verify` cuts each
name at its first blank before reading the object, and `whole_file_rows.py` does after compiling.

For the link, the initialiser's own object (`isolate_emitted_body`) renames its `.init` to `.text`, which
`tools/linkgen.py` pins at the initialiser's layout address like any code unit, and keeps the `.ctor` word,
pinned at its table entry by carving the raw data unit around it as for an exception record. Every other
member's object drops the `.ctor`.

### The Alchemy library initialisers

Five initialisers construct the static smart pointers of an Alchemy library file, each from its owner's
whole file. The objects are defined in the library's `.cpp` directly after its header, in the initialiser's
construction order. Each `igSmartPointer<T>` makes the compiler emit a `__dt__…igSmartPointer<T>Fv` copy, and
the row's `emitted` (or `duplicates`, for a copy another file places) gives each copy its retail address by name,
so the order the copies take in the object does not matter.

| initialiser | file | objects (retail address) |
|---|---|---|
| `0x51fd00` | `src/engine/attrs/AttrsLibrary.cpp` | `igAttrPool` (`0x55f4b8`), `igCustomVectorStateList` (`0x55f4d8`), `igCustomMatrixStateList` (`0x55f4f0`), `igModelViewMatrixAttr` (`0x55f508`), `igCustomVectorStateList` (`0x55f538`) |
| `0x51fe40` | `src/engine/audio/AudioLibrary.cpp` | `igPsx2AudioSourceList` (`0x55f5d0`) |
| `0x520cf0` | `src/engine/scenegraph/SceneGraphLibrary.cpp` | three animation pools, a `(1, 1, 1)` `igVec3f`, the Enbaya context pool, an alpha-state attribute, an `igFolder`, the projective shadow's viewport matrix and the environment-map shader's eleven default attributes (`0x562528` up to `0x562b58`) |
| `0x5210d0` | `src/engine/base/BaseLibrary.cpp` | `igIntList` (`0x56da78`), `igNodeUsageObjectDefinitionList` (`0x56da90`), `igIntList` (`0x56daa8`) |
| `0x521750` | `src/engine/gui/GuiLibrary.cpp` | `igGraphPath` (`0x58c670`) |

No PS2 code reads `0x55f4d8`, `0x55f4f0`, `0x55f538`, the three base objects or the gui path. The initialiser only
constrains which of them share a type (one destructor for `0x55f4d8`/`0x55f538`, one for `0x56da78`/`0x56daa8`). The
types come from the GameCube `main.dol`, whose initialisers for the attrs and base files construct the same objects in the
same order with the same sharing. There, the attrs objects are written by virtual functions of
`igFloatConstantAttr`, `igMatrixConstantAttr` and `igVectorConstantAttr`. Each function creates the list and fills
it with 128 `igCustomVectorState`/`igCustomMatrixState`. The base pair `0x56da90`/`0x56daa8` is written by
`igStatisticsNodeUsage`. The GameCube gui object is passed as the path a graph search fills, so it is an `igGraphPath`.
The PS2 build registers none of the three list classes or their owners, so the lists are declared in
`include/dw4/unregisteredClasses.h`, with the GameCube registrations' bases. The game's own users of retail
`0x150eb0` already call it `igSmartPointer<igIntList>`'s destructor.

## Verification and placement

For a registered compiler object, verification requires:

1. Every declared function symbol exists at offset zero in its own complete
   `.text` section (`.init` for the static initialiser), with the exact recorded retail size.
2. All nonempty allocated/executable/code sections belong to declared members.
   Unknown code, emitted runtime data and exception tables fail closed.
3. Retail extents do not overlap, and explicit external aliases cannot conflict
   with the existing symbol map or definitions in the object.
4. Every instruction byte and relocation in every member agrees with retail.
   Checking the owner also checks its destructor; checking the destructor also
   checks its owner. A failed member rejects the whole object.

Objects without an ownership entry retain the isolated-function rule. The
existing test with an extra unknown function still fails; the rule is not
replaced by an unchecked function slice.

After full verification, each layout entry receives one member object. Sibling
definitions become external references to their own independently placed units.
The selected symbol receives its canonical retail label; the compiler-specific
binding becomes an ordinary global for GNU ld. Section names are changed by
index before removing the already-verified siblings from this per-function copy.
The retained instruction payload and complete relocation stream, including
ownership and ordering, must remain unchanged apart from declared symbol aliases.
No instruction is patched to make a match.

`-Cpp_exceptions off` suppresses new exception metadata in this compiler unit.
It does not suppress the destructor. Original retail data stays in the normal
layout; the setting is a matching-build requirement, not proof of original flags.

## Complete title update unit

The [title-menu update](title-menu-controller.md#complete-matching-unit)
(`0x3f2ef0`) uses the full code/table path: an 8,992-byte primary body, five
128-byte cleanup copies, three switch tables and its original exception
index/payload. The five copies are `duplicates` of independently matched
standalone cleanup sources; those sources retain placement ownership.

The 128-byte exception region includes one zero alignment byte. All fourteen
protected ranges and the five cleanup identities agree with compiler output.
Redirecting one cleanup alias to a byte-identical function is rejected by the
exception-table comparison even though every code body still matches. Selecting
the adjacent exception-index record is rejected too.
`config/SLUS-20836/unit-objects.json` records the source, profiles and evidence.

The symbol reader handles processor-specific binding 13. Readelf prints that
binding in several tokens, so section/name extraction uses its final columns
instead of fixed binding-column positions.

## RAII holders and exception tables

A RAII cleanup scope reproduces retail's exception table only when the holder:

- is a class with a real inline destructor (the release is not hand-spelled before each exit);
- is built at its use site from the factory result (`Holder h(create(a));`, no constructor store);
- is declared after any earlier return;
- has one class instantiation per distinct destructor copy the table names: `igSmartPointer<A>` and
  `igSmartPointer<B>` are two copies, each with its own row.

The `unit-objects` row names that copy, read from the decoded table's action list, in `duplicates`
(copy elsewhere) or `emitted` (copy placed behind the owner). `externals.__dl__FPv` is what that copy
calls: `0x100610` for releasing copies, `0x2ed5c0` only for the 68-byte empty destructor at `0x2e2300`.

Table tags: `0x02` destroy, `0x06`/`0x86` base subobject flag 0, `0x07`/`0x87` member subobject flag -1,
`0x01` chain link. `scripts/combat_unwind_inventory.py` does not decode `0x01`, `0x06`/`0x86`/`0xa6`,
`0x07`/`0x87`/`0x27` or an FPR-flag header.

An out-of-line constructor that keeps `this` in a saved register writes its members' cleanup as
`0x27` (`0xa7` for the last action of the chain): the location byte is the register (`0x20`, register 16,
`s0`), then the member's compact offset and the destructor address. A class held as the first member
(`0xa7 20 00 ...`) is told apart from a base class this way: a base writes `0xa6 20` with no offset, and
its destructor is called with flag 0 where a member's gets -1. Each range action starts the chain at the
last member constructed before that call; a by-value temporary passed to the first member's constructor
has its own destroy action (`0x82`) over that call alone. Members whose constructors make no call (a
retaining holder built from 0, a `bool`) add no range.

Further holder shapes:

- Expression temporaries take the lowest frame slots. A temporary read in one statement is destroyed at
  its end and gets no unwind range.
- Nested holder chains take one holder per scope, built at the use site.
- A holder inside an inline helper has its destructor expanded only at an inline depth of 2 or more.
  Bec and Ndmw build with `-inline level=8,bottomup`, so there it needs nothing extra, except in a function
  past the bottom-up size limit ([build profiles](build-profiles.md)), where only the helper itself is
  expanded; the locals of an inlined helper take the frame slots below the function's own locals and temporaries.
- Volatile holder members reproduce a store-then-reload.

## One reference holder

Every reference holder is `igSmartPointer<T>` in `include/dw4/igSmartPointer.h`; the executable holds its name, as
`::~igSmartPointer<`. Its destructor is `igRelease(p)`, an inline taking `igObject *`, and that one text gives both the
128-byte out-of-line copy retail keeps and every inlined release. Whether an inlined release reloads the held pointer
after the decrement store depends on the holder, not on the class:

- An unnamed temporary reloads: a by-value argument, a returned value, a temporary bound to `const &`, or `.get()`
  on a temporary. So does a named holder built by copy-initialisation (`h = f()`) and read only through `.p`.
- A named holder built by direct initialisation does not, nor one used through `.get()`, `->`, its `T *` conversion,
  `const &` or `&`. The exception mode and `-O4,s` against `-O4,p` make no difference.
- The implicit `T *` to `igObject *` conversion in the call decides load reuse. With `T` a derived class, a test read of
  the holder is reused by the destructor; with `T = igObject`, a `.get()` read is not. This is why `reflected.h` gives
  each class an `igObject` base under C++.
- The out-of-line copy is 128 bytes because `this->p` goes through the parameter.

A class with virtual functions has its vtable pointer where `igObject` keeps `_vtable`, so it derives from
`igVirtualObject` instead, which has a real virtual first slot and `_refCount` at +4. A plain constructor adopts the
reference; a retaining one takes `kRetainReference`, an enum that costs no bytes.

## Tests

`python3 tools/test_unitobject_metadata.py` (seven tests, same GNU-linker oracle)
covers duplicates in the same and a different profile, switch tables, exception
index and table, padding, corruption of each region, fail-closed rejection without
the declarations and complete linkgen placement.

Run `python3 tools/test_unitobjects.py`. Six real-compiler tests compare both
bodies with independently GNU-linked bytes, verify source ownership, reject a
corrupted member from either entry, reject missing/unowned functions and
conflicting aliases, reject unresolved auxiliary calls and exception data, and
link the complete fixture including untouched gap bytes. Corrupting the member
also prevents linkgen from producing a link script. The existing relocation,
multiple-switch-table and permuter tests remain applicable.

Run `python3 tools/test_whole_file_units.py` for the whole-file rows: the overlay rules, the row
generator's placement, and against
a GNU-linked fixture, a changed datum, a wrong address, an undeclared datum, labels renumbered by one
more declaration, two references that disagree and the isolated body; the runtime's `NMWException.cpp`
still verifies against its row with an enum added ahead of it. Against retail, a recovered file's static
initialiser verifies with its table entry and record and links with them, the rows find it in the table, an
initialiser whose bytes differ makes the file a mismatch, one the row does not name rejects the file, and a
row naming two is refused.

Implementation: `tools/unitobjects.py`, `tools/units.py`, `tools/verify.py`,
`tools/check.py` and `tools/linkgen.py`. The full byte-identical retail relink
remains the integration oracle.

## Open questions

- **Why `igTDataList` takes its parameter's address.** `find` and `append` take the value by value and read it through
  `const T *p = &v`, which is what keeps it on the stack. A plain read or a reference folds it into a register. The
  bytes show the store, not the reason, and nothing yet shows why the source would write this.
- **What the empty tag objects were.** The `sb zero` beside a factory call shows an empty class passed by value. Its
  purpose is not shown: it may have selected a constructor, or been a default argument or an allocator. Names such as
  `AdoptReference` and `DriverType` are best guesses and need more evidence. One context is known: the five tags of
  the viewer setup's constructor (`0x463560`) are the adopting `igSmartPointer` constructor's argument in member
  initialisers, with no helper, and its destructor (`0x463910`) is the compiler's teardown of those members.
- **One root.** `igVirtualObject` stands beside `igObject` because a polymorphic class puts its vtable pointer at +0. A
  polymorphic `igObject` under C++ would give one root, but needs another pass over the generated header.
- **What the retain tag was.** `RetainReference` selects the retaining constructor at no cost in bytes. The name and the
  mechanism are best guesses: the original may have used a separate function or another overload.
- **Helpers holding only an empty tag.** Some inline factories exist to hold an empty tag object for its `sb zero`, and
  some take one. The bytes show the object, not these helpers or their names, which need a later pass.
- **A unit's profile and its pragma.** One member of a `-O3,p` unit needs no pragma under `-O4,p -inline level=8`, but
  another member then gains a code difference. Which profile the unit was built with is open.
- **Limits of the unit-objects model.** Two class symbols cannot alias one retail destructor address:
`0x41acf0` needs direct-p and single-load shapes at different sites of one class. The closest spelling of
`0x38b1f0` differs in the order and registers of loop-invariant values in the preheader.
- **Member-subobject tables at the frame size.** `0x350100`, `0x3b0a80`, `0x33c950`, `0x3c0120`, `0x3c0640`,
  `0x3bfd60` and `0x3c1480` are the only retail functions with tag `0x07`/`0x87` (`0x86` for the base) tables
  whose location field equals the frame size, and they never materialise an inlined `this`: every member
  address is a constant `addiu a0,sp,N`. The construct is a class with N non-trivial members whose constructor
is inlined. A spelling reproduces the tables of `0x3bfd60` and `0x3c1480`. For the other five,
no available compiler emits the construct: the combat family uses tag `0x27`/`0xa7`
  with a register in the location field and keeps `this` in a saved register (712 bytes against 784 for
  `0x350100`); the stack family uses tag `0x07`/`0x87` with frame-4 and stores and reloads `this`. About 25
  spellings and every pragma and flag variant failed. Unproven: retail's compiler build treats the tracked
  `this` as a dead variable at the default location, a build not available here.
- **Names from the reflection accessors.** Unproven: `0x195a90` is the `igNode` destructor
  (`igTransform_GetVTable` ends with a call to it), `0x1962d0` the `igTransform` destructor, and `0x33f5e0` the
  destructor of an unnamed controller base shared by `beLayerCtl`, `beFont`, `beMovie`,
  `beNDMWLogo`/`SaveCtrl`/`SaveIntf`/`GameRam` and `beShadow01`.
- **Owners resting on position.** `0x521150` (a 16-colour palette nothing reads) is scene-search's by its place
  in `.rodata`, and `0x5223f0` (two colours nothing reads) is `beCameraMode`'s or `igViewManager`'s: the bytes are
  the same either way.
- **Names of the library initialisers' objects.** A defined object needs a name that spells no address, but most
  of these names are inferred:
  - **From the creating function.** `g_<Class>_instance` names the one object a function creates. The three pools
    `main` creates are in [engine boot](engine-boot.md#the-managers-are-named).
  - **From the GameCube owner and type.** `g_igFloatConstantAttr_stateList` and its siblings, and
    `g_igStatisticsNodeUsage_definitions`/`_intList`.
  - **From what the creator sets.** In `g_envMapTextureUnit1On` the unit and enable values are its creator's
    `igTextureStateAttr` calls. In `g_envMapBlendOneOneUnit1` the factors are its creator's `igBlendFunctionAttr`
    calls, and the factor names come from `IG_GFX_BLENDING_FUNCTION`.
  - **Without an owner.** `g_baseIntList` (`0x56da78`) has no owner in either build. The GameCube build reads
    `g_guiGraphPath` (`0x58c670`) once, as the path a gui method fills through a graph search, and nothing names
    that method's class.
