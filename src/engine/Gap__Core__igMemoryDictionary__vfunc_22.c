/* 0x00331270: published MetaObject accessor of Gap::Core::igMemoryDictionary.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igMemoryDictionary_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igMemoryDictionary_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igMemoryDictionary_metaObject[4];
int Gap__Core__igMemoryDictionary__vfunc_22(void) {
    return g_igMemoryDictionary_metaObject[0];
}
