extern char DAT_004fb410[];
extern char DAT_004fb418[];
int FUN_0010bd90(int);

void Gap__Core__igPsx2Thread__vfunc_28(int *arg0, void *arg1) {
    int *var_v1;

    if (FUN_0010bd90(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = (int *)DAT_004fb418;
    } else {
        var_v1 = (int *)DAT_004fb410;
    }
    *arg0 = *var_v1;
}
