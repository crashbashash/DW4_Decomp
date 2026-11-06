/* In-place `t &= 0xFF; t <<= n;` and `v &= mask; v |= t;` keep one web per variable. */
int FUN_0015e130();
void FUN_0015e160(unsigned int *arg0, unsigned int arg1) {
    unsigned int v;
    unsigned int t;
    v = 0;
    if (arg1 & 3) {
        v |= 1;
    } else {
        v &= ~1;
    }
    if (arg1 & 0xC) {
        v |= 2;
    } else {
        v &= ~2;
    }
    if (arg1 & 0xF0) {
        v |= 4;
    } else {
        v &= ~4;
    }
    t = FUN_0015e130(arg1 & 0xF0000);
    t &= 0xFF;
    t <<= 16;
    v &= 0xFFF0FFFF;
    v |= t;
    t = FUN_0015e130(arg1 & 0xF00);
    t &= 0xFF;
    t <<= 4;
    v &= ~0xF0;
    v |= t;
    t = FUN_0015e130(arg1 & 0xF000);
    t &= 0xFF;
    t <<= 8;
    v &= ~0xF00;
    v |= t;
    *arg0 = v;
}
