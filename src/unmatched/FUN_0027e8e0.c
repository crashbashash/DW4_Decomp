/* Returns the global's address so the lui/addiu pair lands in v0. */
extern int DAT_00570ba0[4];
int *FUN_0027e8e0(int arg0, int arg1) {
    int *p = (int *)((char *)&DAT_00570ba0[0]);
    *(int *)((char *)&(DAT_00570ba0[0]) + 4) = arg1;
    *(int *)((char *)&(DAT_00570ba0[0]) + 0) = arg0;
    return p;
}
