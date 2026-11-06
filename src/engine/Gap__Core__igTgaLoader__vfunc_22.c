/* 0x00180de0: published MetaObject accessor of Gap::Core::igTgaLoader.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igTgaLoader_metaObject_*,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igTgaLoader_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igTgaLoader_metaObject[4];
int Gap__Core__igTgaLoader__vfunc_22(void) {
    return g_igTgaLoader_metaObject[0];
}
