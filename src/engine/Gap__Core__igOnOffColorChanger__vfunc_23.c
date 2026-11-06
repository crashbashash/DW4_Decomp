int Gap__Core__igOnOffColorChanger__vfunc_23(int arg0, unsigned char *arg1) {
    int var_a2;
    unsigned char t, f, g;
    int ff, gg;
    if (arg1[12] == 0) return arg0 + 0x48;
    t = arg1[13];
    var_a2 = 0;
    if (t != 0) var_a2 += 1;
    f = arg1[15] != 0; if (f != 0) f = t != 0;
    gg = f & 0xff; if ((gg = gg, *(volatile unsigned char*)(arg1+36) ^ gg) != 0) var_a2 += 2;
    return arg0 + (var_a2 * 0x10) + 8;
}
