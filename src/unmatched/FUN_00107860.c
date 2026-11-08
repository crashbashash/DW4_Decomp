void FUN_00108078(char *d, int a, int b);
void FUN_00108188(char *d, int a, int b, int c);
void FUN_00107860(char *d, int n, int flag) {
    int a, b;

    if (flag) {
        if (*(int *)(d + 396) == 3) {
            FUN_00108078(d, *(int *)(d + 360) == 3 ? *(int *)(d + 476) : *(int *)(d + 464), n - 1);
        } else {
            if (*(int *)(d + 360) == 3) {
                a = *(int *)(d + 492);
                b = *(int *)(d + 508);
            } else {
                a = *(int *)(d + 480);
                b = *(int *)(d + 496);
            }
            FUN_00108188(d, a, b, n - 1);
        }
    }
    if (*(int *)(d + 272) == 1) {
        *(int *)(d + 272) = 2;
    }
}
