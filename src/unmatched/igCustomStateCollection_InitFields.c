int igStringMetaField_SetDefaultText();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00489050[4];
extern int DAT_00489058[4];
extern int DAT_00489060[4];
extern int DAT_00489068[4];
extern int DAT_004dc870[4];
extern int DAT_0055fe70[4];
void igCustomStateCollection_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055fe70[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489050[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), &DAT_004dc870[0]);
    igMetaObject_NameFields(temp_s0, &DAT_00489058[0], &DAT_00489060[0], &DAT_00489068[0], temp_s1);
}
