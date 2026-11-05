/* 0x00264f98 — FUN_00264f98 (204 bytes). Until the 64-bit flag DAT_0049da40 is set, raises the request DAT_0049da38 and wakes the thread DAT_0049da18 at priority 1 (then FUN_00264368 on it); afterwards clears both flags and the thread id. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* All three are shared with the woken thread: retail re-reads every access, so they are volatile. */
extern volatile long DAT_0049da40;
extern volatile long DAT_0049da38;
extern volatile int DAT_0049da18;
int ChangeThreadPriority(int thread_id, int priority);
int WakeupThread(int thread_id);
int FUN_00264368(int thread_id);

void FUN_00264f98(void) {
    while (DAT_0049da40 == 0) {
        DAT_0049da38 = 1;
        ChangeThreadPriority(DAT_0049da18, 1);
        WakeupThread(DAT_0049da18);
        FUN_00264368(DAT_0049da18);
    }
    DAT_0049da40 = 0;
    DAT_0049da38 = 0;
    DAT_0049da18 = 0;
}

