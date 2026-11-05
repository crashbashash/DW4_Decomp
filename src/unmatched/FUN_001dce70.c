struct S { char pad[8]; int f8; char pad2[4]; long long *f16; };
int FUN_001002f0(long long, long long);
int FUN_001dce70(struct S *arg0, long long arg1) {
    int temp_s0;
    int temp_s1;
    int var_s2;
    int var_s3;

    var_s3 = 0;
    temp_s0 = arg0->f8;
    var_s2 = temp_s0 - 1;
    while (var_s3 < var_s2) {
        temp_s1 = (var_s2 + var_s3 + 1) >> 1;
        if (FUN_001002f0(arg1, arg0->f16[temp_s1]) != 0) {
            var_s2 = temp_s1 - 1;
        } else {
            var_s3 = temp_s1;
        }
    }
    if (temp_s0 != 0) {
        if (FUN_001002f0(arg0->f16[var_s3], arg1) != 0) {
            var_s3 += 1;
        }
    }
    return var_s3;
}
