/* The lower bound is spelled `arg1 <= -1` so it fuses into slti at. */
int FUN_002d8370(void *arg0, int arg1) {
    void *temp_a0;
    if (!(arg1 <= -1)) {
        temp_a0 = (void *)(*(int *)((char *)(arg0) + 28));
        if (arg1 < *(int *)((char *)(temp_a0) + 8)) {
            return *(int *)(*(int *)((char *)(temp_a0) + 16) + (arg1 * 4));
        }
    }
    return 0;
}
