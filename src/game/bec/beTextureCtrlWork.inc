igMetaObject *g_beTextureCtrlWork_metaObject;
igMetaField *g_beTextureCtrlWork_textureListMetaField;
igMetaField *g_beTextureCtrlWork_attributeListMetaField;

void beTextureCtrlWork_Create(int allocator) {
    beTextureCtrlWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587CD0, allocator);
}

igMetaObject *beTextureCtrlWork_GetOrCreateMetaObject(void) {
    if (g_beTextureCtrlWork_metaObject == 0) {
        g_beTextureCtrlWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beTextureCtrlWork_metaObject;
}

void *beTextureCtrlWork_GetMetaObject(void) {
    bool ok;
    if (g_beTextureCtrlWork_metaObject == 0) goto make;
    ok = !!(g_beTextureCtrlWork_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beTextureCtrlWork_EnsureRegistered();
done:;
    return g_beTextureCtrlWork_metaObject;
}

int beTextureCtrlWork_GetVTable(void) {
    beTextureCtrlWork obj;
    int vtable;
    igObject **attributeListSlot;
    igObject **textureListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beTextureCtrlWork_vtable[0];
    textureListSlot = (igObject **)&obj._textureList;
    *textureListSlot = 0;
    attributeListSlot = (igObject **)&obj._attributeList;
    *attributeListSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beTextureCtrlWork_vtable[0];
    igObjectRef_Release(attributeListSlot);
    igObjectRef_Release(textureListSlot);
    return vtable;
}

void beTextureCtrlWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlWork_Register);
}

static igMetaObjectCallback g_beTextureCtrlWork_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beTextureCtrlWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beTextureCtrlWork_GetMetaObjectFunction,
        "beTextureCtrlWork",
        0x10, /* instance size */
        beTextureCtrlWork_GetVTable,
        beTextureCtrlWork_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlWork_callbackList /* callback list */
    );
}

void beTextureCtrlWork_GetMetaObjectFunction(void)
{
    beTextureCtrlWork_GetMetaObject();
}

static FieldFactory g_beTextureCtrlWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrlWork_fieldTable[] = {
    "_textureList",
    "_attributeList",
};
static igMetaField **g_beTextureCtrlWork_fieldHandles[] = {
    &g_beTextureCtrlWork_textureListMetaField,
    &g_beTextureCtrlWork_attributeListMetaField,
};
static int g_beTextureCtrlWork_fieldOffsets[] = {
    8,
    12,
};

void beTextureCtrlWork_InitFields(void) {
    int base;
    void *attributeList;
    void *textureList;
    void *meta;

    meta = (void *)g_beTextureCtrlWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTextureCtrlWork_ctorTable, 2);
    textureList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)textureList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)textureList)->_construct = 1;
    attributeList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)attributeList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)attributeList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beTextureCtrlWork_fieldTable, g_beTextureCtrlWork_fieldHandles, g_beTextureCtrlWork_fieldOffsets, base);
}

