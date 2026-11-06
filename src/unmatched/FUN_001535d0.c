int igMetaEnum_Create();
extern int DAT_00489f28[4];
extern int DAT_00489f38[4];
extern int DAT_004de1f0[4];
extern int DAT_00560570[4];
int FUN_001535d0(void) {
    if (DAT_00560570[0] == 0) {
        DAT_00560570[0] = igMetaEnum_Create(&DAT_004de1f0[0], &DAT_00489f28[0], &DAT_00489f38[0], 3);
    }
    return DAT_00560570[0];
}
