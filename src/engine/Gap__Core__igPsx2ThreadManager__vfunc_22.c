/* 0x00330800: published MetaObject accessor of Gap::Core::igPsx2ThreadManager.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igPsx2ThreadManager_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igPsx2ThreadManager_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igPsx2ThreadManager_metaObject[4];
int Gap__Core__igPsx2ThreadManager__vfunc_22(void) {
    return g_igPsx2ThreadManager_metaObject[0];
}
