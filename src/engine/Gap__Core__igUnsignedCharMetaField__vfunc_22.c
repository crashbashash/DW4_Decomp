/* 0x00331050: published MetaObject accessor of Gap::Core::igUnsignedCharMetaField.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igUnsignedCharMetaField_metaObject_*,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igUnsignedCharMetaField_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igUnsignedCharMetaField_metaObject[4];
int Gap__Core__igUnsignedCharMetaField__vfunc_22(void) {
    return g_igUnsignedCharMetaField_metaObject[0];
}
