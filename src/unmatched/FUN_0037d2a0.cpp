/* 0x0037d2a0 - FUN_0037d2a0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int FUN_003332b0(int, int, int);
extern int DAT_005875e8[4];
void FUN_0037d2a0(int arg0, int arg1, int arg2);
}

void FUN_0037d2a0(int arg0, int arg1, int arg2) {
    if ((arg1 < 0) || (arg1 >= DAT_005875e8[0])) {
        return;
    }
    FUN_003332b0(arg1, arg2, 0);
}
