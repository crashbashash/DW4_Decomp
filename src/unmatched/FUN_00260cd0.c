/* 0x00260cd0 — FUN_00260cd0 (44 bytes). Busy-waits 50000 empty iterations; the five no-ops in the loop are ee-gcc's R5900 short-loop padding, not source. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00260cd0(void) {
    int i;

    for (i = 0; i < 50000; i++) {
    }
}
