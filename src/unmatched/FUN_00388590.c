void FUN_00388590(int arg0, float *arg1, float *arg2, int arg3) {
    float b;
    float a;
    b = *arg2;
    a = *arg1;
    if (a < b) {
        if (arg3 == 0) {
            *arg1 = b;
        }
    } else if (!(a <= b) && (arg3 == 1)) {
        *arg1 = b;
    }
}
