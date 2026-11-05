/* 0x001236b8 — FUN_001236b8 (24 bytes). Raises signal 6 through FUN_00129ba0 and then exits with status 1 through
 * thunk_FUN_001145c8 (exit), never returning. The shape of newlib's abort() (hypothesis: SIGABRT = 6). Sony EE GCC
 * 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00129ba0(int sig);
void thunk_FUN_001145c8(int status) __attribute__((noreturn));

void FUN_001236b8(void) {
    /* The loop is newlib's; with the callee marked noreturn it also keeps the second call a jal instead of a tail jump. */
    for (;;) {
        FUN_00129ba0(6);
        thunk_FUN_001145c8(1);
    }
}
