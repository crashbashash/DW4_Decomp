/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7858[4];
extern int DAT_004c7860[4];
extern int DAT_004c7868[4];
extern int DAT_004c7870[4];
extern int DAT_00587198[4];
extern int DAT_00589bd8[4];
void beCameraCtrlInfo_InitFields(void);
}
void beCameraCtrlInfo_InitFields(void) {
    void *temp_s0;
    int temp_s1;
    void *f;

    temp_s0 = (void *)DAT_00589bd8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7858[0], 1);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)((char *)f + 56) = DAT_00587198[0];
    igMetaObject_NameFields(temp_s0, &DAT_004c7860[0], &DAT_004c7868[0], &DAT_004c7870[0], temp_s1);
}
