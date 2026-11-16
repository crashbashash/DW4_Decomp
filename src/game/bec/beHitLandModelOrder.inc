igMetaObject *g_beHitLandModelOrder_metaObject;
igMetaField *g_beHitLandModelOrder_infoNameMetaField;
igMetaField *g_beHitLandModelOrder_ramNoMetaField;
igMetaField *g_beHitLandModelOrder_kindMetaField;
igMetaField *g_beHitLandModelOrder_raymaxMetaField;
igMetaField *g_beHitLandModelOrder_rayminMetaField;
igMetaField *g_beHitLandModelOrder_rayCountMetaField;
igMetaField *g_beHitLandModelOrder_rayListMetaField;
igMetaField *g_beHitLandModelOrder_hitdataCountMetaField;
igMetaField *g_beHitLandModelOrder_hitdataListMetaField;

void beHitLandModelOrder_Create(int allocator) {
    beHitLandModelOrder_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589390, allocator);
}

igMetaObject *beHitLandModelOrder_GetOrCreateMetaObject(void) {
    if (g_beHitLandModelOrder_metaObject == 0) {
        g_beHitLandModelOrder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandModelOrder_metaObject;
}

void *beHitLandModelOrder_GetMetaObject(void) {
    bool ok;
    if (g_beHitLandModelOrder_metaObject == 0) goto make;
    ok = !!(g_beHitLandModelOrder_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beHitLandModelOrder_EnsureRegistered();
done:;
    return g_beHitLandModelOrder_metaObject;
}

int beHitLandModelOrder_GetVTable(void) {
    union U_35df70 u;
    int temp_s0;
    igObject *q0;
    igObject *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beHitLandModelOrder_vtable[0];
    q2 = &u.b[32];
    *(int *)q2 = 0;
    q1 = (igObject *)&u.b[48];
    *(int *)q1 = 0;
    q0 = (igObject *)&u.b[56];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beHitLandModelOrder_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
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

void beHitLandModelOrder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModelOrder_Register);
}

static igMetaObjectCallback g_beHitLandModelOrder_callbackList[] = { igRayList_EnsureRegistered, beHitLandResultDataList_EnsureRegistered, 0 };

void *beHitLandModelOrder_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModelOrder_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandModelOrder_GetMetaObjectFunction,
        "beHitLandModelOrder",
        0x3c, /* instance size */
        beHitLandModelOrder_GetVTable,
        beHitLandModelOrder_InitFields,
        0, /* extra callback item */
        g_beHitLandModelOrder_callbackList /* callback list */
    );
}

void beHitLandModelOrder_GetMetaObjectFunction(void)
{
    beHitLandModelOrder_GetMetaObject();
}

static FieldFactory g_beHitLandModelOrder_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beHitLandModelOrder_fieldTable[] = {
    "_infoName",
    "_ramNo",
    "_kind",
    "_raymax",
    "_raymin",
    "_rayCount",
    "_rayList",
    "_hitdataCount",
    "_hitdataList",
};
static igMetaField **g_beHitLandModelOrder_fieldHandles[] = {
    &g_beHitLandModelOrder_infoNameMetaField,
    &g_beHitLandModelOrder_ramNoMetaField,
    &g_beHitLandModelOrder_kindMetaField,
    &g_beHitLandModelOrder_raymaxMetaField,
    &g_beHitLandModelOrder_rayminMetaField,
    &g_beHitLandModelOrder_rayCountMetaField,
    &g_beHitLandModelOrder_rayListMetaField,
    &g_beHitLandModelOrder_hitdataCountMetaField,
    &g_beHitLandModelOrder_hitdataListMetaField,
};
static int g_beHitLandModelOrder_fieldOffsets[] = {
    32,
    36,
    40,
    8,
    20,
    44,
    48,
    52,
    56,
};

void beHitLandModelOrder_InitFields(void) {
    void *raymax;
    void *raymin;
    void *rayList;
    int base;
    void *hitdataList;
    void *meta;
    int rayMaxDefault[3];
    int rayMinDefault[3];

    meta = (void *)g_beHitLandModelOrder_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandModelOrder_ctorTable, 9);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), "");
    raymax = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    rayMaxDefault[0] = 0;
    rayMaxDefault[1] = 0;
    rayMaxDefault[2] = 0;
    FUN_0018e470(raymax, rayMaxDefault);
    raymin = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    rayMinDefault[0] = 0;
    rayMinDefault[1] = 0;
    rayMinDefault[2] = 0;
    FUN_0018e470(raymin, rayMinDefault);
    rayList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)rayList)->_metaObject = igRayList_GetOrCreateMetaObject();
    ((igRefMetaField *)rayList)->_construct = 1;
    hitdataList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)hitdataList)->_metaObject = (int)beHitLandResultDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)hitdataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beHitLandModelOrder_fieldTable, g_beHitLandModelOrder_fieldHandles, g_beHitLandModelOrder_fieldOffsets, base);
}

