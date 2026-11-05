int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498048[4];
extern int DAT_00498050[4];
extern int DAT_00498058[4];
extern int DAT_00498060[4];
extern int DAT_0056db30[4];
extern int DAT_00587198[4];
void igMessageDefaultReceiver_InitFields(void) {
    int temp_s0;
    int temp_s1;
    char *p;

    temp_s0 = DAT_0056db30[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498048[0], 2);
    p = (char *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)(p + 56) = (int)DAT_00587198[0];
    p = (char *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    *(short *)(p + 20) = 0xC;
    igMetaObject_NameFields(temp_s0, &DAT_00498050[0], &DAT_00498058[0], &DAT_00498060[0], temp_s1);
}
