# Explicit compiler-emitted function ownership

The player stat recompute (`0x3fab90`) and the nearby-query C++ source are
one compiler unit (its source includes the query from
`src/game/beNDMWGameRam_CollectNearbyNonzeroHp.inc`). It emits two further real
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
    "data": {"@183": "0x004e7490", "inflate_mask": "0x00497b20"}
  }
}
```

The owner is the file's first retail function and `emitted` names the others; the file has one
`config/SLUS-20836/units.tsv` row, so every member shares its profile. `tools/whole_file_rows.py`
measures the rows from retail and stops if a retail function in its range has no compiled copy; its
docstring gives the command, and [`src/third_party/`](../../src/third_party/README.md) holds the
sources. A C++ file's object names are mangled while `symbols.txt` keeps the plain names its source
and callers use, so `emitted` and `externals` carry the mangled names and `symbol` gives the owner's.
Two stock files may each keep a `static` of one name: the row that places the name says which is the
retail function. Three things differ from an ordinary group:

- **The source is never split.** `tools/units.py` hands the file to the compiler unchanged, so its
  statics and macros stay in place. K&R definitions are read as definitions.
- **`stripped` is any function the retail linker dropped**, not only a destructor. It must still be
  a complete `.text` section that nothing kept references. The search for a retail copy is skipped:
  a stock getter matches any getter once its relocated words are masked, and a stripped name earns
  no credit and is never linked.
- **`data` gives each datum a retail address.** A row is a compiler symbol (`@183` is a string
  literal; the numbering is stable for one source and profile) defined by the object, or a name it
  only references. Each defined section is compared byte for byte with retail, relocations applied,
  and references resolve to the row. Switch tables are `data` rows here too, since they belong to a
  member rather than the owner, and their retail `jtbl` units stay.

A data section no placed body or declared datum reaches went with the functions the retail linker
dropped, so it needs no row and is not linked. A section a placed body does reach must have a row,
or the object is rejected as unowned. The data itself is never linked from the object: the isolated
body refers to `DAT_<address>`, which `tools/linkgen.py` provides, and retail's bytes stay in place
after being compared.

## Verification and placement

For a registered compiler object, verification requires:

1. Every declared function symbol exists at offset zero in its own complete
   `.text` section, with the exact recorded retail size.
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
- has one class per distinct destructor copy the table names.

The `unit-objects` row names that copy, read from the decoded table's action list, in `duplicates`
(copy elsewhere) or `emitted` (copy placed behind the owner). `externals.__dl__FPv` is what that copy
calls: `0x100610` for releasing copies, `0x2ed5c0` only for the 68-byte empty destructor at `0x2e2300`.

Table tags: `0x02` destroy, `0x06`/`0x86` base subobject flag 0, `0x07`/`0x87` member subobject flag -1,
`0x01` chain link. `scripts/combat_unwind_inventory.py` does not decode `0x01`, `0x06`/`0x86`/`0xa6`,
`0x07`/`0x87`/`0x27` or an FPR-flag header.

Further holder shapes:

- Expression temporaries take the lowest frame slots. A temporary read in one statement is destroyed at
  its end and gets no unwind range.
- Nested holder chains take one holder per scope, built at the use site.
- A holder inside an inline helper has its destructor expanded only at an inline depth of 2 or more.
  Bec and Ndmw build with `-inline level=8`, so there it needs nothing extra; the locals of an inlined
  helper take the frame slots below the function's own locals and temporaries.
- Volatile holder members reproduce a store-then-reload.
- A `(o = p) != 0` destructor shares the load with the use site.

In several units the destructor inlined in the owner reloads the held pointer after the decrement store
(direct `p->_refCount = p->_refCount - 1`) while retail's 128-byte out-of-line copy does not
(`igObject *o = p`), and one source text cannot produce both. The verifier compiles an exceptions-off
duplicate's copy in a second compile, so the spellings can be selected per mode with
`#if __option(exceptions)` (`__option(cpp_exceptions)` is silently false in both compiles) or a
`__MWERKS__ >= 0x3000` gate. The split is a compiler constraint and carries a matching-construct comment.
It suggests the retail sources had two definitions of the class.

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
a GNU-linked fixture, a changed datum, a wrong address, an undeclared datum and the isolated body.

Implementation: `tools/unitobjects.py`, `tools/units.py`, `tools/verify.py`,
`tools/check.py` and `tools/linkgen.py`. The full byte-identical retail relink
remains the integration oracle.

## Open questions

- **Why `igTDataList` takes its parameter's address.** `find` and `append` take the value by value and read it through
  `const T *p = &v`, which is what keeps it on the stack. A plain read or a reference folds it into a register. The
  bytes show the store, not the reason, and nothing yet shows why the source would write this.
- **What the empty tag objects were.** The `sb zero` beside a factory call shows an empty class passed by value. Its
  purpose is not shown: it may have selected a constructor, or been a default argument or an allocator. Names such as
  `AdoptReference` and `DriverType` are best guesses and need more evidence.
- **When the inlined release reloads.** Unproven: retail's inlined reference release reloads the holder
  pointer between the decrement store and the zero test only when the holder's address escaped to a call,
  not for register-held holders (seen at `0x33bd30`, `0x339110`, `0x43dc10`, `0x25ac60`). In one compile the
  direct `p->` spelling reproduces each owner body and table but makes the kept linkonce destructor 132 bytes
  under the default profile, against retail's 128; the `o = p` spelling does the reverse. About seven
  spellings per unit were tried.
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
