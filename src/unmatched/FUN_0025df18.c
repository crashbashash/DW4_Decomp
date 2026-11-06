int FUN_0026f058();
int FUN_0026f0e8();

void FUN_0025df18(void *arg0, int arg1) {
    int temp_s0;
    void *temp_v0;

    temp_v0 = (void *)((char *)arg0 + 0x48);
    temp_s0 = *(int *)((char *)(arg0) + 8);
    FUN_0026f058(temp_s0, *(int *)((char *)(arg0) + 72), arg1, *(int *)((char *)(temp_v0) + 20) + (*(int *)((char *)(temp_v0) + 32) * 2), 0);
    FUN_0026f0e8(temp_s0);
}
