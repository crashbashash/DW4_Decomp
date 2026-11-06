int igMetaEnum_Create();
extern int DAT_00485f98[4];
extern int DAT_00485fa8[4];
extern int DAT_004d5140[4];
extern int DAT_0055eed0[4];
int FUN_00134150(void) {
    if (DAT_0055eed0[0] == 0) {
        DAT_0055eed0[0] = igMetaEnum_Create(&DAT_004d5140[0], &DAT_00485f98[0], &DAT_00485fa8[0], 3);
    }
    return DAT_0055eed0[0];
}
