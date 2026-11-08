int vprintf();

int Gap__igLogInterface__vfunc_27(void *arg0, int arg1, int arg2) {
    int var_v0;

    var_v0 = -1;
    if (*(unsigned char *)((char *)(arg0) + 32) != 0) {
        var_v0 = vprintf(arg1, arg2);
    }
    return var_v0;
}
