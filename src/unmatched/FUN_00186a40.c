int FUN_00186e40();
int FUN_00186f70();
int FUN_00190370();
extern unsigned char DAT_00554b7c;
void FUN_00186a40(void) {
    if (DAT_00554b7c == 0) {
        DAT_00554b7c = 1;
        FUN_00186e40();
        FUN_00186f70();
        FUN_00190370();
    }
}
