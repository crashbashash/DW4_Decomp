void FUN_001b4500(void *arg0) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg0) + 136));
    if (temp_a1 != 0) {
        int k;
        if ((k = *(int *)((char *)(temp_a1) + 12)) == 1) {
            *(float *)((char *)(arg0) + 56) = (float) *(float *)((char *)(temp_a1) + 116);
            *(float *)((char *)(arg0) + 60) = (float) *(float *)((char *)(temp_a1) + 120);
            *(float *)((char *)(arg0) + 64) = (float) *(float *)((char *)(temp_a1) + 124);
            *(int *)((char *)(arg0) + 68) = 0x3F800000;
            return;
        }
        *(float *)((char *)(arg0) + 56) = (float) *(float *)((char *)(temp_a1) + 128);
        *(float *)((char *)(arg0) + 60) = (float) *(float *)((char *)(temp_a1) + 132);
        *(float *)((char *)(arg0) + 64) = (float) *(float *)((char *)(temp_a1) + 136);
        *(int *)((char *)(arg0) + 68) = 0;
    }
}
