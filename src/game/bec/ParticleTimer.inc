igMetaObject *g_ParticleTimer_metaObject;
igMetaField *g_ParticleTimer_timeRunningMetaField;
igMetaField *g_ParticleTimer_timeBiasMetaField;
igMetaField *g_ParticleTimer_timeMetaField;

igMetaObject *ParticleTimer_GetOrCreateMetaObject(void) {
    if (g_ParticleTimer_metaObject == 0) {
        g_ParticleTimer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_ParticleTimer_metaObject;
}

igMetaObject *ParticleTimer_GetMetaObject(void)
{
    igMetaObject *g = g_ParticleTimer_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        ParticleTimer_EnsureRegistered();
    return g_ParticleTimer_metaObject;
}

int ParticleTimer_GetVTable(void) {
    struct Obj_36e660 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    obj.vt = &g_ParticleTimer_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_ParticleTimer_vtable[0];
    FUN_0019d120(&obj, 0);
    return t;
}

void ParticleTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(ParticleTimer_Register);
}

void *ParticleTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_ParticleTimer_metaObject,
        igGeometry_Register,
        igGeometry_GetPublishedMetaObject,
        ParticleTimer_GetMetaObjectFunction,
        "ParticleTimer",
        0x40, /* instance size */
        ParticleTimer_GetVTable,
        ParticleTimer_InitFields,
        FUN_0036e860, /* extra callback item */
        0 /* callback list */
    );
}

void ParticleTimer_GetMetaObjectFunction(void)
{
    ParticleTimer_GetMetaObject();
}

static FieldFactory g_ParticleTimer_ctorTable[] = {
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_ParticleTimer_fieldTable[] = {
    "_timeRunning",
    "_timeBias",
    "_time",
};
static igMetaField **g_ParticleTimer_fieldHandles[] = {
    &g_ParticleTimer_timeRunningMetaField,
    &g_ParticleTimer_timeBiasMetaField,
    &g_ParticleTimer_timeMetaField,
};
static int g_ParticleTimer_fieldOffsets[] = {
    44,
    48,
    56,
};

void ParticleTimer_InitFields(void) {
    int base;
    void *time;
    void *timeBias;
    void *meta;

    meta = (void *)g_ParticleTimer_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_ParticleTimer_ctorTable, 3);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base), 1);
    timeBias = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    igLongMetaField_SetDefault(timeBias, 0);
    ((igLongMetaField *)timeBias)->_persistent = 0;
    time = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    igLongMetaField_SetDefault(time, 0);
    ((igLongMetaField *)time)->_persistent = 0;
    igMetaObject_NameFields(meta, g_ParticleTimer_fieldTable, g_ParticleTimer_fieldHandles, g_ParticleTimer_fieldOffsets, base);
}

void FUN_0036e860(void)
{
    FUN_003a3900();
}

