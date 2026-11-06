/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c8180[4];
extern int DAT_004c8190[4];
extern int DAT_004c81a0[4];
extern int DAT_004c81b0[4];
extern int DAT_00589fe8[4];
void beAction2MOTIONSET_InitFields(void);
}
void beAction2MOTIONSET_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589fe8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8180[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c8190[0], &DAT_004c81a0[0], &DAT_004c81b0[0], temp_s1);
}
