igMetaObject *g_beChangePosTransformInfoRam_metaObject;
igMetaField *g_beChangePosTransformInfoRam_transformMetaField;

igMetaObject *beChangePosTransformInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beChangePosTransformInfoRam_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beChangePosTransformInfoRam_EnsureRegistered();
    return g_beChangePosTransformInfoRam_metaObject;
}

int beChangePosTransformInfoRam_GetVTable(void) {
    Obj_368360 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m40 = 0;
    obj.vt = &g_beChangePosTransformInfoRam_vtable[0];
    obj.m44 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beChangePosTransformInfoRam_vtable[0];
    obj.rel44();
    obj.vt = &g_beBaseInfoRam_vtable[0];
    obj.rel40();
    return r;
}

void beChangePosTransformInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfoRam_Register);
}

static igMetaObjectCallback g_beChangePosTransformInfoRam_callbackList[] = { igTransform_EnsureRegistered, 0 };

void *beChangePosTransformInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beChangePosTransformInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beChangePosTransformInfoRam_GetMetaObjectFunction,
        "beChangePosTransformInfoRam",
        0x30, /* instance size */
        beChangePosTransformInfoRam_GetVTable,
        beChangePosTransformInfoRam_InitFields,
        0, /* extra callback item */
        g_beChangePosTransformInfoRam_callbackList /* callback list */
    );
}

void beChangePosTransformInfoRam_GetMetaObjectFunction(void)
{
    beChangePosTransformInfoRam_GetMetaObject();
}

static FieldFactory g_beChangePosTransformInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beChangePosTransformInfoRam_fieldTable[] = {
    "_transform",
};
static igMetaField **g_beChangePosTransformInfoRam_fieldHandles[] = {
    &g_beChangePosTransformInfoRam_transformMetaField,
};
static int g_beChangePosTransformInfoRam_fieldOffsets[] = {
    44,
};

void beChangePosTransformInfoRam_InitFields(void) {
    int base;
    void *transform;
    void *meta;

    meta = (void *)g_beChangePosTransformInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beChangePosTransformInfoRam_ctorTable, 1);
    transform = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)transform)->_metaObject = igTransform_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beChangePosTransformInfoRam_fieldTable, g_beChangePosTransformInfoRam_fieldHandles, g_beChangePosTransformInfoRam_fieldOffsets, base);
}

