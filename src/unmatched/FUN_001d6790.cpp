extern "C" {
struct EE;
EE *FUN_002d7e90(...);
int igObject_IsKindOf(...);
extern int DAT_005611d0[4];
extern int DAT_005611d8[4];
extern int DAT_00585b70[4];
struct OO; struct AA;
void FUN_001d6790(OO *arg0, AA *arg1);
}
class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual long long vX(); };
class DW4VC_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual long long vX(); };
class DW4VC_260_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual long long vX(); };
struct OO { char pad[32]; long long f32; long long f40; };
struct AA { char pad[8]; unsigned int n; };
struct EE { char pad[24]; void *f24; };
void FUN_001d6790(OO *arg0, AA *arg1) {
    long long temp_v1;
    long long var_s0;
    long long temp_s1;
    unsigned int var_s2;
    unsigned int temp_s3;
    void *temp_s6;
    EE *temp_v0;

    arg0->f32 = 0;
    arg0->f40 = 0;
    temp_s3 = arg1->n;
    var_s2 = 0;
    while (var_s2 < temp_s3) {
        temp_v0 = FUN_002d7e90(arg1, var_s2);
        if (igObject_IsKindOf(temp_v0, DAT_00585b70[0]) != 0) {
            temp_s6 = temp_v0->f24;
            if (igObject_IsKindOf(temp_s6, DAT_005611d0[0]) != 0) {
                temp_s1 = ((DW4VC_124_0 *)(temp_s6))->vX();
                var_s0 = ((DW4VC_128_0 *)(temp_s6))->vX();
                if (igObject_IsKindOf(temp_s6, DAT_005611d8[0]) != 0) {
                    temp_v1 = temp_s1 + ((DW4VC_260_0 *)(temp_s6))->vX();
                    if (var_s0 < temp_v1) {
                        var_s0 = temp_v1;
                    }
                }
                if (temp_s1 < arg0->f32) {
                    arg0->f32 = temp_s1;
                }
                if (arg0->f40 < var_s0) {
                    arg0->f40 = var_s0;
                }
            }
        }
        var_s2++;
    }
}
