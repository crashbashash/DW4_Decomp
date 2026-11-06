int FUN_002855d8();
int FUN_0028b098();

void FUN_00285910(int arg0, int *arg1, int *arg2) {
    void *temp_s0;

    temp_s0 = (void *)(arg0 + 0x160);
    if (FUN_0028b098() != 0) {
        FUN_002855d8(0, 0xFF03020E);
        return;
    }
    *arg1 = *(int *)((char *)(temp_s0) + 208);
    *arg2 = *(int *)((char *)(temp_s0) + 212);
}
