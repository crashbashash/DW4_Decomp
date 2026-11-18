igMetaObject *g_igPsx2AudioSourceList_metaObject;

void *igPsx2AudioSourceList_Create(igMemoryPoolView *pool) {
    igPsx2AudioSourceList_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igPsx2AudioSourceList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igPsx2AudioSourceList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2AudioSourceList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2AudioSourceList_EnsureRegistered();
    return g_igPsx2AudioSourceList_metaObject;
}

int igPsx2AudioSourceList_GetVTable(void) {
    struct SourceListProbe obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPsx2AudioSourceList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igPsx2AudioSourceList_EnsureRegistered(void)
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
        igPsx2AudioSourceList_GetMetaObjectFunction,
        "igPsx2AudioSourceList",
        0x14, /* instance size */
        igPsx2AudioSourceList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igPsx2AudioSourceList_GetMetaObjectFunction(void) {
    igPsx2AudioSourceList_GetMetaObject();
}

igMetaObject *igDataList_GetPublishedMetaObject(void){return g_igDataList_metaObject;}

