void igAllocator_EncodeIndexAlias(int extra0) {
    igAllocator_EncodeIndex((AllocatorLookupView *)extra0);
}

void FUN_002f0660(void) {

}

/* Encode an allocator as its registry index: Kind() == 0 allocators live in the
 * primary list (code = index << 1), the rest in the secondary one (code =
 * index << 1 | 1); 0 when the object system is inactive.  An absent allocator
 * is not rejected, it encodes the -1 from IndexOf. */
int igAllocator_EncodeIndex(AllocatorLookupView *allocator){
    if(*g_objectSystem[0]&&!allocator->Kind())return (unsigned)igMemoryPoolInfoList_IndexOf(g_primaryAllocatorList[0],allocator)<<1;
    unsigned char result=0;
    if(*g_objectSystem[0])return ((unsigned)igMemoryPoolInfoList_IndexOf(g_secondaryAllocatorList[0],allocator)<<1)|1;
    return result;
}

void FUN_002f0750(void) {

}

void FUN_002f0760(int arg0, int extra1) {
    int var_s2;
    VC_2f0760 *temp_s1;
    VC_2f0760 *temp_s2;
    int var_s1;

    var_s2 = ((L_2f0760 * *)g_secondaryAllocatorList)[0]->n - 1;
    while (var_s2 >= 0) {
        temp_s1 = ((L_2f0760 * *)g_secondaryAllocatorList)[0]->arr[var_s2];
        if ((temp_s1 != 0) && (temp_s1->a() != 0)) {
            temp_s1->b(arg0);
        }
        var_s2 -= 1;
    }
    var_s1 = ((L_2f0760 * *)g_primaryAllocatorList)[0]->n - 1;
    while (var_s1 >= 0) {
        temp_s2 = ((L_2f0760 * *)g_primaryAllocatorList)[0]->arr[var_s1];
        if ((temp_s2 != 0) && (temp_s2->a() != 0)) {
            temp_s2->b(arg0);
        }
        var_s1 -= 1;
    }
}

void FUN_002f0860(int *arg0) {
    *arg0 = g_resultFailure.v;
}

int FUN_002f0870(void) {
    return 0;
}

igResult FUN_002f0880(void **arg1, void *arg2) {
    DW4SR4 sp2C;
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg2) + 32);
    if (temp_v1 != 0) {
        sp2C = ((DW4VCSR_164_1 *)(arg1))->vX((long long)temp_v1);
    }
    return g_resultSuccess;
}

