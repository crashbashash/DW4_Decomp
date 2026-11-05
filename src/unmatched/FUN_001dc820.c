void FUN_001dc820(void *arg0, unsigned int arg1) {
    int *temp_a1;
    int temp_a2_2;
    unsigned int temp_a3;
    void *temp_a2;
    int nv;

    temp_a2 = (void *)(*(int *)((char *)(arg0) + 32));
    temp_a3 = arg1 >> 5;
    temp_a1 = (int *)(*(int *)((char *)(temp_a2) + 16) + (temp_a3 * 4));
    temp_a2_2 = *(int *)((char *)(temp_a2) + 8);
    nv = (1 << (arg1 & 0x1F)) | *temp_a1;
    if ((temp_a2_2 != 0) && ((int) temp_a3 >= 0) && ((int) temp_a3 < temp_a2_2)) {
        *temp_a1 = nv;
    }
}
