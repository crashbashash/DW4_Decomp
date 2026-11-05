typedef struct { unsigned short v : 11; unsigned short r : 5; } H;
typedef struct { unsigned long long a : 3; unsigned long long rest : 61; } R0;
typedef struct { unsigned long long pad : 16; unsigned long long a : 1; unsigned long long b : 2; unsigned long long rest : 45; } R312;
typedef struct { unsigned long long pad : 32; unsigned long long a : 1; unsigned long long rest : 31; } R368;
typedef struct { int lo; int hi; } L2;
typedef struct {
    R0 r0;
    unsigned char b8, b9, b10, b11;
    char p12[148];
    long long f160;
    char p168[88];
    H h[4];
    char p264[48];
    R312 r312;
    char p320[32];
    L2 f352;
    char p360[8];
    long long f368_dummy;
} G;
int FUN_001ea180();
int FUN_001ebc00();
int FUN_001f76f0();
int FUN_00208200();
extern int DAT_0048dd10[4];
extern int DAT_00491478[4];
extern int DAT_00562d68[4];
extern int DAT_00562d70[4];
extern int DAT_00562d78[4];
extern short DAT_00568e08[8];
extern short DAT_00568e0a[8];
extern short DAT_00568e22[8];
extern short DAT_00568e24[8];
extern int DAT_00568e28[8];
extern G *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_001e99f0(int arg0, unsigned int arg1, int arg2) {
    long long s4;
    long long s8;
    int s3;
    int s2;
    long long spC0;
    long long spB0;
    long long spA0;
    int zero;
    s3 = (FUN_001ebc00() & 2) != 0;
    if (arg0 != 0) {
        if (DAT_00568e28[0] < 0) {
            s2 = s3 != 0 ? DAT_00568e24[0] : DAT_00568e0a[0];
        } else {
            s2 = FUN_00208200(DAT_00568e28[0]);
        }
        s4 = *(long long *)&DAT_0056ad80[0]->f160;
        spC0 = *(long long *)&DAT_0056ad80[0]->r312;
        s8 = *(long long *)((char *)DAT_0056ad80[0] + 368);
        spB0 = *(long long *)&DAT_0056ad80[0]->f352;
        spA0 = *(long long *)&DAT_0056ad80[0]->h[0];
        if (!(arg0 & 1)) DAT_0056ad80[0]->f352.hi = -1;
        zero = 0;
        DAT_0056ad80[0]->h[0].v = zero;
        DAT_0056ad80[0]->h[2].v = zero;
        DAT_0056ad80[0]->h[1].v = (s3 != 0 ? DAT_00568e22[0] : DAT_00568e08[0]) - 1;
        DAT_0056ad80[0]->h[3].v = (s3 != 0 ? DAT_00568e24[0] : DAT_00568e0a[0]) - 1;
        {
            G *g1 = DAT_0056ad80[0];
            g1->f160 = 0;
            g1->r0.a = 6;
        }
        {
            G *g2 = DAT_0056ad80[0];
            *(long long *)&g2->r312 = 0;
            g2->r312.a = 1;
        }
        DAT_0056ad80[0]->r312.b = 1;
        ((R368 *)((char *)DAT_0056ad80[0] + 368))->a = ((arg0 & 2) != 0) ^ 1;
        DAT_00562d78[0] = 0;
        while (DAT_00562d78[0] < DAT_00562d70[0] + 1) {
            if (DAT_00562d70[0] != 0) {
                DAT_0056ad80[0]->b8 = DAT_00562d78[0] << 5;
            } else {
                DAT_0056ad80[0]->b8 = arg1 & 0xff;
            }
            DAT_0056ad80[0]->b9 = (arg1 >> 8) & 0xff;
            DAT_0056ad80[0]->b10 = (arg1 >> 16) & 0xff;
            DAT_0056ad80[0]->b11 = (arg1 >> 24) & 0xff;
            FUN_001f76f0(8, &DAT_0048dd10[0]);
            if (DAT_00562d68[0] != 0) {
                FUN_001ea180(DAT_00562d68[0], s2, arg2);
            } else {
                FUN_001ea180((short)(s3 != 0 ? DAT_00568e22[0] : DAT_00568e08[0]), s2, arg2);
            }
            DAT_00562d78[0] += 1;
        }
        {
            G *g = DAT_0056ad80[0];
            *(long long *)&g->f160 = s4;
            *(long long *)&g->r312 = spC0;
            *(long long *)((char *)g + 368) = s8;
            *(long long *)&g->f352 = spB0;
            *(long long *)&g->h[0] = spA0;
        }
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x100000LL | (0x5081LL << 32);
    }
}
