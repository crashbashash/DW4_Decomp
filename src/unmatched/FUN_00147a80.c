int FUN_001180c0(int, int);
int Memory_FreeBuffer(int);
int Gap__Core__igObject__vfunc_10(void *);

void FUN_00147a80(void *arg0) {
    int temp_a0;

    FUN_001180c0(*(int *)((char *)arg0 + 64), *(int *)((char *)arg0 + 60));
    temp_a0 = *(int *)((char *)arg0 + 72);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    Gap__Core__igObject__vfunc_10(arg0);
}
