/* Busy-wait delay of 256 iterations. */
void FUN_002753a8(void) {
    int count;

    count = 0x1FFF;
    do {
        count -= 32;
        /* An empty C loop is deleted by GCC, so one explicit nop keeps the delay loop (ee-gcc then
         * adds its four r5900 short-loop pad nops). */
        __asm__ volatile("nop");
    } while (count >= 0);
}
