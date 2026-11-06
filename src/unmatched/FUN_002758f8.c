/* Issues FUN_00272780(handle, 0, 0) and, if that succeeds, FUN_00272780(handle, 0, 2), each
 * bracketed by FUN_002725a0 trace markers (0x4700/0x4701, 0x4800/0x4801); returns the second
 * result, or 0 when either call fails. */
extern void FUN_002725a0(int marker);
extern int FUN_00272780(int handle, int a1, int a2);

int FUN_002758f8(int handle) {
    int result;

    FUN_002725a0(0x4700);
    result = FUN_00272780(handle, 0, 0);
    FUN_002725a0(0x4701);
    if (result < 0) {
        return 0;
    }
    FUN_002725a0(0x4800);
    result = FUN_00272780(handle, 0, 2);
    FUN_002725a0(0x4801);
    if (result < 0) {
        return 0;
    }
    return result;
}
