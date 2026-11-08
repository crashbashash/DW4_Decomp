/* Busy-wait delay of 256 iterations. */
void FUN_002753a8(void) {
    int count;

    /* matching construct: hand search — GCC deletes this empty loop when the test is `count >= 0` */
    for (count = 0x1FFF; count > -1; count -= 32) {
    }
}
