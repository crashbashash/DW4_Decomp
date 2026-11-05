/* 0x003312b0: published MetaObject accessor of Gap::Core::igLongArrayMetaField.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igLongArrayMetaField_metaObject_00586060,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igLongArrayMetaField_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igLongArrayMetaField_metaObject_00586060[4];
int Gap__Core__igLongArrayMetaField__vfunc_22(void) {
    return g_igLongArrayMetaField_metaObject_00586060[0];
}
