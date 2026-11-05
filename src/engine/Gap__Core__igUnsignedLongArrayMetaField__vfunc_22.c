/* 0x00331010: published MetaObject accessor of Gap::Core::igUnsignedLongArrayMetaField.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igUnsignedLongArrayMetaField_metaObject_*,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igUnsignedLongArrayMetaField_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igUnsignedLongArrayMetaField_metaObject_00585720[4];
int Gap__Core__igUnsignedLongArrayMetaField__vfunc_22(void) {
    return g_igUnsignedLongArrayMetaField_metaObject_00585720[0];
}
