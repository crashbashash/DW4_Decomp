/* 0x00331990: published MetaObject accessor of Gap::Core::igStringObj.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igStringObj_metaObject_005858f0,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igStringObj_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igStringObj_metaObject_005858f0[4];
int Gap__Core__igStringObj__vfunc_22(void) {
    return g_igStringObj_metaObject_005858f0[0];
}
