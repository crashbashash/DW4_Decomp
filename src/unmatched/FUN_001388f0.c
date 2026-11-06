int igMetaEnum_Create();
extern int DAT_00486790[4];
extern int DAT_004867b0[4];
extern int DAT_004d58b8[4];
extern int DAT_0055f250[4];
int FUN_001388f0(void) {
    if (DAT_0055f250[0] == 0) {
        DAT_0055f250[0] = igMetaEnum_Create(&DAT_004d58b8[0], &DAT_00486790[0], &DAT_004867b0[0], 5);
    }
    return DAT_0055f250[0];
}
