/* 0x00331530
 * Metaobject accessor of Gap::Core::igArenaMemoryPool: returns the class handle slot
 * g_igArenaMemoryPool_metaObject, the "published MetaObject slot" that
 * igArenaMemoryPool_Register.c passes to igMetaObject_RegisterClass.
 * The slot is read through the array extern so the load stays absolute. */
extern int g_igArenaMemoryPool_metaObject[4];
int Gap__Core__igArenaMemoryPool__vfunc_22(void) {
    return g_igArenaMemoryPool_metaObject[0];
}
