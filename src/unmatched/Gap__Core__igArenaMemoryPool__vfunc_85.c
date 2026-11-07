struct T { unsigned char lo:7; unsigned char flag:1; };
struct H { unsigned sz:24; unsigned idx:5; unsigned mid:2; unsigned big:1; unsigned pad4; unsigned rest:12; unsigned ext:12; unsigned top:8; };
void *igAllocator_ResolveEncodedIndex(int);
int Gap__Core__igArenaMemoryPool__vfunc_85(void *self, unsigned char *p) {
    struct H *h;
    unsigned off;
    unsigned idx;
    if (p == 0) {
        return 0;
    }
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        if (off < 0x100011) {
            p = p - off;
        } else {
            return 0;
        }
    }
    h = (struct H *)(p - 4);
    if (((struct T *)(p - 1))->flag == 1) {
        h = (struct H *)(p - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        idx = h->idx;
    } else {
        idx = h->idx + (h->ext << 5);
    }
    return igAllocator_ResolveEncodedIndex(idx * 2) == self;
}
