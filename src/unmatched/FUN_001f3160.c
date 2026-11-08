int FUN_001eb810();
int FUN_001f64a0();
int FUN_001ff3b0();
int FUN_001ff720();
int FUN_001fffb0();
int FUN_00200980();
int FUN_00201a90();
extern int DAT_00491478[16];
extern int DAT_00491480[16];
extern short DAT_004914a6[16];
extern int DAT_00562c70[16];
extern int DAT_00569228[16];
extern int DAT_00569230[16];
extern int * DAT_00569238[16];
extern int DAT_00569240[16];
extern long long DAT_00569248[16];
extern long long DAT_00569250[16];
extern long long DAT_00569258[16];
extern long long DAT_00569270[16];
extern long long DAT_00569278[16];
extern long long DAT_00569280[16];
extern long long DAT_00569288[16];
extern long long DAT_00569290[16];
extern long long DAT_00569298[16];
extern long long DAT_005692a0[16];
extern int DAT_005692b0[16];
extern int DAT_005692c0[16];
extern int DAT_00569300[16];
extern int DAT_00569330[16];
extern int DAT_0056bad8[16];
int FUN_001f4100();
int FUN_001f47c0();

void FUN_001f3160(unsigned int arg0, unsigned short *arg1) {
    unsigned int ctl;
    int a1;
    int flag;
    unsigned int n;
    unsigned int chunk;
    unsigned int limit;
    unsigned int cnt;
    unsigned long long w;
    int mask;
    int b27;

    n = arg0;
    ctl = *(unsigned int *)((char *)DAT_00562c70 + DAT_00569330[0] * 4);
    b27 = (ctl >> 27) & 1;
    if (DAT_00491480[0] != 3) {
        DAT_00491480[0] = 3;
        DAT_00491478[0] |= 9;
        DAT_005692a0[0] += 1;
    }
    a1 = DAT_00569300[0];
    flag = a1 == 0;
    if ((DAT_00569240[0] ^ flag) != 0) {
        DAT_00569240[0] = flag;
        DAT_00491478[0] |= 0x11;
        DAT_00569298[0] += 1;
    }
    if (DAT_00569228[0] & 0x20) {
        DAT_00569228[0] &= ~7;
        DAT_00569228[0] |= (a1 != 0) ? 2 : 0;
        DAT_00569228[0] |= (DAT_005692c0[0] != 0) ? 4 : 0;
        if (DAT_005692b0[0] != 0) {
            DAT_00569228[0] |= 1;
        }
        FUN_001fffb0();
        FUN_00200980();
        FUN_00201a90();
        DAT_00569238[0] = (int *)(&FUN_001f4100);
    } else {
        if ((ctl >> 22) & 1) {
            DAT_00569228[0] &= ~7;
            DAT_00569228[0] |= (a1 != 0) ? 2 : 0;
            DAT_00569228[0] |= (DAT_005692b0[0] != 0) ? 1 : 0;
            DAT_00569228[0] |= (DAT_005692c0[0] != 0) ? 4 : 0;
        }
        DAT_00569230[0] = 0;
        DAT_00569238[0] = (int *)(&FUN_001f47c0);
        if (DAT_00491478[0] != 0) {
            FUN_001ff3b0(0x1FF);
            FUN_001ff720(0x1FF);
        }
    }
    if (b27) {
        FUN_001eb810();
    }
    {
        DAT_00569250[0] += n;
        DAT_00569248[0] += n;
        DAT_00569258[0] += n / 3U;
        mask = DAT_0056bad8[0];
        if (mask & 1) DAT_00569270[0] += n;
        if (mask & 2) DAT_00569280[0] += n;
        if (mask & 4) DAT_00569278[0] += n;
        if (mask & 8) DAT_00569288[0] += n;
        if (mask & 0x10) DAT_00569290[0] += n;
    }
    limit = ((unsigned int)DAT_004914a6[0] / 3U) * 3;
    while (n >= 3U) {
        chunk = n;
        if (limit < n) chunk = limit;
        FUN_001f64a0(chunk, 0, arg1);
        n -= chunk;
        arg1 += chunk;
    }
}
