int memset();
int FUN_00244e30();
int Memory_AllocateDefaultBuffer();
int Memory_FreeBufferAliasA();
extern unsigned int DAT_004986a0[4];
extern unsigned int DAT_004986a8[4];
extern unsigned int DAT_0056dea0[4];
extern int *DAT_0056dea8[4];
extern int DAT_0056deb0[4];
void FUN_00244e70(void) {
    int *a0;
    unsigned int bits;
    unsigned int s0;
    int *s4;
    unsigned int s3;
    unsigned int s2;
    int s1;

    if (DAT_0056dea8[0] == 0) {
        DAT_0056dea8[0] = (int *)Memory_AllocateDefaultBuffer(DAT_004986a8[0] * 4);
        memset(DAT_0056dea8[0], 0, DAT_004986a8[0] * 4);
        return;
    }
    if (DAT_0056deb0[0] == 0) {
        if (DAT_0056dea0[0] == 0) {
            Memory_FreeBufferAliasA(DAT_0056dea8[0], DAT_0056dea0[0]);
            DAT_0056dea8[0] = 0;
            DAT_004986a8[0] = 0x400;
            return;
        }
        bits = DAT_004986a0[0];
        s3 = bits;
        if (DAT_004986a8[0] < DAT_0056dea0[0]) {
            s3 = bits + 1;
        } else if (DAT_0056dea0[0] < (DAT_004986a8[0] >> 1) && bits > 10) {
            s3 = bits - 1;
        }
        if (s3 != bits) {
            s2 = 1 << s3;
            s0 = s2 * 4;
            s1 = Memory_AllocateDefaultBuffer(s0);
            memset(s1, 0, s0);
            for (s0 = 0; s0 < DAT_004986a8[0]; s0++) {
                a0 = (int *)DAT_0056dea8[0][s0];
                while (a0 != 0) {
                    s4 = (int *)a0[1];
                    FUN_00244e30(a0, s1, s2, s3);
                    a0 = s4;
                }
            }
            DAT_004986a8[0] = s2;
            DAT_004986a0[0] = s3;
            Memory_FreeBufferAliasA(DAT_0056dea8[0]);
            DAT_0056dea8[0] = (int *)s1;
        }
    }
}
