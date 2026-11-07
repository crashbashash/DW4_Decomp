void FUN_00285a30(int arg0, int arg1, int arg2, int arg3, int arg4) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)(arg0 + (0xC * arg1));
    temp_a0_2 = (void *)(0x118 + (char *)temp_a0);
    *(int *)(280 + (char *)(temp_a0)) = arg2;
    *(int *)(4 + (char *)(temp_a0_2)) = arg3;
    *(int *)((char *)(temp_a0_2) + 8) = arg4;
}
