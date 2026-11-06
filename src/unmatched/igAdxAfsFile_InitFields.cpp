/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c2670[4];
extern int DAT_004c2678[4];
extern int DAT_004c2680[4];
extern int DAT_004c2688[4];
extern int DAT_00587638[4];
void igAdxAfsFile_InitFields(void);
}
void igAdxAfsFile_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00587638[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c2670[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c2678[0], &DAT_004c2680[0], &DAT_004c2688[0], temp_s1);
}
