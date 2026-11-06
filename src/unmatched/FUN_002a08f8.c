void FUN_002a08f8(int arg0) {
    void *temp_a0;
    void *temp_a1;

    temp_a1 = (void *)(arg0 + 0x98);
    temp_a0 = (void *)(arg0 + 0x90C);
    *(int *)((char *)(temp_a0) + 36) = (int)((int) *(int *)((char *)(temp_a1) + 4));
    *(int *)((char *)(temp_a0) + 40) = (int)((int) *(int *)((char *)(temp_a1) + 8));
    *(int *)((char *)(temp_a0) + 44) = (int)((int) *(int *)((char *)(temp_a1) + 12));
}
