/* 0x00264d28 — FUN_00264d28 (204 bytes). Stops the thread DAT_0049da20: until it reports exit in DAT_0049da60, raises the exit request DAT_0049da58, boosts it to priority 1, wakes it and resumes it with FUN_00264368; then clears both flags and the thread id. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int ChangeThreadPriority(int threadId, int priority);
int WakeupThread(int threadId);
int FUN_00264368(int threadId);
extern volatile long DAT_0049da60; /* thread exited */
extern volatile long DAT_0049da58; /* exit requested */
extern volatile int DAT_0049da20;  /* thread id */

void FUN_00264d28(void) {
    while (DAT_0049da60 == 0) {
        DAT_0049da58 = 1;
        ChangeThreadPriority(DAT_0049da20, 1);
        WakeupThread(DAT_0049da20);
        FUN_00264368(DAT_0049da20);
    }
    DAT_0049da60 = 0;
    DAT_0049da58 = 0;
    DAT_0049da20 = 0;
}
