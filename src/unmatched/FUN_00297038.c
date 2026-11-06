int FUN_002ad950();

void FUN_00297038(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg0) + 64);
    if (arg1 == 1) {
        FUN_002ad950(temp_a0, 0x27, 1);
        return;
    }
    FUN_002ad950(temp_a0, 0x27, 0);
}
