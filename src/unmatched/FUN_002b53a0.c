/* True when the handle is non-null, arg1 is not negative, FUN_002b52d8(handle, arg1) succeeds and
 * FUN_0012aba0(handle+20, DAT_004f5a58, 1) reports 0 (a match). */
int FUN_0012aba0();
int FUN_002b52d8();

extern char DAT_004f5a58[];

int FUN_002b53a0(char *handle, int arg1) {
    if (handle == 0 || arg1 < 0) {
        return 0;
    }
    if (FUN_002b52d8(handle, arg1) == 0) {
        return 0;
    }
    return FUN_0012aba0(handle + 20, DAT_004f5a58, 1) == 0;
}
