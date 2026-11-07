extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c8140[4];
extern int DAT_004c8150[4];
extern int DAT_004c8160[4];
extern int DAT_004c8170[4];
extern int DAT_00589fc8[4];
void beAction2JOINTSET_InitFields(void);
}
void beAction2JOINTSET_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589fc8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8140[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c8150[0], &DAT_004c8160[0], &DAT_004c8170[0], temp_s1);
}
