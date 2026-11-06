extern "C" {
void FUN_00100e50(int *arg0) {
    int a = arg0[0];
    if (a != 0) {
        int (*f)(int, int) = (int (*)(int, int))arg0[2];
        if (f != 0) {
            f(a, -1);
        }
    }
}
}
