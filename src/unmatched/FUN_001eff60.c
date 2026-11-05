int FUN_00204240();
extern void * DAT_005691c0[4];
void FUN_001eff60(int arg0) {
    int i = 0;
    int *n = (int *)DAT_005691c0[0];
    while (i < arg0) {
        if (n == 0) break;
        n = (int *)n[1];
        i++;
    }
    if (i != arg0) {
        FUN_00204240(8, &DAT_005691c0[0], i);
    }
}
