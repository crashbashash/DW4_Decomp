igMetaObject *g_beTextureCtrlAttr_metaObject;
igMetaField *g_beTextureCtrlAttr_attrSetMetaField;

igMetaObject *beTextureCtrlAttr_GetMetaObject(void) {
    if (g_beTextureCtrlAttr_metaObject == 0 || !isValid(g_beTextureCtrlAttr_metaObject)) beTextureCtrlAttr_EnsureRegistered();
    return g_beTextureCtrlAttr_metaObject;
}

int beTextureCtrlAttr_GetVTable(void) {
    beTextureCtrlAttr obj;
    int vtable;
    igObject **attrSetSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beTextureCtrlAttr_vtable[0];
    attrSetSlot = (igObject **)&obj._attrSet;
    *attrSetSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beTextureCtrlAttr_vtable[0];
    igObjectRef_Release(attrSetSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beTextureCtrlAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlAttr_Register);
}

static igMetaObjectCallback g_beTextureCtrlAttr_callbackList[] = { igAttrSet_EnsureRegistered, 0 };

CallbackArray *beTextureCtrlAttr_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlAttr_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beTextureCtrlAttr_GetMetaObjectFunction,
        "beTextureCtrlAttr",
        0x10, /* instance size */
        beTextureCtrlAttr_GetVTable,
        beTextureCtrlAttr_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlAttr_callbackList /* callback list */
    );
}

void beTextureCtrlAttr_GetMetaObjectFunction(void)
{
    beTextureCtrlAttr_GetMetaObject();
}

static FieldFactory g_beTextureCtrlAttr_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrlAttr_fieldTable[] = {
    "_attrSet",
};
static igMetaField **g_beTextureCtrlAttr_fieldHandles[] = {
    &g_beTextureCtrlAttr_attrSetMetaField,
};
static int g_beTextureCtrlAttr_fieldOffsets[] = {
    12,
};

void beTextureCtrlAttr_InitFields(void) {
    int base;
    void *attrSet;
    igMetaObject *meta;

    meta = g_beTextureCtrlAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTextureCtrlAttr_ctorTable, 1);
    attrSet = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)attrSet)->_metaObject = (int)igAttrSet_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beTextureCtrlAttr_fieldTable, g_beTextureCtrlAttr_fieldHandles, g_beTextureCtrlAttr_fieldOffsets, base);
}

