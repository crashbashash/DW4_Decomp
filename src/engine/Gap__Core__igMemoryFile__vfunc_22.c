/* 0x00331260
 * Vtable slot 22 (GetMetaObject): returns the first word of the igMemoryFile class's
 * metaobject handle at 0x00585f18 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igMemoryFile_metaObject_00585f18[4];
int Gap__Core__igMemoryFile__vfunc_22(void) {
    return g_igMemoryFile_metaObject_00585f18[0];
}
