typedef struct S_ref { char pad4[4]; int f4; } S_ref;
typedef struct T { char pad28[28]; unsigned char f28; char pad29[15]; S_ref *f44; S_ref *f48; } T;
int FUN_00308e00();
int Gap__Core__igObject__vfunc_10();
int igObject_Destroy();

void Gap__Core__igResource__vfunc_12(T *arg0) {
    S_ref *temp_a0;
    S_ref *temp_a0_2;

    if (arg0->f28 == 1) {
        FUN_00308e00();
    }
    temp_a0 = arg0->f44;
    if (temp_a0 != 0) {
        temp_a0->f4 = temp_a0->f4 - 1;
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f44 = 0;
    temp_a0_2 = arg0->f48;
    if (temp_a0_2 != 0) {
        temp_a0_2->f4 = temp_a0_2->f4 - 1;
        if (((unsigned long long) ((long long) temp_a0_2->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->f48 = 0;
    Gap__Core__igObject__vfunc_10(arg0);
}
