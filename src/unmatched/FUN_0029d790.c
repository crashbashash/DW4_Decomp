/* 0x0029d790 — FUN_0029d790 (60 bytes). Runs FUN_0029d7d0 for channels 0, 1 and 2. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_0029d7d0(void *handle, int channel);

void FUN_0029d790(void *handle) {
    FUN_0029d7d0(handle, 0);
    FUN_0029d7d0(handle, 1);
    FUN_0029d7d0(handle, 2);
}
