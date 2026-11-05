/* 0x00127310 — FUN_00127310 (124 bytes). Recursive lock: the owning thread only bumps the depth count; any other
 * thread waits on the semaphore D_00482590 and then takes ownership. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int GetThreadId(void);
int WaitSema(int sema_id);

extern int D_00485908;  /* owning thread id */
extern int D_0048590c;  /* recursion depth */
extern int D_00482590;  /* semaphore id */

void FUN_00127310(void) {
    int thread = GetThreadId();

    if (D_00485908 == thread) {
        D_0048590c++;
        return;
    }
    WaitSema(D_00482590);
    D_00485908 = thread;
    D_0048590c++;
}
