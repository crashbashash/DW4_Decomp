extern int FUN_001eb810();
extern int FUN_001f4100();
extern int FUN_001f47c0();
extern int FUN_001ff3b0(int);
extern int FUN_001ff720(int);
extern int FUN_001fffb0();
extern int FUN_00200980();
extern int FUN_00201a90();
extern int DAT_00491478[4];
extern int DAT_00491480[4];
extern short DAT_004914a6[16];
extern unsigned int DAT_00562c70[4];
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
void FUN_001f23a0(unsigned int arg0) {
    unsigned int a1;
    int bit27;
    int t;
    int v;
    unsigned int s0;
    unsigned long long a3;
    int f;
    a1 = DAT_00562c70[DAT_00569330[0]];
    bit27 = (a1 >> 0x1B) & 1;
    if (DAT_00491480[0] != 5) {
        DAT_00491480[0] = 5;
        DAT_00491478[0] |= 9;
        DAT_005692a0[0] += 1;
    }
    t = DAT_00569300[0] == 0;
    if ((DAT_00569240[0] ^ t) != 0) {
        DAT_00569240[0] = t;
        DAT_00491478[0] |= 0x11;
        DAT_00569298[0] += 1;
    }
    if (DAT_00569228[0] & 0x20) {
        DAT_00569228[0] &= ~7;
        if (DAT_00569300[0] != 0) {
            v = 2;
        } else {
            v = 0;
        }
        DAT_00569228[0] |= v;
        if (DAT_005692c0[0] != 0) {
            v = 4;
        } else {
            v = 0;
        }
        DAT_00569228[0] |= v;
        if (DAT_005692b0[0] != 0) {
            DAT_00569228[0] |= 1;
        }
        FUN_001fffb0();
        FUN_00200980();
        FUN_00201a90();
        DAT_00569238[0] = (int (*)(unsigned int, int))FUN_001f4100;
    } else {
        if ((a1 >> 0x16) & 1) {
            DAT_00569228[0] &= ~7;
            if (DAT_00569300[0] != 0) {
                v = 2;
            } else {
                v = 0;
            }
            DAT_00569228[0] |= v;
            if (DAT_005692b0[0] != 0) {
                v = 1;
            } else {
                v = 0;
            }
            DAT_00569228[0] |= v;
            if (DAT_005692c0[0] != 0) {
                v = 4;
            } else {
                v = 0;
            }
            DAT_00569228[0] |= v;
        }
        DAT_00569230[0] = 0;
        DAT_00569238[0] = (int (*)(unsigned int, int))FUN_001f47c0;
        if (DAT_00491478[0] != 0) {
            FUN_001ff3b0(0x1FF);
            FUN_001ff720(0x1FF);
        }
    }
    if (bit27) {
        FUN_001eb810();
    }
    s0 = ((unsigned int)DAT_004914a6[0] < arg0) ? (unsigned int)DAT_004914a6[0] : arg0;
    DAT_00569238[0](s0, 0);
    a3 = s0;
    DAT_00569250[0] += a3;
    DAT_00569258[0] += (s0 - 2);
    f = DAT_0056bad8[0];
    if (f & 1) {
        DAT_00569270[0] += a3;
    }
    if (f & 2) {
        DAT_00569280[0] += a3;
    }
    if (f & 4) {
        DAT_00569278[0] += a3;
    }
    if (f & 8) {
        DAT_00569288[0] += a3;
    }
    if (f & 0x10) {
        DAT_00569290[0] += a3;
    }
}
