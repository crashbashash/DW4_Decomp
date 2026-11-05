typedef struct S {
    char p0[136]; union { struct { short a; short pad; short b; short c; } h; long long q; } u136; long long q144;
    char p152[24]; long long q176; char p184[168]; union { long long q; int i; } u352; long long q360; union { long long q; int i; } u368; long long q376;
} S;
extern int FUN_001ebc00();
extern int FUN_001f76f0();
extern int DAT_004918a0[4];
extern int DAT_004918b0[4];
extern int DAT_00562c70[4];
extern short DAT_00568e08[8];
extern short DAT_00568e0a[8];
extern short DAT_00568e22[8];
extern short DAT_00568e24[8];
extern int DAT_00568e28[4];
extern int DAT_00568e30[4];
extern int DAT_00569330[4];
extern S *DAT_0056ad80[4];
extern int DAT_0056c138[4];
extern int DAT_0056c140[4];
extern long long DAT_0056c148[4];
void FUN_0020b110(void) {
    short v;
    int a1;
    int s0;
    S *p;

    s0 = ((unsigned int) DAT_00562c70[DAT_00569330[0]] >> 0x17) & 1;
    a1 = (FUN_001ebc00() & 2) != 0;
    if (DAT_00568e28[0] != -1) {
        DAT_0056ad80[0]->u352.i = DAT_0056c138[0];
        DAT_0056ad80[0]->u368.i = DAT_0056c140[0];
        p = DAT_0056ad80[0];
        p->q176 = DAT_0056c148[0];
        if (a1 != 0) v = DAT_00568e22[0]; else v = DAT_00568e08[0];
        p->u136.h.a = (0x800 - (v >> 1)) * 0x10;
        if (a1 != 0) v = DAT_00568e24[0]; else v = DAT_00568e0a[0];
        DAT_0056ad80[0]->u136.h.b = (0x800 - (v >> 1)) * 0x10;
        if (s0 != 0) {
            p = DAT_0056ad80[0];
            p->q360 = p->u352.q;
            p->q144 = p->u136.q;
            p->q376 = p->u368.q;
            FUN_001f76f0(3, &DAT_004918b0[0]);
        }
        FUN_001f76f0(4, &DAT_004918a0[0]);
        DAT_00568e28[0] = -1;
        DAT_00568e30[0] = -1;
    }
}
