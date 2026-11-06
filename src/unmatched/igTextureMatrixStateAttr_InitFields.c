struct F { char pad[48]; int *f48; };
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00141620(void);
extern int DAT_00485af8[4];
extern int DAT_00485b00[4];
extern int DAT_00485b08[4];
extern int DAT_00485b10[4];
extern int DAT_0055ecc0[4];
void igTextureMatrixStateAttr_InitFields(void) {
    int temp_s0;
    int temp_s1;
    struct F *f;

    temp_s0 = DAT_0055ecc0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485af8[0], 2);
    f = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    f->f48 = (int *)FUN_00141620;
    igMetaObject_NameFields(temp_s0, &DAT_00485b00[0], &DAT_00485b08[0], &DAT_00485b10[0], temp_s1);
}
