/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7350[4];
extern int DAT_004c7370[4];
extern int DAT_004c7390[4];
extern int DAT_004c73b0[4];
extern int DAT_00589960[4];
void beCriVolume_InitFields(void);
}
void beCriVolume_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589960[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7350[0], 6);
    igMetaObject_NameFields(temp_s0, &DAT_004c7370[0], &DAT_004c7390[0], &DAT_004c73b0[0], temp_s1);
}
