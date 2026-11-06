int FUN_0014a040();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485f68[4];
extern int DAT_00485f70[4];
extern int DAT_00485f78[4];
extern int DAT_00485f80[4];
extern int DAT_0055eeb0[4];
struct F { char pad[38]; unsigned char b38; unsigned char b39; unsigned char b40; char pad2[3]; unsigned char b44; char pad3[11]; int f56; };
void igRenderListAttr_InitFields(void) {
    int temp_s2;
    struct F *temp_v0;
    struct F *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055eeb0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485f68[0], 2);
    temp_v0 = (struct F *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002ea4b0(temp_v0, -1);
    temp_v0->b38 = 0;
    temp_s1 = (struct F *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    temp_s1->f56 = FUN_0014a040();
    temp_s1->b38 = 0;
    temp_s1->b40 = 1;
    temp_s1->b39 = 1;
    temp_s1->b44 = 3;
    igMetaObject_NameFields(temp_s0, &DAT_00485f70[0], &DAT_00485f78[0], &DAT_00485f80[0], temp_s2);
}
