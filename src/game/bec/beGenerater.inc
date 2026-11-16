igMetaObject *g_beGenerater_metaObject;
igMetaField *g_beGenerater_luaManagerMetaField;
igMetaField *g_beGenerater_isPerfectDropMetaField;

void beGenerater_CreateInstance(int allocator) {
    beGenerater_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5895D0, allocator);
}

igMetaObject *beGenerater_GetOrCreateMetaObject(void) {
    if (g_beGenerater_metaObject == 0) {
        g_beGenerater_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGenerater_metaObject;
}

void *beGenerater_GetMetaObject(void) {
    igMetaObject *g = g_beGenerater_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGenerater_EnsureRegistered();
    }
    return g_beGenerater_metaObject;
}

int beGenerater_GetVTable(void) {
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
    u.vt = (int)&g_beGenerater_vtable[0];
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

void beGenerater_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGenerater_Register);
}

static igMetaObjectCallback g_beGenerater_callbackList[] = { beLua_EnsureRegistered, 0 };

void *beGenerater_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGenerater_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beGenerater_GetMetaObjectFunction,
        "beGenerater",
        0x28, /* instance size */
        beGenerater_GetVTable,
        beGenerater_InitFields,
        0, /* extra callback item */
        g_beGenerater_callbackList /* callback list */
    );
}

void beGenerater_GetMetaObjectFunction(void)
{
    beGenerater_GetMetaObject();
}

static FieldFactory g_beGenerater_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beGenerater_fieldTable[] = {
    "_luaManager",
    "_isPerfectDrop",
};
static igMetaField **g_beGenerater_fieldHandles[] = {
    &g_beGenerater_luaManagerMetaField,
    &g_beGenerater_isPerfectDropMetaField,
};
static int g_beGenerater_fieldOffsets[] = {
    32,
    36,
};

void beGenerater_InitFields(void) {
    int base;
    void *luaManager;
    void *meta;

    meta = (void *)g_beGenerater_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGenerater_ctorTable, 2);
    luaManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)luaManager)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)luaManager)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beGenerater_fieldTable, g_beGenerater_fieldHandles, g_beGenerater_fieldOffsets, base);
}

