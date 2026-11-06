extern "C" {
int FUN_0026bd20(int);

int FUN_00332490(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return -1;
    }
    return FUN_0026bd20(temp_a0);
}
}
