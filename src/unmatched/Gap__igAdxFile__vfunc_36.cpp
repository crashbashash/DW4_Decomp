extern "C" {
typedef struct O { char pad[63]; char f3f; char pad2[8]; int f48; char pad3[4]; int f50; char pad4[12]; int f60; } O;
int FUN_002623f8(int, int, int);

int Gap__igAdxFile__vfunc_36(O *arg0, int arg1, int arg2) {
    int n;
    int r;

    n = arg1 / arg0->f50;
    arg0->f3f = 0;
    switch (arg2) {
    case 0:
        arg0->f48 = arg1;
        FUN_002623f8(arg0->f60, n, 0);
        break;
    case 1:
        arg0->f48 = arg0->f48 + arg1;
        FUN_002623f8(arg0->f60, n, 1);
        break;
    case 2:
        r = FUN_002623f8(arg0->f60, n, 2);
        arg0->f48 = r * arg0->f50;
        break;
    }
    return -1;
}
}
