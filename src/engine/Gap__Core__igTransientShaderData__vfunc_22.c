/* 0x001e3a30: published MetaObject accessor of Gap::Core::igTransientShaderData.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igTransientShaderData_metaObject_*,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igTransientShaderData_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igTransientShaderData_metaObject_005611a8[4];
int Gap__Core__igTransientShaderData__vfunc_22(void) {
    return g_igTransientShaderData_metaObject_005611a8[0];
}
