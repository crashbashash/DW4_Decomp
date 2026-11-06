int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048a0d8[4];
extern int DAT_0048a0e0[4];
extern int DAT_0048a0e8[4];
extern int DAT_0048a0f0[4];
extern void * DAT_00560610[4];
extern void thunk_igClut_GetMetaObject(void);
void igPsx2Clut_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;
    temp_s0 = (void *)(DAT_00560610[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048a0d8[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002ea4b0(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048a0e0[0], &DAT_0048a0e8[0], &DAT_0048a0f0[0], temp_s2);
    *(int *)((char *)(DAT_00560610[0]) + 64) = (int)thunk_igClut_GetMetaObject;
}
