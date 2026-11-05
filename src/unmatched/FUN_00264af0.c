/* 0x00264af0 — FUN_00264af0 (148 bytes). Drops one ADXM initialisation reference; on the last one runs the thread shutdown functions, restores the start priority of thread DAT_0049da28 and runs the FUN_0027e8e0/FUN_0027e8f8/FUN_0027ec50 teardown. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00264aa0(void);
void FUN_00264c58(void);
void FUN_00264df8(void);
void FUN_00264d28(void);
void FUN_00264f98(void);
int ChangeThreadPriority(int threadId, int priority);
void FUN_0027e8e0(int a, int b);
void FUN_0027e8f8(int a, int b);
void FUN_0027ec50(void);
extern int DAT_0049d984;          /* initialisation count */
extern volatile int DAT_0049da28; /* thread id */
extern int DAT_004a52b8;          /* thread start priority */

void FUN_00264af0(void) {
    if (--DAT_0049d984 == 0) {
        FUN_00264aa0();
        FUN_00264c58();
        FUN_00264df8();
        FUN_00264d28();
        FUN_00264f98();
        ChangeThreadPriority(DAT_0049da28, DAT_004a52b8);
        FUN_0027e8e0(0, 0);
        FUN_0027e8f8(0, 0);
        FUN_0027ec50();
    }
}
