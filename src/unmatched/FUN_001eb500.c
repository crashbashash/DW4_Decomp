struct E { long long mask; char pad[56]; };
extern struct E DAT_00562da0[];
extern int DAT_00568da0[4];
int FUN_001eb500(int arg0, int arg1) {
    int cnt;
    long long v;
    unsigned int n;
    int r;

    r = 0;
    for (; arg1 <= DAT_00568da0[0]; arg1++) {
        cnt = 0;
        n = 0;
        v = DAT_00562da0[arg1].mask;
        do {
            if (v & 1) {
                cnt += 1;
            }
            n += 1;
            v = v >> 1;
        } while (n < 32U);
        if (cnt == arg0) {
            r = arg1; break;
        }
    }
    return r;
}
