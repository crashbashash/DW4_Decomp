int igMetaEnum_Create();
extern int DAT_00488650[4];
extern int DAT_00488680[4];
extern int DAT_004dbd40[4];
extern int DAT_0055fa50[4];
int FUN_0014b330(void) {
    if (DAT_0055fa50[0] == 0) {
        DAT_0055fa50[0] = igMetaEnum_Create(&DAT_004dbd40[0], &DAT_00488650[0], &DAT_00488680[0], 0xB);
    }
    return DAT_0055fa50[0];
}
