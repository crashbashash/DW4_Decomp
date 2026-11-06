extern "C" {
int FUN_0020d360(int);
int ReferThreadStatus(int, int);
extern int DAT_004fb410[4];
}
struct SR { int w; };
class VC1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual SR vX(int); };
class VC2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual SR vX(); };

struct T { char p0[48]; void *f48; char p1[8]; int f60; };
extern "C" {
void Gap__Core__igPsx2Thread__vfunc_24(int *arg0, void *arg1, T *arg2);
void Gap__Core__igPsx2Thread__vfunc_24(int *arg0, void *arg1, T *arg2) {
    SR sp3C;
    SR sp38;
    sp3C = ((VC1 *)arg2->f48)->vX(1);
    sp38 = ((VC2 *)arg2->f48)->vX();
    if (arg2->f60 != -1) {
        while (ReferThreadStatus(arg2->f60, 0) != 0x10) {
            FUN_0020d360(1);
        }
    }
    *arg0 = DAT_004fb410[0];
}
}
