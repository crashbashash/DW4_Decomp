extern int FUN_001eb810();
extern int FUN_001f4100(unsigned int, int);
extern int FUN_001f47c0(unsigned int, int);
extern int FUN_001ff3b0();
extern int FUN_001ff720();
extern int FUN_001fffb0();
extern int FUN_00200980();
extern int FUN_00201a90();
extern int DAT_00491478[4];
extern int DAT_00491480[4];
extern short DAT_004914a6[16];
extern int DAT_00562c70[4];
extern int DAT_00569228[4];
extern int DAT_00569230[4];
extern int (*DAT_00569238[4])(unsigned int, int);
extern int DAT_00569240[4];
extern long long DAT_00569250[4];
extern long long DAT_00569258[4];
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
extern int FUN_001f64a0(unsigned int, int, int);
extern long long DAT_00569248[4];
void FUN_001f2d90(unsigned int arg0, int arg1) {
    unsigned int s3;
    int s2;
    int s1;
    unsigned int s0;
    unsigned int a2;
    int a0;
    int a1;
    int a3;
    int t;
    int fl;
    int t3;

    s3 = arg0;
    s2 = arg1;
    a2 = DAT_00562c70[DAT_00569330[0]];
    fl = (a2 >> 0x1B) & 1;
    if (DAT_00491480[0] != 4) {
        DAT_00491480[0] = 4;
        DAT_00491478[0] |= 9;
        DAT_005692a0[0] += 1;
    }
    a1 = DAT_00569300[0];
    t = a1 == 0;
    if ((DAT_00569240[0] ^ t) != 0) {
        DAT_00569240[0] = t;
        DAT_00491478[0] |= 0x11;
        DAT_00569298[0] += 1;
    }
    if (DAT_00569228[0] & 0x20) {
        DAT_00569228[0] &= ~7;
        if (a1 != 0) {
            a0 = 2;
        } else {
            a0 = 0;
        }
        DAT_00569228[0] |= a0;
        if (DAT_005692c0[0] != 0) {
            a0 = 4;
        } else {
            a0 = 0;
        }
        DAT_00569228[0] |= a0;
        if (DAT_005692b0[0] != 0) {
            DAT_00569228[0] |= 1;
        }
        FUN_001fffb0();
        FUN_00200980();
        FUN_00201a90();
        DAT_00569238[0] = FUN_001f4100;
    } else {
        if ((a2 >> 0x16) & 1) {
            DAT_00569228[0] &= ~7;
            if (a1 != 0) {
                a1 = 2;
            } else {
                a1 = 0;
            }
            DAT_00569228[0] |= a1;
            if (DAT_005692b0[0] != 0) {
                a1 = 1;
            } else {
                a1 = 0;
            }
            DAT_00569228[0] |= a1;
            if (DAT_005692c0[0] != 0) {
                a0 = 4;
            } else {
                a0 = 0;
            }
            DAT_00569228[0] |= a0;
        }
        DAT_00569230[0] = 0;
        DAT_00569238[0] = FUN_001f47c0;
        if (DAT_00491478[0] != 0) {
            FUN_001ff3b0(0x1FF);
            FUN_001ff720(0x1FF);
        }
    }
    if (fl) {
        FUN_001eb810();
    }
    s1 = DAT_004914a6[0];
    while (s3 >= 3U) {
        s0 = s3;
        if ((unsigned int)s1 < s3) {
            s0 = s1;
        }
        FUN_001f64a0(s0, 0, s2);
        DAT_00569250[0] += s0;
        DAT_00569248[0] += s0;
        DAT_00569258[0] += s0 - 2;
        a3 = DAT_0056bad8[0];
        if (a3 & 1) DAT_00569270[0] += s0;
        if (a3 & 2) DAT_00569280[0] += s0;
        if (a3 & 4) DAT_00569278[0] += s0;
        if (a3 & 8) DAT_00569288[0] += s0;
        if (a3 & 0x10) DAT_00569290[0] += s0;
        t3 = s0 - 2;
        s2 += t3 * 2;
        s3 -= t3;
    }
}
