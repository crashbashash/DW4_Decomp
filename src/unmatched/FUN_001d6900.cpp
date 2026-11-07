extern "C" {
void *FUN_00137810(...);
int FUN_002f8a20(...);
int igObject_Destroy(...);

}
struct DW4SR4 { int w0; };
class DW4VC_116_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int); };
class DW4VC_156_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(int, int, int); };
class DW4VCSR_128_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(DW4SR4 *, int, int, int); };

struct Rf { int w0; int references; };
extern "C" int FUN_001d6900(Rf **arg0) {
    float v[18];
    Rf * volatile op;
    DW4SR4 r;
    int i;
    op = (Rf *)FUN_00137810(FUN_002f8a20());
    r.w0 = 0;
    r.w0 = 1 | r.w0;
    ((DW4VCSR_128_3 *)op)->vX(&r, 6, 0, 0);
    ((DW4VC_156_3 *)op)->vX(3, 2, 0);
    v[2] = 0.0f;
    v[0] = -1.0f;
    i = 0;
    v[1] = -1.0f;
    v[3] = 1.0f;
    v[4] = -1.0f;
    v[5] = 0.0f;
    v[6] = -1.0f;
    v[7] = 1.0f;
    v[8] = 0.0f;
    v[9] = 1.0f;
    v[10] = 1.0f;
    v[11] = 0.0f;
    v[12] = -1.0f;
    v[16] = -1.0f;
    v[13] = 1.0f;
    v[14] = 0.0f;
    v[15] = 1.0f;
    v[17] = 0.0f;
    do {
        ((DW4VC_116_2 *)(*(void ***)((char *)op + 12)))->vX(i, (int)&v[i * 3]);
        i += 1;
    } while (i < 6);
    *arg0 = op;
    Rf *t = *arg0;
    if (t) {
        t->references = t->references + 1;
    }
    Rf *u = op;
    if (u) {
        u->references = u->references - 1;
        if (((unsigned long long)(long long)u->references & 0x7fffffULL) == 0)
            igObject_Destroy(u);
    }
    return 0;
}
