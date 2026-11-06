int memset();
extern int DAT_00499cd8[4];
extern int DAT_00499cdc[4];
extern int DAT_00499ce0[4];
void FUN_00260788(void) {
    memset(&DAT_00499ce0[0], 0, 0x100);
    DAT_00499cd8[0] = 0;
    DAT_00499cdc[0] = 0;
}
