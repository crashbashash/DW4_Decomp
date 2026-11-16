igMetaObject *g_beCopyTransform_metaObject;
igMetaField *g_beCopyTransform_srcTransformMetaField;

void *beCopyTransform_GetMetaObject(void) {
    igMetaObject *g = g_beCopyTransform_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCopyTransform_EnsureRegistered();
    }
    return g_beCopyTransform_metaObject;
}

int beCopyTransform_GetVTable(void) {
    CopyTransformView transform;
    return *(int *)((char *)&transform + *(int *)((char *)g_objectSystem[0] + 916));
}

void beCopyTransform_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCopyTransform_Register);
}

static igMetaObjectCallback g_beCopyTransform_callbackList[] = { igTransform_EnsureRegistered, 0 };

void *beCopyTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCopyTransform_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyTransform_GetMetaObjectFunction,
        "beCopyTransform",
        0x70, /* instance size */
        beCopyTransform_GetVTable,
        beCopyTransform_InitFields,
        beCopyTransform_StaticInitCallback, /* extra callback item */
        g_beCopyTransform_callbackList /* callback list */
    );
}

void beCopyTransform_GetMetaObjectFunction(void)
{
    beCopyTransform_GetMetaObject();
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
    int base;
    void *srcTransform;
    void *meta;

    meta = (void *)g_beCopyTransform_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCopyTransform_ctorTable, 1);
    srcTransform = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)srcTransform)->_metaObject = igTransform_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beCopyTransform_fieldTable, g_beCopyTransform_fieldHandles, g_beCopyTransform_fieldOffsets, base);
}

void beCopyTransform_StaticInitCallback(void)
{
    beCopyTransform_RegisterTraversal();
}

