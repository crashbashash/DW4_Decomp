/* 0x002753a8 — FUN_002753a8 (44 bytes). Busy-wait delay of 256 iterations. Sony EE GCC 2.96 unit
   (docs/engine/sd-prologue.md). */
void FUN_002753a8(void) {
    int count;

    count = 0x1FFF;
    do {
        count -= 32;
        /* asm-body: reason=an empty C loop is deleted by GCC; one explicit nop keeps the delay loop (ee-gcc
           then adds its four r5900 short-loop pad nops) tried=empty do/while and for loops (deleted), asm("") (4 nops) */
        __asm__ volatile("nop");
    } while (count >= 0);
}
