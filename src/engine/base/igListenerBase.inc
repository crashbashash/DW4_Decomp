igMetaObject *igListenerBase_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002272f0();
    return g_igListenerBase_metaObject[0];
}

int igListenerBase_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c7b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_002272f0(void)
{
    igMetaObject_RunStaticInit(igListenerBase_Register);
}

void igListenerBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igListenerBase_GetMetaObject,
        igListenerBase_className,
        0x20, /* instance size */
        igListenerBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igListenerBase_GetMetaObject(void) {
    igListenerBase_GetMetaObject();
}

