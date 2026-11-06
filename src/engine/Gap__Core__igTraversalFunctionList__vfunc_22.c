/* published MetaObject accessor of Gap::Core::igTraversalFunctionList. A 12-byte leaf (lui/lw)
 * that returns the class handle slot g_igTraversalFunctionList_metaObject_*, the "published
 * MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igTraversalFunctionList_Register.c; the same shape as
 * igObjectList_GetPublishedMetaObject (rule `published-accessor`). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igTraversalFunctionList_metaObject[4];
int Gap__Core__igTraversalFunctionList__vfunc_22(void) {
    return g_igTraversalFunctionList_metaObject[0];
}
