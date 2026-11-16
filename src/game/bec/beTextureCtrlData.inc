igMetaObject *g_beTextureCtrlData_metaObject;
igMetaField *g_beTextureCtrlData_texMetaField;

void *beTextureCtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beTextureCtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTextureCtrlData_EnsureRegistered();
    }
    return g_beTextureCtrlData_metaObject;
}

int beTextureCtrlData_GetVTable(void) {
    beTextureCtrlData obj;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_beTextureCtrlData_vtable[0];
    obj._tex = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beTextureCtrlData_vtable[0];
    if (&obj._tex != 0) {
        o = (char *)obj._tex;
        if (o != 0) {
            ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (&obj._name != 0) {
        o = (char *)obj._name;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beTextureCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlData_Register);
}

static igMetaObjectCallback g_beTextureCtrlData_callbackList[] = { igTextureAttr_EnsureRegistered, 0 };

void *beTextureCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beTextureCtrlData_GetMetaObjectFunction,
        "beTextureCtrlData",
        0x10, /* instance size */
        beTextureCtrlData_GetVTable,
        beTextureCtrlData_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlData_callbackList /* callback list */
    );
}

void beTextureCtrlData_GetMetaObjectFunction(void)
{
    beTextureCtrlData_GetMetaObject();
}

static FieldFactory g_beTextureCtrlData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrlData_fieldTable[] = {
    "_tex",
};
static igMetaField **g_beTextureCtrlData_fieldHandles[] = {
    &g_beTextureCtrlData_texMetaField,
};
static int g_beTextureCtrlData_fieldOffsets[] = {
    12,
};

void beTextureCtrlData_InitFields(void) {
    int base;
    void *tex;
    void *meta;

    meta = (void *)g_beTextureCtrlData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTextureCtrlData_ctorTable, 1);
    tex = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)tex)->_metaObject = igTextureAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beTextureCtrlData_fieldTable, g_beTextureCtrlData_fieldHandles, g_beTextureCtrlData_fieldOffsets, base);
}

