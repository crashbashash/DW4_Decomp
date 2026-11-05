int FUN_001eb810();
int FUN_001f64a0();
int FUN_001ff3b0();
int FUN_001ff720();
int FUN_001fffb0();
int FUN_00200980();
int FUN_00201a90();
extern int DAT_00491478[4];
extern int DAT_00491480[4];
extern short DAT_004914a6[8];
extern int DAT_00562c70[4];
extern int DAT_00569220[4];
extern int DAT_00569228[4];
extern int DAT_00569230[4];
extern int *DAT_00569238[4];
extern int DAT_00569240[4];
extern long long DAT_00569248[4];
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
extern int DAT_00569308[4];
extern int DAT_00569330[4];
extern int DAT_0056bad8[4];
int FUN_001f4100();
int FUN_001f47c0();

void FUN_001f3d00(unsigned arg0, int arg1) {
    int temp_s3;
    int temp_a0;
    int var_a0;
    int var_a0_2;
    int var_a0_3;
    int var_a0_4;
    int var_a1;
    int var_a1_2;
    int var_v0;
    int var_v1;
    int var_v1_2;
    int var_v1_3;
    int var_v1_4;
    unsigned int temp_a2;
    unsigned long long temp_a2_2;
    unsigned var_s2;
    unsigned var_s0;
    int m;
    int b27;

    var_s2 = arg0;
    temp_a2 = DAT_00562c70[DAT_00569330[0]];
    b27 = (temp_a2 >> 0x1B) & 1;
    if (DAT_00491480[0] != 6) {
        DAT_00491480[0] = 6;
        DAT_00491478[0] |= 9;
        DAT_005692a0[0] += 1;
    }
    var_a1 = DAT_00569300[0];
    temp_a0 = var_a1 == 0;
    if ((DAT_00569240[0] ^ temp_a0) != 0) {
        DAT_00569240[0] = temp_a0;
        DAT_00491478[0] |= 0x11;
        DAT_00569298[0] += 1;
    }
    if (DAT_00569228[0] & 0x20) {
        DAT_00569228[0] &= ~7;
        if (var_a1 != 0) {
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
        if (DAT_00569308[0] != 0) {
            var_a0_3 = 0x100;
        } else {
            var_a0_3 = 0;
        }
        DAT_00569228[0] |= var_a0_3;
        if (DAT_005692b0[0] != 0) {
            switch (DAT_00569220[0]) {
            case 0:
                var_v0 = DAT_00569228[0] | 0x40;
                DAT_00569228[0] = var_v0;
                break;
            case 1:
                var_v0 = DAT_00569228[0] | 0x80;
                DAT_00569228[0] = var_v0;
                break;
            }
        }
        FUN_001fffb0(var_a0_3, var_a1, temp_a2);
        FUN_00200980();
        FUN_00201a90();
        DAT_00569238[0] = (int *)(&FUN_001f4100);
    } else {
        if ((temp_a2 >> 0x16) & 1) {
            DAT_00569228[0] &= ~7;
            if (var_a1 != 0) {
                var_a1_2 = 2;
            } else {
                var_a1_2 = 0;
            }
            DAT_00569228[0] |= var_a1_2;
            if (DAT_005692b0[0] != 0) {
                var_a1 = 1;
            } else {
                var_a1 = 0;
            }
            DAT_00569228[0] |= var_a1;
            if (DAT_005692c0[0] != 0) {
                var_a0_4 = 4;
            } else {
                var_a0_4 = 0;
            }
            DAT_00569228[0] |= var_a0_4;
        }
        DAT_00569230[0] = 0;
        DAT_00569238[0] = (int *)(&FUN_001f47c0);
        if (DAT_00491478[0] != 0) {
            FUN_001ff3b0(0x1FF, var_a1, temp_a2);
            FUN_001ff720(0x1FF);
        }
    }
    if (b27) {
        FUN_001eb810();
    }
    temp_a2_2 = (unsigned long long)(unsigned)var_s2;
    DAT_00569250[0] += temp_a2_2;
    DAT_00569248[0] += temp_a2_2;
    m = DAT_0056bad8[0];
    if (m & 1) DAT_00569270[0] += temp_a2_2;
    if (m & 2) DAT_00569280[0] += temp_a2_2;
    if (m & 4) DAT_00569278[0] += temp_a2_2;
    if (m & 8) DAT_00569288[0] += temp_a2_2;
    if (m & 0x10) DAT_00569290[0] += temp_a2_2;
    temp_s3 = DAT_004914a6[0];
    while (var_s2 != 0) {
        var_s0 = var_s2;
        if ((unsigned)temp_s3 < var_s2) var_s0 = temp_s3;
        FUN_001f64a0(var_s0, 0, arg1);
        var_s2 -= var_s0;
    }
}
