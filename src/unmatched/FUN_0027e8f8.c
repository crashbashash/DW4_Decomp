extern int DAT_00570ba8[4];
int FUN_0027e8f8(int arg0, int arg1) {
    *(int *)((char *)&(DAT_00570ba8[0]) + 4) = arg1;
    *(int *)((char *)&(DAT_00570ba8[0]) + 0) = arg0;
    return (int)&DAT_00570ba8[0];
}
