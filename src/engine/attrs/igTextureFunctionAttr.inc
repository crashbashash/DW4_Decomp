void FUN_00131c60(int arg0) {
    FUN_00131d80();
    igMetaObject_CreateInstance(*(int *)0x55ED00, arg0);
}

int FUN_00131ca0(void) {
    if (DAT_0055ed00[0] == 0) {
        DAT_0055ed00[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055ed00[0];
}

igMetaObject *igTextureFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00131d80();
    return g_igTextureFunctionAttr_metaObject[0];
}

int igTextureFunctionAttr_GetVTable(void) {
    struct Obj_131d40 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522a10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00131d80(void)
{
    igMetaObject_RunStaticInit(igTextureFunctionAttr_Register);
}

void igTextureFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureFunctionAttr_GetMetaObject,
        igTextureFunctionAttr_className,
        sizeof(igTextureFunctionAttr),                     /* Instance size. */
        igTextureFunctionAttr_GetVTable,
        &igTextureFunctionAttr_InitFields,
        FUN_00131f70, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureFunctionAttr_GetMetaObject(void) {
    igTextureFunctionAttr_GetMetaObject();
}

void igTextureFunctionAttr_InitFields(void) {
    void *temp_s1;
    int temp_s0;
    struct TextureMetaFieldView *temp_v0;
    struct TextureMetaFieldView *temp_v0_2;
    struct TextureMetaFieldView *t1;
    struct TextureMetaFieldView *t2;
    struct TextureMetaFieldView *t3;
    struct TextureMetaFieldView *t4;

    temp_s1 = (void *)DAT_0055ed00[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00485b60[0], 7);
    temp_v0 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0);
    FUN_002dc7a0(temp_v0, &DAT_00485be0[0]);
    temp_v0->f52 = FUN_002d1870;
    t1 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1);
    t1->f48 = (void (*)())FUN_00141250;
    t2 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2);
    t2->f52 = FUN_0014d450;
    t3 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3);
    t3->f52 = FUN_0014d450;
    t4 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4);
    t4->f52 = FUN_0014d4b0;
    FUN_0030e750(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5), 2);
    temp_v0_2 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6);
    FUN_002dc7a0(temp_v0_2, &DAT_00485be8[0]);
    temp_v0_2->f52 = FUN_0014d510;
    igMetaObject_NameFields(temp_s1, &DAT_00485b80[0], &DAT_00485ba0[0], &DAT_00485bc0[0], temp_s0);
}

void FUN_00131f70(void) {
    FUN_001412a0();
}

