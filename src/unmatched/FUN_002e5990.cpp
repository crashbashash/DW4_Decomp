extern "C" int igObject_Destroy(void *);
extern "C" int DAT_004fb410[4];
class Mgr { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void rel(int); };
struct Rc { int p; int f4; };
struct T {
    char pad0[120]; int f120; char pad1[48]; int f172; int f176; int f180; int f184; char pad2[48]; int f236;
    char pad3[40]; Mgr *mgr; char pad4[12]; int f296; int f300; Rc *f304;
};
extern "C" void FUN_002e5990(int *arg0, T *o) {
    o->mgr->rel(o->f172); o->f172 = 0;
    o->mgr->rel(o->f176); o->f176 = 0;
    o->mgr->rel(o->f180); o->f180 = 0;
    o->mgr->rel(o->f184); o->f184 = 0;
    o->mgr->rel(o->f236); o->f236 = 0;
    if (o->f120) o->mgr->rel(o->f120);
    o->f296 = 0;
    if (o->f300) { o->mgr->rel(o->f300); o->f300 = 0; }
    Rc *r = o->f304;
    if (r) { r->f4 -= 1; if ((r->f4 & 0x7fffff) == 0) igObject_Destroy(r); }
    o->f304 = 0;
    *arg0 = DAT_004fb410[0];
}
