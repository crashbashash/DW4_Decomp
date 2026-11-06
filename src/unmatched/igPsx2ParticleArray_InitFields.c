int FUN_002d3890();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489eb0[4];
extern int DAT_00489ed0[4];
extern int DAT_00489ef0[4];
extern int DAT_00489f10[4];
extern void * DAT_00560540[4];
int thunk_igParticleArray_GetMetaObject();

void igPsx2ParticleArray_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00560540[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489eb0[0], 5);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1)) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)) + 38) = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00489ed0[0], &DAT_00489ef0[0], &DAT_00489f10[0], temp_s1);
    *(int *)((char *)(DAT_00560540[0]) + 64) = (int)(&thunk_igParticleArray_GetMetaObject);
}
