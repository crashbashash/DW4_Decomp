int FUN_002e3810(int, float);
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00488d10[4];
extern int DAT_00488d18[4];
extern int DAT_00488d20[4];
extern int DAT_00488d28[4];
extern int DAT_0055fd18[4];
void igLineWidthExt_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055fd18[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488d10[0], 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_00488d18[0], &DAT_00488d20[0], &DAT_00488d28[0], temp_s1);
}
