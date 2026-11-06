/* published MetaObject accessor of Gap::Core::igSorter. A 12-byte leaf (lui/lw) that returns the
 * class handle slot g_igSorter_metaObject, the "published MetaObject slot" passed to
 * igMetaObject_RegisterClass in src/engine/igSorter_Register.c; the same shape as
 * igObjectList_GetPublishedMetaObject (rule `published-accessor`). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igSorter_metaObject[4];
int Gap__Core__igSorter__vfunc_22(void) {
    return g_igSorter_metaObject[0];
}
