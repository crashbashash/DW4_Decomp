int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048ae08[4];
extern int DAT_0048ae18[4];
extern int DAT_0048ae28[4];
extern int DAT_0048ae38[4];
extern int DAT_00560fe0[4];
int FUN_001869e0();

void igPlane_InitFields(void) {
    int temp_s0;
    int temp_s1;
    void *f;

    temp_s0 = DAT_00560fe0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ae08[0], 3);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    *(int *)((char *)f + 52) = (int)(&FUN_001869e0);
    igMetaObject_NameFields(temp_s0, &DAT_0048ae18[0], &DAT_0048ae28[0], &DAT_0048ae38[0], temp_s1);
}
