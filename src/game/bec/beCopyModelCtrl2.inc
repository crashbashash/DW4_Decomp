igMetaObject *g_beCopyModelCtrl2_metaObject;
igMetaField *g_beCopyModelCtrl2_srcNodeMetaField;

igMetaObject *beCopyModelCtrl2_GetMetaObject(void)
{
    igMetaObject *g = g_beCopyModelCtrl2_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beCopyModelCtrl2_EnsureRegistered();
    return g_beCopyModelCtrl2_metaObject;
}

int beCopyModelCtrl2_GetVTable(void) {
    CopyModelCtrl2View copy;
    return *(int *)((char *)&copy + *(int *)((char *)g_objectSystem + 916));
}

void beCopyModelCtrl2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCopyModelCtrl2_Register);
}

static igMetaObjectCallback g_beCopyModelCtrl2_callbackList[] = { beModelCtrlNode2_EnsureRegistered, 0 };

CallbackArray *beCopyModelCtrl2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCopyModelCtrl2_metaObject,
        (igMetaObjectRegisterFunction)igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyModelCtrl2_GetMetaObjectFunction,
        "beCopyModelCtrl2",
        0x70, /* instance size */
        beCopyModelCtrl2_GetVTable,
        beCopyModelCtrl2_InitFields,
        beCopyModelCtrl2_StaticInitCallback, /* extra callback item */
        g_beCopyModelCtrl2_callbackList /* callback list */
    );
}

void beCopyModelCtrl2_GetMetaObjectFunction(void)
{
    beCopyModelCtrl2_GetMetaObject();
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
    int base;
    void *srcNode;
    igMetaObject *meta;

    meta = g_beCopyModelCtrl2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCopyModelCtrl2_ctorTable, 1);
    srcNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)srcNode)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beCopyModelCtrl2_fieldTable, g_beCopyModelCtrl2_fieldHandles, g_beCopyModelCtrl2_fieldOffsets, base);
}

void beCopyModelCtrl2_StaticInitCallback(void)
{
    beCopyModelCtrl2_RegisterTraversal();
}

