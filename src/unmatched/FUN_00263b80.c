/* 0x00263b80 — FUN_00263b80 (132 bytes). Enters the nestable ADX lock: on the first level raises the calling thread to the priority in DAT_0049d990 (saving the old one and the thread id) and resumes the ADX server thread (DAT_0049da18) with FUN_00264368; always counts the level. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int GetThreadId(void);
int ChangeThreadPriority(int threadId, int priority);
int FUN_00264368(int threadId);
extern int DAT_0049d9c0;          /* lock depth */
extern int DAT_0049d990;          /* priority while locked */
extern volatile int DAT_0049da18; /* ADX server thread id */
extern int DAT_004a52b0;          /* priority before locking */
extern int DAT_004a52b4;          /* locking thread */

void FUN_00263b80(void) {
    int threadId;

    if (DAT_0049d9c0 == 0) {
        threadId = GetThreadId();
        DAT_004a52b0 = ChangeThreadPriority(threadId, DAT_0049d990);
        DAT_004a52b4 = threadId;
        FUN_00264368(DAT_0049da18);
        DAT_0049da18; /* matching construct: retail re-reads the thread id after the call (dead load) */
    }
    DAT_0049d9c0++;
}
