/* 0x00331230
 * Vtable slot 22 (GetMetaObject): returns the first word of the igMemoryPoolInfo class's
 * metaobject handle at 0x00585e00 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igMemoryPoolInfo_metaObject_00585e00[4];
int Gap__Core__igMemoryPoolInfo__vfunc_22(void) {
    return g_igMemoryPoolInfo_metaObject_00585e00[0];
}
