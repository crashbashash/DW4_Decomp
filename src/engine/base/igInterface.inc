igMetaObject *igInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228c60();
    return g_igInterface_metaObject[0];
}

int igInterface_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c670[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00228c60(void)
{
    igMetaObject_RunStaticInit(igInterface_Register);
}

void igInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInterface_metaObject,
        igInterfaced_Register,
        igInterfaced_GetPublishedMetaObject,
        thunk_igInterface_GetMetaObject,
        igInterface_className,
        0x20, /* instance size */
        igInterface_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igInterface_GetMetaObject(void) {
    igInterface_GetMetaObject();
}

