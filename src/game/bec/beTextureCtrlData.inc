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
    int vtable;
    igObject **texSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beTextureCtrlData_vtable[0];
    texSlot = (igObject **)&obj._tex;
    *texSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beTextureCtrlData_vtable[0];
    igObjectRef_Release(texSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beTextureCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlData_Register);
}

static igMetaObjectCallback g_beTextureCtrlData_callbackList[] = { igTextureAttr_EnsureRegistered, 0 };

CallbackArray *beTextureCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlData_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
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
    igMetaObject *meta;

    meta = g_beTextureCtrlData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTextureCtrlData_ctorTable, 1);
    tex = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)tex)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beTextureCtrlData_fieldTable, g_beTextureCtrlData_fieldHandles, g_beTextureCtrlData_fieldOffsets, base);
}

