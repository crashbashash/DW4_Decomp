extern "C" {
int FUN_002ea4b0(int, int);
int igStringMetaField_SetDefaultText(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c27c0[4];
extern int DAT_004c27f0[4];
extern int DAT_004c2820[4];
extern int DAT_004c2850[4];
extern int DAT_005876e0[4];
void igAdxAudio_InitFields(void);
}
void igAdxAudio_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005876e0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c27c0[0], 9);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 4);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 2);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5), 4);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6), 0xBB80);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c27f0[0], &DAT_004c2820[0], &DAT_004c2850[0], temp_s1);
}
