int igMetaEnum_Create(int *, int, int, int);
extern int DAT_004f7910[4];
extern int DAT_00586dc0[4];
int FUN_002d1870(void) {
    if (DAT_00586dc0[0] == 0) {
        DAT_00586dc0[0] = igMetaEnum_Create(&DAT_004f7910[0], 0, 0, 0);
    }
    return DAT_00586dc0[0];
}
