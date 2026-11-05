int FUN_003a4e40(void *arg0, int arg1) {
    int v = 0;
    if (arg1 > 0) {
        v = arg1 / 128 + 1;
        if (v >= 100) {
            v = 99;
        }
        if (v % 10 == 0) {
            v++;
        }
    } else if (arg1 < 0) {
        v = arg1 / 128 - 1;
        if (v < -99) {
            v = -99;
        }
        if (v % 10 == 0) {
            v--;
        }
    }
    return v;
}
