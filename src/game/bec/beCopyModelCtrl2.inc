igMetaObject *g_beCopyModelCtrl2_metaObject;
igMetaField *g_beCopyModelCtrl2_srcNodeMetaField;

igMetaObject *FUN_003680b0(void)
{
    igMetaObject *g = g_beCopyModelCtrl2_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003681a0();
    return g_beCopyModelCtrl2_metaObject;
}

int beCopyModelCtrl2_GetVTable(void) {
    CopyModelCtrl2View copy;
    return *(int *)((char *)&copy + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_003681a0(void)
{
    igMetaObject_RunStaticInit(beCopyModelCtrl2_Register);
}

static igMetaObjectCallback g_beCopyModelCtrl2_callbackList[] = { FUN_0034fe80, 0 };

void *beCopyModelCtrl2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCopyModelCtrl2_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyModelCtrl2_GetMetaObject,
        "beCopyModelCtrl2",
        0x70, /* instance size */
        beCopyModelCtrl2_GetVTable,
        beCopyModelCtrl2_InitFields,
        FUN_003682f0, /* extra callback item */
        g_beCopyModelCtrl2_callbackList /* callback list */
    );
}

void beCopyModelCtrl2_GetMetaObject(void)
{
    FUN_003680b0();
}

static FieldFactory g_beCopyModelCtrl2_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beCopyModelCtrl2_fieldTable[] = {
    "_srcNode",
};
static igMetaField **g_beCopyModelCtrl2_fieldHandles[] = {
    &g_beCopyModelCtrl2_srcNodeMetaField,
};
static int g_beCopyModelCtrl2_fieldOffsets[] = {
    108,
};

void beCopyModelCtrl2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCopyModelCtrl2_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCopyModelCtrl2_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034fd40();
    igMetaObject_NameFields(temp_s0, g_beCopyModelCtrl2_fieldTable, g_beCopyModelCtrl2_fieldHandles, g_beCopyModelCtrl2_fieldOffsets, temp_s2);
}

void FUN_003682f0(void)
{
    beCopyModelCtrl2_RegisterTraversal();
}

