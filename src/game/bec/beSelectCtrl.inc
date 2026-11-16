igMetaObject *g_beSelectCtrl_metaObject;
igMetaField *g_beSelectCtrl_padManagerMetaField;
igMetaField *g_beSelectCtrl_isEnableCtrlMetaField;

void beSelectCtrl_CreateInstance(int allocator) {
    beSelectCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587F98, allocator);
}

igMetaObject *beSelectCtrl_GetOrCreateMetaObject(void) {
    if (g_beSelectCtrl_metaObject == 0) {
        g_beSelectCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSelectCtrl_metaObject;
}

void *beSelectCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beSelectCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSelectCtrl_EnsureRegistered();
    }
    return g_beSelectCtrl_metaObject;
}

int beSelectCtrl_GetVTable(void) {
    union U u;
    int temp_s0;
    igObject *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    q0 = (igObject *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&g_beSelectCtrl_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beSelectCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSelectCtrl_Register);
}

static igMetaObjectCallback g_beSelectCtrl_callbackList[] = { bePadManager_EnsureRegistered, 0 };

void *beSelectCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSelectCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSelectCtrl_GetMetaObjectFunction,
        "beSelectCtrl",
        0x28, /* instance size */
        beSelectCtrl_GetVTable,
        beSelectCtrl_InitFields,
        0, /* extra callback item */
        g_beSelectCtrl_callbackList /* callback list */
    );
}

void beSelectCtrl_GetMetaObjectFunction(void)
{
    beSelectCtrl_GetMetaObject();
}

static FieldFactory g_beSelectCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beSelectCtrl_fieldTable[] = {
    "_padManager",
    "_isEnableCtrl",
};
static igMetaField **g_beSelectCtrl_fieldHandles[] = {
    &g_beSelectCtrl_padManagerMetaField,
    &g_beSelectCtrl_isEnableCtrlMetaField,
};
static int g_beSelectCtrl_fieldOffsets[] = {
    32,
    36,
};

void beSelectCtrl_InitFields(void) {
    int base;
    void *padManager;
    void *meta;

    meta = (void *)g_beSelectCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSelectCtrl_ctorTable, 2);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 1), 1);
    igMetaObject_NameFields(meta, g_beSelectCtrl_fieldTable, g_beSelectCtrl_fieldHandles, g_beSelectCtrl_fieldOffsets, base);
}

