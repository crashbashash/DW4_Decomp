typedef struct E { unsigned short a:1; unsigned short c:15; unsigned short b:15; unsigned short d:1; } E;
extern int DAT_0048dce0[4];
extern E DAT_00568db0[];
int FUN_001eb730(int arg0) {
    E *p = &DAT_00568db0[arg0];
    int v = p->c + (p->a + p->b);
    int r = v / 8;
    switch (arg0) {
    case 0: case 1:
        if (r == 0) return 12;
        return r * 3;
    case 2:
        if (r == 0) return 8;
        return r * 2;
    case 3:
        if (r == 0) return DAT_0048dce0[0] * 4;
        r = r * DAT_0048dce0[0];
    case 4:
        break;
    }
    return r;
}
