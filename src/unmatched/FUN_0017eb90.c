typedef struct B { char p0[944]; struct C *f944; struct D *f948; } B;
struct C { char p[12]; int f12; };
struct D { char p[8]; int *f8; };
int FUN_0017df40(B *, int, int, int *, int *, int *, int *);
int FUN_0017e590(B *, int, int, int *, int *);
int FUN_0017e980(B *, int, int);
int FUN_001e74b0(int);
int FUN_001e7500(int);
int FUN_001e7560(int);
int FUN_001f10c0(int, int);
int FUN_001f10f0(int, int, int, int);
int FUN_001f1120(int);
int FUN_001f14b0(int);
int FUN_001f1850(int);
int FUN_001f1c00(int);
int FUN_001f1fe0(int);
int FUN_001f23a0(int);
int FUN_001f2730(int, int *);
int FUN_001f2d90(int, int);
int FUN_001f3160(int, int);
int FUN_001f3550(int, int);
int FUN_001f3900(int);
int FUN_001f3d00(int, int);

void FUN_0017eb90(B *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int spBC;
    int spB8;
    int spB4;
    int spB0;
    int spAC;
    int spA8;
    int *var_s3;
    int var_s0;
    int var_s0_2;
    int var_s1;
    int var_s6;
    int temp_s7;
    struct C *c;

    c = arg0->f944;
    var_s1 = arg4;
    if (c != 0) {
        var_s0 = c->f12;
    } else {
        var_s0 = 0;
    }
    temp_s7 = FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4) & 0xFF;
    FUN_0017e980(arg0, arg1, var_s1);
    if ((temp_s7 != 0) || (arg6 != 0)) {
        FUN_001e74b0(0x1B);
    } else if (FUN_001e7560(0x1B) != 0) {
        FUN_001e7500(0x1B);
    }
    switch (arg2) {
    case 0x0:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        FUN_001f1120(arg3);
        break;
    case 0x1:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        FUN_001f14b0(arg3);
        break;
    case 0x2:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        FUN_001f1850(arg3);
        break;
    case 0x3:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f1c00(arg3);
        } else {
            FUN_001f3160(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x4:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f1fe0(arg3);
        } else {
            FUN_001f2d90(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x5:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f23a0(arg3);
        } else {
            FUN_001f3550(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x1000:
        if ((FUN_0017e590(arg0, arg1, var_s1, &spA8, &spB0) != 0) && (temp_s7 == 0)) {
            FUN_001e74b0(0x1B);
        }
        FUN_001f10c0(1, spB0);
        FUN_001f10f0(spBC, spA8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f3900(arg3);
        } else {
            FUN_001f3d00(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x2000:
        var_s3 = arg0->f948->f8 + arg5;
        for (var_s0_2 = 0; var_s0_2 < arg3; var_s0_2++) {
            FUN_001f10f0(spBC, spB8, spAC, spB4);
            FUN_001f1850(*var_s3);
            var_s1 += *var_s3;
            var_s3 += 1;
            FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
            FUN_0017e980(arg0, arg1, var_s1);
        }
        break;
    case 0x2002:
        var_s3 = arg0->f948->f8 + arg5;
        for (var_s6 = 0; var_s6 < arg3; var_s6++) {
            FUN_001f10f0(spBC, spB8, spAC, spB4);
            if (var_s0 == 0) {
                FUN_001f23a0(*var_s3);
            } else {
                FUN_001f3550(*var_s3, var_s0 + (var_s1 * 2));
            }
            var_s1 += *var_s3;
            var_s3 += 1;
            FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
            FUN_0017e980(arg0, arg1, var_s1);
        }
        break;
    case 0x2001:
        var_s3 = arg0->f948->f8 + arg5;
        if (var_s0 == 0) {
            FUN_001f10f0(spBC, spB8, spAC, spB4);
            FUN_001f2730(arg3, var_s3);
        } else {
            for (var_s6 = 0; var_s6 < arg3; var_s6++) {
                FUN_001f10f0(spBC, spB8, spAC, spB4);
                FUN_001f2d90(*var_s3, var_s0 + (var_s1 * 2));
                var_s1 += *var_s3;
                var_s3 += 1;
                FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
                FUN_0017e980(arg0, arg1, var_s1);
            }
        }
        break;
    }
}
