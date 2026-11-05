long long FUN_00202fa0(int arg0) {
    int m;
    unsigned int i;
    int c;
    int j;
    int b;

    m = arg0;
    for (i = 0; i < 0x20U; i++) {
        b = 1 << i;
        if (arg0 & b) {
            break;
        }
        m |= b;
    }
    j = 0x1F;
    while (1) {
        c = 1 << j;
        if (arg0 & c) {
            break;
        }
        m |= c;
        j--;
    }
    return ~m;
}
