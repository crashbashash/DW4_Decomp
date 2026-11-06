int FUN_001d15a0(void *);
int FUN_001d1a90(int, int, int);

void FUN_001d1760(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 52);
    if (temp_a0 != 0) {
        FUN_001d1a90(temp_a0, *(int *)((char *)arg0 + 44), arg1);
    }
    FUN_001d15a0(arg0);
}
