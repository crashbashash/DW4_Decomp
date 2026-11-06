int igMetaEnum_Create();
extern int DAT_00489f48[4];
extern int DAT_00489f58[4];
extern int DAT_004de2a0[4];
extern int DAT_00560578[4];
int FUN_00153630(void) {
    if (DAT_00560578[0] == 0) {
        DAT_00560578[0] = igMetaEnum_Create(&DAT_004de2a0[0], &DAT_00489f48[0], &DAT_00489f58[0], 3);
    }
    return DAT_00560578[0];
}
