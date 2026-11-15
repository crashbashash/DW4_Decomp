int FUN_0019cba0(int arg0) {
    FUN_0019ccc0();
    return igMetaObject_CreateInstance((int)g_igNodeList_metaObject, arg0);
}

igMetaObject *g_igNodeList_metaObject;

igMetaObject *FUN_0019cbe0(void) {
    if (g_igNodeList_metaObject == 0) {
        g_igNodeList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igNodeList_metaObject;
}

igMetaObject *igNodeList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019ccc0();
    return g_igNodeList_metaObject;
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

static igMetaObjectCallback g_igNodeList_callbackList[] = { FUN_0019cf10, 0 };

void igNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNodeList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNodeList_GetMetaObject,
        "igNodeList",
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

