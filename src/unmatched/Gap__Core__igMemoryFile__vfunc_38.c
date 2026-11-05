int Gap__Core__igMemoryFile__vfunc_38(int *arg0, int arg1, int arg2) {
    int t;
    switch (arg2) {
    case 0:
        arg0[14] = arg1;
        break;
    case 1:
        arg0[14] = arg0[14] + arg1;
        break;
    case 2:
        arg0[14] = arg0[13] + arg1;
        break;
    }
    t = arg0[14];
    if (t < 0) return -1;
    return -(arg0[13] < t);
}
