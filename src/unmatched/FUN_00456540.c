typedef struct N { int w0, w4, w8, wC; int f10; int f14; struct N *f18; } N;
int FUN_004559a0(int a, int b);

int FUN_00456540(int arg0, N *arg1, N *arg2, int arg3) {
    int r;

    if (arg1 != 0) {
        if (arg1 == arg2) {
            return r;
        }
        FUN_004559a0(arg1->f10, arg3);
        r = FUN_00456540(arg0, arg1->f18, arg2, arg3);
    }
    return r;
}
