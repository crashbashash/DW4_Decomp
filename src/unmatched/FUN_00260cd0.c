/* Busy-waits 50000 empty iterations; the five no-ops in the loop are ee-gcc's R5900 short-loop
 * padding, not source. */
void FUN_00260cd0(void) {
    int i;

    for (i = 0; i < 50000; i++) {
    }
}
