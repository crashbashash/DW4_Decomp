void * FUN_002c8af0(int arg0) {
    FUN_002c8c10();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5867C0), (igMemoryPoolView *)arg0));
}

igMetaObject *FUN_002c8b30(void) {
    if (g_igMetaFieldList_metaObject[0] == 0) {
        g_igMetaFieldList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaFieldList_metaObject[0];
}

igMetaObject *igMetaFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8c10();
    return g_igMetaFieldList_metaObject[0];
}

int igMetaFieldList_GetVTable(void) {
    igMetaFieldList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&DAT_005320a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c8c10(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaFieldList_Register);
}

void igMetaFieldList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaFieldList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMetaFieldList_GetMetaObject,
        igMetaFieldList_className,
        0x14, /* instance size */
        igMetaFieldList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaFieldList_callbackList /* callback list */
    );
}

void thunk_igMetaFieldList_GetMetaObject(void) {
    igMetaFieldList_GetMetaObject();
}

