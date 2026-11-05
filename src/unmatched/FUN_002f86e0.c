extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_00587000[4];
extern int DAT_00587010[4];
void FUN_002f86e0(int *arg0, void *arg1) {

    if ((arg1 != 0) && (DAT_00587010[0] >= 0) && (DAT_00587010[0] < 4)) {
        DAT_00587000[DAT_00587010[0]] = (int)(arg1);
        DAT_00587010[0] += 1;
        *(int *)((char *)(arg1) + 4) = (int)((int) (*(int *)((char *)(arg1) + 4) + 1));
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
