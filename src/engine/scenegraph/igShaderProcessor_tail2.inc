int Gap__Sg__igShaderProcessor__vfunc_24(void *arg0, void *arg1) {
    return *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg1) + 36)) + 8)) + 8) > 0;
}

void Gap__Sg__igShaderProcessor__vfunc_25(void) {

}

void FUN_001d9090(SkeletonBitOwnerView *o, int index, int value) {
    SkeletonBitListView *l = o->_bits;
    int i = l->_bitCount;
    if (i <= index) {
        unsigned int words;
        int n = index + 1;
        l->_bitCount = n;
        words = (unsigned int)(n + 31) >> 5;
        if ((int)words >= 0) {
            if ((int)words <= l->_capacity) { l->_count = words; }
            else { List_Resize(l, words, 4); }
        }
        {
            int j;
            for (j = i; j <= index; j++) {
                setBit(o->_bits, j);
            }
        }
    }
    l = o->_bits;
    if (value != 0) {
        setBit(l, index);
    } else {
        clearBit(l, index);
    }
}

