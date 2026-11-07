class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} igResult &operator=(const igResult &o) { v = o.v; return *this; }
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, char *);
void StringChunk_ReleaseHeader(int, void *);
char *strncpy(char *, const char *, int);
int Memory_GetAllocatorBySelector(int);
}
extern void *DAT_00586f20;
extern char *DAT_004c2170[46];
extern char DAT_004e0858[];
extern int DAT_00587018[4];
struct PoolDescString { int chunk; int refs; };
static inline void *descPool() {
    if (DAT_00586f20 == 0) {
        void *p = FUN_002eb010(16);
        if (p != 0) { p = StringPool_Construct(p); }
        DAT_00586f20 = p;
    }
    return DAT_00586f20;
}
static inline void setDescString(char **dst, char *src) {
    char *v = StringPool_Intern(descPool(), src);
    char *old = *dst;
    if (old != 0) {
        PoolDescString *h = (PoolDescString *)(old - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader(h->chunk, h); }
    }
    *dst = v;
}
struct PoolDescRecord { int vt; int rc; char *name; char q12[8]; char *alias; char *s24; int a28; int a32; int a36; char *s40; char *s44; char *s48; char *s52; char *s56; char *s60; char *s64; char *s68; char *s72; char *s76; int a80; };
struct PoolDescSlot { int pool; char name[128]; PoolDescRecord *record; };
extern "C" {
PoolDescRecord *FUN_002f8be0(int, char *);
PoolDescRecord *FUN_002f8ca0(int, char *);
PoolDescRecord *FUN_002bfed0(int);
void FUN_002f8a80(int, PoolDescRecord *);
}
class PoolDescManagerBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual igResult build(int, int); };
class PoolDescManager : public PoolDescManagerBase { public: char q4[4]; int nextSlot; char q12[4]; int table; };
static inline char *descName(PoolDescRecord *r) { char *n = r->name; if (n != 0) { return n; } return DAT_004e0858; }
extern "C" igResult FUN_002f3910(PoolDescManager *self, int index, PoolDescRecord *desc, int build) {
    igResult result = DAT_004fb410;
    int fail;
    PoolDescSlot *slot;
    if (index == -1) {
        index = self->nextSlot;
        if (index < 46) {
            setDescString(&desc->alias, DAT_004c2170[index]);
            self->nextSlot = self->nextSlot + 1;
        }
    } else if (index >= self->nextSlot) {
        self->nextSlot = index + 1;
    }
    if (index >= 0 && index < 46) {
        slot = (PoolDescSlot *)((char *)self + index * 0x90 + 0x14);
        strncpy(slot->name, descName(desc), 0x7f);
        slot->name[127] = 0;
        slot->record = FUN_002f8be0(self->table, descName(desc));
        if (slot->record == 0) { slot->record = FUN_002f8ca0(self->table, desc->alias); }
        if (slot->record == 0) {
            slot->record = FUN_002bfed0(Memory_GetAllocatorBySelector(DAT_00587018[0]));
            FUN_002f8a80(self->table, slot->record);
        }
        if (slot->record != desc) {
            { PoolDescRecord *d; char *src; src = desc->s24; d = slot->record; setDescString(&d->s24, src); }
            slot->record->a28 = desc->a28;
            slot->record->a32 = desc->a32;
            slot->record->a36 = desc->a36;
            { PoolDescRecord *d; char *src; src = desc->s40; d = slot->record; setDescString(&d->s40, src); }
            { PoolDescRecord *d; char *src; src = desc->s44; d = slot->record; setDescString(&d->s44, src); }
            { PoolDescRecord *d; char *src; src = desc->s48; d = slot->record; setDescString(&d->s48, src); }
            { PoolDescRecord *d; char *src; src = desc->s52; d = slot->record; setDescString(&d->s52, src); }
            { PoolDescRecord *d; char *src; src = desc->s56; d = slot->record; setDescString(&d->s56, src); }
            { PoolDescRecord *d; char *src; src = desc->s60; d = slot->record; setDescString(&d->s60, src); }
            { PoolDescRecord *d; char *src; src = desc->s64; d = slot->record; setDescString(&d->s64, src); }
            { PoolDescRecord *d; char *src; src = desc->s68; d = slot->record; setDescString(&d->s68, src); }
            { PoolDescRecord *d; char *src; src = desc->s72; d = slot->record; setDescString(&d->s72, src); }
            { PoolDescRecord *d; char *src; src = desc->s76; d = slot->record; setDescString(&d->s76, src); }
            slot->record->a80 = desc->a80;
        }
        if (build != 0) {
            if (self->build(index, 0).isFailed(fail)) { result.v = fail; }
        }
    } else {
        result = DAT_004fb418;
    }
    return result;
}
