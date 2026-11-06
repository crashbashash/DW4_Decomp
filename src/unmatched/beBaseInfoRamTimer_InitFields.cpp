/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int FUN_002e3810(int, float);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7c70[4];
extern int DAT_004c7c90[4];
extern int DAT_004c7cb0[4];
extern int DAT_004c7cd0[4];
extern int DAT_00589d78[4];
void beBaseInfoRamTimer_InitFields(void);
}
void beBaseInfoRamTimer_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589d78[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7c70[0], 6);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5), 0.0f);
    igMetaObject_NameFields(temp_s0, &DAT_004c7c90[0], &DAT_004c7cb0[0], &DAT_004c7cd0[0], temp_s1);
}
