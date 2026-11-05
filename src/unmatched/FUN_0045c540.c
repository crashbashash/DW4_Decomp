int igMetaEnum_Create();
extern int DAT_004d1460[4];
extern int DAT_004d1470[4];
extern int DAT_0051f630[4];
extern int DAT_0058cbf0[4];
int FUN_0045c540(void) {
    if (DAT_0058cbf0[0] == 0) {
        DAT_0058cbf0[0] = igMetaEnum_Create(&DAT_0051f630[0], &DAT_004d1460[0], &DAT_004d1470[0], 3);
    }
    return DAT_0058cbf0[0];
}
