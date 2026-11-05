class Src { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int rd(int, int, int); };
struct Dst { char p0[24]; char *f24; int f28; };
struct Rd { char p0[104]; Src *f104; char p1[48]; int f156; char p2[96]; int f256; int f260; int f264; int f268; int f272; };
extern "C" int memcpy(...);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_35(Dst *arg0, Rd *arg1) {
    int s6;
    int s8;
    char *s7;
    int s4;
    int s3;
    int s2;
    int s1;
    int base;
    int s0;
    int t;
    s6 = 0;
    s8 = arg0->f28;
    s7 = arg0->f24;
    s4 = arg1->f260;
    s3 = arg1->f256;
    s2 = arg1->f268;
    s1 = arg1->f272;
    base = arg1->f264;
    while (s6 < s8) {
        if (s1 == 0) {
            t = arg1->f156;
            if (t < s4 + s2) {
                s4 = t - s2;
            }
            s2 += s4 * arg1->f104->rd(base, s4, 1);
            s1 = s4;
        }
        s0 = s8 - s6;
        s0 = s0 < s1 ? s0 : s1;
        memcpy(s7, base + s3, s0);
        s7 += s0;
        s1 -= s0;
        s6 += s0;
        s3 = (s3 + s0) % s4;
    }
    t = s3;
    if (s4 > 0) {
        s3 = ((s3 + 3) & ~3) % s4;
    }
    s1 = s1 - (s3 - t);
    if (s3 < t) s1 = 0;
    arg1->f260 = s4;
    arg1->f256 = s3;
    arg1->f268 = s2;
    arg1->f272 = s1;
}
