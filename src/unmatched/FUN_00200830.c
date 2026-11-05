struct P { long long m0; long long m8; int p16; struct P *next; int sh; int pad28; int tab[1]; };
struct E { int w0; int w4; };
extern long long DAT_0056b478[2];
extern struct E DAT_0056b4a0[16];
extern int DAT_00562da0[16];
extern int DAT_0056b480[4];
extern int DAT_0056b490[4];
int FUN_00200830(struct P *p, long long *out) {
    int res = 0;
    long long m;
    int i;
    int j;
    int w;
    int k;
    int f;
    int lo;
    int hi;
    struct E *e;
    for (; p != 0; p = p->next) {
        m = p->m0;
        if (m == (m & DAT_0056b478[0])) {
            if (!(p->m8 & DAT_0056b478[0])) {
                for (i = 0; i < 32; i++) {
                    if (m & (1LL << i)) break;
                }
                j = 32;
                for (; j > 0; j--) {
                    if (m & (1LL << j)) break;
                }
                e = &DAT_0056b4a0[i];
                w = e->w0 | (DAT_0056b4a0[j].w0 << p->sh);
                k = p->tab[w];
                if (k != -1) {
                    e->w0 = w;
                    e->w4 = (int)p->tab;
                    *out &= ~p->m0 | (1LL << i);
                    f = *(int *)((char *)DAT_00562da0 + (k << 6) + 40);
                    lo = f & 0x30;
                    if (lo != 0) {
                        DAT_0056b480[0] = (DAT_0056b480[0] & 0x1cc0) | lo;
                    }
                    hi = f & 0x300;
                    if (hi != 0) {
                        DAT_0056b490[0] = hi;
                    }
                    res = 1;
                }
            }
        }
    }
    return res;
}
