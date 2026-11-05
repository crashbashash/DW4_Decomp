struct E { unsigned short flag : 1; unsigned short a : 15; unsigned short b : 15; unsigned short c : 1; };
extern struct E DAT_00568db0[4];
int FUN_001eb650(int arg0, int *arg1) {
    struct E *e;
    int r;

    e = &DAT_00568db0[arg0];
    r = e->flag + e->b;
    *arg1 = (0x96 - e->a) << 0x17;
    return r != 0;
}
