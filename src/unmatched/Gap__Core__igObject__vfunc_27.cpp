struct X { char pad[46]; unsigned char f46; };
struct L { char pad0[8]; int f8; char padC[4]; void **f16; };
struct Item { char pad[24]; L *f24; };
struct L2 { char pad0[8]; int f8; char padC[4]; Item **f16; };
class Self { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void v31(void *); char p4[12]; X *f16; char p20[4]; L2 *f24; unsigned char f28; };
extern "C" {
int FUN_003a0540(...);
void Gap__Core__igObject__vfunc_27(Self *arg0) {
    int temp_s5;
    int var_s4;
    int temp_s3;
    int var_s2;
    L *temp_s7;
    if (FUN_003a0540(arg0->f16) != 0 && arg0->f28 != 0 && arg0->f16->f46 == 0) {
        temp_s5 = arg0->f24->f8;
        for (var_s4 = 0; var_s4 < temp_s5; var_s4++) {
            temp_s7 = arg0->f24->f16[var_s4]->f24;
            temp_s3 = temp_s7->f8;
            for (var_s2 = 0; var_s2 < temp_s3; var_s2++) {
                arg0->v31(temp_s7->f16[var_s2]);
            }
        }
    }
}
}
