igMetaObject *g_beWaterMove_metaObject;
igMetaField *g_beWaterMove_baseTimeMetaField;
igMetaField *g_beWaterMove_elapseTimeMetaField;
igMetaField *g_beWaterMove_maxTimeMetaField;
igMetaField *g_beWaterMove_targetDataMetaField;
igMetaField *g_beWaterMove_dataListMetaField;

igMetaObject *beWaterMove_GetOrCreateMetaObject(void) {
    if (g_beWaterMove_metaObject == 0) {
        g_beWaterMove_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWaterMove_metaObject;
}

void *beWaterMove_GetMetaObject(void) {
    igMetaObject *g = g_beWaterMove_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWaterMove_EnsureRegistered();
    }
    return g_beWaterMove_metaObject;
}

int beWaterMove_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;

    igObject_InitHeader(&o);
    o.vt = g_beWaterMove_vtable;
    *(int *)((char *)&o + 36) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beWaterMove_vtable;
    if (&*(int *)((char *)&o + 36) != 0) { p = *(struct Ref **)((char *)&o + 36); if (p != 0) { p->u.w = p->u.w - 1; if (p->u.b.cnt == 0) igObject_Destroy(p); } }
    return r;
}

void beWaterMove_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterMove_Register);
}

static igMetaObjectCallback g_beWaterMove_callbackList[] = { beWaterMoveDataList_EnsureRegistered, 0 };

void *beWaterMove_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterMove_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMove_GetMetaObjectFunction,
        "beWaterMove",
        0x28, /* instance size */
        beWaterMove_GetVTable,
        beWaterMove_InitFields,
        0, /* extra callback item */
        g_beWaterMove_callbackList /* callback list */
    );
}

void beWaterMove_GetMetaObjectFunction(void)
{
    beWaterMove_GetMetaObject();
}

static FieldFactory g_beWaterMove_ctorTable[] = {
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWaterMove_fieldTable[] = {
    "_baseTime",
    "_elapseTime",
    "_maxTime",
    "_targetData",
    "_dataList",
};
static igMetaField **g_beWaterMove_fieldHandles[] = {
    &g_beWaterMove_baseTimeMetaField,
    &g_beWaterMove_elapseTimeMetaField,
    &g_beWaterMove_maxTimeMetaField,
    &g_beWaterMove_targetDataMetaField,
    &g_beWaterMove_dataListMetaField,
};
static int g_beWaterMove_fieldOffsets[] = {
    8,
    16,
    24,
    32,
    36,
};

void beWaterMove_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWaterMove_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beWaterMove_ctorTable, 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beWaterMoveDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beWaterMove_fieldTable, g_beWaterMove_fieldHandles, g_beWaterMove_fieldOffsets, temp_s2);
}

