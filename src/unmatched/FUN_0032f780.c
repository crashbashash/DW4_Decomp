int sbrk();
int FUN_0032f780(int arg0, int arg1) {
    int s1 = sbrk(arg1);
    int low;
    int pad;
    if (s1 != -1) {
        low = s1 & 0xFFF;
        if (low != 0) {
            pad = 0x1000 - low;
            if (sbrk(pad) == -1) {
                return -1;
            }
            s1 += pad;
        }
    }
    return s1;
}
