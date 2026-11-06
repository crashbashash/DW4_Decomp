/* Releases one level of the recursive library lock; on the last release clears the owner and
 * signals the lock semaphore. */
int SignalSema(int semaphoreId);
extern int DAT_00482590; /* lock semaphore id */
extern int DAT_00485908; /* owning thread, -1 when free */
extern int DAT_0048590c; /* recursion depth */

void FUN_00127390(void) {
    if (--DAT_0048590c == 0) {
        DAT_00485908 = -1;
        SignalSema(DAT_00482590);
    }
}
