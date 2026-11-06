/* Dispatches on the mode byte at 0x004a9289: mode 1 returns twice FUN_00272380's result, mode 2
 * tail-calls FUN_002723c0, any other mode returns 0. */
extern int FUN_00272380(void);
extern int FUN_002723c0(void);
extern signed char DAT_004a9289;

int FUN_00272460(void) {
    if (DAT_004a9289 == 1) {
        return FUN_00272380() * 2;
    }
    if (DAT_004a9289 == 2) {
        return FUN_002723c0();
    }
    return 0;
}
