int igMetaEnum_Create();
extern int DAT_004bfdd0[4];
extern int DAT_004bfde0[4];
extern int DAT_004f6790[4];
extern int DAT_00585cc0[4];
int FUN_002bec40(void) {
    if (DAT_00585cc0[0] == 0) {
        DAT_00585cc0[0] = igMetaEnum_Create(&DAT_004f6790[0], &DAT_004bfdd0[0], &DAT_004bfde0[0], 4);
    }
    return DAT_00585cc0[0];
}
