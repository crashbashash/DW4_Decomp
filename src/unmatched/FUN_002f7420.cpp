extern "C" {
int FUN_0030d080(int);
int FUN_0030d1d0(int, int);
int FUN_0030d4a0(int, int);
int *FUN_002ee430(int);
void *memset(void *, int, int);
int FUN_00304430(const int *, ...);
void FUN_00304680();
void qsort(void *, int, int, int (*)(const void *, const void *));
int FUN_002f7410(const void *, const void *);
int sprintf(char *, const int *, ...);
int FUN_002e1500(void *, int);
void igObject_Destroy(void *);
}
extern int DAT_004f95a0[4];
extern int DAT_004fa930[4];
extern int DAT_004fa988[4];
extern int DAT_004fa990[4];
extern int DAT_004fa9b0[4];
extern int DAT_004fa9d0[4];
enum LeakKind { LeakKindFirst = 0, LeakKindCount = 32 };
class LeakReportTracker { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void summary(int, int, int *, int *, int *, int *, int *, int *, int *, int *, int *, int, int, int *, int, int); virtual void describe(int, int, int, int *, int *, int *, int *);
  int rc; char q8[48]; int names; };
struct LeakReportContext { char p0[84]; LeakReportTracker *tracker; char p88[30]; unsigned char dumpLeaks; unsigned char dumpSummary; unsigned char dumpNames; };
extern LeakReportContext *DAT_00586dc8;
class LeakReportOwner { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void flush(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual int count(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void dump(); };
class LeakReportPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual LeakReportOwner *owner(); virtual void release(int); };
struct LeakReportSlot { char p0[20]; LeakReportPool *pool; char p24[120]; };
extern "C" void FUN_002f7420(LeakReportSlot *self) {
    int sizeA;
    int sizeB;
    int sizeC;
    int sizeD;
    int total;
    int f;
    int g;
    int h;
    int i2;
    int j2;
    int k2;
    int l2;
    int m2;
    char line[140];
    int counts[32];
    char type[80];
    LeakReportTracker *tracker = DAT_00586dc8->tracker;
    int i;
    if (tracker != 0) {
        if (DAT_00586dc8->dumpNames != 0) {
            int n;
            int names;
            int k;
            int it;
            int bytes;
            int *list;
            names = tracker->names;
            if (names != 0) {
                n = FUN_0030d080(names);
                bytes = n * 4;
                it = 0;
                list = FUN_002ee430(bytes);
                memset(list, 0, bytes);
                FUN_00304430(DAT_004fa930);
                FUN_00304680();
                for (k = 0; k < n; k++) {
                    if (it == -1) { break; }
                    list[k] = FUN_0030d1d0(names, it);
                    it = FUN_0030d4a0(names, it);
                }
                qsort(list, n, 4, FUN_002f7410);
                for (it = 0; it < n; it++) {
                    int name = list[it];
                    tracker->describe(0, -1, name, &sizeA, &sizeB, &sizeC, &sizeD);
                    sprintf(line, DAT_004fa988, name);
                    FUN_00304430(DAT_004fa990, line, sizeA, sizeB, sizeC, sizeD);
                    FUN_00304680();
                }
            }
        }
        if (DAT_00586dc8->dumpSummary != 0) {
            total = 0; f = 0; g = 0; h = 0; i2 = 0; j2 = 0; k2 = 0; l2 = 0; m2 = 0;
            tracker->summary(0, -1, &total, counts, &f, &g, &h, &i2, &j2, &k2, &l2, 1, 1, &m2, 2, -1);
            for (LeakKind t = LeakKindFirst; t < LeakKindCount; t = (LeakKind)(t + 1)) {
                int *c = &counts[t];
                if (*c != 0) {
                    sprintf(type, DAT_004f95a0, FUN_002e1500(tracker, t));
                    FUN_00304430(DAT_004fa9b0, type, *c);
                    FUN_00304680();
                }
            }
            FUN_00304430(DAT_004fa9d0, total, f, g, h, i2, l2, m2, j2, k2);
            FUN_00304680();
        }
    }
    for (i = 0; i < 46; i++) {
        LeakReportPool *p = self[i].pool;
        if (p != 0) {
            int j;
            int seen;
            LeakReportOwner *o;
            o = p->owner();
            seen = 0;
            if (o != 0) {
                for (j = 0; j < i; j++) {
                    LeakReportPool *q = self[j].pool;
                    if (q != 0 && q->owner() == o) { seen = 1; break; }
                }
                if (o != 0 && seen == 0) {
                    if (DAT_00586dc8->dumpLeaks != 0) {
                        if (o->count() > 0) { o->dump(); }
                    }
                    o->flush();
                }
            }
        }
    }
    {
        LeakReportTracker *t = DAT_00586dc8->tracker;
        if (t != 0) {
            t->rc = t->rc - 1;
            if (((unsigned long long)((long long)(int)t->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t);
            DAT_00586dc8->tracker = 0;
        }
    }
    for (int k = 0; k < 46; k++) {
        LeakReportPool *p = self[k].pool;
        if (p != 0 && p->owner() != 0) { p->release(0); }
    }
}
