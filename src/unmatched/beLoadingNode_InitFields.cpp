/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4a50[4];
extern int DAT_004c4a58[4];
extern int DAT_004c4a60[4];
extern int DAT_004c4a68[4];
extern int DAT_005886e8[4];
void beLoadingNode_InitFields(void);
}
void beLoadingNode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005886e8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4a50[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c4a58[0], &DAT_004c4a60[0], &DAT_004c4a68[0], temp_s1);
}
