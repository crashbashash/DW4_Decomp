typedef struct S { char pad8[8]; int f8; int fC; int f10; } S;
int FUN_00300e50();
int FUN_00300f50();

void Gap__igItemDataBaseList__vfunc_18(S *arg0) {
    int temp_s0;

    temp_s0 = arg0->f8;
    if (temp_s0 < arg0->fC) {
        if (temp_s0 != 0) {
            arg0->f10 = FUN_00300e50(arg0, arg0->f10, temp_s0 * 0xC);
            arg0->fC = temp_s0;
            return;
        }
        FUN_00300f50(arg0, arg0->f10);
        arg0->f10 = 0;
        arg0->fC = arg0->f8;
    }
}
