int FUN_002d3890();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void thunk_FUN_00143150(void);
extern int DAT_00486cd8[4];
extern int DAT_00486ce0[4];
extern int DAT_00486ce8[4];
extern int DAT_00486cf0[4];
extern void * DAT_0055f540[4];
void igAudioContext_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f540[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486cd8[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486ce0[0], &DAT_00486ce8[0], &DAT_00486cf0[0], temp_s1);
    *(int *)((char *)(DAT_0055f540[0]) + 60) = (int)(thunk_FUN_00143150);
}
