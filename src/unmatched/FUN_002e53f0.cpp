extern "C" {
int igObject_GetSerializedSize(...);
int igObject_WritePersistentFields(int, int, int, int, unsigned char);
extern int DAT_004fb410[4];
void FUN_002e53f0(int *arg0, void *arg1);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(int, int); };
struct O {
    char pad0[8];
    int f8;
    char pad1[4];
    int *f16;
    char pad2[92];
    int f112;
    char pad3[8];
    int f124;
    char pad4[40];
    unsigned char f168;
    char pad5[7];
    int f176;
    char pad6[12];
    int f192;
    char pad7[84];
    VC *f280;
};
void FUN_002e53f0(int *arg0, void *arg1) {
    O *o = (O *)arg1;
    int var_s0;
    int var_s1;
    o->f124 = 0;
    var_s0 = 0;
    o->f112 = o->f8;
    while (var_s0 < o->f112) {
        o->f124 = o->f124 + igObject_GetSerializedSize(o->f16[var_s0]);
        var_s0 += 1;
    }
    o->f176 = o->f280->v220(o->f124, 16);
    var_s1 = o->f176;
    var_s0 = 0;
    while (var_s0 < o->f112) {
        var_s1 += igObject_WritePersistentFields(o->f16[var_s0], var_s1, 0, o->f192, o->f168);
        var_s0 += 1;
    }
    *arg0 = DAT_004fb410[0];
}
