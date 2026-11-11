int FUN_0014b180(int arg0) {
    FUN_0014b2a0();
    return igMetaObject_CreateInstance(*(int *)0x55FA48, arg0);
}

int FUN_0014b1c0(void) {
    if (DAT_0055fa48[0] == 0) {
        DAT_0055fa48[0] = (int)igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055fa48[0];
}

igMetaObject *igVertexDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014b2a0();
    return g_igVertexDataList_metaObject[0];
}

int igVertexDataList_GetVTable(void) {
    union U_14b260 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00527100[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_0014b2a0(void)
{
    igMetaObject_RunStaticInit(igVertexDataList_Register);
}

void igVertexDataList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igVertexDataList_GetMetaObject,
        igVertexDataList_className,
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

