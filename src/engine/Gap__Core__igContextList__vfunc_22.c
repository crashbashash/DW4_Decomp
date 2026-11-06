/* 0x003315c0: published MetaObject accessor of Gap::Core::igContextList.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igContextList_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igContextList_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igContextList_metaObject[4];
int Gap__Core__igContextList__vfunc_22(void) {
    return g_igContextList_metaObject[0];
}
