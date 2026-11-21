igMetaObject *igPsx2PointSpriteExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2PointSpriteExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2PointSpriteExt_EnsureRegistered();
    return g_igPsx2PointSpriteExt_metaObject;
}

int igPsx2PointSpriteExt_GetVTable(void) {
    struct O_1531c0 o;
    int temp_s0;
    char *pa = (char *)&o;

    igObject_InitHeader((igObject *)&o);
    o.f8 = 0;
    o.vt = (int)&g_igPointSpriteExt_vtable[0];
    o.f16 = 0;
    o.f24 = 0;
    igMatrix44f_SetIdentity((float *)&o.t[8]);
    igMatrix44f_SetIdentity((float *)(pa + 104));
    igMatrix44f_SetIdentity((float *)(pa + 168));
    igMatrix44f_SetIdentity((float *)(pa + 232));
    igMatrix44f_SetIdentity((float *)(pa + 296));
    o.vt = (int)&g_igPsx2PointSpriteExt_vtable[0];
    temp_s0 = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = (int)&g_igPsx2PointSpriteExt_vtable[0];
    FUN_0014c440((O *)&o, 0);
    return temp_s0;
}

void igPsx2PointSpriteExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2PointSpriteExt_Register);
}

static igMetaObjectCallback g_igPsx2PointSpriteExt_callbackList[] = { igPsx2VisualContext_EnsureRegistered, 0 };

CallbackArray *igPsx2PointSpriteExt_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2PointSpriteExt_metaObject,
        igPointSpriteExt_Register,
        igPointSpriteExt_GetPublishedMetaObject,
        igPsx2PointSpriteExt_GetMetaObjectFunction,
        "igPsx2PointSpriteExt",
        0x18C, /* instance size */
        igPsx2PointSpriteExt_GetVTable,
        &igPsx2PointSpriteExt_InitFields,
        0, /* extra callback item */
        g_igPsx2PointSpriteExt_callbackList /* callback list */
    );
}

igMetaObject *igPointSpriteExt_GetPublishedMetaObject(void) {
    return g_igPointSpriteExt_metaObject;
}

static FieldFactory g_igPsx2PointSpriteExt_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igPsx2PointSpriteExt_fieldTable[] = {
    "_context",
};
static igMetaField **g_igPsx2PointSpriteExt_fieldHandles[] = {
    &g_igPsx2PointSpriteExt_contextMetaField,
};
static int g_igPsx2PointSpriteExt_fieldOffsets[] = {
    392,
};

void igPsx2PointSpriteExt_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPsx2PointSpriteExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2PointSpriteExt_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igPsx2VisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_igPsx2PointSpriteExt_fieldTable, g_igPsx2PointSpriteExt_fieldHandles, g_igPsx2PointSpriteExt_fieldOffsets, fieldStart);
}

