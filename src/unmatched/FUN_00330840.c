int FUN_00300f50();

void FUN_00330840(void *arg0) {
    int temp_a1;

    if (*(unsigned char *)((char *)(arg0) + 45) == 0) {
        temp_a1 = *(int *)((char *)(arg0) + 32);
        if (temp_a1 != 0) {
            FUN_00300f50(arg0, temp_a1);
        }
    }
}
