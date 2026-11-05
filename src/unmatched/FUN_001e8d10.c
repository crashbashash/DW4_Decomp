typedef struct { unsigned short v : 11; unsigned short r : 5; } H;
typedef struct { char p[256]; H h[8]; } G;
int FUN_001ebc00();
int FUN_00208200();
extern int DAT_00491478[4];
extern short DAT_00568e08[8];
extern short DAT_00568e0a[8];
extern short DAT_00568e0c[8];
extern short DAT_00568e0e[8];
extern short DAT_00568e22[8];
extern short DAT_00568e24[8];
extern int DAT_00568e28[4];
extern int DAT_00569330[4];
extern G *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056b058[4];
void FUN_001e8d10(int arg0, int arg1, int arg2, int arg3) {
    int a1;
    int a2;
    int a0;
    int lim;
    int s1;
    int v;
    s1 = (FUN_001ebc00() & 2) != 0;
    if (DAT_00568e0e[0] == 0 && DAT_00568e0c[0] > 0 && DAT_00568e28[0] == -1) {
        arg1 = arg1 / 2;
        arg3 = arg3 / 2;
    }
    if (DAT_00568e28[0] < 0) {
        v = s1 != 0 ? DAT_00568e24[0] : DAT_00568e0a[0];
    } else {
        v = FUN_00208200(DAT_00568e28[0]);
    }
    a0 = v - arg1 - 1;
    a2 = arg0 + arg2 - 1;
    a1 = a0 - arg3 + 1;
    if (a1 < 0) a1 = 0;
    if (a0 < 0) a0 = 0;
    if (arg0 < 0) arg0 = 0;
    if (a2 < 0) a2 = 0;
    lim = s1 != 0 ? DAT_00568e22[0] : DAT_00568e08[0];
    if (a2 >= lim) {
        lim = s1 != 0 ? DAT_00568e22[0] : DAT_00568e08[0];
        a2 = lim - 1;
    }
    if (DAT_00569330[0] == 0) {
        DAT_0056ad80[0]->h[3].v = a0;
        DAT_0056ad80[0]->h[2].v = a1;
        DAT_0056ad80[0]->h[1].v = a2;
        DAT_0056ad80[0]->h[0].v = arg0;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 1LL << 32;
        if (DAT_0056b058[0] != 0) {
            DAT_0056ad80[0]->h[7].v = a0;
            DAT_0056ad80[0]->h[6].v = a1;
            DAT_0056ad80[0]->h[5].v = a2;
            DAT_0056ad80[0]->h[4].v = arg0;
            DAT_00491478[0] |= 0x40;
            DAT_0056ae48[0] |= 2LL << 32;
        }
    } else {
        DAT_0056ad80[0]->h[7].v = a0;
        DAT_0056ad80[0]->h[6].v = a1;
        DAT_0056ad80[0]->h[5].v = a2;
        DAT_0056ad80[0]->h[4].v = arg0;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 2LL << 32;
    }
}
