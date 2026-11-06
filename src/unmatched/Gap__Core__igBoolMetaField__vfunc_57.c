int sprintf();
int FUN_002eb010();
int StringPool_Construct();
int StringPool_Intern();
extern int DAT_004f9590[4];
extern int DAT_004f9598[4];
extern int DAT_004f95a0[4];
extern int DAT_00586f20[4];
void Gap__Core__igBoolMetaField__vfunc_57(int *arg0, void *arg1, unsigned char *arg2) {
    int sp20[256];
    int *var_a2;
    int var_v0;
    int var_v1;

    if (*arg2 != 0) {
        var_a2 = (int *)(&DAT_004f9590[0]);
    } else {
        var_a2 = (int *)(&DAT_004f9598[0]);
    }
    sprintf(sp20, &DAT_004f95a0[0], var_a2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern(DAT_00586f20[0], sp20);
    }
    *arg0 = var_v1;
}
