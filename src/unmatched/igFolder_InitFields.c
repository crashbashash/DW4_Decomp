int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0a98[4];
extern int DAT_004c0aa0[4];
extern int DAT_004c0aa8[4];
extern int DAT_004c0ab0[4];
extern void * DAT_00586368[4];
int thunk_igPsx2Folder_GetMetaObject();

void igFolder_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00586368[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0a98[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c0aa0[0], &DAT_004c0aa8[0], &DAT_004c0ab0[0], temp_s1);
    *(int *)((char *)(DAT_00586368[0]) + 60) = (int)(&thunk_igPsx2Folder_GetMetaObject);
}
