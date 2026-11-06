/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cbba0[4];
extern int DAT_004cbbc0[4];
extern int DAT_004cbbe0[4];
extern int DAT_004cbc00[4];
extern int DAT_0058bcc8[4];
void beNDMWMcSlot_InitFields(void);
}
void beNDMWMcSlot_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058bcc8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbba0[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004cbbc0[0], &DAT_004cbbe0[0], &DAT_004cbc00[0], temp_s1);
}
