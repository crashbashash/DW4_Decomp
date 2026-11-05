int FUN_00169c20();
int FUN_0016a300();
int FUN_0016a380(int, float);
int FUN_0016a460();

void FUN_0013c5c0(void *arg0, int arg1) {
    int temp_a1;

    FUN_0016a380(arg1, *(float *)((char *)(arg0) + 64));
    FUN_0016a300(arg1, *(int *)((char *)(arg0) + 60));
    FUN_0016a460(arg1, *(int *)((char *)(arg0) + 56));
    temp_a1 = *(int *)((char *)(arg0) + 12);
    if (temp_a1 != 0) {
        FUN_00169c20(arg1, temp_a1);
    }
}
