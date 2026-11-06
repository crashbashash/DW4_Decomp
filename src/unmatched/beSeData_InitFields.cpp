extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3bd8[4];
extern int DAT_004c3be0[4];
extern int DAT_004c3be8[4];
extern int DAT_004c3bf0[4];
extern int DAT_00587fd0[4];
void beSeData_InitFields(void);
}
void beSeData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587fd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3bd8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c3be0[0], &DAT_004c3be8[0], &DAT_004c3bf0[0], temp_s1);
}
