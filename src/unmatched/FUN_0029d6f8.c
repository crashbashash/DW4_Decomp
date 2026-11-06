int FUN_0027bd48();
int FUN_002a0bb8();

int FUN_0029d6f8(void *arg0, int arg1, int arg2, int arg3) {
    int temp_v0;
    int temp_v0_2;

    temp_v0 = arg2 - arg3;
    *(int *)((char *)(arg0) + 0) = 0;
    *(int *)((char *)(arg0) + 8) = arg1;
    *(int *)((char *)(arg0) + 12) = temp_v0;
    if (temp_v0 <= 0) {
        return FUN_002a0bb8(0, 0xFF00040C, arg3);
    }
    *(int *)((char *)(arg0) + 16) = arg3;
    *(int *)((char *)(arg0) + 20) = 0;
    temp_v0_2 = FUN_0027bd48(arg1, temp_v0, arg3);
    *(int *)((char *)(arg0) + 4) = temp_v0_2;
    if (temp_v0_2 == 0) {
        return FUN_002a0bb8(0, 0xFF00040A);
    }
    return 0;
}
