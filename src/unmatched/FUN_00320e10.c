int FUN_00300f50(void *, int);
int Gap__Core__igProgramFile__vfunc_25(int, void *);

void FUN_00320e10(int arg0, void *arg1) {
    int temp_a1;
    int temp_a1_2;
    int temp_a1_3;
    int temp_a1_4;

    temp_a1 = *(int *)((char *)arg1 + 80);
    if (temp_a1 != 0) {
        FUN_00300f50(arg1, temp_a1);
    }
    temp_a1_2 = *(int *)((char *)arg1 + 72);
    if (temp_a1_2 != 0) {
        FUN_00300f50(arg1, temp_a1_2);
    }
    temp_a1_3 = *(int *)((char *)arg1 + 88);
    if (temp_a1_3 != 0) {
        FUN_00300f50(arg1, temp_a1_3);
    }
    temp_a1_4 = *(int *)((char *)arg1 + 96);
    if (temp_a1_4 != 0) {
        FUN_00300f50(arg1, temp_a1_4);
    }
    Gap__Core__igProgramFile__vfunc_25(arg0, arg1);
}
