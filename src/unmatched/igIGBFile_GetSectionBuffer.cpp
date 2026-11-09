class P { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vB(int, unsigned short); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void vA(int); };
struct Inf { char p0[28]; int f28; char p1[4]; unsigned short f36; };
struct S { char p0[104]; Inf *f104; char p1[56]; int f164; char p2[92]; int f260; int f264; char p3[12]; P *f280; };
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void igIGBFile_GetSectionBuffer(int *arg0, S *arg1, int arg2);
void igIGBFile_GetSectionBuffer(int *arg0, S *arg1, int arg2) {
    int a1;
    a1 = arg1->f264;
    if (a1 != 0 && arg1->f260 >= arg2) {
        *arg0 = DAT_004fb410[0];
    } else {
        if (a1 != 0) {
            arg1->f280->vA(a1);
        }
        arg1->f260 = arg1->f164;
        if (arg1->f260 < 0) {
            arg1->f260 = arg1->f104->f28;
        }
        if (arg1->f260 < arg2) {
            arg1->f260 = arg2;
        }
        arg1->f260 = (arg1->f260 + 3) & ~3;
        arg1->f264 = arg1->f280->vB(arg1->f260, arg1->f104->f36);
        if (arg1->f264 == 0) {
            *arg0 = DAT_004fb418[0];
        } else {
            *arg0 = DAT_004fb410[0];
        }
    }
}
}
