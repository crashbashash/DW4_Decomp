int FUN_00457a10(int, int);

void FUN_00457bc0(void *arg0, void *arg1) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg1 + 8);
    if (temp_a1 == *(int *)0x58C280) {
        FUN_00457a10(*(int *)((char *)arg0 + 12), temp_a1);
    }
}
