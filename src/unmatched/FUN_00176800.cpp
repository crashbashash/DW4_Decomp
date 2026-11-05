extern "C" {
int FUN_001f7340(...);
int FUN_001f7360(...);
int Gap__Core__igPrimLengthArray1_1__vfunc_60(...);
extern int DAT_004df6b0[4];
void FUN_00176800(int *arg0, int arg1, int arg2);
}
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void vX(int,int,int); };
void FUN_00176800(int *arg0, int arg1, int arg2) {
    int *p;
    int *q;
    int s3, a1, a0_3, s3_2;
    if (!(((int *)arg0[6])[5] & 0x10)) {
        Gap__Core__igPrimLengthArray1_1__vfunc_60(arg0);
        return;
    }
    p = ((VA *)arg0[6])->vX();
    s3 = ((unsigned int)(*p & 0xF0000) >> 0x10) & 0xFF;
    q = ((VA *)arg0[6])->vX();
    a1 = *q;
    a0_3 = ((unsigned int)(a1 & 0x300000) >> 0x14) & 0xFF;
    s3_2 = DAT_004df6b0[a0_3 | (((s3 & 0xFF) == 2) * 4)];
    if (s3_2 != FUN_001f7360(a0_3, a1)) {
        FUN_001f7340(s3_2);
    }
    ((VB *)arg0[98])->vX(0x1000, arg1, arg2);
}
