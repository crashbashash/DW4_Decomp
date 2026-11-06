extern "C" {
bool FUN_003885e0(int arg0, float *arg1, float *arg2, float *arg3, float *arg4);
}
bool FUN_003885e0(int arg0, float *arg1, float *arg2, float *arg3, float *arg4) {
    bool r = false;
    if (!(arg1[0] < arg4[0]) && (arg3[0] <= arg2[0]) && !(arg1[2] < arg4[2]) && (arg3[2] <= arg2[2])) {
        r = true;
    }
    return r;
}
