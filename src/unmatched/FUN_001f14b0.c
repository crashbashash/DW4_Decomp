int FUN_001eb810(void);
int FUN_001f4100(unsigned int, int);
int FUN_001f47c0(unsigned int, int);
int FUN_001ff3b0(int);
int FUN_001ff720(int);
int FUN_001fffb0(void);
int FUN_00200980(void);
int FUN_00201a90(void);
extern int DAT_00491478[4];
extern int DAT_00491480[4];
extern short DAT_004914a6[8];
extern int DAT_00562c70[4096];
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
void FUN_001f14b0(unsigned int arg0) {
    int var_s3;
    int var_a0_3;
    int var_a1_2;
    int b27;
    int var_a1;
    int var_a0_2;
    unsigned int var_s2;
    unsigned int var_s1;
    int var_v1_4;
    int temp_a0;
    unsigned int temp_s0;
    int var_v1;
    int var_v1_2;
    int var_v1_3;
    unsigned int temp_a2;
    unsigned long long temp_a1;
    int fl;
    int var_a0;

    var_s1 = arg0;
    temp_a2 = DAT_00562c70[DAT_00569330[0]];
    b27 = 1 & (temp_a2 >> 0x1B);
    if (1 != DAT_00491480[0]) {
        DAT_00491480[0] = 1;
        DAT_00491478[0] |= 9;
        DAT_005692a0[0] += 1;
    }
    var_a1 = DAT_00569300[0];
    temp_a0 = var_a1 == 0;
    if ((DAT_00569240[0] ^ temp_a0) != 0) {
        DAT_00569240[0] = temp_a0;
        DAT_00491478[0] = DAT_00491478[0] | 0x11;
        DAT_00569298[0] += 1;
    }
    if (DAT_00569228[0] & 0x20) {
        DAT_00569228[0] &= ~7;
        if (var_a1) {
            var_a0 = 2;
        } else {
            var_a0 = 0;
        }
        DAT_00569228[0] |= var_a0;
        if (DAT_005692c0[0] != 0) {
            var_a0_2 = 4;
        } else {
            var_a0_2 = 0;
        }
        DAT_00569228[0] |= var_a0_2;
        if (DAT_005692b0[0] != 0) {
            DAT_00569228[0] |= 1;
        }
        FUN_001fffb0();
        FUN_00200980();
        FUN_00201a90();
        DAT_00569238[0] = FUN_001f4100;
    } else {
        if (1 & (temp_a2 >> 0x16)) {
            DAT_00569228[0] &= ~7;
            if (var_a1) {
                var_a1_2 = 2;
            } else {
                var_a1_2 = 0;
            }
            DAT_00569228[0] |= var_a1_2;
            if (0 != DAT_005692b0[0]) {
                var_a1 = 1;
            } else {
                var_a1 = 0;
            }
            DAT_00569228[0] |= var_a1;
            if (0 != DAT_005692c0[0]) {
                var_a0_3 = 4;
            } else {
                var_a0_3 = 0;
            }
            DAT_00569228[0] |= var_a0_3;
        }
        DAT_00569230[0] = 0;
        DAT_00569238[0] = FUN_001f47c0;
        if (DAT_00491478[0] != 0) {
            FUN_001ff3b0(0x1FF);
            FUN_001ff720(0x1FF);
        }
    }
    if (b27) {
        FUN_001eb810();
    }
    DAT_00569250[0] += arg0;
    fl = DAT_0056bad8[0];
    if (1 & fl) {
        DAT_00569270[0] += arg0;
    }
    if (2 & fl) {
        DAT_00569280[0] += arg0;
    }
    if (4 & fl) {
        DAT_00569278[0] += arg0;
    }
    if (fl & 8) {
        DAT_00569288[0] += arg0;
    }
    if (fl & 0x10) {
        DAT_00569290[0] += arg0;
    }
    var_s3 = 0;
    temp_s0 = DAT_004914a6[0] & ~1;
    while (var_s1) {
        var_s2 = var_s1;
        if (temp_s0 < var_s1) {
            var_s2 = temp_s0;
        }
        DAT_00569238[0](var_s2, var_s3);
        var_s3 += var_s2;
        var_s1 -= var_s2;
    }
}
