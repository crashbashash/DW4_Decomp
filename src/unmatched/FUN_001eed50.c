int FUN_001ee1a0();
int FUN_00330770();

void FUN_001eed50(void *arg0) {
    void *temp_a0;

    temp_a0 = (void *)(*(int *)((char *)(arg0) + 20));
    if (temp_a0 != 0) {
        FUN_001eed50(temp_a0);
    }
    FUN_00330770(*(int *)((char *)(arg0) + 12), 0xB);
    FUN_001ee1a0(arg0);
}
