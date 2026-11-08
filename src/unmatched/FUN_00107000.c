int FUN_00106c88();
int FUN_001070c8();
int FUN_001073e0();
int FUN_00107428();

void FUN_00107000(void *arg0) {
    int temp_s1;

    temp_s1 = FUN_00106c88(arg0, 0xA);
    *(int *)((char *)(arg0) + 360) = FUN_00106c88(arg0, 3);
    FUN_00106c88(arg0, 0x10);
    if ((unsigned int) (*(int *)((char *)(arg0) + 360) - 2) < 2U) {
        *(int *)((char *)(arg0) + 364) = FUN_00106c88(arg0, 1);
        *(int *)((char *)(arg0) + 368) = FUN_00106c88(arg0, 3);
    }
    if (*(int *)((char *)(arg0) + 360) == 3) {
        *(int *)((char *)(arg0) + 372) = FUN_00106c88(arg0, 1);
        *(int *)((char *)(arg0) + 376) = FUN_00106c88(arg0, 3);
    }
    FUN_001073e0(arg0);
    FUN_001070c8(arg0);
    FUN_00107428(arg0, temp_s1);
}
