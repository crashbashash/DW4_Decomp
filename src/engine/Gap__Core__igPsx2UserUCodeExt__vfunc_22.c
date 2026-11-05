/* 0x00180bf0: published MetaObject accessor of Gap::Core::igPsx2UserUCodeExt.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igPsx2UserUCodeExt_metaObject_005604d0,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igPsx2UserUCodeExt_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igPsx2UserUCodeExt_metaObject_005604d0[4];
int Gap__Core__igPsx2UserUCodeExt__vfunc_22(void) {
    return g_igPsx2UserUCodeExt_metaObject_005604d0[0];
}
