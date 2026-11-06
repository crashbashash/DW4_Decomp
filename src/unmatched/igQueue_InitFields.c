int FUN_002b8390();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf9b8[4];
extern int DAT_004bf9c0[4];
extern int DAT_004bf9c8[4];
extern int DAT_004bf9d0[4];
extern void * DAT_00585aa8[4];
extern void thunk_igStandardQueue_GetMetaObject(void);

void igQueue_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00585aa8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf9b8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_002b8390();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004bf9c0[0], &DAT_004bf9c8[0], &DAT_004bf9d0[0], temp_s2);
    *(int *)((char *)(DAT_00585aa8[0]) + 60) = (int)thunk_igStandardQueue_GetMetaObject;
}
