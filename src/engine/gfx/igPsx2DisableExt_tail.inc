igMetaObject *igPsx2DisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DisableExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2DisableExt_EnsureRegistered();
    return g_igPsx2DisableExt_metaObject;
}

int igPsx2DisableExt_GetVTable(void) {
    union U_153f60 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p40;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&DAT_00530a10[0];
    p38 = &u.b[8];
    *(int *)p38 = 0;
    p40 = &u.b[16];
    *(int *)p40 = 0;
    u.vt = (int)&g_igPsx2DisableExt_vtable[0];
    r = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00530a10[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    return r;
}

void igPsx2DisableExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2DisableExt_Register);
}

static igMetaObjectCallback g_igPsx2DisableExt_callbackList[] = { Gap::Gfx::igPsx2VisualContext::arkRegister, 0 };

CallbackArray *igPsx2DisableExt_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2DisableExt_metaObject,
        igDisableExt_Register,
        igDisableExt_GetPublishedMetaObject,
        igPsx2DisableExt_GetMetaObjectFunction,
        "igPsx2DisableExt",
        0x18, /* instance size */
        igPsx2DisableExt_GetVTable,
        &igPsx2DisableExt_InitFields,
        0, /* extra callback item */
        g_igPsx2DisableExt_callbackList /* callback list */
    );
}

igMetaObject *igDisableExt_GetPublishedMetaObject(void) {
    return g_igDisableExt_metaObject;
}

static FieldFactory g_igPsx2DisableExt_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igPsx2DisableExt_fieldTable[] = {
    "_context",
};
static igMetaField **g_igPsx2DisableExt_fieldHandles[] = {
    &g_igPsx2DisableExt_contextMetaField,
};
static int g_igPsx2DisableExt_fieldOffsets[] = {
    20,
};

void igPsx2DisableExt_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPsx2DisableExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2DisableExt_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)Gap::Gfx::igPsx2VisualContext::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_igPsx2DisableExt_fieldTable, g_igPsx2DisableExt_fieldHandles, g_igPsx2DisableExt_fieldOffsets, fieldStart);
}

