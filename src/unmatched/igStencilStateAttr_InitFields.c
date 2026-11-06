int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485e48[4];
extern int DAT_00485e50[4];
extern int DAT_00485e58[4];
extern int DAT_00485e60[4];
extern int DAT_0055ee40[4];
void igStencilStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ee40[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485e48[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00485e50[0], &DAT_00485e58[0], &DAT_00485e60[0], temp_s1);
}
