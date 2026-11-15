void igAllocator_EncodeIndexAlias(int extra0) {
    igAllocator_EncodeIndex((igMemoryPoolView *)extra0);
}

void igMemoryPool_SetPoolIndex(void) {

}

/* Encode an allocator as its registry index: IsSecondaryAllocator() == 0 allocators live in the
 * primary list (code = index << 1), the rest in the secondary one (code =
 * index << 1 | 1); 0 when the object system is inactive.  An absent allocator
 * is not rejected, it encodes the -1 from IndexOf. */
int igAllocator_EncodeIndex(igMemoryPoolView *allocator){
    if(*g_objectSystem&&!allocator->IsSecondaryAllocator())return (unsigned)igMemoryPoolInfoList_IndexOf(g_primaryAllocatorList,allocator)<<1;
    unsigned char result=0;
    if(*g_objectSystem)return ((unsigned)igMemoryPoolInfoList_IndexOf(g_secondaryAllocatorList,allocator)<<1)|1;
    return result;
}

/* Decode igAllocator_EncodeIndex: the low bit picks the registry, the rest is the index into it. */
igMemoryPoolView *igAllocator_ResolveEncodedIndex(int index) {
    if (index & 1) {
        return g_secondaryAllocatorList->data[index >> 1];
    }
    return g_primaryAllocatorList->data[index >> 1];
}

void igMemoryPool_CollectMemoryRegions(void) {

}

void igMemoryPool_CollectAllMemoryRegions(int regions, int unused) {
    int i;
    igMemoryPoolView *pool;
    igMemoryPoolView *primary;
    int j;

    i = g_secondaryAllocatorList->count - 1;
    while (i >= 0) {
        pool = g_secondaryAllocatorList->data[i];
        if ((pool != 0) && (pool->IsActive() != 0)) {
            pool->CollectMemoryRegions(regions);
        }
        i -= 1;
    }
    j = g_primaryAllocatorList->count - 1;
    while (j >= 0) {
        primary = g_primaryAllocatorList->data[j];
        if ((primary != 0) && (primary->IsActive() != 0)) {
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

