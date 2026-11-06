/* Intrusive reference-count copy (assign, then increment the count). */
void FUN_001cf950(int **arg0, int *arg1) {
    int *a;
    *arg0 = (int *)arg1[4];
    a = *arg0;
    if (a != 0) {
        a[1] = a[1] + 1;
    }
}
