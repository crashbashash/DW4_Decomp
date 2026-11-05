int igIntMetaField_GetDefaultDescriptor();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00487428[4];
extern int DAT_00487430[4];
extern int DAT_00487438[4];
extern int DAT_00487440[4];
extern void * DAT_0055f6b0[4];
void thunk_igPsx2Controller_GetMetaObject(void);

void igController_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)(DAT_0055f6b0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487428[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = igIntMetaField_GetDefaultDescriptor();
    *(char *)((char *)(temp_s1) + 53) = 1;
    *(char *)((char *)(temp_s1) + 64) = 1;
    *(char *)((char *)(temp_s1) + 65) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487430[0], &DAT_00487438[0], &DAT_00487440[0], temp_s2);
    *(int *)((char *)(DAT_0055f6b0[0]) + 60) = (int)thunk_igPsx2Controller_GetMetaObject;
}
