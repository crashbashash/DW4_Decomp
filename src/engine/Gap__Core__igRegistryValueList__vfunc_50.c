/* 0x00331950: igRegistryValueList vtable slot 50. Unlike the class's own published-MetaObject accessor, this
 * leaf (lui/lw) returns the class handle slot g_igShortMetaField_metaObject_00585948 of the sibling class igShortMetaField
 * (registered in src/engine/igShortMetaField_Register.c). Read through the array extern so the
 * load stays absolute; slot role not established beyond the returned handle. */
extern int g_igShortMetaField_metaObject_00585948[4];
int Gap__Core__igRegistryValueList__vfunc_50(void) {
    return g_igShortMetaField_metaObject_00585948[0];
}
