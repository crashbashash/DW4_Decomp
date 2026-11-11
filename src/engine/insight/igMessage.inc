igMetaObject *igMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igMessage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231700();
    return g_igMessage_metaObject[0];
}

int igMessage_GetVTable(void) {
    struct Obj_2316c0 o; igObject_InitHeader(&o);
    o.vt = &DAT_0052d000[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00231700(void)
{
    igMetaObject_RunStaticInit(igMessage_Register);
}

void igMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessage_GetMetaObject,
        igMessage_className,
        8, /* instance size */
        igMessage_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessage_GetMetaObject(void) {
    igMessage_GetMetaObject();
}

