int FUN_0014e930(int arg0) {
    FUN_0014ea50();
    return igMetaObject_CreateInstance(*(int *)0x55FE48, arg0);
}

igMetaObject *FUN_0014e970(void) {
    if (g_igCustomStateFieldList_metaObject[0] == 0) {
        g_igCustomStateFieldList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igCustomStateFieldList_metaObject[0];
}

igMetaObject *igCustomStateFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateFieldList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ea50();
    return g_igCustomStateFieldList_metaObject[0];
}

int igCustomStateFieldList_GetVTable(void) {
    struct Obj_14ea10 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00526e50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0014ea50(void)
{
    igMetaObject_RunStaticInit(igCustomStateFieldList_Register);
}

void igCustomStateFieldList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateFieldList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateFieldList_GetMetaObject,
        igCustomStateFieldList_className,
        0x14, /* instance size */
        igCustomStateFieldList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateFieldList_callbackList /* callback list */
    );
}

void thunk_igCustomStateFieldList_GetMetaObject(void) {
    igCustomStateFieldList_GetMetaObject();
}

