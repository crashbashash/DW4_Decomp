/* 0x003319d0
 * Class-handle getter: vtable slot 50 of Gap::Core::igNonRefCountedThreadList returns the metaobject slot of
 * igUnsignedIntMetaField (global at 0x585738), not of igNonRefCountedThreadList itself.
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igUnsignedIntMetaField_metaObject[4];
int Gap__Core__igNonRefCountedThreadList__vfunc_50(void) {
    return g_igUnsignedIntMetaField_metaObject[0];
}
