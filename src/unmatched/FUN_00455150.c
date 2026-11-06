int FUN_004552e0(int, void *, void *);

void FUN_00455150(void *arg0, void *arg1) {
    int temp_a0;

    if ((*(int *)((char *)arg1 + 0) == 0) || (*(int *)((char *)arg0 + 16) == *(int *)((char *)arg1 + 8))) {
        temp_a0 = *(int *)((char *)arg0 + 12);
        if (temp_a0 != 0) {
            FUN_004552e0(temp_a0, arg0, arg0);
        }
    }
}
