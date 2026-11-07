int igMetaEnum_Create();
extern int DAT_00488560[4];
extern int DAT_00488570[4];
extern int DAT_004dbaa0[4];
extern int DAT_0055fa00[4];
int FUN_0014ad00(void) {
    if (DAT_0055fa00[0] == 0) {
        DAT_0055fa00[0] = igMetaEnum_Create(&DAT_004dbaa0[0], &DAT_00488560[0], &DAT_00488570[0], 3);
    }
    return DAT_0055fa00[0];
}
