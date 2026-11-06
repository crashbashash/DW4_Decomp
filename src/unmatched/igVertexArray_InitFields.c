int FUN_002bfa60();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004887d0[4];
extern int DAT_004887e0[4];
extern int DAT_004887f0[4];
extern int DAT_00488800[4];
extern void * DAT_0055fac8[4];
int thunk_igPsx2VertexArray1_1_GetMetaObject();

void igVertexArray_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055fac8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004887d0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = FUN_002bfa60();
    *(char *)((char *)(temp_s1) + 40) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004887e0[0], &DAT_004887f0[0], &DAT_00488800[0], temp_s2);
    *(int *)((char *)(DAT_0055fac8[0]) + 60) = (int)(&thunk_igPsx2VertexArray1_1_GetMetaObject);
}
