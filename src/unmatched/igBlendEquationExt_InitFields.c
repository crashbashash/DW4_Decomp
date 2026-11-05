int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489118[4];
extern int DAT_00489120[4];
extern int DAT_00489128[4];
extern int DAT_00489130[4];
extern int DAT_00489138[4];
extern void * DAT_0055ff00[4];
int FUN_002d1870();
int thunk_igPsx2BlendEquationExt_GetMetaObject();

void igBlendEquationExt_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)(DAT_0055ff00[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489118[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00489138[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002d1870);
    igMetaObject_NameFields(temp_s0, &DAT_00489120[0], &DAT_00489128[0], &DAT_00489130[0], temp_s2);
    *(int *)((char *)(DAT_0055ff00[0]) + 60) = (int)(&thunk_igPsx2BlendEquationExt_GetMetaObject);
}
