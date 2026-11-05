int FUN_001ebc00();
int FUN_001f76f0();
int FUN_0020b7f0();
extern int DAT_004917b0[4];
extern int DAT_00491860[4];
extern short DAT_00568e08[];
extern short DAT_00568e0a[];
extern short DAT_00568e12[];
extern short DAT_00568e22[];
extern short DAT_00568e24[];
struct G {
    char p0[355]; unsigned char x355:6; char p1[12];
    unsigned short x368:9; char p2[14];
    unsigned short x384:14; unsigned char x386:6; unsigned char x387:6;
    unsigned short x388:14; unsigned char x390:6; unsigned char x391:6;
    unsigned short x392:11; unsigned short x394:11; unsigned short x396:11; unsigned short x398:11; unsigned char x399:2;
    unsigned short x400:12; char p4[2];
    unsigned short x404:12; char p5[2]; unsigned char x408:2;
};
struct A0 { char p0[56]; int f56; unsigned short f60; char p1[4]; unsigned short f66; char p2[2]; signed char f70:7; char p3; char f72; };
extern struct G *DAT_0056ad80[4];
void FUN_0020a590(struct A0 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int sp0;
    int s0;
    int v;
    int w;
    short u;
    short m;
    int pr;
    int t;
    sp0 = DAT_0056ad80[0]->x355;
    s0 = (FUN_001ebc00() & 2) != 0;
    arg0->f72 = 1;
    switch (arg0->f70) {
    case 1:
        if (FUN_0020b7f0(arg0) == 0) return;
        arg0->f70 = 3;
        break;
    case 4:
    case 3:
    case 5:
        arg0->f70 = 3;
        break;
    }
    DAT_0056ad80[0]->x391 = DAT_004917b0[arg0->f66];
    DAT_0056ad80[0]->x388 = arg0->f56;
    DAT_0056ad80[0]->x390 = (arg0->f60 + 63) / 64;
    DAT_0056ad80[0]->x387 = sp0;
    if (arg7 != 0) {
        DAT_0056ad80[0]->x384 = DAT_0056ad80[0]->x368 << 5;
    } else {
        DAT_0056ad80[0]->x384 = (DAT_00568e12[0] != 0 && !s0) ? (DAT_00568e08[0] * DAT_00568e0a[0]) / 64 : 0;
    }
    if (s0 != 0) u = DAT_00568e22[0]; else u = DAT_00568e08[0];
    DAT_0056ad80[0]->x386 = u / 64;
    DAT_0056ad80[0]->x396 = arg3;
    DAT_0056ad80[0]->x398 = arg4;
    DAT_0056ad80[0]->x392 = arg1;
    if (s0 != 0) m = DAT_00568e24[0]; else m = DAT_00568e0a[0];
    DAT_0056ad80[0]->x394 = m - (arg6 + arg2);
    DAT_0056ad80[0]->x399 = 0;
    DAT_0056ad80[0]->x400 = arg5;
    DAT_0056ad80[0]->x404 = arg6;
    DAT_0056ad80[0]->x408 = 2;
    FUN_001f76f0(4, &DAT_00491860[0]);
}
