class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
extern "C" {
int FUN_002cd990();
int FUN_002cd9f0();
int FUN_002cda50();
void FUN_003065f0(int, int, int *, int *, int, int);
void FUN_00306e50(int, int, int *, unsigned char *, int, int);
void FUN_00307470(int, int, int *, int, int *, int, int);
void FUN_00307550(int, int, int *, int, int *, int, int);
void igObject_Destroy(void *);
int igObject_IsKindOf(void *, int);
}
extern int DAT_004c2228[4];
extern int DAT_004c2368[4];
extern int DAT_004c2370[4];
extern int DAT_004fa400[4];
extern int DAT_004fa420[4];
extern int DAT_004fa440[4];
extern int DAT_004fa460[4];
extern int DAT_004fa490[4];
extern int DAT_004fa4c0[4];
extern int DAT_004fa4f0[4];
extern int DAT_004fa510[4];
extern int DAT_00586a88[4];
extern int DAT_005871f8[4];
extern unsigned char GPR_00554994;
extern unsigned char GPR_00554c14;
class PoolConfigObject { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void finish(); virtual void p29(); virtual void p30(); virtual int inUse(); virtual igResult lock(int); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual igResult setName(int); int rc; char q8[184]; int options; };
struct PoolConfigContext { char p0[48]; PoolConfigObject *main; PoolConfigObject *second; int config; char p60[28]; PoolConfigObject *a88; char p92[4]; PoolConfigObject *a96; };
extern PoolConfigContext *DAT_00586dc8;
class PoolConfigManagerBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual PoolConfigObject *poolFor(int); virtual void p22(); virtual void setPool(int, PoolConfigObject *); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual igResult setDefault(int, int); virtual void p34(); virtual void p35(); virtual void setFlags(int); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual igResult readConfig(int, int); virtual void p47(); virtual igResult apply(); virtual igResult build(int, int); virtual void p50(); virtual void p51(); virtual void finish(); };
class PoolConfigManager : public PoolConfigManagerBase { public: char q4[8]; int flags; int defaultSize; PoolConfigObject *first; char q24[140]; PoolConfigObject *third; char q168[284]; PoolConfigObject *fallback; };
extern PoolConfigManager *DAT_00586fd0;
extern "C" {
PoolConfigObject *FUN_002cdab0(PoolConfigObject *);
void igArenaMemoryPool_SetPoolOptionFlags(PoolConfigObject *, int);
}
extern "C" void FUN_002f4a60(int *out, PoolConfigManager *self) {
    unsigned char useFlag;
    unsigned char lockFlag;
    unsigned char optFlag;
    int options;
    int optB;
    int optC;
    int mainSize;
    int nextSize;
    PoolConfigObject *mainPool;
    int i;
    int config;
    PoolConfigObject *o;
    int result;
    PoolConfigObject *second;
    int fail;
    config = DAT_00586dc8->config;
    mainPool = DAT_00586dc8->main;
    second = DAT_00586dc8->second;
    options = DAT_004c2370[0];
    mainSize = 0;
    nextSize = 0;
    optB = DAT_004c2368[0];
    optC = DAT_005871f8[0];
    {
    int f = self->flags;
    result = DAT_004fb410.v;
    lockFlag = GPR_00554994;
    useFlag = (f & 4) != 0;
    }
    FUN_003065f0(config, 2, DAT_004fa400, &mainSize, 0, 0);
    if (mainSize > 0) { mainPool->setName(mainSize); }
    FUN_00306e50(config, 2, DAT_004fa420, &lockFlag, lockFlag, 0);
    GPR_00554994 = lockFlag;
    FUN_00306e50(config, 2, DAT_004fa440, &useFlag, useFlag, 0);
    self->setFlags(useFlag != 0 ? self->flags | 4 : self->flags & ~4);
    FUN_00307550(config, 2, DAT_004fa460, FUN_002cd990(), &options, DAT_004c2370[0], 0);
    FUN_00307470(config, 2, DAT_004fa490, FUN_002cd9f0(), &optB, DAT_004c2368[0], 0);
    FUN_00307470(config, 2, DAT_004fa4c0, FUN_002cda50(), &optC, DAT_005871f8[0], 0);
    {
        int v = (options & 0x200) != 0;
        optFlag = v;
        FUN_00306e50(config, 2, DAT_004fa4f0, &optFlag, v, 0);
    }
    if (optFlag != 0) { options |= 0x200; }
    DAT_004c2370[0] = options;
    DAT_004c2368[0] = optB;
    DAT_005871f8[0] = optC;
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && igObject_IsKindOf(o, DAT_00586a88[0]) != 0) {
            igArenaMemoryPool_SetPoolOptionFlags(o, (options & ~1) | (o->options & 1));
        }
    }
    FUN_003065f0(config, 2, DAT_004fa510, &nextSize, 0, 0);
    PoolConfigManager *top = DAT_00586fd0;
    PoolConfigObject *fb = self->fallback;
    if (self == top && fb == mainPool) {
        PoolConfigObject *n = FUN_002cdab0(mainPool);
        if (nextSize > 0) { n->setName(nextSize); }
        n->finish();
        self->setPool(3, n);
        n->rc = n->rc - 1;
        if (((unsigned long long)((long long)(int)n->rc << 0x29) >> 0x29) == 0) igObject_Destroy(n);
    }
    if (self->readConfig(config, DAT_004c2228[0]).isFailed(fail)) { result = fail; }
    if (self->setDefault(self->defaultSize, 0).isFailed(fail)) { result = fail; }
    if (self->apply().isFailed(fail)) { result = fail; }
    if (GPR_00554c14 == 0) {
        for (i = 0; i < 46; i++) {
            if (i != 0) {
                PoolConfigObject **slot = (PoolConfigObject **)((char *)self + i * 144 + 20);
                PoolConfigObject *p = *slot;
                if (p == mainPool) {
                    p->rc = p->rc - 1;
                    if (((unsigned long long)((long long)(int)p->rc << 0x29) >> 0x29) == 0) igObject_Destroy(p);
                    *slot = 0;
                }
            }
        }
        for (i = 0; i < 46; i++) {
            if (i == 2) {
                self->setPool(i, self->third);
            } else {
                if (self->build(i, 0).isFailed(fail)) { result = fail; }
            }
        }
    } else {
        self->setPool(2, self->third);
    }
    self->finish();
    o = self->poolFor(20);
    if (o != mainPool && o != second) { DAT_00586dc8->a88 = o; }
    o = self->poolFor(7);
    if (o != mainPool && o != second) { DAT_00586dc8->a96 = o; }
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && o->inUse() == 0) { o->finish(); }
    }
    if (DAT_004c2370[0] & 8) {
        mainPool->lock(1);
        if (second != mainPool) { second->lock(1); }
    }
    if (result == DAT_004fb410.v) { self->setFlags(self->flags | 8); }
    *out = result;
}
