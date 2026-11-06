extern int DAT_00573f5c[4];
int FUN_00290d48(int arg0) {
    int var_a0;

    var_a0 = arg0;
    if (DAT_00573f5c[0] != 0) {
        var_a0 |= 0x02000000;
    }
    return var_a0;
}
