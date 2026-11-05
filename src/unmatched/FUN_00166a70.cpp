extern "C" {
int sprintf(...);
int FUN_00230298(float);
int FUN_00304430(...);
int FUN_00304680(...);
extern float DAT_0048a470[4];
extern int DAT_004df110[4];
extern int DAT_004df130[4];
extern float DAT_005607a0[4];
extern float DAT_005607a8[4];
extern int DAT_005607b0[4];
extern float DAT_005607b8[4];
extern float DAT_005607c0[4];
extern int DAT_005607d0[4];
extern float DAT_00560838[4];
void FUN_00166a70(void *arg0, float fparg0, float fparg1);
}
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual void vX(int, int, int *); char pad[57]; unsigned char f61; };
void FUN_00166a70(void *arg0_, float fparg0, float fparg1) {
    C *arg0 = (C *)arg0_;
    float temp_f4;
    int temp_s2;
    int temp_s1;

    DAT_005607a0[0] += fparg0;
    DAT_005607a8[0] += fparg1;
    DAT_005607b0[0] += 1;
    if (fparg0 < DAT_0048a470[0]) {
        DAT_0048a470[0] = fparg0;
    }
    if (!(fparg0 <= DAT_00560838[0])) {
        DAT_00560838[0] = fparg0;
    }
    if (!(DAT_005607a0[0] < 1.5f)) {
        temp_f4 = (float) DAT_005607b0[0];
        DAT_005607b8[0] = temp_f4 / DAT_005607a0[0];
        DAT_005607c0[0] = (1000.0f * DAT_005607a8[0]) / temp_f4;
        temp_s2 = FUN_00230298(1.0f / DAT_00560838[0]);
        temp_s1 = FUN_00230298(1.0f / DAT_0048a470[0]);
        sprintf(&DAT_005607d0[0], &DAT_004df110[0], temp_s2, temp_s1, FUN_00230298(DAT_005607b8[0]));
        DAT_005607a0[0] = 0.0f;
        DAT_005607a8[0] = 0.0f;
        DAT_005607b0[0] = 0;
        DAT_00560838[0] = 0.0f;
        DAT_0048a470[0] = (float) 0xF4240;
    }
    if (arg0->f61 != 0) {
        if (DAT_005607b0[0] == 0) {
            FUN_00304430(&DAT_004df130[0], &DAT_005607d0[0]);
            FUN_00304680();
        }
    } else {
        arg0->vX(0, 0, &DAT_005607d0[0]);
    }
}
