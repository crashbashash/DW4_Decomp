int strlen();
int FUN_0030bfa0();
int FUN_0012a110();

int FUN_001b7af0(void *arg0, int arg1) {
    int temp_v0_2;
    void *temp_v0;

    if ((arg1 == 0) || (strlen(arg1) == 0)) {
        return 0;
    }
    temp_v0_2 = FUN_0030bfa0(*(int *)((char *)(arg0) + 260), arg1, &FUN_0012a110);
    if (temp_v0_2 < 0) {
        return 0;
    }
    temp_v0 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 264)) + 16) + (temp_v0_2 * 4)));
    return *(int *)(*(int *)((char *)(temp_v0) + 16) + ((*(int *)((char *)(temp_v0) + 8) - 1) * 4));
}
