/* 0x00142770: published MetaObject accessor of Gap::Core::igLightingStateAttr.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igLightingStateAttr_metaObject,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igLightingStateAttr_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igLightingStateAttr_metaObject[4];
int Gap__Core__igLightingStateAttr__vfunc_22(void) {
    return g_igLightingStateAttr_metaObject[0];
}
