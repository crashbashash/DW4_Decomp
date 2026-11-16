igMetaObject *g_beCameraMode_metaObject;
igMetaField *g_beCameraMode_cameraPathMetaField;
igMetaField *g_beCameraMode_cameraMetaField;
igMetaField *g_beCameraMode_insightMetaField;
igMetaField *g_beCameraMode_svWorldTimeLMetaField;
igMetaField *g_beCameraMode_nowTimeLMetaField;
igMetaField *g_beCameraMode_timeLengthMetaField;
igMetaField *g_beCameraMode_isEndMetaField;
igMetaField *g_beCameraMode_isFreezeMetaField;

void beCameraMode_Create(int arg0) {
    beCameraMode_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589B90, arg0);
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
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCameraMode_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCameraMode_ctorTable, 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igGraphPath_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igCamera_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beCameraMode_fieldTable, g_beCameraMode_fieldHandles, g_beCameraMode_fieldOffsets, temp_s2);
}

