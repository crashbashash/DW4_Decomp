igMetaObject *g_beTextureCtrlInfo_metaObject;
igMetaField *g_beTextureCtrlInfo_isTextureMetaField;
igMetaField *g_beTextureCtrlInfo_dataListMetaField;

igMetaObject *beTextureCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beTextureCtrlInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beTextureCtrlInfo_EnsureRegistered();
done:
    return g_beTextureCtrlInfo_metaObject;
}

int beTextureCtrlInfo_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&g_beTextureCtrlInfo_vtable[0]);
    obj.f20 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beTextureCtrlInfo_vtable[0]);
    FUN_00199450(&obj.f20, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
}

void beTextureCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfo_Register);
}

static igMetaObjectCallback g_beTextureCtrlInfo_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beTextureCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beTextureCtrlInfo_GetMetaObjectFunction,
        "beTextureCtrlInfo",
        0x24, /* instance size */
        beTextureCtrlInfo_GetVTable,
        beTextureCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlInfo_callbackList /* callback list */
    );
}

void beTextureCtrlInfo_GetMetaObjectFunction(void)
{
    beTextureCtrlInfo_GetMetaObject();
}

static FieldFactory g_beTextureCtrlInfo_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrlInfo_fieldTable[] = {
    "_isTexture",
    "_dataList",
};
static igMetaField **g_beTextureCtrlInfo_fieldHandles[] = {
    &g_beTextureCtrlInfo_isTextureMetaField,
    &g_beTextureCtrlInfo_dataListMetaField,
};
static int g_beTextureCtrlInfo_fieldOffsets[] = {
    28,
    32,
};

void beTextureCtrlInfo_InitFields(void) {
    int base;
    void *dataList;
    void *meta;

    meta = (void *)g_beTextureCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTextureCtrlInfo_ctorTable, 2);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)dataList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beTextureCtrlInfo_fieldTable, g_beTextureCtrlInfo_fieldHandles, g_beTextureCtrlInfo_fieldOffsets, base);
}

