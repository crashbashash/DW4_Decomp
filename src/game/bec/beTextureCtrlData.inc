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
    char *text;
    int *header;
    int refCount;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_beTextureCtrlData_vtable[0];
    obj._tex = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beTextureCtrlData_vtable[0];
    if (&obj._tex != 0) {
        text = (char *)obj._tex;
        if (text != 0) {
            ((igObject *)text)->_refCount = ((igObject *)text)->_refCount - 1;
            if ((((igObject *)text)->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(text);
            }
        }
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (&obj._name != 0) {
        text = (char *)obj._name;
        if (text != 0) {
            header = (int *)(text - 8);
            refCount = *(int *)(text - 4) - 1;
            *(int *)(text - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
    }
    return vtable;
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

