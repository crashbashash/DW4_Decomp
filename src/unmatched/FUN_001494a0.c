int igMetaEnum_Create();
extern int DAT_00487790[4];
extern int DAT_004877b0[4];
extern int DAT_004d72a0[4];
extern int DAT_0055f838[4];
int FUN_001494a0(void) {
    if (DAT_0055f838[0] == 0) {
        DAT_0055f838[0] = igMetaEnum_Create(&DAT_004d72a0[0], &DAT_00487790[0], &DAT_004877b0[0], 8);
    }
    return DAT_0055f838[0];
}
