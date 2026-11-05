int sprintf();
int FUN_00230298(float);
int FUN_002eb010();
int StringPool_Construct();
int StringPool_Intern();
extern int DAT_004f9a70[4];
extern int DAT_00586f20[4];
void FUN_002e3760(int *arg0, int arg1, float *arg2) {
    char sp20[1024];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004f9a70[0], FUN_00230298(*arg2));
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
