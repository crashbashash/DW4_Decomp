int FUN_00309640();
int FUN_00309750();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void FUN_00308c00(int *arg0, void *arg1) {
    int temp_s0;

    if (arg1 == 0) {
        *arg0 = DAT_004fb418[0];
    } else {
        temp_s0 = *(int *)((char *)(arg1) + 32);
        if (*(int *)((char *)(arg1) + 52) > 1) {
            FUN_00309640(temp_s0);
            FUN_00309750(temp_s0, *(int *)((char *)(arg1) + 20));
        }
        *arg0 = DAT_004fb410[0];
    }
}
