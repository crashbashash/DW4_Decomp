int FUN_00455610();
int FUN_00455620();
void FUN_004570a0(void *arg0) {
    int temp_s1;
    int temp_s0;
    temp_s0 = *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 168);
    if (temp_s0 != 0) {
        temp_s1 = FUN_00455620(temp_s0) & 0xFF;
        FUN_00455610(temp_s0, (temp_s1 != 0) ^ 1);
        FUN_00455610(temp_s0, temp_s1);
    }
}
