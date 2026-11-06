int FUN_002935a8(int arg0, int arg1) {
    int var_a2;
    unsigned int temp_v1;
    void *temp_a0;

    temp_a0 = (void *)(arg0 + 0x200);
    temp_v1 = *(int *)((char *)(temp_a0) + 12) + arg1;
    var_a2 = 0;
    if ((unsigned int) *(int *)((char *)(temp_a0) + 4) >= temp_v1) {
        var_a2 = *(int *)((char *)(temp_a0) + 8);
        *(int *)((char *)(temp_a0) + 12) = temp_v1;
        *(int *)((char *)(temp_a0) + 8) = (int)((int) (var_a2 + arg1));
    }
    return var_a2;
}
