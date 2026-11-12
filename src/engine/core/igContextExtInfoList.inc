void * FUN_002cb4b0(int arg0) {
    FUN_002cb5d0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5868C0), (MemoryPool *)arg0));
}

igMetaObject *FUN_002cb4f0(void) {
    if (g_igContextExtInfoList_metaObject[0] == 0) {
        g_igContextExtInfoList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igContextExtInfoList_metaObject[0];
}

igMetaObject *igContextExtInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb5d0();
    return g_igContextExtInfoList_metaObject[0];
}

int igContextExtInfoList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((ObjectHeader *)&tmp[0]);
    tmp[0] = (int)&DAT_00531910[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_002cb5d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtInfoList_Register);
}

void igContextExtInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igContextExtInfoList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igContextExtInfoList_GetMetaObject,
        igContextExtInfoList_className,
        0x14, /* instance size */
        igContextExtInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextExtInfoList_callbackList /* callback list */
    );
}

void thunk_igContextExtInfoList_GetMetaObject(void) {
    igContextExtInfoList_GetMetaObject();
}

