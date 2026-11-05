extern char DAT_004d3d10[];
void FUN_002db480(int *arg0) {
    char c;
    while (DAT_004d3d10[(c = *(char *)arg0[13]) + 1] & 8) {
        if (c == 10) {
            arg0[11] = arg0[11] + 1;
        }
        arg0[13] = arg0[13] + 1;
    }
}
