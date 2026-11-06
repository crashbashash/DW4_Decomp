/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cbb80[4];
extern int DAT_004cbb88[4];
extern int DAT_004cbb90[4];
extern int DAT_004cbb98[4];
extern int DAT_0058bca8[4];
void beNDMWMcSlotGC_InitFields(void);
}
void beNDMWMcSlotGC_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bca8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbb80[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004cbb88[0], &DAT_004cbb90[0], &DAT_004cbb98[0], temp_s1);
}
