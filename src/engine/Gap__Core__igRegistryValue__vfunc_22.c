/* 0x00331930: published MetaObject accessor of Gap::Core::igRegistryValue.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igRegistryValue_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igRegistryValue_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igRegistryValue_metaObject[4];
int Gap__Core__igRegistryValue__vfunc_22(void) {
    return g_igRegistryValue_metaObject[0];
}
