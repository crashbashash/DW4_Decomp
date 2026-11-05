/* 0x0031edb0 - 264 bytes. Allocator block-size decode (same header layout as FUN_00324b50/FUN_0031f230, 19-bit size plus 12-bit extension); alternate -O3. */
struct T { unsigned char lo:7; unsigned char flag:1; };
struct H { unsigned lo:5; unsigned sz:19; unsigned mid:7; unsigned big:1; unsigned pad4; unsigned ext:12; unsigned rest:20; };
int FUN_0031edb0(int arg0, unsigned char *p) {
    unsigned int off;
    unsigned int v;
    struct H *h;
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        p = p - off;
        h = (struct H *)(p - 4);
        if (((struct T *)(p - 1))->flag == 1) {
            h = (struct H *)(p - 12);
        }
        if (h == 0) {
            return 0;
        }
        if (h->big == 0) {
            v = h->sz;
        } else {
            v = h->sz + (h->ext << 19);
        }
        return v - (off + 4);
    }
    h = (struct H *)(p - 4);
    if (((struct T *)(p - 1))->flag == 1) {
        h = (struct H *)(p - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        return h->sz;
    }
    return h->sz + (h->ext << 19);
}
