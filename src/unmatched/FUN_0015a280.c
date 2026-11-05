void FUN_0015a280(unsigned char *arg0, int arg1, int arg2) {
    int i;
    switch (arg2) {
    case 7:
        for (i = 0; i < arg1; i++) {
            unsigned char t = arg0[3];
            arg0[3] = (t >> 1) + (t & 1);
            arg0 += 4;
        }
        break;
    case 1:
    case 3:
    case 2:
    case 8:
    case 9:
        break;
    }
}
