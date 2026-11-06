int FUN_001c5b80();
int FUN_001c5d10();
int igObject_Destroy();
struct R { int w0; int rc; };
struct L { char pad[8]; int cnt; int cap; int *data; };
struct S { char pad[64]; struct L *f64; };

void Gap__Sg__igProjectiveShadowShader__vfunc_17(struct S *arg0) {
    int temp_s1;
    int var_s0;
    struct R *temp_a0;
    struct L *temp_v1;

    FUN_001c5b80();
    temp_v1 = arg0->f64;
    if (temp_v1 != 0) {
        temp_s1 = temp_v1->cnt;
        for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
            FUN_001c5d10(arg0, arg0->f64->data[var_s0]);
        }
        temp_a0 = (struct R *)arg0->f64;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f64 = 0;
    }
}
