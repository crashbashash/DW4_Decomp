igMetaObject *g_beCameraMode_metaObject;
igMetaField *g_beCameraMode_cameraPathMetaField;
igMetaField *g_beCameraMode_cameraMetaField;
igMetaField *g_beCameraMode_insightMetaField;
igMetaField *g_beCameraMode_svWorldTimeLMetaField;
igMetaField *g_beCameraMode_nowTimeLMetaField;
igMetaField *g_beCameraMode_timeLengthMetaField;
igMetaField *g_beCameraMode_isEndMetaField;
igMetaField *g_beCameraMode_isFreezeMetaField;

void beCameraMode_Create(int allocator) {
    beCameraMode_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589B90, allocator);
}

igMetaObject *beCameraMode_GetOrCreateMetaObject(void) {
    if (g_beCameraMode_metaObject == 0) {
        g_beCameraMode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCameraMode_metaObject;
}

void *beCameraMode_GetMetaObject(void) {
    igMetaObject *g = g_beCameraMode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCameraMode_EnsureRegistered();
    }
    return g_beCameraMode_metaObject;
}

int beCameraMode_GetVTable(void) {
    struct Obj_368ad0 o;
    int r;
    int *t;

    igObject_InitHeader(&o);
    o.vt = &g_igViewMode_vtable[0];
    igMatrix44f_SetIdentity(o.sub);
    o.vt = &g_beCameraMode_vtable[0];
    o.r1 = 0;
    o.r2 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beCameraMode_vtable[0];
    if (&o.r2 != 0) {
        t = o.r2;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    if (&o.r1 != 0) {
        t = o.r1;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void beCameraMode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraMode_Register);
}

static igMetaObjectCallback g_beCameraMode_callbackList[] = { igGraphPath_EnsureRegistered, igCamera_EnsureRegistered, igInsightCore_EnsureRegistered, 0 };

void *beCameraMode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        beCameraMode_GetMetaObjectFunction,
        "beCameraMode",
        0x78, /* instance size */
        beCameraMode_GetVTable,
        beCameraMode_InitFields,
        0, /* extra callback item */
        g_beCameraMode_callbackList /* callback list */
    );
}

void beCameraMode_GetMetaObjectFunction(void)
{
    beCameraMode_GetMetaObject();
}

int igViewMode_GetPublishedMetaObject(void) {
    return g_igViewMode_metaObject[0];
}

static FieldFactory g_beCameraMode_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beCameraMode_fieldTable[] = {
    "_cameraPath",
    "_camera",
    "_insight",
    "_svWorldTimeL",
    "_nowTimeL",
    "_timeLength",
    "_isEnd",
    "_isFreeze",
};
static igMetaField **g_beCameraMode_fieldHandles[] = {
    &g_beCameraMode_cameraPathMetaField,
    &g_beCameraMode_cameraMetaField,
    &g_beCameraMode_insightMetaField,
    &g_beCameraMode_svWorldTimeLMetaField,
    &g_beCameraMode_nowTimeLMetaField,
    &g_beCameraMode_timeLengthMetaField,
    &g_beCameraMode_isEndMetaField,
    &g_beCameraMode_isFreezeMetaField,
};
static int g_beCameraMode_fieldOffsets[] = {
    76,
    80,
    84,
    88,
    96,
    104,
    112,
    113,
};

void beCameraMode_InitFields(void) {
    int base;
    void *insight;
    void *camera;
    void *cameraPath;
    void *meta;

    meta = (void *)g_beCameraMode_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCameraMode_ctorTable, 8);
    cameraPath = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)cameraPath)->_metaObject = igGraphPath_GetOrCreateMetaObject();
    camera = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)camera)->_metaObject = igCamera_GetOrCreateMetaObject();
    insight = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)insight)->_metaObject = igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insight)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beCameraMode_fieldTable, g_beCameraMode_fieldHandles, g_beCameraMode_fieldOffsets, base);
}

