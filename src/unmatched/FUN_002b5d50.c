int FUN_002b7c00();
int FUN_002b8020();
int FUN_002b8470();
int FUN_002c5ee0();
int FUN_002cb980();
extern unsigned char DAT_00554bf4[4];
void FUN_002b5d50(void) {
    if (DAT_00554bf4[0] == 0) {
        DAT_00554bf4[0] = 1;
        FUN_002b7c00();
        FUN_002b8470();
        FUN_002b8020();
        FUN_002c5ee0();
        FUN_002cb980();
    }
}
