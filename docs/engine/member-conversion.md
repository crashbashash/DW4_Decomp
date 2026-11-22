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

A flat struct's C++ view may carry the kit's inlines of its converted class, forwarding to the `Gap::` class, so
code holding a flat pointer already reads in the kit's form and keeps it when its class converts. Their rows are
`class-members.tsv` rows keyed `::<class>`: the generator declares them in the flat struct under `#ifdef
__cplusplus` and defines them after the `Gap::` classes. The flat `igObject` has `ref()`, `release()` and the
static `ref`/`release(igObject *)`, each forwarding to `Gap::Core::igObject`'s; C keeps the word. The views that
stand in for igObject in C++ (`igVirtualObject`, `igObjectDispatchView`, gfx's `igObjectSlotView`) carry the same
static `ref`/`release` forwarders.

**Smart pointers** (include/dw4/core/igSmartPointer.h) are the kit's igCore/igSmartPointer.h in their count
handling: every ref and release is the kit's static `igObject::ref/release`, which the kit calls as
`igObject::release((igObject *)_ptr)`. DW4 calls it through the held class, `T::release(p)` / `T::ref(p)`: a Gap
class inherits the root's statics, a flat struct its C++ view's forwarders, a view its own. So
`igSmartPointer<GapClass>` works (`igMemoryRefMetaField::_memTypeRef` is `igSmartPointer<igMetaField>`, and core's
copy of its destructor is retail's 0x14ec50), the call binds at instantiation, and the pointer reaches the static
uncast. That last point is what retail's codegen needs: MWCC substitutes an inline's argument that has the
parameter's type, and copies one that needs a conversion (an explicit cast, or even `T *` to `const T *`). A copied
argument loses the reload retail shows when a temporary's release re-reads `p` from its stack slot
(igDirectory_ReplaceReference, and the shader processor's temporaries in scenegraph). This is why the flat and
view statics take a non-const pointer, while the Gap root keeps the kit's `const igObject *`. `clear()` releases
directly, and the depth from a
destructor to the count body is the template, then the static, then `release()`. That is the depth retail's
units built without `-inline level=8` inline. The assignments are the kit's `igSmartPointerAssign` written inline
(ref the new object, release the old, store); DW4's pointer adopts the reference a `T *` hands it, and
`kRetainReference` retains it as the kit's `igSmartPointer(T *)` does. reflected.h includes the header right
after `Gap::Core::igObject`, because the views' forwarders read the root's members. DW4's `igRelease` helper is
gone: its callers are the kit's `igObject::release(p)` (or a view's `release`), and `tools/releaseconv.py`
rewrites any that remain. beNDMWLoadIntf2's retail out-of-line release at 0x3e9110 is the kit's
`igObject::release(igObject *)`.

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
   its callers after. The unit's present row settles its partial functions, ambiguous starts (a member whose
   mangled name changed only in a parameter's type or its class template's argument, `platformLoad(igFile *)` once
   igFile is the Gap class, takes its former name's address), static-initializer entry and data names; retail's
   references settle byte-identical functions left with the same starts (empty virtual slots by the vtable words);
   `--drop`/`--at` are needed only for a start neither settles, which the run names. Rows that would not load (two
   rows placing one function) are not written: the run stops naming the function and the rows, and
   unit-objects.json stays as it was.
5. Run `tools/compiler_names.py --write`.
6. Run `tools/check.py --function <va> --cand <source>` for every touched unit. Each must report `MATCH`. Then
   `tools/memberize.py --check` (no C-name declaration left over) and `tools/typed_coverage.py --check`.

### The batch tool

`tools/classconv.py <spec.py> {tables,memberize,splice,decls,all} [<class> ...]` runs steps 1-3 for a batch from a
spec file (Python defining `SPECS`; its docstring lists the keys: `rows`, `typed`, `map`/`extra`/`keep`/`data`,
`gen`, hand `bodies` in the kit's form, `boot` overrides, `lib`, `base`, `add`). It stubs every C function a hand
body or the generator replaces with the member's parameters before `memberize.py --apply`, splices the generator's
boilerplate and the hand bodies over the memberized definitions (a definition's head only, in code: never a call
naming the member, nor a comment or string; an overload's, static or not, by its parameter types), writes a
metafield's igen descriptor creator and `getMetaField`, writes a bootstrap class's three
constructors, copy slot and `__bootstrapDestruct` in the kit's form (renaming their `unit-objects.json` keys),
respells static data in their declared types and drops the C-name declarations `memberize.py --check` reports.
A generator member no C name of the spec maps is the function at its role's retail address (a field adder
symbols.txt names only by its address); a hand body's member that no C function becomes and the class does not
define stops the run, naming it. A spec with `add` adds members to a converted class: the `rows` and `typed`
fields the class lacks join the tables in the spec's order among the ones it has (a row it has is one of the same
declaration, access label and spacing aside, so a repeated row is never added twice), and only its own C names are
memberized. A run that fails leaves `src/`, `include/` and `config/` as it found them. Run `decls` once more after
the rows are regenerated: a vtable's C name goes unused only then. `classconv.array_spec` builds a scalar array
metafield's spec. Tests: `tools/test_classconv.py`.

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
   pair (`igObject_AllocateRawStorage`); and the release idiom, which is now the kit's. The root's reference word
   is the kit's union (`_refAndMemPool`: `_both`, and a struct of `_refCount : 23` then `_memPoolIndex : 9`, the
   little-endian order; the kit header, alchemy-kit_202309 igCore/igObject.h, splits a `_scriptFlag : 1` off a
   22-bit count), protected as in the kit; igObject's own constructors and `getMemoryPool` read it through the
   `igRefCountWord` views. `release()` is `_both--; if (_either._refCount == 0) internalRelease();`, `ref()` is
   `_both++`, and the static `release`/`ref(const igObject *)` test for null (the flat view's take `igObject *`,
   above). MWCC writes the decrement, the reload
   and the `dsll32 9`/`dsrl32 9` test every release site has, and the `addiu 1` increment. The kit's `release()`
   calls a `decrementRefCount()` that holds that body; DW4's is written in `release()` itself, because the units
   built without `-inline level=8` (GameMain, igAdx, the movie units) stop inlining one call short of the flat
   view's `release()` -> `igObject::release()` -> `decrementRefCount()` chain and call an out-of-line copy. The
   same depth limit is why a release inside a `static inline` helper or an inline destructor of those units stays
   open. `tools/releaseconv.py` rewrites the open sites (`p->release()`, and `igObject::release(p)` for one under
   its own null test; the same for `ref`); a site stays open when its pointer is a view without the members (`f4`,
   `refs`, `rc`, `references`, or `+4` through casts), when it is in a macro, or when the unit no longer matches
   with it (a pointer whose address escaped and is reloaded after the decrement, or a register allocation that
   moves: the `<Class>_InitFields` copies of C classes, where declaring the field local first restores retail's
   allocation, as in the core unit's four);
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
   `igSmartPointer<igMetaField>` and `_poolName` an `igStringRef` under C++, so its implicit destructor is
   retail's `igMemoryRefMetaField_Destroy`; the kit's `setPool`/`getPool`, `setAlignmentType`,
   `setDefault(igMemoryRef)`, the private `refObjects`/`releaseObjects`, and its slot overrides) is converted;
   its field adder replaces the inherited `_resetMethod` by a new `igEnumMetaField`, which the generator
   writes. `igStringMetaField` (bootstrap; the kit's inline `set(igObject *, igStringRef)` behind its copy,
   reset and destruct slots: retail keeps the out-of-line copy scenegraph emits at 0x1c8c00, which stays a C
   definition there until its not-yet-decompiled caller is, and core's copy is a `duplicates` row) and the
   arrays `igStringArrayMetaField`, `igMemoryRefArrayMetaField` and `igObjectRefArrayMetaField` (the kit's
   `IG_ARRAY_IMPL`, raw readers looping through the element class's, the ObjectRef array's out-of-line
   `set(obj, index, val)`) are converted. The whole isAlike family is the kit's `igBool` (`bool`): igObject's
   `isAlike*` and `userIsAlike*`, igMetaField's `isAlike*` and every `isAlikeCompare*` slot; a caller tests the
   result directly (`if (!f->isAlikeDeep(…))`), since `== 0` widens it. `igStringRef`'s destructor is written
   compactly: MWCC's bottom-up inliner weighs an inline's size, and retail inlines it two base destructors deep.
   The Math library's metafields `igVec2fMetaField`, `igVec3fMetaField`, `igVec4fMetaField`, `igVec4ucMetaField`,
   `igMatrix44fMetaField` and `igVec4fArrayMetaField` are the first `Gap::Math` classes (`IG_OBJECT_DEFINE`,
   `IG_METAFIELD_SETUP`; their descriptor creators and `getMetaField`s were unnamed `FUN_` functions, their factory
   `CreateInstance` is the generator's `_instantiateFromPool`). `endianSwapMemory` is the kit's
   `IG_ARRAYBASED_IMPL` (`int numElts = getSize() / sizeof(float)`, through igMetaField's kit inline `getSize()`),
   the array's the kit's `IG_ARRAY_IMPL`, and `setDefault` takes the kit's `const igVec3f &` (`const igMatrix44f &`:
   reflected.h declares `igMatrix44f` ahead, since a matrix field stays sixteen floats). The field adders that pass
   a float array dereference it as the vector (`setDefault(*(const igVec3f *)v)`) until their own classes convert,
   and pass the identity temporaries themselves (`setDefault(igMatrix44f(...))`). Retail's out-of-line copy of
   `igMetaField::getClassMeta` that the registrars name is the compiler's (a `duplicates` row in the Math unit).
   `igCompoundMetaField` is converted (`IG_ABSTRACT_OBJECT_DEFINE`, so it registers no vtable probe; the
   protected `k_fieldList`, `_fieldList` an `igSmartPointer<igMetaFieldList>` under C++, the slot-9 override
   `initDefaults` calling the static `arkRegisterCompoundFields`, and its 29 slot overrides, each a loop over
   `_fieldList`'s elements; `computeTypeSize` is the kit's `getSize()`). Its flat subclasses igDependencyMetaField,
   igMemoryDescriptorMetaField, igTrackedElementMetaField, igCharMetricsMetaField and igItemDataBaseField still
   probe their vtables in C, stamping the compound vtable by its C name, and register through
   `igCompoundMetaField::arkRegisterInternal`. `igDataList` is converted (`IG_OBJECT_DEFINE`, the protected
   `k_count`/`k_capacity`/`k_data`, the kit's inline `getCount()` and the slot-21 `getElementSize()`, -1 here). Its
   inline virtual `getMeta` and its `getCount` have out-of-line retail copies in the attrs and base units (the
   units that compiled igDataList's vtable and called `getCount` uninlined), which stay C functions there until
   those units build their lists in C++; DW4's `GetOrCreateMetaObject` is still free. The list services are its
   members in the kit's access (alchemy-kit_202309 igCore/igDataList.h): the public `setCapacity` (`List_Reserve`)
   and `resizeAndSetCount` (`List_Resize`), and the protected `insert`, `append`, `remove(pos, itemSize)`,
   `sortedFind`, `resizeAndSetCount4For1` (`List_AppendWord`), `insert4`, `append4`, `remove4(pos)`, `sortedFind4`
   and `binaryInsert4` (`List_LowerBound`), in retail's order; the kit's other overloads (`find`, `bubbleSort`,
   the ranged `remove`, …) are not in DW4's image and are not declared. The item size is the kit's unsigned
   (`setCapacity`'s `divu` needs it), `_data` the kit's `unsigned char *` under C++, and the compare callback the
   kit's `Gap::igCompareFunction` (`include/dw4/core/igCore.h`) without the kit's later user-data argument.
   Code outside igDataList's subclasses still calls the protected services by their C names, as their
   prototypes in `igDataLists.h` keep them, until it is written through a typed list's inlines;
3. the flat metafield subclasses above, with igMetaFieldList (a kit `igTObjectList<igMetaField>`), so that the
   compound's loops read `_fieldList->get(i)`;
4. `igObjectList` is converted (`IG_OBJECT_DEFINE`, the private `k_data`, igen's field adder that replaces `_data`
   with a clone retyped to igObjectRefMetaField). Its C++ base is the kit's `igTDataList<igObject *>`
   (converted-classes.tsv's third column; the template is `Gap::Core::igTDataList` in `include/dw4/core/igTDataList.h`,
   which reflected.h reads after igDataList): retail's igDirectory constructor stamps igDataList's, the template
   instance's and igObjectList's vtables in turn, and the instance's vtable overrides slot 16 `trimCapacity` (the
   kit's `clean`, through `setCapacityToCount`) and slot 21 `getElementSize` (4). igObjectList adds the inline
   `userPreWrite` (calling `trimCapacity`), `getMeta` and the new slot 22 `getElementMeta` (igObject's `_Meta`).
   Retail kept those inline copies and igObjectList's vtable from attrs; core's copies are `duplicates` rows
   (its `userPreWrite` copy also fits igStringRefList's identical body, so the core row is written with `--drop`),
   and attrs' C definitions stay until attrs builds its lists in C++. The flat view template `igTDataList<T>`
   stays for unconverted code; inside `Gap::Core` it is spelled `::igTDataList`. igObjectList's services are its
   public members with the kit's names: `append` (`ObjectList_AppendRetained`, which grows through
   `resizeAndSetCount4For1`), `concatenate`, `setAll`, `clearAll`, `setCount`, `removeByValue`, `removeAllByValue` (an `int`: scenegraph's caller tests the count signed, where
   the kit's header has `igUnsignedInt`),
   `appendUnique` (through the kit's inline `find`, the template's `find(const T &, int)`), the field-keyed
   `search(igStringMetaField *, const char *)` and `search(igObjectRefMetaField *, const igObject *)`,
   `sortedSearch`, `fastBinaryFind` (`igProperty_FindInsertionIndex`) and `bubbleSort(igRefMetaField *)`; the kit's
   `igConstRawRef` values are `const void *`, whose comparisons are retail's unsigned ones. Their releases are still
   written open (the kit's `igObject::release()` waits for the root's `_refCount` bitfield, below), and attrs still
   calls `append`, `appendUnique` and `setCount` by their C names until attrs converts. The typed data lists
   `igIntList`, `igBoolList`, `igCharList`, `igShortList`, `igUnsignedShortList`, `igUnsignedCharList`, `igFloatList`
   and `igPointerList` are converted over the kit template `igTDataList<T>` (alchemy-kit_202309
   igCore/igCoreLists.h: `IG_OBJECT_DEFINE`, the private `k_data`, igen's boilerplate), with `igIntListNoClean` and
   `igCharListNoClean` overriding `trimCapacity` empty (the kit's `clean`). Each instance's `trimCapacity` and
   `getElementSize` are the compiler's copies, at retail's places at the end of the core unit; the template
   instance's vtable the compiler also writes is referenced by nothing and is not in retail. Their factories
   (`Create`) stay free, as the metafields' do, since callers pass allocator words. One gfx vertex-stream binder still
   reads the char/short list metas by their C names: through the inline `getClassMeta` MWCC keeps the meta in one
   saved register fewer than retail. `igLongList` (`igTDataList<long long>`, the kit's igLong; its template copies
   are gfx's `igTDataList` of an 8-byte element), `igUnsignedIntList`, `igUnsignedIntListNoClean` (the empty
   `trimCapacity`) and `igDoubleList` are converted the same way. igUnsignedIntList's and igDoubleList's vtables and
   inline copies are scenegraph's in retail: their C copies (`getMeta` reading `getClassMeta()`, `trimCapacity`,
   `getElementSize`) stay there, and core's compiled copies are duplicates, until scenegraph builds those lists in
   C++. `igDependencyList` is `igTDataList<igDependency>` (the kit's two-pointer pair, include/dw4/core/igCore.h),
   its `trimCapacity`/`getElementSize` the compiler's copies at retail's places in core's inline tail. The
   `igTObjectList<T>` lists follow. Then
   `igMetaObject`: converting it makes `igMetaObject` in every Gap scope the class, so every converted class's
   `_Meta`, the registrar's `igMetaObject_RegisterClass(…, &_Meta, …)` and the ~2,250 field-adder calls
   (`igMetaObject_GetFieldAt` is the kit's `getIndexedMetaField`, `CreateFields` `instantiateAndAppendFields`,
   `NameFields` `setMetaFieldBasicPropertiesAndValidateAll`, `GetFieldCount` `getMetaFieldCount`) change type at
   once, across ~1,100 files; the generator's templates change with it, and `RegisterClass`/`RunStaticInit` are the
   kit's free `igArkRegister` overloads. igMetaObject, igIGBFile and igObjectDirEntry then also call igObject's
   protected and private construction members directly (the kit makes them friends). `igMetaEnum` is converted
   (alchemy-kit_202309 igCore/igMetaEnum.h: `_name` the kit's igStringRef, `_names`/`_values` smart pointers, the
   private field handles, `getEnumValue(const char *, igEnum &)`, `getEnumName`, `getEnumCount`,
   `getIndexedEnumName`, `getIndexedEnumValue` and the static `createMetaEnum`; `igEnum` is the kit's `int`,
   include/dw4/core/igCore.h). Its eight callers pass the out value by reference, as the kit's signature asks
   (`(int &)fightCommand` for an unsigned one), with no change in code. The name tables stay `const char *`
   arrays, so `createMetaEnum` takes `const char **` where the kit has `igChar *[]`; the holders that are still
   flat `igMetaEnum *` take the result through a cast (`(igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum(…)`,
   which memberize writes). DW4's mask and value-name formatters (`igMetaEnum_GetNamesByMask`,
   `igMetaEnum_GetValueName`) and the empty enum's getter stay free. `igNamedObject` (`_name` the kit's
   igStringRef, `setName`; attrs keeps retail's out-of-line `getMeta` copy at 0x142b60 as a C function reading
   `getClassMeta()`, and gfx/attrs the out-of-line destructors `igNamedObject_Destroy`/`igDirEntry_Destroy` the
   flat subclasses' probes call) and the directory entries are converted (alchemy-kit_202309 igCore/igDirEntry.h,
   igObjectDirEntry.h, igMemoryDirEntry.h, igExternalDirEntry.h, igExternalIndexedEntry.h,
   igExternalInfoEntry.h). DW4's igDirEntry has an older slot set than the kit's: slots 21-40 are `setRef`,
   `refRef`, `releaseRef`, `share`, `refEntry`, `releaseEntry`, `setMemoryPoolHandle`, `getMemoryPoolHandle`,
   `readSetup`, `readPreRead`, `readReadVersion3`, `readRead`, `readMemorySpecial`, `readFinishConstruction`,
   `readPostRead`, `writeMakeProxy`, `writeComputeBufferSize`, `writeWrite`, `writeMemorySpecial` and
   `refNeedsEntryForPostFileReadCleanup` (named from which subclasses override which slot), with no
   `readFastRead`, `getSize`, `appendToCloneInfo`, `cleanupOnFailure` or `dump`; the read slots return void
   and `refNeedsEntryForPostFileReadCleanup` returns `int`, since igMemoryDirEntry's tail-calls `isOfType`,
   DW4's `int`. igExternalDirEntry adds `resolve` and `load` (slots 41-42) taking the kit's
   `igResolveFunction` (include/dw4/core/igCore.h). The string and meta-object reference fields are the kit's
   igStringRef and smart pointers, so the generator's `retrieveVTablePointer` destroys them as retail's probes
   do; a string passed on is its `.p` to a `const char *` parameter (`igDirectory_SetName`,
   `igDirectory_FindInfoByName` take the kit's igString), since an `(int)` cast of it schedules the load
   early. The directory code still reaches entries through `igDirEntryView`. The abstract `igTimer` and `igMedia`
   (alchemy-kit_202309 igCore/igTimer.h, igMedia.h) are converted too: they have no field of their own and so
   no reflected struct, and a `converted-classes.tsv` row is all the generator needs to write their
   registration (gen_type_headers lays out a field-less converted class from reflection.json). Their slots
   21-34 and 21-30 are the kit's pure virtuals in retail's order (igPsx2LongTimer's and igPsx2Media's vtables
   fill them); `arkRegisterInitialize` sets the abstract proxy (`_Meta->_abstractProxy`), igMedia's also adds
   the exit callback `_classDestructor`, and igMedia's `userRegister`/`userUnregister`, `registerMedia` and
   `setDefaultMedia` are members. `findMedia` (`igMediaFile_FindDeviceForPath`), `gDefaultMedia` and `gRegisteredMedia` (an `igSmartPointer<igMediaList>`)
   are members; `igMediaList` is converted over `igTObjectList<igMedia>`. The bootstrap lists the object system keeps its metaobjects and metafields
   in, `__internalNonRefCountedObjectList` and `__internalObjectList`, are converted (alchemy-kit_202309
   igCore/igInternalObjectList.h: `IG_BOOTSTRAP_OBJECT_DEFINE`, `_data` the kit's `igObject **` under C++, the
   slot-16 override `trimCapacity` (the kit's `clean`), `setCount`, `setCapacity`, `append`, `insert`,
   `remove(int)`, `set`, `search(igStringMetaField *, const char *)`, `find` and the kit's inlines, and
   `__internalObjectList`'s reference-counting `setCount`, `append`, `insert` and `set`; DW4's image has no
   `remove(igObject *)`). Their constructors and `__bootstrapDestruct` replace the retail C names
   (`ObjectPointerList_*`, `InternalObjectList_*`, classconv's `boot_names`), and `_instantiateFromPool`
   constructs with `new (0, pool) T(true)` through igObject's kit `operator new(size_t, size_t, igMemoryPool *)`
   pair (`igObject_AllocateRawStorage`, `igObject_AllocateRawStorageDefault`, members of the root, which
   `memberize.py` converts like any static member; the clones are `new (0) T(*this)`):
   one null test, as retail's. The metafield `<Class>_Create` factories are still free, so they call
   `igObject::operator new(size, 0, pool)`. igen's override of an inherited field finds its index with
   `((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField)`, and a metafield's
   descriptor registers with `getMetaFieldTypes()->append(metaField)`. Of the 154 classes the core
   unit registers, 71 are converted (igContext with them); the other kit-declared ones (the remaining typed lists, the memory pools,
   files and media, igRegistry, the threads and timers, …) follow, and those without a kit
   header (the `igPsx2*` platform classes, igDependencyMetaField and igMemoryDescriptorMetaField) take their
   form from retail alone. `igDirectory` and `igDirectoryList` (alchemy-kit_202309 igCore/igDirectory.h) derive
   from the kit's `igTObjectList<igDirEntry>`/`igTObjectList<igDirectory>`: the template instance's vtable is
   retail's 0x532590, which igIGBFile's out-of-line copy of the directory constructor (`igDirectory_Construct`,
   still C while igIGBFile is flat, as is the destructor copy `igDirectory_Destroy`) stamps between igObjectList's
   and igDirectory's. `_name` is the kit's igStringRef (so `setDirectoryName` is the kit's `_name = newName`), the
   list, directory, pointer-list, short-list-list and semaphore fields smart pointers, and the members are the
   kit's names: `addObject`, `addObjectRef`, `addMemoryRef`, `addRawRef`, `findEntryByEntryName`,
   `findRefByEntryName`, `findObjectRefByEntryName`, `binaryFind`, `getRef`, `setRef`, `get` (with the kit's
   inline `getNonShared`), `makeAllConcrete`, `resolveExternal` (slot 23), `appendInfo`, `removeInfo` ×2,
   `getInfo` ×2, `getInfoCount`, `loadRef`, `loadRelease`, `createLoadingSemaphore`, `attemptResolve`, `contains`,
   `fastFindRefEntry`, `releaseDefaults` and `userRegister`. igInfo, igInfoList, igSemaphore and igResource are
   still flat, so their uses go through `igInfoView`, `igSemaphoreView` and flat list casts; the out-of-line
   smart-pointer destructors of the semaphore, directory list and short-list list and the two template
   `getElementMeta` copies are now the compiler's, their C names bound by the compiler-name map.
   `igDirectory_ReplaceReference` (the kit's `replaceObjectInstance`, whose by-value smart pointers DW4 passes by
   reference) and the traversal callback `igDirectory_AddObjectCallback` stay free over the Gap class;
   `igDirectoryView` remains only as igIGBFileView's base and in the external-info helpers. `igRegistry`,
   `igRegistryValue` and `igRegistryValueList` (alchemy-kit_202309 igCore/igRegistry.h) are converted: DW4's
   registry is older than the kit's, with no section list (the value table is the `igTObjectList<igRegistryValue>`,
   the extra sections an `igStringObjList`, both smart pointers, as are the file and the value's two strings,
   whose type is the kit's `igStringObjRef`, include/dw4/core/igStringObj.h). The members are the kit's that the
   image has: `load`, `merge`, `reset`, `findSection`, `getSectionName`, `getKeyCount`, `getKeyName`, the six
   `getValue` overloads (int, igBool, igStringObjRef, igStringRef, igStringRefList, float), `getEnumValue`,
   `getFlagsValue`, `getRawValue`, `getRawValueCount`, the four `setValue` overloads, the protected `parseRegistry`,
   `readLine`, `findValue` (returning the raw value: retail returns no smart pointer) and `preProcessLine`, and
   slot 9 `initDefaults` (the kit's `userInstantiate`). Retail shows the kit's igBool parameters (`createValue`,
   `replaceDuplicates`, the bool value) as `unsigned char`: a `bool` or `unsigned char` parameter is not masked
   where it is tested (`if (createValue)`), but is where it is compared (`!= 0`) or widened to an `int`
   parameter, and every caller holds the flag in an `unsigned char`, which a `bool` parameter would normalise
   (`igStringObj_SetBool` takes its flags the same way). A caller tests the `bool` result directly (`if
   (r->getValue(...))`), since `!= 0` masks it. The enum parsers stay free, as do the data-pump library's
   tail-jump readers `igGetRegistryValue_*`, whose flags are the members' types;
   Files and folders (alchemy-kit_202309 igCore/igFile.h, igMediaFile.h, igMemoryFile.h, igFolder.h) are converted:
   `igFile` (abstract; DW4's slots 21-39 are `open` ... `ftell`, `readPastChar` and `generateFilename`, with no
   `getSize`; `_openMode`/`_readMode` are the kit's enum-typed fields, whose `enum` rows gen_type_headers.py writes
   ahead of the fields; the statics `isAbsolutePath`, `containsRelativePath`, `setSearchPath`,
   `setSearchPathFromRegistry`, `getSearchPath`, `getNextPath`; its implicit destructor is retail's `igFile_Destroy`,
   still named by the flat `igPsx2File`/`igAdxFile` probes), `igMediaFile` (`_media` an `igSmartPointer<igMedia>`,
   `fit`), `igMemoryFile` (statics `userRegister`, `userUnregister`, `setMemoryFile`, `getMemoryFile`; its entry list
   `_entryList` is a `igMemoryFileEntryList *`), `igMemoryFileEntry` (`setBuffer`, `setSize` and the getters, the
   kit's) and `igMemoryFileEntryList` (over `igTObjectList<igMemoryFileEntry>`), `igPsx2File` (no kit header: slots 9
   `initDefaults`, 21-37 and 39 `generateFilename`; statics `userRegister` for the default prefix, `makeCompletePath`,
   `joinPrefix`, `defaultPrefix`; the private `growBuffer`; spec scratch/CoreFiles2/specs/psx2.py), `igPsx2Folder`
   (`getFiles`, `getSubFolders`, `getFilesAndSubFolders`, `trimPath`) and `igFolder` (`getPathToFile`,
   `setFolderName`/`getFolderName`, `appendRelativePath` = `igFolder_SetFolderName`; the three inline
   `get*Folders` slots return a retained null list, whose out-of-line copies in scenegraph and GameMain stay C and
   are duplicates here). The file views are gone from core, Lua, the game and the movie codec: callers use igFile's
   members (`fopen`, `fclose`, `fread`, `fgetc`, `fprintf`, `generateFilename`); the report files are
   `Gap::Core::igFile *`. Still view-based: `igMediaFileView`/`igMemoryFileView`, igIGBFile's `igFileView`,
   scenegraph's `IniFileObject`/`IniPathResolver` (the ini loader) and insight's `NamedObject` folder, and GameMain's
   `Blk::folder` (typing it `Gap::Core::igFolder` moves `Blk::Blk` from 448 to 372 bytes: the intern pool is no
   longer inlined there). Not converted yet: `igIGBFile` (about 2,400 lines; needs `igDirectory_Construct`/`_Destroy`
   copies stamping `igTObjectList<igDirEntry>`'s vtable, its `igFileView`/`igIGBFileView` uses retired, and the
   protected igObject construction members reached as the kit's friend).
5. attrs, then gfx, then scenegraph, then gui/insight/viewer. Attrs so far: `Gap::Attrs::igAttr` (abstract;
   DW4's slots 21-29 read off retail's concrete vtables: `apply(igContext *)`, `apply(igVisualContext *)`,
   `setUnitID`, `synchronizeDefault` ×2, `reset`, `setup` ×2, `getUnitCount`, all kit inlines but `setUnitID`; no
   `compile`/`getMaxCompiledSize`; the kit's `userResetFields`/`postFileRead` are igObject's `resetFields(int)` and
   `userPostLoad`), `igVisualAttribute` (DW4's abstract layer; overrides `setup(igVisualContext *)` as
   `apply(vc)`), and the eleven boolean state attrs (`igAlphaStateAttr`, `igBlendStateAttr`,
   `igClippingStateAttr`, `igDepthStateAttr`, `igDepthWriteStateAttr`, `igFogStateAttr`, `igLightingStateAttr`,
   `igMatrixOptStateAttr`, `igStencilStateAttr`, `igVertexBlendStateAttr`, `igNormalizeNormalsStateAttr`: `_enabled`
   typed `bool`, `setState` out of line as slot 30 since retail keeps it beside `apply`, `synchronizeDefault`
   through `igVisualContextDispatchView`'s state getters, named from igPsx2VisualContext's overrides). The attrs
   unit compiles each converted attr's vtable (a `.vtables` data row) and the inline copies it names (getMeta, igAttr's
   empty slots), placed by name at their retail addresses, so conversion order inside the unit is free; igAttr's and
   igVisualAttribute's vtables (absent from retail) and the inline copies only they name are `stripped`. Also
   converted: `igAlphaFunctionAttr`, `igPolygonModeAttr`, `igShadeModelAttr`, `igPixelPipelineModeAttr`,
   `igMultiPassStateAttr`, `igCullFaceAttr`, `igStencilFunctionAttr`, `igColorMaskAttr`, `igViewportAttr`,
   `igFogAttr`, `igClearAttr`, `igColorAttr`, `igTimeAttr`, `igMaterialAttr`, `igProjectionMatrixAttr`. Their
   accessors are the kit's: enum-typed (`include/dw4/gfx/GfxMetaEnums.h` carries the kit's igGfx enums, which
   reflected.h reads) over the reflected `int` storage, a cast to the enum is what retail's codegen shows; a
   virtual setter is out of line where retail keeps it beside `apply` and the kit's inline where it sits in the
   unit's inline tail; matrix fields are the kit's `igMatrix44f` (typed-fields.tsv) where retail's vtable probe
   constructs one; `synchronizeDefault` reads `igVisualContextDispatchView`'s getters (slots 51-250, named after
   igPsx2VisualContext's overrides with the kit's igGfx/igVisualContext.h names and enum types), in retail's call
   order. Classes tools/gen_odl_source.py cannot write (`--list` says CANNOT) get igen's registration by hand
   (`gen` empty in the spec). The unit-ID family is converted too (`igTextureStateAttr`,
   `igTextureMatrixStateAttr`, `igTextureCoordSourceAttr`, `igTextureUnloadAttr`, `igTexGenMatrixAttr`,
   `igTextureMatrixAttr`, `igVertexBlendMatrixAttr`, `igBlendFunctionAttr`, `igTextureFunctionAttr`): the static
   `synchronizeCachedUnitID` invariance callback (`setCachedUnitID` from the unit field), `setUnitID`, `userPostLoad`
   (the kit's `postFileRead`) and `getUnitCount` through `igCapabilityManagerDispatchView`'s slot 21 `getCapability`
   (the kit's `IG_GFX_CAPABILITY`). `igModelViewMatrixAttr` (with `userRegister`, the registration's
   `arkRegisterUser` callback, `userUnregister` and `getIdentityAttr`), `igGeometryMaskAttr` (its mask the kit's
   `igVertexComponentFilter`, include/dw4/gfx/igVertexComponentFilter.h), `igBlendMatricesAttr`,
   `igBlendMatrixPaletteAttr` (igPsx2VisualContext_SetBlendingMatrices takes the kit's unsigned count and
   `igMatrix44f *`, which retail's scheduling needs), `igDisplayListAttr` (an igAttr) and `igRenderListAttr` are
   converted as well. The two extension attrs keep the kit's static `_extension` and call it through
   `igBlendEquationExtDispatchView` and `igMultiTextureExtDispatchView`. A field naming another Gap class is an
   `igSmartPointer<GapClass>` (smart pointers, above).
   igViewerRenderer calls the converted colour, alpha-function, shade, polygon and lighting-state attrs' members
   (`_lightingState` is the kit's igBool), and their dispatch views are gone; the alpha-test and cull-face calls keep
   their views, since typing igViewerParameters' `_alphaTest`/`_backFaceCulling` bool moves the kit's igBool
   normalisation into `igViewerRenderer_ApplyOptions`, whose ViewerOptions, registry and command-line readers are
   unsigned char. The game's matrix attrs (beCri, beModelCtrl, beModelCtrlSC, beSeCtl) are
   `Gap::Attrs::igModelViewMatrixAttr` and call `setMatrix`. The default managers (`igAttrDefaultManager`,
   `igGenericAttrDefaultManager`, `igVisualContextAttrDefaultManager`) and `igAttrPool` are converted, the kit's
   igAttrRef the Gap `igSmartPointer<igAttr>` (igAttrPool's list fields stay flat smart pointers for now: its code
   reads them through flat list casts); `igAttrList`, `igAttrListList`, `igModelViewMatrixAttrList` and
   `igBlendMatrixPaletteAttrList` derive from the kit's `igTObjectList<T>` (include/dw4/core/igTObjectList.h, whose
   `getElementMeta` is `T::getClassMeta()`), so attrs compiles igObjectList's vtable and inline copies.
   `igLightAttr` (`_vc` an `igSmartPointer<igVisualContext>`, flat until gfx converts; the kit's igBool `_changed`
   and `_cacheable`; `lightChanged` the invariance callback; `reset` through `igVisualContextDispatchView`'s
   `deleteLight`, slot 76) and `igLightStateAttr` (`_light` an `igSmartPointer<igLightAttr>`), with `igLightList` and
   `igLightStateAttrList` over `igTObjectList<T>`, are converted. So is the texture group (`igTextureAttr`,
   `igTextureCubeAttr`, `igTextureBindAttr`, `igCopyRenderDestinationAttr`, `igRenderDestinationAttr`,
   `igSetRenderDestinationAttr`, `igTextureList`, `igImageMipMapList`; spec scratch/Attrs5/specs/texture.py): the
   kit's `set(index, value)` on `igTDataList`/`igObjectList`/`igTObjectList`, slots 35 `getCapability` and 129
   `deleteTexture` of the dispatch view, the kit's `IG_GFX_TEXTURE_SOURCE` and `IG_GFX_RENDERDESTINATION_TYPE`, a
   typed reference array (`igTextureCubeAttr::_cubeImage[6]`) in scripts/gen_type_headers.py, the decompiled
   `igSetRenderDestinationAttr::apply` (0x140060, whose PS2 setters take a trailing 0), `igImageMipMapList` over
   `igTObjectList<igImage>` with the element meta specialised for the flat igImage, and the compiler's smart-pointer
   destructors placed at 0x130140, 0x132130, 0x1321b0 and 0x132390 (`--at`). igMovieManager holds its texture list
   as `igSmartPointer<Gap::Attrs::igTextureList>` and appends through the typed list's `append(igTextureAttr *)`;
   beTextureCtrl_UpdateRam indexes the attribute list's data (`((int *)list->_data)[i]`) where it kept a byte
   offset, which keeps retail's register allocation once it reads `igTextureBindAttr::getClassMeta()` (the inline's
   temporary otherwise takes the offset's register). What is left in attrs, and why:
   - the geometry group: `igGeometryAttr` (abstract; typed vertex/index/primLength/dPds/dPdt smart pointers; no
     virtual declared yet, though retail gives it its own vtable, 0x523970, with pure slots and its own
     `synchronizeDefault` 0x13cf70, `reset` 0x13cfc0, the four-argument `intersectRay` 0x13cf80, `getPrimitiveLength`
     0x13d030, a `getMeta` copy and an out-of-line destructor), `igGeometryAttrList` (over
     `igTObjectList<igGeometryAttr>`) and `igGeometrySetAttr` (slots `releaseDefaults`, `apply`, empty
     `synchronizeDefault`, `reset`, `setup`, `setVisualContext`, and the protected `createRenderList`, 0x13e6e0;
     specs scratch/Gfx4/specs/geom.py, geomlist.py, geomset.py) are converted. `igGeometryAttr1_5` stays flat: its
     slots 30-41 (configureVertexArray, transform, computeBound, the seven-argument intersectRay, setTangents,
     setBinormals, configurePrimitive, setPrimitiveLength, the inline getPrimitiveLength, getNumVerts, the inline
     getPrimLengthArray) still read igVertexArray / igIndexArray through stand-in views and one helper not yet
     decompiled (0x13dbb0, which keeps its C name);
   - `igParticleAttr` (its array is a Gap::Bec class) and `igVertexBlendMatrixListAttr` (whose probe stamps
     igVisualAttribute's vtable from its matrix members' destructor chain) are not started;
   - igAttrPool's list fields (`_metaList`, `_nonSharableMetaList`, `_attributeList`) stay flat smart pointers: its
     code reads them through flat list casts and `igMetaObjectList` is core's.
   Core's `igNonRefCountedObjectList` is converted (`IG_OBJECT_DEFINE` over the kit's `igTDataList<igObject *>`, the
   private `k_data`, the inline `userPreWrite` and `getElementMeta`), and attrs' `igNonRefCountedAttrList` derives
   from the kit's `igTNonRefCountedObjectList<T>` (include/dw4/core/igTNonRefCountedObjectList.h): attrs compiles
   the list's vtable, its inline copies and the copy of `getClassMeta` at 0x13aeb0 that the subclasses in core,
   gfx, gui, datapump and scenegraph register through, so their C copies are gone.
   The specs stay in the agents' scratch (`scratch/Attrs2/specs/visual.py`, `visual2.py`;
   `scratch/Attrs3/specs/unit.py`, `simple.py`, `ext.py`; `scratch/Attrs4/specs/mgr.py`;
   `scratch/Attrs5/specs/light.py`, `texture.py`; `scratch/CoreWave9/specs/`; `scratch/Gfx1/specs/context.py`).
   memberize casts a pool passed as `int` to a factory taking `igMemoryPoolView *` (or drops the `int` cast).
   Core's `igContext` is converted (alchemy-kit_202309 igCore/igContext.h: `IG_ABSTRACT_OBJECT_DEFINE`, the protected
   handles, `generateExtList`, `getExtMeta`, `findExtInstance`, DW4's slots 21-25 `makeCurrent`, `isCurrent`,
   `getExtList`, `getExt` and the inline `detectDriverDatabaseProperties`; the kit's `synchronizeContextExt` and
   `userRelease` are not in DW4's vtable). Its extension fields stay reference words, and its inline slot 25's
   copy (gfx, 0x180c10) stays a C definition until gfx builds the vtable in C++: retail's igContext vtable
   (0x530a10) and igVisualContext vtable (0x525e50) are gfx's data, and DW4's `igContextExt` registers under
   igContext (an ext's probe stamps 0x530a10). Gfx then converts `igVisualContext` (alchemy-kit_202309
   igGfx/igVisualContext.h) and `igPsx2VisualContext`. What retail shows: igVisualContext has its own vtable,
   pure slots written 0, with its own definitions in slots 1 (`constructFields`), 7/8 (userConstruct/Destruct),
   20, 21-22, 26-29, 31-34, 45 (an inline copy in attrs, 0x13ff40), 70-71, 141-145, 189 (an inline copy in attrs,
   0x140050), 195-196, 211-214 and 258-271 (the custom-state slots at 0x155340-0x1562d0, unnamed, and 0x165e50);
   its constructor (0x1510e0) and destructor (0x150af0) are out of line, so its typed fields (the eight memory
   pools and the timer as smart pointers, the two `igMatrix44f`, the sixteen `igVertexArray2` references built with
   `__construct_array`, the custom state lists) must reproduce them; igPsx2VisualContext overrides about 220 slots
   (273 C functions), whose C heads take stand-in view receivers and need rewriting to the member's parameters
   before memberize accepts them, and four of whose slots (0x170ed0 `setLightDirection`, `setLightAttenuation`,
   `setTextureSourceLevel`, 0x16de00) are not decompiled. The dispatch view's named slots (the state getters 51-250,
   `deleteRenderDestination` 45, `deleteLight` 76, `deleteRenderList` 191, `getCapability` 35, `deleteTexture` 129)
   then become `vc->name(...)`, the attrs' `igSmartPointer<igVisualContext>` fields hold the Gap class, and the
   view retires once no caller is left. The gfx classes' registration is igen's: gfx's latch at 0x149bc0 is
   `GfxLibrary_MarkRegistered` (it tests and sets `g_GfxLibrary_registered` and registers the eight extensions, as
   core's latch registers its threads), so tools/gen_odl_source.py finds the gfx classes (`--library Gfx`).
   Converted so far (specs in scratch/Gfx2/specs/index.py, vertex.py, clut.py): `igIndexArray` and
   `igPsx2IndexArray` (alchemy-kit_202309 igGfx/igIndexArray.h; retail's vtable 0x526760 holds every slot 21-34
   and the PS2 class overrides only `getMeta`: `configure`/`reconfigure` with the kit's four parameters,
   `getEditableIndices16/32`, two `commitIndexEdits`, `setIndex16/32`, `setIndex`, `getIndex16/32`, `getIndex`,
   the inline `reset`, whose copy is attrs' 0x13d020, and `cache`; no 8-bit pair; `setIndex`/`getIndex` narrow
   the index they pass to the 16-bit pair, whose own parameter is the kit's unsigned int; `_memPool` a smart
   pointer, so the gfx unit compiles both vtables), the abstract `igVertexArray` (igGfx/igVertexArray.h: DW4's
   pure slots 21-58 in the kit's order, read off igPsx2VertexArray1_1's vtable, with the inline `setUsageFlags`
   as slot 24, whose copy is attrs' 0x13f800; DW4's component lock `igVertexArrayLock`, the kit's
   igComponentEditInfo, is declared ahead in reflected.h), and
   `igClut`/`igPsx2Clut` (igGfx/igClut.h: slots 21-23 `load(fileName)`, `load(fmt, numEntries, clutData)`,
   `loadBuffer`; `releaseDefaults` frees the table; DW4's `copy` returns nothing and `scaleAlpha`/`unScaleAlpha`
   return int, which their callers use unmasked; `loadAct` still reads through the igFile view). The vertex
   format word is the kit's `igVertexFormat` class (include/dw4/gfx/igVertexFormat.h, one of reflected.h's kit
   headers): igVertexComponentFilter holds one, and the units that build formats (the particle array, the movie
   manager) use its setters; its out-of-line `operator&` is retail's 0x164e90, still bound as an external.
   `igVertexArray1_1` (igGfx/igVertexArray1_1.h; spec scratch/Gfx3/specs/vertex11.py) has its own retail vtable
   (0x526480) and out-of-line destructor (0x1524c0, the compiler's now): slot 11 is the kit's userResetFields
   (`resetFields(int)`), slot 18 its makeConcrete (`userMakeConcrete`, folding the pre-1.1 per-weight streams
   into `_blendWeights`/`_blendIndices`), `getVertexFormat` is out of line and read through the vtable,
   `userRegister` aligns the weight storage, and `using igVertexArray::configure` keeps the format overload
   visible beside its own flags overload. `_vdata` is a table of twenty stream pointers (0 positions, 1 normals,
   2 colours, 3-10 the pre-1.1 weights and indices, 11-14 texture coordinates, 15-16 point-sprite sizes, 17
   binormals, 18 tangents, 19 sprite angles). `igPsx2VertexArray1_1` (no kit header; its names follow the kit's
   slots, with `allocateBlendedVertexLists`/`freeBlendedVertexLists` for the skinning lists) holds
   `_pBlendedVertsList`/`_pBlendedNormsList` as `igSmartPointer<igPointerList>` and the flat `igPsx2LongList`
   wait list. `igVertexArray2` and `igPsx2VertexArray2` (igGfx/igVertexArray2.h; spec scratch/Gfx4/specs/vertex2.py) are converted: slots 21 `configure`
   (the base one builds an internal igVertexArray through an `igSmartPointer<igVertexArray2Helper>` and copies each stream; decompiled, 0x15f7d0), 22 `reset` (empty in the base, whose copy is attrs'
   0x13e660; the PS2 class resets its vertex stream), 23 `getCount`; `findVertexData`, `buildVertexDataList`, `isVertexDataSupported`;
   `igVertexStreamDispatchView` (slots 24/25) and `igVisualContextDispatchView::setVertexArray` (slot 259) replace the old stand-ins.
   `igVertexArrayLock` keeps DW4's name and layout: the kit's igComponentEditInfo orders its fields differently and has no
   `_componentIndex`. `igImage`, `igMemoryImage` and `igPsx2Image` are converted (spec scratch/GfxImage/specs/image.py): igImage's 23 slots 23-45 in retail's
   order (copy, copySubImage, scale, reduce, setData, setWidth, setHeight, setPixelFormat, allocateImageMemory,
   setComponentOrder, load, swapComponentOrder, setNumComponents, setPixel, the five-argument load, reduceAux, the
   platformLoad/platformSave/platformConvert hooks, correctBytesPerRow, oldLoad and the pure toggleComponentOrder; the
   hook and slot-45 names are DW4's own); the hooks and `convert` return `unsigned char` as retail's callers mask them;
   `_pClut` is `igSmartPointer<igClut>`, `_pNameString` an `igStringRef`; `setName` takes the string as the kit does;
   igImageMipMapList's element meta is now the Gap class's. reduceAux (0x157ad0) and the tile copy at 0x15a750 have no
   source yet. `igFileImage` (abstract, no members), `igFileImagePng` (typed `_file` `igSmartPointer<igFile>`;
   overrides `releaseDefaults`, `copy`, `load(const char *)` and `toggleComponentOrder`; retail's `copy` calls
   `src->getMeta()` after igImage's, as igPsx2Image's does: no kit inline or assert explains the call, which is
   spelled as the bare virtual call; the PNG reader at 0x167860 is not decompiled, its callees `cleanup`,
   `estimatePixelFormat` and `setReadTransforms` are members over libpng's types, dw4/gfx/png.h, which reflected.h
   reads) and `igExternalImageEntry` (kit igGfx/igExternalImageEntry.h: `load`, `loadWork`, `initDefaults`) are
   converted. The image readers (`load`, `oldLoad`, `newLoad`, `platformLoad`, `platformSave`) call igFile's members
   (`fopen`, `fread`, `fwrite`, `fclose`). The compiler emits the out-of-line destructors, igFileImage's `getMeta`
   (0x180ff0), the igFile smart pointer destructor (0x150180) and the parent accessor copy at 0x14f760. Image
   views left: `igImageConvertRows` (one stand-in for igImageConvert's slots 23-34 until igImageConvert and
   igPsx2ImageConvert convert) and the TGA loader's `O1`/`LoaderRef` (until igTgaLoader converts).
   `igVertexStream`/`igPsx2VertexStream` are converted (enum `_accessMode` of the kit's
   `IG_VERTEX_ACCESS_MODE`, four values, with the inline `getAccessMode()`, which the stream's flat callers read; igPsx2VertexStream's
   `configure`, 0x17f720, links from retail). `igVertexArray2Helper` is converted (DW4's older virtual form of
   igGfx/igVertexArray2Helper.h: slots 21-59 in retail's order, vtable 0x5262a0, the inline `reset` at 0x180e40, the
   statics `getWeightCount`/`getIndexCount`; `compressVertexData`, 0x163810, is declared and links from retail).
   Still flat: igTgaLoader, igPrimLengthArray (slots 21 configure, 22 getEditablePrimLength, 23 commitPrimLengthEdits,
   24 setPrimLength, 25 getPrimLength) and igGeometryAttr1_5;
6. the game's `be*` classes last.

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
  where the member takes one (`igObject(const igObject &)`) is refused and written by hand; a caller passing a
  pointer where the member takes a reference dereferences it (`setDefault(*(const igVec3f *)v)`), passes the
  temporary whose array or address it passed (`igVec4f(…).vec` becomes `igVec4f(…)`, `&igStringRef(…)`
  `igStringRef(…)`), or the value whose address it passed (`(igStringObj **)&value` for an `igStringObjRef &` is
  `value`). An integer passed for an enum parameter is cast to it (`(IG_GFX_DRAW)primitive`), and a call takes
  the member's argument order where the C prototype's differs (igRegistry's float `getValue`), mapped by type and
  name, refused where they leave it open. A member's compiler name spells a nested enum by its owner
  (`Q43Gap4Core6igFile8OpenMode`) and a typedef'd function pointer as its type (`PFii_v`); a key written while a
  parameter's class was flat (`…FP6igFile`) is renamed once the class converts (`memberize.py --rekey`), and so is
  a template instance a unit's object now spells with the class's Gap scope
  (`__dt__42igSmartPointer<Q33Gap3Gfx14igVertexStream>Fv` for `__dt__32igSmartPointer<14igVertexStream>Fv`).
- `tools/classconv.py` stubs a C function with the member's parameters and its own return type; where the member
  returns another type (an unnamed descriptor getter returning `int` becomes `igVec3fMetaField *getMetaField()`),
  memberize casts the uses back: an assignment of the result to the C form's integer
  (`*(int *)p = (int)X::getMetaField()`), and the function named in a field table
  (`(FieldFactory)X::_instantiateFromPool`).
- `tools/whole_file_rows.py` keeps a caller unit's row as it was where the compile did not change it: an entry
  stays in its place while its name still binds at its address (the object names it, or symbols.txt,
  data-names.tsv, the compiler-name map, another unit's row or the address in the name binds it), so stale aliases
  (`DAT_004fb410` beside `g_resultSuccess`) stay until their name stops binding.
- `tools/whole_file_rows.py --unit-va <va> --write` cannot regenerate a unit whose name has two source files
  (`sony_libkernl_exit`) without `--source`; its row stays as it was and still verifies. A start the present row
  places (`0x37a600`, which three duplicate smart-pointer destructors fit) is its name's alone: the other
  byte-identical destructors stay duplicates, and those rows regenerate unchanged.
