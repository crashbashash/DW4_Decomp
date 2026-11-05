int FUN_00460d90();

void FUN_00460f20(void *arg0, int arg1, int arg2) {
    if (arg2 != 0) {
        FUN_00460d90(*(int *)((char *)(arg0) + 44), *(int *)((char *)(arg0) + 48), arg1);
        return;
    }
    FUN_00460d90(*(int *)((char *)(arg0) + 48), *(int *)((char *)(arg0) + 44), arg1);
}
