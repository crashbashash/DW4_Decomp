/* 0x001a1ae0
 * Factory for igEnbayaContextPool: make sure the class is registered (static
 * init), then instantiate its metaobject with the given allocator
 * (igMetaObject_CreateInstance(metaObject, allocator)). */
extern int g_igEnbayaContextPool_metaObject[4];
int igEnbayaContextPool_RunStaticInit();
int igMetaObject_CreateInstance(int, int);

void igEnbayaContextPool_Create(int allocator) {
    igEnbayaContextPool_RunStaticInit();
    igMetaObject_CreateInstance(g_igEnbayaContextPool_metaObject[0], allocator);
}
