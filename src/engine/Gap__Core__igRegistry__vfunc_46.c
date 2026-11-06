/* 0x003057a0: igRegistry vtable slot 46. Unlike the class's own published-MetaObject accessor, this
 * leaf (lui/lw) returns the class handle slot g_igRefMetaField_metaObject of the sibling class igRefMetaField
 * (registered in src/engine/igRefMetaField_Register.c). Read through the array extern so the
 * load stays absolute; slot role not established beyond the returned handle. */
extern int g_igRefMetaField_metaObject[4];
int Gap__Core__igRegistry__vfunc_46(void) {
    return g_igRefMetaField_metaObject[0];
}
