/* 0x002656c8 — FUN_002656c8 (172 bytes). Drops one reference from DAT_0049d984; on the last one, runs the shutdown steps FUN_00264aa0..FUN_00264f98, restores the priority of thread DAT_0049da28 to DAT_004a52b8, clears both FUN_0027e8e0/FUN_0027e8f8 hooks, clears DAT_0049d988 and finishes with FUN_0027ec50. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_0049d984;
extern int DAT_0049d988;
extern volatile int DAT_0049da28; /* thread id; retail re-reads it through its address (volatile) */
extern int DAT_004a52b8;
int ChangeThreadPriority(int thread_id, int priority);
int FUN_00264aa0(void);
int FUN_00264b88(void);
int FUN_00264c58(void);
int FUN_00264d28(void);
int FUN_00264df8(void);
int FUN_00264ec8(void);
void FUN_00264f98(void);
int FUN_0027e8e0(int a, int b);
void FUN_0027e8f8(int a, int b);
int FUN_0027ec50(void);

void FUN_002656c8(void) {
    if (--DAT_0049d984 == 0) {
        FUN_00264aa0();
        FUN_00264b88();
        FUN_00264c58();
        FUN_00264df8();
        FUN_00264d28();
        FUN_00264ec8();
        FUN_00264f98();
        ChangeThreadPriority(DAT_0049da28, DAT_004a52b8);
        FUN_0027e8e0(0, 0);
        FUN_0027e8f8(0, 0);
        DAT_0049d988 = 0;
        FUN_0027ec50();
    }
}
