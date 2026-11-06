int memcpy();
extern int DAT_00491478[4];
extern int DAT_0056aee0[4];
void FUN_001f8aa0(int arg0) {
    memcpy(&DAT_0056aee0[0], arg0, 0x10);
    DAT_00491478[0] |= 4;
}
