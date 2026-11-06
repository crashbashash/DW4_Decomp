/* Factory for igAnimationStatePool: make sure the class is registered (static init), then
 * instantiate its metaobject with the given allocator (igMetaObject_CreateInstance(metaObject,
 * allocator)). */
extern int g_igAnimationStatePool_metaObject[4];
int igAnimationStatePool_RunStaticInit();
int igMetaObject_CreateInstance(int, int);

void igAnimationStatePool_Create(int allocator) {
    igAnimationStatePool_RunStaticInit();
    igMetaObject_CreateInstance(g_igAnimationStatePool_metaObject[0], allocator);
}
