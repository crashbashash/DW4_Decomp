/* Leaves the nestable ADX lock: on the last level suspends the ADX server thread (DAT_0049da18)
 * with FUN_002643d0 and restores the calling thread's saved priority; clamps the depth at zero. */
int GetThreadId(void);
int ChangeThreadPriority(int threadId, int priority);
int FUN_002643d0(int threadId);
extern int DAT_0049d9c0;          /* lock depth */
extern volatile int DAT_0049da18; /* ADX server thread id */
extern int DAT_004a52b0;          /* priority before locking */

void FUN_00263c08(void) {
    if (--DAT_0049d9c0 == 0) {
        FUN_002643d0(DAT_0049da18);
        DAT_0049da18; /* matching construct: retail re-reads the thread id after the call (dead load) */
        ChangeThreadPriority(GetThreadId(), DAT_004a52b0);
    }
    if (DAT_0049d9c0 < 0) {
        DAT_0049d9c0 = 0;
    }
}
