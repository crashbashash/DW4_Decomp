/* 0x00239380: published MetaObject accessor of Gap::Core::igSearchSceneGraph.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igSearchSceneGraph_metaObject_0056dc60,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igSearchSceneGraph_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igSearchSceneGraph_metaObject_0056dc60[4];
int Gap__Core__igSearchSceneGraph__vfunc_22(void) {
    return g_igSearchSceneGraph_metaObject_0056dc60[0];
}
