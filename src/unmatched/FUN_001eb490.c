typedef struct E { long long key; int pad[8]; unsigned int f40; int pad2[5]; } E;
extern E DAT_00562da0[];
extern int DAT_00568da0[4];
int FUN_001eb490(long long arg0, int *arg1) {
    int i;
    int n = 0;

    for (i = 0; DAT_00568da0[0] >= i; i++) {
        E *e = &DAT_00562da0[i];
        if (arg0 == e->key) {
            arg1[(e->f40 & 0xFFFF0000) >> 16] = i;
            n++;
        }
    }
    return n;
}
