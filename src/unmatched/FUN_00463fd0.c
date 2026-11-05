int FUN_00457e90();
int igObject_Destroy();

typedef struct R { int w0; int refs; } R;
typedef struct S { char pad[8]; R *obj; int f12; } S;

void FUN_00463fd0(S *arg0, R *arg1) {
    R *temp_a0;
    R *temp_a0_2;

    temp_a0 = arg0->obj;
    if (temp_a0 != 0) {
        FUN_00457e90(temp_a0, 0);
    }
    if (arg1 != 0) {
        arg1->refs = arg1->refs + 1;
    }
    temp_a0_2 = arg0->obj;
    if (temp_a0_2 != 0) {
        temp_a0_2->refs = temp_a0_2->refs - 1;
        if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->obj = arg1;
    if (arg1 != 0) {
        FUN_00457e90(arg1, arg0->f12);
    }
}
