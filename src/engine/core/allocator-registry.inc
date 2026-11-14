void igAllocator_EncodeIndexAlias(int extra0) {
    igAllocator_EncodeIndex((igMemoryPoolView *)extra0);
}

void igMemoryPool_SetPoolIndex(void) {

}

/* Encode an allocator as its registry index: vfunc_29() == 0 allocators live in the
 * primary list (code = index << 1), the rest in the secondary one (code =
 * index << 1 | 1); 0 when the object system is inactive.  An absent allocator
 * is not rejected, it encodes the -1 from IndexOf. */
int igAllocator_EncodeIndex(igMemoryPoolView *allocator){
    if(*g_objectSystem[0]&&!allocator->vfunc_29())return (unsigned)igMemoryPoolInfoList_IndexOf(g_primaryAllocatorList[0],allocator)<<1;
    unsigned char result=0;
    if(*g_objectSystem[0])return ((unsigned)igMemoryPoolInfoList_IndexOf(g_secondaryAllocatorList[0],allocator)<<1)|1;
    return result;
}

/* Decode igAllocator_EncodeIndex: the low bit picks the registry, the rest is the index into it. */
igMemoryPoolView *igAllocator_ResolveEncodedIndex(int index) {
    if (index & 1) {
        return g_secondaryAllocatorList[0]->data[index >> 1];
    }
    return g_primaryAllocatorList[0]->data[index >> 1];
}

void igMemoryPool_CollectMemoryRegions(void) {

}

void igMemoryPool_CollectAllMemoryRegions(int regions, int unused) {
    int i;
    igMemoryPoolView *pool;
    igMemoryPoolView *primary;
    int j;

    i = g_secondaryAllocatorList[0]->count - 1;
    while (i >= 0) {
        pool = g_secondaryAllocatorList[0]->data[i];
        if ((pool != 0) && (pool->isActive() != 0)) {
            pool->CollectMemoryRegions(regions);
        }
        i -= 1;
    }
    j = g_primaryAllocatorList[0]->count - 1;
    while (j >= 0) {
        primary = g_primaryAllocatorList[0]->data[j];
        if ((primary != 0) && (primary->isActive() != 0)) {
            primary->CollectMemoryRegions(regions);
        }
        j -= 1;
    }
}

void igMemoryPool_SetPreSize(int *status) {
    *status = g_resultFailure.v;
}

int igMemoryPool_GetPreSize(void) {
    return 0;
}

igResult igMemoryPool_Configure(void **pool, void *object) {
    igMemoryPoolInfo *info = (igMemoryPoolInfo *)object;
    igResult discarded;
    int maxSize;

    maxSize = info->_maxSize;
    if (maxSize != 0) {
        discarded = ((igMemoryPoolView *)pool)->SetMaxSize((long long)maxSize);
    }
    return g_resultSuccess;
}

