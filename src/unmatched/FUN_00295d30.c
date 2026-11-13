int FUN_00295c00();
int FUN_002968c0();
int FUN_002971b0();
int mwsfd_Error();
extern int DAT_004f3950[4];
extern int DAT_004f3988[4];
void FUN_00295d30(void **arg0, int arg1, int arg2, int arg3) {
    if (FUN_002968c0() == 0) {
        mwsfd_Error(&DAT_004f3950[0]);
        return;
    }
    if (arg1 == 0) {
        mwsfd_Error(&DAT_004f3988[0]);
        return;
    }
    ((int (*)())*(int *)((char *)((*arg0)) + 60))(arg0, FUN_002971b0(arg0));
    FUN_00295c00(arg0, arg1, arg2, arg3);
}
