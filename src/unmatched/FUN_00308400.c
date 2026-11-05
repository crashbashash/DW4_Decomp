int FUN_00304430();
int FUN_00304550();
int FUN_00304680();
int FUN_003046d0();
extern int DAT_004c22d8[4];
extern int DAT_004fb2a0[4];
extern int DAT_004fb2a8[4];
extern int DAT_004fb2b8[4];
extern int DAT_004fb2c0[4];
extern int DAT_004fb2c8[4];
extern int DAT_004fb2d8[4];
extern int DAT_004fb2e0[4];
extern int DAT_004fb2e8[4];
extern int DAT_004fb2f0[4];
extern int DAT_004fb300[4];
extern unsigned char GPR_005549b0;

int FUN_00308400(int arg0, int arg1) {
    int *p;
    if (DAT_004c22d8[0] < arg0) {
        return 0;
    }
    p = &DAT_004fb2a0[0];
    switch (arg0) {
    case 0: p = &DAT_004fb2a8[0]; break;
    case 1: p = &DAT_004fb2b8[0]; break;
    case 2: p = &DAT_004fb2c0[0]; break;
    case 3: p = &DAT_004fb2c8[0]; break;
    case 4: p = &DAT_004fb2d8[0]; break;
    case 5: p = &DAT_004fb2e0[0]; break;
    case 6: p = &DAT_004fb2e8[0]; break;
    }
    if (arg0 < 4) {
        FUN_00304550(&DAT_004fb2f0[0], p, arg1);
        FUN_003046d0();
    } else {
        FUN_00304430(&DAT_004fb2f0[0], p, arg1);
        FUN_00304680();
        return 0;
    }
    FUN_00304550(&DAT_004fb300[0]);
    FUN_003046d0();
    if (GPR_005549b0 != 0) {
        if (arg0 == 0 || arg0 == 1) return 1;
    }
    return 0;
}
