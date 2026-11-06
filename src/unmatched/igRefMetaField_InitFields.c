int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf960[4];
extern int DAT_004bf968[4];
extern int DAT_004bf970[4];
extern int DAT_004bf978[4];
extern int DAT_00585a60[4];
void igRefMetaField_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00585a60[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf960[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004bf968[0], &DAT_004bf970[0], &DAT_004bf978[0], temp_s1);
}
