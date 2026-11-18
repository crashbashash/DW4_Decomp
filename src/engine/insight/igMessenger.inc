igMetaObject *g_igMessenger_metaObject;
igMetaField *g_igMessenger_dispatcherMetaField;

igMetaObject *igMessenger_GetOrCreateMetaObject(void) {
    if (g_igMessenger_metaObject == 0) {
        g_igMessenger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessenger_metaObject;
}

igMetaObject *igMessenger_GetMetaObject(void)
{
    igMetaObject *g = g_igMessenger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessenger_EnsureRegistered();
    return g_igMessenger_metaObject;
}

int igMessenger_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;
    igObject_InitHeader((igObject *)&o);
    o.vt = g_igMessenger_vtable;
    o.ref = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = g_igMessenger_vtable;
    if (&o.ref != 0) {
        p = o.ref;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
    }
    return r;
}

void igMessenger_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessenger_Register);
}

static igMetaObjectCallback g_igMessenger_callbackList[] = { igMessageDispatcher_EnsureRegistered, 0 };

CallbackArray *igMessenger_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessenger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMessenger_GetMetaObjectFunction,
        "igMessenger",
        0xC, /* instance size */
        igMessenger_GetVTable,
        &igMessenger_InitFields,
        0, /* extra callback item */
        g_igMessenger_callbackList /* callback list */
    );
}

void igMessenger_GetMetaObjectFunction(void) {
    igMessenger_GetMetaObject();
}

static FieldFactory g_igMessenger_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igMessenger_fieldTable[] = {
    "_dispatcher",
};
static igMetaField **g_igMessenger_fieldHandles[] = {
    &g_igMessenger_dispatcherMetaField,
};
static int g_igMessenger_fieldOffsets[] = {
    8,
};

void igMessenger_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igMessenger_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igMessenger_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igMessageDispatcher_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igMessenger_fieldTable, g_igMessenger_fieldHandles, g_igMessenger_fieldOffsets, temp_s2);
}

