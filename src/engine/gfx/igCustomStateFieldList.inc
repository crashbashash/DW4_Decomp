igMetaObject *g_igCustomStateFieldList_metaObject;

int FUN_0014e930(int arg0) {
    FUN_0014ea50();
    return (int)igMetaObject_CreateInstance(g_igCustomStateFieldList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_0014e970(void) {
    if (g_igCustomStateFieldList_metaObject == 0) {
        g_igCustomStateFieldList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCustomStateFieldList_metaObject;
}

igMetaObject *igCustomStateFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateFieldList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ea50();
    return g_igCustomStateFieldList_metaObject;
}

int igCustomStateFieldList_GetVTable(void) {
    struct Obj_14ea10 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCustomStateFieldList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_0014ea50(void)
{
    igMetaObject_RunStaticInit(igCustomStateFieldList_Register);
}

static igMetaObjectCallback g_igCustomStateFieldList_callbackList[] = { FUN_0014ecd0, 0 };

CallbackArray *igCustomStateFieldList_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCustomStateFieldList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateFieldList_GetMetaObject,
        "igCustomStateFieldList",
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

