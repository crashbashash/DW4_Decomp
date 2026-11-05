typedef struct S { char pad44[44]; unsigned char f2c; char pad45[7]; int f34; int f38; char *f3c; } S;
int FUN_002ec570();

int Gap__Core__igMediaFile__vfunc_35(S *arg0, unsigned char arg1) {
    int temp_a1;

    if (arg0->f2c != 0) {
        return -1;
    }
    temp_a1 = arg0->f38 + 1;
    if (temp_a1 >= arg0->f34) {
        FUN_002ec570(arg0, temp_a1);
    }
    arg0->f3c[arg0->f38] = arg1;
    arg0->f38 = arg0->f38 + 1;
    return arg1;
}
