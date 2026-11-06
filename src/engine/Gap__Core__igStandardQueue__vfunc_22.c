/* 0x00330f50: published MetaObject accessor of Gap::Core::igStandardQueue.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igStandardQueue_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igStandardQueue_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igStandardQueue_metaObject[4];
int Gap__Core__igStandardQueue__vfunc_22(void) {
    return g_igStandardQueue_metaObject[0];
}
