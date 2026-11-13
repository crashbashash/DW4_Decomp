int SFD_SetStmObject();

void FUN_002997d8(void *arg0, int arg1) {
    int temp_s1;
    int temp_s2;
    void *temp_s0;

    temp_s0 = (void *)((char *)arg0 + 0x294);
    temp_s1 = *(int *)((char *)(arg0) + 64);
    temp_s2 = *(int *)((char *)(temp_s0) + 12);
    SFD_SetStmObject(temp_s1, *(int *)((char *)(temp_s0) + 16) + 0xC0, 0, 0, 0);
    SFD_SetStmObject(temp_s1, arg1 + 0xC0, temp_s2, 0, 0);
    *(int *)((char *)(temp_s0) + 16) = arg1;
}
