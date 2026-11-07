int FUN_002a11a0();
int FUN_002a1200();
int FUN_002a2248();
int FUN_002a24d0();

int FUN_002a1128(void *arg0) {
    int temp_s1;

    if (FUN_002a2248() == 1) {
        return 0;
    }
    FUN_002a11a0(arg0);
    temp_s1 = FUN_002a1200(arg0);
    if (*(int *)((char *)(arg0) + 72) == 2) {
        FUN_002a24d0(arg0);
    }
    return temp_s1;
}
