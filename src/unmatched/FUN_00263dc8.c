/* 0x00263dc8 — FUN_00263dc8 (88 bytes). Thread body: calls FUN_00263db0 until the exit request DAT_0049da38 is set, then sets the exited flag DAT_0049da40 and ends the thread with ExitDeleteThread. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00263db0(void);
void ExitDeleteThread(void);
extern volatile long DAT_0049da38; /* exit requested */
extern volatile long DAT_0049da40; /* exited */

void FUN_00263dc8(void) {
    while (DAT_0049da38 == 0) {
        FUN_00263db0();
    }
    DAT_0049da40 = 1;
    ExitDeleteThread();
}
