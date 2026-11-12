int FUN_0019cba0(int arg0) {
    FUN_0019ccc0();
    return igMetaObject_CreateInstance(*(int *)0x561830, arg0);
}

igMetaObject *FUN_0019cbe0(void) {
    if (g_igNodeList_metaObject[0] == 0) {
        g_igNodeList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igNodeList_metaObject[0];
}

igMetaObject *igNodeList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019ccc0();
    return g_igNodeList_metaObject[0];
}

int igNodeList_GetVTable(void) {
    struct Obj_19cc80 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ab20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0019ccc0(void)
{
    igMetaObject_RunStaticInit(igNodeList_Register);
}

void igNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNodeList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNodeList_GetMetaObject,
        igNodeList_className,
        0x14, /* instance size */
        igNodeList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNodeList_callbackList /* callback list */
    );
}

void thunk_igNodeList_GetMetaObject(void) {
    igNodeList_GetMetaObject();
}

