int FUN_00294ef8(int);
int mwsfd_Error(int *);
int FUN_002abde0(int);
extern int DAT_004f36a8[4];
int FUN_00295398(void *arg0) {
    int var_v0;

    var_v0 = FUN_002abde0(*(int *)((char *)arg0 + 64));
    if (var_v0 != 0) {
        FUN_00294ef8(-0x133);
        mwsfd_Error(&DAT_004f36a8[0]);
        var_v0 = -0x133;
    }
    return var_v0;
}
