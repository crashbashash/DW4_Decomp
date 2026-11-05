/* 0x00264df8 — FUN_00264df8 (204 bytes). Stops the thread DAT_0049da24: until it reports exit in DAT_0049da70, raises the exit request DAT_0049da68, boosts it to priority 1, wakes it and resumes it with FUN_00264368; then clears both flags and the thread id. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int ChangeThreadPriority(int threadId, int priority);
int WakeupThread(int threadId);
int FUN_00264368(int threadId);
extern volatile long DAT_0049da70; /* thread exited */
extern volatile long DAT_0049da68; /* exit requested */
extern volatile int DAT_0049da24;  /* thread id */

void FUN_00264df8(void) {
    while (DAT_0049da70 == 0) {
        DAT_0049da68 = 1;
        ChangeThreadPriority(DAT_0049da24, 1);
        WakeupThread(DAT_0049da24);
        FUN_00264368(DAT_0049da24);
    }
    DAT_0049da70 = 0;
    DAT_0049da68 = 0;
    DAT_0049da24 = 0;
}
