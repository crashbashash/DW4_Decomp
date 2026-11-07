typedef struct H { char p0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char p1[4]; unsigned int pad : 12; unsigned int ext : 12; unsigned int rest : 8; } H;
typedef struct T { unsigned char b : 7; unsigned char flag : 1; } T;
int igAllocator_ResolveEncodedIndex();

int Gap__Core__igMallocMemoryPool__vfunc_85(int arg0, char *arg1) {
    H *h;
    int v;
    int r;
    int a;

    a = arg0;
    h = (H *)(arg1 - 4);
    if (((T *)(arg1 - 1))->flag == 1) {
        h = (H *)(arg1 - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->flag == 0) {
        v = h->lo * 2;
    } else {
        v = (h->lo + (h->ext << 5)) * 2;
    }
    r = igAllocator_ResolveEncodedIndex(v);
    return r == a;
}
