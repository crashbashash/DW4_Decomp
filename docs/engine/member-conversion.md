# Member conversion: the polymorphic root and staging rules

The engine's classes move from flat structs with free `<Class>_<Method>` functions to Alchemy's polymorphic
classes (`Gap::<library>::<class>`), one class at a time, with every touched unit byte-identical at every step.
This page is the design of that migration and the rules for staging it. The tools are described in
[build-system.md](../build-system.md#member-conversion), the tables in
[typed coverage](typed-coverage.md#c-members-typed-references-and-converted-classes).

## Tables

Three `#`-commented TSV tables drive `scripts/gen_type_headers.py`, which writes `include/dw4/support/reflected.h`:

| Table | Row | Effect |
| --- | --- | --- |
| `config/converted-classes.tsv` | `<class> <library namespace>` | the class is declared as `namespace Gap { namespace <library> { class <class> : public <parent> … } }` after the flat structs, and promoted into `Gap` with `using` |
| `config/class-members.tsv` | `<class> <declaration>` | the class's members in table order: object macros, `k_<field>` handles, kit inlines (`igMetaObject::isValid`), member functions, virtual slots; each in the kit header's access (`protected: igObject();`, unlabelled is public), a section opening where the access changes |
| `config/typed-fields.tsv` | `<class> <field> <C++ type>` | an object-reference field typed under C++ (`igSmartPointer<igVisualContext>`); C keeps the reference word |

A converted class's parent must be converted too. A converted class declares only its own fields, at their
reflected offsets after its parent's registered size, and then its member rows. Access follows the kit header
(owner ruling 6): igObject's constructors and `_Meta` are protected, igRenderer's `k_visualContext` protected,
igClearRenderer's `k_buffersToClear` private; the fields stay public, since C code reads them as data. Code outside
a class reads a protected `_Meta` through the public `getClassMeta()`, as igen's code does
(`Gap::Core::igObject::getClassMeta()`), which compiles to the same load.

## The root

`Gap::Core::igObject` is an ordinary row of `converted-classes.tsv` (`igObject Core`), and all of its
declarations are `igObject` rows of `class-members.tsv`; the generator refuses a root that has no rows and
writes the root's virtual slots before `_refCount`, so the vptr sits at +0 as retail's does. The rows are, in
order:

- the constructor (`igObject::igObject()`, retail's header initialisation) and `operator delete`, which frees
  through `Memory_FreeBufferAliasC`;
- the 20 virtual slots in `igObjectDispatchView`'s order, `destruct` through `cloneViaMetadata`, then the
  inline virtual `getMeta` as slot 20. The macros override `getMeta` in every class, so every class writes its
  vtable the way retail's does. The root declares no destructor;
- the kit's static members: `_Meta`, `arkRegister`, `arkRegisterInternal`, `getClassMeta`,
  `getClassMetaSafe`, `retrieveVTablePointer`, `arkRegisterInitialize`.

The core unit defines these as members and emits igObject's vtable itself.

## Coexistence with flat structs

Every class keeps its flat struct as the C view: the C units and the classes not yet converted still use it.
A converted class's members and typed fields go only into its `Gap::` declaration, and code outside `Gap`
still names the flat struct. A typed field's flat struct still spells the reference as `int`, so
`reflected.untyped_refs` (`tools/progress.py`) leaves out the fields `typed-fields.tsv` lists.

Where converted and unconverted code meet, the boundary keeps the retail **C names** as prototypes:

- a class that is not converted yet still calls the root's slot defaults and its constructor by their C
  names;
- a converted class whose parent is not converted, or a converted parent with flat subclasses, needs the C-name
  prototypes the other side calls. For example, gui and viewer still call `igRenderer_Destroy`, and
  `include/dw4/gui/igRenderer.h` keeps its prototype; the definition is now igRenderer's implicit destructor,
  which insight emits;
- `tools/memberize.py` decides it: while code still names a converted member's C name (a C caller, a flat
  subclass, a flat struct's construction or destruction), the prototype stays in the home header, and in
  another header only for a user's unit that does not read the home header; every other declaration goes, all
  of them once nothing names the C name. `tools/memberize.py --check` reports a C-name declaration no longer
  needed.

A converted class calls through a typed member or a `…DispatchView` with named slots, such as
`igVisualContextDispatchView` for the renderers' visual context. Stand-in views with `dN` slots (`O_…`/`E_…`,
local `…View` classes) go away as their users convert.

## Converting a class, in order

1. Add the class (and any unconverted parent) to `converted-classes.tsv`, its members to `class-members.tsv` in
   the kit header's order, and its typed fields to `typed-fields.tsv`. `tools/gen_odl_source.py
   --write-members` writes the macro and field-handle rows.
2. Run `tools/memberize.py <table> --apply` to rename the free functions and data to members (constructors and
   implicit destructors included) and rewrite their callers; the definitions go into the class's namespaces.
3. Run `tools/gen_odl_source.py` to write igen's registration boilerplate. Write any body that igen's form
   does not cover by hand, in the kit's form. Then regenerate the header with
   `python3 scripts/gen_type_headers.py`.
4. Run `tools/whole_file_rows.py --unit-va <va> --cxx --write` for each touched unit, the defining unit first and
   its callers after. The unit's present row settles its partial functions, ambiguous starts, static-initializer
   entry and data names; `--drop`/`--at` are needed only for a start no row settled yet.
5. Run `tools/compiler_names.py --write`.
6. Run `tools/check.py --function <va> --cand <source>` for every touched unit. Each must report `MATCH`. Then
   `tools/memberize.py --check` (no C-name declaration left over) and `tools/typed_coverage.py --check`.

## Conversion order

The root and the renderers (`igRenderer`, `igClearRenderer`, `igFlushRenderer`) are converted, and of igObject's
kit-declared members also the bootstrap and copy constructors (`igObject(bool bootstrap)`,
`igObject(const igObject &)`, which construct the header with the kit's placement `operator new(size_t, void *,
void *)`), the storage calls (`malloc`, `mallocAligned`, `calloc`, `realloc`, `reallocAligned`, `free`, `strdup`)
and `copy`, `copyShallow`, `isAlikeExactly`, `traverseFields`, `getIoSize`, `printFields`. The order after that:

1. the rest of igObject's kit-declared members: `internalRelease` (`igObject_Destroy`), `isOfType`
   (`igObject_IsKindOf`) and `getMemoryPool` (`igObject_GetAllocator`), which macros and inline casts of
   unconverted classes call; `copyDeep`, `isAlikeDeep`, `isAlikeShallow`, whose C forms take
   `igObjectDispatchView *` parameters;
2. the metafield family (`igMetaField` and its subclasses);
3. `igMetaObject`, `igDataList`/`igObjectList`;
4. attrs, then gfx, then scenegraph, then gui/insight/viewer;
5. the game's `be*` classes last.

## Known differences and gaps

- Definitions written before the namespace spelling (`void Gap::Gui::igRenderer::setVisualContext(…)` at file
  scope) compile to the same code; `tools/memberize.py --respell --apply` moves them into their namespaces.
- A destructor a class declares out of line, and a constructor whose C form constructs its base after other
  statements, are written by hand.
- The flat struct `igObject` and the class `Gap::Core::igObject` are two types of one name, and
  `tools/memberize.py` writes the casts between them: a receiver or a `Class *` argument declared as the flat struct
  (or a flat subclass, or not declared) is cast to the Gap class (`((Gap::Core::igObject *)m)->realloc(…)`,
  `->copy((Gap::Core::igObject *)g_x, 1)`, `igObject` alone in Gap's scope), a cast of `this` to the flat struct
  passed to a Gap parameter goes, and a body moving into the class keeps what its types meant: its bare receiver
  passed on is `(::igObject *)this`, and every other bare `igObject` in it `::igObject`. A C form taking a reference
  where the member takes one (`igObject(const igObject &)`) is refused and written by hand.
- `tools/whole_file_rows.py` keeps a caller unit's row as it was where the compile did not change it: an entry
  stays in its place while its name still binds at its address (the object names it, or symbols.txt,
  data-names.tsv, the compiler-name map, another unit's row or the address in the name binds it), so stale aliases
  (`DAT_004fb410` beside `g_resultSuccess`) stay until their name stops binding.
