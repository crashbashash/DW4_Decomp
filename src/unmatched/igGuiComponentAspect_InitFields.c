int FUN_0018e470();
int FUN_0044f540();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0538[4];
extern int DAT_004d0548[4];
extern int DAT_004d0558[4];
extern int DAT_004d0568[4];
extern int DAT_0058c480[4];
struct GuiAspectMetaField { char pad[56]; int f56; char b60; };

void igGuiComponentAspect_InitFields(void) {
    float v1[3];
    float v2[4];
    void *temp_a0_2;
    void *temp_a0;
    int temp_s2;
    struct GuiAspectMetaField *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c480[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0538[0], 3);
    temp_s1 = (struct GuiAspectMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_s1->f56 = FUN_0044f540();
    temp_s1->b60 = 0;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    v1[0] = 0.0f;
    v1[1] = 0.0f;
    v1[2] = 0.0f;
    FUN_0018e470(temp_a0, v1);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    v2[2] = 1.0f;
    v2[0] = 3.4028235e+38f;
    v2[1] = 3.4028235e+38f;
    FUN_0018e470(temp_a0_2, v2);
    igMetaObject_NameFields(temp_s0, &DAT_004d0548[0], &DAT_004d0558[0], &DAT_004d0568[0], temp_s2);
}
