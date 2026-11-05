typedef struct R { int pad0; int rc; } R;
extern int FUN_00129ef8();
extern void *FUN_002b9500();
extern int FUN_002dbfb0();
extern int FUN_002dc050();
extern int FUN_002dc0a0(int, int, float, float);
extern int FUN_002dc120();
extern int FUN_0030b3c0();
extern int FUN_0030b670();
extern int igObject_Destroy();
extern int igObject_GetAllocator();
extern int DAT_004f9730[4];
extern int DAT_004f9738[4];
unsigned char FUN_002dbd10(int arg0, int arg1, int arg2, int arg3, int arg4) {
    unsigned char sp6F; unsigned char sp6E;
    int sp68; int sp64; float sp60; float sp5C;
    R *volatile sp58;
    R *o;
    unsigned char r;
    switch (arg1) {
    case 1:
        sp68 = 0; sp64 = 0;
        if (FUN_00129ef8(arg2, &DAT_004f9730[0], &sp68) != 1) return 0;
        if (FUN_00129ef8(arg4, &DAT_004f9730[0], &sp64) != 1) return 0;
        r = FUN_002dc050(arg0, sp68, arg3, sp64); break;
    case 2:
        sp60 = 0; sp5C = 0;
        if (FUN_00129ef8(arg2, &DAT_004f9738[0], &sp60) != 1) return 0;
        if (FUN_00129ef8(arg4, &DAT_004f9738[0], &sp5C) != 1) return 0;
        r = FUN_002dc0a0(arg0, arg3, sp60, sp5C); break;
    case 3:
        sp6F = 0; sp6E = 0;
        sp58 = FUN_002b9500(igObject_GetAllocator());
        FUN_0030b3c0(sp58, arg2);
        if (FUN_0030b670(sp58, &sp6F) == 0) {
            o = sp58;
            if (o != 0) { o->rc = o->rc - 1; if (((unsigned long long)((long long)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
            return 0;
        }
        FUN_0030b3c0(sp58, arg4);
        if (FUN_0030b670(sp58, &sp6E) == 0) {
            o = sp58;
            if (o != 0) { o->rc = o->rc - 1; if (((unsigned long long)((long long)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
            return 0;
        }
        r = FUN_002dc120(arg0, sp6F, arg3, sp6E);
        o = sp58;
        if (o != 0) { o->rc = o->rc - 1; if (((unsigned long long)((long long)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
        break;
    default:
    case 0:
        r = FUN_002dbfb0(arg0, arg2, arg3, arg4);
    }
    return r;
}
