/* published MetaObject accessor of Gap::Core::igCallStackTracer. A 12-byte leaf (lui/lw) that
 * returns the class handle slot g_igCallStackTracer_metaObject, the "published MetaObject slot"
 * passed to igMetaObject_RegisterClass in src/engine/igCallStackTracer_Register.c; the same shape
 * as igObjectList_GetPublishedMetaObject (rule `published-accessor`). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igCallStackTracer_metaObject[4];
int Gap__Core__igCallStackTracer__vfunc_22(void) {
    return g_igCallStackTracer_metaObject[0];
}
