/* 0x003314b0: published MetaObject accessor of Gap::Core::igMallocMemoryPool.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igMallocMemoryPool_metaObject_00586b80,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igMallocMemoryPool_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igMallocMemoryPool_metaObject_00586b80[4];
int Gap__Core__igMallocMemoryPool__vfunc_22(void) {
    return g_igMallocMemoryPool_metaObject_00586b80[0];
}
