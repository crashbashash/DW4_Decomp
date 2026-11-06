/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5878[4];
extern int DAT_004c5880[4];
extern int DAT_004c5888[4];
extern int DAT_004c5890[4];
extern int DAT_00588e10[4];
void beModelCtrlLABELCTRL_InitFields(void);
}
void beModelCtrlLABELCTRL_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588e10[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5878[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c5880[0], &DAT_004c5888[0], &DAT_004c5890[0], temp_s1);
}
