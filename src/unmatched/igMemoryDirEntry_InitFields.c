int FUN_002beca0();
int FUN_002cc2c0();
int FUN_002d3890();
int FUN_002ea4b0();
int FUN_00303460();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0300[4];
extern int DAT_004c0320[4];
extern int DAT_004c0340[4];
extern int DAT_004c0360[4];
extern int DAT_00585f60[4];
void igMemoryDirEntry_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585f60[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0300[0], 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002ea4b0(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1) + 56) = FUN_002beca0();
    FUN_00303460(temp_s1, FUN_002cc2c0());
    *(char *)((char *)(temp_s1) + 60) = 0;
    *(char *)((char *)(temp_s1) + 38) = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), -1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004c0320[0], &DAT_004c0340[0], &DAT_004c0360[0], temp_s2);
}
