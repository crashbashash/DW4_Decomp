/* 0x00331140: published MetaObject accessor of Gap::Core::igShortArrayMetaField.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igShortArrayMetaField_metaObject_00585958,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igShortArrayMetaField_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igShortArrayMetaField_metaObject_00585958[4];
int Gap__Core__igShortArrayMetaField__vfunc_22(void) {
    return g_igShortArrayMetaField_metaObject_00585958[0];
}
