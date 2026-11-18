igMetaObject *g_igFilterMessageDispatcher_metaObject;
igMetaField *g_igFilterMessageDispatcher_defaultFiltersMetaField;
igMetaField *g_igFilterMessageDispatcher_filtersMetaField;

igMetaObject *igFilterMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igFilterMessageDispatcher_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231f40();
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
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._defaultFilters != 0) {
        o = (igObject *)obj._defaultFilters;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_00231f40(void)
{
    igMetaObject_RunStaticInit(igFilterMessageDispatcher_Register);
}

static igMetaObjectCallback g_igFilterMessageDispatcher_callbackList[] = { FUN_00231ab0, 0 };

CallbackArray *igFilterMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFilterMessageDispatcher_metaObject,
        igMessageDispatcher_Register,
        igMessageDispatcher_GetPublishedMetaObject,
        thunk_igFilterMessageDispatcher_GetMetaObject,
        "igFilterMessageDispatcher",
        0x10, /* instance size */
        igFilterMessageDispatcher_GetVTable,
        &igFilterMessageDispatcher_InitFields,
        0, /* extra callback item */
        g_igFilterMessageDispatcher_callbackList /* callback list */
    );
}

void thunk_igFilterMessageDispatcher_GetMetaObject(void) {
    igFilterMessageDispatcher_GetMetaObject();
}

igMetaObject *FUN_00231fe0(void) {
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
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002319d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002319d0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igFilterMessageDispatcher_fieldTable, g_igFilterMessageDispatcher_fieldHandles, g_igFilterMessageDispatcher_fieldOffsets, temp_s2);
}

