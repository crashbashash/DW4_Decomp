/* 0x0029a450 — FUN_0029a450 (104 bytes). Waits for the handle's +100 flag to clear, at most 10 rounds of FUN_0029af90(handle, 1), FUN_00265330(), FUN_0029af90(handle, 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029af90(void *handle, int on);
void FUN_00265330(void);

struct Handle0029a450 {
    char pad0[100];
    int busy; /* +100 */
};

void FUN_0029a450(struct Handle0029a450 *handle) {
    int i;

    for (i = 0; i < 10; i++) {
        FUN_0029af90(handle, 1);
        FUN_00265330();
        FUN_0029af90(handle, 0);
        if (handle->busy == 0) {
            break;
        }
    }
}
