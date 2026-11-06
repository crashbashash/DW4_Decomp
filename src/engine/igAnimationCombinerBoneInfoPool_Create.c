/* 0x001a7cc0
 * Factory for igAnimationCombinerBoneInfoPool: make sure the class is
 * registered (static init), then instantiate its metaobject with the given
 * allocator (igMetaObject_CreateInstance(metaObject, allocator)). */
extern int g_igAnimationCombinerBoneInfoPool_metaObject[4];
int igAnimationCombinerBoneInfoPool_RunStaticInit();
int igMetaObject_CreateInstance(int, int);

void igAnimationCombinerBoneInfoPool_Create(int allocator) {
    igAnimationCombinerBoneInfoPool_RunStaticInit();
    igMetaObject_CreateInstance(g_igAnimationCombinerBoneInfoPool_metaObject[0], allocator);
}
