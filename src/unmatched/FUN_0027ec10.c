/* Server-manager init: resets the state (FUN_0027eb68) on the first call and counts the init
 * reference 0x004baff4 up. */
extern void FUN_0027eb68(void);
extern volatile int DAT_004baff4;

void FUN_0027ec10(void) {
    if (DAT_004baff4 == 0) {
        FUN_0027eb68();
    }
    DAT_004baff4++;
}
