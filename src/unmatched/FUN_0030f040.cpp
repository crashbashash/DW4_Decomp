extern "C" {
extern int DAT_004c2368[4];
int FUN_002dcc50(...);
int igReportNotice(...);
extern int DAT_004c2310[4];
extern int DAT_004c2330[4];
extern int DAT_004c2338[4];
extern int DAT_004c2340[4];
extern int DAT_004c2348[4];
extern int DAT_004c2350[4];
extern int DAT_004c2358[4];
extern int DAT_004fb480[4];
extern int DAT_005871e0[4];
extern int DAT_005871e8[4];
extern int (*DAT_005871f0[4])(void *, int, int, int, int, int, int);
extern unsigned char GPR_00554c34;
}
class O30F { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual int v87();
  int pad4[44]; int f180; };
extern "C" void FUN_0030f040(O30F *arg0, int arg1, int arg2, int arg3) {
    int temp_v0;
    int temp_v0_2;
    int var_s1;
    int var_s0;

    if ((DAT_005871e8[0] != 0) && (var_s1 = 0, var_s0 = -1, ((DAT_004c2330[0] & arg1) != 0))) {
        if (DAT_004c2338[0] == arg0->f180) {
            var_s1 |= 1;
        }
        if (arg2 == DAT_004c2340[0]) {
            var_s1 |= 2;
        }
        if (arg3 == DAT_004c2348[0]) {
            var_s1 |= 4;
        }
        if (DAT_005871e0[0] == DAT_004c2350[0]) {
            var_s1 |= 8;
        }
        if (DAT_004c2358[0] != -1) {
            temp_v0 = arg0->v87();
            if (temp_v0 != 0) {
                var_s0 = FUN_002dcc50(temp_v0);
                if (var_s0 == DAT_004c2358[0]) {
                    var_s1 |= 0x10;
                }
            }
        }
        if ((var_s1 != 0) && (DAT_005871e8[0] == (DAT_005871e8[0] & var_s1))) {
            if (DAT_005871f0[0] != 0) {
                DAT_005871f0[0](arg0, arg1, arg2, arg3, DAT_005871e0[0], var_s0, var_s1);
                return;
            }
            if ((DAT_004c2368[0] < 4) && (GPR_00554c34 == 0)) {
                temp_v0_2 = igReportNotice(&DAT_004fb480[0], DAT_004c2310[arg1], arg2, arg3, DAT_005871e0[0], var_s0, var_s1);
                if ((temp_v0_2 != 1) && (temp_v0_2 == 2)) {
                    GPR_00554c34 = 1;
                }
            }
        }
    }
}
