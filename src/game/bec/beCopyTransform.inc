igMetaObject *g_beCopyTransform_metaObject;
igMetaField *g_beCopyTransform_srcTransformMetaField;

void *FUN_00367e50(void) {
    igMetaObject *g = g_beCopyTransform_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00367f40();
    }
    return g_beCopyTransform_metaObject;
}

int beCopyTransform_GetVTable(void) {
    CopyTransformView transform;
    return *(int *)((char *)&transform + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00367f40(void)
{
    igMetaObject_RunStaticInit(beCopyTransform_Register);
}

static igMetaObjectCallback g_beCopyTransform_callbackList[] = { FUN_001964d0, 0 };

void *beCopyTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCopyTransform_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyTransform_GetMetaObject,
        "beCopyTransform",
        0x70, /* instance size */
        beCopyTransform_GetVTable,
        beCopyTransform_InitFields,
        FUN_00368090, /* extra callback item */
        g_beCopyTransform_callbackList /* callback list */
    );
}

void beCopyTransform_GetMetaObject(void)
{
    FUN_00367e50();
}

static FieldFactory g_beCopyTransform_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beCopyTransform_fieldTable[] = {
    "_srcTransform",
};
static igMetaField **g_beCopyTransform_fieldHandles[] = {
    &g_beCopyTransform_srcTransformMetaField,
};
static int g_beCopyTransform_fieldOffsets[] = {
    108,
};

void beCopyTransform_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCopyTransform_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCopyTransform_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    igMetaObject_NameFields(temp_s0, g_beCopyTransform_fieldTable, g_beCopyTransform_fieldHandles, g_beCopyTransform_fieldOffsets, temp_s2);
}

void FUN_00368090(void)
{
    beCopyTransform_RegisterTraversal();
}

