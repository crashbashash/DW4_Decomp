extern int DAT_00587220[64];
extern unsigned int DAT_004c2610[4];
extern unsigned int DAT_00587320[4];
int FUN_0032ac70(int a, unsigned b);
unsigned FUN_0032ad50(int a, unsigned b, unsigned c, unsigned d, int e);
unsigned int Gap__Core__igPsx2CallStackTracer__vfunc_61(void *self, int size) {
    unsigned int s8;
    unsigned int base;
    int p;
    unsigned int s7;
    unsigned int s1;
    unsigned int s2;
    unsigned int s3;
    unsigned int s5;
    unsigned int s6;
    unsigned int v;
    unsigned int s4;
    int r;
    s4 = (unsigned int)(size + 0xFFF) >> 12;
    s1 = 0;
    s5 = DAT_004c2610[0];
    s6 = s5 >> 26;
    s3 = s6;
    s7 = DAT_00587320[0] >> 26;
    while (s3 <= s7) {
        s2 = 0;
        if (s3 == s6) {
            s2 = (DAT_004c2610[0] & 0x3FFFFFF) >> 12;
        }
        base = s3 << 26;
        if (s3 == s7) {
            s8 = (DAT_00587320[0] & 0x3FFFFFF) >> 12;
        } else {
            s8 = 0x4000;
        }
        p = DAT_00587220[s3];
        if (p != 0) {
            while (s2 < s8) {
                r = FUN_0032ac70(p, s2);
                if (r == 1) {
                    v = FUN_0032ad50(p, s2, s4, r, 3);
                    if (s1 == 0) {
                        s5 = base + (s2 << 12);
                    }
                    s1 += v;
                    if (s1 >= s4) {
                        return s5;
                    }
                } else {
                    v = FUN_0032ad50(p, s2, 0x4000, r, 3);
                    s1 = 0;
                }
                s2 += v;
            }
        }
        s3++;
    }
    return -1;
}
