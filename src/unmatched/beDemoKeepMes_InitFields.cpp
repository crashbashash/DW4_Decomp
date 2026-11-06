/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7080[4];
extern int DAT_004c70a0[4];
extern int DAT_004c70c0[4];
extern int DAT_004c70e0[4];
extern int DAT_005897f8[4];
void beDemoKeepMes_InitFields(void);
}
void beDemoKeepMes_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005897f8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7080[0], 7);
    igMetaObject_NameFields(temp_s0, &DAT_004c70a0[0], &DAT_004c70c0[0], &DAT_004c70e0[0], temp_s1);
}
