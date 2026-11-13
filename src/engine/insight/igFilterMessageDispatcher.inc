igMetaObject *igFilterMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igFilterMessageDispatcher_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231f40();
    return g_igFilterMessageDispatcher_metaObject[0];
}

int igFilterMessageDispatcher_GetVTable(void) {
    igFilterMessageDispatcher obj;
    igObject *o;
    int t;
    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0052c8b0[0];
    obj._defaultFilters = 0;
    obj._filters = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &DAT_0052c8b0[0];
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

void igFilterMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFilterMessageDispatcher_metaObject,
        igMessageDispatcher_Register,
        igMessageDispatcher_GetPublishedMetaObject,
        thunk_igFilterMessageDispatcher_GetMetaObject,
        igFilterMessageDispatcher_className,
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
    return g_igMessageDispatcher_metaObject[0];
}

void igFilterMessageDispatcher_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFilterMessageDispatcher_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igFilterMessageDispatcher_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002319d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002319d0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igFilterMessageDispatcher_fieldTable[0], &DAT_00498030[0], &DAT_00498038[0], temp_s2);
}

