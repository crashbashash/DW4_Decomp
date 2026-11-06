/* 0x00142480: published MetaObject accessor of Gap::Core::igTextureCoordSourceAttr.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igTextureCoordSourceAttr_metaObject_*,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igTextureCoordSourceAttr_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igTextureCoordSourceAttr_metaObject[4];
int Gap__Core__igTextureCoordSourceAttr__vfunc_22(void) {
    return g_igTextureCoordSourceAttr_metaObject[0];
}
