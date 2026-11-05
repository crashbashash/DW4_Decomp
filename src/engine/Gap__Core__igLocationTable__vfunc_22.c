/* 0x003312d0: published MetaObject accessor of Gap::Core::igLocationTable.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igLocationTable_metaObject_00586078,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igLocationTable_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igLocationTable_metaObject_00586078[4];
int Gap__Core__igLocationTable__vfunc_22(void) {
    return g_igLocationTable_metaObject_00586078[0];
}
