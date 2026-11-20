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
void *)`), the storage calls (`malloc`, `mallocAligned`, `calloc`, `realloc`, `reallocAligned`, `free`, `strdup`),
`copy`, `copyDeep`, `copyShallow`, `isAlikeExactly`, `isAlikeDeep`, `isAlikeShallow`, `traverseFields`,
`getIoSize`, `printFields`, `isOfType`, `getMemoryPool`, `getClassStorage`, the private `internalRelease`, the
construction steps (`constructDerived`, `constructDerivedFromFile`, `finishConstructDerivedFromFile`,
`commission`, `construct`, `internalResetFields`, `destruct`, `decommission`), `emptyArkRegisterInternal`,
`emptyGetClassMetaSafe`, and slot 0 is the kit's `__bootstrapDestruct`. The order after that:

1. igObject's last kit members: `resetFields()` (`igObject_ResetFields`; memberize tells this non-virtual
   overload from the virtual `resetFields(int)` slot by its parameters), `free(igRawRef)` (`igObject_FreeStorage`),
   `createCopyRef` (`igObject_Clone`, whose return type is a
   smart pointer of the flat struct), the I/O members (`writeToMemory`, `readFromMemory`), the `operator new`
   pair (`igObject_AllocateRawStorage`); and the release idiom: the callers outside igObject still call
   `igObject_Destroy` by its C name, since `internalRelease` is private, until their inline release is written as
   the kit's `release()`;
2. the metafield family: `Gap::Core::igMetaField` is converted (`IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE`, its three
   constructors, the 38 slots 21-58 in retail's vtable order with kit names, igen's registration); DW4's vtable has
   no `computeTypeCount`, no virtual `readFromMemory`/`writeToMemory` and no `postRead`, and overrides
   `userPostRead`. The I/O chain's `endianSwap` is the kit's `igBool` (`bool`, tested as `if (endianSwap)`), so
   `igIGBFile::_endianSwap` is typed `bool` under C++. Not kit-declared and still free: `ConstructCopy`,
   `GetMangledName`, `FindByName`, `AllocateArray`. Flat subclasses still construct and destroy through the C
   names (`igMetaField_Init`, `igMetaField_Destruct`). `_fieldName` is the kit's `igStringRef` under C++, so
   igMetaField's constructors assign it as the kit does and its implicit destructor releases it: a subclass's
   `retrieveVTablePointer` is the kit's form (a temporary whose destructor stamps igMetaField's vtable and
   releases the name), and the implicit destructors MWCC emits out of line are dead-stripped (`stripped`).
   The scalar metafields (`igIntMetaField`, `igShortMetaField`, `igUnsignedShortMetaField`, `igUnsignedIntMetaField`,
   `igLongMetaField`, `igUnsignedLongMetaField`, `igCharMetaField`, `igUnsignedCharMetaField`, `igBoolMetaField`,
   `igFloatMetaField`, `igDoubleMetaField`) are converted: `IG_METAFIELD_SETUP` (the descriptor `_MetaField`,
   `getMetaField`, the inline `getGenericMetaField`), igen's `arkRegisterMetaValidate` that creates the
   descriptor, `computeSize`, `computeRequiredAlignment`, `setMemoryByString`, `getStringFromMemory` and
   `setDefault`. Retail builds some as bootstrap classes (`IG_BOOTSTRAP_OBJECT_DEFINE`: three constructors,
   `__bootstrapDestruct` and the root's copy slot) and the others (float, double, long, unsigned char) with
   `IG_OBJECT_DEFINE`, whose constructor is implicit. Their `_instantiateFromPool` (`<Class>_Create`, the
   factory every field table names) is still free. The fixed-size arrays of these
   (`igBoolArrayMetaField` ... `igUnsignedShortArrayMetaField`, eleven) are converted the same way
   (`IG_OBJECT_DEFINE`, `IG_METAFIELD_SETUP`, the private `k_num` handle and the kit's `setNum`/`getNum`), with
   the kit's `IG_ARRAY_IMPL` `endianSwapMemory` (the element metafield's `getMetaField()->endianSwapMemory(mem,
   getNum() * num)`), `computeSize` (`getNum() * sizeof(element)`) and the `setDefault` overloads retail keeps
   (int and bool fill every element, char sets one); retail drops their unreferenced `getMetaField`, so it is
   declared and not defined. Their boilerplate, the field adder included, is the generator's.
   `igEnumMetaField` (bootstrap; `setDefault(const int &)`, the string overrides through the kit's
   `getMetaEnum()`), `igStructMetaField` (the C++ constructor and destructor hooks behind `construct`,
   `destruct` and `resetByValue`, which fall back on igMetaField's) and `igVirtualCFuncMetaField` (whose reset
   copies the slot at the default's offset out of the object's vtable) are converted too; their implicit
   destructors fit the retail start of igRefMetaField's and are dropped (`--drop`). The reference family's
   root `igRefMetaField` (`IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE`, protected `k_construct`/`k_destruct`, the kit's
   `commission`/`decommission`, `readRawFieldMemory`/`writeRawFieldMemory` through the directory,
   `convertMemoryToString`/`convertStringToMemory`, `compare`) and `igRawRefMetaField` (`print`,
   `addToDirectory`) are converted; igMetaField's `convertMemoryToString` takes the kit's `hdr` and
   `fieldIndent` and its `compare` returns `int` (`!isAlikeExactly(...)`), so igRefMetaField overrides them;
   startup stores the reference descriptor with `igRefMetaField::setMetaField(igRawRefMetaField::getMetaField())`.
   Their arrays `igEnumArrayMetaField` (the kit's `setDefault(igEnum)` filling every element) and
   `igRawRefArrayMetaField` (whose `readRawFieldMemory`/`writeRawFieldMemory` loop over the elements through
   `igRawRefMetaField::`'s versions, called non-virtually) are converted as the scalar arrays are.
   `igObjectRefMetaField` (bootstrap; protected `k_metaObject`/`k_refCounted`/`k_poolName`, `_poolName` an
   `igStringRef` under C++ so the implicit destructor releases it, the kit's `set`/`setDefault(igObject *)`
   with the reference counting `_refCounted || _destruct` asks for, and its slot overrides: `computeSize`,
   the construct/destruct/reset/copy/compare/isAlike family, `print`, `traverse`, `readRawFieldMemory`,
   `initDefaults`/`releaseDefaults`) is converted. `igMemoryRefMetaField` (bootstrap; `_memTypeRef` an
   `igSmartPointer< ::igMetaField>` and `_poolName` an `igStringRef` under C++, so its implicit destructor is
   retail's `igMemoryRefMetaField_Destroy`; the kit's `setPool`/`getPool`, `setAlignmentType`,
   `setDefault(igMemoryRef)`, the private `refObjects`/`releaseObjects`, and its slot overrides) is converted;
   its field adder replaces the inherited `_resetMethod` by a new `igEnumMetaField`, which the generator
   writes;
3. `igMetaObject`, `igDataList`/`igObjectList`; igMetaObject, igIGBFile and igObjectDirEntry then also call
   igObject's protected and private construction members directly (the kit makes them friends);
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
- `tools/whole_file_rows.py --unit-va <va> --write` cannot regenerate some caller units' rows (an ambiguous retail
  start such as `0x37a600`, which three duplicate smart-pointer destructors fit, or a unit name with two source
  files), on main as well; their rows stay as they were and still verify.
