extern int DAT_00587220[64];
int FUN_0032ac70(int a, unsigned b);
unsigned FUN_0032ad50(int a, unsigned b, unsigned c, unsigned d, int e);
int Gap__Core__igPsx2CallStackTracer__vfunc_60(void *self, unsigned int addr, unsigned int len) {
    unsigned int end, s5, s4, i, lo, hi, t, loB, hiB;
    int p, r;
    end = addr + len;
    s5 = addr >> 26;
    s4 = end >> 26;
    loB = (addr & 0x3FFFFFF) >> 12;
    hiB = (end & 0x3FFFFFF) >> 12;
    i = s5;
    if (len == 0) return 0;
    {
        while (i <= s4) {
            p = DAT_00587220[i];
            if (p != 0) {
                lo = loB;
                if (i > s5) lo = 0;
                hi = hiB;
                if (i < s4) hi = 0x4000;
                r = FUN_0032ac70(p, lo);
                if (r != 1) break;
                t = FUN_0032ad50(p, lo, len, hi - lo, r);
                if (t >= len) return 1;
                len -= t;
            }
            i++;
        }
    }
    return 0;
}
