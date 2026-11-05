extern "C" {
int AddIntcHandler(int, int (*)(), int);
int FUN_002651d0();
int FUN_0010b9c0(int);
int FUN_0010ba28(int);
int FUN_0010d940(int);
int FUN_001120e8();
int FUN_00116fb0(int);
int FUN_00117a90(int);
int FUN_00118fe0();
int FUN_00119138(...);
int memset(void *, int, int);
int sprintf(...);
int FUN_0026ac50(int);
int FUN_0026ad50(int *);
int FUN_0026b008(int *);
int FUN_0026b120(int *);
int FUN_0026b1f0(int);
int FUN_00280b98(struct Q *);
int FUN_002ed2b0(int, int, int);
int FUN_0032cf50(...);
int Memory_GetAllocatorByName(int *);
int igStrCmp(int *, int *);
extern int DAT_004ffe68[4];
extern int DAT_004ffe70[4];
extern int DAT_004ffe80[4];
extern int DAT_004ffe90[4];
extern int DAT_004ffea0[4];
extern int DAT_004ffeb0[4];
extern int DAT_004ffee0[4];
extern int DAT_004fff10[4];
extern int DAT_004fff28[4];
extern int DAT_004fff40[4];
extern char DAT_004fff60[16];
extern int DAT_00587390[4];
extern int DAT_005873a0[4];
extern int DAT_005873a4[4];
extern int DAT_005873a8[4];
extern int DAT_005873ac[4];
extern int DAT_005873b0[4];
extern int DAT_005873b4[4];
extern int DAT_005873b8[4];
extern int DAT_005873bc[4];
extern int DAT_005873c0[4];
extern int DAT_005873c8[4];
extern char DAT_005873d0[16];
extern char DAT_005874d0[16];
extern char GPR_005549b8;
extern unsigned char GPR_00554de4;
extern unsigned char GPR_00554de8;

struct Q { int a; int b; int c; int d; };
int FUN_00332860(void) {
    int sp23C;
    int sp238;
    int sp234;
    char sp30[512];
    struct Q sp20;
    int temp_s0;

    if (GPR_00554de8 != 0) {
        return 1;
    }
    FUN_0010d940(0);
    FUN_001120e8();
    FUN_00116fb0(0);
    switch (DAT_005873c8[0]) {
    case 1:
        FUN_00117a90(1);
        break;
    case 2:
        FUN_00117a90(2);
        break;
    }
    GPR_005549b8 = 0;
    FUN_0032cf50(&sp23C, &DAT_004ffe70[0], 1, 0, 0);
    FUN_00118fe0();
    FUN_00119138(1, 0x8000, 0);
    FUN_00119138(1, 0x8010, 0x980, 0x3FFF);
    FUN_00119138(1, 0x8010, 0xA80, 0x3FFF);
    FUN_00119138(1, 0x8010, 0x981, 0x3FFF);
    FUN_00119138(1, 0x8010, 0xA81, 0x3FFF);
    if (DAT_005873d0[0] != 0) {
        sprintf(sp30, &DAT_004ffe80[0], &DAT_005873d0[0]);
    } else if (igStrCmp(&DAT_004ffe90[0], &DAT_004ffea0[0]) == 0) {
        sprintf(sp30, &DAT_004ffeb0[0]);
    } else {
        sprintf(sp30, &DAT_004ffee0[0]);
    }
    FUN_0032cf50(&sp238, sp30, 0, 0x13, &DAT_004fff10[0]);
    if (DAT_005873d0[0] != 0) {
        sprintf(sp30, &DAT_004fff28[0], &DAT_005873d0[0]);
    } else {
        sprintf(sp30, &DAT_004fff40[0]);
    }
    FUN_0032cf50(&sp234, sp30, 0, 0, 0);
    memset(&sp20, 0, 0x10);
    sp20.a = 0x30000;
    sp20.b = 0;
    sp20.c = 0;
    sp20.d = 0;
    FUN_00280b98(&sp20);
    FUN_0026b1f0(0);
    if (DAT_005874d0[0] != 0) {
        memset(&DAT_00587390[0], 0, 0x10);
        DAT_00587390[0] = (int)&DAT_005874d0[0];
        FUN_0026b008(&DAT_00587390[0]);
    } else {
        FUN_0026b008(0);
    }
    temp_s0 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    if (GPR_00554de4 != 0) {
        memset(&DAT_005873a0[0], 0, 0x10);
        DAT_005873a0[0] = (int)&DAT_004fff60[0];
        DAT_005873a4[0] = 0x20;
        DAT_005873ac[0] = ((DAT_005873a4[0] + 1) * 0xD) + 0x68;
        DAT_005873a8[0] = FUN_002ed2b0(DAT_005873ac[0], 0x10, temp_s0);
        FUN_0026b120(&DAT_005873a0[0]);
    }
    if (DAT_005873c8[0] != 0) {
        FUN_0026ac50(0);
        if (GPR_00554de4 != 0) {
            memset(&DAT_005873b0[0], 0, 0x10);
            DAT_005873b0[0] = (int)&DAT_004fff60[0];
            DAT_005873b4[0] = 0x20;
            DAT_005873bc[0] = ((DAT_005873b4[0] + 1) * 0xD) + 0x68;
            DAT_005873b8[0] = FUN_002ed2b0(DAT_005873bc[0], 0x10, temp_s0);
            FUN_0026ad50(&DAT_005873b0[0]);
        }
    }
    FUN_0010b9c0(2);
    DAT_005873c0[0] = AddIntcHandler(2, &FUN_002651d0, 0);
    FUN_0010ba28(2);
    GPR_00554de8 = 1;
    return 1;
}
}
