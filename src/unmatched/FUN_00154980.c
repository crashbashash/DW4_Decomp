struct S { char pad[8]; int f8; int f12; int f16; int f20; int f24; };
int memcpy();
int memset();
int FUN_00154b80();
int FUN_00154e40();
int FUN_00300db0();
int FUN_00300f50();
int FUN_00154980(struct S *arg0, int arg1, int arg2, int arg3) {
    int sp5C;
    int sp58;
    if (arg3 != 0 && arg0->f20 == arg3 && arg1 == arg0->f8 && arg1 != -1) {
        FUN_00154e40(arg0, arg2);
        return 1;
    }
    if (arg0->f20 != 0) {
        FUN_00300f50(arg0, arg0->f20);
    }
    arg0->f8 = arg1;
    arg0->f12 = arg2;
    FUN_00154b80(arg1, arg2, &sp5C, &sp58);
    arg0->f24 = sp5C;
    arg0->f16 = sp58;
    arg0->f20 = FUN_00300db0(arg0, arg0->f24, 0x80);
    if (arg3 != 0) {
        memcpy(arg0->f20, arg3, *(volatile int *)&arg0->f24);
    } else {
        memset(arg0->f20, 0, *(volatile int *)&arg0->f24);
    }
    return 1;
}
