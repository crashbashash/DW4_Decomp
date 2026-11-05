/* 0x00149360: published MetaObject accessor of Gap::Core::igControllerList.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igControllerList_metaObject_0055f608,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igControllerList_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igControllerList_metaObject_0055f608[4];
int Gap__Core__igControllerList__vfunc_22(void) {
    return g_igControllerList_metaObject_0055f608[0];
}
