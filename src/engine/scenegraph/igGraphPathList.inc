int FUN_0019f480(int arg0) {
    FUN_0019f5a0();
    return igMetaObject_CreateInstance(*(int *)0x561A08, arg0);
}

igMetaObject *FUN_0019f4c0(void) {
    if (g_igGraphPathList_metaObject[0] == 0) {
        g_igGraphPathList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGraphPathList_metaObject[0];
}

igMetaObject *igGraphPathList_GetMetaObject(void)
{
    igMetaObject *g = g_igGraphPathList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f5a0();
    return g_igGraphPathList_metaObject[0];
}

int igGraphPathList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_0052a870[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_0019f5a0(void)
{
    igMetaObject_RunStaticInit(igGraphPathList_Register);
}

void igGraphPathList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igGraphPathList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGraphPathList_GetMetaObject,
        igGraphPathList_className,
        0x14, /* instance size */
        igGraphPathList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGraphPathList_callbackList /* callback list */
    );
}

void thunk_igGraphPathList_GetMetaObject(void) {
    igGraphPathList_GetMetaObject();
}

