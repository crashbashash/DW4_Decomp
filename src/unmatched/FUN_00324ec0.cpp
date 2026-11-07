class Heap { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void Free(void *); virtual void d8(); virtual void FreeSized(void *, int); virtual void d10(); virtual void d11(); virtual void FreeAligned(void *, int);  };
extern "C" {
extern Heap *DAT_00587218[4];
}
struct T { unsigned char lo:7; unsigned char flag:1; };
struct B0 { unsigned char b0:1; unsigned char words:4; unsigned char hi:3; char p1[2]; unsigned char lo5:5; unsigned char x5:1; unsigned char offset:1; unsigned char big:1; };
union H {
    struct { unsigned f0:5; unsigned sz:19; unsigned rest:8; unsigned pad4; unsigned short ext:12; } w;
    B0 b;
};
struct Pool { char p[156]; unsigned flags; };
static inline int f20(Pool *p) { return (p->flags & 0x20) != 0; }
static inline int f10(Pool *p) { return (p->flags & 0x10) != 0; }
extern "C" void FUN_00324ec0(Pool *self, unsigned char *p) {
    H *h = (H *)(p - 4);
    unsigned size;
    if (((T *)(p - 1))->flag == 1) {
        h = (H *)(p - 12);
    }
    size = h->w.sz;
    if (h->b.big == 1) {
        size = size + (h->w.ext << 19);
    }
    size = (size + 3) & ~3;
    size = size + (h->b.words + 1) * 4;
    if (h->b.offset != 0) {
        int off = *(unsigned short *)((char *)h - 2);
        char *base = (char *)h - off;
        size = size + ((char *)h - base);
        if (f20(self)) {
            DAT_00587218[0]->FreeAligned(base, size);
        } else if (f10(self)) {
            DAT_00587218[0]->FreeSized(base, size);
        } else {
            DAT_00587218[0]->Free(base);
        }
    } else {
        char *base = (char *)h - 4;
        if (f20(self)) {
            DAT_00587218[0]->FreeAligned(base, size + 4);
        } else if (f10(self)) {
            DAT_00587218[0]->FreeSized(base, size + 4);
        } else {
            DAT_00587218[0]->Free(base);
        }
    }
}
