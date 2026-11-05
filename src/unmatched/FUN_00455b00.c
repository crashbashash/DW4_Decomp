int igMatrix44f_SetIdentity();
int FUN_004578c0();
int Gap__Core__igObject__vfunc_11();
int Matrix44_SetTranslation();
extern int DAT_0058c3e8[4];
void FUN_00455b00(int arg0, int arg1) {
    int args[4];
    float vec[3];

    Gap__Core__igObject__vfunc_11();
    if (arg1 != 0) {
        igMatrix44f_SetIdentity(arg0 + 0x20);
        vec[0] = 0.375f;
        vec[2] = -0.5f;
        vec[1] = 0.375f;
        Matrix44_SetTranslation(arg0 + 0x20, vec);
        args[0] = 2;
        args[1] = 0;
        args[2] = DAT_0058c3e8[0];
        FUN_004578c0(arg0, args);
    }
}
