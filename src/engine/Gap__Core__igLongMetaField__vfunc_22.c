/* 0x00331290: published MetaObject accessor of Gap::Core::igLongMetaField.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igLongMetaField_metaObject_00586050,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igLongMetaField_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igLongMetaField_metaObject_00586050[4];
int Gap__Core__igLongMetaField__vfunc_22(void) {
    return g_igLongMetaField_metaObject_00586050[0];
}
