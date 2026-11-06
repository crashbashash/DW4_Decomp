/* 0x00458210: published MetaObject accessor of Gap::Core::igCharMetricsList.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igCharMetricsList_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igCharMetricsList_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igCharMetricsList_metaObject[4];
int Gap__Core__igCharMetricsList__vfunc_22(void) {
    return g_igCharMetricsList_metaObject[0];
}
