struct BitLayoutEntry { unsigned short a : 1; unsigned short c : 15; unsigned short b : 15; unsigned short d : 1; };
extern struct BitLayoutEntry DAT_00568db0[];
void FUN_001eb6a0(int arg0, int *arg1) {
    struct BitLayoutEntry *e;
    int a;
    int c;
    int b;
    int n;
    int v;
    e = &DAT_00568db0[arg0];
    b = e->b;
    a = e->a;
    c = e->c;
    n = (c + (a + b)) / 8;
    if (n != 0) {
        if (a != 0) {
            v = 1 << b;
        } else {
            v = 0;
        }
        *arg1 = (1 << (0x17 - c)) + v;
        return;
    }
    *arg1 = 0;
}
