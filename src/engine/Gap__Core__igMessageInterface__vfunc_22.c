/* 0x0022ca20
 * Vtable slot 22 (GetMetaObject): returns the first word of the igMessageInterface class's
 * metaobject handle at 0x0056d8a8 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igMessageInterface_metaObject_0056d8a8[4];
int Gap__Core__igMessageInterface__vfunc_22(void) {
    return g_igMessageInterface_metaObject_0056d8a8[0];
}
