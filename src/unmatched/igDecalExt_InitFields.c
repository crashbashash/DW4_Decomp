int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489070[4];
extern int DAT_00489078[4];
extern int DAT_00489080[4];
extern int DAT_00489088[4];
extern void * DAT_0055fea8[4];
int thunk_igPsx2DecalExt_GetMetaObject();

void igDecalExt_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055fea8[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489070[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00489078[0], &DAT_00489080[0], &DAT_00489088[0], temp_s1);
    *(int *)((char *)(DAT_0055fea8[0]) + 60) = (int)(&thunk_igPsx2DecalExt_GetMetaObject);
}
