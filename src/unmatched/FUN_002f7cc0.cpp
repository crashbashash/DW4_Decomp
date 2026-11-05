extern "C" int FUN_002dcc60(...);
class DW4VC_356_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86();  virtual int vX(); };
struct E { char pad[20]; DW4VC_356_0 *f20; char pad2[120]; };
extern "C" void FUN_002f7cc0(E *arg0, int arg1, int *arg2, int arg3);
void FUN_002f7cc0(E *arg0, int arg1, int *arg2, int arg3) {
    /* matching construct: variant search — decl order [8, 7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int w;
    DW4VC_356_0 *temp_a0_2;
    DW4VC_356_0 *temp_a0;
    int *var_s5;
    int var_s4;
    int var_s3;
    int var_s2;
    int var_s1;
    int temp_v0;

    var_s5 = arg2;
    var_s4 = arg3;
    for (var_s3 = 0; var_s3 < 0x2E; var_s3++) {
        temp_a0 = arg0[var_s3].f20;
        if (temp_a0 == 0) { continue; }
        temp_v0 = temp_a0->vX();
        var_s1 = 0;
        if (temp_v0 == 0) { continue; }
        for (var_s2 = 0; var_s2 < var_s3; var_s2++) {
            temp_a0_2 = arg0[var_s2].f20;
            if (temp_a0_2 != 0) {
                w = temp_a0_2->vX();
                if (w == temp_v0) { var_s1 = 1; break; }
            }
        }
        if (var_s1 == 0 && temp_v0 != 0) {
            if (var_s4 <= 0) { return; }
            *var_s5 = temp_v0 + 0x2328;
            var_s4 -= 1;
            var_s5 += 1;
            FUN_002dcc60(temp_v0, arg1);
        }
    }
}
