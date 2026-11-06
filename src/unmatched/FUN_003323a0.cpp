extern "C" {
int FUN_0026cf70(int);

int FUN_003323a0(void *arg0) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 44);
    if (temp_a0 == 0) {
        return -1;
    }
    return FUN_0026cf70(temp_a0);
}
}
