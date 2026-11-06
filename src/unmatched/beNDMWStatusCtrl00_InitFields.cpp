/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004ca010[4];
extern int DAT_004ca018[4];
extern int DAT_004ca020[4];
extern int DAT_004ca028[4];
extern int DAT_0058afe0[4];
void beNDMWStatusCtrl00_InitFields(void);
}
void beNDMWStatusCtrl00_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058afe0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca010[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004ca018[0], &DAT_004ca020[0], &DAT_004ca028[0], temp_s1);
}
