typedef struct P { char pad8[8]; int f8; int fc; int f10; } P;
int FUN_00300e50();
int FUN_00300f50();

int Gap__Core__igPrimLengthArray1_1__vfunc_23(P *arg0, int arg1, int arg2) {
    int temp_s0;

    arg0->f10 = arg2;
    arg0->fc = arg1;
    temp_s0 = arg0->fc * 4;
    if (temp_s0 != 0) {
        arg0->f8 = FUN_00300e50(arg0, arg0->f8, temp_s0);
    } else {
        if (arg0->f8 != 0) {
            FUN_00300f50(arg0, arg0->f8);
        }
        arg0->f8 = 0;
    }
    return temp_s0;
}
