/* Stops the thread DAT_0049da30: until it reports exit in DAT_0049da90, raises the exit request
 * DAT_0049da88, boosts it to priority 1, wakes it and resumes it with FUN_00264368; then clears
 * both flags and the thread id. */
int ChangeThreadPriority(int threadId, int priority);
int WakeupThread(int threadId);
int FUN_00264368(int threadId);
extern volatile long DAT_0049da90; /* thread exited */
extern volatile long DAT_0049da88; /* exit requested */
extern volatile int DAT_0049da30;  /* thread id */

void FUN_00264b88(void) {
    while (DAT_0049da90 == 0) {
        DAT_0049da88 = 1;
        ChangeThreadPriority(DAT_0049da30, 1);
        WakeupThread(DAT_0049da30);
        FUN_00264368(DAT_0049da30);
    }
    DAT_0049da90 = 0;
    DAT_0049da88 = 0;
    DAT_0049da30 = 0;
}
