# Alchemy core: the `CoreLibrary` unit

Alchemy's core library (`Gap::Core`) is the bottom layer of the engine: the object model and reflection, typed
lists, memory pools, interned strings, files and media, the PS2 platform classes and the diagnostics. In the
retail image it is one source file, the unit `alchemy-core_CoreLibrary` at `0x2b5d50..0x331f30`, rebuilt as
`src/engine/core/CoreLibrary.cpp`. This page is the map; the mechanisms have their own documents, linked from
each section.

## Source layout

- **One unit, one profile.** `config/SLUS-20836/units.tsv` has a single `whole file` row for the range: MWCC
  `b52`, `-O4,s -sdatathreshold 2 -RTTI off -inline level=8,bottomup`, exceptions off
  ([build profiles](build-profiles.md)). Its `config/SLUS-20836/unit-objects.json` row is keyed `0x002b5d50`
  (`symbol` `CoreLibrary_MarkRegistered`, `whole_file`) and lists every emitted body, the dead-stripped
  destructor copies, the data the file defines and the static initialiser `__sinit_CoreLibrary.cpp`
  ([whole-file units](emitted-functions.md#whole-file-units),
  [Alchemy library initialisers](emitted-functions.md#the-alchemy-library-initialisers)).
- **`CoreLibrary.cpp`** is only includes and the globals: `CoreLibrary.h`, then the `.inc` fragments in retail
  address order, then the objects `__sinit_CoreLibrary.cpp` constructs (the file-device list, the 46
  `kIGMemoryPoolHandle*` handles, `g_resultSuccess`/`g_resultFailure` and `g_systemAllocator`).
- **`CoreLibrary.h`** is the unit's one header: every declaration, struct, view class and inline helper the
  fragments share, so each class has exactly one definition. Reflected data layouts come from the generated
  `include/dw4/reflected.h`; `igTDataList<T>` is `include/dw4/igTDataList.h`, and `igSmartPointer<T>` with
  `igVirtualObject` (an `igObject` whose vtable is a real vptr) is `include/dw4/igSmartPointer.h`.
- **`include/dw4/igMemoryPoolView.h`** is the memory-pool vtable (slots 0-96) as a class. It is shared outside
  core: `src/movie/igCriMovieCodec.cpp` and, through `include/dw4/lua_game_state.h`, the Lua units
  `src/lua/lmem.c` and `src/lua/lstate.c`. Those build with `-Dlong=int`, so the slots with a 64-bit argument or
  return have an `#ifndef long` arm that keeps the slot without its signature. A change to this header is
  checked against all three users, not core alone.
- **Fragment order follows retail.** The file is laid out the way the original compiler emitted it, in four
  runs:
  1. `LibraryFront.inc`: `CoreLibrary_MarkRegistered`, the library's one-shot registration latch.
  2. `0x2b5da0..0x2d0530`: one `<Class>.inc` per class holding its registration block (`_Create`,
     `_GetMetaObject`, `_GetVTable`, `_EnsureRegistered`, `_Register`, `_InitFields`, smart-pointer destructors).
     The classes run in reverse alphabetical order (`igVirtualCFuncMetaField` first), the list classes
     grouped after `igDataList`; an `igPsx2*` class's accessors follow its abstract base's block, and the
     pools, the program files and the `igPsx2*` registration blocks come last.
  3. `0x2d0550..0x330e50`: the method bodies, class by class in alphabetical order (`igAliasMemoryPool_tail.inc`
     first), with the pools' allocators, `psx2PageMemory.inc` (the system allocator) and the `igPsx2*` classes
     at the end. A class whose methods are split by another class's bodies has `_tail2`, `_tail3` fragments;
     topic fragments (`list-services`, `allocator-registry`, `init-callback-array` for the object system,
     `igMemory`, `StringPool`, `StringTable`) hold runs that belong to no one class.
  4. `InlineTail.inc` (`0x330e60..0x331e80`): the out-of-line copies of small members (the `_GetMeta` leaves,
     default initialisers, list trims) the compiler placed after everything else.

  A new body goes into the fragment whose range holds its address, in address order inside it.

### Proving a change

The verdict is the whole file's: `python3 tools/check.py --no-cache --function 0x2b5d50 --cand
src/engine/core/CoreLibrary.cpp` compiles the unit under its profile and checks every body, its relocations
and the unit's data. A change to `CoreLibrary.h` is covered by that run (no other source includes it); a
change to `igMemoryPoolView.h` also needs the movie codec's and the two Lua units' rows checked.

## Class families and their views

A *view* is a class in `CoreLibrary.h` that spells a reflected class's vtable so callers can make virtual
calls: placeholder slots (`d<N>`, `RESERVED(n)`) hold the position of slots nobody calls, and the named slots sit
at their retail byte offsets (MWCC keeps two header words in front, so slot N is at byte 8 + 4N). Views are ABI
only and never instantiated; there is one per class, derived where retail's classes derive.

### Object model

- **`igObject`** (`_vtable`, `_refCount`) is the data form in `reflected.h`; `igObjectDispatchView` is its
  vtable. `_refCount` packs the count (low 23 bits), a flag and the owning pool's index (top byte):
  `igRefCountWord`; a count reaching zero calls `igObject_Destroy`. Bodies: `igObject.inc`, `igObject_tail*.inc`.
- **`igMetaObject`** is a class's runtime description, **`igMetaField`** a field's; `igMetaFieldView` is the
  field family's vtable, described slot by slot in [MetaField vtables](metafield-vtable.md). The per-type field
  classes (`ig<Type>MetaField`, `ig<Type>ArrayMetaField`, `igRefMetaField`, `igMemoryRefMetaField`, …) and
  `igMetaEnum` are the bulk of the registration pass. What the metadata means: [reflection
  metadata](reflection-metadata.md).
- **Registration.** Every class has the same pattern: `<Class>_EnsureRegistered` runs
  `igMetaObject_RunStaticInit(<Class>_Register)`; `<Class>_Register` calls `CoreLibrary_MarkRegistered` and then
  `igMetaObject_RegisterClass` with the parent's register and accessor functions, `<Class>_GetMetaObjectFunction`,
  the class name, the instance size, `<Class>_GetVTable`, `<Class>_InitFields`, a static-init callback and
  `g_<Class>_callbackList`. `_InitFields` builds the fields from `g_<Class>_ctorTable`
  (`igMetaObject_CreateFields`), sets defaults and target classes, and names them from `g_<Class>_fieldTable`
  (`igMetaObject_NameFields`). An abstract base passes `<Class>_SetAbstractProxy` in the accessor's place, which
  points the meta-object at its PS2 class (`igTimer_SetAbstractProxy` → `igLongTimer`, `igMedia` → `igPsx2Media`,
  `igSemaphore`, `igCallStackTracer`); a few PS2 classes pass `<Class>_SetWriteProxy`, which points back at the
  base (`igPsx2ThreadManager_SetWriteProxy`, `igPsx2CallStackTracer_SetWriteProxy`). The registrar's arguments and
  states: [class registration](reflection-registration.md); the object-system side:
  [metadata bootstrap](metadata-bootstrap.md), [object base](object-base.md), [object creation](object-creation.md),
  [field factories](field-factories.md). `_GetVTable` builds a stack instance and reads its vtable word
  ([getvtable-fold](getvtable-fold.md)).
- **Object system.** `init-callback-array.inc` holds the growable callback array and `igObjectSystem_*`
  (start-up, ini and path settings, exit); the boot path into it is in [engine boot](engine-boot.md), the
  registry and contexts in [registry bootstrap](registry-bootstrap.md).

### Lists

`igTDataList<T>` is the one list template (`_count`, `_capacity`, `_data` after the object header);
`igDataList` and the typed lists (`igIntList`, `igObjectList`, the `*NoClean` and `*ListList` variants, …) are
its registered instances. The shared growth, insertion and search primitives (`List_*`) are in
[list services](list-services.md), the retaining object-list operations in [object lists](object-lists.md),
and `__internalObjectList`/`__internalNonRefCountedObjectList` in [internal object lists](internal-object-lists.md).

### Memory

- **Contexts.** `MemoryContext` is the 46-slot allocator table (a `ContextRecord` per slot: allocator, name,
  descriptor); `igMemoryPoolContextInfo` and `igMemoryPoolInfo` are its reflected configuration. Construction
  and slots: [context lifecycle](context-lifecycle.md), the slot builder [allocator builder](allocator-builder.md),
  owner search and encoded pool indices [allocator registries](allocator-registry.md). The `Memory_*` entry
  points (`igMemory.inc`) allocate through the current context.
- **Pools.** `igMemoryPool` is the base (`igMemoryPoolView`); each pool class appends its own slots from 97 in
  a derived view: `igAliasMemoryPoolView` ([alias-pool binding](alias-pool-binding.md),
  [alias-pool runtime](alias-pool-runtime.md)), `igArenaMemoryPoolView` (dlmalloc 2.7 with the
  `TaggedBlockHeader` chunk header, `ArenaState` and `GangRecord` gang allocations:
  [arena allocator](arena-allocator.md)), `igMallocMemoryPoolView` (tagged blocks with tail sentinels),
  `igPageMemoryPoolView` and the stack pool (`StackBlockRecord`). Page and stack pools sit in the secondary
  allocator list, the others in the primary one.
- **System allocator.** `SystemAllocator` (`psx2PageMemory.inc`) owns the process memory map: 4 KB pages
  tracked two bits each in 64 page tables, `SystemMemoryStatistics`, and the memory-map dump (`DumpRegion`).
  Allocation helpers and buffers on top: [array storage](array-storage.md),
  [memory-field copy](memory-field-copy.md), [memory field values](memory-field-values.md).

### Strings

`StringPool` interns strings into `StringChunk`s (a `StringTokenHeader` with owner and count in front of each
token) and keeps them ordered in a `StringTable`; `igStringRef` is the holder that interns in its constructor
and releases in its destructor, and `InternedStrings::get()` creates the shared pool on first use. See
[string pool](string-pool.md) and [string chunks](string-chunks.md). The reflected string classes are separate:
`igStringObj` (an owned, formatted string), `igStringTable` (hashed, `igStringTableView`) and
`igStringRefList`; field-level string handling is [string fields](string-fields.md).

### Files and media

- **Files.** `igFile` is the base (`igFileView`); `igMediaFile` (`igMediaFileView`) opens through a media
  device, `igPsx2File` (`igPsx2FileView`) through the IOP file system, `igMemoryFile` from a buffer,
  `igAdxFile` along a list of search paths, and `igProgramFile`/`igElfFile` read an ELF image (`ElfFileView`).
  `igFolder`/`igPsx2Folder` list directories.
- **Media.** `igMedia`/`igPsx2Media` (`igPsx2MediaView`) forward requests to the IOP file module over RPC,
  with a handle table (`MediaHandlePool`) and request records (`MediaIoRequest`).
- **IGB.** `igIGBFile` (`igIGBFileView`, a directory) reads and writes `.igb` files: header, meta-object and
  meta-field tables, objects and memory blocks ([igBinary format](igbinary-format.md)). Its `igDirectory` base
  (`igDirectoryView`) holds `igDirEntry` subclasses: `igObjectDirEntry`, `igMemoryDirEntry` and the
  `igExternal*Entry` references. `igInfo` objects travel in directories, and `igResource` (`igResourceView`)
  tracks the directories loaded.
- **Configuration.** `igRegistry` holds the ini sections; `igDriverDatabase` parses the driver database into
  `ConfigNode` trees; `igPluginHelper`, `igLibrary` and `igLibraryLoader` load plug-in libraries.

### Platform

`igThread`/`igPsx2Thread` (`igPsx2ThreadView`, managed by `igPsx2ThreadManager`), `igSemaphore`/`igPsx2Semaphore`
(`igSemaphoreView`; `ScopedLock` holds one for a scope), `igTimer`/`igLongTimer`/`igPsx2LongTimer`
(`igLongTimerView`), `igQueue`/`igStandardQueue` (service threads) and `igPsx2IopRpcConnection` (a bound SIF RPC
client, `SifClientData`). The inventory of the platform classes and their interfaces is generated in
[platform seam](platform-seam.md); what touches hardware is in [platform boundary](platform-boundary.md).

### Diagnostics

`igEventTracker` (`igEventTrackerView`, `EventRecord`) records memory, marker and notification events;
`igCallStackTable` and `igCallStackTracer`/`igPsx2CallStackTracer` record call stacks; `igLocationTable`
(`LocationRecord`) and `igSymbolTable` (`SymbolRecord`) map addresses to names; `igReport_*` prints notices,
warnings and errors (to `g_reportOutputFile` when set); `igErrorHandler` is the error singleton.

## Naming

- **Functions** are `<Class>_<Method>` (`igIGBFile_ReadObjects`), with the reflection pattern names above, and
  `List_*`, `Memory_*`, `StringPool_*` for the topic runs. A few virtuals keep their mangled
  `Gap__Core__<Class>__<method>` symbol.
- **Slots** take the name of the implementation the vtable word points to: a view slot is named once a body
  behind that word has a recovered name, and the name carries to every override. Slots nobody has read keep a
  placeholder or `vfunc_NN`.
- **Data** follow the data-name rules in [naming](naming.md): `g_<Class>_vtable`, `g_<Class>_metaObject`,
  `<Class>_className`, `g_<Class>_callbackList`, `g_<Class>_ctorTable`, `g_<Class>_fieldTable`,
  `g_<Class>_fieldDescriptors`, `g_<Class>_fieldOffsets` (`config/SLUS-20836/data-names.tsv`).
- **`config/SLUS-20836/names/CoreNames.tsv`** is the core overlay: address, name, module, confidence and the
  evidence (assert strings, the view slot a body fills, registrar arguments, the body itself); medium rows
  record the alternative considered. The object-model overlays `ObjectModel.tsv` and `MetaFieldSlots.tsv`
  cover the meta-field family. Applying names: [naming](naming.md).

## What is open

- **Resisting shapes.** [Understanding a resisting shape](understanding-shapes.md) records the causes found in
  this unit (most entries name `CoreLibrary.cpp`); its open entries for core are the two `xori 1` in a row
  (the semaphore functions below) and the malloc pool's free path (`0x3236a0`), which matches on PS2 only with
  a variable its GameCube sibling reuses.
- **Functions without source.** Five functions in the range have no definition in `src/` and link from the
  retail image:
  - `igDependencyOrderedList_TopologicalSort` (`0x2d7280`): gathers the nodes of the dependency pairs into a
    sorted pointer list and moves the nodes nothing depends on into the ordered list, flagging a cycle when it
    has to pick one; called before `igDependencyOrderedList_Rebuild`.
  - `igDriverDatabase_SetSubPropertyValue` (`0x2d9740`): creates a property's name and value lists when
    missing, then replaces the value of an interned name or appends the pair; the setter of
    `igDriverDatabase_GetSubPropertyValue`.
  - `igPsx2Semaphore_Signal` (`0x32ef20`): signals the semaphore, choosing `SignalSema` or `iSignalSema` from
    the interrupt-enable bit, which retail tests with the open `sltu; xori; xori; andi 0xff` sequence.
  - `igPsx2Semaphore_Wait` (`0x32f060`): `WaitSema` or `PollSema` by the block flag, with the same
    interrupt-state test.
  - `igPsx2Thread_ThreadEntry` (`0x32f7f0`): the entry `igPsx2Thread_Start` gives the kernel; calls the thread
    function with its argument, stores the result and finishes the thread through the thread manager. Retail
    zero-extends the incoming argument from 64 bits (`dsll32`/`dsrl32`) before using it as the thread object.
