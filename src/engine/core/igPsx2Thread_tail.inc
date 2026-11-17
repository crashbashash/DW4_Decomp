igMetaObject *g_igPsx2Thread_metaObject;
igMetaField *g_igPsx2Thread_threadIDField;
igMetaField *g_igPsx2Thread_threadDoneSemaMetaField;
igMetaField *g_igPsx2Thread_resultMetaField;
igMetaField *g_igPsx2Thread_isDeferredMetaField;
igMetaField *g_igPsx2Thread_stopRequestedMetaField;
igMetaField *g_igPsx2Thread_atStoppingPointMetaField;

igMetaObject *igPsx2Thread_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Thread_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Thread_EnsureRegistered();
    return g_igPsx2Thread_metaObject;
}

int igPsx2Thread_GetVTable(void) {
    igPsx2Thread thread;
    int t;
    char *o;
    int *a1;
    int v0;
    igObject *p0, *p1;
    igObject_InitHeader((igObject *)&thread);
    p0 = (igObject *)&thread._name;
    *(int *)p0 = 0;
    thread._vtable = (int)&g_igPsx2Thread_vtable[0];
    p1 = (igObject *)&thread._threadDoneSema;
    *(int *)p1 = 0;
    t = *(int *)((char *)&thread + g_objectSystem->vtableProbeOffset);
    thread._vtable = (int)&g_igPsx2Thread_vtable[0];
    if (p1 != 0) {
        p1 = *(igObject **)p1;
        if (p1 != 0) {
            p1->_refCount = (int)((int) (p1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) p1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    thread._vtable = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igPsx2Thread_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2Thread_Register);
}

static igMetaObjectCallback g_igPsx2Thread_callbackList[] = { igSemaphore_EnsureRegistered, 0 };

CallbackArray *igPsx2Thread_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPsx2Thread_metaObject,
        igThread_Register,
        igThread_GetPublishedMetaObject,
        igPsx2Thread_GetMetaObjectFunction,
        "igPsx2Thread",
        0x40,
        igPsx2Thread_GetVTable,
        igPsx2Thread_InitFields,
        0,
        g_igPsx2Thread_callbackList
    );
}

igMetaObject *igThread_GetPublishedMetaObject(void) {
    return g_igThread_metaObject;
}

static FieldFactory g_igPsx2Thread_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igPsx2Thread_fieldTable[] = {
    "_threadID",
    "_threadDoneSema",
    "_result",
    "_isDeferred",
    "_stopRequested",
    "_atStoppingPoint",
};
static igMetaField **g_igPsx2Thread_fieldDescriptors[] = {
    &g_igPsx2Thread_threadIDField,
    &g_igPsx2Thread_threadDoneSemaMetaField,
    &g_igPsx2Thread_resultMetaField,
    &g_igPsx2Thread_isDeferredMetaField,
    &g_igPsx2Thread_stopRequestedMetaField,
    &g_igPsx2Thread_atStoppingPointMetaField,
};
static int g_igPsx2Thread_fieldOffsets[] = {
    60,
    48,
    52,
    56,
    57,
    58,
};

void igPsx2Thread_InitFields(void) {
    int base;
    igObjectRefMetaField *field;
    void *meta;

    meta = (void *)(g_igPsx2Thread_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPsx2Thread_ctorTable, 6);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), -1);
    field = (igObjectRefMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    field->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    field->_construct = 1;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igPsx2Thread_fieldTable, g_igPsx2Thread_fieldDescriptors, g_igPsx2Thread_fieldOffsets, base);
    *(int *)((char *)(g_igPsx2Thread_metaObject) + 64) = (int)(&igThread_GetMetaObjectFunction);
}

