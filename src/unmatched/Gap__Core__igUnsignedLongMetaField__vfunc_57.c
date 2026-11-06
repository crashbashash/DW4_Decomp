int sprintf();
int FUN_002eb010();
int StringPool_Construct();
int StringPool_Intern();
extern int DAT_004f9bc0[4];
extern int DAT_00586f20[4];
void Gap__Core__igUnsignedLongMetaField__vfunc_57(int *arg0, int arg1, long long *arg2) {
    struct { int w; int pad[255]; } sp20;
    int var_v0;
    int var_v1;

    sprintf((int *)&sp20, &DAT_004f9bc0[0], *arg2);
    if ((int *)&sp20 == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern(DAT_00586f20[0], (int *)&sp20);
    }
    *arg0 = var_v1;
}
