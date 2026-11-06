/* `arg3 > 0xFB` keeps the fused slti/bnez on at, and every path stores its own status. */
int FUN_00113038();
char *FUN_0032cb50();
int Memory_FreeBufferAliasA();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void FUN_0032cf70(int *arg0, int arg1, int arg2, int arg3, int arg4, int *arg5) {
    int var_v0;
    char *temp_v0;

    if (arg3 > 0xFB) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    temp_v0 = FUN_0032cb50(arg1, arg2);
    if (temp_v0 == 0) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (*temp_v0 == 0x63) {
        do {
            var_v0 = FUN_00113038(temp_v0, arg3, arg4);
        } while (var_v0 < 0);
    } else {
        var_v0 = FUN_00113038(temp_v0, arg3, arg4);
    }
    if (var_v0 < 0) {
        Memory_FreeBufferAliasA(temp_v0);
        *arg0 = DAT_004fb418[0];
        return;
    }
    *arg5 = var_v0;
    Memory_FreeBufferAliasA(temp_v0);
    *arg0 = DAT_004fb410[0];
}
