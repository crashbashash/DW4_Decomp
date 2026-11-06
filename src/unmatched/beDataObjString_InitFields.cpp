/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igStringMetaField_SetDefaultText(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7188[4];
extern int DAT_004c7190[4];
extern int DAT_004c7198[4];
extern int DAT_004c71a0[4];
extern int DAT_00589878[4];
void beDataObjString_InitFields(void);
}
void beDataObjString_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589878[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7188[0], 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c7190[0], &DAT_004c7198[0], &DAT_004c71a0[0], temp_s1);
}
