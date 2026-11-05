int FUN_001eb810();
int FUN_001f4100();
int FUN_001f47c0();
int FUN_001ff3b0();
int FUN_001ff720();
int FUN_001fffb0();
int FUN_00200980();
int FUN_00201a90();
extern int DAT_00491478[4];
extern int DAT_00491480[4];
extern short DAT_004914a6[16];
extern int DAT_00562c70[4];
extern int DAT_00569228[4];
extern int DAT_00569230[4];
extern int (*DAT_00569238[4])(unsigned int, int);
extern int DAT_00569240[4];
extern long long DAT_00569250[4];
extern long long DAT_00569270[4];
extern long long DAT_00569278[4];
extern long long DAT_00569280[4];
extern long long DAT_00569288[4];
extern long long DAT_00569290[4];
extern long long DAT_00569298[4];
extern long long DAT_005692a0[4];
extern int DAT_005692b0[4];
extern int DAT_005692c0[4];
extern int DAT_00569300[4];
extern int DAT_00569330[4];
extern int DAT_0056bad8[4];
void FUN_001f1850(unsigned int arg0) {
    /*D*/
    unsigned long long t;
    unsigned int s3;
    int s2;
    int s1;
    int a1;
    unsigned int f;
    int s0;
    unsigned int a2;
    int a0;
    /*E*/

    s3 = arg0;
    a2 = *(unsigned int *)((char *)DAT_00562c70 + DAT_00569330[0] * 4);
    s0 = (a2 >> 0x1B) & 1;
    if (DAT_00491480[0] != 2) {
        DAT_00491480[0] = 2;
        DAT_00491478[0] |= 9;
        DAT_005692a0[0] += 1;
    }
    a1 = DAT_00569300[0];
    a0 = a1 == 0;
    if ((DAT_00569240[0] ^ a0) != 0) {
        DAT_00569240[0] = a0;
        DAT_00491478[0] |= 0x11;
        DAT_00569298[0] += 1;
    }
    if (DAT_00569228[0] & 0x20) {
        DAT_00569228[0] &= ~7;
        if (a1 != 0) a0 = 2; else a0 = 0;
        DAT_00569228[0] |= a0;
        if (DAT_005692c0[0] != 0) a0 = 4; else a0 = 0;
        DAT_00569228[0] |= a0;
        if (DAT_005692b0[0] != 0) DAT_00569228[0] |= 1;
        FUN_001fffb0();
        FUN_00200980();
        FUN_00201a90();
        DAT_00569238[0] = (int (*)(unsigned int, int))FUN_001f4100;
    } else {
        if ((a2 >> 0x16) & 1) {
            DAT_00569228[0] &= ~7;
            if (a1 != 0) a1 = 2; else a1 = 0;
            DAT_00569228[0] |= a1;
            if (DAT_005692b0[0] != 0) a1 = 1; else a1 = 0;
            DAT_00569228[0] |= a1;
            if (DAT_005692c0[0] != 0) a0 = 4; else a0 = 0;
            DAT_00569228[0] |= a0;
        }
        DAT_00569230[0] = 0;
        DAT_00569238[0] = (int (*)(unsigned int, int))FUN_001f47c0;
        if (DAT_00491478[0] != 0) {
            FUN_001ff3b0(0x1FF);
            FUN_001ff720(0x1FF);
        }
    }
    if (s0) {
        FUN_001eb810();
    }
    s2 = 0;
    f = DAT_004914a6[0] & ~1;
    while (s3 >= 2U) {
        s1 = s3;
        if (f < s3) s1 = f;
        DAT_00569238[0](s1, s2);
        s2 += s1 - 1;
        t = (unsigned int)s1;
        DAT_00569250[0] += t;
        if (DAT_0056bad8[0] & 1) DAT_00569270[0] += t;
        if (DAT_0056bad8[0] & 2) DAT_00569280[0] += t;
        if (DAT_0056bad8[0] & 4) DAT_00569278[0] += t;
        if (DAT_0056bad8[0] & 8) DAT_00569288[0] += t;
        if (DAT_0056bad8[0] & 0x10) DAT_00569290[0] += t;
        s3 -= s1 - 1;
    }
}
