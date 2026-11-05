extern int DAT_00562da0[4];
extern int DAT_00562dc4[4];
extern int DAT_00562dc8[4];
void FUN_001eb3b0(int arg0, long long arg1, int arg2, int arg3) {
    int temp_a5;
    temp_a5 = arg0 << 6;
    *(long long *)((char *)DAT_00562da0 + temp_a5) = arg1;
    *(int *)((char *)DAT_00562dc4 + temp_a5) = arg2;
    *(int *)((char *)DAT_00562dc8 + temp_a5) = arg3;
}
