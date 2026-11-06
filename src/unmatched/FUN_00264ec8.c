/* Stops the thread DAT_0049da1c: until it reports exit in DAT_0049da50, raises the exit request
 * DAT_0049da48, boosts it to priority 1, wakes it and resumes it with FUN_00264368; then clears
 * both flags and the thread id. */
int ChangeThreadPriority(int threadId, int priority);
int WakeupThread(int threadId);
int FUN_00264368(int threadId);
extern volatile long DAT_0049da50; /* thread exited */
extern volatile long DAT_0049da48; /* exit requested */
extern volatile int DAT_0049da1c;  /* thread id */

void FUN_00264ec8(void) {
    while (DAT_0049da50 == 0) {
        DAT_0049da48 = 1;
        ChangeThreadPriority(DAT_0049da1c, 1);
        WakeupThread(DAT_0049da1c);
        FUN_00264368(DAT_0049da1c);
    }
    DAT_0049da50 = 0;
    DAT_0049da48 = 0;
    DAT_0049da1c = 0;
}
