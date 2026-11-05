/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
extern int DAT_00586f20[4];
int *FUN_003cc550(int *arg0, int arg1) {
    int var_v0;
    int var_v0_2;

    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = StringPool_Intern(DAT_00586f20[0], arg1);
    }
    *arg0 = var_v0;
    return arg0;
}
} /* extern "C" */
