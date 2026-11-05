int FUN_001683a0();
int FUN_00168400();

unsigned char FUN_00168420(void *arg0) {
    int temp_v1;

    if ((FUN_00168400() != 0) && (FUN_001683a0(arg0) == 0)) {
        return 0xFFU;
    }
    temp_v1 = *(int *)((char *)(arg0) + 36);
    *(int *)((char *)(arg0) + 36) = (int)((int) (temp_v1 + 1));
    return *(int *)(*(int *)((char *)(arg0) + 20) + temp_v1);
}
