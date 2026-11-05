struct S { char p0[12]; unsigned f12; char p1[32]; int f48; unsigned char *f52; char p2[20]; int f76; };
extern "C" {
int FUN_00158480(...);
int Memory_FreeBuffer(...);
void **Memory_GetAllocatorBySelector(...);
void **igObject_GetAllocator(...);
extern unsigned char GPR_00554c14;
extern int DAT_005870e8[4];
void FUN_0015a100(S *arg0);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual unsigned char *vX(int, int); };
void FUN_0015a100(S *arg0) {
    int n;
    int j;
    unsigned i;
    unsigned char *src;
    unsigned char *dst;
    unsigned char *buf;
    A *al;
    int v = arg0->f76;
    if (v > 0) {
        n = v;
    } else {
        n = (unsigned)arg0->f48 / arg0->f12;
    }
    FUN_00158480(arg0);
    if (arg0->f52 != 0 && n != arg0->f76) {
        al = (A *)igObject_GetAllocator(arg0);
        al = (GPR_00554c14 != 0) ? al : (A *)Memory_GetAllocatorBySelector(DAT_005870e8[0]);
        buf = al->vX(arg0->f48, 0x80);
        src = arg0->f52;
        dst = buf;
        for (i = 0; i < arg0->f12; i++) {
            for (j = 0; j < n; j++) {
                *dst = *src;
                src++;
                dst++;
            }
            dst += arg0->f76 - n;
        }
        Memory_FreeBuffer(arg0->f52);
        arg0->f52 = buf;
    }
}
