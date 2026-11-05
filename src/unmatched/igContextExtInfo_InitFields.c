int FUN_002be610();
int FUN_002cc2c0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igStringMetaField_SetDefaultText();
extern int DAT_004c1420[4];
extern int DAT_004c1430[4];
extern int DAT_004c1440[4];
extern int DAT_004c1450[4];
extern int DAT_005868c8[4];
void igContextExtInfo_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_005868c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1420[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_002be610();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igStringMetaField_SetDefaultText(temp_v0, 0);
    *(char *)((char *)(temp_v0) + 53) = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_2) + 60) = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c1430[0], &DAT_004c1440[0], &DAT_004c1450[0], temp_s2);
}
