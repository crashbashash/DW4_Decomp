int igMetaEnum_Create();
extern int DAT_00487510[4];
extern int DAT_00487520[4];
extern int DAT_004d6ce8[4];
extern int DAT_0055f730[4];
int FUN_00146d90(void) {
    if (DAT_0055f730[0] == 0) {
        DAT_0055f730[0] = igMetaEnum_Create(&DAT_004d6ce8[0], &DAT_00487510[0], &DAT_00487520[0], 4);
    }
    return DAT_0055f730[0];
}
