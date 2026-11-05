/* 0x00263e20 — FUN_00263e20 (152 bytes). Thread body: until the exit request DAT_0049da48 is set, counts a pass in DAT_0049d9e8 and runs FUN_0027ea98 with the busy flag DAT_0049d9cc raised, then FUN_00264350; finally sets the exited flag DAT_0049da50 and ends the thread. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0027ea98(void);
void FUN_00264350(void);
void ExitDeleteThread(void);
extern volatile long DAT_0049da48; /* exit requested */
extern volatile long DAT_0049da50; /* exited */
extern volatile long DAT_0049d9e8; /* pass count */
extern volatile int DAT_0049d9cc;  /* busy while FUN_0027ea98 runs */

void FUN_00263e20(void) {
    while (DAT_0049da48 == 0) {
        DAT_0049d9e8++;
        DAT_0049d9cc = 1;
        FUN_0027ea98();
        DAT_0049d9cc = 0;
        FUN_00264350();
    }
    DAT_0049da50 = 1;
    ExitDeleteThread();
}
