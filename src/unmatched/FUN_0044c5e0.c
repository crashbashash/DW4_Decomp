int FUN_00135430();
int FUN_0014aa70();
int ObjectRef_Destruct_001c6460();
int FUN_00233590();
int thunk_FUN_002ed460__002ff810();
extern int DAT_0052cc20[4];
extern int DAT_00541dd0[4];
int **FUN_0044c5e0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541dd0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x14), -1);
            FUN_00135430((int **)((char *)arg0 + 0x10), -1);
            FUN_00233590((int **)((char *)arg0 + 0xC), -1);
            FUN_0014aa70((int **)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
