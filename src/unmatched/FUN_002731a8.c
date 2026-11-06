extern char DAT_004aa3b0[];
int FUN_0010e2a8();
extern int DAT_0056e580[4];
extern int DAT_0056e680[4];
int FUN_002731a8(int arg0, int arg1, int arg2, int arg3) {
    *(int *)((char *)&(DAT_0056e580[0]) + 0) = arg0;
    *(int *)((char *)&(DAT_0056e580[0]) + 4) = arg1;
    *(int *)((char *)&(DAT_0056e580[0]) + 8) = arg2;
    *(int *)((char *)&(DAT_0056e580[0]) + 12) = arg3;
    FUN_0010e2a8(DAT_004aa3b0, 2, 0, &DAT_0056e580[0], 0x10, &DAT_0056e680[0], 4, 0, 0);
    return DAT_0056e680[0];
}
