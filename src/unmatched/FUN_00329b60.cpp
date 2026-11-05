class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void vX(); };
extern "C" {
extern char DAT_004ff5c8[];
int sprintf(...);
int strcpy(...);
int FUN_00304430(...);
int FUN_00304680(...);
int FUN_0032ac70(...);
extern int DAT_004f95c8[4];
extern int DAT_004ff5c0[4];
extern int DAT_00587220[4];
void FUN_00329b60(V *arg0);
}
void FUN_00329b60(V *arg0) {
    char sp80[256];
    unsigned int var_s4;
    unsigned int var_s3;
    int var_s2;
    int temp_s1;
    int var_s0;

    var_s4 = 0;
    do {
        temp_s1 = DAT_00587220[var_s4];
        if (temp_s1 != 0) {
            var_s2 = 0;
            var_s3 = 0;
            do {
                var_s0 = var_s3 & 0x3F;
                if (var_s0 == 0) {
                    sprintf(sp80, &DAT_004ff5c0[0], (var_s4 << 0x1A) + (var_s3 << 0xC));
                    var_s2 = 0xB;
                }
                sp80[var_s2] = (char) (FUN_0032ac70(temp_s1, var_s3) + 0x30);
                var_s2 += 1;
                if (var_s0 == 0x3F) {
                    strcpy(sp80 + var_s2, &DAT_004f95c8[0]);
                    FUN_00304430(sp80);
                    FUN_00304680();
                    var_s2 = 0;
                }
                var_s3 += 1;
            } while (var_s3 < 0x4000U);
        } else {
            FUN_00304430(&DAT_004ff5c8[0], var_s4 << 0x1A);
            FUN_00304680();
        }
        var_s4 += 1;
    } while (var_s4 < 0x40U);
    arg0->vX();
}