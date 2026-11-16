igMetaObject *g_beNDMWSaveCtrl_metaObject;
igMetaField *g_beNDMWSaveCtrl_padManagerMetaField;

void beNDMWSaveCtrl_CreateInstance(int arg0) {
    beNDMWSaveCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWSaveCtrl_metaObject, arg0);
}

igMetaObject *beNDMWSaveCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWSaveCtrl_metaObject == 0) {
        g_beNDMWSaveCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWSaveCtrl_metaObject;
}

void *beNDMWSaveCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWSaveCtrl_EnsureRegistered();
    }
    return g_beNDMWSaveCtrl_metaObject;
}

int beNDMWSaveCtrl_GetVTable(void) {
    union U_3bd4d0 u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beNDMWSaveCtrl_vtable[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWSaveCtrl_vtable[0];
    FUN_0033dda0(ps, -1);
    FUN_0033f5e0(u.b, 0);
    return temp_s0;
}

void beNDMWSaveCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrl_Register);
}

static igMetaObjectCallback g_beNDMWSaveCtrl_callbackList[] = { bePadManager_EnsureRegistered, 0 };

void *beNDMWSaveCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWSaveCtrl_GetMetaObject,
        "beNDMWSaveCtrl",
        0x24, /* instance size */
        beNDMWSaveCtrl_GetVTable,
        beNDMWSaveCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveCtrl_callbackList /* callback list */
    );
}

void beNDMWSaveCtrl_GetMetaObject(void)
{
    beNDMWSaveCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWSaveCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWSaveCtrl_fieldTable[] = {
    "_padManager",
};
static igMetaField **g_beNDMWSaveCtrl_fieldHandles[] = {
    &g_beNDMWSaveCtrl_padManagerMetaField,
};
static int g_beNDMWSaveCtrl_fieldOffsets[] = {
    32,
};

void beNDMWSaveCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWSaveCtrl_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWSaveCtrl_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = bePadManager_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWSaveCtrl_fieldTable, g_beNDMWSaveCtrl_fieldHandles, g_beNDMWSaveCtrl_fieldOffsets, temp_s2);
}

