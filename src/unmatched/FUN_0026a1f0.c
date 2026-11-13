int ADXCRS_Lock();
int ADXCRS_Unlock();
int FUN_0026a178();

int FUN_0026a1f0(void *arg0, int arg1) {
    ADXCRS_Lock();
    FUN_0026a178(arg0);
    *(int *)((char *)(arg0) + 92) = arg1;
    ADXCRS_Unlock();
    return 1;
}
