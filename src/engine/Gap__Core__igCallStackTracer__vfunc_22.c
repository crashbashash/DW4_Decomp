/* 0x00331450: published MetaObject accessor of Gap::Core::igCallStackTracer.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igCallStackTracer_metaObject_00586958,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igCallStackTracer_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igCallStackTracer_metaObject_00586958[4];
int Gap__Core__igCallStackTracer__vfunc_22(void) {
    return g_igCallStackTracer_metaObject_00586958[0];
}
