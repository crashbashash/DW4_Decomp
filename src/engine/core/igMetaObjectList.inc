void * FUN_002c8e10(int arg0) {
    FUN_002c8f30();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5867D0), (igMemoryPoolView *)arg0));
}

igMetaObject *FUN_002c8e50(void) {
    if (g_igMetaObjectList_metaObject[0] == 0) {
        g_igMetaObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaObjectList_metaObject[0];
}

igMetaObject *igMetaObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8f30();
    return g_igMetaObjectList_metaObject[0];
}

int igMetaObjectList_GetVTable(void) {
    igMetaObjectList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&DAT_00531fc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c8f30(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaObjectList_Register);
}

void igMetaObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaObjectList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMetaObjectList_GetMetaObject,
        igMetaObjectList_className,
        0x14, /* instance size */
        igMetaObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaObjectList_callbackList /* callback list */
    );
}

void thunk_igMetaObjectList_GetMetaObject(void) {
    igMetaObjectList_GetMetaObject();
}

