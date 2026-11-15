igMetaObject *g_igVertexDataList_metaObject;

int FUN_0014b180(int arg0) {
    FUN_0014b2a0();
    return igMetaObject_CreateInstance(g_igVertexDataList_metaObject, arg0);
}

igMetaObject *FUN_0014b1c0(void) {
    if (g_igVertexDataList_metaObject == 0) {
        g_igVertexDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igVertexDataList_metaObject;
}

igMetaObject *igVertexDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014b2a0();
    return g_igVertexDataList_metaObject;
}

int igVertexDataList_GetVTable(void) {
    union U_14b260 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00527100[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_0014b2a0(void)
{
    igMetaObject_RunStaticInit(igVertexDataList_Register);
}

static igMetaObjectCallback g_igVertexDataList_callbackList[] = { FUN_0014b500, 0 };

void igVertexDataList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igVertexDataList_GetMetaObject,
        "igVertexDataList",
        0x14, /* instance size */
        igVertexDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexDataList_callbackList /* callback list */
    );
}

void thunk_igVertexDataList_GetMetaObject(void) {
    igVertexDataList_GetMetaObject();
}

