igMetaObject *g_igFilterMessageDispatcher_metaObject;
igMetaField *g_igFilterMessageDispatcher_defaultFiltersMetaField;
igMetaField *g_igFilterMessageDispatcher_filtersMetaField;

igMetaObject *igFilterMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igFilterMessageDispatcher_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFilterMessageDispatcher_EnsureRegistered();
    return g_igFilterMessageDispatcher_metaObject;
}

int igFilterMessageDispatcher_GetVTable(void) {
    igFilterMessageDispatcher obj;
    igObject *o;
    int t;
    igObject_InitHeader((igObject *)&obj);
    *(int **)&obj._vtable = &g_igFilterMessageDispatcher_vtable[0];
    obj._defaultFilters = 0;
    obj._filters = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igFilterMessageDispatcher_vtable[0];
    if (&obj._filters != 0) {
        o = (igObject *)obj._filters;
        igObject::release(o);
    }
    if (&obj._defaultFilters != 0) {
        o = (igObject *)obj._defaultFilters;
        igObject::release(o);
    }
    return t;
}

void igFilterMessageDispatcher_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFilterMessageDispatcher_Register);
}

static igMetaObjectCallback g_igFilterMessageDispatcher_callbackList[] = { igMessageFilterList_EnsureRegistered, 0 };

CallbackArray *igFilterMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFilterMessageDispatcher_metaObject,
        igMessageDispatcher_Register,
        igMessageDispatcher_GetPublishedMetaObject,
        igFilterMessageDispatcher_GetMetaObjectFunction,
        "igFilterMessageDispatcher",
        0x10, /* instance size */
        igFilterMessageDispatcher_GetVTable,
        &igFilterMessageDispatcher_InitFields,
        0, /* extra callback item */
        g_igFilterMessageDispatcher_callbackList /* callback list */
    );
}

void igFilterMessageDispatcher_GetMetaObjectFunction(void) {
    igFilterMessageDispatcher_GetMetaObject();
}

igMetaObject *igMessageDispatcher_GetPublishedMetaObject(void) {
    return g_igMessageDispatcher_metaObject;
}

static FieldFactory g_igFilterMessageDispatcher_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igFilterMessageDispatcher_fieldTable[] = {
    "_defaultFilters",
    "_filters",
};
static igMetaField **g_igFilterMessageDispatcher_fieldHandles[] = {
    &g_igFilterMessageDispatcher_defaultFiltersMetaField,
    &g_igFilterMessageDispatcher_filtersMetaField,
};
static int g_igFilterMessageDispatcher_fieldOffsets[] = {
    8,
    12,
};

void igFilterMessageDispatcher_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igFilterMessageDispatcher_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igFilterMessageDispatcher_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igMessageFilterList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igMessageFilterList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igFilterMessageDispatcher_fieldTable, g_igFilterMessageDispatcher_fieldHandles, g_igFilterMessageDispatcher_fieldOffsets, temp_s2);
}

