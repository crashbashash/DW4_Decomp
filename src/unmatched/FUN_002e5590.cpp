extern "C" void *memset(void *, int, int);
extern "C" int DAT_004fb410[4];
class Mgr { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void *alloc(int, int); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void rel(void *); };
class Z { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void a(void *, int); };
class Q { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void b(void *, int, int); };
struct O {
 char p0[36]; unsigned char b36; char p1[28]; unsigned char b65; char p2[30]; int f96; int f100; Q *f104; char p3[4]; int f112; char p4[8]; int f124; int f128; int f132; int f136; int f140; int f144; int f148; int f152; int f156; char p5[8]; unsigned char b168; char p6[35]; Z *f204; char p7[4]; unsigned char b212; unsigned char b213; char p8[66]; Mgr *mgr;
};
extern "C" void FUN_002e5590(int *arg0, O *o) {
    int *t = (int *)o->mgr->alloc(48, 16);
    memset(t, 0, 48);
    t[0] = o->f124; t[1] = o->f112; t[2] = o->f132; t[3] = o->f128; t[4] = o->f148; t[5] = o->f144;
    t[6] = o->f156; t[7] = o->f152; t[8] = o->f140; t[9] = o->f136; t[10] = o->f96;
    int v = o->f100;
    if (o->b212) v |= 0x80000000;
    if (o->b213) v |= 0x40000000;
    if (o->b36) v |= 0x20000000;
    if (o->b65) v |= 0x10000000;
    t[11] = v;
    if (o->b168) o->f204->a(t, 12);
    o->f104->b(t, 4, 12);
    o->mgr->rel(t);
    *arg0 = DAT_004fb410[0];
}
