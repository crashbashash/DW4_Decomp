igMetaObject *g_igPsx2AudioSourceList_metaObject;

void *FUN_001435c0(igMemoryPoolView *pool) {
    FUN_00143690();
    return (void *)igMetaObject_CreateInstance(g_igPsx2AudioSourceList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igPsx2AudioSourceList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2AudioSourceList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143690();
    return g_igPsx2AudioSourceList_metaObject;
}

int igPsx2AudioSourceList_GetVTable(void) {
    struct SourceListProbe obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPsx2AudioSourceList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00143690(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioSourceList_Register);
}

CallbackArray *igPsx2AudioSourceList_Register(void) {
    AudioLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2AudioSourceList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPsx2AudioSourceList_GetMetaObject,
        "igPsx2AudioSourceList",
        0x14, /* instance size */
        igPsx2AudioSourceList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPsx2AudioSourceList_GetMetaObject(void) {
    igPsx2AudioSourceList_GetMetaObject();
}

igMetaObject *igDataList_GetPublishedMetaObject(void){return g_igDataList_metaObject;}

