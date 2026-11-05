/* 0x00331210
 * Vtable slot 22 (GetMetaObject): returns the first word of the igMemoryRefArrayMetaField class's
 * metaobject handle at 0x00585de0 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igMemoryRefArrayMetaField_metaObject_00585de0[4];
int Gap__Core__igMemoryRefArrayMetaField__vfunc_22(void) {
    return g_igMemoryRefArrayMetaField_metaObject_00585de0[0];
}
