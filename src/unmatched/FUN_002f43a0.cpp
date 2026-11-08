extern char *DAT_00586de8;
extern int DAT_004f8b50[4];
extern int DAT_004f8c80[4];
extern int DAT_00586fd8[4];
extern int DAT_00586fe0[4];
extern int DAT_00586fe8[4];
extern int DAT_00586ff0[4];
extern unsigned char GPR_00554c14;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
class PoolObjectBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void finish(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual igResult setName(int); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual void p87(); virtual void p88(); virtual void p89(); virtual void p90(); virtual void p91(); virtual void p92(); virtual void p93(); virtual void p94(); virtual void prepare(); };
class PoolObject : public PoolObjectBase { public: int rc; };
struct PoolContext { char p0[48]; PoolObject *main; PoolObject *second; };
extern PoolContext *DAT_00586dc8;
extern "C" {
igResult FUN_002f86e0(void *);
void *FUN_002f0040(int, int, int);
int Memory_GetDefaultAllocator();
PoolObject *FUN_0031eb90(void *);
PoolObject *FUN_003235c0(void *);
int strcmp(char *, int *);
void Memory_InitializeAllocatorRegistries(PoolObject *);
void FUN_002f0370(PoolObject *);
}
struct PoolSlot { char p0[144]; };
struct PoolSlotTable { char p0[20]; PoolObject *first; };
static inline PoolObject *newLargePool() {
    void *p = FUN_002f0040(0xd0, 0, Memory_GetDefaultAllocator());
    if (p != 0) { p = FUN_0031eb90(p); }
    return (PoolObject *)p;
}
static inline PoolObject *newSmallPool() {
    void *p = FUN_002f0040(0xa0, 0, Memory_GetDefaultAllocator());
    if (p != 0) { p = FUN_003235c0(p); }
    return (PoolObject *)p;
}
#define NEW_LARGE_POOL(p) { p = newLargePool(); }
#define NEW_SMALL(p) { p = newSmallPool(); }
#define NEW_POOL(p) { if (DAT_00586de8 != 0) { if (strcmp(DAT_00586de8, DAT_004f8b50) == 0) { NEW_LARGE_POOL(p) } else if (strcmp(DAT_00586de8, DAT_004f8c80) == 0) { NEW_SMALL(p) } else { NEW_LARGE_POOL(p) } } else { NEW_LARGE_POOL(p) } }
extern "C" void FUN_002f43a0(PoolSlotTable *self) {
    PoolObject *p;
    int i;
    FUN_002f86e0(self);
    i = 0;
    do {
        switch (i) {
        case 0:
            NEW_POOL(p)
            break;
        case 4: case 5: case 6:
            if (GPR_00554c14 != 0) { p = self->first; } else { NEW_POOL(p) }
            break;
        default:
            p = self->first;
            break;
        }
        *(PoolObject **)((char *)self + i * 144 + 20) = p;
        if (GPR_00554c14 != 0) {
            switch (i) {
            case 0:
                p->prepare();
                if (DAT_00586fd8[0] != 0) { p->setName(DAT_00586fd8[0]); }
                p->finish();
                DAT_00586dc8->main = p;
                Memory_InitializeAllocatorRegistries(p);
                break;
            case 4:
                DAT_00586dc8->second = p;
                break;
            }
        } else {
            switch (i) {
            case 0:
                p->prepare();
                if (DAT_00586fd8[0] != 0) { p->setName(DAT_00586fd8[0]); }
                p->finish();
                DAT_00586dc8->main = p;
                Memory_InitializeAllocatorRegistries(p);
                break;
            case 4:
                DAT_00586dc8->second = p;
                p->prepare();
                if (DAT_00586fe0[0] != 0) { p->setName(DAT_00586fe0[0]); }
                FUN_002f0370(p);
                p->finish();
                break;
            case 5:
                p->prepare();
                if (DAT_00586fe8[0] != 0) { p->setName(DAT_00586fe8[0]); }
                FUN_002f0370(p);
                p->finish();
                break;
            case 6:
                p->prepare();
                if (DAT_00586ff0[0] != 0) { p->setName(DAT_00586ff0[0]); }
                FUN_002f0370(p);
                p->finish();
                break;
            }
        }
        i++;
        p->rc = p->rc + 1;
    } while (i < 46);
}
