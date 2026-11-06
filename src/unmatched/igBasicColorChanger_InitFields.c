/* The constant store after GetFieldAt needs the call result in a local. */
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0840[4];
extern int DAT_004d0848[4];
extern int DAT_004d0850[4];
extern int DAT_004d0858[4];
extern int DAT_0058c5f0[4];
void igBasicColorChanger_InitFields(void) {
    void *temp_s0;
    int temp_s1;
    void *f;
    temp_s0 = (void *)DAT_0058c5f0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0840[0], 2);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)((char *)f + 52) = 4;
    igMetaObject_NameFields(temp_s0, &DAT_004d0848[0], &DAT_004d0850[0], &DAT_004d0858[0], temp_s1);
}
