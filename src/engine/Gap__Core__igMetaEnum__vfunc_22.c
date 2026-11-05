/* 0x003318a0
 * Vtable slot 22 (GetMetaObject): returns the first word of the igMetaEnum class's
 * metaobject handle at 0x00585d60 (class name from data/reflection.json; slot 22 is the
 * metaobject accessor, docs/engine/igvertexarray2helper.md).  The receiver is not
 * touched, so the function takes no parameters. */
extern int g_igMetaEnum_metaObject_00585d60[4];
int Gap__Core__igMetaEnum__vfunc_22(void) {
    return g_igMetaEnum_metaObject_00585d60[0];
}
