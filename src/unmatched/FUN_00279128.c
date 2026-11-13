int ADXM_Lock();
int ADXM_Unlock();
int ADXT_Stop();
int FUN_00278738();
int FUN_002788c8();

void FUN_00279128(void *arg0) {
    int temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(*(int *)((char *)(*(int *)((char *)(arg0) + 4)) + 4));
    temp_s0 = *(int *)((char *)(temp_s1) + 232);
    if (temp_s0 == 0) {
        return;
    }
    ADXT_Stop();
    ADXM_Lock();
    FUN_002788c8(temp_s0);
    *(int *)((char *)(temp_s1) + 232) = 0;
    FUN_00278738(0);
    ADXM_Unlock();
}
