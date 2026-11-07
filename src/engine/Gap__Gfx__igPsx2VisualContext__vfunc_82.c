extern int DAT_005608d0[4];
int FUN_00171690();
void Gap__Gfx__igPsx2VisualContext__vfunc_82(char *arg0, int arg1, float *arg2);
void Gap__Gfx__igPsx2VisualContext__vfunc_82(char *arg0, int arg1, float *arg2) {
    char *a3;
    float *t;
    int e;
    a3 = *(char **)(arg0 + 1336);
    arg1 = *(int *)(a3 + 16) + arg1 * 0xA0;
    t = (float *)arg1;
    if (t != 0) {
        e = 1;
        if (t[8] != arg2[0]) e = 0;
        if (e != 0) { e = 1; if (t[9] != arg2[1]) e = 0; }
        if (e != 0) { e = 1; if (t[10] != arg2[2]) e = 0; }
        if (e != 0) { e = 1; if (t[11] != arg2[3]) e = 0; }
        if (e != 0) {
            DAT_005608d0[0] += 1;
        }
        t[8] = arg2[0];
        t[9] = arg2[1];
        t[10] = arg2[2];
        t[11] = arg2[3];
        FUN_00171690(arg0, t);
    }
}
