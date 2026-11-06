int igMetaEnum_Create();
extern int DAT_00489f70[4];
extern int DAT_00489fa0[4];
extern int DAT_004de540[4];
extern int DAT_00560580[4];
int FUN_00153690(void) {
    if (DAT_00560580[0] == 0) {
        DAT_00560580[0] = igMetaEnum_Create(&DAT_004de540[0], &DAT_00489f70[0], &DAT_00489fa0[0], 0xC);
    }
    return DAT_00560580[0];
}
