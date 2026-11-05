struct S { char pad[836]; int f836; int f840; int f844; int f848; int f852; int f856; int f860; };
int FUN_0017ccb0(struct S *, int, int, int *);

int FUN_0017cb80(struct S *arg0, int arg1, int *arg2) {
    int sp3C = 0;
    int r = -1;
    switch (arg1) {
    case 0:
        if (arg0->f836 == -1) {
            arg0->f836 = FUN_0017ccb0(arg0, 0, 8, &sp3C);
            arg0->f852 = sp3C;
        }
        r = arg0->f836;
        *arg2 = 0x10000;
        break;
    case 1:
        if (arg0->f840 == -1) {
            arg0->f840 = FUN_0017ccb0(arg0, 8, 0, &sp3C);
            arg0->f856 = sp3C;
        }
        r = arg0->f840;
        *arg2 = 0x10000;
        break;
    case 3:
    case 2:
        if (arg0->f844 == -1) {
            arg0->f844 = FUN_0017ccb0(arg0, 4, 4, &sp3C);
            arg0->f860 = sp3C;
        }
        *arg2 = 0x10000;
        r = arg0->f844;
        break;
    case 9:
        *arg2 = 7;
        break;
    case 10:
        *arg2 = 8;
        break;
    }
    return r;
}
