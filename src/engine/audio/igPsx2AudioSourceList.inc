void *FUN_001435c0(int arg0) {
    FUN_00143690();
    return (void *)igMetaObject_CreateInstance(*(int *)0x55F5A8, arg0);
}

igMetaObject *igPsx2AudioSourceList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2AudioSourceList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143690();
    return g_igPsx2AudioSourceList_metaObject[0];
}

int igPsx2AudioSourceList_GetVTable(void) {
    struct SourceListProbe obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524b80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00143690(void)
{
    igMetaObject_RunStaticInit(igPsx2AudioSourceList_Register);
}

void igPsx2AudioSourceList_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2AudioSourceList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPsx2AudioSourceList_GetMetaObject,
        igPsx2AudioSourceList_className,
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

int igDataList_GetPublishedMetaObject(void){return g_igDataList_metaObject[0];}

