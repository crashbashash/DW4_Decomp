int List_Resize();
extern int DAT_004c1ea0[4];
int *Gap__Core__igCallStackTracer__vfunc_24(int *arg0) {
    int t;
    if (arg0[3] > 0) {
        arg0[2] = 1;
    } else {
        List_Resize(arg0, 1, 4);
    }
    t = arg0[2];
    if (t != 0 && 0 < t) {
        *(int *)arg0[4] = DAT_004c1ea0[0];
    }
    return (int *)arg0[4];
}
