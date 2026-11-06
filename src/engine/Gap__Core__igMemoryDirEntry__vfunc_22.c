/* 0x002ef670
 * Vtable slot 22 (GetMetaObject): returns the first word of the igMemoryDirEntry class's
 * metaobject handle at 0x00585f60 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igMemoryDirEntry_metaObject[4];
int Gap__Core__igMemoryDirEntry__vfunc_22(void) {
    return g_igMemoryDirEntry_metaObject[0];
}
