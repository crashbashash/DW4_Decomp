struct TaggedBlockHeader {
    unsigned char used : 1;
    unsigned char words : 4;
    unsigned size : 19;
    unsigned char poolLow : 5;
    unsigned char marked : 1;
    unsigned char relocated : 1;
    unsigned char big : 1;
    int previous;
    unsigned short sizeHigh : 12;
    unsigned poolHigh : 12;
    unsigned char extraUsed : 1;
    unsigned char extraMarked : 1;
    unsigned char extraTag : 5;
    unsigned char extraBig : 1;
};
class TaggedReallocHeap { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void *Reallocate(void *block, unsigned size, unsigned old); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void *ReallocateSized(void *block, unsigned size, unsigned old); virtual void d11(); virtual void d12(); virtual void *ReallocateAligned(void *block, unsigned size, unsigned old); };
struct TaggedTailByte { unsigned char low : 7; unsigned char extended : 1; };
class TaggedPool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int GetPoolIndex(); char pad4[116]; unsigned index; char pad124[32]; unsigned flags; };
extern "C" {
extern TaggedReallocHeap *DAT_00587218;
void *FUN_00324be0(TaggedPool *self, unsigned size);
void FUN_00324ec0(TaggedPool *self, void *p);
void *FUN_00325060(TaggedPool *self, char *p, unsigned size);
void *memcpy(void *, const void *, unsigned);
void *memmove(void *, const void *, unsigned);
}
static inline int usesAligned(TaggedPool *p) { return (p->flags & 0x20) != 0; }
static inline int usesSized(TaggedPool *p) { return (p->flags & 0x10) != 0; }
void *FUN_00325060(TaggedPool *self, char *p, unsigned size) {
    TaggedBlockHeader *h;
    unsigned end;
    unsigned aligned;
    int big;
    char *base;
    char *block;
    unsigned kept;
    unsigned total;
    unsigned index;
    unsigned newOverhead;
    unsigned slot;
    unsigned newSize;
    unsigned oldOverhead;
    unsigned used;
    TaggedBlockHeader *fresh;
    h = (TaggedBlockHeader *)(p - 4);
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    big = h->big;
    if (big == 0) {
        used = h->size;
        kept = used;
    } else {
        used = h->size;
        kept = used + (h->sizeHigh << 19);
    }
    if (big == 1) {
        used += h->sizeHigh << 19;
    }
    used = (used + 3) & ~3;
    total = used + (h->words + 1) * 4;
    oldOverhead = big == 0 ? 4 : 12;
    slot = self->index >> 1;
    if (size >= 0x80000 || slot >= 32) {
        newOverhead = 12;
    } else {
        newOverhead = 4;
    }
    base = (char *)h - 4;
    newSize = size + (newOverhead + 4);
    if (newOverhead + 4 < oldOverhead + 4) {
        newSize += oldOverhead - newOverhead;
    }
    if (h->relocated != 0) {
        char *moved = (char *)FUN_00324be0(self, size);
        if (moved != 0) {
            memcpy(moved, p, kept < size ? kept : size);
            FUN_00324ec0(self, p);
        }
        return moved;
    }
    if (usesAligned(self)) {
        block = (char *)DAT_00587218->ReallocateAligned(base, newSize, total + 4);
    } else if (usesSized(self)) {
        block = (char *)DAT_00587218->ReallocateSized(base, newSize, total + 4);
    } else {
        block = (char *)DAT_00587218->Reallocate(base, newSize, total);
    }
    if (block == 0) {
        return 0;
    }
    if (newOverhead + 4 != oldOverhead + 4) {
        memmove(block + (newOverhead + 4), block + (oldOverhead + 4), kept < size ? kept : size);
    }
    fresh = (TaggedBlockHeader *)(block + 4);
    index = self->index >> 1;
    fresh->poolLow = index;
    fresh->relocated = 0;
    fresh->marked = 0;
    fresh->used = 0;
    if (size >= 0x80000 || index >= 32) {
        fresh->sizeHigh = size >> 19;
        fresh->poolHigh = index >> 5;
        fresh->big = 1;
        fresh->extraBig = 1;
        fresh->extraUsed = 0;
        fresh->extraMarked = 0;
        fresh->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        fresh->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    fresh->words = ((end - aligned) >> 2) - 1;
    fresh->size = size;
    return (char *)fresh + (fresh->big == 0 ? 4 : 12);
}
