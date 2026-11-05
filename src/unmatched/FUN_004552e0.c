int FUN_004551a0();
void FUN_004552e0(int *arg0, int *arg1) {
    int n = *(int *)(arg0[2] + 8);
    int i = 0;
    while (i < n) {
        int a = ((int *)*(int *)(arg0[2] + 16))[i];
        if (a != (int)arg1) {
            FUN_004551a0(a, arg1[2], arg1[4]);
        }
        i++;
    }
}
