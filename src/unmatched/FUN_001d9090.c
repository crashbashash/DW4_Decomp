typedef struct SkeletonBitListView { int _vtable; unsigned int _refCount; int _count; int _capacity; unsigned int *_data; int _bitCount; } SkeletonBitListView;
typedef struct SkeletonBitOwnerView { char pad[44]; SkeletonBitListView *_bits; } SkeletonBitOwnerView;
void List_Resize(void *, int, int);
static inline void setBit(SkeletonBitListView *l, int i) {
    unsigned int mask = 1 << (i & 31);
    int w = (unsigned int)i >> 5;
    unsigned int *p = &l->_data[w];
    int c = l->_count;
    unsigned int v = mask | *p;
    if (c != 0 && w >= 0 && c > w) { *p = v; }
}
static inline void clearBit(SkeletonBitListView *l, int i) {
    unsigned int mask = ~(1 << (i & 31));
    int w = (unsigned int)i >> 5;
    unsigned int *p = &l->_data[w];
    int c = l->_count;
    unsigned int v = mask & *p;
    if (c != 0 && w >= 0 && c > w) { *p = v; }
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
