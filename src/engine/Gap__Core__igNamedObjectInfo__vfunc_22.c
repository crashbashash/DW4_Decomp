/* 0x003311f0
 * Vtable slot 22 (GetMetaObject): returns the first word of the igNamedObjectInfo class's
 * metaobject handle at 0x00585bc0 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igNamedObjectInfo_metaObject_00585bc0[4];
int Gap__Core__igNamedObjectInfo__vfunc_22(void) {
    return g_igNamedObjectInfo_metaObject_00585bc0[0];
}
