/* 0x0029c470 — FUN_0029c470 (36 bytes). True when FUN_0026bd20 reports a value of 2 or more. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern unsigned int FUN_0026bd20(void *handle);

int FUN_0029c470(void *handle) {
    if (FUN_0026bd20(handle) < 2) {
        return 0;
    }
    return 1;
}
