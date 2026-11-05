int FUN_0010b5e0();
int FUN_0032f780(int arg0, int arg1) {
    int s1 = FUN_0010b5e0(arg1);
    int low;
    int pad;
    if (s1 != -1) {
        low = s1 & 0xFFF;
        if (low != 0) {
            pad = 0x1000 - low;
            if (FUN_0010b5e0(pad) == -1) {
                return -1;
            }
            s1 += pad;
        }
    }
    return s1;
}
