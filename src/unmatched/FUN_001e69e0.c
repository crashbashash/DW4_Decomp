/* 0x001e69e0 — FUN_001e69e0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int FUN_001904f0();
int List_Resize();
int Matrix44_Copy();
struct S { char pad[8]; volatile int f8; int f12; char *f16; };

int FUN_001e69e0(struct S *arg0, int arg1) {
    char *temp_a0;
    char *temp_a1;
    int temp_v1;
    int var_s0;

    var_s0 = arg0->f8;
    if (var_s0 == 0) {
        if (var_s0 < arg0->f12) {
            arg0->f8 = arg0->f8 + 1;
        } else {
            List_Resize(arg0, var_s0 + 1, 0x40);
        }
        Matrix44_Copy(arg0->f16 + (var_s0 << 6), arg1);
    } else {
        temp_v1 = arg0->f8;
        if (temp_v1 == 0) {
            var_s0 = 0;
        } else {
            if (var_s0 < arg0->f12) {
                arg0->f8 = temp_v1 + 1;
            } else {
                List_Resize(arg0, var_s0 + 1, 0x40);
            }
            temp_a1 = arg0->f16;
            Matrix44_Copy(temp_a1 + (var_s0 << 6), temp_a1 + ((var_s0 - 1) << 6));
        }
        temp_a0 = arg0->f16 + ((arg0->f8 - 1) << 6);
        FUN_001904f0(temp_a0, temp_a0, arg1);
    }
    return var_s0;
}
