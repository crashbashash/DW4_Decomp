/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5798[4];
extern int DAT_004c57a0[4];
extern int DAT_004c57a8[4];
extern int DAT_004c57b0[4];
extern int DAT_00588d70[4];
void beModelCtrlPDMOVE_InitFields(void);
}
void beModelCtrlPDMOVE_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588d70[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5798[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c57a0[0], &DAT_004c57a8[0], &DAT_004c57b0[0], temp_s1);
}
