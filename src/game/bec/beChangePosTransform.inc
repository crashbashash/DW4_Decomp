igMetaObject *g_beChangePosTransform_metaObject;
igMetaField *g_beChangePosTransform_oldPosMetaField;

void beChangePosTransform_CreateInstance(int allocator) {
    beChangePosTransform_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589B80, allocator);
}

igMetaObject *beChangePosTransform_GetOrCreateMetaObject(void) {
    if (g_beChangePosTransform_metaObject == 0) {
        g_beChangePosTransform_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beChangePosTransform_metaObject;
}

igMetaObject *beChangePosTransform_GetMetaObject(void) {
    if (g_beChangePosTransform_metaObject == 0 || !isValid(g_beChangePosTransform_metaObject)) beChangePosTransform_EnsureRegistered();
    return g_beChangePosTransform_metaObject;
}

int beChangePosTransform_GetVTable(void) {
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
    u.vt = (int)&g_beChangePosTransform_vtable[0];
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

void beChangePosTransform_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beChangePosTransform_Register);
}

void *beChangePosTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beChangePosTransform_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beChangePosTransform_GetMetaObjectFunction,
        "beChangePosTransform",
        0x2c, /* instance size */
        beChangePosTransform_GetVTable,
        beChangePosTransform_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beChangePosTransform_GetMetaObjectFunction(void)
{
    beChangePosTransform_GetMetaObject();
}

static FieldFactory g_beChangePosTransform_ctorTable[] = {
    FUN_00187890,
};
static const char *g_beChangePosTransform_fieldTable[] = {
    "_oldPos",
};
static igMetaField **g_beChangePosTransform_fieldHandles[] = {
    &g_beChangePosTransform_oldPosMetaField,
};
static int g_beChangePosTransform_fieldOffsets[] = {
    32,
};

void beChangePosTransform_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beChangePosTransform_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beChangePosTransform_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beChangePosTransform_fieldTable, g_beChangePosTransform_fieldHandles, g_beChangePosTransform_fieldOffsets, base);
}

