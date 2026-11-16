igMetaObject *g_igListenerList_metaObject;

igMetaObject *igListenerList_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002271d0();
    return g_igListenerList_metaObject;
}

int igListenerList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igListenerList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_002271d0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igListenerList_Register);
}

static igMetaObjectCallback g_igListenerList_callbackList[] = { FUN_002272f0, 0 };

CallbackArray *igListenerList_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igListenerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igListenerList_GetMetaObject,
        "igListenerList",
        0x14, /* instance size */
        igListenerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igListenerList_callbackList /* callback list */
    );
}

void thunk_igListenerList_GetMetaObject(void) {
    igListenerList_GetMetaObject();
}

