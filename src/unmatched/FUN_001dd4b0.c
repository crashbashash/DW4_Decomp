long long __udivdi3();
long long __muldi3();
extern long long DAT_00562a18[4];
extern long long DAT_00562a20[4];
extern int DAT_00562a28[4];
extern long long DAT_00562a30[4];
int FUN_001dd4b0(long long arg0, long long arg1, long long *arg2) {
    long long r, v;
    if (DAT_00562a18[0] == arg0 && arg1 == DAT_00562a20[0]) {
        *arg2 = DAT_00562a30[0];
        return DAT_00562a28[0];
    } else {
        DAT_00562a18[0] = arg0;
        DAT_00562a20[0] = arg1;
        r = __udivdi3(arg0, arg1);
        v = arg0 - __muldi3(r, arg1);
        DAT_00562a30[0] = v;
        *arg2 = v;
        DAT_00562a28[0] = (int)r;
    }
    return DAT_00562a28[0];
}
