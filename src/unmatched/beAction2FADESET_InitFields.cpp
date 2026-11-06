extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c8120[4];
extern int DAT_004c8128[4];
extern int DAT_004c8130[4];
extern int DAT_004c8138[4];
extern int DAT_00589fb0[4];
void beAction2FADESET_InitFields(void);
}
void beAction2FADESET_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589fb0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8120[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c8128[0], &DAT_004c8130[0], &DAT_004c8138[0], temp_s1);
}
