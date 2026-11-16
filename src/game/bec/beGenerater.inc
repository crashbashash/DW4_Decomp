igMetaObject *g_beGenerater_metaObject;
igMetaField *g_beGenerater_luaManagerMetaField;
igMetaField *g_beGenerater_isPerfectDropMetaField;

void beGenerater_CreateInstance(int arg0) {
    beGenerater_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5895D0, arg0);
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
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&g_beGenerater_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beGenerater_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beGenerater_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beGenerater_fieldTable, g_beGenerater_fieldHandles, g_beGenerater_fieldOffsets, temp_s2);
}

