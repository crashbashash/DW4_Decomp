igMetaObject *g_beTimer_metaObject;
igMetaField *g_beTimer_systemMetaField;
igMetaField *g_beTimer_padManagerMetaField;
igMetaField *g_beTimer_luaManagerMetaField;
igMetaField *g_beTimer_dataListMetaField;
igMetaField *g_beTimer_oldWorldTimeMetaField;

void beTimer_CreateInstance(int arg0) {
    beTimer_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587C18, arg0);
}

igMetaObject *beTimer_GetOrCreateMetaObject(void) {
    if (g_beTimer_metaObject == 0) {
        g_beTimer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beTimer_metaObject;
}

void *beTimer_GetMetaObject(void) {
    igMetaObject *g = g_beTimer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTimer_EnsureRegistered();
    }
    return g_beTimer_metaObject;
}

int beTimer_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beTimer_vtable[0];
    q0 = (S_ref *)&u.b[28];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beTimer_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
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

void beTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTimer_Register);
}

static igMetaObjectCallback g_beTimer_callbackList[] = { beSystem_EnsureRegistered, bePadManager_EnsureRegistered, beLua_EnsureRegistered, beTimerDataList_EnsureRegistered, 0 };

void *beTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTimer_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTimer_GetMetaObjectFunction,
        "beTimer",
        0x28, /* instance size */
        beTimer_GetVTable,
        beTimer_InitFields,
        0, /* extra callback item */
        g_beTimer_callbackList /* callback list */
    );
}

void beTimer_GetMetaObjectFunction(void)
{
    beTimer_GetMetaObject();
}

static FieldFactory g_beTimer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beTimer_fieldTable[] = {
    "_system",
    "_padManager",
    "_luaManager",
    "_dataList",
    "_oldWorldTime",
};
static igMetaField **g_beTimer_fieldHandles[] = {
    &g_beTimer_systemMetaField,
    &g_beTimer_padManagerMetaField,
    &g_beTimer_luaManagerMetaField,
    &g_beTimer_dataListMetaField,
    &g_beTimer_oldWorldTimeMetaField,
};
static int g_beTimer_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
};

void beTimer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTimer_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beTimer_ctorTable, 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)beTimerDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beTimer_fieldTable, g_beTimer_fieldHandles, g_beTimer_fieldOffsets, temp_s2);
}

