/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c71d0[4];
extern int DAT_004c71d8[4];
extern int DAT_004c71e0[4];
extern int DAT_004c71e8[4];
extern int DAT_00589898[4];
void beDataObjBool_InitFields(void);
}
void beDataObjBool_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589898[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c71d0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c71d8[0], &DAT_004c71e0[0], &DAT_004c71e8[0], temp_s1);
}
