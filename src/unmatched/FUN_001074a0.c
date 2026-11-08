int FUN_00106c88();
int FUN_001070c8();

void FUN_001074a0(void *arg0) {
    *(int *)((char *)(arg0) + 256) = 0;
    *(int *)((char *)(arg0) + 2156) = 1;
    *(int *)((char *)(arg0) + 2148) = (int)((int) (*(int *)((char *)(arg0) + 2152) + 1));
    FUN_00106c88(arg0, 1);
    FUN_00106c88(arg0, 5);
    FUN_00106c88(arg0, 6);
    FUN_00106c88(arg0, 1);
    FUN_00106c88(arg0, 6);
    FUN_00106c88(arg0, 6);
    *(int *)((char *)(arg0) + 444) = FUN_00106c88(arg0, 1);
    *(int *)((char *)(arg0) + 448) = FUN_00106c88(arg0, 1);
    FUN_001070c8(arg0);
}
