igMetaObject *igListenerList_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002271d0();
    return g_igListenerList_metaObject[0];
}

int igListenerList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c4c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_002271d0(void)
{
    igMetaObject_RunStaticInit(igListenerList_Register);
}

void igListenerList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igListenerList_GetMetaObject,
        igListenerList_className,
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

