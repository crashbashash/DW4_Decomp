/* FUN_00298d78 */
int FUN_002944b0();
int FUN_00297810();
int FUN_002b3bd8();

void FUN_00298d78(void *arg0) {
    int temp_v0;

    if (*(int *)((char *)(arg0) + 80) == 0) {
        temp_v0 = FUN_002944b0();
        if (temp_v0 != -1) {
            *(int *)((char *)(arg0) + 84) = temp_v0;
        } else {
            *(int *)((char *)(arg0) + 84) = 0x11;
        }
    }
    FUN_002b3bd8(FUN_00297810(arg0), *(int *)((char *)(arg0) + 84));
}
