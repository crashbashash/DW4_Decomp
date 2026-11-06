int igMetaEnum_Create();
extern int DAT_004c1760[4];
extern int DAT_004c1790[4];
extern int DAT_004f8ac0[4];
extern int DAT_00586a70[4];
int FUN_002cd990(void) {
    if (DAT_00586a70[0] == 0) {
        DAT_00586a70[0] = igMetaEnum_Create(&DAT_004f8ac0[0], &DAT_004c1760[0], &DAT_004c1790[0], 0xA);
    }
    return DAT_00586a70[0];
}
