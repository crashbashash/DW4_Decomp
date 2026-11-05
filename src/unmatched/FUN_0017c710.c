int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_00560a3c[4];
void FUN_0017c710(int arg0, int arg1, int arg2, unsigned char arg3) {
    if (arg1 < 8) {
        unsigned char v = *(unsigned char *)(arg1 + arg0 + 540); if (v == (arg2 & 0xFF)) {
            DAT_00560a3c[arg1] = DAT_00560a3c[arg1] + 1;
        }
    }
    *(char *)(arg1 + arg0 + 540) = arg2;
    if (arg1 == 0) {
        if (arg2 != 0) {
            FUN_001e74b0(0x1A, arg1);
            return;
        }
        FUN_001e7500(0x1A, arg1);
    }
}
