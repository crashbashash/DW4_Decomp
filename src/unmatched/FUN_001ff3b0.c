extern int FUN_001f8b50();
extern int FUN_001fffb0();
extern int FUN_00200980();
extern int FUN_00201a90();
extern int FUN_00204ea0();
extern int DAT_00491478[4];
extern int DAT_00568e50[4];
extern int DAT_0056b3b0[4];
extern int DAT_0056b3b4[4];
extern int DAT_0056b3b8[4];
extern int DAT_0056b3c0[4];
extern int DAT_0056b448[4];
extern int DAT_0056b480[4];
extern long long DAT_0056b5a8[4];
extern long long DAT_0056b5b0[4];
extern long long DAT_0056b5b8[4];
extern long long DAT_0056b5c0[4];
extern long long DAT_0056b5c8[4];
extern long long DAT_0056b5d0[4];
extern long long DAT_0056b5d8[4];
extern long long DAT_0056b5e0[4];
extern long long DAT_0056b5e8[4];
extern long long DAT_0056b5f0[4];
extern int DAT_0056b5f8[4];
extern int DAT_0056b608[4];
extern int DAT_0056ba00[16];
extern int DAT_0056ba20[4];
void FUN_001ff3b0(int arg0) {
    int s;
    int f;
    int n, a;
    s = DAT_00491478[0] & arg0;
    if (s != 0) {
        DAT_0056b5a8[0] += 1;
    }
    if (DAT_00568e50[0] == 0) {
        if (s & 4) {
            DAT_0056b5c0[0] += 1;
            FUN_001f8b50();
            s = DAT_00491478[0] & arg0;
        }
        if (s & 0x193) {
            DAT_0056b608[0] = FUN_00204ea0();
            s = DAT_00491478[0] & arg0;
            if (DAT_0056b608[0] == 0 || (DAT_0056b608[0] == 1 && (s & 0x100))) {
                if (s & 0x10) {
                    FUN_001fffb0(DAT_0056b608[0]);
                    s |= 0x80;
                    DAT_00491478[0] |= 0x80;
                }
                if (s & 1) {
                    FUN_00200980();
                    s = DAT_00491478[0] & arg0;
                }
                if (s & 2) {
                    if (DAT_00568e50[0] == 0) {
                        f = DAT_0056b480[0];
                        a = f & 0x10;
                        n = 0;
                        if (a && (f & 0x20)) {
                            n++;
                            DAT_0056ba00[0] = DAT_0056b3b8[0];
                        } else if (f & 0x20) {
                            n++;
                            DAT_0056ba00[0] = DAT_0056b3b4[0];
                        } else if (a) {
                            n++;
                            DAT_0056ba00[0] = DAT_0056b3b0[0];
                        }
                        if (f & 0x40) {
                            DAT_0056ba00[n] = DAT_0056b3c0[0];
                            n++;
                        }
                        if (f & 0x1C00) {
                            DAT_0056ba00[n] = DAT_0056b3c0[(f & 0x1C00) >> 10];
                            n++;
                        }
                        DAT_0056ba00[n] = DAT_0056b448[0];
                        DAT_0056ba20[0] = n + 1;
                        if (DAT_0056ba20[0] > 1) {
                            DAT_0056b5f8[0] = 1;
                        } else {
                            DAT_0056b5f8[0] = 0;
                        }
                    }
                }
                if (s & 0x80) {
                    FUN_00201a90();
                }
            }
        }
        if (s & 1) DAT_0056b5b0[0] += 1;
        if (s & 2) DAT_0056b5b8[0] += 1;
        if (s & 0x10) DAT_0056b5d0[0] += 1;
        if (s & 0x80) DAT_0056b5e8[0] += 1;
        if (s & 8) DAT_0056b5c8[0] += 1;
        if (s & 0x100) DAT_0056b5f0[0] += 1;
        if (s & 0x40) DAT_0056b5e0[0] += 1;
        if (s & 0x20) DAT_0056b5d8[0] += 1;
    }
}
