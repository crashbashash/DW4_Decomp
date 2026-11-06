extern int DAT_00562da0[4];
int *FUN_00202f60(int *arg0, long long arg1) {
    for (; arg0 != 0; arg0 = (int *)arg0[5]) {
        if (arg1 == *(long long *)((char *)DAT_00562da0 + (arg0[4] << 6))) break;
    }
    return arg0;
}
