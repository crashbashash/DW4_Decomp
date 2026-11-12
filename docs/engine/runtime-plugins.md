# Runtime plugins

The game ships two runtime plugins, `libBecRuntimePlugin` (the Bec framework, 39 manager references)
and `libNdmwRuntimePlugin` (the Ndmw game, 21). Each is an `igObject` whose reflected fields are
references to the module's managers; the plugin's job is to create those managers and hand them to
the Insight core. Both are built from the same three slots, and their source files share one shape
(`src/game/libBecRuntimePlugin.cpp`, `src/game/libNdmwRuntimePlugin.cpp`).

| Slot | Bec | Ndmw | Role |
| --- | --- | --- | --- |
| 20 | `Gap__Bec__libBecRuntimePlugin__vfunc_20` | `Gap__Bec__libNdmwRuntimePlugin__vfunc_20` | returns the plugin's meta object |
| 21 | `Gap__Bec__libBecRuntimePlugin__vfunc_21` | `Gap__Bec__libNdmwRuntimePlugin__vfunc_21` | creates every manager, then adds each to the core |
| 22 | `Gap__Bec__libBecRuntimePlugin__vfunc_22` | `Gap__Bec__libNdmwRuntimePlugin__vfunc_22` | removes each manager from the core |

## Creating the managers

For every field, in a fixed order, slot 21:

1. picks an allocator: the plugin's own (`igObject_GetAllocator`) when `g_useOwnerAllocator` is set,
   otherwise `Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0])`;
2. releases the old reference: decrements `_refCount` and calls `igObject_Destroy` when its low
   23 bits reach zero;
3. stores a new instance from the class's create function, which fetches the class meta object and
   calls `igMetaObject_CreateInstance` with the allocator.

`igMoviePlugin` does the same for its single manager. Bec's `_memory` is never created here but is
still added and removed.

## Adding and removing

The second half of slot 21, and all of slot 22, pass every non-null manager to
`igInsightCore_AddManager` / `igInsightCore_RemoveManager`. Add does nothing when the manager is
already in the core's `_managerList`; otherwise it appends it, stores the core in the manager's +12
word and calls the manager's slot 23. Remove does the reverse: slot 24, clear +12, drop from the
list. The add and remove orders differ from the field order and from each other; the source keeps
the retail order, since it is the order managers start and stop.

## Open questions

- The create functions are named `FUN_` in source; their recovered names (`<Class>_CreateInstance`,
  class from the meta object each loads) touch every Bec/Ndmw class file and are queued as a wide rename.
- Manager slots 23 and 24 are named only by role (attach/detach to the core).
