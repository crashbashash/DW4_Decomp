struct S { char pad[92]; float f92; float f96; float f100; float f104; };
void FUN_004661e0(struct S *arg0, int arg1, int arg2, float fparg0, float fparg1) {
    int temp_a1;
    temp_a1 = arg2 & 0xFFFF;
    if (temp_a1 == 0) {
        arg0->f100 = fparg0;
        arg0->f104 = fparg1;
    } else if (temp_a1 == 1) {
        arg0->f92 = fparg0;
        arg0->f96 = fparg1;
    }
}