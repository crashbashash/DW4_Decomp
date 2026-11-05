/* 0x0030ba20 - FUN_0030ba20. Backward scan for a path separator, then a framed call; pointer declared before the base; alternate compiler. Verified byte-identical by tools/verify.py. */
int FUN_0030b3c0();
void FUN_0030ba20(int *arg0) {
    char *p;
    unsigned int a3;
    a3 = arg0[2];
    if (a3 != 0) {
        p = (char *)(a3 + arg0[3]);
        while (--p, a3 < (unsigned int)p) {
            char c = *p;
            if (c == 0x5C || c == 0x2F) {
                FUN_0030b3c0(arg0, p + 1);
                return;
            }
        }
    }
}
