/* 0x00180c60: published MetaObject accessor of Gap::Core::igPsx2ScissorExt.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igPsx2ScissorExt_metaObject_005604f8,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igPsx2ScissorExt_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igPsx2ScissorExt_metaObject_005604f8[4];
int Gap__Core__igPsx2ScissorExt__vfunc_22(void) {
    return g_igPsx2ScissorExt_metaObject_005604f8[0];
}
