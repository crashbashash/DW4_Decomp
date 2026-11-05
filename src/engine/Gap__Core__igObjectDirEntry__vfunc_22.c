/* 0x00301520
 * Class-handle getter: vtable slot 22 of Gap::Core::igObjectDirEntry returns the cached metaobject
 * pointer in the global at 0x585b70, the slot the class registration fills.
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igObjectDirEntry_metaObject_00585b70[4];
int Gap__Core__igObjectDirEntry__vfunc_22(void) {
    return g_igObjectDirEntry_metaObject_00585b70[0];
}
