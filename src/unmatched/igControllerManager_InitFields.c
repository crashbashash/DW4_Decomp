int FUN_00146300();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00487268[4];
extern int DAT_00487270[4];
extern int DAT_00487278[4];
extern int DAT_00487280[4];
extern void * DAT_0055f698[4];
int thunk_igPsx2ControllerManager_GetMetaObject();

void igControllerManager_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)(DAT_0055f698[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487268[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00146300();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487270[0], &DAT_00487278[0], &DAT_00487280[0], temp_s2);
    *(int *)((char *)(DAT_0055f698[0]) + 60) = (int)(&thunk_igPsx2ControllerManager_GetMetaObject);
}
