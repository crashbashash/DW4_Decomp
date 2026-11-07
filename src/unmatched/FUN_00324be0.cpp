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
class TaggedHeap { public: virtual void d0(); virtual void d1(); virtual void *Allocate(unsigned size); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void *AllocateSized(unsigned size); virtual void d9(); virtual void d10(); virtual void *AllocateAligned(unsigned size); };
class TaggedPool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int GetPoolIndex(); char pad4[116]; unsigned index; char pad124[32]; unsigned flags; };
extern "C" {
extern TaggedHeap *DAT_00587218;
void *FUN_00324be0(TaggedPool *self, unsigned size);
}
static inline int usesAligned(TaggedPool *p) { return (p->flags & 0x20) != 0; }
static inline int usesSized(TaggedPool *p) { return (p->flags & 0x10) != 0; }
void *FUN_00324be0(TaggedPool *self, unsigned size) {
    unsigned overhead;
    unsigned total;
    void *block;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot = self->index >> 1;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total = overhead + size;
    if (usesAligned(self)) {
        block = DAT_00587218->AllocateAligned(total + 4);
    } else if (usesSized(self)) {
        block = DAT_00587218->AllocateSized(total + 4);
    } else {
        block = DAT_00587218->Allocate(total + 4);
    }
    if (block != 0) {
    h = (TaggedBlockHeader *)((char *)block + 4);
    id = self->GetPoolIndex() >> 1;
    h->poolLow = id;
    h->relocated = 0;
    h->marked = 0;
    h->used = 0;
    if (size >= 0x80000 || id >= 32) {
        h->sizeHigh = size >> 19;
        h->poolHigh = id >> 5;
        h->big = 1;
        h->extraBig = 1;
        h->extraUsed = 0;
        h->extraMarked = 0;
        h->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        h->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    h->words = ((end - aligned) >> 2) - 1;
    h->size = size;
    return (char *)h + (h->big == 0 ? 4 : 12);
    }
    return 0;
}
