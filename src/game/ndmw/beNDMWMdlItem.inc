igMetaObject *g_beNDMWMdlItem_metaObject;
igMetaField *g_beNDMWMdlItem_viewerSIManagerMetaField;
igMetaField *g_beNDMWMdlItem_lockRamListMetaField;

void beNDMWMdlItem_CreateInstance(int arg0) {
    beNDMWMdlItem_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlItem_metaObject, arg0);
}

igMetaObject *beNDMWMdlItem_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlItem_metaObject == 0) {
        g_beNDMWMdlItem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlItem_metaObject;
}

igMetaObject *beNDMWMdlItem_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlItem_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWMdlItem_EnsureRegistered();
    return g_beNDMWMdlItem_metaObject;
}

int beNDMWMdlItem_GetVTable(void) {
    struct Obj_3c1200 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f24 = 0;
    o.vt = &g_beNDMWMdlItem_vtable[0];
    o.f48 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWMdlItem_vtable[0];
    igSmartPointer_igObjectList_Destruct(&o.f48, -1);
    FUN_003bf2f0((struct NamedRefObject *)&o, (long long)0);
    return r;
}

void beNDMWMdlItem_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItem_Register);
}

static igMetaObjectCallback g_beNDMWMdlItem_callbackList[] = { igViewerSceneInfoManager_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

void *beNDMWMdlItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlItem_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlItem_GetMetaObject,
        "beNDMWMdlItem",
        0x34, /* instance size */
        beNDMWMdlItem_GetVTable,
        beNDMWMdlItem_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItem_callbackList /* callback list */
    );
}

void beNDMWMdlItem_GetMetaObject(void)
{
    beNDMWMdlItem_GetReadyMetaObject();
}

static FieldFactory g_beNDMWMdlItem_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWMdlItem_fieldTable[] = {
    "_viewerSIManager",
    "_lockRamList",
};
static igMetaField **g_beNDMWMdlItem_fieldHandles[] = {
    &g_beNDMWMdlItem_viewerSIManagerMetaField,
    &g_beNDMWMdlItem_lockRamListMetaField,
};
static int g_beNDMWMdlItem_fieldOffsets[] = {
    44,
    48,
};

void beNDMWMdlItem_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWMdlItem_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWMdlItem_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igViewerSceneInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWMdlItem_fieldTable, g_beNDMWMdlItem_fieldHandles, g_beNDMWMdlItem_fieldOffsets, temp_s2);
}

